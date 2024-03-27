# HdmiIn Test Document

## Version History

| Date(DD/MM/YY) | Comment       | Version |
| -------------- | ------------- | ------- |
| 27/03/2024     | First Release | 1.0.0   |

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Introduction](#introduction)
- [Module Description](#module-description)
- [Testing Scope](#testing-scope)

## Acronyms, Terms and Abbreviations

- `EDID`  - Extended Display Identification
- `API`   - Application programming interface
- `HDMI`  - High-Definition Multimedia Interface
- `dsHdmiIn` - Device Settings High-Definition Multimedia Interface Input
- `SPD` - Source Product Descriptor
- `ALLM` - Auto Low Latency Mode 

## Introduction

This document provides an overview of the testing requirements for the `dsHdmiIn` module. It outlines the scope of testing, objectives, testing levels and approaches, specific test requirements, emulator requirements, control plane requirements and expected deliverables.

Interface of the test is available in this link -  [https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsHdmiIn.h](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsHdmiIn.h)

## Module Description

High level overview:

- `dsHdmiIn` provides a variety of `API`s for accessing information regarding the `HDMI` Inputs on sink devices and source devices that has an input port.
- It facilitates interaction with `HDMI` Input ports, aiding in their configuration and utilization within the system. This information is then passed to the caller.
- For the sink and source devices, to retrieve the available `HDMI` Input information, an external device must be connected.

## Testing Scope

|#|Test Functionality|Test Description|
|-|------------------|----------------|
|1|[Get Number of Inputs](#get-number-of-inputs)|The test aims to verify and validate the number of HDMI Input ports available on the platform.|
|2|[Get the Input Status](#get-the-input-status)|The test is to verify the status of all HDMI Input ports available on the platform.|
|3|[Set the `HDMI` port](#set-the-hdmi-port)|The test is to set and verify the HDMI Input port for Presentation|
|4|[Scale the `HDMI` Input Video](#scale-the-hdmi-input-video)|The test aims to verify and validate the video size and coordinates of the HMDI Input Video.|
|5|[Select Zoom Mode](#select-zoom-mode)|The test aims to verify the zoom mode functionality of the module.|
|6|[Get Current Video Mode](#get-current-video-mode)|The test is to get current HDMI input video mode from active port.|
|7|[Callback for connection Status](#callback-for-connection-status)|The test aims to verify whether it notifies applications when the HDMI input port connection status changes|
|8|[Callback for Signal Change](#callback-for-signal-change)|The test aims to verify the callback function used to inform applications about changes in the signal status of the `HDMI` In.(NoSignal/UnstableSignal/NotSupportedSignal/StableSignal)|
|9|[Callback for Status Change](#callback-for-status-change)|The test validates the functionality of the callback function designed to notify applications of `HDMI` Input status change events.(Port,IsPresented flag status)|
|9|[Callback for Video Mode Change](#callback-for-video-mode-change)|The test validates the functionality of the callback function designed to notify when there is a change in the video resolution|
|10|[Callback for `ALLM` Mode Change](#callback-for-allm-mode-change)|The test validates the functionality of the callback function designed to notify when `HDMI` input `ALLM` mode changes|
|11|[Callback for AV Latency Change](#callback-for-av-latency-change)|The test validates the functionality of the callback function designed to notify when `HDMI` input AV latency changes|
|12|[Callback for AVI Content Type Change](#callback-for-avi-content-type-change)|The test validates the functionality of the callback function designed to notify when `HDMI` input AVI content type changes|
|13|[Check `HDMI` ARC Port](#check-hdmi-arc-port)|The test verifies whether the given port is an `HDMI` ARC port or not|
|14|[Set and Get `EDID` Information](#set-and-get-edid-information)|The test is to validate by setting and getting the `EDID` bytes information and `EDID` version|
|15|[Get `HDMI` `SPD` Info](#get-hdmi-spd-info)|The test is to get and verify the `SPD` information.|
|16|[Get Supported Game Feature List](#get-supported-game-feature-list)|The test verifies by getting the all supported game features in the list.|
|17|[Get AV latency](#get-av-latency)|The test validates by getting the current av latency.|
|18|[Get `ALLM` status](#get-allm-status)|The test aims to verify that `ALLM` status is enabled or disabled for the specific `HDMI` input port.|
|19|[Get and Set `EDID` to all `ALLM` Support](#get-and-set-edid-to-all-allm-support)|The test aims to verfiy by setting and getting the `EDID` `ALLM` support.|
-----------

## Get Number of Inputs

|Description|L2|L3|Source|Sink|
|-----------|--|--|------|----|
|Verify that the function returns the expected `HDMI` Input ports.|Y|N|Y|Y|

### Test Startup Requirement - Get Number of Inputs

The test begins with the configured `HDMI` input port details.

### Emulator Requirement - Get Number of Inputs

Emulator will boot with the port informations coming from the configuration file.

### Control Plane Requirement - Get Number of Inputs

None

## Get the Input Status

|Description|L2|L3|Source|Sink|
|-----------|--|--|------|----|
|Verify the status of the `HDMI` Input by ensuring it is in disable status.|Y|N|Y|Y|
|Verify the status of the `HDMI` Input by ensuring it is enabled/disabled, connected to the source, and that the `HDMI` input port is active.|N|Y|Y|Y|

### Test Startup Requirement - Get the Input Status

Connection of the source device with the `HDMI` Input.

### Emulator Requirement - Get the Input Status

Emulator will boot with the port informations coming from the configuration file.

### Control Plane Requirement - Get the Input Status

The handling of connecting and disconnecting source devices in the `HDMI` Input will be managed by the Control Plane.

## Set the `HDMI` port

|Description|L2|L3|Source|Sink|
|-----------|--|--|------|----|
|Verify that the function successfully sets the specified `HDMI` Input port as active for presentation and check the port information using "Get status".|Y|Y|Y|Y|
|Evaluate the function's response when called with a port ID that is already selected as active, ensuring it does not introduce any unintended changes.|N|Y|Y|Y|
|Set the Audio Mix to be enable and disable|N|Y|N|Y|
|Verify the `HDMI` input with the video plane in both primary and secondary. Additionally, validate the topmost flag.|N|Y|N|Y|

### Test Startup Requirement - Set the `HDMI` port

The test begins with the configured `HDMI` input port numbers, video plane types.

### Emulator Requirement - Set the `HDMI` port

Emulator will boot with the port informations coming from the configuration file.

### Control Plane Requirement - Set the `HDMI` port

The Control Plane must monitor the external device (Video analyzer) to detect any video glitches and other audio mix, video plane functionalities.

## Scale the `HDMI` Input Video

|Description|L2|L3|Source|Sink|
|-----------|--|--|------|----|
|Verify that the function successfully scales the `HDMI` input video when valid coordinates and dimensions are provided within the current resolution limits. Based on video resolution need to check whether the coordinates are in range|N|Y|Y|Y|

### Test Startup Requirement - Scale the `HDMI` Input Video

The test begins by setting up the video analyzer, and the video should be played.

### Emulator Requirement - Scale the `HDMI` Input Video

Emulator will boot with the port informations coming from the configuration file. Predefined coordinates and dimesions to compare.

### Control Plane Requirement - Scale the `HDMI` Input Video

Control plane to validate the coordinates and dimensions by the video analyzers.

## Select Zoom Mode

|Description|L2|L3|Source|Sink|
|-----------|--|--|------|----|
|Verify that the function successfully updates the video zoom on the active `HDMI` input using the provided zoom mode|N|Y|Y|N|

### Test Startup Requirement - Select Zoom Mode

The test begins by setting up the video analyzer, and the video should be played.

### Emulator Requirement - Select Zoom Mode

Emulator will boot with the zoom modes in the configuration file.

### Control Plane Requirement - Select Zoom Mode

Changing the zoom modes by the Control Plane.

## Get Current Video Mode

|Description|L2|L3|Source|Sink|
|-----------|--|--|------|----|
|Verify that the function successfully updates the current `HDMI` input video modes like Pixel resolution, frame rate and interlaced information of the active port|N|Y|Y|Y|

### Test Startup Requirement - Get Current Video Mode

The test begins by setting up the video analyzer, and the video should be played.

### Emulator Requirement - Get Current Video Mode

Emulator will boot with the all video mode related information in the configuration file.

### Control Plane Requirement - Get Current Video Mode

None

## Callback for connection Status

|Description|L2|L3|Source|Sink|
|-----------|--|--|------|----|
|Verify that the callback function properly notifies the application when a `HDMI` Input port is connected or disconnected.|N|Y|Y|Y|
|Validate that the callback function updates the isPortConnected status correctly based on the connection state provided.|N|Y|Y|Y|
|Verify that the callback function properly updates the isPresented status in ::dsHdmiInStatus_t if the connected port is active and presents video after being connected.|N|Y|Y|Y|

### Test Startup Requirement - Callback for connection Status

Connection of the source device with the `HDMI` Input.

### Emulator Requirement - Callback for connection Status

Emulator will boot with the port information coming from the configuration file.

### Control Plane Requirement - Callback for connection Status

The handling of connecting and disconnecting source devices in the `HDMI` Input will be managed by the Control Plane.

## Callback for Signal Change

|Description|L2|L3|Source|Sink|
|-----------|--|--|------|----|
|Verify that the callback function properly handles different signal statuses (e.g., NoSignal, UnstableSignal, NotSupportedSignal, StableSignal) and updates the application accordingly.|N|Y|N|Y|
|Validate that the callback function updates the sigStatus parameter correctly based on the signal status provided.|N|Y|N|Y|

### Test Startup Requirement - Callback for Signal Change

Connection of the source device with the `HDMI` Input.

### Emulator Requirement - Callback for Signal Change

Emulator will boot with the port informations coming from the configuration file.

### Control Plane Requirement - Callback for Signal Change

The handling of connecting and disconnecting source devices in the `HDMI` Input will be managed by the Control Plane.
Provide resolution changes or configurations changes on the connected device that affects the output signal.

## Callback for Status Change

|Description|L2|L3|Source|Sink|
|-----------|--|--|------|----|
|Verify that the callback function properly notifies the application of the `HDMI` Input status change event.|N|Y|N|Y|
|Validate that the callback function updates the inputStatus parameter correctly based on the status change provided.|N|Y|N|Y|
|Verify that the callback function properly triggers whenever the dsHdmiInStatus_t is updated|N|Y|N|Y|

### Test Startup Requirement - Callback for Status Change

Connection of the source device with the `HDMI` Input.

### Emulator Requirement - Callback for Status Change

Emulator will boot with the port informations coming from the configuration file.

### Control Plane Requirement - Callback for Status Change

The handling of connecting and disconnecting source devices in the `HDMI` Input will be managed by the Control Plane.

## Callback for Video Mode Change

|Description|L2|L3|Source|Sink|
|-----------|--|--|------|----|
|Verify that the callback function properly notifies the application whenever there is resolution and other video mode changes.|N|Y|N|Y|

### Test Startup Requirement - Callback for Video Mode Change

Connection of the source device with the `HDMI` Input.

### Emulator Requirement - Callback for Video Mode Change

Emulator will boot with the video resolutions and other video modes from the configuration file.

### Control Plane Requirement - Callback for Video Mode Change

Changing of the video resolution by control Plane.

## Callback for `ALLM` mode change

|Description|L2|L3|Source|Sink|
|-----------|--|--|------|----|
|Verify that the callback function properly notifies the application whenever there is `ALLM` mode and Dolby Vison Mode change.|N|Y|N|Y|

### Test Startup Requirement - Callback for `ALLM` mode change

Connection of the source device/compatible gaming console devices with the `HDMI` Input.

### Emulator Requirement - Callback for `ALLM` mode change

Emulator will boot with the `HDMI` input port numbers and `ALLM` mode information.

### Control Plane Requirement - Callback for `ALLM` mode change

Changing of the `ALLM` mode by control Plane.

## Callback for AV Latency Change

|Description|L2|L3|Source|Sink|
|-----------|--|--|------|----|
|Verify that the callback function notifies the `HDMI` input Audio and Video latency within its Max and Min ranges.|N|Y|N|Y|

### Test Startup Requirement - Callback for AV Latency Change

Connection of the source device with the `HDMI` Input and video analyzer to check the AV latency.

### Emulator Requirement - Callback for AV Latency Change

Emulator will boot with the AV latency information.

### Control Plane Requirement - Callback for AV Latency Change

Control Plane changes the AV latency

## Callback for AVI Content Type Change

|Description|L2|L3|Source|Sink|
|-----------|--|--|------|----|
|Verify that the callback function properly notifies the application whenever there is a change in the AVI content type.|N|Y|N|Y|

### Test Startup Requirement - Callback for AVI Content Type Change

Connection of the source device with the `HDMI` Input.

### Emulator Requirement - Callback for AVI Content Type Change

Emulator will boot with the AVI content type information.

### Control Plane Requirement - Callback for AVI Content Type Change

Changing AVI content type by control Plane.

## Check `HDMI` ARC Port

|Description|L2|L3|Source|Sink|
|-----------|--|--|------|----|
|Verify whether given port is an `HDMI` ARC port or not.|Y|N|N|Y|

### Test Startup Requirement - Check `HDMI` ARC Port

Connection of the source device with the `HDMI` Input.

### Emulator Requirement - Check `HDMI` ARC Port

Emulator will boot with the `HDMI` ARC port information.

### Control Plane Requirement - Check `HDMI` ARC Port

Changing of the port with `HDMI` ARC by control Plane.

## Set and Get `EDID` Information

|Description|L2|L3|Source|Sink|
|-----------|--|--|------|----|
|Setting the `EDID` version for a given port|Y|Y|N|Y|
|Get the `EDID` version and length for a given port and compare with the Set value|Y|Y|N|Y|
|This test ensures that the module can accurately retrieve and interpret `EDID` information, providing essential data about the display's capabilities and characteristics.|N|Y|N|Y|

### Test Startup Requirement - Set and Get `EDID` Information

Launch the test with the predefined configuration set of results.

### Emulator Requirement - Set and Get `EDID` Information

Emulator will boot with the `EDID` coming from the configuration file.

### Control Plane Requirement - Set and Get `EDID` Information

None

## Get `HDMI` `SPD` Info

|Description|L2|L3|Source|Sink|
|-----------|--|--|------|----|
|Test to get the `HDMI` `SPD` Info. Check whether it gets the spd info frame information properly.|N|Y|N|Y|

### Test Startup Requirement - Get `HDMI` `SPD` Info

Connection of the source device with the `HDMI` Input. Expected predefined data to compare the information.

### Emulator Requirement - Get `HDMI` `SPD` Info

Emulator will boot with the `HDMI` SPD information from the configuration file.

### Control Plane Requirement - Get `HDMI` `SPD` Info

None

## Get Supported Game Feature List

|Description|L2|L3|Source|Sink|
|-----------|--|--|------|----|
|Make sure that the functionality can list and get the count of all the game features that are supported.|Y|N|N|Y|

### Test Startup Requirement - Get Supported Game Feature List

Connection of the source device/game supported device with the `HDMI` Input.

### Emulator Requirement - Get Supported Game Feature List

Emulator will boot with the game supported features in the configuration.

### Control Plane Requirement - Get Supported Game Feature List

None

## Get AV latency 

|Description|L2|L3|Source|Sink|
|-----------|--|--|------|----|
|Test verifies to get the current AV latency connected when there is a change in the AV content. eg., Shifting from FilmMaker mode to any other mode|N|Y|N|Y|

### Test Startup Requirement - Get AV latency

Connection of the source device with the `HDMI` Input.

### Emulator Requirement - Get AV latency

Emulator will boot with the av latency information in configuration file.

### Control Plane Requirement - Get AV latency

None.

## Get `ALLM` Status 

|Description|L2|L3|Source|Sink|
|-----------|--|--|------|----|
|Gets the `ALLM` status of the designated `HDMI` input port. The status information indicates whether `ALLM` is enabled or disabled|Y|N|N|Y|

### Test Startup Requirement - Get `ALLM` status

Connection of the Game console source devce with the `HDMI` Input with game playback.

### Emulator Requirement - Get `ALLM` status

Emulator will boot with the `ALLM` configuration details.

### Control Plane Requirement - Get `ALLM` status

None

## Get and Set `EDID` to all `ALLM` Support 

|Description|L2|L3|Source|Sink|
|-----------|--|--|------|----|
|Set the `ALLM` support to `EDID` Version 2.0. Check by enable and disable the support.|N|Y|N|Y|
|Get the `ALLM` support to `EDID` Version 2.0. Check whether it is enabled or disabled. |N|Y|N|Y|

### Test Startup Requirement - Get and Set `EDID` to all `ALLM` Support

Connection of the Game console source device with the `HDMI` Input.

### Emulator Requirement - Get and Set `EDID` to all `ALLM` Support

Emulator will boot with the `ALLM` support information.

### Control Plane Requirement - Get and Set `EDID` to all `ALLM` Support

None
