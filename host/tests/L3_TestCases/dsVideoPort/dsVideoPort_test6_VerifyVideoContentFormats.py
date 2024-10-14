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

class dsVideoPort_test6_VerifyVideoContentFormats(utHelperClass):
    """
    Test class for verifying video content formats on supported video ports.
    """

    testName  = "test6_VerifyVideoContentFormats"
    testSetupPath = dir_path + "/dsVideoPort_L3_testSetup.yml"
    moduleName = "dsVideoPort"
    rackDevice = "dut"

    def __init__(self):
        """
        Initializes the test6_VerifyVideoContentFormats test case with required setup.

        Args:
            None.
        """
        super().__init__(self.testName, '1')

        # Test Setup configuration file
        self.testSetup = ConfigRead(self.testSetupPath, self.moduleName)

        # Open Session for hal test
        self.hal_session = self.dut.getConsoleSession("ssh_hal_test")

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
        url = self.testSetup.assets.device.test6_VerifyVideoContentFormats.artifacts
        if url is not None:
            self.downloadToDevice(url, self.deviceDownloadPath, self.rackDevice)

        #download test streams to device
        url = self.testSetup.assets.device.test6_VerifyVideoContentFormats.streams
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
        cmds = self.testSetup.assets.device.test6_VerifyVideoContentFormats.execute
        if cmds is not None:
            for cmd in cmds:
                self.writeCommands(cmd)

    #TODO: Current version supports only manual verification.
    def testVerifyHDRFormat(self, manual=False,hdr_mode:str=0):
        """
        Verifies the HDR Format .

        Args:
            manual (bool, optional): Manual verification (True: manual, False: other verification methods).
                                     Defaults to other verification methods

        Returns:
            bool: True if verification successful, False otherwise.
        """
        if manual == True:
            return self.testUserResponse.getUserYN(f'is {hdr_mode} displayed on Analyzer (Y/N): ')
        else :
            #TODO: Add automation verification methods
            return False

    def enablePortAndVerifyFormats(self, port, index):
        """
        Enables the given video port and verifies supported HDR formats.

        Args:
            port (str): The name of the video port.
            index (int): The port index.

        Returns:
            bool: Result of the HDR format verification.
        """
        self.log.stepStart(f'Enable {port} Port')
        self.testdsVideoPort.enablePort(port, index)

        # Enable HDCP if device type requires it
        if self.testdsVideoPort.getDeviceType():
            self.testdsVideoPort.enable_HDCP(port, index)

        # Verify HDR capabilities
        supported_formats = self.testdsVideoPort.getHDRCapabilities()
        if supported_formats:
            for hdr_format in supported_formats:
                self.testdsVideoPort.select_HDRModes(port, index, hdr_format)
                self.log.step(f'Verify HDR {hdr_format} with Analyzer')
                result = self.testVerifyHDRFormat(manual=True, hdr_mode=hdr_format)

                # Log the verification result
                self.log.stepResult(result, f"HDR {hdr_format} verification result")
        else:
            self.log.error("No HDR formats available for verification.")
            result = False

        return result

    def testFunction(self):
        """
        Main test function to verify video ports by enabling/disabling them and verifying HDR formats.

        Returns:
            bool: Final test result.
        """
        # Download the assets listed in the test setup configuration file
        self.testDownloadAssets()

        # Run prerequisites listed in the test setup configuration file
        self.testRunPrerequisites()

        # Create and initialize the dsVideoPort class
        self.testdsVideoPort = dsVideoPortClass(self.deviceProfile, self.hal_session)
        self.testdsVideoPort.initialise()

        self.log.testStart(self.testName, '1')

        # Loop through supported video ports and verify HDR formats
        for port, index in self.testdsVideoPort.getSupportedPorts():
            result = self.enablePortAndVerifyFormats(port, index)

        # Clean the assets downloaded to the device
        self.testCleanAssets()

        # Delete the dsVideoPort class
        del self.testdsVideoPort

        return result

if __name__ == '__main__':
    test = dsVideoPort_test6_VerifyVideoContentFormats()
    test.run(False)
