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
sys.path.append(os.path.join(dir_path, "../"))

from dsClasses.dsAudio import dsAudioClass
from raft.framework.plugins.ut_raft import utHelperClass
from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.plugins.ut_raft.utPlayer import utPlayer
from raft.framework.plugins.ut_raft.utUserResponse import utUserResponse

class dsAudio_test23_AssociateMix(utHelperClass):
    """
    Test class for verifying the functionality of audio mixing in the dsAudio module.

    This test validates the associate audio mixing feature of the device under test (DUT)
    by adjusting fader levels and checking audio playback with and without mixing enabled.

    Attributes:
        testName (str): Name of the test.
        testSetupPath (str): Path to the test setup configuration file.
        moduleName (str): Name of the module being tested.
        rackDevice (str): Identifier for the device under test.
        faderValues (list): List of fader values to test (in decibels).
    """

    testName  = "test23_AssociateMix"
    testSetupPath = os.path.join(dir_path, "dsAudio_L3_testSetup.yml")
    moduleName = "dsAudio"
    rackDevice = "dut"
    faderValues = [-32, 0, 32]

    def __init__(self):
        """
        Initializes the dsAudio_test23_AssociateMix test class.

        Sets up the necessary configuration, player session, and user response handling.

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

        # remove the callback log files
        self.deleteFromDevice([self.connectionCB, self.formatCB, self.atmosCB])

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
    def testVerifyAssociateAudioMix(self, mixer_status, fader, manual=False):
        """
        Verifies the audio playback quality under the specified mixing conditions.

        Args:
            mixer_status (bool): True if associate audio mixing is enabled, False otherwise.
            fader (int): Fader control value (e.g., -32 for mute, 32 for full).
            manual (bool, optional): Flag for manual verification (True for manual, False for automated).
                                     Defaults to False.

        Returns:
            bool: True if audio is as expected; otherwise, False.
        """
        if manual == True:
            return self.testUserResponse.getUserYN(f"Is Audio playing as expected with Mixing: {mixer_status} fader: {fader}? (Y/N):")
        else :
            #TODO: Add automation verification methods
            return False

    def testFunction(self):
        """
        Executes the associate mixing test.

        This method performs the following steps:
        - Downloads required assets.
        - Runs prerequisite commands.
        - Initializes the dsAudio module.
        - Tests audio mixing by playing each stream with various fader settings.
        - Cleans up downloaded assets and terminates the dsAudio module.

        Returns:
            bool: True if the test execution completes successfully; otherwise, False.
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

        for stream in self.testStreams:

            self.log.stepStart(f'Associate Mixing Disabled, Stream: {stream} Fader: 0')

            self.testdsAudio.enableAssociateAudioMixig(False)

            # Start the stream playback
            self.testPlayer.play(stream)

            result = self.testVerifyAssociateAudioMix(False, 0, True)

            self.log.stepResult(result, f'Associate Mixing Disabled, Stream: {stream} Fader: 0')

            for fade in self.faderValues:
                self.log.stepStart(f'Associate Mixing Stream: {stream} Fader: {fade}')

                self.testdsAudio.enableAssociateAudioMixig(True, fade)

                result = self.testVerifyAssociateAudioMix(True, fade, True)

                self.log.stepResult(result, f'Associate Mixing Stream: {stream} Fader: {fade}')

            # Stop the stream playback
            self.testPlayer.stop()

        # Clean the assets downloaded to the device
        self.testCleanAssets()

        # Terminate dsAudio Module
        self.testdsAudio.terminate()

        # Delete the dsAudio class
        del self.testdsAudio

        return True

if __name__ == '__main__':
    test = dsAudio_test23_AssociateMix()
    test.run(False)
