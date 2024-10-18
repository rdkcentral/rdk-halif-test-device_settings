# dsAudio HAL L3 Python Test Procedure

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Setting Up Test Environment](#setting-up-test-environment)
- [Streams Required](#streams-required)
- [Test Setup Connections](#test-setup-connections)
- [Test Cases](#test-cases)
  - [dsaudio_test01_enabledisableandverifyaudioportstatus.py](#dsaudio_test01_enabledisableandverifyaudioportstatuspy)
  - [dsaudio_test02_portconnectionstatus.py](#dsaudio_test02_portconnectionstatuspy)
  - [dsaudio_test03_ms12audiocompression.py](#dsaudio_test03_ms12audiocompressionpy)
  - [dsaudio_test04_ms12dialogueenhancer.py](#dsaudio_test04_ms12dialogueenhancerpy)
  - [dsaudio_test05_ms12dolbyvolume.py](#dsaudio_test05_ms12dolbyvolumepy)
  - [dsaudio_test06_ms12intelligentequalizer.py](#dsaudio_test06_ms12intelligentequalizerpy)
  - [dsaudio_test07_ms12volumeleveller.py](#dsaudio_test07_ms12volumelevellerpy)
  - [dsaudio_test08_ms12bassenhancer.py](#dsaudio_test08_ms12bassenhancerpy)
  - [dsaudio_test09_ms12surrounddecoder.py](#dsaudio_test09_ms12surrounddecoderpy)
  - [dsaudio_test10_ms12drcmode.py](#dsaudio_test10_ms12drcmodepy)
  - [dsaudio_test11_ms12surroundvirtualizer.py](#dsaudio_test11_ms12surroundvirtualizerpy)
  - [dsaudio_test12_ms12misteering.py](#dsaudio_test12_ms12misteeringpy)
  - [dsaudio_test13_ms12graphicequalizer.py](#dsaudio_test13_ms12graphicequalizerpy)
  - [dsaudio_test14_ms12leconfig.py](#dsaudio_test14_ms12leconfigpy)
  - [dsaudio_test15_arcport.py](#dsaudio_test15_arcportpy)
  - [dsaudio_test16_arcsad.py](#dsaudio_test16_arcsadpy)
  - [dsaudio_test17_outputmode.py](#dsaudio_test17_outputmodepy)
  - [dsaudio_test18_audiolevel.py](#dsaudio_test18_audiolevelpy)
  - [dsaudio_test19_speakeraudiogain.py](#dsaudio_test19_speakeraudiogainpy)
  - [dsaudio_test20_muteunmute.py](#dsaudio_test20_muteunmutepy)
  - [dsaudio_test21_audiodelay.py](#dsaudio_test21_audiodelaypy)
  - [dsaudio_test22_audioformat.py](#dsaudio_test22_audioformatpy)
  - [dsaudio_test23_associatemix.py](#dsaudio_test23_associatemixpy)
  - [dsaudio_test24_primarysecondarylanguage.py](#dsaudio_test24_primarysecondarylanguagepy)
  - [dsaudio_test25_audiomix.py](#dsaudio_test25_audiomixpy)
  - [dsaudio_test26_ms12audioprofiles.py](#dsaudio_test26_ms12audioprofilespy)

## Acronyms, Terms and Abbreviations

- `HAL`    - Hardware Abstraction Layer
- `L3`     - Level 3 Testing
- `ARC`    - Audio Return Channel
- `eARC`   - Enhanced Audio Return Channel
- `SAD`    - Short Audio Descriptor
- `SPDIF`  - Sony/Philips Digital Interface
- `HDMI`   - High-Definition Multimedia Interface
- `LE`     - Loudness Equivalence
- `DRC`    - Dynamic Range Control
- `MI`     - Media Intelligent
- `MS12`   - MultiStream 12
- `PCM`    - Pulse Code Modulation
- `AC3`    - Audio Codec 3
- `EAC3`   - Enhanced `AC3`
- `WMA`    - Windows Media Audio
- `AAC`    - Advanced Audio coding
- `DD`     - DOLBY Digital
- `DDPLUS` - DOLBY Digital Plus
- `MAT`    - Metadata-enhanced Audio Transmission
- `DAP`    - Digital Audio Processing
- `DUT`    - Device Under Test
- `RAFT`   - Rapid Automation Framework for Testing
- `YAML`   - YAML Ain't Markup Language
- `avr`    - Audio Video Receiver

## Setting Up Test Environment

To execute `HAL` `L3` Python test cases, need a Python environment. Follow these steps mentioned in [HPK Public Documentation](https://github.com/rdkcentral/rdk-hpk-documentation/blob/main/README.md)

### Update Configuration Files

#### Rack Configuration File

Example Rack configuration File: `ut/host/tests/configs/example_rack_config.yml`

For more details refer [RAFT](https://github.com/rdkcentral/python_raft/blob/1.0.0/README.md) and [example_rack_config.yml](https://github.com/rdkcentral/python_raft/blob/1.0.0/examples/configs/example_rack_config.yml)

In this file, update the configuration to define the console sessions for the `DUT` and the outbound settings:

|Console Session|Description|
|---------------|-----------|
|default|Downloads the streams required for test cases|
|ssh_player|Plays the stream required for test case|
|ssh_player_secondary|Plays a secondary stream, if required for test case|
|ssh_hal_test|Executes the `HAL` binary for the test case|

```yaml
rackConfig:
  - dut:
      ip: "XXX.XXX.XXX.XXX"  # IP Address of the device
      description: "stb device under test"
      platform: "stb"
      consoles:
        - default:
            type: "ssh"
            port: 10022
            username: "root"
            ip: "XXX.XXX.XXX" # IP address of the device
            password: ' '
        - ssh_player:
            type: "ssh"
            port: 10022
            username: "root"
            ip: "XXX.XXX.XXX" # IP address of the device
            password: ' '
        - ssh_player_secondary:
            type: "ssh"
            port: 10022
            username: "root"
            ip: "XXX.XXX.XXX" # IP address of the device
            password: ' '
        - ssh_hal_test:
            type: "ssh"
            port: 10022
            username: "root"
            ip: "XXX.XXX.XXX" # IP address of the device
            password: ' '
      outbound:
        download_url: "tftp://tftp-server.com/rack1/slot1/"    # Download location for the CPE device
        upload_url: "sftp://server-address/home/workspace/tftp/rack1/slot1/" # Upload location
        upload_url_base_dir: "sftp://server-address/home/workspace/tftp/rack1/slot1"
        httpProxy:   # Local proxy if required
        workspaceDirectory: './logs/workspace'   # Local working directory

```

#### Device Configuration File

Example Device configuration File: `ut/host/tests/configs/deviceConfig.yml`

For more details refer [RAFT](https://github.com/rdkcentral/python_raft/blob/1.0.0/README.md) and [example_device_config.yml](https://github.com/rdkcentral/python_raft/blob/1.0.0/examples/configs/example_device_config.yml)

Update the target directory where `HAL` binaries will be copied into the device. Also, map the profile to the source/sink settings `YAML` file path.

Ensure the platform should match with the `DUT` platform in [Rack Configuration](#rack-configuration-file)

```yaml
deviceConfig:
  cpe1:
    platform: "stb"    # Must match the platform in example_rack_config.yml
    model: "uk"
    target_directory: "/tmp"  # Path where HAL binaries are copied in device
    test:
      profile: "../../../../profiles/sink/Sink_AudioSettings.yaml"
      player:
        tool: "gstreamer"
        prerequisites:
          - export xxxx    # Pre-commands required to play the stream

```

#### Test Setup Configuration File

Example Test Setup configuration File: `ut/host/tests/L3_TestCases/dsAudio/dsAudio_L3_testSetup.yml`

Provide the stream paths for each test case.

If a test case requires multiple streams or needs to be validated using several streams, ensure that all necessary streams are added sequentially for that specific test case.

```yaml
dsAudio:
  description: "dsAudio Device Settings test setup"
  assets:
    device:
      test01_EnableDisableAndVerifyAudioPortStatus:
        streams:
          - "<URL Path>/streams/tones_string_48k_stereo.ac3"
      test02_PortConnectionStatus:
        streams:
      test03_MS12AudioCompression:
        streams:
          - "<URL Path>/streams/tones_string_48k_stereo.ac3"
      test04_MS12DialogueEnhancer:
        streams:
          - "<URL Path>/streams/tones_string_48k_stereo.ac3"
      test05_MS12DolbyVolume:
        streams:
          - "<URL Path>/streams/tones_string_48k_stereo.ac3"
```

#### Test Suite Configuration

Example Test Setup configuration File: `ut/host/tests/dsClasses/dsAudio_test_suite.yml`

Update the execute command according to the device path where `HAL` binaries are copied.

```yaml
dsAudio:
    description: "dsAudio Device Settings testing profile / menu system for UT"
    test:
        artifacts:
          - "../../../bin/hal_test"
          - "../../../bin/libut_control.so"
          - "../../../bin/run.sh"
        execute:
          command: "run.sh"
          arguments: ""
        type: UT-C # C (UT-C Cunit) / C++ (UT-G (g++ ut-core gtest backend))
```

## Run Test Cases

Once the environment is set up, you can execute the test cases with the following command

```bash
python <TestCaseName.py> --config </PATH>/ut/host/tests/configs/example_rack_config.yml --deviceConfig </PATH>/ut/host/tests/configs/deviceConfig.yml
```

## Streams Required

Refer [ds-audio_L3_Low-Level_TestSpecification.md](./ds-audio_L3_Low-Level_TestSpecification.md#audio-streams-requirement) for the stream details

## Test Setup Connections

To verify the audio connect the external devices to `DUT`.
For Example:

- Connect headphone port to a aux speaker or headphone
- Connect `ARC` port to a `avr`

## Test Cases

### dsAudio_test01_EnableDisableAndVerifyAudioPortStatus.py

#### Platform Support - test01

- Source
- Sink

#### User Input Required - test01

**Yes**: User interaction is necessary to confirm audio playback status (This will be automated later).

#### Acceptance Criteria - test01

Play **Stream #1** and confirm that audio is heard through the supported ports.

#### Expected Results - test01

The test enables the specified audio ports, plays the audio stream, and subsequently disables the ports

Success Criteria

- User should hear audio through the enabled port during playback
- User should not hear any audio when the port is disabled.

#### Test Steps - test01

- Initiate the Test:

  - Select and execute the Python file: **`dsAudio_test01_EnableDisableAndVerifyAudioPortStatus.py`**
  - The test will automatically download all required artifacts and streams, copying them to the designated target directory before commencing execution.

- Audio Playback Verification:

    The test will play the designated audio stream and prompt the user with the following:

  - Question: "Is audio playing on the enabled audio port? (Y/N)"
  - Press **Y** if audio is heard (this will mark the step as PASS).
  - Press **N** if no audio is heard (this will mark the step as FAIL).

- Audio Status Confirmation (Port Disabled):

  After confirming audio playback, the test will disable the audio port and prompt the user again:

  - Question: "Is audio playing when the port is disabled? (Y/N)"
  - Press **N** if no audio is heard (this will mark the step as PASS).
  - Press **Y** if audio is heard (this will mark the step as FAIL).

- Repeat for All Ports:

  The test will iterate through all available audio ports, enabling/disabling each one and collecting user feedback accordingly.

- Test Conclusion:

  Upon receiving user responses for all ports, the test will conclude and present a final result: PASS or FAIL based on the user inputs throughout the test execution.

### dsAudio_test02_PortConnectionStatus.py

#### Platform Supported - test02

- Sink

#### User Input Required - test02

- Yes (This will be automated later).

#### Acceptance Criteria - test02

- Verify the Headphone connection status.

#### Expected Results - test02

- This test checks whether the headphones are connected or disconnected.

#### Test Steps - test02

- Run the test file: **`dsAudio_test02_PortConnectionStatus.py`**
- Execution process:

  Upon execution, the test will:

  - Download all the required artifacts.
  - Copy them to the target directory.
  - Automatically start the test execution.

- User prompt for action:

  During the test, the user will be prompted to connect or disconnect the headphones. When prompted:

  - The message "Connect/Disconnect the HEADPHONES and press Enter" will appear.
  - The user must physically connect or disconnect the headphones as requested, then press **Enter** to proceed.

- Completion and Result:

  Once all necessary user actions are completed, the test will evaluate the results and display whether the test Passed or Failed.

### dsAudio_test03_MS12AudioCompression.py

#### Platform Supported - test03

- Source
- Sink

#### User Input Required - test03

Yes (This will be automated later).

#### Acceptance Criteria - test03

Verify the changes in audio compression levels across the supported audio ports for **Stream #1**.

#### Expected Results - test03

The test will evaluate the audio compression levels for various settings. The user should notice a change in audio playback as different compression levels are applied.

#### Test Steps - test03

- Select the test file:

  - Run the Python script **`dsAudio_test03_MS12AudioCompression.py`**

- Execution process:

  The test will:

  - Download all the required artifacts and audio streams.
  - Copy them to the target directory.
  - Automatically start the test execution.

- Play the audio stream:

  Test starts the audio stream playback specified in the test setup configuration file, and the user will be prompted to assess the applied audio compression levels on the supported ports.

- User interaction for verification:

  For each iteration:

  - The test will ask: "Is the audio compression level applied to the supported ports? (Y/N) ?"
  - If the compression level is noticeable, the user should press **Y** to confirm (passing that step).
  - If not, press **N** (failing the step).

- Iterating through compression levels:

  The test will repeat for different audio compression levels. The user must confirm each response accordingly.

- Completion and results:

  After all iterations are complete and the user provides the required responses, the test will conclude and display the final result (PASS/FAIL).

### dsAudio_test04_MS12DialogueEnhancer.py

#### Platform Supported - test04

- Source
- Sink

#### User Input Required - test04

Yes (This will be automated later).

#### Acceptance Criteria - test04

Verify the impact of the dialogue enhancer levels on the supported audio ports for **Stream #2**.

#### Expected Results - test04

This test will evaluate the dialogue enhancer levels. The user should notice an improvement in audio clarity as different enhancement levels are applied.

#### Test Steps - test04

- Select the test file:  

  - Run the Python script **`dsAudio_test04_MS12DialogueEnhancer.py`**

- Execution process:

  The test will:

  - Download all required artifacts and audio streams.
  - Copy them to the target directory.
  - Automatically begin the test execution.

- Play the audio stream:  

  Test starts the audio stream playback specified in the test setup configuration file, and the user will be prompted to verify whether the Dialogue Enhancer level has been applied.

- User interaction for verification:  

  For each iteration:

  - The test will ask: "Is the Dialogue Enhancer level applied to the supported ports? (Y/N) ?"
  - If the enhancer is noticeable, the user should press **Y** to confirm (passing that step).
  - If not, press **N** (failing the step).

- Iterating through enhancement levels:

  The test will iterate through various dialogue enhancer levels, and the user must confirm the response for each level.

- Completion and results:

  After receiving all user inputs, the test will conclude and provide a final result (PASS/FAIL).

### dsAudio_test05_MS12DolbyVolume.py

#### Platform Supported - test05

- Source
- Sink

#### User Input Required - test05

Yes (This will be automated later).

#### Acceptance Criteria - test05

Verify the audio playback with Dolby Volume enabled/disabled (TRUE/FALSE) for all supported audio ports for **Stream #1**.

#### Expected Results - test05

The test evaluates the effect of Dolby Volume on audio playback. The user should notice a clear difference in audio output when Dolby Volume is toggled between TRUE and FALSE.

#### Test Steps - test05

- Run the Test:

  - Select and run the Python script: **`dsAudio_test05_MS12DolbyVolume.py`**

- Download and Setup:

  The test will automatically download all necessary artifacts and streams, and copy them to the target directory on the device.

- Stream Playback:

  - The test will play the designated audio stream.
  - During playback, the test will prompt the user to verify whether Dolby Volume (TRUE/FALSE) is applied to the supported ports.

- User Interaction:

  For each prompt, the user should assess the audio output and respond:

  - If the Dolby Volume (TRUE/FALSE) change is noticeable, the user should press **Y** to confirm that it was applied (this will pass the step).
  - If not, press **N** (this will fail the step).

- Completion:

  After receiving all necessary user inputs, the test case will conclude and display the final result: PASS or FAIL.

### dsAudio_test06_MS12IntelligentEqualizer.py

#### Platform Supported - test06

- Source
- Sink

#### User Input Required - test06

Yes (This will be automated later).

#### Acceptance Criteria - test06

Verify the audio playback for different Intelligent Equalizer modes on all supported audio ports for **Stream #3**.

#### Expected Results - test06

The test evaluates the various modes of the Intelligent Equalizer. The user should observe clear differences in audio quality as different equalizer modes are applied.

#### Test Steps - test06

- Run the Test

  - Select and execute the Python script: **`dsAudio_test06_MS12IntelligentEqualizer.py`**

- Download and Setup:

  The test will automatically:

  - Download all required artifacts and audio streams.
  - Copy them to the target directory on the device.
  - Start the test execution.

- Stream Playback:

  - The test will play the specified audio stream.
  - During playback, the test will prompt the user to verify whether the Intelligent Equalizer mode has been successfully applied to the supported ports (Y/N)?

- User Interaction:

  For each prompt, The user must assess the audio output and respond:

  - If the Intelligent Equalizer mode is applied and noticeable, the user should press **Y** (this passes the step).
  - If not, press **N** (this fails the step).

- Iteration Through Modes:

  The test will iterate through various Intelligent Equalizer modes, and the user will be prompted to confirm their observations for each mode.

- Completion:

  After collecting all user inputs for the different equalizer modes, the test case will conclude and display the final result: PASS or FAIL.

### dsAudio_test07_MS12Volumeleveller.py

#### Platform Supported - test07

- Source
- Sink

#### User Input Required - test07

Yes (This will be automated later).

#### Acceptance Criteria - test07

Verify the behavior of the Volume Leveller across different modes and levels for supported audio ports for **Stream #4**.

#### Expected Results - test07

This test will evaluate the impact of various Volume Leveller settings. The user should observe distinct changes in audio transitions when the stream shifts from low to high frequency.

The Expected Resultss for the different modes are as follows:

- Mode 0 (Volume Leveller OFF): No change in the audio transition.
- Mode 2 (Volume Leveller AUTO): Noticeable change in audio transition as the volume adjusts automatically.
- Mode 1 (Volume Leveller ON): The transition will be less abrupt, as the leveller reduces audio peaks if the level increases.

#### Test Steps - test07

- Run the Test:

  - Select and execute the Python script: **`dsAudio_test07_MS12VolumeLeveller.py`**

- Download and Setup:

  The test will automatically:

  - Download all required artifacts and audio streams.
  - Copy them to the target directory on the device.
  - Start the test execution.

- Stream Playback:

  - The test will play the specified audio stream.
  - The user will be prompted to confirm whether the Volume Leveller mode and level are applied to the supported audio ports.

- User Interaction:

  For each prompt:

  - The test will ask: "Is the Volume Leveller mode and level applied to the supported ports? (Y/N)"
  - If the leveller is functioning as expected, the user should press **Y** (this passes the step).
  - If not, press **N** (this fails the step).

- Iteration Through Modes and Levels:

  The test will iterate through the different Volume Leveller Modes (0, 1, 2) and Levels (0, 5, 10), and the user must confirm their observations for each setting.

- Completion:

  After collecting all user inputs for the various modes and levels, the test will conclude and display the final result: PASS or FAIL.

### dsAudio_test08_MS12BassEnhancer.py

#### Platform Supported - test08

- Source
- Sink

#### User Input Required - test08

Yes (This will be automated later).

#### Acceptance Criteria - test08

Verify the functionality of the Bass Enhancer at various boost levels for all supported audio ports for **Stream #5**.

#### Expected Results - test08

This test will assess the Bass Enhancer by applying different boost values. The user should be able to detect an enhancement in the bass levels when these boost values are applied.

#### Test Steps - test08

- Run the Test:

  - Select and execute the Python script: **`dsAudio_test08_MS12BassEnhancer.py`**

- Download and Setup:

  The test will automatically:

  - Download all required artifacts and audio streams.
  - Copy them to the target directory on the device.
  - Begin the test execution.

- Stream Playback:

  - The test will play the specified audio stream.

  - During playback, the user will be prompted to confirm whether the Bass Boost level is applied to the supported ports.

- User Interaction:

  For each prompt:

  - The test will ask: "Is the Bass Boost level applied to the supported ports? (Y/N)"
  - If the user detects enhanced bass, they should press **Y** (this passes the step).
  - If not, press **N** (this fails the step).

- Iteration Through Boost Levels:

  The test will iterate through multiple Bass Boost levels, and the user must confirm their observations for each level.

- Completion:

  After collecting all user inputs for the various bass boost levels, the test case will conclude and display the final result: PASS or FAIL.

### dsAudio_test09_MS12SurroundDecoder.py

#### Platform Supported - test09

- Source
- Sink

#### User Input Required - test09

Yes (This will be automated later).

#### Acceptance Criteria - test09

Verify the status of the Surround Decoder Mode for supported audio ports for **Stream #6**.

#### Expected Results - test09

This test will evaluate the functionality of the Surround Decoder Mode. The user should observe a noticeable change in audio playback when the surround decoder is enabled or disabled.

#### Test Steps - test09

- Run the Test:

  - Select and execute the Python script: **`dsAudio_test09_MS12SurroundDecoder.py`**

- Download and Setup:

  The test will automatically:

  - Download all required artifacts and the audio stream.
  - Copy them to the target directory on the device.
  - Begin the test execution.

- Stream Playback:

  - The test will play the specified audio stream.
  - During playback, the user will be prompted to confirm whether the Surround Decoder mode (TRUE/FALSE) is applied to the supported audio ports.

- User Interaction:

  For each prompt:

  - The test will ask: "Is the Surround Decoder mode applied to the supported ports? (Y/N)"
  - If the user detects the feature is working as expected for TRUE/FALSE mode, they should press **Y** (this passes the step).
  - If not, press **N** (this fails the step).

- Completion:

  After collecting user inputs, the test will conclude and display the final result: PASS or FAIL.

### dsAudio_test10_MS12DRCMode.py

#### Platform Supported - test10

- Source
- Sink

#### User Input Required - test10

Yes (This will be Automated later).

#### Acceptance Criteria - test10

Play **Stream #4** and verify the Dynamic Range Compression (DRC) Modes for all supported audio ports.

#### Expected Results - test10

This test evaluates the functionality of DRC Modes. The user should notice a distinct change in audio output when different DRC modes are applied.

DRC Modes:

- Mode 0 = Line Mode -- Balances the volume during high-frequency audio playback.
- Mode 1 = RF Mode -- Enhances the volume for low-frequency audio playback.

#### Test Steps - test10

- Run the Test:

  - Select and execute the Python script: **`dsAudio_test10_MS12DRCMode.py`**

- Download and Setup:

  The test will automatically:

  - Download all required artifacts and the audio stream.
  - Copy them to the target directory on the device.
  - Begin test execution.

- Stream Playback:

  - The test will play the specified audio stream.
  - During playback, the user will be prompted to confirm whether the DRC Mode (Line or RF) is applied to the supported audio ports.

- User Interaction:

  For each prompt:

  - The test will ask: "Is the DRC Mode applied to the supported ports ? (Y/N)"
  - If the user detects the mode is applied, they should press **Y** (this passes the step).
  - If not, press **N** (this fails the step).

- DRC Mode Iteration:

  The test will loop through the available DRC modes. The user must confirm their observations for each mode.

- Completion:

  Once all user inputs are collected, the test case concludes and provides a final result: PASS or FAIL.

### dsAudio_test11_MS12SurroundVirtualizer.py

#### Platform Supported - test11

- Source
- Sink

#### User Input Required - test11

Yes (This will be automated later).

#### Acceptance Criteria - test11

Play **Stream #6** and verify the Surround Virtualizer modes for supported audio ports.

#### Expected Results - test11

This test evaluates the functionality of the Surround Virtualizer by checking different modes and levels. The user should observe a noticeable change in the audio experience when these modes and levels are applied.

Surround Virtualizer Modes:

- Mode 0 = OFF (No virtual surround effect)
- Mode 2 = Auto Mode (Automatically adjusts the surround effect based on the audio content)
- Mode 1 = ON (Enables virtual surround)

#### Test Steps - test11

- Run the Test:

  - Select and execute the Python script: **`dsAudio_test11_MS12SurroundVirtualizer.py`**

- Download and Setup:

  The test will:

  - Automatically download all required artifacts and the audio stream.
  - Copy them to the target directory on the device.
  - Begin execution.

- Stream Playback:

  - The test will play the specified audio stream.
  - During playback, the user will be prompted to confirm whether the Surround Virtualizer Mode and levels are applied to the supported audio ports.

- User Interaction:

  For each prompt:

  - The test will ask: "Is the Surround Virtualizer Mode and level applied to the supported ports? (Y/N)"
  - If the user detects the mode or level is applied, they should press **Y** (this passes the step).
  - If not, press **N** (this fails the step).

- Surround Virtualizer Mode Iteration:

  - The test will loop through the available Surround Virtualizer Modes and levels.
  - The user must confirm their observations for each combination.

- Completion:

  Once all user inputs are collected, the test case will conclude and display a final result: PASS or FAIL.

### dsAudio_test12_MS12MISteering.py

#### Platform Supported - test12

- Source
- Sink

#### User Input Required - test12

Yes (This will be Automated later).

#### Acceptance Criteria - test12

Play **Stream #1** and verify the MI Steering functionality for supported audio ports.

#### Expected Results - test12

This test evaluates the MI Steering feature by enabling and disabling it. The user should observe a distinct change in the audio output when this functionality is applied.

#### Test Steps - test12

- Run the Test:

  - Select and execute the Python script: **`dsAudio_test12_MS12MISteering.py`**

- Download and Setup:

  The test will:

  - Automatically download all necessary artifacts and the audio stream.
  - Copy them to the target directory on the device.
  - Begin execution.

- Stream Playback:

  - The test will play the specified audio stream.
  - During playback, the user will be prompted to confirm whether MI Steering (TRUE/FALSE) is applied to the supported audio ports.

- User Interaction:

  For each prompt:

  - The test will ask: "Is MI Steering applied to the supported ports? (Y/N)"
  - If the user detects the MI Steering feature (TRUE/FALSE) is applied, they should press **Y** (this passes the step).
  - If not, press **N** (this fails the step).

- Completion:

  Once all user inputs are gathered, the test will conclude with a final result: PASS or FAIL.

### dsAudio_test13_MS12GraphicEqualizer.py

#### Platform Supported - test13

- Source
- Sink

#### User Input Required - test13

Yes (This wil be Automated later).

#### Acceptance Criteria - test13

Play **Stream #1** and verify the functionality of the Graphic Equalizer Modes for supported audio ports.

#### Expected Results - test13

This test evaluates the different modes of the Graphic Equalizer. The user should be able to detect an audible change in the sound output when each mode is applied.

Graphic Equalizer Modes:

- Mode 0: Off (No effect on audio output)
- Mode 1: Open (Wider soundstage, emphasis on clarity)
- Mode 2: Rich (Deeper, fuller sound profile)
- Mode 3: Focused (More concentrated, detailed sound)

#### Test Steps - test13

- Run the Test:

  - Select and execute the Python script: **`dsAudio_test13_MS12GraphicEqualizer.py`**

- Download and Setup:

  The test will:

  - Automatically download all required artifacts and the audio stream.
  - Copy them to the target directory on the device.
  - Begin execution.

- Stream Playback:

  - The test will play the specified audio stream.
  - During playback, the user will be prompted to confirm whether the Graphic Equalizer mode is applied to the supported audio ports.

- User Interaction:

  - For each mode, the test will ask: "Is the Graphic Equalizer mode applied to the supported ports? (Y/N)"
  - If the user detects the mode is applied correctly, they should press **Y** (this passes the step).
  - If not, press **N** (this fails the step).

- Mode Iteration:

  The test will iterate through all Graphic Equalizer modes (Off, Open, Rich, Focused). The user should confirm their response for each mode.

- Completion:

  Once all user inputs are collected, the test concludes with a final result: PASS or FAIL.

### dsAudio_test14_MS12LEConfig.py

#### Platform Supported - test14

- Source
- Sink

#### User Input Required - test14

Yes (This will be Automated later).

#### Acceptance Criteria - test14

Play **Stream #4** and verify the functionality of the LE Config for supported audio ports.

#### Expected Results - test14

This test evaluates the LE Config functionality. The user should notice changes in the audio output as the stream transitions from low frequency to high frequency when LE Config is enabled or disabled.

#### Test Steps - test14

- Run the Test:

  - Select and execute the Python script: **`dsAudio_test14_MS12LEConfig.py`**

- Download and Setup:

  The test will:

  - Automatically download all required artifacts and the audio stream.
  - Copy them to the target directory on the device.
  - Begin execution.

- Stream Playback:

  - The test will play the specified audio stream.
  - During playback, the user will be prompted to confirm whether LE Config (TRUE/FALSE) is applied to the supported audio ports.

- User Interaction:

  - For each configuration, the test will ask: "Is the LE Config (TRUE/FALSE) applied to the supported ports? (Y/N)"
  - If the user confirms that LE Config (TRUE/FALSE) is applied correctly, they should press **Y** (this passes the step).
  - If not, press **N** (this fails the step).

- Completion:

  Once all user inputs are collected, the test concludes with a final result: PASS or FAIL.

### dsAudio_test15_ARCPort.py

#### Platform Supported - test15

- Sink

#### User Input Required - test15

Yes (This will be Automated later).

#### Acceptance Criteria - test15

Verify the HDMI ARC/eARC port connection status.

#### Expected Results - test15

This test checks the status of the HDMI ARC or eARC connection. The user will be required to connect or disconnect the ARC/eARC port and confirm the status.

#### Test Steps - test15

- Run the Test:

  - Select and execute the Python script: **`dsAudio_test15_ARCPort.py`**

- Download and Setup:

  The test will:

  - Automatically download all necessary artifacts.
  - Copy them to the target directory on the device.
  - Start execution.

- ARC/eARC Port Interaction:

  - During the test, the user will be prompted to connect or disconnect the ARC/eARC port.
  - Once the action is performed, the user must press **ENTER** to proceed.

- User Confirmation:

  The test may prompt the user multiple times to interact with the ARC/eARC connection, asking for confirmation of the status.

- Completion:

  If all user interactions and responses are successfully received, the test will conclude with a final result: PASS or FAIL.

### dsAudio_test16_ARCSAD.py

#### Platform Supported - test16

- Sink

#### User Input Required - test16

Yes (This will be Automated later).

#### Acceptance Criteria - test16

Verify the SAD (Short Audio Descriptor) functionality for the HDMI ARC audio port.

#### Expected Results - test16

This test will send SAD values to the ARC device, and the user is required to verify that these values are correctly received and applied on the ARC device.

#### Test Steps - test16

- Run the Test:

  - Select and execute the Python script: **`dsAudio_test16_ARCSAD.py`**

- Download and Setup:

  The test will:

  - Automatically download all necessary artifacts.
  - Copy them to the target directory on the device.
  - Initiate the test execution.

- SAD Value Transmission:

  - The test will send SAD values (Short Audio Descriptors) to the connected ARC device.
  - The user will be prompted to verify if the values were received and applied on the ARC device.

- User Confirmation:

  - After each SAD value is transmitted, the test will prompt the user with the question: "Was the SAD value sent to the ARC device? (Y/N)".
  - If the SAD value was received, the user should press **Y** to pass the step.
  - If the value was not received, the user should press **N** to fail the step.

- Iterate through SAD Values:

  The test will loop through multiple SAD values, and for each value, the user will be asked to confirm whether it was successfully transmitted and received.

- Completion:

  Once all the SAD values have been processed and user responses are collected, the test case will conclude with a final result: PASS or FAIL based on the user's inputs.

### dsAudio_test17_OutputMode.py

#### Platform Supported - test17

- Source
- Sink

#### User Input Required - test17

Yes (This will be Automated later).

#### Acceptance Criteria - test17

Play **Streams #7, #1, and #8** and verify the audio output mode for all supported audio ports.

#### Expected Results - test17

This test will play different audio output modes for streams on the supported audio ports. The user should verify the audio output format when various output modes are applied.

|Stream|OutputMode (Format)|
|------|-------------------|
|tones_string_48k_stereo.wav|STEREO (PCM), PASSTHRU (PCM)|
|tones_string_48k_stereo.ac3|STEREO (PCM), DD (DD), PASSTHRU (DD)|
|tones_string_48k_stereo.eac3|STEREO (PCM), DD (DD), DDPLUS (DD+), PASSTHRU (DD+)|

#### Test Steps - test17

- Run the Test:

  - Select and execute the Python script: **`dsAudio_test17_OutputMode.py`**

- Download and Setup:

  The test will:

  - Download all necessary artifacts and streams.
  - Copy the files to the target directory.
  - Begin the test execution.

- Audio Output Verification:

  - The test will play the specified streams and prompt the user to verify if the output mode on the supported ports is in the correct format.
  - The user will be asked: "For the currently playing stream is the output mode on the supported port was in the correct format? (Y/N)"
  - If the format is correct for the output mode, the user should press **Y** (this passes the step).
  - If the format is incorrect, the user should press **N** (this fails the step).

- Iterate through Output Modes and Streams:

  The test will loop through different streams and output modes, and for each combination, the user should confirm whether the audio format is correct.

- Completion:

  Once all the streams and output modes have been tested and user responses are collected, the test case will conclude with a final result: PASS or FAIL based on the user’s inputs.

### dsAudio_test18_AudioLevel.py

#### Platform Supported - test18

- Sink

#### User Input Required - test18

Yes (This will be automated later)

#### Acceptance Criteria - test18

Play **Stream #1** and verify the audio level functionality across supported audio ports.

#### Expected Results - test18

This test evaluates the incremental adjustment of audio levels. The user should observe a noticeable increase in volume as the test applies different audio levels.

#### Test Steps - test18

- Run the Test Script:

  - Select the Python file **`dsAudio_test18_AudioLevel.py`** and execute it.

- Download and Prepare Artifacts:

  - The test will automatically download all necessary artifacts and streams, copying them to the target directory before starting the execution.

- Play the Stream:

  - The test will play Stream and prompt the user to confirm if the specified volume level is applied to the supported audio ports.
  - The user should press **Y** if the volume level is correctly applied (this will pass the step) or **N** if it is not (this will fail the step).

- Iterate Through Audio Levels:

  The test will continue iterating through various audio levels. The user should respond at each prompt to confirm whether the volume level is applied.

- Test Conclusion:

  Once the test receives all user responses, it will conclude and output the final test result: PASS or FAIL.

### dsAudio_test19_SpeakerAudioGain.py

#### Platform Supported - test19

- Sink

#### User Input Required - test19

Yes (This will be Automated later).

#### Acceptance Criteria - test19

Play **Stream #1** and verify the audio gain values for the speaker output port.

#### Expected Results - test19

This test assesses different audio gain values for the speaker. The user should notice distinct volume changes as varying audio gain levels are applied.

#### Test Steps - test19

- Run the Test Script:

  - Select the Python file **`dsAudio_test19_SpeakerAudioGain.py`** and execute it.

- Download and Prepare Artifacts:

  The test will automatically download all required artifacts and streams, copying them to the target directory before execution begins.

- Play the Stream:

  - The test will play Stream and prompt the user to confirm whether the correct volume gain value is applied to the speaker port.
  - The user should press Y if the gain value is correctly applied (this passes the step) or N if it is not (this fails the step).

- Iterate Through Audio Gain Values:

  The test will iterate through multiple audio gain values, and the user will need to verify each level, confirming if the volume changes accordingly.

- Test Completion

  After gathering all user responses, the test will conclude and display the final test result: PASS or FAIL.

### dsAudio_test20_MuteUnMute.py

#### Platform Supported - test20

- Source
- Sink

#### User Input Required - test20

Yes (This will be Automated later).

#### Acceptance Criteria- test20

Play **Stream #1** and verify the Mute and Unmute functionalities for the supported audio ports.

#### Expected Results - test20

The test will play the stream and evaluate the mute/unmute functionality on supported audio ports.

- When muted, the user should not hear any audio.
- When unmuted, the user should hear the audio clearly.

#### Test Steps - test20

- Run the Test Script:

  - Select the Python file **`dsAudio_test20_MuteUnMute.py`** and execute it.

- Download and Prepare Artifacts:

  The test will automatically download all required artifacts and streams, copying them to the target directory before execution begins.

- Play the Stream and Respond to Prompts:

  - The test will play Stream and prompt the user with the following question for each supported port:

    - "Is audio playing on the supported port ? (Y/N)"
    - In the Mute case: The user should press **N** if no sound is heard (this passes the step), otherwise **Y** (this fails the step).
    - In the Unmute case: The user should press **Y** if audio is heard (this passes the step), otherwise **N** (this fails the step).

- Iterate Through Supported Ports:

  The test will loop through each supported audio port (e.g., speakers, HDMI ARC, SPDIF, etc.), and the user must confirm if the mute/unmute functionality is working as expected.

- Test Completion:

  After gathering all user responses for each audio port, the test will conclude and display the final test result.

### dsAudio_test21_AudioDelay.py

#### Platform Supported - test21

- Source
- Sink

#### User Input Required - test21

Yes (This will be Automated later).

#### Acceptance Criteria - test21

Play **Stream #18** and verify the Audio Delay functionality for supported audio ports.

#### Expected Results - test21

- The test will play the stream and apply different delay values to evaluate the Audio Delay feature on the supported audio ports.
- The user should be able to notice the delay in audio relative to the video playback for various delay values.

#### Test Steps - test21

- Run the Test Script:

  - Select the Python file **`dsAudio_test21_AudioDelay.py`** and execute it.

- Download and Prepare Artifacts:

  The test will automatically download all required artifacts and streams, copying them to the target directory before the execution begins.

- Play the Stream and Respond to Prompts:

  - The test will play Stream and prompt the user with the following question for each supported port:

    - "Is the audio delay value applied to the supported port? (Y/N)"
    - The user should press **Y** if the audio delay is correctly observed (this passes the step), or **N** if the delay is not observed (this fails the step).

- Iterate Through Different Audio Delay Values:

  The test will loop through different audio delay values (e.g., increasing or decreasing delay) and evaluate them across all supported audio ports. The user must confirm if the delay is noticeable and accurate for each configuration.

- Test Completion:

  After receiving all user responses for each audio delay setting and port, the test will conclude and display the final test result.

### dsAudio_test22_AudioFormat.py

#### Platform Supported - test22

- Source
- Sink

#### User Input Required - test22

No (Fully automated test case).

#### Acceptance Criteria - test22

Play the **Streams #7, #1, #8, #9, #10, #11, #19, #12, #13, #14, #15, #16, #17** sequentially, and the test case will automatically verify the audio formats based on device feedback.

#### Expected Results - test22

- This test will automatically play streams with different audio formats and verify the formats based on the callbacks reported by the device.
- The system should accurately detect and validate the audio format of each stream, confirming whether the format matches the expected result.

#### Test Steps - test22

- Run the Test Script:

  - Select the Python file **`dsAudio_test22_AudioFormat.py`** and execute it.

- Download and Prepare Artifacts:

  The test will automatically download all necessary artifacts and streams and copy them to the designated target directory before starting the execution.

- Stream Playback and Automated Verification:

  - The test case will sequentially play the predefined streams on the device.
  - As each stream is played, the device will report callbacks indicating the detected audio format.

- Result Evaluation:

  - The test case will automatically verify the audio format based on the reported callbacks from the device and evaluate whether the correct format is detected for each stream.
  - Each step will be marked PASS or FAIL based on whether the expected audio format matches the actual format reported.

- Test Completion:

  Once all streams have been tested, the test will conclude and provide a final result (PASS/FAIL) based on the overall success or failure of the format verification.

### dsAudio_test23_AssociateMix.py

#### Platform Supported - test23

- Source
- Sink

#### User Input Required - test23

Yes (This will be Automated later)

#### Acceptance Criteria - test23

Play **Stream #19** and verify the associate audio mixing functionality for supported audio ports.

#### Expected Results - test23

This test will play a stream containing two audio tracks (main and associate) and adjust the fader control values to test audio mixing.

- when mixing is false, user should hear only main Audio
- When the mixing is TRUE and fader control value is set to -32, the user should hear only the main audio.
- When the mixing is TRUE and fader control value is set to 32, the user should hear only the associate audio.
- When the mixing is TRUE and fader control value is set to 0, the user should hear both the main and associate audios mixed together.

#### Test Steps - test23

- Run the Test Script:

  - Select the Python file **`dsAudio_test23_AssociateMix.py`** and execute it.

- Download and Prepare Artifacts:

  The test will automatically download all required artifacts and streams, then copy them to the designated target directory before starting the execution.

- Stream Playback and User Verification:

  - The test will play the stream containing both main and associate audio tracks and prompt the user to verify if the audio mixing and fader control are working correctly.
  - The test will ask the user: "Is audio playing on the supported port with mixing (TRUE/FALSE) and fader control value (Y/N)?"

- Test Loop:

  The test will continue through a loop, testing the different fader control values (-32, 0, 32). The user must respond accordingly to each scenario.

- Mixing and Fader Control Verification:

  - If Mixing is False, Press **Y** (this pass the step) if only main audio audio is heard other **N** (this fails the step).
  - If Mixing is True and:

    - For fader value -32:

      - The user should hear only the main audio.
      - If the main audio is heard, press **Y** (this pass the step), otherwise press **N** (this fails the step).

    - For fader value 32:

      - The user should hear only the associate audio.
      - If the associate audio is heard, press **Y** (this pass the step), otherwise press **N** (this fails the step).

    - For fader value 0:

      - The user should hear both the main and associate audios mixed together.
      - If both audios are heard, press **Y** (this pass the step), otherwise press **N** (this fails the step).

- Test Completion:

  Once all user responses are received, the test case will conclude and provide a final result. If all steps pass, the test ends with Result: PASS/FAIL.

### dsAudio_test24_PrimarySecondaryLanguage.py

#### Platform Supported - test24

- Source
- Sink

#### User Input Required - test24

Yes (This will be Automated later).

#### Acceptance Criteria - test24

Play **Stream #19** and verify the primary and secondary language functionality for the supported audio ports.

#### Expected Results - test24

- This test will play a stream containing multiple PIDs (Program Identifiers) associated with different languages.
- The test will switch between different languages for both primary and secondary audio streams, and the user should verify that the audio is being played in the selected language.

#### Test Steps - test24

- Run the Test Script

  - Select the Python file **`dsAudio_test24_PrimarySecondaryLanguage.py`** and execute it.

- Download and Prepare Artifacts:

  The test will automatically download all required artifacts and streams, and copy them to the target directory before starting the execution.

- Stream Playback and Language Verification:

  - The test will play the stream containing multiple audio tracks in different languages.
  - The test will prompt the user to verify if the correct primary and secondary languages are applied to the audio port:
  - "Is audio playing on supported port with applied primary/secondary language ? (Y/N)"
  - The user must respond based on what they hear:
  - If the audio is playing in the correct language, press **Y** to pass the step.
  - If the audio is not in the correct language, press **N** this fails the step.

- Language Switching Loop:

  - The test will iterate through various language configurations for both primary and secondary audio tracks.
  - After each language change, the user will be prompted to verify the language and respond accordingly.

- Test Completion:

  Once all user responses are received, the test will conclude and provide a final result.
If all language configurations are verified correctly, the test will end with Result: PASS/FAIL.

### dsAudio_test25_AudioMix.py

#### Platform Supported - test25

- Sink

#### User Input Required - test25

Yes (This will be Automated later).

#### Acceptance Criteria - test25

Play **Streams #20 and #21** and verify the audio mixing volume levels for supported audio ports.

#### Expected Results - test25

This test will play multiple streams simultaneously, adjusting different mixing volume levels for both the primary and system audio tracks. The user should hear both audio sources with the applied volume settings.

#### Test Steps - test25

- Run the Test Script:

  - Select the Python file **`dsAudio_test25_AudioMix.py`** and execute it.

- Download and Prepare Artifacts:

  The test will automatically download all required artifacts and streams, copying them to the target directory before execution begins.

- Stream Playback and Volume Mixing Verification:

  - The test will start playing the stream and prompt the user to verify if the audio mixing and volume settings are correctly applied:
  - "Is the audio playing on supported port with Mixing and applied primary and system volume levels ? (Y/N)"
  - If the user hears the correct audio mixing with the applied volume levels, they should press **Y** to pass the step.
  - If the volume levels are not correctly applied, the user should press **N** this fails the step.

- Volume Mixing Loop:

  - The test will iterate through various combinations of volume levels for both the primary and system audio tracks.
  - After each change in the volume levels, the user will be prompted to verify the audio mix and respond accordingly.

- Test Completion:

  - Once all user responses are collected, the test will end, providing a final result.
  - If all volume levels for the primary and system audios are verified successfully, the test will end with Result: PASS. Otherwise, it will conclude with Result: FAIL.

### dsAudio_test26_MS12AudioProfiles.py

#### Platform Supported - test26

- Sink

#### User Input Required - test26

Yes (This will be Automated later).

#### Acceptance Criteria - test26

Play **Stream #3** and verify the MS12 Audio Profile modes for the supported audio ports.

#### Expected Results - test26

- This test will play the stream and apply different MS12 Audio Profile modes. The user should notice a change in the audio output when these modes are applied.

- MS12 Audio Profile Modes:
  - Mode: Off
  - Mode: User

#### Test Steps - test26

- Run the Test Script:

  - Select the Python file **`dsAudio_test26_MS12AudioProfiles.py`** and execute it.

- Download and Prepare Artifacts:

  The test will automatically download all required artifacts and streams, copying them to the target directory before execution begins.

- Stream Playback and Profile Mode Verification:

  - The test will play the stream and prompt the user:
  - "Is the MS12 Audio Profile mode applied to the supported port ? (Y/N)"
  - If the correct audio profile mode is applied and the user notices the change in audio, they should press **Y** to pass the step.
  - If no change is noticed or the mode is not applied, the user should press **N** this fails the step.

- Profile Mode Loop:

  - The test will iterate through different MS12 Audio Profile modes (Off, User).
  - After each mode is applied, the user will be prompted to verify the change in audio and respond accordingly.

- Test Completion:

  - Once all user responses are collected, the test will conclude.
  - If all profile modes are verified successfully, the test will end with Result: PASS. If any of the modes fail, the test will conclude with Result: FAIL.