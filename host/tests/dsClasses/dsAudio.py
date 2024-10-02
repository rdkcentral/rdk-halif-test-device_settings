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
sys.path.append(dir_path+"/../")

from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.plugins.ut_raft.utSuiteNavigator import UTSuiteNavigatorClass
from raft.framework.plugins.ut_raft.interactiveShell import InteractiveShell

class dsAudioPortType(Enum):
    dsAUDIOPORT_TYPE_ID_LR     = 0
    dsAUDIOPORT_TYPE_HDMI      = auto()
    dsAUDIOPORT_TYPE_SPDIF     = auto()
    dsAUDIOPORT_TYPE_SPEAKER   = auto()
    dsAUDIOPORT_TYPE_HDMI_ARC  = auto()
    dsAUDIOPORT_TYPE_HEADPHONE = auto()

class dsAudioClass():

    moduleName = "dsAudio"
    menuConfig =  dir_path + "/dsAudio_test_suite.yml"
    testSuite = "L3 dsAudio"

    """
    Device Settings Audio Class

    This module provides common extensions for device Settings Audio Module.
    """
    def __init__(self, deviceProfilePath:str, session=None ):
        """
        Initializes the dsAudio class function.
        """
        self.deviceProfile = ConfigRead( deviceProfilePath, self.moduleName)
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
        Initializes the device settings Audio module.

        Args:
            device_type (int, optional): 0 - sink device, 1 - source device. Defaults to sink.

        Returns:
            None
        """
        promptWithAnswers = [
                {
                    "query_type": "direct",
                    "query": "Select Device Type[0: Sink, 1: Source]:",
                    "input": "0"
                }
        ]
        promptWithAnswers[0]["input"] = str(device_type)
        result = self.utMenu.select( self.testSuite, "Initialize dsAudio", promptWithAnswers)

    def terminate(self):
        """
        Enables the audio port.

        Args:
            None.

        Returns:
            None
        """
        result = self.utMenu.select(self.testSuite, "test_terminate_audio")

    def enablePort(self, audio_port:int, port_index:int=0, arc_type:int=2):
        """
        Enables the audio port.

        Args:
            audio_port (int): audio port enum value
            port_index (int, optional): port index. Defaults to 0
            arc_type (int, optional): Type of ARC. Defaults to eArc.

        Returns:
            None
        """
        promptWithAnswers = [
                {
                    "query_type": "list",
                    "query": "Select dsAudio Port:",
                    "input": ""
                },
                {
                    "query_type": "direct",
                    "query": "Select dsAudio Port Index[0-10]:",
                    "input": "0"
                },
                {
                    "query_type": "direct",
                    "query": "Select ARC Type:",
                    "input": "0"
                }
        ]
        promptWithAnswers[0]["input"] = audio_port
        promptWithAnswers[1]["input"] = str(port_index)
        if audio_port == dsAudioPortType.dsAUDIOPORT_TYPE_HDMI_ARC.name:
            promptWithAnswers[2]["input"] = str(arc_type)
        else:
            promptWithAnswers.pop(2)

        result = self.utMenu.select(self.testSuite, "Enable Audio Port", promptWithAnswers)

    def disablePort(self, audio_port:int, port_index:int=0):
        """
        Disables the audio port.

        Args:
            audio_port (str): name of the audio port. Refer dsAudioPortType enum
            port_index (int, optional): port index. Defaults to 0

        Returns:
            None
        """
        promptWithAnswers = [
                {
                    "query_type": "list",
                    "query": "Select dsAudio Port:",
                    "input": ""
                },
                {
                    "query_type": "direct",
                    "query": "Select dsAudio Port Index[0-10]:",
                    "input": "0"
                }
        ]

        promptWithAnswers[0]["input"] = audio_port
        promptWithAnswers[1]["input"] = str(port_index)

        result = self.utMenu.select(self.testSuite, "Disable Audio Port", promptWithAnswers)

    def setGainLevel(self, audio_port:int, port_index:int=0, gainLevel:float=0.0):
        """
        Sets audio gain level.

        Args:
            audio_port (str): name of the audio port. Refer dsAudioPortType enum
            port_index (int, optional): port index. Defaults to 0
            gainLevel (float, optional): Gain level to be applied. Ranges from 0.0 to 100.0. Defaults to 0.0

        Returns:
            None
        """
        promptWithAnswers = [
                {
                    "query_type": "list",
                    "query": "Select dsAudio Port:",
                    "input": ""
                },
                {
                    "query_type": "direct",
                    "query": "Select dsAudio Port Index[0-10]:",
                    "input": "0"
                },
                {
                    "query_type": "direct",
                    "query": "Enter Gain Level[0.0 to 100.0]:",
                    "input": "0"
                }
        ]

        promptWithAnswers[0]["input"] = audio_port
        promptWithAnswers[1]["input"] = str(port_index)
        promptWithAnswers[2]["input"] = str(gainLevel)

        result = self.utMenu.select(self.testSuite, "Set Audio Level", promptWithAnswers)

    def setSpeakerGain(self, audio_port:int, port_index:int=0, gain:float=0.0):
        """
        Sets speaker gain.

        Args:
            audio_port (str): name of the audio port. Refer dsAudioPortType enum
            port_index (int, optional): port index. Defaults to 0
            gain (float, optional): Gain value to be applied. Ranges from -2080.0 to 480.0. Defaults to 0.0

        Returns:
            None
        """
        promptWithAnswers = [
                {
                    "query_type": "direct",
                    "query": "Enter Gain[-2080.0 to 480.0]:",
                    "input": "0"
                }
        ]

        promptWithAnswers[0]["input"] = str(gain)

        result = self.utMenu.select(self.testSuite, "Set Audio Gain For Speaker", promptWithAnswers)

    def setAudioMute(self, audio_port:int, port_index:int=0, mute:bool=True):
        """
        Mutes/Unmutes the audio.

        Args:
            audio_port (str): name of the audio port. Refer dsAudioPortType enum
            port_index (int, optional): port index. Defaults to 0
            mute (bool, optional): True - Mutes, False - Unmutes. Defaults to True

        Returns:
            None
        """
        promptWithAnswers = [
                {
                    "query_type": "list",
                    "query": "Select dsAudio Port:",
                    "input": ""
                },
                {
                    "query_type": "direct",
                    "query": "Select dsAudio Port Index[0-10]:",
                    "input": "0"
                },
                {
                    "query_type": "direct",
                    "query": "Audio Mute/UnMute[1:Mute, 2:UnMute]:",
                    "input": "1"
                }
        ]

        promptWithAnswers[0]["input"] = audio_port
        promptWithAnswers[1]["input"] = str(port_index)
        if mute == True:
            promptWithAnswers[2]["input"] = "1"
        else:
            promptWithAnswers[2]["input"] = "2"

        result = self.utMenu.select(self.testSuite, "Audio Mute/UnMute", promptWithAnswers)

    def setAudioDelay(self, audio_port:int, port_index:int=0, delay:int=0):
        """
        Set the audio delay.

        Args:
            audio_port (str): name of the audio port. Refer dsAudioPortType enum
            port_index (int, optional): port index. Defaults to 0
            delay (int, optional): audio delay to be applied. Ranges from 0 to 200. Defaults to 0

        Returns:
            None
        """
        promptWithAnswers = [
                {
                    "query_type": "list",
                    "query": "Select dsAudio Port:",
                    "input": ""
                },
                {
                    "query_type": "direct",
                    "query": "Select dsAudio Port Index[0-10]:",
                    "input": "0"
                },
                {
                    "query_type": "direct",
                    "query": "Enter Audio Delay in milli seconds[0 to 200]:",
                    "input": "0"
                }
        ]
        promptWithAnswers[0]["input"] = audio_port
        promptWithAnswers[1]["input"] = str(port_index)
        promptWithAnswers[2]["input"] = str(delay)

        result = self.utMenu.select(self.testSuite, "Set Audio Delay", promptWithAnswers)

    def enableAssociateAudioMixig(self, enable:bool = True, fader:int = 0):
        """
        Enable Associate Audio Mixing.

        Args:
            enable (bool, optional): enables the associate audio mixing. Defaults to True
            fader (bool, optional): Fader Control,-32:mute associated audio) to 32:mute main audio. Defaults to 0

        Returns:
            None
        """
        promptWithAnswers = [
                {
                    "query_type": "direct",
                    "query": "Enable/Disable Associated Audio Mixing[1:Enable, 2:Disable]:",
                    "input": "1"
                },
                {
                    "query_type": "direct",
                    "query": "Set Fader Control[-32(mute associated audio) to 32(mute main audio)]:",
                    "input": "0"
                }
        ]
        if enable:
            promptWithAnswers[0]["input"] = "1"
            promptWithAnswers[1]["input"] = str(fader)
        else:
            promptWithAnswers[0]["input"] = "2"
            promptWithAnswers.pop(1)

        result = self.utMenu.select(self.testSuite, "Set Associate Audio Mixing", promptWithAnswers)

    def setAudioMixerLevels(self, mixer_input:str, volume:int = 0):
        """
        Sets mixer levels for primary and system audio.

        Args:
            mixer_input (str): primary:Sets the volume for primary audio, "system":Sets the volume for system audio.
            volume (int, optional): volume ranges 0-100. Defaults to 0

        Returns:
            None
        """
        promptWithAnswers = [
                {
                    "query_type": "list",
                    "query": "Select Mixer Input:",
                    "input": ""
                },
                {
                    "query_type": "direct",
                    "query": "Set the Volume[0 to 100]:",
                    "input": "0"
                }
        ]

        promptWithAnswers[0]["input"] = mixer_input
        promptWithAnswers[1]["input"] = str(volume)

        result = self.utMenu.select(self.testSuite, "Set Audio Mixer Levels", promptWithAnswers)

    def setPrimarySecondaryLanguage(self, language_type:str, language:str):
        """
        Sets mixer levels for primary and system audio.

        Args:
            language_type (str): Primary:Primary language, Secondary:Secondary language.
            language (str): 3 letter long language as per ISO 639-3. eg: eng - English

        Returns:
            None
        """
        promptWithAnswers = [
                {
                    "query_type": "direct",
                    "query": "Select the Language Type[1: Primary, 2: Secondary]:",
                    "input": "1"
                },
                {
                    "query_type": "direct",
                    "query": "Enter 3 letter long language as per ISO 639-3:",
                    "input": "eng"
                }
        ]

        if (language_type == "Primary"):
            promptWithAnswers[0]["input"] = "1"
        else:
            promptWithAnswers[0]["input"] = "2"

        promptWithAnswers[1]["input"] = language

        result = self.utMenu.select(self.testSuite, "Primary/Secondary Language", promptWithAnswers)

    def getHeadphoneConnectionStatus(self):
        """
        Gets the headphone connection status.

        Args:
            None.

        Returns:
            bool : connection status
        """
        result = self.utMenu.select( self.testSuite, "Headphone Connection")
        connectionStatusPattern = r"Result dsAudioOutIsConnected\(IN:handle:\[.*\], OUT:isConnected:\[(true|false)\]\)"
        isConnected = self.searchPattern(result, connectionStatusPattern)
        if(isConnected == "true"):
            return True
        return False

    def getAudioFormat(self):
        """
        Gets the audio format.

        Args:
            None.

        Returns:
            str : audio format
        """
        result = self.utMenu.select( self.testSuite, "Get Audio Format")
        audioFormatPattern = r"dsGetAudioFormat\(IN:handle:\[.*\], OUT:audioFormat:\[(dsAUDIO_FORMAT_\w+)\]\)"
        audioFormat = self.searchPattern(result, audioFormatPattern)

        return audioFormat

    def getSupportedPorts(self):
        """
        Returns the supported audio ports on device.

        Args:
            None.

        Returns:
            returns the list of supported audio ports
        """
        portLists = []

        ports = self.deviceProfile.get("Ports")
        for i in range(1, len(ports)+1):
            entry = ports[i]
            portLists.append([dsAudioPortType(entry['Typeid']).name, entry['Index']])

        return portLists

    def getDeviceType(self):
        """
        Returns the supported audio ports on device.

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

    platformProfile = dir_path + "/../../../profiles/sink/Sink_AudioSettings.yaml"
    # test the class assuming that it's optional
    test = dsAudioClass(platformProfile, shell)

    test.initialise()
    ports = test.getSupportedPorts()

    test.enablePort(ports[0][0], ports[0][1])
    test.disablePort(ports[0][0], ports[0][1])

    test.terminate()

    shell.close()
