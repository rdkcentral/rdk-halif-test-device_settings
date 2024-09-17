# Device Settings Composite Input L3 Test Specification and Procedure Documentation

## Table of Contents

- [Overview](#overview)
- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [References](#references)
- [Level 3 Test cases High Level Overview](#level-3-test-cases-high-level-overview)

## Overview

This document describes the L3 Test Specification and Procedure Documentation for the Device Settings Composite Input module.

### Acronyms, Terms and Abbreviations

- `HAL` \- Hardware Abstraction Layer, may include some common components
- `API` \- Application Programming Interface
- `UT`  \- Unit Test(s)
- `OEM` \- Original Equipment Manufacture
- `SoC` \- System on a Chip
- `NA`  \- Not Applicable
- `DUT` \- Device Under Test
- `RAFT`\- Rapid Automation Framework for Testing

### References

- `High Level Test Specification` - [ds-compositeIn-High-Level_TestSpec.md](https://github.com/rdkcentral/rdk-halif-test-device_settings/blob/main/docs/pages/ds-compositeIn-High-Level_TestSpec.md)

- `HAL Interface file` - [dsCompositeIn Header](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsCompositeIn.h)

## Level 3 Test Cases High Level Overview

|#|TestName|Description|
|-|--------|-----------|
|1|Verify the CompositeIn port connection with callbacks|Connect/disconnect the CompositeIn source device and check the callbacks is triggered when the connection status changes|
|2|Select the CompositeIn port |Select the composite input port and verify the status|
|3|Verify the CompositeIn active port status with callbacks|Select the CompositeIn port and check the callbacks is triggered when the active status changes|
|4|Scale the video and verify |Play a video in CompositeIn source device and scale the video resolution|
|5|Verify the status information of CompositeIn port |Play a video in CompositeIn source device connected to the active CompositeIn port and verify the status|
