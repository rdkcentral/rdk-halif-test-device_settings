# dsVideoDevice HAL L1 and L2 Test Procedure

## Table of Contents

- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Run L1 and L2 Test directly (without python)](#run-l1-and-l2-test-directly-without-python)
- [Run L1 and L2 using python](#run-l1-and-l2-using-python)
  - [Setting Up Test Environment](#setting-up-test-environment)
  - [Update Configuration Files](#update-configuration-files)
  - [Run Test Cases](#run-test-cases)

## Acronyms, Terms and Abbreviations

- `HAL`    - Hardware Abstraction Layer
- `L1`     - Level 1 Testing
- `L2`     - Level 2 Testing
- `DUT`    - Device Under Test
- `RAFT`   - Rapid Automation Framework for Testing
- `YAML`   - YAML Ain't Markup Language

## Run L1 and L2 Test directly (without python)

- Copy the hal binaries, libraries and the profile to the `DUT`

eg:
```bash
    scp bin/run.sh <user>@<ip>:/tmp/dsVideoDevice/ -p <port number>
    scp bin/hal_test <user>@<ip>:/tmp/dsVideoDevice/ -p <port number>
    scp bin/libut_control.so <user>@<ip>:/tmp/dsVideoDevice/ -p <port number>
    scp profile/<profile.yaml> <user>@<ip>:/tmp/dsVideoDevice/ -p <port number>
```

- on `DUT` run the test

```bash
    cd /tmp/dsVideoDevice
    ./run.sh -p <profile.yaml>
```

- Run all the test cases or individual cases by selecting corresponding menu option

```bash
***************** CUNIT CONSOLE - MAIN MENU ******************************
(R)un  (S)elect  (L)ist  (A)ctivate  (F)ailures  (O)ptions  (H)elp  (Q)uit
Enter command: H

Commands:  R - run all tests in all suites
           S - Select a suite to run or modify
           L - List all registered suites
           A - Activate or deactivate a suite (toggle)
           F - Show failures from last test run
           O - Set CUnit options
           H - Show this help message
           Q - Quit the application

```

## Run L1 and L2 using python

### Setting Up Test Environment

To execute `HAL` `L1` and `L2` Python test cases, need a Python environment. Follow these steps mentioned in [HPK Public Documentation](https://github.com/rdkcentral/rdk-hpk-documentation/blob/main/README.md)

### Update Configuration Files

#### Rack Configuration File

Example Rack configuration File: [example_rack_config.yml](../../../../ut/host/tests/configs/example_rack_config.yml)

For more details refer [RAFT](https://github.com/rdkcentral/python_raft/blob/1.0.0/README.md) and [example_rack_config.yml](https://github.com/rdkcentral/python_raft/blob/1.0.0/examples/configs/example_rack_config.yml)

In this file, update the configuration to define the console sessions for the `DUT` and the outbound settings:

|Console Session|Description|
|---------------|-----------|
|default|To run the `HAL` binary|

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
      outbound:
        download_url: "http://localhost:8000/"    # download location for the CPE device
        httpProxy:   # Local Proxy if required
        workspaceDirectory: './logs/workspace'   # Local working directory
```

#### Device Configuration File

Example Device configuration File: [deviceConfig.yml](ut/host/tests/configs/deviceConfig.yml)

For more details refer [RAFT](https://github.com/rdkcentral/python_raft/blob/1.0.0/README.md) and [example_device_config.yml](https://github.com/rdkcentral/python_raft/blob/1.0.0/examples/configs/example_device_config.yml)

Update below fields in the device configuration file:

- Set the path for `target_directory` where `HAL` binaries will be copied onto the device.
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
```

#### Test Setup Configuration File

Example Test Setup configuration File: [dsVideoDevice_L1_L2_testSetup.yml](../../../../ut/host/tests/L1_L2_TestCases/dsVideoDevice/dsVideoDevice_L1_L2_testSetup.yml)

This `yaml` contains the list of test_suites and test_cases to run

eg:
```yaml
dsVideoDevice:
  description: "dsVideoDevice Device Settings L1 and L2 test setup"
  test_suites: # List of L1 and L2 test suites
    - name: "L1 dsVideoDevice" # Name of the test suit to run
      test_cases: # List of test cases to execute, if empty test runs all test cases with `r` option
        - dsVideoDeviceInit_positive
        - dsVideoDeviceTerm_positive
        - dsGetVideoDevice_positive
    - name: "L1 dsVideoDevice"
      test_cases: # Runs all tests in the test suit
    - name: "L1 dsVideoDevice" # Name of the test suit to run
      test_cases: # List of test cases to execute, if empty test runs all test cases with `r` option
        - dsGetSupportVidFormats_negative
        - dsGetVideoCodecInfo_negative
        - dsSetFRFMode_negative
        - dsGetFRFMode_negative
    - name: "L2 dsVideoDevice - Sink"
      test_cases:
        - GetHDRCapabilities
        - GetSupportedVideoCodingFormats
        - SetAndVerifyDisplayframerate
        - SetAndVerifyFRFMode
```

#### Test Configuration

Example Test Setup configuration File: [dsVideoDevice_testConfig.yml](../../../host/tests/dsClasses/dsVideoDevice_testConfig.yml)

Execute command to run the HAL binary was provided in this file.

```yaml
dsVideoDevice:
    description: "dsVideoDevice Device Settings testing profile / menu system for UT"
    test:
        artifacts:
        #List of artifacts folders, test class copies the content of folder to the target device workspace
          - "../../../bin/"
        # exectute command, this will appended with the target device workspace path
        execute: "run.sh"
        type: UT-C # C (UT-C Cunit) / C++ (UT-G (g++ ut-core gtest backend))
```

### Run Test Cases

Once the environment is set up, you can execute the test cases with the following command

```bash
python dsVideoDevice_L1_L2_tests.py --config </PATH>/ut/host/tests/configs/example_rack_config.yml --deviceConfig </PATH>/ut/host/tests/configs/deviceConfig.yml
```
