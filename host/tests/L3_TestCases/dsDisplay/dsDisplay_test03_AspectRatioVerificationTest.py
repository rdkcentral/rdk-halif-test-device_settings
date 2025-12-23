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

import os
import sys

dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(dir_path, "../../"))

from dsDisplayHelperClass import dsDisplayHelperClass
from raft.framework.core.logModule import logModule
from dsClasses.dsVideoPort import dsVideoPortClass, dsVideoResolution, dsVideoAspectRatio, dsVideoStereoScopicMode, dsVideoFrameRate, dsVideoScanModeMode
from raft.framework.plugins.ut_raft.configRead import ConfigRead

class dsDisplay_test03_AspectRatioVerificationTest(dsDisplayHelperClass):

    """
    Test class to retrieve and verify the display aspect ratio.

    This class uses the `dsDisplayClass` to interact with the device's display,
    downloading necessary test assets, retrieving the aspect ratio, and performing verification.
    """

    def __init__(self, log:logModule=None):
        """
        Initializes the test03_GetDisplayAspectRatio test .

        Args:
            None.
        """
        # Class variables
        self.testName  = "test03_AspectRatioVerificationTest"
        self.qcID = '3'
        super().__init__(self.testName, self.qcID, log)
    
    def enablePort(self, video_port:int, port_index:int=0):
        """
        Enables the specified Video port.

        Args:
        video_port (int): The enumeration value representing the video port to enable.
                           Refer to the appropriate enum for valid options.
        port_index (int, optional): The index of the specific port to enable. Defaults to 0.

        Returns:
            None

        Example:
            enablePort(video_port=dsVIDEOPORT_TYPE_HDMI, port_index=1)
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

        # Convert input arguments to strings and update the prompts
        promptWithAnswers[0]["input"] = str(video_port)
        promptWithAnswers[1]["input"] = str(port_index)

        result = self.testdsDisplay.utMenu.select(self.videoPortTestSuit, "Enable VideoPort", promptWithAnswers)
        type = self.testdsDisplay.moduleConfigProfile.get("Type")
        # Enable HDCP for source devices
        if type == "source":
            result = self.testdsDisplay.utMenu.select(self.videoPortTestSuit, "Enable HDCP", promptWithAnswers)

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

        for i in range(1, len(self.ports)+1):
            entry = self.ports[i]
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

    def select_Resolution(self,video_port:int, port_index:int=0, resolution: dict = None ):
        """
        Sets the resolution of the specified video port.

        This method configures the resolution settings for a video port, including pixel resolution,
        aspect ratio, stereoscopic mode, frame rate, and scan mode. It provides options based on
        the specified parameters or defaults to predefined values if not provided.

        Args:
            video_port (int): The enumeration value representing the video port.
                            Refer to the dsVideoPortType enum for valid options.
            port_index (int, optional): The index of the specific port to configure. Defaults to 0.
            resolution (dict, optional): A dictionary containing resolution settings:
                - "pixelResolution" (str): Desired pixel resolution (e.g., 'dsVIDEO_PIXELRES_1920x1080').
                - "aspectRatio" (str): Desired aspect ratio (e.g., 'dsVIDEO_ASPECT_RATIO_16x9').
                - "stereoScopicMode" (str): Desired stereoscopic mode (e.g., 'dsVIDEO_SSMODE_2D').
                - "frameRate" (str): Desired frame rate (e.g., 'dsVIDEO_FRAMERATE_24').
                - "interlaced" (str): Desired scan mode (e.g., 'dsVIDEO_SCANMODE_INTERLACED').

        Returns:
            None

        Example:
            select_Resolution(video_port=dsVIDEOPORT_TYPE_HDMI, port_index=0, resolution={
                "pixelResolution": "dsVIDEO_PIXELRES_3840x2160",
                "aspectRatio": "dsVIDEO_ASPECT_RATIO_16x9",
                "stereoScopicMode": "dsVIDEO_SSMODE_3D",
                "frameRate": "dsVIDEO_FRAMERATE_60",
                "interlaced": "dsVIDEO_SCANMODE_PROGRESSIVE"
            })
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

        # Convert input arguments to strings and update the prompts
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

        result = self.testdsDisplay.utMenu.select(self.videoPortTestSuit, "Set Resolution", promptWithAnswers)

    def testFunction(self):
        """
        This function will test the Display by getting the aspectratio of the display.

        This function:
        - Retrieves aspectratio for each supported port and verifies them.
        - Cleans up assets after the test.

        Returns:
            bool: Final result of the test.
        """

        self.videoPortProfilefile = os.path.join(dir_path, "../../../../profiles/source/Source_4K_VideoPort.yaml")
        self.testdsDisplay.utils.scpCopy(self.hal_session, self.videoPortProfilefile, self.targetWorkspace)
        self.videoPortTestSuit = "L3 dsVideoPort"
        self.videoPortmoduleName     = "dsVideoPort"
        self.videoPortmoduleConfigProfile     = ConfigRead(self.videoPortProfilefile , self.videoPortmoduleName)
        self.ports                   = self.videoPortmoduleConfigProfile.fields.get("Ports")
        result = self.testdsDisplay.utMenu.select( self.videoPortTestSuit, "VideoPort Init")
        # Initialize the dsDisplay module
        self.testdsDisplay.initialise()

        result = False
        # Loop through the supported video ports
        for port, index in self.testdsDisplay.getSupportedPorts():
            # Enable video port
            self.enablePort(port, index)

            for resolution in self.getResolutions():
                #set videoport resolution
                self.select_Resolution(port, index, resolution)

                self.testdsDisplay.selectDisplayPort(port, index)

                aspectRatio = resolution.get("aspectRatio")

                self.log.stepStart(f'Test Display Aspect Ratio {aspectRatio} Port: {port}')
                ratio = self.testdsDisplay.getAspectRatio()
                if ratio == aspectRatio:
                    result = True
                self.log.stepResult(result, f'Test Display Aspect Ratio {aspectRatio} Port: {port}')

        result = self.testdsDisplay.utMenu.select(self.videoPortTestSuit, "VideoPort Term")
        #Terminate dsDisplay Module
        self.testdsDisplay.terminate()

        return result

if __name__ == '__main__':
    summerLogName = os.path.splitext(os.path.basename(__file__))[0] + "_summery"
    summeryLog = logModule(summerLogName, level=logModule.INFO)
    test = dsDisplay_test03_AspectRatioVerificationTest(summeryLog)
    test.run(False)

