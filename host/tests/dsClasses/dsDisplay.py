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

class dsAVIScanInformation(Enum):
    dsAVI_SCAN_TYPE_NO_DATA = 0
    dsAVI_SCAN_TYPE_OVERSCAN = 1
    dsAVI_SCAN_TYPE_UNDERSCAN = 2
    dsAVI_SCAN_TYPE_MAX = 3

class dsAviContentType(Enum):
    dsAVICONTENT_TYPE_GRAPHICS = 0
    dsAVICONTENT_TYPE_PHOTO = 1
    dsAVICONTENT_TYPE_CINEMA = 2
    dsAVICONTENT_TYPE_GAME = 3
    dsAVICONTENT_TYPE_NOT_SIGNALLED = 4
    dsAVICONTENT_TYPE_MAX = 5

class dsDisplayClass():

    """
    Device Settings Display Class
    This module provides common extensions for device Settings Display Module.
    """

    def __init__(self, moduleConfigProfileFile :str, session=None, testSuite:str="L3 dsDisplay", targetWorkspace="/tmp" , copyArtifacts:bool=True):
        """
        Initializes the dsDisplay class function.
        """

        self.moduleName = "dsDisplay"
        self.testConfigFile = os.path.join(dir_path, "dsDisplay_testConfig.yml")
        self.testSuite = testSuite

        # Load configurations for device profile and menu
        self.moduleConfigProfile = ConfigRead(moduleConfigProfileFile , self.moduleName)
        self.testConfig          = ConfigRead(self.testConfigFile, self.moduleName)
        self.testConfig.test.execute = os.path.join(targetWorkspace, self.testConfig.test.execute)
        self.testConfig.test.execute = self.testConfig.test.execute + f" -p {os.path.basename(moduleConfigProfileFile)}"
        self.utMenu              = UTSuiteNavigatorClass(self.testConfig, None, session)
        self.testSession         = session
        self.utils               = utBaseUtils()

        if copyArtifacts:
            # Copy bin files to the target
            for artifact in self.testConfig.test.artifacts:
                filesPath = os.path.join(dir_path, artifact)
                self.utils.rsync(self.testSession, filesPath, targetWorkspace)

            # Copy the profile file to the target
            self.utils.scpCopy(self.testSession, moduleConfigProfileFile, targetWorkspace)
        
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
    
    def extract_output_values(self, result: str, out_pattern: str = r'OUT:[\w_]+:\[([\w_]+)\]') -> list:
        """
        Extracts values from a given result string based on a specified pattern.

        This method uses a regular expression to find and extract relevant output
        values from the provided result string. It is particularly useful for
        parsing structured output from commands or logs.

        Args:
            result (str): The input string from which to extract values.
                        This string typically contains multiple lines of output.
            out_pattern (str, optional): The regex pattern to use for matching
                                        the desired output values. Defaults to
                                        a pattern that captures values in the
                                        format 'OUT:<identifier>:[<value>]'.

        Returns:
            list: A list of extracted values that match the specified pattern.

        Example:
            extracted_values = extract_output_values(result="OUT:Example:[Value1]\nOUT:Example:[Value2]")
        """

        # Find all matches in the result string using the provided pattern
        out_values = re.findall(out_pattern, result, re.MULTILINE)

        # Return the extracted values as a list
        return list(out_values)

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
        Initializes the device settings Display module.

        Args:
            None

        Returns:
                None
        """
        result = self.utMenu.select( self.testSuite, "Initialize dsDisplay")

    def selectDisplayPort(self, video_port: str, port_index: int=0):
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

        result = self.utMenu.select(self.testSuite, "Select Display Port", promptWithAnswers)

    def getEdid(self):
        """
        Gets the EDID information.

        Args:
            None.

        Returns:
            Edid informaton in Dict type
            {
                'productCode': '',
                'serialNumber': '',
                'manufactureYear': '',
                'manufactureWeek': '',
                'hdmiDeviceType': '',
                'isRepeater': '',
                'physicalAddressA': '',
                'physicalAddressB': '',
                'physicalAddressC': '',
                'physicalAddressD': '',
                'numOfSupportedResolution':'',
                'monitorName': ''
            }
        """
        result = self.utMenu.select(self.testSuite, "Get display EDID")

        if result == None:
            return None

        edidInfo = {}
        pattern = r"Result dsGetEDID\(dsDisplayEDID_t\((.*?)\)"
        matches = re.findall(pattern, result, re.DOTALL)

        for match in matches:
            fields = match.split(",")
            for field in fields:
                key_value_pattern = r"(\w+):\[(.*?)\]"
                cleaned_string = field.replace("\r", "").replace("\n", "")
                key_value_match = re.match(key_value_pattern, cleaned_string.strip())

                if key_value_match:
                    key = key_value_match.group(1)
                    value = key_value_match.group(2)
                    edidInfo[key] = value

        return edidInfo

    def getEdidBytes(self):
        """
        Gets the EDID bytes.

        Args:
            None.

        Returns:
            None
        """
        result = self.utMenu.select(self.testSuite, "Get display EDIDBytes")
        pattern = r'edidbyte\[\d+\]:\[(\w+)\]'
        edid_bytes = [int(match, 16) for match in re.findall(pattern, result)]

        return edid_bytes
    
    def setAllmMode(self, mode:str="Disable"):
        """
        Enables/Disables ALLM mode for HDMI output port connected to display.

        This method allows you to enables or disables the Auto Low Latency Mode (ALLM) 
        for HDMI output port connected to display, as per the HDMI 2.1 specification.


        Args:
            mode (str, optional) : ALLM mode, defaults to "Disable"

        Returns:
            None

        Example:
            setAllmMode(mode:str="Disable")
        """
        promptWithAnswers = [
            {
                "query_type": "list",
                "query": "Choose ALLM mode to be Enable/Disable:",
                "input": "Disable"
            }
        ]

        # Convert input arguments to strings and update the prompts
        promptWithAnswers[0]["input"] = str(mode)


        result = self.utMenu.select(self.testSuite, "Set Allm Enabled", promptWithAnswers)

    def getAllmMode(self):
        """
        Checks whether ALLM mode of HDMI output port connected to display is enabled or not.

        This method allows you to check whether the Auto Low Latency Mode (ALLM) 
        for a HDMI output port connected to display is enabled or disabled, as 
        per the HDMI 2.1 specification.

        Returns:
            list: A list containing the information on status of the ALLM mode.

        Example:
            getAllmMode(self):
        """
        result = self.utMenu.select(self.testSuite, "Get Allm Enabled")

        # Extract and return the output values from the result
        output_list = self.extract_output_values(result)

        return bool(output_list)


    def getAspectRatio(self):
        """
        Gets the display aspect ratio.

        Args:
            None.

        Returns:
            None
        """
        result = self.utMenu.select(self.testSuite, "Get display AspectRatio")
        if result == None:
            return None
        aspectRatioPattern = r"Result dsGetDisplayAspectRatio\(handle:\[.*\], dsVideoAspectRatio_t:\[(.*?)\], dsError_t=\[.*?\]\)"
        aspectRatio = self.searchPattern(result, aspectRatioPattern)
        return aspectRatio

    def setAVIContentType(self, contentType: str):
        """
        Sets the AVI Content Type.

        Args:
            contentType (str): One of [
            "dsAVICONTENT_TYPE_GRAPHICS", 
            "dsAVICONTENT_TYPE_PHOTO", 
            "dsAVICONTENT_TYPE_CINEMA", 
            "dsAVICONTENT_TYPE_GAME", 
            "dsAVICONTENT_TYPE_NOT_SIGNALLED"
        ]
        """
        promptWithAnswers = [
                {
                    "query_type": "list",
                    "query": "Select AVI Content Type to set:",
                    "input": str(contentType)
                }
        ]

        result = self.utMenu.select(self.testSuite, "Set display AVI content type", promptWithAnswers)
        return result

    def getAVIContentType(self):
        """
        Gets the AVI Content Type from the display.

        Returns:
                str or None: The AVI Content Type string (e.g., 'dsAVICONTENT_TYPE_PHOTO') or None if not found.
        """
        result = self.utMenu.select(self.testSuite, "Get AVI Content Type")
        if result is None:
           return None

        avicontentPattern = r"Result dsGetAVIContentType\(handle:\[.*?\], dsAviContentType_t:\[(.*?)\], dsError_t:\[.*?\]\)"
        contentType = self.searchPattern(result, avicontentPattern)
        return contentType

    def setAVIScanInformation(self, scanInfo: str):
        """
        Sets the AVI Scan Information on the selected display port.
        """

        promptWithAnswers = [
            {
                "query_type": "list",
                "query": "Select Scan Information:",
                "input": str(scanInfo)
           }
        ]

        result = self.utMenu.select(self.testSuite, "Set display AVI scan information", promptWithAnswers)
        return result

    def getAVIScanInformation(self):
        """
        Gets the AVI Scan Information from the display port.

        Returns:
            str or None: The scan information value like "dsAVI_SCAN_TYPE_UNDERSCAN" or None if not matched.
        """
        result = self.utMenu.select(self.testSuite, "Get AVI Scan Information")
        if result is None:
            return None

        pattern = r"Result dsGetAVIScanInformation\(handle:\[.*?\], dsAVIScanInformation_t:\[(.*?)\], dsError_t:\[.*?\]\)"
        scanInfo = self.searchPattern(result, pattern)
        return scanInfo

    def getDisplayEventFromCallback(self):
        """
        Retrieves the display event callback status from the device.
        This function reads the output from the device session to detect the
        display event status. The callback message contains the event type,
        which is parsed and returned as a string.
        Args:
            None
        Returns:
            str: List of display events.
            empty list: If no matching event status is found.
        """

        result = self.testSession.read_until("Display EventCallback(IN:handle:")
        pattern = r"Display EventCallback\(IN:.*?dsDisplayEvent_t:\[([^\]]+)\]"
        events = re.findall(pattern, result)
        return events

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

        ports = self.moduleConfigProfile.get("Video_Ports")
        indices = self.moduleConfigProfile.get("VideoPort_Index")

        for i, port in enumerate(ports):
            video_port_name = dsVideoPortType(port).name
            port_index = indices[i]
            portLists.append((video_port_name, port_index))

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

    edidInfo = test.getEdid(ports[0][0], ports[0][1])
    print(edidInfo)

    edidBytes = test.getEdidBytes(ports[0][0], ports[0][1])
    print(edidBytes)

    aspectRatio = test.getAspectRatio(ports[0][0], ports[0][1])
    print(aspectRatio)

    test.terminate()

    shell.close()


