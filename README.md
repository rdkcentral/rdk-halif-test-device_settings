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
|2|`DS` Audio Test Suits Specifications |`L1`,`L2`,`L3` Test Specification Documentation for `DS` Audio module.|Refer [dsAudio](#l1-l2-l3-testprocedure-documents)|
|3|`DS` Video Device Test Suits Specifications |`L1`,`L2`,`L3` Test Specification Documentation for `DS` Video Device module.|Refer [dsVideoDevice](#l1-l2-l3-testprocedure-documents)|
|4|`DS` Video Port  Test Suits Specifications |`L1`,`L2`,`L3` Test Specification Documentation for `DS` Video Port  module.|Refer [dsVideoPort](#l1-l2-l3-testprocedure-documents)|
|5|`DS` Display Test Suits Specifications |`L1`,`L2`,`L3` Test Specification Documentation for `DS` Display module.|Refer [dsDisplay](#l1-l2-l3-testprocedure-documents)|
|6|`DS` Front Panel Display Test Suits Specifications |`L1`,`L2`,`L3` Test Specification Documentation for `DS` Front Panel Display module.|Refer [dsFPD](#l1-l2-l3-testprocedure-documents)|
|7|`DS` Host Test Suits Specifications |`L1`,`L2`,`L3` Test Specification Documentation for `DS` Host module.|Refer [dsHost](#l1-l2-l3-testprocedure-documents)|
|8|`DS` HDMI Input Test Suits Specifications |`L1`,`L2`,`L3` Test Specification Documentation for `DS` HDMI Input module.|Refer [dsHdmiIn](#l1-l2-l3-testprocedure-documents)|
|9|`DS` Composite Input Test Suits Specifications |`L1`,`L2`,`L3` Test Specification Documentation for `DS` Composite Input module.|Refer [dsCompositeIn](#l1-l2-l3-testprocedure-documents)|

## `L1` `L2` `L3` TestProcedure Documents

|`DS` Module|L1 L2 TestProcedure docs|L3 TestProcedure docs|
|-----------|------------------------|---------------------|
|dsAudio|[ds-audio_High-Level_TestSpecification.md](./docs/pages/dsAudio/ds-audio_High-Level_TestSpecification.md), [ds-audio_L2_Low-Level_TestSpecification.md](./docs/pages/dsAudio/ds-audio_L2_Low-Level_TestSpecification.md)|[ds-audio_High-Level_TestSpecification.md](./docs/pages/dsAudio/ds-audio_High-Level_TestSpecification.md), [ds-audio_L3_Low-Level_TestSpecification.md](./docs/pages/dsAudio/ds-audio_L3_Low-Level_TestSpecification.md), [ds-audio_L3_TestProcedure.md](./docs/pages/dsAudio/ds-audio_L3_TestProcedure.md)|
|dsDisplay|[ds-display-high-Level_TestSpec.md](./docs/pages/dsDisplay/ds-display-high-Level_TestSpec.md),  [ds-display-L2-Low-Level_TestSpec.md](./docs/pages/dsDisplay/ds-display-L2-Low-Level_TestSpec.md)|[ds-display-high-Level_TestSpec.md](./docs/pages/dsDisplay/ds-display-high-Level_TestSpec.md), [ds-display_L3_Low-Level_TestSpecification.md](./docs/pages/dsDisplay/ds-display_L3_Low-Level_TestSpecification.md), [ds-display_L3_TestProcedure.md](./docs/pages/dsDisplay/ds-display_L3_TestProcedure.md)|
|dsFPD|[ds-front-panel-display_High-Level_TestSpec.md](./docs/pages/dsFPD/ds-front-panel-display_High-Level_TestSpec.md), [ds-front-panel-display_L2_Low-Level_TestSpecification.md](./docs/pages/dsFPD/ds-front-panel-display_L2_Low-Level_TestSpecification.md)|[ds-front-panel-display_High-Level_TestSpec.md](./docs/pages/dsFPD/ds-front-panel-display_High-Level_TestSpec.md), [ds-front-panel-display_L3_Low-Level_TestSpecification.md](./docs/pages/dsFPD/ds-front-panel-display_L3_Low-Level_TestSpecification.md), [ds-front-panel-display_L3_TestProcedure.md](./docs/pages/dsFPD/ds-front-panel-display_L3_TestProcedure.md)|
|dsHost|[ds-host_High-Level_TestSpecification.md](./docs/pages/dsHost/ds-host_High-Level_TestSpecification.md), [ds-host_L2_Low-Level_TestSpecification.md](./docs/pages/dsHost/ds-host_L2_Low-Level_TestSpecification.md)|[ds-host_High-Level_TestSpecification.md](./docs/pages/dsHost/ds-host_High-Level_TestSpecification.md),[ds-host_L3_TestProcedure.md](./docs/pages/dsHost/ds-host_L3_TestProcedure.md), [ds-host_L3_Low-Level_TestSpec.md](./docs/pages/dsHost/ds-host_L3_Low-Level_TestSpec.md)|
|dsCompositeIn|[ds-compositeIn-High-Level_TestSpec.md](./docs/pages/dsCompositeIn/ds-compositeIn-High-Level_TestSpec.md), [ds-compositeIn-L2-Low-Level_TestSpec.md](./docs/pages/dsCompositeIn/ds-compositeIn-L2-Low-Level_TestSpec.md)|[ds-compositeIn-High-Level_TestSpec.md](./docs/pages/dsCompositeIn/ds-compositeIn-High-Level_TestSpec.md), [ds-compositeIn-L3-Low-Level-TestSpec.md](./docs/pages/dsCompositeIn/ds-compositeIn-L3-Low-Level-TestSpec.md), [ds-compositeIn-L3-TestProcedure.md](./docs/pages/dsCompositeIn/ds-compositeIn-L3-TestProcedure.md)|
|dsHdmiIn|[ds-hdmi-in-High-Level_TestSpec.md](./docs/pages/dsHDMIIn/ds-hdmi-in-High-Level_TestSpec.md), [ds-hdmi-in-L2-Low-Level_TestSpec.md](./docs/pages/dsHDMIIn/ds-hdmi-in-L2-Low-Level_TestSpec.md)|[ds-hdmi-in-High-Level_TestSpec.md](./docs/pages/dsHDMIIn/ds-hdmi-in-High-Level_TestSpec.md), [ds-Hdmi-In_L3_Low-Level_TestSpecification.md](./docs/pages/dsHDMIIn/ds-Hdmi-In_L3_Low-Level_TestSpecification.md)[ds-hdmi-in_L3_Test-Procedure.md](./docs/pages/dsHDMIIn/ds-hdmi-in_L3_Test-Procedure.md)|
|dsVideoDevice|[ds-video-device_High-Level_TestSpec.md](./docs/pages/dsVideoDevice/ds-video-device_High-Level_TestSpec.md), [ds-video-device_L2-Low-Level_TestSpec.md](./docs/pages/dsVideoDevice/ds-video-device_L2-Low-Level_TestSpec.md)|[ds-video-device_High-Level_TestSpec.md](./docs/pages/dsVideoDevice/ds-video-device_High-Level_TestSpec.md), [ds-video-device_L3_Low-Level_TestSpecification.md](./docs/pages/dsVideoDevice/ds-video-device_L3_Low-Level_TestSpecification.md), [ds-video-device_L3_TestProcedure.md](./docs/pages/dsVideoDevice/ds-video-device_L3_TestProcedure.md)|
|dsVideoPort|[ds-video-port_High-Level_TestSpec.md](./docs/pages/dsVideoPort/ds-video-port_High-Level_TestSpec.md), [ds-video-port_L2_Low-Level_TestSpecification.md](./docs/pages/dsVideoPort/ds-video-port_L2_Low-Level_TestSpecification.md)|[ds-video-port_High-Level_TestSpec.md](./docs/pages/dsVideoPort/ds-video-port_High-Level_TestSpec.md), [ds-video-port_L3_Low-Level_TestSpecification.md](./docs/pages/dsVideoPort/ds-video-port_L3_Low-Level_TestSpecification.md), [ds-video-port_L3_Test-Procedure.md](./docs/pages/dsVideoPort/ds-video-port_L3_Test-Procedure.md)|

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

- Install Python Environment and Activation Scripts please check the[HPK Documentation](https://github.com/rdkcentral/rdk-hpk-documentation/blob/main/README.md)
