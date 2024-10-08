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
class dsVideoPorthdcp_version(Enum):
    dsHDCP_VERSION_1X            = 0
    dsHDCP_VERSION_2X            = auto()
    dsHDCP_VERSION_MAX           = auto()

class dsHDRStandard(Enum):
    dsHDRSTANDARD_NONE = 0x0               # When No video format is decoded
    dsHDRSTANDARD_HDR10 = 0x01             # Video Format HDR
    dsHDRSTANDARD_HLG = 0x02               # Video Format HLG
    dsHDRSTANDARD_DolbyVision = 0x04       # Video Format Dolby Vision
    dsHDRSTANDARD_TechnicolorPrime = 0x08  # Video Format Technicolor Prime
    dsHDRSTANDARD_HDR10PLUS = 0x10         # Video Format HDRPlus
    dsHDRSTANDARD_SDR = 0x20               # Video Format SDR
    dsHDRSTANDARD_Invalid = 0x80           # When invalid value observed

class dsDisplayColorDepth(Enum):
    dsDISPLAY_COLORDEPTH_UNKNOWN = 0x0  # Unknown color depth
    dsDISPLAY_COLORDEPTH_8BIT = 0x01    # 8-bit color depth
    dsDISPLAY_COLORDEPTH_10BIT = 0x02   # 10-bit color depth
    dsDISPLAY_COLORDEPTH_12BIT = 0x04   # 12-bit color depth
    dsDISPLAY_COLORDEPTH_AUTO = 0x08    # Automatic color depth

class dsVideoResolution(Enum):
    dsVIDEO_PIXELRES_720x480 = 0      # 720x480 Resolution
    dsVIDEO_PIXELRES_720x576 = 1      # 720x576 Resolution
    dsVIDEO_PIXELRES_1280x720 = 2     # 1280x720 Resolution
    dsVIDEO_PIXELRES_1366x768 = 3     # 1366x768 Resolution
    dsVIDEO_PIXELRES_1920x1080 = 4    # 1920x1080 Resolution
    dsVIDEO_PIXELRES_3840x2160 = 5    # 3840x2160 Resolution
    dsVIDEO_PIXELRES_4096x2160 = 6    # 4096x2160 Resolution
    dsVIDEO_PIXELRES_MAX = 7          # Out of range

class dsVideoAspectRatio(Enum):
    dsVIDEO_ASPECT_RATIO_4x3 = 0     # 4:3 aspect ratio
    dsVIDEO_ASPECT_RATIO_16x9 = 1    # 16:9 aspect ratio
    dsVIDEO_ASPECT_RATIO_MAX = 2     # Out of range

class dsVideoFrameRate(Enum):
    dsVIDEO_FRAMERATE_UNKNOWN = 0         # Unknown frame rate
    dsVIDEO_FRAMERATE_24 = 1              # Played at 24 frames per second
    dsVIDEO_FRAMERATE_25 = 2              # Played at 25 frames per second
    dsVIDEO_FRAMERATE_30 = 3              # Played at 30 frames per second
    dsVIDEO_FRAMERATE_60 = 4              # Played at 60 frames per second
    dsVIDEO_FRAMERATE_23dot98 = 5         # Played at 23.98 frames per second
    dsVIDEO_FRAMERATE_29dot97 = 6         # Played at 29.97 frames per second
    dsVIDEO_FRAMERATE_50 = 7              # Played at 50 frames per second
    dsVIDEO_FRAMERATE_59dot94 = 8         # Played at 59.94 frames per second
    dsVIDEO_FRAMERATE_MAX = 9             # Out of range

class dsVideoStereoScopicMode(Enum):
    dsVIDEO_SSMODE_UNKNOWN = 0           # Unknown mode
    dsVIDEO_SSMODE_2D = 1                # 2D mode
    dsVIDEO_SSMODE_3D_SIDE_BY_SIDE = 2   # 3D side by side (L/R) stereo mode
    dsVIDEO_SSMODE_3D_TOP_AND_BOTTOM = 3 # 3D top & bottom stereo mode
    dsVIDEO_SSMODE_MAX = 4               # Out of range

class dsVideoScanModeMode(Enum):
    dsVIDEO_SCANMODE_INTERLACED = 0
    dsVIDEO_SCANMODE_PROGRESSIVE  = 1

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
        self.menuSession   = session
        self.utMenu.start()

    def extract_output_values(self,result: str,out_pattern:str=r'OUT:[\w_]+:\[([\w_]+)\]'):

        # Find all matches in the result string
        out_values = re.findall(out_pattern, result, re.MULTILINE)
        # Store the extracted values in a list
        output_list = list(out_values)
        return output_list

    def read_Callbacks(self,input_str: str):

        result = self.menuSession.read_until(input_str)
        return result

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
        Enables the specified Video port.

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
        Disable the specified Video port.

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

    def select_HdmiPreference(self,video_port:int, port_index:int=0,hdcp_version:int=0):
        """
            Sets the preferred HDMI Protocol of the specified video port.

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
            },
            {
                "query_type": "list",
                "query": "Supported HDCP Versions",
                "input": "dsHDCP_VERSION_1X"
            }
        ]

        promptWithAnswers[0]["input"] = str(video_port)
        promptWithAnswers[1]["input"] = str(port_index)
        promptWithAnswers[2]["input"] = str(hdcp_version)

        result = self.utMenu.select(self.testSuite, "Set HdmiPreference", promptWithAnswers)

    def enable_HDCP(self,video_port:int, port_index:int=0):
        """
            Enable the HDCP for the specified Video port.

            Args:
                video_port (str): name of the video port. Refer dsVideoPortType enum
                port_index (str): Index of the video device

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


        result = self.utMenu.select(self.testSuite, "Enable HDCP", promptWithAnswers)

    def disable_HDCP(self,video_port:int, port_index:int=0):
        """
            Disable the HDCP for the specified Video port.

            Args:
                video_port (str): name of the video port. Refer dsVideoPortType enum
                port_index (str): Index of the video device

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


        result = self.utMenu.select(self.testSuite, "Disable HDCP", promptWithAnswers)

    def select_Resolution(self,video_port:int, port_index:int=0, resolution: dict = None ):
        """
             sets the resolution of the specified Video port.

            Args: #todo
                video_port (str) : name of the video port. Refer dsVideoPortType enum
                port_index (str) : Index of the video device
                video_resolution :

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
            }]
        """
        promptWithAnswers.append(
            {
                "query_type": "list",
                "query": "Select Resolution",
                "input": "dsVIDEO_PIXELRES_1920x1080"
            },
            {
                "query_type": "list",
                "query": "Select Aspect Ratio",
                "input": "dsVIDEO_ASPECT_RATIO_16x9"
            },
            {
                "query_type": "list",
                "query": "Select Stereo ScopicMode",
                "input": "dsVIDEO_SSMODE_2D"
            },
            {
                "query_type": "list",
                "query": "Select Frame Rates",
                "input": "dsVIDEO_FRAMERATE_24"
            },
            {
                "query_type": "list",
                "query": "Select Scan modes",
                "input": "dsVIDEO_SCANMODE_INTERLACED"
            }
        )
        """
        promptWithAnswers[0]["input"] = str(video_port)
        promptWithAnswers[1]["input"] = str(port_index)

        # Check if a valid resolution dictionary is provided
        if resolution:
            # Add resolution-related prompts using the provided resolution details
            promptWithAnswers.extend([
                {
                "query_type": "list",
                "query": "Supported Resolution",
                "input": resolution.get("pixelResolution", "dsVIDEO_PIXELRES_1920x1080")  # Fallback if missing
                },
                {
                    "query_type": "list",
                    "query": "Supported Aspect Ratio",
                    "input": resolution.get("aspectRatio", "dsVIDEO_ASPECT_RATIO_16x9")  # Fallback if missing
                },
                {
                    "query_type": "list",
                    "query": "Supported Stereo ScopicMode",
                    "input": resolution.get("stereoScopicMode", "dsVIDEO_SSMODE_2D")  # Fallback if missing
                },
                {
                    "query_type": "list",
                    "query": "Supported Frame Rates",
                    "input": resolution.get("frameRate", "dsVIDEO_FRAMERATE_24")  # Fallback if missing
                },
                {
                    "query_type": "list",
                    "query": "Supported Scan modes",
                    "input": resolution.get("interlaced", "dsVIDEO_SCANMODE_INTERLACED")  # Fallback if missing
                }
            ])
        else:
            # If no resolution is provided, use defaults or provide a prompt
            print("No resolution provided, using defaults.")

        result = self.utMenu.select(self.testSuite, "Set Resolution", promptWithAnswers)

    def select_HDRModes(self,video_port:int, port_index:int=0,hdr_mode:int=0):
        """
            Sets/reset the force HDR mode for the specified video port.

            Args:
                video_port (str): name of the video port. Refer dsVideoPortType enum
                port_index (str): Index of the video device

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
            },
            {
                "query_type": "list",
                "query": "Select HDR modes",
                "input": "dsHDRSTANDARD_SDR"
            }
        ]

        promptWithAnswers[0]["input"] = str(video_port)
        promptWithAnswers[1]["input"] = str(port_index)
        promptWithAnswers[2]["input"] = str(hdr_mode)

        result = self.utMenu.select(self.testSuite, "Set ForceHDRMode", promptWithAnswers)

    def resetOutputToSDR(self,video_port:int, port_index:int=0):
        """
            resets the video output to SDR.

            Args:
                video_port (str): name of the video port. Refer dsVideoPortType enum
                port_index (str): Index of the video device

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


        result = self.utMenu.select(self.testSuite, "ResetOutputToSDR", promptWithAnswers)

    def select_PreferredColorDepth(self,video_port:int, port_index:int=0,color_depth:int=0):
        """
            set the preferred color depth for the specified Video port..

            Args:
                video_port (str): name of the video port. Refer dsVideoPortType enum
                port_index (str): Index of the video device

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
            },
            {
                "query_type": "list",
                "query": "Select Color depth to set",
                "input": "dsDISPLAY_COLORDEPTH_8BIT"
            }
        ]

        promptWithAnswers[0]["input"] = str(video_port)
        promptWithAnswers[1]["input"] = str(port_index)
        promptWithAnswers[2]["input"] = str(color_depth)

        result = self.utMenu.select(self.testSuite, "Set PreferredColorDepth", promptWithAnswers)

    def select_BackgroundColor(self,video_port:int, port_index:int=0,background_color:int=0):
        """
             sets the background color of the specified video port

            Args:
                video_port (str): name of the video port. Refer dsVideoPortType enum
                port_index (str): Index of the video device

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
            },
            {
                "query_type": "list",
                "query": "Supported Background Color",
                "input": "dsVIDEO_BGCOLOR_BLUE"
            }
        ]

        promptWithAnswers[0]["input"] = str(video_port)
        promptWithAnswers[1]["input"] = str(port_index)
        promptWithAnswers[2]["input"] = str(background_color)

        result = self.utMenu.select(self.testSuite, "Set BackgroundColor", promptWithAnswers)

    def getCurrentOutputSettings(self,video_port:int, port_index:int=0):
        """
            Gets current color space setting, color depth, matrix coefficients, video Electro-Optical Transfer Function (EOT)
            and  quantization range in one call of the specified video port

            Args:
                video_port (str): name of the video port. Refer dsVideoPortType enum
                port_index (str): Index of the video device

            Returns:

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

        result = self.utMenu.select(self.testSuite, "Get CurrentOutputSettings", promptWithAnswers)
        output_list = self.extract_output_values(result)
        return output_list

    def getResolution(self,video_port:int, port_index:int=0):
        """
            Gets the display resolution of specified video port.

            Args:
                video_port (str): name of the video port. Refer dsVideoPortType enum
                port_index (str): Index of the video device

            Returns:

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

        result = self.utMenu.select(self.testSuite, "Get Resolution", promptWithAnswers)
        output_list = self.extract_output_values(result)
        return output_list

    def getVideoEOTF(self,video_port:int, port_index:int=0):
        """
            Gets the display resolution of specified video port.

            Args:
                video_port (str): name of the video port. Refer dsVideoPortType enum
                port_index (str): Index of the video device

            Returns:

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

        result = self.utMenu.select(self.testSuite, "Get VideoEOTF", promptWithAnswers)
        output_list = self.extract_output_values(result)
        return output_list

    def isOutputHDR(self,video_port:int, port_index:int=0):
        """
            checks if the video output is HDR or not.

            Args:
                video_port (str): name of the video port. Refer dsVideoPortType enum
                port_index (str): Index of the video device

            Returns:

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

        result = self.utMenu.select(self.testSuite, "IsOutputHDR", promptWithAnswers)
        output_list = self.extract_output_values(result)
        return output_list

    def getHDCPStatus(self,video_port:int, port_index:int=0):
        """
            Gets the current HDCP status of the specified video port.

            Args:
                video_port (str): name of the video port. Refer dsVideoPortType enum
                port_index (str): Index of the video device

            Returns:

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

        result = self.utMenu.select(self.testSuite, "Get HDCPStatus", promptWithAnswers)
        output_list = self.extract_output_values(result)
        return output_list

    def getHDCPCurrentProtocol(self,video_port:int, port_index:int=0):
        """
            Gets the current negotiated HDCP protocol version.

            Args:
                video_port (str): name of the video port. Refer dsVideoPortType enum
                port_index (str): Index of the video device

            Returns:

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

        result = self.utMenu.select(self.testSuite, "Get HDCPCurrentProtocol", promptWithAnswers)
        output_list = self.extract_output_values(result)
        return output_list

    def getHdmiPreference(self,video_port:int, port_index:int=0):
        """
            Gets the preferred HDMI Protocol version of specified video port.

            Args:
                video_port (str): name of the video port. Refer dsVideoPortType enum
                port_index (str): Index of the video device

            Returns:

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

        result = self.utMenu.select(self.testSuite, "Get HdmiPreference", promptWithAnswers)
        output_list = self.extract_output_values(result)
        return output_list

    def getColorSpace(self,video_port:int, port_index:int=0):
        """
            Gets the color space setting of specified video port.

            Args:
                video_port (str): name of the video port. Refer dsVideoPortType enum
                port_index (str): Index of the video device

            Returns:

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

        result = self.utMenu.select(self.testSuite, "Get ColorSpace", promptWithAnswers)
        output_list = self.extract_output_values(result)
        return output_list

    def getColorDepth(self,video_port:int, port_index:int=0):
        """
            Gets the color depth value of specified video port.

            Args:
                video_port (str): name of the video port. Refer dsVideoPortType enum
                port_index (str): Index of the video device

            Returns:

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

        result = self.utMenu.select(self.testSuite, "Get ColorDepth", promptWithAnswers)
        output_list = self.extract_output_values(result)
        return output_list

    def getHDCPReceiverProtocol(self,video_port:int, port_index:int=0):
        """
            Gets the HDCP protocol version of the connected sink device.

            Args:
                video_port (str): name of the video port. Refer dsVideoPortType enum
                port_index (str): Index of the video device

            Returns:

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

        result = self.utMenu.select(self.testSuite, "Get HDCPReceiverProtocol", promptWithAnswers)
        output_list = self.extract_output_values(result)
        return output_list

    def getIgnoreEDIDStatus(self,video_port:int, port_index:int=0):
        """
            Gets the IgnoreEDID status variable set in the device.

            Args:
                video_port (str): name of the video port. Refer dsVideoPortType enum
                port_index (str): Index of the video device

            Returns:

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

        result = self.utMenu.select(self.testSuite, "Get IgnoreEDIDStatus", promptWithAnswers)
        output_list = self.extract_output_values(result)
        return output_list

    def getPreferredColorDepth(self,video_port:int, port_index:int=0):
        """
            Gets the preferred color depth values.

            Args:
                video_port (str): name of the video port. Refer dsVideoPortType enum
                port_index (str): Index of the video device

            Returns:

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

        result = self.utMenu.select(self.testSuite, "Get PreferredColorDepth", promptWithAnswers)
        output_list = self.extract_output_values(result)
        return output_list

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

    def getHDCPVersion(self):
        """
        Returns the supported HDCP on device.

        Args:
            None.

        Returns:
            returns the supported hdcp_protocol_version
        """
        hdcp_protocol_version = 0

        ports = self.deviceProfile.get("Ports")
        for i in range(1, len(ports)+1):
            entry = ports[i]
            hdcp_protocol_version = dsVideoPorthdcp_version(entry['hdcp_protocol_version']).name

        return hdcp_protocol_version

    def getResolutions(self):
        """
        Returns the supported Resolutions on device.

        Args:
            None.

        Returns:
            returns the supported resolutions
        """
        # Store the resolutions in a list
        resolutions_list = []
        pixel_res = 0

        ports = self.deviceProfile.get("Ports")
        for i in range(1, len(ports)+1):
            entry = ports[i]
            num_supported_resolutions = entry["numSupportedResolutions"]
            supported_resolutions = entry["supportedResolutions"]
            for j in range(1, num_supported_resolutions + 1):
                resolutions_data = supported_resolutions.get(j)
                if resolutions_data:
                    # Convert pixelResolution value to dsVideoResolution enum and add to list
                    pixel_res = resolutions_data.get("pixelResolution")
                    resolution_enum = dsVideoResolution(pixel_res).name
                    aspectRatio_res = resolutions_data.get("aspectRatio")
                    aspectRatio_enum = dsVideoAspectRatio(aspectRatio_res).name
                    stereoScopicMode_res = resolutions_data.get("stereoScopicMode")
                    stereoScopicMode_enum = dsVideoStereoScopicMode(stereoScopicMode_res).name
                    frameRate_res = resolutions_data.get("frameRate")
                    frameRate_enum = dsVideoFrameRate(frameRate_res).name
                    scanModes_res = resolutions_data.get("interlaced")
                    scanModes_enum = dsVideoScanModeMode(scanModes_res).name

                    resolutions_list.append({
                        "pixelResolution":resolution_enum,
                        "aspectRatio":aspectRatio_enum,
                        "stereoScopicMode":stereoScopicMode_enum,
                        "frameRate":frameRate_enum,
                         "interlaced":scanModes_enum
                        })

        return resolutions_list

    def getAspectRatio(self):
        """
        Returns the supported aspectRatio on device.

        Args:
            None.

        Returns:
            returns the supported aspectRatio
        """
        # Store the resolutions in a list
        aspectRatio_list = []

        ports = self.deviceProfile.get("Ports")
        for i in range(1, len(ports)+1):
            entry = ports[i]
            num_supported_resolutions = entry["numSupportedResolutions"]
            supported_resolutions = entry["supportedResolutions"]
            for j in range(1, num_supported_resolutions + 1):
                aspectRatio_data = supported_resolutions.get(j)
                if aspectRatio_data:
                    # Convert aspectRatio value to dsVideoAspectRatio enum and add to list
                    aspectRatio_res = aspectRatio_data.get("aspectRatio")
                    aspectRatio_enum = dsVideoAspectRatio(aspectRatio_res).name
                    aspectRatio_list.append(aspectRatio_enum)

        return aspectRatio_list

    def getStereoScopicMode(self):
        """
        Returns the supported stereoScopicMode on device.

        Args:
            None.

        Returns:
            returns the supported stereoScopicMode
        """
        # Store the resolutions in a list
        stereoScopicMode_list = []

        ports = self.deviceProfile.get("Ports")
        for i in range(1, len(ports)+1):
            entry = ports[i]
            num_supported_resolutions = entry["numSupportedResolutions"]
            supported_resolutions = entry["supportedResolutions"]
            for j in range(1, num_supported_resolutions + 1):
                stereoScopicMode_data = supported_resolutions.get(j)
                if stereoScopicMode_data:
                    # Convert stereoScopicMode value to dsVideoStereoScopicMode enum and add to list
                    stereoScopicMode_res = stereoScopicMode_data.get("stereoScopicMode")
                    stereoScopicMode_enum = dsVideoStereoScopicMode(stereoScopicMode_res).name
                    stereoScopicMode_list.append(stereoScopicMode_enum)

        return stereoScopicMode_list

    def getFrameRates(self):
        """
        Returns the supported Frame rates on device.

        Args:
            None.

        Returns:
            returns the supported Frame rates
        """
        # Store the resolutions in a list
        frameRates_list = []

        ports = self.deviceProfile.get("Ports")
        for i in range(1, len(ports)+1):
            entry = ports[i]
            num_supported_resolutions = entry["numSupportedResolutions"]
            supported_resolutions = entry["supportedResolutions"]
            for j in range(1, num_supported_resolutions + 1):
                frameRate_data = supported_resolutions.get(j)
                if frameRate_data:
                    # Convert frameRate value to dsVideoFrameRate enum and add to list
                    frameRate_res = frameRate_data.get("frameRate")
                    frameRate_enum = dsVideoFrameRate(frameRate_res).name
                    frameRates_list.append(frameRate_enum)

        return frameRates_list

    def getScanModes(self):
        """
        Returns the supported ScanModes on device.

        Args:
            None.

        Returns:
            returns the supported ScanModes
        """
        # Store the resolutions in a list
        scanModes_list = []

        ports = self.deviceProfile.get("Ports")
        for i in range(1, len(ports)+1):
            entry = ports[i]
            num_supported_resolutions = entry["numSupportedResolutions"]
            supported_resolutions = entry["supportedResolutions"]
            for j in range(1, num_supported_resolutions + 1):
                scanModes_data = supported_resolutions.get(j)
                if scanModes_data:
                    # Convert interlaced value to dsVideoScanModeMode enum and add to list
                    scanModes_res = scanModes_data.get("interlaced")
                    scanModes_enum = dsVideoScanModeMode(scanModes_res).name
                    scanModes_list.append(scanModes_enum)

        return scanModes_list

    def getHDRCapabilities(self):
        """
        Returns the supported HDR Formats on device.

        Args:
            None.

        Returns:
            returns the supported HDR Formats
        """
        supported_HDRformats = []

        ports = self.deviceProfile.get("Ports")
        for i in range(1, len(ports)+1):
            entry = ports[i]
            hdr_capabilities = entry['hdr_capabilities']
            for hdr_format in dsHDRStandard:
                if hdr_capabilities & hdr_format.value:  # Check if the format is supported
                    supported_HDRformats.append(hdr_format.name)

        return supported_HDRformats

    def getColorDepth(self):
        """
        Returns the supported Color depth.

        Args:
            None.

        Returns:
            returns the color depth
        """
        color_depth = 0

        color_depth = dsDisplayColorDepth(self.deviceProfile.get("color_depth")).name
        return color_depth

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
