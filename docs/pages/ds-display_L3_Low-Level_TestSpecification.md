# Device Settings Display L3 Low Level Test Specification and Procedure Documentation

## Table of Contents

- [Overview](#overview)
- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [References](#references)
- [Level 3 Test cases High Level Overview](#level-3-test-cases-high-level-overview)

## Overview

This document describes the L3 Low Level Test Specification and Procedure Documentation for the Device Settings Display module.

### Acronyms, Terms and Abbreviations

- `HAL`  \- Hardware Abstraction Layer, may include some common components
- `UT`   \- Unit Test(s)
- `OEM`  \- Original Equipment Manufacture
- `EDID` \- Extended Display Identification Data
- `Y`    \- yes supported
- `NA`   \- Not Supported

### References

- `High Level Test Specification` - [dsDisplay High Level TestSpec](ds-display-high-Level_TestSpec.md)

- `HAL Interface file` - [dsDisplay Header 4.0.0](https://github.com/rdkcentral/rdk-halif-device_settings/blob/4.0.0/include/dsDisplay.h)

## Level 3 Test Cases High Level Overview

Below are the top test use cases for the display.

|#|Test-case|Description|Focus APIs|
|-|---------|-----------|----------|
|1|Verify Display Events with callbacks|Monitor and verify that the callbacks are triggered correctly for each display event |`dsRegisterDisplayEventCallback()`|
|2|Gets the EDID information|Verify the functionality of retrieving the EDID information of a display |`dsGetEDID()`|
|3|Gets the EDID buffer and EDID length|Verify the functionality of retrieving the EDID bytes of a display |`dsGetEDIDBytes()`|
|4|Gets Aspect Ratio | Verify the functionality of retrieving the aspect ratio of a display | `dsGetDisplayAspectRatio()`|

## Level 3 Python Test Cases High Level Overview

The class diagram below illustrates the flow of dsDisplay L3 Python test cases:

```mermaid
---
title: dsDisplay - Python Class Flow
---
classDiagram
    testControl <|-- ut_raft
    class ut_raft{
    }
    ut_raft   <|-- dsDisplay
    dsDisplay <|-- L3TestClasses
```

- **testControl**
  - Test Control Module for running rack Testing. This module configures the `DUT` based on the rack configuration file provided to the test.
  - This class is defined in `RAFT` framework. For more details refer [RAFT](https://github.com/rdkcentral/python_raft/blob/1.0.0/README.md)
- **ut_raft**
  - Python based testing framework for writing engineering tests.
  - It provides common functionalities like menu navigation, configuration reader, reading user response etc.
  - For more details [ut-raft](https://github.com/rdkcentral/ut-raft).
- **dsDisplay**
  - This is test helper class which communicates with the `L3` C/C++ test running on the `DUT` through menu
- **L3TestClasses**
  - These are the L3 test case classes
  - Each class covers the each test use-case defined in [L3 Test use-cases](#level-3-test-cases-high-level-overview) table

## YAML File Inputs

```mermaid
---
title: dsDisplay - YAML
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
  - Example configuration file [dsDisplay_Settings](https://github.com/rdkcentral/rdk-halif-test-device_settings/blob/3.0.0/profiles/sink/Sink_4K_Display.yaml)

- **testSetupConfig.yaml**
  - This configuration file contains the list of requirements for tests to execute. Eg: Copying the streams, setting environment variables etc.
  - Example configuration file listed below:

```yaml
dsAudio:
  description: "dsDisplay Device Settings test setup"
  assets:
    device:
      Common: #List of common requirements for all the tests
        artifacts:
          -  "<URL>/hal_test" #URL Path to the bin files to copy
          -  "<URL>/ut_control.so" #URL Path to the .so files if any to copy
          -  "<URL>/run.sh"
        execute:
          - ""  #prerequisites commands if required
        streams:
      test1_VerifyPortSelectionAndStatus: #Requirements for specific test
        artifacts:
        execute:
        streams:
    host:
      menu_config: "../../assets/dsDisplay_L3_menu.yml" #Menu configuration file
```
- **menuConfig**
  - This configuration file contains the list of menu items for C/C++ L3 test running on `DUT`
  - Example configuration file listed below:

```yaml
dsDisplay:
  description: "dsDisplay Device Settings testing profile / menu system for UT"
  test:
  control:
    menu:
      type: UT-C # C (UT-C Cunit) / C++ (UT-G (g++ ut-core gtest backend))
      groups:
          name: "L3 dsDisplay - Sink"
          menu_initialize:
            name: "Initialize dsDisplay"
          menu_enable:
            name: "Select Port"
            input:
                - "Select video Port"
```

## Test Execution

- Folder Structure
  - assets
    - testSetupConfig.yaml
    - menuConfig.yaml
  - host
    - tests
      - helpers
        - dsDisplayTestHelper.py
      - dsDisplay_test1_XYZ.py

- User runs test (eg: test1_XYZ.py)
  - Chooses platform via --config config.yaml and config file
  - --slot 1 is default (optional)
  - Test reads the testSetupConfig.yaml from the assets folder
- Test extracts
  - Specific component configuration
  - validationProfile for the platform
  - Specific test setup requirements
  - Specific test menu configurations