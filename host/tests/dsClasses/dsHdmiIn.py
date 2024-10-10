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

class dsHdmiInPortType(Enum):
    dsHDMI_IN_PORT_0      = 0
    dsHDMI_IN_PORT_1      = auto()
    dsHDMI_IN_PORT_2      = auto()

class dsHdmiInClass():

    moduleName = "dsHdmiIn"
    menuConfig =  dir_path + "/dsHdmiIn_test_suite.yml"
    testSuite = "L3 dsHdmiIn"

    """
    Device Settings HdmiIn Class

    This module provides common extensions for device Settings HdmiIn Module.
    """
    def __init__(self, deviceProfilePath:str, session=None ):
        """
        Initializes the dsHdmiIn class function.
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

    def initialise(self, device_type:int=0, connectionCBFile:str="", signalchangeCBFile:str="", statusCBFile:str="",
                   videomodeCBFile:str="", allmCBFile:str="", avlatencyCBFile:str="", avicontentCBFile:str=""):
        """
        Initializes the device settings HdmiIn module.

        Args:
            device_type (int, optional): 0 - sink device, 1 - source device. Defaults to sink.

        Returns:
            None
        """
        promptWithAnswers = [
                {
                    "query_type": "direct",
                    "query": "Select Device Type[0: Sink, 1: Source]:",
                    "input": str(device_type)
                },
                {
                    "query_type": "direct",
                    "query": "Enter file name with path to log connection status callbacks:",
                    "input": connectionCBFile
                },
                {
                    "query_type": "direct",
                    "query": "Enter file name with path to log  signal change callbacks:",
                    "input": signalchangeCBFile
                },
                {
                    "query_type": "direct",
                    "query": "Enter file name with path to log status change callbacks:",
                    "input": statusCBFile
                },
                {
                    "query_type": "direct",
                    "query": "Enter file name with path to log video mode update callbacks:",
                    "input": videomodeCBFile
                },
                {
                    "query_type": "direct",
                    "query": "Enter file name with path to log allm change callbacks:",
                    "input": allmCBFile
                },
                {
                    "query_type": "direct",
                    "query": "Enter file name with path to log audio video latency change callbacks:",
                    "input": avlatencyCBFile
                },
                {
                    "query_type": "direct",
                    "query": "Enter file name with path to log avi content change callbacks:",
                    "input": avicontentCBFile
                }
        ]
        result = self.utMenu.select( self.testSuite, "Initialize dsHdmiIn", promptWithAnswers)

    def terminate(self):
        """
        Terminate the HdmiIn port.

        Args:
            None.

        Returns:
            None
        """
        result = self.utMenu.select(self.testSuite, "Terminate dsHdmiIn")

    def getports():
        """
        Gets the number of HdmiIn port on device.

        Args:
            None.
        Returns:
            bool.
        """
        ports = self.deviceProfile.get("Ports")
        if not ports:
            return false

        result = self.utMenu.select( self.testSuite, "Get Input Port")
        print(result)
        typeStatusPattern = re.findall(r'\d{1,3}',result)
        numports = int(''.join(typeStatusPattern))
        if numports == ports:
           return true
        else:
           return false

    def getportstatus():
        """
        Gets the port status.

        Args:
            None.
        Returns:
            bool.
        """
        result = self.utMenu.select( self.testSuite, "Get Status")
        typeStatusPattern = r"Result dsHdmiInGetStatus\(OUT:inputstatus:\[isPresented:\[(\w+)\], activeport:\[(dsHDMI_IN_PORT_\w+)\] \],dsError_t:\[(dsERR_\w+)\]\)"
        match = re.search(typeStatusPattern, result)
        if match:
            isPresented = match.group(1)
            activeport = match.group(2)

        if numports == ports:
           return true
        else:
           return false


    def selectPort(self, hdmiin_port:str, port_index:int=0, audmix:int=0, videoplane:int=0, topmost:int=1):
        """
        Selects specified port.

        Args:
            hdmiin_port (str): name of the hdiin port. Refer dsHdmiInPort enum
            port_index (int, optional): port index. Defaults to 0
            audmix (int, optional): audmix .
            videoplane(int, optional): videoplane.
            topmost(int, optional): topmost.
           
        Returns:
            None
        """
        promptWithAnswers = [
                {
                    "query_type": "list",
                    "query": "Select dsAudio Port:",
                    "input": hdmiin_port
                },
                {
                    "query_type": "direct",
                    "query": "Select dsAudio Port Index[0-10]:",
                    "input": str(port_index)
                },
                {
                    "query_type": "direct",
                    "query": "Select audiomix value Index[0-1]:",
                    "input": str(audmix)
                },
                {
                    "query_type": "direct",
                    "query": "Select videoplane value Index[0]:",
                    "input": str(videoplane)
                },
                {
                    "query_type": "direct",
                    "query": "Select videoplane value Index[1]:",
                    "input": str(topmost)
                }
        ]

        result = self.utMenu.select(self.testSuite, "Select Port", promptWithAnswers)

    def scalevdieo(self, hdmiin_port:str, xcord:int=0, ycord:int=0, width:int=0, height:int=0):
        """
        Scale video of specified port.

        Args:
            xcord (int, optional): xcoordiante. Defaults to 0
            ycord (int, optional): ycoordiante. Defaults to 0
            width (int, optional): width. Defaults to 0
            height(int, optional): height. Defaults to 0

        Returns:
            None
        """
        promptWithAnswers = [
                {
                    "query_type": "list",
                    "query": "Select dsAudio Port:",
                    "input": hdmiin_port
                },
                {
                    "query_type": "direct",
                    "query": "Select dsAudio Port Index[0-10]:",
                    "input": str(xcord)
                },
                {
                    "query_type": "direct",
                    "query": "Select audiomix value Index[0-1]:",
                    "input": str(ycord)
                },
                {
                    "query_type": "direct",
                    "query": "Select videoplane value Index[0]:",
                    "input": str(width)
                },
                {
                    "query_type": "direct",
                    "query": "Select videoplane value Index[1]:",
                    "input": str(height)
                }
        ]

        result = self.utMenu.select(self.testSuite, "Scale Video", promptWithAnswers)
  
    def getSupportedPorts(self):
        """
        Returns a list of supported audio ports on the device.

        Args:
            None

        Returns:
            list: A list of tuples containing the port name and index.
        """

        ports = self.deviceProfile.get("Ports")
        if not ports:
            return []  # Handle empty ports list

        supported_ports = []
        for entry in ports.values():
            supported_ports.append((dsHdmiInPortType(entry['Typeid']).name, entry['Index']))

        return supported_ports

    def zoommode(zoom_mode:int=0):
        """
        sets zoommode  on a particular HdmiIn port.

        Args:
            zoommode (int, optional): zoommode. Defaults to 0

        Returns:
            None.
        """
        promptWithAnswers = [
            {
                "query_type": "list",
                "query": "Selected Zoom Mode",
                "input": "dsVIDEO_ZOOM_NONE"
            }
        ]
        
        promptWithAnswers[0]["input"] = str(zoom_mode)
        
        result = self.utMenu.select(self.testSuite, "Zoom Mode", promptWithAnswers)

    def setedidversion(edidversion:int=0):
        """
        sets edid version  on a particular HdmiIn port.

        Args:
            edidversion (int, optional): edidversion. Defaults to 0             
 
        Returns:
            None.
        """
        promptWithAnswers = [
            {
                "query_type": "list",
                "query": "Selected EDID Version",
                "input": "HDMI_EDID_VER_14"
            }
        ]

        promptWithAnswers[0]["input"] = str(edidversion)

        result = self.utMenu.select(self.testSuite, "Set EdidVersion", promptWithAnswers)

    def getedidversion(port_index:int=0):
        """
        Gets edidversion.

        Args:
            None.
        Returns:
            string.
        """
        promptWithAnswers = [
            {
                "query_type": "direct",
                "query": "Get EDID Version",
                "input": "0"
            }
        ]
        
        promptWithAnswers[0]["input"] = str(port_index)

        result = self.utMenu.select( self.testSuite, "Get EdidVersion", promptWithAnswers)
        typeStatusPattern = r"Result dsGetEdidVersion IN:port:\[(\w+)\]:\[.*\] OUT:edidver:\[(HDMI_EDID_VER_\w+)\]:\[.*\],dsError_t:\[(dsERR_\w+)\]"
        match = re.search(typeStatusPattern, result)
        if match:
            edidversion = match.group(2)

        return edidversion

    def setedid2allm(port_index:int=0, allm_support:int=0):
        """
        sets edid2allm support  on a particular HdmiIn port.

        Args:
            allm_support (int, optional): allm_support. Defaults to 0

        Returns:
            None.
        """
        promptWithAnswers = [
            {
                "query_type": "direct",
                "query": "Selected EDID Version",
                "input": "dsHDMI_IN_PORT_0"
            },
            {
                "query_type": "list",
                "query": "Selected EDID Version",
                "input": "0"
            }

        ]

        promptWithAnswers[0]["input"] = str(port_index)
        promptWithAnswers[1]["input"] = str(allm_support)

        result = self.utMenu.select(self.testSuite, "Set Edid 2 Allm Support", promptWithAnswers)

    def getedid2allm(port_index:int=0):
        """
        Gets edid 2 allm support.

        Args:
            None.
        Returns:
            string.
        """
        promptWithAnswers = [
            {
                "query_type": "direct",
                "query": "Get EDID Version",
                "input": "0"
            }
        ]

        promptWithAnswers[0]["input"] = str(port_index)

        result = self.utMenu.select( self.testSuite, "Get Edid 2 Allm Support", promptWithAnswers)
        typeStatusPattern = r"Result dsGetEdid2AllmSupport IN:port:\[(\w+)\]:\[.*\] OUT:allmsupport:\[(\w+)\]:\[.*\],dsError_t:\[(dsERR_\w+)\]"
        match = re.search(typeStatusPattern, result)
        if match:
            edid2allm = match.group(2)

        return edid2allm

    def __del__(self):
        """
        De-Initializes the dsHdmiIn helper function.

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

    platformProfile = dir_path + "/../../../profiles/sink/Sink_HDMIIN.yaml"
    # test the class assuming that it's optional
    test = dsHdmiInClass(platformProfile, shell)

    test.initialise()
    ports = test.getSupportedPorts()

    test.selectport()
    test.getportstatus()

    test.terminate()

    shell.close()
