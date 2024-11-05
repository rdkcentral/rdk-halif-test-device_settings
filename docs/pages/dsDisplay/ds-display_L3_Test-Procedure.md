# Device Settings Display L3 Test Case and Procedure Documentation

## Table of Contents

- [Overview](#overview)
- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [References](#references)
- [Setting Up Test Environment](#setting-up-test-environment)
- [Test Case Procedure](#test-case-procedure)
  - [dsDisplay_test01_VerifyDisplayConnectCallBackTest.py](#dsdisplay_test01_verifydisplayconnectCallBackTestpy)
  - [dsDisplay_test02_TestVerifyDisplayEdid.py](#dsdisplay_test02_testverifydisplayEdidpy)
  - [dsDisplay_test03_AspectRatioVerificationTest.py](#dsdisplay_test03_aspectratioverificationtestpy)
  - [dsDisplay_test04_TestVerifyDisplayEdidBytes.py](#dsdisplay_test04_testverifydisplayEdidbytespy)

## Overview

This document describes the L3 Test case Procedure Documentation for the Device Settings Display module.

### Acronyms, Terms and Abbreviations

- `HAL` \- Hardware Abstraction Layer, may include some common components
- `UT`  \- Unit Test(s)
- `OEM` \- Original Equipment Manufacture
- `SoC` \- System on a Chip
- `HDMI`\- High-Definition Multimedia Interface
- `EDID`\- Extended Display Identification Data
- `RAFT`\- Rapid Automation Framework for Testing
- `DVI` \- Digital Video Interface
- `Y`   \- yes supported
- `NA`  \- Not Supported

### References

- `High Level Test Specification` - [dsDisplay High Level TestSpec](ds-display-high-Level_TestSpec.md)

- `dsDisplay L3 Low Level Test Specification` - [dsDisplay L3 Low Level TestSpec](ds-display_L3_Low-Level_TestSpecification.md)

## Setting Up Test Environment

To execute `HAL` `L3` Python test cases, need a Python environment. Follow these steps mentioned in [HPK Public Documentation](https://github.com/rdkcentral/rdk-hpk-documentation/blob/main/README.md)

### Update Configuration Files

#### Rack Configuration File

Example Rack configuration File: `ut/host/tests/configs/example_rack_config.yml`

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
      profile: "../../../../profiles/source/Source_4K_Display.yaml"
      player:
        tool: "gstreamer"
        prerequisites:
          - export xxxx    # Pre-commands required to play the stream

```

#### Test Setup Configuration File

Update the artifact paths from which the binaries should be copied to the device.

Set the execution paths.

- Example configuration file: [dsDisplay_L3_testSetup.yml](../../../host/tests/L3_TestCases/dsDisplay/dsDisplay_L3_testSetup.yml).

#### Test Suite Configuration

Update the execute command according to the device path where `HAL` binaries are copied and Update the test suite for each level test case

- Example configuration file: [dsDisplay_test_suite.yml](../../../host/tests/dsClasses/dsDisplay_test_suite.yml).

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

This test retrieves and verifies `EDID` by connecting various pre-defined displays to each supported video port. It then compares the retrieved `EDID` data against expected values to ensure accurate display identification.

**Platform Supported:**

- Source
- Sink

**User Input Required:**

Yes: User input is required to manually connect the display to the specified port, with the prompt question `Connect Device: {display} to Port: {port} and Press Enter:` (This will be automated later).

**Acceptance Criteria:**

Connect each display to the supported video ports, retrieve the `EDID` information, and verify it against the expected EDID data.

**Expected Results:**

The test will connect various displays, retrieve their `EDID` information, and confirm that the monitor names match the expected values. The test will pass if all expected `EDID` data is correctly identified; otherwise, it will fail.

**Test Steps:**

- Run the Python file `dsDisplay_test02_TestVerifyDisplayEdid.py` with the appropriate configuration:

```bash
dsDisplay_test02_TestVerifyDisplayEdid.py --config /host/tests/configs/example_rack_config.yml --deviceConfig /host/tests/configs/deviceConfig.yml
```

- The test will download all required artifacts, copy them to the target directory, and start execution.

- Display Device Verification:

  - For each port, it will prompt the user to connect the specified display device and confirm successful connection.
  - The test will retrieve the `EDID` information from the connected display device and verify it against the expected details, such as the monitor name, for each display.

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

- Aspect Ratio Verification:
    - For each video port, the user will be prompted to set the specified aspect ratio on the port and confirm by pressing Enter.
    - The test will retrieve the aspect ratio from the connected display device.
    - The retrieved aspect ratio will be compared to the expected value for each configuration.

- Completion and Results:

  If all expected aspect ratios are verified for each port, the test will conclude and display the final result (PASS/FAIL).

### dsDisplay_test04_TestVerifyDisplayEdidBytes

**Overview:**

This test retrieves and verifies the `EDID` bytes from connected displays through each supported video port. The test compares the retrieved EDID bytes against expected values to ensure accurate identification and functionality of the display.

**Platform Supported:**

- Source
- Sink

**User Input Required:**

Yes: User input is required to manually connect the display to the specified port, with the prompt question `Connect Device: {display} to Port: {port} and Press Enter:` (This will be automated in future versions.)

**Acceptance Criteria:**

Connect each display to the supported video ports, retrieve the `EDID` bytes, and verify them against the expected `EDID` data.

**Expected Results:**

The test will retrieve and parse EDID bytes for each connected display. It will verify that the EDID information, including fields like manufacturerId and monitorName, matches the expected values for each display. The test will pass if all expected EDID details are retrieved and verified correctly for each display and port.

**Test Steps:**

- Run the Python file `dsDisplay_test04_TestVerifyDisplayEdidBytes` with the appropriate configuration:

```bash
dsDisplay_test04_TestVerifyDisplayEdidBytes --config /host/tests/configs/example_rack_config.yml --deviceConfig /host/tests/configs/deviceConfig.yml
```

- The test will download the required artifacts, then copy them to the target directory.

- EDID Bytes Verification:
  - For each display, the test will prompt the user to connect the display to the specified port.
  - The test will retrieve the EDID bytes from the connected display device.
  - The test will verify the retrieved EDID bytes against the expected details, such as manufacturer ID and monitor name, for each connected display.

- Completion and Results:

  If all expected EDID bytes are verified, the test will conclude and display the final result (PASS/FAIL).