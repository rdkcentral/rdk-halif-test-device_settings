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

# Get directory path and append to system path
dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(dir_path+"/../")

# Import required classes from modules
from dsClasses.dsVideoPort import dsVideoPortClass
from raft.framework.plugins.ut_raft import utHelperClass
from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.plugins.ut_raft.utPlayer import utPlayer
from raft.framework.plugins.ut_raft.utUserResponse import utUserResponse

class dsVideoPort_test2_Check_DisplayConnected_VideoPort(utHelperClass):
    """
    A class to test the display connectivity via different video ports.

    Attributes:
        testName (str): The name of the test.
        testSetupPath (str): Path to the test setup configuration file.
        moduleName (str): Module name for the test.
        rackDevice (str): Device under test.
    """

    testName  = "test2_Check_DisplayConnected_VideoPort"
    testSetupPath = dir_path + "/dsVideoPort_L3_testSetup.yml"
    moduleName = "dsVideoPort"
    rackDevice = "dut"

    def __init__(self):
        """
        Initializes the test and sets up sessions and player classes.

        Initializes test setup, player, and HAL test sessions, and prepares the
        user response and device profile paths.
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
        url = self.testSetup.assets.device.test2_Check_DisplayConnected_VideoPort.artifacts
        if url is not None:
            self.downloadToDevice(url, self.deviceDownloadPath, self.rackDevice)

        #download test streams to device
        url = self.testSetup.assets.device.test2_Check_DisplayConnected_VideoPort.streams
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
        cmds = self.testSetup.assets.device.test2_Check_DisplayConnected_VideoPort.execute
        if cmds is not None:
            for cmd in cmds:
                self.writeCommands(cmd)

    #TODO: Current version supports only manual verification.
    def testVerifyDisplay(self, manual=False):
        """
        Verifies whether video is being displayed or not.

        Args:
            manual (bool, optional): Indicates if manual verification is required.
                                     Defaults to False (automatic verification).

        Returns:
            bool: Verification result (True if the video is displayed, False otherwise).
        """
        if manual == True:
            return self.testUserResponse.getUserYN("Is Video Display on the port? (Y/N):")
        else :
            #TODO: Add automation verification methods
            return False

    def testEnablePortAndVerify(self, port, index):
        """
        Enables a video port and verifies video output.

        Args:
            port (str): The video port to be enabled.
            index (int): The index of the video port.

        Returns:
            bool: The result of the video port verification.
        """
        # Enable video port
        self.log.stepStart(f'Enable {port} Port')
        self.testdsVideoPort.enablePort(port, index)

        # Enable HDCP for source devices
        if self.testdsVideoPort.getDeviceType():
            self.testdsVideoPort.enable_HDCP(port, index)

        # Verify video display
        self.log.step(f'Verify {port} Port')
        result = self.testVerifyDisplay(True)
        self.log.stepResult(result, f'VideoPort Verification {port} Port')
        return result

    def testDisablePortAndVerify(self, port, index):
        """
        Disables a video port and verifies that no video is displayed.

        Args:
            port (str): The video port to be disabled.
            index (int): The index of the video port.

        Returns:
            bool: The result of the video port disable verification.
        """
        self.log.stepStart(f'Disable {port} Port')
        self.testdsVideoPort.disablePort(port, index)

        # Verify that the video is no longer displayed
        self.log.step(f'Verify {port} Port')
        result = not self.testVerifyDisplay(True)
        self.log.stepResult(result, f'VideoPort Disable Verification {port} Port')
        return result

    def testFunction(self):
        """
        The main test function that checks display connectivity by enabling and disabling video ports.

        This function downloads assets, runs prerequisites, enables/disables ports, and verifies
        display connectivity for each port.

        Returns:
            bool: The result of the final video verification.
        """
        self.testDownloadAssets()  # Download required assets
        self.testRunPrerequisites()  # Run test prerequisites
        self.testPlayer.play(self.testStreams[0])  # Start playback

        # Create the dsVideoPort class and initialize if sink device
        self.testdsVideoPort = dsVideoPortClass(self.deviceProfile, self.hal_session)
        self.log.testStart(self.testName, '1')
        if not self.testdsVideoPort.getDeviceType():
            self.testdsVideoPort.initialise()

        # Loop through supported video ports and verify connectivity
        for port, index in self.testdsVideoPort.getSupportedPorts():
            # Enable and verify the video port
            result = self.testEnablePortAndVerify(port, index)

            # Disable and verify the video port
            result = result and self.testDisablePortAndVerify(port, index)

        self.testPlayer.stop()  # Stop playback
        self.testCleanAssets()  # Clean up assets
        del self.testdsVideoPort  # Clean up the video port class

        return result

if __name__ == '__main__':
    test = dsVideoPort_test2_Check_DisplayConnected_VideoPort()
    test.run(False)
