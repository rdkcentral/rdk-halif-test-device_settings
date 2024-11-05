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

from L3_TestCases.dsHdmiIn.dsHdmiInHelperClass import dsHdmiInHelperClass

class dsHdmiIn_test8_SelectPortAndVerifyPortStatus(dsHdmiInHelperClass):
    """
    A test class for selecting HDMI input ports and verifying their status.

    This class extends the `dsHdmiInHelperClass` and performs the following:
    - Selects supported HDMI input ports.
    - Verifies the status of the selected ports.
    """

    def __init__(self):
        """
        Initializes the test8_SelectPortAndVerifyPortStatus test.

        Sets the test name and calls the superclass constructor.
        """
        self.testName  = "test8_SelectPortAndVerifyPortStatus"
        super().__init__(self.testName, '1')


    def testFunction(self):
        """
        The main test function that selects HDMI input ports and verifies their statuses.

        This function:
        - Initializes the HDMI input module.
        - Loops through each supported HDMI input port to verify selection status.

        Returns:
            bool: Final result of the test, indicating success or failure.
        """

        self.log.testStart(self.testName, '1')

        # Initialize the dsHdmiIn module
        self.testdsHdmiIn.initialise()

        # Loop through the supported HdmiIn ports
        for port in self.testdsHdmiIn.getSupportedPorts():
            self.log.stepStart(f'Select {port} Port')
            self.log.step(f'Select {port} Port')

            # Check the HdmiIn device connected to is active
            result = self.CheckDeviceStatus(True, port)
            if not result:
                self.testdsHdmiIn.selectHDMIInPort(port, audMix=0, videoPlane=0, topmost=1)
                time.sleep(5)
                self.log.step(f'Port Selected {port}')
            portStatus = self.testdsHdmiIn.getHDMIInPortStatus()
            if port == portStatus[1]:
               result &= True
               self.log.step(f'HdmiIn Select Verification isPresented:{portStatus[0]} activePort:{portStatus[1]}')
            else:
                result &= False
                self.log.step(f'HdmiIn Select Verification isPresented:{portStatus[0]} activePort:{portStatus[1]}')

        self.log.stepResult(result,f"Port Status Verified ")
        #Run postRequisites listed in the test setup configuration file
        self.testRunPostRequisites()

        # Terminate dsHdmiIn Module
        self.testdsHdmiIn.terminate()

        return result

if __name__ == '__main__':
    test = dsHdmiIn_test8_SelectPortAndVerifyPortStatus()
    test.run(False)
