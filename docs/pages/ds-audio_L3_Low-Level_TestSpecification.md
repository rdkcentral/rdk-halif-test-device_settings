# Audio Settings L3 Low Level Test Specification and Procedure Documentation

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Overview](#overview)
- [Definitions](#definitions)
- [References](#references)
- [Audio Streams Requirement](#audio-streams-requirement)
- [Level 3 Test Procedure](#level-3-test-procedure)

### Acronyms, Terms and Abbreviations

- `HAL`    - Hardware Abstraction Layer
- `API`    - Application Programming Interface
- `L2`     - Level 2 Testing
- `L3`     - Level 3 Testing
- `DS`     - Device Settings
- `ARC`    - Audio Return Channel
- `HDMI`   - High-Definition Multimedia Interface
- `LE`     - Loudness Equivalence
- `DRC`    - Dynamic Range Control
- `MI`     - Media Intelligent
- `MS12`   - MultiStream 12
- `MS11`   - MultiStream 11
- `DAP`    - Digital Audio Processing
- `PCM`    - Pulse Code Modulation
- `WAV`    - Waveform
- `DUT`    - Device Under Test
- `NA`     - Not Applicable
- `RAFT`   - Rapid Automation Framework for Testing

## Overview

This document describes the L3 Test Procedure for the Device Settings Audio module.

## Definitions

- `ut-core` \- Common Testing Framework [ut-core](https://github.com/rdkcentral/ut-core), which wraps a open-source framework that can be expanded to the requirements for future framework.
- `user` \- Refers to either human or the test automation framework like `RAFT`

## References

- dsAudio HAL Interface - [dsAudio.h](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsAudio.h)
- High Level Test Specification - [ds-audio_High-Level_TestSpecification.md](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/docs/pages/ds-audio_High-Level_TestSpecification.md)

## Audio Streams Requirement

|ID|Description|Audio Format|Samplerate|Channels|Bitrate(kbps)|Stream Path|
|--|-----------|------------|----------|--------|-------------|-----------|
|001|400Hz sine tone|`PCM` with `WAV` header|48000|2|1536|`TBD`|
|002|AAC stream|aac with `ADTS`|48000|2|256|`TBD`|
|003|Vorbis stream|vorbis with `ogg`|48000|2|256|`TBD`|
|004|wma stream|wma|48000|2|256|`TBD`|
|005|Dolby AC3 (Dolby digital)|ac3|48000|2|256|`TBD`|
|006|Dolby EAC3 (Dolby Digital plus)|ac3|48000|2|256|`TBD`|
|007|Dolby AC4|ac4|48000|2|256|`TBD`|
|008|Dolby MAT|MAT|48000|2|256|`TBD`|
|009|Dolby TrueHD|ac3|48000|2|256|`TBD`|
|010|Dolby EAC3 Atmos|eac3|48000|2|256|`TBD`|
|011|Dolby TRUEHD Atmos|ac3|48000|2|256|`TBD`|
|012|Dolby MAT Atmos|MAT|48000|2|256|`TBD`|
|013|Dolby AC4 Atmos|ac4|48000|2|256|`TBD`|

## Level 3 Test Procedure

The following functions are expecting to test the module operates correctly.

### Test 1

|Title|Details|
|-----|-------|
|Test Name|`test1_EnableDisableAndVerifyAudioPortStatus`|
|Description|Enable/disable audio ports and verifY the status|

**Pre-Conditions :**

- Play the audio stream ID `001` [audio-streams-requirement](#audio-streams-requirement) on `DUT`

**Dependencies :**
None

**User Interaction :**
None

#### Test Procedure - Test 1

|Variation / Steps|Description|
|-----------------|-----------|
|01|Initialize dsAudio|
|02|Enable the Port|
|03|Check playback status on enabled port|
|04|Disable the port|
|05|Check playback status on disabled port|
|06|De-Initialize the dsAudio|

### Test 2

|Title|Details|
|-----|-------|
|Test Name|`test2_CheckHeadphoneConnectionStatus`|
|Description|Checks headphone connection status|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**

- Connect/disconnect the headphone

#### Test Procedure - Test 2

|Variation / Steps|Description|
|-----------------|-----------|
|01|Initialize dsAudio|
|02|Enable the Port|
|03|Connect the headphone to `DUT`|
|04|Check the connection status|
|05|Disconnect the headphone from `DUT`|
|06|Check the connection status|
|07|De-Initialize the dsAudio|

### Test 3

|Title|Details|
|-----|-------|
|Test Name|`test3_CheckAudioFormat`|
|Description|Checks audio format of playback stream|

**Pre-Conditions :**

- Play audio streams [audio-streams-requirement](#audio-streams-requirement) on `DUT`

**Dependencies :**
None

**User Interaction :**
None

#### Test Procedure - Test 3

|Variation / Steps|Description|
|-----------------|-----------|
|01|Initialize dsAudio|
|02|Play the audio stream|
|03|Check the audio format in call back and with API|
|04|De-Initialize the dsAudio|
