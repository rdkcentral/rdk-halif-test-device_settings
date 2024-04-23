# Device Settings Front Panel Display Test Document

## Version History

| Date(DD/MM/YY) | Comment       | Version |
| -------------- | ------------- | ------- |
| 20/03/2024     | First Release | 1.0.0   |

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
- `LED`     - Light Emiting Devices
- `dsFPD` - Device Settings Front Panel Display

## Introduction

This document provides an overview of the testing requirements for the `dsFPD` module. It outlines the scope of testing, objectives, testing levels and approaches, specific test requirements, emulator requirements, control plane requirements and expected deliverables.

Interface of the test is available in this link -  [https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsFPD.h](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsFPD.h)

## Module Description

High level overview:

- `dsFPD` provides a set of APIs to control the `FP`discrete `LED`s and 7-segment `LED`s existing on a platform.
- It facilitates the communication to `FP` `LED`s, aiding in their configuration and utilization within the system. The `LED`s is controlled by the caller based on the platform requirements. 

## Testing Scope

|#|Test Functionality|Test Description|
|-|------------------|----------------|
|1|[Discrete LED Brightness Control](#discrete_led_brightness_control)|The test aims to set and verify the Brightness of the discrete `LED`s supported on the platform.|
|2|[Discrete `LED` Blink Control](#discrete_led_blink_control)|The test aims to set and verify the blink activity of the discrete `LED`s supported on the platform|
|3|[Discrete `LED` Color Control](#discrete_led_color_control)|The test aims to set and verify the color control activities of the discrete `LED`s supported on the platform|
|4|[Discrete Power `LED` Control](#discrete_power_led_control)|The test aims to set and verify the discrete Power `LED` supported on the platform|
|5|[`FPD` Text Display Control](#fpd_text_display_control)|The test aims to set and verify the text display and its brightness on the 7-Segment `LED` Display supported on the platform|
|6|[`FPD` Text Mode and Scroll control](#fpd_text_mode_and_scroll_control)|The test aims to verify the `FPD` Mode control (Text/Time) and scroll control)|
|7|[`FPD` Clock/Time display control ](#fpd_clock_display_control)|The test aims to set and verify the time display, Clock Display and set the Timer format on the 7-Segment `LED` Display supported on the platform|
-----------

## Discrete `LED` Brightness Control

|Description|L2|L3|Control Plane|
|-----------|--|--|-------------|
|Verify the Discrete `LED`s Brightness using Set and Get functions.|Y|Y|Read the `LED` Brightness

### Test Startup Requirement 

NA

### Emulator Requirement

Emulator will boot with the `LED` configurations that should include 
1. Number of discrete `LED`s, available 
2. Max and Min value of Brightness.
3. Default brightness of each discrete `LED`

### Control Plane Requirement 
Read the brightness intensity of the `LED` when set to a different level and compare with the previous intensity value using a `LED` detector device.

## Discrete `LED` blink control

|Description|L2|L3|Control Plane|
|-----------|--|--|-------------|
|Validate the blink functionality of discrete `LED` available on the platform |N|Y| Read the `LED` blink rate

### Test Startup Requirement

NA

### Emulator Requirement

Emulator will boot with the `LED` configurations that should include
1. Number of discrete `LED`s, available


### Control Plane Requirement

Read the Blink interval from the `LED` detector device.

## Discrete `LED` color control

|Description|L2|L3|Control Plane|
|-----------|--|--|-------------|
|Validate the color functionality of discrete `LED` available by setting and getting different colours supported by the discrete `LED` |Y|Y| Read the `LED` Color

### Test Startup Requirement 

NA

### Emulator Requirement

Emulator will boot with the `LED` configurations that should include
1. Number of discrete `LED`s, available
2. Supported colors for each `LED`


### Control Plane Requirement 

The control panel should able to read the color of the `LED` through the specialised devices that shall identify the `LED` color and shall provide the same information to the control panel.

## Discrete Power `LED` control

|Description|L2|L3|Control Plane|
|-----------|--|--|-------------|
|Validate the functionality of discrete Power `LED` available on the platform in different states by set and get `API`s. The `LED` functionality should be validated agains the different supported states on the platform |Y|Y|NA

### Test Startup Requirement 

NA

### Emulator Requirement

Emulator will boot with the `LED` configurations that should include
1. Provide the configuration of Power `LED` states supported.

### Control Plane Requirement 

Due to platform specific requirement, it may not be possible to capture the `LED` behaviour is each state.

## Frontpanel Display Text Display and Brightness Control

|Description|L2|L3|Control Plane|
|-----------|--|--|-------------|
|Set the `FPD` mode to "Text" mode and set the valid "Text" using dsSetFPText `API`. Validate the displayed "Text" |N|Y|Read the "Text"
|Set the `FPD` mode to "Any" mode and set the valid "Text" using dsSetFPText `API`. Validate the displayed "Text" |N|Y|Read the "Text"
|Set the `FPD` mode to "Text" mode and set the "Text" to display. Now set the brightness of the `FPD`  using appropriate Set API and validate it Get API |Y|Y|Read the Brightness

### Test Startup Requirement 

NA

### Emulator Requirement 
Emulator will boot with the configurations that should include
1. 7-seg `FPD` Text/Clock mode, Brightness, cyclerate, supported characters, Rows, columns, and Vertical/Horizontal scroll supported on the platform.


### Control Plane Requirement 

Control Panel should able read the data from the tool that shall recognize the text display and brightness level. This data should be validated to declare the test result.

## Frontpanel Display Text Mode and Scroll control

|Description|L2|L3|Control Plane|
|-----------|--|--|-------------|
|Set the `FPD` mode to "Text" mode, "Any" mode and "clock" mode to validate the "Text" display. The test should fail to display the "Text" when "Clock" mode is set |Y|Y|Read the "Text"
|Set the `FPD` mode to "Text" mode, set the "Text" scroll duration and set the "Text" to display using dsSetFPText `API` |N|Y|Read the scroll rate
|Set the `FPD` mode to "Any" mode, set the "Text" scroll duration and set the "Text" to display using dsSetFPText `API` |N|Y|Read the scroll rate

### Test Startup Requirement 

NA

### Emulator Requirement 

Emulator will boot with the configurations that should include
1. 7-seg `FPD` Text/Clock mode, Brighness, cyclerate, supported characters, Rows, columns, and Vertical/Horizontal scroll supported on the platform.

### Control Plane Requirement 

Control Panel should able read the data from the tool that shall recognize the text display and validate the scroll activity. This data should be validated to declare the test result.

## Frontpanel Display Clock/Time Control

|Description|L2|L3|Control Plane|
|-----------|--|--|-------------|
|Set the `FPD` Time Format using set `API` and validate the same with get `API` |Y|N|NA
|Set the `FPD` Time with supported formats. |N|Y|Read the Time and Time Format
|Enable the `FPD` Clock display and validate|N|Y|Read the Time and Time Format
|Disable the `FPD` Clock display and validate |N|Y|validate that NO Time is displayed

### Test Startup Requirement 

NA

### Emulator Requirement 

Emulator will boot with the configurations that should include
1. 7-seg `FPD` Text/Clock mode, Brighness, cyclerate, supported characters, Rows, columns, and Vertical/Horizontal scroll supported on the platform.

### Control Plane Requirement 

Control Panel should able read the data from the tool that shall recognize the "Time" display and validate. This data should be read and validated to declare the test result.
