# Display Test Document

## Version History

| Date(DD/MM/YY) | Comment       | Version |
| -------------- | ------------- | ------- |
| 05/03/2024     | First Release | 1.0.0   |

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [References](#references)
- [Introduction](#introduction)
- [Module Description](#module-description)
- [Testing Scope](#test-scope)

## Acronyms, Terms and Abbreviations

- `HAL`       - Hardware Abstraction layer
- `SOC`       - System On a Chip
- `EDID`      - Extended Display Identification
- `API`       - Application programming interface
- `CPU`       - Central processing unit
- `RDK`       - Reference Design Kit
- `dsDisplay` - Device Settings Display

## References

- `EDID` Specifications [https://en.wikipedia.org/wiki/Extended_Display_Identification_Data](https://en.wikipedia.org/wiki/Extended_Display_Identification_Data)
- Python `EDID` decoder library is available here - [https://pypi.org/project/pyedid/](https://en.wikipedia.org/wiki/Extended_Display_Identification_Data)

## Introduction

This document provides an overview of the testing requirements for the dsDisplay module. It outlines the scope of testing, objectives, testing levels and approaches, specific test requirements, emulator requirements, control plane requirements and expected deliverables.

Interface of the test is available in this link - [https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsDisplay.h](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsDisplay.h)

## Module Description

High level overview:

- `dsDisplay` offers a range of APIs for retrieving information about the Display Device.
- Data is retrieved from the Display Device and HDMI. This data is passed to the caller.
- In order to retrieve HDMI information, an external device must be connected.

## Testing Scope

|#|Test Functionality|Test Description|
|-|------------------|----------------|
|1|[Get EDID Information](#get-edid-information)|Test validates the accuracy and functionality of the display device module's functions (dsGetEDID and dsGetEDIDBytes) in retrieving the Extended Display Identification Data (EDID) from connected display devices|
|2|[Get Aspect Ratio](#get-aspect-ratio)| Test provides the aspect ratio of the display device|
|3|[Callback Registration for Display Related Events](#callback-registration-for-display-related-events)|To verify the callback registration for display related events. The display events are Dislay connected event, Display disconnected event, Rx Sense ON event, Rx Sense OFF event, HDCP protocol version change event|
-----------

## Get EDID Information

|Description|L2|L3|Source|Sink|
|-----------|--|--|------|----|
|The Get EDID Information test aims to verify the functionality of the display device module's dsGetEDID and dsGetEDIDBytes functions, which are responsible for retrieving the Extended Display Identification Data (EDID) from connected display devices. This test ensures that the module can accurately retrieve and interpret EDID information, providing essential data about the display's capabilities and characteristics.|N|Y|Y|Y|
|For sink devices, validate the predefined the EDID value coming from the TV HDMI port1 EDID |Y|Y|Y|Y|

### Test Startup Requirement - Get EDID Information

Launch the test with the predefined configuration set of results.

### Emulator Requirement - Get EDID Information

Emulator will boot with the EDID coming from the configuration file.

|#|Description|
|-|-----------|
|1|EDID for a panel TV|

TODO: Generate a list of sample list for 5 to 6 different TV's.
Generate a list of TV's from the office for the different EDIDs and store the binaries of the test. It can use it as samples.

### Control Plane Requirement - Get EDID Information

None

## Get Aspect Ratio

|Description|L2|L3|Source|Sink|
|-----------|--|--|------|----|
|Test the aspect ratio returned by the dsGetDisplayAspectRatio() function for the specified display device handle.|N|Y|Y|N
|Adjust and test the aspect ratio to ensure it is providing the expected aspect ratio.|N|Y|Y|N|

### Test Startup Requirement - Get Aspect Ratio

Launch the test with the predefined configuration set of results.

### Emulator Requirement - Get Aspect Ratio

Emulator will boot with the Aspect ratio coming from the configuration file.

### Control Plane Requirement - Get Aspect Ratio

Maintains the configuration of various aspect ratios and provides them whenever a user is supposed to make a change.

## Callback Registration for Display Related Events

|Description|L2|L3|Source|Sink|
|-----------|--|--|------|----|
|Test the 'Display connected' event. Upon connecting the display device, the callback should trigger the event|N|Y|Y|Y|
|Test the 'Display disconnected' event. Upon disconnecting the display device, the callback should trigger the event|N|Y|Y|Y|
|Test the 'Rx Sense ON' event by verifying the presence of a signal from the receiving device; the callback should be triggered when the signal is detected|N|Y|N|Y|
|Test the 'Rx Sense OFF' event by verifying the absense of a signal from the receiving device; the callback should be triggered when the signal is detected|N|Y|N|Y|
|Test the 'HDCP protocol version change' event by verifying if there is a change in the HDCP protocol version used for content protection; the callback should be triggered upon detection of the protocol change.|N|Y|N|Y|


### Test Startup Requirement -Callback Registration for Display Related Events

Launch the test with the predefined set of configured HDCP 1.x and HDCP 2.x keys.

### Emulator Requirement - Callback Registration for Display Related Events

Emulator will boot with the HDCP keys coming from the configuration file.

### Control Plane Requirement - Callback Registration for Display Related Events

The control plane will generate events for HDMI connection and disconnection. It also supplies signals to the receiving devices to initiate the Rx Sense ON/Rx Sense OFF events.