# Device Settings Video Port High Level Test Specification Documentation

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Introduction](#introduction)
- [Module Description](#module-description)
- [Testing Scope](#testing-scope)
  - [Emulator Requirements](#emulator-requirements)
  - [Check the Video port status](#check-the-video-port-status)
  - [Check Video Content Format and HDR Capability](#check-video-content-format-and-hdr-capability)
  - [Check Video Resolution](#check-video-resolution)
  - [HDCP Management](#hdcp-management)
  - [Color Capabilities](#color-capabilities)

## Acronyms, Terms and Abbreviations

- `HAL`    - Hardware Abstraction Layer
- `API`    - Caller Programming Interface
- `DS`     - Device Settings
- `HDMI`   - High-Definition Multimedia Interface
- `HDCP`   - High-bandwidth Digital Content Protection
- `HDR`    - High Dynamic Range
- `SDR`    - Standard Dynamic Range
- `EDID`   - Extended Display Identification Data
- `EOTF`   - Electro-Optical Transfer Function
- `NA`     - Not Applicable
- `Y`      - Yes

## Introduction

This document provides an overview of the High Level testing requirements for the Device Settings Video Port module. It outlines the scope of testing, objectives, testing levels and approaches, specific test requirements, and expected deliverables.

Interface header is available here: [dsVideoPort HAL header](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsVideoPort.h)

## Module Description

`DS` Video Port `HAL` provides a set of `APIs` to initialize, query and set information about the Video ports like getting  video port handle, fetching connected display information such as color depth, color space, matrix coefficients, quantization range, supported video resolutions using the video port handle. It also provides `APIs` to enable or disable content protection like `HDCP`, to set the background color and preferred color depth of the video port.

Interface specification is available here: [dsVideoPort HAL Spec](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/docs/pages/ds-video-port_halSpec.md)

## Testing Scope

|#|Test Functionality|Description|
|-|------------------|-----------|
|1|[Check the Video port status](#check-the-video-port-status)|Check the Video Port Access and Status |
|2|[Check Video Content Format and HDR Capability](#check-video-content-format-and-hdr-capability)|Check Video content Format and `HDR` Capability|
|3|[Check Video Resolution](#check-video-resolution)|Check Video resolution|
|4|[HDCP and HDMI Management](#hdcp-and-hdmi-management)|Check `HDCP` and `HDMI` Status|
|5|[Color Capabilities](#color-capabilities)|Check the color capabilities|

### Emulator Requirements

Boot configuration: Check video ports, formats, frame rates, and device-supported resolutions, along with the number of ports supported by each device.

Supported Video Port [dsVideoPortType_t link](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsAVDTypes.h#L132)

Supported Video resolutions [dsTVResolution_t link](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsAVDTypes.h#L489)

Supported Frame rates [dsVideoFrameRate_t link](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsAVDTypes.h#L508)

Supported Video formats [dsHDRStandard_t link](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsAVDTypes.h#L625)

Supported Video background Color [dsVideoBackgroundColor_t link](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsAVDTypes.h#L540)

Supported Display Color Depth [dsDisplayColorDepth_t link](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsAVDTypes.h#L758)

Supported Display Color Space [dsDisplayColorSpace_t link](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsAVDTypes.h#L733)

Supported Display MatrixCoefficient [dsDisplayMatrixCoefficients_t link](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsAVDTypes.h#L780)

Supported Display QuantizationRange [dsDisplayQuantizationRange_t link](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsAVDTypes.h#L745)

### Check the video port status

|Test Functionality|Description|HAL APIs|L2|L3|Source|Sink|
|------------------|-----------|--------|--|--|------|----|
|Check the video port status|Get the video port handle,check the Video Port enable/disable|dsGetVideoPort(), dsIsVideoPortEnabled(), dsIsVideoPortActive(), dsEnableVideoPort()|`Y`|`Y`|`Y`|`Y`|
||Verify display connected/disconnected status without video port connected|dsIsDisplayConnected()|`Y`|`NA`|`Y`|`Y`|
||Verify display connected/disconnected status by connecting/disconnecting video port|dsIsDisplayConnected()|`NA`|`Y`|`Y`|`NA`|
||Verify the surround mode capabilities with/without playback|dsIsDisplaySurround(), dsGetSurroundMode()|`Y`|`Y`|`Y`|`Y`|
||Verify the surround mode capabilities of connected display with/without playback|dsIsDisplaySurround(), dsGetSurroundMode()|`Y`|`Y`|`Y`|`NA`|

#### Test Startup Requirement-Check the video port status

Playback the pre-define streams

#### Emulator Requirements-Check the video port status

[Emulator Requirements](#emulator-requirements)

#### Control Plane Requirements-Check the video port status

Unplug the Video port,Verify the surround mode

### Check Video Content Format and HDR Capability

|Test Functionality|Description|HAL API's|L2|L3|Source|Sink|
|------------------|-----------|---------|--|--|------|----|
|Check Video Format Content and HDR Capability|Notify an event when the list of video Format changes|dsVideoFormatUpdateRegisterCB()|`NA`|`Y`|`Y`|`Y`|
||Get the HDR capabilities and status|dsIsOutputHDR(), dsGetTVHDRCapabilities()|`Y`|`NA`|`Y`|`Y`|
||Set Force Disable 4KSupport with/without playback|dsSetForceHDRMode()|`Y`|`Y`|`Y`|`Y`|
||Disable 4KSupport with external analyzer|dsSetForceHDRMode()|`NA`|`Y`|`Y`|`NA`|
||Reset the video output to SDR with/without playback|dsResetOutputToSDR()|`NA`|`Y`|`Y`|`Y`|
||Reset the video output to SDR with external analyzer|dsResetOutputToSDR()|`NA`|`Y`|`Y`|`NA`|

#### Test Startup Requirement-Check Video Content Format and HDR Capability

Playback the pre-define streams

#### Emulator Requirements-Check Video Content Format and HDR Capability

[Emulator Requirements](#emulator-requirements)

#### Control Plane Requirements-Check Video Content Format and HDR Capability

Check the port output resolutions and HDR with analyzer

### Check Video Resolution

|Test Functionality|Description|HAL API's|L2|L3|Source|Sink|
|------------------|-----------|---------|--|--|------|----|
|Check Resolution with/without playback|Set/Get Video port properties like pixel resolution, Aspect ratio, Stereo Scopic modes, frame rates and scan modes|dsSetResolution(), dsGetResolution()|`Y`|`Y`|`Y`|`NA`|
||Get Video port properties like pixel resolution, Aspect ratio, Stereo Scopic modes, frame rates and scan modes and verify|dsGetResolution()|`Y`|`NA`|`NA`|`Y`|
||Check Video port properties with external Analyzer|dsSetResolution(), dsGetResolution()|`NA`|`Y`|`Y`|`NA`|

#### Test Startup Requirement-Check Video Resolution

Playback the pre-define streams

#### Emulator Requirements-Check Video Resolution

[Emulator Requirements](#emulator-requirements)

#### Control Plane Requirements-Check Video Resolution

Verify the AspectRatio,video Stereo Scopic modes,video Frame rates,interlaced/progressive.

### HDCP and HDMI Management

|Test Functionality|Description|HAL API's|L2|L3|Source|Sink|
|------------------|-----------|---------|--|--|------|----|
|Check HDCP and HDMI status|Check enable/disable the HDCP for the specified video port|dsEnableHDCP(),dsIsHDCPEnabled()|`Y`|`Y`|`Y`|`NA`|
||Check HDCP status for valid port|dsGetHDCPStatus()|`Y`|`Y`|`Y`|`Y`|
||Check HDCP protocol Status|dsGetHDCPProtocol(), dsGetHDCPCurrentProtocol()|`Y`|`Y`|`Y`|`Y`|
||Check HDCP Receiver protocol|dsGetHDCPReceiverProtocol(),|`NA`|`Y`|`Y`|`NA`|
||Ignore EDID status|dsGetIgnoreEDIDStatus()|`N`|`Y`|`Y`|`NA`|
||set/get preferred HDMI Protocol|dsSetHdmiPreference(), dsGetHdmiPreference()|`Y`|`Y`|`Y`|`Y`|
||Notify event if the HDCP status change|dsRegisterHdcpStatusCallback()|`NA`|`Y`|`Y`|`NA`|
||Check HDCP status with external analyzer|dsRegisterHdcpStatusCallback()|`NA`|`Y`|`Y`|`NA`|

#### Test Startup Requirement-HDCP Management

Playback the pre-define streams

#### Emulator Requirements-HDCP Management

[Emulator Requirements](#emulator-requirements)

#### Control Plane Requirements-HDCP Management

Check the HDCP status with external analyzer

### Color Capabilities

|Test Functionality|Description|HAL API's|L2|L3|Source|Sink|
|------------------|-----------|---------|--|--|------|----|
|Check Color Capabilities|Get Color Space, compare with the configuration file and with/without video|dsGetColorSpace()|`Y`|`Y`|`Y`|`Y`|
||Set/Get Color Depth Capabilities, compare with the configuration file and with/without video|dsGetColorDepth(), dsColorDepthCapabilities(), dsGetPreferredColorDepth(),dsSetPreferredColorDepth()|`Y`|`Y`|`Y`|`Y`|
||Check QuantizationRange status|dsGetQuantizationRange()|`Y`|`Y`|`Y`|`Y`|
||Check MatrixCoefficients status with/without video |dsGetMatrixCoefficients()|`Y`|`Y`|`Y`|`Y`|
||Set Background Color|dsSetBackgroundColor()|`N`|`Y`|`Y`|`NA`|
||Check the color space capabilities with analyzer|dsGetColorSpace()|`NA`|Y|Y|`NA`|

#### Test Startup Requirement-Color Capabilities

Playback the pre-define streams

#### Emulator Requirements-Color Capabilities

[Emulator Requirements](#emulator-requirements)

#### Control Plane Requirements-Color Capabilities

Verify the Color Space,Color Depth,QuantizationRange,MatrixCoefficients,Background Color
