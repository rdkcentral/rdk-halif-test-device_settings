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
from enum import Enum, auto

# Add parent outside of the class directory
dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(dir_path+"/../")

from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.plugins.ut_raft.utSuiteNavigator import UTSuiteNavigatorClass
from raft.framework.plugins.ut_raft.interactiveShell import InteractiveShell

class dsHostClass():

    moduleName = "dsHost"
    menuConfig =  dir_path + "/dsHost_test_suite.yml"
    testSuite = "L3 dsHost"

    """
    Device Settings Audio Class

    This module provides common extensions for device Settings Audio Module.
    """
    def __init__(self, deviceProfilePath:str, session=None ):
        """
        Initializes the dsHost class function.
        """
        self.deviceProfile = ConfigRead( deviceProfilePath, self.moduleName)
        self.utMenu        = UTSuiteNavigatorClass(self.menuConfig, self.moduleName, session)

        self.utMenu.start()

    def initialise(self):
        """
        Initializes the device settings Host module.

        Args:
            None

        Returns:
            None
        """
        result = self.utMenu.select( self.testSuite, "Initialize dsHost")
    
    def getCPUTemperature(self):
        """
        Get the CPU temperature.

        Args:
            None

        Returns:
            None
        """
        result = self.utMenu.select( self.testSuite, "Get CPU Temperature")

    def getSoCID(self):
        """
        Get the SoC ID.

        Args:
            None

        Returns:
            None
        """
        result = self.utMenu.select( self.testSuite, "Get SoC ID")

    def getHostEDID(self):
        """
        Get the Host EDID.

        Args:
            None

        Returns:
            None
        """
        result = self.utMenu.select( self.testSuite, "Get Host EDID")

    def terminate(self):
        """
        Enables the audio port.

        Args:
            None.

        Returns:
            None
        """
        result = self.utMenu.select(self.testSuite, "Terminate dsHost")

    def __del__(self):
        """
        De-Initializes the dsHost helper function.

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

    platformProfile = dir_path + "/../../../profiles/sink/Sink_AudioSettings.yaml"
    # test the class assuming that it's optional
    test = dsHostClass(platformProfile, shell)

    test.initialise()
    test.getCPUTemperature()
    test.getSoCID()
    test.getHostEDID()
    test.terminate()

    shell.close()
