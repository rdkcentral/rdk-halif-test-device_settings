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

from L3_TestCases.dsDisplay.dsDisplayHelperClass import dsDisplayHelperClass

class dsDisplay_test02_TestVerifyDisplayEdid(dsDisplayHelperClass):

    """
    Test class to retrieve and verify the display Edid information.

    This class uses the `dsDisplayClass` to interact with the device's display,
    downloading necessary test assets, retrieving the Edid, and performing verification.
    """

    # Class variables
    def __init__(self):
        """
        Initializes the test02_TestVerifyDisplayEdid test .

        Args:
            None.
        """
        self.testName  = "test02_TestVerifyDisplayEdid"
        super().__init__(self.testName,'2')

    #TODO: Current version supports only manual verification.
    def testConnectDisplay(self, port:str, display:str, manual=False):
        """
        Connects the display to specified port
        Args:
            port (str): display port
            display (str): Display name
            manual (bool, optional): Manual verification (True: manual, False: other verification methods).
                                     Defaults to other verification methods
        Returns:
            bool
        """
        if manual == True:
            return self.testUserResponse.getUserYN(f"Connect Device: {display} to Port: {port} and Press Enter")
        else :
            #TODO: Add automation verification methods
            return False

    def testFunction(self):
        """
        This function will test the Edid of Display.

        Returns:
            bool: Final result of the test.
        """

        self.log.testStart(self.testName, '2')

        # Initialize the dsDisplay module
        self.testdsDisplay.initialise()
        result = False

        # Loop through the supported video ports
        for port, index in self.testdsDisplay.getSupportedPorts():
            self.testdsDisplay.selectDisplayPort(port, index)

            for display in self.testMonitorNameDetails:
                self.log.stepStart(f'Test Display Edid Port: {port} Device: {display}')
                # Wait for the device connection
                self.testConnectDisplay(port, display, True)

                # Get the Edid information
                edidInfo = self.testdsDisplay.getEdid()

                if edidInfo and "monitorName" in edidInfo:
                    result = edidInfo["monitorName"] == display
                self.log.stepResult(result, f'Test Display Edid Port: {port} Device: {display}')

        #Terminate dsDisplay Module
        self.testdsDisplay.terminate()

        return result

if __name__ == '__main__':
    test = dsDisplay_test02_TestVerifyDisplayEdid()
    test.run(False)
