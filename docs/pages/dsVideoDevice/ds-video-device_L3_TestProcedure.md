# dsVideoDevice HAL L3 Python Test Procedure

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Setting Up Test Environment](#setting-up-test-environment)
- [Streams Required](#streams-required)
- [Test Cases](#test-cases)
  - [dsVideoDevice_test1_FrameratePreChangePostChangeCallback_Verify.py](#dsVideoDevice_test1_FrameratePreChangePostChangeCallback_Verifypy)
  - [dsVideoDevice_test2_SetAndGetZoomMode.py](#dsVideoDevice_test2_SetAndGetZoomModepy)
  - [dsVideoDevice_test3_SetDisplayFramerate.py](#dsVideoDevice_test3_SetDisplayFrameratepy)
  - [dsVideoDevice_test4_SetAndGetFRFMode.py](#dsVideoDevice_test4_SetAndGetFRFModepy)
  
## Acronyms, Terms and Abbreviations

- `HAL`  \- Hardware Abstraction Layer
- `L3`   \- Level 3 Testing
- `DUT`  \- Device Under Test
- `RAFT` \- Rapid Automation Framework for Testing
- `YAML` \- YAML Ain't Markup Language
- `DS`   \- Device Settings
- `FPS`  \- Frames Per Second.
- `FRF`  \- Frame Rate Frequency
- `HEVC` \- High Efficiency Video Coding

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
      profile: "../../../../profiles/sink/Sink_4K_VideoDevice.yaml"
      player:
        tool: "gstreamer"
        prerequisites:
          - export xxxx    # Pre-commands required to play the stream

```

#### Test Setup Configuration File

Example Test Setup configuration File: `ut/host/tests/L3_TestCases/dsVideoDevice/dsVideoDevice_L3_testSetup.yml`

Update the artifact paths from which the binaries should be copied to the device.

Set the execution paths and provide the stream paths for each test case.

If a test case requires multiple streams or needs to be validated using several streams, ensure that all necessary streams are added sequentially for that specific test case.

```yaml
dsVideoDevice:
  description: "dsVideoDevice Device Settings test setup"
  assets:
    device:
      defaults: &defaults
        artifacts:
          - "<path>/bin/hal_test"
          - "<path>/bin/libut_control.so"
          - "<path>/bin/Sink_4k_VideoDevice.yaml"
          - "<path>/bin/run.sh"
        execute:
          - "chmod +x /opt/HAL/dsVideoDevice_L3/hal_test"
          - "chmod +x /opt/HAL/dsVideoDevice_L3/run.sh"
          - cp -rf /usr/lib/libdshal.so /opt/HAL/dsVideoDevice_L3/
          - "ln -s /usr/lib/libds-hal.so /opt/HAL/dsVideoDevice_L3/libdshal.so"
      test1_FrameratePrePostChangeCallBack_Verify:
        <<: *defaults
      test2_ZoomMode:
        <<: *defaults
        streams:
          - "<URL Path>/streams/BounceBall_3840x2160_23.98fps.mp4"
      test3_SetDisplayFramerate:
        <<: *defaults
        streams:
          - "<URL Path>/streams/BounceBall_3840x2160_23.98fps.mp4"
          - "<URL Path>/streams/BounceBall_3840x2160_24fps.mp4"
      test4_FRFMode:
        <<: *defaults
        streams:
          - "<URL Path>/streams/BounceBall_3840x2160_23.98fps.mp4"
          - "<URL Path>/streams/BounceBall_3840x2160_24fps.mp4"

```

#### Test Suite Configuration

Example Test Setup configuration File: `ut/host/tests/dsClasses/dsVideoDevice_test_suite.yml`

Update the execute command according to the device path where `HAL` binaries are copied.

```yaml
dsVideoDevice:
  description: "dsVideoDevice Device Settings testing profile"
  test:
    execute: "/tmp/run.sh -p /tmp/Sink_4k_VideoDevice.yaml"
    type: UT-C  # Cunit tests (UT-C)

```

## Run Test Cases

Once the environment is set up, you can execute the test cases with the following command

```bash
python <TestCaseName.py> --config </PATH>/ut/host/tests/configs/example_rack_config.yml --deviceConfig </PATH>/ut/host/tests/configs/deviceConfig.yml
```

## Streams Required

Refer [ds-video-device_L3_Low-Level_TestSpecification.md](./ds-video-device_L3_Low-Level_TestSpecification.md#video-streams-requirement) for the stream details


## Test Cases

### dsVideoDevice_test1_FrameratePreChangePostChangeCallback_Verify.py

#### Platform Supported - test01

- Sink

#### User Input Required - test01

- No

#### Acceptance Criteria - test01

- Verify the display framerate change with pre and post change callbacks.

#### Expected Results - test01

- This test checks whether the callback is triggered before and after when the display framerate changes.

#### Test Steps - test01

- Run the test file: **`dsVideoDevice_test1_FrameratePreChangePostChangeCallback_Verify.py`**
- Execution process:

  Upon execution, the test will:

  - Download all the required artifacts.
  - Copy them to the target directory.
  - Automatically start the test execution.

- Iterating through supported display framerates:

  The test will repeat for different supported display framerates. Before that set the FRF mode to `Disable`. And, then on setting each framerates callback need to be triggered accordingly.

- Completion and results:

  After all iterations are complete and based on the callback responses, the test will conclude and display the final result (PASS/FAIL).

### dsVideoDevice_test2_SetAndGetZoomMode.py

#### Platform Supported - test02

- Source

#### User Input Required - test0

Yes (This will be automated later).

#### Acceptance Criteria - test02

Verify the changes in zoom modes across the supported zoom modes for designated video streams.

#### Expected Results - test02

The test will evaluate the various zoom modes. The user should notice a zoom mode change in video playback as different zoom modes are applied.

#### Test Steps - test02

- Select the test file:

  - Run the Python script **`dsVideoDevice_test2_SetAndGetZoomMode.py`**

- Execution process:

  The test will:

  - Download all the required artifacts and video streams.
  - Copy them to the target directory.
  - Automatically start the test execution.

- Play the video stream:

  Test starts the video stream playback specified in the test setup configuration file.

- Iterating through supported zoom modes:

  The test will repeat for different supported zoom modes. On setting each zoom mode user need to verify it is applied in video stream.

- User interaction for verification:

  For each iteration:

  - The test will ask: "Is the selected Zoom mode applied in the device's output? (Y/N):"

- Completion and results:

  Once all necessary user actions are completed, the test will evaluate the results and display whether the test Passed or Failed.

### dsVideoDevice_test3_SetDisplayFramerate.py

#### Platform Supported - test03

- Sink

#### User Input Required - test03

Yes (This will be automated later).

#### Acceptance Criteria - test03

Verify the impact of the supported display framerates for **Stream #2**.

#### Expected Results - test03

This test will evaluate the supported display framerates. The user should notice a video playback when display framerates are applied.

#### Test Steps - test03

- Select the test file:  

  - Run the Python script **`dsVideoDevice_test3_SetDisplayFramerate.py`**

- Execution process:

  The test will:

  - Download all required artifacts and video streams.
  - Copy them to the target directory.
  - Automatically begin the test execution.

- Stream Playback:

  - The test will play the designated video stream.
  - During playback, the test will prompt the user to verify whether displayRate with a streamRate acceptable.

- Iterating through supported display framerates:

  The test will repeat for different supported framerates. Before that set the FRF mode to `Disable`. And, then on setting each displayRate user need to verify it is applied in video stream.

- User Interaction:

  For each prompt, the user should assess the video playback output and respond:

  - Is a displayRate with a streamRate acceptable? (Y/N):, the user should press **Y** to confirm (this will pass the step).
  - If not, press **N** (this will fail the step).

- Completion and results:

  After receiving all user inputs, the test will conclude and provide a final result (PASS/FAIL).

### dsVideoDevice_test4_SetAndGetFRFMode.py

#### Platform Supported - test04

- Sink

#### User Input Required - test04

Yes (This will be automated later).

#### Acceptance Criteria - test04

Verify the video playback with FRF mode enabled/disabled for all supported video device for **Stream #1**.

#### Expected Results - test04

The test evaluates the effect of FRF mode on video playback. The user should notice a clear difference in video output when FRF is toggled between Enable and Disable.

#### Test Steps - test04

- Run the Test:

  - Select and run the Python script: **`dsVideoDevice_test4_SetAndGetFRFMode.py`**

- Download and Setup:

  The test will automatically download all necessary artifacts and streams, and copy them to the target directory on the device.

- Stream Playback:

  - The test will play the designated video stream.
  - During playback, the test will prompt the user to verify whether FRF mode is applied based on video playback.

- User Interaction:

  For each prompt, the user should assess the video playback output and respond:

  - The test will ask: Has the display refresh rate been changed to expectedMode (Y/N):, the user should press **Y** to confirm the experience (this will pass the step).
  - If not, press **N** (this will fail the step).

- Completion:

  After receiving all necessary user inputs, the test case will conclude and display the final result: PASS or FAIL.
