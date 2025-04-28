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
sys.path.append(os.path.join(dir_path))
sys.path.append(os.path.join(dir_path, "../../"))

from L3_TestCases.dsHdmiIn.dsHdmiInHelperClass import dsHdmiInHelperClass
from raft.framework.core.logModule import logModule

class dsHdmiIn_test15_SetGetVrrStatusAndCallback(dsHdmiInHelperClass):
    """
    A test class for verifying the get/set of vrrstatus and callback of HDMI inputs.

    This class extends `dsHdmiInHelperClass` and provides functionality
    to test the zoom modes of HDMI inputs on the device.
    """

    def __init__(self, log:logModule=None):
        """
        Initializes the test15_SetGetVrrStatusAndCallback test .

        Args:
            None.
        """
        self.testName  = "test15_SetGetVrrStatusAndCallback"
        self.qcID = '15'
        super().__init__(self.testName, self.qcID, log)

    #TODO: Current version supports only manual verification.
    def CheckDeviceStatusAndVerifyVRR(self, Manual=False, port_type:str=0,verifyVrr:str=0, vrrState:bool=False):
        """
        Verifies whether the VRR mode is changes in HDMI analyser.

        Args:
            manual (bool, optional): Indicates if manual verification is needed.
            port_type (str): The type of the port being verified.
            verifyVrr (bool): Indicates if VRR verification is required.
            vrrState (bool): The state of VRR to be changed in source device

        Returns:
            bool: True if verification is successful, otherwise False.
        """
        if Manual == True and verifyVrr == False:
            self.testUserResponse.getUserYN(f'Please connect the {port_type} and press Enter:')
            time.sleep(3)
            return self.testUserResponse.getUserYN(f'Is HDMI device connected and display is ON {port_type}? Y/N:')
        elif Manual == True and verifyVrr == True:
            return self.testUserResponse.getUserYN(f"change the VRR state to {'ENABLE' if vrrState == True else 'DISABLE'} in HDMI analyser on port {port_type} and press Y: ")
        else :
            #TODO: Add automation verification methods
            return False

    def testFunction(self):
        """
        The main test function to verify the Zoom Mode of HDMI input devices.

        This function:
        - Initializes the HDMI input module.
        - Loops through each supported HDMI port.
        - Selects the port and verifies the zoom modes.
        """

        # Initialize the dsHDMIIn module
        self.testdsHdmiIn.initialise()
        result = True

        # Loop through the supported HdmiIn ports
        for port in self.testdsHdmiIn.getSupportedPorts():
            self.log.stepStart(f'Select {port} Port')
            self.log.step(f'Select {port} Port')

            # Check the HdmiIn device connected to is active
            status = self.CheckDeviceStatusAndVerifyVRR(True,port,False)
            if not status:
                self.testdsHdmiIn.selectHDMIInPort(port, audMix=0, videoPlane=0, topmost=1)
                time.sleep(5)
                self.log.step(f'Port Selected {port}')

            # Get if the VRR is supported for specific port
            getresponse = self.testdsHdmiIn.getVRRSupport(port)
            # If the VRR is not suppoorted for specific port then continue with next port
            if getresponse:
                if "dsERR_OPERATION_NOT_SUPPORTED" in getresponse[1]: continue

            # If the VRR support is disabled for port then set the VRR support to enable
                if getresponse[0] == False:
                    self.testdsHdmiIn.setVRRSupport(port,1)
                vrrstate = [True, False]
                for state in vrrstate:
                    # Enable/Disable the VRR at source device
                    status = self.CheckDeviceStatusAndVerifyVRR(True,port,True,state)
                    time.sleep(3)
                    # Check for the VRR callback when VRR  state changed at source device
                    vrrcallback = self.testdsHdmiIn.getVrrTypeCallbackStatus()
                    if vrrcallback != None and vrrcallback[0] == port:
                        self.log.stepResult(True,f'VRR status:{vrrcallback[1]} on port:{vrrcallback[0]} found')
                        result &= True
                        self.log.step(f'Verify VRR type')
                        # Get the current VRR type
                        getstatusresponse = self.testdsHdmiIn.getVRRType(port)
                        if getstatusresponse:
                            # Compare the current VRR type with the one received in callback
                            if vrrcallback[1] == getstatusresponse:
                                self.log.stepResult(True,f'VRR Type set in HDMI analyser[{vrrcallback[1]}] same as the GET Api[{getstatusresponse}]')
                                result &= True
                            else:
                                self.log.stepResult(False,f'VRR Type set in HDMI analyser[{vrrcallback[1]}] is not same as GET Api[{getstatusresponse}]')
                                result &= False
                    else:
                        self.log.stepResult(False,f'VRR status callback not found on port:{port}')
                        result &= False

        self.log.stepResult(result,f"Verified  VRR Type and Callback")

        # Terminate dsHdmiIn Module
        self.testdsHdmiIn.terminate()

        return result

if __name__ == '__main__':
    summerLogName = os.path.splitext(os.path.basename(__file__))[0] + "_summery"
    summeryLog = logModule(summerLogName, level=logModule.INFO)
    test = dsHdmiIn_test15_SetGetVrrStatusAndCallback(summeryLog)
    test.run(False)
