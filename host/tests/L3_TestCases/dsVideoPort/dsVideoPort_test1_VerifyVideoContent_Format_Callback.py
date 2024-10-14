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

# Append the parent directory to system path for module imports
dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(dir_path+"/../../")

# Import required classes from modules
from dsClasses.dsVideoPort import dsVideoPortClass
from raft.framework.plugins.ut_raft import utHelperClass
from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.plugins.ut_raft.utPlayer import utPlayer
from raft.framework.plugins.ut_raft.utUserResponse import utUserResponse

class dsVideoPort_test1_VerifyVideoContent_Formats(utHelperClass):

    """
    A class used to test video content formats through different video ports.

    Attributes:
        testName (str): Name of the test.
        testSetupPath (str): Path to the test setup YAML file.
        moduleName (str): The module being tested.
        rackDevice (str): Device under test (DUT).
        HDRFormats (list): Supported HDR formats for testing.
    """

    testName  = "test1_VerifyVideoContent_Formats"
    testSetupPath = dir_path + "/dsVideoPort_L3_testSetup.yml"
    moduleName = "dsVideoPort"
    rackDevice = "dut"
    HDRFormats = ["NONE", "HDR10", "HLG", "DolbyVision", "TechnicolorPrime", "HDR10PLUS", "SDR"]

    def __init__(self):
        """
        Initializes the dsVideoPort_test1_VerifyVideoContent_Formats class and sets up test resources.

        This includes initializing the test setup, player session, and HAL test session,
        as well as preparing the user response and device profile paths.
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
        Downloads required test assets (artifacts and streams) to the device under test (DUT).

        The paths are defined in the test setup configuration file.
        """

        # List of streams with path
        self.testStreams = []

        self.deviceDownloadPath = self.cpe.get("target_directory")

        #download test artifacts to device
        url = self.testSetup.assets.device.test1_VerifyVideoContent_Formats.artifacts
        if url is not None:
            self.downloadToDevice(url, self.deviceDownloadPath, self.rackDevice)

        #download test streams to device
        #stream_url = self.testSetup.assets.device.test1_VerifyVideoContent_Formats.streams[format_index]
        #stream_download_path = self.deviceDownloadPath + "/" + os.path.basename(stream_url)

        # Download the stream to the device as a list
        #self.downloadToDevice([stream_url], self.deviceDownloadPath, self.rackDevice)

        #return stream_download_path
    def downloadStreamForFormat(self, format_index):
        """
        Downloads the specific stream for the HDR format being tested.

        Args:
            format_index (int): The index corresponding to the HDR format in the test setup.

        Returns:
            str: The full path of the downloaded stream.
        """
        stream_url = self.testSetup.assets.device.test1_VerifyVideoContent_Formats.streams[format_index]
        stream_download_path = self.deviceDownloadPath + "/" + os.path.basename(stream_url)

        # Download the stream to the device as a list
        self.downloadToDevice([stream_url], self.deviceDownloadPath, self.rackDevice)

        return stream_download_path
    def testCleanSingleAsset(self, stream_path):
        """
        Cleans up by removing a single stream from the DUT after it has been played.

        Args:
            stream_path (str): The full path of the stream to be deleted.
        """
        self.deleteFromDevice([stream_path])

    def testCleanAssets(self):
        """
        Cleans up by removing the test assets downloaded to the DUT.
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
        """
        Checks if a specific video format status is present in the input string.

        Args:
            input_str (str): The string to search in.
            status (str): The video format status to look for.

        Returns:
            bool: True if the status is found, False otherwise.
        """
        if status in input_str:
            return True
        return False

    def testFunction(self):
        """
        Main test function that verifies video formats on supported ports by enabling and disabling the ports.

        This includes playing and stopping video streams, checking HDR formats, and verifying callbacks.

        Returns:
            bool: The result of the final video format callback check.
        """

        # Step 1: Run prerequisite commands
        self.testDownloadAssets()
        self.testRunPrerequisites()

        # Step 2: Initialize and create the dsVideoPort class
        self.testdsVideoPort = dsVideoPortClass(self.deviceProfile, self.hal_session)
        self.testdsVideoPort.initialise()

        self.log.testStart("test1_VerifyVideoContent_Formats", '1')

        # Step 3: Loop through the supported video ports and test HDR formats
        for port, index in self.testdsVideoPort.getSupportedPorts():
            self.log.stepStart(f'Enable {port} Port')
            self.testdsVideoPort.enablePort(port, index)

            # Loop through HDR formats, download stream, play it, and then delete it
            for i, format in enumerate(self.HDRFormats):
                if format not in ["NONE", "TechnicolorPrime"]:
                    # Step 3.1: Download the stream for this HDR format
                    stream_path = self.downloadStreamForFormat(i)

                    # Step 3.2: Play the corresponding stream
                    self.testPlayer.play(stream_path)
                    time.sleep(10)
                result = self.testdsVideoPort.read_Callbacks("Video Format Callback dsHDRStandard_t:")
                print(result)
                if format not in "TechnicolorPrime":
                    if self.find_VideoFormat_Status(result, f'dsHDRSTANDARD_{format}'):
                        self.log.stepResult(True,f'{format} VideoFormat Callback found')
                    else:
                        self.log.stepResult(False,f'{format} VideoFormat Callback Not found')
                if format not in ["NONE", "TechnicolorPrime"]:
                    # Stop the stream playback
                    self.testPlayer.stop()
                    time.sleep(0.1)
                    self.testCleanSingleAsset(stream_path)

        # Step 4: Clean up the test resources
        del self.testdsVideoPort

        return result

if __name__ == '__main__':
    test = dsVideoPort_test1_VerifyVideoContent_Formats()
    test.run(False)
