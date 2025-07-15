# Device Settings Composite Input L2 Low Level Test Specification and Procedure Documentation


## Overview

This document describes the Low Level L2 Test Specification and Procedure for the Device Settings Composite Input module.

### Acronyms, Terms and Abbreviations

- `HAL` \- Hardware Abstraction Layer, may include some common components
- `UT`  \- Unit Test(s)
- `OEM`  \- Original Equipment Manufacture
- `SoC`  \- System on a Chip

### Definitions

- `ut-core` \- Common Testing Framework <https://github.com/rdkcentral/ut-core>, which wraps a open-source framework that can be expanded to the requirements for future framework.

### References

- `High Level Test Specification` - [ds-compositeIn-High-Level_TestSpec.md](https://github.com/rdkcentral/rdk-halif-test-device_settings/blob/main/docs/pages/ds-compositeIn-High-Level_TestSpec.md)
- `HAL Interface file` - [dsCompositeIn Header](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsCompositeIn.h)

## Level 2 Test Procedure

The following functions are expecting to test the module operates correctly.

### Test 1

|Title|Details|
|--|--|
|Function Name|`test_l2_dsCompositeIn_GetNumberOfInputs`|
|Description|Ensure that the function returns the expected number of COMPOSITE input ports by comparing the input port values parsed from the configuration YAML file for the platform under test. The value to be retrieved from the YAML is `dsCompositeIn/composite_input_configurations/number_of_ports`.|
|Test Group|02|
|Test Case ID|001|
|Priority|High|

**Pre-Conditions**
None

**Dependencies**
None

**User Interaction**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

#### Test Procedure - Test 1

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize the COMPOSITE Input module using `dsCompositeInInit` | None | `dsERR_NONE` | Should be successful |
| 02 | Get the number of COMPOSITE Input ports using `dsCompositeInGetNumberOfInputs` | numInputs = valid buffer | `dsERR_NONE` | Should be successful |
| 03 | Compare the value returned by `dsCompositeInGetNumberOfInputs` with the value retrieved from the YAML file | numInputs, `dsCompositeIn/composite_input_configurations/number_of_ports` from configuration file | They should match | Should be successful |
| 04 | Terminate the COMPOSITE Input module using `dsCompositeInTerm` | None | `dsERR_NONE` | Should be successful |

```mermaid
graph TB
A[Call dsCompositeInInit] -->|Success| B[Parse 'Panel_CompositeInput.yaml']
A -->|Failure| A1[Test case fail: dsCompositeInInit failed]
B -->|Success| C[Call dsCompositeInGetNumberOfInputs]
B -->|Failure| B1[Test case fail: Parsing YAML file failed]
C -->|Success| E[Compare num of ports values]
C -->|Failure| C1[Test case fail: dsCompositeInGetNumberOfInputs failed]
E -->|Success| F[Call dsCompositeInTerm]
E -->|Failure| E1[Test case fail]
F -->|Success| G[Test case success]
F -->|Failure| F1[Test case fail: dsCompositeInTerm failed]
```

### Test 2

|Title|Details|
|--|--|
|Function Name|`test_l2_dsCompositeIn_VerifyCompositeInputStatus`|
|Description|Verify the status of the Composite Inputs by ensuring it is in disable status.|
|Test Group|02|
|Test Case ID|002|
|Priority|High|

**Pre-Conditions**
None

**Dependencies**
None

**User Interaction**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

#### Test Procedure - Test 2

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize the Composite Input using `dsCompositeInInit` | None | `dsERR_NONE` | Should be successful |
| 02 | Get the status of the Composite Input using `dsCompositeInGetStatus` | status = valid buffer | `dsERR_NONE` | Should be successful |
| 03 | Check if the Composite Input is presented or not | isPresented = false | false | Should be successful |
| 04 | Loop through and check if each of the Composite Input Port existing on the platform is connected or not| status.isPortConnected[Port No] = false | false | Should be successful |
| 05 | Check the active port of the Composite Input | status.activePort = `dsCOMPOSITE_IN_PORT_NONE` | `dsCOMPOSITE_IN_PORT_NONE` | Should be successful |
| 06 | Terminate the Composite Input using `dsCompositeInTerm` | None | `dsERR_NONE` | Should be successful |

```mermaid
graph TB
    Step1[Call dsCompositeInInit] -->|dsERR_NONE| Step2[Call dsCompositeInGetStatus]
    Step1 -->|Failure| Fail1[Test Case Failed: dsCompositeInInit failed]
    Step2 -->|dsERR_NONE| Step3[Check 'isPresented' field]
    Step2 -->|Failure| Fail2[Test Case Failed: dsCompositeInGetStatus failed]
    Step3 -->|isPresented = false| Step4Loop{Loop through each port as per test profile} --> Step4
    Step3 -->|Failure| Fail3[Test Case Failed: isPresented field check failed]
    Step4[Check 'isPortConnected' field] -->|Failure| Fail4[Test Case Failed: isPortConnected field check failed] -->     Step5LoopCheck[Loop check]
    Step4 -->|Passed| Pass1[isPortConnected field check passed] --> Step5LoopCheck[Loop check]
    Step5LoopCheck -->|More ports| Step4Loop
    Step5LoopCheck -->|Loop ends| Step6[Check 'activePort' field]
    Step6 -->|activePort = dsCOMPOSITE_IN_PORT_NONE| Step7[Call dsCompositeInTerm]
    Step6 -->|Failure| Fail5[Test Case Failed: activePort field check failed]
    Step7 -->|dsERR_NONE| Step8[Test Case Passed]
    Step7 -->|Failure| Fail6[Test Case Failed: dsCompositeInTerm failed]
```

### Test 3

|Title|Details|
|--|--|
|Function Name|`test_l2_dsCompositeIn_VerifyCompositeInPortSelectionAndStatus`|
|Description|Loop through all the existing composite ports on the platform, verify that the function successfully sets the specified COMPOSITE Input port when there is no connection of source device, and check the disable status of the port information using Get status.|
|Test Group|02|
|Test Case ID|003|
|Priority|High|

**Pre-Conditions**
None

**Dependencies**
None

**User Interaction**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

#### Test Procedure - Test 3

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize the COMPOSITE Input module using `dsCompositeInInit` | None | `dsERR_NONE` | Should be successful |
| 02 | Loop through the supported COMPOSITE Input ports on the platform based on the get number of Inputs and select each port using `dsCompositeInSelectPort` | port = `dsCompositeInGetNumberOfInputs` | `dsERR_NONE` | Should be successful |
| 03 | Get the status of the selected COMPOSITE Input port using `dsCompositeInGetStatus` | status = valid buffer | `dsERR_NONE` | Should be successful |
| 04 | Check if the active port is the selected port ,if the port is not presented and if the port is not connected | activePort = port, isPresented = false, isPortConnected = false | activePort = port, isPresented = false, isPortConnected = false | Should be successful |
| 05 | Terminate the COMPOSITE Input module using `dsCompositeInTerm` | None | `dsERR_NONE` | Should be successful |

```mermaid
graph TB
    A[Call dsCompositeInInit] -->|Success| B{Loop through <br> all composite <br> ports}
    A -->|Failure| A1[Test case fail]
    B -->|dsCOMPOSITE_IN_PORT_0 to dsCOMPOSITE_IN_PORT_MAX| C[Call dsCompositeInSelectPort <br> with current port]
    C -->|Success| D[Verify function sets <br> specified COMPOSITE <br> Input port]
    D --> E[Call dsCompositeInGetStatus]
    E -->|Success| F[Check disable status of the port]
    F --> G{End of Loop?}
    G -->|No| B
    G -->|Yes| H[Call dsCompositeInTerm]
    H -->|Success| I[Test case success]
    H -->|Failure| H1[Test case fail]
```
