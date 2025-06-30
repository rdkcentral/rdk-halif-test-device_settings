# Device Settings Video Port L3 Test Case and Procedure Documentation

## Table of Contents

- [Overview](#overview)
- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [References](#references)
- [Setting Up Test Environment](#setting-up-test-environment)
- [Test Case Procedure](#test-case-procedure)
  - [dsVideoPort_test1_VerifyVideoContent_Format_Callback.py](#dsvideoport_test1_verifyvideocontent_format_callbackpy)
  - [dsVideoPort_test2_EnableDisableAndVerifyPortStatus.py](#dsvideoport_test2_enabledisableandverifyportstatuspy)
  - [dsVideoPort_test3_VerifyHDCP_Version.py](#dsvideoport_test3_verifyhdcp_versionpy)
  - [dsVideoPort_test4_VerifyResolution.py](#dsvideoport_test4_verifyresolutionpy)
  - [dsVideoPort_test5_VerifyHDCP_Callback.py](#dsvideoport_test5_verifyhdcp_callbackpy)
  - [dsVideoPort_test6_VerifyVideoContentFormats.py](#dsvideoport_test6_verifyvideocontentformatspy)
  - [dsVideoPort_test7_ResetToSDRMode.py](#dsvideoport_test7_resettosdrmodepy)
  - [dsVideoPort_test8_VerifyColorDepth.py](#dsvideoport_test8_verifycolordepthpy)
  - [dsVideoPort_test9_VerifyBackgroundColor.py](#dsvideoport_test9_verifybackgroundcolorpy)

## Overview

This document describes the L3 Test case Procedure Documentation for the Device Settings Video Port module.

### Acronyms, Terms and Abbreviations

- `HAL` \- Hardware Abstraction Layer, may include some common components
- `UT`  \- Unit Test(s)
- `OEM` \- Original Equipment Manufacture
- `SoC` \- System on a Chip
- `HDMI`\- High-Definition Multimedia Interface
- `HDCP`\- High-bandwidth Digital Content Protection
- `HDR` \- High Dynamic Range
- `HLG` \- Hybrid Log-Gamma
- `SDR` \- Standard Dynamic Range
- `ALLM` \- Auto Low Latency Mode
- `Y`   \- yes supported
- `NA`  \- Not Supported

### References

- `High Level Test Specification` - [dsVideoPort High Level TestSpec](ds-video-port_High-Level_TestSpec.md)
- `dsVideoPort L3 Low Level Test Specification` - [dsVideoPort L3 LowLevel TestSpec](ds-video-port_L3_Low-Level_TestSpecification.md)

## Setting Up Test Environment

To execute `HAL` `L3` Python test cases, need a Python environment. Follow these steps mentioned in [HPK Public Documentation](https://github.com/rdkcentral/rdk-hpk-documentation/blob/main/README.md)

### Update Configuration Files

#### Rack Configuration File

- It identifies the rack configuration and platform used. We need to update our target device specif information in the rackconfig.yaml. In this file, update the configuration to define the console sessions for the device under test (DUT)
Example Rack configuration File: `ut/host/tests/configs/example_rack_config.yml`
  - For more details refer [RAFT](https://github.com/rdkcentral/python_raft/blob/1.0.0/README.md) and [example_rack_config.yml](https://github.com/rdkcentral/python_raft/blob/1.0.0/examples/configs/example_rack_config.yml)

In this file, update the configuration to define the console sessions for the `DUT` and the outbound settings:

|Console Session|Description|
|---------------|-----------|
|default | Downloads the streams required for test cases.|
|ssh_player | Plays the stream required for test case.|
|ssh_hal_test | Executes the HAL binary for the test case.|

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

  Example Device configuration File: `ut/host/tests/configs/deviceConfig.yml`

For more details refer [RAFT](https://github.com/rdkcentral/python_raft/blob/1.0.0/README.md) and [example_device_config.yml](https://github.com/rdkcentral/python_raft/blob/1.0.0/examples/configs/example_device_config.yml)

Update the target directory where `HAL` binaries will be copied into the device. Also, map the profile to the source/sink settings `YAML` file path.

Ensure the platform should match with the `DUT` platform in [Rack Configuration](#rack-configuration-file)

```yaml
deviceConfig:
    cpe1:
        platform: "xi-one"
        model: "uk"
        soc_vendor: "realtek"
        target_directory: "/opt/"  # Target Directory on device
        prompt: "" # Prompt string on console
        test:
            #TODO: Use the single profile file which contains all details (ds, hdmi, etc)
            profile: "../../../../profiles/source/Source_4K_VideoPort.yaml"
            streams_download_url: "" #URL path from which the streams are downloaded to the device

```

- Example Device Config file: [deviceConfig.yml](../../../host/tests/configs/deviceConfig.yml).

#### Test Setup Configuration File

Each test case requires a stream name to be provided if required. If a test case involves multiple streams or requires validation using several streams, ensure that all necessary streams are added sequentially under the specific test case.

The URL paths for the streams are defined in the [deviceConfig.yml](../../../host/tests/configs/deviceConfig.yml) file, under the parameter `streams_download_url`

- Example configuration file [dsVideoPort_L3_testSetup.yml](../../../host/tests/L3_TestCases/dsVideoPort/dsVideoPort_L3_testSetup.yml).

#### Test Suite Configuration

Update the execute command according to the device path where `HAL` binaries are copied and Update the test suite for each level test case

- Example configuration file: [dsVideoPort_testConfig.yml](../../../host/tests/dsClasses/dsVideoPort_testConfig.yml).

## Run Test Cases

Once the environment is set up, you can execute the test cases with the following command

```bash
python <TestCaseName.py> --config </PATH>/ut/host/tests/configs/example_rack_config.yml --deviceConfig </PATH>/ut/host/tests/configs/deviceConfig.yml
```

## Test Case Procedure

### dsVideoPort_test1_VerifyVideoContent_Format_Callback.py

**Overview:**

This test plays pre-defined streams in various video content formats (HDR, HLG, Dolby Vision, etc.) and checks if the appropriate callbacks are triggered when the video format changes.

**Platform Supported:**

Sink

**User Input Required:**

No

**Acceptance Criteria:**

Play the pre-defined streams with different video content formats (HDR, HLG, Dolby Vision, etc.) and check that the callbacks are triggered when the video content format changes.

**Expected Results:**

The test will download and play multiple streams, each corresponding to a specific video format, and verify that the expected callbacks are triggered. After playback, the streams will be removed, and the test will pass if all expected callbacks are received.

**Test Steps:**

- Run the Python file dsVideoPort_test1_VerifyVideoContent_Format_Callback.py with the required configuration:

```bash
dsVideoPort_test1_VerifyVideoContent_Format_Callback.py --config /host/tests/configs/example_rack_config.yml --deviceConfig /host/tests/configs/deviceConfig.yml
```

- The test will download the required assets and begin execution, playing streams in various formats.
- For each video format, the test will verify that the appropriate callbacks are triggered:
  - NONE Video Format Callback
  - `HDR10` Video Format Callback
  - `HLG` Video Format Callback
  - `Dolby Vision` Video Format Callback
  - `HDR10PLUS` Video Format Callback
  - `SDR` Video Format Callback
- The test will pass if all the required callbacks are detected; otherwise, it will fail.

### dsVideoPort_test2_EnableDisableAndVerifyPortStatus.py

**Overview:**

This test enables and disables video ports, requiring manual user interaction to verify if the video is displayed when the port is enabled, and if the display is blank when the port is disabled. The user is asked to confirm the video playback status.

**Platform Supported:**

Source, Sink

**User Input Required:**

Yes:User input is required to verify whether the video is playing or not with prompt question `Is Video Display on the port? (Y/N)` (This will be automated later).

**Acceptance Criteria:**

Verify the Display by enabling and disable each supported video port.

**Expected Results:**

The video is visible when the port is enabled and goes blank when the port is disabled. User responses (Y/N) will determine if the test passes.

**Test Steps:**

- Run the Python file `dsVideoPort_test2_EnableDisableAndVerifyPortStatus.py` with the appropriate configuration:

```bash
dsVideoPort_test2_EnableDisableAndVerifyPortStatus.py --config /host/tests/configs/example_rack_config.yml --deviceConfig /host/tests/configs/deviceConfig.yml
```

- The test will download all required artifacts and streams, copy them to the target directory, and start execution.
- The test will play the stream, enable the video port, and ask the user to confirm the video playback status. It will then disable the port and ask the user to confirm that the display is blank.

### dsVideoPort_test3_VerifyHDCP_Version.py

**Overview:**

This test is designed to verify the correct `HDCP` version used during video playback. The test will specifically enable `HDCP` 2.2 encryption and ask the user to confirm the version displayed using an AV analyzer connected to the video output. The user must verify if the correct `HDCP` version is being used.

**Platform Supported:**

Source, Sink

**User Input Required:**

Yes: The user is required to verify the `HDCP` version on an external AV analyzer connected to the device. (This will be automated later).

**Acceptance Criteria:**

The test must successfully enable HDCP 2.2 encryption, and the user must confirm that HDCP 2.X is displayed on the AV analyzer for the test to pass.

**Expected Results:**

The test will enable HDCP 2.2 encryption on the video output. The user will confirm the correct HDCP version using a supported AV analyzer, ensuring proper encryption is applied.

**Test Steps:**

- Run the Python file `dsVideoPort_test3_VerifyHDCP_Version.py` with the appropriate configuration:

```bash
dsVideoPort_test3_VerifyHDCP_Version.py --config /host/tests/configs/example_rack_config.yml --deviceConfig /host/tests/configs/deviceConfig.yml
```

- Download and copy all required assets to the target directory.
- Enable HDCP 2.2 encryption on the video output.
- Prompt the user to verify that HDCP 2.X is displayed on the AV analyzer.
- The test will pass if the user confirms that the correct HDCP version is being used.

### dsVideoPort_test4_VerifyResolution.py

**Overview:**

This test verifies the resolution settings supported by the source device. It sets different resolutions and checks additional parameters, including aspect ratio, SS mode, frame rate, and scan mode. The user must confirm the accuracy of these settings using an AV analyzer connected to the video output. The test involves manual verification of video parameters displayed on the AV analyzer.

**Platform Supported:**

Source

**User Input Required:**

Yes: The user must verify the video resolution and other attributes (aspect ratio, SS mode, frame rate, scan mode) using a connected AV analyzer. (This will be automated later).

**Acceptance Criteria:**

The user verifies that the correct resolution, aspect ratio, SS mode, frame rate, and scan mode are displayed on the AV analyzer for each tested video resolution.

**Expected Results:**

The test sets various resolutions on the video output and prompts the user to confirm the correctness of the settings via an AV analyzer. If all settings match, the test will pass

**Test Steps:**

- Run the Python file `dsVideoPort_test4_VerifyResolution.py` with the appropriate configuration:

```bash
dsVideoPort_test4_VerifyResolution.py --config /host/tests/configs/example_rack_config.yml --deviceConfig /host/tests/configs/deviceConfig.yml
```

- The test will download the required artifacts and streams, then copy them to the target directory.
- For each supported resolution, the test will set the following parameters and prompt the user for confirmation using an AV analyzer:
  - Resolution (e.g., 720x480, 1920x1080)
  - Aspect Ratio (e.g., 4:3, 16:9)
  - SS Mode (e.g., 2D, 3D)
  - Frame Rate (e.g., 29.97, 60 Hz)
  - Scan Mode (e.g., Interlaced, Progressive)
- The test will repeat step 3 for all supported resolutions.
- If the user confirms the correct settings for all resolutions and parameters, the test will pass.

### dsVideoPort_test5_VerifyHDCP_Callback.py

**Overview:**

This test verifies `HDCP` status using callbacks during HDMI plug and unplug events. The test will ask the user to physically disconnect and reconnect the `HDMI` cable and then verify whether the appropriate `HDCP` callbacks for "plug" and "unplug" events are received and logged.

**Platform Supported:**

Source

**User Input Required:**

Yes: The user is required to unplug and plug the `HDMI` cable and confirm actions using the AV analyzer. (This will be automated in future versions.)

**Acceptance Criteria:**

- The user successfully unplugs and plugs the `HDMI` cable.
- The system receives the appropriate `HDCP` status callbacks: "HDMI Unplug Callback found" and "HDMI Plug Callback found."

**Expected Results:**

- The test prompts the user to physically disconnect and reconnect the HDMI cable.
- The system detects the HDMI plug/unplug events and verifies the corresponding HDCP callbacks.

**Test Steps:**

- Run the Python file `dsVideoPort_test5_VerifyHDCP_Callback.py` with the appropriate configuration:

```bash
dsVideoPort_test5_VerifyHDCP_Callback.py --config /host/tests/configs/example_rack_config.yml --deviceConfig /host/tests/configs/deviceConfig.yml
```

- The test will automatically download the necessary artifacts and streams, copy them to the target directory, and begin execution.
- The test prompts the user to perform the following actions:
  - Unplug the `HDMI` cable when prompted with:
    - `UnPlug the HDMI Cable? (Y/N):`
    - The user must unplug the `HDMI` cable and confirm by entering 'y'.
  - Plug the HDMI cable back in when prompted with:
    - `Plug the HDMI Cable? (Y/N):`
    - The user must plug the `HDMI` cable and confirm by entering 'y'.
- The user must also confirm that the following HDCP callbacks are received and logged:
  - `HDMI Unplug Callback found`
  - `HDMI Plug Callback found`

### dsVideoPort_test6_VerifyVideoContentFormats.py

**Overview:**

This test verifies the supported `HDR` (High Dynamic Range) video content formats by playing various predefined streams and checking their formats via callbacks. The user will confirm the displayed formats using an AV analyzer.

**Platform Supported:**

Source

**User Input Required:**

Yes: The user needs to verify HDR formats using an AV analyzer(This will be automated in future versions with callbacks.)

**Acceptance Criteria:**

- The test will play streams in different HDR formats.
- The user must verify and confirm the video content format displayed on the analyzer for each HDR mode.

**Expected Results:**

- The test will automatically download and play predefined video streams in different HDR content formats.
- The user must confirm the displayed format using an AV analyzer for formats like HDR10, HLG, Dolby Vision, and HDR10+.
- The test passes if the user confirms all HDR formats were displayed correctly.

**Test Steps:**

- Run the Python file `dsVideoPort_test6_VerifyVideoContentFormats.py` with the appropriate configuration:

```bash
dsVideoPort_test6_VerifyVideoContentFormats.py --config /host/tests/configs/example_rack_config.yml --deviceConfig /host/tests/configs/deviceConfig.yml
```

- The test will automatically download the necessary artifacts and streams, copy them to the target directory, and begin execution.
- The test will play streams in various HDR content formats and prompt the user to confirm the format displayed on the analyzer:

  - Is dsHDRSTANDARD_HDR10 displayed on the analyzer? (Y/N)
  - Is dsHDRSTANDARD_HLG displayed on the analyzer? (Y/N)
  - Is dsHDRSTANDARD_DolbyVision displayed on the analyzer? (Y/N)
  - Is dsHDRSTANDARD_HDR10PLUS displayed on the analyzer? (Y/N)

### dsVideoPort_test7_ResetToSDRMode.py

**Overview:**

This test verifies the ability to reset the video output from `HDR` to `SDR` . The user will confirm if the video format has changed successfully from `HDR` to `SDR` using a display analyzer.

**Platform Supported:**

Source

**User Input Required:**

Yes: The user will verify whether the video playback has switched from HDR to SDR. (This will be automated in future versions.)

**Acceptance Criteria:**

- The test will play an HDR stream, and the video content format will be reset to SDR.
- The user must verify that the playback format changes from HDR to SDR.
- The test will query the user with: "Is Video Display on the port?" to confirm if SDR mode is enabled.

**Expected Results:**

- The test will download and play an HDR stream.
- It will switch the playback from HDR to SDR mode.
- The user must confirm that the video display is now in SDR mode using an analyzer or visual confirmation.

**Test Steps:**

- Run the Python file `dsVideoPort_test7_ResetToSDRMode.py` with the appropriate configuration:

```bash
dsVideoPort_test7_ResetToSDRMode.py --config /host/tests/configs/example_rack_config.yml --deviceConfig /host/tests/configs/deviceConfig.yml
```

- The test will automatically download the necessary artifacts and streams, copy them to the target directory, and begin execution.
- The test will play `HDR` video content and switch the playback output to `SDR` mode. The user must verify that the output has changed to `SDR`:
  - Is Video Playback in `HDR`on the port? (Y/N):
  - If the answer is "Yes", the test passes.

### dsVideoPort_test8_VerifyColorDepth.py

**Overview:**

This test verifies that the video output color depth on supported video ports can be correctly set and confirmed by the user using an AV analyzer or through command-line verification. The test focuses on verifying the 8-bit color depth configuration, which the source device supports.

**Platform Supported:**

Source

**User Input Required:**

Yes: The user will verify if the color depth has been correctly set using an AV analyzer or command-line output. (This will be automated in future versions.)

**Acceptance Criteria:**

- The test will set the color depth to 8-bit, and the user will confirm if the output has been set correctly.
- The user can verify this by inspecting the AV analyzer or running the command HdmiClient get-res to check the color depth.

**Expected Results:**

- The test will set the color depth to 8-bit (supported by the source device).
- The user will confirm if the video output matches the set color depth:
  - Is dsDISPLAY_COLORDEPTH_10BIT displayed on the Analyzer (Y/N)?

**Test Steps:**

- Run the Python file `dsVideoPort_test8_VerifyColorDepth.py` with the appropriate configuration:

```bash
dsVideoPort_test8_VerifyColorDepth.py --config /host/tests/configs/example_rack_config.yml --deviceConfig /host/tests/configs/deviceConfig.yml
```

- The test will automatically download the necessary artifacts and streams, copy them to the target directory, and begin execution.
- The test will configure the color depth to 8-bit, which is supported by the source device.
- The user will be asked to confirm if the color depth has been correctly set by checking the AV analyzer or running the command:
  - `Is dsVIDEO_BGCOLOR_BLUE displayed on the Analyzer (Y/N)?`
- If the answer is `Yes,` the test will pass.

### dsVideoPort_test9_VerifyBackgroundColor.py

**Overview:**

This test verifies that the video output background color on supported video ports can be correctly set and confirmed by the user. The test allows the user to select a background color from a supported list and asks for confirmation of the color setting via an AV analyzer.

**Platform Supported:**

Source

**User Input Required:**

Yes: The user will verify if the background color has been correctly set using an AV analyzer.(This will be automated in future versions.)

**Acceptance Criteria:**

he test will set the background color from the supported list and ask the user to confirm whether the color is displayed correctly.

**Expected Results:**

- The test will set the background color from the supported list and ask the user to verify each color:
  - Is dsVIDEO_BGCOLOR_BLUE displayed on the Analyzer (Y/N)?
  - Is dsVIDEO_BGCOLOR_BLACK displayed on the Analyzer (Y/N)?
  - Is dsVIDEO_BGCOLOR_NONE displayed on the Analyzer (Y/N)?
- If the user answers "Yes" to all three questions, the test will pass.

**Test Steps:**

- Run the Python file `dsVideoPort_test9_VerifyBackgroundColor.py` with the appropriate configuration:

```bash
dsVideoPort_test9_VerifyBackgroundColor.py --config /host/tests/configs/example_rack_config.yml --deviceConfig /host/tests/configs/deviceConfig.yml
```

- The test will automatically download the necessary artifacts and streams, copy them to the target directory, and begin execution.
- The test will set the background color from the supported list and prompt the user for confirmation. The user will be asked to verify the following colors:
  - Is dsVIDEO_BGCOLOR_BLUE displayed on the Analyzer (Y/N)?
  - Is dsVIDEO_BGCOLOR_BLACK displayed on the Analyzer (Y/N)?
  - Is dsVIDEO_BGCOLOR_NONE displayed on the Analyzer (Y/N)?
- If the answers to all three questions are "Yes," the test will pass.

### dsVideoPort_test10_VerifyALLM_Mode.py

**Overview:**

This test is designed to verify the functionality of the dsSetAllmEnabled API in enabling or disabling Auto Low Latency Mode (`ALLM`) for an HDMI output port. The test will check the API's ability to correctly toggle ALLM based on the sink device's compatibility with HDMI 2.1 specifications. Users will validate the `ALLM` status using an AV analyzer.

**Platform Supported:**

Source

**User Input Required:**

Yes: The user is required to verify the `ALLM` mode on an external AV analyzer connected to the device. (This will be automated later).

**Acceptance Criteria:**

The test must successfully enable/disable ALLM mode, and the user must confirm that respective mode is displayed on the AV analyzer for the test to pass.

**Expected Results:**

The test will enable/disable ALLM mode on the HDMI output video port. The user will confirm the correct ALLM mode using a supported AV analyzer.

**Note:** Currently unable to verify this test case.

**Test Steps:**

- Run the Python file `dsVideoPort_test10_VerifyALLM_Mode.py` with the appropriate configuration:

```bash
dsVideoPort_test10_VerifyALLM_Mode.py --config /host/tests/configs/example_rack_config.yml --deviceConfig /host/tests/configs/deviceConfig.yml
```

- Download and copy all required assets to the target directory.
- Enable ALLM mode.
- Prompt the user to verify that respective ALLM mode is displayed on the AV analyzer.
- The test will pass if the user confirms that the ALLM mode is enabled.
- Disable ALLM mode.
- Prompt the user to verify that respective ALLM mode is displayed on the AV analyzer.
- The test will pass if the user confirms that the ALLM mode is disabled.
