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
from dsClasses.dsDisplay import dsDisplayEvent


class dsDisplay_test01_VerifyDisplayConnectCallBackTest(dsDisplayHelperClass):

    """
    Test class to retrieve and verify the display aspect ratio.

    This class uses the `dsDisplayClass` to interact with the device's display,
    downloading necessary test assets, retrieving the aspect ratio, and performing verification.
    """

    # Class variables
    def __init__(self):
        """
        Initializes the test01_VerifyDisplayConnectCallBackTest test .

        Args:
            None.
        """
        self.testName  = "test01_VerifyDisplayConnectCallBackTest"
        super().__init__(self.testName,'1')

    #TODO: Current version supports only manual verification.
    def testRaiseDisplayEvent(self,port, event:str, manual=False):
        """
        Verifies whether the compositeIn connected or not.
        Args:
            disconnect (bool): Connect or Disconnect compositeIn source device
            manual (bool, optional): Manual verification (True: manual, False: other verification methods).
                                     Defaults to other verification methods
        Returns:
            bool
        """
        if manual == True:
            return self.testUserResponse.getUserYN(f"Change the {port} status to {event} and press Y:")
        else :
            #TODO: Add automation verification methods
            return False

    def testFunction(self):
        """
        This function will test the Display by getting the aspectratio of the display.

        This function:
        - Runs the prerequisite commands.
        - Retrieves aspectratio for each supported port and verifies them.
        - Cleans up assets after the test.

        Returns:
            bool: Final result of the test.
        """

        self.log.testStart(self.testName, '1')
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
            for event in dsDisplayEvent:
                if event == dsDisplayEvent.dsDISPLAY_EVENT_MAX:
                    continue
                self.testRaiseDisplayEvent(port,event.name,True)
                status = self.testdsDisplay.getConnectionCallbackStatus()
                if status != event.name:
                    self.log.error(f"Event did not found in device.")

        #Terminate dsDisplay Module
        self.testdsDisplay.terminate()

        # Delete the dsDisplay class
        del self.testdsDisplay

        return result

if __name__ == '__main__':
    test = dsDisplay_test01_VerifyDisplayConnectCallBackTest()
    test.run(False)