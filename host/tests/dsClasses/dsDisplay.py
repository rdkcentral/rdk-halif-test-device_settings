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

class dsVideoPortType(Enum):
    dsVIDEOPORT_TYPE_RF     = 0
    dsVIDEOPORT_TYPE_BB =auto()
    dsVIDEOPORT_TYPE_SVIDEO =auto()
    dsVIDEOPORT_TYPE_1394 =auto()
    dsVIDEOPORT_TYPE_DVI =auto()
    dsVIDEOPORT_TYPE_COMPONENT =auto()
    dsVIDEOPORT_TYPE_HDMI =auto()
    dsVIDEOPORT_TYPE_HDMI_INPUT =auto()
    dsVIDEOPORT_TYPE_INTERNAL =auto()

class dsDisplayClass():

    moduleName = "dsDisplay"
    menuConfig =  dir_path + "/dsDisplay_test_suite.yml"
    testSuite = "L3 dsDisplay"

    """
    Device Settings Display Class
    This module provides common extensions for device Settings Display Module.
    """
    def __init__(self, deviceProfilePath:str, session=None ):
        """
        Initializes the dsDisplay class function.
        """
        self.deviceProfile = ConfigRead( deviceProfilePath, self.moduleName)
        self.utMenu        = UTSuiteNavigatorClass(self.menuConfig, self.moduleName, session)

        self.utMenu.start()

    def initialise(self, device_type:int=0):
        """
        Initializes the device settings Display module.

        Args:
            device_type (int, optional): 0 - sink device, 1 - source device. Defaults to sink.

        Returns:
                None
        """
        result = self.utMenu.select( self.testSuite, "Initialize dsDisplay")

    def getEdid(self, video_port: str, port_index: int = 0):
        """
        Gets the EDID information.

        Args:
            port_type (str): name of the video port. Refer dsVideoPortType enum
            port_index (int, optional): port index. Defaults to 0

            Returns:
                None
        """
        promptWithAnswers = [
                {
                    "query_type": "list",
                    "query": "Select dsVideo Port:",
                    "input":str(video_port)
                },
                {
                    "query_type": "direct",
                    "query": "Select dsVideo Port Index[0-10]:",
                    "input": str(port_index)
                }
        ]

        promptWithAnswers[0]["input"] = str(video_port)
        promptWithAnswers[1]["input"] = str(port_index)

        result = self.utMenu.select(self.testSuite, "Get display EDID", promptWithAnswers)

    def getEdidBytes(self, video_port: str, port_index: int = 0):
        """
        Gets the EDID bytes.

        Args:
            video_port (str): name of the video port. Refer dsVideoPortType enum
            port_index (int, optional): port index. Defaults to 0

        Returns:
            None
        """
        promptWithAnswers = [
                {
                    "query_type": "list",
                    "query": "Select dsVideo Port:",
                    "input": str(video_port)
                },
                {
                    "query_type": "direct",
                    "query": "Select dsVideo Port Index[0-10]:",
                    "input": str(port_index)
                }
        ]

        promptWithAnswers[0]["input"] = str(video_port)
        promptWithAnswers[1]["input"] = str(port_index)

        result = self.utMenu.select(self.testSuite, "Get display EDIDBytes", promptWithAnswers)

    def getAspectRatio(self, video_port: str, port_index: int = 0):
        """
        Gets the display aspect ratio.

        Args:
            video_port (str): name of the video port. Refer dsVideoPortType enum
            port_index (int, optional): port index. Defaults to 0

        Returns:
            None
        """
        promptWithAnswers = [
            {
                "query_type": "list",
                "query": "Select dsVideo Port:",
                "input": str(video_port)
            },
            {
                "query_type": "direct",
                "query": "Select dsVideo Port Index[0-10]:",
                "input": str(port_index)
            }
        ]

        promptWithAnswers[0]["input"] = str(video_port)
        promptWithAnswers[1]["input"] = str(port_index)

        result = self.utMenu.select(self.testSuite, "Get display AspectRatio", promptWithAnswers)

    def terminate(self):
        """
        Terminates the display.

        Args:
            None.

        Returns:
            None
        """
        result = self.utMenu.select(self.testSuite, "Terminate dsDisplay")

    def getDisplayHandle(self, video_port: str, port_index: int=0):
        """
        Returns the handle of the display port.

        Args:
            video_port (str): name of the video port. Refer dsVideoPortType enum
            port_index (int): port index

        Returns:
            int: The handle of the display port.
        """
        ports = self.deviceProfile.get("Ports")
        if not ports:
            return None  # Handle empty ports list

        for entry in ports.values():
            if entry['Typeid'] == video_port and entry['Index'] == port_index:
                handle = entry['Handle']
                return handle

        return None

    def getSupportedPorts(self):
        """
        Returns the supported Video ports on the device.
        Args:
            None.

        Returns:
            list: A list of tuples containing (video_port_name, index).
        """
        portLists= []

        ports = self.deviceProfile.get("Video_Ports")  # Default to empty list if "Ports" not found
        for entry in ports:  # Iterate directly through the list of ports

            video_port_name = dsVideoPortType(entry).name  # Get the name of the video port type
            port_index =  0# Get the index
            portLists.append((video_port_name, port_index))  # Append as a tuple

        return portLists

    def __del__(self):
        """
        De-Initializes the dsDisplay helper function.
        Args:
            None.
        Returns:
            None
        """
        self.utMenu.stop()

if __name__ == '__main__':

    shell = InteractiveShell()
    shell.open()

    platformProfile = dir_path + "/../../../profiles/source/Source_4K_DisplayPort.yaml"
    # test the class assuming that it's optional
    test = dsDisplayClass(platformProfile, shell)

    test.initialise()

    ports = test.getSupportedPorts()

    test.getEdid(ports[0][0], ports[0][1])
    test.getEdidBytes(ports[0][0], ports[0][1])
    test.getAspectRatio(ports[0][0], ports[0][1])

    test.terminate()

    shell.close()


