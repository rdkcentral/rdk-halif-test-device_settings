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
sys.path.append(os.path.join(dir_path))
sys.path.append(os.path.join(dir_path, "../../"))

from L3_TestCases.dsHdmiIn.dsHdmiInHelperClass import dsHdmiInHelperClass
from raft.framework.core.logModule import logModule

class dsHdmiIn_test07_AVIChangeCallback_Verify(dsHdmiInHelperClass):
    """
    A test class to verify AVI content change callbacks for HDMI input devices.

    This class inherits from `dsHdmiInHelperClass` and focuses on:
    - Verifying the status of AVI content changes through callback mechanisms.
    """


    def __init__(self, log:logModule=None):
        """
        Initializes the dsHdmiIn_test07_AVIChangeCallback_Verify test.

        Sets the test name and calls the superclass constructor.
        """
        self.testName  = "test07_AVIChangeCallback_Verify"
        self.qcID = '7'
        super().__init__(self.testName, self.qcID, log)

    def CheckDeviceStatus(self, manual=False, port_type:str=0, avi_input:str=0, avi_content:str=""):
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
            time.sleep(3)
            return True
        elif manual == True and avi_input == True:
            return self.testUserResponse.getUserYN(f'Change the AVI Content to {avi_content} on device connected to {port_type} and press Enter:')
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

        # Initialize the dsHdmiIn module
        self.testdsHdmiIn.initialise()
        result = True

        # Loop through the supported HdmiIn ports
        for port in self.testdsHdmiIn.getSupportedPorts():
            self.log.stepStart(f'Select {port} Port')
            self.log.step(f'Select {port} Port')

            # Check the HdmiIn device is active
            status = self.CheckDeviceStatus(True, port, False)

            self.testdsHdmiIn.selectHDMIInPort(port, audMix=0, videoPlane=0, topmost=1)
            time.sleep(5)
            self.log.step(f'Port Selected {port}')

            #get the list avi content type list
            aviContentTypeList = self.testdsHdmiIn.getAviContentTypeList()
            aviContentTypeList.append(aviContentTypeList[0])
            skip_check = True
            for aviContentType in aviContentTypeList:
                if aviContentType not in ["dsAVICONTENT_TYPE_NOT_SIGNALLED", "dsAVICONTENT_TYPE_MAX"]:

                    self.CheckDeviceStatus(True, port, True, aviContentType)
                    time.sleep(1)
                    aviStatus = self.testdsHdmiIn.getAVIContentCallbackStatus()
                    if skip_check:
                        skip_check = False
                        continue
                    if aviStatus != None and aviStatus[0] == port:
                        self.log.stepResult(True,f'AVI content type:{aviStatus[1]} on port:{aviStatus[0]} found')
                        self.log.step(f'Verify content type')
                        if (aviContentType == aviStatus[1]):
                            self.log.stepResult(True,f'AVI content type is same as the one USER set')
                            result &= True
                        else:
                            self.log.stepResult(False,f'AVI content type is not same as the one USER set')
                            result &= False
                    else:
                        self.log.stepResult(False,f'AVI content callback not found on port:{port}')
                        result &= False

        self.log.stepResult(result,f"AVI content type Verified ")

        # Terminate dsHdmiIn Module
        self.testdsHdmiIn.terminate()

        return result

if __name__ == '__main__':
    summerLogName = os.path.splitext(os.path.basename(__file__))[0] + "_summery"
    summeryLog = logModule(summerLogName, level=logModule.INFO)
    test = dsHdmiIn_test07_AVIChangeCallback_Verify(summeryLog)
    test.run(False)
