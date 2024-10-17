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
from enum import Enum, auto

dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(dir_path, "../"))

from dsClasses.dsHdmiIn import dsHdmiInClass
from raft.framework.plugins.ut_raft import utHelperClass
from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.plugins.ut_raft.utUserResponse import utUserResponse

class hdmiVideoResolution(Enum):
      dsVIDEO_PIXELRES_720x480   = 0     #720x480 Resolution
      dsVIDEO_PIXELRES_720x576   = 1     #720x576 Resolution
      dsVIDEO_PIXELRES_1280x720  = 2     #1280x720 Resolution
      dsVIDEO_PIXELRES_1366x768  = 3     #1366x768 Resolution
      dsVIDEO_PIXELRES_1920x1080 = 4     #1920x1080 Resolution
      dsVIDEO_PIXELRES_3840x2160 = 5     #3840x2160 Resolution
      dsVIDEO_PIXELRES_4096x2160 = 6     #3840x2160 Resolution
      dsVIDEO_PIXELRES_MAX = 7           #dsVIDEO_PIXELRES_MAX

class hdmiVideoAspectRatio(Enum):
      dsVIDEO_ASPECT_RATIO_4x3 = 0    #< 4:3 aspect ratio
      dsVIDEO_ASPECT_RATIO_16x9 = 1   #< 16:9 aspect ratio
      dsVIDEO_ASPECT_RATIO_MAX = 2    #< Out of range

class hdmiVideoStereoScopicMode(Enum):
    dsVIDEO_SSMODE_UNKNOWN = 0            #Unknown mode
    dsVIDEO_SSMODE_2D, = 1                #2D mode
    dsVIDEO_SSMODE_3D_SIDE_BY_SIDE = 2    #3D side by side (L/R) stereo mode
    dsVIDEO_SSMODE_3D_TOP_AND_BOTTOM = 3  #3D top & bottom stereo mode
    dsVIDEO_SSMODE_MAX = 4                #Out of range

class hdmiVideoFrameRate(Enum):
    dsVIDEO_FRAMERATE_UNKNOWN = 0  #Unknown frame rate
    dsVIDEO_FRAMERATE_24 = 1       # Played at 24 frames per second
    dsVIDEO_FRAMERATE_25 = 2       # Played at 25 frames per second
    dsVIDEO_FRAMERATE_30 = 3       # Played at 30 frames per second
    dsVIDEO_FRAMERATE_60 = 4       # Played at 60 frames per second
    dsVIDEO_FRAMERATE_23dot98 = 5  # Played at 23.98 frames per second
    dsVIDEO_FRAMERATE_29dot97 = 6  # Played at 29.97 frames per second
    dsVIDEO_FRAMERATE_50 = 7       # Played at 50 frames per second
    dsVIDEO_FRAMERATE_59dot94 = 8  # Played at 59.94 frames per second
    dsVIDEO_FRAMERATE_MAX = 9      # Out of range

class dsHdmiIn_test4_VideoModeChangeCallback_Verify(utHelperClass):

    testName  = "test4_VideoModeChangeCallback_Verify"
    testSetupPath = dir_path + "/dsHdmiIn_L3_testSetup.yml"
    moduleName = "dsHdmiIn"
    rackDevice = "dut"

    def __init__(self):
        """
        Initializes the test4_VideoModeChangeCallback_Verify test .

        Args:
            None.
        """
        super().__init__(self.testName, '1')

        # Test Setup configuration file
        self.testSetup = ConfigRead(self.testSetupPath, self.moduleName)

        # Open Session for hal test
        self.hal_session = self.dut.getConsoleSession("ssh_hal_test")

         # Create user response Class
        self.testUserResponse = utUserResponse()

        # Get path to device profile file
        self.deviceProfile = dir_path + "/" + self.cpe.get("test").get("profile")

    def testDownloadAssets(self):
        """
        Downloads the artifacts and streams listed in test-setup configuration file to the dut.

        Args:
            None.
        """

        self.deviceDownloadPath = self.cpe.get("target_directory")

        #download test artifacts to device
        url = self.testSetup.assets.device.test4_VideoModeChangeCallback_Verify.artifacts
        if url is not None:
            self.downloadToDevice(url, self.deviceDownloadPath, self.rackDevice)

    def testCleanAssets(self):
        """
        Removes the assets copied to the dut.

        Args:
            None.
        """
        self.deleteFromDevice(self.testStreams)

    def testRunPrerequisites(self):
        """
        Runs Prerequisite commands listed in test-setup configuration file on the dut.

        Args:
            None.
        """

       # Run commands as part of test postrequisites
        test = self.testSetup.get("assets").get("device").get(self.testName)
        cmds = test.get("postcmd")
        if cmds is not None:
            for cmd in cmds:
                self.writeCommands(cmd)

    #TODO: Current version supports only manual verification.
    def CheckDeviceStatusAndResolutionChange(self, manual=False, port_type:str=0):
       """
     #TODO: Current version supports only manual verification.
    def CheckDeviceStatus(self, manual=False, port_type:str:0):
        """
        Verifies whether the particular input selected or not.

        Args:
            manual (bool, optional): Manual verification (True: manual, False: other verification methods).
                                     Defaults to other verification methods
            port_type (str) : Hdmi In port type as string.
            resolution (bool, optional) : Manual verification(True: manual, False: other verification methods)

        Returns:
            bool
        if manual == True:
            return self.testUserResponse.getUserYN(f'Is {port_type} Hdmi In device is ON? and change the resolution on source side (Y/N):')
        else :
            #TODO: Add automation verification methods
            return False

    #TODO: Current version supports only manual verification.
    def VerifyInput(self, manual=False):
        """
        Verifies whether the particular input selected or not.

        Args:
            manual (bool, optional): Manual verification (True: manual, False: other verification methods).
                                     Defaults to other verification methods

        Returns:
            bool
        """
        if manual == True:
            return self.testUserResponse.getUserYN("Is HdmiIn port selected? (Y/N):")
        else :
            #TODO: Add automation verification methods
            return False

    def find_VideoModeStatus(self, input_str: str, vmode_status: str) -> bool:
        if vmode_status in input_str:
            return True
        return False

    def testFunction(self):
        """This Callback will check for Video Mode change events on HdmiIn ports

        Returns:
            bool
        """

        # Download the assets listed in test setup configuration file
        self.testDownloadAssets()

        # Run Prerequisites listed in the test setup configuration file
        self.testRunPrerequisites()

        # Create the dsHdmiIn class
        self.testdsHdmiIn = dsHdmiInClass(self.deviceProfile, self.hal_session)

        self.log.testStart("test4_VideoModeChangeCallback_Verify", '1')

        # Initialize the dsAudio module
        self.testdsHdmiIn.initialise(self.testdsHdmiIn.getDeviceType())

        audmix = 0      #default value false
        videoplane = 0  #Always select primary plane.
        topmost = 1     #Always should be true.
   
        # Loop through the supported HdmiIn ports
        for port,index in self.testdsAudio.getSupportedPorts():
            self.log.stepStart(f'Select {port} Port')
            self.log.step(f'Select {port} Port')

            self.testdsHdmiIn.selectHDMIInPort(port, audmix, videoplane, topmost)
            self.log.step(f'Port Selcted {port}')

            # Check the HdmiIn device is active
            self.CheckDeviceStatusAndResolutionChange(True,port)
            
            videomode = self.testdsHdmiIn.getVideoModeCallbackStatus()
            if port == videomode[0] and videomode[3] == "true":
                result = True
                self.log.stepResult(result,f'hdmi video mode port:{port} pixelresolution:{videomode[1]} aspectratio:{videomode[2]} in Callback found')
            else:
                result = False
                self.log.stepResult(result,f'hdmi video mode port:{port} pixelresolution:{videomode[1]} aspectratio:{videomode[2]} in Callback found')
            result = self.CheckDeviceStatus(True,port)
          
            if result != False:
                self.testdsHdmiIn.selectPort(port, index, audmix, videoplane, topmost)
                result = self.VerifyInput(True)
                self.log.stepResult(result, f'HdmiIn Select Verification {port} Port')
                
                result = self.hal_session.read_until("Result dsHdmiInGetCurrentVideoMode OUT:resolution:(resolution name:[  ], pixelResolution:[  ] ,aspectRatio:")
                print(result)
                
                for pixelresolution in list(hdmiVideoResolution):
                    if find_VideoModeStatus(result,hdmiVideoResolution(pixelresolution).name):
                        self.log.stepResult(True,f'hdmi Video Resolution {hdmiVideoResolution(pixelresolution).name} in Callback found')
                    else:
                        self.log.stepResult(False,f'hdmi Video Resolution {hdmiVideoResolution(pixelresolution).name} in Callback found')
                
                for aspectratio in list(hdmiVideoAspectRatio):
                    if aspectratio != hdmiVideoAspectRatio.dsVIDEO_ASPECT_RATIO_MAX:
                        if find_VideoModeStatus(result,hdmiVideoAspectRatio(aspectratio).name):
                            self.log.stepResult(True,f'hdmi aspect ratio {hdmiVideoAspectRatio(aspectratio).name} in Callback found')
                        else:
                            self.log.stepResult(False,f'hdmi aspect ratio {hdmiVideoAspectRatio(aspectratio).name} in Callback found')

                result = self.hal_session.read_until("Result dsHdmiInGetCurrentVideoMode OUT:resolution:(stereoScopicMode:[  ], frameRate:[  ], interlaced:[  ]")
                print(result)

                for stereoscopic in list(hdmiVideoStereoScopicMode):
                    if stereoscopic != hdmiVideoStereoScopicMode.dsVIDEO_SSMODE_MAX:
                        if find_VideoModeStatus(result,hdmiVideoStereoScopicMode(stereoscopic).name):
                            self.log.stepResult(True,f'hdmi stereo scopic {hdmiVideoStereoScopicMode(stereoscopic).name} in Callback found')
                        else:
                            self.log.stepResult(False,f'hdmi aspect ratio {hdmiVideoStereoScopicMode(stereoscopic).name} in Callback found')
               
                for framerate in list(hdmiVideoFrameRate):
                    if framerate != hdmiVideoFrameRate.dsVIDEO_FRAMERATE_MAX:
                        if find_VideoModeStatus(result,hdmiVideoFrameRate(framerate).name):
                            self.log.stepResult(True,f'hdmi frame rate {hdmiVideoFrameRate(framerate).name} in Callback found')
                        else:
                            self.log.stepResult(False,f'hdmi frame rate {hdmiVideoFrameRate(framerate).name} in Callback found')


        # Clean the assets downloaded to the device
        self.testCleanAssets()

        # Terminate dsHdmiIn Module
        self.testdsHdmiIn.terminate()

        # Delete the dsHdmiIn class
        del self.testdsHdmiIn

        return result

if __name__ == '__main__':
    test = dsHdmiIn_test4_VideoModeChangeCallback_Verify()
    test.run(False)
