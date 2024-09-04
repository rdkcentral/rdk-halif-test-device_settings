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

This document describes the Low Level L3 Test Specification and Procedure for the Device Settings Audio module.

## Definitions

- `ut-core` \- Common Testing Framework [ut-core](https://github.com/rdkcentral/ut-core), which wraps a open-source framework that can be expanded to the requirements for future framework.
- `user` \- Refers to either human or the test automation framework like `RAFT`

## References

- dsAudio HAL Interface - [dsAudio.h](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsAudio.h)
- High Level Test Specification - [ds-audio_High-Level_TestSpecification.md](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/docs/pages/ds-audio_High-Level_TestSpecification.md)

## Audio Streams Requirement

|ID|Description|Audio Format|Samplerate|Channels|Bitrate(kbps)|
|--|-----------|------------|----------|--------|-------|
|001|400Hz sine tone|`PCM` with `WAV` header|48000|2|1536|
|002|AAC stream|aac with `ADTS`|48000|2|256|
|003|Vorbis stream|vorbis with `ogg`|48000|2|256|
|004|wma stream|wma|48000|2|256|
|005|Dolby AC3 (Dolby digital)|ac3|48000|2|256|
|006|Dolby EAC3 (Dolby Digital plus)|ac3||||
|007|Dolby AC4|ac4||||
|008|Dolby MAT|||||
|009|Dolby TrueHD|||||
|010|Dolby EAC3 Atmos|||||
|011|Dolby TRUEHD Atmos|||||
|012|Dolby MAT Atmos|||||
|013|Dolby AC4 Atmos|||||

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
|03|Check port enable status|
|04|Disable the port|
|05|Check port disable status|
|06|De-Initialize the dsAudio|

### Test 2

|Title|Details|
|-----|-------|
|Function Name|`test2_CheckHeadphoneConnectionStatus`|
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
|04|Check the status|
|05|Disconnect the headphone from `DUT`|
|06|Check the status|
|07|De-Initialize the dsAudio|

### Test 3

|Title|Details|
|-----|-------|
|Function Name|`test3_CheckAudioFormat`|
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
