# Device Settings Front Panel Deisplay L3 Low Level Test Specification and Procedure Documentation

## Table of Contents

- [Overview](#overview)
- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [References](#references)
- [Level 3 Test cases High Level Overview](#level-3-test-cases-high-level-overview)

## Overview

This document describes the L3 Low Level Test Specification and Procedure Documentation for the Device Settings Video Port module.

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
- `Interface header` - [dsFPD HAL header](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsFPD.h)

## Level 3 Test Cases High Level Overview

|#|Test-case|Description|HAL APIs|Source|Sink|
|-|---------|-----------|--------|------|----|
|1|Verify LED can be set On and OFF|Verify each LED can be powered on or off |`dsSetFPState()`|`Y`|`Y`|
|2|Check Brightness Control|Verify the LED brightness control by changing the brightness |`dsSetFPBrightness()`|`Y`|`Y`|
|3|Check LED Blink funciton|Verify the LED can be set with specified Blink rate |`dsSetFPState()`|`Y`|`Y`|
|4|Verify LED Color support  | Verify the Front panel LED can be set to supported colors | `dsSetFPColor()` | `Y` | `Y`|
|5|Verify All the Supported State pattern of LED | Verify the Front Panel LED can set all the pattern to be shown during different state of the device | `dsFPSetLEDState()`|`Y`|`Y`|