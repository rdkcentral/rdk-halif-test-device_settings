# HdmiIn High Level Test Specification Document

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Introduction](#introduction)
- [Module Description](#module-description)
- [Testing Scope](#testing-scope)

## Acronyms, Terms and Abbreviations

- `EDID`     - Extended Display Identification Data
- `API`      - Application programming interface
- `HDMI`     - High-Definition Multimedia Interface
- `dsHdmiIn` - Device Settings High-Definition Multimedia Interface Input
- `SPD`      - Source Product Descriptor
- `ALLM`     - Auto Low Latency Mode
- `AVI`      - Audio Video Interleave
- `Y`        - Yes
- `N`        - No
- `NA`       - Not Applicable

## Introduction

This document provides an overview of the high level testing requirements for the `dsHdmiIn` module. It outlines the scope of testing, objectives, testing levels and approaches, specific test requirements, emulator requirements, control plane requirements and expected deliverables.

- Interface of the test is available in this link -  [Interface header](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsHdmiIn.h)

## Module Description

High level overview:

- `dsHdmiIn` provides a variety of `API`s for accessing information regarding the `HDMI` Inputs on sink devices and source devices that has an input port.
- It facilitates interaction with `HDMI` Input ports, aiding in their configuration and utilization within the system. This information is then passed to the caller.
- For the sink and source devices, to retrieve the available `HDMI` Input information, an external device must be connected.

- `HAL` specification : [ds-hdmiIn HAL Spec](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/docs/pages/ds-hdmi-in_halSpec.md)

## Testing Scope

|#|Test Functionality|Test Description|
|-|------------------|----------------|
|1|[Get Number of Inputs](#get-number-of-inputs)|The test aims to verify and validate the number of HDMI Input ports available on the platform.|
|2|[Set and Get the `HDMI` Input port Status](#set-and-get-the-hdmi-input-port-status)|The test is to verify by selecting the HDMI input and getting the status of HDMI Input ports available on the platform.|
|3|[Scale the `HDMI` Input Video](#scale-the-hdmi-input-video)|The test aims to verify and validate the video size and coordinates of the HMDI Input Video.|
|4|[Select Zoom Mode](#select-zoom-mode)|The test aims to verify the zoom mode functionality of the module.|
|5|[Get Current Video Mode](#get-current-video-mode)|The test is to get current HDMI input video mode from active port.|
|6|[Callback for connection Status](#callback-for-connection-status)|The test aims to verify whether it notifies applications when the HDMI input port connection status changes|
|7|[Callback for Signal Change](#callback-for-signal-change)|The test aims to verify the callback function used to inform applications about changes in the signal status of the `HDMI` In.(NoSignal/UnstableSignal/NotSupportedSignal/StableSignal)|
|8|[Callback for Status Change](#callback-for-status-change)|The test validates the functionality of the callback function designed to notify applications of `HDMI` Input status change events.(Port,IsPresented flag status)|
|9|[Callback for Video Mode Change](#callback-for-video-mode-change)|The test validates the functionality of the callback function designed to notify when there is a change in the video resolution|
|10|[Callback for `ALLM` Mode Change](#callback-for-allm-mode-change)|The test validates the functionality of the callback function designed to notify when `HDMI` input `ALLM` mode changes|
|11|[Callback for AV Latency Change](#callback-for-av-latency-change)|The test validates the functionality of the callback function designed to notify when `HDMI` input AV latency changes|
|12|[Callback for `AVI` Content Type Change](#callback-for-avi-content-type-change)|The test validates the functionality of the callback function designed to notify when `HDMI` input AVI content type changes|
|13|[Check `HDMI` ARC Port](#check-hdmi-arc-port)|The test verifies whether the given port is an `HDMI` ARC port or not|
|14|[Set and Get `EDID` Information](#set-and-get-edid-information)|The test is to validate by setting and getting the `EDID` bytes information and `EDID` version|
|15|[Get `HDMI` `SPD` Info](#get-hdmi-spd-info)|The test is to get and verify the `SPD` information.|
|16|[Get Supported Game Feature List](#get-supported-game-feature-list)|The test verifies by getting the all supported game features in the list.|
|17|[Get AV latency](#get-av-latency)|The test validates by getting the current av latency.|
|18|[Get `ALLM` status](#get-allm-status)|The test aims to verify that `ALLM` status is enabled or disabled for the specific `HDMI` input port.|
|19|[Get and Set `EDID` to all `ALLM` Support](#get-and-set-edid-to-all-allm-support)|The test aims to verfiy by setting and getting the `EDID` `ALLM` support.|
-----------

## Get Number of Inputs

|Test Functionality|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|--------|--|--|------|----|--------------------------|
|Get Number of Inputs|Verify that the function returns the expected `HDMI` Input ports. Compare the input port values by parsing the configuration YAML file for sink is `Sink_HDMIIN.yaml (HDMIIN/HdmiInputPort/numberOfPorts)` and source is `Source_HDMIIN.yaml(HDMIIN/HdmiInputPort/numberOfPorts)`|dsHdmiInGetNumberOfInputs()|`Y`|`N`|`Y`|`Y`|`NA`|

### Test Startup Requirement - Get Number of Inputs

The test begins with the configured `HDMI` input port details.

### Emulator Requirement - Get Number of Inputs

Emulator will boot with the port information's coming from the configuration file.

### Control Plane Requirement - Get Number of Inputs

None

## Set and Get the `HDMI` Input port Status

|Test Functionality|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|--------|--|--|------|----|--------------------------|
|Set and Get the `HDMI` Input port Status|Loop through supported `HDMI` Input port, verify that the function successfully sets the specified `HDMI` Input port without any external device connection and "Get status" to check the active port is false, port connected is false and presentation is false. Note:supported `HDMI` Input port, Check profile file for sink is `Sink_HDMIIN.yaml (HDMIIN/HdmiInputPort/numberOfPorts)` and source is `Source_HDMIIN.yaml(HDMIIN/HdmiInputPort/numberOfPorts)`|dsHdmiInGetNumberOfInputs(), dsHdmiInSelectPort(), dsHdmiInGetStatus()|`Y`|`N`|`Y`|`Y`|`NA`|
||Loop through all `HDMI` Input port, verify that the function successfully sets the specified `HDMI` Input port as active for presentation and check the port information is valid using "Get status".Note:supported `HDMI` Input port, Check profile file for sink is `Sink_HDMIIN.yaml (HDMIIN/HdmiInputPort/numberOfPorts)` and source is `Source_HDMIIN.yaml(HDMIIN/HdmiInputPort/numberOfPorts)`|dsHdmiInGetNumberOfInput(), dsHdmiInSelectPort(), dsHdmiInGetStatus()|`N`|`Y`|`Y`|`Y`|`Y`|
||On the active HDMI port, set the Audio Mix to be enable and disable|dsHdmiInSelectPort()|`N`|`Y`|`N`|`Y`|`Y`|
||On the active HDMI port, verify the `HDMI` input with the video plane in both primary and secondary. Additionally, validate the topmost flag.|dsHdmiInSelectPort()|`N`|`Y`|`N`|`Y`|`Y`|

### Test Startup Requirement - Set and Get the `HDMI` Input port Status

- The test begins with the configured `HDMI` input port numbers.
- Connection of the source device with the `HDMI` Input.

### Emulator Requirement - Set and Get the `HDMI` Input port Status

Emulator will boot with the port information's coming from the configuration file.

### Control Plane Requirement - Set and Get the `HDMI` Input port Status

- Connecting and disconnecting source devices in the `HDMI` Input will be handled by the Control Plane. 
- Validate the Audio mix and Video plane by the analyzers.

## Scale the `HDMI` Input Video

|Test Functionality|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|--------|--|--|------|----|--------------------------|
|Scale the `HDMI` Input Video|Verify that the function successfully scales the `HDMI` input video when valid coordinates and dimensions are provided within the resolution limits. Based on video resolution need to check whether the coordinates are in range|dsHdmiInScaleVideo()|`N`|`Y`|`Y`|`Y`|`Y`|

### Test Startup Requirement - Scale the `HDMI` Input Video

The test begins by setting up the video analyzer, and the video should be played.

### Emulator Requirement - Scale the `HDMI` Input Video

Emulator will boot with the port information's coming from the configuration file. Predefined coordinates and dimesions to compare.

### Control Plane Requirement - Scale the `HDMI` Input Video

Control plane to validate the coordinates and dimensions by the video analyzers.

## Select Zoom Mode

|Test Functionality|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|--------|--|--|------|----|--------------------------|
|Select Zoom Mode|Verify that the function successfully updates the video zoom on the active `HDMI` input using the provided zoom mode|dsHdmiInSelectZoomMode()|`N`|`Y`|`Y`|`N`|`Y`|

### Test Startup Requirement - Select Zoom Mode

The test begins by setting up the video analyzer, and the video should be played.

### Emulator Requirement - Select Zoom Mode

Emulator will boot with the zoom modes in the configuration file.

### Control Plane Requirement - Select Zoom Mode

Changing the zoom modes by the Control Plane. Validates the zoom mode by analyzers.

## Get Current Video Mode

|Test Functionality|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|--------|--|--|------|----|--------------------------|
|Get Current Video Mode|Verify that the function successfully updates the current `HDMI` input video modes like Pixel resolution, frame rate and interlaced information of the active port|dsHdmiInGetCurrentVideoMode()|`N`|`Y`|`Y`|`Y`|`Y`|

### Test Startup Requirement - Get Current Video Mode

The test begins by setting up the video analyzer, and the video should be played.

### Emulator Requirement - Get Current Video Mode

Emulator will boot with the all video mode related information in the configuration file.

### Control Plane Requirement - Get Current Video Mode

Control plane validates the current mode by the analyzers.

## Callback for connection Status

|Test Functionality|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|--------|--|--|------|----|--------------------------|
|Callback for connection Status|Verify that the callback function properly updates the connection/disconnection status flag and notifies the application when a `HDMI` Input port is connected or disconnected.|dsHdmiInRegisterConnectCB()|`N`|`Y`|`Y`|`Y`|`Y`|
|Callback for connection Status|Verify that the callback function properly updates the isPresented status in ::dsHdmiInStatus_t, if the connected port is active and presents video after being connected.|dsHdmiInRegisterConnectCB()|`N`|`Y`|`Y`|`Y`|`Y`|

### Test Startup Requirement - Callback for connection Status

Connection of the source device with the `HDMI` Input.

### Emulator Requirement - Callback for connection Status

Emulator will boot with the port information coming from the configuration file.

### Control Plane Requirement - Callback for connection Status

Connecting and disconnecting source devices in the `HDMI` Input will be handled by the Control Plane.

## Callback for Signal Change

|Test Functionality|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|--------|--|--|------|----|--------------------------|
|Callback for Signal Change|Verify that the callback function properly notifies the application whenever there is a change in the signal statuses (e.g., NoSignal, UnstableSignal, NotSupportedSignal, StableSignal) for the `HDMI` Input port.|dsHdmiInRegisterSignalChangeCB()|`N`|`Y`|`N`|`Y`|`Y`|

### Test Startup Requirement - Callback for Signal Change

Connection of the source device with the `HDMI` Input.

### Emulator Requirement - Callback for Signal Change

Emulator will boot with the port information's coming from the configuration file.

### Control Plane Requirement - Callback for Signal Change

- Connecting and disconnecting source devices in the `HDMI` Input will be handled by the Control Plane.
- Provide resolution changes or configurations changes on the connected device that affects the output signal.

## Callback for Status Change

|Test Functionality|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|--------|--|--|------|----|--------------------------|
|Callback for Status Change|Verify that the callback function properly triggers whenever the dsHdmiInStatus_t is updated and notifies the application of the `HDMI` Input status change event.|dsHdmiInRegisterStatusChangeCB()|`N`|`Y`|`N`|`Y`|`Y`|

### Test Startup Requirement - Callback for Status Change

Connection of the source device with the `HDMI` Input.

### Emulator Requirement - Callback for Status Change

Emulator will boot with the port information's coming from the configuration file.

### Control Plane Requirement - Callback for Status Change

Connecting and disconnecting source devices in the `HDMI` Input will be handled by the Control Plane.

## Callback for Video Mode Change

|Test Functionality|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|--------|--|--|------|----|--------------------------|
|Callback for Video Mode Change|Verify that the callback function properly notifies the application whenever there is resolution and other video mode changes.|dsHdmiInRegisterVideoModeUpdateCB()|`N`|`Y`|`N`|`Y`|`Y`|

### Test Startup Requirement - Callback for Video Mode Change

Connection of the source device with the `HDMI` Input.

### Emulator Requirement - Callback for Video Mode Change

Emulator will boot with the video resolutions and other video modes from the configuration file.

### Control Plane Requirement - Callback for Video Mode Change

Changing of the video resolution by control Plane. 

## Callback for `ALLM` mode change

|Test Functionality|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|--------|--|--|------|----|--------------------------|
|Callback for `ALLM` mode change|Verify that the callback function properly notifies the application whenever there is `ALLM` mode change.|dsHdmiInRegisterAllmChangeCB()|`N`|`Y`|`N`|`Y`|`Y`|

### Test Startup Requirement - Callback for `ALLM` mode change

Connection of the source device/compatible gaming console devices with the `HDMI` Input.

### Emulator Requirement - Callback for `ALLM` mode change

Emulator will boot with the `HDMI` input port numbers and `ALLM` mode information.

### Control Plane Requirement - Callback for `ALLM` mode change

Changing of the `ALLM` mode by control Plane.

## Callback for AV Latency Change

|Test Functionality|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|--------|--|--|------|----|--------------------------|
|Callback for AV Latency Change|Verify that the callback function notifies the application whenever there is a change in the `HDMI` input Audio and Video latency within its Max(500ms) and Min(0) ranges.|dsHdmiInRegisterAVLatencyChangeCB()|`N`|`Y`|`N`|`Y`|`Y`|

### Test Startup Requirement - Callback for AV Latency Change

- Connection of the source device with the `HDMI` Input. 
- Test starts with the video playback with different modes ( Film Maker, Cinema mode )

### Emulator Requirement - Callback for AV Latency Change

Emulator will boot with the AV latency information.

### Control Plane Requirement - Callback for AV Latency Change

Control plane signals the source device to play the content ( Cinema mode to Film Maker mode ).

## Callback for `AVI` Content Type Change

|Test Functionality|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|--------|--|--|------|----|--------------------------|
|Callback for `AVI` Content Type Change|Verify that the callback function properly notifies the application whenever there is a change in the `AVI` content type.|dsHdmiInRegisterAviContentTypeChangeCB()|`N`|`Y`|`N`|`Y`|`Y`|

### Test Startup Requirement - Callback for `AVI` Content Type Change

- Connection of the source device with the `HDMI` Input.
- Test starts with the video playback.

### Emulator Requirement - Callback for `AVI` Content Type Change

Emulator will boot with the `AVI` content type information.

### Control Plane Requirement - Callback for `AVI` Content Type Change

Changing `AVI` content type by control Plane..

## Check `HDMI` ARC Port

|Test Functionality|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|--------|--|--|------|----|--------------------------|
|Check `HDMI` ARC Port|Loop through supported `HDMI` Input port and verify whether the given port is an HDMI ARC port by comparing it with the `Sink_HDMIIN.yaml (HDMIIN/HdmiArcPort/portNumber)` configuration file.Note:supported `HDMI` Input port, Check profile file for sink is `Sink_HDMIIN.yaml (HDMIIN/HdmiInputPort/numberOfPorts)`|dsIsHdmiARCPort()|`Y`|`N`|`N`|`Y`|`NA`|

### Test Startup Requirement - Check `HDMI` ARC Port

Test starts with the number of ports and ARC port from the configuration file.

### Emulator Requirement - Check `HDMI` ARC Port

Emulator will boot with the `HDMI` ARC port information.

### Control Plane Requirement - Check `HDMI` ARC Port

None

## Set and Get `EDID` Information

|Test Functionality|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|--------|--|--|------|----|--------------------------|
|Set and Get `EDID` Information|Setting the `EDID` version for a given port and getting back the `EDID` version and compare with the Set value. Also, validate the EDID length for a given port. Compare the EDID length values by parsing the configuration YAML file `Sink_EDID_Info.yaml (HDMIIN/EDID_Data/edidBytesLength)`|dsSetEdidVersion(), dsGetEdidVersion(), dsGetEDIDBytesInfo()|`Y`|`N`|`N`|`Y`|`NA`|
||This test ensures that the module can accurately retrieve and interpret `EDID` information, providing essential data about the display's capabilities and characteristics.|dsGetEdidVersion(), dsGetEDIDBytesInfo()|`N`|`Y`|`N`|`Y`|`Y`|

### Test Startup Requirement - Set and Get `EDID` Information

- Connection of the source device with the `HDMI` Input and video analyzer to check the display capabilities.
- Test starts with the predefined EDID length information coming from the configuration file.

### Emulator Requirement - Set and Get `EDID` Information

Emulator will boot with the `EDID` coming from the configuration file.

### Control Plane Requirement - Set and Get `EDID` Information

Connecting and disconnecting source devices in the `HDMI` Input will be handled by the Control Plane.

## Get `HDMI` `SPD` Info

|Test Functionality|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|--------|--|--|------|----|--------------------------|
|Get `HDMI` `SPD` Info|Test to get the `HDMI` `SPD` Info. Check whether it gets the spd info frame information properly.|dsGetHDMISPDInfo()|`N`|`Y`|`N`|`Y`|`Y`|

### Test Startup Requirement - Get `HDMI` `SPD` Info

Connection of the source device with the `HDMI` Input.

### Emulator Requirement - Get `HDMI` `SPD` Info

Emulator will boot with the `HDMI` SPD information from the configuration file.

### Control Plane Requirement - Get `HDMI` `SPD` Info

Connecting and disconnecting source devices in the `HDMI` Input will be handled by the Control Plane. Check the SPD info frame - Vendor name by the Analyzers.

## Get Supported Game Feature List

|Test Functionality|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|--------|--|--|------|----|--------------------------|
|Get Supported Game Feature List|Make sure that the functionality can list and get the count of all the game features that are supported. Compare the result by parsing the configuration YAML file `Sink_HDMIIN.yaml(HDMIIN/gameFeatures/count)`|dsGetSupportedGameFeaturesList()|`Y`|`N`|`N`|`Y`|`NA`|

### Test Startup Requirement - Get Supported Game Feature List

Connection of the source device/game supported device with the `HDMI` Input. Test boots with the game feature list and count in the configuration file to compare the results.

### Emulator Requirement - Get Supported Game Feature List

Emulator will boot with the game supported features in the configuration.

### Control Plane Requirement - Get Supported Game Feature List

None

## Get AV latency 

|Test Functionality|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|--------|--|--|------|----|--------------------------|
|Get AV latency|The test gets the current AV latency connected to the source device. Also, It checks the AV latency after changing the AV content, such as switching from FilmMaker mode to any other mode.|dsGetAVLatency|`N`|`Y`|`N`|`Y`|`Y`|

### Test Startup Requirement - Get AV latency

- Connection of the source device with the `HDMI` Input.
- Test starts up with the video playback content of different modes ( Film Maker mode, Cinema mode )

### Emulator Requirement - Get AV latency

Emulator will boot with the av latency information in configuration file.

### Control Plane Requirement - Get AV latency

- Control plane handles the switch between the modes ( Film Maker modes and Cinema modes ). 
- Control Plane to test the content with post processing and without post processing.

## Get `ALLM` Status 

|Test Functionality|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|--------|--|--|------|----|--------------------------|
|Get `ALLM` Status|Gets the `ALLM` status of the designated `HDMI` input port. The status information indicates whether `ALLM` is enabled or disabled|dsGetAllmStatus()|`N`|`Y`|`N`|`Y`|`NA`|

### Test Startup Requirement - Get `ALLM` status

Connection of the Game console source devce with the `HDMI` Input with game playback. 

### Emulator Requirement - Get `ALLM` status

Emulator will boot with the `ALLM` configuration details.

### Control Plane Requirement - Get `ALLM` status

None

## Get and Set `EDID` to all `ALLM` Support

|Test Functionality|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|------------------|-----------|--------|--|--|------|----|--------------------------|
|Get and Set `EDID` to all `ALLM` Support|Set and Get the `ALLM` support to `EDID` version 2.0 without connecting any source devices.|dsSetEdid2AllmSupport(), dsGetEdid2AllmSupport()|`Y`|`N`|`N`|`Y`|`NA`|
||Set and Get `ALLM` support to `EDID` Version 2.0 with the connected external source device|dsSetEdid2AllmSupport(), dsGetEdid2AllmSupport()|`N`|`Y`|`N`|`Y`|`Y`|

### Test Startup Requirement - Get and Set `EDID` to all `ALLM` Support

Connection of the Game console source device with the `HDMI` Input.

### Emulator Requirement - Get and Set `EDID` to all `ALLM` Support

Emulator will boot with the `ALLM` support information.

### Control Plane Requirement - Get and Set `EDID` to all `ALLM` Support

Control plane connects/ disconnects the external devices. Validates the ALLM by analyzers.
