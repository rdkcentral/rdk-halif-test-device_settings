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

class dsHdmiIn_test10_ZoomModeAndVerify(dsHdmiInHelperClass):
    """
    A test class for verifying the Zoom Mode of HDMI inputs.

    This class extends `dsHdmiInHelperClass` and provides functionality
    to test the zoom modes of HDMI inputs on the device.
    """

    def __init__(self):
        """
        Initializes the test10_ZoomModeAndVerify test .

        Args:
            None.
        """
        self.testName  = "test10_ZoomModeAndVerify"
        super().__init__(self.testName, '1')

    #TODO: Current version supports only manual verification.
    def CheckDeviceStatusAndVerifyZoomMode(self, Manual=False, port_type:str=0,videoZoomMode:str=0):
        """
        Verifies whether the particular zoom mode is selected or not.

        Args:
            manual (bool, optional): Indicates if manual verification is needed.
            port_type (str): The type of the port being verified.
            video_zoom_mode (bool): Indicates if zoom mode verification is required.

        Returns:
            bool: True if verification is successful, otherwise False.
        """
        if Manual == True and videoZoomMode == False:
            return self.testUserResponse.getUserYN(f'Check Device is ON connected to {port_type} and press Enter')
        elif Manual == True and videoZoomMode == True:
            return self.testUserResponse.getUserYN(f'Verify Zoom Mode selected on port {port_type} and press Enter')
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

        self.log.testStart(self.testName, '1')

        # Initialize the dsHDMIIn module
        self.testdsHdmiIn.initialise()

        # Loop through the supported HdmiIn ports
        for port in self.testdsHdmiIn.getSupportedPorts():
            self.log.stepStart(f'Select {port} Port')
            self.log.step(f'Select {port} Port')

            # Check the HdmiIn device connected to is active
            result = self.CheckDeviceStatusAndVerifyZoomMode(True,port,False)
            self.log.stepResult(result,f'Hdmi In Device is active {result} on {port}')

            # Select the HdmiIn port
            self.testdsHdmiIn.selectHDMIInPort(port, audMix=0, videoPlane=0, topmost=1)
            self.log.step(f'Port Selected {port}')

            #get the list of Zoom Modes
            zoomModeList = self.testdsHdmiIn.getVideoZoomModeList()

            for zoomModeIndex in range (1,len(zoomModeList)):
                   self.testdsHdmiIn.setHdmiInZoomMode(zoomModeList[zoomModeIndex])
                   result = self.CheckDeviceStatusAndVerifyZoomMode(True,port,True)
                   self.log.stepResult(result, f'Verified selected Zoom Mode {zoomModeList[zoomModeIndex]}')

        #Run postRequisites listed in the test setup configuration file
        self.testRunPostRequisites()

        # Terminate dsHdmiIn Module
        self.testdsHdmiIn.terminate()

        return result

if __name__ == '__main__':
    test = dsHdmiIn_test10_ZoomModeAndVerify()
    test.run(False)
