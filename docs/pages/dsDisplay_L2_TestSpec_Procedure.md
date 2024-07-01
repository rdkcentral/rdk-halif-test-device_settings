# L2 Test Specification and Procedure Document

## Table of Contents

- [Overview](#overview)
- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Level 2 Test Specification](#level-2-test-specification)
- [Level 2 Test Procedure](#level-2-test-procedure)
  - [Get `EDID` for sink devices](#get-edid-for-sink-devices)
  
## Overview

This document describes the Level 2 Test Specification and Procedure for the Device Settings Display module.

Interface of the test is available here: [Display HAL header](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsDisplay.h)

### Acronyms, Terms and Abbreviations

- `EDID` \- Extended Display Identification Data.
- `HDMI` \- High-Definition Multimedia Interface.

## Level 2 Test Specification

The following test case are defined based on profile configuration :

|#|Test Functionality|Description|Goal|
|-|------------------|-----------|----|
|1|[Get `EDID` for sink devices](#get-edid-for-sink-devices)|For sink devices, TVs are just returning the `HDMI` Port 1 `EDID`.|No errors|

## Level 2 Test Procedure

### Get `EDID` for sink devices

|Title|Details|
|-----|-------|
|Function Name|`L2_dsDisplay_getedid`|
|Description| For the sink devices, get the `HDMI` port 1 `EDID` values return by the TV|
|Test ID| 02 (Advanced) |
|Priority| High |

**Pre-Conditions :** 
`dsDisplayInit()` and `dsGetDisplay()` should get called before calling the `dsGetEDIDBytes()`

**Dependencies :** None

**User Interaction :** None

| Variation / Steps | Description | Test Data | Expected Result |
| ------------------| --------- | ---------- | -------------- |
| 01 | Call `dsDisplayInit()` to init the module | Valid status | dsERR_NONE |
| 02 | Call `dsGetDisplay()` to get display handle | Valid handle | dsERR_NONE |
| 03 | Call `dsGetEDIDBytes()` for sink devices and get `EDID` Bytes. It copies the `EDID` buffer and length of the TVs `HDMI` port 1|Valid status|dsERR_NONE |
| 04 | Call `dsDisplayTerm` to term the module | Valid status  | dsERR_NONE |


