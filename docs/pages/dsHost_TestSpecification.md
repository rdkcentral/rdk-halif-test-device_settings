# HOST Test Document

## Version History

| Date(DD/MM/YY) | Comment       | Version |
| -------------- | ------------- | ------- |
| 01/03/2024     | First Release | 1.0.0   |

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [References](#references)
- [Introduction](#introduction)
- [Module Description](#module-description)
- [Testing Scope](#testing-scope)

## Acronyms, Terms and Abbreviations

- `SoC`    - System On a Chip
- `EDID`   - Extended Display Identification
- `API`    - Application programming interface
- `CPU`    - Central processing unit
- `dsHost` - Device Settings Host
- `HDMI`   - High-Definition Multimedia Interface

## References

- `EDID` specifications - [https://en.wikipedia.org/wiki/Extended_Display_Identification_Data](https://en.wikipedia.org/wiki/Extended_Display_Identification_Data)
- Python `EDID` decoder library is available here - [https://pypi.org/project/pyedid/](https://pypi.org/project/pyedid/)

## Introduction

This document provides an overview of the testing requirements for the `dsHost` module.
It outlines the scope of testing, objectives, testing levels and approaches, specific test requirements, and expected deliverables.

Interface of the test is available in this link - [https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsHost.h](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsHost.h)

## Module Description

High level overview:

- `dsHost` offers a range of `API`s for retrieving information about the platform.
- Data is retrieved from the `SoC` and `HDMI`. This data is passed to the caller.
- In order to retrieve `HDMI` information, an external device must be connected.

## Testing Scope

|#|Testing Scope|Description|
|-|------------------|----------------|
|1|[Retrieve CPU Temperature](#retrieve-cpu-temperature)|Test if the module correctly retrieves the `CPU` temperature.|
|2|[Obtain SOC ID](#obtain-soc-id)|Test if the module successfully obtains the 8-byte `SoC` ID programmed to the CHIP One Time Programmable area.|
|3|[Fetch Host EDID](#fetch-host-edid)|Test if the module fetches the host `EDID` along with its length|
-----------

## Retrieve CPU Temperature

|Description|HAL APIs|L2|L3|Control plane requirements|
|-----------|--------|--|--|--------------------------|
|Invoke the module to retrieve `CPU` temperature, verify the returned temperature falls within valid operating range and ensure the `CPU` is in a normal operating state based on the test profile|dsGetCPUTemperature|Y|N|N|
|Invoke the module to retrieve `CPU` temperature while the device is within a heat/cold chambers to verify that the device will properly retrieve the information while within abnormal temperatures based on the test profile, see ../../profiles/TempatureSettings.yaml |dsGetCPUTemperature|N|Y|N|

### Test Startup Requirement - Retrieve CPU Temperature

None

### Emulator Requirement - Retrieve CPU Temperature

None

### Control Plane Requirement - Retrieve CPU Temperature

None

## Obtain SoC ID

|Description|HAL APIs|L2|L3|Control plane requirements|
|-----------|--------|--|--|--------------------------|
|Trigger the module to obtain `SoC` ID and verify the returned ID matches the expected format and length based on the configuration file.|dsGetSocIDFromSDK|Y|N|N|

### Test Startup Requirement-Obtain SoC ID

None

### Emulator Requirement-Obtain SoC ID

None

### Control Plane Requirement-Obtain SoC ID

None

## Fetch Host EDID

|Description|HAL APIs|L2|L3|Control plane requirements|
|-----------|--------|--|--|--------------------------|
|Call the module function dsGetHostEDID() to fetch the host `EDID`. Verify the retrieved `EDID` data corresponds to the capabilities and specifications of the host device. Each device will have it's own `EDID` that is supports. I.E. Two devices with the same resolution and size will have the same `EDID` values. If the devices are not the same size, resolution, and device type they will not have the same `EDID` value. The retrieved `EDID` values will be compared against those within the configuration file.|dsGetHostEDID|Y|N|N|

### Test Startup Requirement - Fetch Host EDID

Launch the test with the predefined configuration set of results.

### Emulator Requirement - Fetch Host EDID

Emulator will boot with the `EDID` coming from the configuration file. Each 

### Control Plane Requirement - Fetch Host EDID

None