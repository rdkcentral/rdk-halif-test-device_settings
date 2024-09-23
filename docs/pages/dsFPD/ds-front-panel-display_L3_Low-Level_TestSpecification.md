# Device Settings Front Panel Display L3 Low Level Test Specification and Procedure Documentation

## Table of Contents

- [Overview](#overview)
- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [References](#references)
- [Level 3 Test cases High Level Overview](#level-3-test-cases-high-level-overview)

## Overview

This document describes the L3 Low Level Test Specification and Procedure Documentation for the Device Settings Front Panel Display module.

### Acronyms, Terms and Abbreviations

- `HAL` \- Hardware Abstraction Layer, may include some common components
- `UT`  \- Unit Test(s)
- `OEM` \- Original Equipment Manufacture
- `SoC` \- System on a Chip
- `LED` \- Light Emitting Diode
- `FPD` \- Front Panel Display
- `Y`   \- yes supported
- `NA`  \- Not Supported

### References

- `High Level Test Specification` - [dsFrontPanelDevice High Level TestSpec](ds-front-panel-display_High-Level_TestSpec.md)
- `Interface header [4.0.0]` - [dsFPD HAL header](https://github.com/rdkcentral/rdk-halif-device_settings/blob/4.0.0/include/dsFPD.h)

## Level 3 Test Cases High Level Overview

|#|Test-case|Description|HAL APIs|Source|Sink|
|-|---------|-----------|--------|------|----|
|1|Verify LED can be set On and OFF|Verify each LED can be powered on or off |`dsSetFPState()`|`Y`|`Y`|
|2|Check Brightness Control|Verify the LED brightness control by changing the brightness |`dsSetFPBrightness()`|`Y`|`Y`|
|3|Check LED Blink funciton|Verify the LED can be set with specified Blink rate |`dsSetFPState()`|`Y`|`Y`|
|4|Verify LED Color support  | Verify the Front panel LED can be set to supported colors | `dsSetFPColor()` | `Y` | `Y`|
|5|Verify All the Supported State pattern of LED | Verify the Front Panel LED can set all the pattern to be shown during different state of the device | `dsFPSetLEDState()`|`Y`|`Y`|

## Level 3 Python Test Cases High Level Overview

The class diagram below illustrates the flow of dsFPD L3 Python test cases:

```mermaid
---
title: dsFPD - Python Class Flow
---
classDiagram
    testControl <|-- ut_raft
    class ut_raft{
    }
    ut_raft <|-- dsFPD
    dsFPD <|-- L3TestClasses
```

- **testControl**
  - Test Control Module for running rack Testing. This module configures the `DUT` based on the rack configuration file provided to the test.
  - This class is defined in `RAFT` framework. For more details refer [RAFT](https://github.com/rdkcentral/python_raft/blob/1.0.0/README.md)
- **ut_raft**
  - Python based testing framework for writing engineering tests.
  - It provides common functionalities like menu navigation, configuration reader, reading user response etc.
  - For more details [ut-raft](https://github.com/rdkcentral/ut-raft).
- **dsFPD**
  - This is test helper class which communicates with the `L3` C/C++ test running on the `DUT` through menu
- **L3TestClasses**
  - These are the L3 test case classes
  - Each class covers the each test use-case defined in [L3 Test use-cases](#level-3-test-cases-high-level-overview) table

## YAML File Inputs

```mermaid
---
title: dsFPD - YAML
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
  - Example configuration file [dsVideoPort_Settings](https://github.com/rdkcentral/rdk-halif-test-device_settings/blob/main/profiles/sink/Sink_4K_VideoPort.yaml)

- **testSetupConfig.yaml**
  - This configuration file contains the list of requirements for tests to execute. Eg: Setting up the extenal devices, setting environment variables etc.
  - Example configuration file listed below:

```yaml
dsFPD:
  description: "dsFPD Device Settings test setup"
  assets:
    device:
      Common: #List of common requirements for all the tests
        artifacts:
          -  "<URL>/hal_test" #URL Path to the bin files to copy
          -  "<URL>/libut_control.so" #URL Path to the .so files if any to copy
          -  "<URL>/run.sh"
        execute:
          - ""  #prerequisites commands if required
      test1_enable_front_panel_led: #Requirements for specific test
        artifacts:
        execute:
      test2_led_brightness:
        artifacts:
        execute:
    host:
      menu_config: "../../assets/dsFPD_L3_menu.yml" #Menu configuration file
```
- **menuConfig**
  - This configuration file contains the list of menu items for C/C++ L3 test running on `DUT`
  - Example configuration file listed below:

```yaml
dsFPD:
  description: "dsFPD Device Settings testing profile / menu system for UT"
  test:
  control:
    menu:
      type: UT-C # C (UT-C Cunit) / C++ (UT-G (g++ ut-core gtest backend))
      groups:
          name: "L3 dsFPD "
          menu_initialize:
            name: "Initialize dsFPD"
          menu_enable:
            name: "Enable Front Panel LED"
            input:
                - "Select LED Indicator"
          menu_disable:
            name: "Disable Front Panle LED"
            input:
                - "Select LED Indicator"
```

## Test Execution

- Folder Structure
  - assets
    - testSetupConfig.yaml
    - menuConfig.yaml
  - host
    - tests
      - helpers
        - dsFPDTestHelper.py
      - dsFPD_test1_XYZ.py
      - dsFPD_test2_XYZ.py

- User runs test (eg: test1_XYZ.py)
  - Chooses platform via --config config.yaml and config file
  - --slot 1 is default (optional)
  - Test reads the testSetupConfig.yaml from the assets folder
- Test extracts
  - Specific component configuration
  - validationProfile for the platform
  - Specific test setup requirements
  - Specific test menu configurations