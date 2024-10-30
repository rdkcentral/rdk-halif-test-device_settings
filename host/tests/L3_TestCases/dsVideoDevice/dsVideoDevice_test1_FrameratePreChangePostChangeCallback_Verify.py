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
import time

dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(dir_path, "../../"))

from L3_TestCases.dsVideoDevice.dsVideoDeviceHelperClass import dsVideoDeviceHelperClass

class dsVideoDevice_test1_FrameratePreChangeCallback_Verify(dsVideoDeviceHelperClass):
    """
    Class to verify display framerate change pre and post callback .

    Inherits from utHelperClass to leverage common test functionalities.

    Attributes:
        testName (str): Name of the test case.
        testSetupPath (str): Path to the test setup configuration file.
        moduleName (str): Name of the module being tested.
        rackDevice (str): Identifier for the device under test.
    """


    def __init__(self):
        """
        Initializes the test1_FrameratePrePostChangeCallBack_Verify test .

        Args:
            None.
        """
        self.testName  = "test1_FrameratePrePostChangeCallBack_Verify"
        super().__init__(self.testName, '1')


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
        
    def find_CBStatus(self, input_str: str, status: str) -> bool:
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


        self.log.testStart(self.testName, '1')

        # Initialize the dsVideoDevice module
        self.testdsVideoDevice.initialise(self.testdsVideoDevice.getDeviceType())

        self.log.stepStart(f'Check the video device status')
        self.log.step(f'Check the video device status')

        # Check the Display device connected to is active
        result = self.checkDeviceStatus(True)
        self.log.stepResult(result,'Display Device is active')


        supported_framerate = self.testdsVideoDevice.getSupportedFrameRates()
        if supported_framerate:
            for framerate in supported_framerate:   
                self.testdsVideoDevice.setDisplayFramerate(0, framerate)
                time.sleep(20)
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


        # Terminate dsVideoDevice Module
        self.testdsVideoDevice.terminate()

        return result

if __name__ == '__main__':
    test = dsVideoDevice_test1_FrameratePreChangeCallback_Verify()
    test.run(False)
