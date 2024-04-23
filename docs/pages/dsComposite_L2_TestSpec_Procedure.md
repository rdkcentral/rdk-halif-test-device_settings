# L2 Test Specification and Procedure Document

## Table of Contents

- [Overview](#overview)
- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Level 2 Test Specification](#level-2-test-specification)
- [Level 2 Test Procedure](#level-2-test-procedure)
  - [Get Number of Inputs](#get-number-of-inputs)
  - [Get Input Status](#get-input-status)
  - [Select Composite Input port](#select-composite-input-port)

## Overview

This document describes the Low Level L2 Test Specification and Procedure for the Device settings Composite Input Module. It is applicable only for the sink devices.

- Interface of the Composite Input is available here: [Composite Input HAL header](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsCompositeIn.h)
- High level test specification document is available here: [Composite High Level Specification Document](https://github.com/rdkcentral/rdk-halif-test-device_settings/blob/develop/docs/pages/dsComposite_test_spec.md)

### Acronyms, Terms and Abbreviations

- `API` \- Application Programming Interface

## Level 2 Test Specification

The following test case are defined based on profile configuration :

|#|Test Functionality|Description|Goal|
|-|------------------|-----------|----|
|1|[Get Number of Inputs](#get-input-status)|Get the number of composite inputs|No errors|
|2|[Get Input Status](#get-input-status)|Get the input status when there is no source device connected to it.(disable status) |No errors|
|3|[Select Composite Input port](#select-composite-input-port)|Select the composite input port without any source devices.|No errors|

## Level 2 Test Procedure

### Get Number of Inputs

|Title|Details|
|-----|-------|
|Function Name|`L2_dsCompositeIn_getNumberOfInputs`|
|Description| Get the number of composite inputs for the sink devices. |
|Test ID| 02 (Advanced) |
|Priority| High |

**Pre-Conditions :** None

**Dependencies :** None

**User Interaction :** None

| Variation / Steps | Description | Test Data | Expected Result |
| ------------------| --------- | ---------- | -------------- |
| 01 | Call `dsCompositeInInit()` to init the module | Valid status | dsERR_NONE |
| 02 | Call `dsCompositeInGetNumberOfInputs()` to get the composite input numbers | Valid number of Composite Input ports | dsERR_NONE |
| 03 | Compare the composite input numbers with the configurations. | Valid status | True |
| 04 | Call `dsCompositeInTerm()` to term the module | Valid status | dsERR_NONE |

### Get Input Status

|Title|Details|
|--|--|
|Function Name|`L2_dsCompositeIn_getInputStatus`|
|Description| Get the input status when there is no source device connected to the sink device|
|Test ID| 02 (Advanced) |
|Priority| High |

**Pre-Conditions :** None

**Dependencies :** None

**User Interaction :** None

| Variation / Steps | Description | Test Data | Expected Result |
| ------------------| --------- | ---------- | -------------- |
| 01 | Call `dsCompositeInInit()` to init the module | Valid status | dsERR_NONE |
| 02 | Call `dsCompositeInGetStatus()` to get the all composite input port status when there is no source device connected | Valid Input port status data | dsERR_NONE |
| 03 | Check the activePort status, isPresented and isPortConnected values as false | Valid status | True |
| 03 | Call `dsCompositeInTerm()` to term the module | Valid status | dsERR_NONE |

### Select Composite Input port

|Title|Details|
|--|--|
|Function Name|`L2_dsCompositeIn_selectCompositeIn`|
|Description| Select and set the composite input port when there is no source device is connected|
|Test ID| 02 (Advanced) |
|Priority| High |

**Pre-Conditions :** None

**Dependencies :** None

**User Interaction :** None

| Variation / Steps | Description | Test Data | Expected Result |
| ------------------| --------- | ---------- | -------------- |
| 01 | Call `dsCompositeInInit()` to init the module | Valid status | dsERR_NONE |
| 02 | Call `dsCompositeInSelectPort()` to select and set the composite input port when there is no source device connected| Valid status | dsERR_NONE |
| 03 | Call `dsCompositeInGetStatus()` to get the composite input port status and check the active port status as false | Valid input port status | dsERR_NONE |
| 04 | Call `dsCompositeInTerm()` to term the module | Valid status | dsERR_NONE |status