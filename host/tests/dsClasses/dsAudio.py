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

class dsMS12Capabilities(Enum):
    DolbyVolume          = 0x01
    IntelligentEqualizer = 0x02
    DialogueEnhancer     = 0x04
    Volumeleveller       = 0x08
    BassEnhancer         = 0x10
    SurroundDecoder      = 0x20
    DRCMode              = 0x40
    SurroundVirtualizer  = 0x80
    MISteering           = 0x100
    GraphicEqualizer     = 0x200
    LEConfig             = 0x400

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
        result = self.utMenu.select(self.testSuite, "Terminate dsAudio")

    def enablePort(self, audio_port:str, port_index:int=0, arc_type:int=2):
        """
        Enables the audio port.

        Args:
            audio_port (str): audio port
            port_index (int, optional): port index. Defaults to 0
            arc_type (int, optional): Type of ARC. Defaults to eArc.

        Returns:
            None
        """
        promptWithAnswers = [
                {
                    "query_type": "list",
                    "query": "Select dsAudio Port:",
                    "input": audio_port
                },
                {
                    "query_type": "direct",
                    "query": "Select dsAudio Port Index[0-10]:",
                    "input": str(port_index)
                }
        ]

        if audio_port == dsAudioPortType.dsAUDIOPORT_TYPE_HDMI_ARC.name:
            promptWithAnswers.append({
                    "query_type": "direct",
                    "query": "Select ARC Type:",
                    "input": str(arc_type)
                })

        result = self.utMenu.select(self.testSuite, "Enable Audio Port", promptWithAnswers)

    def disablePort(self, audio_port:str, port_index:int=0):
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
                    "input": audio_port
                },
                {
                    "query_type": "direct",
                    "query": "Select dsAudio Port Index[0-10]:",
                    "input": str(port_index)
                }
        ]

        result = self.utMenu.select(self.testSuite, "Disable Audio Port", promptWithAnswers)

    def setGainLevel(self, audio_port:str, port_index:int=0, gainLevel:float=0.0):
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
                    "input": audio_port
                },
                {
                    "query_type": "direct",
                    "query": "Select dsAudio Port Index[0-10]:",
                    "input": str(port_index)
                },
                {
                    "query_type": "direct",
                    "query": "Enter Gain Level[0.0 to 100.0]:",
                    "input": str(gainLevel)
                }
        ]

        result = self.utMenu.select(self.testSuite, "Set Audio Level", promptWithAnswers)

    def setSpeakerGain(self, audio_port:str, port_index:int=0, gain:float=0.0):
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
                    "input": str(gain)
                }
        ]

        result = self.utMenu.select(self.testSuite, "Set Audio Gain For Speaker", promptWithAnswers)

    def setAudioMute(self, audio_port:str, port_index:int=0, mute:bool=True):
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
                    "input": audio_port
                },
                {
                    "query_type": "direct",
                    "query": "Select dsAudio Port Index[0-10]:",
                    "input": str(port_index)
                },
                {
                    "query_type": "direct",
                    "query": "Audio Mute/UnMute[1:Mute, 2:UnMute]:",
                    "input": self.boolToString(mute)
                }
        ]

        result = self.utMenu.select(self.testSuite, "Audio Mute/UnMute", promptWithAnswers)

    def setAudioDelay(self, audio_port:str, port_index:int=0, delay:int=0):
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
                    "input": audio_port
                },
                {
                    "query_type": "direct",
                    "query": "Select dsAudio Port Index[0-10]:",
                    "input": str(port_index)
                },
                {
                    "query_type": "direct",
                    "query": "Enter Audio Delay in milli seconds[0 to 200]:",
                    "input": str(delay)
                }
        ]

        result = self.utMenu.select(self.testSuite, "Set Audio Delay", promptWithAnswers)

    def setAudioCompression(self, audio_port:str, port_index:int=0, compression:int=0):
        """
        Set the audio compression.

        Args:
            audio_port (str): name of the audio port. Refer dsAudioPortType enum
            port_index (int, optional): port index. Defaults to 0
            compression (int, optional): audio compression to be applied. Ranges from 0 to 10. Defaults to 0

        Returns:
            None
        """
        promptWithAnswers = [
                {
                    "query_type": "list",
                    "query": "Select dsAudio Port:",
                    "input": audio_port
                },
                {
                    "query_type": "direct",
                    "query": "Select dsAudio Port Index[0-10]:",
                    "input": str(port_index)
                },
                {
                    "query_type": "direct",
                    "query": "Select Compression[0-10]:",
                    "input": str(compression)
                }
        ]

        result = self.utMenu.select(self.testSuite, "Audio Compression", promptWithAnswers)

    def setMS12Feature(self, audio_port:str, port_index:int=0, feature:dict = None):
        """
        Sets the audio compression.

        Args:
            audio_port (str): Name of the audio port (refer to dsAudioPortType enum).
            port_index (int, optional): Port index. Defaults to 0.
            feature (dict, optional): Dictionary containing the feature to be enabled and its value.
                        Keys should be feature names (e.g., "DolbyVolume", "IntelligentEqualizer" refer: dsMS12Capabilities).
                        Values depend on the feature:
                            - Boolean features: True/False
                            - Single-value features: String or int representing the value
                            - Multi-value features: List containing two values (e.g., [mode, level])
                        Defaults to None.

        Returns:
            None
        """

        if not feature or len(feature) != 2:
            return False  # Handle missing or invalid feature data

        feature_name = feature["name"]
        feature_value = feature["value"]

        promptWithAnswers = [
                {
                    "query_type": "list",
                    "query": "Select dsAudio Port:",
                    "input": str(audio_port)
                },
                {
                    "query_type": "direct",
                    "query": "Select dsAudio Port Index[0-10]:",
                    "input": str(port_index)
                },
                {
                    "query_type": "list",
                    "query": "Select MS12 DAP Feature:",
                    "input": feature_name
                }
        ]

        if(feature_name == "DolbyVolume"):
            promptWithAnswers.append({
                    "query_type": "direct",
                    "query": "Dolby Volume[1:Enable, 2:Disable]:",
                    "input": self.boolToString(feature_value)
                })
        elif(feature_name == "IntelligentEqualizer"):
            promptWithAnswers.append({
                    "query_type": "list",
                    "query": "Select IntelligentEqualizer Mode:",
                    "input": feature_value
                })
        elif(feature_name == "DialogueEnhancer"):
            promptWithAnswers.append({
                    "query_type": "direct",
                    "query": "Select DialogueEnhancer Level[0-16]:",
                    "input": str(feature_value)
                })
        elif(feature_name == "Volumeleveller"):
            promptWithAnswers.append({
                    "query_type": "direct",
                    "query": "Select Volumeleveller Mode[0:Off, 1:On, 2:Auto]:",
                    "input": str(feature_value[0])
                })
            promptWithAnswers.append({
                    "query_type": "direct",
                    "query": "Select Volumeleveller Level[0-10]:",
                    "input": str(feature_value[1])
                })
        elif(feature_name == "BassEnhancer"):
            promptWithAnswers.append({
                    "query_type": "direct",
                    "query": "Select BassEnhancer Boost[0-100]:",
                    "input": str(feature_value)
                })
        elif(feature_name == "SurroundDecoder"):
            promptWithAnswers.append({
                    "query_type": "direct",
                    "query": "Surround Decoder[1:Enable, 2:Disable]:",
                    "input": self.boolToString(feature_value)
                })
        elif(feature_name == "DRCMode"):
            promptWithAnswers.append({
                    "query_type": "direct",
                    "query": "Select DRC Mode[0: DRC Line Mode, 1: DRC RF Mode]:",
                    "input": str(feature_value)
                })
        elif(feature_name == "SurroundVirtualizer"):
            promptWithAnswers.append({
                    "query_type": "direct",
                    "query": "Select SurroundVirtualizer Mode[0:Off, 1:On, 2:Auto]:",
                    "input": str(feature_value[0])
                })
            promptWithAnswers.append({
                    "query_type": "direct",
                    "query": "Select SurroundVirtualizer Boost[0-96]:",
                    "input": str(feature_value[1])
                })
        elif(feature_name == "MISteering"):
            promptWithAnswers.append({
                    "query_type": "direct",
                    "query": "MI Steering[1:Enable, 2:Disable]:",
                    "input": self.boolToString(feature_value)
                })
        elif(feature_name == "GraphicEqualizer"):
            promptWithAnswers.append({
                    "query_type": "direct",
                    "query": "Select GraphicEqualizer Mode[0: OFF, 1: EQ Open, 2: EQ Rich, 3: EQ Focused]:",
                    "input": str(feature_value)
                })
        elif(feature_name == "LEConfig"):
            promptWithAnswers.append({
                    "query_type": "direct",
                    "query": "LE Configuration[1:Enable, 2:Disable]:",
                    "input": self.boolToString(feature_value)
                })
        else:
            return

        result = self.utMenu.select(self.testSuite, "MS12 DAP Features", promptWithAnswers)

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
                    "input": self.boolToString(enable)
                }
        ]

        if enable:
            promptWithAnswers.append({
                    "query_type": "direct",
                    "query": "Set Fader Control[-32(mute associated audio) to 32(mute main audio)]:",
                    "input": str(fader)
                })

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
                    "input": mixer_input
                },
                {
                    "query_type": "direct",
                    "query": "Set the Volume[0 to 100]:",
                    "input": str(volume)
                }
        ]

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
                    "input": language
                }
        ]

        if (language_type == "Primary"):
            promptWithAnswers[0]["input"] = "1"
        else:
            promptWithAnswers[0]["input"] = "2"

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

    def boolToString(self, val:bool):
        if(val):
            return "1"
        else:
            return "2"

    def getSupportedPorts(self):
        """
        Returns a list of supported audio ports on the device.

        Args:
            None

        Returns:
            list: A list of tuples containing the port name and index.
        """

        ports = self.deviceProfile.get("Ports")
        if not ports:
            return []  # Handle empty ports list

        supported_ports = []
        for entry in ports.values():
            supported_ports.append((dsAudioPortType(entry['Typeid']).name, entry['Index']))

        return supported_ports

    def getDeviceType(self):
        """
        Returns the supported audio ports on device.

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

    def getMS12DAPFeatureSupport(self, audio_port: str, port_index: int = 0, feature: str = ""):
        """
        Checks if the specified audio port supports the given MS12 feature.

        Args:
            audio_port (str): The name of the audio port.
            port_index (int, optional): The port index. Defaults to 0.
            feature (str, optional): The MS12 feature to check.

        Returns:
            bool: True if the feature is supported, False otherwise.
        """

        ports = self.deviceProfile.get("Ports")
        if not ports:
            return False  # Handle empty ports list

        for entry in ports.values():
            if (dsAudioPortType(entry['Typeid']).name == audio_port
                and entry['Index'] == port_index
                and entry["MS12_Capabilities"] & dsMS12Capabilities[feature].value):
                return True

        return False

    def getAudioCompressionSupport(self, audio_port: str, port_index: int = 0):
        """
        Checks if the specified audio port supports audio compression.

        Args:
            audio_port (str): The name of the audio port.
            port_index (int, optional): The port index. Defaults to 0.

        Returns:
            bool: True if the port supports audio compression, False otherwise.
        """

        ports = self.deviceProfile.get("Ports")
        if not ports:
            return False  # Handle empty ports list

        for entry in ports.values():
            if (dsAudioPortType(entry['Typeid']).name == audio_port
                and entry['Index'] == port_index
                and entry["number_of_supported_compressions"] > 0 ):
                return True

        return False

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
