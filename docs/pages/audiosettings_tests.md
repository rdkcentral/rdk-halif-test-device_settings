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
|01|[Set And Get Audio Encoding](#set-and-get-audio-encoding)|Audio Setting Module should set the encoding type for all the supported ports and same should be retrieved|
|02|[Test Audio Encoding](#test-audio-encoding)|Audio Setting Module should set the encoding type and analyze the data from the port with analyzer for verification|
|03|[Set and Get Dialog Enhancement](#set-and-get-dialog-enhancement)|Audio Setting Module should set the dialog enhancement and same should be retrieved|
|04|[Set and Get Dolby Volume Mode](#set-and-get-dolby-volume-mode)|Audio Setting Module should set the Dolby Volume Mode and same should be retrieved|
|05|[Set and Get Intelligent Equalizer Mode](#set-and-get-intelligent-equalizer-mode)|Audio Setting Module should set the Intelligent Equalizer Mode and same should be retrieved|

## Emulator Requirements

Boot configuration: Various Audio ports and audio formats supported by device and the number of ports for each type

**Audio Ports:**

- `RCA` Audio Port
- `HDMI` Port
- `SPDIF` Port
- Internal Speaker
- `ARC`/`eARC` `HDMI`
- Headphone Jack

## Set And Get Audio Encoding

|Description|L2|L3|Control plane requirements|
|-----------|--|--|--------------------------|
|Set various encoding types for supported ports and retrieve it for verification|Y|`NA`|`NA`|

### Test Startup Requirement - Set And Get Audio Encoding

`NA`

### Emulator Requirements - Set And Get Audio Encoding

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Set And Get Audio Encoding

`NA`

## Test Audio Encoding

|Description|L2|L3|Control plane requirements|
|-----------|--|--|--------------------------|
|Set various encoding types for all supported ports and verify using the analyzers to check the port output|`NA`|Y|`NA`|

### Test Startup Requirement - Test Audio Encoding

`NA`

### Emulator Requirements - Test Audio Encoding

[Emulator Requirements](#emulator-requirements)

### Control Plane Requirements - Test Audio Encoding

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
