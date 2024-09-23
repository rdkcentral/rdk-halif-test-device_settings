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

# Add parent outside of the helper directory
dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(dir_path+"/../")

from raft.framework.plugins.ut_raft.configRead import ConfigRead
from host.tests.raft.framework.plugins.ut_raft.utSuiteNavigator import UTSuiteNavigatorClass
from raft.framework.plugins.ut_raft.interactiveShell import InteractiveShell

class PortType(Enum):
    ID_LR     = 0
    HDMI      = 1
    SPDIF     = 2
    SPEAKER   = 3
    HDMI_ARC  = 4
    HEADPHONE = 5

class dsAudioClass():

    """
    Device Settings Audio Class

    This module provides common extensions for device Settings Audio Module.
    """
    def __init__(self, profile:str, session:object=None ):
        """
        Initializes the dsAudio class function.
        """
        suiteConfig="./dsAudio_test_suite.yaml"
        self.profile = ConfigRead( profile, "dsAudio:" )
        testSuite="L3 dsAudio"
        script_directory = os.path.dirname(os.path.abspath(__file__)) + suiteConfig
        self.utMenu = UTSuiteNavigatorClass(script_directory, "dsAudio:", session)
        self.utMenu.start()

    def initialise(self):
        """
        Initializes the device settings Audio module.

        Args:
            None.

        Returns:
            None
        """
        self.utMenu.select(self.testSuite,"test_initialise_audio")

    def enablePort(self, audio_port:str):
        """
        Enables the audio port.

        Args:
            audio_port (str): name of the audio port. Refer dsAudioPortType enum

        Returns:
            None
        """
        if audio_port > self.profile.PortTypes:
            self.log.error("Port Issue")

        # Validate the video 
        self.utMenu.select(self.testSuite, "test_enable_audio_port", audio_port)

    def disablePort(self, audio_port):
        """
        Enables the audio port.

        Args:
            audio_port (str): name of the audio port. Refer dsAudioPortType enum

        Returns:
            None
        """
        self.utMenu.select(self.testSuite, "test_disable_audio_port", audio_port)

    def terminate(self):
        """
        Enables the audio port.

        Args:
            None.

        Returns:
            None
        """
        self.utMenu.select(self.testSuite, "test_terminate_audio")

    def getSupportedPorts(self):
        """
        Returns the supported audio ports on device.

        Args:
            None.

        Returns:
            returns the list of supported audio ports
        """
        #TODO: Unclear if this is correct for this function, but I would expand the return to be specific about what is returned.
        #      You may want to translate it into something simplier for the caller depending on usage.
        portsTypes = self.profile.PortTypes
        return portsTypes

    def __del__(self):
        """
        De-Initializes the dsAudio helper function.

        Args:
            None.

        Returns:
            None
        """
        self.dsAudioTerminate()

# Test and example usage code
if __name__ == '__main__':
    platformProfile="""
    dsAudio:
        Type: sink
        Name: dsAudio_4_port

        # Profile for L1
        features:
            extendedEnumsSupported: false

        # dsAUDIOPORT_TYPE_ID_LR       = 0x00,  ///< RCA audio output
        # dsAUDIOPORT_TYPE_HDMI        = 0x01,  ///< HDMI audio output
        # dsAUDIOPORT_TYPE_SPDIF       = 0x02,  ///< SPDIF audio output
        # dsAUDIOPORT_TYPE_SPEAKER     = 0x03,  ///< SPEAKER audio output
        # dsAUDIOPORT_TYPE_HDMI_ARC    = 0x04,  ///< HDMI ARC/EARC audio output
        # dsAUDIOPORT_TYPE_HEADPHONE   = 0x05,  ///< Headphone jack
        # dsAUDIOPORT_TYPE_MAX         = 0x06   ///< Out of range
        PortTypes:
        - 0x02 #SPDIF
        - 0x03 #SPEAKER
        - 0x04 #HDMI_ARC
        - 0x05 #HEADPHONE

        # Number of supported ports
        Number_of_supported_ports: 4

        # dsAUDIOSUPPORT_NONE             = 0x0,     ///< None
        # dsAUDIOSUPPORT_ATMOS            = 0x01,    ///< Dolby Atmos
        # dsAUDIOSUPPORT_DD               = 0x02,    ///< Dolby Digitial
        # dsAUDIOSUPPORT_DDPLUS           = 0x04,    ///< Dolby Digital Plus
        # dsAUDIOSUPPORT_DAD              = 0x08,    ///< Digital Audio Delivery
        # dsAUDIOSUPPORT_DAPv2            = 0x10,    ///< Digital Audio Processing version 2
        # dsAUDIOSUPPORT_MS12             = 0x20,    ///< Multi Stream 12
        # dsAUDIOSUPPORT_MS12V2           = 0x40,    ///< Multi Stream Version 2
        # dsAUDIOSUPPORT_Invalid          = 0x80,    ///< Invalid
        Audio_Capabilities: 0x37  # dsAUDIOSUPPORT_ATMOS | dsAUDIOSUPPORT_DAPv2 | dsAUDIOSUPPORT_MS12 | dsAUDIOSUPPORT_DD | dsAUDIOSUPPORT_DDPLUS

        # Port details
        Ports:
            # Port Number to parse the port details
            1:
                # dsAUDIOPORT_TYPE_ID_LR       = 0x00,  ///< RCA audio output
                # dsAUDIOPORT_TYPE_HDMI        = 0x01,  ///< HDMI audio output
                # dsAUDIOPORT_TYPE_SPDIF       = 0x02,  ///< SPDIF audio output
                # dsAUDIOPORT_TYPE_SPEAKER     = 0x03,  ///< SPEAKER audio output
                # dsAUDIOPORT_TYPE_HDMI_ARC    = 0x04,  ///< HDMI ARC/EARC audio output
                # dsAUDIOPORT_TYPE_HEADPHONE   = 0x05,  ///< Headphone jack
                # dsAUDIOPORT_TYPE_MAX         = 0x06   ///< Out of range
                Typeid: 0x03  # SPEAKER
                # SPEAKER
                # HDMI_ARC
                # SPDIF
                # HEADPHONE
                Name: "SPEAKER"
                # An index value used to access a specific port within an array of ports with the same type.
                Index: 0
                # Number of Supported Compressions
                number_of_supported_compressions: 4
                # dsAUDIO_CMP_NONE   = 0x00,  ///< No audio compression.
                # dsAUDIO_CMP_LIGHT  = 0x01,  ///< Light audio level compression.
                # dsAUDIO_CMP_MEDIUM = 0x02,  ///< Medium audio level compression.
                # dsAUDIO_CMP_HEAVY  = 0x03,  ///< Heavy audio level compression.
                # dsAUDIO_CMP_MAX    = 0x04   ///< Out of range
                compressions: [0x00, 0x01, 0x02, 0x03]  # NONE, LIGHT, MEDIUM, HEAVY
                # Number of supported Stereo modes
                number_of_supported_stereo_modes: 1
                # dsAUDIO_STEREO_UNKNOWN                   = 0x00, ///< Stereo mode none
                # dsAUDIO_STEREO_MONO                      = 0x01, ///< Mono mode
                # dsAUDIO_STEREO_STEREO                    = 0x02, ///< Normal stereo mode (L+R)
                # dsAUDIO_STEREO_SURROUND                  = 0x03, ///< Surround mode
                # dsAUDIO_STEREO_PASSTHRU                  = 0x04, ///< Passthrough mode
                # dsAUDIO_STEREO_DD                        = 0x05, ///< Dolby Digital
                # dsAUDIO_STEREO_DDPLUS                    = 0x06, ///< Dolby Digital Plus
                # dsAUDIO_STEREO_MAX                       = 0x07  ///< Out of range
                stereo_modes: [0x2]  # STEREO, SURROUND
                stereo_auto_mode: false
                # dsMS12SUPPORT_NONE                       = 0x0,   ///< MS12 Supported None
                # dsMS12SUPPORT_DolbyVolume                = 0x01,  //< MS12 supported Dolby Volume
                # dsMS12SUPPORT_InteligentEqualizer        = 0x02,  ///< MS12 supported Intelligent Equalizer
                # dsMS12SUPPORT_DialogueEnhancer           = 0x04,  ///< MS12 Dialogue Enhancer supported
                # dsMS12SUPPORT_Volumeleveller             = 0x08,  ///< MS12 Volume leveller
                # dsMS12SUPPORT_BassEnhancer               = 0x10,  ///< MS12 Bass Enhancer
                # dsMS12SUPPORT_SurroundDecoder            = 0x20,  ///< MS12 Surround Decoder
                # dsMS12SUPPORT_DRCMode                    = 0x40,  ///< MS12 DRC Mode
                # dsMS12SUPPORT_SurroundVirtualizer        = 0x80,  ///< MS12 Surround Virtualizer
                # dsMS12SUPPORT_MISteering                 = 0x100, ///< MS12 MI Steering
                # dsMS12SUPPORT_GraphicEqualizer           = 0x200, ///< MS12 Graphic equalizer
                # dsMS12SUPPORT_LEConfig                   = 0x400, ///< MS12 LE config
                # dsMS12SUPPORT_Invalid                    = 0x800  ///< Invalid / Out of range
                MS12_Capabilities: 0x07  # DolbyVolume | IntelligentEqualizer | DialogueEnhancer
                # profile names from the "ms12_audio_profiles.ini" file.
                MS12_AudioProfiles:
                - Off
                - Music
                - Movie
                - Sports
                - Entertainment
                - Night
                - Party
                - User
                # number of counts from the "ms12_audio_profiles.ini" file
                MS12_AudioProfileCount: 8
                # @a true if audio port supports Dolby MS12 Multistream Decoding or @a false otherwise
                IsMS12Decode: true
                # @a true if audio port supports Dolby MS11 Multistream Decoding or @a false otherwise
                IsMS11Decode: true
                # dsAUDIO_ATMOS_NOTSUPPORTED               = 0x00, ///< ATMOS audio not supported
                # dsAUDIO_ATMOS_DDPLUSSTREAM               = 0x01, ///< can handle dd plus stream which is only way to pass ATMOS metadata
                # dsAUDIO_ATMOS_ATMOSMETADATA              = 0x02, ///< capable of parsing ATMOS metadata
                # dsAUDIO_ATMOS_MAX                        = 0x03  ///< Out of range
                ATMOS_Capabilities: 0x02  # ATMOSMETADATA

            # Port Number to parse the port details
            2:
                # dsAUDIOPORT_TYPE_ID_LR       = 0x00,       ///< RCA audio output
                # dsAUDIOPORT_TYPE_HDMI        = 0x01,       ///< HDMI audio output
                # dsAUDIOPORT_TYPE_SPDIF       = 0x02,       ///< SPDIF audio output
                # dsAUDIOPORT_TYPE_SPEAKER     = 0x03,       ///< SPEAKER audio output
                # dsAUDIOPORT_TYPE_HDMI_ARC    = 0x04,       ///< HDMI ARC/EARC audio output
                # dsAUDIOPORT_TYPE_HEADPHONE   = 0x05,       ///< Headphone jack
                # dsAUDIOPORT_TYPE_MAX         = 0x06        ///< Out of range
                Typeid: 0x04  # HDMI_ARC
                # SPEAKER
                # HDMI_ARC
                # SPDIF
                # HEADPHONE
                Name: "HDMI_ARC"
                # An index value used to access a specific port within an array of ports with the same type.
                Index: 0
                # number of supported compressions
                number_of_supported_compressions: 0
                # dsAUDIO_CMP_NONE   = 0x00, ///< No audio compression.
                # dsAUDIO_CMP_LIGHT  = 0x01, ///< Light audio level compression.
                # dsAUDIO_CMP_MEDIUM = 0x02, ///< Medium audio level compression.
                # dsAUDIO_CMP_HEAVY  = 0x03, ///< Heavy audio level compression.
                # dsAUDIO_CMP_MAX    = 0x04  ///< Out of range
                compressions:
                # Number of supported Stereo modes
                number_of_supported_stereo_modes: 3
                # dsAUDIO_STEREO_UNKNOWN                   = 0x00,  ///< Stereo mode none
                # dsAUDIO_STEREO_MONO                      = 0x01,  ///< Mono mode
                # dsAUDIO_STEREO_STEREO                    = 0x02,  ///< Normal stereo mode (L+R)
                # dsAUDIO_STEREO_SURROUND                  = 0x03,  ///< Surround mode
                # dsAUDIO_STEREO_PASSTHRU                  = 0x04,  ///< Passthrough mode
                # dsAUDIO_STEREO_DD                        = 0x05,  ///< Dolby Digital
                # dsAUDIO_STEREO_DDPLUS                    = 0x06,  ///< Dolby Digital Plus
                # dsAUDIO_STEREO_MAX                       = 0x07   ///< Out of range
                stereo_modes: [0x02, 0x03, 0x04]  # STEREO, SURROUND, PASSTHRU
                stereo_auto_mode: true
                # dsMS12SUPPORT_NONE                       = 0x0,   ///< MS12 Supported None
                # dsMS12SUPPORT_DolbyVolume                = 0x01,  //< MS12 supported Dolby Volume
                # dsMS12SUPPORT_InteligentEqualizer        = 0x02,  ///< MS12 supported Intelligent Equalizer
                # dsMS12SUPPORT_DialogueEnhancer           = 0x04,  ///< MS12 Dialogue Enhancer supported
                # dsMS12SUPPORT_Volumeleveller             = 0x08,  ///< MS12 Volume leveller
                # dsMS12SUPPORT_BassEnhancer               = 0x10,  ///< MS12 Bass Enhancer
                # dsMS12SUPPORT_SurroundDecoder            = 0x20,  ///< MS12 Surround Decoder
                # dsMS12SUPPORT_DRCMode                    = 0x40,  ///< MS12 DRC Mode
                # dsMS12SUPPORT_SurroundVirtualizer        = 0x80,  ///< MS12 Surround Virtualizer
                # dsMS12SUPPORT_MISteering                 = 0x100, ///< MS12 MI Steering
                # dsMS12SUPPORT_GraphicEqualizer           = 0x200, ///< MS12 Graphic equalizer
                # dsMS12SUPPORT_LEConfig                   = 0x400, ///< MS12 LE config
                # dsMS12SUPPORT_Invalid                    = 0x800  ///< Invalid / Out of range
                MS12_Capabilities: 0x00  # dsMS12SUPPORT_NONE
                MS12_AudioProfiles:
                # number of counts from the "ms12_audio_profiles.ini" file
                MS12_AudioProfileCount: 0
                # @a true if audio port supports Dolby MS12 Multistream Decoding or @a false otherwise
                IsMS12Decode: false
                # @a true if audio port supports Dolby MS11 Multistream Decoding or @a false otherwise
                IsMS11Decode: false
                # dsAUDIO_ATMOS_NOTSUPPORTED               = 0x00,  ///< ATMOS audio not supported
                # dsAUDIO_ATMOS_DDPLUSSTREAM               = 0x01,  ///< can handle dd plus stream which is only way to pass ATMOS metadata
                # dsAUDIO_ATMOS_ATMOSMETADATA              = 0x02,  ///< capable of parsing ATMOS metadata
                # dsAUDIO_ATMOS_MAX                        = 0x03   ///< Out of range
                ATMOS_Capabilities: 0x00  # ATMOSMETADATA
                # dsAUDIOARCSUPPORT_NONE                   = 0x0,   ///< None
                # dsAUDIOARCSUPPORT_ARC                    = 0x01,  ///< Audio Return Channel
                # dsAUDIOARCSUPPORT_eARC                   = 0x02,  ///< Enhanced Audio Return Channel
                Arc_Types: 0x01 # dsAUDIOARCSUPPORT_ARC

            # Port Number to parse the port details
            3:
                # dsAUDIOPORT_TYPE_ID_LR       = 0x00,      ///< RCA audio output
                # dsAUDIOPORT_TYPE_HDMI        = 0x01,      ///< HDMI audio output
                # dsAUDIOPORT_TYPE_SPDIF       = 0x02,      ///< SPDIF audio output
                # dsAUDIOPORT_TYPE_SPEAKER     = 0x03,      ///< SPEAKER audio output
                # dsAUDIOPORT_TYPE_HDMI_ARC    = 0x04,      ///< HDMI ARC/EARC audio output
                # dsAUDIOPORT_TYPE_HEADPHONE   = 0x05,      ///< Headphone jack
                # dsAUDIOPORT_TYPE_MAX         = 0x06       ///< Out of range
                Typeid: 0x02  # SPDIF
                # SPEAKER
                # HDMI_ARC
                # SPDIF
                # HEADPHONE
                Name: "SPDIF"
                # An index value used to access a specific port within an array of ports with the same type.
                Index: 0
                #Number of supported compressions
                number_of_supported_compressions: 0
                #dsAUDIO_CMP_NONE     = 0x00,  ///< No audio compression.
                #dsAUDIO_CMP_LIGHT    = 0x01,  ///< Light audio level compression.
                #dsAUDIO_CMP_MEDIUM   = 0x02,  ///< Medium audio level compression.
                #dsAUDIO_CMP_HEAVY    = 0x03,  ///< Heavy audio level compression.
                #dsAUDIO_CMP_MAX      = 0x04   ///< Out of range
                compressions:
                #number of supported stereo modes
                number_of_supported_stereo_modes: 3
                #dsAUDIO_STEREO_UNKNOWN                   = 0x00,   ///< Stereo mode none
                #dsAUDIO_STEREO_MONO                      = 0x01,   ///< Mono mode
                #dsAUDIO_STEREO_STEREO                    = 0x02,   ///< Normal stereo mode (L+R)
                #dsAUDIO_STEREO_SURROUND                  = 0x03,   ///< Surround mode
                #dsAUDIO_STEREO_PASSTHRU                  = 0x04,   ///< Passthrough mode
                #dsAUDIO_STEREO_DD                        = 0x05,   ///< Dolby Digital
                #dsAUDIO_STEREO_DDPLUS                    = 0x06,   ///< Dolby Digital Plus
                #dsAUDIO_STEREO_MAX                       = 0x07    ///< Out of range
                stereo_modes: [0x02, 0x03, 0x04]  # STEREO, SURROUND, PASSTHRU
                stereo_auto_mode: true
                # dsMS12SUPPORT_NONE                       = 0x0,   ///< MS12 Supported None
                # dsMS12SUPPORT_DolbyVolume                = 0x01,  //< MS12 supported Dolby Volume
                # dsMS12SUPPORT_InteligentEqualizer        = 0x02,  ///< MS12 supported Intelligent Equalizer
                # dsMS12SUPPORT_DialogueEnhancer           = 0x04,  ///< MS12 Dialogue Enhancer supported
                # dsMS12SUPPORT_Volumeleveller             = 0x08,  ///< MS12 Volume leveller
                # dsMS12SUPPORT_BassEnhancer               = 0x10,  ///< MS12 Bass Enhancer
                # dsMS12SUPPORT_SurroundDecoder            = 0x20,  ///< MS12 Surround Decoder
                # dsMS12SUPPORT_DRCMode                    = 0x40,  ///< MS12 DRC Mode
                # dsMS12SUPPORT_SurroundVirtualizer        = 0x80,  ///< MS12 Surround Virtualizer
                # dsMS12SUPPORT_MISteering                 = 0x100, ///< MS12 MI Steering
                # dsMS12SUPPORT_GraphicEqualizer           = 0x200, ///< MS12 Graphic equalizer
                # dsMS12SUPPORT_LEConfig                   = 0x400, ///< MS12 LE config
                # dsMS12SUPPORT_Invalid                    = 0x800  ///< Invalid / Out of range
                MS12_Capabilities: 0x00  # dsMS12SUPPORT_NONE
                MS12_AudioProfiles:
                # number of counts from the "ms12_audio_profiles.ini" file
                MS12_AudioProfileCount: 0
                # @a true if audio port supports Dolby MS12 Multistream Decoding or @a false otherwise
                IsMS12Decode: false
                # @a true if audio port supports Dolby MS11 Multistream Decoding or @a false otherwise
                IsMS11Decode: true
                # dsAUDIO_ATMOS_NOTSUPPORTED               = 0x00,  ///< ATMOS audio not supported
                # dsAUDIO_ATMOS_DDPLUSSTREAM               = 0x01,  ///< can handle dd plus stream which is only way to pass ATMOS metadata
                # dsAUDIO_ATMOS_ATMOSMETADATA              = 0x02,  ///< capable of parsing ATMOS metadata
                # dsAUDIO_ATMOS_MAX                        = 0x03   ///< Out of range
                ATMOS_Capabilities: 0  # dsAUDIO_ATMOS_NOTSUPPORTED

            # Port Number to parse the port details
            4:
                #dsAUDIOPORT_TYPE_ID_LR       = 0x00,      ///< RCA audio output
                #dsAUDIOPORT_TYPE_HDMI        = 0x01,      ///< HDMI audio output
                #dsAUDIOPORT_TYPE_SPDIF       = 0x02,      ///< SPDIF audio output
                #dsAUDIOPORT_TYPE_SPEAKER     = 0x03,      ///< SPEAKER audio output
                #dsAUDIOPORT_TYPE_HDMI_ARC    = 0x04,      ///< HDMI ARC/EARC audio output
                #dsAUDIOPORT_TYPE_HEADPHONE   = 0x05,      ///< Headphone jack
                #dsAUDIOPORT_TYPE_MAX         = 0x06       ///< Out of range
                Typeid: 0x05  # HEADPHONE
                # SPEAKER
                # HDMI_ARC
                # SPDIF
                # HEADPHONE
                Name: "HEADPHONE"
                # An index value used to access a specific port within an array of ports with the same type.
                Index: 0
                #Number of supported compressions
                number_of_supported_compressions: 0
                #dsAUDIO_CMP_NONE   = 0x00,  ///< No audio compression.
                #dsAUDIO_CMP_LIGHT  = 0x01,  ///< Light audio level compression.
                #dsAUDIO_CMP_MEDIUM = 0x02,  ///< Medium audio level compression.
                #dsAUDIO_CMP_HEAVY  = 0x03,  ///< Heavy audio level compression.
                #dsAUDIO_CMP_MAX    = 0x04   ///< Out of range
                compressions:
                #Number of Supported stereo modes
                number_of_supported_stereo_modes: 0
                #dsAUDIO_STEREO_UNKNOWN                   = 0x00,   ///< Stereo mode none
                #dsAUDIO_STEREO_MONO                      = 0x01,   ///< Mono mode
                #dsAUDIO_STEREO_STEREO                    = 0x02,   ///< Normal stereo mode (L+R)
                #dsAUDIO_STEREO_SURROUND                  = 0x03,   ///< Surround mode
                #dsAUDIO_STEREO_PASSTHRU                  = 0x04,   ///< Passthrough mode
                #dsAUDIO_STEREO_DD                        = 0x05,   ///< Dolby Digital
                #dsAUDIO_STEREO_DDPLUS                    = 0x06,   ///< Dolby Digital Plus
                #dsAUDIO_STEREO_MAX                       = 0x07    ///< Out of range
                stereo_modes:
                stereo_auto_mode: false
                # dsMS12SUPPORT_NONE                       = 0x0,   ///< MS12 Supported None
                # dsMS12SUPPORT_DolbyVolume                = 0x01,  //< MS12 supported Dolby Volume
                # dsMS12SUPPORT_InteligentEqualizer        = 0x02,  ///< MS12 supported Intelligent Equalizer
                # dsMS12SUPPORT_DialogueEnhancer           = 0x04,  ///< MS12 Dialogue Enhancer supported
                # dsMS12SUPPORT_Volumeleveller             = 0x08,  ///< MS12 Volume leveller
                # dsMS12SUPPORT_BassEnhancer               = 0x10,  ///< MS12 Bass Enhancer
                # dsMS12SUPPORT_SurroundDecoder            = 0x20,  ///< MS12 Surround Decoder
                # dsMS12SUPPORT_DRCMode                    = 0x40,  ///< MS12 DRC Mode
                # dsMS12SUPPORT_SurroundVirtualizer        = 0x80,  ///< MS12 Surround Virtualizer
                # dsMS12SUPPORT_MISteering                 = 0x100, ///< MS12 MI Steering
                # dsMS12SUPPORT_GraphicEqualizer           = 0x200, ///< MS12 Graphic equalizer
                # dsMS12SUPPORT_LEConfig                   = 0x400, ///< MS12 LE config
                # dsMS12SUPPORT_Invalid                    = 0x800  ///< Invalid / Out of range
                MS12_Capabilities: 0x00  # dsMS12SUPPORT_NONE
                MS12_AudioProfiles:
                # number of counts from the "ms12_audio_profiles.ini" file
                MS12_AudioProfileCount: 0
                # @a true if audio port supports Dolby MS12 Multistream Decoding or @a false otherwise
                IsMS12Decode: false
                # @a true if audio port supports Dolby MS11 Multistream Decoding or @a false otherwise
                IsMS11Decode: false
                # dsAUDIO_ATMOS_NOTSUPPORTED               = 0x00,  ///< ATMOS audio not supported
                # dsAUDIO_ATMOS_DDPLUSSTREAM               = 0x01,  ///< can handle dd plus stream which is only way to pass ATMOS metadata
                # dsAUDIO_ATMOS_ATMOSMETADATA              = 0x02,  ///< capable of parsing ATMOS metadata
                # dsAUDIO_ATMOS_MAX                        = 0x03   ///< Out of range
                ATMOS_Capabilities: 0  # dsAUDIO_ATMOS_NOTSUPPORTED
        """
    shell = InteractiveShell()
    shell.open()

    # test the class assuming that it's optional
    audio = dsAudioClass(platformProfile, shell)
    audio.initialise()
    audio.enablePort("dsAUDIOPORT_TYPE_SPEAKER")
    audio.disablePort("dsAUDIOPORT_TYPE_SPEAKER")
    ports = audio.getSupportedPorts()
    print(ports)
    audio.Terminate()

    shell.close()
