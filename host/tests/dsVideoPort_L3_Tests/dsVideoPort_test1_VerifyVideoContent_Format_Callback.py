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

from dsClasses.dsVideoPort import dsVideoPortClass
from raft.framework.plugins.ut_raft import utHelperClass
from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.plugins.ut_raft.utPlayer import utPlayer
from raft.framework.plugins.ut_raft.utUserResponse import utUserResponse

class dsVideoPort_test1_VerifyVideoContent_Formats(utHelperClass):

    testName  = "test1_VerifyVideoContent_Formats"
    testSetupPath = dir_path + "/dsVideoPort_L3_testSetup.yml"
    moduleName = "dsVideoPort"
    rackDevice = "dut"
    HDRFormats = ["NONE", "HDR10", "HLG", "DolbyVision", "TechnicolorPrime", "HDR10PLUS", "SDR"]

    def __init__(self):
        """
        Initializes the test1_VerifyVideoContent_Formats test .

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

        #download test artifacts to device
        url = self.testSetup.assets.device.test1_VerifyVideoContent_Formats.artifacts
        if url is not None:
            self.downloadToDevice(url, self.deviceDownloadPath, self.rackDevice)

        #download test streams to device
        url = self.testSetup.assets.device.test1_VerifyVideoContent_Formats.streams
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
        cmds = self.testSetup.assets.device.test1_VerifyVideoContent_Formats.execute
        if cmds is not None:
            for cmd in cmds:
                self.writeCommands(cmd)

    #TODO: Current version supports only manual verification.
    def find_VideoFormat_Status(self, input_str: str, status: str) -> bool:
        if status in input_str:
            return True
        return False

    def testFunction(self):
        """This function will test the Video Ports by enabling and disabling the ports

        Returns:
            bool
        """

        # Download the assets listed in test setup configuration file
        self.testDownloadAssets()

        # Run Prerequisites listed in the test setup configuration file
        self.testRunPrerequisites()


        # Create the dsVideoPort class
        self.testdsVideoPort = dsVideoPortClass(self.deviceProfile, self.hal_session)

        self.log.testStart("test1_VerifyVideoContent_Formats", '1')

        # Initialize the dsVideoPort module
        self.testdsVideoPort.initialise()

        # Loop through the supported Video ports
        for port,index in self.testdsVideoPort.getSupportedPorts():
            self.log.stepStart(f'Enable {port} Port')
            self.log.step(f'Enable {port} Port')

            # Enable the Video port
            self.testdsVideoPort.enablePort(port, index)

            i = 0
            for formats in self.HDRFormats:
                # Start the stream playback
                if formats not in ["NONE", "TechnicolorPrime"]:
                    self.testPlayer.play(self.testStreams[i])
                    i+=1
                    # Pause execution for 0.5 second
                    time.sleep(1)

                result = self.testdsVideoPort.read_Callbacks("Video Format Callback dsHDRStandard_t:")
                print(result)
                if formats not in "TechnicolorPrime":
                    if self.find_VideoFormat_Status(result, f'dsHDRSTANDARD_{formats}'):
                        self.log.stepResult(True,f'{formats} VideoFormat Callback found')
                    else:
                        self.log.stepResult(False,f'{formats} VideoFormat Callback found')
                if formats not in ["NONE", "TechnicolorPrime"]:
                    # Stop the stream playback
                    self.testPlayer.stop()
                    time.sleep(0.1)

        # Clean the assets downloaded to the device
        self.testCleanAssets()

        # Delete the dsVideoPort class
        del self.testdsVideoPort

        return result

if __name__ == '__main__':
    test = dsVideoPort_test1_VerifyVideoContent_Formats()
    test.run(False)
