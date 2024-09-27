# Device Settings Video Port L3 Low Level Test Specification and Procedure Documentation

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
- `HDMI`\- High-Definition Multimedia Interface
- `HDCP`\- High-bandwidth Digital Content Protection
- `HDR` \- High Dynamic Range
- `HLG` \- Hybrid Log-Gamma
- `SDR` \- Standard Dynamic Range

### References

- `High Level Test Specification` - [dsVideoPort High Level TestSpec](ds-video-port_High-Level_TestSpec.md)
- `Interface header` - [dsVideoPort HAL header](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsVideoPort.h)

## Level 3 Test Cases High Level Overview

|#|TestName|Description|
|-|--------|-----------|
|1|Verify the Video content Formats with callbacks|Play the pre-defined streams different video content format(`HDR`,`HLG`,DolbyVision,..) and check the callbacks is triggered when the video content format changes|
|2|Check DisplayConnected|Verify the Display by enabling and disable port|
|3|Select the `HDCP` Version |Select the Supported `HDCP` version and verify|
|4|Verify the Resolution for source|Play the pre-defined streams and set supported resolution and verify the resolution|
|5|Verify the `HDCP` status using callbacks for Source|Power off and power on TV or pug/unplug `HDMI` and Check the `HDCP` status using callbacks(i.e.UNPOWERED,AUTHENTICATED,.. )|
|6|Select video content formats for Source |Select the Supported `HDR` modes & Verify the video content formats|
|7|Resets the video output to `SDR` for Source |Play the `HDR` stream and verify the video content formats|
|8|Select preferred color depth for Source|Select the Color depth from Supported list & verify|
|9|sets the background color for Source |Select the background color form supported list & verify|
