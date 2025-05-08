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
    to test the VRR type of HDMI inputs on the device.
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

    def ChangeAndVerifyConnect(self, Manual=False, port_type:str=0):
        """
        Verifies connection of external source device.

        Args:
            manual (bool, optional): Indicates if manual verification is needed.
            port_type (str): The type of the port being verified.

        Returns:
            bool: True if verification is successful, otherwise False.
        """
        if Manual == True:
            # Check the HdmiIn device connected is active
            self.testUserResponse.getUserYN(f'Please connect the {port_type} and press Enter:')
            time.sleep(1)
            self.testdsHdmiIn.selectHDMIInPort(port_type, audMix=0, videoPlane=0, topmost=1)
            time.sleep(1)
            portstatus = self.testdsHdmiIn.getHDMIInPortStatus()
            if portstatus[1] == port_type: return True
        return False

    #TODO: Current version supports only manual verification.
    def ChangeAndVerifyVRR(self, Manual=False, port_type:str=0,vrrType:str=""):
        """
        Verifies whether the VRR mode is changed in external source device.

        Args:
            manual (bool, optional): Indicates if manual verification is needed.
            port_type (str): The type of the port being verified.
            verifyVrr (bool): Indicates if VRR verification is required.
            vrrState (bool): The state of VRR to be changed in source device

        Returns:
            bool: True if verification is successful, otherwise False.
        """
        if Manual == True:
            return self.testUserResponse.getUserYN(f"change the VRR type {vrrType} in external source device on port {port_type} and press Y: ")
        else :
            #TODO: Add automation verification methods
            return False

    def testFunction(self):
        """
        The main test function to verify the VRR types of HDMI input devices.

        This function:
        - Initializes the HDMI input module.
        - Loops through each supported HDMI port.
        - Selects the port and verifies the VRR type.
        """

        # Initialize the dsHDMIIn module
        self.testdsHdmiIn.initialise()
        result = False

        # If the vrr is not supported for current platform return
        featurelist = self.testdsHdmiIn.getSupportedGameFeatures()
        if featurelist == None or not any("vrr" in feature.lower() for feature in featurelist):
            self.testdsHdmiIn.terminate()
            return True

        vrr_feature_map = {
                          "vrr_hdmi": "dsVRR_HDMI_VRR",
                          "vrr_amd_freesync": "dsVRR_AMD_FREESYNC",
                          "vrr_amd_freesync_premium": "dsVRR_AMD_FREESYNC_PREMIUM",
                          "vrr_amd_freesync_premium_pro": "dsVRR_AMD_FREESYNC_PREMIUM_PRO"
        }
        vrrtypelist = self.testdsHdmiIn.getVRRTypeList()
        supportedVrrList = [
                           vrr_feature_map[feature]
                           for feature in featurelist
                           if feature in vrr_feature_map
                           and vrr_feature_map[feature] in vrrtypelist
        ]

        # Loop through the supported HdmiIn ports
        for port in self.testdsHdmiIn.getSupportedPorts():
            self.log.stepStart(f'Verify VRR for {port} Port')
            self.log.step(f'Select {port} Port')

            result = self.ChangeAndVerifyConnect(True,port)
            self.log.stepResult(result, f'Port Selected {port}')

            # Get if the VRR is supported for specific port
            getresponse = self.testdsHdmiIn.getVRRSupport(port)

            # If the VRR is not supported for specific port then continue with next port
            if getresponse:
                vrrSupport = getresponse[0] == "True"
                if "dsERR_OPERATION_NOT_SUPPORTED" in getresponse[1]: continue

                if not vrrSupport:
                    # Check for the VRR callback when VRR support is disabled for port
                    status = self.ChangeAndVerifyVRR(True,port)
                    time.sleep(1)
                    if status:
                        self.log.step(f'Verify VRR callback for VRR support disabled port {port}')
                        vrrcallback = self.testdsHdmiIn.getVrrTypeCallbackStatus()
                        if vrrcallback == None: 
                            result &= True
                        else:
                            result &= False
                        self.log.stepResult(result, f'No VRR callback for VRR support disabled port {port}')
                else:
                    for type in supportedVrrList:
                        status = self.testUserResponse.getUserYN(f'If required to connect other source device which supports VRR {type} Y/N: ')
                        if status:
                            self.ChangeAndVerifyConnect(True,port)
                        # Enable/Disable the VRR at source device
                        status = self.ChangeAndVerifyVRR(True,port,type)
                        if not status: continue
                        time.sleep(1)
                        # Check for the VRR callback when VRR  state changed at source device
                        self.log.step(f'Verify VRR callback for VRR support enabled port {port}')
                        vrrcallback = self.testdsHdmiIn.getVrrTypeCallbackStatus()
                        if vrrcallback != None and vrrcallback[0] == port:
                            self.log.stepResult(True,f'VRR status:{vrrcallback[1]} on port:{vrrcallback[0]} found')
                            result &= True

                            self.log.step(f'Verify VRR type')
                            # Compare the current VRR type with the one received in callback
                            if vrrcallback[1] == type:
                                self.log.stepResult(True,f'VRR Type set in external source device[{vrrcallback[1]}] same as the one set by user[{type}]')
                                result &= True
                            else:
                                self.log.stepResult(False,f'VRR Type set in external source device[{vrrcallback[1]}] is not same as the one set by user[{type}]')
                                result &= False
                        else:
                            self.log.stepResult(False,f'VRR status callback not found on port:{port}')
                            result &= False

                    # If the VRR support is enabled for port then set the VRR support to disable
                    self.testdsHdmiIn.setVRRSupport(port,0)
                    status = self.ChangeAndVerifyVRR(True,port)
                    if status:
                        self.log.step(f'Verify VRR callback for VRR support disabled port {port}')
                        vrrcallback = self.testdsHdmiIn.getVrrTypeCallbackStatus()
                        if vrrcallback == None: 
                            result &= True
                        else:
                            result &= False
                        self.log.stepResult(result, f'No VRR callback for VRR support disabled port {port}')
                    # Set the VRR support value back old state
                    self.testdsHdmiIn.setVRRSupport(port,vrrSupport)

        self.log.stepResult(result,f"Verified  VRR Type and Callback")

        # Terminate dsHdmiIn Module
        self.testdsHdmiIn.terminate()

        return result

if __name__ == '__main__':
    summerLogName = os.path.splitext(os.path.basename(__file__))[0] + "_summery"
    summeryLog = logModule(summerLogName, level=logModule.INFO)
    test = dsHdmiIn_test15_SetGetVrrStatusAndCallback(summeryLog)
    test.run(False)
