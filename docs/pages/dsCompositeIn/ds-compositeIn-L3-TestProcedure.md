# dscompositeIn HAL L3 Python Test Procedure

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Setting Up Test Environment](#setting-up-test-environment)
- [Run Test Cases](#run-test-cases)
- [Test Setup Connections](#test-setup-connections)
- [Test Cases](#test-cases)
  - [dsCompositeIn_test1_VerifyConnect_Callback.py](#dscompositein_test1_verifyconnect_callbackpy)
  - [dsCompositeIn_test2_VerifyStatus_Callback.py](#dscompositein_test2_verifystatus_callbackpy)
  - [dsCompositeIn_test3_ScaleAndVerify_Video.py](#dscompositein_test3_scaleandverify_videopy)
  - [dsCompositeIn_test4_VerifySignal_Callback.py](#dscompositein_test4_verifysignal_callbackpy)

## Acronyms, Terms and Abbreviations

- `HAL`    - Hardware Abstraction Layer
- `L3`     - Level 3 Testing
- `DUT`    - Device Under Test
- `RAFT`   - Rapid Automation Framework for Testing
- `YAML`   - YAML Ain't Markup Language

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
      profile: "../../../../profiles/sink/Sink_compositeIn.yaml"
      prerequisites:
        - export xxxx    # Pre-commands required to play the stream

```

#### Test Setup Configuration File

Example Test Setup configuration File: [dscompositeIn_L3_testSetup.yml](../../..//host/tests/dsCompositeIn_L3_Tests/dsCompositeIn_L3_testSetup.yml)

Update the artifact paths from which the binaries should be copied to the device.

Set the execution paths and provide the stream paths for each test case.

If a test case requires multiple streams or needs to be validated using several streams, ensure that all necessary streams are added sequentially for that specific test case.

```yaml
dscompositeIn:
  description: "dscompositeIn Device Settings test setup"
  assets:
    device:
      defaults: &defaults
        artifacts:
          - "<path>/bin/hal_test"
          - "<path>/bin/libut_control.so"
          - "<path>/bin/Sink_CompositeInput.yaml"
          - "<path>/bin/run.sh"
        execute:
          - "chmod +x <PATH>/dscompositeIn_L3/hal_test"
          - "chmod +x <PATH>/dscompositeIn_L3/run.sh"
        streams:
        test1_VerifyConnect_Callback:
          <<: *defaults
          streams:
        test2_VerifyStatus_Callback:
          <<: *defaults
          streams:
        test3_ScaleAndVerify_Video:
          <<: *defaults
          streams:
        test4_VerifySignal_Callback:
          <<: *defaults
          streams:
```

#### Test Suite Configuration

Example Test Setup configuration File: [dsCompositeIn_test_suite.yml](../../../host/tests/dsClasses/dsCompositeIn_test_suite.yml)

Update the execute command according to the device path where `HAL` binaries are copied.

## Run Test Cases

Once the environment is set up, you can execute the test cases with the following command

```bash
python <TestCaseName.py> --config </PATH>/ut/host/tests/configs/example_rack_config.yml --deviceConfig </PATH>/ut/host/tests/configs/deviceConfig.yml
```

## Test Setup Connections

To verify the compositeIn connect the external devices to `DUT`.
For Example:

- Connect external device with Composite Out to Composite In port.

## Test Cases
### dsCompositeIn_test1_VerifyConnect_Callback.py

#### Platform Support - test01

- Sink

#### User Input Required - test01

**Yes**: User interaction is necessary to connect/disconnect Composite Source device (This will be automated later).

#### Acceptance Criteria - test01

Connect the external device and check if dut recognize the event.
Disconnect the external device and check if dut recognize the event.

#### Expected Results - test01

The test registers the event and check for  the event call back.

Success Criteria

- Device should recognize the connect/Disconnect event.

#### Test Steps - test01

- Initiate the Test:

  - Select and execute the Python file: **`dsCompositeIn_test1_VerifyConnect_Callback.py`**
  - The test will automatically download all required artifacts, copying them to the designated target directory before commencing execution.

- Device Connect prompt:

    The test will Request User to connect Source device to Composite In port:

  - Question: "Connect the compositeIn source device to Port port_type and press Y: "
  - Press **Y** if user connected the device and acknowledge the same. (this will mark the step as PASS).

- Device connect Confirmation:

  - Test will check if the event has reached the device. 
  - If event detected will mark the step as PASS
  - If event not detected will mark the step as FAIL

- Device Disconnect prompt:

    The test will Request User to disconnect Source device to Composite In port:

  - Question: "Disonnect the compositeIn source device to Port port_type and press Y: "
  - Press **Y** if user connected the device and acknowledge the same. (this will mark the step as PASS).

- Device disconnect Confirmation:

  - Test will check if the event has reached the device. 
  - If event detected will mark the step as PASS
  - If event not detected will mark the step as FAIL

- Repeat for All Ports:

  The test will iterate through all available  ports, connecting/disconnecting each one and collecting user feedback accordingly.

- Test Conclusion:

  Upon receiving user responses for all ports, the test will conclude and present a final result: PASS or FAIL based on the user inputs throughout the test execution.

### dsCompositeIn_test2_VerifyStatus_Callback.py
#### Platform Support - test02

- Sink

#### User Input Required - test02

**Yes**: User interaction is necessary to check the connect status of Composite Source device (This will be automated later).

#### Acceptance Criteria - test02

Test detects the status of the Source device connected to Composite In port

#### Expected Results - test02

The test registers the event and check for  the event call back.

Success Criteria

- Device should recognize the status of the port connected.

#### Test Steps - test02

- Initiate the Test:

  - Select and execute the Python file: **`dsCompositeIn_test2_VerifyStatus_Callback.py`**
  - The test will automatically download all required artifacts, copying them to the designated target directory before commencing execution.

- Device Connect prompt:

    The test will Request User to connect Source device to Composite In port:

  - Question: "Connect the compositeIn source device to Port port_type and press Y: "
  - Press **Y** if user connected the device and acknowledge the same. (this will mark the step as PASS).

- Device status Confirmation:

  - Test will select the port and check if the device status event has reached the device. 
  - If event detected will mark the step as PASS
  - If event not detected will mark the step as FAIL

- Repeat for All Ports:

  The test will iterate through all available  ports, selecting each one and collecting user feedback accordingly.

- Test Conclusion:

  Upon receiving user responses for all ports, the test will conclude and present a final result: PASS or FAIL based on the user inputs throughout the test execution.
### dsCompositeIn_test3_ScaleAndVerify_Video.py
#### Platform Support - test03

- Sink

#### User Input Required - test03

**Yes**: User interaction is necessary to check the connect status of compositeIn Source device and to verify the video scaling (This will be automated later).

#### Acceptance Criteria - test03

Test checks if video scaling happens on video from the Source device connected to Composite In port

#### Expected Results - test03

The test scales the video playing from compositeIn source device 

Success Criteria

- User should see video scaling happening in dut.

#### Test Steps - test03

- Initiate the Test:

  - Select and execute the Python file: **`dsCompositeIn_test3_ScaleAndVerify_Video.py`**
  - The test will automatically download all required artifacts, copying them to the designated target directory before commencing execution.

- Device Connect prompt:

    The test will Request User to connect Source device to Composite In port:

  - Question: "Connect the compositeIn source device to Port port_type and press Y: "
  - Press **Y** if user connected the device and acknowledge the same. (this will mark the step as PASS).

- Device changes the scale and request user to confirm:

  - Question: "Check video scaled on port_type and press (Y/N)"
  - Press **Y** if user sees the video scaling. (this will mark the step as PASS).
  - Press **N** if user could not see the video scaling. (this will mark the step as FAIL).

- Repeat for Scaling factor:

  The test will iterate through all available scaling parameter and set scaling accordingly..

- Repeat for All Ports:

  The test will iterate through all available ports.

- Test Conclusion:

  Upon receiving user responses for all ports, the test will conclude and present a final result: PASS or FAIL based on the user inputs throughout the test execution.
### dsCompositeIn_test4_VerifySignal_Callback.py
#### Platform Support - test04

- Sink

#### User Input Required - test04

**Yes**: User interaction is necessary to connect/Disconnet the device (This will be automated later).

#### Acceptance Criteria - test04

Test detects the signal status of the compposit In signal.

#### Expected Results - test04

The test checks the signal change in composite source 

Success Criteria

- Test identifies the signal change.

#### Test Steps - test04

- Initiate the Test:

  - Select and execute the Python file: **`dsCompositeIn_test4_VerifySignal_Callback.py`**
  - The test will automatically download all required artifacts, copying them to the designated target directory before commencing execution.

- Device Connect prompt:

    The test will Request User to connect Source device to Composite In port:

  - Question: "Connect the compositeIn source device to Port port_type and press Y: "
  - Press **Y** if user connected the device and acknowledge the same. (this will mark the step as PASS).

- Signal change confirmation:

  - Test will check if the event has reached the device. 
  - If event detected will mark the step as PASS
  - If event not detected will mark the step as FAIL

- Device Disconnect/Standby prompt:

    The test will Request User to disconnect the Source device to Composite In port or make Source device to standby mode:

  - Question: "Check if CompositeIn source is disconnected to port_type/set to standby and press Y: "
  - Press **Y** if user connected the device and acknowledge the same. (this will mark the step as PASS).

- Signal change confirmation:

  - Test will check if the event has reached the device. 
  - If event detected will mark the step as PASS
  - If event not detected will mark the step as FAIL

- Repeat for All Ports:

  The test will iterate through all available ports.

- Test Conclusion:

  Upon receiving user responses for all ports, the test will conclude and present a final result: PASS or FAIL based on the user inputs throughout the test execution.
