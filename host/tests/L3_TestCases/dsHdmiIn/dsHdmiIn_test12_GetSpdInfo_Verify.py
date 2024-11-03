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
from enum import Enum, auto

dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(dir_path, "../../"))

from L3_TestCases.dsHdmiIn.dsHdmiInHelperClass import dsHdmiInHelperClass

class dsHdmiIn_test12_GetSpdInfo_Verify(dsHdmiInHelperClass):
    """
    A test class for verifying the SPD information from HDMI input devices.

    This class extends `dsHdmiInHelperClass` and provides functionality
    to test the SPD info of HDMI inputs on the device.
    """

    def __init__(self):
        """
        Initializes the test12_GetSpdInfo_Verify test .

        Args:
            None.
        """
        self.testName  = "test12_GetSpdInfo_Verify"
        super().__init__(self.testName, '1')

    #TODO: Current version supports only manual verification.
    def CheckDeviceAndInfoStatus(self, manual = False, port_type:str=0, spd_info:str=0):
        """
        Verifies the status of the device and whether SPD info is received on the specified port.

        Args:
            manual (bool, optional): Manual verification flag (True: manual, False: automated).
            port_type (str): The type of port being checked.
            spd_info (Optional[str]): SPD information status.

        Returns:
            bool: True if the status is verified, False otherwise.
        """
        if manual == True and spd_info == False:
            self.testUserResponse.getUserYN(f'Please connect the {port_type} and press Enter:')
            return self.testUserResponse.getUserYN(f'Is HdmiIn device connected and Displayed is ON {port_type} press Y/N:')
        elif manual == True and spd_info == True:
            return self.testUserResponse.getUserYN(f'check the Spd Info received of device connected to {port_type} and press Enter:')
        else :
            #TODO: Add automation verification methods
            return False

    def testFunction(self):
        """
        The main test function to verify SPD information on HDMI input ports.

        This function:
        - Initializes the HDMI input module.
        - Loops through each supported HDMI port.
        - Checks the active status of each port and retrieves its SPD info.

        Returns:
            None
        """

        self.log.testStart(self.testName, '1')

        # Initialize the dsHDMIIn module
        self.testdsHdmiIn.initialise()

        # Loop through the supported HdmiIn ports
        for port in self.testdsHdmiIn.getSupportedPorts():
            self.log.stepStart(f'{port} Port')

            # Check the HdmiIn device connected to is active
            result = self.CheckDeviceAndInfoStatus(True, port, False)
            #self.log.step(f'Hdmi In Device is active on {port}')

            if not result:
                # Select the HdmiIn port
                self.testdsHdmiIn.selectHDMIInPort(port, audMix=0, videoPlane=0, topmost=1)
                self.log.step(f'Selected port {port} Port')

            time.sleep(5)
            #Getting Spd Info on particular Hdmi input port
            result = self.testdsHdmiIn.getSpdInfo(port)
            print(result)
            self.log.stepResult(result,f'Verified Spd info on {port}')
            result = self.CheckDeviceAndInfoStatus(True, port , True)
            self.log.stepResult(result,f'Verified Spd info on {port}')

        #Run postRequisites listed in the test setup configuration file
        self.testRunPostRequisites()

        # Terminate dsHdmiIn Module
        self.testdsHdmiIn.terminate()

        return result

if __name__ == '__main__':
    test = dsHdmiIn_test12_GetSpdInfo_Verify()
    test.run(False)
