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
- `DAP`    - Digital Audio Processing

## Introduction

This document provides an overview of the testing requirements for the Audio Settings module. It outlines the scope of testing, objectives, testing levels and approaches, specific test requirements, and expected deliverables.

Interface of the test is available here: [Audio Settings HAL header](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsAudio.h)

## Module Description

The Audio device setting interface provides control to enable or disable Audio Output ports like TV Internal Speakers, `ARC`/`eARC`, Headphones, `SPDIF` and allows `caller` to configure or retrieve various audio parameters like audio encoding, audio compression, dialog enhancement, DOLBY volume mode, intelligent equalizer, volume leveller, bass enhancer, `DRC` mode, surround virtualizer, `MI` steering, graphic equalizer, `MS12` audio profile, stereo mode, audio gain, audio `dB`, audio level, audio max and min `dB`, audio delay, fader control, primary language and secondary language. It also provides `APIs` to  enable loop through, set audio ducking, enable `LE`, get the Atmos capability of sink device

## Testing Scope

|#|Test Functionality|Description|
|-|------------------|-----------|
|01|[Test Audio Encoding Mode](#test-audio-encoding-mode)|Test for Audio Encoding Mode|
|02|[Test MS12 `DAP` Capabilities](#test-ms12-dap-capabilities)|Test for MS12 `DAP` capabilities like compression, dialogue enhancement, volume mode, intelligent equalizer, bass enhancer Surround decode, `DRC` mode, Surround Virtualizer, `MI` Steering, Graphic equalizer, `LE` configuration|
|03|[`ARC`Type Support - Sink Device](#arctype-support---sink-device)|Test for `ARC` devices|
|04|[Stereo Mode Support](#stereo-mode-support)|Test for Stereo mode configurations|
|05|[Audio Gain and Level](#audio-gain-and-level)|Test for audio gain and level configurations|
|06|[Audio Delay](#audio-delay)|Test for audio delay configuration|
|07|[Test Atmos Mode](#test-atmos-mode)|Test for audio atmos capabilities|
|08|[Audio Mute Tests](#audio-mute-tests)|Test for audio mute configuration|
|09|[Audio Port Tests](#audio-port-tests)|Test for audio port configuration|
|10|[Audio Loop through Test](#audio-loop-through-test)|Test for audio loop through configuration|
|11|[Test `MS12` Profiles and Capabilities](#test-ms12-profiles-and-capabilites)|Test for `MS12` configurations|
|12|[Test Associated Audio Mixing](#test-associated-audio-mixing)|Test for Associated Audio Mixing|
|13|[Test Primary/Secondary Language](#test-primarysecondary-language)|Test for primary/secondary language configuration|
|14|[Test Audio Mixer Levels](#test-audio-mixer-levels)|Test for primary/secondary language configuration|

## Emulator Requirements

Boot configuration: Various Audio ports and audio formats supported by device and the number of ports for each type

**Audio Ports:**

- `RCA` Audio Port
- `HDMI` Port
- `SPDIF` Port
- Internal Speaker
- `ARC`/`eARC` `HDMI`
- Headphone Jack

**Audio Encoding Formats:**

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

|Description|L2|L3|Control plane requirements|Source|Sink|
|-----------|--|--|--------------------------|------|----|
|Set various encoding types for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|`Y`|`Y`|
|Set various encoding types for all supported ports and verify using the analyzers to check the port output|`NA`|`Y`|Control the external analyzer|`Y`|`Y`|
|Get the audio format of stream played and verify|`NA`|`Y`|`NA`|`Y`|`Y`|
|Change the audio format and check for call-back|`NA`|`Y`|`NA`|`Y`|`Y`|

### Test Startup Requirement - Test Audio Encoding Mode

Playback of different audio formats ([Audio Formats](#emulator-requirements)) supported by the platform is required for the L3 testcase

### Emulator Requirements - Test Audio Encoding Mode

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Test Audio Encoding Mode

Control the external analyzer

## Test MS12 `DAP` Capabilities

|Description|L2|L3|Control plane requirements|Source|Sink|
|-----------|--|--|--------------------------|------|----|
|Set various compression levels for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|`Y`|`Y`|
|Test various compression levels with stream playback|`NA`|`Y`|Control the external analyzer|`Y`|`Y`|
|Set Dialog Enhancement for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|`Y`|`Y`|
|Reset Dialog Enhancement for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|`Y`|`Y`|
|Test Dialog Enhancement for supported ports with stream playback|`NA`|`Y`|Control the external analyzer|`Y`|`Y`|
|Set DOLBY Volume Mode for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|`Y`|`Y`|
|Test DOLBY Volume Mode for supported ports with stream playback|`NA`|`Y`|Control the external analyzer|`Y`|`Y`|
|Set Intelligent Equalizer Mode for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|`Y`|`Y`|
|Test Intelligent Equalizer Mode with stream playback|`NA`|`Y`|Control the external analyzer|`Y`|`Y`|
|Set Volume leveller for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|`Y`|`Y`|
|Reset Volume leveller for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|`Y`|`Y`|
|Test Volume leveller for supported ports with stream playback|`NA`|`Y`|Control the external analyzer|`Y`|`Y`|
|Set Bass Enhancer for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|`Y`|`Y`|
|Reset Bass Enhancer for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|`Y`|`Y`|
|Test Bass Enhancer for supported ports with stream playback|`NA`|`Y`|Control the external analyzer|`Y`|`Y`|
|Set Surround Decoder for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|`Y`|`Y`|
|Test Surround Decoder for supported ports with stream playback|`NA`|`Y`|Control the external analyzer|`Y`|`Y`|
|Set `DRC` Mode for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|`Y`|`Y`|
|Test `DRC` Mode for supported ports with stream playback|`NA`|`Y`|Control the external analyzer|`Y`|`Y`|
|Set Surround Virtualizer for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|`Y`|`Y`|
|Reset Surround Virtualizer for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|`Y`|`Y`|
|Test Surround Virtualizer for supported ports with stream playback|`NA`|`Y`|Control the external analyzer|`Y`|`Y`|
|Set `MI` Steering for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|`Y`|`Y`|
|TEst `MI` Steering for supported ports with stream playback|`NA`|`Y`|Control the external analyzer|`Y`|`Y`|
|Set Graphic Equalizer for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|`Y`|`Y`|
|Test Graphic Equalizer for supported ports with stream playback|`NA`|`Y`|Control the external analyzer|`Y`|`Y`|
|Enable/disable audio loudness equivalence and retrieve status for verification|`Y`|`NA`|`NA`|`Y`|`Y`|

### Test Startup Requirement - Test MS12 `DAP` Capabilities

Playback of different audio formats ([Audio Formats](#emulator-requirements)) supported by the platform is required for the L3 testcase

### Emulator Requirements - Test MS12 `DAP` Capabilities

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Test MS12 `DAP` Capabilities

Control the external analyzer

## `ARC`Type Support - Sink Device

|Description|L2|L3|Control plane requirements|Source|Sink|
|-----------|--|--|--------------------------|------|----|
|Validate the `ARC` port supported|`Y`|`NA`|`NA`|`NA`|`Y`|
|Enable the `ARC` Port and check if the audio routed to `ARC` port using external analyzers|`NA`|`Y`|Control the external analyzer|`NA`|`Y`|
|Set `SAD` for ARC port and verify using external analyzers|`NA`|`Y`|Control the external analyzer|`NA`|`Y`|

### Test Startup Requirement - `ARC`Type Support

Playback of different audio formats ([Audio Formats](#emulator-requirements)) supported by the platform is required for the L3 testcase

### Emulator Requirements - `ARC`Type Support

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - `ARC`Type Support

Control the external analyzer

## Stereo Mode Support

|Description|L2|L3|Control plane requirements|Source|Sink|
|-----------|--|--|--------------------------|------|----|
|Set Stereo mode for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|`Y`|`Y`|
|Set various stereo modes for all supported ports and verify using the analyzer|`NA`|`Y`|Control the external analyzer|`Y`|`Y`|
|Set Stereo Auto mode for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|`Y`|`Y`|
|Set Auto Stereo mode for all supported ports and verify using the analyzer|`NA`|`Y`|Control the external analyzer|`Y`|`Y`|

### Test Startup Requirement - Stereo Mode Support

Playback of different audio formats ([Audio Formats](#emulator-requirements)) supported by the platform is required for the L3 testcase

### Emulator Requirements - Stereo Mode Support

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Stereo Mode Support

Control the external analyzer

## Audio Gain and Level

|Description|L2|L3|Control plane requirements|Source|Sink|
|-----------|--|--|--------------------------|------|----|
|Set Linear Audio Gain Values for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|`Y`|`Y`|
|Set Linear Audio Gain Values for all supported ports and verify levels using the analyzers|`NA`|`Y`|Control the external analyzer|`Y`|`Y`|
|Set Audio Level in `dB` for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|`Y`|`Y`|
|Set Audio Level in `dB` for all supported ports and verify `dB` levels using the analyzers|`NA`|`Y`|Control the external analyzer|`Y`|`Y`|
|Set Audio Level for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|`Y`|`Y`|
|Set Audio Level for all supported ports and verify using the analyzers|`NA`|`Y`|Control the external analyzer|`Y`|`Y`|
|Get Supported Max and Min Audio Levels, set the level and retrieve it for verification|`Y`|`NA`|`NA`|`Y`|`Y`|
|Get Supported Max and Min Audio Levels for all supported ports, set the levels and verify `dB` levels using the analyzers|`NA`|`Y`|Control the external analyzer|`Y`|`Y`|
|Get Supported Optimal Audio Level, set the level and retrieve it for verification|`Y`|`NA`|`NA`|`Y`|`Y`|
|Get Supported Optimal Audio Level, set the level and verify `dB` levels using the analyzers|`NA`|`Y`|Control the external analyzer|`Y`|`Y`|

### Test Startup Requirement - Audio Gain and Level

Playback of different audio formats ([Audio Formats](#emulator-requirements)) supported by the platform is required for the L3 testcase

### Emulator Requirements - Audio Gain and Level

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Audio Gain and Level

Control the external analyzer

## Audio Delay

|Description|L2|L3|Control plane requirements|Source|Sink|
|-----------|--|--|--------------------------|------|----|
|Set Audio delay for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|`Y`|`Y`|
|Set Audio delay offset for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|`Y`|`Y`|
|Set Audio delay and offset values for supported ports and measure audio-video delay using external analyzers|`NA`|`Y`|Control the external analyzer|`Y`|`Y`|

### Test Startup Requirement - Audio Delay

Playback of stream is required for the L3 testcase

### Emulator Requirements - Audio Delay

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Audio Delay

Control the external analyzer

## Test Atmos Mode

|Description|L2|L3|Control plane requirements|Source|Sink|
|-----------|--|--|--------------------------|------|----|
|Enable Audio Atmos for supported ports and analyze with external device|`NA`|`Y`|Controls the external analyzer|`Y`|`Y`|
|Get the ATMOS capabilities of connected devices and verify|`NA`|`Y`|Get the ATMOS capabilities of connected devices|`Y`|`Y`|

### Test Startup Requirement - Atmos Capabilities

`NA`

### Emulator Requirements - Atmos Capabilities

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Atmos Capabilities

- Get the ATMOS capabilities of connected devices
- Controls the external analyzer

## Audio Mute Tests

|Description|L2|L3|Control plane requirements|Source|Sink|
|-----------|--|--|--------------------------|------|----|
|Enable/disable audio mute for supported ports and and retrieve it for verification|`Y`|`NA`|`NA`|`Y`|`Y`|
|Enable/disable audio mute and verify mute status using external analyzer|`NA`|`Y`|Control the external analyzer|`Y`|`Y`|

### Test Startup Requirement - Audio Mute Tests

Playback of stream is required for the L3 testcase

### Emulator Requirements - Audio Mute Tests

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Audio Mute Tests

Control the external analyzer

## Audio Port Tests

|Description|L2|L3|Control plane requirements|Source|Sink|
|-----------|--|--|--------------------------|------|----|
|Enable/disable audio ports and retrieve information for verification|`Y`|`NA`|`NA`|`Y`|`Y`|
|Enable/disable audio ports and verify using external analyzer|`NA`|`Y`|Control the external analyzer|`Y`|`Y`|
|Check the connection status and verify|`Y`|`NA`|`NA`|`Y`|`Y`|
|Check the connection status by connecting/disconnecting the port|`NA`|`Y`|Control the port connections|`Y`|`Y`|
|Check the connection status with call-back function by connecting/disconnecting the port|`NA`|`Y`|Control the port connections|`Y`|`Y`|

### Test Startup Requirement - Audio Port Tests

Playback of stream is required for the L3 testcase

### Emulator Requirements - Audio Port Tests

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Audio Port Tests

- Control the external analyzer
- Control the port connections

## Audio Loop through Test

|Description|L2|L3|Control plane requirements|Source|Sink|
|-----------|--|--|--------------------------|------|----|
|Enable/disable audio loop through and retrieve status for verification|`Y`|`NA`|`NA`|`Y`|`Y`|

### Test Startup Requirement - Audio Loop through Test

`NA`

### Emulator Requirements - Audio Loop through Test

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Audio Loop through Test

`NA`

## Test `MS12` Profiles and Capabilites

|Description|L2|L3|Control plane requirements|Source|Sink|
|-----------|--|--|--------------------------|------|----|
|Enable/disable `MS12` configurations and retrieve for verification|`Y`|`NA`|`NA`|`Y`|`Y`|
|Enable/disable `MS12` configurations and verify with external analyzer|`NA|`Y`|Control the external analyzer|`Y`|`Y`|

### Test Startup Requirement - `MS12` Test

Playback of stream is required for the L3 testcase

### Emulator Requirements - `MS12` Test

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - `MS12` Test

Control the external analyzer

## Test Associated Audio Mixing

|Description|L2|L3|Control plane requirements|Source|Sink|
|-----------|--|--|--------------------------|------|----|
|Set Associated Audio Mixing for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|`Y`|`Y`|
|Set Fader Control for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|`Y`|`Y`|
|Test Associate Audio mixing and fader control with stream playback|`NA`|`Y`|Control the external analyzer|`Y`|`Y`|

### Test Startup Requirement - Associated Audio Mixing Test

Playback of stream is required for the L3 testcase

### Emulator Requirements - Associated Audio Mixing Test

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Associated Audio Mixing Test

Control the external analyzer

## Test Primary/Secondary Language

|Description|L2|L3|Control plane requirements|Source|Sink|
|-----------|--|--|--------------------------|------|----|
|Test Primary/Secondary Language and retrieve it for verification with stream playback|`NA`|`Y`|`NA`|`Y`|`Y`|

### Test Startup Requirement - Language Test

Playback of stream is required for the L3 testcase

### Emulator Requirements - Language Test

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Language Test

`NA`

## Test Audio Mixer Levels

|Description|L2|L3|Control plane requirements|Source|Sink|
|-----------|--|--|--------------------------|------|----|
|Set Audio mixer levels and verify with stream playback|`NA`|`Y`|Control the external analyzer|`NA`|`Y`|

### Test Startup Requirement - Test Audio Mixer Levels

Playback of stream is required for the L3 testcase

### Emulator Requirements -Test Audio Mixer Levels

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Test Audio Mixer Levels

Control the external analyzer
