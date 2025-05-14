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

class dsDisplay_test06_AVIScanInfoVerificationTest(dsDisplayHelperClass):
    """
    Test validates the setting and retrieval of AVI Scan Information.
    """

    def __init__(self, log: logModule = None):
        self.testName = "test06_AVIScanInfoVerificationTest"
        self.qcID = '6'
        super().__init__(self.testName, self.qcID, log)

    def testVerifyAVIScanInfo(self, scanInfo: str):
        """
        Verifies manually if the HDMI Analyzer shows the correct scan info.

        Args:
            scanInfo (str): Expected scan info ("dsAVI_SCAN_TYPE_NO_DATA", "dsAVI_SCAN_TYPE_OVERSCAN", "dsAVI_SCAN_TYPE_UNDERSCAN")
        """
        return self.testUserResponse.getUserYN(
            f"Is Scan Info '{scanInfo}' (S1/S0 bits) shown correctly on HDMI Analyzer? (Y/N): "
        )

    def testFunction(self):

        """
        Validates Setting and Retrieving AVI scaninfo.

        This function performs the following steps:
        - Sets the AVI scaninfo .
        - Waits for manual confirmation via HDMI Analyzer
        - Retrieves the current AVI Scan Information via API
        - Verifies that the retrieved scan info matches the one that was set.
        """

        self.testdsDisplay.initialise()
        finalResult = True

        for port, index in self.testdsDisplay.getSupportedPorts():
            self.testdsDisplay.selectDisplayPort(port, index)

            #for scanInfo in self.testScanInfo:
            for scanInfo in self.testdsDisplay.getaviscaninfolist():
                if scanInfo not in ["dsAVI_SCAN_TYPE_MAX"]:
                    self.log.stepStart(f'Test AVI Scan Info: {scanInfo} on Port: {port}')

                    # Set Scan Info
                    self.testdsDisplay.setAVIScanInformation(scanInfo)

                    # Manual HDMI Analyzer confirmation
                    manualConfirmed = self.testVerifyAVIScanInfo(scanInfo)

                    # API Validation
                    apiResult = self.testdsDisplay.getAVIScanInformation()
                    apiConfirmed = scanInfo in apiResult

                    # Final result for this scanInfo
                    result = manualConfirmed and apiConfirmed
                    self.log.stepResult(result, f"Verified Scan Info '{scanInfo}' for port {port}")

                    finalResult &= result

            self.testdsDisplay.terminate()
            return finalResult

if __name__ == '__main__':
    summerLogName = os.path.splitext(os.path.basename(__file__))[0] + "_summery"
    summeryLog = logModule(summerLogName, level=logModule.INFO)
    test = dsDisplay_test06_AVIScanInfoVerificationTest(summeryLog)
    test.run(False)
