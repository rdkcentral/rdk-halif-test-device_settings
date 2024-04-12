# CompositeIn Test Document

## Version History

| Date(DD/MM/YY) | Comment       | Version |
| -------------- | ------------- | ------- |
| 18/03/2024     | First Release | 1.0.0   |

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
- `dsComposite` - Device Settings Composite

## Introduction

This document provides an overview of the testing requirements for the `dsComposite` module. It outlines the scope of testing, objectives, testing levels and approaches, specific test requirements, emulator requirements, control plane requirements and expected deliverables.

Interface of the test is available in this link -  [https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsCompositeIn.h](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsCompositeIn.h)

## Module Description

High level overview:

- `dsComposite` provides a variety of APIs for accessing information regarding the Composite Inputs on sink devices.
- It facilitates interaction with Composite Input ports, aiding in their configuration and utilization within the system. This information is then passed to the caller.
- For the sink devices, to retrieve the available Composite Input information, an external device must be connected.

## Testing Scope

|#|Test Functionality|Test Description|
|-|------------------|----------------|
|1|[Get Number of Inputs](#get_number_of_inputs)|The test aims to verify the availability of Composite Input ports by confirming the number present.|
|2|[Get the Input Status](#get_the_input_status)|The test is to verify the status of all Composite Input Status|
|3|[Set the Composite port](#set_the_composite_port)|The test is to set the Composite Input port for Presentation|
|4|[Scale the Composite Input Video](#scale_the_composite_input_video)|The test scales the COMPOSITE input video, ensuring that the width and height, determined by the x and y coordinates respectively, do not surpass the current resolution limits of the device.|
|5|[Callback for connection Status](#callback_for_connection_status)|The test aims to verify the Callback function used for notifying applications of the COMPOSITE In hot plug status.|
|6|[Callback for Signal Change](#callback_for_signal_change)|The test aims to verify the callback function used to inform applications about changes in the signal status of the Composite In.(NoSignal/UnstableSignal/NotSupportedSignal/StableSignal)|
|7|[Callback for Status Change](#callback_for_status_change)|The test validates the functionality of the callback function designed to notify applications of Composite Input status change events.(Port,IsPresented flag status)|
-----------

## Get Number of Inputs

|Description|L2|L3|
|-----------|--|--|
|Verify that the function returns the expected COMPOSITE Input ports.|Y|N|

### Test Startup Requirement - Get Number of Inputs

The test begins with the configured composite input port details.

### Emulator Requirement - Get Number of Inputs

Emulator will boot with the port informations coming from the configuration file.

### Control Plane Requirement - Get Number of Inputs

None

## Get the Input Status

|Description|L2|L3|
|-----------|--|--|
|Verify the status of the Composite Input by ensuring it is in disable status.|Y|N|
|Verify the status of the Composite Input by ensuring it is enabled, connected to the source, and that the composite input port is active.|N|Y|

### Test Startup Requirement - Get the Input Status

Connection of the source device with the CompositeIn.

### Emulator Requirement - Get the Input Status

Emulator will boot with the port informations coming from the configuration file.

### Control Plane Requirement - Get the Input Status

The handling of connecting and disconnecting source devices in the CompositeIn will be managed by the Control Plane.

## Set the Composite port

|Description|L2|L3|
|-----------|--|--|
|verify that the function successfully sets the specified COMPOSITE Input port as active for presentation and check the port information using "Get status".|Y|Y|
|Evaluate the function's response when called with a port ID that is already selected as active, ensuring it does not introduce any unintended changes.|N|Y|

### Test Startup Requirement - Set the Composite port

The test begins with the configured composite input port numbers.

### Emulator Requirement - Set the Composite port

Emulator will boot with the port informations coming from the configuration file.

### Control Plane Requirement - Set the Composite port

The Control Plane must monitor the external device (Video analyzer) to detect any video glitches.

## Scale the Composite Input Video

|Description|L2|L3|
|-----------|--|--|
|Verify that the function successfully scales the COMPOSITE input video when valid coordinates and dimensions are provided within the current resolution limits. Based on video resolution need to check whether the coordinates are in range|N|Y|

### Test Startup Requirement - Scale the Composite Input Video

The test begins by setting up the video analyzer, and the video should be played. 

### Emulator Requirement - Scale the Composite Input Video

Emulator will boot with the port informations coming from the configuration file.

### Control Plane Requirement - Scale the Composite Input Video

The handling of connecting and disconnecting source devices in the CompositeIn will be managed by the Control Plane.

## Callback for connection Status

|Description|L2|L3|
|-----------|--|--|
|Verify that the callback function properly notifies the application when a COMPOSITE Input port is connected or disconnected.|N|Y|
|Validate that the callback function updates the isPortConnected status correctly based on the connection state provided.|N|Y|
|Verify that the callback function properly updates the isPresented status in ::dsCompositeInStatus_t if the connected port is active and presents video after being connected.|N|Y|

### Test Startup Requirement - Callback for connection Status

Connection of the source device with the CompositeIn.

### Emulator Requirement - Callback for connection Status

Emulator will boot with the port information coming from the configuration file.

### Control Plane Requirement - Callback for connection Status

The handling of connecting and disconnecting source devices in the CompositeIn will be managed by the Control Plane.

## Callback for Signal Change

|Description|L2|L3|
|-----------|--|--|
|Verify that the callback function properly handles different signal statuses (e.g., NoSignal, UnstableSignal, NotSupportedSignal, StableSignal) and updates the application accordingly.|N|Y|
|Validate that the callback function updates the sigStatus parameter correctly based on the signal status provided.|N|Y|

### Test Startup Requirement - Callback for Signal Change

Connection of the source device with the CompositeIn.

### Emulator Requirement - Callback for Signal Change

Emulator will boot with the port informations coming from the configuration file.

### Control Plane Requirement - Callback for Signal Change

The handling of connecting and disconnecting source devices in the CompositeIn will be managed by the Control Plane.
Provide resolution changes or configurations changes on the connected device that affects the output signal.

## Callback for Status Change

|Description|L2|L3|
|-----------|--|--|
|Verify that the callback function properly notifies the application of the Composite Input status change event.|N|Y|
|Validate that the callback function updates the inputStatus parameter correctly based on the status change provided.|N|Y|
|Verify that the callback function properly triggers whenever the dsCompositeInStatus_t is updated|N|Y|

### Test Startup Requirement - Callback for Status Change

Connection of the source device with the CompositeIn.

### Emulator Requirement - Callback for Status Change

Emulator will boot with the port informations coming from the configuration file.

### Control Plane Requirement - Callback for Status Change

The handling of connecting and disconnecting source devices in the CompositeIn will be managed by the Control Plane.
