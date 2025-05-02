# Device Settings Display L3 Test Case and Procedure Documentation

## Table of Contents

- [Overview](#overview)
- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [References](#references)
- [Setting Up Test Environment](#setting-up-test-environment)
- [Run Test Cases](#run-test-cases)
- [Test Case Procedure](#test-case-procedure)
  - [dsDisplay_test01_VerifyDisplayConnectCallBackTest.py](#dsdisplay_test01_verifydisplayconnectcallbacktestpy)
  - [dsDisplay_test02_TestVerifyDisplayEdid.py](#dsdisplay_test02_testverifydisplayedidpy)
  - [dsDisplay_test03_AspectRatioVerificationTest.py](#dsdisplay_test03_aspectratioverificationtestpy)
  - [dsDisplay_test04_TestVerifyDisplayEdidBytes.py](#dsdisplay_test04_testverifydisplayedidbytes)
  - [dsDisplay_test07_VerifyALLM_Mode.py](#dsdisplay_test07_verifyallm_modepy)
  - [dsDisplay_test05_AVIContentTypeVerificationTest.py](#dsdisplay_test05_avicontenttypeverificationtest)
  - [dsDisplay_test06_AVIScanInfoVerificationTest.py](#dsdisplay_test06_aviscaninfoverificationtest)
  - [dsDisplay_L3_Runall_Source.py](#dsdisplay_l3_runall_sourcepy)
  - [dsDisplay_L3_Runall_Sink.py](#dsdisplay_l3_runall_sinkpy)

## Overview

This document describes the VTS Level 3 Test scenarios and the execution process for the Device Setting Display Module.

### Acronyms, Terms and Abbreviations

- `HAL`  \- Hardware Abstraction Layer, may include some common components
- `UT`   \- Unit Test(s)
- `OEM`  \- Original Equipment Manufacture
- `SoC`  \- System on a Chip
- `HDMI` \- High-Definition Multimedia Interface
- `EDID` \- Extended Display Identification Data
- `RAFT` \- Rapid Automation Framework for Testing
- `Y`    \- yes supported
- `NA`   \- Not Supported

### References

- `High Level Test Specification` - [dsDisplay High Level TestSpec](ds-display-high-Level_TestSpec.md)

- `dsDisplay L3 Low Level Test Specification` - [dsDisplay L3 Low Level TestSpec](ds-display_L3_Low-Level_TestSpecification.md)

## Setting Up Test Environment

To execute `HAL` `L3` Python test cases, need a Python environment. Follow these steps mentioned in [HPK Public Documentation](https://github.com/rdkcentral/rdk-hpk-documentation/blob/main/README.md)

### Update Configuration Files

#### Rack Configuration File

Example Rack configuration File: [example_rack_config.yml](../../../host/tests/configs/example_rack_config.yml)

For more details refer [RAFT](https://github.com/rdkcentral/python_raft/blob/1.0.0/README.md) and [example_rack_config.yml](https://github.com/rdkcentral/python_raft/blob/1.0.0/examples/configs/example_rack_config.yml)

In this file, update the configuration to define the console sessions for the `DUT` and the outbound settings:

|Console Session|Description|
|---------------|-----------|
|default | Downloads the streams required for test cases.|
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

Update the target directory where `HAL` binaries will be copied into the device. Also, map the profile to the source/sink settings `YAML` file path.

Ensure the platform should match with the `DUT` platform in [Rack Configuration](#rack-configuration-file)

```yaml
deviceConfig:
  cpe1:
    platform: "stb"    # Must match the platform in example_rack_config.yml
    model: "uk"
    target_directory: "/tmp"  # Path where HAL binaries are copied in device
    test:
      profile: "../../../../profiles/source/Source_4K_Display.yaml"
      player:
        tool: "gstreamer"
        prerequisites:
          - export xxxx    # Pre-commands required to play the stream

```

#### Test Setup Configuration File

Update the artifact paths from which the binaries should be copied to the device.

Set the execution paths for each test case.

- Example configuration file: [dsDisplay_L3_testSetup.yml](../../../host/tests/L3_TestCases/dsDisplay/dsDisplay_L3_testSetup.yml).

#### Test Configuration

Update the execute command according to the device path where `HAL` binaries are copied and Update the test suite for each level test case

- Example configuration file: [dsDisplay_testConfig.yml](../../../host/tests/dsClasses/dsDisplay_testConfig.yml).

## Run Test Cases

Once the environment is set up, you can execute the test cases with the following command

```bash
python <TestCaseName.py> --config </PATH>/ut/host/tests/configs/example_rack_config.yml --deviceConfig </PATH>/ut/host/tests/configs/deviceConfig.yml
```

## Test Case Procedure

### dsDisplay_test01_VerifyDisplayConnectCallBackTest.py

**Overview:**

This test verifies display event callbacks by connecting and disconnecting a display device on each supported video port, ensuring that appropriate callbacks are triggered for display connection, disconnection, Rx Sense ON, Rx Sense OFF, and HDCP protocol version change events.

**Platform Supported:**

- Source
- Sink

**User Input Required:**

Yes: User input is required to manually change the display status (connect/disconnect) during the test execution, with the prompt question `Change the {port} status to {event} and press Enter:` (This will be automated later).

**Acceptance Criteria:**

The test will pass if each display event triggers the expected callback for every supported display port.

**Expected Results:**

The test will raise events for connecting and disconnecting the display and verify that the expected callbacks are received for each event. The test will pass if all expected callbacks are detected; otherwise, it will fail.

**Test Steps:**

- Run the Python file `dsDisplay_test01_VerifyDisplayConnectCallBackTest.py` with the appropriate configuration:

```bash
dsDisplay_test01_VerifyDisplayConnectCallBackTest.py --config /host/tests/configs/example_rack_config.yml --deviceConfig /host/tests/configs/deviceConfig.yml
```

- The test will download all required artifacts, copy them to the target directory, and start execution.

- Callback Event Verification:

  - Prompting the user to change display status for each supported port (connect/disconnect)
  - Capture and verify the device's callback status to confirm receipt of the expected event callback.
  - For each event, verify the following:
    - dsDISPLAY_EVENT_CONNECTED
    - dsDISPLAY_EVENT_DISCONNECTED
    - dsDISPLAY_RXSENSE_ON
    - dsDISPLAY_RXSENSE_OFF
    - dsDISPLAY_HDCPPROTOCOL_CHANGE

- Completion and results:

  After verifying all callback statuses, the test will conclude and display the final result (PASS/FAIL).

### dsDisplay_test02_TestVerifyDisplayEdid.py

**Overview:**

This test case is designed for Source devices and focuses on retrieving and verifying the `EDID` by connecting various pre-defined displays to each supported video port. The test compares the `EDID` data retrieved from the connected displays against expected values to ensure accurate identification. It uses the [dsDisplay_test_MonitorDetails.yml](../../../host/tests/L3_TestCases/dsDisplay/dsDisplay_test_MonitorDetails.yml) file, which contains the details of the connected monitors for verification.

**Platform Supported:**

- Source

**User Input Required:**

Yes: User input is required to manually connect the display to the specified port, with the prompt question `Connect Device: {display} to Port: {port} and Press Enter:` (This will be automated later).

**Acceptance Criteria:**

This test retrieves and verifies `EDID` by connecting various pre-defined displays to each supported video port. It then compares the retrieved `EDID` data against expected values to ensure accurate display identification.

**Expected Results:**

Connect each specified display device, retrieve `EDID` data, and confirm that the retrieved monitor names match the expected values defined in [dsDisplay_test_MonitorDetails.yml](../../../host/tests/L3_TestCases/dsDisplay/dsDisplay_test_MonitorDetails.yml), returning a pass/fail status based on the comparison.

**Test Steps:**

- Run the Python file `dsDisplay_test02_TestVerifyDisplayEdid.py` with the appropriate configuration:

```bash
dsDisplay_test02_TestVerifyDisplayEdid.py --config /host/tests/configs/example_rack_config.yml --deviceConfig /host/tests/configs/deviceConfig.yml
```

- The test will download all required artifacts, copy them to the target directory, and start execution.

- Display Device Verification:

  - For each available video port, the test prompts the user to connect the specified display device (LG, Philips, Sony, Samsung).
  - The test will retrieve the `EDID` information from the connected display device and verify it against the expected details, such as the monitor name, for each display device.
  - It will confirm that the `monitorName` field in the retrieved `EDID` matches the expected monitor name specified in [dsDisplay_test_MonitorDetails.yml](../../..//host/tests/L3_TestCases/dsDisplay/dsDisplay_test_MonitorDetails.yml).

- Completion and Results:

  After verifying the `EDID` information for all connected display devices, the test will conclude and display the final result (PASS/FAIL).

### dsDisplay_test03_AspectRatioVerificationTest.py

**Overview:**

This test retrieves and verifies the aspect ratio of the display on each supported video port. For each specified aspect ratio, the test checks that the retrieved aspect ratio matches the expected value, ensuring that the display correctly adapts to the given configuration.

**Platform Supported:**

- Source

**User Input Required:**

Yes: User input is required to manually set the aspect ratio for the specified port, with the prompt question `Set the aspect ratio {aspectRatio} to Port: {port} and Press Enter:` (This will be automated later).

**Acceptance Criteria:**

Verify that the display’s aspect ratio is correctly retrieved for each configured setting (16x9, 4x3).

**Expected Results:**

The test will set various aspect ratios, retrieve the current aspect ratio from the display, and confirm that it matches the expected value. The test will pass if all aspect ratios are correctly identified; otherwise, it will fail.

**Test Steps:**

- Run the Python file `dsDisplay_test03_AspectRatioVerificationTest.py` with the appropriate configuration:

```bash
dsDisplay_test03_AspectRatioVerificationTest.py --config /host/tests/configs/example_rack_config.yml --deviceConfig /host/tests/configs/deviceConfig.yml
```

- The test will download the required artifacts, then copy them to the target directory.

- Aspect Ratio Verification
  - For each video port, the user will be prompted to set the specified aspect ratio on the port and confirm by pressing Enter.
  - The test will retrieve the aspect ratio from the connected display device.
  - The retrieved aspect ratio will be compared to the expected value for each configuration.

- Completion and Results:

  If all expected aspect ratios are verified for each port, the test will conclude and display the final result (PASS/FAIL).

### dsDisplay_test04_TestVerifyDisplayEdidBytes

**Overview:**

This test case is designed for Source devices and focuses on retrieving and verifying the `EDID` bytes by connecting various pre-defined displays to each supported video port. The test parses the `EDID` bytes retrieved from the connected displays against expected values to ensure accurate identification. It uses the [dsDisplay_test_MonitorDetails.yml](../../../host/tests/L3_TestCases/dsDisplay/dsDisplay_test_MonitorDetails.yml) file, which contains the details of the connected monitors for verification.

**Platform Supported:**

- Source

**User Input Required:**

Yes: User input is required to manually connect the display to the specified port, with the prompt question `Connect Device: {display} to Port: {port} and Press Enter:` (This will be automated in future versions.)

**Acceptance Criteria:**

Connect each display to the supported video ports, retrieve the `EDID` bytes, and verify them against the expected `EDID` data.

**Expected Results:**

The test will retrieve and parse `EDID` bytes for each connected display. It will verify that the `EDID` information, including fields like manufacturerId and monitorName, matches the expected values for each display. The test will pass if all expected `EDID` details are retrieved and verified correctly for each display and port.

**Test Steps:**

- Run the Python file `dsDisplay_test04_TestVerifyDisplayEdidBytes` with the appropriate configuration:

```bash
dsDisplay_test04_TestVerifyDisplayEdidBytes --config /host/tests/configs/example_rack_config.yml --deviceConfig /host/tests/configs/deviceConfig.yml
```

- The test will download the required artifacts, then copy them to the target directory.

- EDID Bytes Verification:
  - For each display, the test will prompt the user to connect the display to the specified port.
  - The test will retrieve the `EDID` bytes from the connected display device.
  - The test will verify the retrieved `EDID` bytes against the expected details, such as manufacturer ID and monitor name, for each connected display.

- Completion and Results:

  If all expected `EDID` bytes are verified, the test will conclude and display the final result (PASS/FAIL).

### dsDisplay_test07_VerifyALLM_Mode.py

**Overview:**

This test is designed to verify the functionality of the dsSetAllmEnabled API in enabling or disabling Auto Low Latency Mode (`ALLM`) for an HDMI output port. The test will check the API's ability to correctly toggle ALLM based on the sink device's compatibility with HDMI 2.1 specifications. Users will validate the `ALLM` status using an HDMI analyzer.

**Platform Supported:**

Source

**User Input Required:**

Yes: The user is required to verify the `ALLM` mode on an external HDMI analyzer connected to the device. (This will be automated later).

**Acceptance Criteria:**

The test must successfully enable/disable ALLM mode, and the user must confirm that respective mode is displayed on the HDMI analyzer for the test to pass.

**Expected Results:**

The test will Enables/Disables ALLM mode for HDMI output port connected to display. The user will confirm the correct ALLM mode using a supported HDMI analyzer.

**Note:** Currently unable to verify this test case.

**Test Steps:**

- Run the Python file `dsDisplay_test07_VerifyALLM_Mode.py` with the appropriate configuration:

```bash
dsDisplay_test07_VerifyALLM_Mode.py --config /host/tests/configs/example_rack_config.yml --deviceConfig /host/tests/configs/deviceConfig.yml
```

- Download and copy all required assets to the target directory.
- Enable ALLM mode.
- Prompt the user to verify that respective ALLM mode is displayed on the HDMI analyzer.
- The test will pass if the user confirms that the ALLM mode is enabled.
- Disable ALLM mode.
- Prompt the user to verify that respective ALLM mode is displayed on the HDMI analyzer.
- The test will pass if the user confirms that the ALLM mode is disabled.

### dsDisplay_test05_AVIContentTypeVerificationTest.py

**Overview:**

This test case is designed for Source devices and focuses on setting and verifying the AVI Content Type (dsAVICONTENT_TYPE_GRAPHICS,dsAVICONTENT_TYPE_PHOTO,dsAVICONTENT_TYPE_CINEMA,dsAVICONTENT_TYPE_GAME) through the HDMI InfoFrame. It ensures that the correct content type is displayed on the HDMI analyzer and is validated using the dsGetAVIContentType() API.

**Platform Supported:**

- Source

**User Input Required:**

Yes: The user must confirm that the correct AVI Content Type is visible on the HDMI analyzer after setting it.

**Acceptance Criteria:**

The test uses dsSetAVIContentType() to set the content type and validates it using both HDMI analyzer output and dsGetAVIContentType(). The test passes when both validations succeed.

**Expected Results:**

For each content type set, the analyzer correctly reflects the HDMI InfoFrame content type and the API returns the expected value.

**Test Steps:**

- Run the Python file `dsDisplay_test05_AVIContentTypeVerificationTest.py

```bash
dsDisplay_test05_AVIContentTypeVerificationTest --config /host/tests/configs/example_rack_config.yml --deviceConfig /host/tests/configs/deviceConfig.yml
```

- The test will download the required artifacts, then copy them to the target directory.

- AVI Content Verification
  - For each AVI Content Type (dsAVICONTENT_TYPE_GRAPHICS,dsAVICONTENT_TYPE_PHOTO,dsAVICONTENT_TYPE_CINEMA,dsAVICONTENT_TYPE_GAME), the test sets the value using dsSetAVIContentType().
  - The user is prompted to confirm the visibility of the correct content type on the HDMI analyzer.
  - The current value is retrieved using dsGetAVIContentType() and compared with the expected content type.
  - The result is logged as PASS/FAIL based on the manual confirmation from the HDMI analyzer and the API result.

- Completion and Results:

 If all expected content types are verified for each port, the test will conclude and display the final result (PASS/FAIL).

### dsDisplay_test06_AVIScanInfoVerificationTest.py

**Overview:**

This test case is designed for Source devices and focuses on setting and verifying the AVI Scan Information (dsAVI_SCAN_TYPE_NO_DATA,dsAVI_SCAN_TYPE_OVERSCAN,dsAVI_SCAN_TYPE_UNDERSCAN) through the HDMI InfoFrame. The test confirms that the correct scan info bits (S1/S0) are reflected on the HDMI analyzer and verifies that the dsGetAVIScanInformation API returns the expected value.

**Platform Supported:**

- Source

**User Input Required:**

Yes: The user must confirm whether the correct Scan Info (S1/S0 bits) is displayed on the HDMI analyzer after setting it.

**Acceptance Criteria:**

This test sets the Scan Info using dsSetAVIScanInformation(), confirms visibility through an HDMI analyzer, and verifies it using dsGetAVIScanInformation(). The test passes if both manual and API verifications are successful.

**Expected Results:**

Each configured Scan Info setting is correctly reflected on the HDMI analyzer and accurately returned by the get API.

**Test Steps:**

- Run the Python file `dsDisplay_test06_AVIScanInfoVerificationTest.py` with the appropriate configuration:

```bash
dsDisplay_test06_AVIScanInfoVerificationTest --config /host/tests/configs/example_rack_config.yml --deviceConfig /host/tests/configs/deviceConfig.yml
```

- The test will download the required artifacts, then copy them to the target directory.

- AVI Scan Info Verification
  - For each Scan Info setting (dsAVI_SCAN_TYPE_NO_DATA,dsAVI_SCAN_TYPE_OVERSCAN,dsAVI_SCAN_TYPE_UNDERSCAN), the test sets the value using dsSetAVIScanInformation().
  - The user is prompted to check the HDMI analyzer for the correct bit representation (S1/S0).
  - The current Scan Info is retrieved using dsGetAVIScanInformation() and compared with the expected value.
  - The result is logged as PASS/FAIL based on the manual confirmation from the HDMI analyzer and the API result.

- Completion and Results:

  If all expected AVI scan information is verified for each port, the test will conclude and display the final result (PASS/FAIL).

### dsDisplay_L3_Runall_Source.py 

This python file runs all the tests supported by `source` devices

```bash
python dsDisplay_L3_Runall_Source.py  --config </PATH>/ut/host/tests/configs/example_rack_config.yml --deviceConfig </PATH>/ut/host/tests/configs/deviceConfig.yml
```

### dsDisplay_L3_Runall_Sink.py 

This python file runs all the tests supported by `sink` devices

```bash
python dsDisplay_L3_Runall_Sink.py  --config </PATH>/ut/host/tests/configs/example_rack_config.yml --deviceConfig </PATH>/ut/host/tests/configs/deviceConfig.yml
```
