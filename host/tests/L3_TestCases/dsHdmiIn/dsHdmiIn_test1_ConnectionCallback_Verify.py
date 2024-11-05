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

from L3_TestCases.dsHdmiIn.dsHdmiInHelperClass import dsHdmiInHelperClass

class dsHdmiIn_test1_ConnectionCallback_Verify(dsHdmiInHelperClass):
    """
    A test class to verify HDMI connection and disconnection events through callbacks on the Device Under Test (DUT).

    This class is built upon the dsHdmiInHelperClass, providing specific test functions that:
    - Detect HDMI cable plug/unplug events.
    - Confirm status changes on HDMI ports through callbacks.
    """

    def __init__(self):
        """
        Initializes the test1_ConnectionCallback_Verify test case.
        Sets up test-specific variables and initiates the superclass with the test name and quality control ID.

        Args:
            None.
        """
        # Class variables
        self.testName  = "test1_ConnectionCallback_Verify"
        super().__init__(self.testName, '1')

    def testPlugUnplugHDMI(self, port:str, plug:True, manual=False):

        """
        Waits for the HDMI port connection or disconnection event, either manually or automatically.

        Args:
            port (str): HDMI port identifier to be tested.
            plug (bool): Indicates if the HDMI cable should be plugged (True) or unplugged (False).
            manual (bool, optional): Enables manual verification prompts if set to True. Defaults to False.

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
        The main test function that verifies HDMI connection and disconnection callbacks.

        This function:
        - Starts logging and initializes the dsHdmiIn module.
        - Iterates over HDMI ports, simulating plug/unplug events and verifying callback statuses.
        - Logs test results for each event.
        - Terminates the dsHdmiIn module and cleans up.

        Returns:
            bool: Final test result, True if all port tests pass, otherwise False.
        """

        self.log.testStart(self.testName, '1')

        # Initialize the dsHDMIIn module
        self.testdsHdmiIn.initialise()

        # Iterate through each supported HDMI port for the test
        for port in self.testdsHdmiIn.getSupportedPorts():
            self.log.stepStart(f'HDMI Connect Status Test for {port} Port')

            # Wait for HDMI Plug In
            result = self.testPlugUnplugHDMI(port, True, True)

            status = self.testdsHdmiIn.getHDMIConnectionCallbackStatus()

            result = False
            if status:
                if port == status[0] and status[1]:
                    result = True

            self.log.stepResult(result, f'HDMI Connect Status Test for {port} Port')

            self.log.stepStart(f'HDMI Disconnect Status Test for {port} Port')

            # Wait for HDMI UnPlug
            result = self.testPlugUnplugHDMI(port, False, True)

            status = self.testdsHdmiIn.getHDMIConnectionCallbackStatus()

            result = False
            if status:
                if port == status[0] and not status[1]:
                    result &= True

            self.log.stepResult(result, f'HDMI Connect Status Test for {port} Port')

        # Terminate dsHdmiIn Module
        self.testdsHdmiIn.terminate()

        return result

if __name__ == '__main__':
    test = dsHdmiIn_test1_ConnectionCallback_Verify()
    test.run(False)
