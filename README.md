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
- `NA` - Not Applicable

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
|2|`DS` Audio Test Suits Specifications |`L1`,`L2`,`L3` Test Specification Documentation for `DS` Audio module.|Refer [dsAudio](#l1-l2-l3-testprocedure-documents)|
|3|`DS` Video Device Test Suits Specifications |`L1`,`L2`,`L3` Test Specification Documentation for `DS` Video Device module.|Refer [dsVideoDevice](#l1-l2-l3-testprocedure-documents)|
|4|`DS` Video Port  Test Suits Specifications |`L1`,`L2`,`L3` Test Specification Documentation for `DS` Video Port  module.|Refer [dsVideoPort](#l1-l2-l3-testprocedure-documents)|
|5|`DS` Display Test Suits Specifications |`L1`,`L2`,`L3` Test Specification Documentation for `DS` Display module.|Refer [dsDisplay](#l1-l2-l3-testprocedure-documents)|
|6|`DS` Front Panel Display Test Suits Specifications |`L1`,`L2`,`L3` Test Specification Documentation for `DS` Front Panel Display module.|Refer [dsFPD](#l1-l2-l3-testprocedure-documents)|
|7|`DS` Host Test Suits Specifications |`L1`,`L2`,`L3` Test Specification Documentation for `DS` Host module.|Refer [dsHost](#l1-l2-l3-testprocedure-documents)|
|8|`DS` HDMI Input Test Suits Specifications |`L1`,`L2`,`L3` Test Specification Documentation for `DS` HDMI Input module.|Refer [dsHdmiIn](#l1-l2-l3-testprocedure-documents)|
|9|`DS` Composite Input Test Suits Specifications |`L1`,`L2`,`L3` Test Specification Documentation for `DS` Composite Input module.|Refer [dsCompositeIn](#l1-l2-l3-testprocedure-documents)|

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

- Profiles files defines the configuration for the platform available for sink and source

|`DS` Module|Sink Profile yaml|Source Profile yaml|
|-----------|-----------------|-------------------|
|dsAudio|[Sink_AudioSettings.yaml](./profiles/sink/Sink_AudioSettings.yaml)|[Source_AudioSettings.yaml](./profiles/source/Source_AudioSettings.yaml)|
|dsDisplay|[Sink_4K_Display.yaml](./profiles/sink/Sink_4K_Display.yaml)|[Source_4K_Display.yaml](./profiles/source/Source_4K_Display.yaml)|
|dsFPD|[Sink_FPD.yaml](./profiles/sink/Sink_FPD.yaml)|[Source_FPD.yaml](./profiles/source/Source_FPD.yaml)|
|dsHost|[Sink_HostSettings.yaml](./profiles/sink/Sink_HostSettings.yaml)|[Source_HostSettings.yaml](./profiles/source/Source_HostSettings.yaml)|
|dsCompositeIn|[Sink_CompositeInput.yaml](./profiles/sink/Sink_CompositeInput.yaml)|`NA`|
|dsHdmiIn|[Sink_HDMIIN.yaml](./profiles/sink/Sink_HDMIIN.yaml)|[Source_HDMIIN.yaml](./profiles/source/Source_HDMIIN.yaml)|
|dsVideoDevice|[Sink_2K_VideoDevice.yaml](./profiles/sink/Sink_2K_VideoDevice.yaml) [Sink_4K_VideoDevice.yaml](./profiles/sink/Sink_4K_VideoDevice.yaml)|[Source_VideoDevice.yaml](./profiles/source/Source_VideoDevice.yaml)|
|dsVideoPort|[Sink_4K_VideoPort.yaml](./profiles/sink/Sink_4K_VideoPort.yaml)|[Source_4K_VideoPort.yaml](./profiles/source/Source_4K_VideoPort.yaml)|

### Setting Python environment for running the `L1` `L2` and `L3` automation test cases

- For running the `L1` `L2` and `L3` test suite, a host PC or server with a Python environment is required.
- Install Python Environment and Activation Scripts as detailed in the [HPK Documentation](https://github.com/rdkcentral/rdk-hpk-documentation/tree/main?tab=readme-ov-file#installing-the-python-environment-for-l3-testing-suite)
- To run the `L1` and `L2` test cases of `DS` sub-modules follow the "`L1` `L2` TestProcedure docs". And, to run the `L3` test cases of `DS` sub-modules follow the "`L3` TestProcedure docs" mentioned in below table.

## `L1` `L2` `L3` TestProcedure Documents

|`DS` Module|L1 L2 TestProcedure docs|L3 TestProcedure docs|
|-----------|------------------------|---------------------|
|dsAudio|[ds-audio_High-Level_TestSpecification.md](./docs/pages/dsAudio/ds-audio_High-Level_TestSpecification.md) [ds-audio_L1_L2_TestProcedure.md](./docs/pages/dsAudio/ds-audio_L1_L2_TestProcedure.md) [ds-audio_L2_Low-Level_TestSpecification.md](./docs/pages/dsAudio/ds-audio_L2_Low-Level_TestSpecification.md)|[ds-audio_High-Level_TestSpecification.md](./docs/pages/dsAudio/ds-audio_High-Level_TestSpecification.md) [ds-audio_L3_TestProcedure.md](./docs/pages/dsAudio/ds-audio_L3_TestProcedure.md)|
|dsDisplay|[ds-display-high-Level_TestSpec.md](./docs/pages/dsDisplay/ds-display-high-Level_TestSpec.md) [ds-display_L1_L2_TestProcedure.md](./docs/pages/dsDisplay/ds-display_L1_L2_TestProcedure.md) [ds-display-L2-Low-Level_TestSpec.md](./docs/pages/dsDisplay/ds-display-L2-Low-Level_TestSpec.md)|[ds-display-high-Level_TestSpec.md](./docs/pages/dsDisplay/ds-display-high-Level_TestSpec.md) [ds-display_L3_TestProcedure.md](./docs/pages/dsDisplay/ds-display_L3_TestProcedure.md)|
|dsFPD|[ds-front-panel-display_High-Level_TestSpec.md](./docs/pages/dsFPD/ds-front-panel-display_High-Level_TestSpec.md) [ds-front-panel-display_L1_L2_TestProcedure.md](./docs/pages/dsFPD/ds-front-panel-display_L1_L2_TestProcedure.md) [ds-front-panel-display_L2_Low-Level_TestSpecification.md](./docs/pages/dsFPD/ds-front-panel-display_L2_Low-Level_TestSpecification.md)|[ds-front-panel-display_High-Level_TestSpec.md](./docs/pages/dsFPD/ds-front-panel-display_High-Level_TestSpec.md) [ds-front-panel-display_L3_TestProcedure.md](./docs/pages/dsFPD/ds-front-panel-display_L3_TestProcedure.md)|
|dsHost|[ds-host_High-Level_TestSpecification.md](./docs/pages/dsHost/ds-host_High-Level_TestSpecification.md) [ds-host_L1_L2_TestProcedure.md](./docs/pages/dsHost/ds-host_L1_L2_TestProcedure.md) [ds-host_L2_Low-Level_TestSpecification.md](./docs/pages/dsHost/ds-host_L2_Low-Level_TestSpecification.md)|[ds-host_High-Level_TestSpecification.md](./docs/pages/dsHost/ds-host_High-Level_TestSpecification.md) [ds-host_L3_TestProcedure.md](./docs/pages/dsHost/ds-host_L3_TestProcedure.md)|
|dsCompositeIn|[ds-compositeIn-High-Level_TestSpec.md](./docs/pages/dsCompositeIn/ds-compositeIn-High-Level_TestSpec.md) [ds-compositeIn_L1_L2_TestProcedure.md](./docs/pages/dsCompositeIn/ds-compositeIn_L1_L2_TestProcedure.md) [ds-compositeIn-L2-Low-Level_TestSpec.md](./docs/pages/dsCompositeIn/ds-compositeIn-L2-Low-Level_TestSpec.md)|[ds-compositeIn-High-Level_TestSpec.md](./docs/pages/dsCompositeIn/ds-compositeIn-High-Level_TestSpec.md) [ds-compositeIn-L3-TestProcedure.md](./docs/pages/dsCompositeIn/ds-compositeIn-L3-TestProcedure.md)|
|dsHdmiIn|[ds-hdmi-in-High-Level_TestSpec.md](./docs/pages/dsHDMIIn/ds-hdmi-in-High-Level_TestSpec.md) [ds-hdmi-in_L1_L2_TestProcedure.md](./docs/pages/dsHDMIIn/ds-hdmi-in_L1_L2_TestProcedure.md) [ds-hdmi-in-L2-Low-Level_TestSpec.md](./docs/pages/dsHDMIIn/ds-hdmi-in-L2-Low-Level_TestSpec.md)|[ds-hdmi-in-High-Level_TestSpec.md](./docs/pages/dsHDMIIn/ds-hdmi-in-High-Level_TestSpec.md) [ds-hdmi-in_L3_Test-Procedure.md](./docs/pages/dsHDMIIn/ds-hdmi-in_L3_Test-Procedure.md)|
|dsVideoDevice|[ds-video-device_High-Level_TestSpec.md](./docs/pages/dsVideoDevice/ds-video-device_High-Level_TestSpec.md) [ds-video-device_L1_L2_TestProcedure.md](./docs/pages/dsVideoDevice/ds-video-device_L1_L2_TestProcedure.md) [ds-video-device_L2-Low-Level_TestSpec.md](./docs/pages/dsVideoDevice/ds-video-device_L2-Low-Level_TestSpec.md)|[ds-video-device_High-Level_TestSpec.md](./docs/pages/dsVideoDevice/ds-video-device_High-Level_TestSpec.md) [ds-video-device_L3_TestProcedure.md](./docs/pages/dsVideoDevice/ds-video-device_L3_TestProcedure.md)|
|dsVideoPort|[ds-video-port_High-Level_TestSpec.md](./docs/pages/dsVideoPort/ds-video-port_High-Level_TestSpec.md) [ds-video-port_L1_L2_TestProcedure.md](./docs/pages/dsVideoPort/ds-video-port_L1_L2_TestProcedure.md) [ds-video-port_L2_Low-Level_TestSpecification.md](./docs/pages/dsVideoPort/ds-video-port_L2_Low-Level_TestSpecification.md)|[ds-video-port_High-Level_TestSpec.md](./docs/pages/dsVideoPort/ds-video-port_High-Level_TestSpec.md) [ds-video-port_L3_Test-Procedure.md](./docs/pages/dsVideoPort/ds-video-port_L3_Test-Procedure.md)|
