# Audio Settings L3 Low Level Test Specification and Procedure Documentation

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Overview](#overview)
- [Definitions](#definitions)
- [References](#references)
- [Audio Streams Requirement](#audio-streams-requirement)
- [Tools Requirement](#tools-required-on-device)
- [C Test Menus](#c-test-menus)
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

|ID|Description|Audio Format|
|--|-----------|------------|
|001|400Hz sine tone|`PCM` with `WAV` header|
|002|AAC stream|aac with `ADTS`|
|003|Vorbis stream|vorbis with `ogg`|
|004|wma stream|wma|
|005|Dolby AC3 (Dolby digital)|ac3|
|006|Dolby EAC3 (Dolby Digital plus)|ac3|
|007|Dolby AC4|ac4|
|008|Dolby MAT||
|009|Dolby TrueHD||
|010|Dolby EAC3 Atmos||
|011|Dolby TRUEHD Atmos||
|012|Dolby MAT Atmos||
|013|Dolby AC4 Atmos||

## Tools Required on Device

|#|Tools|Description|
|-|-----|-----------|
|1|gst-play|Gstreamer tool to playback the streams|

## C Test Menus

### UT Test Suites

|Test Suites|
|---------|
|L1 dsAudio|
|L2 dsAudio|
|L3 dsAudio|

### L3 dsAudio Main Menu

|Test Name|
|---------|
|Initialize dsAudio|
|Enable Audio Port|
|Disable Audio Port|
|Headphone Connection|
|Audio Compression|
|MS12 DAP Features|
|Set Stereo Mode|
|Enable/Disable Stereo Auto|
|Set Audio Level|
|Set Audio Gain For Speaker|
|Audio Mute/UnMute|
|Set Audio Delay|
|Get Audio Format|
|Set ATMOS Output Mode|
|Get ATMOS Capabilities|
|Set MS12 Profiles|
|Set Associate Audio Mixing|
|Set Audio Mixer Levels|
|Primary/Secondary Language|
|Get ARC Type|
|Set SAD List|
|Terminate dsAudio|

### dsAudio Ports

|Test Name|Index|
|---------|-----|
|dsAUDIOPORT_TYPE_HDMI|0|
|dsAUDIOPORT_TYPE_SPDIF|0|
|dsAUDIOPORT_TYPE_SPEAKER|0|
|dsAUDIOPORT_TYPE_HDMI_ARC|0|
|dsAUDIOPORT_TYPE_HEADPHONE|0|

## Level 3 Test Procedure

The following functions are expecting to test the module operates correctly.

### Test 1

|Title|Details|
|-----|-------|
|Function Name|`test_l3_EnableDisableAndVerifyAudioPortStatus`|
|Description|Enable/disable audio ports and verifY the status|
|Test Group|03|
|Test Case ID|001|
|Priority|High|

**Pre-Conditions :**

- Copy and Playback of audio stream ID `001` [audio-streams-requirement](#audio-streams-requirement) on `DUT`
  - Example Playback command:
`gst-play-1.0 audo_stream_001.wav`
- Copy the dsAudio hal test binary and configuration files to `DUT`

**Dependencies :**
None

**User Interaction :**

- Audio Verification - Different ways to validate the audio playback through the ports:

  - Listen to the audio played in different audio ports
  - Tap the audio data on `DUT` and verify

#### Test Procedure - Test 1

|Variation / Steps|Description|Menu Sequence|
|-----------------|-----------|-------------|
|01|Initialize dsAudio|Select `Initialize dsAudio` from [L3 dsAudio Main Menu](#l3-dsaudio-main-menu)|
|02|Enable the Port|Select `Enable Audio Port` from [L3 dsAudio Main Menu](#l3-dsaudio-main-menu). From the available ports on `DUT`, select the port to enable. Example Menu [Audio Ports](#dsaudio-ports)|
|03|Check port enable status|Audio should be played from the enabled port|
|04|Disable the port|Select `Disable Audio Port` from [L3 dsAudio Main Menu](#l3-dsaudio-main-menu). From the enable ports, select the port to disable|
|05|Check port disable status|Audio should not be played from the disable port|
|06|De-Initialize the dsAudio|Select `Terminate dsAudio` from [L3 dsAudio Main Menu](#l3-dsaudio-main-menu)|
