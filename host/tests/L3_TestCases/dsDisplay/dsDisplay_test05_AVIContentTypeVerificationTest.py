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

class dsDisplay_test05_AVIContentTypeVerificationTest(dsDisplayHelperClass):
    """
    Test validates the setting and retrieval of AVI content type.
    """

    def __init__(self, log: logModule = None):

        self.testName = "test05_AVIContentTypeVerificationTest"
        self.qcID = '5'
        super().__init__(self.testName, self.qcID, log)

    def testVerifyAVIContentType(self, contentType: str):
        """
        Verifies manually if the HDMI Analyzer shows the correct contenttype.

        Args:
            contentType (str): Expected content type string (dsAVICONTENT_TYPE_GRAPHICS, dsAVICONTENT_TYPE_PHOTO,dsAVICONTENT_TYPE_GAME,dsAVICONTENT_TYPE_NOT_SIGNALLED).
        """
        return self.testUserResponse.getUserYN(
            f"Is ContentType '{contentType}' shown correctly on HDMI Analyzer? (Y/N): "
        )

    def testFunction(self):
        """
        Validates Setting and Retrieving AVI Content Types.

        This function performs the following steps:
        - Sets the AVI content type.
        - Waits for manual confirmation via HDMI Analyzer
        - Retrieves the current AVI Scan Information via API
        - Verifies that the retrieved scan info matches the one that was set.

        """

        self.testdsDisplay.initialise()
        finalResult = True

        for port, index in self.testdsDisplay.getSupportedPorts():
            self.testdsDisplay.selectDisplayPort(port, index)

            for contentType in self.testdsDisplay.getavicontenttypelist():
                if contentType not in ["dsAVICONTENT_TYPE_MAX"]:
                    self.log.stepStart(f'Test AVI Content Type: {contentType} on Port: {port}')

                    # Set contenttype
                    self.testdsDisplay.setAVIContentType(contentType)

                    # Manual HDMI Analyzer confirmation
                    manualConfirmed = self.testVerifyAVIContentType(contentType)

                    # API Validation
                    apiResult = self.testdsDisplay.getAVIContentType()
                    #apiConfirmed = contentType in apiResult
                    apiConfirmed=apiResult is not None and contentType in apiResult

                    # Final result for this contentype
                    result = manualConfirmed and apiConfirmed
                    self.log.stepResult(result, f"Verified Content Type '{contentType}' for port {port}")

                    finalResult &= result

            self.testdsDisplay.terminate()
            return finalResult

if __name__ == '__main__':
    summerLogName = os.path.splitext(os.path.basename(__file__))[0] + "_summery"
    summeryLog = logModule(summerLogName, level=logModule.INFO)
    test = dsDisplay_test05_AVIContentTypeVerificationTest(summeryLog)
    test.run(False)

