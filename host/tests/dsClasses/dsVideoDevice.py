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
                    "query_type": "list",
                    "query": " Select the Display Framerate :",
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
                    "query_type": "direct",
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
        De-Initializes the dsAudio helper function.

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

    platformProfile = dir_path + "/../../../profiles/source/Source_VideoDevice.yaml"
    # test the class assuming that it's optional
    test = dsVideoDeviceClass(platformProfile, shell)

    test.initialise()
    ports = test.getVideoDevice()

    test.terminate()

    shell.close()