# Unit Testing Suite For Device Settings HAL

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Description](#description)
- [Reference Documents](#reference-documents)
- [How to build the test suite](#how-to-build-the-test-suite)
- [Notes](#notes)
- [Manual way of running the L1 and L2 test cases](#manual-way-of-running-the-l1-and-l2-test-cases)
- [Setting Python environment for running the L1 L2 and L3 automation test cases](#setting-python-environment-for-running-the-l1-l2-and-l3-automation-test-cases)

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
- `Low-Level Test Specification` : These specification will deeper into the technical details. They will define specific test cases with inputs, expected outputs, and pass/fail criteria for individual functionalities, modules, or APIs.

## Description

This repository contains the Unit Test Suites (`L1` , `L2` and `L3`) for the following submodules of Device Settings  `HAL` :

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
|2|`DS` Audio Test Suits Specifications |`L1`,`L2`,`L3` Test Specification Documentation for `DS` Audio module.|[dsAudioTestDoc]( https://github.com/rdkcentral/rdk-halif-test-device_settings/tree/main/docs/pages/dsAudio)|
|3|`DS` Video Device Test Suits Specifications |`L1`,`L2`,`L3` Test Specification Documentation for `DS` Video Device module.|[dsVideoDeviceTestDoc](https://github.com/rdkcentral/rdk-halif-test-device_settings/tree/main/docs/pages/dsVideoDevice)|
|4|`DS` Video Port  Test Suits Specifications |`L1`,`L2`,`L3` Test Specification Documentation for `DS` Video Port  module.|[dsVideoPortTestDoc](https://github.com/rdkcentral/rdk-halif-test-device_settings/tree/main/docs/pages/dsVideoPort)|
|5|`DS` Display Test Suits Specifications |`L1`,`L2`,`L3` Test Specification Documentation for `DS` Display module.|[dsDisplayTestDoc](https://github.com/rdkcentral/rdk-halif-test-device_settings/tree/main/docs/pages/dsDisplay)|
|6|`DS` Front Panel Display Test Suits Specifications |`L1`,`L2`,`L3` Test Specification Documentation for `DS` Front Panel Display module.|[dsFPDTestDoc](https://github.com/rdkcentral/rdk-halif-test-device_settings/tree/main/docs/pages/dsFPD)|
|7|`DS` Host Test Suits Specifications |`L1`,`L2`,`L3` Test Specification Documentation for `DS` Host module.|[dsHostTestDoc](https://github.com/rdkcentral/rdk-halif-test-device_settings/tree/main/docs/pages/dsHost)|
|8|`DS` HDMI Input Test Suits Specifications |`L1`,`L2`,`L3` Test Specification Documentation for `DS` HDMI Input module.|[dsHDMIInTestDoc](https://github.com/rdkcentral/rdk-halif-test-device_settings/tree/main/docs/pages/dsHDMIIn)|
|9|`DS` Composite Input Test Suits Specifications |`L1`,`L2`,`L3` Test Specification Documentation for `DS` Composite Input module.|[dsCompositeInTestDoc](https://github.com/rdkcentral/rdk-halif-test-device_settings/tree/main/docs/pages/dsCompositeIn)|

## Notes

- All APIs in each individual sub-module need to be implemented in this current version. If any API is not supported, please add stub implementation with return type dsERR_OPERATION_NOT_SUPPORTED for the same.
- Building against the actual library may introduce SOC dependencies. Hence, a template SKELETON library is created without SOC dependencies. On the real platform (target), it can be mounted, copied and bound with the actual library.
- When executing the binary, ensure to include a platform-specific profile file as an argument for the designated test cases. The following example illustrates this:

## How to build the test suite

In order to build the test suits, there is a requirement to supply the toolchain, either as a vendor independent toolchain, an SDK, or an RDK Docker Toolchain .

For more information about RDK Docker Toolchain, please check [RDK Docker Toolchain](https://github.com/rdkcentral/ut-core/wiki/FAQ:-RDK-Docker-Toolchain)

- Export the Toolchain Path:

```bash
export TOOLCHAIN_PATH=/opt/toolchains/rdk-glibc-x86_64/sysroots/armv7at2hf-neon-rdk-linux-gnueabi
export CC="arm-rdk-linux-gnueabi-gcc  -march=armv7-a -mthumb -mfpu=neon -mfloat-abi=hard --sysroot=$TOOLCHAIN_PATH"
```

- Clone the `HAL` Repository:

```bash
git clone git@github.com:rdkcentral/rdk-halif-device_settings.git
```

- Set Project Version:

If you want to build the test repository with a specific tag or branch, set the UT_PROJECT_VERSION variable accordingly. If not set, the default main branch will be used.

```bash
export UT_PROJECT_VERSION=1.0.1  # Build using a specific tag
```

or

```bash
export UT_PROJECT_VERSION=develop  # Build using a specific branch
```

- Build Targets:

 There are two targets for the platform

  1. linux - (default)
  2. arm - TARGET=arm

```bash
build_ut.sh TARGET=arm
```

- `build_ut.sh` script will clone the hal-test repo, ut-core and generate a `hal_test_dshal` binary in `ut/bin/` upon successful completion.

### Manual way of running the `L1` and `L2` test cases

```bash
 ./hal_test_dshal -p Sink_AudioSettings.yaml
 ```

Alternatively, use the run.sh script with the profile file:

```bash
./run.sh -p /absolute/path/to/profile/file
 ```

- Profiles files defines the configuration for the platform available for sink and source [profile yaml file](https://github.com/rdkcentral/rdk-halif-test-device_settings/tree/main/profiles)

### Setting Python environment for running the `L1` `L2` and `L3` automation test cases

- For running the `L1` `L2` and `L3` test suite, a host PC or server with a Python environment is required.
- Install Python Environment and Activation Scripts as detailed in the [HPK Documentation](https://github.com/rdkcentral/rdk-hpk-documentation/tree/main?tab=readme-ov-file#installing-the-python-environment-for-l3-testing-suite)
- To run the `L1` and `L2` test cases of `DS` sub-modules follow the [L1 L2 TestProcedure docs](https://github.com/rdkcentral/rdk-halif-test-device_settings/tree/main/docs/pages)
- To run the `L3` test cases of `DS` sub-modules follow the [L3 TestProcedure docs](https://github.com/rdkcentral/rdk-halif-test-device_settings/tree/main/docs/pages)
