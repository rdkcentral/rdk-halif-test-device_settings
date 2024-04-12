# L2 Test Specification and Procedure Document

## Version History

| Date(DD/MM/YY) | Comment       | Version |
| -------------- | ------------- | ------- |
| 12/04/24       | First Release | 1.0.0   |

## Table of Contents

- [Overview](#overview)
- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Level 2 Test Specification](#level-2-test-specification)
- [Level 2 Test Procedure](#level-2-test-procedure)
  - [Test `MS12` `DAP` Compression levels](#test-ms12-dap-compression-levels)
  - [Test `MS12` `DAP` Dialog Enhancement](#test-ms12-dap-dialog-enhancement)
  - [Test `MS12` `DAP` Dolby Volume Mode](#test-ms12-dap-dolby-volume-mode)
  - [Test `MS12` `DAP` Intelligent Equalizer Mode](#test-ms12-dap-intelligent-equalizer-mode)


## Overview

This document describes the Level 2 Test Specification and Procedure for the Audio device settings module.

Interface of the test is available here: [Audio Settings HAL header](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsAudio.h)

### Acronyms, Terms and Abbreviations

- `HAL`    - Hardware Abstraction Layer
- `UT`     - Unit Test(s)
- `MS12`   - MultiStream 12
- `DAP`    - Digital Audio Processing
- `NA`     - Not Applicable

## Level 2 Test Specification

The following test case are defined based on profile configuration :

|#|Test Functionality|Description|Goal|
|-|------------------|-----------|----|
|1|[Test `MS12` `DAP` Compression levels](#test-ms12-dap-compression-levels)|Set the `MS12` `DAP` Audio compression levels and get the same for verification|No errors|

## Level 2 Test Procedure

### Test `MS12` `DAP` Compression levels

|Title|Details|
|-----|-------|
|Function Name|`L2_dsAudio_MS12DAP_compression_level`|
|Description|Set the `MS12` `DAP` Audio compression levels and get the same for verification|
|Test ID| 02 (Advanced) |
|Priority| High |

**Pre-Conditions :** None

**Dependencies :** None

**User Interaction :** None

|Variation / Steps|Description|Test Data|Expected Result|
|-----------------|-----------|---------|---------------|
|01|Call `dsAudioPortInit()` to open interface|`NA`|dsERR_NONE|
|02|Call `dsGetAudioPort()` to get the audio port handles for valid audio port type and valid index which supports `MS12`|Valid handle|dsERR_NONE|
|03|Call `dsSetAudioCompression()` by looping through the acquired port handles and set the audio compression level for each port|`NA`|dsERR_NONE|
|04|Call `dsGetAudioCompression()` by looping through the acquired port handles to get the audio compression level of each port|`NA`|dsERR_NONE|
|05|Validate the compression levels|Compare compression levels set in step 03 with the values retrieved in step 04|Compression values should match|
|06|Repeat step 03 to step 05 for various values of compression levels (compression level ranges from 0 to 10)|`NA`|`NA`|
|07|Call `dsAudioPortTerm()` to terminate audio ports|`NA`|dsERR_NONE|

### Test `MS12` `DAP` Dialog Enhancement

|Title|Details|
|-----|-------|
|Function Name|`L2_dsAudio_MS12DAP_dialog_enhancement`|
|Description|Set the `MS12` `DAP` Dialog Enhancement and get the same for verification|
|Test ID| 02 (Advanced) |
|Priority| High |

**Pre-Conditions :** None

**Dependencies :** None

**User Interaction :** None

|Variation / Steps|Description|Test Data|Expected Result|
|-----------------|-----------|---------|---------------|
|01|Call `dsAudioPortInit()` to open interface|`NA`|dsERR_NONE|
|02|Call `dsGetAudioPort()` to get the audio port handles for valid audio port type and valid index which supports `MS12`|Valid handle|dsERR_NONE|
|03|Call `dsSetDialogEnhancement()` by looping through the acquired port handles to set the dialog enhancement levels for each port|`NA`|dsERR_NONE|
|04|Call `dsGetDialogEnhancement()` by looping through the acquired port handles to get the dialog enhancement levels for each port|`NA`|dsERR_NONE|
|05|Validate the dialog enhancement levels|Compare dialog enhancement levels set in step 03 with the values retrieved in step 04|dialog enhancement levels should match|
|06|Repeat step 03 to step 05 for various values of dialog enhancement levels (dialog enhancement levels ranges from 0 to 16)|`NA`|`NA`|
|07|Call `dsAudioPortTerm()` to terminate audio ports|`NA`|dsERR_NONE|

### Test `MS12` `DAP` Dolby Volume Mode

|Title|Details|
|-----|-------|
|Function Name|`L2_dsAudio_MS12DAP_dolby_volume_mode`|
|Description|Set the `MS12` `DAP` Dolby Volume Mode and get the same for verification|
|Test ID| 02 (Advanced) |
|Priority| High |

**Pre-Conditions :** None

**Dependencies :** None

**User Interaction :** None

|Variation / Steps|Description|Test Data|Expected Result|
|-----------------|-----------|---------|---------------|
|01|Call `dsAudioPortInit()` to open interface|`NA`|dsERR_NONE|
|02|Call `dsGetAudioPort()` to get the audio port handles for valid audio port type and valid index which supports `MS12`|Valid handle|dsERR_NONE|
|03|Call `dsSetDolbyVolumeMode()` by looping through the acquired supported port handles and valid modes(i.e TRUE or FALSE)|`NA`|dsERR_NONE|
|04|Call `dsGetDolbyVolumeMode()` by looping through the acquired port handles and valid pointer to get the Dolby Volume mode of each port|`NA`|dsERR_NONE|
|05|Validate the dolby volume mode|Compare dolby volume mode set in step 03 with the values retrieved in step 04|dolby volume mode should match|
|06|Call `dsAudioPortTerm()` to terminate audio ports|`NA`|dsERR_NONE|

### Test `MS12` `DAP` Intelligent Equalizer Mode

|Title|Details|
|-----|-------|
|Function Name|`L2_dsAudio_MS12DAP_compression_level`|
|Description|Set the `MS12` `DAP` Audio Intelligent Equalizer Mode and get the same for verification|
|Test ID| 02 (Advanced) |
|Priority| High |

**Pre-Conditions :** None

**Dependencies :** None

**User Interaction :** None

|Variation / Steps|Description|Test Data|Expected Result|
|-----------------|-----------|---------|---------------|
|01|Call `dsAudioPortInit()` to open interface|`NA`|dsERR_NONE|
|02|Call `dsGetAudioPort()` to get the audio port handles for valid audio port type and valid index which supports `MS12`|Valid handle|dsERR_NONE|
|03|Call `dsSetAudioCompression()` by looping through the acquired port handles and set the Intelligent Equalizer Modes for each port|`NA`|dsERR_NONE|
|04|Call `dsGetAudioCompression()` by looping through the acquired port handles to get the Intelligent Equalizer Modes of each port|`NA`|dsERR_NONE|
|05|Validate the Intelligent Equalizer Mode|Compare Intelligent Equalizer Mode set in step 03 with the values retrieved in step 04|Compression values should match|
|06|Repeat step 03 to step 05 for various values of Intelligent Equalizer Modes (Modes: 0 = OFF, 1 = Open, 2 = Rich, 3 = Focused, 4 = Balanced, 5 = Warm, 6 = Detailed)|`NA`|`NA`|
|07|Call `dsAudioPortTerm()` to terminate audio ports|`NA`|dsERR_NONE|

### Test `MS12` `DAP` Volume leveller

|Title|Details|
|-----|-------|
|Function Name|`L2_dsAudio_MS12DAP_compression_level`|
|Description|Set the `MS12` `DAP` Volume leveller and get the same for verification|
|Test ID| 02 (Advanced) |
|Priority| High |

**Pre-Conditions :** None

**Dependencies :** None

**User Interaction :** None

|Variation / Steps|Description|Test Data|Expected Result|
|-----------------|-----------|---------|---------------|
|01|Call `dsAudioPortInit()` to open interface|`NA`|dsERR_NONE|
|02|Call `dsGetAudioPort()` to get the audio port handles for valid audio port type and valid index which supports `MS12`|Valid handle|dsERR_NONE|
|03|Call `dsSetVolumeLeveller()` by looping through the acquired port handles and set the Volume leveller for each port|`NA`|dsERR_NONE|
|04|Call `dsGetVolumeLeveller()` by looping through the acquired port handles to get the Volume leveller of each port|`NA`|dsERR_NONE|
|05|Validate the Volume leveller|Compare Volume leveller set in step 03 with the values retrieved in step 04|Compression values should match|
|06|Repeat step 03 to step 05 for various values of Volume leveller (the range of mode is (0,1,2) and range of level is (0 to 10)|`NA`|`NA`|
|07|Call `dsAudioPortTerm()` to terminate audio ports|`NA`|dsERR_NONE|
