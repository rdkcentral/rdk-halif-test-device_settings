# Device Settings Composite Input L3 Low Level Test Specification and Procedure Documentation

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Overview](#overview)
- [Definitions](#definitions)
- [References](#references)
- [Level 3 Test Procedure](#level-3-test-procedure)

### Acronyms, Terms and Abbreviations

- `HAL`    - Hardware Abstraction Layer
- `API`    - Application Programming Interface
- `L2`     - Level 2 Testing
- `L3`     - Level 3 Testing
- `DS`     - Device Settings
- `UT`     - Unit Test(s)
- `OEM`    - Original Equipment Manufacture
- `SoC`    - System on a Chip
- `NA`     - Not Applicable
- `DUT`    - Device Under Test
- `RAFT`   - Rapid Automation Framework for Testing

## Overview

This document describes the Low Level L2 Test Specification and Procedure for the Device Settings Composite Input module.

## Definitions

- `ut-core` \- Common Testing Framework [ut-core](https://github.com/rdkcentral/ut-core), which wraps a open-source framework that can be expanded to the requirements for future framework.
- `user` \- Refers to either human or the test automation framework like `RAFT`

## References

- `High Level Test Specification` - [ds-compositeIn-High-Level_TestSpec.md](https://github.com/rdkcentral/rdk-halif-test-device_settings/blob/main/docs/pages/ds-compositeIn-High-Level_TestSpec.md)
- `HAL Interface file` - [dsCompositeIn Header](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsCompositeIn.h)

## Level 3 Test Procedure

The following functions are expecting to test the module operates correctly.

### Test 1

|Title|Details|
|-----|-------|
|Test Name|`test1_VerifyCompositeInPortConnectionAndStatus`|
|Description|Verify the COMPOSITE Input port connection status|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
- Connect/disconnect the CompisiteIn source device

#### Test Procedure - Test 1

|Variation / Steps|Description|
|-----------------|-----------|
|01|Initialize dsCompositeIn|
|02|Connect the CompisiteIn source device to `DUT` |
|03|Check the connection status|
|04|Disconnect the CompisiteIn source device from `DUT`|
|05|Check the connection status|
|06|De-Initialize the dsCompositeIn|

### Test 2

|Title|Details|
|-----|-------|
|Test Name|`test2_VerifyCompositeInPortSelectionAndStatus`|
|Description|Sets the COMPOSITE Input port as active for presentation and verifY the status|

**Pre-Conditions :**

None

**Dependencies :**
None

**User Interaction :**
None

#### Test Procedure - Test 2

|Variation / Steps|Description|
|-----------------|-----------|
|01|Initialize dsCompositeIn|
|02|Get the supported CompositeIn Input ports|
|03|Specify the port to select |
|04|Set the input port to active|
|05|Check status on input port|
|06|De-Initialize the dsCompositeIn|

### Test 3

|Title|Details|
|-----|-------|
|Test Name|`test3_ScaleCompositeInVideoAndVerifyStatus`|
|Description|Scales the COMPOSITE In video and checks for the presented status|

**Pre-Conditions :**
- Connect compositeIn source device and play video.

**Dependencies :**
None

**User Interaction :**

None

#### Test Procedure - Test 3

|Variation / Steps|Description|
|-----------------|-----------|
|01|Initialize dsCompositeIn|
|02|Get the supported CompositeIn Input ports|
|03|Specify the port to select |
|04|Set the input port to active|
|05|Check status on input port|
|06| Scale the video
|07|Check status on input port|
|08|De-Initialize the dsCompositeIn|
