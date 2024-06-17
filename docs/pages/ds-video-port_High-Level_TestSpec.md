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
|Check the each video port status |Get the handle for each video port, check the status of each video port to see if it's enabled or disabled. If a port is disabled, enable it, and then verify the status of each port. |dsGetVideoPort(), dsIsVideoPortEnabled(), dsEnableVideoPort() |`Y`|`NA`|`Y`|`Y`|`NA`|
||Verify the connected/disconnected status of each port's display when no video port is connected.|dsIsDisplayConnected(), dsIsVideoPortActive()|`Y`|`NA`|`Y`|`Y`|`NA`|
||Verify the connected/disconnected status of each port's display by connecting/disconnecting the video port|dsIsDisplayConnected(), dsIsVideoPortActive()|`NA`|`Y`|`Y`|`NA`|`Y`|
||Retrieve the surround mode capabilities of each port and verify them with the configuration YAML file. If it is a sink device, retrieve the value from 'Sink_4K_VideoPort.yaml' using the path "Ports/1/Display_surround" since the sink device has only an INTERNAL port. It is not supported for the source devices|dsIsDisplaySurround()|`Y`|`NA`|`NA`|`Y`|`NA`|
||Verify the each port surround mode capabilities of connected display and verify with configuration file. It is not supported of Sink devices. If it is a source devices, the value has to be retrieved from the "Source_4K_VideoPort.yaml" using the path "Ports/1/Display_surround" supported by the HDMI device.|dsIsDisplaySurround(), dsGetSurroundMode()|`Y`|`NA`|`Y`|`NA`|`NA`|

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
||Set properties for each video port, including pixel resolution, aspect ratio, stereoscopic modes, frame rates, and scan modes, looping through supported values. Verify the settings using the get function |dsSetResolution(), dsGetResolution()|`Y`|`NA`|`Y`|`NA`|`NA`|
||Set current active Video port properties like pixel resolution, Aspect ratio, Stereo Scopic modes, frame rates & scan modes and looping through with supported values and verify external Analyzer with video playback |dsIsVideoPortActive(), dsSetResolution(), dsGetResolution()|`NA`|`Y`|`Y`|`NA`|`Y`|
||Gets the each port supported resolutions of TV and verify with the configuration YAML file. If it is a sink device, the value to be retrieved from the 'Sink_4K_VideoPort.yaml' by using the path "Ports/1/Supported_tv_resolutions_capabilities", supported by INTERNAL port. For source devices, the value to be retrieved from the 'Source_4K_VideoPort.yaml' by using the path "Ports/1/Supported_tv_resolutions_capabilities", supported by HDMI port.|dsSupportedTvResolutions()|`Y`|`NA`|`Y`|`Y`|`Y`|
||Get the current active Video port resolution and verify with the external device|dsIsVideoPortActive(), dsGetResolution()|`NA`|`Y`|`Y`|`Y`|`Y`|

#### Test Startup Requirement-Check Video Content Format and Resolution

Playback the pre-define streams

#### Emulator Requirements-Check Video Content Format and Resolution

[Emulator Requirements](#emulator-requirements)

#### Control Plane Requirements-Check Video Content Format and Resolution

Check the each  port output resolutions and Verify the AspectRatio,video Stereo Scopic modes,video Frame rates,interlaced/progressive.

### Check HDR Capability

|Test Functionality|Description|HAL API's|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|---------|--|--|------|----|--------------------------|
|Check HDR Capability|Get the each port HDR capabilities & verify with the configuration YAML file YAML file. If it is a sink device, the value to be retrieved from the 'Sink_4K_VideoPort.yaml' by using the path "Ports/1/hdr_capabilities", supported by INTERNAL port. For source devices, the value to be retrieved from the 'Source_4K_VideoPort.yaml' by using the path "Ports/1/hdr_capabilities", supported only by HDMI port.|dsGetTVHDRCapabilities()|`Y`|`NA`|`Y`|`Y`|`NA`|
||get the HDR format current active video port and verify with external analyzer|dsIsVideoPortActive(), dsGetVideoEOTF()|`NA`|`Y`|`Y`|`Y`|`Y`|
||Checks current active video port output is HDR with different HDR/SDR streams and verify with external analyzer|dsIsVideoPortActive(), dsIsOutputHDR()|`NA`|`Y`|`Y`|`Y`|`Y`|
||Set/Reset force HDR mode for the current active video port and verify with external analyzer is HDR mode is set/reset|dsIsVideoPortActive(), dsSetForceHDRMode()|`NA`|`Y`|`Y`|`NA`|`Y`|
||Reset the current active video port output to SDR and verify with external analyzer|dsIsVideoPortActive(), dsResetOutputToSDR()|`NA`|`Y`|`Y`|`NA`|`Y`|
||Set Force-disable 4K support for each port and verify it using the get function.|dsSetForceDisable4KSupport(), dsGetForceDisable4KSupport()|`Y`|`NA`|`Y`|`Y`|`NA`|
||Set Force Disable 4KSupport for active port on playback and verify with analyzer|dsIsVideoPortActive(), dsSetForceDisable4KSupport()|`NA`|`Y`|`Y`|`Y`|`NA`|


#### Test Startup Requirement-Check HDR Capability

Playback the pre-define streams

#### Emulator Requirements-Check HDR Capability

[Emulator Requirements](#emulator-requirements)

#### Control Plane Requirements-Check HDR Capability

Check video out is HDR or SDR and verify with analyzer

### HDCP Management

|Test Functionality|Description|HAL API's|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|---------|--|--|------|----|--------------------------|
|Check HDCP status|Check enable/disable the HDCP(1.x & 2.x) for the current active video port with playback |dsIsVideoPortActive(), dsEnableHDCP(), dsIsHDCPEnabled()|`NA`|`Y`|`Y`|`NA`|`NA`|
||Check the HDCP status of each port and verify if dsHDCP_STATUS_AUTHENTICATED is returned for sinks, and dsHDCP_STATUS_UNPOWERED/dsHDCP_STATUS_PORTDISABLED is returned for sources. |dsGetHDCPStatus()|`Y`|`NA`|`Y`|`Y`|`NA`|
||Check current active port HDCP status and check with connected device|dsIsVideoPortActive(), dsGetHDCPStatus() |`NA`|`Y`|`Y`|`NA`|`NA`|
||Check the HDCP protocol status of each port and verify it with the configuration YAML file. If it is a sink device, retrieve the value from the 'Sink_4K_VideoPort.yaml' file using the path "Ports/1/hdcp_protocol_version" supported by INTERNAL port. For a source device, retrieve the value from the 'Source_4K_VideoPort.yaml' file using the path "Ports/1/hdcp_protocol_version" supported by HDMI port.|dsGetHDCPProtocol()|`Y`|`NA`|`Y`|`Y`|`NA`|
||Check current active port HDCP protocol Status with connected device |dsIsVideoPortActive(), dsGetHDCPCurrentProtocol()|`NA`|`Y`|`Y`|`Y`|`Y`|
||Check active port HDCP Receiver protocol version with connected device|dsIsVideoPortActive(), dsGetHDCPReceiverProtocol(),|`NA`|`Y`|`Y`|`NA`|`Y`|
||Ignore EDID status for active port with connected device|dsIsVideoPortActive(), dsGetIgnoreEDIDStatus()|`N`|`Y`|`Y`|`NA`|`Y`|
||Set the preferred HDCP Protocol version for each valid port and verify it using the get function.|dsSetHdmiPreference(), dsGetHdmiPreference()|`Y`|`NA`|`Y`|`Y`|`NA`|
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

|Test Functionality|Description|HAL API's|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|---------|--|--|------|----|--------------------------|
|Check Color information |Get each port Color Space, compare with the configuration YAML file. If it is a sink device, retrieve the value from the 'Sink_4K_VideoPort.yaml' file using the path "Ports/1/colorspaces" supported by INTERNAL port. For a source device, retrieve the value from the 'Source_4K_VideoPort.yaml' file using the path "Ports/1/colorspaces" supported by HDMI port.|dsGetColorSpace()|`Y`|`NA`|`Y`|`Y`|`NA`|
||Get Color Space of active port with video playback|dsIsVideoPortActive(), dsGetColorSpace()|`NA`|`Y`|`Y`|`Y`|`NA`|
||Check each port Color Depth Capabilities and compare with the configuration YAML file . If it is a sink device, retrieve the value from the 'Sink_4K_VideoPort.yaml' file using the pat "Ports/1/Supported_color_depth_capabilities" supported by INTERNAL port. For a source device, retrieve the value from the 'Source_4K_VideoPort.yaml' file using the path "Ports/1/Supported_color_depth_capabilities" supported by HDMI port.|dsColorDepthCapabilities()|`Y`|`NA`|`Y`|`NA`|`NA`|
||Get each port Color Depth and verify with the configuration YAML file . If it is a sink device, retrieve the value from the 'Sink_4K_VideoPort.yaml' file using the path "color_depth" supported by INTERNAL port. For a source device, retrieve the value from the 'Source_4K_VideoPort.yaml' file using the path "color_depth" supported by HDMI port.|dsGetColorDepth()|`Y`|`NA`|`Y`|`Y`|`NA`|
||Get active port Color Depth and verify with the analyzer|dsIsVideoPortActive(), dsGetColorDepth()|`NA`|`Y`|`Y`|`Y`|`Y`|
||Set preferred color depth for each port and compare get function |dsSetPreferredColorDepth(), dsGetPreferredColorDepth()|`Y`|`NA`|`Y`|`NA`|`NA`|
||Set preferred color depth for current active port and verify with the analyzer |dsIsVideoPortActive(), dsSetPreferredColorDepth()|`NA`|`Y`|`Y`|`NA`|`Y`|
||Get each port QuantizationRange status and verify with the configuration YAML file. If it is a sink device, retrieve the value from the 'Sink_4K_VideoPort.yaml' file using the path "Ports/1/quantization_ranges" supported only by INTERNAL port. For a source device, retrieve the value from the 'Source_4K_VideoPort.yaml' file using the path "Ports/1/quantization_ranges" supported by HDMI port. |dsGetQuantizationRange()|`Y`|`NA`|`Y`|`Y`|`NA`|
||Get each port MatrixCoefficients status and verify return dsDISPLAY_MATRIXCOEFFICIENT_UNKNOWN for source and with the configuration YAML file. If it is a sink device, retrieve the value from the 'Sink_4K_VideoPort.yaml' file using the path "Ports/1/matrix_coefficients" supported only by INTERNAL port. For a source device, retrieve the value from the 'Source_4K_VideoPort.yaml' file using the path "Ports/1/matrix_coefficients" supported by HDMI port.|dsGetMatrixCoefficients()|`Y`|`NA`|`Y`|`Y`|`NA`|
||Check active port MatrixCoefficients status with video playback and verify with analyzer|dsIsVideoPortActive(), dsGetMatrixCoefficients()|`NA`|`Y`|`Y`|`Y`|`NA`|
||Set Background Color for active port with video playback and verify with analyzer/external device |dsIsVideoPortActive(), dsSetBackgroundColor()|`N`|`Y`|`Y`|`NA`|`Y`|
||Gets current color space setting, color depth, matrix coefficients, HDR type,quantization range in one call of the active video port and verify with analyzer/external device|dsIsVideoPortActive(), dsGetCurrentOutputSettings()|`NA`|`Y`|`Y`|`Y`|`Y`|

#### Test Startup Requirement-Color Capabilities

Playback the pre-define streams

#### Emulator Requirements-Color Capabilities

[Emulator Requirements](#emulator-requirements)

#### Control Plane Requirements-Color Capabilities

Verify the Color Space,Color Depth,QuantizationRange,MatrixCoefficients,Background Color with analyzer/external device
