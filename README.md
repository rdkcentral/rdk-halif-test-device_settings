# Unit Testing Suite For Device Settings HAL

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Description](#description)
- [Reference Documents](#reference-documents)
- [Notes](#notes)

## Acronyms, Terms and Abbreviations

- `L1`  - Functional Tests
- `L2`  - Module functional Testing
- `L3`  - Module testing with External Stimulus is required to validate and control device
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
|2|`DS` Audio Test Suits Specifications |`L1`,`L2`,`L3` Test Specification Documentation for `DS` Audio module.|[dsAudioTestDoc]( docs/pages/dsAudio/)|
|3|`DS` Video Device Test Suits Specifications |`L1`,`L2`,`L3` Test Specification Documentation for `DS` Video Device module.|[dsVideoDeviceTestDoc]( docs/pages/dsVideoDevice/)|
|4|`DS` Video Port  Test Suits Specifications |`L1`,`L2`,`L3` Test Specification Documentation for `DS` Video Port  module.|[dsVideoPortTestDoc]( docs/pages/dsVideoPort/)|
|5|`DS` Display Test Suits Specifications |`L1`,`L2`,`L3` Test Specification Documentation for `DS` Display module.|[dsDisplayTestDoc]( docs/pages/dsDisplay/)|
|6|`DS` Front Panel Display Test Suits Specifications |`L1`,`L2`,`L3` Test Specification Documentation for `DS` Front Panel Display module.|[dsFPDTestDoc]( docs/pages/dsFPD/)|
|7|`DS` Host Test Suits Specifications |`L1`,`L2`,`L3` Test Specification Documentation for `DS` Host module.|[dsHostTestDoc]( docs/pages/dsHost/)|
|8|`DS` HDMI Input Test Suits Specifications |`L1`,`L2`,`L3` Test Specification Documentation for `DS` HDMI Input module.|[dsHDMIInTestDoc]( docs/pages/dsHDMIIn/)|
|9|`DS` Composite Input Test Suits Specifications |`L1`,`L2`,`L3` Test Specification Documentation for `DS` Composite Input module.|[dsCompositeInTestDoc]( docs/pages/dsCompositeIn/)|

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

- Install Python Environment and Activation Scripts please check the[HPK Documentation](https://github.com/rdkcentral/rdk-hpk-documentation/blob/main/README.md)
