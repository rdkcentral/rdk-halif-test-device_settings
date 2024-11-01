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

class dsVideoCodec(Enum):
    dsVIDEO_CODEC_MPEGHPART2  = (0x01 << 0) 
    dsVIDEO_CODEC_MPEG4PART10 = (0x01 << 1)  
    dsVIDEO_CODEC_MPEG2       = (0x01 << 2)  
    dsVIDEO_CODEC_MAX         = (0x01 << 3) 

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
        self.testSession   = session
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
        frameRatePattern = r"Result dsSetDisplayframerate\(IN:Handle:\[.*\],IN:framerate:\[(3840x\w+)\]\)"
        frameRate = self.searchPattern(result, frameRatePattern)

        return frameRate

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
                    "input": mode
                }
        ]

        result = self.utMenu.select(self.testSuite, "SetFRFMode", promptWithAnswers)

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

        if match:
            tSecond = match.group(1)
            return tSecond
        
        return None


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
        codecInfoPattern = r"Result dsGetVideoCodecInfo\(IN:Handle:\[.*\],IN:Codec\[(\w+)\], OUT:Codec number of Entires\[(\w+)\]"
        codecInfo = re.search(codecInfoPattern,result)
        if codecInfo:
            count = codecInfo.group(2)


        codecpattern = r"OUT:CodecProfile\[(dsVIDEO_CODEC_\w+)\]"
        pattern = re.search(codecpattern,result)

        codecValues = ''
        if pattern:
            codecValues = pattern.group(0)
        
        return  int(count), codecValues

        
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
        supportedCodecPattern = r"Result dsGetSupportedVideoCodingFormats\(IN:Handle[.*\],OUT:supportedFormat[.*\]\)"
        supportedCodec = self.searchPattern(result, supportedCodecPattern)

        return supportedCodec


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
        frfModepattern = r"Result dsGetFRFMode\(IN:Handle\[.*\],OUT:frfMode\[(\w+)\]\)"
        match = re.search(frfModepattern, result)

        if match:
            mode = match.group(1)
            return mode
        
        return None



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
        frameRatePattern = r"Result dsGetCurrentDisplayframerate\(IN:Handle\[.*\],OUT:currentFrameRate\[(3840x\w+)\]\)"
        frameRate = self.searchPattern(result, frameRatePattern)

        return frameRate

    def getZoomMode(self,device:int=0):
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
                    "input": str(device)
                }
        ]

        result = self.utMenu.select(self.testSuite, "GetZoomMode", promptWithAnswers)
        zoomModePattern = r"Result dsGetDFC\(\(IN:Handle\[.*\],OUT:CurrentZoomMode\[(dsVIDEO_ZOOM_\w+)\]\)"
        zoomMode = self.searchPattern(result, zoomModePattern)

        return zoomMode



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

        return supported_Framerates	

    def getsupportedCodingFormats(self):
        """
        Returns the supported Framerate Formats on device.

        Args:
            None.

        Returns:
            returns the supported Framerate Formats
        """
        supported_CodingFormats = []

        Device = self.deviceProfile.get("Device")
        for i in range(1, len(Device)+1):
            entry = Device[i]
            SupportedVideoCodingFormats = entry['SupportedVideoCodingFormats']
            
            codec_list = list(dsVideoCodec)
            
            for i, codec in enumerate(codec_list, start=1):
                if SupportedVideoCodingFormats & codec.value:
                    supported_CodingFormats.append(codec.name)

        return supported_CodingFormats	
    
    
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