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

from L3_TestCases.dsFPD.dsFPDHelperClass import dsFPDHelperClass
from dsClasses.dsFPD import dsFPDIndicatorType
from dsClasses.dsFPD import dsFPDColor
from dsClasses.dsFPD import dsFPDLedState
from dsClasses.dsFPD import dsFPDState


class dsFPD_test01_EnableDisableAndVerifyLEDIndicators(dsFPDHelperClass):

    def __init__(self):
        """
        Initializes the dsFPD_test01_EnableDisableAndVerifyLEDIndicators test .

        Args:
            None.
        """
        self.testName  = "test01_EnableDisableAndVerifyLEDIndicators"
        super().__init__(self.testName, '1')


    #TODO: Current version supports only manual verification.
    def testVerifyIndicator(self, indicator, state, manual=False):
        """
        Verifies whether the Front panel Indicator is set to specified state

        Args:
            indicator (str) : Front Panel Indicator
            state (str) : Front Panel Indicator State
            manual (bool, optional): Manual verification (True: manual, False: automated).
                                     Defaults to False

        Returns:
            bool : Returns the status of the indicator state verification.
        """
        if manual == True:
            return self.testUserResponse.getUserYN(f"Is {indicator} state {state}? (Y/N):")
        else :
            #TODO: add automation verification methods
            return False

    def testFunction(self):
        """tests the front panel indicators by enabling and disabling the indicators.

        Returns:
            bool: final result of the test.
        """

        self.log.testStart(self.testName, '1')

        # initialize the dsFPD module
        self.testdsFPD.initialise()

        # Loop through the supported indicators
        for indicator in self.testdsFPD.getSupportedIndicators():
            # Indicator Enable test
            self.log.stepStart(f'Set {indicator.name} State ON')
            # Enable the indicator
            self.testdsFPD.setState(indicator.name,dsFPDState.dsFPD_STATE_ON.name)
            result = self.testVerifyIndicator(indicator.name,dsFPDState.dsFPD_STATE_ON.name, True)
            self.log.stepResult(result, f'Indicator State Verification {indicator.name} indicator')
            result = False
            state = self.testdsFPD.getState(indicator.name)
            if state == dsFPDState.dsFPD_STATE_ON.name:
                result = True
            self.log.stepResult(result, f'Indicator {indicator.name} get  {state} state')

            # Indicator Disable test
            self.log.stepStart(f'Set {indicator.name} state OFF')
            # Disable the indicator
            self.testdsFPD.setState(indicator.name,dsFPDState.dsFPD_STATE_OFF.name)
            result = self.testVerifyIndicator(indicator.name,dsFPDState.dsFPD_STATE_OFF.name,True)
            self.log.stepResult(result, f'Indicator State Verification {indicator.name} indicator')
            result = False
            state = self.testdsFPD.getState(indicator.name)
            if state == dsFPDState.dsFPD_STATE_OFF.name:
                result = True
            self.log.stepResult(result, f'Indicator {indicator.name} get  {state} state')

        # Terminate dsFPD Module
        self.testdsFPD.terminate()

        return result

if __name__ == '__main__':
    test = dsFPD_test01_EnableDisableAndVerifyLEDIndicators()
    test.run(False)
