# Unit Testing Suite For Device Settings HAL

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Description](#description)
- [Reference Documents](#reference-documents)
- [Notes](#notes)

## Acronyms, Terms and Abbreviations

- `L1`  - Functional Tests
- `HAL` - Hardware Abstraction Layer
- `API` - Application Programming Interface
- `DS`  - Device Settings
- `FPD` - Front Panel Display
- `HDMIIn` - HDMI Input
- `CompositeIn` - Composite Input

## Description

This repository contains the Unit Test Suites (L1) for the following submodules of Device Settings  `HAL` :

- `DS` Audio `HAL`
- `DS` Video Device `HAL`
- `DS` Video Port `HAL`
- `DS` Display `HAL`
- `DS` Front Panel Display `HAL`
- `DS` Host `HAL`
- `DS` HDMI Input `HAL`
- `DS` Composite Input `HAL`

## Reference Documents

<!-- Need to update links to rdkcentral and point to branch main-->
|SNo|Document Name|Document Description|Document Link|
|---|-------------|--------------------|-------------|
|1|Device Settings `HAL`|This document provides specific information on each `DS` sub-module's `APIs` for which tests are written in this module|[`DS` `HAL` Guide - v1.0.8]( https://github.com/rdkcentral/rdk-halif-device_settings/blob/1.0.8/docs/pages/README.md "Device Settings `HAL` Guide" )|
|2|`DS` Audio `L1` Tests |`L1` Test Case File for `DS` Audio `HAL`|[test_l1_dsAudio.c - v1.0.3]( https://github.com/rdkcentral/rdk-halif-test-device_settings/blob/1.0.3/src/test_l1_dsAudio.c "test_l1_dsAudio.c" )|
|3|`DS` Video Device `L1` Tests|`L1` Test Case File for `DS` Video Device `HAL`|[test_l1_dsVideoDevice.c - v1.0.3]( https://github.com/rdkcentral/rdk-halif-test-device_settings/blob/1.0.3/src/test_l1_dsVideoDevice.c "test_l1_dsVideoDevice.c" )|
|4|`DS` Video Port `L1` Tests |`L1` Test Case File for `DS` Video Port `HAL`|[test_l1_dsVideoPort.c - v1.0.3]( https://github.com/rdkcentral/rdk-halif-test-device_settings/blob/1.0.3/src/test_l1_dsVideoPort.c "test_l1_dsVideoPort.c" )|
|5|`DS` Display `L1` Tests |`L1` Test Case File for `DS` Display `HAL`|[test_l1_dsDisplay.c - v1.0.3]( https://github.com/rdkcentral/rdk-halif-test-device_settings/blob/1.0.3/src/test_l1_dsDisplay.c "test_l1_dsDisplay.c" )|
|6|`DS` Front Panel Display `L1` Tests |`L1` Test Case File for `DS` Front Panel Display `HAL`|[test_l1_dsFPD.c - v1.0.3]( https://github.com/rdkcentral/rdk-halif-test-device_settings/blob/1.0.3/src/test_l1_dsFPD.c "test_l1_dsFPD.c" )|
|7|`DS` Host `L1` Tests |`L1` Test Case File for `DS` Host `HAL`|[test_l1_dsHost.c - v1.0.3]( https://github.com/rdkcentral/rdk-halif-test-device_settings/blob/1.0.3/src/test_l1_dsHost.c "test_l1_dsHost.c" )|
|8|`DS` HDMI Input `L1` Tests |`L1` Test Case File for `DS` HDMI Input `HAL`|[test_l1_dsHdmiIn.c - v1.0.3]( https://github.com/rdkcentral/rdk-halif-test-device_settings/blob/1.0.3/src/test_l1_dsHdmiIn.c "test_l1_dsHdmiIn.c" )|
|9|`DS` Composite Input `L1` Tests |`L1` Test Case File for `DS` Composite Input `HAL`|[test_l1_dsCompositeIn.c - v1.0.3]( https://github.com/rdkcentral/rdk-halif-test-device_settings/blob/1.0.3/src/test_l1_dsCompositeIn.c "test_l1_dsCompositeIn.c" )|

## Notes

- All APIs in each individual sub-module need to be implemented in this current version. If any API is not supported, please add stub implementation with return type dsERR_OPERATION_NOT_SUPPORTED for the same.
- Building against the actual library may introduce SOC dependencies. Hence, a template SKELETON library is created without SOC dependencies. On the real platform (target), it can be mounted, copied and bound with the actual library.
- The configuration/settings file(s) for certain `DS` sub-modules, specific to a platform (templates in [DS HAL README.md](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/docs/pages/README.md "DS HAL README.md")), should be added in the `profiles/include` directory within the root directory of the DS HAL Test repository.