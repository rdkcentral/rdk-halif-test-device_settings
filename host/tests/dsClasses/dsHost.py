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
import re
from enum import Enum, auto

# Add parent outside of the class directory
dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(dir_path+"/../")

from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.plugins.ut_raft.utSuiteNavigator import UTSuiteNavigatorClass
from raft.framework.plugins.ut_raft.interactiveShell import InteractiveShell
from raft.framework.plugins.ut_raft.utBaseUtils import utBaseUtils

class dsHostClass():

    """
    Device Settings Host Class

    This module provides common extensions for device Settings Host Module.
    """
    def __init__(self, moduleConfigProfileFile:str, session=None, testSuite:str="L3 dsHost",targetWorkspace="/tmp" ):
        """
        Initializes the dsHost class function.

        Args:
            moduleConfigProfileFile  (str): Path to the device profile configuration file.
            session: Optional; session object for the user interface.

        Returns:
            None
        """

        self.moduleName = "dsHost"
        self.testConfigFile =  os.path.join(dir_path, "dsHost_testConfig.yml")
        self.testConfig    = ConfigRead(self.testConfigFile, self.moduleName)
        self.testConfig.test.execute = os.path.join(targetWorkspace, self.testConfig.test.execute)
        self.testConfig.test.execute = self.testConfig.test.execute + f" -p {os.path.basename(moduleConfigProfileFile)}"
        self.testSuite = testSuite

        self.deviceProfile = ConfigRead( moduleConfigProfileFile, self.moduleName)
        self.utMenu        = UTSuiteNavigatorClass(self.testConfig, None, session)
        self.testSession = session
        self.utils         = utBaseUtils()

        for artifact in self.testConfig.test.artifacts:
            filesPath = os.path.join(dir_path, artifact)
            self.utils.rsync(self.testSession, filesPath, targetWorkspace)

        # Copy the profile file to the target
        self.utils.scpCopy(self.testSession, moduleConfigProfileFile, targetWorkspace)

        self.utMenu.start()

    def searchPattern(self, haystack, pattern):
        match = re.search(pattern, haystack)
        if match:
            return match.group(1)
        return None

    def runTest(self, test_case:str=None):
        """
        Runs the test case passed to this funtion

        Args:
            test_case (str, optional): test case name to run, default runs all test

        Returns:
            bool: True - test pass, False - test fails
        """
        output = self.utMenu.select( self.testSuite, test_case)
        results = self.utMenu.collect_results(output)
        if results == None:
            results = False
        return results

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
        typeStatusPattern = r'Result dsGetCPUTemperature\(cpuTemperature: (?P<cpuTemperature>[-+]?\d*\.\d+|\d+)\)'
        match = self.searchPattern(result, typeStatusPattern)

        if match:
            temperature = float(match)
            return temperature
        else:
            print("Error: Could not get CPU temperature")
            return None

    def terminate(self):
        """
        Terminates the host plugin.

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

    platformProfile = dir_path + "/../../../profiles/sink/Sink_HostSettings.yaml"
    # test the class assuming that it's optional
    test = dsHostClass(platformProfile, shell)

    test.initialise()
    test.getCPUTemperature()
    test.terminate()

    shell.close()
