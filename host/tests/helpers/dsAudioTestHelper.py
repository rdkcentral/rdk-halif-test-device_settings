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
dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(dir_path+"/../")

from raft.framework.plugins.ut_raft.utHelper import utHelperClass

#TODO: used by ut_core remove later after updating ut_core
run_script="./bins/run.sh"

class dsAudioPortType(Enum):
    dsAUDIOPORT_TYPE_ID_LR     = 0
    dsAUDIOPORT_TYPE_HDMI      = auto()
    dsAUDIOPORT_TYPE_SPDIF     = auto()
    dsAUDIOPORT_TYPE_SPEAKER   = auto()
    dsAUDIOPORT_TYPE_HDMI_ARC  = auto()
    dsAUDIOPORT_TYPE_HEADPHONE = auto()

class dsAudioTestHelperClass(utHelperClass):

    moduleName = "dsAudio"
    """
    Device Settings Audio Test Helper Code

    This module provides common extensions for device Settings Audio Module.
    """
    def __init__(self, test_config, testGroup="", testName="", qcId="", device="cpe1", log=None ):
        """
        Initializes the dsAudio test helper function.

        Args:
            test_config (str): test configuration file.
            testGroup (str, optional): test group name. Defaults to "".
            testName (str, optional): Name of the test. Defaults to "".
            qcId (str, optional): QC ID of the test. Defaults to "".
            device (str, optional): Device name. Defaults to cpe1.
            log (class, optional): Parent log class. Defaults to None.
        """
        super().__init__(test_config, self.moduleName, testGroup, testName, qcId, device, log=log )

        # Download Assets on device
        self.downloadAssetsToDevice()

        # Run Prerequisite commands on the device
        self.runPrerequisiteOnDevice()

        # Initialize the dsAudio
        self.dsAudioInitialise()

    def dsAudioInitialise(self):
        """
        Initializes the device settings Audio module.

        Args:
            None.

        Returns:
            None
        """
        self.UT.run_tests(run_script, self.testGroup, "Initialize dsAudio")

    def dsAudioEnablePort(self, audio_port):
        """
        Enables the audio port.

        Args:
            audio_port (str): name of the audio port. Refer dsAudioPortType enum

        Returns:
            None
        """
        output = self.selectGroupTest("menu_enable", self.queryPrompt)
        self.selectGroupMenus(output, audio_port)

    def dsAudioVerifyAudio(self, manual=True):
        """
        Verifies whether the audio is fine or not.

        Args:
            manual (bool, optional): Manual verification (True: manual, False: other verification methods).
                                     Defaults to manual verification

        Returns:
            bool
        """
        if manual == True:
            return self.hostUserResponse.getUserYNFromHost("Is Audio playing fine[y/n]")
        else :
            #TOD: Add automation verification methods
            return False

    def dsAudioDisablePort(self, audio_port):
        """
        Enables the audio port.

        Args:
            audio_port (str): name of the audio port. Refer dsAudioPortType enum

        Returns:
            None
        """
        output = self.selectGroupTest("menu_disable", self.queryPrompt)
        self.selectGroupMenus(output, audio_port)

    def dsAudioTerminate(self):
        """
        Enables the audio port.

        Args:
            None.

        Returns:
            None
        """
        output = self.selectGroupTest("menu_menu_terminate", self.queryPrompt)

    def dsAudioGetSupportedPorts(self):
        """
        Returns the supported audio ports on device.

        Args:
            None.

        Returns:
            returns the list of supported audio ports
        """
        ports = self.deviceProfile.get("PortTypes")

        return [dsAudioPortType(value).name for value in ports] if ports is not None else []

    def dsAudioGetStreams(self):
        """
        Returns the streams copied to the device.

        Args:
            None.

        Returns:
            returns the list of steams
        """
        return self.testStreams

    def dsAudioPlay(self, stream):
        """
        Start of Playback of the stream.

        Args:
            None.

        Returns:
            None
        """
        self.player.utStartPlay(stream)

    def dsAudioPlayStop(self, stream):
        """
        Stops of Playback of the stream.

        Args:
            None.

        Returns:
            None
        """
        self.player.utStopPlay()

    def __del__(self):
        """
        De-Initializes the dsAudio helper function.

        Args:
            None.

        Returns:
            None
        """
        self.dsAudioTerminate()
