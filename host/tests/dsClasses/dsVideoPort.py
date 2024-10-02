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
    dsVIDEOPORT_TYPE_RF          = 0
    dsVIDEOPORT_TYPE_BB          = auto()
    dsVIDEOPORT_TYPE_SVIDEO      = auto()
    dsVIDEOPORT_TYPE_1394        = auto()
    dsVIDEOPORT_TYPE_DVI         = auto()
    dsVIDEOPORT_TYPE_COMPONENT   = auto()
    dsVIDEOPORT_TYPE_HDMI        = auto()
    dsVIDEOPORT_TYPE_HDMI_INPUT  = auto()
    dsVIDEOPORT_TYPE_INTERNAL    = auto()
    dsVIDEOPORT_TYPE_MAX         = auto()

class dsVideoPortClass():

    moduleName = "dsVideoPort"
    menuConfig =  dir_path + "/dsVideoPort_test_suite.yml"
    testSuite = "L3 dsVideoPort"

    """
    Device Settings VideoPort Class

    This module provides common extensions for device Settings VideoPort Module.
    """
    def __init__(self, deviceProfilePath:str, session=None ):
        """
        Initializes the dsVideoPort class function.
        """
        self.deviceProfile = ConfigRead( deviceProfilePath, self.moduleName)
        self.utMenu        = UTSuiteNavigatorClass(self.menuConfig, self.moduleName, session)

        self.utMenu.start()

    def initialise(self, device_type:int=0):
        """
        Initializes the device settings dsVideoPort module.

        Args:
            device_type (int, optional): 0 - sink device, 1 - source device. Defaults to sink.

        Returns:
            None
        """
        result = self.utMenu.select( self.testSuite, "VideoPort Init")

    def enablePort(self, video_port:int, port_index:int=0):
        """
        Enables the video port.

        Args:
            video_port (int): video port enum value
            port_index (int): port index
            arc_type (int, optional): Type of ARC. Defaults to eArc.

        Returns:
            None
        """
        promptWithAnswers = [
            {
                "query_type": "list",
                "query": "Select the Video Port",
                "input": "dsVIDEOPORT_TYPE_HDMI"
            },
            {
                "query_type": "direct",
                "query": "Select the Video Port Index[0-9]:",
                "input": "0"
            }
        ]

        promptWithAnswers[0]["input"] = str(video_port)
        promptWithAnswers[1]["input"] = str(port_index)

        result = self.utMenu.select(self.testSuite, "Enable VideoPort", promptWithAnswers)

    def disablePort(self, video_port:int, port_index:int=0):
        """
        Enables the Video port.

        Args:
            video_port (str): name of the video port. Refer dsVideoPortType enum

        Returns:
            None
        """
        promptWithAnswers = [
            {
                "query_type": "list",
                "query": "Select the Video Port",
                "input": "dsVIDEOPORT_TYPE_HDMI"
            },
            {
                "query_type": "direct",
                "query": "Select the Video Port Index[0-9]:",
                "input": "0"
            }
        ]

        promptWithAnswers[0]["input"] = str(video_port)
        promptWithAnswers[1]["input"] = str(port_index)

        result = self.utMenu.select(self.testSuite, "Disable VideoPort", promptWithAnswers)

    def terminate(self):
        """
        Enables the Video port.

        Args:
            None.

        Returns:
            None
        """
        result = self.utMenu.select(self.testSuite, "VideoPort Term")

    def getSupportedPorts(self):
        """
        Returns the supported Video ports on device.

        Args:
            None.

        Returns:
            returns the list of supported Video ports
        """
        portLists = []

        ports = self.deviceProfile.get("Ports")
        for i in range(1, len(ports)+1):
            entry = ports[i]
            portLists.append([dsVideoPortType(entry['Typeid']).name, entry['Index']])

        return portLists

    def getDeviceType(self):
        """
        Returns the supported Video ports on device.

        Args:
            None.

        Returns:
            returns the device type (0-Sink device, 1-Source device)
        """
        portLists = []

        type = self.deviceProfile.get("Type")
        if type == "sink":
            return 0
        elif type == "source":
            return 1


    def __del__(self):
        """
        De-Initializes the dsVideoPort helper function.

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

    platformProfile = dir_path + "/../../../profiles/source/Source_4K_VideoPort.yaml"
    # test the class assuming that it's optional
    test = dsVideoPortClass(platformProfile, shell)

    test.initialise()
    ports = test.getSupportedPorts()

    test.enablePort(ports[0][0], ports[0][1])
    test.disablePort(ports[0][0], ports[0][1])

    test.terminate()

    shell.close()
