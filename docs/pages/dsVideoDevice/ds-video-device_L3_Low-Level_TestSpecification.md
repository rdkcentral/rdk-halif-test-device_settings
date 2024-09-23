# Device Settings Video Device L3 Low Level Test Specification and Procedure Documentation

## Table of Contents

- [Overview](#overview)
- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [References](#references)
- [Level 3 Test cases High Level Overview](#level-3-test-cases-high-level-overview)
- [Level 3 Python Test](#level-3-python-test-cases-high-level-overview)

## Overview

This document describes the L3 Low Level Test Specification and Procedure Documentation for the Device Settings Video Device module.

### Acronyms, Terms and Abbreviations

- `HAL` \- Hardware Abstraction Layer, may include some common components
- `DFC`  \- Decoder Format Conversion
- `SoC` \- System on a Chip
- `L3`   \- Level 3 Testing
- `DS`   \- Device Settings
- `HDR`  \- High Dynamic Range
- `FPS`  \- Frames Per Second
- `FRF`  \- Frame Rate Frequency
- `HEVC` \- High Efficiency Video Coding
- `RAFT`  \- Rapid Automation Framework for Testing
- `DUT`   \- Device Under Test
- `NA`   \- Not Applicable
- `Y`    \- Yes

### References

- `High Level Test Specification` - [dsVideoDevice High Level TestSpec](ds-video-device_High-Level_TestSpec.md)
- `Interface header` - [dsVideoDevice HAL header](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsVideoDevice.h)

## Level 3 Test Cases High Level Overview
Below are top test use-case for the Video Display.

|#|Test-case|Description|HAL APIs|Source|Sink|
|-|---------|-----------|--------|------|----|
|1|Verify the Video Display framerate change with pre-change callback.|Play any video content and check the callback is triggered before when the framerate of a display changes|`dsRegisterFrameratePreChangeCB()`|`NA`|`Y`|
|2|Verify the Video Display framerate change with post-change callback|Play any video content and check the callback is triggered after when the framerate of a display changes|`dsRegisterFrameratePostChangeCB()`|`NA`|`Y`|
|3|Set and verify the Zoom mode of the source device|Set the Zoom mode and verify the selected Zoom mode|`dsSetDFC()`, `dsGetDFC()`|`Y`|`NA`|
|4|Select the Device Frame Rate of Sink device |Select the Device Frame Rate of Sink device and verify|`dsSetDisplayframerate()`|`NA`|`Y`|
|5|Set and verify the `FRF` mode|Select the`FRF`mode and verify the selected `FRF` mode|`dsSetFRFMode()`,`dsGetFRFMode()`|`NA`|`Y`|

## Level 3 Python Test Cases High Level Overview

The class diagram below illustrates the flow of dsVideoDevice L3 Python test cases:

```mermaid
---
title: dsVideoDevice - Python Class Flow
---
classDiagram
    testControl <|-- ut_raft
    class ut_raft{
    }
    ut_raft <|-- dsVideoDevice
    dsVideoDevice <|-- L3TestClasses
```

- **testControl**
  - Test Control Module for running rack Testing. This module configures the `DUT` based on the rack configuration file provided to the test.
  - This class is defined in `RAFT` framework. For more details refer [RAFT](https://github.com/rdkcentral/python_raft/blob/1.0.0/README.md)
- **ut_raft**
  - Python based testing framework for writing engineering tests.
  - It provides common functionalities like menu navigation, configuration reader, reading user response etc.
  - For more details [ut-raft](https://github.com/rdkcentral/ut-raft).
- **dsVideoDevice**
  - This is test helper class which communicates with the `L3` C/C++ test running on the `DUT` through menu
- **L3TestClasses**
  - These are the L3 test case classes
  - Each class covers the each test use-case defined in [L3 Test use-cases](#level-3-test-cases-high-level-overview) table

## YAML File Inputs

```mermaid
---
title: dsVideoDevice - YAML
---
classDiagram
    class Config {
        - rackConfiguration
        - platform
    }
    class DeviceConfig {
        - cpePlatformConfiguration
    }
    class PlatformProfile {
        - componentConfigurations
    }
    PlatformProfile <|-- DeviceConfig
    DeviceConfig <|-- Config
    class TestSetupConfig {
        - testSetupConfiguration
    }
    class MenuConfig {
        - menuConfiguration
    }
    MenuConfig <|-- TestSetupConfig
```

- **config.yaml**
  - Identifies the rack configuration and platform used
  - References platform-specific config from `deviceConfig.yaml`
  - For more details refer [RAFT](https://github.com/rdkcentral/python_raft/blob/1.0.0/README.md) and [example_rack_config.yml](https://github.com/rdkcentral/python_raft/blob/1.0.0/examples/configs/example_rack_config.yml)

- **deviceConfig.yaml**
  - Specifies overall configuration for the platform
  - Can be overridden by:
    - Changing locally .yaml file directory
    - Using --deviceConfig command line switch
  - For more details refer [RAFT](https://github.com/rdkcentral/python_raft/blob/1.0.0/README.md) and [example_device_config.yml](https://github.com/rdkcentral/python_raft/blob/1.0.0/examples/configs/example_device_config.yml)

- **componentProfile.yaml/platformProfile.yaml**
  - Contains component-specific configurations
  - Contains platform wide configuration broken down into separate components
  - Example configuration file [dsVideoDevice_Settings](https://github.com/rdkcentral/rdk-halif-test-device_settings/blob/3.1.4/profiles/source/Source_VideoDevice.yaml)

- **testSetupConfig.yaml**
  - This configuration file contains the list of requirements for tests to execute. Eg: Copying the streams, setting environment variables etc.
  - Example configuration file listed below:

```yaml
dsVideoDevice:
  description: "dsVideoDevice Device Settings test setup"
  assets:
    device:
      Common: #List of common requirements for all the tests
        artifacts:
          -  "<URL>/hal_test" #URL Path to the bin files to copy
          -  "<URL>/ut_contol.so" #URL Path to the .so files if any to copy
          -  "<URL>/run.sh"
        execute:
          - ""  #prerequisites commands if required
        streams:
      test1_SetZoomModeAndVerify: #Requirements for specific test
        artifacts:
        execute:
        streams:
      test2_SetDisplayFrameRateAndVerify:
        artifacts:
        execute:
        streams:
    host:
      menu_config: "../../assets/dsVideoDevice_L3_menu.yml" #Menu configuration file
```
- **menuConfig**
  - This configuration file contains the list of menu items for C/C++ L3 test running on `DUT`
  - Example configuration file listed below:

```yaml
dsVideoDevice:
  description: "dsVideoDevice Device Settings testing profile / menu system for UT"
  test:
  control:
    menu:
      type: UT-C # C (UT-C Cunit) / C++ (UT-G (g++ ut-core gtest backend))
      groups:
          name: "L3 dsVideoDevice - Source"
          menu_initialize:
            name: "Initialize dsVideoDevice"
          menu_zoomMode:
            name: "Zoom mode"
            input:
                - "Select the supported zoom mode"
          menu_displayFramerate:
            name: "Display Framerate"
            input:
                - "Select the framerate for display"
                
```

## Test Execution

- Folder Structure
  - assets
    - testSetupConfig.yaml
    - menuConfig.yaml
  - host
    - tests
      - helpers
        - dsVideoDeviceTestHelper.py
      - dsVideoDevice_test1_XYZ.py
      - dsVideoDevice_test2_XYZ.py

- User runs test (eg: test1_XYZ.py)
  - Chooses platform via --config config.yaml and config file
  - --slot 1 is default (optional)
  - Test reads the testSetupConfig.yaml from the assets folder
- Test extracts
  - Specific component configuration
  - validationProfile for the platform
  - Specific test setup requirements
  - Specific test menu configurations
