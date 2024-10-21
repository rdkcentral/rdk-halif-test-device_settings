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

from dsClasses.dsVideoDevice import dsVideoDeviceClass
from raft.framework.plugins.ut_raft import utHelperClass
from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.plugins.ut_raft.utUserResponse import utUserResponse

class dsVideoDevice_test1_FrameratePreChangeCallback_Verify(utHelperClass):

    testName  = "test1_FrameratePreChangeCallBack_Verify"
    testSetupPath = dir_path + "/dsVideoDevice_L3_testSetup.yml"
    moduleName = "dsVideoDevice"
    rackDevice = "dut"

    def __init__(self):
        """
        Initializes the test1_FrameratePreChangeCallBack_Verify test .

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
    def checkDeviceStatus(self, manual=False):
        """
        Checks Display device is connected and Power status is ON.

        Args:
            manual (bool, optional): Manual verification (True: manual, False: other verification methods).
                                     Defaults to other verification methods
        Returns:
            bool
        """
        if manual == True:
            return self.testUserResponse.getUserYN('check video display connected and in ON state and press Enter:')
        else :
            #TODO: Add automation verification methods
            return False

    def testFunction(self):
        """
        The main test function that verifies display framerate prechange in video device.

        This function:
        - Downloads necessary assets.
        - Runs prerequisite commands.
        - Verifies display framerate prechange through callbacks.

        Returns:
            bool: Final result of the test.
        """

        # Download the assets listed in test setup configuration file
        self.testDownloadAssets()

        # Run Prerequisites listed in the test setup configuration file
        self.testRunPrerequisites()

        # Create the dsVideoDevice class
        self.testdsVideoDevice = dsVideoDeviceClass(self.deviceProfile, self.hal_session)

        self.log.testStart("test1_FrameratePreChangeCallBack_Verify", '1')

        # Initialize the dsVideoDevice module
        self.testdsVideoDevice.initialise(self.testdsVideoDevice.getDeviceType())

   
        self.log.stepStart(f'Check the video device status')
        self.log.step(f'Check the video device status')

        # Check the Display device connected to is active
        result = self.CheckDeviceStatus(True)
        self.log.stepResult(result,'Display Device is active')
        
        status = self.testdsVideoDevice.getFrameratePrechangeCallbackStatus()
        if status:
            result = True
            self.log.stepResult(result,f'Framerate Prechange tSecond {status[0]} found in Callback')
        else:
            result = False
            self.log.stepResult(result,f'Framerate Prechange tSecond not found in Callback')

        # Clean the assets downloaded to the device
        self.testCleanAssets()

        #Run postrequisites listed in the test setup configuration file 
        self.testRunPostreiquisites()

        # Terminate dsVideoDevice Module
        self.testdsVideoDevice.terminate()

        # Delete the dsVideoDevice class
        del self.testdsVideoDevice

        return result

if __name__ == '__main__':
    test = dsVideoDevice_test1_FrameratePreChangeCallback_Verify()
    test.run(False)
