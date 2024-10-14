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
from enum import Enum, auto

dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(dir_path, "../"))

from dsClasses.dsCompositeIn import dsCompositeInClass
from raft.framework.plugins.ut_raft import utHelperClass
from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.plugins.ut_raft.utUserResponse import utUserResponse

class dsCompositeIn_test4_VerifySignal_Callback(utHelperClass):

    testName  = "test4_VerifySignal_Callback"
    testSetupPath = dir_path + "/dsCompositeIn_L3_testSetup.yml"
    moduleName = "dsCompositeIn"
    rackDevice = "dut"

    def __init__(self):
        """
        Initializes the test4_VerifySignal_Callback test .

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
        Removes the assets copied to the dut.

        Args:
            None.
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

    def testRunPostreiquisites(self):
        """
        Executes postrequisite commands listed in test-setup configuration file on the DUT.

        Args:
            None.
        """

       # Run commands as part of test prerequisites
        test = self.testSetup.get("assets").get("device").get(self.testName)
        cmds = test.get("postcmd")
        if cmds is not None:
            for cmd in cmds:
                self.writeCommands(cmd)

     #TODO: Current version supports only manual verification.
    def CheckDeviceStatus(self, manual=False, port_type:str=0):
        """
        Verifies whether Composite Source Device connected or not

        Args:
            port_type (str) : CompositeIn port
            manual (bool, optional): Manual verification (True: manual, False: other verification methods).
                                     Defaults to other verification methods

        Returns:
            bool
        """
        if manual == True:
            return self.testUserResponse.getUserYN("Check if CompositeIn source is connected to {port_type} and press Enter:")
        else :
            #TODO: Add automation verification methods
            return False

    def testFunction(self):
        """
        The main test function that verifies signal status of Hdmi In device.

        This function:
        - Downloads necessary assets.
        - Runs prerequisite commands.
        - Verifies HDMI In signal status through callbacks.

        Returns:
            bool: Final result of the test.
        """

        # Download the assets listed in test setup configuration file
        self.testDownloadAssets()

        # Run Prerequisites listed in the test setup configuration file
        self.testRunPrerequisites()

        # Create the dsHdmiIn class
        self.testdsCompositeIn = dsCompositeInClass(self.deviceProfile, self.hal_session)

        self.log.testStart("test4_VerifySignal_Callback", '1')

        # Initialize the dsHdmiIn module
        self.testdsCompositeIn.initialise()

        # Loop through the supported HdmiIn ports
        for port in self.testdsCompositeIn.getSupportedPorts():
            self.log.stepStart(f'Select {port} Port')
            self.log.step(f'Select {port} Port')

            # Check the HdmiIn device connected to is active
            portstr = f"dsCOMPOSITE_IN_PORT_{port}"
            result = self.CheckDeviceStatus(True,portstr)
            self.log.stepResult(result,f'CompositeIn Device is connected {result} on {portstr}')
            
            self.testdsCompositeIn.selectPort(port)
            self.log.step(f'Port Selcted {port}')

            status = self.testdsCompositeIn.getSignalChangeCallbackStatus()
            result = False
            if port == status[0]:
               result = True
               self.log.stepResult(result,f'Signal status {status[1]} found in Callback')
            else:
               result = False
               self.log.stepResult(result,f'Signal status not found in Callback found')

        # Clean the assets downloaded to the device
        self.testCleanAssets()

        #Run postrequisites listed in the test setup configuration file 
        self.testRunPostreiquisites()

        # Terminate testdsCompositeIn Module
        self.testdsCompositeIn.terminate()

        # Delete the testdsCompositeIn class
        del self.testdsCompositeIn

        return result

if __name__ == '__main__':
    test = dsCompositeIn_test4_VerifySignal_Callback()
    test.run(False)