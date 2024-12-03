# Device Settings Front Panel Display High Level Test Specification Documentation

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Introduction](#introduction)
- [Module Description](#module-description)
- [Testing Scope](#testing-scope)

## Acronyms, Terms and Abbreviations

- `HAL`     - Hardware Abstraction layer
- `SOC`     - System On a Chip
- `FP`      - Front Panel
- `FPD`     - Front Panel Display
- `ds`      - Device Settings.
- `LED`     - Light Emitting Devices
- `dsFPD`   - Device Settings Front Panel Display

## Introduction

This document provides an overview of the High Level Test Specification requirements for the `dsFPD` module. It outlines the scope of testing, objectives, testing levels and approaches, specific test requirements, emulator requirements, control plane requirements, and expected deliverables.

The interface of the test is available here: [ds-fdp HAl Header](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsFPD.h)

`Note: There will be no test case implemented to verify the 7-segment front panel display LEDs.`

## Module Description

High-level overview:

- `dsFPD` provides a set of APIs to control the `FP`discrete `LED`s and 7-segment `LED`s existing on a platform.
- It facilitates the communication to `FP` `LED`s, aiding in their configuration and utilization within the system. The `LED`s is controlled by the caller based on the platform requirements.
Interface specification is available here: [ds-fdp HAl Spec](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/docs/pages/ds-front-panel-display_halSpec.md)

## Testing Scope

|#|Test Functionality|Test Description|
|-|------------------|----------------|
|1|[Discrete `LED` Brightness Control](#discrete-led-brightness-control)|The test aims to set and verify the Brightness of the discrete `LED`s supported on the platform.|
|2|[Discrete `LED` Blink Control](#discrete-led-blink-control)|The test aims to set and verify the blink activity of the discrete `LED`s supported on the platform|
|3|[Discrete `LED` Color Control](#discrete-led-color-control)|The test aims to set and verify the color control activities of the discrete `LED`s supported on the platform|
|4|[Discrete Power `LED` Control](#discrete-power-led-control)|The test aims to set and verify the discrete Power `LED` supported on the platform|

## Discrete `LED` Brightness Control

|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|-----------|--------|--|--|------|----|--------------------------|
|Iterate over supported `FPD` indicators. For each supported indicator: 1. Check the current state of the `FP`. 2. If it's OFF, set it to ON. 3. Set the brightness of the discrete `LED` within the specified range (min-max) and verify using the get function. Note: 1. For supported `FPD` indicators check profile file for Sink `Sink_FPD.yaml`(path:`dsFPD/SupportedFPDIndicators/[Indicator number]/Indicator_type`) and for Source `Source_FPD.yaml`(path:`dsFPD/SupportedFPDIndicators/[Indicator number]/Indicator_type`) 2. for Brightness range check  Sink `Sink_FPD.yaml`(path:`dsFPD/SupportedFPDIndicators/[Indicator number]/MAX_BRIGHTNESS and dsFPD/SupportedFPDIndicators/[Indicator number]/MIN_BRIGHTNESS`) and for Source `Source_FPD.yaml`(path:`dsFPD/SupportedFPDIndicators/[Indicator number]/MAX_BRIGHTNESS and dsFPD/SupportedFPDIndicators/[Indicator number]/MIN_BRIGHTNESS`)|dsGetFPState(), dsSetFPState(), dsSetFPBrightness(), dsGetFPBrightness()|`Y`|`NA`|`Y`|`Y`|`NA`|
|Iterate over supported `FPD` indicators. For each supported indicator: 1. Check the current state of the `FP`. 2. If it's ON, set it to OFF. 3. Set the brightness of the discrete `LED` and check it returns `dsERR_OPERATION_NOT_SUPPORTED`.Note: For supported `FPD` indicators check profile file for Sink `Sink_FPD.yaml`(path:`dsFPD/SupportedFPDIndicators/[Indicator number]/Indicator_type`) and for Source `Source_FPD.yaml`(path:`dsFPD/SupportedFPDIndicators/[Indicator number]/Indicator_type`)|dsGetFPState(), dsSetFPState(), dsSetFPBrightness()|`Y`|`NA`|`Y`|`Y`|`NA`|
|Iterate over supported `FPD` indicators. For each supported indicator: 1.Check the current state of the `FP`.2. If it's OFF, set it to ON. 3. Set the brightness of the discrete `LED` and verify brightness intensity with help of control plane.Note: 1. For supported `FPD` indicators check profile file for Sink `Sink_FPD.yaml`(path:`dsFPD/SupportedFPDIndicators/[Indicator number]/Indicator_type`) and for Source `Source_FPD.yaml`(path:`dsFPD/SupportedFPDIndicators/[Indicator number]/Indicator_type`) 2. for Brightness range check  Sink `Sink_FPD.yaml`(path:`dsFPD/SupportedFPDIndicators/[Indicator number]/MAX_BRIGHTNESS and dsFPD/SupportedFPDIndicators/[Indicator number]/MIN_BRIGHTNESS`) and for Source `Source_FPD.yaml`(path:`dsFPD/SupportedFPDIndicators/[Indicator number]/MAX_BRIGHTNESS and dsFPD/SupportedFPDIndicators/[Indicator number]/MIN_BRIGHTNESS`)|dsGetFPState(), dsSetFPState(), dsSetFPBrightness()|`NA`|`Y`|`Y`|`Y`|`Y`|

### Test Startup Requirement-Discrete `LED` Brightness Control

`NA`

### Emulator Requirement-Discrete `LED` Brightness Control

The emulator will boot with the `LED` configurations that should include

1. Number of discrete `LED`s, available
2. Max and Min value of Brightness.
3. Default brightness of each discrete `LED`

### Control Plane Requirement-Discrete `LED` Brightness Control

Read the brightness intensity of the `LED` when set to a different level and compare it with the previous intensity value using a `LED` detector device.

## Discrete `LED` blink control

|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|-----------|--------|--|--|------|----|--------------------------|
|Iterate over supported `FPD` indicators. For each supported indicator: 1. Check the current state of the `FP`. 2. If it's OFF, set it to ON. 3. set the blink functionality of discrete `LED` and verify Blink interval with help of control plane.Note: For supported `FPD` indicators check profile file for Sink `Sink_FPD.yaml`(path:`dsFPD/SupportedFPDIndicators/[Indicator number]/Indicator_type`) and for Source `Source_FPD.yaml`(path:`dsFPD/SupportedFPDIndicators/[Indicator number]/Indicator_type`)|dsGetFPState(), dsSetFPState(), dsSetFPBlink()|`NA`|`Y`|`Y`|`Y`|`Y`|
|Iterate over supported `FPD` indicators. For each supported indicator: 1. Check the current state of the `FP`. 2. If it's ON, set it to OFF. 3. set the blink functionality of discrete `LED` and check it returns `dsERR_OPERATION_NOT_SUPPORTED`.Note: For supported `FPD` indicators check profile file for Sink `Sink_FPD.yaml`(path:`dsFPD/SupportedFPDIndicators/[Indicator number]/Indicator_type`) and for Source `Source_FPD.yaml`(path:`dsFPD/SupportedFPDIndicators/[Indicator number]/Indicator_type`)|dsGetFPState(), dsSetFPState(), dsSetFPBlink()|`Y`|`NA`|`Y`|`Y`|`NA`|

### Test Startup Requirement-Discrete `LED` blink control

`NA`

### Emulator Requirement-Discrete `LED` blink control

The emulator will boot with the `LED` configurations that should include

1. Number of discrete `LED`s, available

### Control Plane Requirement-Discrete `LED` blink control

Read the Blink interval from the `LED` detector device.

## Discrete `LED` color control

|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|-----------|--------|--|--|------|----|--------------------------|
|Iterate over supported `FPD` indicators. For each supported indicator: 1. Check the current state of the `FP`. 2. If it's OFF, set it to ON. 3. Check the indicator supports multi-colored 4. set the color functionality of discrete `LED` available by setting and getting different colors supported by the discrete `LED` Note: 1. For supported `FPD` indicators check profile file for Sink `Sink_FPD.yaml`(path:`dsFPD/SupportedFPDIndicators/[Indicator number]/Indicator_type`) and for Source `Source_FPD.yaml`(path:`dsFPD/SupportedFPDIndicators/[Indicator number]/Indicator_type`) 2. for indicator color support check  Sink `Sink_FPD.yaml`(path:`dsFPD/SupportedFPDIndicators/[Indicator number]/DEFAULT_COLOR_MODE`) and for Source `Source_FPD.yaml`(path:`dsFPD/SupportedFPDIndicators/[Indicator number]/DEFAULT_COLOR_MODE`)|dsGetFPState(), dsSetFPState(), dsSetFPColor(), dsGetFPColor()|`Y`|`NA`|`Y`|`Y`|`NA`|
|Iterate over supported `FPD` indicators. For each supported indicator: 1. Check the current state of the `FP`. 2. If it's ON, set it to OFF. 3. set the color functionality of discrete `LED` and check it returns `dsERR_OPERATION_NOT_SUPPORTED`.Note: For supported `FPD` indicators check profile file for Sink `Sink_FPD.yaml`(path:`dsFPD/SupportedFPDIndicators/[Indicator number]/Indicator_type`) and for Source `Source_FPD.yaml`(path:`dsFPD/SupportedFPDIndicators/[Indicator number]/Indicator_type`)|dsGetFPState(), dsSetFPState(), dsSetFPColor()|`Y`|`NA`|`Y`|`Y`|`NA`|
|Iterate over supported `FPD` indicators. For each supported indicator: 1. Check the current state of the `FP`. 2. If it's ON, set it to OFF. 3. Check the indicator supports `single-colored` 4. set the color functionality of discrete `LED` and check it returns `dsERR_OPERATION_NOT_SUPPORTED`.Note: For supported `FPD` indicators check profile file for Sink `Sink_FPD.yaml`(path:`dsFPD/SupportedFPDIndicators/[Indicator number]/Indicator_type`) and for Source `Source_FPD.yaml`(path:`dsFPD/SupportedFPDIndicators/[Indicator number]/Indicator_type`)|dsGetFPState(), dsSetFPState(), dsSetFPColor()|`Y`|`NA`|`Y`|`Y`|`NA`|
|Iterate over supported `FPD` indicators. For each supported indicator: 1. Check the current state of the `FP`. 2. If it's OFF, set it to ON. 3. Check the indicator supports multi-colored 4. set the color functionality of discrete `LED` available by setting and verify Blink interval with help of control plane. Note: 1. For supported `FPD` indicators check profile file for Sink `Sink_FPD.yaml`(path:`dsFPD/SupportedFPDIndicators/[Indicator number]/Indicator_type`) and for Source `Source_FPD.yaml`(path:`dsFPD/SupportedFPDIndicators/[Indicator number]/Indicator_type`) 2. for indicator color support check  Sink `Sink_FPD.yaml`(path:`dsFPD/SupportedFPDIndicators/[Indicator number]/DEFAULT_COLOR_MODE`) and for Source `Source_FPD.yaml`(path:`dsFPD/SupportedFPDIndicators/[Indicator number]/DEFAULT_COLOR_MODE`)|dsGetFPState(), dsSetFPState(), dsSetFPColor()|`NA`|`Y`|`Y`|`Y`|`Y`|

### Test Startup Requirement-Discrete `LED` color control

`NA`

### Emulator Requirement-Discrete `LED` color control

The emulator will boot with the `LED` configurations that should include

1. Number of discrete `LED`s, available
2. Supported colors for each `LED`

### Control Plane Requirement-Discrete `LED` color control

The control panel should be able to read the color of the `LED` through the specialized devices that shall identify the `LED` color and provide the same information to the control panel.

## Discrete Power `LED` control

|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|-----------|--------|--|--|------|----|--------------------------|
|Verify the `LED` state transitions 1.Loop through all supported `LED` states. 2. For each state, set the `LED` to that state using dsFPSetLEDState(). 3. Verify the state using dsFPGetLEDState(). 4. Ensure each state transition is valid.Note: 1.For supported `LED` states check profile file for Sink `Sink_FPD.yaml`(path:`dsFPD/SupportedFPDIndicators/[Indicator number]/Indicator_type`) and for Source `Source_FPD.yaml`(path:`dsFPD/SupportedFPDIndicators/[Indicator number]/Indicator_type`)|dsFPGetSupportedLEDStates(), dsFPSetLEDState(), dsFPGetLEDState()|`Y`|`NA`|`Y`|`Y`|`NA`|
|Verify the `LED` state transitions 1.Loop through all supported `LED` states. 2. For each state, set the `LED` to that state using dsFPSetLEDState(). 3. Verify the state with control plane. 4. Ensure each state transition is valid.Note: For supported `LED` states check profile file for Sink `Sink_FPD.yaml`(path:`dsFPD/SupportedFPDIndicators/[Indicator number]/Indicator_type`) and for Source `Source_FPD.yaml`(path:`dsFPD/SupportedFPDIndicators/[Indicator number]/Indicator_type`)|dsFPGetSupportedLEDStates(), dsFPSetLEDState()|`NA`|`Y`|`Y`|`Y`|`Y`|

### Test Startup Requirement-Discrete Power `LED` control

NA

### Emulator Requirement-Discrete Power `LED` control

The emulator will boot with the `LED` configurations that should include

1. Provide the configuration of Power `LED` states supported.

### Control Plane Requirement-Discrete Power `LED` control

Due to platform-specific requirements, it may not be possible to capture the `LED` behavior in each state.
