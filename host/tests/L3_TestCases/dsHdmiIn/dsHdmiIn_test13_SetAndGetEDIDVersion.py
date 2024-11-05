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

class dsHdmiIn_test13_SetAndGetEDIDVersion(dsHdmiInHelperClass):
    """
    A test class for setting and verifying the EDID version on HDMI input ports.

    This class extends `dsHdmiInHelperClass` and provides functionality
    to test the EDID version settings on HDMI inputs.
    """

    def __init__(self):
        """
        Initializes the test13_SetAndGetEDIDVersion test .

        Args:
            None.
        """
        self.testName  = "test13_SetAndGetEDIDVersion"
        super().__init__(self.testName, '1')

    def testFunction(self):
        """
        The main test function to set and verify EDID versions on HDMI input ports.

        This function:
        - Initializes the HDMI input module.
        - Loops through each supported HDMI port.
        - Sets and verifies the EDID version for each port.

        Returns:
            None
        """

        self.log.testStart(self.testName, '1')

        # Initialize the dsHDMIIn module
        self.testdsHdmiIn.initialise()
        result = True

        # Loop through the supported HdmiIn ports
        for port in self.testdsHdmiIn.getSupportedPorts():
            self.log.stepStart(f'{port} Port')

            #get the list EDID versions
            edidVersionList = self.testdsHdmiIn.getEDIDVersionList()

            #Setting EDID Version on particular Hdmi input
            for edidVersion in edidVersionList:
               if edidVersion != "HDMI_EDID_VER_MAX":
                   self.testdsHdmiIn.setEdidVersion(port, edidVersion)
                   #Getting EDID Version
                   self.log.step(f'Getting {port} edid version')
                   edidStatus = self.testdsHdmiIn.getEdidVersion(port)
                   if edidStatus == edidVersion:
                         result &= True
                         self.log.step(f'Verified getVersion:{edidStatus} setVersion:{edidVersion} same')
                   else:
                         result &= False
                         self.log.step(f'Verified getVersion:{edidStatus} setVersion:{edidVersion} same')

        self.log.stepResult(result,f"Verified EDID Version ")
        #Run postRequisites listed in the test setup configuration file
        self.testRunPostRequisites()

        # Terminate dsHdmiIn Module
        self.testdsHdmiIn.terminate()

        return result

if __name__ == '__main__':
    test = dsHdmiIn_test13_SetAndGetEDIDVersion()
    test.run(False)
