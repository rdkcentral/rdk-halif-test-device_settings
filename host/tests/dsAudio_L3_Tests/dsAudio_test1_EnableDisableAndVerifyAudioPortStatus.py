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

dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(dir_path+"/../")

from dsClasses.dsAudio import dsAudioClass
from raft.framework.plugins.ut_raft import utHelperClass
from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.plugins.ut_raft.utPlayer import utPlayer
from raft.framework.plugins.ut_raft.utUserResponse import utUserResponse

class dsAudio_test1_EnableDisableAndVerifyAudioPortStatus(utHelperClass):

    testName  = "test1_EnableDisableAndVerifyAudioPortStatus"
    testSetupPath = dir_path + "/dsAudio_L3_testSetup.yml"
    moduleName = "dsAudio"
    rackDevice = "dut"

    def __init__(self):
        """
        Initializes the test1_EnableDisableAndVerifyAudioPortStatus test .

        Args:
            None.
        """
        super().__init__(self.testName, '1')

        # Test Setup configuration file
        self.testSetup = ConfigRead(self.testSetupPath, self.moduleName)

        # Open Session of player
        self.player_session = self.dut.getConsoleSession("ssh_player")

        # Create player Class
        self.testPlayer = utPlayer(self.player_session)

         # Create user response Class
        self.testUserResponse = utUserResponse()

        # Get path to device profile file
        self.deviceProfile = self.cpe.get("test").get("profile")

    def testDownloadAssets(self):
        """
        Downloads the artifacts and streams listed in test-setup configuration file to the dut.

        Args:
            None.
        """

        # List of streams with path
        self.testStreams = []

        self.deviceDownloadPath = self.cpe.get("target_directory")

        #download test artifacts to device
        url = self.testSetup.assets.device.test1_EnableDisableAndVerifyAudioPortStatus.artifacts
        if url is not None:
            self.downloadToDevice(url, self.deviceDownloadPath, self.rackDevice)

        #download test streams to device
        url = self.testSetup.assets.device.test1_EnableDisableAndVerifyAudioPortStatus.streams
        if url is not None:
            self.downloadToDevice(url, self.deviceDownloadPath, self.rackDevice)
            self.testStreams.append(self.deviceDownloadPath + "/" + os.path.basename(url))

    def testRunPrerequisites(self):
        """
        Runs Prerequisite commands listed in test-setup configuration file on the dut.

        Args:
            None.
        """

        #Run test specific commands
        cmds = self.testSetup.assets.device.test1_EnableDisableAndVerifyAudioPortStatus.execute
        if cmds is not None:
            self.writeCommandsOnDevice(cmds, None, self.rackDevice)

    def testVerifyAudio(self, manual=False):
        """
        Verifies whether the audio is fine or not.

        Args:
            manual (bool, optional): Manual verification (True: manual, False: other verification methods).
                                     Defaults to other verification methods

        Returns:
            bool
        """
        if manual == True:
            return self.testUserResponse.getUserYN("Is audio playing on the port? (Y/N):")
        else :
            #TOD: Add automation verification methods
            return False

    def testFunction(self):
        """This function will test the Audio Ports by enabling and disabling the ports

        Returns:
            bool
        """

        # Download the assets
        self.testDownloadAssets()
        self.testRunPrerequisites()

        # Start the stream playback
        self.testPlayer.play(self.testStreams[0])

        # Create the dsAudio class
        self.testdsAudio = dsAudioClass(self.deviceProfile, self.session)

        self.log.testStart("test1_EnableDisableAndVerifyAudioPortStatus", '1')

        self.testdsAudio.initialise()

        for port,index in self.testdsAudio.getSupportedPorts():
            self.log.stepStart(f'Enable {port} Port')
            self.log.step(f'Enable {port} Port')

            self.testdsAudio.enablePort(port, index)

            self.log.step(f'Verify {port} Port')
            result = self.testVerifyAudio(True)

            self.log.stepResult(result, f'Audio Verification {port} Port')
            self.log.stepStart(f'Disable {port} Port')

            self.testdsAudio.disablePort(port, index)

            self.log.step(f'Verify {port} Port')
            result = self.testVerifyAudio(True)

            self.log.stepResult(not result, f'Audio Verification {port} Port')

        self.dsAudioPlayStop()

        return result

if __name__ == '__main__':
    test = dsAudio_test1_EnableDisableAndVerifyAudioPortStatus()
    test.run(False)
