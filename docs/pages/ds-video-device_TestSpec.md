# Device Settings Video Device Test Specification Documentation

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Introduction](#introduction)
- [Module Description](#module-description)
- [Testing Scope](#testing-scope)
  - [Emulator Requirements](#emulator-requirements)
  - [Check the Zoom Control](#check-the-zoom-control)
  - [Check the HDR Capability](#check-the-hdr-capability)
  - [Check Video codec and Formats](#check-video-codec-and-formats)
  - [Check the Display frame rate Capability](#check-the-display-frame-rate-capability)

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

This document provides an overview of the testing requirements for the Device Settings Video Device module. It outlines the scope of testing, objectives, testing levels and approaches, specific test requirements, and expected deliverables.

Interface of the test is available here: [dsVideoDevice HAL header](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsVideoDevice.h)

## Module Description

`DS` Video device `HAL` provides a set of `APIs` to initialize, query and set information about about the zoom mode, `HDR` capabilities, Video encoding formats and frame rate.

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

|Test Functionality|Description|L2|L3|Source|Sink|
|------------------|-----------|--|--|------|----|
|Check the zoom mode status|Ensure that the video device can be retrieved and the zoom mode can be set, retrieved and verify successfully with/without Video playback |`Y`|`Y`|`Y`|`NA`|

#### Test Startup Requirement-Check the Zoom Control

Playback the pre-define streams

#### Emulator Requirements-Check the Zoom Control

[Emulator Requirements](#emulator-requirements)

#### Control Plane Requirements-Check the Zoom Control

Verify the applied zoom mode during playback with analyzer.

### Check the HDR Capability

|Test Functionality|Description|L2|L3|Source|Sink|
|------------------|-----------|--|--|------|----|
|Check `HDR` Capability|Get the `HDR` capabilities and status|`Y`|`NA`|`Y`|`Y`|
||Force `HDR` disable with/without Video playback and verify|`Y`|`Y`|`Y`|`NA`|

#### Test Startup Requirement-Check the HDR Capability

Playback the pre-define streams

#### Emulator Requirements-Check the HDR Capability

[Emulator Requirements](#emulator-requirements)

#### Control Plane Requirements-Check the HDR Capability

Verify the `HDR` status with analyzer.

### Check Video codec and Formats

|Test Functionality|Description|L2|L3|Source|Sink|
|------------------|-----------|--|--|------|----|
|Check Video codec Formats and information|Check the supported Video coding format |`Y`|`NA`|`Y`|`Y`|
||Verify video codec format and information with/without Video playback using analyzer|`NA`|`Y`|`Y`|`NA`|

#### Test Startup Requirement-Check Video codec and Formats

Playback the pre-define streams

#### Emulator Requirements-Check Video codec and Formats

[Emulator Requirements](#emulator-requirements)

#### Control Plane Requirements-Check Video codec and Formats

Verify the codec formats with analyzer.

### Check the Display frame rate Capability

|Test Functionality|Description|L2|L3|Source|Sink|
|------------------|-----------|--|--|------|----|
|Check the Display frame rate Capability|set, retrieved and verify the display framerate successfully|`Y`|`NA`|`NA`|Y|
||Set the frame rate and check if callbacks are triggered|`NA`|`Y`|`NA`|`Y`|

#### Test Startup Requirement-Check the Display frame rate Capability

Playback the pre-define streams

#### Emulator Requirements-Check the Display frame rate Capability

[Emulator Requirements](#emulator-requirements)

#### Control Plane Requirements-Check the Display frame rate Capability

Verify the frame rate with analyzer
