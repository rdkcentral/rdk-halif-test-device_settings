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

|Description|L2|L3|Control Plane Requirements|
|-----------|--|--|--------------------------|
|Invoke the module to retrieve `CPU` temperature, verify the returned temperature falls within valid operating range and ensure the `CPU` is in a normal operating state.|Y|N|N|

### Test Startup Requirement - Retrieve CPU Temperature

None

### Emulator Requirement - Retrieve CPU Temperature

None

### Control Plane Requirement - Retrieve CPU Temperature

None

## Obtain SoC ID

|Description|L2|L3|Control Plane Requirements|
|-----------|--|--|--------------------------|
|Trigger the module to obtain `SoC` ID and verify the returned ID matches the expected format and length.|Y|N|N|

### Test Startup Requirement-Obtain SoC ID

None

### Emulator Requirement-Obtain SoC ID

None

### Control Plane Requirement-Obtain SoC ID

None

## Fetch Host EDID

|Description|L2|L3|Control Plane Requirements|
|-----------|--|--|--------------------------|
|Call the module function dsGetHostEDID() to fetch the host `EDID`. Verify the retrieved `EDID` data corresponds to the capabilities and specifications of the host device|Y|N|N|

### Test Startup Requirement - Fetch Host EDID

Launch the test with the predefined configuration set of results.

### Emulator Requirement - Fetch Host EDID

Emulator will boot with the `EDID` coming from the configuration file.

|#|Description|
|-|-----------|
|1|`EDID` for a panel TV|

TODO: Generate a list of sample list for 5 to 6 different TV's.
Generate a list of TV's from the office for the different `EDID`s and store the binaries of the test. It can use it as samples.

### Control Plane Requirement - Fetch Host EDID

None