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
- `Interface header` - [dsDisplay HAL header](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsDisplay.h)

## Level 3 Test Cases High Level Overview

|#|Test-case|Description|HAL APIs|Source|Sink|
|-|---------|-----------|--------|------|----|
|1|Verify Display Events with callbacks|Monitor and verify that the callbacks are triggered correctly for each display event |`dsRegisterDisplayEventCallback()`|`Y`|`Y`|
|2|Gets the EDID information|Verify the functionality of retrieving the EDID information of a display |`dsGetEDID()`|`Y`|`Y`|
|3|Gets the EDID buffer and EDID length|Verify the functionality of retrieving the EDID bytes of a display |`dsGetEDIDBytes()`|`Y`|`Y`|
|4|Gets Aspect Ratio | Verify the functionality of retrieving the aspect ratio of a display | `dsGetDisplayAspectRatio()` |`Y`|`NA`|

