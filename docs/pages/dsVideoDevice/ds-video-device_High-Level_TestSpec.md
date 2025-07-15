# Device Settings Video Device High Level Test Specification Documentation

## Acronyms, Terms and Abbreviations

- `HAL`  - Hardware Abstraction Layer
- `API`  - Caller Programming Interface
- `DS`   - Device Settings
- `HDR`  - High Dynamic Range
- `FPS`  - Frames Per Second.
- `FRF`  - Frame Rate Frequency
- `HEVC` - High Efficiency Video Coding
- `NA`   - Not Applicable
- `Y`    - Yes

## Introduction

This document provides an overview of the High Level testing requirements for the Device Settings Video Device module. It outlines the scope of testing, objectives, testing levels and approaches, specific test requirements, and expected deliverables.

Interface of the test is available here: [dsVideoDevice HAL header](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsVideoDevice.h)

## Module Description

`DS` Video device `HAL` provides a set of `APIs` to initialize, query and set information about about the zoom mode, `HDR` capabilities, Video encoding formats and frame rate.

Interface specification is available here: [dsVideoPort HAL Spec](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/docs/pages/ds-video-device_halSpec.md)

## Testing Scope

|#|Test Functionality|Description|
|-|------------------|-----------|
|1|[Check the Zoom Control](#check-the-zoom-control)|Verify setting and getting the zoom modes|
|2|[Check the HDR Capability](#check-the-hdr-capability)|Check the `HDR` Capability|
|3|[Check Video codec and Formats](#check-video-codec-and-formats)|Check supported video codec formats|
|4|[Check the Display frame rate Capability](#check-the-display-frame-rate-capability)|Check supported Display frame rates|

### Emulator Requirements

Boot configuration: Check video ports, encoding formats, profiles, frame rates, and device-supported zoom modes, along with the number of ports supported by each device.

Supported Video encoding formats [dsVideoCodingFormat_t link](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsVideoDeviceTypes.h#L165)

Supported Video `HEVC` profiles [dsVideoCodecHevcProfiles_t link](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsVideoDeviceTypes.h#L177)

Supported Frame rates [dsVideoFrameRate_t link](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsAVDTypes.h#L508)

Supported Video formats [dsHDRStandard_t link](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsAVDTypes.h#L625)

Supported zoom modes [dsVideoZoom_t link](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsVideoDeviceTypes.h#L140)

### Check the Zoom Control

|Test Functionality|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|--------|--|--|------|----|--------------------------|
|Check the zoom mode status|Loop through each supported video device and the zoom mode can be set using `Source_VideoDevice.yaml(dsVideoDevice/Device/[Device Number]/SupportedDFCs)` profile file and verify using get function.Note:Supported Number of VideoDevices check this profile file for source `Source_VideoDevice.yaml(dsVideoDevice/NumVideoDevices)` |dsGetVideoDevice(), dsSetDFC(), dsGetDFC()|`Y`|`N`|`Y`|`NA`|`NA`|
||Loop through each supported video device and the zoom mode can be set using `Source_VideoDevice.yaml(dsVideoDevice/Device/[Device Number]/SupportedDFCs)` profile file and verify using get with Video playback & connected device. Note:Supported Number of VideoDevices check this profile file for source `Source_VideoDevice.yaml(dsVideoDevice/NumVideoDevices)` |dsGetVideoDevice(), dsSetDFC(), dsGetDFC()|`NA`|`Y`|`Y`|`NA`|`Y`|

#### Test Startup Requirement-Check the Zoom Control

Playback the pre-define streams

#### Emulator Requirements-Check the Zoom Control

[Emulator Requirements](#emulator-requirements)

#### Control Plane Requirements-Check the Zoom Control

Verify the applied zoom mode during playback with analyzer.

### Check the HDR Capability

|Test Functionality|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|--------|--|--|------|----|--------------------------|
|Check `HDR` Capability|Loop through each supported video device and Get the `HDR` capabilities for each video device and verify with the profile file for source use this `Source_VideoDevice.yaml(dsVideoDevice/Device/[Device Number]/HDRCapabilities)` and for the sink use this `Sink_VideoDevice.yaml(dsVideoDevice/Device/[Device Number]/HDRCapabilities)` Note:Supported Number of VideoDevices check this profile file for source `Source_VideoDevice.yaml(dsVideoDevice/NumVideoDevices)` and for the sink use this `Sink_VideoDevice.yaml(dsVideoDevice/NumVideoDevices)`|dsGetHDRCapabilities() |`Y`|`NA`|`Y`|`Y`|`NA`|

#### Test Startup Requirement-Check the HDR Capability

`NA`

#### Emulator Requirements-Check the HDR Capability

[Emulator Requirements](#emulator-requirements)

#### Control Plane Requirements-Check the HDR Capability

`NA`

### Check Video codec and Formats

|Test Functionality|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|--------|--|--|------|----|--------------------------|
|Check Video coding Formats and information|Loop through each supported video device and the get Video coding format for each video device and verify the with profile file for source use this file `Source_VideoDevice.yaml(dsVideoDevice/Device/[Device Number]/SupportedVideoCodingFormats)` and for the sink use this `Sink_VideoDevice.yaml(dsVideoDevice/Device/[Device Number]/SupportedVideoCodingFormats)` Note:Supported Number of VideoDevices check this profile file for source `Source_VideoDevice.yaml(dsVideoDevice/NumVideoDevices)` and for the sink use this `Sink_VideoDevice.yaml(dsVideoDevice/NumVideoDevices)` |dsGetSupportedVideoCodingFormats() |`Y`|`NA`|`Y`|`Y`|`NA`|
||Loop through each supported video device and get Video codec information for each video device and verify the with `Source_VideoDevice.yaml(dsVideoDevice/Device/[Device Number]/VideoCodecInfo)` profile file.Note:Supported Number of VideoDevices check this profile file for source `Source_VideoDevice.yaml(dsVideoDevice/NumVideoDevices)`.|dsGetVideoCodecInfo() |`Y`|`NA`|`Y`|`NA`|`NA`|

#### Test Startup Requirement-Check Video codec and Formats

`NA`

#### Emulator Requirements-Check Video codec and Formats

[Emulator Requirements](#emulator-requirements)

#### Control Plane Requirements-Check Video codec and Formats

`NA`

### Check the Display frame rate Capability

|Test Functionality|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|--------|--|--|------|----|--------------------------|
|Check the Display frame rate Capability|Loop through each supported video device and Set the supported display frame rate for each video device using profile file `Source_VideoDevice.yaml(dsVideoDevice/Device/[Device Number]/SupportedDisplayFramerate)` and verify using get function. Note:Supported Number of VideoDevices check this profile file for source `Source_VideoDevice.yaml(dsVideoDevice/NumVideoDevices)`.|dsSetDisplayframerate(), dsGetCurrentDisplayframerate()|`Y`|`NA`|`NA`|`Y`|`NA`|
||Loop through each supported video device and Set the supported display frame rate for each video device using profile file `Source_VideoDevice.yaml(dsVideoDevice/Device/[Device Number]/SupportedDisplayFramerate)` and check if callbacks are triggered Note:Supported Number of VideoDevices check this profile file for source `Source_VideoDevice.yaml(dsVideoDevice/NumVideoDevices)` |dsSetDisplayframerate(), dsRegisterFrameratePreChangeCB(), dsRegisterFrameratePostChangeCB()|`NA`|`Y`|`NA`|`Y`|`Y`|

#### Test Startup Requirement-Check the Display frame rate Capability

Playback the pre-define streams

#### Emulator Requirements-Check the Display frame rate Capability

[Emulator Requirements](#emulator-requirements)

#### Control Plane Requirements-Check the Display frame rate Capability

Verify the frame rate with analyzer
