# dscompositeIn HAL L3 Python Test Procedure

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Setting Up Test Environment](#setting-up-test-environment)
- [Run Test Cases](#run-test-cases)
- [Test Cases](#test-cases)
  - [dsCompositeIn_test1_VerifyConnect_Callback.py](#dscompositein_test1_verifyconnect_callbackpy)
  - [dsCompositeIn_test2_VerifyStatus_Callback.py](#dscompositein_test2_verifystatus_callbackpy)
  - [dsCompositeIn_test3_ScaleAndVerify_Video.py](#dscompositein_test3_scaleandverify_videopy)
  - [dsCompositeIn_test4_VerifySignal_Callback.py](#dscompositein_test4_verifysignal_callbackpy)
  - [dsCompositeIn_test5_VerifyVideoMode_Callback.py](#dscompositein_test5_verifyvideomode_callbackpy)
  - [dsCompositeIn_L3_Runall_Sink.py](#dscompositein_l3_runall_sinkpy)

## Acronyms, Terms and Abbreviations

- `HAL`     - Hardware Abstraction Layer
- `L3`      - Level 3 Testing
- `DUT`     - Device Under Test
- `RAFT`    - Rapid Automation Framework for Testing
- `YAML`    - YAML Ain't Markup Language

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
            profile: "../../../../profiles/sink/Sink_CompositeInput.yaml"
            streams_download_url: "<URL_Path>" #URL path from which the streams are downloaded to the device

```

#### Test Setup Configuration File

Example Test Setup configuration File: [dscompositeIn_L3_testSetup.yml](../../..//host/tests/L3_TestCases/dsCompositeIn/dsCompositeIn_L3_testSetup.yml)

Provide the streams for each test case. This path is appended with `streams_download_url` entry from [Device Configuration File](#device-configuration-file)

If a test case requires multiple streams or needs to be validated using several streams, ensure that all necessary streams are added sequentially for that specific test case.

```yaml
dscompositeIn:
  description: "dscompositeIn Device Settings test setup"
  assets:
    device:
        test1_VerifyConnect_Callback:
          streams:
        test2_VerifyStatus_Callback:
          streams:
        test3_ScaleAndVerify_Video:
          streams:
        test4_VerifySignal_Callback:
          streams:
        test5_VerifyVideoMode_Callback:
          streams:
```

#### Test Configuration

Example Test Setup configuration File: [dsCompositeIn_testConfig.yml](../../../host/tests/dsClasses/dsCompositeIn_testConfig.yml)

Update the execute command according to the device path where `HAL` binaries are copied.

## Run Test Cases

Once the environment is set up, you can execute the test cases with the following command

```bash
python <TestCaseName.py> --config </PATH>/ut/host/tests/configs/example_rack_config.yml --deviceConfig </PATH>/ut/host/tests/configs/deviceConfig.yml
```

## Test Cases

### dsCompositeIn_test1_VerifyConnect_Callback.py

#### Platform Support - test01

- Sink

#### User Input Required - test01

**Yes**: User interaction is necessary to connect/disconnect the Composite Source device (This will be automated later).

#### Acceptance Criteria - test01

Connect the external device and check if 'DUT' recognizes the events
Disconnect the external device and check if 'DUT' recognizes the event

#### Expected Results - test01

The test registers the event and checks for  the event call back.

Success Criteria

- The device should recognize the connect/Disconnect event.

#### Test Steps - test01

- Initiate the Test:

  - Select and execute the Python file: **`dsCompositeIn_test1_VerifyConnect_Callback.py`**
  - The test will automatically download all required artifacts, copying them to the designated target directory before commencing execution.

- Device Connect prompt:

    The test will Request the User to connect the Source device to the Composite In port:

  - Question: "Connect the compositeIn source device to Port port_type and press Y: "
  - Press **Y** if the user connected the device and acknowledged it. (this will mark the step as PASS).

- Device connect Confirmation:

  - The test will check if the event has reached the device.
  - If the event is detected will mark the step as PASS
  - If the event is not detected will mark the step as FAIL

- Device Disconnect prompt:

    The test will Request the User to disconnect the Source device to the Composite In port:

  - Question: "Disconnect the compositeIn source device to Port port_type and press Y: "
  - Press **Y** if the user connected the device and acknowledged it. (this will mark the step as PASS).

- Device disconnect Confirmation:

  - The test will check if the event has reached the device.
  - If the event detected will mark the step as PASS
  - If the event not detected will mark the step as FAIL

- Repeat for All Ports:

  The test will iterate through all available  ports, connecting/disconnecting each one and collecting user feedback accordingly.

- Test Conclusion:

  Upon receiving user responses for all ports, the test will conclude and present a final result: PASS or FAIL based on the user inputs throughout the test execution.

### dsCompositeIn_test2_VerifyStatus_Callback.py

#### Platform Support - test02

- Sink

#### User Input Required - test02

**Yes**: User interaction is necessary to check the connect status of the Composite Source device (This will be automated later).

#### Acceptance Criteria - test02

The test detects the status of the Source device connected to the Composite In port

#### Expected Results - test02

The test registers the event and checks for  the event call back.

Success Criteria

- The device should recognize the status of the port connected.

#### Test Steps - test02

- Initiate the Test:

  - Select and execute the Python file: **`dsCompositeIn_test2_VerifyStatus_Callback.py`**
  - The test will automatically download all required artifacts, copying them to the designated target directory before commencing execution.

- Device Connect prompt:

    The test will Request the User to connect the Source device to the Composite In port:

  - Question: "Connect the compositeIn source device to Port port_type and press Y: "
  - Press **Y** if the user connected the device and acknowledged it. (this will mark the step as PASS).

- Device status Confirmation:

  - The test will select the port and check if the device status event has reached the device.
  - If the event is detected will mark the step as PASS
  - If the event is not detected will mark the step as FAIL

- Repeat for All Ports:

  The test will iterate through all available  ports, selecting each port and collecting user feedback accordingly.

- Test Conclusion:

  Upon receiving user responses for all the ports, the test will conclude and present a final result: PASS or FAIL based on the user inputs throughout the test execution.

### dsCompositeIn_test3_ScaleAndVerify_Video.py

#### Platform Support - test03

- Sink

#### User Input Required - test03

**Yes**: User interaction is necessary to check the composite connection with the source device and to verify the video scaling (This will be automated later).

#### Acceptance Criteria - test03

Test checks if video scaling happens on video from the Source device connected to the Composite In port

#### Expected Results - test03

The test scales the video playing from compositeIn source device

Success Criteria

- The user should see video scaling happening in 'DUT'.

#### Test Steps - test03

- Initiate the Test:

  - Select and execute the Python file: **`dsCompositeIn_test3_ScaleAndVerify_Video.py`**
  - The test will automatically download all required artifacts, copying them to the designated target directory before commencing execution.

- Device Connect prompt:

    The test will Request the User to connect the Source device to the Composite In port:

  - Question: "Connect the compositeIn source device to Port port_type and press Y: "
  - Press **Y** if the user connected the device and acknowledged it. (this will mark the step as PASS).

- The device changes the scale and requests user to confirm:

  - Question: "Check video scaled on port_type and press (Y/N)"
  - Press **Y** if the user sees the video scaling. (this will mark the step as PASS).
  - Press **N** if the user cannot see the video scaling. (this will mark the step as FAIL).

- Repeat for Scaling factor:

  The test will iterate through all available scaling parameters and set scaling accordingly..

- Repeat for All Ports:

  The test will iterate through all available ports.

- Test Conclusion:

  Upon receiving user responses for all ports, the test will conclude and present a final result: PASS or FAIL based on the user inputs throughout the test execution.

### dsCompositeIn_test4_VerifySignal_Callback.py

#### Platform Support - test04

- Sink

#### User Input Required - test04

**Yes**: User interaction is necessary to connect/Disconnect the device (This will be automated later).

#### Acceptance Criteria - test04

The test detects the signal status of the compositeIn signal.

#### Expected Results - test04

The test checks the signal change in the composite source

Success Criteria

- Test identifies the signal change.

#### Test Steps - test04

- Initiate the Test:

  - Select and execute the Python file: **`dsCompositeIn_test4_VerifySignal_Callback.py`**
  - The test will automatically download all required artifacts, copying them to the designated target directory before commencing execution.

- Device Connect prompt:

    The test will Request the User to connect the Source device to the Composite In port:

  - Question: "Connect the compositeIn source device to Port port_type and press Y: "
  - Press **Y** if the user connected the device and acknowledged it. (this will mark the step as PASS).

- Signal change confirmation:

  - The test will check if the event has reached the device.
  - If the event is detected will mark the step as PASS
  - If the event is not detected will mark the step as FAIL

- Device Disconnect/Standby prompt:

    The test will Request the User to disconnect the Source device to the Composite In port or make Source device to standby mode:

  - Question: "Check if CompositeIn source is disconnected to port_type/set to standby and press Y: "
  - Press **Y** if the user connected the device and acknowledged it. (this will mark the step as PASS).

- Signal change confirmation:

  - The test will check if the event has reached the device.
  - If the event is detected will mark the step as PASS
  - If the event is not detected will mark the step as FAIL

- Repeat for All Ports:

  The test will iterate through all available ports.

- Test Conclusion:

  Upon receiving user responses for all ports, the test will conclude and present a final result: PASS or FAIL based on the user inputs throughout the test execution.

### dsCompositeIn_test5_VerifyVideoMode_Callback.py

#### Platform Support - test05

- Sink

#### User Input Required - test05

**Yes**: User interaction is necessary to connect/Disconnect the device (This will be automated later).

#### Acceptance Criteria - test05

The test detects the video mode change of the compositeIn video.

#### Expected Results - test05

The test checks the video mode change in the composite source

Success Criteria

- Test identifies the video mode change.

#### Test Steps - test05

- Initiate the Test:

  - Select and execute the Python file: **`dsCompositeIn_test5_VerifyVideoMode_Callback.py`**
  - The test will automatically download all required artifacts, copying them to the designated target directory before commencing execution.

- Device Connect prompt:

    The test will Request the User to connect the Source device to the Composite In port:

  - Question: "Connect the compositeIn source device to Port port_type and press Y: "
  - Press **Y** if the user connected the device and acknowledged it. (this will mark the step as PASS).

- Device connect confirmation:

  - The test will check if the event has reached the device.
  - If the event is detected will mark the step as PASS
  - If the event is not detected will mark the step as FAIL

- Source video resolution change prompt:

    The test will Request the User to change the resolution of video on Source device connected to the Composite In port:

  - Question: "Change the resolution of video played from CompositeIn source device connected to port_type and press Y: "
  - Press **Y** if the user changed the resolution and acknowledged it. (this will mark the step as PASS).

- Source video resolution change confirmation:

  - The test will check if the event has reached the device.
  - If the event is detected will mark the step as PASS
  - If the event is not detected will mark the step as FAIL

- Repeat for All Ports:

  The test will iterate through all available ports.

- Test Conclusion:

  Upon receiving user responses for all ports, the test will conclude and present a final result: PASS or FAIL based on the user inputs throughout the test execution.

### dsCompositeIn_L3_Runall_Sink.py

This python file runs all the tests supported by `sink` devices

```bash
python dsCompositeIn_L3_Runall_Sink.py --config </PATH>/ut/host/tests/configs/example_rack_config.yml --deviceConfig </PATH>/ut/host/tests/configs/deviceConfig.yml
```
