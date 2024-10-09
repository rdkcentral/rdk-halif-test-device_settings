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

import yaml
import os
import sys
import time
from enum import Enum, auto
import re

# Add parent outside of the class directory
dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(dir_path+"/../")

from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.plugins.ut_raft.utSuiteNavigator import UTSuiteNavigatorClass
from raft.framework.plugins.ut_raft.interactiveShell import InteractiveShell

class dsFPDIndicatorType(Enum):
    dsFPD_INDICATOR_MESSAGE   = 0
    dsFPD_INDICATOR_POWER     = auto()
    dsFPD_INDICATOR_RECORD    = auto()
    dsFPD_INDICATOR_REMOTE    = auto()
    dsFPD_INDICATOR_RFBYPASS  = auto() 
    dsFPD_INDICATOR_MAX       = auto()

class dsFPDState(Enum):
    dsFPD_STATE_OFF  = 0
    dsFPD_STATE_ON   = auto()
    dsFPD_STATE_MAX  = auto()

class dsFPDLedState(Enum):
    dsFPD_LED_DEVICE_NONE                    = 0
    dsFPD_LED_DEVICE_ACTIVE                  = auto()
    dsFPD_LED_DEVICE_STANDBY                 = auto()
    dsFPD_LED_DEVICE_WPS_CONNECTING          = auto()
    dsFPD_LED_DEVICE_WPS_CONNECTED           = auto()
    dsFPD_LED_DEVICE_WPS_ERROR               = auto()
    dsFPD_LED_DEVICE_FACTORY_RESET           = auto()
    dsFPD_LED_DEVICE_USB_UPGRADE             = auto()
    dsFPD_LED_DEVICE_SOFTWARE_DOWNLOAD_ERROR = auto()
    dsFPD_LED_DEVICE_MAX                     = auto()

class dsFPDColor(Enum):
    dsFPD_COLOR_BLUE   = 0x0000FF
    dsFPD_COLOR_GREEN  = 0x00FF00
    dsFPD_COLOR_RED    = 0xFF0000
    dsFPD_COLOR_YELLOW = 0xFFFFE0
    dsFPD_COLOR_ORANGE = 0xFF8C00
    dsFPD_COLOR_WHITE  = 0xFFFFFF
    dsFPD_COLOR_MAX    = 6  

class dsFPDClass():

    moduleName = "dsFPD"
    menuConfig =  dir_path + "/dsFPD_test_suite.yml"
    testSuite = "L3 dsFPD"

    """
    Device Settings Front Panel Device Class

    This module provides common extensions for device Settings Front Panel Device Module.
    """
    def __init__(self, deviceProfilePath:str, session=None ):
        """
        Initializes the dsFPD class function.
        """
        self.deviceProfile = ConfigRead( deviceProfilePath, self.moduleName)
        self.utMenu        = UTSuiteNavigatorClass(self.menuConfig, self.moduleName, session)

        self.utMenu.start()

    def searchPattern(self, haystack, pattern):
        match = re.search(pattern, haystack)
        if match:
            return match.group(1)
        return None

    def initialise(self, device_type:int=0):
        """
        Initializes the device settings Front Panel Device module.

        Args:
            None
        Returns:
            None
        """
        result = self.utMenu.select( self.testSuite, "Initialize dsFPD")

    def setState(self, fdp_indicator:int=1, indicator_state:int=1):
        """
        Set the LED Indicator State.

        Args:
            fdp_indicator (int): fpd indicator value enum
            indicator_state (int): fpd indicator state value enum.

        Returns:
            None
        """
        promptWithAnswers = [
            {
                "query_type": "list",
                "query": "Select Indicator : ",
                "input": "dsFPD_INDICATOR_POWER"
            },
            {
                "query_type": "list",
                "query": "Select State : ",
                "input": "dsFPD_STATE_ON"
            }
        ]
        promptWithAnswers[0]["input"] = str(fdp_indicator)
        promptWithAnswers[1]["input"] = str(indicator_state)
        result = self.utMenu.select(self.testSuite, "Set Front Panel Indicator State", promptWithAnswers)

    def getState(self, fdp_indicator:int=1):
        """
        Get the LED Indicator State.

        Args:
            fdp_indicator (int): fpd indicator value enum

        Returns:
            fpd indicator state value enum.
            None
        """
        promptWithAnswers = [
            {
                "query_type": "list",
                "query": "Select Indicator : ",
                "input": "dsFPD_INDICATOR_POWER"
            }
        ]
        promptWithAnswers[0]["input"] = str(fdp_indicator)

        result = self.utMenu.select(self.testSuite, "Get Front Panel Indicator State", promptWithAnswers)
        LedStatePattern = r"Result dsGetFPState\(IN:Indicator:\[.*\], OUT:State:\[(dsFPD_INDICATOR_\w+)\]\)"
        ledState = self.searchPattern(result,LedStatePattern)

        return ledState

    def blinkIndicator(self, fdp_indicator:int=1, blink_duration:int=1000, blink_iteration:int=3):
        """
        Set the FPD indicator to defined Blink pattern.

        Args:
            fdp_indicator (int):   fpd indicator value enum
            blink_duration (int):  duration of On and off state
            blink_iteration (int): iteration of Blink

        Returns:
            None
        """
        promptWithAnswers = [
            {
                "query_type": "list",
                "query": "Select Indicator :",
                "input": "dsFPD_INDICATOR_POWER"
            },
            {
                "query_type": "direct",
                "query": "Enter Blink Duration in ms: ",
                "input": "1000"
            },
            {
                "query_type": "direct",
                "query": "Enter Blink iteration: ",
                "input": "3"
            }
        ]
        promptWithAnswers[0]["input"] = str(fdp_indicator)
        promptWithAnswers[1]["input"] = str(blink_duration)
        promptWithAnswers[1]["input"] = str(blink_iteration)
        result = self.utMenu.select(self.testSuite, "Blink Front Panel Indicator", promptWithAnswers)

    def setBrightness(self, fdp_indicator:int=1, brightness:int=100):
        """
        Set the FPD indicator to defined Blink pattern.

        Args:
            fdp_indicator (int):   fpd indicator value enum
            brightness (int):  brightness of indicator [0-100]

        Returns:
            None
        """
        promptWithAnswers = [
            {
                "query_type": "list",
                "query": "Select Indicator :",
                "input": "dsFPD_INDICATOR_POWER"
            },
            {
                "query_type": "direct",
                "query": "Enter LED Brightness (Range: 0-100): ",
                "input": "100"
            }
        ]
        promptWithAnswers[0]["input"] = str(fdp_indicator)
        promptWithAnswers[1]["input"] = str(brightness)
        result = self.utMenu.select(self.testSuite, "Set Front Panel Indicaor Brightness", promptWithAnswers)

    def getBrightness(self, fdp_indicator:int=1):
        """
        Get the FPD indicator to defined Blink pattern.

        Args:
            fdp_indicator (int):   fpd indicator value enum

        Returns:
            brightness of indicator [0-100]
        """
        promptWithAnswers = [
            {
                "query_type": "list",
                "query": "Select Indicator :",
                "input": "dsFPD_INDICATOR_POWER"
            }
        ]
        promptWithAnswers[0]["input"] = str(fdp_indicator)
        result = self.utMenu.select(self.testSuite, "Get Front Panel Indicaor Brightness", promptWithAnswers)
        
        LedBrightnessPattern = r"Result dsGetFPBrightness\(IN:Indicator:\[.*\], OUT:Brightness:\[(\d+)\]\)"
        ledBrightness = self.searchPattern(result,LedBrightnessPattern)

        return ledBrightness

    def setIndicatorColor(self, fdp_indicator:int=1, color:int=0xFFFFFF):
        """
        Set the FPD indicator to defined Blink pattern.

        Args:
            fdp_indicator (int):   fpd indicator value enum
            color (int):  Front panel indicator color.

        Returns:
            None
        """
        promptWithAnswers = [
            {
                "query_type": "list",
                "query": "Select Indicator :",
                "input": "dsFPD_INDICATOR_POWER"
            },
            {
                "query_type": "list",
                "query": "Select Color: ",
                "input": "dsFPD_COLOR_WHITE"
            }
        ]
        promptWithAnswers[0]["input"] = str(fdp_indicator)
        promptWithAnswers[1]["input"] = str(color)
        result = self.utMenu.select(self.testSuite, "Set Front Panel State Pattern", promptWithAnswers)

    def getIndicatorColor(self, fdp_indicator:int=1):
        """
        Get the FPD indicator to defined Blink pattern.

        Args:
            fdp_indicator (int):   fpd indicator value enum

        Returns:
            Front panel indicator color.
        """
        promptWithAnswers = [
            {
                "query_type": "list",
                "query": "Select Indicator :",
                "input": "dsFPD_INDICATOR_POWER"
            }
        ]
        promptWithAnswers[0]["input"] = str(fdp_indicator)
        result = self.utMenu.select(self.testSuite, "Get Front Panel Indicator Color", promptWithAnswers)

        LedColorPattern = r"Result dsGetFPColor(IN:Indicator:\[.*\], OUT:Color:\[(dsFPD_COLOR_\w+)\]\)"
        ledColor = self.searchPattern(result,LedColorPattern)

        return ledColor


    def setLedStatPattern(self, fdp_indicator:int=1, pattern:int=1):
        """
        Set the FPD indicator to defined Blink pattern.

        Args:
            fdp_indicator (int):   fpd indicator value enum
            pattern (int):  Front panel state for different fucnitons.

        Returns:
            None
        """
        promptWithAnswers = [
            {
                "query_type": "list",
                "query": "Select Indicator :",
                "input": "dsFPD_INDICATOR_POWER"
            },
            {
                "query_type": "list",
                "query": "Select State: ",
                "input": "dsFPD_LED_DEVICE_ACTIVE"
            }
        ]
        promptWithAnswers[0]["input"] = str(fdp_indicator)
        promptWithAnswers[1]["input"] = str(pattern)
        result = self.utMenu.select(self.testSuite, "Set Front Panel State Pattern", promptWithAnswers)

    def getLedStatPattern(self, fdp_indicator:int=1):
        """
        Get the FPD indicator to defined Blink pattern.

        Args:
            fdp_indicator (int):   fpd indicator value enum

        Returns:
            Front panel pattern states.
        """
        promptWithAnswers = [
            {
                "query_type": "list",
                "query": "Select Indicator :",
                "input": "dsFPD_INDICATOR_POWER"
            }
        ]
        promptWithAnswers[0]["input"] = str(fdp_indicator)
        result = self.utMenu.select(self.testSuite, "Get Front Panel State Pattern", promptWithAnswers)

        FPStatePattern = r"Result dsFPGetLEDState(OUT:FP LED State:\[(dsFPD_LED_DEVICE_\w+)\]\)"
        fpState = self.searchPattern(result,FPStatePattern)

        return fpState

    def getSupportedFPStates(self):
        """
        Get Supported Front Panel State patterns.

        Args:
            None.

        Returns:
            All supported Front panel pattern States.
        """
        result = self.utMenu.select(self.testSuite, "Get Supported Front Panel State Patterns")
        SupportedStatesPattern = r"Result dsFPGetSupportedLEDStates\(OUT:states:\[(0x\w+)\]\)"
        supportedStates = self.searchPattern(result,SupportedStatesPattern)

        return supportedStates

    def terminate(self):
        """
        Terminate Front Panle Device.

        Args:
            None.

        Returns:
            None
        """
        result = self.utMenu.select(self.testSuite, "Terminate dsFPD")

    def __del__(self):
        """
        De-Initializes the dsFPD helper function.

        Args:
            None.

        Returns:
            None
        """
        self.utMenu.stop()

# Test and example usage code
if __name__ == '__main__':

    shell = InteractiveShell()
    shell.open()

    platformProfile = dir_path + "/../../../profiles/sink/Sink_FPD.yaml"
    # test the class assuming that it's optional
    test = dsFPDClass(platformProfile, shell)

    test.initialise()
    test.setState(dsFPDIndicatorType.dsFPD_INDICATOR_POWER.value,dsFPDState.dsFPD_STATE_ON.value)
    test.blinkIndicator(dsFPDIndicatorType.dsFPD_INDICATOR_POWER.value,1000,3)
    time.sleep(10)
    test.setState(dsFPDIndicatorType.dsFPD_INDICATOR_POWER.value,dsFPDState.dsFPD_STATE_OFF.value)
    test.setState(dsFPDIndicatorType.dsFPD_INDICATOR_POWER.value,dsFPDState.dsFPD_STATE_ON.value)


    test.terminate()

    shell.close()
