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

- `HAL`   - Hardware Abstraction layer
- `SOC`   - System On a Chip
- `EDID`  - Extended Display Identification
- `API`   - Application programming interface
- `CPU`   - Central processing unit
- `RDK`   - Reference Design Kit
- `HDMI`  - High-Definition Multimedia Interface
- `dsHdmiIn` - Device Settings High-Definition Multimedia Interface Input
- `SPD` - Source Product Descriptor

## Introduction

This document provides an overview of the testing requirements for the `dsHdmiIn` module. It outlines the scope of testing, objectives, testing levels and approaches, specific test requirements, emulator requirements, control plane requirements and expected deliverables.

Interface of the test is available in this link -  [https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsHdmiIn.h](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsHdmiIn.h)

## Module Description

High level overview:

- `dsHdmiIn` provides a variety of APIs for accessing information regarding the Hdmi Inputs on sink devices.
- It facilitates interaction with Hdmi Input ports, aiding in their configuration and utilization within the system. This information is then passed to the caller.
- For the sink devices, to retrieve the available Hdmi Input information, an external device must be connected.

## Testing Scope

|#|Test Functionality|Test Description|
|-|------------------|----------------|
|1|[Get Number of Inputs](#get_number_of_inputs)|The test aims to verify the availability of Hdmi Input ports by confirming the number present.|
|2|[Get the Input Status](#get_the_input_status)|The test is to verify the status of all Hdmi Input Status|
|3|[Set the Hdmi port](#set_the_Hdmi_port)|The test is to set the Hdmi Input port for Presentation|
|4|[Scale the Hdmi Input Video](#scale_the_Hdmi_input_video)|The test scales the Hdmi input video, ensuring that the width and height, determined by the x and y coordinates respectively, do not surpass the current resolution limits of the device.|
|5|[Select Zoom Mode](#select_zoom_mode)|The test is to verify the requested zoom mode|
|6|[Get Current Video Mode](#get_current_video_mode)|The test is to verify the current HDMI input video mode of the HDMI port|
|7|[Callback for connection Status](#callback_for_connection_status)|The test aims to verify the Callback function used for notifying applications of the Hdmi In hot plug status.|
|8|[Callback for Signal Change](#callback_for_signal_change)|The test aims to verify the callback function used to inform applications about changes in the signal status of the Hdmi In.(NoSignal/UnstableSignal/NotSupportedSignal/StableSignal)|
|9|[Callback for Status Change](#callback_for_status_change)|The test validates the functionality of the callback function designed to notify applications of Hdmi Input status change events.(Port,IsPresented flag status)|
|9|[Callback for Video Mode Change](#callback_for_video_mode_change)|The test validates the functionality of the callback function designed to notify when there is a change in the video resolution|
|10|[Callback for ALLM Mode Change](#callback_for_allm_mode_change)|The test validates the functionality of the callback function designed to notify when HDMI input ALLM mode changes|
|11|[Callback for AV Latency Change](#callback_for_av_latency_change)|The test validates the functionality of the callback function designed to notify when HDMI input AV latency changes|
|12|[Callback for AVI Content Type Change](#callback_for_avi_content_type_change)|The test validates the functionality of the callback function designed to notify when HDMI input AVI content type changes|
|13|[Check HDMI ARC Port](#check_hdmi_arc_port)|The test checks if the given port is an HDMI ARC port or not|
|14|[Set and Get EDID Information](#set_get_edid_information)|The test sets and gets the `EDID` bytes information and `EDID` version|
|15|[Get HDMI `SPD` Info](#get_hdmi_`SPD`_info)|The test gets the ``SPD`` information|
|16|[Get Supported Game Feature List](#get_supported_game_feature_list)|The test gets the all supported game features in the list information|
|17|[Get AV latency](#get_av_latency)|The test gets the current av latency|
|18|[Get ALLM status](#get_allm_status)|The test aims to checks whether ALLM status is enabled or disabled for the specific HDMI input port|
|19|[Get and Set ALLM Support](#get_set_allm_support)|The test sets and gets the ALLM support|
-----------

## Get Number of Inputs

|Description|L2|L3|
|-----------|--|--|
|Verify that the function returns the expected Hdmi Input ports.|Y|N|

### Test Startup Requirement - Get Number of Inputs

The test begins with the configured Hdmi input port details.

### Emulator Requirement - Get Number of Inputs

Emulator will boot with the port informations coming from the configuration file.

### Control Plane Requirement - Get Number of Inputs

None

## Get the Input Status

|Description|L2|L3|
|-----------|--|--|
|Verify the status of the Hdmi Input by ensuring it is in disable status.|Y|N|
|Verify the status of the Hdmi Input by ensuring it is enabled, connected to the source, and that the Hdmi input port is active.|N|Y|

### Test Startup Requirement - Get the Input Status

Connection of the source device with the HdmiIn.

### Emulator Requirement - Get the Input Status

Emulator will boot with the port informations coming from the configuration file.

### Control Plane Requirement - Get the Input Status

The handling of connecting and disconnecting source devices in the HdmiIn will be managed by the Control Plane.

## Set the Hdmi port

|Description|L2|L3|
|-----------|--|--|
|verify that the function successfully sets the specified Hdmi Input port as active for presentation and check the port information using "Get status".|Y|Y|
|Evaluate the function's response when called with a port ID that is already selected as active, ensuring it does not introduce any unintended changes.|N|Y|

### Test Startup Requirement - Set the Hdmi port

The test begins with the configured Hdmi input port numbers.

### Emulator Requirement - Set the Hdmi port

Emulator will boot with the port informations coming from the configuration file.

### Control Plane Requirement - Set the Hdmi port

The Control Plane must monitor the external device (Video analyzer) to detect any video glitches.

## Scale the Hdmi Input Video

|Description|L2|L3|
|-----------|--|--|
|Verify that the function successfully scales the Hdmi input video when valid coordinates and dimensions are provided within the current resolution limits. Based on video resolution need to check whether the coordinates are in range|N|Y|

### Test Startup Requirement - Scale the Hdmi Input Video

The test begins by setting up the video analyzer, and the video should be played. 

### Emulator Requirement - Scale the Hdmi Input Video

Emulator will boot with the port informations coming from the configuration file.

### Control Plane Requirement - Scale the Hdmi Input Video

The handling of connecting and disconnecting source devices in the HdmiIn will be managed by the Control Plane.

## Select Zoom Mode

|Description|L2|L3|
|-----------|--|--|
|Verify that the function successfully updates the video zoom on the active HDMI input using the provided zoom mode|N|Y|

### Test Startup Requirement - Select Zoom Mode

The test begins by setting up the video analyzer, and the video should be played. 

### Emulator Requirement - Select Zoom Mode

Emulator will boot with the zoom modes in the configuration file.

### Control Plane Requirement - Select Zoom Mode

Changing the zoom modes by the Control Plane.

## Get Current Video Mode

|Description|L2|L3|
|-----------|--|--|
|Verify that the function successfully updates the current HDMI input video modes like Pixel resolution, frame rate and interlaced information of the active port|N|Y|

### Test Startup Requirement - Get Current Video Mode

The test begins by setting up the video analyzer, and the video should be played. 

### Emulator Requirement - Get Current Video Mode

Emulator will boot with the all video mode related information in the configuration file.

### Control Plane Requirement - Get Current Video Mode

None

## Callback for connection Status

|Description|L2|L3|
|-----------|--|--|
|Verify that the callback function properly notifies the application when a Hdmi Input port is connected or disconnected.|N|Y|
|Validate that the callback function updates the isPortConnected status correctly based on the connection state provided.|N|Y|
|Verify that the callback function properly updates the isPresented status in ::dsHdmiInStatus_t if the connected port is active and presents video after being connected.|N|Y|

### Test Startup Requirement - Callback for connection Status

Connection of the source device with the HdmiIn.

### Emulator Requirement - Callback for connection Status

Emulator will boot with the port information coming from the configuration file.

### Control Plane Requirement - Callback for connection Status

The handling of connecting and disconnecting source devices in the HdmiIn will be managed by the Control Plane.

## Callback for Signal Change

|Description|L2|L3|
|-----------|--|--|
|Verify that the callback function properly handles different signal statuses (e.g., NoSignal, UnstableSignal, NotSupportedSignal, StableSignal) and updates the application accordingly.|N|Y|
|Validate that the callback function updates the sigStatus parameter correctly based on the signal status provided.|N|Y|

### Test Startup Requirement - Callback for Signal Change

Connection of the source device with the HdmiIn.

### Emulator Requirement - Callback for Signal Change

Emulator will boot with the port informations coming from the configuration file.

### Control Plane Requirement - Callback for Signal Change

The handling of connecting and disconnecting source devices in the HdmiIn will be managed by the Control Plane.
Provide resolution changes or configurations changes on the connected device that affects the output signal.

## Callback for Status Change

|Description|L2|L3|
|-----------|--|--|
|Verify that the callback function properly notifies the application of the Hdmi Input status change event.|N|Y|
|Validate that the callback function updates the inputStatus parameter correctly based on the status change provided.|N|Y|
|Verify that the callback function properly triggers whenever the dsHdmiInStatus_t is updated|N|Y|

### Test Startup Requirement - Callback for Status Change

Connection of the source device with the HdmiIn.

### Emulator Requirement - Callback for Status Change

Emulator will boot with the port informations coming from the configuration file.

### Control Plane Requirement - Callback for Status Change

The handling of connecting and disconnecting source devices in the HdmiIn will be managed by the Control Plane.

## Callback for Video Mode Change

|Description|L2|L3|
|-----------|--|--|
|Verify that the callback function properly notifies the application whenever there is resolution change.|N|Y|

### Test Startup Requirement - Callback for Video Mode Change

Connection of the source device with the HdmiIn.

### Emulator Requirement - Callback for Video Mode Change

Emulator will boot with the video resolutions from the configuration file.

### Control Plane Requirement - Callback for Video Mode Change

Changing of the video resolution by control Plane.

## Callback for ALLM mode change 

|Description|L2|L3|
|-----------|--|--|
|Verify that the callback function properly notifies the application whenever there is resolution change.|N|Y|

### Test Startup Requirement - Callback for ALLM mode change

Connection of the source device with the HdmiIn.

### Emulator Requirement - Callback for ALLM mode change

Emulator will boot with the video resolutions from the configuration file.

### Control Plane Requirement - Callback for ALLM mode change

Changing of the video resolution by control Plane.

## Callback for AV Latency Change 

|Description|L2|L3|
|-----------|--|--|
|Verify that the function gets the current Audio and Video latency.|N|Y|

### Test Startup Requirement - Callback for AV Latency Change 

Connection of the source device with the HdmiIn.

### Emulator Requirement - Callback for AV Latency Change 

Emulator will boot with the AV latency information from the configuration file.

### Control Plane Requirement - Callback for AV Latency Change 

Control Plane changes the AV latency 

## Callback for AVI Content Type Change

|Description|L2|L3|
|-----------|--|--|
|Verify that the callback function properly notifies the application whenever there is a change in the AVI content type.|N|Y|

### Test Startup Requirement - Callback for AVI Content Type Change

Connection of the source device with the HdmiIn.

### Emulator Requirement - Callback for AVI Content Type Change

Emulator will boot with the AVI content type information.

### Control Plane Requirement - Callback for AVI Content Type Change

Changing AVI content type by control Plane.

## Check HDMI ARC Port

|Description|L2|L3|
|-----------|--|--|
|Verify whether given port is an HDMI ARC port or not.|Y|N|

### Test Startup Requirement - Check HDMI ARC Port

Connection of the source device with the HdmiIn.

### Emulator Requirement - Check HDMI ARC Port

Emulator will boot with the HDMI ARC information.

### Control Plane Requirement - Check HDMI ARC Port

Changing of the port with HDMI ARC by control Plane.

## Set and Get EDID Information 

|Description|L2|L3|
|-----------|--|--|
|Setting the EDID version for a given port|Y|Y|
|Get the EDID version for a given port and compare with the Set value|Y|Y|
|This test ensures that the module can accurately retrieve and interpret EDID information, providing essential data about the display's capabilities and characteristics.|N|Y|

### Test Startup Requirement - Set and Get EDID Information

Launch the test with the predefined configuration set of results.

### Emulator Requirement - Set and Get EDID Information

Emulator will boot with the EDID coming from the configuration file.

### Control Plane Requirement - Set and Get EDID Information

None

## Get HDMI `SPD` Info

|Description|L2|L3|
|-----------|--|--|
|Test to get the HDMI `SPD` Info.|N|Y|

### Test Startup Requirement - Get HDMI `SPD` Info

Connection of the source device with the HdmiIn.

### Emulator Requirement - Get HDMI `SPD` Info

Emulator will boot with the HDMI Serial Product Descriptor information from the configuration file.

### Control Plane Requirement - Get HDMI `SPD` Info

None

## Get Supported Game Feature List

|Description|L2|L3|
|-----------|--|--|
|The test aims to verify the function that gets all the supported game features.|Y|Y|

### Test Startup Requirement - Get Supported Game Feature List

Connection of the source device with the HdmiIn.

### Emulator Requirement - Get Supported Game Feature List

Emulator will boot with the game supported features in the configuration.

### Control Plane Requirement - Get Supported Game Feature List

None

## Get AV latency 

|Description|L2|L3|
|-----------|--|--|
|Test verifies to get the current AV latency when no source device connected.|Y|N|
|Test verifies to get the current AV latency connected with the source device.|N|Y|

### Test Startup Requirement - Get AV latency

Connection of the source device with the HdmiIn.

### Emulator Requirement - Get AV latency

Emulator will boot with the av latency information in configuration file.

### Control Plane Requirement - Get AV latency

None.

## Get ALLM Status 

|Description|L2|L3|
|-----------|--|--|
|The test to verify whether the ALLM is enabled or disabled by switching to video games. To see whether it is enabling ALLM and reducing the input lag.|N|Y|

### Test Startup Requirement - Get and Set ALLM Support

Connection of the source device with the HdmiIn with game playback.

### Emulator Requirement - Get and Set ALLM Support

Emulator will boot with the ALLM configuration details.

### Control Plane Requirement - Get and Set ALLM Support

None

## Get and Set EDID to ALLM Support 

|Description|L2|L3|
|-----------|--|--|
|Set the ALLM support to EDID Version 2.0|N|Y|
|Get the ALLM support to EDID Version 2.0|N|Y|

### Test Startup Requirement - Get and Set ALLM Support

Connection of the source device with the HdmiIn.

### Emulator Requirement - Get and Set ALLM Support

Emulator will boot with the EDID coming from the configuration file.

### Control Plane Requirement - Get and Set ALLM Support

None
