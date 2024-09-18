# Device Settings HdmiIn L3 High Level Test Specification and Procedure Documentation

## Table of Contents

- [Overview](#overview)
- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [References](#references)
- [Level 3 Test cases High Level Overview](#level-3-test-cases-high-level-overview)

## Overview

This document describes the L3 Low Level Test Specification and Procedure Documentation for the Device Settings HdmiIn module.

### Acronyms, Terms and Abbreviations

- `HAL` \- Hardware Abstraction Layer, may include some common components
- `UT`  \- Unit Test(s)
- `OEM` \- Original Equipment Manufacture
- `SoC` \- System on a Chip
- `HDMI`\- High-Definition Multimedia Interface
- `HDR` \- High Dynamic Range
- `HLG` \- Hybrid Log-Gamma
- `SDR` \- Standard Dynamic Range

### References

- `Low Level Test Specification` - [dsHdmiIn Low Level TestSpec](ds-hdmi-in_L3_Low-Level_TestSpecification.md)
- `Interface header` - [dsHdmiIn HAL header](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsHdmiIn.h)

## Level 3 Test Cases High Level Overview

|#|TestName|Description|HAL API|Source|Sink|Streams|
|-|--------|-----------|-------|------|----|-------|
|1|Verify the HdmiIn Connect status with callback|Connect or Disconnect Hdmi input device on any of the hdmi input ports and check the hdmiInConnectCB callback is triggered|`NA`|`Y`|
|2|Verify the HdmiIn Signal change with callback|Select the HdmiInput port and check the callback is triggered when the change in signal status occurs|`NA`|`Y`|
|3|Verify the HdmiIn Status change with callback|Select the HdmiInput port and check the callback is triggered when the status change occurs(i.e like isPresented, activeport) and  check the callbacks is triggered|`NA`|`Y`|
|4|Verify the HdmiIn Video Mode update  with callback|Play the streams from hdminput device video content with any format(like `HDR`,`HLG`,DolbyVision,SDR,...) and check the callbacks is triggered when we change the resolution|`NA`|`Y`|
|5|Verify the HdmiIn Allm change  with callback|Change the allm option to TRUE/FALSE after connecting game controller on 4k supported panel and check the callbacks is triggered when the allm status change occurs|`NA`|`Y`|
|6|Verify the  HdmiIn Audio Video lateny with callback|Play the streams from hdminput device video content with any format(like `HDR`,`HLG`,DolbyVision,SDR,...) and check the callbacks is triggered when there is latency change|`NA`|`Y`|
|7|Verify the HdmiIn AVI content change with callbacks|Play the streams from hdminput device video content with any format(like `HDR`,`HLG`,DolbyVision,SDR,...) and check the callbacks is triggered there is AVI content change|`NA`|`Y`|
|8|Get HdmiIn status of the selected port|Select the Hdmi Input and verify the status whether selected port active or not|dsHdmiInSelectPort(),dsHdmiInGetStatus()|`Y`|`Y`|
|9|Scale HdmiIn video of the selected port|Select the Hdmi Input and scale the video on the selcted port verify video scaled or not|dsHdmiInSelectPort(),dsHdmiInScaleVideo()|`Y`|`Y`|
|10|Check and verify Zoom mode selected|Select the Zoom mode from the available inputs and verify its set or not|dsHdmiInSelectZoomMode()|`Y`|`NA`|
|11|Get Current video mode of slected input port|Play the video from the selected Hdmi Input port and get the current video mode|dsHdmiInSelectPort(),dsHdmiInGetCurrentVideoMode()|`Y`|`Y`|
|12|Check and verify the slected port is ARC|Select the HdmiInput port and check whether the selected port ARC or not|dsIsHdmiARCPort()|`NA`|`Y`|
|13|Get and verify the edid of selected port|Select the HdmiInput and get the edid for that particular Input port|dsGetEDIDBytesInfo()|`NA`|`Y`|
|14|Get and verify the spdinfo of selected port|Select the HdmiInput and get the spdinfo for that particular Input port|dsGetHDMISPDInfo()|`NA`|`Y`|
|15|Set and verify the edid version on selected port|Set the edid version and verify by retrieving the edid version|dsSetEdidVersion(),dsGetEdidVersion()|`NA`|`Y`|
|16|Get the allm status of selected port|Select the HdmiInput and get the allm status for that particular Input port|dsGetAllmStatus()|`NA`|`Y`|
|17|Get the SupportedGame features list |Lists all the supported game features list on sink device|dsGetSupportedGameFeaturesList()|`NA`|`Y`|
|18|Get audio video latency of current video|Play the video on selected Hdmi Input port and get the audio video latency of current content|dsHdmiInSelectPort(),dsGetAVLatency()|`NA`|`Y`|
|19|Set and verify edid allm support on selected port|Set and retrieve allm on selected port|dsSetEdid2AllmSupport(),dsGetEdid2AllmSupport()|`NA`|`Y`|
