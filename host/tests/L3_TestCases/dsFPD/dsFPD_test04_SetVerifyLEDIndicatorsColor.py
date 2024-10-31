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
from dsClasses.dsFPD import dsFPDState


class dsFPD_test04_SetVerifyLEDIndicatorsColor(dsFPDHelperClass):

    def __init__(self):
        """
        Initializes the test04_SetVerifyLEDIndicatorsColor test .

        Args:
            None.
        """
        self.testName  = "test04_SetVerifyLEDIndicatorsColor"
        super().__init__(self.testName, '4')


    def testVerifyIndicatorColor(self, indicator, color, manual=False):
        """
        Verifies whether the indicator is in provided color

        Args:
            indicator (str) : front panel indicator
            color (str) : color of front panel indicator
            manual (bool, optional): Manual verification (True: manual, False: automated).
                                     Defaults to False

        Returns:
            bool : Returns the status of the front panel indicator color verification.
        """
        if manual == True:
            return self.testUserResponse.getUserYN(f"Is {indicator} color {color}? (Y/N):")
        else :
            #todo: add automation verification methods
            return False

    def testFunction(self):
        """tests the front panle indicator colors.

        Returns:
            bool: final result of the test.
        """

        self.log.testStart(self.testName, '4')

        # initialize the dsFPD module
        self.testdsFPD.initialise()

        # Loop through the supported indicators
        for indicator in self.testdsFPD.getSupportedIndicators():
            colorMode = self.testdsFPD.getDefaultColorMode(indicator.value)
            if colorMode == 0:
                result = False
                self.log.stepResult(result, f'Indicator {indicator.name} Do not support Multi Color Mode')
                continue

            self.log.stepStart(f'Set {indicator.name} State ON')
            # Enable the Indicator
            self.testdsFPD.setState(indicator.name,dsFPDState.dsFPD_STATE_ON.name)
            result = self.testVerifyIndicator(indicator.name,dsFPDState.dsFPD_STATE_ON.name, True)
            self.log.stepResult(result, f'Indicator State Verification {indicator.name} indicator')
            # Loop through supported colors
            colors = self.testdsFPD.getSupportedColors(indicator.value)
            for color in colors:
                self.testdsFPD.setIndicatorColor(indicator.name,color.value)
                result = self.testVerifyIndicatorColor(indicator.name,color.name, True)
                self.log.stepResult(result, f'Color Verification for {indicator.name} indicator, {color.name} Color')
                retrievedColor = self.testdsFPD.getIndicatorColor(indicator.name)
                result = False
                if retrievedColor == color.name:
                    result = True
                self.log.stepResult(result, f'Indicator Get Color Verification {indicator.name} indicator, {retrievedColor}')

            self.log.stepStart(f'Set {indicator.name} state OFF')
            # Disable the Indicator
            self.testdsFPD.setState(indicator.name,dsFPDState.dsFPD_STATE_OFF.name)
            result = self.testVerifyIndicator(indicator.name,dsFPDState.dsFPD_STATE_OFF.name,True)
            self.log.stepResult(result, f'Indicator State Verification {indicator.name} indicator')

        # Terminate dsFPD Module
        self.testdsFPD.terminate()

        return result

if __name__ == '__main__':
    test = dsFPD_test04_SetVerifyLEDIndicatorsColor()
    test.run(False)
