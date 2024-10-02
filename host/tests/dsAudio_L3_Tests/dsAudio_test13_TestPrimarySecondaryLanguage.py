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
sys.path.append(dir_path+"/../")

from dsClasses.dsAudio import dsAudioClass
from raft.framework.plugins.ut_raft import utHelperClass
from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.plugins.ut_raft.utPlayer import utPlayer
from raft.framework.plugins.ut_raft.utUserResponse import utUserResponse

class dsAudio_test13_TestPrimarySecondaryLanguage(utHelperClass):

    testName  = "test13_TestPrimarySecondaryLanguage"
    testSetupPath = dir_path + "/dsAudio_L3_testSetup.yml"
    moduleName = "dsAudio"
    rackDevice = "dut"
    streamLanguage = [{"Primary": ["eng", "ger"], "Secondary": ["eng", "spa"]},
                      {"Primary": ["eng", "ger"], "Secondary": ["eng", "spa"]},
                      {"Primary": ["eng", "ger"], "Secondary": ["eng", "spa"]}]

    def __init__(self):
        """
        Initializes the test13_TestPrimarySecondaryLanguage test .

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
        self.deviceProfile = dir_path + "/" + self.cpe.get("test").get("profile")

    def testDownloadAssets(self):
        """
        Downloads the artifacts and streams listed in test-setup configuration file to the dut.

        Args:
            None.
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
                self.testStreams.append(self.deviceDownloadPath + "/" + os.path.basename(streampath))

    def testCleanAssets(self):
        """
        Removes the assets copied to the dut.

        Args:
            None.
        """
        self.deleteFromDevice(self.testStreams)

    def testRunPrerequisites(self):
        """
        Runs Prerequisite commands listed in test-setup configuration file on the dut.

        Args:
            None.
        """

        #Run test specific commands
        test = self.testSetup.get("assets").get("device").get(self.testName)
        cmds = test.get("execute");
        if cmds is not None:
            for cmd in cmds:
                self.writeCommands(cmd)

    #TODO: Current version supports only manual verification.
    def testVerifyAudio(self, language_type:str, language:str, manual=False):
        """
        Verifies whether the audio is fine or not.

        Args:
            language_type (str): Primary:Primary language, Secondary:Secondary language.
            language (str): 3 letter long language as per ISO 639-3. eg: eng - English
            manual (bool, optional): Manual verification (True: manual, False: other verification methods).
                                     Defaults to other verification methods

        Returns:
            bool : returns the status of audio
        """
        if manual == True:
            return self.testUserResponse.getUserYN(f"Is Audio playing as expected with {language_type} {language} Language? (Y/N):")
        else :
            #TODO: Add automation verification methods
            return False

    def testFunction(self):
        """This function will test the Audio Ports by enabling and disabling the ports

        Returns:
            bool
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

        i = 0
        for stream in self.testStreams:

            self.testdsAudio.enableAssociateAudioMixig(False)

            # Start the stream playback
            self.testPlayer.play(stream)

            self.testdsAudio.enableAssociateAudioMixig(True, -32)

            for primary in self.streamLanguage[i]["Primary"]:
                self.log.stepStart(f'Primary Language Test Stream: {stream} Language: {primary}')

                self.testdsAudio.setPrimarySecondaryLanguage("Primary", primary)

                result = self.testVerifyAudio("Primary", primary, True)

                self.log.stepResult(result, f'Primary Language Test Stream: {stream} Language: {primary}')

            self.testdsAudio.enableAssociateAudioMixig(True, 32)

            for secondary in self.streamLanguage[i]["Secondary"]:
                self.log.stepStart(f'Secondary Language Test Stream: {stream} Language: {secondary}')

                self.testdsAudio.setPrimarySecondaryLanguage("Secondary", secondary)

                result = self.testVerifyAudio("Secondary", secondary, True)

                self.log.stepResult(result, f'Secondary Language Test Stream: {stream} Language: {secondary}')

            # Stop the stream playback
            self.testPlayer.stop()

            i += 1

        # Clean the assets downloaded to the device
        self.testCleanAssets()

        # Delete the dsAudio class
        del self.testdsAudio

        return True

if __name__ == '__main__':
    test = dsAudio_test13_TestPrimarySecondaryLanguage()
    test.run(False)
