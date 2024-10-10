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

from dsClasses.dsVideoPort import dsVideoPortClass
from raft.framework.plugins.ut_raft import utHelperClass
from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.plugins.ut_raft.utPlayer import utPlayer
from raft.framework.plugins.ut_raft.utUserResponse import utUserResponse

class dsVideoPort_test4_VerifyResolution(utHelperClass):

    testName  = "test4_VerifyResolution"
    testSetupPath = dir_path + "/dsVideoPort_L3_testSetup.yml"
    moduleName = "dsVideoPort"
    rackDevice = "dut"

    def __init__(self):
        """
        Initializes the test4_VerifyResolution test .

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
        url = self.testSetup.assets.device.test4_VerifyResolution.artifacts
        if url is not None:
            self.downloadToDevice(url, self.deviceDownloadPath, self.rackDevice)

        #download test streams to device
        url = self.testSetup.assets.device.test4_VerifyResolution.streams
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
        cmds = self.testSetup.assets.device.test4_VerifyResolution.execute
        if cmds is not None:
            for cmd in cmds:
                self.writeCommands(cmd)

    #TODO: Current version supports only manual verification.
    def testVerifyResolution(self, manual=False,resolution:dict= None):
        """
        Verifies the Resolutions .

        Args:
            manual (bool, optional): Manual verification (True: manual, False: other verification methods).
                                     Defaults to other verification methods

        Returns:
            bool
        """
        if manual == True:
            # Query user confirmation for each resolution attribute and combine results logically
            result = True
            result &= self.testUserResponse.getUserYN(f'is {resolution.get("pixelResolution")} on HDMI Analyzer (Y/N): ')
            result &= self.testUserResponse.getUserYN(f'is {resolution.get("aspectRatio")} on HDMI Analyzer (Y/N): ')
            result &= self.testUserResponse.getUserYN(f'is {resolution.get("stereoScopicMode")} on HDMI Analyzer (Y/N): ')
            result &= self.testUserResponse.getUserYN(f'is {resolution.get("frameRate")} on HDMI Analyzer (Y/N): ')
            result &= self.testUserResponse.getUserYN(f'is {resolution.get("interlaced")} on HDMI Analyzer (Y/N): ')
            return result
        else :
            #TODO: Add automation verification methods
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

        self.log.testStart("test4_VerifyResolution", '1')

        # Initialize the dsVideoPort module
        self.testdsVideoPort.initialise()

        # Loop through the supported Video ports
        for port,index in self.testdsVideoPort.getSupportedPorts():
            self.log.stepStart(f'Enable {port} Port')
            self.log.step(f'Enable {port} Port')

            # Enable the Video port
            self.testdsVideoPort.enablePort(port, index)

            # Enable the HDCP only for source devices
            if self.testdsVideoPort.getDeviceType():
                self.testdsVideoPort.enable_HDCP(port, index)

            # Enable the Video port
            for resolution in self.testdsVideoPort.getResolutions():
                self.testdsVideoPort.select_Resolution(port, index, resolution)
                result = self.testVerifyResolution(True,resolution)
                """
                result = self.testUserResponse.getUserYN(f'is {resolution.get("pixelResolution")} on HDMI Analyzer (Y/N): ')
                result &= self.testUserResponse.getUserYN(f'is {resolution.get("aspectRatio")} on HDMI Analyzer (Y/N): ')
                result &= self.testUserResponse.getUserYN(f'is {resolution.get("stereoScopicMode")} on HDMI Analyzer (Y/N): ')
                result &= self.testUserResponse.getUserYN(f'is {resolution.get("frameRate")} on HDMI Analyzer (Y/N): ')
                result &= self.testUserResponse.getUserYN(f'is {resolution.get("interlaced")} on HDMI Analyzer (Y/N): ')
                """
            self.log.stepResult(result, "All parameters verified using HDMI Analyzer")

        # Clean the assets downloaded to the device
        self.testCleanAssets()

        # Delete the dsVideoPort class
        del self.testdsVideoPort

        return result

if __name__ == '__main__':
    test = dsVideoPort_test4_VerifyResolution()
    test.run(False)
