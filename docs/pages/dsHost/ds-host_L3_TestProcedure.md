# dsHost HAL L3 Python Test Procedure

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Setting Up Test Environment](#setting-up-test-environment)
- [Streams Required](#streams-required)
- [Test Setup Connections](#test-setup-connections)
- [Test Cases](#test-cases)
  = [dsHost_test1_VerifyTemperature.py](#dshost_test1_verifytemperaturepy)
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
      profile: "../../../../profiles/sink/Sink_HostSettings.yaml"
      player:
        tool: "gstreamer"
        prerequisites:
          - export xxxx    # Pre-commands required to play the stream

```

#### Test Setup Configuration File

Example Test Setup configuration File: `ut/host/tests/dsHost_L3_Tests/dsHost_L3_testSetup.yml`

Update the artifact paths from which the binaries should be copied to the device.

Set the execution paths and provide the stream paths for each test case.

If a test case requires multiple streams or needs to be validated using several streams, ensure that all necessary streams are added sequentially for that specific test case.

```yaml
dsHost:
  description: "dsHost Device Settings test setup"
  assets:
    device:
      defaults: &defaults
        artifacts:
          - "<path>/bin/hal_test"
          - "<path>/bin/libut_control.so"
          - "<path>/bin/Sink_HostSettings.yaml"
          - "<path>/bin/run.sh"
        execute:
          - "chmod +x /opt/HAL/dshost_L3/hal_test"
          - "chmod +x /opt/HAL/dshost_L3/run.sh"
          - cp -rf /usr/lib/libdshal.so /opt/HAL/dshost_L3/
          - "ln -s /usr/lib/libds-hal.so /opt/HAL/dshost_L3/libdshal.so"
        streams:
        test1_VerifyConnect_Callback:
          <<: *defaults
          streams:
```

#### Test Suite Configuration

Example Test Setup configuration File: `ut/host/tests/dsClasses/dshost_test_suite.yml`

Update the execute command according to the device path where `HAL` binaries are copied.

```yaml
dsHost:
  description: "dsHost Device Settings testing profile"
  test:
    execute: "/tmp/run.sh -p /tmp/Sink_HostSettings.yaml"
    type: UT-C  # Cunit tests (UT-C)

```

## Run Test Cases

Once the environment is set up, you can execute the test cases with the following command

```bash
python <TestCaseName.py> --config </PATH>/ut/host/tests/configs/example_rack_config.yml --deviceConfig </PATH>/ut/host/tests/configs/deviceConfig.yml
```

## Test Setup Connections

To verify the verify the get temperature works as expected.
For Example:

- Get the temperature, and then place the device in a heat chamber, and verify the temperature increases.

## Test Cases
### dsHost_test1_VerifyTemperature.py

#### Platform Support - test01

- Sink/Source

#### User Input Required - test01

**Yes**: User interaction is necessary to connect/disconnect Composite Source device (This will be automated later).

#### Acceptance Criteria - test01

The temperature is noted to be increasing once placed in the heat chamber, or location to increase the temperature

#### Expected Results - test01

The temperature should increase

#### Test Steps - test01

- Initiate the Test:

  - Select and execute the Python file: **`dsHost_test1_VerifyTemperature.py`**
  - The test will automatically download all required artifacts, copying them to the designated target directory before commencing execution.

- Increase Temperature prompt:

    The test will Request User to place the device in a heat chamber, or do something to icnrease the temperature:

  - Question: "Please begin to increase the temperature, and wait around one to two minutes before pressing enter to continue:"
  - Press **Enter** once the device is in a location to increase the temperature and suitable time has passed the the change in temperature can be recorded..

- Test Conclusion:

  The temperature should increase as expected.

