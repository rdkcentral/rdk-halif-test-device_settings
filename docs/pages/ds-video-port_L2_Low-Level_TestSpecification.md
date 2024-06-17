# Device Settings Video Port L2 Low Level Test Specification and Procedure Documentation

## Table of Contents

- [Overview](#overview)
- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Definitions](#definitions)
- [References](#references)
- [Level 2 Test Procedure](#level-2-test-procedure)

## Overview

This document describes the level 2 testing suite for the Device Settings Video Port module.

### Acronyms, Terms and Abbreviations

- `HAL` \- Hardware Abstraction Layer, may include some common components
- `UT`  \- Unit Test(s)
- `OEM`  \- Original Equipment Manufacture
- `SoC`  \- System on a Chip

### Definitions

- `ut-core` \- Common Testing Framework <https://github.com/rdkcentral/ut-core>, which wraps a open-source framework that can be expanded to the requirements for future framework.

### References

- `High Level Test Specification` - [ds-video-port_High-Level_TestSpec.md](ds-video-port_High-Level_TestSpec.md)

## Level 2 Test Procedure

The following functions are expecting to test the module operates correctly.

### Test 1

|Title|Details|
|--|--|
|Function Name|`test_l2_dsVideoPort_EnableDisabledVideoPorts_sink`|
|Description|Get the handle for each video port, check the status of each video port to see if it's enabled or disabled. If a port is disabled, enable it, and then verify the status of each port.|
|Test Group|02|
|Test Case ID|001|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**

If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize the video port using dsVideoPortInit() | None | dsERR_NONE | Should be successful |
| 02 | Get the handle for each video port using dsGetVideoPort() | type = dsVIDEOPORT_TYPE_RF to dsVIDEOPORT_TYPE_MAX, index = 0 | dsERR_NONE | Should be successful |
| 03 | Check the status of each video port using dsIsVideoPortEnabled() | handle = obtained from dsGetVideoPort() | dsERR_NONE | Should be successful |
| 04 | If a port is disabled, enable it using dsEnableVideoPort() | handle = obtained from dsGetVideoPort(), enabled = true | dsERR_NONE | Should be successful |
| 05 | Verify the status of each port using dsIsVideoPortEnabled() | handle = obtained from dsGetVideoPort() | dsERR_NONE, enabled = true | Should be successful |
| 06 | Terminate the video port using dsVideoPortTerm() | None | dsERR_NONE | Should be successful |

```mermaid
graph TB
    A[Call dsVideoPortInit API] -->|dsERR_NONE| B{For each video port type <br>call dsGetVideoPort API}
    A -->|Not dsERR_NONE| A1[Test case fail]
    B -->|dsERR_NONE and valid handle| D[Call dsIsVideoPortEnabled API]
    D -->|dsERR_NONE| E[Check if video port is enabled]
    E -->|Enabled flag is false| F[Call dsEnableVideoPort API]
    F -->|dsERR_NONE| G[Call dsIsVideoPortEnabled API]
    G -->|dsERR_NONE and enabled flag is true| B
    B -->|End of loop|I[Call dsVideoPortTerm API]
    I -->|dsERR_NONE| J[Test case success]
    I -->|Not dsERR_NONE| I1[Test case fail]
```

### Test 2

|Title|Details|
|--|--|
|Function Name|`test_l2_dsVideoPort_EnableDisabledVideoPorts_source`|
|Description|Get the handle for each video port, check the status of each video port to see if it's enabled or disabled. If a port is disabled, enable it, and then verify the status of each port.|
|Test Group|02|
|Test Case ID|002|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize video port using dsVideoPortInit | None | dsERR_NONE | Should be successful |
| 02 | Get the handle for each video port using dsGetVideoPort | type = dsVIDEOPORT_TYPE_RF to dsVIDEOPORT_TYPE_MAX, index = 0 | dsERR_NONE | Should be successful |
| 03 | Check the status of each video port using dsIsVideoPortEnabled | handle = obtained from dsGetVideoPort | dsERR_NONE | Should be successful |
| 04 | If a port is disabled, enable it using dsEnableVideoPort | handle = obtained from dsGetVideoPort, enabled = true | dsERR_NONE | Should be successful |
| 05 | Verify the status of each port using dsIsVideoPortEnabled | handle = obtained from dsGetVideoPort | dsERR_NONE, enabled = true | Should be successful |
| 06 | Terminate video port using dsVideoPortTerm | None | dsERR_NONE | Should be successful |

```mermaid
graph TB
    A[Call dsVideoPortInit API] -->|dsERR_NONE| B{For each video port type <br>call dsGetVideoPort API}
    A -->|Not dsERR_NONE| A1[Test case fail]
    B -->|dsERR_NONE and valid handle| D[Call dsIsVideoPortEnabled API]
    D -->|dsERR_NONE| E[Check if video port is enabled]
    E -->|Enabled flag is false| F[Call dsEnableVideoPort API]
    F -->|dsERR_NONE| G[Call dsIsVideoPortEnabled API]
    G -->|dsERR_NONE and enabled flag is true| B
    B -->|End of loop|I[Call dsVideoPortTerm API]
    I -->|dsERR_NONE| J[Test case success]
    I -->|Not dsERR_NONE| I1[Test case fail]
```

### Test 3

|Title|Details|
|--|--|
|Function Name|`test_l2_dsVideoPort_VerifyDisplayAndPortStatus_sink`|
|Description|Verify the connected/disconnected status of each port's display when no video port is connected.|
|Test Group|02|
|Test Case ID|003|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize the video port using dsVideoPortInit | None | dsERR_NONE | Should be successful |
| 02 | Get the video port handle for each type of video port using dsGetVideoPort | type = dsVIDEOPORT_TYPE_RF to dsVIDEOPORT_TYPE_MAX, index = 0 | dsERR_NONE | Should be successful |
| 03 | Check if the display is connected for the obtained video port handle using dsIsDisplayConnected | handle = obtained from dsGetVideoPort | dsERR_NONE, connected = false | Should be successful |
| 04 | Check if the video port is active for the obtained video port handle using dsIsVideoPortActive | handle = obtained from dsGetVideoPort | dsERR_NONE, active = false | Should be successful |
| 05 | Terminate the video port using dsVideoPortTerm | None | dsERR_NONE | Should be successful |

```mermaid
graph TB
    A[Call dsVideoPortInit] -->|dsERR_NONE| B{For each type and index <br> call dsGetVideoPort}
    A -->|Not dsERR_NONE| A1[Test case fail]
    B -->|dsERR_NONE and valid handle| C[Call dsIsDisplayConnected for each handle]
    C -->|dsERR_NONE and connected is false| D[Call dsIsVideoPortActive for each handle]
    D -->|dsERR_NONE and enabled flag is true| B
    B -->|End of loop|I[Call dsVideoPortTerm API]
    I -->|dsERR_NONE| J[Test case success]
    I -->|Not dsERR_NONE| I1[Test case fail]
```

### Test 4

|Title|Details|
|--|--|
|Function Name|`test_l2_dsVideoPort_VerifyDisplayAndPortStatus_source`|
|Description|Verify the connected/disconnected status of each port's display when no video port is connected.|
|Test Group|02|
|Test Case ID|004|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize the video port using dsVideoPortInit | None | dsERR_NONE | Should be successful |
| 02 | Get the video port handle for each type of video port using dsGetVideoPort | type = dsVIDEOPORT_TYPE_RF to dsVIDEOPORT_TYPE_MAX, index = 0 | dsERR_NONE | Should be successful |
| 03 | Check if the display is connected for each video port using dsIsDisplayConnected | handle = obtained from dsGetVideoPort | dsERR_NONE, connected = false | Should be successful |
| 04 | Check if the video port is active for each video port using dsIsVideoPortActive | handle = obtained from dsGetVideoPort | dsERR_NONE, active = false | Should be successful |
| 05 | Terminate the video port using dsVideoPortTerm | None | dsERR_NONE | Should be successful |

```mermaid
graph TB
    A[Call dsVideoPortInit] -->|dsERR_NONE| B{For each type and index <br> call dsGetVideoPort}
    A -->|Not dsERR_NONE| A1[Test case fail]
    B -->|dsERR_NONE and valid handle| C[Call dsIsDisplayConnected for each handle]
    C -->|dsERR_NONE and connected is false| D[Call dsIsVideoPortActive for each handle]
    D -->|dsERR_NONE and enabled flag is true| B
    B -->|End of loop|I[Call dsVideoPortTerm API]
    I -->|dsERR_NONE| J[Test case success]
    I -->|Not dsERR_NONE| I1[Test case fail]
```

### Test 5

|Title|Details|
|--|--|
|Function Name|`test_l2_dsVideoPort_RetrieveAndVerifySurroundModeCapabilities_sink`|
|Description|Retrieve the surround mode capabilities of each port and verify them with the configuration YAML file. If it is a sink device, retrieve the value from 'Sink_4K_VideoPort.yaml' using the path Ports/1/Display_surround" since the sink device has only an INTERNAL port. It is not supported for the source devices.|
|Test Group|02|
|Test Case ID|005|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize the video port using dsVideoPortInit() | None | dsERR_NONE | Should be successful |
| 02 | Get the video port handle using dsGetVideoPort() with dsVIDEOPORT_TYPE_INTERNAL and index 0 | dsVIDEOPORT_TYPE_INTERNAL, 0 | dsERR_NONE | Should be successful |
| 03 | Check if the display is in surround mode using dsIsDisplaySurround() with the obtained handle | handle = obtained from previous step | dsERR_NONE | Should be successful |
| 04 | Verify if the surround mode from previous step matches with the configuration YAML file | surrond, "Ports/1/Display_surrond" | None | Should be successful |
| 05 | Terminate the video port using dsVideoPortTerm() | None | dsERR_NONE | Should be successful |

```mermaid
graph TB
    Step1[Call dsVideoPortInit API]
    Step1 -->|dsERR_NONE| Step2[Call dsGetVideoPort API]
    Step1 -->|Not dsERR_NONE| Fail1[Test Case Failed]
    Step2 -->|dsERR_NONE and valid handle| Step3[Call dsIsDisplaySurround API]
    Step3 -->|dsERR_NONE and boolean value| Step4[Retrieve surround mode capabilities]
    Step4 --> Step5[Verify if dsIsDisplaySurround value matches with configuration file value]
    Step5 --> Step6[Call dsVideoPortTerm API]
    Step6 -->|dsERR_NONE| End[Test Case Passed]
    Step6 -->|Not dsERR_NONE| Fail5[Test Case Failed]
```

### Test 6

|Title|Details|
|--|--|
|Function Name|`test_l2_dsVideoPort_VerifyDisplaySurround_source`|
|Description|Verify the each port surround mode capabilities of connected display and verify with configuration file. It is not supported of Sink devices. If it is a source devices, the value has to be retrieved from the Source_4K_VideoPort.yaml" using the path "Ports/1/Display_surround" supported by the HDMI device.|
|Test Group|02|
|Test Case ID|006|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize the video port using dsVideoPortInit() | None | dsERR_NONE | Should be successful |
| 02 | Get the video port handle using dsGetVideoPort() with HDMI and index 0 | dsVIDEOPORT_TYPE_HDMI, 0, &handle | dsERR_NONE | Should be successful |
| 03 | Check if the display is surround using dsIsDisplaySurround() with valid handle | handle, &surround | dsERR_NONE | Should be successful |
| 04 | If display is surround, get the surround mode using dsGetSurroundMode() with valid handle | handle, &surround_mode | dsERR_NONE | Should be successful |
| 05 | Verify if the surround mode from previous step matches with the configuration YAML file | surrond, "Ports/1/Display_surrond" | True | Should be successful |
| 06 | Terminate the video port using dsVideoPortTerm() | None | dsERR_NONE | Should be successful |

```mermaid
graph TB
A[Call dsVideoPortInit] -->|dsERR_NONE| B[Call dsGetVideoPort]
A -->|Not dsERR_NONE| A1[Test case fail]
B -->|dsERR_NONE and valid handle| C[Call dsIsDisplaySurround]
C -->|dsERR_NONE and display supports surround| D[Call dsGetSurroundMode]
C -->|Not dsERR_NONE| C1[Test case fail]
D -->|dsERR_NONE and valid surround mode| E[Verify if surround mode matches with value from Source_4K_VideoPort.yaml]
E -->G[Call dsVideoPortTerm]
G -->|dsERR_NONE| G1[Test case success]
G -->|Not dsERR_NONE| G2[Test case fail]
```

### Test 7

|Title|Details|
|--|--|
|Function Name|`test_l2_dsVideoPort_SetAndGetResolution_source`|
|Description|Set properties for each video port, including pixel resolution, aspect ratio, stereoscopic modes, frame rates, and scan modes, looping through supported values. Verify the settings using the get function.|
|Test Group|02|
|Test Case ID|007|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize video port using dsVideoPortInit() | None | dsERR_NONE | Should be successful |
| 02 | Loop through each video port and get the handle using dsGetVideoPort() | type = dsVIDEOPORT_TYPE_RF to dsVIDEOPORT_TYPE_MAX, 0, &handle | dsERR_NONE | Should be successful |
| 03 | Loop through all possible pixel resolutions, aspect ratios, stereoscopic modes, frame rates, and scan modes | pixelResolution = dsVIDEO_PIXELRES_720x480 to dsVIDEO_PIXELRES_MAX, aspectRatio = dsVIDEO_ASPECT_RATIO_4x3 to dsVIDEO_ASPECT_RATIO_MAX, stereoScopicMode = dsVIDEO_SSMODE_UNKNOWN to dsVIDEO_SSMODE_MAX, frameRate = dsVIDEO_FRAMERATE_UNKNOWN to dsVIDEO_FRAMERATE_MAX, interlaced = false | dsERR_NONE | Should be successful |
| 04 | Set resolution using dsSetResolution() with handle and setResolution | handle, &setResolution | dsERR_NONE | Should be successful |
| 05 | Get resolution using dsGetResolution() with handle and getResolution | handle, &getResolution | dsERR_NONE | Should be successful |
| 06 | Compare setResolution and getResolution | setResolution, getResolution | Equal values for all properties | Should be successful |
| 07 | Terminate video port using dsVideoPortTerm() | None | dsERR_NONE | Should be successful |

```mermaid
graph TB
    A[Call dsVideoPortInit] -->|dsERR_NONE| B[Call dsGetVideoPort]
    A -->|Not dsERR_NONE| A1[Test case Fail]
    B -->|dsERR_NONE and valid handle| C{Loop through supported values}
    C --> E[Set values using dsSetResolution API]
    E --> F[Get values using dsGetResolution API]
    F --> G[Compare returned and set resolution]
    G --> C
    F --> I[Call dsVideoPortTerm]
    I -->|dsERR_NONE| J[Test case Success]
    I -->|Not dsERR_NONE| I1[Test case Fail]
```

### Test 8

|Title|Details|
|--|--|
|Function Name|`test_l2_dsVideoPort_VerifySupportedTvResolutions_sink`|
|Description|Gets the each port supported resolutions of TV and verify with the configuration YAML file. If it is a sink device, the value to be retrieved from the 'Sink_4K_VideoPort.yaml' by using the path 'Ports/1/Supported_tv_resolutions_capabilities', supported by INTERNAL port. For source devices, the value to be retrieved from the 'Source_4K_VideoPort.yaml' by using the path 'Ports/1/Supported_tv_resolutions_capabilities', supported by HDMI port.|
|Test Group|02|
|Test Case ID|008|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize the video port using dsVideoPortInit | None | dsERR_NONE | Should be successful |
| 02 | Get the video port handle using dsGetVideoPort with type as dsVIDEOPORT_TYPE_INTERNAL and index as 0 | type = dsVIDEOPORT_TYPE_INTERNAL, index = 0 | dsERR_NONE | Should be successful |
| 03 | Get the supported TV resolutions using dsSupportedTvResolutions with the obtained handle | handle = obtained from previous step | dsERR_NONE | Should be successful |
| 04 | Verify the obtained resolutions with the expected resolutions from the configuration YAML file | resolutions = value in "Ports/1/Supported_tv_resolutions_capabilities" | dsERR_NONE | Should be successful |
| 05 | Terminate the video port using dsVideoPortTerm | None | dsERR_NONE | Should be successful |

```mermaid
graph TB
    Step1[Call dsVideoPortInit API]
    Step1 -- dsERR_NONE --> Step2[Call dsGetVideoPort API with dsVIDEOPORT_TYPE_INTERNAL]
    Step1 -- Not dsERR_NONE --> Fail1[Test case fail]
    Step2 -- dsERR_NONE and valid handle --> Step3[Call dsSupportedTvResolutions API]
    Step3 -- dsERR_NONE and valid resolutions --> Step4[Verfiy if resolutions match with Sink_4K_VideoPort.yaml file value]
    Step4 --> Step5[Call dsVideoPortTerm API]
    Step5 -- dsERR_NONE --> End[Test Case Passed]
    Step5 -- Not dsERR_NONE --> Fail5[Test Case Failed: dsVideoPortTerm API failed]
```

### Test 9

|Title|Details|
|--|--|
|Function Name|`test_l2_dsVideoPort_VerifySupportedTvResolutions_source`|
|Description|Gets the each port supported resolutions of TV and verify with the configuration YAML file. If it is a sink device, the value to be retrieved from the 'Sink_4K_VideoPort.yaml' by using the path 'Ports/1/Supported_tv_resolutions_capabilities', supported by INTERNAL port. For source devices, the value to be retrieved from the 'Source_4K_VideoPort.yaml' by using the path 'Ports/1/Supported_tv_resolutions_capabilities', supported by HDMI port.|
|Test Group|02|
|Test Case ID|009|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize the video port using dsVideoPortInit | None | dsERR_NONE | Should be successful |
| 02 | Get the video port handle using dsGetVideoPort with type=dsVIDEOPORT_TYPE_HDMI and index=1 | type=dsVIDEOPORT_TYPE_HDMI, index=1 | dsERR_NONE | Should be successful |
| 03 | Get the supported TV resolutions using dsSupportedTvResolutions with the obtained handle | handle=obtained handle | dsERR_NONE | Should be successful |
| 04 | Verify the obtained resolutions with the configuration YAML file | resolutions= value in "Ports/1/Supported_tv_resolutions_capabilities" | dsERR_NONE | Should be successful |
| 05 | Terminate the video port using dsVideoPortTerm | None | dsERR_NONE | Should be successful |

```mermaid
graph TB
    Step1[Call dsVideoPortInit API]
    Step1 -- dsERR_NONE --> Step2[Call dsGetVideoPort API with dsVIDEOPORT_TYPE_HDMI]
    Step1 -- Not dsERR_NONE --> Fail1[Test case fail]
    Step2 -- dsERR_NONE and valid handle --> Step3[Call dsSupportedTvResolutions API]
    Step3 -- dsERR_NONE and valid resolutions --> Step4[Verfiy if resolutions match with Source_4K_VideoPort.yaml file value]
    Step4 --> Step5[Call dsVideoPortTerm API]
    Step5 -- dsERR_NONE --> End[Test Case Passed]
    Step5 -- Not dsERR_NONE --> Fail5[Test Case Failed: dsVideoPortTerm API failed]
```

### Test 10

|Title|Details|
|--|--|
|Function Name|`test_l2_dsVideoPort_GetHDRCapabilities_sink`|
|Description|Get the each port HDR capabilities & verify with the configuration YAML file YAML file. If it is a sink device, the value to be retrieved from the 'Sink_4K_VideoPort.yaml' by using the path 'Ports/1/hdr_capabilities', supported by INTERNAL port. For source devices, the value to be retrieved from the 'Source_4K_VideoPort.yaml' by using the path 'Ports/1/hdr_capabilities', supported only by HDMI port.|
|Test Group|02|
|Test Case ID|10|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize the video port using dsVideoPortInit() | None | dsERR_NONE | Should be successful |
| 02 | Get the video port handle using dsGetVideoPort() with dsVIDEOPORT_TYPE_INTERNAL and index 0 | dsVIDEOPORT_TYPE_INTERNAL, 0 | dsERR_NONE | Should be successful |
| 03 | Get the HDR capabilities of the TV using dsGetTVHDRCapabilities() with the obtained handle | handle = obtained from previous step | dsERR_NONE | Should be successful |
| 04 | Verify the obtained capabilities with the configuration YAML file | capabilities = obtained from previous step | capabilities = value in "Ports/1/hdr_capabilities | Should be successful |
| 05 | Terminate the video port using dsVideoPortTerm() | None | dsERR_NONE | Should be successful |

```mermaid
graph TB
    A[Call dsVideoPortInit API] -->|dsERR_NONE| B[Call dsGetVideoPort API with dsVIDEOPORT_TYPE_INTERNAL]
    A -->|Not dsERR_NONE| A1[Test case fail]
    B -->|dsERR_NONE and valid handle| C[Call dsGetTVHDRCapabilities API with handle]
    C -->|dsERR_NONE and bitwise OR-ed value| D[Verify if output matches with value from Sink_4K_VideoPort.yaml]
    D --> E[Call dsVideoPortTerm API]
    E -->|dsERR_NONE| F[Test case success]
    E -->|Not dsERR_NONE| E1[Test case fail]
```

### Test 11

|Title|Details|
|--|--|
|Function Name|`test_l2_dsVideoPort_GetHDRCapabilities_source`|
|Description|Get the each port HDR capabilities & verify with the configuration YAML file YAML file. If it is a sink device, the value to be retrieved from the 'Sink_4K_VideoPort.yaml' by using the path 'Ports/1/hdr_capabilities', supported by INTERNAL port. For source devices, the value to be retrieved from the 'Source_4K_VideoPort.yaml' by using the path 'Ports/1/hdr_capabilities', supported only by HDMI port.|
|Test Group|02|
|Test Case ID|011|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize the video port using dsVideoPortInit | None | dsERR_NONE | Should be successful |
| 02 | Get the video port handle for HDMI type using dsGetVideoPort | type = dsVIDEOPORT_TYPE_HDMI, index = 0, handle = valid pointer | dsERR_NONE | Should be successful |
| 03 | Get the HDR capabilities of the TV using dsGetTVHDRCapabilities with the handle obtained from previous step | handle = obtained from step 02, capabilities = valid pointer | dsERR_NONE | Should be successful |
| 04 | Verify the obtained capabilities with the configuration YAML file | capabilities = obtained from step 03 | capabilities = value in 'Ports/1/hdr_capabilities' | Should be successful |
| 05 | Terminate the video port using dsVideoPortTerm | None | dsERR_NONE | Should be successful |

```mermaid
graph TB
    A[Call dsVideoPortInit API] -->|dsERR_NONE| B[Call dsGetVideoPort API with dsVIDEOPORT_TYPE_HDMI]
    A -->|Not dsERR_NONE| A1[Test case fail]
    B -->|dsERR_NONE and valid handle| C[Call dsGetTVHDRCapabilities API with handle]
    C -->|dsERR_NONE and bitwise OR-ed value| D[Verify if output matches with value from Source_4K_VideoPort.yaml]
    D --> E[Call dsVideoPortTerm API]
    E -->|dsERR_NONE| F[Test case success]
    E -->|Not dsERR_NONE| E1[Test case fail]
```

### Test 12

|Title|Details|
|--|--|
|Function Name|`test_l2_dsVideoPort_SetAndGetForceDisable4KSupport_sink`|
|Description|Set Force-disable 4K support for each port and verify it using the get function.|
|Test Group|02|
|Test Case ID|12|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize the video port using dsVideoPortInit() | None | dsERR_NONE | Should be successful |
| 02 | Loop through all video ports and get the video port handle using dsGetVideoPort()| type = dsVIDEOPORT_TYPE_RF to dsVIDEOPORT_TYPE_MAX, 0, &handle | dsERR_NONE | Should be successful |
| 03 | Set Force-disable 4K support using dsSetForceDisable4KSupport() with handle and disable set to true | handle, true | dsERR_NONE | Should be successful |
| 04 | Get Force-disable 4K support using dsGetForceDisable4KSupport() with handle | handle, &getDisable | dsERR_NONE, true | Should be successful |
| 05 | Set Force-disable 4K support using dsSetForceDisable4KSupport() with handle and disable set to false | handle, false | dsERR_NONE | Should be successful |
| 06 | Get Force-disable 4K support using dsGetForceDisable4KSupport() with handle | handle, &getDisable | dsERR_NONE, false | Should be successful |
| 07 | Terminate the video port using dsVideoPortTerm() | None | dsERR_NONE | Should be successful |

```mermaid
graph TB
    A[Call dsVideoPortInit API] -->|Not dsERR_NONE| A1[Test case fail]
    A --> P{For each video port type <br>call dsGetVideoPort API} --> B[Call dsGetVideoPort API] 
    B[Call dsGetVideoPort API] --> |dsERR_NONE and valid handle|C[Set disable to true/false using dsSetForceDisable4KSupport API]
    C --> |dsERR_NONE| D[Get the disable value using dsGetForceDisable4KSupport API] 
    D --> |dsERR_NONE| E[Verify if the disable values retrieved from set and get APIs match]
    E --> |Iterate through all possible values | P
    E --> |End of loop| F -->|Not dsERR_NONE| G[Test case fail]
    F[Call dsVideoPortTerm API] -->|dsERR_NONE| F1[Test case success]
```

### Test 13

|Title|Details|
|--|--|
|Function Name|`test_l2_dsVideoPort_SetAndGetForceDisable4KSupport_source`|
|Description|Set Force-disable 4K support for each port and verify it using the get function.|
|Test Group|02|
|Test Case ID|013|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize video port using dsVideoPortInit() | None | dsERR_NONE | Should be successful |
| 02 | Loop through all video ports and get the video port handle using dsGetVideoPort()| type = dsVIDEOPORT_TYPE_RF to dsVIDEOPORT_TYPE_MAX, 0 , handle = valid pointer | dsERR_NONE | Should be successful |
| 03 | Set Force-disable 4K support using dsSetForceDisable4KSupport() with handle and disable = true | handle = obtained handle, disable = true | dsERR_NONE | Should be successful |
| 04 | Get Force-disable 4K support using dsGetForceDisable4KSupport() with handle | handle = obtained handle, getDisable = valid pointer | dsERR_NONE, getDisable = true | Should be successful |
| 05 | Set Force-disable 4K support using dsSetForceDisable4KSupport() with handle and disable = false | handle = obtained handle, disable = false | dsERR_NONE | Should be successful |
| 06 | Get Force-disable 4K support using dsGetForceDisable4KSupport() with handle | handle = obtained handle, getDisable = valid pointer | dsERR_NONE, getDisable = false | Should be successful |
| 07 | Terminate video port using dsVideoPortTerm() | None | dsERR_NONE | Should be successful |

```mermaid
graph TB
    A[Call dsVideoPortInit API] -->|Not dsERR_NONE| A1[Test case fail]
    A --> P{For each video port type <br>call dsGetVideoPort API} --> B[Call dsGetVideoPort API] 
    B[Call dsGetVideoPort API] --> |dsERR_NONE and valid handle|C[Set disable to true/false using dsSetForceDisable4KSupport API]
    C --> |dsERR_NONE| D[Get the disable value using dsGetForceDisable4KSupport API] 
    D --> |dsERR_NONE| E[Verify if the disable values retrieved from set and get APIs match]
    E --> |Iterate through all possible values | P
    E --> |End of loop| F -->|Not dsERR_NONE| G[Test case fail]
    F[Call dsVideoPortTerm API] -->|dsERR_NONE| F1[Test case success]
```

### Test 14

|Title|Details|
|--|--|
|Function Name|`test_l2_dsVideoPort_GetHDCPStatus_sink`|
|Description|Check the HDCP status of each port and verify if dsHDCP_STATUS_AUTHENTICATED is returned for sinks and dsHDCP_STATUS_UNPOWERED/dsHDCP_STATUS_PORTDISABLED is returned for sources.|
|Test Group|02|
|Test Case ID|14|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize the video port using dsVideoPortInit() | None | dsERR_NONE | Should be successful |
| 02 | Loop through all video ports and get the video port handle using dsGetVideoPort()| type = dsVIDEOPORT_TYPE_RF to dsVIDEOPORT_TYPE_MAX, index = 0, handle = valid pointer | dsERR_NONE | Should be successful |
| 03 | Get the HDCP status for each handle using dsGetHDCPStatus() | handle = obtained from dsGetVideoPort() | dsERR_NONE | Should be successful |
| 04 | Check if the HDCP status is authenticated | status = obtained from dsGetHDCPStatus() | dsHDCP_STATUS_AUTHENTICATED | Should be successful |
| 05 | Terminate the video port using dsVideoPortTerm() | None | dsERR_NONE | Should be successful |

```mermaid
graph TB
    A[Call dsVideoPortInit API] --> |dsERR_NONE| B{For each video port type <br>call dsGetVideoPort API}
    A -->|Not dsERR_NONE| A1[Test Case Fail]
    B -->|dsERR_NONE and valid handle| C[Call dsGetHDCPStatus API with handle]
    C -->|dsERR_NONE and HDCP status| D[Verify HDCP status is dsHDCP_STATUS_AUTHENTICATED]
    D --> |Iterate through all possible values| B
    D -->|End of loop|E[Call dsVideoPortTerm API]
    E -->|dsERR_NONE| F[Test Case Success]
    E -->|Not dsERR_NONE| E1[Test Case Fail]
```

### Test 15

|Title|Details|
|--|--|
|Function Name|`test_l2_dsVideoPort_GetHDCPStatus_source`|
|Description|Check the HDCP status of each port and verify if dsHDCP_STATUS_AUTHENTICATED is returned for sinks and dsHDCP_STATUS_UNPOWERED/dsHDCP_STATUS_PORTDISABLED is returned for sources.|
|Test Group|02|
|Test Case ID|015|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize the video port using dsVideoPortInit() | None | dsERR_NONE | Should be successful |
| 02 | Loop through all video ports and get the video port handle using dsGetVideoPort()| type = dsVIDEOPORT_TYPE_RF to dsVIDEOPORT_TYPE_MAX, index = 0, handle = valid pointer | dsERR_NONE | Should be successful |
| 03 | Get the HDCP status using dsGetHDCPStatus() with the valid handle | handle = obtained handle, status = valid pointer | dsERR_NONE | Should be successful |
| 04 | Check if the HDCP status is either dsHDCP_STATUS_UNPOWERED or dsHDCP_STATUS_PORTDISABLED | status = obtained status | dsHDCP_STATUS_UNPOWERED or dsHDCP_STATUS_PORTDISABLED | Should be successful |
| 05 | Terminate the video port using dsVideoPortTerm() | None | dsERR_NONE | Should be successful |

```mermaid
graph TB
    A[Call dsVideoPortInit API] --> |dsERR_NONE| B{For each video port type <br>call dsGetVideoPort API}
    A -->|Not dsERR_NONE| A1[Test Case Fail]
    B -->|dsERR_NONE and valid handle| C[Call dsGetHDCPStatus API with handle]
    C -->|dsERR_NONE and HDCP status| D[Verify HDCP status is dsHDCP_STATUS_UNPOWERED or dsHDCP_STATUS_PORTDISABLED]
    D --> |Iterate through all possible values| B
    D -->|End of loop|E[Call dsVideoPortTerm API]
    E -->|dsERR_NONE| F[Test Case Success]
    E -->|Not dsERR_NONE| E1[Test Case Fail]
```

### Test 16

|Title|Details|
|--|--|
|Function Name|`test_l2_dsVideoPort_VerifyHDCPProtocolStatus_sink`|
|Description|Check the HDCP protocol status of each port and verify it with the configuration YAML file. If it is a sink device, retrieve the value from the 'Sink_4K_VideoPort.yaml' file using the path 'Ports/1/hdcp_protocol_version' supported by INTERNAL port. For a source device, retrieve the value from the 'Source_4K_VideoPort.yaml' file using the path 'Ports/1/hdcp_protocol_version' supported by HDMI port.|
|Test Group|02|
|Test Case ID|16|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize the video port using dsVideoPortInit | None | dsERR_NONE | Should be successful |
| 02 | Get the video port handle using dsGetVideoPort with dsVIDEOPORT_TYPE_INTERNAL and index 0 | dsVIDEOPORT_TYPE_INTERNAL, index = 0 | dsERR_NONE | Should be successful |
| 03 | Get the HDCP protocol version using dsGetHDCPProtocol with the obtained handle | handle = obtained from previous step | dsERR_NONE | Should be successful |
| 04 | Verify the obtained protocol version with the value from the configuration YAML file | protocolVersion = obtained from previous step | Ports/1/hdcp_protocol_version | Should be successful |
| 05 | Terminate the video port using dsVideoPortTerm | None | dsERR_NONE | Should be successful |

```mermaid
graph TB
    Step1[Call dsVideoPortInit API]
    Step1 -- dsERR_NONE --> Step2[Call dsGetVideoPort API with dsVIDEOPORT_TYPE_INTERNAL port]
    Step1 -- Not dsERR_NONE --> Fail1[Test Case Failed]
    Step2 -- dsERR_NONE and valid handle --> Step3[Call dsGetHDCPProtocol API and get HDCP protocol version]
    Step3 -- dsERR_NONE --> Step5[Compare the version with the value from Sink_4K_VideoPort.yaml file ]
    Step5 --> Step6[Call dsVideoPortTerm API]
    Step6 -- dsERR_NONE --> End[Test Case Passed]
    Step6 -- Not dsERR_NONE --> Fail6[Test Case Failed]
```

### Test 17

|Title|Details|
|--|--|
|Function Name|`test_l2_dsVideoPort_VerifyHDCPProtocolStatus_source`|
|Description|Check the HDCP protocol status of each port and verify it with the configuration YAML file. If it is a sink device, retrieve the value from the 'Sink_4K_VideoPort.yaml' file using the path 'Ports/1/hdcp_protocol_version' supported by INTERNAL port. For a source device, retrieve the value from the 'Source_4K_VideoPort.yaml' file using the path 'Ports/1/hdcp_protocol_version' supported by HDMI port.|
|Test Group|02|
|Test Case ID|017|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize the video port using dsVideoPortInit | None | dsERR_NONE | Should be successful |
| 02 | Get the video port handle using dsGetVideoPort with HDMI type and index 0 | type = dsVIDEOPORT_TYPE_HDMI, index = 0 | dsERR_NONE | Should be successful |
| 03 | Get the HDCP protocol version using dsGetHDCPProtocol with the obtained handle | handle = obtained from dsGetVideoPort | dsERR_NONE | Should be successful |
| 04 | Verify the HDCP protocol version with the value from the configuration YAML file | protocolVersion = value in "Ports/1/hdcp_protocol_version" | "Ports/1/hdcp_protocol_version" from YAML file | Should be successful |
| 05 | Terminate the video port using dsVideoPortTerm | None | dsERR_NONE | Should be successful |

```mermaid
graph TB
    Start(Start) --> Step1[Call dsVideoPortInit API]
    Step1 -- dsERR_NONE --> Step2[Call dsGetVideoPort API with dsVIDEOPORT_TYPE_HDMI port]
    Step1 -- Not dsERR_NONE --> Fail1[Test Case Failed]
    Step2 -- dsERR_NONE and valid handle --> Step3[Call dsGetHDCPProtocol API and get HDCP protocol version]
    Step3 -- dsERR_NONE --> Step5[Compare the version with the value from Source_4K_VideoPort.yaml file ]
    Step5 --> Step6[Call dsVideoPortTerm API]
    Step6 -- dsERR_NONE --> End[Test Case Passed]
    Step6 -- Not dsERR_NONE --> Fail6[Test Case Failed]
```

### Test 18

|Title|Details|
|--|--|
|Function Name|`test_l2_dsVideoPort_SetAndGetHdmiPreference_sink`|
|Description|Set the preferred HDCP Protocol version for each valid port and verify it using the get function.|
|Test Group|02|
|Test Case ID|018|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize the video port using dsVideoPortInit | None | dsERR_NONE | Should be successful |
| 02 | Get the video port handle using dsGetVideoPort with INTERNAL type and index 0 | type = dsVIDEOPORT_TYPE_INTERNAL, index = 0 | dsERR_NONE | Should be successful |
| 03 | Get the HDCP protocol version using dsGetHDCPProtocol with the obtained handle | handle = obtained from dsGetVideoPort | dsERR_NONE | Should be successful |
| 04 | Verify the HDCP protocol version with the value from the configuration YAML file | protocolVersion = value in "Ports/1/hdcp_protocol_version" | "Ports/1/hdcp_protocol_version" from YAML file | Should be successful |
| 05 | Terminate the video port using dsVideoPortTerm | None | dsERR_NONE | Should be successful |

```mermaid
graph TB
    A[Call dsVideoPortInit] -->|return dsERR_NONE| B[Call dsGetVideoPort] -->|return dsERR_NONE and valid handle| P{Loop through all the valid ports and protocol versions}
    A -->|Not dsERR_NONE| C[Test case fail]
    P --> D[Call dsSetHdmiPreference API]
    D -->|dsERR_NONE| F[Call dsGetHdmiPreference API] --> |Proceed to other values| P
    F --> J[Call dsVideoPortTerm API]
    J -->|dsERR_NONE| K[Test case success]
    J -->|Not dsERR_NONE| L[Test case fail]
```

### Test 19

|Title|Details|
|--|--|
|Function Name|`test_l2_dsVideoPort_SetAndGetHdmiPreference_source`|
|Description|Set the preferred HDCP Protocol version for each valid port and verify it using the get function.|
|Test Group|02|
|Test Case ID|019|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize the video port using dsVideoPortInit | None | dsERR_NONE | Should be successful |
| 02 | Get the video port handle using dsGetVideoPort with HDMI type and index 0 | type = dsVIDEOPORT_TYPE_HDMI, index = 0 | dsERR_NONE | Should be successful |
| 03 | Get the HDCP protocol version using dsGetHDCPProtocol with the obtained handle | handle = obtained from dsGetVideoPort | dsERR_NONE | Should be successful |
| 04 | Verify the HDCP protocol version with the value from the configuration YAML file | protocolVersion = value in "Ports/1/hdcp_protocol_version" | "Ports/1/hdcp_protocol_version" from YAML file | Should be successful |
| 05 | Terminate the video port using dsVideoPortTerm | None | dsERR_NONE | Should be successful |

```mermaid
graph TB
    A[Call dsVideoPortInit] -->|return dsERR_NONE| B[Call dsGetVideoPort] -->|return dsERR_NONE and valid handle| P{Loop through all the valid ports and protocol versions}
    A -->|return not dsERR_NONE| C[Test case fail]
    P --> D[Call dsSetHdmiPreference API]
    D -->|return dsERR_NONE| F[Call dsGetHdmiPreference API] --> |Proceed to other values| P
    F --> J[Call dsVideoPortTerm API]
    J -->|return dsERR_NONE| K[Test case success]
    J -->|return not dsERR_NONE| L[Test case fail]
```

### Test 20

|Title|Details|
|--|--|
|Function Name|`test_l2_dsVideoPort_GetColorSpace_sink`|
|Description|Get each port Color Space, compare with the configuration YAML file. If it is a sink device, retrieve the value from the 'Sink_4K_VideoPort.yaml' file using the path 'Ports/1/colorspaces' supported by INTERNAL port. For a source device, retrieve the value from the 'Source_4K_VideoPort.yaml' file using the path 'Ports/1/colorspaces' supported by HDMI port.|
|Test Group|02|
|Test Case ID|20|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize video port using dsVideoPortInit() | None | dsERR_NONE | Should be successful |
| 02 | Get video port handle using dsGetVideoPort() with type as dsVIDEOPORT_TYPE_INTERNAL and index as 0 | type = dsVIDEOPORT_TYPE_INTERNAL, index = 0 | dsERR_NONE | Should be successful |
| 03 | Get color space using dsGetColorSpace() with handle obtained from previous step | handle = handle obtained from step 02 | dsERR_NONE | Should be successful |
| 04 | Compare the obtained color space with the value from the configuration YAML file | color_space = value in 'Ports/1/colorspaces' | Value from the configuration YAML file | Should be successful |
| 05 | Terminate video port using dsVideoPortTerm() | None | dsERR_NONE | Should be successful |

```mermaid
graph TB
A[Call dsVideoPortInit] -->|dsERR_NONE| B[Call dsGetVideoPort with type as dsVIDEOPORT_TYPE_INTERNAL]
A -->|Not dsERR_NONE| A1[Test case fail]
B -->|dsERR_NONE and valid handle| C[Call dsGetColorSpace API]
C -->|dsERR_NONE| D[Compare color space with value from Sink_4K_VideoPort.yaml file]
D --> E[Call dsVideoPortTerm]
E -->|dsERR_NONE| F[Test case success]
E -->|dsERR_NONE| E1[Test case fail]
```

### Test 21

|Title|Details|
|--|--|
|Function Name|`test_l2_dsVideoPort_GetColorSpace_source`|
|Description|Get each port Color Space, compare with the configuration YAML file. If it is a sink device, retrieve the value from the 'Sink_4K_VideoPort.yaml' file using the path 'Ports/1/colorspaces' supported by INTERNAL port. For a source device, retrieve the value from the 'Source_4K_VideoPort.yaml' file using the path 'Ports/1/colorspaces' supported by HDMI port.|
|Test Group|02|
|Test Case ID|21|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize the video port using dsVideoPortInit() | None | dsERR_NONE | Should be successful |
| 02 | Get the video port handle using dsGetVideoPort() with type as dsVIDEOPORT_TYPE_HDMI and index as 0 | type = dsVIDEOPORT_TYPE_HDMI, index = 0 | dsERR_NONE | Should be successful |
| 03 | Get the color space using dsGetColorSpace() with the handle obtained from previous step | handle = obtained from step 02 | dsERR_NONE | Should be successful |
| 04 | Compare the obtained color space with the value from the configuration YAML file | color_space = value in 'Ports/1/colorspaces' | Value from 'Ports/1/colorspaces' in the YAML file | Should be successful |
| 05 | Terminate the video port using dsVideoPortTerm() | None | dsERR_NONE | Should be successful |

```mermaid
graph TB
A[Call dsVideoPortInit] -->|return dsERR_NONE| B[Call dsGetVideoPort with type as dsVIDEOPORT_TYPE_HDMI]
A -->|Not dsERR_NONE| A1[Test case fail]
B -->|dsERR_NONE and valid handle| C[Call dsGetColorSpace API]
C -->|dsERR_NONE| D[Compare color space with value from Source_4K_VideoPort.yaml file]
D --> E[Call dsVideoPortTerm]
E -->|dsERR_NONE| F[Test case success]
E -->|Not dsERR_NONE| E1[Test case fail]
```

### Test 22

|Title|Details|
|--|--|
|Function Name|`test_l2_dsVideoPort_CheckColorDepthCapabilities_sink`|
|Description|Check each port Color Depth Capabilities and compare with the configuration YAML file. If it is a sink device, retrieve the value from the 'Sink_4K_VideoPort.yaml' file using the path 'Ports/1/Supported_color_depth_capabilities' supported by INTERNAL port. For a source device, retrieve the value from the 'Source_4K_VideoPort.yaml' file using the path 'Ports/1/Supported_color_depth_capabilities' supported by HDMI port.|
|Test Group|02|
|Test Case ID|22|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize the video port using dsVideoPortInit | None | dsERR_NONE | Should be successful |
| 02 | Get the video port handle using dsGetVideoPort with dsVIDEOPORT_TYPE_INTERNAL and index 0 | dsVIDEOPORT_TYPE_INTERNAL, 0 | dsERR_NONE | Should be successful |
| 03 | Check the color depth capabilities using dsColorDepthCapabilities with the obtained handle | handle | dsERR_NONE | Should be successful |
| 04 | Compare the obtained color depth capability with the value from the configuration YAML file | colorDepthCapability = value in 'Ports/1/Supported_color_depth_capabilities' | Check if equal | Should be successful |
| 05 | Terminate the video port using dsVideoPortTerm | None | dsERR_NONE | Should be successful |

```mermaid
graph TB
    Start(Start) --> Step1[Call dsVideoPortInit API]
    Step1 -- "dsERR_NONE" --> Step2[Call dsGetVideoPort API with dsVIDEOPORT_TYPE_INTERNAL]
    Step1 -- "Not dsERR_NONE" --> Fail1[Test Case Failed]
    Step2 -- "dsERR_NONE and valid handle" --> Step3[Call dsColorDepthCapabilities API with handle]
    Step3 -- "dsERR_NONE" --> Step4[Compare if value retrieved from API and Sink_4K_VideoPort.yaml file matches]
    Step4 --> Step6[Call dsVideoPortTerm API]
    Step6 -- "dsERR_NONE" --> End[Test Case Passed]
    Step6 -- "Not dsERR_NONE" --> Fail6[Test Case Failed]
```

### Test 23

|Title|Details|
|--|--|
|Function Name|`test_l2_dsVideoPort_CheckColorDepthCapabilities_source`|
|Description|Check each port Color Depth Capabilities and compare with the configuration YAML file. If it is a sink device, retrieve the value from the 'Sink_4K_VideoPort.yaml' file using the path 'Ports/1/Supported_color_depth_capabilities' supported by INTERNAL port. For a source device, retrieve the value from the 'Source_4K_VideoPort.yaml' file using the path 'Ports/1/Supported_color_depth_capabilities' supported by HDMI port.|
|Test Group|02|
|Test Case ID|23|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize the video port using dsVideoPortInit | None | dsERR_NONE | Should be successful |
| 02 | Get the video port handle using dsGetVideoPort with dsVIDEOPORT_TYPE_HDMI and index 0 | dsVIDEOPORT_TYPE_HDMI, 0 | dsERR_NONE | Should be successful |
| 03 | Check the color depth capabilities using dsColorDepthCapabilities with the obtained handle | handle | dsERR_NONE | Should be successful |
| 04 | Compare the obtained color depth capability with the value from the configuration YAML file | colorDepthCapability = value in 'Ports/1/Supported_color_depth_capabilities' | Check if equal | Should be successful |
| 05 | Terminate the video port using dsVideoPortTerm | None | dsERR_NONE | Should be successful |

```mermaid
graph TB
    Start(Start) --> Step1[Call dsVideoPortInit API]
    Step1 -- "dsERR_NONE" --> Step2[Call dsGetVideoPort API with dsVIDEOPORT_TYPE_HDMI]
    Step1 -- "Not dsERR_NONE" --> Fail1[Test Case Failed]
    Step2 -- "dsERR_NONE and valid handle" --> Step3[Call dsColorDepthCapabilities API with handle]
    Step3 -- "dsERR_NONE" --> Step4[Compare if value retrieved from API and Source_4K_VideoPort.yaml file matches]
    Step4 --> Step6[Call dsVideoPortTerm API]
    Step6 -- "dsERR_NONE" --> End[Test Case Passed]
    Step6 -- "Not dsERR_NONE" --> Fail6[Test Case Failed]
```

### Test 24

|Title|Details|
|--|--|
|Function Name|`test_l2_dsVideoPort_GetColorDepth_sink`|
|Description|Get each port Color Depth and verify with the configuration YAML file. If it is a sink device, retrieve the value from the 'Sink_4K_VideoPort.yaml' file using the path 'color_depth' supported by INTERNAL port. For a source device, retrieve the value from the 'Source_4K_VideoPort.yaml' file using the path 'color_depth' supported by HDMI port.|
|Test Group|02|
|Test Case ID|24|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize the video port using dsVideoPortInit() | None | dsERR_NONE | Should be successful |
| 02 | Get the video port handle using dsGetVideoPort() with type=dsVIDEOPORT_TYPE_INTERNAL and index=0 | type=dsVIDEOPORT_TYPE_INTERNAL, index=0 | dsERR_NONE | Should be successful |
| 03 | Get the color depth using dsGetColorDepth() with the obtained handle | handle=obtained handle | dsERR_NONE | Should be successful |
| 04 | Verify the obtained color depth with the value from the configuration YAML file | color_depth=value in 'Ports/1/Supported_color_depth_capabilities'| Should be equal | Should be successful |
| 05 | Terminate the video port using dsVideoPortTerm() | None | dsERR_NONE | Should be successful |

```mermaid
graph TB
    A[Call dsVideoPortInit] -->|dsERR_NONE| B[Call dsGetVideoPort with type=dsVIDEOPORT_TYPE_INTERNAL]
    A -->|Not dsERR_NONE| A1[Test case fail]
    B -->|dsERR_NONE and valid handle| C[Call dsGetColorDepth with handle from previous step]
    C -->|dsERR_NONE| D[Compare the color depth values from API and Sink_4K_VideoPort.yaml file]
    D --> F[Call dsVideoPortTerm]
    F -->|dsERR_NONE| G[Test case success]
    F -->|Not dsERR_NONE| F1[Test case fail]
```

### Test 25

|Title|Details|
|--|--|
|Function Name|`test_l2_dsVideoPort_GetColorDepth_source`|
|Description|Get each port Color Depth and verify with the configuration YAML file. If it is a sink device, retrieve the value from the 'Sink_4K_VideoPort.yaml' file using the path 'color_depth' supported by INTERNAL port. For a source device, retrieve the value from the 'Source_4K_VideoPort.yaml' file using the path 'color_depth' supported by HDMI port.|
|Test Group|02|
|Test Case ID|25|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize the video port using dsVideoPortInit() | None | dsERR_NONE | Should be successful |
| 02 | Get the video port handle using dsGetVideoPort() with type as dsVIDEOPORT_TYPE_HDMI and index as 0 | type = dsVIDEOPORT_TYPE_HDMI, index = 0 | dsERR_NONE | Should be successful |
| 03 | Get the color depth using dsGetColorDepth() with the handle obtained from previous step | handle = obtained from step 02 | dsERR_NONE | Should be successful |
| 04 | Verify the color depth with the value from the 'Source_4K_VideoPort.yaml' file | color_depth=value in 'Ports/1/Supported_color_depth_capabilities'| Should be equal | Should be successful |
| 05 | Terminate the video port using dsVideoPortTerm() | None | dsERR_NONE | Should be successful |

```mermaid
graph TB
    A[Call dsVideoPortInit] -->|dsERR_NONE| B[Call dsGetVideoPort with type=dsVIDEOPORT_TYPE_HDMI]
    A -->|Not dsERR_NONE| A1[Test case fail]
    B -->|dsERR_NONE and valid handle| C[Call dsGetColorDepth with handle from previous step]
    C -->|dsERR_NONE| D[Compare the color depth values from API and Source_4K_VideoPort.yaml file]
    D --> F[Call dsVideoPortTerm]
    F -->|dsERR_NONE| G[Test case success]
    F -->|Not dsERR_NONE| F1[Test case fail]
```

### Test 26

|Title|Details|
|--|--|
|Function Name|`test_l2_dsVideoPort_SetAndGetPreferredColorDepth_source`|
|Description|Set preferred color depth for each port and compare get function|
|Test Group|02|
|Test Case ID|26|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize video port using dsVideoPortInit() | None | dsERR_NONE | Should be successful |
| 02 | Get video port handle for each port type using dsGetVideoPort() | type = dsVIDEOPORT_TYPE_RF to dsVIDEOPORT_TYPE_MAX, index = 0 | dsERR_NONE | Should be successful |
| 03 | Set preferred color depth for each color depth type using dsSetPreferredColorDepth() | handle = from step 02, colorDepthSet = dsDISPLAY_COLORDEPTH_8BIT to dsDISPLAY_COLORDEPTH_AUTO | dsERR_NONE | Should be successful |
| 04 | Get preferred color depth using dsGetPreferredColorDepth() | handle = from step 02, colorDepthGet | dsERR_NONE | Should be successful |
| 05 | Compare set and get color depth | colorDepthSet = colorDepthGet | colorDepthSet should be equal to colorDepthGet | Should be successful |
| 06 | Terminate video port using dsVideoPortTerm() | None | dsERR_NONE | Should be successful |

```mermaid
graph TB
    Step1[Call dsVideoPortInit API]
    Step1 --> Step{Loop through all possible ports and color depths} -->  Step2[Call dsGetVideoPort API]
    Step1 -->|Failure| TestcaseFail1[Testcase Fail]
    Step2 -->|dsERR_NONE and valid handle| Step3[Call dsSetPreferredColorDepth API]
    Step3 -->|dsERR_NONE| Step4[Call dsGetPreferredColorDepth API]
    Step4 -->|dsERR_NONE| Step5[Compare color depth values] --> |Continue to next set of values| Step
    Step5 -->|End of Iteration| Step7[Call dsVideoPortTerm API]
    Step7 -->|dsERR_NONE| End(End)
    Step7 -->|Failure| TestcaseFail6[Testcase Fail]
```

### Test 27

|Title|Details|
|--|--|
|Function Name|`test_l2_dsVideoPort_GetQuantizationRange_sink`|
|Description|Get each port QuantizationRange status and verify with the configuration YAML file. If it is a sink device, retrieve the value from the 'Sink_4K_VideoPort.yaml' file using the path 'Ports/1/quantization_ranges' supported only by INTERNAL port. For a source device, retrieve the value from the 'Source_4K_VideoPort.yaml' file using the path 'Ports/1/quantization_ranges' supported by HDMI port.|
|Test Group|02|
|Test Case ID|27|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize the video port using dsVideoPortInit() | None | dsERR_NONE | Should be successful |
| 02 | Get the video port handle using dsGetVideoPort() with dsVIDEOPORT_TYPE_INTERNAL as type and 0 as index | type = dsVIDEOPORT_TYPE_INTERNAL, index = 0 | dsERR_NONE | Should be successful |
| 03 | Get the Quantization Range using dsGetQuantizationRange() with the handle obtained from previous step | handle = obtained from step 02 | dsERR_NONE | Should be successful |
| 04 | Verify the Quantization Range with the value from the configuration YAML file | quantization_range = value in "Ports/1/quantization_ranges" | Should be equal | Should be successful |
| 05 | Terminate the video port using dsVideoPortTerm() | None | dsERR_NONE | Should be successful |

```mermaid
graph TB
    Start(Start) --> Step1[Call dsVideoPortInit]
    Step1 -- dsERR_NONE --> Step2[Call dsGetVideoPort with dsVIDEOPORT_TYPE_INTERNAL port]
    Step1 -- Not dsERR_NONE --> TestcaseFail1[Test case fail]
    Step2 -- dsERR_NONE and valid handle --> Step3[Call dsGetQuantizationRange with handle]
    Step3 -- dsERR_NONE and valid quantization range --> Step4[Compare quantization range with Sink_4K_VideoPort.yaml]
    Step4  --> Step5[Call dsVideoPortTerm]
    Step5 -- dsERR_NONE --> End[Test case success]
    Step5 -- Not dsERR_NONE --> TestcaseFail5[Test case fail]
```

### Test 28

|Title|Details|
|--|--|
|Function Name|`test_l2_dsVideoPort_GetQuantizationRange_source`|
|Description|Get each port QuantizationRange status and verify with the configuration YAML file. If it is a sink device, retrieve the value from the 'Sink_4K_VideoPort.yaml' file using the path 'Ports/1/quantization_ranges' supported only by INTERNAL port. For a source device, retrieve the value from the 'Source_4K_VideoPort.yaml' file using the path 'Ports/1/quantization_ranges' supported by HDMI port.|
|Test Group|02|
|Test Case ID|28|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize the video port using dsVideoPortInit() | None | dsERR_NONE | Should be successful |
| 02 | Get the video port handle using dsGetVideoPort() with dsVIDEOPORT_TYPE_HDMI as type and 0 as index | type = dsVIDEOPORT_TYPE_HDMI, index = 0 | dsERR_NONE | Should be successful |
| 03 | Get the Quantization Range using dsGetQuantizationRange() with the handle obtained from dsGetVideoPort() | handle = obtained from dsGetVideoPort() | dsERR_NONE | Should be successful |
| 04 | Verify the Quantization Range with the value from the configuration YAML file | quantization_range = quantization_range = value in "Ports/1/quantization_ranges" | Should be equal | Should be successful |
| 05 | Terminate the video port using dsVideoPortTerm() | None | dsERR_NONE | Should be successful |

```mermaid
graph TB
    Start(Start) --> Step1[Call dsVideoPortInit]
    Step1 -- dsERR_NONE --> Step2[Call dsGetVideoPort with dsVIDEOPORT_TYPE_HDMI port]
    Step1 -- Not dsERR_NONE --> TestcaseFail1[Test case fail]
    Step2 -- dsERR_NONE and valid handle --> Step3[Call dsGetQuantizationRange with handle]
    Step3 -- dsERR_NONE and valid quantization range --> Step4[Compare quantization range with Source_4K_VideoPort.yaml]
    Step4  --> Step5[Call dsVideoPortTerm]
    Step5 -- dsERR_NONE --> End[Test case success]
    Step5 -- Not dsERR_NONE --> TestcaseFail5[Test case fail]
```

### Test 29

|Title|Details|
|--|--|
|Function Name|`test_l2_dsVideoPort_GetMatrixCoefficients_sink`|
|Description|Get each port MatrixCoefficients status and verify return dsDISPLAY_MATRIXCOEFFICIENT_UNKNOWN for source and with the configuration YAML file. If it is a sink device, retrieve the value from the 'Sink_4K_VideoPort.yaml' file using the path 'Ports/1/matrix_coefficients' supported only by INTERNAL port. For a source device, retrieve the value from the 'Source_4K_VideoPort.yaml' file using the path 'Ports/1/matrix_coefficients' supported by HDMI port.|
|Test Group|02|
|Test Case ID|29|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize the video port using dsVideoPortInit | None | dsERR_NONE | Should be successful |
| 02 | Get the video port with type=dsVIDEOPORT_TYPE_INTERNAL and index=1 using dsGetVideoPort | type=dsVIDEOPORT_TYPE_INTERNAL, index=1 | dsERR_NONE | Should be successful |
| 03 | Get the Matrix Coefficients with handle obtained from dsGetVideoPort using dsGetMatrixCoefficients | handle=handle obtained from dsGetVideoPort | dsERR_NONE | Should be successful |
| 04 | Verify the Matrix Coefficients with the value from the configuration YAML file | matrix_coefficients='Ports/1/matrix_coefficients'| Should be equal | Should be successful |
| 05 | Terminate the video port using dsVideoPortTerm | None | dsERR_NONE | Should be successful |

```mermaid
graph TB
    Step1[Call dsVideoPortInit]
    Step1 -- dsERR_NONE --> Step2[Call dsGetVideoPort with type=dsVIDEOPORT_TYPE_INTERNAL]
    Step1 -- Not dsERR_NONE --> Fail1[Test Case Fail]
    Step2 -- dsERR_NONE and valid handle --> Step3[Call dsGetMatrixCoefficients with handle]
    Step3 -- dsERR_NONE --> Step4[Compare the retrieved matrix_coefficients with value from Sink_4K_VideoPort.yaml file]
    Step4 --> Step6[Call dsVideoPortTerm]
    Step6 -- dsERR_NONE --> End[Test Case Success]
    Step6 -- Not dsERR_NONE --> Fail6[Test Case Fail]
```

### Test 30

|Title|Details|
|--|--|
|Function Name|`test_l2_dsVideoPort_GetMatrixCoefficients_source`|
|Description|Get each port MatrixCoefficients status and verify return dsDISPLAY_MATRIXCOEFFICIENT_UNKNOWN for source and with the configuration YAML file. If it is a sink device, retrieve the value from the 'Sink_4K_VideoPort.yaml' file using the path 'Ports/1/matrix_coefficients' supported only by INTERNAL port. For a source device, retrieve the value from the 'Source_4K_VideoPort.yaml' file using the path 'Ports/1/matrix_coefficients' supported by HDMI port.|
|Test Group|02|
|Test Case ID|30|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

**Test Procedure :**

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize the video port using dsVideoPortInit() | None | dsERR_NONE | Should be successful |
| 02 | Get the video port handle using dsGetVideoPort() with type as dsVIDEOPORT_TYPE_HDMI and index as 1 | type = dsVIDEOPORT_TYPE_HDMI, index = 1 | dsERR_NONE | Should be successful |
| 03 | Get the Matrix Coefficients using dsGetMatrixCoefficients() with the handle obtained from previous step | handle = obtained from step 02 | dsDISPLAY_MATRIXCOEFFICIENT_UNKNOWN | Should be successful |
| 04 | Verify the Matrix Coefficients with the value from the configuration YAML file | matrix_coefficients='Ports/1/matrix_coefficients'| Should be equal  | Should be successful |
| 05 | Terminate the video port using dsVideoPortTerm() | None | dsERR_NONE | Should be successful |

```mermaid
graph TB
    Step1[Call dsVideoPortInit]
    Step1 -- dsERR_NONE --> Step2[Call dsGetVideoPort with type=dsVIDEOPORT_TYPE_HDMI]
    Step1 -- Not dsERR_NONE --> Fail1[Test Case Fail]
    Step2 -- dsERR_NONE and valid handle --> Step3[Call dsGetMatrixCoefficients with handle]
    Step3 -- dsERR_NONE --> Step4[Verify matrix_coefficients value is dsDISPLAY_MATRIXCOEFFICIENT_UNKNOWN]
    Step4 -- dsERR_NONE --> Step5[Compare the retrieved matrix_coefficients with value from Source_4K_VideoPort.yaml file]
    Step5 -- dsERR_NONE --> Step6[Call dsVideoPortTerm]
    Step6 -- dsERR_NONE --> End[Test Case Success]
    Step6 -- Not dsERR_NONE --> Fail6[Test Case Fail]
```
