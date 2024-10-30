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
sys.path.append(os.path.join(dir_path, "../../"))

from L3_TestCases.dsVideoDevice.dsVideoDeviceHelperClass import dsVideoDeviceHelperClass

class dsVideoDevice_test3_SetDisplayFramerate(dsVideoDeviceHelperClass):
    """
    Class to perform set and get the FRF mode on video device.

    Inherits from utHelperClass to leverage common test functionalities.

    Attributes:
        testName (str): Name of the test case.
        testSetupPath (str): Path to the test setup configuration file.
        moduleName (str): Name of the module being tested.
        rackDevice (str): Identifier for the device under test.
    """


    def __init__(self):
        """
        Initializes the test3_SetDisplayFramerate test .

        Args:
            None.
        """
        self.testName = "test3_SetDisplayFramerate"
        super().__init__(self.testName, '1')


    def testFunction(self):
        """
        Executes the set display framerate tests on the video device.

        This function performs the following steps:
        - Downloads necessary assets.
        - Runs prerequisite commands.
        - Initializes the dsVideoDevice module.
        - Set Display framerate
        - Cleans up the downloaded assets after testing.

        Returns:
            bool: Status of the last verification (True if successful, False otherwise).
        """

    
        self.log.testStart(self.testName, '1')

        # Initialize the dsVideoDevice module
        self.testdsVideoDevice.initialise(self.testdsVideoDevice.getDeviceType())

        # set the display framerate
        supported_framerate = self.testdsVideoDevice.getSupportedFrameRates()
        if supported_framerate:
            for framerate in supported_framerate:   
                frr = self.testdsVideoDevice.setDisplayFramerate(0, framerate)
                self.log.stepResult(framerate in frr, f'Set display framerate {framerate} Test')
            result = True
                
        else:
            self.log.error("No supported framerates available.")
            result = False

        
        # Terminate dsVideoDevice Module
        self.testdsVideoDevice.terminate()

        
        return result

if __name__ == '__main__':
    test = dsVideoDevice_test3_SetDisplayFramerate()
    test.run(False)
