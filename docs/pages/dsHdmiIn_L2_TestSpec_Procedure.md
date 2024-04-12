# L2 Test Specification and Procedure Document

## Table of Contents

- [Overview](#overview)
- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Level 2 Test Specification](#level-2-test-specification)
- [Level 2 Test Procedure](#level-2-test-procedure)
  - [Get Number of Inputs](#get-number-of-inputs)
  - [Get Input Status](#get-input-status)
  - [Select `HDMI` Input port](#select-hdmi-input-port)
  - [Check `HDMI` ARC port](#check-hdmi-arc-port)
  - [Set and Get `EDID` version](#set-and-get-edid-version)
  - [Get Supported Game Feature list](#get-supported-game-feature-list)
  - [Get `ALLM` status](#get-allm-status)

## Overview

This document describes the Level 2 Test Specification and Procedure for the Device settings `HDMI` Input Module. It is applicable only for the source and sink devices.

### Acronyms, Terms and Abbreviations

- `API` \- Application Programming Interface
- `HDMI` \- High-Definition Multimedia Interface
- `EDID` \- Extended Display Identification Data
- `ALLM` \- Auto Low Latency Mode

## Level 2 Test Specification

The following test case are defined based on profile configuration :

|#|Test Functionality|Description|Goal|
|-|------------------|-----------|----|
|1|[Get Number of Inputs](#get-input-status)|Get the number of `HDMI` inputs|No errors or data callbacks|
|2|[Get Input Status](#get-input-status)|Get the input status when there is no source devce connected to it.(disable status) |No errors or data callbacks|
|3|[Select `HDMI` Input port](#select-hdmi-port)|Select the `HDMI` input port without any source devices.|No errors or data callbacks|
|4|[Check `HDMI` ARC port](#check-hdmi-arc-port)|The test verifies whether the given port is an HDMI ARC port or not.|No errors or data callbacks|
|5|[Set and Get `EDID` version](#set-and-get-edid-version)|The test is to validate by setting and getting the `EDID` bytes information and `EDID` version.|No errors or data callbacks|
|6|[Get Supported Game Feature list](#get-supported-game-feature-list)|The test verifies by getting the all supported game features in the list.|No errors or data callbacks|
|7|[Get `ALLM` status](#get-allm-status)|The test aims to verify that `ALLM` status is enabled or disabled for the specific HDMI input port.|No errors or data callbacks|

## Level 2 Test Procedure

### Get Number of Inputs

|Title|Details|
|-----|-------|
|Function Name|`L2_dsHdmiIn_getNumberOfInputs`|
|Description| Get the number of `HDMI` inputs for the sink devices. |
|Test ID| 02 (Advanced) |
|Priority| High |

**Pre-Conditions :** 
`dsHdmiInInit()` should be called before calling this `dsHdmiInGetNumberOfInputs()` `API`.

**Dependencies :** None

**User Interaction :** None

| Variation / Steps | Description | Test Data | Expected Result |
| ------------------| --------- | ---------- | -------------- |
| 01 | Call `dsHdmiInInit()` to init the module | Valid status | dsERR_NONE |
| 02 | Call `dsHdmiInGetNumberOfInputs()` to get the `HDMI` input numbers | valid status | dsERR_NONE |
| 03 | Call `dsHdmiInTerm()` to term the module | Valid status | dsERR_NONE |

### Get Input Status

|Title|Details|
|--|--|
|Function Name|`L2_dsHdmiIn_getInputStatus`|
|Description| Get the input status when there is no source device connected to the sink device|
|Test ID| 02 (Advanced) |
|Priority| High |

**Pre-Conditions :**
`dsHdmiInInit()` should be called before calling this `dsHdmiInGetStatus()` `API`.

**Dependencies :** None

**User Interaction :** None

| Variation / Steps | Description | Test Data | Expected Result |
| ------------------| --------- | ---------- | -------------- |
| 01 | Call `dsHdmiInInit()` to init the module | Valid status | dsERR_NONE |
| 02 | Call `dsHdmiInGetStatus()` to get the `HDMI` input status when there is no source device connected | valid status | dsERR_NONE |
| 03 | Call `dsHdmiInTerm()` to term the module | Valid status | dsERR_NONE |

### Select `HDMI` Input port

|Title|Details|
|--|--|
|Function Name|`L2_dsHdmiIn_selectPort`|
|Description| Select and set the `HDMI` input port when there is no source device is connected|
|Test ID| 02 (Advanced) |
|Priority| High |

**Pre-Conditions :**
`dsHdmiInInit()` should be called before calling this `dsHdmiInSelectPort()` `API`.

**Dependencies :** None

**User Interaction :** None

| Variation / Steps | Description | Test Data | Expected Result |
| ------------------| --------- | ---------- | -------------- |
| 01 | Call `dsHdmiInInit()` to init the module | Valid status | dsERR_NONE |
| 02 | Call `dsHdmiInSelectPort()` to select and set the `HDMI` input when there is no source device connected and check active port is false| valid status | dsERR_NONE |
| 03 | Call `dsHdmiInTerm()` to term the module | Valid status | dsERR_NONE |

### Check `HDMI` ARC port

|Title|Details|
|--|--|
|Function Name|`L2_dsHdmiIn_checkARCPort`|
|Description|Verifies whether the given port is an HDMI ARC port or not.|No errors or data callbacks|
|Test ID| 02 (Advanced) |
|Priority| High |

**Pre-Conditions :**
`dsHdmiInInit()` should be called before calling this `dsIsHdmiARCPort()` `API`.

**Dependencies :** None

**User Interaction :** None

| Variation / Steps | Description | Test Data | Expected Result |
| ------------------| --------- | ---------- | -------------- |
| 01 | Call `dsHdmiInInit()` to init the module | Valid status | dsERR_NONE |
| 02 | Call `dsIsHdmiARCPort()` to check whether the given port is an `HDMI` ARC port or not| valid status | dsERR_NONE |
| 03 | Call `dsHdmiInTerm()` to term the module | Valid status | dsERR_NONE |

### Set and Get `EDID` version

|Title|Details|
|-----|-------|
|Function Name|`L2_dsHdmiIn_setandGetEDIDVersion`|
|Description|Validate by setting and getting the `EDID` bytes information and `EDID` version.|
|Test ID| 02 (Advanced) |
|Priority| High |

**Pre-Conditions :**
`dsHdmiInInit()` should be called before calling this `dsSetEdidVersion()`, `dsGetEdidVersion()` and `dsGetEDIDBytesInfo()` `API`.

**Dependencies :** None

**User Interaction :** None

| Variation / Steps | Description | Test Data | Expected Result |
| ------------------| --------- | ---------- | -------------- |
| 01 | Call `dsHdmiInInit()` to init the module | Valid status | dsERR_NONE |
| 02 | Call `dsSetEdidVersion()` to set the `EDID` version by port id| valid status | dsERR_NONE |
| 03 | call `dsGetEdidVersion()` to get the `EDID` version by port id| valid status | dsERR_NONE |
| 04 | validate and compare the `EDID` version from the Set and Get calls | valid status | true |
| 05 | Call the `dsGetEDIDBytesInfo()` to get the `EDID` bytes and `EDID` length of the given port| valid status | dsERR_NONE |
| 03 | Call `dsHdmiInTerm()` to term the module | Valid status | dsERR_NONE |

### Get Supported Game Feature list

|Title|Details|
|-----|-------|
|Function Name|`L2_dsHdmiIn_getSupportedGameFeaturesList`|
|Description| Gets the all supported game features list information.|
|Test ID| 02 (Advanced)|
|Priority| High |

**Pre-Conditions :**
`dsHdmiInInit()` should be called before calling this `dsGetSupportedGameFeaturesList()` `API`.

**Dependencies :** None

**User Interaction :** None

| Variation / Steps | Description | Test Data | Expected Result |
| ------------------| --------- | ---------- | -------------- |
| 01 | Call `dsHdmiInInit()` to init the module | Valid status | dsERR_NONE |
| 02 | Call `dsGetSupportedGameFeaturesList()` gets all the supported game features list information, compare it with the predefined information| valid status | dsERR_NONE |
| 03 | Call `dsHdmiInTerm()` to term the module | Valid status | dsERR_NONE |

### Get `ALLM` status

|Title|Details|
|--|--|
|Function Name|`L2_dsHdmiIn_getALLMStatus`|
|Description| Get whether the `ALLM` status is enabled or disabled for the specific `HDMI` input port.|
|Test ID| 02 (Advanced) |
|Priority| High |

**Pre-Conditions :**
`dsHdmiInInit()` should be called before calling this `dsGetAllmStatus()` `API`.

**Dependencies :** None

**User Interaction :** None

| Variation / Steps | Description | Test Data | Expected Result |
| ------------------| --------- | ---------- | -------------- |
| 01 | Call `dsHdmiInInit()` to init the module | Valid status | dsERR_NONE |
| 02 | Call `dsGetAllmStatus()` to check whether the `ALLM` status is enabled or disabled for the specific `HDMI` input port.| valid status | dsERR_NONE |
| 03 | Call `dsHdmiInTerm()` to term the module | Valid status | dsERR_NONE |