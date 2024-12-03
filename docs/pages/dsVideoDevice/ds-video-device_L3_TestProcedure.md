# dsVideoDevice HAL L3 Python Test Procedure

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Setting Up Test Environment](#setting-up-test-environment)
- [Streams Required](#streams-required)
- [Test Cases](#test-cases)
  - [dsVideoDevice_test1_FrameratePreChangePostChangeCallback_Verify.py](#dsvideodevice_test1_framerateprechangepostchangecallback_verifypy)
  - [dsVideoDevice_test2_SetAndGetZoomMode.py](#dsvideodevice_test2_setandgetzoommodepy)
  - [dsVideoDevice_test3_SetDisplayFramerate.py](#dsvideodevice_test3_setdisplayframeratepy)
  - [dsVideoDevice_test4_SetAndGetFRFMode.py](#dsvideodevice_test4_setandgetfrfmodepy)
  - [dsVideoDevice_L3_Runall_Sink.py](#dsVideoDevice_L3_Runall_Sinkpy)
  - [dsVideoDevice_L3_Runall_Source.py](#dsVideoDevice_L3_Runall_Sourcepy)
  
  
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

Example Rack configuration File: [example_rack_config.yml](../../../host/tests/configs/example_rack_config.yml)

For more details refer [RAFT](https://github.com/rdkcentral/python_raft/blob/1.0.0/README.md) and [example_rack_config.yml](https://github.com/rdkcentral/python_raft/blob/1.0.0/examples/configs/example_rack_config.yml)

In this file, update the configuration to define the console sessions for the `DUT` and the outbound settings:

|Console Session|Description|
|---------------|-----------|
|default|Downloads the streams required for test cases|
|ssh_player|Plays the stream required for test case|
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

Example Device configuration File: [deviceConfig.yml](../../../host/tests/configs/deviceConfig.yml)

For more details refer [RAFT](https://github.com/rdkcentral/python_raft/blob/1.0.0/README.md) and [example_device_config.yml](https://github.com/rdkcentral/python_raft/blob/1.0.0/examples/configs/example_device_config.yml)

Update below fileds in the device configuration file:
- Set the folder path for `target_directory` where `HAL` binaries will be copied onto the device.
- Specify the device profile path in `test/profile`
- Ensure the `platform` should match with the `DUT` `platform` in [Rack Configuration](#rack-configuration-file)

```yaml
deviceConfig:
    cpe1:
        platform: "linux"
        model: "uk"
        soc_vendor: "intel"
        target_directory: "/tmp/"  # Target Directory on device
        prompt: "" # Prompt string on console
        test:
            profile: "../../../../profiles/sink/Source_VideoDevice.yaml"
            streams_download_url: "<URL_Path>" #URL path from which the streams are downloaded to the device
```

#### Test Setup Configuration File

  Example Test Setup configuration File: [dsVideoDevice_L3_testSetup.yml](../../../host/tests/L3_TestCases/dsVideoDevice/dsVideoDevice_L3_testSetup.yml)

Provide the streams for each test case. This path is appended with `streams_download_url` entry from [Device Configuration File](#device-configuration-file)

If a test case requires multiple streams or needs to be validated using several streams, ensure that all necessary streams are added sequentially for that specific test case.

```yaml
dsVideoDevice:  
  description: "dsVideoDevice Device Settings test setup"
  assets:
    device:
      test1_FrameratePrePostChangeCallBack_Verify:
        streams:
      test2_ZoomMode:
        streams:
      test3_SetDisplayFramerate:
        streams:
      test4_FRFMode:
        streams:
```

#### Test Configuration

Example Test Setup configuration File: [dsVideoDevice_testConfig.yml](../../../host/tests/dsClasses/dsVideoDevice_testConfig.yml)

Update the execute command according to the device path where `HAL` binaries are copied.

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

- Play Streams `#1` `#2` `#3` `#4` `#5` `#6` `#7` `#8` of different fps sequentially and verify whether pre and post display framerate change callbacks triggered or not.

#### Expected Results - test01

- This test should verify the triggered pre and post callbacks whenever there is a framerate change.

#### Test Steps - test01

- Run the test file: **`dsVideoDevice_test1_FrameratePreChangePostChangeCallback_Verify.py`**
- Execution process:

  Upon execution, the test will:

  - Download all the required artifacts and streams.
  - Copy them to the target directory.
  - Automatically start the test execution.

- Iterating through supported display framerates and respective stream:

    The test sets the auto frame mode and verifies the pre- and post-frame rate change callbacks for different streams with varying frame rates.

- Completion and results:

  Upon verifying the supported framerates and based on the callback responses, the test will conclude and display the final result (PASS/FAIL).

### dsVideoDevice_test2_SetAndGetZoomMode.py

#### Platform Supported - test02

- Source

#### User Input Required - test02

Yes (This will be automated later).

#### Acceptance Criteria - test02

Play Stream `#9` and verify the supported zoom modes on device.

#### Expected Results - test02

The test will set the various zoom modes. The user should able to notice a change in device's output while different zoom modes are applied.

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

  The test will repeat for different supported zoom modes. On setting each zoom mode user need to verify whether it is applied to playback stream.

- User interaction for verification:

  For each iteration:

  - The test will ask: `Is the Zoom mode {zoomMode} applied in the device: {device}? (Y/N):`
  - The user should press **Y** if the zoom mode is applied correctly (this passes the step), or **N** if the zoom is not observed (this fails the step).

- Completion and results:

  Once all necessary user actions are completed, the test will evaluate the results and display whether the test Passed or Failed.

### dsVideoDevice_test3_SetDisplayFramerate.py

#### Platform Supported - test03

- Sink

#### User Input Required - test03

Yes (This will be automated later).

#### Acceptance Criteria - test03

Play Streams `#1` `#2` `#3` `#4` `#5` `#6` `#7` `#8` of different fps sequentially an verify the impact of the supported display framerates.

#### Expected Results - test03

This test will evaluate the supported display framerates. The user should notice a difference in video playback when different streamrates are applied.

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

```bash
  For example, to verify the display frame rate for weston-gl, run the following commands to check the refresh rate set on the display:

  export XDG_RUNTIME_DIR=/tmp
  westeros-gl-console get auto-frm-mode   //auto-frm-mode 0 - Disable, auto-frm-mode 1 - Enable
  westeros-gl-console get mode            //mode 3840x2160px60 - 60FPS
```

- Iterating through supported display framerates:

  The test will repeat for different supported display framerates.

- User Interaction:

  For each prompt, the user should assess the video playback output and respond:

  - `Is a displayRate {displayFramerate} with a streamRate {StreamFrameRate} acceptable? (Y/N):`, the user should press **Y** to confirm (this will pass the step).
  - If not, press **N** (this will fail the step).

- Completion and results:

  After receiving all user inputs, the test will conclude and provide a final result (PASS/FAIL).

### dsVideoDevice_test4_SetAndGetFRFMode.py

#### Platform Supported - test04

- Sink

#### User Input Required - test04

Yes (This will be automated later).

#### Acceptance Criteria - test04

Play Streams `#1` `#2` `#3` `#4` `#5` `#6` `#7` `#8` sequentially and verify the video playback and Framerate with `FRF` mode enabled.

#### Expected Results - test04

The test evaluates the effect of `FRF` mode on video playback. The user should notice a difference in video output for different frame rate streams when Auto `FRF` mode is enabled.

#### Test Steps - test04

- Run the Test:

  - Select and run the Python script: **`dsVideoDevice_test4_SetAndGetFRFMode.py`**

- Download and Setup:

    The test will automatically download all necessary artifacts and streams, and copy them to the target directory on the device.

- Stream Playback:

  - The test will play the designated video stream.
  - During playback, the test will prompt the user to verify whether `FRF` mode is applied based on video playback.

- User Interaction:

  For each prompt, the user should assess the video playback output and respond:

  - The test will ask: `Has the display refresh rate been changed to match Stream Framerate:{streamFramerate} (Suggested mode is {expectedMode})? (Y/N):`, the user should press **Y** to confirm the experience (this will pass the step).
  - If not, press **N** (this will fail the step).

```bash
  For example, to verify the display frame rate for weston-gl, run the following commands to check the refresh rate set on the display:

  export XDG_RUNTIME_DIR=/tmp
  westeros-gl-console get auto-frm-mode   //auto-frm-mode 0 - Disable, auto-frm-mode 1 - Enable
  westeros-gl-console get mode            //mode 3840x2160px60 - 60FPS
```

- Completion:

  After receiving all necessary user inputs, the test case will conclude and display the final result: PASS or FAIL.

### dsVideoDevice_L3_Runall_Sink.py

This python file runs all the tests supported by `sink` devices

```bash
python dsVideoDevice_L3_Runall_Sink.py --config </PATH>/ut/host/tests/configs/example_rack_config.yml --deviceConfig </PATH>/ut/host/tests/configs/deviceConfig.yml
```

### dsVideoDevice_L3_Runall_Source.py

This python file runs all the tests supported by `source` devices

```bash
python dsVideoDevice_L3_Runall_Source.py --config </PATH>/ut/host/tests/configs/example_rack_config.yml --deviceConfig </PATH>/ut/host/tests/configs/deviceConfig.yml
```