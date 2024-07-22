# Device Settings Video Port L3 Low Level Test Specification and Procedure Documentation

## Table of Contents

- [Overview](#overview)
- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [References](#references)
- [Level 3 Test Procedure](#level-3-test-procedure)
  - [RAFT/Human](#rafthuman)
  - [Verify the Video content Formats with callbacks](#verify-the-video-content-formats-with-callbacks)
  - [CheckDisplayConnected](#checkdisplayconnected)
  - [Verify the Resolution](#verify-the-resolution)
  - [Verify the HDCP status using callbacks for Source](#verify-the-hdcp-status-using-callbacks-for-source)
  - [Verify CurrentOutputSettings](#verify-currentoutputsettings)

## Overview

This document describes the L3 Low Level Test Specification and Procedure Documentation for the Device Settings Video Port module.

### Acronyms, Terms and Abbreviations

- `HAL` \- Hardware Abstraction Layer, may include some common components
- `UT`  \- Unit Test(s)
- `OEM`  \- Original Equipment Manufacture
- `SoC`  \- System on a Chip
- `HDMI`  \- High-Definition Multimedia Interface
- `HDCP`  \- High-bandwidth Digital Content Protection

### References

- `High Level Test Specification` - [dsVideoPort High Level TestSpec](ds-video-port_High-Level_TestSpec.md)
- `Interface header` - [dsVideoPort HAL header](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsVideoPort.h)

## Level 3 Test Procedure

The following functions are expecting to test the module operates correctly.

### RAFT/Human

- Boot the vendor layer test image.
- Launch AV playback with pre-defined streams before starting test.
- Initializes the Video Port module.
- Terminate the Video Port after all the test.

### Test Streams

### Verify the Video content Formats with callbacks

|Title|Details|
|--|--|
|Test Name|`Verify the Video content Formats with callbacks`|
|Description| Play the pre-defined streams different video content format and check the callbacks is triggered when the video content format changes |
|Test Group| 03 |
|Priority| high |

**Pre-Conditions :**

- For Source device is need to connect to TV using HDMI cable for the display.
- For Sink device can use internal port or supported ports for display.

**Dependencies :**

Configuration YAML file contains all info

- Information about the Vendor layer test image path/location.
- fixed streams and the format of each stream.
- list of cmd's to play the AV.

**User Interaction :**

Check AV is displayed

- Read proc info to confirm is HDR/SDR stream is played.
- User can check the stream content formate using analyzer and confirm.

| # | Description |
| - | ----------- |
| 01 | [RAFT/Human](#rafthuman) Need to start the test|
| 02 | Loop through supported Video Ports and get port handle using`dsGetVideoPort()`type = `dsVideoPort/Ports/[port no]/Typeid` index = `dsVideoPort/Ports/[port no]/Index`|
| 03 | If the video port is not active(`dsIsVideoPortActive()`), enable the video port `dsEnableVideoPort()`  |
| 04 | Verify if the display is connected `dsIsDisplayConnected()`|
| 05 | Check Video content Formats and verify callbacks 1.Play HDR stream 2. Play SDR Stream`dsVideoFormatUpdateRegisterCB(),dsGetVideoEOTF(),dsIsOutputHDR()`|

```mermaid
sequenceDiagram
    participant DUT
    participant RAFT/User
    activate RAFT/User
    RAFT/User->>DUT: Boot the vendor layer test image <br> & wait for cmd promote
    RAFT/User->>DUT: Launch AV playback with pre-defined streams
    RAFT/User->>DUT: Initializes the Video Port module if not initialized
    deactivate RAFT/User
    activate DUT
    Loop the supported Video Ports
        DUT->>DUT: dsGetVideoPort
        DUT->>DUT: dsIsVideoPortActive
        DUT->>DUT: dsEnableVideoPort (enable the video port if not)
        DUT->>DUT: dsIsDisplayConnected (is display connected)
        deactivate DUT
        DUT->>DUT: Await RAFT/User confirmation of Displayed
        opt confirmation of Displayed
            DUT->>RAFT/User: Read the Query
            activate RAFT/User
            RAFT/User-->>DUT: Response back to DUT
            deactivate RAFT/User
        end
        RAFT/User->>DUT: playback the HDR streams
        opt is playback stream is HDR
           DUT->>RAFT/User:[Query] is playback stream HDR
           activate RAFT/User
           RAFT/User-->>DUT: Response to the playback status
           deactivate RAFT/User
        end
        RAFT/User->>DUT: playback the SDR streams
        opt is playback stream is SDR
           DUT->>RAFT/User: Read the Query
           activate RAFT/User
           RAFT/User-->>DUT: Response to the playback status
           deactivate RAFT/User
        end
    End
```

### CheckDisplayConnected

|Title|Details|
|--|--|
|Test Name|`CheckDisplayConnected`|
|Description| Verify the Display connected/disconnected and check status of each supported video port |
|Test Group| 03 |
|Priority| high |

**Pre-Conditions :**

- For Source device is need to connect to TV using HDMI cable for the display.
- For Sink device can use internal port or supported ports for display.

**Dependencies :**

Configuration YAML file contains all info

- Information about the Vendor layer test image path/location.
- fixed streams and the format of each stream.
- list of cmd's to play the AV.

**User Interaction :**

Check AV is displayed

- Read proc info and verify the Display.
- User can check the display and confirm.

| # | Description |
| - | ----------- |
| 01 | [RAFT/Human](#rafthuman) Need to start the test|
| 02 | Loop through supported Video Ports and get port handle using`dsGetVideoPort()`type = `dsVideoPort/Ports/[port no]/Typeid` index = `dsVideoPort/Ports/[port no]/Index`|
| 03 | If the video port is not active(`dsIsVideoPortActive()`), enable the video port `dsEnableVideoPort()`  |
| 04 | Verify if the display is connected `dsIsDisplayConnected()`|

### Verify the Resolution

|Title|Details|
|--|--|
|Test Name|`Verify the Resolution`|
|Description| Play the pre-defined streams and set supported resolution and verify |
|Test Group| 03 |
|Priority| high |

**Pre-Conditions :**

- For Source device is need to connect to TV using HDMI cable for the display.
- For Sink device can use internal port or supported ports for display.

**Dependencies :**

Configuration YAML file contains all info

- Information about the Vendor layer test image path/location.
- fixed streams and the format of each stream.
- list of cmd's to play the AV.

**User Interaction :**

Check AV is displayed

- Read proc info and verify the resolution.
- User can check the resolution using analyzer and confirm.

| # | Description |
| - | ----------- |
| 01 | [RAFT/Human](#rafthuman) Need to start the test|
| 02 | Loop through supported Video Ports and get port handle using`dsGetVideoPort()`type = `dsVideoPort/Ports/[port no]/Typeid` index = `dsVideoPort/Ports/[port no]/Index`|
| 03 | If the video port is not active(`dsIsVideoPortActive()`), enable the video port `dsEnableVideoPort()`  |
| 04 | For source Set with supported Resolution using pre-defined streams `dsSetResolution()`|
| 05 | Verify Resolution with pre-defined stream`dsGetResolution()`|

### Verify the HDCP status using callbacks for Source

|Title|Details|
|--|--|
|Test Name|`Verify the HDCP status`|
|Description| Check the HDCP status using callbacks with timing info|
|Test Group| 03 |
|Priority| high |

**Pre-Conditions :**

- For Source device is need to connect to TV using HDMI cable for the display.
- For Sink device can use internal port or supported ports for display.

**Dependencies :**

NA

**User Interaction :**

- Unplug/plug the HDMI cable.

| # | Description |
| - | ----------- |
| 01 | [RAFT/Human](#rafthuman) Need to start the test|
| 02 | Loop through supported Video Ports and get port handle using`dsGetVideoPort()`type = `dsVideoPort/Ports/[port no]/Typeid` index = `dsVideoPort/Ports/[port no]/Index`|
| 03 | If the video port is not active(`dsIsVideoPortActive()`), enable the video port `dsEnableVideoPort()`  |
| 04 | Verify HDCP status `dsEnableHDCP(),dsIsHDCPEnabled(),dsGetHDCPStatus() dsRegisterHdcpStatusCallback()`|

### Verify CurrentOutputSettings

|Title|Details|
|--|--|
|Test Name|`Verify CurrentOutputSettings`|
|Description| Play the pre-defined streams and verify current color space,color depth, matrix coefficients, EOT, quantization range |
|Test Group| 03 |
|Priority| high |

**Pre-Conditions :**

- For Source device is need to connect to TV using HDMI cable for the display.
- For Sink device can use internal port or supported ports for display.

**Dependencies :**

Configuration YAML file contains all info

- Information about the Vendor layer test image path/location.
- fixed streams and the format of each stream.
- list of cmd's to play the AV.

**User Interaction :**

Check AV is displayed

- Read proc info and verify the EOT,color,quantization range.
- User can check the EOT using analyzer and confirm.

| # | Description |
| - | ----------- |
| 01 | [RAFT/Human](#rafthuman) Need to start the test|
| 02 | Loop through supported Video Ports and get port handle using`dsGetVideoPort()`type = `dsVideoPort/Ports/[port no]/Typeid` index = `dsVideoPort/Ports/[port no]/Index`|
| 03 | If the video port is not active(`dsIsVideoPortActive()`), enable the video port `dsEnableVideoPort()`  |
| 04 | For source Set with supported Resolution using pre-defined streams `dsSetResolution()`|
| 05 | check color space, color depth, matrix coefficients, video Electro-Optical Transfer Function (EOT) and  quantization range using `dsGetCurrentOutputSettings()`|

### Test3

|Title|Details|
|--|--|
|Test Name|`Verify the Video content Formats`|
|Description| Play the pre-defined HDR streams formats, check HDR mode can force and reset the output to SDR and playback the SDR streams. |
|Test Group| 03 |
|Priority| high |

**Pre-Conditions :**
Launch AV playback in the background before starting test.
Initializes the Video Port

**Dependencies :**
Configuration YAML file contains all info on fixed streams and the format of each stream

**User Interaction :** Yes
Verify the Video content Formats with analyzer.

| # | Description |
| - | ----------- |
|01|Loop through supported Video Ports and get port handle using`dsGetVideoPort()`type = `dsVideoPort/Ports/[port no]/Typeid` index = `dsVideoPort/Ports/[port no]/Index`|
| 02 | If the video port is not active(`dsIsVideoPortActive()`), enable the video port `dsEnableVideoPort()`  |
| 03 | play pre-defined streams with different Video content Formats and verify content  backs`dsSetForceHDRMode(),dsResetOutputToSDR()`|

### Test5

Note: Test case for Sink
|Title|Details|
|--|--|
|Test Name|`Verify the Resolution`|
|Description| Play the pre-defined streams with different resolution and verify |
|Test Group| 03 |
|Priority| high |

**Pre-Conditions :**
Launch AV playback in the background before starting test.
Initializes the Video Port

**Dependencies :**
Configuration YAML file contains all info on fixed streams and the format of each stream

**User Interaction :** Yes
Verify Resolutions with analyzer.

| # | Description |
| - | ----------- |
|01|Loop through supported Video Ports and get port handle using`dsGetVideoPort()`type = `dsVideoPort/Ports/[port no]/Typeid` index = `dsVideoPort/Ports/[port no]/Index`|
| 02 | If the video port is not active(`dsIsVideoPortActive()`), enable the video port `dsEnableVideoPort()`  |
| 03 | Verify Resolution with pre-defined streams `dsGetResolution()`|