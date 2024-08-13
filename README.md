# Unit Testing Suite For Device Settings HAL

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Description](#description)
- [Reference Documents](#reference-documents)
- [Notes](#notes)

## Acronyms, Terms and Abbreviations

- `L1`  - Functional Tests
- `L2`  - Module functional Testing
- `HAL` - Hardware Abstraction Layer
- `API` - Application Programming Interface
- `DS`  - Device Settings
- `FPD` - Front Panel Display
- `HDMIIn` - HDMI Input
- `CompositeIn` - Composite Input
- `High-Level Test Specification` : These specification will provide a broad overview of the system's functionality from the callers' perspective. It focuses on major use cases, system behavior, and overall caller experience.
- `Low-Level Test Specification` : These specification will delve deeper into the technical details. They will define specific test cases with inputs, expected outputs, and pass/fail criteria for individual functionalities, modules, or APIs.

## Description

This repository contains the Unit Test Suites (L1 & L2) for the following submodules of Device Settings  `HAL` :

- `DS` Audio `HAL`
- `DS` Video Device `HAL`
- `DS` Video Port `HAL`
- `DS` Display `HAL`
- `DS` Front Panel Display `HAL`
- `DS` Host `HAL`
- `DS` HDMI Input `HAL`
- `DS` Composite Input `HAL`

## Reference Documents

|SNo|Document Name|Document Description|Document Link|
|---|-------------|--------------------|-------------|
|1|Device Settings `HAL`|This document provides specific information on each `DS` sub-module's `APIs` for which tests are written in this module|[`DS` `HAL` Guide](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/docs/pages/README.md)|
|2|`DS` Audio High-Level Test Spec |`High Level Test Specification` Documentation for `DS` Audio module.|[ds-audio_High-Level_TestSpecification.md]( docs/pages/ds-audio_High-Level_TestSpecification.md)|
|3|`DS` Audio `L2` Low-Level Test Spec |`L2` `Low Level Test Specification` Documentation for `DS` Audio module|[ds-audio_L2_Low-Level_TestSpecification.md]( docs/pages/ds-audio_L2_Low-Level_TestSpecification.md)|
|4|`DS` Video Device High-Level Test Spec |`High Level Test Specification` Documentation for `DS` Video Device module.|[ds-video-device_High-Level_TestSpec.md]( docs/pages/ds-video-device_High-Level_TestSpec.md)|
|5|`DS` Video Device `L2` Low-Level Test Spec |`L2` `Low Level Test Specification` Documentation for `DS` Video Device module|[ds-video-device_L2-Low-Level_TestSpec.md]( docs/pages/ds-video-device_L2-Low-Level_TestSpec.md)|
|6|`DS` Video Port High-Level Test Spec |`High Level Test Specification` Documentation for `DS` Video Port module.|[ds-video-port_High-Level_TestSpec.md]( docs/pages/ds-video-port_High-Level_TestSpec.md)|
|7|`DS` Video Port `L2` Low-Level Test Spec |`L2` `Low Level Test Specification` Documentation for `DS` Video Port module|[ds-video-port_L2_Low-Level_TestSpecification.md]( docs/pages/ds-video-port_L2_Low-Level_TestSpecification.md)|
|8|`DS` Display High-Level Test Spec |`High Level Test Specification` Documentation for `DS` Display module.|[ds-display-high-Level_TestSpec.md]( docs/pages/ds-display-high-Level_TestSpec.md)|
|9|`DS` Display `L2` Low-Level Test Spec |`L2` `Low Level Test Specification` Documentation for `DS` Display module|[ds-display-L2-Low-Level_TestSpec.md]( docs/pages/ds-display-L2-Low-Level_TestSpec.md)|
|10|`DS` Front Panel Display High-Level Test Spec |`High Level Test Specification` Documentation for `DS` Front Panel Display module.|[ds-front-panel-display_High-Level_TestSpec.md]( docs/pages/ds-front-panel-display_High-Level_TestSpec.md)|
|11|`DS` Front Panel Display `L2` Low-Level Test Spec |`L2` `Low Level Test Specification` Documentation for `DS` Front Panel Display module|[ds-front-panel-display_L2_Low-Level_TestSpecification.md]( docs/pages/ds-front-panel-display_L2_Low-Level_TestSpecification.md)|
|12|`DS` Host High-Level Test Spec |`High Level Test Specification` Documentation for `DS` Host module.|[ds-host_High-Level_TestSpecification.md]( docs/pages/ds-host_High-Level_TestSpecification.md)|
|13|`DS` Host `L2` Low-Level Test Spec |`L2` `Low Level Test Specification` Documentation for `DS` Host module|[ds-host_L2_Low-Level_TestSpecification.md]( docs/pages/ds-host_L2_Low-Level_TestSpecification.md)|
|14|`DS` HDMI Input High-Level Test Spec |`High Level Test Specification` Documentation for `DS` HDMI Input module.|[ds-hdmi-in-High-Level_TestSpec.md]( docs/pages/ds-hdmi-in-High-Level_TestSpec.md)|
|15|`DS` HDMI Input `L2` Low-Level Test Spec |`L2` `Low Level Test Specification` Documentation for `DS` HDMI Input module|[ds-hdmi-in-L2-Low-Level_TestSpec.md]( docs/pages/ds-hdmi-in-L2-Low-Level_TestSpec.md)|
|16|`DS` Composite Input High-Level Test Spec |`High Level Test Specification` Documentation for `DS` Composite Input module.|[ds-compositeIn-High-Level_TestSpec.md]( docs/pages/ds-compositeIn-High-Level_TestSpec.md)|
|17|`DS` Composite Input `L2` Low-Level Test Spec |`L2` `Low Level Test Specification` Documentation for `DS` Composite Input module|[ds-compositeIn-L2-Low-Level_TestSpec.md]( docs/pages/ds-compositeIn-L2-Low-Level_TestSpec.md)|

## Notes

- All APIs in each individual sub-module need to be implemented in this current version. If any API is not supported, please add stub implementation with return type dsERR_OPERATION_NOT_SUPPORTED for the same.
- Building against the actual library may introduce SOC dependencies. Hence, a template SKELETON library is created without SOC dependencies. On the real platform (target), it can be mounted, copied and bound with the actual library.
- When executing the binary, ensure to include a platform-specific profile file as an argument for the designated test cases. The following example illustrates this:

```bash
 ./hal_test -p Sink_AudioSettings.yaml
 ```

Alternatively, use the run.sh script with the profile file:

```bash
./run.sh -p /absolute/path/to/profile/file
 ```

- Profiles files defines the configuration for the platform available for sink and source [profile yaml file](./profiles/)
