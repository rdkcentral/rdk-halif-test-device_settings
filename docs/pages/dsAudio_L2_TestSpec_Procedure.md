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
  - [Test `MS12` `DAP` Volume leveller](#test-ms12-dap-volume-leveller)
  - [Test `MS12` `DAP` Bass Enhancer](#test-ms12-dap-bass-enhancer)
  - [Test `MS12` `DAP` Surround Encoder](#test-ms12-dap-surround-encoder)
  - [Test `MS12` `DAP` `DRC` Mode](#test-ms12-dap-drc-mode)
  - [Test `MS12` `DAP` Surround Virtualizer](#test-ms12-dap-surround-virtualizer)
  - [Test `MS12` `DAP` `MI` Steering](#test-ms12-dap-mi-steering)
  - [Test `MS12` `DAP` Graphic Equalizer mode](#test-ms12-dap-graphic-equalizer-mode)
  - [Test `MS12` `DAP` `LE` Configuration](#test-ms12-dap-le-configuration)


## Overview

This document describes the Level 2 Test Specification and Procedure for the Audio device settings module.

Interface of the test is available here: [Audio Settings HAL header](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsAudio.h)

### Acronyms, Terms and Abbreviations

- `HAL`    - Hardware Abstraction Layer
- `API`    - Application Programming Interface
- `L2`     - Level 2 Testing
- `L3`     - Level 3 Testing
- `NA`     - Not Applicable
- `Y`      - Yes
- `DS`     - Device Settings
- `Caller` - Any user of the interface via the `APIs`
- `CB`     - Call-back function (suffix)
- `ARC`    - Audio Return Channel
- `eARC`   - Enhanced Audio Return Channel
- `SAD`    - Short Audio Descriptor
- `SPDIF`  - Sony/Philips Digital Interface
- `HDMI`   - High-Definition Multimedia Interface
- `LE`     - Loudness Equivalence
- `DRC`    - Dynamic Range Control
- `MI`     - Media Intelligent
- `RF`     - Radio Frequency
- `dB`     - Decibel
- `MS12`   - MultiStream 12
- `AC4`    - Audio Compression 4
- `PCM`    - Pulse Code Modulation
- `AC3`    - Audio Codec 3
- `EAC3`   - Enhanced `AC3`
- `ms`     - milliseconds
- `CPU`    - Central Processing Unit
- `SoC`    - System-on-Chip
- `RCA`    - Radio Corporation of America
- `WMA`    - Windows Media Audio
- `AAC`    - Advanced Audio coding
- `DD`     - DOLBY Digital
- `DDPLUS` - DOLBY Digital Plus
- `DAP`    - Digital Audio Processing

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
|03|Call `dsSetDolbyVolumeMode()` by looping through the acquired supported port handles and set the mode as TRUE|`NA`|dsERR_NONE|
|04|Call `dsGetDolbyVolumeMode()` by looping through the acquired port handles and valid pointer to get the Dolby Volume mode of each port|`NA`|dsERR_NONE|
|05|Validate the dolby volume mode|Compare dolby volume mode set in step 03 with the values retrieved in step 04|dolby volume mode status should be TRUE|
|06|Call `dsSetDolbyVolumeMode()` by looping through the acquired supported port handles and set the mode as FALSE|`NA`|dsERR_NONE|
|07|Call `dsGetDolbyVolumeMode()` by looping through the acquired port handles and valid pointer to get the Dolby Volume mode of each port|`NA`|dsERR_NONE|
|08|Validate the dolby volume mode|Compare dolby volume mode set in step 06 with the values retrieved in step 07|dolby volume mode status should be FALSE|
|09|Call `dsAudioPortTerm()` to terminate audio ports|`NA`|dsERR_NONE|

### Test `MS12` `DAP` Intelligent Equalizer Mode

|Title|Details|
|-----|-------|
|Function Name|`L2_dsAudio_MS12DAP_intelligent_equalizer_mode`|
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
|05|Validate the Intelligent Equalizer Mode|Compare Intelligent Equalizer Mode set in step 03 with the values retrieved in step 04|Intelligent Equalizer Mode values should match|
|06|Repeat step 03 to step 05 for various values of Intelligent Equalizer Modes (Modes: 0 = OFF, 1 = Open, 2 = Rich, 3 = Focused, 4 = Balanced, 5 = Warm, 6 = Detailed)|`NA`|`NA`|
|07|Call `dsAudioPortTerm()` to terminate audio ports|`NA`|dsERR_NONE|

### Test `MS12` `DAP` Volume leveller

|Title|Details|
|-----|-------|
|Function Name|`L2_dsAudio_MS12DAP_volume_leveller`|
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
|05|Validate the Volume leveller|Compare Volume leveller set in step 03 with the values retrieved in step 04|Volume leveller values should match|
|06|Repeat step 03 to step 05 for various values of Volume leveller (the range of mode is [0,1,2] and range of level is [0 to 10])|`NA`|`NA`|
|07|Call `dsAudioPortTerm()` to terminate audio ports|`NA`|dsERR_NONE|

### Test `MS12` `DAP` Bass Enhancer

|Title|Details|
|-----|-------|
|Function Name|`L2_dsAudio_MS12DAP_bass_enhancer`|
|Description|Set the `MS12` `DAP` Bass Enhancer and get the same for verification|
|Test ID| 02 (Advanced) |
|Priority| High |

**Pre-Conditions :** None

**Dependencies :** None

**User Interaction :** None

|Variation / Steps|Description|Test Data|Expected Result|
|-----------------|-----------|---------|---------------|
|01|Call `dsAudioPortInit()` to open interface|`NA`|dsERR_NONE|
|02|Call `dsGetAudioPort()` to get the audio port handles for valid audio port type and valid index which supports `MS12`|Valid handle|dsERR_NONE|
|03|Call `dsSetBassEnhancer()` by looping through the acquired port handles and set the Bass Enhancer for each port|`NA`|dsERR_NONE|
|04|Call `dsGetBassEnhancer()` by looping through the acquired port handles to get the Bass Enhancer of each port|`NA`|dsERR_NONE|
|05|Validate the Bass Enhancer|Compare Bass Enhancer set in step 03 with the values retrieved in step 04|Bass Enhancer values should match|
|06|Repeat step 03 to step 05 for various values of Bass Enhancer (ranging from 0 to 100)|`NA`|`NA`|
|07|Call `dsAudioPortTerm()` to terminate audio ports|`NA`|dsERR_NONE|

### Test `MS12` `DAP` Surround Encoder

|Title|Details|
|-----|-------|
|Function Name|`L2_dsAudio_MS12DAP_surround_encoder`|
|Description|Set the `MS12` `DAP` Surround Encoder and get the same for verification|
|Test ID| 02 (Advanced) |
|Priority| High |

**Pre-Conditions :** None

**Dependencies :** None

**User Interaction :** None

|Variation / Steps|Description|Test Data|Expected Result|
|-----------------|-----------|---------|---------------|
|01|Call `dsAudioPortInit()` to open interface|`NA`|dsERR_NONE|
|02|Call `dsGetAudioPort()` to get the audio port handles for valid audio port type and valid index which supports `MS12`|Valid handle|dsERR_NONE|
|03|Call `dsEnableSurroundDecoder()` by looping through the acquired port handles and Enable Surround Encoder for each port|`NA`|dsERR_NONE|
|04|Call `dsIsSurroundDecoderEnabled()` by looping through the acquired port handles to get the Surround Encoder of each port|`NA`|dsERR_NONE|
|05|Validate the Surround Encoder|Compare Surround Encoder set in step 03 with the values retrieved in step 04|Surround Encoder status should be enabled|
|06|Call `dsEnableSurroundDecoder()` by looping through the acquired port handles and disable Surround Encoder for each port|`NA`|dsERR_NONE|
|07|Call `dsIsSurroundDecoderEnabled()` by looping through the acquired port handles to get the Surround Encoder of each port|`NA`|dsERR_NONE|
|08|Validate the Surround Encoder|Compare Surround Encoder set in step 06 with the values retrieved in step 07|Surround Encoder status should be disabled|
|09|Call `dsAudioPortTerm()` to terminate audio ports|`NA`|dsERR_NONE|

### Test `MS12` `DAP` `DRC` Mode

|Title|Details|
|-----|-------|
|Function Name|`L2_dsAudio_MS12DAP_drc_mode`|
|Description|Set the `MS12` `DAP` `DRC` Mode and get the same for verification|
|Test ID| 02 (Advanced) |
|Priority| High |

**Pre-Conditions :** None

**Dependencies :** None

**User Interaction :** None

|Variation / Steps|Description|Test Data|Expected Result|
|-----------------|-----------|---------|---------------|
|01|Call `dsAudioPortInit()` to open interface|`NA`|dsERR_NONE|
|02|Call `dsGetAudioPort()` to get the audio port handles for valid audio port type and valid index which supports `MS12`|Valid handle|dsERR_NONE|
|03|Call `dsSetDRCMode()` by looping through the acquired port handles and set `DRC` Mode 0 -`DRC` line mode |`NA`|dsERR_NONE|
|04|Call `dsGetDRCMode()` by looping through the acquired port handles to get the `DRC` Mode of each port|`NA`|dsERR_NONE|
|05|Validate the `DRC` Mode|Compare `DRC` Mode set in step 03 with the values retrieved in step 04|`DRC` Mode should be 0 - `DRC` line mode|
|06|Call `dsSetDRCMode()` by looping through the acquired port handles and set `DRC` Mode 1 -`DRC` RF mode |`NA`|dsERR_NONE|
|07|Call `dsGetDRCMode()` by looping through the acquired port handles to get the `DRC` Mode of each port|`NA`|dsERR_NONE|
|08|Validate the `DRC` Mode|Compare `DRC` Mode set in step 06 with the values retrieved in step 07|`DRC` Mode should be 1 - `DRC` RF mode|
|09|Call `dsAudioPortTerm()` to terminate audio ports|`NA`|dsERR_NONE|

### Test `MS12` `DAP` Surround Virtualizer

|Title|Details|
|-----|-------|
|Function Name|`L2_dsAudio_MS12DAP_surround_virtualizer`|
|Description|Set the `MS12` `DAP` Surround Virtualizer and get the same for verification|
|Test ID| 02 (Advanced) |
|Priority| High |

**Pre-Conditions :** None

**Dependencies :** None

**User Interaction :** None

|Variation / Steps|Description|Test Data|Expected Result|
|-----------------|-----------|---------|---------------|
|01|Call `dsAudioPortInit()` to open interface|`NA`|dsERR_NONE|
|02|Call `dsGetAudioPort()` to get the audio port handles for valid audio port type and valid index which supports `MS12`|Valid handle|dsERR_NONE|
|03|Call `dsSetSurroundVirtualizer()` by looping through the acquired port handles and set the Surround Virtualizer for each port|`NA`|dsERR_NONE|
|04|Call `dsGetSurroundVirtualizer()` by looping through the acquired port handles to get the Surround Virtualizer of each port|`NA`|dsERR_NONE|
|05|Validate the Surround Virtualizer|Compare Surround Virtualizer set in step 03 with the values retrieved in step 04|Surround Virtualizer values should match|
|06|Repeat step 03 to step 05 for various values of Surround Virtualizer (mode [0 = off, 1 = on, 2 = auto] and boost [0 to 96])|`NA`|`NA`|
|07|Call `dsAudioPortTerm()` to terminate audio ports|`NA`|dsERR_NONE|

### Test `MS12` `DAP` `MI` Steering

|Title|Details|
|-----|-------|
|Function Name|`L2_dsAudio_MS12DAP_mi_steering`|
|Description|Set the `MS12` `DAP` `MI` Steering and get the same for verification|
|Test ID| 02 (Advanced) |
|Priority| High |

**Pre-Conditions :** None

**Dependencies :** None

**User Interaction :** None

|Variation / Steps|Description|Test Data|Expected Result|
|-----------------|-----------|---------|---------------|
|01|Call `dsAudioPortInit()` to open interface|`NA`|dsERR_NONE|
|02|Call `dsGetAudioPort()` to get the audio port handles for valid audio port type and valid index which supports `MS12`|Valid handle|dsERR_NONE|
|03|Call `dsSetMISteering()` by looping through the acquired port handles and enable `MI` Steering mode|`NA`|dsERR_NONE|
|04|Call `dsGetMISteering()` by looping through the acquired port handles to get the `MI` Steering mode of each port|`NA`|dsERR_NONE|
|05|Validate the `MI` Steering|Compare `MI` Steering set in step 03 with the status retrieved in step 04|`MI` Steering mode should be enabled|
|06|Call `dsSetMISteering()` by looping through the acquired port handles and disable `MI` Steering mode |`NA`|dsERR_NONE|
|07|Call `dsGetMISteering()` by looping through the acquired port handles to get the `MI` Steering mode of each port|`NA`|dsERR_NONE|
|08|Validate the `MI` Steering|Compare `MI` Steering set in step 06 with the status retrieved in step 07|`MI` Steering mode should be enabled|
|09|Call `dsAudioPortTerm()` to terminate audio ports|`NA`|dsERR_NONE|

### Test `MS12` `DAP` Graphic Equalizer mode

|Title|Details|
|-----|-------|
|Function Name|`L2_dsAudio_MS12DAP_graphic_equalizer`|
|Description|Set the `MS12` `DAP` Graphic Equalizer mode and get the same for verification|
|Test ID| 02 (Advanced) |
|Priority| High |

**Pre-Conditions :** None

**Dependencies :** None

**User Interaction :** None

|Variation / Steps|Description|Test Data|Expected Result|
|-----------------|-----------|---------|---------------|
|01|Call `dsAudioPortInit()` to open interface|`NA`|dsERR_NONE|
|02|Call `dsGetAudioPort()` to get the audio port handles for valid audio port type and valid index which supports `MS12`|Valid handle|dsERR_NONE|
|03|Call `dsSetGraphicEqualizerMode()` by looping through the acquired port handles and set the Graphic Equalizer mode for each port|`NA`|dsERR_NONE|
|04|Call `dsGetGraphicEqualizerMode()` by looping through the acquired port handles to get the Graphic Equalizer mode of each port|`NA`|dsERR_NONE|
|05|Validate the Graphic Equalizer mode|Compare Graphic Equalizer mode set in step 03 with the values retrieved in step 04|Graphic Equalizer mode values should match|
|06|Repeat step 03 to step 05 for various values of Graphic Equalizer mode (0 = EQ OFF, 1 = EQ Open, 2 = EQ Rich and 3 = EQ Focused)|`NA`|`NA`|
|07|Call `dsAudioPortTerm()` to terminate audio ports|`NA`|dsERR_NONE|

### Test `MS12` `DAP` `LE` Configuration

|Title|Details|
|-----|-------|
|Function Name|`L2_dsAudio_MS12DAP_le_configuration`|
|Description|Set the `MS12` `DAP` `LE` configuration and get the same for verification|
|Test ID| 02 (Advanced) |
|Priority| High |

**Pre-Conditions :** None

**Dependencies :** None

**User Interaction :** None

|Variation / Steps|Description|Test Data|Expected Result|
|-----------------|-----------|---------|---------------|
|01|Call `dsAudioPortInit()` to open interface|`NA`|dsERR_NONE|
|02|Call `dsGetAudioPort()` to get the audio port handles for valid audio port type and valid index which supports `MS12`|Valid handle|dsERR_NONE|
|03|Call `dsEnableLEConfig()` by looping through the acquired port handles and enable `LE` configuration|`NA`|dsERR_NONE|
|04|Call `dsGetLEConfig()` by looping through the acquired port handles to get the `LE` configuration of each port|`NA`|dsERR_NONE|
|05|Validate the `LE` configuration|Compare `LE` configuration set in step 03 with the status retrieved in step 04|`LE` configuration should be enabled|
|06|Call `dsEnableLEConfig()` by looping through the acquired port handles and disable `LE` configuration |`NA`|dsERR_NONE|
|07|Call `dsGetLEConfig()` by looping through the acquired port handles to get the `LE` configuration of each port|`NA`|dsERR_NONE|
|08|Validate the `LE` configuration|Compare `LE` configuration set in step 06 with the status retrieved in step 07|`LE` configuration should be enabled|
|09|Call `dsAudioPortTerm()` to terminate audio ports|`NA`|dsERR_NONE|