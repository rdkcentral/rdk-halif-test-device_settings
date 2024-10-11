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

# Append the parent directory to system path for module imports
dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(dir_path+"/../")

# Import required classes from modules
from dsClasses.dsVideoPort import dsVideoPortClass
from raft.framework.plugins.ut_raft import utHelperClass
from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.plugins.ut_raft.utPlayer import utPlayer
from raft.framework.plugins.ut_raft.utUserResponse import utUserResponse

class dsVideoPort_test7_ResetToSDRMode(utHelperClass):
    """
    Test class for resetting video output to SDR mode and verifying playback.
    """

    testName  = "test7_ResetToSDRMode"
    testSetupPath = dir_path + "/dsVideoPort_L3_testSetup.yml"
    moduleName = "dsVideoPort"
    rackDevice = "dut"

    def __init__(self):
        """
        Initializes the test7_ResetToSDRMode test case with required setup.

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
        url = self.testSetup.assets.device.test7_ResetToSDRMode.artifacts
        if url is not None:
            self.downloadToDevice(url, self.deviceDownloadPath, self.rackDevice)

        #download test streams to device
        url = self.testSetup.assets.device.test7_ResetToSDRMode.streams
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
        cmds = self.testSetup.assets.device.test7_ResetToSDRMode.execute
        if cmds is not None:
            for cmd in cmds:
                self.writeCommands(cmd)

    #TODO: Current version supports only manual verification.
    def testVerifyPlayback(self, manual=False):
        """
        Verifies whether the Video&audio displayed or not.

        Args:
            manual (bool, optional): Manual verification (True: manual, False: other verification methods).
                                     Defaults to other verification methods

        Returns:
            bool: True if playback is verified successfully, False otherwise.
        """
        if manual == True:
            return self.testUserResponse.getUserYN("Is Video PlayBack is HDR on the port? (Y/N):")
        else :
            #TODO: Add automation verification methods
            return False

    def enablePortAndResetToSDR(self, port, index):
        """
        Enables the video port and resets the output to SDR mode.

        Args:
            port (str): The name of the video port.
            index (int): The port index.

        Returns:
            bool: Result of playback verification.
        """
        self.log.stepStart(f'Enable {port} Port')
        self.testdsVideoPort.enablePort(port, index)

        # Enable HDCP if required for the device
        if self.testdsVideoPort.getDeviceType():
            self.testdsVideoPort.enable_HDCP(port, index)

        # Reset output to SDR mode
        self.testdsVideoPort.resetOutputToSDR(port, index)
        result = self.testVerifyPlayback(manual=True)

        # Log the verification result
        self.log.stepResult(not result, "Verified parameters using HDMI Analyzer")

        return result

    def testFunction(self):
        """
        Main test function that resets video output to SDR mode and verifies playback.

        Returns:
            bool: Final test result.
        """
        # Download the assets listed in the test setup configuration file
        self.testDownloadAssets()

        # Run prerequisites listed in the test setup configuration file
        self.testRunPrerequisites()

        # Start the stream playback
        self.testPlayer.play(self.testStreams[0])

        # Create and initialize the dsVideoPort class
        self.testdsVideoPort = dsVideoPortClass(self.deviceProfile, self.hal_session)

        self.log.testStart(self.testName, '1')

        # Loop through supported video ports and verify playback after resetting to SDR mode
        for port, index in self.testdsVideoPort.getSupportedPorts():
            result = self.enablePortAndResetToSDR(port, index)

        # Stop the stream playback
        self.testPlayer.stop()

        # Clean the assets downloaded to the device
        self.testCleanAssets()

        # Delete the dsVideoPort class
        del self.testdsVideoPort

        return result

if __name__ == '__main__':
    test = dsVideoPort_test7_ResetToSDRMode()
    test.run(False)
