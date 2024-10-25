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
sys.path.append(os.path.join(dir_path, "../"))

from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.plugins.ut_raft.utSuiteNavigator import UTSuiteNavigatorClass
from raft.framework.plugins.ut_raft.interactiveShell import InteractiveShell

class dsVideoZoomMode(Enum):		
    dsVIDEO_ZOOM_NONE = 0          
    dsVIDEO_ZOOM_FULL = 1              # Full screen 
    dsVIDEO_ZOOM_LB_16_9 = 2           # 16:9 Letterbox 
    dsVIDEO_ZOOM_LB_14_9 = 3           # 14:9 Letterbox 
    dsVIDEO_ZOOM_CCO = 4               # Center Cut-out 
    dsVIDEO_ZOOM_PAN_SCAN = 5          # Pan & Scan 
    dsVIDEO_ZOOM_LB_2_21_1_ON_4_3 = 6  # 2.21:1 Letterbox on 4:3 
    dsVIDEO_ZOOM_LB_2_21_1_ON_16_9 = 7 # 2.21:1 Letterbox on 16:9 
    dsVIDEO_ZOOM_PLATFORM = 8          # Control over the decoder format conversions is managed by the platform
    dsVIDEO_ZOOM_16_9_ZOOM = 9         # 16:9 Zoom 
    dsVIDEO_ZOOM_PILLARBOX_4_3 = 10     # Pillarbox 4:3
    dsVIDEO_ZOOM_WIDE_4_3 = 11          # Wide 4:3 
    dsVIDEO_ZOOM_MAX = 12                # Out of range 

class dsVideoDeviceClass():

    moduleName = "dsVideoDevice"
    menuConfig =  os.path.join(dir_path, "dsVideoDevice_test_suite.yml")
    testSuite = "L3 dsVideoDevice"

    """
    Device Settings Videodevice Class

    This module provides common extensions for device Settings Videodevice Module.
    """
    def __init__(self, deviceProfilePath:str, session=None ):
        """
        Initializes the dsVideodevice class function.
        """
        self.deviceProfile = ConfigRead( deviceProfilePath, self.moduleName)
        self.suitConfig    = ConfigRead(self.menuConfig, self.moduleName)
        self.utMenu        = UTSuiteNavigatorClass(self.menuConfig, self.moduleName, session)
        self.menuSession   = session
        self.utMenu.start()

    def searchPattern(self, haystack, pattern):
        match = re.search(pattern, haystack)
        if match:
            return match.group(1)
        return None

    def initialise(self, device_type:int=0):
        """
        Initializes the device settings VideoDevice module.

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
                }
        ]
        result = self.utMenu.select( self.testSuite, "VideoDevice_Init",promptWithAnswers)

    def terminate(self):
        """
        Terminate the VideoDevice.

        Args:
            None.

        Returns:
            None
        """
        result = self.utMenu.select(self.testSuite, "VideoDevice_Term")

    def setZoomMode(self, device:int=0, mode:str=0):
        """
        sets the zoom mode.

        Args:
            None

        Returns:
            None
        """
        promptWithAnswers = [
                {
                    "query_type": "direct",
                    "query": "Select the Video Device:",
                    "input": str(device)
                },
                {
                    "query_type": "list",
                    "query": " Select the Zoom mode:",
                    "input": mode
                }
        ]

        result = self.utMenu.select(self.testSuite, "SetZoomMode", promptWithAnswers)

    def setDisplayFramerate(self, device:int=0, framerate:str=0):
        """
        Sets display framerate.

        Args:
           None

        Returns:
            None
        """
        promptWithAnswers = [
                {
                    "query_type": "direct",
                    "query": "Select the Video Device:",
                    "input": str(device)
                },
                {
                    "query_type": "direct",
                    "query": " Provided Display Framerate :",
                    "input": str(framerate)
                }
        ]

        result = self.utMenu.select(self.testSuite, "SetDisplayFramerate", promptWithAnswers)

    def setFRFMode(self, device:int=0, mode:str=0):
        """
        Sets display FRF mode.

        Args:
            None

        Returns:
            None
        """
        promptWithAnswers = [
                {
                    "query_type": "device",
                    "query": "Select the Video Device:",
                    "input": str(device)
                },
                {
                    "query_type": "list",
                    "query": " Select the Display FRF Mode :",
                    "input": str(mode)
                }
        ]

        result = self.utMenu.select(self.testSuite, "SetFRFMode", promptWithAnswers)

    def getVideoCodecInfo(self,device:int=0,codec:str=0):
        """
        Gets the Video codec information.

        Args:
            None

        Returns:
            None
        """
        promptWithAnswers = [
                {
                    "query_type": "direct",
                    "query": "Select the Video Device:",
                    "input": str(device)
                },
                {
                    "query_type": "list",
                    "query": " Select the Codec for Info :",
                    "input": str(codec)
                }
        ]

        result = self.utMenu.select(self.testSuite, "GetVideoCodecInfo", promptWithAnswers)

        
    def getSupportedVideoCodingFormat(self,device:int=0):
        """
        Gets the Supported VideoCoding Format.

        Args:
            None

        Returns:
            None
        """
        promptWithAnswers = [
                {
                    "query_type": "direct",
                    "query": "Select the Video Device:",
                    "input": str(device)
                }
        ]

        result = self.utMenu.select(self.testSuite, "GetSupportedVideoCodingFormat", promptWithAnswers)

    def getHDRCapabilities(self,device:int=0):
        """
        Gets the HDR capabilities.

        Args:
            None.

        Returns:
            None
        """
        promptWithAnswers = [
                {
                    "query_type": "list",
                    "query": "Select the Video Device:",
                    "input": str(device)
                }
        ]

        result = self.utMenu.select(self.testSuite, "GetHDRCapabilities", promptWithAnswers)

    def getFRFMode(self, device:int=0):
        """
        Gets the FRF mode.

        Args:
            None.

        Returns:
            None
        """
        promptWithAnswers = [
                {
                    "query_type": "direct",
                    "query": "Select the Video Device:",
                    "input": str(device)
                }
        ]

        result = self.utMenu.select(self.testSuite, "dsGetFRFMode", promptWithAnswers)


    def getCurrentDisplayframerate(self,device:int=0):
        """
        Gets the current display framerate.

        Args:
            None.

        Returns:
            None
        """
        promptWithAnswers = [
                {
                    "query_type": "direct",
                    "query": "Select the Video Device:",
                    "input": str(device)
                }
        ]

        result = self.utMenu.select(self.testSuite, "GetCurrentDisplayframerate", promptWithAnswers)

    def getZoomMode(self):
        """
        Gets the Zoom mode.

        Args:
            None.

        Returns:
            None
        """
        promptWithAnswers = [
                {
                    "query_type": "direct",
                    "query": "Select the Video Device:",
                    "input": str(0)
                }
        ]

        result = self.utMenu.select(self.testSuite, "GetZoomMode", promptWithAnswers)


    def getVideoDevice(self):
        """
        Returns a list of video devices.

        Args:
            None

        Returns:
            list: A list of tuples containing the video devices.
        """

        devices = self.deviceProfile.get("NumVideoDevices")
        if not devices:
            return []  # Handle empty ports list

        return devices

    def getDeviceType(self):
        """
        Returns the device type.

        Args:
            None.

        Returns:
            returns the device type (0-Sink device, 1-Source device)
        """

        type = self.deviceProfile.get("Type")
        if type == "sink":
            return 0
        elif type == "source":
            return 1
        else:
            return None

    
    def __del__(self):
        """
        De-Initializes the dsVideo helper function.

        Args:
            None.

        Returns:
            None
        """
        self.utMenu.stop()
    
    def getFrameratePrechangeCallbackStatus(self):
        """
        Retrieves the display Framerate Prechange status using a callback.

        Args:
            None.
        Returns:
            tuple:
                - tSecond: Time in seconds as a integer.
            None: If no matching signal status is found.
        """
        result = self.testSession.read_until("FrameratePreChange callback tSecond: ")
        framerateprechange = r"FrameratePreChange callback tSecond: (\d+)"
        match = re.search(framerateprechange, result)
        print(f'PRECB_MATCH = {match}')

        if match:
            tSecond = match.group(1)
            return tSecond
        
        return None

    def getFrameratePostchangeCallbackStatus(self):
        """
        Retrieves the display Framerate Postchange status using a callback.

        Args:
            None.
        Returns:
            tuple:
                - tSecond: Time in seconds as a integer.
            None: If no matching signal status is found.
        """
        result = self.testSession.read_until("FrameratePostChange callback tSecond: ")
        framerateprechange = r"FrameratePostChange callback tSecond: (\d+)"
        match = re.search(framerateprechange, result)
        print(f'POSTCB_MATCH = {match}')

        if match:
            tSecond = match.group(1)
            return tSecond
        
        return None
    
    def read_Callbacks(self, input_str: str) -> str:
        """
        Reads data from the menu session until a specified input string is encountered.

        This method is useful for capturing output or response data from the menu session
        until a predefined string is reached, which can be important for synchronizing
        interactions or processing command outputs.

        Args:
            input_str (str): The string that indicates where to stop reading from the session.

        Returns:
            str: The data read from the session up to the specified input string.

        Example:
            output = read_Callbacks("EndOfResponse")
        """
        result = self.menuSession.read_until(input_str)
        return result
    
    def getSupportedFrameRates(self):
        """
        Returns the supported Framerate Formats on device.

        Args:
            None.

        Returns:
            returns the supported Framerate Formats
        """
        supported_Framerates = []

        Device = self.deviceProfile.get("Device")
        for i in range(1, len(Device)+1):
            entry = Device[i]
            SupportedDisplayFramerate = entry['SupportedDisplayFramerate']
            for j in range(0, len(SupportedDisplayFramerate)):
                supported_Framerates.append(SupportedDisplayFramerate[j])

        print(f"Supported FR's {supported_Framerates}")

        return supported_Framerates	

    def getZoomModes(self):
        """
        Returns the supported Zoom modes on device.

        Args:
            None.

        Returns:
            returns the supported Zoom modes
        """
        supported_ZoomModes = []

        Device = self.deviceProfile.get("Device")
        for i in range(1, len(Device)+1):
            entry = Device[i]
            SupportedDFCs = entry['SupportedDFCs']
            for j in range(0, len(SupportedDFCs)):
                zoomModes_enum = dsVideoZoomMode(SupportedDFCs[j]).name
                supported_ZoomModes.append(zoomModes_enum)

        return supported_ZoomModes


# Test and example usage code
if __name__ == '__main__':

    shell = InteractiveShell()
    shell.open()

    platformProfile = dir_path + "/../../../profiles/sink/Sink_4K_VideoDevice.yaml"
    # test the class assuming that it's optional
    test = dsVideoDeviceClass(platformProfile, shell)

    test.initialise()
    ports = test.getVideoDevice()

    test.terminate()

    shell.close()