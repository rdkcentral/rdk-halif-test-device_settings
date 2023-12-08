# Unit Testing Suite For Device Settings HAL

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Description](#description)
- [Reference Documents](#reference-documents)

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

- [`DS` Audio `HAL`]( https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsAudio.h )
- [`DS` Video Device `HAL`]( https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsVideoDevice.h )
- [`DS` Video Port `HAL`]( https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsVideoPort.h )
- [`DS` Display `HAL`]( https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsDisplay.h )
- [`DS` Front Panel Display `HAL`]( https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsFPD.h )
- [`DS` Host `HAL`]( https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsHost.h )
- [`DS` HDMI Input `HAL`]( https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsHdmiIn.h )
- [`DS` Composite Input `HAL`]( https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsCompositeIn.h )

## Reference Documents

<!-- Need to update links to rdkcentral and point to branch main-->
|SNo|Document Name|Document Description|Document Link|
|---|-------------|--------------------|-------------|
|1|Device Settings `HAL`|This document provides specific information on each `DS` sub-module's `APIs` for which tests are written in this module|[`DS` `HAL` Guide]( https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/docs/pages/README.md "Device Settings `HAL` Guide" )|
|2|`DS` Audio `L1` Tests |`L1` Test Case File for `DS` Audio `HAL` |[test_l1_dsAudio.c]( https://github.com/comcast-sky/rdk-components-haltest-devicesettings/blob/main/src/test_l1_dsAudio.c "test_l1_dsAudio.c" )|
|3|`DS` Video Device `L1` Tests |`L1` Test Case File for `DS` Video Device `HAL` |[test_l1_dsVideoDevice.c]( https://github.com/comcast-sky/rdk-components-haltest-devicesettings/blob/main/src/test_l1_dsVideoDevice.c "test_l1_dsVideoDevice.c" )|
|4|`DS` Video Port `L1` Tests |`L1` Test Case File for `DS` Video Port `HAL` |[test_l1_dsVideoPort.c]( https://github.com/comcast-sky/rdk-components-haltest-devicesettings/blob/main/src/test_l1_dsVideoPort.c "test_l1_dsVideoPort.c" )|
|5|`DS` Display `L1` Tests |`L1` Test Case File for `DS` Display `HAL` |[test_l1_dsDisplay.c]( https://github.com/comcast-sky/rdk-components-haltest-devicesettings/blob/main/src/test_l1_dsDisplay.c "test_l1_dsDisplay.c" )|
|6|`DS` Front Panel Display `L1` Tests |`L1` Test Case File for `DS` Front Panel Display `HAL` |[test_l1_dsFPD.c]( https://github.com/comcast-sky/rdk-components-haltest-devicesettings/blob/main/src/test_l1_dsFPD.c "test_l1_dsFPD.c" )|
|7|`DS` Host `L1` Tests |`L1` Test Case File for `DS` Host `HAL` |[test_l1_dsHost.c]( https://github.com/comcast-sky/rdk-components-haltest-devicesettings/blob/main/src/test_l1_dsHost.c "test_l1_dsHost.c" )|
|8|`DS` HDMI Input `L1` Tests |`L1` Test Case File for `DS` HDMI Input `HAL` |[test_l1_dsHdmiIn.c]( https://github.com/comcast-sky/rdk-components-haltest-devicesettings/blob/main/src/test_l1_dsHdmiIn.c "test_l1_dsHdmiIn.c" )|
|9|`DS` Composite Input `L1` Tests |`L1` Test Case File for `DS` Composite Input `HAL` |[test_l1_dsCompositeIn.c]( https://github.com/comcast-sky/rdk-components-haltest-devicesettings/blob/main/src/test_l1_dsCompositeIn.c "test_l1_dsCompositeIn.c" )|
