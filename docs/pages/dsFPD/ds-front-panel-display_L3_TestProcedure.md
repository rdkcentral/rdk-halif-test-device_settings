# dsFPD HAL L3 Python Test Procedure

## Acronyms, Terms and Abbreviations

- `HAL`    - Hardware Abstraction Layer
- `L3`     - Level 3 Testing
- `FPD`    - Front Panel Display
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
|default|Downloads the artifacts required for test cases|
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
      profile: "../../../../profiles/sink/Sink_FPD.yaml"
```

#### Test Setup Configuration File

Example Test Setup configuration File: [dsFPD_L3_testSetup.yml](../../../host/tests/L3_TestCases/dsFPD/dsFPD_L3_testSetup.yml)

Update the artifact paths from which the binaries should be copied to the device.

Set the execution paths for each test case.

```yaml
dsFPD:
  description: "dsFPD Device Settings test setup"
  assets:
    device:
      defaults: &defaults
        execute:
      test01_EnableDisableAndVerifyLEDIndicators:
        <<: *defaults
      test02_SetVerifyLEDIndicatorsBrightness:
        <<: *defaults
      test03_SetVerifyLEDIndicatorsBlink:
        <<: *defaults
      test04_SetVerifyLEDIndicatorsColor:
        <<: *defaults
      test05_SetVerifyFPPattern:
        <<: *defaults
```

#### Test Suite Configuration

Example Test Setup configuration File: [dsFPD_testConfig.yml](../../../host/tests/dsClasses/dsFPD_testConfig.yml)

Update the execute command according to the device path where `HAL` binaries are copied.

## Run Test Cases

Once the environment is set up, you can execute the test cases with the following command

```bash
python <TestCaseName.py> --config </PATH>/ut/host/tests/configs/example_rack_config.yml --deviceConfig </PATH>/ut/host/tests/configs/deviceConfig.yml
```
## Test Cases

### dsFPD_test01_EnableDisableAndVerifyLEDIndicators.py

### Overview

This test helps to verify if the Led indicators can be switched ON and OFF using the HAL API's

#### Platform Support - test01

- Source
- Sink


#### User Input Required - test01

**Yes**: User interaction is necessary to confirm front panel LED status (This will be automated later).

#### Acceptance Criteria - test01

Set supported Front panel LED State to ON and OFF and verify.

#### Expected Results - test01

The test enables the supported front panel LED, and subsequently disabled the LED

Success Criteria

- User should see the supported LED turned to ON State
- User should see the supported LED turned to OFF state.

#### Test Steps - test01

- Initiate the Test:

  - Select and execute the Python file: **`dsFPD_test01_EnableDisableAndVerifyLEDIndicators.py`**
  - The test will automatically download all required artifacts, copying them to the designated target directory before commencing execution.

- LED state Verification:

    The test will enable LED and prompt the user with the following:

  - Question: "Is Indicator state dsFPD_STATE_ON ? (Y/N):? (Y/N)"
  - Press **Y** if specified LED indicator is ON  (this will mark the step as PASS).
  - Press **N** if specified LED indicator is OFF (this will mark the step as FAIL).

- LED status confirmation (LED indicator Disabled):

  After confirming LED state, the test will disable the LED indicator and prompt the user again:

  - Question: "Is Indicator state dsFPD_STATE_OFF ? (Y/N)"
  - Press **Y** if specified LED indicator is OFF (this will mark the step as PASS).
  - Press **N** if specified LED indicator is ON  (this will mark the step as FAIL).

- Repeat for All supported LED indicators:

  The test will iterate through all supported Indicators, enabling/disabling each one and collecting user feedback accordingly.

- Test Conclusion:

  Upon receiving user responses for all indicators, the test will conclude and present a final result: PASS or FAIL based on the user inputs throughout the test execution.

### dsFPD_test02_SetVerifyLEDIndicatorsBrightness.py

### Overview

This test helps to verify if the Led indicators can be set with specified brightness.

#### Platform Support - test02

- Source
- Sink

#### User Input Required - test02

**Yes**: User interaction is necessary to confirm front panel LED status and Brightness (This will be automated later).

#### Acceptance Criteria - test02

Set supported Front panel LED can be set with different brightness, 0%, 50% and 100%

#### Expected Results - test02

The test enables the supported front panel LED, sets brightness value to 0, 50 and 100, subsequently disables the LED indicator.

Success Criteria

- User should see the supported LED turned to ON State
- User should see the supported LED glowing in 0% brightness
- User should see the supported LED glowing in 50% brightness
- User should see the supported LED glowing in 100% brightness
- User should see the supported LED turned to OFF state.

#### Test Steps - test02

- Initiate the Test:

  - Select and execute the Python file: **`dsFPD_test02_SetVerifyLEDIndicatorsBrightness.py`**
  - The test will automatically download all required artifacts, copying them to the designated target directory before commencing execution.

- LED state Verification:

    The test will enable LED and prompt the user with the following:

  - Question: "Is Indicator state dsFPD_STATE_ON ? (Y/N):? (Y/N)"
  - Press **Y** if specified LED indicator is ON  (this will mark the step as PASS).
  - Press **N** if specified LED indicator is OFF (this will mark the step as FAIL).

- LED 0% brightness Verification:

    The test will set LED brightness to 0% and prompt the user with the following:

  - Question: "Is Indicator brightness 0% ? (Y/N):? (Y/N)"
  - Press **Y** if specified LED indicator brightness is 0%  (this will mark the step as PASS).
  - Press **N** if specified LED indicator brightness is not 0% (this will mark the step as FAIL).

- LED 50% brightness Verification:

    The test will set LED brightness to 50% and prompt the user with the following:

  - Question: "Is Indicator brightness 50% ? (Y/N):? (Y/N)"
  - Press **Y** if specified LED indicator brightness is 50%  (this will mark the step as PASS).
  - Press **N** if specified LED indicator brightness is not 50% (this will mark the step as FAIL).

- LED 100% brightness Verification:

    The test will set LED brightness to 100% and prompt the user with the following:

  - Question: "Is Indicator brightness 100% ? (Y/N):? (Y/N)"
  - Press **Y** if specified LED indicator brightness is 100%  (this will mark the step as PASS).
  - Press **N** if specified LED indicator brightness is not 100% (this will mark the step as FAIL).

- LED status confirmation (LED indicator Disabled):

  After confirming LED state, the test will disable the LED indicator and prompt the user again:

  - Question: "Is Indicator state dsFPD_STATE_OFF ? (Y/N)"
  - Press **Y** if specified LED indicator is OFF (this will mark the step as PASS).
  - Press **N** if specified LED indicator is ON  (this will mark the step as FAIL).

- Repeat for All supported LED indicators:

  The test will iterate through all supported Indicators, enabling/disabling and setting brightness to each one and collecting user feedback accordingly.

- Test Conclusion:

  Upon receiving user responses for all indicators, the test will conclude and present a final result: PASS or FAIL based on the user inputs throughout the test execution.

### dsFPD_test03_SetVerifyLEDIndicatorsBlink.py

### Overview

This test helps to verify if the Led indicators can blink with specified parameter.

#### Platform Support - test03

- Source
- Sink

#### User Input Required - test03

**Yes**: User interaction is necessary to confirm front panel LED status and blinking (This will be automated later).

#### Acceptance Criteria - test03

Set supported Front panel LED with blink duration of 1000 ms and 5 iterations.

#### Expected Results - test02

The test enables the supported front panel LED, sets LED to blink with 1000ms duration and 5 iterations , subsequently disables the LED indicator.

Success Criteria

- User should see the supported LED turned to ON State
- User should see the supported LED blinking with 1000ms duration and 5 iterations.
- User should see the supported LED turned to OFF state.

#### Test Steps - test03

- Initiate the Test:

  - Select and execute the Python file: **`dsFPD_test03_SetVerifyLEDIndicatorsBlink.py`**
  - The test will automatically download all required artifacts, copying them to the designated target directory before commencing execution.

- LED state Verification:

    The test will enable LED and prompt the user with the following:

  - Question: "Is Indicator state dsFPD_STATE_ON ? (Y/N):? (Y/N)"
  - Press **Y** if specified LED indicator is ON  (this will mark the step as PASS).
  - Press **N** if specified LED indicator is OFF (this will mark the step as FAIL).

- LED blink Verification:

    The test will set LED to blink with duration of 1000ms for 5 times and prompt the user with the following:

  - Question: "Is indicator blinking 5 times with 1 sec ? (Y/N)"
  - Press **Y** if specified LED indicator blink with the duration specified. (this will mark the step as PASS).
  - Press **N** if specified LED indicator did not blink with duration specified. (this will mark the step as FAIL).

- LED status confirmation (LED indicator Disabled):

  After confirming LED state, the test will disable the LED indicator and prompt the user again:

  - Question: "Is Indicator state dsFPD_STATE_OFF ? (Y/N)"
  - Press **Y** if specified LED indicator is OFF (this will mark the step as PASS).
  - Press **N** if specified LED indicator is ON  (this will mark the step as FAIL).

- Repeat for All supported LED indicators:

  The test will iterate through all supported Indicators, enabling/disabling and setting blink parameter to each one and collecting user feedback accordingly.

- Test Conclusion:

  Upon receiving user responses for all indicators, the test will conclude and present a final result: PASS or FAIL based on the user inputs throughout the test execution.

### dsFPD_test04_SetVerifyLEDIndicatorsColor.py

### Overview

This test helps to verify if the Led indicators can set with supported colors.

#### Platform Support - test04

- Source
- Sink

#### User Input Required - test04

**Yes**: User interaction is necessary to confirm front panel LED status and blinking (This will be automated later).

#### Acceptance Criteria - test04

Set supported Front panel LED set with supported colors.

#### Expected Results - test04

The test enables the supported front panel LED, sets LED to its supported colors , subsequently disables the LED indicator.

Success Criteria

- User should see the supported LED turned to ON State
- User should see the supported LED set with supported color
- User should see the supported LED turned to OFF state.

#### Test Steps - test04

- Initiate the Test:

  - Select and execute the Python file: **`dsFPD_test04_SetVerifyLEDIndicatorsColor.py`**
  - The test will automatically download all required artifacts, copying them to the designated target directory before commencing execution.

- LED state Verification:

    The test will enable LED and prompt the user with the following:

  - Question: "Is Indicator state dsFPD_STATE_ON ? (Y/N):? (Y/N)"
  - Press **Y** if specified LED indicator is ON  (this will mark the step as PASS).
  - Press **N** if specified LED indicator is OFF (this will mark the step as FAIL).

- LED color Verification:

    The test will set LED to supported color and prompt the user with the following:

  - Question: "Is indicator color <color>? (Y/N)"
  - Press **Y** if specified LED indicator set with specified color. (this will mark the step as PASS).
  - Press **N** if specified LED indicator is not set with specified color. (this will mark the step as FAIL).

- Repeat for All supported color for the LED indicators:

  The test will iterate through all supported colors of the indicator and collecting user feedback accordingly.

- LED status confirmation (LED indicator Disabled):

  After confirming LED state, the test will disable the LED indicator and prompt the user again:

  - Question: "Is Indicator state dsFPD_STATE_OFF ? (Y/N)"
  - Press **Y** if specified LED indicator is OFF (this will mark the step as PASS).
  - Press **N** if specified LED indicator is ON  (this will mark the step as FAIL).

- Repeat for All supported LED indicators:

  The test will iterate through all supported Indicators and collecting user feedback accordingly.

- Test Conclusion:

  Upon receiving user responses for all indicators, the test will conclude and present a final result: PASS or FAIL based on the user inputs throughout the test execution.

### dsFPD_test05_SetVerifyFPPattern.py

### Overview

This test helps to verify if the front panel can set with different patterns.

#### Platform Support - test05

- Source
- Sink

#### User Input Required - test05

**Yes**: User interaction is necessary to confirm front panel Patterns is set (This will be automated later).

#### Acceptance Criteria - test05

Set supported Front panel pattern

#### Expected Results - test05

The test sets all the supported Front panel patterns and verifies.

Success Criteria

- User should see all the supported front panel patterns one buy one.

#### Test Steps - test05

- Initiate the Test:

  - Select and execute the Python file: **`dsFPD_test05_SetVerifyFPPattern.py`**
  - The test will automatically download all required artifacts, copying them to the designated target directory before commencing execution.

- Front panel pattern verification:

    The test will set the pattern and prompt the user with the following:

  - Question: "Is Front panel shows <Pattern> ? (Y/N):? (Y/N)"
  - Press **Y** if specified pattern is shown  (this will mark the step as PASS).
  - Press **N** if specified pattern is not shown (this will mark the step as FAIL).


- Repeat for All supported patterns:

  The test will iterate through all supported patterns of the device collecting user feedback accordingly.

- Test Conclusion:

  Upon receiving user responses for all indicators, the test will conclude and present a final result: PASS or FAIL based on the user inputs throughout the test execution.

### dsFPD_L3_Runall.py

This python file runs all the tests supported

```bash
python dsFPD_L3_Runall.py --config </PATH>/ut/host/tests/configs/example_rack_config.yml --deviceConfig </PATH>/ut/host/tests/configs/deviceConfig.yml
```
