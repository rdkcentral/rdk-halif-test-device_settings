# Device Settings HdmiIn L3 Low Level Test Specification and Procedure Documentation

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

- `High Level Test Specification` - [dsHdmiIn High Level TestSpec](ds-hdmi-in_L3_High-Level_TestSpecification.md)
- `Interface header` - [dsHdmiIn HAL header](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsHdmiIn.h)

## Level 3 Test Cases High Level Overview

|#|Streams Name|Streams description|
|-|------------|-------------------|
|1|vts_HDR10_stream|Format: HDR10,Resolution: 3840 x 2160 (4K UHD),Color Depth: 10-bit,Color Space: Rec. 2020|
|2|vts_SDR_stream|Format: SDR,Resolution: 1920 x 1080|
|3|vts_HLG_stream|Format: HLG,Resolution: 3840 x 2160 or It can also be used with 1080p and 720p resolutions.|
|4|vts_DolbyVision_stream|Format: Dolby Vision,Resolution: 3840 x 2160 (4K UHD),Color Depth: 10/12-bit,Color Space: Rec. 2020format and dynamic metadata.|
|5|vts_HDR10plus_stream|Format: HDR10,Resolution: 3840 x 2160 (4K UHD),Color Depth: 10-bit,Color Space: Rec. 2020 and dynamic metadata capabilities.|

Each test case need to verify with the each HdmiIn port.
Below are top test use-case for the HdmiIn port.

|#|Test-case|Description|HAL APIs|Source|Sink|Streams|
|-|---------|-----------|--------|------|----|-------|
|1|Verify the HdmiIn Connect status with callback|Connect or Disconnect Hdmi input device on any of the hdmi input ports and check the hdmiInConnectCB callback is triggered|dsHdmiInRegisterConnectCB()|`Y`|`Y`|`NA`|
|2|Verify the HdmiIn Signal change with callback|Select the HdmiInput port and check the callback is triggered when the change in signal status occurs|dsHdmiInRegisterSignalChangeCB()|`NA`|`Y`|`NA`|
|3|Verify the HdmiIn Status change with callback|Select the HdmiInput port and check the callback is triggered when the status change occurs(i.e like isPresented, activeport) and  check the callbacks is triggered|dsHdmiInRegisterStatusChangeCB()|`NA`|`Y`|`NA`|
|4|Verify the HdmiIn Video Mode update  with callback|Play the streams from hdminput device video content with any format(like `HDR`,`HLG`,DolbyVision,SDR,...) and check the callbacks is triggered when we change the resolution|dsHdmiInRegisterVideoModeUpdateCB()|`NA`|`Y`|1,2,3,4,5|
|5|Verify the HdmiIn Allm change  with callback|Change the allm option to TRUE/FALSE after connecting game controller on 4k supported panel and check the callbacks is triggered when the allm status change occurs|dsHdmiInRegisterAllmChangeCB()|`NA`|`Y`|`NA`|
|6|Verify the  HdmiIn Audio Video lateny with callback|Play the streams from hdminput device video content with any format(like `HDR`,`HLG`,DolbyVision,SDR,...) and check the callbacks is triggered when there is latency change|dsHdmiInRegisterAVLatencyChangeCB()|`NA`|`Y`|1,2,3,4,5|
|7|Verify the HdmiIn AVI content change with callbacks|Play the streams from hdminput device video content with any format(like `HDR`,`HLG`,DolbyVision,SDR,...) and check the callbacks is triggered there is AVI content change|dsHdmiInRegisterAviContentTypeChangeCB()|`NA`|`Y`|1,2,3,4,5|
|8|Get HdmiIn status of the selected port|Select the Hdmi Input and verify the status whether selected port active or not|dsHdmiInSelectPort(),dsHdmiInGetStatus()|`Y`|`Y`|`NA`|
|9|Scale HdmiIn video of the selected port|Select the Hdmi Input and scale the video on the selcted port verify video scaled or not|dsHdmiInScaleVideo()|`Y`|`Y`|`NA`|
|10|Check and verify Zoom mode selected|Select the Zoom mode from the available inputs and verify its set or not|dsHdmiInSelectZoomMode()|`Y`|`NA`|1,2,3,4,5|
|11|Get Current video mode of slected input port|Play the video from the selected Hdmi Input port and get the current video mode|dsHdmiInGetCurrentVideoMode()|`Y`|`Y`|1,2,3,4,5|
|12|Check and verify the slected port is ARC|Select the HdmiInput port and check whether the selected port ARC or not|dsIsHdmiARCPort()|`NA`|`Y`|`NA`|
|13|Get and verify the edid of selected port|Select the HdmiInput and get the edid for that particular Input port|dsGetEDIDBytesInfo()|`NA`|`Y`|`NA`|
|14|Get and verify the spdinfo of selected port|Select the HdmiInput and get the spdinfo for that particular Input port|dsGetHDMISPDInfo()|`NA`|`Y`|`NA`|
|15|Set and verify the edid version on selected port|Set the edid version and verify by retrieving the edid version|dsSetEdidVersion(),dsGetEdidVersion()|`NA`|`Y`|`NA`|
|16|Get the allm status of selected port|Select the HdmiInput and get the allm status for that particular Input port|dsGetAllmStatus()|`NA`|`Y`|`NA`|
|17|Get the SupportedGame features list |Lists all the supported game features list on sink device|dsGetSupportedGameFeaturesList()|`NA`|`Y`|`NA`|
|18|Get audio video latency of current video|Play the video on selected Hdmi Input port and get the audio video latency of current content|dsGetAVLatency()|`NA`|`Y`|1,2,3,4,5|
|19|Set and verify edid allm support on selected port|Set and retrieve allm on selected port|dsSetEdid2AllmSupport(),dsGetEdid2AllmSupport()|`NA`|`Y`|`NA`|
