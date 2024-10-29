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
import time
import sys
from enum import Enum, auto

dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(dir_path, "../../"))

from dsClasses.dsVideoDevice import dsVideoDeviceClass
from raft.framework.plugins.ut_raft import utHelperClass
from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.plugins.ut_raft.utUserResponse import utUserResponse

class dsVideoDevice_test1_FrameratePreChangePostChangeCallback_Verify(utHelperClass):

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

            
    def find_CBStatus(self, input_str: str, status: str) -> bool:
        """
        Finds the framerate change callback in a given input string.

        Args:
            input_str (str): The input log containing callback string.
            status (str): The callback string to look for.

        Returns:
            bool: True if the status is found, False otherwise.
        """
        if status in input_str:
            return True
        return False

    def testFunction(self):
        """
        The main test function that verifies display framerate prechange in video device.

        This function:
        - Downloads necessary assets.
        - Runs prerequisite commands.
        - Verifies display framerate prechange and postchange through callbacks.

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

   
        self.log.stepStart(f'Set the display framerate')

        supported_framerate = self.testdsVideoDevice.getSupportedFrameRates()
        if supported_framerate:
            for framerate in supported_framerate:   
                self.testdsVideoDevice.setDisplayFramerate(0, framerate)
                result = self.testdsVideoDevice.read_Callbacks("FrameratePreChange callback tSecond:")
                if self.find_CBStatus(result, "FrameratePreChange callback tSecond:"):
                    self.log.stepResult(True, "Framerate Prechange tSecond found in Callback")
                else:
                    self.log.stepResult(False, "Framerate Prechange tSecond not found in Callback")
                    
                result = self.testdsVideoDevice.read_Callbacks("FrameratePostChange callback tSecond:")
                if self.find_CBStatus(result, "FrameratePostChange callback tSecond"):
                    self.log.stepResult(True, "FrameratePostChange callback tSecond found in Callback")
                else:
                    self.log.stepResult(False, "FrameratePostChange callback tSecond not found in Callback")

        else:
            self.log.error("No supported framerates available for verification.")
            result = False
        
        #Run postrequisites listed in the test setup configuration file 
        self.testRunPostreiquisites()

        # Terminate dsVideoDevice Module
        self.testdsVideoDevice.terminate()

        # Delete the dsVideoDevice class
        del self.testdsVideoDevice

        return result

if __name__ == '__main__':
    test = dsVideoDevice_test1_FrameratePreChangePostChangeCallback_Verify()
    test.run(False)
