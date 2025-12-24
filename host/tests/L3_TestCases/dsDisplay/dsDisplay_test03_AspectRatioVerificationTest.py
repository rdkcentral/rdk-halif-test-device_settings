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

from dsDisplayHelperClass import dsDisplayHelperClass
from raft.framework.core.logModule import logModule
from dsClasses.dsVideoPort import dsVideoPortClass

class dsDisplay_test03_AspectRatioVerificationTest(dsDisplayHelperClass):

    """
    Test class to retrieve and verify the display aspect ratio.

    This class uses the `dsDisplayClass` to interact with the device's display,
    downloading necessary test assets, retrieving the aspect ratio, and performing verification.
    """

    def __init__(self, log:logModule=None):
        """
        Initializes the test03_GetDisplayAspectRatio test .

        Args:
            None.
        """
        # Class variables
        self.testName  = "test03_AspectRatioVerificationTest"
        self.qcID = '3'
        super().__init__(self.testName, self.qcID, log)
        self.videoPortProfileFile = os.path.join(dir_path, "../../../../profiles/source/Source_4K_VideoPort.yaml")
        self.videoport_session = self.dut.getConsoleSession("ssh_hal_test1")
        self.testdsVideoPort = dsVideoPortClass(self.videoPortProfileFile, self.videoport_session, "L3 dsVideoPort", self.targetWorkspace)


    def testFunction(self):
        """
        This function will test the Display by getting the aspectratio of the display.

        This function:
        - Retrieves aspectratio for each supported port and verifies them.
        - Cleans up assets after the test.

        Returns:
            bool: Final result of the test.
        """

        self.testdsVideoPort.initialise()
        # Initialize the dsDisplay module
        self.testdsDisplay.initialise()

        result = False
        # Loop through the supported video ports
        for port, index in self.testdsDisplay.getSupportedPorts():
            # Enable video port
            self.testdsVideoPort.enablePort(port, index)
            # Enable HDCP for source devices
            if self.testdsVideoPort.getDeviceType():
                self.testdsVideoPort.enable_HDCP(port, index)

            for resolution in self.testdsVideoPort.getResolutions():
                # set videoport resolution
                self.testdsVideoPort.select_Resolution(port, index, resolution)

                self.testdsDisplay.selectDisplayPort(port, index)

                aspectRatio = resolution.get("aspectRatio")

                self.log.stepStart(f'Test Display Aspect Ratio {aspectRatio} Port: {port}')
                ratio = self.testdsDisplay.getAspectRatio()
                if ratio == aspectRatio:
                    result = True
                else:
                    result = False
                self.log.stepResult(result, f'Test Display Aspect Ratio {aspectRatio} Port: {port}')

        self.testdsVideoPort.terminate()
        #Terminate dsDisplay Module
        self.testdsDisplay.terminate()

        return result

if __name__ == '__main__':
    summerLogName = os.path.splitext(os.path.basename(__file__))[0] + "_summery"
    summeryLog = logModule(summerLogName, level=logModule.INFO)
    test = dsDisplay_test03_AspectRatioVerificationTest(summeryLog)
    test.run(False)

