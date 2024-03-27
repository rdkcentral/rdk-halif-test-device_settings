# Audio Settings Test Document

## Version History

| Date(DD/MM/YY) | Comment       | Version |
| -------------- | ------------- | ------- |
| 26/02/24       | First Release | 1.0.0   |

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Introduction](#introduction)
- [Module Description](#module-description)
- [Testing Scope](#testing-scope)

## Acronyms, Terms and Abbreviations

- `HAL`    - Hardware Abstraction Layer
- `API`    - Application Programming Interface
- `L2`     - Level 2 Testing ()
- `L3`     - Level 3 Testing ()
- `NA`     - Not Applicable
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
- `RF`     - Radio Frequency
- `dB`     - Decibel
- `MS12`   - MultiStream 12
- `AC4`    - Audio Compression 4
- `PCM`    - Pulse Code Modulation
- `AC3`    - Audio Codec 3
- `EAC3`   - Enhanced `AC3`
- `ms`     - milliseconds
- `CPU`    - Central Processing Unit
- `SoC`    - System-on-Chip
- `RCA`    - Radio Corporation of America
- `WMA`    - Windows Media Audio
- `AAC`    - Advanced Audio coding
- `DD`     - DOLBY Digital
- `DDPLUS` - DOLBY Digital Plus

## Introduction

This document provides an overview of the testing requirements for the Audio Settings module. It outlines the scope of testing, objectives, testing levels and approaches, specific test requirements, and expected deliverables.

Interface of the test is available here: [Audio Settings HAL header](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsAudio.h)

## Module Description

The Audio device setting interface provides control to enable or disable Audio Output ports like TV Internal Speakers, `ARC`/`eARC`, Headphones, `SPDIF` and allows `caller` to configure or retrieve various audio parameters like audio encoding, audio compression, dialog enhancement, DOLBY volume mode, intelligent equalizer, volume leveller, bass enhancer, `DRC` mode, surround virtualizer, `MI` steering, graphic equalizer, `MS12` audio profile, stereo mode, audio gain, audio `dB`, audio level, audio max and min `dB`, audio delay, fader control, primary language and secondary language. It also provides `APIs` to  enable loop through, set audio ducking, enable `LE`, get the Atmos capability of sink device

## Testing Scope

|#|Test Functionality|Description|
|-|------------------|-----------|
|01|[Test Audio Encoding Mode](#test-audio-encoding-mode)|Test for Audio Encoding Mode|
|02|[Set and Get Audio Compression Levels](#set-and-get-audio-compression-levels)|Audio Setting Module should set the compression levels and same should be retrieved|
|03|[Set and Get Dialog Enhancement](#set-and-get-dialog-enhancement)|Audio Setting Module should set the dialog enhancement and same should be retrieved|
|04|[DOLBY Volume Mode Test](#dolby-volume-mode-test)|Audio Setting Module should set the DOLBY Volume Mode and same should be retrieved|
|05|[Set and Get Intelligent Equalizer Mode](#set-and-get-intelligent-equalizer-mode)|Audio Setting Module should set the Intelligent Equalizer Mode and same should be retrieved|
|06|[Set and Get Bass Enhancer](#set-and-get-bass-enhancer)|Audio Setting Module should set the Bass Enhancer and same should be retrieved|
|07|[Set and Get Surround Decoder](#set-and-get-surround-decoder)|Audio Setting Module should set the Surround Decoder and same should be retrieved|
|08|[Set and Get `DRC` Mode](#set-and-get-drc-mode)|Audio Setting Module should set the `DRC` Mode and same should be retrieved|
|09|[Set and Get Surround Virtualizer](#set-and-get-surround-virtualizer)|Audio Setting Module should set the Surround Virtualizer and same should be retrieved|
|10|[Set and Get `MI` Steering](#set-and-get-mi-steering)|Audio Setting Module should set the `MI` Steering and same should be retrieved|
|11|[Set and Get Graphic Equalizer](#set-and-get-graphic-equalizer)|Audio Setting Module should set the Graphic Equalizer and same should be retrieved|
|12|[`ARC`Type Support - Sink Device](#arctype-support---sink-device)|Test for `ARC` devices|
|13|[Stereo Mode Support](#stereo-mode-support)|Test for Stereo mode configurations|
|14|[Audio Gain and Level](#audio-gain-and-level)|Test for audio gain and level configurations|
|15|[Audio Delay](#audio-delay)|Test for audio delay configuration|
|16|[Atmos Tests](#atmos-tests)|Test for audio atmos capabilities|
|17|[Audio Mute Tests](#audio-mute-tests)|Test for audio mute configuration|
|18|[Audio Port Tests](#audio-port-tests)|Test for audio port configuration|
|19|[Audio Loop through Test](#audio-loop-through-test)|Test for audio loop through configuration|
|20|[Loudness Equivalence Test](#audio-loop-through-test)|Test for Loudness Equivalence|
|21|[`MS12` Test](#ms12-test)|Test for `MS12` configurations |
|22|[Associated Audio Mixing Test](#associated-audio-mixing-test)|Test for Associated Audio Mixing|
|23|[Fader Control Test](#fader-control-test)|Test for Fader Control|
|24|[Language Test](#language-test)|Test for primary/secondary language configuration|

## Emulator Requirements

Boot configuration: Various Audio ports and audio formats supported by device and the number of ports for each type

**Audio Ports:**

- `RCA` Audio Port
- `HDMI` Port
- `SPDIF` Port
- Internal Speaker
- `ARC`/`eARC` `HDMI`
- Headphone Jack

**Audio Formats:**

- `PCM`
- DOLBY `AC3`
- DOLBY `EAC3`
- DOLBY `AC4`
- DOLBY `MAT`
- DOLBY TRUEHD
- DOLBY `EAC3` Atmos
- DOLBY TRUEHD Atmos
- DOLBY AC4 Atmos
- `AAC`
- VORBIS
- `WMA`

**Stereo Modes:**

- Mono
- Stereo
- Surround
- `DD`
- `DDPlus`

**Audio Compression Levels:**

- Light
- Medium
- High

## Test Audio Encoding Mode

|Description|L2|L3|Control plane requirements|
|-----------|--|--|--------------------------|
|Set various encoding types for supported ports and retrieve it for verification|Y|`NA`|`NA`|
|Set various encoding types for all supported ports and verify using the analyzers to check the port output|`NA`|Y|Control the external analyzer|
|Get the audio format of stream played and verify|`NA`|Y|`NA`|
|Change the audio format and check for call-back|`NA`|Y|`NA`|

### Test Startup Requirement - Test Audio Encoding Mode

Playback of different audio formats ([Audio Formats](#emulator-requirements)) supported by the platform is required for the L3 testcase

### Emulator Requirements - Test Audio Encoding Mode

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Test Audio Encoding Mode

Control the external analyzer

## Set and Get Audio Compression Levels

|Description|L2|L3|Control plane requirements|
|-----------|--|--|--------------------------|
|Set various compression levels for supported ports and retrieve it for verification|Y|`NA`|`NA`|

### Test Startup Requirement - Set and Get Audio Compression Levels

`NA`

### Emulator Requirements - Set and Get Audio Compression Levels

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Set and Get Audio Compression Levels

`NA`

## Set and Get Dialog Enhancement

|Description|L2|L3|Control plane requirements|
|-----------|--|--|--------------------------|
|Set Dialog Enhancement for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|
|Reset Dialog Enhancement for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|

### Test Startup Requirement - Set and Get Dialog Enhancement

`NA`

### Emulator Requirements - Set and Get Dialog Enhancement

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Set and Get Dialog Enhancement

`NA`

## DOLBY Volume Mode Test

|Description|L2|L3|Control plane requirements|
|-----------|--|--|--------------------------|
|Set DOLBY Volume Mode for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|
|Set DOLBY Volume Mode for supported ports and verify using the analyzers|`NA`|Y|Control the external analyzer|

### Test Startup Requirement - DOLBY Volume Mode

Playback of different audio formats ([Audio Formats](#emulator-requirements)) supported by the platform is required for the L3 testcase

### Emulator Requirements - DOLBY Volume Mode

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - DOLBY Volume Mode

Control the external analyzer

## Set and Get Intelligent Equalizer Mode

|Description|L2|L3|Control plane requirements|
|-----------|--|--|--------------------------|
|Set Intelligent Equalizer Mode for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|

### Test Startup Requirement - Intelligent Equalizer Mode

`NA`

### Emulator Requirements - Intelligent Equalizer Mode

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Intelligent Equalizer Mode

`NA`

## Set and Get Volume leveller

|Description|L2|L3|Control plane requirements|
|-----------|--|--|--------------------------|
|Set Volume leveller for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|
|Reset Volume leveller for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|

### Test Startup Requirement - Volume leveller

`NA`

### Emulator Requirements - Volume leveller

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Volume leveller

`NA`

## Set and Get Bass Enhancer

|Description|L2|L3|Control plane requirements|
|-----------|--|--|--------------------------|
|Set Bass Enhancer for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|
|Reset Bass Enhancer for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|

### Test Startup Requirement - Bass Enhancer

`NA`

### Emulator Requirements - Bass Enhancer

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Bass Enhancer

`NA`

## Set and Get Surround Decoder

|Description|L2|L3|Control plane requirements|
|-----------|--|--|--------------------------|
|Set Surround Decoder for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|

### Test Startup Requirement - Surround Decoder

`NA`

### Emulator Requirements - Surround Decoder

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Surround Decoder

`NA`

## Set and Get `DRC` Mode

|Description|L2|L3|Control plane requirements|
|-----------|--|--|--------------------------|
|Set `DRC` Mode for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|

### Test Startup Requirement - `DRC` Mode

`NA`

### Emulator Requirements - `DRC` Mode

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - `DRC` Mode

`NA`

## Set and Get Surround Virtualizer

|Description|L2|L3|Control plane requirements|
|-----------|--|--|--------------------------|
|Set Surround Virtualizer for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|
|Reset Surround Virtualizer for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|

### Test Startup Requirement - Surround Virtualizer

`NA`

### Emulator Requirements - Surround Virtualizer

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Surround Virtualizer

`NA`

## Set and Get `MI` Steering

|Description|L2|L3|Control plane requirements|
|-----------|--|--|--------------------------|
|Set `MI` Steering for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|

### Test Startup Requirement - `MI` Steering

`NA`

### Emulator Requirements - `MI` Steering

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - `MI` Steering

`NA`

## Set and Get Graphic Equalizer

|Description|L2|L3|Control plane requirements|
|-----------|--|--|--------------------------|
|Set Graphic Equalizer for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|

### Test Startup Requirement - Graphic Equalizer

`NA`

### Emulator Requirements - Graphic Equalizer

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Graphic Equalizer

`NA`

## `ARC`Type Support - Sink Device

|Description|L2|L3|Control plane requirements|
|-----------|--|--|--------------------------|
|Validate the `ARC` port supported|`Y`|`NA`|`NA`|
|Enable the `ARC` Port and check if the audio routed to `ARC` port using external analyzers|`NA`|`Y`|Control the external analyzer|
|Set `SAD` for ARC port and verify using external analyzers|`NA`|`Y`|Control the external analyzer|

### Test Startup Requirement - `ARC`Type Support

Playback of different audio formats ([Audio Formats](#emulator-requirements)) supported by the platform is required for the L3 testcase

### Emulator Requirements - `ARC`Type Support

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - `ARC`Type Support

Control the external analyzer

## Stereo Mode Support

|Description|L2|L3|Control plane requirements|
|-----------|--|--|--------------------------|
|Set Stereo mode for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|
|Set various stereo modes for all supported ports and verify using the analyzers to check the port output|`NA`|`Y`|Control the external analyzer|
|Set Stereo Auto mode for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|
|Set Auto Stereo mode for all supported ports and verify using the analyzers to check the port output|`NA`|`Y`|Control the external analyzer|

### Test Startup Requirement - Stereo Mode Support

Playback of different audio formats ([Audio Formats](#emulator-requirements)) supported by the platform is required for the L3 testcase

### Emulator Requirements - Stereo Mode Support

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Stereo Mode Support

Control the external analyzer

## Audio Gain and Level

|Description|L2|L3|Control plane requirements|
|-----------|--|--|--------------------------|
|Set Linear Audio Gain Values for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|
|Set Linear Audio Gain Values for all supported ports and verify levels using the analyzers|`NA`|`Y`|Control the external analyzer|
|Set Audio Level in `dB` for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|
|Set Audio Level in `dB` for all supported ports and verify `dB` levels using the analyzers|`NA`|`Y`|Control the external analyzer|
|Set Audio Level for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|
|Set Audio Level for all supported ports and verify using the analyzers|`NA`|`Y`|Control the external analyzer|
|Get Supported Max and Min Audio Levels, set the level and retrieve it for verification|`Y`|`NA`|`NA`|
|Get Supported Max and Min Audio Levels for all supported ports, set the levels and verify `dB` levels using the analyzers|`NA`|`Y`|Control the external analyzer|
|Get Supported Optimal Audio Level, set the level and retrieve it for verification|`Y`|`NA`|`NA`|
|Get Supported Optimal Audio Level, set the level and verify `dB` levels using the analyzers|`NA`|`Y`|Control the external analyzer|

### Test Startup Requirement - Audio Gain and Level

Playback of different audio formats ([Audio Formats](#emulator-requirements)) supported by the platform is required for the L3 testcase

### Emulator Requirements - Audio Gain and Level

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Audio Gain and Level

Control the external analyzer

## Audio Delay

|Description|L2|L3|Control plane requirements|
|-----------|--|--|--------------------------|
|Set Audio delay for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|
|Set Audio delay offset for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|
|Set Audio delay and offset values for supported ports and measure audio-video delay using external analyzers|`NA`|`Y`|Control the external analyzer|

### Test Startup Requirement - Audio Delay

Playback of stream is required for the L3 testcase

### Emulator Requirements - Audio Delay

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Audio Delay

Control the external analyzer

## Atmos Tests

|Description|L2|L3|Control plane requirements|
|-----------|--|--|--------------------------|
|Enable Audio Atmos for supported ports and analyze with external device|`NA`|`Y`|Controls the external analyzer|
|Get the ATMOS capabilities of connected devices and verify|`NA`|`Y`|Get the ATMOS capabilities of connected devices|

### Test Startup Requirement - Atmos Capabilities

`NA`

### Emulator Requirements - Atmos Capabilities

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Atmos Capabilities

- Get the ATMOS capabilities of connected devices
- Controls the external analyzer

## Audio Mute Tests

|Description|L2|L3|Control plane requirements|
|-----------|--|--|--------------------------|
|Enable/disable audio mute for supported ports and and retrieve it for verification|`Y`|`NA`|`NA`|
|Enable/disable audio mute and verify mute status using external analyzer|`NA`|`Y`|Control the external analyzer|

### Test Startup Requirement - Audio Mute Tests

Playback of stream is required for the L3 testcase

### Emulator Requirements - Audio Mute Tests

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Audio Mute Tests

Control the external analyzer

## Audio Port Tests

|Description|L2|L3|Control plane requirements|
|-----------|--|--|--------------------------|
|Enable/disable audio ports and retrieve information for verification|`Y`|`NA`|`NA`|
|Enable/disable audio ports and verify using external analyzer|`NA`|`Y`|Control the external analyzer|
|Check the connection status and verify|`Y`|`NA`|`NA`|
|Check the connection status by connecting/disconnecting the port|`NA`|`Y`|Control the port connections|
|Check the connection status with call-back function by connecting/disconnecting the port|`NA`|`Y`|Control the port connections|

### Test Startup Requirement - Audio Port Tests

Playback of stream is required for the L3 testcase

### Emulator Requirements - Audio Port Tests

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Audio Port Tests

- Control the external analyzer
- Control the port connections

## Audio Loop through Test

|Description|L2|L3|Control plane requirements|
|-----------|--|--|--------------------------|
|Enable/disable audio loop through and retrieve status for verification|`Y`|`NA`|`NA`|

### Test Startup Requirement - Audio Loop through Test

`NA`

### Emulator Requirements - Audio Loop through Test

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Audio Loop through Test

`NA`

## Loudness Equivalence Test

|Description|L2|L3|Control plane requirements|
|-----------|--|--|--------------------------|
|Enable/disable audio loudness equivalence and retrieve status for verification|`Y`|`NA`|`NA`|

### Test Startup Requirement - Loudness Equivalence Test

`NA`

### Emulator Requirements - Loudness Equivalence Test

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Loudness Equivalence Test

`NA`

## `MS12` Test

|Description|L2|L3|Control plane requirements|
|-----------|--|--|--------------------------|
|Enable/disable `MS12` configurations and retrieve for verification|`Y`|`NA`|`NA`|
|Enable/disable `MS12` configurations and verify with external analyzer|`NA|`Y`|Control the external analyzer|

### Test Startup Requirement - `MS12` Test

Playback of stream is required for the L3 testcase

### Emulator Requirements - `MS12` Test

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - `MS12` Test

Control the external analyzer

## Associated Audio Mixing Test

|Description|L2|L3|Control plane requirements|
|-----------|--|--|--------------------------|
|Set Associated Audio Mixing for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|

### Test Startup Requirement - Associated Audio Mixing Test

`NA`

### Emulator Requirements - Associated Audio Mixing Test

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Associated Audio Mixing Test

`NA`

## Fader Control Test

|Description|L2|L3|Control plane requirements|
|-----------|--|--|--------------------------|
|Set Fader Control for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|

### Test Startup Requirement - Fader Control Test

`NA`

### Emulator Requirements - Fader Control Test

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Fader Control Test

`NA`

## Language Test

|Description|L2|L3|Control plane requirements|
|-----------|--|--|--------------------------|
|Set Primary Language and retrieve it for verification|`Y`|`NA`|`NA`|
|Set Secondary Language and retrieve it for verification|`Y`|`NA`|`NA`|

### Test Startup Requirement - Language Test

`NA`

### Emulator Requirements - Language Test

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Language Test

`NA`
