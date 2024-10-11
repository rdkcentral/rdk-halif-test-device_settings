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
sys.path.append(os.path.join(dir_path, "../"))

from dsClasses.dsHdmiIn import dsHdmiInClass
from raft.framework.plugins.ut_raft import utHelperClass
from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.plugins.ut_raft.utPlayer import utPlayer
from raft.framework.plugins.ut_raft.utUserResponse import utUserResponse

class dsHdmiIn_test1_ConnectionCallback_Verify(utHelperClass):

    testName  = "test1_ConnectionCallback_Verify"
    testSetupPath = dir_path + "/dsHdmiIn_L3_testSetup.yml"
    moduleName = "dsHdmiIn"
    rackDevice = "dut"

    def __init__(self):
        """
        Initializes the test1_ConnectionCallback_Verify test .

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
        Downloads the test artifacts and streams listed in the test setup configuration.

        This function retrieves audio streams and other necessary files and
        saves them on the DUT (Device Under Test).

        Args:
            None
        """

        # List of streams with path
        self.testStreams = []

        self.deviceDownloadPath = self.cpe.get("target_directory")

        test = self.testSetup.get("assets").get("device").get(self.testName)

        # Download test artifacts to device
        url = test.get("artifacts")
        if url is not None:
            self.downloadToDevice(url, self.deviceDownloadPath, self.rackDevice)

        # Download test streams to device
        url =  test.get("streams")
        if url is not None:
            self.downloadToDevice(url, self.deviceDownloadPath, self.rackDevice)
            for streampath in url:
                self.testStreams.append(os.path.join(self.deviceDownloadPath, os.path.basename(streampath)))

    def testCleanAssets(self):
        """
        Removes the downloaded assets and test streams from the DUT after test execution.

        Args:
            None
        """
        self.deleteFromDevice(self.testStreams)

    def testRunPrerequisites(self):
        """
        Executes prerequisite commands listed in the test setup configuration file on the DUT.

        Args:
            None
        """

        # Run commands as part of test prerequisites
        test = self.testSetup.get("assets").get("device").get(self.testName)
        cmds = test.get("execute")
        if cmds is not None:
            for cmd in cmds:
                self.writeCommands(cmd)

    def testPlugUnplugHDMI(self, port:str, plug:True, manual=False):
        """
        Waits for the HDMI port connection or disconnection.
        Args:
            port (str) : HDMI port
            plug (bool, optional): True - Plug the HDMI, False - Unplug the HDMI
            manual (bool, optional): Manual verification (True: manual, False: other verification methods).
                                     Defaults to other verification methods
        Returns:
            None
        """
        if manual == True:
            if plug == True:
                self.testUserResponse.getUserYN(f"Plug the HDMI cable {port} and Press Enter:")
            else :
                self.testUserResponse.getUserYN(f"UnPlug the HDMI cable {port} and Press Enter:")
        else :
            #TODO: Add automation verification methods
            return

    def testFunction(self):
        """
        The main test function that verifies HDMI connection and disconnection.

        This function:
        - Downloads necessary assets.
        - Runs prerequisite commands.
        - Verifies HDMI connection and disconnection through callbacks.

        Returns:
            bool: Final result of the test.
        """

        # Download the assets listed in test setup configuration file
        self.testDownloadAssets()

        # Run Prerequisites listed in the test setup configuration file
        self.testRunPrerequisites()

        # Create the dsHdmiIn class
        self.testdsHdmiIn = dsHdmiInClass(self.deviceProfile, self.hal_session)

        self.log.testStart("test1_ConnectionCallback_Verify", '1')

        # Initialize the dsHDMIIn module
        self.testdsHdmiIn.initialise()

        # Loop through the supported HdmiIn ports
        for port in self.testdsHdmiIn.getSupportedPorts():
            self.log.stepStart(f'HDMI Connect Status Test for {port} Port')

            # Wait for HDMI Plug In
            result = self.testPlugUnplugHDMI(port, True, True)

            status = self.testdsHdmiIn.getHDMIConnectionStatus()

            result = False
            if status:
                if port == status[0] and status[1]:
                    result = True

            self.log.stepResult(result, f'HDMI Connect Status Test for {port} Port')

            self.log.stepStart(f'HDMI Disconnect Status Test for {port} Port')

            # Wait for HDMI UnPlug
            result = self.testPlugUnplugHDMI(port, False, True)

            status = self.testdsHdmiIn.getHDMIConnectionStatus()

            result = False
            if status:
                if port == status[0] and not status[1]:
                    result = True

            self.log.stepResult(result, f'HDMI Connect Status Test for {port} Port')

        # Clean the assets downloaded to the device
        self.testCleanAssets()

        # Terminate dsHdmiIn Module
        self.testdsHdmiIn.terminate()

        # Delete the dsHdmiIn class
        del self.testdsHdmiIn

        return result

if __name__ == '__main__':
    test = dsHdmiIn_test1_ConnectionCallback_Verify()
    test.run(False)
