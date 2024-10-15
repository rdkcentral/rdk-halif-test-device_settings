# dsAudio HAL L3 Python Test Procedure

## Table of Contents

- [Setting Up Test Envirionment](#setting-up-test-environment)
- [Streams Required](#streams-required)
- [Test Setup Connections](#test-setup-connections)
- [Test Cases](#test-cases)
  - [test01_enabledisableandverifyaudioportstatuspy](#dsaudio_test01_enabledisableandverifyaudioportstatuspy)

## Setting Up Test Environment

To execute HAL L3 Python test cases, you need to set up the Python environment properly. Follow these steps mentioned in [HPK Public Documentation](https://github.com/rdkcentral/rdk-hpk-documentation/blob/main/README.md)

Modify Configuration Files:

a. `ut/host/tests/configs/example_rack_config.yml`

In this file, update the configuration to define the console sessions for the device under test (DUT) and the outbound settings:

|Console Session|Description|
|---------------|-----------|
|default | Downloads the streams required for test cases.
|ssh_player | Plays the stream required for test case.
|ssh_player_secondary | Plays a secondary stream, if required for test case.
|ssh_hal_test | Executes the HAL binary for the test case.

```mermaid
rackConfig:
  - dut:
      ip: "XXX.XXX.XXX.XXX"  # IP Address of the device
      description: "Element device under test"
      platform: "Element"
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
b. `ut/host/tests/configs/deviceConfig.yml`

Update the target directory where HAL binaries will be copied into the device. Also, map the profile to the source/sink settings YAML file path. 

Ensure the platform matches the DUT platform in `example_rack_config.yml`.

```mermaid
deviceConfig:
  cpe1:
    platform: "Element"    # Must match the platform in example_rack_config.yml
    model: "X3"
    target_directory: "/opt/HAL/dsAudio_L3"  # Path where HAL binaries are copied in device
    test:
      profile: "../../../profiles/sink/Sink_AudioSettings.yaml"
      player:
        tool: "gstreamer"
        prerequisites:
          - export xxxx    # Pre-commands required to play the stream

```
c. `ut/host/tests/dsAudio_L3_Tests/dsAudio_L3_testSetup.yml`

Update the artifact paths from which the binaries should be copied to the device.

Set the execution paths and provide the stream paths for each test case.

If a test case requires multiple streams or needs to be validated using several streams, ensure that all necessary streams are added sequentially for that specific test case.

```mermaid
dsAudio:
  description: "dsAudio Device Settings test setup"
  assets:
    device:
      defaults: &defaults
        artifacts:
          - "<path>/bin/hal_test"
          - "<path>/bin/libut_control.so"
          - "<path>/bin/Sink_AudioSettings.yaml"
          - "<path>/bin/run.sh"
        execute:
          - "chmod +x /opt/HAL/dsAudio_L3/hal_test"
          - "chmod +x /opt/HAL/dsAudio_L3/run.sh"
          - cp -rf /usr/lib/libdshal.so /opt/HAL/dsAudio_L3/
          - "ln -s /usr/lib/libds-hal.so /opt/HAL/dsAudio_L3/libdshal.so"
      test01_EnableDisableAndVerifyAudioPortStatus:
        <<: *defaults
        streams:
          - "<path>/streams/tones_string_48k_stereo.ac3"
      test02_PortConnectionStatus:
        <<: *defaults
      test25_AudioMix:
        <<: *defaults
        streams:
          - "<path>/streams/primary_audio_48k_2ch.ac3"
          - "<path>/streams/system_audio_48k_2ch.wav"

```
d. `ut/host/tests/dsClasses/dsAudio_test_suite.yml`

Update the execute command according to the device path where HAL binaries are copied.

```mermaid
dsAudio:
  description: "dsAudio Device Settings testing profile"
  test:
    execute: "/opt/HAL/dsAudio_L3/run.sh -p /opt/HAL/dsAudio_L3/Sink_AudioSettings.yaml"
    type: UT-C  # Cunit tests (UT-C)

```

5.Run Test Cases:

Once the environment is set up, you can execute the test cases with the following command:

```mermaid
python <TestCaseName.py> --config </PATH>/rdk-halif-device_settings/ut/host/tests/configs/example_rack_config.yml --deviceConfig </PATH>/rdk-halif-device_settings/ut/host/tests/configs/deviceConfig.yml
```

## Streams Required

| # | Streams Name | Description                                                                                   |
|---|--------------------------|-------------------------------------------------------------------------------------------------------------|
| 1 | tones_string_48k_stereo.ac3                        | Format: AC3
| 2 | Dolby_stream_supports_Dialouge_Enhancer            | Format: AC4
| 3 | music_lowdb.ac3                                    | Format: AC3
| 4 | tone_500Hz_compress_48k_stereo.ac3                 | Format: AC3
| 5 | tone_bassrange_150Hz_48k_Stereo.ac3                | Format: AC3
| 6 | Dolby_atmos_stream_supports_surround_mode          | Format: AC4 / EAC3_ATMOS / AC4_ATMOS
| 7 | tones_string_48k_stereo.wav                        | Format: PCM
| 8 | tones_string_48k_stereo.eac3                       | Format: EAC3
| 9 | tones_string_48k_stereo.aac                        | Format: AAC
|10 | tones_string_48k_stereo.ogg                        | Format: VORBIS
|11 | tones_string_48k_stereo.wma                        | Format: WMA
|12 | Audio_supports_MAT_format                          | Format: MAT
|13 | Dolby_audio_supports_TRUEHD_format                 | Format: TRUEHD
|14 | DolbyDigitalPlus_atmos_audio                       | Format: EAC3_ATMOS
|15 | TRUEHD_atmos_audio                                 | Format: TRUEHD_ATMOS
|16 | MAT_atmos_audio                                    | Format: MAT_ATMOS
|17 | Dolby_atmos_audio                                  | Format: AC4_ATMOS
|18 | Dolby_stream_supports_AVsync                       | Format: AAC
|19 | Dolby_stream_supports_Multi-Language               | Format: AC4
|20 | primary_audio_48k_2ch.ac3                          | Format: AC3
|21 | system_audio_48k_2ch.wav                           | Format: PCM
|22 | Dolby_music                                        | Format: AC3

## Test Setup Connections

### Supported Audio Output Ports

### Source

HDMI Out is the only supported audio port for Source device. So for verifying Audio in Source device HDMI Out should be connected to a Sink Device.

### Sink

There are different Audio output ports available for Sink device. So for verifying audio 

## Test Cases

### dsAudio_test01_EnableDisableAndVerifyAudioPortStatus.py

#### Overview

- This test case verifies the functionality of enabling and disabling audio ports while ensuring that audio is correctly routed through the appropriate channels based on the device type (Source or Sink).

#### Platform Support

- Source
- Sink

#### User Input Required

- Yes: User interaction is necessary to confirm audio playback status (This will be automated later).

#### Acceptance Criteria

- Play **Stream #1** and confirm that audio is heard through the supported ports.

#### Expected Results

The test enables the specified audio ports, plays the audio stream, and subsequently disables the ports

- Success Criteria
  - Users should hear audio through the enabled port during playback.
  - Users should not hear any audio when the port is disabled.

#### Test Steps

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

### 2. dsAudio_test02_PortConnectionStatus.py

2.1 Platform Supported:

- Sink

2.2 User Input Required:

- Yes (This will be automated later).

2.3 Acceptance Criteria:

- Verify the Headphone connection status.

2.4 Expected Outcome:

- This test checks whether the headphones are connected or disconnected.

2.5 Test Steps:

Select the test file:

- Select and Execute **`dsAudio_test02_PortConnectionStatus.py`**

Execution process:

Upon execution, the test will:

- Download all the required artifacts.
- Copy them to the target directory.
- Automatically start the test execution.

User prompt for action:

During the test, the user will be prompted to connect or disconnect the headphones. When prompted:

- The message "Connect/Disconnect the HEADPHONES and press Enter" will appear.
- The user must physically connect or disconnect the headphones as requested, then press **Enter** to proceed.

Completion and Result:

- Once all necessary user actions are completed, the test will evaluate the results and display whether the test Passed or Failed.

### 3. dsAudio_test03_MS12AudioCompression.py

3.1 Platform Supported:

- Sink

3.2 User Input Required:

- Yes (This will be automated later).

3.3 Acceptance Criteria:

- Play the audio **Stream #1** and verify the changes in audio compression levels across the supported audio ports.

3.4 Expected Outcome:

- The test will evaluate the audio compression levels for various settings. The user should notice a change in audio playback as different compression levels are applied.

3.5 Test Steps:

Select the test file:

- Run the Python script **`dsAudio_test03_MS12AudioCompression.py`**

Execution process:

The test will:

- Download all the required artifacts and audio streams.
- Copy them to the target directory.
- Automatically start the test execution.

Play the audio stream:

- During the test, an audio stream will play, and the user will be prompted to assess the applied audio compression levels on the supported ports.

User interaction for verification:

For each iteration:

- The test will ask: "Is the audio compression level applied to the supported ports? (Y/N) ?"
- If the compression level is noticeable, the user should press **Y** to confirm (passing that step).
- If not, press **N** (failing the step).

Iterating through compression levels:

- The test will repeat for different audio compression levels. The user must confirm each response accordingly.

Completion and results:

- After all iterations are complete and the user provides the required responses, the test will conclude and display the final result (PASS/FAIL).

### 4. dsAudio_test04_MS12DialogueEnhancer.py

4.1 Platform Supported:

- Source
- Sink

4.2 User Input Required:

- Yes (This will be automated later).

4.3 Acceptance Criteria:

- Play the audio **Stream #2** and verify the impact of the dialogue enhancer levels on the supported audio ports.

4.4 Expected Outcome:

- This test will evaluate the dialogue enhancer levels. The user should notice an improvement in audio clarity as different enhancement levels are applied.

4.5 Test Steps:

Select the test file:  

- Run the Python script **`dsAudio_test04_MS12DialogueEnhancer.py`**

Execution process:

The test will:

- Download all required artifacts and audio streams.
- Copy them to the target directory.
- Automatically begin the test execution.

Play the audio stream:  

- During the test, an audio stream will play, and the user will be prompted to verify whether the Dialogue Enhancer level has been applied.

User interaction for verification:  

For each iteration:

- The test will ask: "Is the Dialogue Enhancer level applied to the supported ports? (Y/N) ?"
- If the enhancer is noticeable, the user should press **Y** to confirm (passing that step).
- If not, press **N** (failing the step).

Iterating through enhancement levels:

- The test will iterate through various dialogue enhancer levels, and the user must confirm the response for each level.

Completion and results:

- After receiving all user inputs, the test will conclude and provide a final result (PASS/FAIL).

### 5. dsAudio_test05_MS12DolbyVolume.py

5.1 Platform Supported:

- Source
- Sink

5.2 User Input Required:

- Yes (This will be automated later).

5.3 Acceptance Criteria:

- Play audio **Stream #1** and verify the audio playback with Dolby Volume enabled/disabled (TRUE/FALSE) for all supported audio ports.

5.4 Expected Results:

- The test evaluates the effect of Dolby Volume on audio playback. The user should notice a clear difference in audio output when Dolby Volume is toggled between TRUE and FALSE.

5.5 Test Steps:

Run the Test:

- Select and run the Python script: **`dsAudio_test05_MS12DolbyVolume.py`**

Download and Setup:

- The test will automatically download all necessary artifacts and streams, and copy them to the target directory on the device.

Stream Playback:

- The test will play the designated audio stream.
- During playback, the test will prompt the user to verify whether Dolby Volume (TRUE/FALSE) is applied to the supported ports.

User Interaction:

For each prompt, the user should assess the audio output and respond:

- If the Dolby Volume (TRUE/FALSE) change is noticeable, the user should press **Y** to confirm that it was applied (this will pass the step).
- If not, press **N** (this will fail the step).

Completion:

- After receiving all necessary user inputs, the test case will conclude and display the final result: PASS or FAIL.

### 6. dsAudio_test06_MS12IntelligentEqualizer.py

6.1 Platform Supported:

- Sink

6.2 User Input Required:

- Yes (This will be automated later).

6.3 Acceptance Criteria:

- Play **Stream #3** and verify the audio playback for different Intelligent Equalizer modes on all supported audio ports.

6.4 Expected Results:

- The test evaluates the various modes of the Intelligent Equalizer. The user should observe clear differences in audio quality as different equalizer modes are applied.

6.5 Test Steps:

Run the Test:

- Select and execute the Python script: **`dsAudio_test06_MS12IntelligentEqualizer.py`**

Download and Setup:

The test will automatically:

- Download all required artifacts and audio streams.
- Copy them to the target directory on the device.
- Start the test execution.

Stream Playback:

- The test will play the specified audio stream.
- During playback, the test will prompt the user to verify whether the Intelligent Equalizer mode has been successfully applied to the supported ports (Y/N)?

User Interaction:

For each prompt, The user must assess the audio output and respond:

- If the Intelligent Equalizer mode is applied and noticeable, the user should press **Y** (this passes the step).
- If not, press **N** (this fails the step).

Iteration Through Modes:

- The test will iterate through various Intelligent Equalizer modes, and the user will be prompted to confirm their observations for each mode.

Completion:

- After collecting all user inputs for the different equalizer modes, the test case will conclude and display the final result: PASS or FAIL.

### 7. dsAudio_test07_MS12Volumeleveller.py

7.1 Platform Supported:

- Source
- Sink

7.2 User Input Required:

- Yes (This will be automated later).

7.3 Acceptance Criteria:

- Play **Stream #4** and verify the behavior of the Volume Leveller across different modes and levels for supported audio ports.

7.4 Expected Results:

- This test will evaluate the impact of various Volume Leveller settings. The user should observe distinct changes in audio transitions when the stream shifts from low to high frequency.

The expected outcomes for the different modes are as follows:

- Mode 0 (Volume Leveller OFF): No change in the audio transition.
- Mode 2 (Volume Leveller AUTO): Noticeable change in audio transition as the volume adjusts automatically.
- Mode 1 (Volume Leveller ON): The transition will be less abrupt, as the leveller reduces audio peaks if the level increases.

7.5 Test Steps:

Run the Test:

- Select and execute the Python script: **`dsAudio_test07_MS12VolumeLeveller.py`**

Download and Setup:

The test will automatically:

- Download all required artifacts and audio streams.
- Copy them to the target directory on the device.
- Start the test execution.

Stream Playback:

- The test will play the specified audio stream.
- The user will be prompted to confirm whether the Volume Leveller mode and level are applied to the supported audio ports.

User Interaction:

For each prompt:

- The test will ask: "Is the Volume Leveller mode and level applied to the supported ports? (Y/N)"
- If the leveller is functioning as expected, the user should press **Y** (this passes the step).
- If not, press **N** (this fails the step).

Iteration Through Modes and Levels:

- The test will iterate through the different Volume Leveller Modes (0, 1, 2) and Levels (0, 5, 10), and the user must confirm their observations for each setting.

Completion:

- After collecting all user inputs for the various modes and levels, the test will conclude and display the final result: PASS or FAIL.

### 8. dsAudio_test08_MS12BassEnhancer.py

8.1 Platform Supported:

- Sink

8.2 User Input Required:

- Yes (This will be automated later).

8.3 Acceptance Criteria:

- Play **Stream #5** and verify the functionality of the Bass Enhancer at various boost levels for all supported audio ports.

8.4 Expected Results:

- This test will assess the Bass Enhancer by applying different boost values. The user should be able to detect an enhancement in the bass levels when these boost values are applied.

8.5 Test Steps:

Run the Test:

- Select and execute the Python script: **`dsAudio_test08_MS12BassEnhancer.py`**

Download and Setup:

The test will automatically:

- Download all required artifacts and audio streams.
- Copy them to the target directory on the device.
- Begin the test execution.

Stream Playback:

- The test will play the specified audio stream.

- During playback, the user will be prompted to confirm whether the Bass Boost level is applied to the supported ports.

User Interaction:

For each prompt:

- The test will ask: "Is the Bass Boost level applied to the supported ports? (Y/N)"
- If the user detects enhanced bass, they should press **Y** (this passes the step).
- If not, press **N** (this fails the step).

Iteration Through Boost Levels:

- The test will iterate through multiple Bass Boost levels, and the user must confirm their observations for each level.

Completion:

- After collecting all user inputs for the various bass boost levels, the test case will conclude and display the final result: PASS or FAIL.

### 9. dsAudio_test09_MS12SurroundDecoder.py

9.1 Platform Supported:

- Sink

9.2 User Input Required:

- Yes (This will be automated later).

9.3 Acceptance Criteria:

- Play **Stream #6** and verify the status of the Surround Decoder Mode for supported audio ports.

9.4 Expected Results:

- This test will evaluate the functionality of the Surround Decoder Mode. The user should observe a noticeable change in audio playback when the surround decoder is enabled or disabled.

9.5 Test Steps:

Run the Test:

- Select and execute the Python script: **`dsAudio_test09_MS12SurroundDecoder.py`**

Download and Setup:

The test will automatically:

- Download all required artifacts and the audio stream.
- Copy them to the target directory on the device.
- Begin the test execution.

Stream Playback:

- The test will play the specified audio stream.
- During playback, the user will be prompted to confirm whether the Surround Decoder mode (TRUE/FALSE) is applied to the supported audio ports.

User Interaction:

For each prompt:

- The test will ask: "Is the Surround Decoder mode applied to the supported ports? (Y/N)"
- If the user detects the feature is working as expected for TRUE/FALSE mode, they should press **Y** (this passes the step).
- If not, press **N** (this fails the step).

Completion:

- After collecting user inputs, the test will conclude and display the final result: PASS or FAIL.

### 10. dsAudio_test10_MS12DRCMode.py

10.1 Platform Supported:

- Source
- Sink

10.2 User Input Required:

- Yes (This will be Automated later).

10.3 Acceptance Criteria:

- Play **Stream #4** and verify the Dynamic Range Compression (DRC) Modes for all supported audio ports.

10.4 Expected Results:

- This test evaluates the functionality of DRC Modes. The user should notice a distinct change in audio output when different DRC modes are applied.

DRC Modes:

- Mode 0 = Line Mode -- Balances the volume during high-frequency audio playback.
- Mode 1 = RF Mode -- Enhances the volume for low-frequency audio playback.

10.5 Test Steps:

Run the Test:

- Select and execute the Python script: **`dsAudio_test10_MS12DRCMode.py`**

Download and Setup:

The test will automatically:

- Download all required artifacts and the audio stream.
- Copy them to the target directory on the device.
- Begin test execution.

Stream Playback:

- The test will play the specified audio stream.
- During playback, the user will be prompted to confirm whether the DRC Mode (Line or RF) is applied to the supported audio ports.

User Interaction:

For each prompt:

- The test will ask: "Is the DRC Mode applied to the supported ports ? (Y/N)"
- If the user detects the mode is applied, they should press **Y** (this passes the step).
- If not, press **N** (this fails the step).

DRC Mode Iteration:

- The test will loop through the available DRC modes. The user must confirm their observations for each mode.

Completion:

- Once all user inputs are collected, the test case concludes and provides a final result: PASS or FAIL.

### 11. dsAudio_test11_MS12SurroundVirtualizer.py

11.1 Platform Supported:

- Sink

11.2 User Input Required:

- Yes (This will be automated later).

11.3 Acceptance Criteria:

- Play **Stream #6** and verify the Surround Virtualizer modes for supported audio ports.

11.4 Expected Results:

- This test evaluates the functionality of the Surround Virtualizer by checking different modes and levels. The user should observe a noticeable change in the audio experience when these modes and levels are applied.

  - Surround Virtualizer Modes:

    - Mode 0 = OFF (No virtual surround effect)
    - Mode 2 = Auto Mode (Automatically adjusts the surround effect based on the audio content)
    - Mode 1 = ON (Enables virtual surround)

11.5 Test Steps:

- Run the Test:

  - Select and execute the Python script: **`dsAudio_test11_MS12SurroundVirtualizer.py`**

- Download and Setup:

  - The test will:

    - Automatically download all required artifacts and the audio stream.
    - Copy them to the target directory on the device.
    - Begin execution.

- Stream Playback:

  - The test will play the specified audio stream.
  - During playback, the user will be prompted to confirm whether the Surround Virtualizer Mode and levels are applied to the supported audio ports.

- User Interaction:

  - For each prompt:

    - The test will ask: "Is the Surround Virtualizer Mode and level applied to the supported ports? (Y/N)"
    - If the user detects the mode or level is applied, they should press **Y** (this passes the step).
    - If not, press **N** (this fails the step).

- Surround Virtualizer Mode Iteration:

  - The test will loop through the available Surround Virtualizer Modes and levels.
  - The user must confirm their observations for each combination.

- Completion:

  - Once all user inputs are collected, the test case will conclude and display a final result: PASS or FAIL.

### 12. dsAudio_test12_MS12MISteering.py

12.1 Platform Supported:

- Sink

12.2 User Input Required:

- Yes (This will be Automated later).

12.3 Acceptance Criteria:

- Play **Stream #1** and verify the MI Steering functionality for supported audio ports.

12.4 Expected Results:

- This test evaluates the MI Steering feature by enabling and disabling it. The user should observe a distinct change in the audio output when this functionality is applied.

12.5 Test Steps:

- Run the Test:

  - Select and execute the Python script: **`dsAudio_test12_MS12MISteering.py`**

- Download and Setup:

  - The test will:

    - Automatically download all necessary artifacts and the audio stream.
    - Copy them to the target directory on the device.
    - Begin execution.

- Stream Playback:

  - The test will play the specified audio stream.
  - During playback, the user will be prompted to confirm whether MI Steering (TRUE/FALSE) is applied to the supported audio ports.

- User Interaction:

  - For each prompt:

    - The test will ask: "Is MI Steering applied to the supported ports? (Y/N)"
    - If the user detects the MI Steering feature (TRUE/FALSE) is applied, they should press **Y** (this passes the step).
    - If not, press **N** (this fails the step).

- Completion:

  - Once all user inputs are gathered, the test will conclude with a final result: PASS or FAIL.

### 13. dsAudio_test13_MS12GraphicEqualizer.py

13.1 Platform Supported:

- Sink

13.2 User Input Required:

- Yes (This wil be Automated later).

13.3 Acceptance Criteria:

- Play **Stream #1** and verify the functionality of the Graphic Equalizer Modes for supported audio ports.

13.4 Expected Results:

- This test evaluates the different modes of the Graphic Equalizer. The user should be able to detect an audible change in the sound output when each mode is applied.

  - Graphic Equalizer Modes:

    - Mode 0: Off (No effect on audio output)
    - Mode 1: Open (Wider soundstage, emphasis on clarity)
    - Mode 2: Rich (Deeper, fuller sound profile)
    - Mode 3: Focused (More concentrated, detailed sound)

13.5 Test Steps:

- Run the Test:

  - Select and execute the Python script: **`dsAudio_test13_MS12GraphicEqualizer.py`**

- Download and Setup:

  - The test will:

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

  - The test will iterate through all Graphic Equalizer modes (Off, Open, Rich, Focused). The user should confirm their response for each mode.

- Completion:

  - Once all user inputs are collected, the test concludes with a final result: PASS or FAIL.

### 14. dsAudio_test14_MS12LEConfig.py

14.1 Platform Supported:

- Sink

14.2 User Input Required:

- Yes (This will be Automated later).

14.3 Acceptance Criteria:

- Play **Stream #4** and verify the functionality of the LE Config for supported audio ports.

14.4 Expected Results:

- This test evaluates the LE Config functionality. The user should notice changes in the audio output as the stream transitions from low frequency to high frequency when LE Config is enabled or disabled.

14.5 Test Steps:

- Run the Test:

  - Select and execute the Python script: **`dsAudio_test14_MS12LEConfig.py`**

- Download and Setup:

  - The test will:

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

  - Once all user inputs are collected, the test concludes with a final result: PASS or FAIL.

### 15. dsAudio_test15_ARCPort.py

15.1 Platform Supported:

- Sink

15.2 User Input Required:

- Yes (This will be Automaed later).

15.3 Acceptance Criteria:

- Verify the HDMI ARC/eARC port connection status.

15.4 Expected Results:

- This test checks the status of the HDMI ARC or eARC connection. The user will be required to connect or disconnect the ARC/eARC port and confirm the status.

15.5 Test Steps:

- Run the Test:

  - Select and execute the Python script: **`dsAudio_test15_ARCPort.py`**

- Download and Setup:

  - The test will:

    - Automatically download all necessary artifacts.
    - Copy them to the target directory on the device.
    - Start execution.

- ARC/eARC Port Interaction:

  - During the test, the user will be prompted to connect or disconnect the ARC/eARC port.
  - Once the action is performed, the user must press **ENTER** to proceed.

- User Confirmation:

  - The test may prompt the user multiple times to interact with the ARC/eARC connection, asking for confirmation of the status.

- Completion:

  - If all user interactions and responses are successfully received, the test will conclude with a final result: PASS or FAIL.

### 16. dsAudio_test16_ARCSAD.py

16.1 Platform Supported:

- Sink

16.2 User Input Required:

- Yes (This will be Automated later).

16.3 Acceptance Criteria:

- Verify the SAD (Short Audio Descriptor) functionality for the HDMI ARC audio port.

16.4 Expected Results:

- This test will send SAD values to the ARC device, and the user is required to verify that these values are correctly received and applied on the ARC device.

16.5 Test Steps:

- Run the Test:

  - Select and execute the Python script: **`dsAudio_test16_ARCSAD.py`**

- Download and Setup:

  - The test will:

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

  - The test will loop through multiple SAD values, and for each value, the user will be asked to confirm whether it was successfully transmitted and received.

- Completion:

  - Once all the SAD values have been processed and user responses are collected, the test case will conclude with a final result: PASS or FAIL based on the user's inputs.

### 17. dsAudio_test17_OutputMode.py

17.1 Platform Supported:

- Source
- Sink

17.2 User Input Required:

- Yes (This will be Automated later).

17.3 Acceptance Criteria:

- Play **Streams #7, #1, and #8** and verify the audio output mode for all supported audio ports.

17.4 Expected Results:

- This test will play different audio output modes for stremas on the supported audio ports. The user should verify the audio output format when various output modes are applied.

|    Stream                        |        OutputMode (Format)                |
|----------------------------------|-----------------------------------|
|tones_string_48k_stereo.wav | STEREO (PCM), PASSTHRU (PCM) |
|tones_string_48k_stereo.ac3 | STEREO (PCM), DD (DD), PASSTHRU (DD) |
|tones_string_48k_stereo.eac3| STEREO (PCM), DD (DD), DDPLUS (DD+), PASSTHRU (DD+) |

17.5 Test Steps:

- Run the Test:

  - Select and execute the Python script: **`dsAudio_test17_OutputMode.py`**

- Download and Setup:

  - The test will:

    - Download all necessary artifacts and streams.
    - Copy the files to the target directory.
    - Begin the test execution.

- Audio Output Verification:

  - The test will play the specified streams and prompt the user to verify if the output mode on the supported ports is in the correct format.
  - The user will be asked: "For the currently playing stream is the output mode on the supported port was in the correct format? (Y/N)"
  - If the format is correct for the output mode, the user should press **Y** (this passes the step).
  - If the format is incorrect, the user should press **N** (this fails the step).

- Iterate through Output Modes and Streams:

  - The test will loop through different streams and output modes, and for each combination, the user should confirm whether the audio format is correct.

- Completion:

  - Once all the streams and output modes have been tested and user responses are collected, the test case will conclude with a final result: PASS or FAIL based on the user’s inputs.

### 18. dsAudio_test18_AudioLevel.py

Platform Supported:

- Sink

User Input Required:

- Yes (This will be automated later).

Acceptance Criteria:

- Play the Stream #1 and verify the LE Config functionality for supported audio ports.

Expected Results:

- This test will Enable and disable LE Config, user should notice change in audio when these modes are applied.

Test Steps:

1. Select the Python file `dsAudio_test18_AudioLevel.py` and run it.
2. The test will download all required artifacts and streams and copy them to the target directory then start execution.
3. The test will play stream and asks user whether LEConfig (TRUE/FALSE) is applied to the supported ports (Y/N) if applied user should press Y (this pass the step) otherwise N (this fails the step).
4. The loop continues for different modes of Graphc Equalizer, and user should respond.
5. If the test receives all the user responses then this ends the test case with result.
