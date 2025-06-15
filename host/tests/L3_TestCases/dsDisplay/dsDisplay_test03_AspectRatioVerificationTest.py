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

class dsDisplay_test03_AspectRatioVerificationTest(dsDisplayHelperClass):

    """
    Test class to verify display aspect ratio by playing a known resolution stream and comparing with expected aspect ratio.
    """

    def __init__(self, log:logModule=None):
        """
        Initializes the test03_GetDisplayAspectRatio test .

        Args:
            None.
        """
        # Class variables
        self.testAspectRatios = ["dsVIDEO_ASPECT_RATIO_16x9", "dsVIDEO_ASPECT_RATIO_4x3"]
        self.testName  = "test03_AspectRatioVerificationTest"
        self.qcID = '3'
        super().__init__(self.testName, self.qcID, log)

    #TODO: Current version supports only manual verification.
    def testChangeDisplayAspectRatio(self, port:str, aspectRatio:str, manual=False) -> bool:
        """
        Gets the aspectratio of the display.
        Args:
            port (str): Port name
            aspectRatio (str) : aspectRatio ratio eg: 4x3, 16x9
            manual (bool, optional): Manual verification (True: manual, False: other verification methods).
                                    Defaults to other verification methods
        Returns:
            None
        """
        if manual:
            return self.testUserResponse.getUserYN(f"Is the aspect ratio {aspectRatio} correctly applied on Port: {port}? (Y/N):")
        else :
            return False

    def testFunction(self):
        """
        Executes the aspect ratio verification test by:
        - Playing a known-resolution stream.
        - Getting current aspect ratio from dsDisplay.
        - Comparing it with expected value.

        Returns:
            bool: Final result of the test.
        """

        # Initialize the dsDisplay module
        self.testdsDisplay.initialise()

        result = True

        for streamUrl, aspectRatio in zip(self.streamPaths, self.testAspectRatios):
                streamPath = self.downloadStreamToDevice(streamUrl)
                streamPath = streamPath.replace("\\", "/")
                for port, index in self.testdsDisplay.getSupportedPorts():
                    self.testdsDisplay.selectDisplayPort(port, index)
                    self.testPlayer.play(streamPath)
                    self.log.stepStart(f"Testing Display Aspect Ratio {aspectRatio} on Port: {port}")
                    userConfirmed = self.testChangeDisplayAspectRatio(port, aspectRatio, manual=True)
                    reportedAspect = self.testdsDisplay.getAspectRatio()
                    matched = aspectRatio in reportedAspect if reportedAspect else False
                    stepResult = userConfirmed and matched
                    self.log.stepResult(stepResult, f"Expected: {aspectRatio}, Reported: {reportedAspect}, Port: {port}")

                    result = result and stepResult
                    self.testPlayer.stop()

                self.testDeleteSingleStream(streamPath)

        #Terminate dsDisplay Module
        self.testdsDisplay.terminate()

        return result

if __name__ == '__main__':
    summerLogName = os.path.splitext(os.path.basename(__file__))[0] + "_summery"
    summeryLog = logModule(summerLogName, level=logModule.INFO)
    test = dsDisplay_test03_AspectRatioVerificationTest(summeryLog)
    test.run(False)
