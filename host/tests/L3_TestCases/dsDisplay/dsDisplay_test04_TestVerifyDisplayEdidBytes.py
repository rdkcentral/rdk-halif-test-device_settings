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
sys.path.append(dir_path+"../../../")

from L3_TestCases.dsDisplay.dsDisplayHelperClass import dsDisplayHelperClass

class dsDisplay_test04_TestVerifyDisplayEdidBytes(dsDisplayHelperClass):

    """
    Test class to retrieve and verify the display EdidBytes.

    This class uses the `dsDisplayClass` to interact with the device's display,
    downloading necessary test assets, retrieving the EdidBytes, and performing verification.
    """

    # Class variables
    def __init__(self):
        """
        Initializes the test04_TestVerifyDisplayEdidBytes test .

        Args:
            None.
        """
        self.testName  = "test04_TestVerifyDisplayEdidBytes"
        super().__init__(self.testName,'4')

    def testFunction(self):
        self.log.testStart(self.testName, '4')

        # Initialize the dsDisplay module
        self.testdsDisplay.initialise()

        # Get the supported video ports
        supported_ports = self.testdsDisplay.getSupportedPorts()
        result=True

        if not supported_ports:
            self.log.error("No supported ports found.")
            return False

        # Loop through the supported video ports
        for port, index in supported_ports:
            self.log.info(f"Testing port {port} at index {index}.")
            self.testdsDisplay.getDisplayHandle(port, index)
            result = self.testdsDisplay.getEdidBytes()
            if result == True:
                self.log.stepResult(result,f'Verified EDID Info received on {port}')
            else:
                result = False
                self.log.stepResult(result,f'Verified EDID Info received on {port}')

        #Terminate dsDisplay Module
        self.testdsDisplay.terminate()

        # Delete the dsDisplay class
        del self.testdsDisplay

        return result

if __name__ == '__main__':
    test = dsDisplay_test04_TestVerifyDisplayEdidBytes()
    test.run(False)
