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

class dsDisplayEvent(Enum):
    dsDISPLAY_EVENT_CONNECTED = 0
    dsDISPLAY_EVENT_DISCONNECTED = auto()
    dsDISPLAY_RXSENSE_ON = auto()
    dsDISPLAY_RXSENSE_OFF = auto()
    dsDISPLAY_HDCPPROTOCOL_CHANGE = auto()
    dsDISPLAY_EVENT_MAX = auto()

class dsVideoAspectRatio(Enum):
    dsVIDEO_ASPECT_RATIO_4x3 = auto()
    dsVIDEO_ASPECT_RATIO_16x9 = auto()
    dsVIDEO_ASPECT_RATIO_MAX = auto()


class dsDisplayClass():

    """
    Device Settings Display Class
    This module provides common extensions for device Settings Display Module.
    """
    moduleName = "dsDisplay"
    menuConfig = dir_path+ "/dsDisplay_test_suite.yml"
    testSuite = "L3 dsDisplay"
    validationConfig = dir_path + "/../L3_TestCases/dsDisplay/dsDisplay_test_validation.yml"

    def __init__(self, deviceProfilePath :str, session=None, targetWorkspace="/tmp" ):
        """
        Initializes the dsDisplay class function.
        """

        # Load configurations for device profile and menu
        self.deviceProfile = ConfigRead( deviceProfilePath , self.moduleName)
        self.validationProfile = ConfigRead(self.validationConfig,self.moduleName)
        self.utMenu        = UTSuiteNavigatorClass(self.menuConfig, self.moduleName, session)
        self.testSession   = session

         # Start the user interface menu
        self.utMenu.start()

    def searchPattern(self, haystack, pattern):
        """
        Searches for the first occurrence of a specified pattern in the provided string.

        Args:
            haystack (str): The string to be searched.
            pattern (str): The regular expression pattern to search for.

        Returns:
            str: The first capturing group of the match if found; otherwise, None.

        Notes:
            - The pattern should contain at least one capturing group (parentheses).
            - If no match is found, None is returned.
        """
        match = re.search(pattern, haystack)
        if match:
            return match.group(1)
        return None

    def initialise(self):
        """
        Initializes the device settings Display module.

        Args:
            None

        Returns:
                None
        """
        result = self.utMenu.select( self.testSuite, "Initialize dsDisplay")

    def getDisplayHandle(self, video_port: str, port_index: int=0):
        """
        Returns the handle of the display port.

        Args:
            video_port (str): name of the video port. Refer dsVideoPortType enum
            port_index (int): port index

        Returns:
            int: The handle of the display port.
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

        result = self.utMenu.select(self.testSuite, "Get display handle", promptWithAnswers)

    def getEdid(self):
        """
        Gets the EDID information.

        Args:
            None.

        Returns:
            None
        """
        result = self.utMenu.select(self.testSuite, "Get display EDID")
        # Define the pattern to extract EDID information
        edidPattern = r"Result dsGetEDID\(dsDisplayEDID_t\(OUT:monitorName:\[(\w+)\], dsError_t=\[.*\]\)"
        monitorName = self.searchPattern(result, edidPattern)
        return monitorName

    def getEdidBytes(self):
        """
        Gets the EDID bytes.

        Args:
            None.

        Returns:
            None
        """
        edid_list = self.deviceProfile.get("edidbytes")
        result = self.utMenu.select(self.testSuite, "Get display EDIDBytes")
        pattern = r'edidbyte\[(8|9)\]:\[(\w{2})\]'
        matches = re.findall(pattern, result)
        if matches:
            edid_values = {int(index): value for index, value in matches}
        for key in edid_values:
            if int(edid_values.get(key)) in edid_list:
                if(key == 9):
                    return True

        return None

    def getAspectRatio(self):
        """
        Gets the display aspect ratio.

        Args:
            None.

        Returns:
            None
        """
        result = self.utMenu.select(self.testSuite, "Get display AspectRatio")
        aspectRatioPattern = r"Result dsGetDisplayAspectRatio\(handle:\[.*\], dsVideoAspectRatio_t:\[(.*?)\], dsError_t=\[.*?\]\)"
        aspectRatio = self.searchPattern(result, aspectRatioPattern)
        return aspectRatio

    def getConnectionCallbackStatus(self):
        """
        Retrieves the display event callback status from the device.
        This function reads the output from the device session to detect the
        display event status. The callback message contains the event type,
        which is parsed and returned as a string.
        Args:
            None
        Returns:
            str: The display event type (e.g., 'dsVIDEO_EVENT_CONNECTED').
            None: If no matching event status is found.
        """

        result = self.testSession.read_until("Display EventCallback(IN:handle:")
        callpattern = r"Display EventCallback\(IN:handle:\[.*\], dsDisplayEvent_t:\[(\w+)\]"
        status = self.searchPattern(result, callpattern)
        return status

    def terminate(self):
        """
        Terminates the display.

        Args:
            None.

        Returns:
            None
        """
        result = self.utMenu.select(self.testSuite, "Terminate dsDisplay")


    def getSupportedPorts(self):
        """
        Returns the supported Video ports on the device.
        Args:
            None.

        Returns:
            list: A list of tuples containing (video_port_name, index).
        """
        portLists= []

        ports = self.deviceProfile.get("Video_Ports")
        for entry in ports:

            video_port_name = dsVideoPortType(entry).name
            port_index =  0# Get the index
            portLists.append((video_port_name, port_index))

        return portLists

    def getDisplayInfoFromConfig(self):
        monitorNames = []
        displays = self.validationProfile.get("Displays")
        for entry in displays:
            monitorNames.append(displays[entry].get("Name"))
        return monitorNames

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


