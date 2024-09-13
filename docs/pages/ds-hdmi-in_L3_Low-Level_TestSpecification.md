# HdmiIn L3 Low Level Test Specification and Procedure Documentation

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

- dsHdmiIn  HAL Interface - [dsHdmiIn.h](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsHdmiIn.h)
- High Level Test Specification - [ds-hdmi-in-High-Level_TestSpec.md](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/docs/pages/ds-hdmi-in-High-Level_TestSpec.md)

## Level 3 Test Procedure

The following functions are expecting to test the module operates correctly.

### Test 1

|Title|Details|
|-----|-------|
|Test Name|`test1_HdmiIn_get_status`|
|Description|Get the status of hdmiin ports |

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
None

#### Test Procedure - Test 1

|Variation / Steps|Description|
|-----------------|-----------|
|01|Initialize dsHdmiIn|
|02|Get HdmiIn status|
|03|Check the status|
|04|De-Initialize the dsHdmiIn|

### Test 2

|Title|Details|
|-----|-------|
|Test Name|`test2_HdmiIn_select_port`|
|Description|selects HdmiInput port on platform|

**Pre-Conditions :**
HdmiIn devices connected in ports.

**Dependencies :**
None

**User Interaction :**
Verify particular port is selected.

#### Test Procedure - Test 2

|Variation / Steps|Description|
|-----------------|-----------|
|01|Initialize dsHdmiIn|
|02|select the port|
|03|verify particular port is selected|
|04|De-Initialize the HdmiIn|

### Test 3

|Title|Details|
|-----|-------|
|Test Name|`test3_HdmiIn_scale_video`|
|Description|Scales video on slected port|

**Pre-Conditions :**

- Play Video streams from any of the HdmiInput on `DUT`

**Dependencies :**
None

**User Interaction :**
Verify video scaling happened or not.

#### Test Procedure - Test 3

|Variation / Steps|Description|
|-----------------|-----------|
|01|Initialize dsHdmiIn|
|02|Play the video stream on selected port|
|03|Perform video scaling on selected port|
|04|Verify video scaling happened or not|
|05|De-Initialize the dsHdmiIn|

### Test 4

|Title|Details|
|-----|-------|
|Test Name|`test4_HdmiIn_zoom_mode`|
|Description|Selects zoom mode on slected port|

**Pre-Conditions :**

- Play Video streams from any of the HdmiInput on `DUT`

**Dependencies :**
None

**User Interaction :**
Verify video zoom selected or not.

#### Test Procedure - Test 4

|Variation / Steps|Description|
|-----------------|-----------|
|01|Initialize dsHdmiIn|
|02|Play the video stream on selected port|
|03|Select Zoom Mode on particular port|
|04|Verify video Zoom selected or not|
|05|De-Initialize the dsHdmiIn|

### Test 5

|Title|Details|
|-----|-------|
|Test Name|`test5_HdmiIn_video_mode`|
|Description|Gets current video mode on slected port|

**Pre-Conditions :**

- Play Video streams from any of the HdmiInput on `DUT`

**Dependencies :**
None

**User Interaction :**
None

#### Test Procedure - Test 5

|Variation / Steps|Description|
|-----------------|-----------|
|01|Initialize dsHdmiIn|
|02|Play the video stream on selected port|
|03|Perform get current video mode on selected port|
|04|De-Initialize the dsHdmiIn|

### Test 6

|Title|Details|
|-----|-------|
|Test Name|`test6_HdmiIn_arc_port`|
|Description|Gets arc status on slected port|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
None

#### Test Procedure - Test 6

|Variation / Steps|Description|
|-----------------|-----------|
|01|Initialize dsHdmiIn|
|02|chek whether the port selected is arc or not|
|03|De-Initialize the dsHdmiIn|

### Test 7

|Title|Details|
|-----|-------|
|Test Name|`test7_HdmiIn_arc_port`|
|Description|Gets edid data on slected port|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
None

#### Test Procedure - Test 7

|Variation / Steps|Description|
|-----------------|-----------|
|01|Initialize dsHdmiIn|
|02|get the edid data on selected port|
|03|De-Initialize the dsHdmiIn|

### Test 8

|Title|Details|
|-----|-------|
|Test Name|`test8_HdmiIn_spd_info`|
|Description|Gets spdinfo on slected port|

**Pre-Conditions :**
Port should be selected using dsHdmiInSelectPort api.

**Dependencies :**
None

**User Interaction :**
None

#### Test Procedure - Test 8

|Variation / Steps|Description|
|-----------------|-----------|
|01|Initialize dsHdmiIn|
|02|Select the port using dsHdmiInSelectPort api|
|03|Get spf info of slected port|
|04|De-Initialize the dsHdmiIn|

### Test 9

|Title|Details|
|-----|-------|
|Test Name|`test9_HdmiIn_set_edidversion`|
|Description|Sets edid version on slected port|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
None

#### Test Procedure - Test 9

|Variation / Steps|Description|
|-----------------|-----------|
|01|Initialize dsHdmiIn|
|02|Set edid version on selected port|
|03|Get the edid version and verify|
|04|De-Initialize the dsHdmiIn|

### Test 10

|Title|Details|
|-----|-------|
|Test Name|`test10_HdmiIn_get_allmstatus`|
|Description|Get allm status  on slected port|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
None

#### Test Procedure - Test 10

|Variation / Steps|Description|
|-----------------|-----------|
|01|Initialize dsHdmiIn|
|02|Get allm status on selected port|
|03|De-Initialize the dsHdmiIn|

### Test 11

|Title|Details|
|-----|-------|
|Test Name|`test11_HdmiIn_get_gamefeatureslist`|
|Description|Get supported game features list|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
None

#### Test Procedure - Test 11

|Variation / Steps|Description|
|-----------------|-----------|
|01|Initialize dsHdmiIn|
|02|Get supported game features list||
|03|De-Initialize the dsHdmiIn|

### Test 12

|Title|Details|
|-----|-------|
|Test Name|`test12_HdmiIn_get_avlatency`|
|Description|Get audio video latency|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
None

#### Test Procedure - Test 12

|Variation / Steps|Description|
|-----------------|-----------|
|01|Initialize dsHdmiIn|
|02|Get audio video latency|
|03|De-Initialize the dsHdmiIn|

### Test 13

|Title|Details|
|-----|-------|
|Test Name|`test13_HdmiIn_set_edid2allmsupport`|
|Description|Get audio video latency|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
None

#### Test Procedure - Test 13

|Variation / Steps|Description|
|-----------------|-----------|
|01|Initialize dsHdmiIn|
|02|Set allmsupport on selected port|
|03|Get allmsupport and verify|
|04|De-Initialize the dsHdmiIn|
