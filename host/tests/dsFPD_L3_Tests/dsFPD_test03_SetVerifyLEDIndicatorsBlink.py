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

class dsFPD_test03_SetVerifyLEDIndicatorsBlink(utHelperClass):

    testName  = "test03_SetVerifyLEDIndicatorsBlink"
    testSetupPath = os.path.join(dir_path, "dsFPD_L3_testSetup.yml")
    moduleName = "dsFPD"
    rackDevice = "dut"
    blinkDuration = 1000
    blinkIteration = 5

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

        self.blinkDuration = 1000
        self.blinkIteration = 5

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
    def testVerifyIndicatorBlink(self, indicator, manual=False):
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
            return self.testUserResponse.getUserYN(f"Is {indicator} Blinking {self.blinkDuration/1000} seconds for {self.blinkIteration} times? (Y/N):")
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

        # Loop through the supported audio ports
        for indicator in self.testdsFPD.getSupportedIndicators():
            # Port Enable test
            self.log.stepStart(f'Set {indicator.name} State ON')
            # Enable the audio port
            self.testdsFPD.setState(indicator.name,dsFPDState.dsFPD_STATE_ON.name)
            result = self.testVerifyIndicator(indicator.name,dsFPDState.dsFPD_STATE_ON.name, True)
            self.log.stepResult(result, f'Indicator State Verification {indicator.name} indicator')
            self.testdsFPD.blinkIndicator(indicator.name,self.blinkDuration,self.blinkIteration)
            result = self.testVerifyIndicatorBlink(indicator.name,True)
            self.log.stepResult(result, f'Indicator State Verification {indicator.name} indicator')
            # Port Disable test
            self.log.stepStart(f'Set {indicator.name} state OFF')
            # Disable the audio port
            self.testdsFPD.setState(indicator.name,dsFPDState.dsFPD_STATE_OFF.name)
            result = self.testVerifyIndicator(indicator.name,dsFPDState.dsFPD_STATE_OFF.name,True)
            self.log.stepResult(result, f'Indicator State Verification {indicator.name} indicator')

        # Clean the assets downloaded to the device
        self.testCleanAssets()

        # Terminate dsAudio Module
        self.testdsFPD.terminate()

        # Clean up the dsAudio instance
        del self.testdsFPD

        return result

if __name__ == '__main__':
    test = dsFPD_test03_SetVerifyLEDIndicatorsBlink()
    test.run(False)
