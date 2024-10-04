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

    def select_Resolution(self,video_port:int, port_index:int=0, video_resolution:int=4, frame_rate:int=0, scan_mode:int=0):
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
            },
            {
                "query_type": "list",
                "query": "Supported Resolution",
                "input": "dsVIDEO_PIXELRES_1920x1080"
            },
            {
                "query_type": "list",
                "query": "Supported Frame Rates",
                "input": "dsVIDEO_FRAMERATE_24"
            },
            {
                "query_type": "list",
                "query": "Supported Scan modes",
                "input": "dsVIDEO_SCANMODE_INTERLACED"
            }
        ]

        promptWithAnswers[0]["input"] = str(video_port)
        promptWithAnswers[1]["input"] = str(port_index)
        promptWithAnswers[2]["input"] = str(video_resolution)
        promptWithAnswers[3]["input"] = str(frame_rate)
        promptWithAnswers[4]["input"] = str(scan_mode)


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
                "query": "Supported HDR modes",
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
                "query": "Supported display Color depth to set",
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
                "query": "Select Background Color to set",
                "input": "dsVIDEO_BGCOLOR_BLUE"
            }
        ]

        promptWithAnswers[0]["input"] = str(video_port)
        promptWithAnswers[1]["input"] = str(port_index)
        promptWithAnswers[2]["input"] = str(background_color)

        result = self.utMenu.select(self.testSuite, "Set BackgroundColor", promptWithAnswers)

    def dsVideoPort_CurrentOutputSettings(self,video_port:int, port_index:int=0):
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

    def dsVideoPort_GetResolution(self,video_port:int, port_index:int=0):
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

    def dsVideoPort_GetVideoEOTF(self,video_port:int, port_index:int=0):
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

    def dsVideoPort_IsOutputHDR(self,video_port:int, port_index:int=0):
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

    def dsVideoPort_GetHDCPStatus(self,video_port:int, port_index:int=0):
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

    def dsVideoPort_GetHDCPCurrentProtocol(self,video_port:int, port_index:int=0):
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

    def dsVideoPort_GetHdmiPreference(self,video_port:int, port_index:int=0):
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

    def dsVideoPort_GetColorSpace(self,video_port:int, port_index:int=0):
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

    def dsVideoPort_GetColorDepth(self,video_port:int, port_index:int=0):
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

    def dsVideoPort_GetHDCPReceiverProtocol(self,video_port:int, port_index:int=0):
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

    def dsVideoPort_GetIgnoreEDIDStatus(self,video_port:int, port_index:int=0):
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

    def dsVideoPort_GetPreferredColorDepth(self,video_port:int, port_index:int=0):
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
        hdcp_protocol_version =0

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
            returns the supported hdcp_protocol_version
        """
        hdcp_protocol_version =0

        ports = self.deviceProfile.get("Ports")
        for i in range(1, len(ports)+1):
            entry = ports[i]
            hdcp_protocol_version = dsVideoPorthdcp_version(entry['hdcp_protocol_version']).name

        return hdcp_protocol_version

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
            hdr_capabilities = dsHDRStandard(entry['hdr_capabilities']).name
            for hdr_format in dsHDRStandard:
                if hdr_capabilities & hdr_format.value:
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
        color_depth =0

        color_depth = self.deviceProfile.get("color_depth")
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
