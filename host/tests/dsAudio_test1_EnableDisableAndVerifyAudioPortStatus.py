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

from helpers.dsAudioTestHelper import dsAudioTestHelperClass

test_setup="<PATH>/dsAudio_test1_EnableDisableAndVerifyAudioPortStatus_testsetup.yml" #path to test setup file

class dsAudio_test1_EnableDisableAndVerifyAudioPortStatus(dsAudioTestHelperClass):

    def __init__(self):

        #TODO: read device from yaml file
        super().__init__('test1_EnableDisableAndVerifyAudioPortStatus', '1', test_setup, "cpe1")

    def testFunction(self):
        """This function will test the Audio Port by enabling and disabling the ports

        Returns:
            bool: true
        """
        print("dsAudio_test1_EnableDisableAndVerifyAudioPortStatus")

        self.dsAudioInitialise()
        self.dsAudioEnablePort()
        result = self.dsAudioVerifyAudio(True)
        if result == True:
            self.log.testResultMessage("Passed")
        else :
            self.log.testResultMessage("Failed")

        self.dsAudioDisablePort()
        result = self.dsAudioVerifyAudio(True)
        if result == False:
            self.log.testResultMessage("Passed")
        else :
            self.log.testResultMessage("Failed")

        self.dsAudioTerminate()

        return result

if __name__ == '__main__':
    test = dsAudio_test1_EnableDisableAndVerifyAudioPortStatus()
    test.run(False)
