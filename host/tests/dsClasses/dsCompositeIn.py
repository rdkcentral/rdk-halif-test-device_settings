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
import re

# Add parent outside of the class directory
dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(dir_path+"/../")

from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.plugins.ut_raft.utSuiteNavigator import UTSuiteNavigatorClass
from raft.framework.plugins.ut_raft.interactiveShell import InteractiveShell

class dsCompositeInClass():

    moduleName = "dsCompositeIn"
    menuConfig =  dir_path + "/dsCompositeIn_test_suite.yml"
    testSuite = "L3 dsCompositeIn"

    """
    Device Settings CompositeIn Class

    This module provides common extensions for device Settings CompositeIn Module.
    """
    def __init__(self, deviceProfilePath:str, session=None ):
        """
        Initializes the dsCompositeIn class function.
        """
        self.deviceProfile = ConfigRead( deviceProfilePath, self.moduleName)
        self.utMenu        = UTSuiteNavigatorClass(self.menuConfig, self.moduleName, session)
        self.testSession   = session
        self.utMenu.start()

    def searchPattern(self, haystack, pattern):
        match = re.search(pattern, haystack)
        if match:
            return match.group(1)
        return None

    def initialise(self, device_type:int=0):
        """
        Initializes the device settings CompositeIn module.

        Args:
            device_type (int, optional): 0 - sink device, 1 - source device. Defaults to sink.

        Returns:
            None
        """
        result = self.utMenu.select( self.testSuite, "Initialize CompositeIn")

    def terminate(self):
        """
        Terminates the device settings CompositeIn module.

        Args:
            None.

        Returns:
            None
        """
        result = self.utMenu.select(self.testSuite, "Terminate CompositeIn")

    def getSupportedPorts(self):
        """
        Returns a list of supported compositeIn ports on the device.

        Args:
            None

        Returns:
            list: A list of ports.
        """

        ports = self.deviceProfile.get("ports")
        if not ports:
            return []  # Handle empty ports list

        return ports

    def getStatus(self):
        """
        Gets the status of compositeIn ports.

        Args:
            None.

        Returns:
            dsCompositeInStatus_t : port status
        """
        result = self.utMenu.select( self.testSuite, "Get status of ports")

    def selectPort(self, compositein_port:int):
        """
        Enables the compositeIn port.

        Args:
            compositein_port (int): compositein port.

        Returns:
            None
        """
        promptWithAnswers = [
                {
                    "query_type": "direct",
                    "query": "Enter the port to select:",
                    "input": compositein_port
                }
        ]

        result = self.utMenu.select(self.testSuite, "Select port", promptWithAnswers)

    def scaleVideo(self):
        """
        Scale the video played in compositIn source device

        Args:
            None

        Returns:
            None
        """
        promptWithAnswers = [
                {
                    "query_type": "direct",
                    "query": "Enter the x coordinate to scale:",
                    "input": 0
                },
                {
                    "query_type": "direct",
                    "query": "Enter the y coordinate to scale:",
                    "input": 0
                },
                {
                    "query_type": "direct",
                    "query": "Enter the width coordinate to scale:",
                    "input": 720
                },
                {
                    "query_type": "direct",
                    "query": "Enter the height coordinate to scale:",
                    "input": 576
                }
        ]

        result = self.utMenu.select(self.testSuite, "Scale the compositeIn video", promptWithAnswers)

    def __del__(self):
        """
        De-Initializes the dsCompositeIn helper function.

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

    platformProfile = dir_path + "/../../../profiles/sink/Sink_CompositeInput.yaml"
    # test the class assuming that it's optional
    test = dsCompositeInClass(platformProfile, shell)

    test.initialise()
    ports = test.getSupportedPorts()
    test.getStatus()
    test.scaleVideo()
    test.terminate()

    shell.close()
