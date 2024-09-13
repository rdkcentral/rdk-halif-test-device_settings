# Display Settings L3 Low Level Test Specification and Procedure Documentation

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Overview](#overview)
- [Definitions](#definitions)
- [References](#references)
- [Level 3 Test Procedure](#level-3-test-procedure)

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

This document describes the L3 Test Procedure for the Device Settings Display module.

## Definitions

- `ut-core` \- Common Testing Framework [ut-core](https://github.com/rdkcentral/ut-core), which wraps a open-source framework that can be expanded to the requirements for future framework.
- `user` \- Refers to either human or the test automation framework like `RAFT`

### References

- `High Level Test Specification` - [dsDisplay High Level TestSpec](ds-display-high-Level_TestSpec.md)
- `Interface header` - [dsDisplay HAL header](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsDisplay.h)

## Level 3 Test Procedure

The following functions are expecting to test the module operates correctly.

### Test 1

|Title|Details|
|-----|-------|
|Test Name|`test1_dsDisplay_get_handle`|
|Description| Retrieves the display handle based on user-selected video port. |

**Pre-Conditions :**
None.

**Dependencies :**
None.

**User Interaction :**
Select a video port.

#### Test Procedure - Test 1

|Variation / Steps|Description|
|-----------------|-----------|
|01|Initialize dsDisplay|
|02|Select a video port|
|03|Retrieve the display handle|
|04|Check the display handle status|
|05|De-Initialize the dsDisplay|

### Test 2

|Title|Details|
|-----|-------|
|Test Name|`test2_dsDisplay_get_edid`|
|Description|Verify the functionality of retrieving the EDID information of a display|

**Pre-Conditions :**
A valid display handle is required.

**Dependencies :**
None.

**User Interaction :**
None.

#### Test Procedure - Test 2

|Variation / Steps|Description|
|-----------------|-----------|
|01|Initialize dsDisplay|
|02|Retrieve the display handle|
|03|Get the EDID information for the display|
|04|Verify the retrieved EDID information|
|05|De-Initialize the dsDisplay|

### Test 3

|Title|Details|
|-----|-------|
|Test Name|`test3_dsDisplay_get_edidbytes`|
|Description|Verify the functionality of retrieving the EDID bytes of a display|

**Pre-Conditions :**
A valid display handle is required.

**Dependencies :**
None.

**User Interaction :**
None.

#### Test Procedure - Test 3

|Variation / Steps|Description|
|-----------------|-----------|
|01|Initialize dsDisplay|
|02|Retrieve the display handle|
|03|Get the EDID bytes for the display|
|04|Verify the retrieved EDID bytes|
|05|De-Initialize the dsDisplay|

### Test 4

|Title|Details|
|-----|-------|
|Test Name|`test4_dsDisplay_get_aspectratio`|
|Description|Verify the functionality of retrieving the aspect ratio of a display|

**Pre-Conditions :**
A valid display handle is required.

**Dependencies :**
None.

**User Interaction :**
None.

#### Test Procedure - Test 4

|Variation / Steps|Description|
|-----------------|-----------|
|01|Initialize dsDisplay|
|02|Retrieve the display handle|
|03|Get the aspect ratio of the display|
|04|Verify the retrieved aspect ratio|
|05|De-Initialize the dsDisplay|
