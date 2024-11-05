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
#*******************************************************************************

import os
import sys
import time

dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(dir_path, "../../"))

from L3_TestCases.dsHdmiIn.dsHdmiInHelperClass import dsHdmiInHelperClass

class dsHdmiIn_test9_ScaleVideoAndVerify(dsHdmiInHelperClass):
    """
    A test class for scaling HDMI input video and verifying the scaling status.

    This class extends the `dsHdmiInHelperClass` and provides functionality to
    test the video scaling features of HDMI inputs.
    """

    def __init__(self):
        """
        Initializes the test9_ScaleVideoAndVerify test .

        Args:
            None.
        """
        self.testName  = "test9_ScaleVideoAndVerify"
        super().__init__(self.testName, '1')

    def CheckDeviceStatusAndVerifyVideoScale(self, manual=False, port_type=0, videoScale=False, xCord=0, yCord=0, width=0, height=0):
        """
        Verifies the device status and checks if the video scaling is correct.

        Args:
            manual (bool): Flag to indicate if manual verification is required.
            port_type (str): The type of the port being verified.
            videoScale (bool): Indicates if video scaling is being verified.
            xCord (int): The x-coordinate of the scaled video.
            yCord (int): The y-coordinate of the scaled video.
            width (int): The width of the scaled video.
            height (int): The height of the scaled video.

        Returns:
            bool: True if verification is successful, otherwise False.
        """
        if manual:
            if not videoScale:
                self.testUserResponse.getUserYN(f'Please connect the {port_type} and press Enter:')
                time.sleep(3)
                return self.testUserResponse.getUserYN(f'Is HDMI device connected and display is ON {port_type}? Y/N:')
            else:
                return self.testUserResponse.getUserYN(f'Check if video is scaled to {xCord}*{yCord}*{width}*{height} on port {port_type}. Press Y/N:')
        return False

    def testFunction(self):
        """
        The main test function to verify HDMI input video scaling.

        This function performs the following:
        - Initializes the HDMI input module.
        - Loops through each supported HDMI input port.
        - Verifies the connection status and scales video as needed.
        """
        self.log.testStart(self.testName, '1')

        # Initialize the dsHDMIIn module
        self.testdsHdmiIn.initialise()

        # Define scaling parameters for testing
        videoScale_argList = [
            [500, 500, 500, 500],
            [500, 500, 1000, 1000],
            [1000, 1000, 1000, 1000]
        ]

        for port in self.testdsHdmiIn.getSupportedPorts():
            if not self.CheckDeviceStatusAndVerifyVideoScale(True, port, False):
                self.testdsHdmiIn.selectHDMIInPort(port, audMix=0, videoPlane=0, topmost=1)
                time.sleep(5)
            for xCord, yCord, width, height in videoScale_argList:
                self.testdsHdmiIn.scaleHdmiInVideo(xCord, yCord, width, height)
                result = self.CheckDeviceStatusAndVerifyVideoScale(True, port, True, xCord, yCord, width, height)
                self.log.stepResult(result, "Video scaled successfully")

        #Run postRequisites listed in the test setup configuration file
        self.testRunPostRequisites()

        # Terminate dsHdmiIn Module
        self.testdsHdmiIn.terminate()

        return result

if __name__ == '__main__':
    test = dsHdmiIn_test9_ScaleVideoAndVerify()
    test.run(False)
