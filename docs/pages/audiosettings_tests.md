# Audio Settings High Level Test Specification Document

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Introduction](#introduction)
- [Module Description](#module-description)
- [Testing Scope](#testing-scope)

## Acronyms, Terms and Abbreviations

- `HAL`    - Hardware Abstraction Layer
- `API`    - Application Programming Interface
- `L2`     - Level 2 Testing
- `L3`     - Level 3 Testing
- `NA`     - Not Applicable
- `Y`      - Yes
- `DS`     - Device Settings
- `Caller` - Any user of the interface via the `APIs`
- `CB`     - Call-back function (suffix)
- `ARC`    - Audio Return Channel
- `eARC`   - Enhanced Audio Return Channel
- `SAD`    - Short Audio Descriptor
- `SPDIF`  - Sony/Philips Digital Interface
- `HDMI`   - High-Definition Multimedia Interface
- `LE`     - Loudness Equivalence
- `DRC`    - Dynamic Range Control
- `MI`     - Media Intelligent
- `MS12`   - MultiStream 12
- `PCM`    - Pulse Code Modulation
- `AC3`    - Audio Codec 3
- `EAC3`   - Enhanced `AC3`
- `WMA`    - Windows Media Audio
- `AAC`    - Advanced Audio coding
- `DD`     - DOLBY Digital
- `DDPLUS` - DOLBY Digital Plus
- `DAP`    - Digital Audio Processing

## Introduction

This document provides an overview of the testing requirements for the Audio Settings module. It outlines the scope of testing, objectives, testing levels and approaches, specific test requirements, and expected deliverables.

- Interface of the test is available here - [Audio Settings HAL header](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsAudio.h)
- `HAL` specification in this link - [Audio Settings HAL Specification](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/docs/pages/ds-audio_halSpec.md)

## Module Description

The Audio device setting interface provides control to enable or disable Audio Output ports like TV Internal Speakers, `ARC`/`eARC`, Headphones, `SPDIF` and allows `caller` to configure or retrieve various audio parameters like `MS12` `DAP` Capabilities, `MS12` audio profile, stereo mode, audio gain, audio delay, fader control, primary language and secondary language.

## Testing Scope

|#|Test Functionality|Description|
|-|------------------|-----------|
|01|[Test Audio Port](#test-audio-port)|Test for audio port configuration|
|02|[Test MS12 `DAP` Capabilities](#test-ms12-dap-capabilities)|Test for MS12 `DAP` capabilities like compression, dialogue enhancement, volume mode, intelligent equalizer, bass enhancer Surround decode, `DRC` mode, Surround Virtualizer, `MI` Steering, Graphic equalizer, `LE` configuration|
|03|[Test MS12 Capabilities](#test-ms12-capabilities)|Test for MS12 capabilities|
|04|[Test `ARC` Support - Sink Device](#test-arc-support---sink-device)|Test for `ARC` Ports|
|05|[Test Stereo Mode Support](#test-stereo-mode-support)|Test for Stereo mode configurations|
|06|[Test Audio Gain and Mute](#test-audio-gain-and-mute)|Test for audio gain level configurations and mute functionality|
|07|[Test Audio Delay](#test-audio-delay)|Test for audio delay configuration|
|08|[Test Atmos Mode](#test-atmos-mode)|Test for audio atmos capabilities|
|09|[Test Audio Format](#test-audio-format)|Test for Audio Formats|
|10|[Test Associated Audio Mixing](#test-associated-audio-mixing)|Test for Associated Audio Mixing|
|11|[Test Primary/Secondary Language](#test-primarysecondary-language)|Test for primary/secondary language configuration|
|12|[Test Audio Mixer Levels](#test-audio-mixer-levels)|Test for primary/secondary language configuration|

## Emulator Requirements

Boot configuration: Various Audio ports, audio formats, Stereo modes and `Ms12` features supported by device

- Supported Audio Ports - [dsAudioPortType_t](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsAVDTypes.h#L201)
- Supported Audio Encoding Formats - [dsAudioEncoding_t](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsAVDTypes.h#L222)
- Supported Stereo Modes - [dsSetStereoMode](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsAVDTypes.h#L376)
- Supported Audio Compression - [dsAudioCompression_t](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsAVDTypes.h#L234)
- Supported `MS12` `DAP` Capabilities - [dsMS12Capabilities_t](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsAVDTypes.h#L335)
- Supported `MS12` Profiles - [dsMS12AudioProfileList_t](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsAVDTypes.h#L345)
- Supported `ARC` Types - [dsAudioARCTypes_t](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsAVDTypes.h#L304)

## Test Audio Port

|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|-----------|--------|--|--|------|----|--------------------------|
|Loop through supported audio ports, Enable/disable audio ports and retrieve status for verification|dsGetAudioPort(), dsEnableAudioPort(), dsIsAudioPortEnabled()|`Y`|`NA`|`Y`|`Y`|`NA`|
|Loop through supported audio ports, Enable/disable audio ports and verify using external analyzer with stream playback|dsGetAudioPort(), dsEnableAudioPort()|`NA`|`Y`|`Y`|`Y`|`Y`|
|Loop through supported audio ports, Check the connection status. For Sink devices, dsAUDIOPORT_TYPE_SPEAKER(internal speaker) connection status should be true always and other ports connection status should be false. For Source devices the connection status is always false for all ports|dsGetAudioPort(), dsAudioOutIsConnected()|`Y`|`NA`|`Y`|`Y`|`NA`|
|Loop through supported audio ports, Check the connection status by connecting/disconnecting the port. For Sink devices, dsAUDIOPORT_TYPE_SPEAKER (internal speaker) connection status should be true always|dsGetAudioPort(), dsAudioOutIsConnected()|`NA`|`Y`|`Y`|`Y`|`Y`|
|Select dsAUDIOPORT_TYPE_HEADPHONE port, Check the connection status with call-back function by connecting/disconnecting the port|dsGetAudioPort(), dsAudioOutRegisterConnectCB()|`NA`|`Y`|`NA`|`Y`|`Y`|

### Test Startup Requirement - Test Audio Port

Playback of stream is required for the L3 testcases

### Emulator Requirements - Test Audio Port

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Test Audio Port

- Control the external analyzer
- Control the port connections

## Test MS12 `DAP` Capabilities

|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|-----------|--------|--|--|------|----|--------------------------|
|Get supported `MS12` `DAP` capabilities of device and verify with configuration file|dsGetAudioPort(), dsGetMS12Capabilities()|`Y`|`NA`|`Y`|`Y`|`NA`|
|Loop through supported audio ports, Set various compression levels for supported ports and retrieve compression levels for verification|dsGetAudioPort(), dsSetAudioCompression(), dsGetAudioCompression()|`Y`|`NA`|`Y`|`Y`|`NA`|
|Test various compression levels with stream playback. Loop through supported audio ports, Set various compression levels for supported ports and verify with external analyzer|dsGetAudioPort(), dsSetAudioCompression()|`NA`|`Y`|`Y`|`Y`|`Y`|
|Loop through supported audio ports, Set Dialog Enhancement for supported ports and retrieve Dialog Enhancement for verification|dsGetAudioPort(), dsSetDialogEnhancement(), dsGetDialogEnhancement()|`Y`|`NA`|`Y`|`Y`|`NA`|
|Test Dialog Enhancement for supported ports with stream playback. Loop through supported audio ports, Set Dialog Enhancement for supported ports and verify with external analyzer|dsGetAudioPort(), dsSetDialogEnhancement()|`NA`|`Y`|`Y`|`Y`|`Y`|
|Loop through supported audio ports, Set DOLBY Volume Mode for supported ports and retrieve DOLBY Volume Mode for verification|dsGetAudioPort(), dsSetDolbyVolumeMode(), dsGetDolbyVolumeMode()|`Y`|`NA`|`Y`|`Y`|`NA`|
|Test DOLBY Volume Mode for supported ports with stream playback. Loop through supported audio ports, Set DOLBY Volume Mode for supported ports and verify with external analyzer|dsGetAudioPort(), dsSetDolbyVolumeMode()|`NA`|`Y`|`Y`|`Y`|`Y`|
|Loop through supported audio ports, Set Intelligent Equalizer Mode for supported ports and retrieve Intelligent Equalizer Mode for verification|dsGetAudioPort(), dsSetIntelligentEqualizerMode(), dsGetIntelligentEqualizerMode()|`Y`|`NA`|`Y`|`Y`|`NA`|
|Test Intelligent Equalizer Mode with stream playback. Loop through supported audio ports, Set Intelligent Equalizer Mode for supported ports and verify with external analyzer|dsGetAudioPort(), dsSetIntelligentEqualizerMode()|`NA`|`Y`|`Y`|`Y`|`Y`|
|Loop through supported audio ports, Set Volume leveller for supported ports and retrieve Volume leveller for verification|dsGetAudioPort(), dsSetVolumeLeveller(), dsGetVolumeLeveller()|`Y`|`NA`|`Y`|`Y`|`NA`|
|Test Volume leveller for supported ports with stream playback. Loop through supported audio ports, Set Volume leveller for supported ports and verify with external analyzer|dsGetAudioPort(), dsSetVolumeLeveller()|`NA`|`Y`|`Y`|`Y`|`Y`|
|Loop through supported audio ports, Set Bass Enhancer for supported ports and retrieve Bass Enhancer for verification|dsGetAudioPort(), dsSetBassEnhancer(), dsGetBassEnhancer()|`Y`|`NA`|`Y`|`Y`|`NA`|
|Test Bass Enhancer for supported ports with stream playback. Loop through supported audio ports, Set Bass Enhancer for supported ports and verify with external analyzer|dsGetAudioPort(), dsSetBassEnhancer()|`NA`|`Y`|`Y`|`Y`|`Y`|
|Loop through supported audio ports, Enable Surround Decoder for supported ports and retrieve Surround Decoder status for verification|dsGetAudioPort(), dsEnableSurroundDecoder(), dsIsSurroundDecoderEnabled()|`Y`|`NA`|`Y`|`Y`|`NA`|
|Test Surround Decoder for supported ports with stream playback. Loop through supported audio ports, Set Bass Enhancer for supported ports and verify with external analyzer|dsGetAudioPort(), dsEnableSurroundDecoder()|`NA`|`Y`|`Y`|`Y`|`Y`|
|Loop through supported audio ports, Set `DRC` Mode for supported ports and retrieve `DRC` Mode for verification|dsGetAudioPort(), dsSetDRCMode(), dsGetDRCMode()|`Y`|`NA`|`Y`|`Y`|`NA`|
|Test `DRC` Mode for supported ports with stream playback. Loop through supported audio ports, Set `DRC` Mode for supported ports and verify with external analyzer|dsGetAudioPort(), dsSetDRCMode()|`NA`|`Y`|`Y`|`Y`|`Y`|
|Loop through supported audio ports, Set Surround Virtualizer for supported ports and retrieve Surround Virtualizer for verification|dsGetAudioPort(), dsSetSurroundVirtualizer(), dsGetSurroundVirtualizer()|`Y`|`NA`|`Y`|`Y`|`NA`|
|Test Surround Virtualizer for supported ports with stream playback. Loop through supported audio ports, Set Surround Virtualizer for supported ports and verify with external analyzer|dsGetAudioPort(), dsSetSurroundVirtualizer()|`NA`|`Y`|`Y`|`Y`|`Y`|
|Loop through supported audio ports, Set `MI` Steering for supported ports and retrieve `MI` Steering for verification|dsGetAudioPort(), dsSetMISteering(), dsGetMISteering()|`Y`|`NA`|`Y`|`Y`|`NA`|
|Test `MI` Steering for supported ports with stream playback. Loop through supported audio ports, Set `MI` Steering for supported ports and verify with external analyzer|dsGetAudioPort(), dsSetMISteering()|`NA`|`Y`|`Y`|`Y`|`Y`|
|Loop through supported audio ports, Set Graphic Equalizer for supported ports and retrieve Graphic Equalizer for verification|dsGetAudioPort(), dsSetGraphicEqualizerMode(), dsGetGraphicEqualizerMode()|`Y`|`NA`|`Y`|`Y`|`NA`|
|Test Graphic Equalizer for supported ports with stream playback. Loop through supported audio ports, Set Graphic Equalizer for supported ports and verify with external analyzer|dsGetAudioPort(), dsSetGraphicEqualizerMode()|`NA`|`Y`|`Y`|`Y`|`Y`|
|Loop through supported audio ports, Enable/disable audio loudness equivalence and retrieve audio loudness equivalence status for verification|dsGetAudioPort(), dsEnableLEConfig(), dsGetLEConfig()|`Y`|`NA`|`Y`|`Y`|`NA`|
|Test audio loudness equivalence for supported ports with stream playback. Loop through supported audio ports, Enable/Disable audio loudness equivalence for supported ports and verify with external analyzer|dsGetAudioPort(), dsEnableLEConfig()|`NA`|`Y`|`Y`|`Y`|`Y`|

### Test Startup Requirement - Test MS12 `DAP` Capabilities

Playback of stream is required for the L3 testcases

### Emulator Requirements - Test MS12 `DAP` Capabilities

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Test MS12 `DAP` Capabilities

- Control the external analyzer
- Control the port connections

## Test MS12 Capabilities

|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|-----------|--------|--|--|------|----|--------------------------|
|Loop through supported audio ports, Check whether the port supports `MS12` decode or not with configuration file|dsGetAudioPort(), dsIsAudioMS12Decode()|`Y`|`NA`|`Y`|`Y`|`NA`|
|Loop through supported audio ports, Check whether the port supports `MS11` decode or not with configuration file|dsGetAudioPort(), dsIsAudioMSDecode()|`Y`|`NA`|`Y`|`Y`|`NA`|
|Get Supported `MS12` Audio profiles and verify with configuration file|dsGetAudioPort(), dsGetMS12AudioProfileList()|`Y`|`NA`|`NA`|`Y`|`NA`|
|Get Supported `MS12` Audio profiles, Loop through supported audio ports, set various audio profiles for supported ports and retrieve audio profile for verification|dsGetAudioPort(), dsGetMS12AudioProfileList(), dsSetMS12AudioProfile(), dsGetMS12AudioProfile()|`Y`|`NA`|`NA`|`Y`|`NA`|

### Test Startup Requirement - Test MS12 Capabilities

`NA`

### Emulator Requirements - Test MS12 Capabilities

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Test MS12 Capabilities

`NA`

## Test `ARC` Support - Sink Device

|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|-----------|--------|--|--|------|----|--------------------------|
|Get the `ARC` port handle by looping through supported audio ports, get the `ARC` type for `ARC` port and verify with configuration file|dsGetAudioPort(), dsGetSupportedARCTypes()|`Y`|`NA`|`NA`|`Y`|`NA`|
|Get the `ARC` port ID and verify with configuration file|dsGetHDMIARCPortId()|`Y`|`NA`|`NA`|`Y`|`NA`|
|Get the `ARC` port handle by looping through supported audio ports, enable the `ARC` Port and check if the audio routed to `ARC` port using external analyzers|dsGetAudioPort(), dsAudioEnableARC()|`NA`|`Y`|`NA`|`Y`|`Y`|
|Get the `ARC` port handle by looping through supported audio ports, enable the `ARC` Port, Set `SAD` for `ARC` port and verify using external analyzers|dsGetAudioPort(), dsAudioEnableARC(), dsAudioSetSAD()|`NA`|`Y`|`NA`|`Y`|`Y`|

### Test Startup Requirement - Test `ARC` Support

Playback of stream is required for the L3 testcases

### Emulator Requirements - Test `ARC` Support

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Test `ARC` Support

- Control the external analyzer
- Control the port connections

## Test Stereo Mode Support

|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|-----------|--------|--|--|------|----|--------------------------|
|Loop through supported audio ports, Set Stereo mode for supported ports and retrieve Stereo mode for verification|dsGetAudioPort(), dsSetStereoMode(), dsGetStereoMode()|`Y`|`NA`|`Y`|`Y`|`NA`|
|Loop through supported audio ports, Set various stereo modes for all supported ports and verify using the external analyzer|dsGetAudioPort(), dsSetStereoMode()|`NA`|`Y`|`Y`|`Y`|`Y`|
|Loop through supported audio ports, Set Stereo Auto mode for supported ports and retrieve it for verification|dsGetAudioPort(), dsSetStereoAuto(), dsGetStereoAuto()|`Y`|`NA`|`NA`|`Y`|`NA`|
|Loop through supported audio ports, Set Auto Stereo mode for all supported ports and verify using the external analyzer|dsGetAudioPort(), dsSetStereoAuto()|`NA`|`Y`|`NA`|`Y`|`Y`|

### Test Startup Requirement - Test Stereo Mode Support

Playback of audio streams supported by the platform is required for the L3 testcases

### Emulator Requirements - Test Stereo Mode Support

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Test Stereo Mode Support

- Control the external analyzer
- Control the port connections

## Test Audio Gain and Mute

|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|-----------|--------|--|--|------|----|--------------------------|
|Loop through supported audio ports, Set various Linear Audio Gain Values for supported ports and retrieve Audio Gain for verification|dsGetAudioPort(), dsSetAudioGain(), dsGetAudioGain()|`Y`|`NA`|`NA`|`Y`|`NA`|
|Loop through supported audio ports, Set various Linear Audio Gain Values for all supported ports and verify levels using the external analyzer|dsGetAudioPort(), dsSetAudioGain()|`NA`|`Y`|`NA`|`Y`|`Y`|
|Loop through supported audio ports, Set various Audio Levels for supported ports and retrieve Audio Level for verification|dsGetAudioPort(), dsSetAudioLevel(), dsGetAudioLevel()|`Y`|`NA`|`NA`|`Y`|`NA`|
|Loop through supported audio ports, Set various Audio Level for all supported ports and verify using the external analyzer|dsGetAudioPort(), dsSetAudioLevel()|`NA`|`Y`|`NA`|`Y`|`Y`|
|Loop through supported audio ports, Enable/disable audio mute for supported ports and retrieve Mute status for verification|dsGetAudioPort(), dsSetAudioMute(), dsIsAudioMute()|`Y`|`NA`|`Y`|`Y`|`NA`|
|Loop through supported audio ports, Enable/disable audio mute and verify mute status using external analyzer|dsGetAudioPort(), dsSetAudioMute()|`NA`|`Y`|`Y`|`Y`|`Y`|

### Test Startup Requirement - Test Audio Gain and Mute

Playback of audio streams supported by the platform is required for the L3 testcases

### Emulator Requirements - Test Audio Gain and Mute

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Test Audio Gain and Mute

- Control the external analyzer
- Control the port connections

## Test Audio Delay

|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|-----------|--------|--|--|------|----|--------------------------|
|Loop through supported audio ports, Set Audio delay for supported ports and retrieve delay for verification|dsGetAudioPort(), dsSetAudioDelay(), dsGetAudioDelay()|`Y`|`NA`|`Y`|`Y`|`NA`|
|Loop through supported audio ports, Set Audio delay for supported ports and measure audio-video delay using external analyzers|dsGetAudioPort(), dsSetAudioDelay()|`NA`|`Y`|`Y`|`Y`|`Y`|

### Test Startup Requirement - Test Audio Delay

Playback of stream is required for the L3 testcase

### Emulator Requirements - Test Audio Delay

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Test Audio Delay

- Control the external analyzer
- Control the port connections

## Test Atmos Mode

|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|-----------|--------|--|--|------|----|--------------------------|
|Loop through supported audio ports, Enable Audio Atmos mode for supported ports and analyze with external device|dsAudioPortInit(), dsSetAudioAtmosOutputMode()|`NA`|`Y`|`Y`|`Y`|`Y`|
|For sink devices get the ATMOS capabilities of dsAUDIOPORT_TYPE_SPEAKER (internal speaker) and verify with configuration file|dsGetAudioPort(), dsGetSinkDeviceAtmosCapability()|`Y`|`NA`|`NA`|`Y`|`NA`|
|Loop through supported audio ports, Get the ATMOS capabilities of connected devices and verify with configuration file|dsGetAudioPort(), dsGetSinkDeviceAtmosCapability()|`NA`|`Y`|`Y`|`Y`|`Y`|
|Register Atmos capability call-back, change the Atmos capabilities of connected device, and check whether the call-back is triggered or not|dsAudioAtmosCapsChangeRegisterCB ()|`NA`|`Y`|`Y`|`Y`|`Y`|

### Test Startup Requirement - Test Atmos Mode

Playback of stream is required for the L3 testcase

### Emulator Requirements - Test Atmos Mode

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Test Atmos Mode

- Control the external analyzer
- Control the port connections

## Test Audio Format

|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|-----------|--------|--|--|------|----|--------------------------|
|Get the audio format of stream played and verify with external analyzer|dsGetAudioFormat()|`NA`|`Y`|`Y`|`Y`|`Y`|
|Get the audio capabilities of the device and verify with configuration file|dsGetAudioCapabilities()|`Y`|`NA`|`Y`|`Y`|`NA`|
|Register a call-back, Change the audio format of playback and check whether call-back is triggered or not|dsAudioFormatUpdateRegisterCB(), dsGetAudioFormat()|`NA`|`Y`|`Y`|`Y`|`NA`|

### Test Startup Requirement - Test Audio Format

Playback of stream is required for the L3 testcases

### Emulator Requirements - Test Audio Format

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Test Audio Format

- Control the external analyzer
- Control the port connections

## Test Associated Audio Mixing

|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|-----------|--------|--|--|------|----|--------------------------|
|Loop through supported audio ports, Enable/disable Associated Audio Mixing for supported ports and retrieve it for verification|dsGetAudioPort(), dsSetAssociatedAudioMixing(), dsGetAssociatedAudioMixing()|`Y`|`NA`|`Y`|`Y`|`NA`|
|Loop through supported audio ports, Enable Associated Audio Mixing for supported ports, Set various Fader Control values for supported ports and retrieve it for verification|dsGetAudioPort(), dsSetAssociatedAudioMixing(), dsSetFaderControl(), dsGetFaderControl()|`Y`|`NA`|`Y`|`Y`|`NA`|
|Loop through supported audio ports, Test Associate Audio mixing and fader control with stream playback and verify with external analyzer|dsGetAudioPort(), dsSetAssociatedAudioMixing(), dsSetFaderControl()|`NA`|`Y`|`Y`|`Y`|`Y`|

### Test Startup Requirement - Associated Audio Mixing Test

Playback of stream is required for the L3 testcases

### Emulator Requirements - Associated Audio Mixing Test

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Associated Audio Mixing Test

- Control the external analyzer
- Control the port connections

## Test Primary/Secondary Language

|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|-----------|--------|--|--|------|----|--------------------------|
|Set Primary Language and retrieve the same for verification|dsGetAudioPort(), dsSetPrimaryLanguage(), dsGetPrimaryLanguage()|`Y`|`NA`|`Y`|`Y`|`NA`|
|Set Primary Language with stream playback and verify with external analyzer|dsGetAudioPort(), dsSetPrimaryLanguage()|`NA`|`Y`|`Y`|`Y`|`Y`|
|Set Secondary Language and retrieve the same for verification|dsGetAudioPort(), dsSetSecondaryLanguage(), dsGetSecondaryLanguage()|`Y`|`NA`|`Y`|`Y`|`NA`|
|Set Primary Language with stream playback and verify with external analyzer|dsGetAudioPort(), dsSetSecondaryLanguage()|`NA`|`Y`|`Y`|`Y`|`Y`|

### Test Startup Requirement - Language Test

Playback of stream is required for the L3 testcase

### Emulator Requirements - Language Test

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Language Test

- Control the external analyzer
- Control the port connections

## Test Audio Mixer Levels

|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|-----------|--------|--|--|------|----|--------------------------|
|Set Audio mixer levels with stream playback and verify with external analyzer|dsGetAudioPort(), dsSetAudioMixerLevels()|`NA`|`Y`|`NA`|`Y`|`Y`|

### Test Startup Requirement - Test Audio Mixer Levels

Playback of stream is required for the L3 testcase

### Emulator Requirements -Test Audio Mixer Levels

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Test Audio Mixer Levels

- Control the external analyzer
- Control the port connections
