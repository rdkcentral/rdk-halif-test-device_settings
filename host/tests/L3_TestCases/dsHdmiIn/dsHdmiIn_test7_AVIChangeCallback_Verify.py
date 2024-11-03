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
sys.path.append(os.path.join(dir_path, "../../"))

from L3_TestCases.dsHdmiIn.dsHdmiInHelperClass import dsHdmiInHelperClass

class dsHdmiIn_test7_AVIChangeCallback_Verify(dsHdmiInHelperClass):
    """
    A test class to verify AVI content change callbacks for HDMI input devices.

    This class inherits from `dsHdmiInHelperClass` and focuses on:
    - Verifying the status of AVI content changes through callback mechanisms.
    """


    def __init__(self):
        """
        Initializes the dsHdmiIn_test7_AVIChangeCallback_Verify test.

        Sets the test name and calls the superclass constructor.
        """
        self.testName  = "test7_AVIChangeCallback_Verify"
        super().__init__(self.testName, '1')

    def CheckDeviceStatus(self, manual=False, port_type:str=0, avi_input:str=0):
        """
        Verifies whether the HDMI input device is connected and active.

        Args:
            manual (bool, optional): Manual verification (True: manual, False: automated).
                                     Defaults to automated verification.
            port_type (str, optional): The type of the port being checked.
            avi_input (str, optional): Indicates whether to check AVI input status.

        Returns:
            bool: True if the device is connected and verified; False otherwise.
        """
        if manual == True and avi_input != True:
            self.testUserResponse.getUserYN(f'Please connect the {port_type} and press Enter:')
            return self.testUserResponse.getUserYN(f'Is HdmiIn device connected and Displayed is ON {port_type} press Y/N:')
        elif manual == True and avi_input == True:
            return self.testUserResponse.getUserYN(f'Change the AVI Content on device connected to {port_type} and press Enter:')
        else :
            #TODO: Add automation verification methods
            return False

    def testFunction(self):
        """
        The main test function that verifies the AVI content change status of HDMI input devices.

        This function:
        - Initializes the HDMI input module.
        - Loops through each supported HDMI input port to verify the AVI content.
        - Logs the results of the AVI content verification.

        Returns:
            bool: True if all checks are successful, otherwise False.
        """

        self.log.testStart(self.testName, '1')

        # Initialize the dsHdmiIn module
        self.testdsHdmiIn.initialise()

        # Loop through the supported HdmiIn ports
        for port in self.testdsHdmiIn.getSupportedPorts():
            self.log.stepStart(f'Select {port} Port')
            self.log.step(f'Select {port} Port')

            # Check the HdmiIn device is active
            self.CheckDeviceStatus(True, port, False)
            self.testdsHdmiIn.selectHDMIInPort(port, audMix=0, videoPlane=0, topmost=1)
            self.log.step(f'HdmiIn Select Verification {port} Port')
            self.CheckDeviceStatus(True, port, True)
            aviStatus = self.testdsHdmiIn.getAVIContentCallbackStatus()
            if aviStatus[0] == port:
               result = True
               self.log.stepResult(result,f'AVI content type:{aviStatus[1]} on port:{aviStatus[0]} found in Callback')
            else:
                result = False
                self.log.stepResult(result,f'AVI content type:{aviStatus[1]} on port:{aviStatus[0]} found in Callback')

        #Run postRequisites listed in the test setup configuration file
        self.testRunPostRequisites()

        # Terminate dsHdmiIn Module
        self.testdsHdmiIn.terminate()

        return result

if __name__ == '__main__':
    test = dsHdmiIn_test7_AVIChangeCallback_Verify()
    test.run(False)
