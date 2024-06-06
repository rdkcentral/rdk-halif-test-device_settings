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
|Check the each video port status |Get the each video port handle,check each Video Port enable/disable if port disabled, enable port and check the each port status. |dsGetVideoPort(), dsIsVideoPortEnabled(), dsEnableVideoPort() |`Y`|`NA`|`Y`|`Y`|`NA`|
||For each video port handle, verify each port display connected/disconnected status without video port connected|dsIsDisplayConnected(), dsIsVideoPortActive()|`Y`|`NA`|`Y`|`Y`|`NA`|
||Verify each port display connected/disconnected status by connecting/disconnecting video port|dsIsDisplayConnected(), dsIsVideoPortActive()|`NA`|`Y`|`Y`|`NA`|`Y`|
||For each video port handle, get the surround mode capabilities of each port and verify with configuration YAML file 'Panel_4K_VideoPort.yaml'. If it is a sink device, the value to be retrieved from the YAML file is "Ports/PortNo/Display_surrond" where PortNo is 1 as sink device has only INTERNAL port.|dsIsDisplaySurround()|`Y`|`NA`|`NA`|`Y`|`NA`|
||For each video port handle, verify the each port surround mode capabilities of connected display and verify with configuration file|dsIsDisplaySurround(), dsGetSurroundMode()|`Y`|`NA`|`Y`|`NA`|`NA`|

#### Test Startup Requirement-Check the video port status

`NA`

#### Emulator Requirements-Check the video port status

[Emulator Requirements](#emulator-requirements)

#### Control Plane Requirements-Check the video port status

plug/Unplug the Video port,Verify with edid info, is surround mode supported

### Check Video Content Format and Resolution

|Test Functionality|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|---------|--|--|------|----|--------------------------|
|Check Video Format Content and Resolution|Register callback for the Video Format update event,change the video formate and check whether callback is Triggered or not|dsVideoFormatUpdateRegisterCB()|`NA`|`Y`|`Y`|`Y`|`Y`|
||For each video port handle, set each Video port properties like pixel resolution, Aspect ratio, Stereo Scopic modes, frame rates & scan modes and looping through with supported values, Verify using get function |dsSetResolution(), dsGetResolution()|`Y`|`NA`|`Y`|`NA`|`NA`|
||Set current active Video port properties like pixel resolution, Aspect ratio, Stereo Scopic modes, frame rates & scan modes and looping through with supported values and verify external Analyzer with video playback |dsIsVideoPortActive(), dsSetResolution(), dsGetResolution()|`NA`|`Y`|`Y`|`NA`|`Y`|
||For each video port handle, gets the each port supported resolutions of TV and verify with the configuration YAML file 'Panel_4K_VideoPort.yaml'. If it is a sink device, the value to be retrieved from the YAML file is "Ports/PortNo/Supported_tv_resolutions_capabilities" where PortNo is 1 as sink device has only INTERNAL port.|dsSupportedTvResolutions()|`Y`|`NA`|`Y`|`Y`|`Y`|
||Get the current active Video port resolution and verify with the external device|dsIsVideoPortActive(), dsGetResolution()|`NA`|`Y`|`Y`|`Y`|`Y`|

#### Test Startup Requirement-Check Video Content Format and Resolution

Playback the pre-define streams

#### Emulator Requirements-Check Video Content Format and Resolution

[Emulator Requirements](#emulator-requirements)

#### Control Plane Requirements-Check Video Content Format and Resolution

Check the each  port output resolutions and Verify the AspectRatio,video Stereo Scopic modes,video Frame rates,interlaced/progressive.

### Check HDR Capability

|Test Functionality|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|---------|--|--|------|----|--------------------------|
|Check HDR Capability|For each video port handle, get the each port HDR capabilities & verify with the configuration YAML file 'Panel_4K_VideoPort.yaml'. If it is a sink device, the value to be retrieved from the YAML file is "Ports/PortNo/hdr_capabilities" where PortNo is 1 as sink device has only INTERNAL port. |dsGetTVHDRCapabilities()|`Y`|`NA`|`Y`|`Y`|`NA`|
||get the HDR format current active video port and verify with external analyzer|dsIsVideoPortActive(), dsGetVideoEOTF()|`NA`|`Y`|`Y`|`Y`|`Y`|
||Checks current active video port output is HDR with different HDR/SDR streams and verify with external analyzer|dsIsVideoPortActive(), dsIsOutputHDR()|`NA`|`Y`|`Y`|`Y`|`Y`|
||Set/Reset force HDR mode for the current active video port and verify with external analyzer is HDR mode is set/reset|dsIsVideoPortActive(), dsSetForceHDRMode()|`NA`|`Y`|`Y`|`NA`|`Y`|
||Reset the current active video port output to SDR and verify with external analyzer|dsIsVideoPortActive(), dsResetOutputToSDR()|`NA`|`Y`|`Y`|`NA`|`Y`|
||For each video port handle, set Force Disable 4KSupport for each port and verify with get function|dsSetForceDisable4KSupport(), dsGetForceDisable4KSupport()|`Y`|`NA`|`Y`|`Y`|`NA`|
||Set Force Disable 4KSupport for active port on playback and verify with analyzer|dsIsVideoPortActive(), dsSetForceDisable4KSupport()|`NA`|`Y`|`Y`|`Y`|`NA`|


#### Test Startup Requirement-Check HDR Capability

Playback the pre-define streams

#### Emulator Requirements-Check HDR Capability

[Emulator Requirements](#emulator-requirements)

#### Control Plane Requirements-Check HDR Capability

Check video out is HDR or SDR and verify with analyzer

### HDCP Management

|Test Functionality|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|---------|--|--|------|----|--------------------------|
|Check HDCP status|Check enable/disable the HDCP(1.x & 2.x) for the current active video port with playback |dsIsVideoPortActive(), dsEnableHDCP(), dsIsHDCPEnabled()|`NA`|`Y`|`Y`|`NA`|`NA`|
||For each video port handle, check each port HDCP status and verify is dsHDCP_STATUS_AUTHENTICATED return for sink and dsHDCP_STATUS_UNPOWERED/dsHDCP_STATUS_PORTDISABLED for source |dsGetHDCPStatus()|`Y`|`NA`|`Y`|`Y`|`NA`|
||Check current active port HDCP status and check with connected device|dsIsVideoPortActive(), dsGetHDCPStatus() |`NA`|`Y`|`Y`|`NA`|`NA`|
||For each video port handle, check each port HDCP protocol Status and verify with the configuration YAML file 'Panel_4K_VideoPort.yaml'. If it is a sink device, the value to be retrieved from the YAML file is "Ports/PortNo/hdcp_protocol_version" where PortNo is 1 as sink device has only INTERNAL port.|dsGetHDCPProtocol()|`Y`|`NA`|`Y`|`Y`|`NA`|
||Check current active port HDCP protocol Status with connected device |dsIsVideoPortActive(), dsGetHDCPCurrentProtocol()|`NA`|`Y`|`Y`|`Y`|`Y`|
||Check active port HDCP Receiver protocol version with connected device|dsIsVideoPortActive(), dsGetHDCPReceiverProtocol(),|`NA`|`Y`|`Y`|`NA`|`Y`|
||Ignore EDID status for active port with connected device|dsIsVideoPortActive(), dsGetIgnoreEDIDStatus()|`N`|`Y`|`Y`|`NA`|`Y`|
||For each video port handle, set preferred HDCP Protocol version for each valid port and verify using get|dsSetHdmiPreference(), dsGetHdmiPreference()|`Y`|`NA`|`Y`|`Y`|`NA`|
||set/get preferred HDCP Protocol version for active port with connected device |dsIsVideoPortActive(), dsSetHdmiPreference(), dsGetHdmiPreference()|`NA`|`Y`|`Y`|`NA`|`NA`|
||Notify event if the HDCP status change and check the timing info for hdcp authentication |dsRegisterHdcpStatusCallback()|`NA`|`Y`|`Y`|`NA`|`Y`|
||Check HDCP status for active port and verify with external analyzer|dsRegisterHdcpStatusCallback()|`NA`|`Y`|`Y`|`NA`|`Y`|

#### Test Startup Requirement-HDCP Management

Playback the pre-define streams

#### Emulator Requirements-HDCP Management

[Emulator Requirements](#emulator-requirements)

#### Control Plane Requirements-HDCP Management

Check the HDCP status with external analyzer

### Color Capabilities

|Test Functionality|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|---------|--|--|------|----|--------------------------|
|For each video port handle, check Color information |Get each port Color Space, compare with the configuration YAML file "Panel_4K_VideoPort.yaml". If it is a sink device,  the value to be retrieved is "Ports/PortNo/colorspaces" where PortNo is 1 as sink device has only INTERNAL port. |dsGetColorSpace()|`Y`|`NA`|`Y`|`Y`|`NA`|
||Get Color Space of active port with video playback|dsIsVideoPortActive(), dsGetColorSpace()|`NA`|`Y`|`Y`|`Y`|`NA`|
||For each video port handle, check each port Color Depth Capabilities and compare with the configuration YAML file "Panel_4K_VideoPort.yaml".If it is a sink device, the value to be retrieved is "Ports/PortNo/Supported_color_depth_capabilities" where PortNo is 1 as sink device has only INTERNAL port. |dsColorDepthCapabilities()|`Y`|`NA`|`Y`|`Y`|`NA`|
||For each video port handle, get each port Color Depth and verify with the configuration YAML file "Panel_4K_VideoPort.yaml".If it is a sink device, the value to be retrieved is "color_depth".|dsGetColorDepth()|`Y`|`NA`|`Y`|`Y`|`NA`|
||Get active port Color Depth and verify with the analyzer|dsIsVideoPortActive(), dsGetColorDepth()|`NA`|`Y`|`Y`|`Y`|`Y`|
||For each video port handle, set preferred color depth for each port and compare get function |dsSetPreferredColorDepth(), dsGetPreferredColorDepth()|`Y`|`NA`|`Y`|`NA`|`NA`|
||Set preferred color depth for current active port and verify with the analyzer |dsIsVideoPortActive(), dsSetPreferredColorDepth()|`NA`|`Y`|`Y`|`NA`|`Y`|
||For each video port handle, get each port QuantizationRange status and verify with the configuration YAML file "Panel_4K_VideoPort.yaml".If it is a sink device, the value to be retrieved is "Ports/PortNo/quantization_ranges" where PortNo is 1 as sink device has only INTERNAL port.|dsGetQuantizationRange()|`Y`|`NA`|`Y`|`Y`|`NA`|
||For each video port handle, get each port MatrixCoefficients status and verify return dsDISPLAY_MATRIXCOEFFICIENT_UNKNOWN for source and with the configuration YAML file "Panel_4K_VideoPort.yaml".If it is a sink device, the value to be retrieved is "Ports/PortNo/matrix_coefficients" where PortNo is 1 as sink device has only INTERNAL port.|dsGetMatrixCoefficients()|`Y`|`NA`|`Y`|`Y`|`NA`|
||Check active port MatrixCoefficients status with video playback and verify with analyzer|dsIsVideoPortActive(), dsGetMatrixCoefficients()|`NA`|`Y`|`Y`|`Y`|`NA`|
||Set Background Color for active port with video playback and verify with analyzer/external device |dsIsVideoPortActive(), dsSetBackgroundColor()|`N`|`Y`|`Y`|`NA`|`Y`|
||Gets current color space setting, color depth, matrix coefficients, HDR type,quantization range in one call of the active video port and verify with analyzer/external device|dsIsVideoPortActive(), dsGetCurrentOutputSettings()|`NA`|`Y`|`Y`|`Y`|`Y`|

#### Test Startup Requirement-Color Capabilities

Playback the pre-define streams

#### Emulator Requirements-Color Capabilities

[Emulator Requirements](#emulator-requirements)

#### Control Plane Requirements-Color Capabilities

Verify the Color Space,Color Depth,QuantizationRange,MatrixCoefficients,Background Color with analyzer/external device
