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

class dsHdmiIn_test6_AVlatencyCallback_Verify(dsHdmiInHelperClass):
    """
    A test class to verify the audio-video latency callback for HDMI input devices.

    This class inherits from `dsHdmiInHelperClass` and focuses on:
    - Verifying the audio and video latency updates through callback mechanisms.
    """


    def __init__(self):
        """
        Initializes the dsHdmiIn_test6_AVlatencyCallback_Verify test case.

        Sets the test name and calls the superclass constructor.
        """
        self.testName  = "test6_AVlatencyCallback_Verify"
        super().__init__(self.testName, '1')

    def testFunction(self):
        """
        The main test function that verifies audio-video latency of HDMI input devices.

        This function:
        - Initializes the HDMI input module.
        - Loops through each supported HDMI input port to verify latency.
        - Logs the results of the latency verification.

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
            result = self.CheckDeviceStatus(True,port)
            if not result:
                self.testdsHdmiIn.selectHDMIInPort(port, audMix=0, videoPlane=0, topmost=1)
                time.sleep(5)
                self.log.step(f'Port Selected {port}')
            avLatency = self.testdsHdmiIn.getAVlatencyCallbackStatus()
            self.log.step(f'audio_latency:{avLatency[0]}ms, videoLatency:{avLatency[1]}ms found in Callback')
            result &= self.testUserResponse.getUserYN(f'Is AV Latency is changed on {port_type} press Y/N:')

        self.log.stepResult(result,f"AV Latency is change Verified ")
        #Run postRequisites listed in the test setup configuration file
        self.testRunPostRequisites()

        # Terminate dsHdmiIn Module
        self.testdsHdmiIn.terminate()

        return result

if __name__ == '__main__':
    test = dsHdmiIn_test6_AVlatencyCallback_Verify()
    test.run(False)
