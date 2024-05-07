# Device Settings Video Port High Level Test Specification Documentation

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Introduction](#introduction)
- [Module Description](#module-description)
- [Testing Scope](#testing-scope)
  - [Emulator Requirements](#emulator-requirements)
  - [Check the Video port status](#check-the-video-port-status)
  - [Check Video Content Format and Resolution](#check-video-content-format-and-resolution)
  - [Check HDR Capability](#check-hdr-capability)
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
|2|[Check Video Content Format and Resolution](#check-video-content-format-and-resolution)|Check Video content Format and Resolution|
|3|[Check HDR Capability](#check-hdr-capability)|Check `HDR` Capability|
|4|[HDCP Management](#hdcp-management)|Check `HDCP` Status|
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

|Test Functionality|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|--------|--|--|------|----|--------------------------|
|Check the each video port status |Get the video port handle,check Video Port enable/disable if port disabled, enable port and check the each port status. |dsGetVideoPort(), dsIsVideoPortEnabled(), dsEnableVideoPort() |`Y`|`NA`|`Y`|`Y`|`NA`|
||Verify display connected/disconnected status without video port connected|dsIsDisplayConnected(), dsIsVideoPortActive()|`Y`|`NA`|`Y`|`Y`|`NA`|
||Verify display connected/disconnected status by connecting/disconnecting video port|dsIsDisplayConnected(), dsIsVideoPortActive()|`NA`|`Y`|`Y`|`NA`|`Y`|
||Get the surround mode capabilities and verify with configuration file|dsIsDisplaySurround()|`Y`|`NA`|`NA`|`Y`|`NA`|
||Verify the surround mode capabilities of connected display and verify with configuration file|dsIsDisplaySurround(), dsGetSurroundMode()|`Y`|`NA`|`Y`|`NA`|`NA`|

#### Test Startup Requirement-Check the video port status

`NA`

#### Emulator Requirements-Check the video port status

[Emulator Requirements](#emulator-requirements)

#### Control Plane Requirements-Check the video port status

plug/Unplug the Video port,Verify with edid info, is surround mode supported

### Check Video Content Format and Resolution

|Test Functionality|Description|HAL API's|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|---------|--|--|------|----|--------------------------|
|Check Video Format Content and Resolution|Register callback for the Video Format update event,change the video formate and check whether callback is Triggered or not|dsVideoFormatUpdateRegisterCB()|`NA`|`Y`|`Y`|`Y`|`Y`|
||Set Video port properties like pixel resolution, Aspect ratio, Stereo Scopic modes, frame rates & scan modes and looping through with supported values of each video port, Verify using get function |dsSetResolution(), dsGetResolution()|`Y`|`NA`|`Y`|`NA`|`NA`|
||Set Video port properties like pixel resolution, Aspect ratio, Stereo Scopic modes, frame rates & scan modes and looping through with supported values  of each video port and verify external Analyzer with video playback |dsSetResolution(), dsGetResolution()|`NA`|`Y`|`Y`|`NA`|`Y`|
||Gets the supported resolutions of TV and verify with the configuration file |dsSupportedTvResolutions()|`Y`|`NA`|`Y`|`Y`|`Y`|
||Get Video port properties like pixel resolution, Aspect ratio, Stereo Scopic modes, frame rates and scan modes and verify with the configuration file|dsGetResolution()|`Y`|`NA`|`NA`|`Y`|`NA`|

#### Test Startup Requirement-Check Video Content Format and Resolution

Playback the pre-define streams

#### Emulator Requirements-Check Video Content Format and Resolution

[Emulator Requirements](#emulator-requirements)

#### Control Plane Requirements-Check Video Content Format and Resolution

Check the port output resolutions and Verify the AspectRatio,video Stereo Scopic modes,video Frame rates,interlaced/progressive.

### Check HDR Capability

|Test Functionality|Description|HAL API's|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|---------|--|--|------|----|--------------------------|
|Check HDR Capability|Get the HDR capabilities & verify with the configuration file and check the status|dsGetTVHDRCapabilities(), dsGetVideoEOTF()|`Y`|`NA`|`Y`|`Y`|`NA`|
||Checks video output is HDR with different HDR/SDR streams and verify with external analyzer|dsIsOutputHDR()|`NA`|`Y`|`Y`|`Y`|`Y`|
||Set and get Force Disable 4KSupport without playback|dsSetForceDisable4KSupport(), dsGetForceDisable4KSupport()|`Y`|`NA`|`Y`|`Y`|`NA`|
||Set and get Force Disable 4KSupport with playback|dsSetForceDisable4KSupport(), dsGetForceDisable4KSupport()|`NA`|`Y`|`Y`|`Y`|`NA`|
||Disable 4K Support with external analyzer|dsSetForceHDRMode()|`NA`|`Y`|`Y`|`NA`|`Y`|
||Reset the video output to SDR with playback|dsResetOutputToSDR()|`NA`|`Y`|`Y`|`Y`|`NA`|
||Reset the video output to SDR with external analyzer|dsResetOutputToSDR()|`NA`|`Y`|`Y`|`NA`|`Y`|

#### Test Startup Requirement-Check HDR Capability

Playback the pre-define streams

#### Emulator Requirements-Check HDR Capability

[Emulator Requirements](#emulator-requirements)

#### Control Plane Requirements-Check HDR Capability

Check HDR enable/disabled and is video reset to SDR with analyzer

### HDCP Management

|Test Functionality|Description|HAL API's|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|---------|--|--|------|----|--------------------------|
|Check HDCP status|Check enable/disable the HDCP(1.x & 2.x) for the specified video port with playback |dsEnableHDCP(), dsIsHDCPEnabled()|`NA`|`Y`|`Y`|`NA`|`NA`|
||Check HDCP status for valid port and verify with the configuration file|dsGetHDCPStatus()|`Y`|`NA`|`Y`|`Y`|`NA`|
||Check HDCP status for valid port and verify with the configuration file and check with connected device|dsGetHDCPStatus() |`NA`|`Y`|`Y`|`NA`|`NA`|
||Check HDCP protocol Status and verify with the configuration file|dsGetHDCPProtocol(), dsGetHDCPCurrentProtocol()|`Y`|`NA`|`NA`|`Y`|`NA`|
||Check HDCP protocol Status with connected device |dsGetHDCPProtocol(), dsGetHDCPCurrentProtocol()|`NA`|`Y`|`Y`|`NA`|`Y`|
||Check HDCP Receiver protocol |dsGetHDCPReceiverProtocol(),|`NA`|`Y`|`Y`|`NA`|`Y`|
||Ignore EDID status|dsGetIgnoreEDIDStatus()|`N`|`Y`|`Y`|`NA`|`Y`|
||set/get preferred HDCP Protocol|dsSetHdmiPreference(), dsGetHdmiPreference()|`Y`|`NA`|`Y`|`Y`|`NA`|
||set/get preferred HDCP Protocol with connected device |dsSetHdmiPreference(), dsGetHdmiPreference()|`NA`|`Y`|`Y`|`NA`|`NA`|
||Notify event if the HDCP status change and check the timing info for hdcp authentication |dsRegisterHdcpStatusCallback()|`NA`|`Y`|`Y`|`NA`|`Y`|
||Check HDCP status with external analyzer|dsRegisterHdcpStatusCallback()|`NA`|`Y`|`Y`|`NA`|`Y`|

#### Test Startup Requirement-HDCP Management

Playback the pre-define streams

#### Emulator Requirements-HDCP Management

[Emulator Requirements](#emulator-requirements)

#### Control Plane Requirements-HDCP Management

Check the HDCP status with external analyzer

### Color Capabilities

|Test Functionality|Description|HAL API's|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|---------|--|--|------|----|--------------------------|
|Check Color |Get Color Space, compare with the configuration file and without video|dsGetColorSpace()|`Y`|`NA`|`Y`|`Y`|`NA`|
||Get Color Space with video playback|dsGetColorSpace()|`NA`|`Y`|`Y`|`Y`|`NA`|
||Set/Get Color Depth Capabilities, compare with the configuration file and without video|dsGetColorDepth(), dsColorDepthCapabilities(), dsGetPreferredColorDepth(), dsSetPreferredColorDepth()|`Y`|`Y`|`Y`|`Y`||
||Set/Get Color Depth Capabilities, compare with the configuration file and with video|dsGetColorDepth(), dsColorDepthCapabilities(), dsGetPreferredColorDepth(), dsSetPreferredColorDepth()|`NA`|`Y`|`Y`|`Y`||
||Check QuantizationRange status|dsGetQuantizationRange()|`Y`|`NA`|`Y`|`Y`||
||Check MatrixCoefficients status |dsGetMatrixCoefficients()|`Y`|`NA`|`Y`|`Y`||
||Check MatrixCoefficients status with video |dsGetMatrixCoefficients()|`NA`|`Y`|`Y`|`Y`||
||Set Background Color|dsSetBackgroundColor()|`N`|`Y`|`Y`|`NA`||
||Check the color space capabilities with analyzer|dsGetColorSpace()|`NA`|`Y`|`Y`|`NA`||

#### Test Startup Requirement-Color Capabilities

Playback the pre-define streams

#### Emulator Requirements-Color Capabilities

[Emulator Requirements](#emulator-requirements)

#### Control Plane Requirements-Color Capabilities

Verify the Color Space,Color Depth,QuantizationRange,MatrixCoefficients,Background Color
