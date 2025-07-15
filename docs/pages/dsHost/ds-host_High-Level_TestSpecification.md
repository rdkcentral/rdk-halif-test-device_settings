# Device Settings Host High Level Test Specification Document

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

|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|-----------|--------|--|--|------|----|--------------------------|
|Get the CPU temperature and check weather the temperature falls within valid operating range and ensure the `CPU` is in a normal operating state based on maximum and minimum values of `dsHost/cpuTemperature` in the configuration yaml|`dsGetCPUTemperature`|Y|N|Y|Y|N|
|Invoke the module to retrieve `CPU` temperature while the device is within a heat/cold chambers to verify that the device will properly retrieve the information|`dsGetCPUTemperature`|N|Y|Y|Y|Y|

### Test Startup Requirement - Retrieve CPU Temperature

None

### Emulator Requirement - Retrieve CPU Temperature

None

### Control Plane Requirement - Retrieve CPU Temperature

Control external heat/cold chambers

## Obtain SoC ID

|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|-----------|--------|--|--|------|----|--------------------------|
|Get the `SoC` ID and verify with `dsHost/socID` value in configuration yaml file.|`dsGetSocIDFromSDK`|Y|N|Y|Y|N|

### Test Startup Requirement-Obtain SoC ID

None

### Emulator Requirement-Obtain SoC ID

None

### Control Plane Requirement-Obtain SoC ID

None

## Fetch Host EDID

|Description|HAL APIs|L2|L3|Source|Sink|Control plane requirements|
|-----------|--------|--|--|------|----|--------------------------|
|Get the host `EDID` bytes and validate the `EDID` bytes and length with the `dsHost/edidBytes` and `dsHost/edidbytesLength` values from the configuration yaml file|`dsGetHostEDID`|Y|N|N|Y|N|

### Test Startup Requirement - Fetch Host EDID

Launch the test with the predefined configuration set of results.

### Emulator Requirement - Fetch Host EDID

Emulator will boot with the `EDID` coming from the configuration file.

### Control Plane Requirement - Fetch Host EDID

None
