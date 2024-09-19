# Device Settings Host L3 Low Level Test Specification and Procedure Documentation

## Table of Contents

- [Overview](#overview)
- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [References](#references)
- [Level 3 Test cases High Level Overview](#level-3-test-cases-high-level-overview)

## Overview

This document describes the L3 Low Level Test Specification and Procedure Documentation for the Device Settings Host module.

### Acronyms, Terms and Abbreviations

- `HAL` \- Hardware Abstraction Layer, may include some common components
- `UT`  \- Unit Test(s)
- `OEM` \- Original Equipment Manufacture
- `SoC` \- System on a Chip
- `Y`   \- yes supported
- `NA`  \- Not Supported

### References

- `High Level Test Specification` - [dsHost_TestSpecification.md](https://github.com/rdkcentral/rdk-halif-test-device_settings/blob/main/docs/pages/dsHost_TestSpecification.md)
- `HAL Interface Header File` - [dsHost.h](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsHost.h)

## Level 3 Test Cases High Level Overview

Each test case need to verify with the each supported video port.
Below are top test use-case for the video port.

|#|Test-case|Description|HAL APIs|Source|Sink|
|-|---------|-----------|--------|------|----|
|1|Verify that the get temperature function |After the device is running for sometime, call getTemperature, and call it after a five minute wait. The two temperatures should not see any noticable changes in temperature |`dsGetCPUTemperature()`|`Y`|`Y`|