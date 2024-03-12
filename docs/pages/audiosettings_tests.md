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
- `CB`     - Callback function (suffix)
- `ARC`    - Audio Return Channel
- `eARC`   - Enhanced Audio Return Channel
- `SPDIF`  - Sony/Philips Digital Interface
- `HDMI`   - High-Definition Multimedia Interface
- `LE`     - Loudness Equivalence
- `DRC`    - Dynamic Range Control
- `MI`     - Media Intelligent
- `RF`     - Radio Frequency
- `dB`     - Decibel
- `MS12`   - MultiStream 12
- `AC4`    - Audio Compression 4
- `ms`     - milliseconds
- `CPU`    - Central Processing Unit
- `SoC`    - System-on-Chip
- `RCA`    - Radio Corporation of America

## Introduction

This document provides an overview of the testing requirements for the Audio Settings module. It outlines the scope of testing, objectives, testing levels and approaches, specific test requirements, and expected deliverables.

Interface of the test is available here: [Audio Settings HAL header](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsAudio.h)

## Module Description

The Audio device setting interface provides control to enable or disable Audio Output ports like TV Internal Speakers, `ARC`/`eARC`, Headphones, `SPDIF` and allows `caller` to configure or retrieve various audio parameters like audio encoding, audio compression, dialog enhancement, dolby volume mode, intelligent equalizer, volume leveller, bass enhancer, `DRC` mode, surround virtualizer, `MI` steering, graphic equalizer, `MS12` audio profile, stereo mode, audio gain, audio `dB`, audio level, audio max and min `dB`, audio delay, fader control, primary language and secondary language. It also provides `APIs` to  enable loop through, set audio ducking, enable `LE`, get the Atmos capability of sink device

## Testing Scope

|#|Test Functionality|Description|
|-|------------------|-----------|
|01|[Test Audio Encoding Mode](#test-audio-encoding-mode)|Test for Audio Encoding Mode|
|02|[Set and Get Dialog Enhancement](#set-and-get-dialog-enhancement)|Audio Setting Module should set the dialog enhancement and same should be retrieved|
|03|[Set and Get Dolby Volume Mode](#set-and-get-dolby-volume-mode)|Audio Setting Module should set the Dolby Volume Mode and same should be retrieved|
|04|[Set and Get Intelligent Equalizer Mode](#set-and-get-intelligent-equalizer-mode)|Audio Setting Module should set the Intelligent Equalizer Mode and same should be retrieved|
|05|[Set and Get Bass Enhancer](#set-and-get-bass-enhancer)|Audio Setting Module should set the Bass Enhancer and same should be retrieved|
|06|[Set and Get Surround Decoder](#set-and-get-surround-decoder)|Audio Setting Module should set the Surround Decoder and same should be retrieved|
|07|[Set and Get `DRC` Mode](#set-and-get-drc-mode)|Audio Setting Module should set the `DRC` Mode and same should be retrieved|
|08|[Set and Get Surround Virtualizer](#set-and-get-surround-virtualizer)|Audio Setting Module should set the Surround Virtualizer and same should be retrieved|
|09|[Set and Get MI Steering](#set-and-get-mi-steering)|Audio Setting Module should set the MI Steering and same should be retrieved|
|10|[Set and Get Graphic Equalizer](#set-and-get-graphic-equalizer)|Audio Setting Module should set the Graphic Equalizer and same should be retrieved|
|11|[`ARC`Type Support - Sink Device](#arctype-support---sink-device)|Audio Setting Module should set the MI Steering and same should be retrieved|
|12|[Stereo Mode Support](#stereo-mode-support)|Test for Stereo mode configurations|
|13|[Audio Gain](#audio-gain)|Test for audio gain configurations|
|14|[Audio Level](#audio-level)|Test for audio level configurations|

## Emulator Requirements

Boot configuration: Various Audio ports and audio formats supported by device and the number of ports for each type

**Audio Ports:**

- `RCA` Audio Port
- `HDMI` Port
- `SPDIF` Port
- Internal Speaker
- `ARC`/`eARC` `HDMI`
- Headphone Jack

## Test Audio Encoding Mode

|Description|L2|L3|Control plane requirements|
|-----------|--|--|--------------------------|
|Set various encoding types for supported ports and retrieve it for verification|Y|`NA`|`NA`|
|Set various encoding types for all supported ports and verify using the analyzers to check the port output|`NA`|Y|`NA`|

### Test Startup Requirement - Test Audio Encoding Mode

`NA`

### Emulator Requirements - Test Audio Encoding Mode

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Test Audio Encoding Mode

`NA`

## Set and Get Dialog Enhancement

|Description|L2|L3|Control plane requirements|
|-----------|--|--|--------------------------|
|Set Dialog Enhancement for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|

### Test Startup Requirement - Set and Get Dialog Enhancement

`NA`

### Emulator Requirements - Set and Get Dialog Enhancement

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Set and Get Dialog Enhancement

`NA`

## Set and Get Dolby Volume Mode

|Description|L2|L3|Control plane requirements|
|-----------|--|--|--------------------------|
|Set Dolby Volume Mode for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|

### Test Startup Requirement - Dolby Volume Mode

`NA`

### Emulator Requirements - Dolby Volume Mode

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Dolby Volume Mode

`NA`

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
|Enable the `ARC` Port and check if the audio routed to `ARC` port using external analyzers|`NA`|`Y`|`NA`|

### Test Startup Requirement - `ARC`Type Support

`NA`

### Emulator Requirements - `ARC`Type Support

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - `ARC`Type Support

`NA`

## Stereo Mode Support

|Description|L2|L3|Control plane requirements|
|-----------|--|--|--------------------------|
|Set Stereo mode for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|
|Set various stereo modes for all supported ports and verify using the analyzers to check the port output|`NA`|`Y`|`NA`|
|Set Stereo Auto mode for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|
|Set Auto Stereo mode for all supported ports and verify using the analyzers to check the port output|`NA`|`Y`|`NA`|

### Test Startup Requirement - Stereo Mode Support

`NA`

### Emulator Requirements - Stereo Mode Support

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Stereo Mode Support

`NA`

## Audio Gain

|Description|L2|L3|Control plane requirements|
|-----------|--|--|--------------------------|
|Set Linear Audio Gain Values for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|
|Set Linear Audio Gain Values for all supported ports and verify dB levels using the analyzers|`NA`|`Y`|`NA`|
|Set Audio Gain in dB for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|
|Set Audio Gain in dB for all supported ports and verify dB levels using the analyzers|`NA`|`Y`|`NA`|

### Test Startup Requirement - Audio Gain

`NA`

### Emulator Requirements - Audio Gain

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Audio Gain

`NA`

## Audio Level

|Description|L2|L3|Control plane requirements|
|-----------|--|--|--------------------------|
|Set Audio Level for supported ports and retrieve it for verification|`Y`|`NA`|`NA`|
|Set Audio Gain in dB for all supported ports and verify dB levels using the analyzers|`NA`|`Y`|`NA`|

### Test Startup Requirement - Audio Level

`NA`

### Emulator Requirements - Audio Level

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Audio Level

`NA`