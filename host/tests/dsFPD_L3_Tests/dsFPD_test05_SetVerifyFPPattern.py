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
sys.path.append(os.path.join(dir_path, "../"))

from dsClasses.dsFPD import dsFPDClass
from dsClasses.dsFPD import dsFPDState
from raft.framework.plugins.ut_raft import utHelperClass
from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.plugins.ut_raft.utPlayer import utPlayer
from raft.framework.plugins.ut_raft.utUserResponse import utUserResponse

class dsFPD_test05_SetVerifyFPPattern(utHelperClass):

    testName  = "test05_SetVerifyFPPattern"
    testSetupPath = os.path.join(dir_path, "dsFPD_L3_testSetup.yml")
    moduleName = "dsFPD"
    rackDevice = "dut"

    def __init__(self):
        """
        Initializes the test01_EnableDisableAndVerifyAudioPortStatus test .

        Args:
            None.
        """
        super().__init__(self.testName, '1')

        # Test Setup configuration file
        self.testSetup = ConfigRead(self.testSetupPath, self.moduleName)

        # Open Sessions for player and hal test
        self.hal_session = self.dut.getConsoleSession("ssh_hal_test")

         # Create user response Class
        self.testUserResponse = utUserResponse()

        # Get path to device profile file
        self.deviceProfile = os.path.join(dir_path, self.cpe.get("test").get("profile"))

    def testDownloadAssets(self):
        """
        Downloads the artifacts in test-setup configuration file to the dut.

        Args:
            None.
        """

        self.deviceDownloadPath = self.cpe.get("target_directory")

        test = self.testSetup.get("assets").get("device").get(self.testName)

        # Download test artifacts to device
        url = test.get("artifacts")
        if url is not None:
            self.downloadToDevice(url, self.deviceDownloadPath, self.rackDevice)

    def testCleanAssets(self):
        """
        Removes the assets copied to the dut.

        Args:
            None.
        """

    def testRunPrerequisites(self):
        """
        Runs Prerequisite commands listed in test-setup configuration file on the dut.

        Args:
            None.
        """

        #Run test specific commands
        test = self.testSetup.get("assets").get("device").get(self.testName)
        cmds = test.get("execute");
        if cmds is not None:
            for cmd in cmds:
                self.writeCommands(cmd)

    #TODO: Current version supports only manual verification.
    def testVerifyIndicator(self, indicator, state, manual=False):
        """
        Verifies whether the audio is working on the specified port.

        Args:
            port (str) : Audio port to verify
            manual (bool, optional): Manual verification (True: manual, False: automated).
                                     Defaults to False

        Returns:
            bool : Returns the status of the audio verification.
        """
        if manual == True:
            return self.testUserResponse.getUserYN(f"Is {indicator} state {state}? (Y/N):")
        else :
            #todo: add automation verification methods
            return False
    
    #TODO: Current version supports only manual verification.
    def testVerifyIndicatorPattern(self, pattern, manual=False):
        """
        Verifies whether the audio is working on the specified port.

        Args:
            port (str) : Audio port to verify
            manual (bool, optional): Manual verification (True: manual, False: automated).
                                     Defaults to False

        Returns:
            bool : Returns the status of the audio verification.
        """
        if manual == True:
            return self.testUserResponse.getUserYN(f"Is Front Panel Pattern {pattern}? (Y/N):")
        else :
            #todo: add automation verification methods
            return False

    def testFunction(self):
        """tests the audio ports by enabling and disabling the ports.

        Returns:
            bool: final result of the test.
        """

        # download the assets listed in test setup configuration file
        self.testDownloadAssets()

        # run prerequisites listed in the test setup configuration file
        self.testRunPrerequisites()

        # create the dsaudio class
        self.testdsFPD = dsFPDClass(self.deviceProfile, self.hal_session)

        self.log.testStart(self.testName, '1')

        # initialize the dsaudio module
        self.testdsFPD.initialise()

        supportedStates = self.testdsFPD.getSupportedFPStates()
        supportedStates = 0x1FE
        for pattern in self.testdsFPD.getSupportedStatesFromConfig():
            if not (supportedStates & (1<<pattern.value)):
                result = False
                self.log.stepResult(result, f'Front Panel Do not support {pattern.name}')
                continue
            self.testdsFPD.setLedStatePattern(pattern.name)
            result = self.testVerifyIndicatorPattern(pattern.name, True)
            currentPattern = self.testdsFPD.getLedStatePattern()
            result = False
            if currentPattern == pattern.name:
                result = True
            self.log.stepResult(result, f'Front Panel Get Pattern Verification for {pattern.name}, retrieved Pattern {currentPattern}')

        # Clean the assets downloaded to the device
        self.testCleanAssets()

        # Terminate dsAudio Module
        self.testdsFPD.terminate()

        # Clean up the dsAudio instance
        del self.testdsFPD

        return result

if __name__ == '__main__':
    test = dsFPD_test05_SetVerifyFPPattern()
    test.run(False)
