# Device Settings Front Panel Display Test Document

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Introduction](#introduction)
- [Module Description](#module-description)
- [Testing Scope](#testing-scope)

## Acronyms, Terms and Abbreviations

- `HAL`     - Hardware Abstraction layer
- `SOC`     - System On a Chip
- `FP`       - Front Panel
- `FPD`     - Front Panel Display
- `ds`       - Device Settings.
- `LED`     - Light Emitting Devices
- `dsFPD` - Device Settings Front Panel Display

## Introduction

This document provides an overview of the testing requirements for the `dsFPD` module. It outlines the scope of testing, objectives, testing levels and approaches, specific test requirements, emulator requirements, control plane requirements, and expected deliverables.

The interface of the test is available here: [ds-fdp HAl Header](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsFPD.h)

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
|5|[FrontPanel Text  and Brightness Display Control](#frontpanel-text-and-brightness-display-control)|The test aims to set and verify the text display and its brightness on the 7-Segment `LED` Display supported on the platform|
|6|[FrontPanel Display Text Mode and Scroll control](#frontpanel-display-text-mode-and-scroll-control)|The test aims to verify the `FPD` Mode control (Text/Time) and scroll control)|
|7|[FrontPanel Clock display control](#frontpanel-clock-display-control)|The test aims to set and verify the time display, Clock Display and set the Timer format on the 7-Segment `LED` Display supported on the platform|
-----------

## Discrete `LED` Brightness Control

|Description|L2|L3|Control Plane|
|-----------|--|--|-------------|
|Verify the Discrete `LED`s Brightness using Set and Get functions.|Y|Y|Read the `LED` Brightness|

### Test Startup Requirement-Discrete `LED` Brightness Control

NA

### Emulator Requirement-Discrete `LED` Brightness Control

The emulator will boot with the `LED` configurations that should include

1. Number of discrete `LED`s, available
2. Max and Min value of Brightness.
3. Default brightness of each discrete `LED`

### Control Plane Requirement-Discrete `LED` Brightness Control

Read the brightness intensity of the `LED` when set to a different level and compare it with the previous intensity value using a `LED` detector device.

## Discrete `LED` blink control

|Description|L2|L3|Control Plane|
|-----------|--|--|-------------|
|Validate the blink functionality of discrete `LED` available on the platform |N|Y| Read the `LED` blink rate|

### Test Startup Requirement-Discrete `LED` blink control

NA

### Emulator Requirement-Discrete `LED` blink control

The emulator will boot with the `LED` configurations that should include

1. Number of discrete `LED`s, available

### Control Plane Requirement-Discrete `LED` blink control

Read the Blink interval from the `LED` detector device.

## Discrete `LED` color control

|Description|L2|L3|Control Plane|
|-----------|--|--|-------------|
|Validate the color functionality of discrete `LED` available by setting and getting different colors supported by the discrete `LED` |Y|Y| Read the `LED` Color|

### Test Startup Requirement-Discrete `LED` color control

NA

### Emulator Requirement-Discrete `LED` color control

The emulator will boot with the `LED` configurations that should include

1. Number of discrete `LED`s, available
2. Supported colors for each `LED`

### Control Plane Requirement-Discrete `LED` color control

The control panel should be able to read the color of the `LED` through the specialized devices that shall identify the `LED` color and provide the same information to the control panel.

## Discrete Power `LED` control

|Description|L2|L3|Control Plane|
|-----------|--|--|-------------|
|Validate the functionality of discrete Power `LED` available on the platform in different states by set and get `API`s. The `LED` functionality should be validated against the different supported states on the platform |Y|Y|NA|

### Test Startup Requirement-Discrete Power `LED` control

NA

### Emulator Requirement-Discrete Power `LED` control

The emulator will boot with the `LED` configurations that should include

1. Provide the configuration of Power `LED` states supported.

### Control Plane Requirement-Discrete Power `LED` control

Due to platform-specific requirements, it may not be possible to capture the `LED` behavior in each state.

## Frontpanel Text and Brightness Display Control

|Description|L2|L3|Control Plane|
|-----------|--|--|-------------|
|Set the `FPD` mode to "Text" mode and set the valid "Text" using dsSetFPText `API`. Validate the displayed "Text" |N|Y|Read the "Text"|
|Set the `FPD` mode to "Any" mode and set the valid "Text" using dsSetFPText `API`. Validate the displayed "Text" |N|Y|Read the "Text"|
|Set the `FPD` mode to "Text" mode and set the "Text" to display. Now set the brightness of the `FPD`  using the appropriate Set API and validate it Get API |Y|Y|Read the Brightness|

### Test Startup Requirement-Frontpanel Text and Brightness Display Control

NA

### Emulator Requirement-Frontpanel Text and Brightness Display Control

The emulator will boot with the configurations that should include

1. 7-seg `FPD` Text/Clock mode, Brightness, cycle rate, supported characters, Rows, columns, and Vertical/Horizontal scroll supported on the platform.

### Control Plane Requirement-Frontpanel Text and Brightness Display Control

The control Panel should be able to read the data from the tool that can recognize the text display and brightness level. This data should be validated to declare the test result.

## Frontpanel Display Text Mode and Scroll control

|Description|L2|L3|Control Plane|
|-----------|--|--|-------------|
|Set the `FPD` mode to "Text" mode, "Any" mode, and "clock" mode to validate the "Text" display. The test should fail to display the "Text" when "Clock" mode is set |Y|Y|Read the "Text"|
|Set the `FPD` mode to "Text" mode, set the "Text" scroll duration, and set the "Text" to display using dsSetFPText `API` |N|Y|Read the scroll rate|
|Set the `FPD` mode to "Any" mode, set the "Text" scroll duration, and set the "Text" to display using dsSetFPText `API` |N|Y|Read the scroll rate|

### Test Startup Requirement-Frontpanel Display Text Mode and Scroll control

NA

### Emulator Requirement-Frontpanel Display Text Mode and Scroll control

The emulator will boot with the configurations that should include

1. 7-seg `FPD` Text/Clock mode, Brightness, cyclerate, supported characters, Rows, columns, and Vertical/Horizontal scroll supported on the platform.

### Control Plane Requirement-Frontpanel Display Text Mode and Scroll control

The control Panel should be able to read the data from the tool that shall recognize the text display and validate the scroll activity. This data should be validated to declare the test result.

## Frontpanel Clock Display Control

|Description|L2|L3|Control Plane|
|-----------|--|--|-------------|
|Set the `FPD` Time Format using set `API` and validate the same with get `API` |Y|N|NA|
|Set the `FPD` Time with supported formats. |N|Y|Read the Time and Time Format|
|Enable the `FPD` Clock display and validate|N|Y|Read the Time and Time Format|
|Disable the `FPD` Clock display and validate |N|Y|validate that NO Time is displayed|

### Test Startup Requirement-Frontpanel Clock Display Control

NA

### Emulator Requirement-Frontpanel Clock Display Control

The emulator will boot with the configurations that should include

1. 7-seg `FPD` Text/Clock mode, Brightness, cycle rate, supported characters, Rows, columns, and Vertical/Horizontal scroll supported on the platform.

### Control Plane Requirement-Frontpanel Clock Display Control

The control Panel should be able to read the data from the tool that shall recognize the "Time" display and validate. This data should be read and validated to declare the test result.
