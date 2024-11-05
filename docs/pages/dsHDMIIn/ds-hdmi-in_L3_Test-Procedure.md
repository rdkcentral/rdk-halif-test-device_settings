# dsHdmiIn HAL L3 Python Test Procedure

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Setting Up Test Environment](#setting-up-test-environment)
- [Streams Required](#streams-required)
- [Test Setup Connections](#test-setup-connections)
- [Test Cases](#test-cases)
  - [dsHdmiIn_test1_ConnectionCallback_Verify.py](#dshdmiin_test1_connectioncallback_verifypy)
  - [dsHdmiIn_test2_SignalChangeCallback_Verify.py](#dshdmiin_test2_signalchangecallback_verifypy)
  - [dsHdmiIn_test3_PortStatusCallback_Verify.py](#dshdmiin_test3_portstatuscallback_verifypy)
  - [dsHdmiIn_test4_VideoModeChangeCallback_Verify.py](#dshdmiin_test4_videomodechangecallback_verifypy)
  - [dsHdmiIn_test5_AllmChangeCallback_Verify.py](#dshdmiin_test5_allmchangecallback_verifypy)
  - [dsHdmiIn_test6_AVlatncyCallback_Verify.py](#dshdmiin_test6_avlatncycallback_verifypy)
  - [dsHdmiIn_test7_AVIChangeCallback_Verify.py](#dshdmiin_test7_avichangecallback_verifypy)
  - [dsHdmiIn_test8_SelectPortAndVerifyPortStatus.py](#dshdmiin_test8_selectportandverifyportstatuspy)
  - [dsHdmiIn_test9_ScaleVideoAndVerify.py](#dshdmiin_test9_scalevideoandverifypy)
  - [dsHdmiIn_test10_ZoomModeAndVerify.py](#dshdmiin_test10_zoommodeandverifypy)
  - [dsHdmiIn_test11_GetEDIDInfo_Verify.py](#dshdmiin_test11_getedidinfo_verifypy)
  - [dsHdmiIn_test12_GetSpdInfo_Verify.py](#dshdmiin_test12_getspdinfo_verifypy)
  - [dsHdmiIn_test13_SetAndGetEDIDVersion.py](#dshdmiin_test13_setandgetedidversionpy)
  - [dsHdmiIn_test14_SetAndGetEDID2ALLMSupport.py](#dshdmiin_test14_setandgetedid2allmsupportpy)

## Acronyms, Terms and Abbreviations

- `HAL`    - Hardware Abstraction Layer
- `L3`     - Level 3 Testing
- `OEM`    - Original Equipment Manufacture
- `SoC`    - System on a Chip
- `HDMI`   - High-Definition Multimedia Interface
- `SDR`    - Standard Dynamic Range
- `EDID`   - Extended Display Identification Data
- `ALLM`   - Auto Low Latency Mode
- `AVI`    - Audio Video Interleave
- `SPD`    - Source Product Descriptor

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
      description: "tv device under test"
      platform: "tv"
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
    platform: "tv"    # Must match the platform in example_rack_config.yml
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

Example Test Setup configuration File: `ut/host/tests/L3_TestCases/dsHdmiIn/dsHdmiIn_L3_testSetup.yml`

Update the artifact paths from which the binaries should be copied to the device.

If need to enable any commands post test case execution update postcmd.

```yaml
dsHdmiIn:
  description: "dsHdmiIn Device Settings test setup"
  assets:
    device:
      defaults: &defaults
        artifacts:
          - "<path>/bin/hal_test"
          - "<path>/bin/libut_control.so"
          - "<path>/bin/Sink_HDMIIN.yaml"
          - "<path>/bin/run.sh"
        execute:
          - "chmod +x /opt/HAL/dsHdmiIn_L3/hal_test"
          - "chmod +x /opt/HAL/dsHdmiIn_L3/run.sh"
          - cp -rf /usr/lib/libdshal.so /opt/HAL/dsHdmiIn_L3/
          - "ln -s /usr/lib/libds-hal.so /opt/HAL/dsHdmiIn_L3/libdshal.so"
       streams:
          -" "
       postcmd:
          -" "
      test1_ConnectionCallback_Verify:
        <<: *defaults
        streams:[]
      test2_SignalChangeCallback_Verify:
        <<: *defaults
        streams:[]
      test14_SetAndGetEDID2ALLMSupport:
        <<: *defaults
        streams:[]

```

#### Test Suite Configuration

Example Test Setup configuration File: `ut/host/tests/dsClasses/dsHdmiIn_test_suite.yml`

Update the execute command according to the device path where `HAL` binaries are copied.

```yaml
dsHdmiIn:
  description: "dsHdmiIn Device Settings testing profile"
  test:
    execute: "/tmp/run.sh -p /tmp/Sink_HDMIIN.yaml"
    type: UT-C  # Cunit tests (UT-C)

```

## Run Test Cases

Once the environment is set up, you can execute the test cases with the following command

```bash
python <TestCaseName.py> --config </PATH>/ut/host/tests/configs/example_rack_config.yml --deviceConfig </PATH>/ut/host/tests/configs/deviceConfig.yml
```
## Test Setup Connections

To verify the HdmiIn connect the external devices to `DUT`.
For Example:

- Connect HdmiIn device to a HdmiIn port.

## Test Cases

### dsHdmiIn_test1_ConnectionCallback_Verify.py

#### Platform Support - test01

- Sink

#### User Input Required - test01

**Yes**: User interaction is necessary to connect and Disconnect the Hdmi In device.(This will be automated later).

#### Acceptance Criteria - test01

Connect the external device and check if dut recognize the event.
Disconnect the external device and check if dut recognize the event.

#### Expected Results - test01

The test registers the event and check for  the event call back.

Success Criteria

- Device should recognize the connect/Disconnect event.

#### Test Steps - test01

- Initiate the Test:

  - Select and execute the Python file: **`dsHdmiIn_test1_ConnectionCallback_Verify.py`**
  - The test will automatically download all required artifacts and streams, copying them to the designated target directory before commencing execution.

-  Device Connect prompt:

    The test will Request User to connect Source device to Hdmi In port:

  - Question: "Plug the HDMI cable {port} and Press Enter: (Y/N)"
  - Press **Y** if Device is connected/disconnect (this will mark the step as PASS).
  - Press **N** if user could not connect/disconnect the device (this will mark the step as FAIL).

- Device Status Confirmation:

  - Test will check if the device status event has reached the device. 
  - If event detected will mark the step as PASS
  - If event not detected will mark the step as FAIL

- Repeat for All Ports:

  The test will iterate through all available Hdmi IN ports, connecting/disconnecting device on each one and collecting user feedback accordingly.

- Test Conclusion:

  Upon receiving user responses for all ports, the test will conclude and present a final result: PASS or FAIL based on the user inputs throughout the test execution.

### dsHdmiIn_test2_SignalChangeCallback_Verify.py

#### Platform Supported - test02

- Sink

#### User Input Required - test02

- **Yes**: User interaction is necessary to connect the Hdmi In device.(This will be automated later).

#### Acceptance Criteria - test02

- Verify the Singal status.

#### Expected Results - test02

- The test registers the event and check for signal status event call back.

#### Test Steps - test02

- Initiate the Test:

  - Select and execute the Python file: **`dsHdmiIn_test2_SignalChangeCallback_Verify.py`**
  - The test will automatically download all required artifacts and streams, copying them to the designated target directory before commencing execution.

-  Device Connect prompt:

    The test will Request User to connect Source device to Hdmi In port:

  - Question: "connect device to porttype and press Enter (Y/N)"
  - Press **Y** if Device is connected (this will mark the step as PASS).
  - Press **N** if user could not connect the device (this will mark the step as FAIL).

- Signal Status Confirmation:

  - Test will check if the signal status event has reached the device.
  - If event detected will mark the step as PASS
  - If event not detected will mark the step as FAIL

- Repeat for All Ports:

  The test will iterate through all available Hdmi IN ports, collects signal status accordingly.

- Test Conclusion:

  Upon receiving user responses for all ports, the test will conclude and present a final result: PASS or FAIL based on the user inputs throughout the test execution.

- Completion and Result:

  Once all necessary user actions are completed, the test will evaluate the results and display whether the test Passed or Failed.

### dsHdmiIn_test3_PortStatusCallback_Verify.py

#### Platform Supported - test03

- Sink

#### User Input Required - test03

- **Yes**: User interaction is necessary to connect the Hdmi In device.(This will be automated later).

#### Acceptance Criteria - test03

- Verify the Port status.

#### Expected Results - test03

- The test registers the event and check for port status event call back.

#### Test Steps - test03

- Initiate the Test:

  - Select and execute the Python file: **`dsHdmiIn_test3_PortStatusCallback_Verify.py`**
  - The test will automatically download all required artifacts and streams, copying them to the designated target directory before commencing execution.

-  Device Connect prompt:

    The test will Request User to connect Source device to Hdmi In port:

  - Question: "connect device to porttype and press Enter (Y/N)"
  - Press **Y** if Device is connected (this will mark the step as PASS).
  - Press **N** if user could not connect the device (this will mark the step as FAIL).

- Port Status Confirmation:

  - Test will check if the port status event has reached the device.
  - If event detected will mark the step as PASS
  - If event not detected will mark the step as FAIL

- Repeat for All Ports:

  The test will iterate through all available Hdmi IN ports, collects port status accordingly.

- Test Conclusion:

  Upon receiving user responses for all ports, the test will conclude and present a final result: PASS or FAIL based on the user inputs throughout the test execution.

- Completion and Result:

  Once all necessary user actions are completed, the test will evaluate the results and display whether the test Passed or Failed.

### dsHdmiIn_test4_VideoModeChangeCallback_Verify.py

#### Platform Supported - test04

- Sink

#### User Input Required - test04

-  **Yes**: User interaction is necessary to connect the Hdmi In device and to change the resolution on connected device.(This will be automated later).

#### Acceptance Criteria - test04

- Verify the video mode stauts.

#### Expected Results - test04

- The test registers the event and check for Video mode status event call back.

#### Test Steps - test04

- Select the test file:  

  - Run the Python script **`dsHdmiIn_test4_VideoModeChangeCallback_Verify.py`**
  - The test will automatically download all required artifacts and streams, copying them to the designated target directory before commencing execution.

  -  Device Connect prompt:

    The test will Request User to connect Source device to Hdmi In port:

  - Question: "connect device to porttype and press Enter (Y/N)"
  - Press **Y** if Device is connected (this will mark the step as PASS).
  - Press **N** if user could not connect the device (this will mark the step as FAIL).

  -  Device resolution change prompt:

    The test will Request User to change resolution on Source device connected to Hdmi In port:

  - Question: "Change the Resolution on device connected to port_type and then press Enter: (Y/N)"
  - Press **Y** if user able to change resolution (this will mark the step as PASS).
  - Press **N** if user unable to change the resolution  (this will mark the step as FAIL).

- Video mode Status Confirmation:

  - Test will check if the video mode status event has reached the device.
  - If event detected will mark the step as PASS
  - If event not detected will mark the step as FAIL

- Repeat for All Ports:

  The test will iterate through all available Hdmi IN ports, collects video mode status accordingly.

- Test Conclusion:

  Upon receiving user responses for all ports, the test will conclude and present a final result: PASS or FAIL based on the user inputs throughout the test execution.

- Completion and Result:

  Once all necessary user actions are completed, the test will evaluate the results and display whether the test Passed or Failed.


### dsHdmiIn_test5_AllmChangeCallback_Verify.py

#### Platform Supported - test05

- Sink

#### User Input Required - test05

-  **Yes**: User interaction is necessary to connect the Hdmi In device and to enable/disable ALLM on connected device.(This will be automated later).

#### Acceptance Criteria - test05

- Verify the ALLM status.

#### Expected Results - test05

- The test registers the event and check for ALLM change event call back

#### Test Steps - test05

- Select the test file:

  - Run the Python script **`dsHdmiIn_test5_AllmChangeCallback_Verify.py`**
  - The test will automatically download all required artifacts and streams, copying them to the designated target directory before commencing execution.

  -  Device Connect prompt:

    The test will Request User to connect Source device to Hdmi In port:

  - Question: "connect device to porttype and press Enter (Y/N)"
  - Press **Y** if Device is connected (this will mark the step as PASS).
  - Press **N** if user could not connect the device (this will mark the step as FAIL).

  - Device ALLM change prompt:

    The test will Request User to enable/disable ALLM on Source device connected to Hdmi In port:

  - Question: "Change ALLM mode on Hdmi In device connected to port to enable ALLM if its in OFF and press Enter: (Y/N)"
  - Press **Y** if user able to enable the ALLM feature (this will mark the step as PASS).
  - Press **N** if user unable to enable ALLM feature  (this will mark the step as FAIL).

  - Question: "Change ALLM mode on Hdmi In device connected to port to disable ALLM and press Enter: (Y/N)"
  - Press **Y** if user able to disable the ALLM feature (this will mark the step as PASS).
  - Press **N** if user unable to disable ALLM feature  (this will mark the step as FAIL).

- ALLM enable/disable Status Confirmation:

  - Test will check if the ALLM change event has reached the device.
  - If event detected will mark the step as PASS
  - If event not detected will mark the step as FAIL

- Repeat for All Ports:

  The test will iterate through all available Hdmi IN ports, collects ALLM status status accordingly.

- Test Conclusion:

  Upon receiving user responses for all ports, the test will conclude and present a final result: PASS or FAIL based on the user inputs throughout the test execution.

- Completion and Result:

  Once all necessary user actions are completed, the test will evaluate the results and display whether the test Passed or Failed.

### dsHdmiIn_test6_AVlatencyCallback_Verify.py

#### Platform Supported - test06

- Sink

#### User Input Required - test06

-  **Yes**: User interaction is necessary to connect the Hdmi In device on ports.(This will be automated later).

#### Acceptance Criteria - test06

- Verify the audio video latency.

#### Expected Results - test06

- The test registers the event and check for audio video latency event call back.

#### Test Steps - test06

- Select the test file:

  - Run the Python script **`dsHdmiIn_test6_AVlatencyCallback_Verify.py`**
  - The test will automatically download all required artifacts and streams, copying them to the designated target directory before commencing execution.
  -  Device Connect prompt:

    The test will Request User to connect Source device to Hdmi In port:

  - Question: "connect device to porttype and press Enter (Y/N)"
  - Press **Y** if Device is connected (this will mark the step as PASS).
  - Press **N** if user could not connect the device (this will mark the step as FAIL).

- Audio Video latency Confirmation:

  - Test will check if the audio video latency event has reached the device.
  - If event detected will mark the step as PASS
  - If event not detected will mark the step as FAIL

- Repeat for All Ports:

  The test will iterate through all available Hdmi IN ports, collects audio video latency status accordingly.

- Test Conclusion:

  Upon receiving user responses for all ports, the test will conclude and present a final result: PASS or FAIL based on the user inputs throughout the test execution.

### dsHdmiIn_test7_AVIChangeCallback_Verify.py

#### Platform Supported - test07

- Sink

#### User Input Required - test07

-  **Yes**: User interaction is necessary to connect the Hdmi In device and to change the AVI content on connected device.(This will be automated later).

#### Acceptance Criteria - test07

- Verify the AVI content type being played on device.

#### Expected Results - test07

- The test registers the event and check for AVI content change event call back

#### Test Steps - test07

- Select the test file:

  - Run the Python script **`dsHdmiIn_test7_AVIChangeCallback_Verify.py`**
  - The test will automatically download all required artifacts and streams, copying them to the designated target directory before commencing execution.

  -  Device Connect prompt:

    The test will Request User to connect Source device to Hdmi In port:

  - Question: "connect device to porttype and press Enter (Y/N)"
  - Press **Y** if Device is connected (this will mark the step as PASS).
  - Press **N** if user could not connect the device (this will mark the step as FAIL).

  -  Device AVI content change prompt:

    The test will Request User to change AVI content on Source device connected to Hdmi In port:

  - Question: "Change the AVI Content on device connected to port and press Enter: (Y/N)"
  - Press **Y** if user able to change AVI content (this will mark the step as PASS).
  - Press **N** if user unable to change the AVI content (this will mark the step as FAIL).

- AVI content Change Confirmation:

  - Test will check if the AVI content change event has reached the device.
  - If event detected will mark the step as PASS
  - If event not detected will mark the step as FAIL

- Repeat for All Ports:

  The test will iterate through all available Hdmi IN ports, collects AVI content change status accordingly.

- Test Conclusion:

  Upon receiving user responses for all ports, the test will conclude and present a final result: PASS or FAIL based on the user inputs throughout the test execution.

- Completion and Result:

  Once all necessary user actions are completed, the test will evaluate the results and display whether the test Passed or Failed.

### dsHdmiIn_test8_SelectPortAndVerifyPortStatus.py

#### Platform Supported - test08

- Sink

#### User Input Required - test08

-  **Yes**: User interaction is necessary to connect the Hdmi In device to port.(This will be automated later)

#### Acceptance Criteria - test08

- Verify the respective port is selected.

#### Expected Results - test08

- The test selects the respective port and verify the same.

#### Test Steps - test08

- Select the test file:

  - Run the Python script **`dsHdmiIn_test8_SelectPortAndVerifyPortStatus.py`**
  - The test will automatically download all required artifacts and streams, copying them to the designated target directory before commencing execution.

  -  Device Connect prompt:

    The test will Request User to connect Source device to Hdmi In port:

  - Question: "connect device to porttype and press Enter (Y/N)"
  - Press **Y** if Device is connected (this will mark the step as PASS).
  - Press **N** if user could not connect the device (this will mark the step as FAIL).

- Port select Confirmation:

  - Test will check the status of the port selected.
  - If port selected and supplied port argument is same then mark the step as PASS
  - If  port selected and supplied port argument is not same then  mark the step as FAIL

- Repeat for All Ports:

  The test will iterate through all available Hdmi IN ports, verify port status accordingly.

- Test Conclusion:

  Upon receiving user responses for all ports, the test will conclude and present a final result: PASS or FAIL based on the user inputs throughout the test execution.

- Completion and Result:

  Once all necessary user actions are completed, the test will evaluate the results and display whether the test Passed or Failed.

### dsHdmiIn_test9_ScaleVideoAndVerify.py

#### Platform Supported - test09

- Sink

#### User Input Required - test09

-  **Yes**: User interaction is necessary to connect the Hdmi In device and to verify the video scaling on connected device.(This will be automated later).

#### Acceptance Criteria - test09

- Verify the video scaled on selected port.

#### Expected Results - test09

- The test selects the respective port and scales video.

#### Test Steps - test09

- Select the test file:

  - Run the Python script **`dsHdmiIn_test9_ScaleVideoAndVerify.py`**
  - The test will automatically download all required artifacts and streams, copying them to the designated target directory before commencing execution.

  -  Device Connect prompt:

    The test will Request User to connect Source device to Hdmi In port:

  - Question: "connect device to porttype and press Enter (Y/N)"
  - Press **Y** if Device is connected (this will mark the step as PASS).
  - Press **N** if user could not connect the device (this will mark the step as FAIL).

- Video scaled Confirmation:
    The test will Request User to check video scaled on particular port or not:

  - Question: "Check if video is scaled  on port port_type. Press Y/N:"
  - Press **Y** if video scaled on particular port happen (this will mark the step as PASS).
  - Press **N** if video scaled on particular port not happen (this will mark the step as FAIL).

- Repeat for All Ports:

  The test will iterate through all available Hdmi IN ports, verify video scaling accordingly.

- Test Conclusion:

  Upon receiving user responses for all ports, the test will conclude and present a final result: PASS or FAIL based on the user inputs throughout the test execution.

- Completion and Result:

  Once all necessary user actions are completed, the test will evaluate the results and display whether the test Passed or Failed.


### dsHdmiIn_test10_ZoomModeAndVerify.py

#### Platform Supported - test10

- Source 

#### User Input Required - test10

-  **Yes**: User interaction is necessary to connect the Hdmi In device and to verify the video scaling on connected device.(This will be automated later).

#### Acceptance Criteria - test10

- Verify the zoom mode on selected port.

#### Expected Results - test10

- The test selects the respective port and sets zoom mode.

#### Test Steps - test10

- Select the test file:

  - Run the Python script **`dsHdmiIn_test10_ZoomModeAndVerify.py`**
  - The test will automatically download all required artifacts and streams, copying them to the designated target directory before commencing execution.

  -  Device Connect prompt:

    The test will Request User to connect Source device to Hdmi In port:

  - Question: "connect device to porttype and press Enter (Y/N)"
  - Press **Y** if Device is connected (this will mark the step as PASS).
  - Press **N** if user could not connect the device (this will mark the step as FAIL).

- Zoom Mode set Confirmation:
    The test will Request User to check particular zoom mode is set on particular port or not:

  - Question: "Verify Zoom Mode selected on port {port_type} and press Enter: Y/N"
  - Press **Y** if zoom mode ablet to set on particular port happen (this will mark the step as PASS).
  - Press **N** if unable to set zoom mode on particular port not happen (this will mark the step as FAIL).

- Repeat for All Ports:

  The test will iterate through all available Hdmi IN ports, verify zoom mode set accordingly.

- Test Conclusion:

  Upon receiving user responses for all ports, the test will conclude and present a final result: PASS or FAIL based on the user inputs throughout the test execution.

- Completion and Result:

  Once all necessary user actions are completed, the test will evaluate the results and display whether the test Passed or Failed.

### dsHdmiIn_test11_GetEDIDInfo_Verify.py

#### Platform Supported - test11

- Sink

#### User Input Required - test11

-  **NO**

#### Acceptance Criteria - test11

- Get and verify EDID info.

#### Expected Results - test11

- The test get EDID info and verifies the info.

#### Test Steps - test11

  - Run the Python script **`dsHdmiIn_test11_GetEDIDInfo_Verify.py`**
  - The test will automatically download all required artifacts and streams, copying them to the designated target directory before commencing execution.
- Edid Info Confirmation:

  - Test will get the EDID info and verifies the same.
  - If EDID info received will compared with the yaml EDID info bytes if same  will mark the step as PASS
  - If EDID info received will compared with the yaml EDID info bytes are not same  will mark the step as FAIL

- Repeat for All Ports:

  The test will iterate through all available Hdmi IN ports, gets EDID and verifies.

- Test Conclusion:

  Upon receiving user responses for all ports, the test will conclude and present a final result: PASS or FAIL based on the user inputs throughout the test execution.

- Completion and Result:

  Once all necessary user actions are completed, the test will evaluate the results and display whether the test Passed or Failed.

## dsHdmiIn_test12_GetSpdInfo_Verify.py

#### Platform Supported - test12

- Sink

#### User Input Required - test12

-  **Yes**: User interaction is necessary to connect the Hdmi In device to port.(This will be automated later).

#### Acceptance Criteria - test12

- Gets SPD Info and verifies the same.

#### Expected Results - test12

This test evaluates the SPD Info received from connected device.

#### Test Steps - test12

  - Run the Python script **`dsHdmiIn_test12_GetSpdInfo_Verify.py`**
  - The test will automatically download all required artifacts and streams, copying them to the designated target directory before commencing execution.

  -  Device Connect prompt:

    The test will Request User to connect Source device to Hdmi In port:

  - Question: "connect device to porttype and press Enter (Y/N)"
  - Press **Y** if Device is connected (this will mark the step as PASS).
  - Press **N** if user could not connect the device (this will mark the step as FAIL).

- SPD Info Confirmation:

  - Test will get the EDID info and verifies the same.

- Repeat for All Ports:

  The test will iterate through all available Hdmi IN ports, gets spdinfo and verifies the same.

- Test Conclusion:

  Upon receiving user responses for all ports, the test will conclude and present a final result: PASS or FAIL based on the user inputs throughout the test execution.

- Completion and Result:

  Once all necessary user actions are completed, the test will evaluate the results and display whether the test Passed or Failed.

### dsHdmiIn_test13_SetAndGetEDIDVersion.py

#### Platform Supported - test13

- Sink

#### User Input Required - test13

- ***NO***

#### Acceptance Criteria - test13

- Verify EDID version by retrieving.

#### Expected Results - test13

This test set EDID version and verifies the same by retrieving the EDID version.

#### Test Steps - test13

  - Run the Python script **`dsHdmiIn_test13_SetAndGetEDIDVersion.py`**
  - The test will automatically download all required artifacts and streams, copying them to the designated target directory before commencing execution.
- EDID version Verification:

  - Test will sets and get the EDID version.
  - If sets and gets EDID version are same then test will mark the step as PASS.
  - If sets and gets EDID version are not same then test will mark the step as FAIL.

- Repeat for All Ports:

  The test will iterate through all available Hdmi IN ports, sets EDID version and verifies by retrieving EDID version.

- Test Conclusion:

  Upon receiving user responses for all ports, the test will conclude and present a final result: PASS or FAIL based on the user inputs throughout the test execution.

- Completion and Result:

  Once all necessary user actions are completed, the test will evaluate the results and display whether the test Passed or Failed.

### dsHdmiIn_test14_SetAndGetEDID2ALLMSupport.py

#### Platform Supported - test14

- Sink

#### User Input Required - test14

- ***NO***

#### Acceptance Criteria - test14

- Verify ALLM by retrieving.

#### Expected Results - test14

This test set ALLM and verifies the same by retrieving the ALLM.

#### Test Steps - test13

  - Run the Python script **`dsHdmiIn_test14_SetAndGetEDID2ALLMSupport.py`**
  - The test will automatically download all required artifacts and streams, copying them to the designated target directory before commencing execution.
- EDID version Verification:

  - Test will sets and get the ALLM.
  - If sets and gets ALLM version are same then test will mark the step as PASS.
  - If sets and gets ALLM version are not same then test will mark the step as FAIL.

- Repeat for All Ports:

  The test will iterate through all available Hdmi IN ports, sets ALLM and verifies by retrieving ALLM.

- Test Conclusion:

  Upon receiving user responses for all ports, the test will conclude and present a final result: PASS or FAIL based on the user inputs throughout the test execution.

- Completion and Result:

  Once all necessary user actions are completed, the test will evaluate the results and display whether the test Passed or Failed.

