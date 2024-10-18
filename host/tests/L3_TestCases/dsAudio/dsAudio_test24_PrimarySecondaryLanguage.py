#!/usr/bin/env python3
#** *****************************************************************************
# *
# * If not stated otherwise in this file or this component's LICENSE file the
# * following copyright and licenses apply:
# *
# * Copyright 2024 RDK Management
# *
# * Licensed under the Apache License, Version 2.0 (the "License");
# * you may not use this file except in compliance with the License.
# * You may obtain a copy of the License at
# *
# *
# http://www.apache.org/licenses/LICENSE-2.0
# *
# * Unless required by applicable law or agreed to in writing, software
# * distributed under the License is distributed on an "AS IS" BASIS,
# * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# * See the License for the specific language governing permissions and
# * limitations under the License.
# *
#* ******************************************************************************

import os
import sys
import time

dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(dir_path, "../../"))

from dsClasses.dsAudio import dsAudioClass
from raft.framework.plugins.ut_raft import utHelperClass
from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.plugins.ut_raft.utPlayer import utPlayer
from raft.framework.plugins.ut_raft.utUserResponse import utUserResponse

class dsAudio_test24_PrimarySecondaryLanguage(utHelperClass):
    """
    Test class for verifying the functionality of Primary and secondary languages.

    Attributes:
        testName (str): Name of the test.
        testSetupPath (str): Path to the test setup configuration file.
        moduleName (str): Name of the module being tested.
        rackDevice (str): Identifier for the device under test.
        streamLanguage (dict): List of Dictionary of languages.
    """
    testName  = "test24_PrimarySecondaryLanguage"
    testSetupPath = os.path.join(dir_path, "dsAudio_L3_testSetup.yml")
    moduleName = "dsAudio"
    rackDevice = "dut"
    streamLanguage = [{"Primary": ["eng", "spa", "zho"], "Secondary": ["eng", "spa", "zho"]}]

    def __init__(self):
        """
        Initializes the test24_PrimarySecondaryLanguage test .

        Args:
            None.
        """
        super().__init__(self.testName, '1')

        # Test Setup configuration file
        self.testSetup = ConfigRead(self.testSetupPath, self.moduleName)

        # Open Session for player
        self.player_session = self.dut.getConsoleSession("ssh_player")

        # Open Session for hal test
        self.hal_session = self.dut.getConsoleSession("ssh_hal_test")

        player = self.cpe.get("test").get("player")

        # Create player Class
        self.testPlayer = utPlayer(self.player_session, player)

         # Create user response Class
        self.testUserResponse = utUserResponse()

        # Get path to device profile file
        self.deviceProfile = os.path.join(dir_path, self.cpe.get("test").get("profile"))

    def testDownloadAssets(self):
        """
        Downloads the test artifacts and streams listed in the test setup configuration.

        This function retrieves audio streams and other necessary files and
        saves them on the DUT (Device Under Test).

        Args:
            None
        """

        # List of streams with path
        self.testStreams = []

        self.deviceDownloadPath = self.cpe.get("target_directory")

        test = self.testSetup.get("assets").get("device").get(self.testName)

        #download test artifacts to device
        url = test.get("artifacts")
        if url is not None:
            self.downloadToDevice(url, self.deviceDownloadPath, self.rackDevice)

        #download test streams to device
        url =  test.get("streams")
        if url is not None:
            self.downloadToDevice(url, self.deviceDownloadPath, self.rackDevice)
            for streampath in url:
                self.testStreams.append(os.path.join(self.deviceDownloadPath, os.path.basename(streampath)))

    def testCleanAssets(self):
        """
        Removes the downloaded assets and test streams from the DUT after test execution.

        Args:
            None
        """
        self.deleteFromDevice(self.testStreams)


    def testRunPrerequisites(self):
        """
        Executes prerequisite commands listed in the test setup configuration file on the DUT.

        Args:
            None
        """

        #Run test specific commands
        test = self.testSetup.get("assets").get("device").get(self.testName)
        cmds = test.get("execute");
        if cmds is not None:
            for cmd in cmds:
                self.writeCommands(cmd)

    #TODO: Current version supports only manual verification.
    def testVerifyAudio(self, port, language_type:str, language:str, manual=False):
        """
        Verifies the audio stream in the specified language (Primary or Secondary).

        The verification can be performed manually or through an automated method (if available).
        Currently, the manual method prompts the user to confirm whether the audio is playing
        correctly.

        Args:
            port (str) : The audio port to verify.
            language_type (str): Specifies the language type, either "Primary" or "Secondary".
            language (str): The 3-letter ISO 639-3 code representing the language (e.g., 'eng' for English).
            manual (bool, optional): If True, prompts the user for manual verification.
                                     Defaults to automated verification (when implemented).

        Returns:
            bool: The status of the audio verification (True if audio is correct, False otherwise).
        """
        if manual == True:
            return self.testUserResponse.getUserYN(f"Is Audio playing on {port} as expected with {language_type} {language} Language? (Y/N):")
        else :
            #TODO: Add automation verification methods
            return False

    def testFunction(self):
        """
        Tests the Primary and Secondary audio language switching functionality.

        This method validates the audio playback for both primary and secondary languages
        by configuring the audio streams as per the test setup, running the test, and verifying
        the results manually.

        Returns:
            bool: True if the test completes successfully.
        """

        # Download the assets listed in test setup configuration file
        self.testDownloadAssets()

        # Run Prerequisites listed in the test setup configuration file
        self.testRunPrerequisites()

        # Create the dsAudio class
        self.testdsAudio = dsAudioClass(self.deviceProfile, self.hal_session)

        self.log.testStart(self.testName, '1')

        # Initialize the dsAudio module
        self.testdsAudio.initialise(self.testdsAudio.getDeviceType())

        for port,index in self.testdsAudio.getSupportedPorts():
            # Enable the audio port
            self.testdsAudio.enablePort(port, index)

            for i, stream in enumerate(self.testStreams):

                self.testdsAudio.enableAssociateAudioMixig(False)

                # Start the stream playback
                self.testPlayer.play(stream)

                for secondary in self.streamLanguage[i]["Secondary"]:
                    self.log.stepStart(f'Secondary Language Test Stream: {stream} Language: {secondary}')

                    self.testdsAudio.setPrimarySecondaryLanguage("Secondary", secondary)

                    result = self.testVerifyAudio(port, "Secondary", secondary, True)

                    self.log.stepResult(result, f'Secondary Language Test Stream: {stream} Language: {secondary}')

                # Stop the stream playback
                self.testPlayer.stop()

                time.sleep(3)

                # Start the stream playback
                self.testPlayer.play(stream)

                for primary in self.streamLanguage[i]["Primary"]:
                    self.log.stepStart(f'Primary Language Test Stream: {stream} Language: {primary}')

                    self.testdsAudio.setPrimarySecondaryLanguage("Primary", primary)

                    result = self.testVerifyAudio(port, "Primary", primary, True)

                    self.log.stepResult(result, f'Primary Language Test Stream: {stream} Language: {primary}')

                # Stop the stream playback
                self.testPlayer.stop()

            # Disable the audio port
            self.testdsAudio.disablePort(port, index)

        # Clean the assets downloaded to the device
        self.testCleanAssets()

        # Terminate dsAudio Module
        self.testdsAudio.terminate()

        # Delete the dsAudio class
        del self.testdsAudio

        return True

if __name__ == '__main__':
    test = dsAudio_test24_PrimarySecondaryLanguage()
    test.run(False)
