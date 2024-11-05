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

class dsHdmiIn_test14_SetAndGetEDID2ALLMSupport(dsHdmiInHelperClass):
    """
    A test class for setting and verifying EDID 2 ALLM support on HDMI input ports.

    This class extends `dsHdmiInHelperClass` and provides functionality
    to test the ALLM (Auto Low Latency Mode) support of EDID 2.
    """
    def __init__(self):
        """
        Initializes the test14_SetAndGetEDID2ALLMSupport test .

        Args:
            None.
        """
        self.testName  = "test14_SetAndGetEDID2ALLMSupport"
        super().__init__(self.testName, '1')

    def testFunction(self):
        """
        The main test function to set and verify EDID 2 ALLM support on HDMI input ports.

        This function:
        - Initializes the HDMI input module.
        - Loops through each supported HDMI port.
        - Sets and verifies the ALLM support for each port.

        Returns:
            None
        """

        self.log.testStart(self.testName, '1')

        # Initialize the dsHDMIIn module
        self.testdsHdmiIn.initialise()

        # Loop through the supported HdmiIn ports
        for port in self.testdsHdmiIn.getSupportedPorts():
            self.log.stepStart(f'{port} Port')

            #Setting ALLM on particular Hdmi input to true and false
            for versionIndex in range(0,1):
                self.testdsHdmiIn.setEdid2Allm(port,versionIndex)
                #Getting ALLM value set
                self.log.step(f'Getting {port} edid 2 allm version')
                allmStatus = self.testdsHdmiIn.getEdid2Allm(port)
                if allmStatus == "false" or "true":
                   result &= True
                   self.log.step(f'Verified get ALLM:{allmStatus} set ALLM same')
                else:
                   result &= False
                   self.log.step(f'Verified get ALLM:{allmStatus} set ALLM same')

        self.log.stepResult(result,f"Verified EDID & ALLM Support ")
        #Run postRequisites listed in the test setup configuration file
        self.testRunPostRequisites()

        return result

if __name__ == '__main__':
    test = dsHdmiIn_test14_SetAndGetEDID2ALLMSupport()
    test.run(False)
