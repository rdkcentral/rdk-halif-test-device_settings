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
sys.path.append(dir_path+"/../../")

# Import required classes from modules
from dsClasses.dsVideoPort import dsVideoPortClass
from raft.framework.plugins.ut_raft import utHelperClass
from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.plugins.ut_raft.utPlayer import utPlayer
from raft.framework.plugins.ut_raft.utUserResponse import utUserResponse

class dsVideoPort_test5_VerifyHDCP_Callback(utHelperClass):
    """
    Test class for verifying HDCP callback during HDMI plug/unplug.
    """

    testName  = "test5_VerifyHDCP_Callback"
    testSetupPath = dir_path + "/dsVideoPort_L3_testSetup.yml"
    moduleName = "dsVideoPort"
    rackDevice = "dut"

    def __init__(self):
        """
        Initializes the test5_VerifyHDCP_Callback test with necessary setup.

        Args:
            None.
        """
        super().__init__(self.testName, '1')

        # Test Setup configuration file
        self.testSetup = ConfigRead(self.testSetupPath, self.moduleName)

        # Open Session for player
        #self.player_session = self.dut.getConsoleSession("ssh_player")

        # Open Session for hal test
        self.hal_session = self.dut.getConsoleSession("ssh_hal_test")

        #player = self.cpe.get("test").get("player")

        # Create player Class
        #self.testPlayer = utPlayer(self.player_session, player)

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
        url = self.testSetup.assets.device.test5_VerifyHDCP_Callback.artifacts
        if url is not None:
            self.downloadToDevice(url, self.deviceDownloadPath, self.rackDevice)

        #download test streams to device
        url = self.testSetup.assets.device.test5_VerifyHDCP_Callback.streams
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
        cmds = self.testSetup.assets.device.test5_VerifyHDCP_Callback.execute
        if cmds is not None:
            for cmd in cmds:
                self.writeCommands(cmd)

    #TODO: Current version supports only manual verification.
    def testUnplugHDMI(self, unplug:True, manual=False):
        """
        Verifies whether the Video&audio displayed or not.

        Args:
            manual (bool, optional): Manual verification (True: manual, False: other verification methods).
                                     Defaults to other verification methods

        Returns:
            bool
        """
        if manual == True:
            if unplug == True:
                return self.testUserResponse.getUserYN("UnPlug the HDMI Cable? (Y/N):")
            else :
                return self.testUserResponse.getUserYN("Plug the HDMI Cable? (Y/N):")
        else :
            #TODO: Add automation verification methods
            return False

    def find_HDCPStatus(self, input_str: str, status: str) -> bool:
        """
        Finds HDCP status in a given input string.

        Args:
            input_str (str): The input log containing HDCP status.
            status (str): The HDCP status string to look for.

        Returns:
            bool: True if the status is found, False otherwise.
        """
        if status in input_str:
            return True
        return False

    def testEnablePortAndVerifyHDCP(self, port, index):
        """
        Enables a video port, performs HDMI plug/unplug actions, and verifies HDCP callbacks.

        Args:
            port (str): The video port name.
            index (int): The port index.

        Returns:
            bool: Result of the HDCP verification.
        """
        self.log.stepStart(f'Enable {port} Port')
        self.testdsVideoPort.enablePort(port, index)

        # Enable HDCP for the port
        self.testdsVideoPort.enable_HDCP(port, index)

        # Verify unplug HDMI event
        result = self.testUnplugHDMI(unplug=True, manual=True)
        result = self.testdsVideoPort.read_Callbacks("HDCP Status Callback dsHdcpStatus_t:")
        if self.find_HDCPStatus(result, "dsHDCP_STATUS_UNPOWERED"):
            self.log.stepResult(True, "HDMI Unplug Callback found")
        else:
            self.log.stepResult(False, "HDMI Unplug Callback Not found")

        # Verify plug HDMI event
        result = self.testUnplugHDMI(unplug=False, manual=True)
        result = self.testdsVideoPort.read_Callbacks("HDCP Status Callback dsHdcpStatus_t:")
        if self.find_HDCPStatus(result, "dsHDCP_STATUS_AUTHENTICATED"):
            self.log.stepResult(True, "HDMI Plug Callback found")
        else:
            self.log.stepResult(False, "HDMI Plug Callback Not found")

        return result

    def testFunction(self):
        """
        Main test function to verify HDCP status callbacks during HDMI plug/unplug events.

        Returns:
            bool: Final result of the test.
        """
        self.testDownloadAssets()
        self.testRunPrerequisites()

        # Initialize the dsVideoPort class
        self.testdsVideoPort = dsVideoPortClass(self.deviceProfile, self.hal_session)
        self.testdsVideoPort.initialise()

        # Loop through all supported video ports and verify HDCP callbacks
        for port, index in self.testdsVideoPort.getSupportedPorts():
            result = self.testEnablePortAndVerifyHDCP(port, index)

        self.testCleanAssets()
        del self.testdsVideoPort

        return result

if __name__ == '__main__':
    test = dsVideoPort_test5_VerifyHDCP_Callback()
    test.run(False)
