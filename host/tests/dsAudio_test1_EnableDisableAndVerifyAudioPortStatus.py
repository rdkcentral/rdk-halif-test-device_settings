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

from tests.helpers.dsAudio import dsAudioTestHelperClass

#TODO: Read from command line argument
test_config="../../assets/dsAudio_L3_testSetup.yml" #path to test setup file
device="cpe1"
testGroup = "L3 dsAudio - Sink"

class dsAudio_test1_EnableDisableAndVerifyAudioPortStatus(utHelperClass):

    testName = "test1_EnableDisableAndVerifyAudioPortStatus"

    def __init__(self):
        """
        Initializes the test1_EnableDisableAndVerifyAudioPortStatus test .

        Args:
            None.
        """
        super().__init__(test_config, testGroup, self.testName, '1', device)

    def testFunction(self):
        """This function will test the Audio Port by enabling and disabling the ports

        Returns:
            bool: true
        """

        profile = selfCPEField( "profile " )
        self.dsAudio = dsAudioClass( profile )
        self.dsVideo = dsVideoClass( profile )
        streams = self.dsAudioGetStreams()
        self.dsAudioPlay(streams[0])

        self.log.testStart("test1_EnableDisableAndVerifyAudioPortStatus", '1')
        for port in self.dsAudioGetSupportedPorts():
            self.log.stepStart(f'Enable {port} Port')
            self.log.step(f'Enable {port} Port')

            enable_input = [port, "dsAUDIOARCSUPPORT_eARC"] if port == "dsAUDIOPORT_TYPE_HDMI_ARC" else [port]

            self.dsAudioEnablePort(enable_input)

            self.log.step(f'Verify {port} Port')
            result = self.dsAudioVerifyAudio(True)

            ## How will this test validate the audio
            self.log.stepResult(result, f'Audio Verification {port} Port')
            self.log.stepStart(f'Disable {port} Port')

            self.dsAudioDisablePort([port])

            self.log.step(f'Verify {port} Port')
            result = self.dsAudioVerifyAudio(True)

            self.log.stepResult(not result, f'Audio Verification {port} Port')

        self.dsAudioPlayStop()

        return result

if __name__ == '__main__':
    test = dsAudio_test1_EnableDisableAndVerifyAudioPortStatus()
    test.run(False)
