# Device Settings CompositeIn High Level Test Specification Document

## Acronyms, Terms and Abbreviations

- `HAL`   - Hardware Abstraction layer
- `API`   - Application programming interface
- `RDK`   - Reference Design Kit
- `dsComposite` - Device Settings Composite

## Introduction

This document provides an overview of the high level testing requirements for the `dsComposite` module. It outlines the scope of testing, objectives, testing levels and approaches, specific test requirements, emulator requirements, control plane requirements and expected deliverables.

- Interface of the test is available in this link -  [https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsCompositeIn.h](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsCompositeIn.h)
- Hal Specification in this link - [https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/docs/pages/ds-composite-in_halSpec.md](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/docs/pages/ds-composite-in_halSpec.md)

## Module Description

High level overview:

- `dsComposite` provides a variety of APIs for accessing information regarding the Composite Inputs on sink devices.
- It facilitates interaction with Composite Input ports, aiding in their configuration and utilization within the system. This information is then passed to the caller.
- For the sink devices, to retrieve the available Composite Input information, an external device must be connected.

## Testing Scope

|#|Test Functionality|Test Description|
|-|------------------|----------------|
|1|[Get Number of Inputs](#get-number-of-inputs)|The test aims to verify the availability of Composite Input ports by confirming the number present.|
|2|[Get the Input Status](#get-the-input-status)|The test is to verify the status of all Composite Input ports|
|3|[Set the Composite port](#set-the-composite-port)|The test is to set the Composite Input port for Presentation|
|4|[Scale the Composite Input Video](#scale-the-composite-input-video)|The test scales the COMPOSITE input video, ensuring that the width and height, determined by the x and y coordinates respectively, do not surpass the current resolution limits of the device.|
|5|[Callback for connection Status](#callback-for-connection-status)|The test aims to verify the Callback function used for notifying applications of the COMPOSITE In hot plug/unplug status.|
|6|[Callback for Signal Change](#callback-for-signal-change)|The test aims to verify the callback function used to inform applications about changes in the signal status of the Composite In.(NoSignal/UnstableSignal/NotSupportedSignal/StableSignal)|
|7|[Callback for Status Change](#callback-for-status-change)|The test validates the functionality of the callback function designed to notify applications of Composite Input status change events.(Port,IsPresented flag status)|
|8|[Callback for Video Mode Change](#callback-for-video-mode-change)|The test validates the functionality of the callback function designed to notify applications of Composite Input video mode change events.(Port,resolution status)|
-----------

## Get Number of Inputs

|Description|HAL APIs|L2|L3|Control plane requirements|
|-----------|--------|--|--|--------------------------|
|Ensure that the function returns the expected number of COMPOSITE input ports by comparing the input port values parsed from the configuration YAML file 'Panel_CompositeInput.yaml'. The value to be retrieved from the YAML is 'composite_input_configurations/number_of_ports'. |dsCompositeInGetNumberOfInputs|Y|N|N|

### Emulator Requirement - Get Number of Inputs

Emulator will boot with the port informations coming from the configuration file.

### Control Plane Requirement - Get Number of Inputs

None

## Get the Input Status

|Description|HAL APIs|L2|L3|Control plane requirements|
|-----------|--------|--|--|--------------------------|
|Verify the status of the Composite Input by ensuring it is in disable status.|dsCompositeInGetStatus|Y|N|N|
|Verify the status of the Composite Input by ensuring it is enabled, connected to the source, and that the composite input port is active.|dsCompositeInGetStatus|N|Y|Y|

### Test Startup Requirement - Get the Input Status

Connection of the source device with the CompositeIn.

### Emulator Requirement - Get the Input Status

Emulator will boot with the port informations coming from the configuration file.

### Control Plane Requirement - Get the Input Status

Connecting and disconnecting source devices in the CompositeIn will be handled by the Control Plane.

## Set the Composite port

|Description|HAL APIs|L2|L3|Control plane requirements|
|-----------|--------|--|--|--------------------------|
|Loop through the all composite ports, verify that the function successfully sets the specified COMPOSITE Input port when there is no connection of source device, and check the disable status of the port information using "Get status".|dsCompositeInSelectPort, dsCompositeInGetStatus|Y|N|N|
|Loop through the all composite ports, verify that the function successfully sets the specified COMPOSITE Input port as active for presentation, and check the port information using "Get status".|dsCompositeInSelectPort, dsCompositeInGetStatus|N|Y|Y|

### Test Startup Requirement - Set the Composite port

Connection of the source device with the CompositeIn.

### Emulator Requirement - Set the Composite port

Emulator will boot with the port informations coming from the configuration file.

### Control Plane Requirement - Set the Composite port

- Connecting and disconnecting source devices in the CompositeIn will be handled by the Control Plane.

## Scale the Composite Input Video

|Description|HAL APIs|L2|L3|Control plane requirements|
|-----------|--------|--|--|--------------------------|
|Verify that the function successfully scales the COMPOSITE input video when valid coordinates and dimensions are provided within the current resolution limits. Based on video resolution need to check whether the coordinates are in range|dsCompositeInSelectPort(), dsCompositeInScaleVideo()|N|Y|Y|

### Test Startup Requirement - Scale the Composite Input Video

The test begins by setting up the video analyzer, and the video should be played. 

### Emulator Requirement - Scale the Composite Input Video

Emulator will boot with the port informations coming from the configuration file.

### Control Plane Requirement - Scale the Composite Input Video

- Connecting and disconnecting source devices in the CompositeIn will be handled by the Control Plane.
- The Control Plane handles the changing of various resolutions.
- The Control Plane checks and validates the coordinates and dimensions by comparing the values from the video analyzer.

## Callback for connection Status

|Description|HAL APIs|L2|L3|Control plane requirements|
|-----------|--------|--|--|--------------------------|
|Verify that the callback function properly updates the connection/disconnection status flag and notifies the application when a COMPOSITE Input port is connected or disconnected.|dsCompositeInRegisterConnectCB|N|Y|Y|
|Verify that the callback function properly updates the isPresented status in `dsCompositeInStatus_t`, if the connected port is active and presents video after being connected.|dsCompositeInRegisterConnectCB|N|Y|Y|

### Test Startup Requirement - Callback for connection Status

Connection of the source device with the CompositeIn.

### Emulator Requirement - Callback for connection Status

Emulator will boot with the port information coming from the configuration file.

### Control Plane Requirement - Callback for connection Status

Connecting and disconnecting source devices in the CompositeIn will be handled by the Control Plane.

## Callback for Signal Change

|Description|HAL APIs|L2|L3|Control plane requirements|
|-----------|--------|--|--|--------------------------|
|Verify that the callback function properly notifies the application whenever there is a change in the signal statuses (e.g., NoSignal, UnstableSignal, NotSupportedSignal, StableSignal) for the composite Input port.|dsCompositeInRegisterSignalChangeCB|N|Y|Y|

### Test Startup Requirement - Callback for Signal Change

Connection of the source device with the CompositeIn.

### Emulator Requirement - Callback for Signal Change

Emulator will boot with the port informations coming from the configuration file.

### Control Plane Requirement - Callback for Signal Change

- Connecting and disconnecting source devices in the CompositeIn will be handled by the Control Plane.
- Provide resolution changes or configurations changes on the connected device that affects the output signal.

## Callback for Status Change

|Description|HAL APIs|L2|L3|Control plane requirements|
|-----------|--------|--|--|--------------------------|
|Verify that the callback function properly triggers whenever the dsCompositeInStatus_t is updated and notifies the application of the Composite Input Status Change event.|dsCompositeInRegisterStatusChangeCB|N|Y|Y|

### Test Startup Requirement - Callback for Status Change

Connection of the source device with the CompositeIn.

### Emulator Requirement - Callback for Status Change

Emulator will boot with the port informations coming from the configuration file.

### Control Plane Requirement - Callback for Status Change

Connecting and disconnecting source devices in the CompositeIn will be handled by the Control Plane.


## Callback for video mode change

|Description|HAL APIs|L2|L3|Control plane requirements|
|-----------|--------|--|--|--------------------------|
|Verify that the callback function properly updates the video mode changes and notifies the application when a COMPOSITE Input video mode changes after the composite signal is stable |dsCompositeInRegisterVideoModeUpdateCB|N|Y|Y|

### Test Startup Requirement - Callback for video mode change

Launching of the source device with the CompositeIn connected.

### Emulator Requirement - Callback for video mode change

Emulator will boot with the port information and its video mode change information received from the configuration file.

### Control Plane Requirement - Callback for video mode change

- Connecting and disconnecting source devices in the CompositeIn will be handled by the Control Plane.
- Provide resolution changes or configurations changes on the connected device that changes the video mode info.

