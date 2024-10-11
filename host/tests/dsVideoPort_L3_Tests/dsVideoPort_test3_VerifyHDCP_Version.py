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

class dsVideoPort_test3_VerifyHDCP_Version(utHelperClass):
    """
    A class to test and verify HDCP version through supported video ports.

    Attributes:
        testName (str): Name of the test.
        testSetupPath (str): Path to the test setup configuration file.
        moduleName (str): Name of the module being tested.
        rackDevice (str): Device under test (DUT).
    """

    testName  = "test3_VerifyHDCP_Version"
    testSetupPath = dir_path + "/dsVideoPort_L3_testSetup.yml"
    moduleName = "dsVideoPort"
    rackDevice = "dut"

    def __init__(self):
        """
        Initializes the test3_VerifyHDCP_Version test setup and configuration.

        Initializes sessions, reads the test setup, and prepares the user response.
        """
        super().__init__(self.testName, '1')

        # Initialize the test setup configuration
        self.testSetup = ConfigRead(self.testSetupPath, self.moduleName)

        # Create session for HAL test
        self.hal_session = self.dut.getConsoleSession("ssh_hal_test")

        # Create user response handler
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
        url = self.testSetup.assets.device.test3_VerifyHDCP_Version.artifacts
        if url is not None:
            self.downloadToDevice(url, self.deviceDownloadPath, self.rackDevice)

        #download test streams to device
        url = self.testSetup.assets.device.test3_VerifyHDCP_Version.streams
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
        cmds = self.testSetup.assets.device.test3_VerifyHDCP_Version.execute
        if cmds is not None:
            for cmd in cmds:
                self.writeCommands(cmd)

    #TODO: Current version supports only manual verification.
    def testVerifyHDCPVersion(self, manual=False):
        """
        Verifies the HDCP version for the current port.

        Args:
            manual (bool, optional): If True, manual verification is done using user response; otherwise,
                                     automated verification is used (yet to be implemented).

        Returns:
            bool: Result of the HDCP version verification.
        """
        if manual == True:
            hdcpVersion = self.testdsVideoPort.getHDCPVersion()
            return self.testUserResponse.getUserYN(f'is {hdcpVersion} HDCP Version displayed on Analyzer (Y/N): ')
        else :
            #TODO: Add automation verification methods
            return False

    def testEnablePortAndVerifyHDCP(self, port, index):
        """
        Enables a video port, verifies HDCP version, and logs the result.

        Args:
            port (str): The name of the video port being enabled.
            index (int): The index of the video port.

        Returns:
            bool: Result of the HDCP version verification after enabling the port.
        """
        self.log.stepStart(f'Enable {port} Port')

        # Enable video port
        self.testdsVideoPort.enablePort(port, index)

        # Enable HDCP if the device is a source
        if self.testdsVideoPort.getDeviceType():
            self.testdsVideoPort.enable_HDCP(port, index)

        # Set HDMI preference to the current HDCP version
        self.testdsVideoPort.select_HdmiPreference(port, index, self.testdsVideoPort.getHDCPVersion())

        # Verify HDCP version
        self.log.step(f'Verify {self.testdsVideoPort.getHDCPVersion()} Version')
        result = self.testVerifyHDCPVersion(True)
        self.log.stepResult(result, f'Verified {self.testdsVideoPort.getHDCPVersion()} Version')
        return result

    def testFunction(self):
        """
        Main test function that enables video ports and verifies the HDCP version.

        Downloads assets, runs prerequisites, enables/disables ports, and verifies HDCP version.

        Returns:
            bool: Final result of the HDCP version verification.
        """
        # Download test assets
        self.testDownloadAssets()

        # Run prerequisite commands
        self.testRunPrerequisites()

        # Initialize the dsVideoPort class
        self.testdsVideoPort = dsVideoPortClass(self.deviceProfile, self.hal_session)
        self.testdsVideoPort.initialise()

        # Loop through supported video ports and verify HDCP version
        result = False
        for port, index in self.testdsVideoPort.getSupportedPorts():
            result = self.testEnablePortAndVerifyHDCP(port, index)

        # Clean up assets
        self.testCleanAssets()

        # Clean up the dsVideoPort class
        del self.testdsVideoPort

        return result

if __name__ == '__main__':
    test = dsVideoPort_test3_VerifyHDCP_Version()
    test.run(False)
