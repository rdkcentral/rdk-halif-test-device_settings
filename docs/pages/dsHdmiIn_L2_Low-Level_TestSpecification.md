# DSHDMIIN L2 Low Level Test Specification and Procedure Documentation

## Table of Contents

- [DSHDMIIN L2 Low Level Test Specification and Procedure Documentation](#dshdmiin-l2-low-level-test-specification-and-procedure-documentation)

  - [Table of Contents](#table-of-contents)
  - [Overview](#overview)
    - [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
    - [Definitions](#definitions)
    - [References](#references)
  - [Level 2 Test Procedure](#level-2-test-procedure)

## Overview

This document describes the level 2 testing suite for the DSHDMIIN module.

### Acronyms, Terms and Abbreviations

- `HAL` \- Hardware Abstraction Layer, may include some common components
- `UT`  \- Unit Test(s)
- `OEM`  \- Original Equipment Manufacture
- `SoC`  \- System on a Chip

### Definitions

  - `ut-core` \- Common Testing Framework <https://github.com/rdkcentral/ut-core>, which wraps a open-source framework that can be expanded to the requirements for future framework.

### References
- `High Level Test Specification` - [dsHdmiIn_test_spec.md](dsHdmiIn_test_spec.md)

## Level 2 Test Procedure

The following functions are expecting to test the module operates correctly.

### Test 1

|Title|Details|
|--|--|
|Function Name|`test_l2_dsHdmiIn_GetNumberOfInputs_sink`|
|Description|Verify that the function returns the expected `HDMI` Input ports. Compare the input port values by parsing the configuration YAML file for sink is `Sink_HDMIIN.yaml (HdmiInputPort/numberOfPorts)` and source is `Source_HDMIIN.yaml(HdmiInputPort/numberOfPorts)`|
|Test Group|Module : 02|
|Test Case ID|001|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

#### Test Procedure :

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize HDMI input using dsHdmiInInit | None | dsERR_NONE | Should be successful |
| 02 | Get the number of HDMI input ports using dsHdmiInGetNumberOfInputs | pNumberOfinputs = valid buffer | dsERR_NONE | Should be successful |
| 03 | Compare the number of HDMI input ports with the value in the configuration file | pNumberOfinputs = value from configuration file | dsERR_NONE | Should be successful |
| 04 | Terminate HDMI input using dsHdmiInTerm | None | dsERR_NONE | Should be successful |


```mermaid
graph TB
A[Call dsHdmiInInit API] -->|dsERR_NONE| B[Parse Sink_HDMIIN.yaml]
A -->|Failure| A1[Test case fail]
B -->|Success| C[Call dsHdmiInGetNumberOfInputs API]
B -->|Failure| B1[Test case fail]
C -->|Success| D[Compare pNumberOfinputs with YAML value]
C -->|Failure| C1[Test case fail]
D -->|Match| E[Call dsHdmiInTerm API]
D -->|Mismatch| D1[Test case fail]
E -->|Failure| E1[Test case fail]
E -->|dsERR_NONE| F[Test case success]
```


### Test 2

|Title|Details|
|--|--|
|Function Name|`test_l2_dsHdmiIn_GetNumberOfInputs_source`|
|Description|Verify that the function returns the expected `HDMI` Input ports. Compare the input port values by parsing the configuration YAML file for sink is `Sink_HDMIIN.yaml (HdmiInputPort/numberOfPorts)` and source is `Source_HDMIIN.yaml(HdmiInputPort/numberOfPorts)`|
|Test Group|Module : 02|
|Test Case ID|002|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

#### Test Procedure :

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize HDMI input using dsHdmiInInit | None | dsERR_NONE | Should be successful |
| 02 | Get the number of HDMI input ports from the configuration file | checkValue = "HdmiInputPort/numberOfPorts" | None | Should be successful |
| 03 | Get the number of HDMI input ports using dsHdmiInGetNumberOfInputs | numberOfInputs = valid buffer | dsERR_NONE | Should be successful |
| 04 | Compare the number of HDMI input ports obtained from the configuration file and the dsHdmiInGetNumberOfInputs function | numberOfInputs, checkValue | numberOfInputs should be equal to checkValue | Should be successful |
| 05 | Terminate HDMI input using dsHdmiInTerm | None | dsERR_NONE | Should be successful |


```mermaid
graph TB
A[Call dsHdmiInInit] -->|dsERR_NONE| B[Parse Source_HDMIIN.yaml]
A -->|Failure| A1[Test case fail]
B -->|Success| C[Call dsHdmiInGetNumberOfInputs]
B -->|Failure| B1[Test case fail]
C -->|dsERR_NONE| D[Compare dsHdmiInGetNumberOfInputs with YAML value]
C -->|Failure| C1[Test case fail]
D -->|Match| E[Call dsHdmiInTerm]
D -->|Mismatch| D1[Test case fail]
E -->|dsERR_NONE| F[Test case success]
E -->|Failure| E1[Test case fail]
```


### Test 3

|Title|Details|
|--|--|
|Function Name|`test_l2_dsHdmiIn_GetStatus_sink`|
|Description|Verify the HDMI port with the 'Get status' function when it is disabled, without selecting any port, and without any external devices.|
|Test Group|Module : 02|
|Test Case ID|003|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

#### Test Procedure :

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize HDMI input using dsHdmiInInit | None | dsERR_NONE | Should be successful |
| 02 | Get the status of HDMI input using dsHdmiInGetStatus | status = valid buffer | dsERR_NONE | Should be successful |
| 03 | Check if HDMI input is presented | isPresented = false | false | Should be successful |
| 04 | Check if any HDMI input port is active | activePort = dsHDMI_IN_PORT_NONE | dsHDMI_IN_PORT_NONE | Should be successful |
| 05 | Check if any HDMI input port is connected | isPortConnected[i] = false for all i in range 0 to dsHDMI_IN_PORT_MAX | false | Should be successful |
| 06 | Terminate HDMI input using dsHdmiInTerm | None | dsERR_NONE | Should be successful |


```mermaid
graph TB
A[Call dsHdmiInInit] -->|dsERR_NONE| B[Call dsHdmiInGetStatus]
A -->|Failure| A1[Test case fail]
B -->|dsERR_NONE| C[Check pStatus]
B -->|Failure| B1[Test case fail]
C -->|isPresented=false, isPortConnected=false, activePort=dsHDMI_IN_PORT_NONE| D[Call dsHdmiInTerm]
C -->|Failure| C1[Test case fail]
D -->|dsERR_NONE| E[Test case success]
D -->|Failure| D1[Test case fail]
```


### Test 4

|Title|Details|
|--|--|
|Function Name|`test_l2_dsHdmiIn_GetStatus_source`|
|Description|Verify the HDMI port with the 'Get status' function when it is disabled, without selecting any port, and without any external devices.|
|Test Group|Module : 02|
|Test Case ID|004|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

#### Test Procedure :

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize HDMI input using dsHdmiInInit() | None | dsERR_NONE | Should be successful |
| 02 | Get the status of HDMI input using dsHdmiInGetStatus() | status = valid pointer | dsERR_NONE | Should be successful |
| 03 | Verify the returned dsHdmiInStatus_t structure. Check if HDMI is presented and if any port is connected | isPresented = false, isPortConnected[i] = false for all i in range dsHDMI_IN_PORT_MAX | false | Should be successful |
| 04 | Check if any port is active | activePort = dsHDMI_IN_PORT_NONE | dsHDMI_IN_PORT_NONE | Should be successful |
| 05 | Terminate HDMI input using dsHdmiInTerm() | None | dsERR_NONE | Should be successful |


```mermaid
graph TB
    A[Call dsHdmiInInit] -->|dsERR_NONE| B[Call dsHdmiInGetStatus]
    A -->|!= dsERR_NONE| C[Test case fail]
    B -->|dsERR_NONE| D[Verify dsHdmiInStatus_t structure]
    B -->|!= dsERR_NONE| E[Test case fail]
    D -->|isPresented = false, isPortConnected = false, <br> activePort = dsHDMI_IN_PORT_NONE| F[Call dsHdmiInTerm]
    D -->|isPresented != false or isPortConnected != false or <br> activePort != dsHDMI_IN_PORT_NONE| G[Test case fail]
    F -->|dsERR_NONE| H[Test case pass]
    F -->|!= dsERR_NONE| I[Test case fail]
```


### Test 5

|Title|Details|
|--|--|
|Function Name|`test_l2_dsHdmiIn_VerifyHdmiInputPortStatus_sink`|
|Description|Loop through all `HDMI` Input port, verify that the function successfully sets the specified `HDMI` Input port without any external device connection and 'Get status' to check the active port is false, port connected is false and presentation is false.|
|Test Group|Module : 02|
|Test Case ID|005|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

#### Test Procedure :

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize HDMI input using dsHdmiInInit | None | dsERR_NONE | Should be successful |
| 02 | Get the number of HDMI inputs using dsHdmiInGetNumberOfInputs | numInputs = valid buffer | dsERR_NONE, numInputs > 0 | Should be successful |
| 03 | Loop through all HDMI input ports and select each port using dsHdmiInSelectPort | port = dsHDMI_IN_PORT_0 to numInputs-1, audioMix = false, evideoPlaneType = dsVideoPlane_PRIMARY, topMost = false | dsERR_NONE | Should be successful |
| 04 | Get the status of the selected HDMI input port using dsHdmiInGetStatus | status = valid buffer | dsERR_NONE, activePort = port, isPresented = false, isPortConnected[port] = false | Should be successful |
| 05 | Terminate HDMI input using dsHdmiInTerm | None | dsERR_NONE | Should be successful |


```mermaid
graph TB
A[Call dsHdmiInInit API] -->|dsERR_NONE| B[Call dsHdmiInGetNumberOfInputs API]
A -->|Not dsERR_NONE| A1[Test case fail]
B -->|dsERR_NONE and<br> non-zero inputs| C{Loop through all <br> HDMI input ports}
B -->|Not dsERR_NONE or <br>zero inputs| B1[Test case fail]
C --> D[Call dsHdmiInSelectPort API with current port]
D -->|dsERR_NONE| E[Call dsHdmiInGetStatus API]
E -->|dsERR_NONE, activePort is current port, isPresented is false, isPortConnected is false| F[Next port in loop]
F --> C
C -->|End of loop| G[Call dsHdmiInTerm API]
G -->|dsERR_NONE| H[Test case pass]
G -->|Not dsERR_NONE| G1[Test case fail]
```



### Test 6

|Title|Details|
|--|--|
|Function Name|`test_l2_dsHdmiIn_VerifyHdmiInputPortStatus_source`|
|Description|Loop through all `HDMI` Input port, verify that the function successfully sets the specified `HDMI` Input port without any external device connection and 'Get status' to check the active port is false, port connected is false and presentation is false.|
|Test Group|Module : 02|
|Test Case ID|006|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

#### Test Procedure :

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize HDMI input using dsHdmiInInit() | None | dsERR_NONE | Should be successful |
| 02 | Get the number of HDMI inputs using dsHdmiInGetNumberOfInputs() | numInputs = valid buffer | dsERR_NONE | Should be successful |
| 03 | Loop through each HDMI input port. For each port, select the port using dsHdmiInSelectPort() | port number = 0 to numInputs, isBlocking = false, videoPlane = dsVideoPlane_PRIMARY, isAudio = false | dsERR_NONE | Should be successful |
| 04 | Get the status of the selected port using dsHdmiInGetStatus() | status = valid buffer | dsERR_NONE | Should be successful |
| 05 | Check if the active port, port connected and presentation are all false | activePort = false, isPortConnected[i] = false, isPresented = false | dsERR_NONE | Should be successful |
| 06 | Terminate HDMI input using dsHdmiInTerm() | None | dsERR_NONE | Should be successful |


```mermaid
graph TB
    A[Call dsHdmiInInit] -->|dsERR_NONE| B[Call dsHdmiInGetNumberOfInputs]
    A -->|!=dsERR_NONE| A1[Test case fail]
    B -->|dsERR_NONE, numInputs| C{Loop through all <br> HDMI input ports}
    B -->|!=dsERR_NONE or ports out of range| B1[Test case fail]
    C --> D[Call dsHdmiInSelectPort with port number]
    D -->|dsERR_NONE| E[Call dsHdmiInGetStatus]
    E -->|dsERR_NONE| F[Verify activePort is false, isPortConnected is false,<br> isPresented is false]
    F --> G{End of Ports?}
    G -->|No| C
    G -->|Yes| H[Call dsHdmiInTerm]
    H -->|dsERR_NONE| I[Test case success]
    H -->|!=dsERR_NONE| H1[Test case fail]
```



### Test 7

|Title|Details|
|--|--|
|Function Name|`test_l2_dsHdmiIn_VerifyHdmiArcPort_sink`|
|Description|Loop through all the ports and verify whether the given port is an HDMI ARC port by comparing it with the `Sink_HDMIIN.yaml (HdmiArcPort/numberOfPorts)` configuration file.|
|Test Group|Module : 02|
|Test Case ID|007|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

#### Test Procedure :

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize HDMI input using dsHdmiInInit | None | dsERR_NONE | Should be successful |
| 02 | Loop through all HDMI input ports | iPort = dsHDMI_IN_PORT_0 to dsHDMI_IN_PORT_MAX | dsERR_NONE | Should be successful |
| 03 | For each port, check if it is an HDMI ARC port using dsIsHdmiARCPort | iPort = current port in loop, &isArcPort = valid buffer | dsERR_NONE | Should be successful |
| 04 | If the port is an HDMI ARC port, verify it with the configuration file | iPort = current port, isArcPort = value returned by dsIsHdmiARCPort | dsERR_NONE | Should be successful |
| 05 | Terminate HDMI input using dsHdmiInTerm | None | dsERR_NONE | Should be successful |


```mermaid
graph TB
    A[Call dsHdmiInInit API] -->|Success| B{Loop through <br> HDMI ports}
    A -->|Failure| A1[Test case fail]
    B --> C[Call dsIsHdmiARCPort API]
    C -->|Success| D[Check isArcPort flag]
    D -->|isArcPort is true| E[Compare with Sink_HDMIIN.yaml]
    E --> F[Is it the last HDMI port?]
    F -->|No| B
    F -->|Yes| G[Call dsHdmiInTerm API]
    G -->|Success| H[Test case pass]
    G -->|Failure| G1[Test case fail]
```



### Test 8

|Title|Details|
|--|--|
|Function Name|`test_l2_dsHdmiIn_SetAndGetEdidVersionAndValidateEdidLength_sink`|
|Description|Setting the `EDID` version for a given port and getting back the `EDID` version and compare with the Set value. Also, validate the EDID length for a given port. Compare the EDID length values by parsing the configuration YAML file `Sink_EDID_Info.yaml (EDID_Reference_Data/edidBytesLength)`|
|Test Group|Module : 02|
|Test Case ID|008|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

#### Test Procedure :

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize HDMI input module using dsHdmiInInit | None | dsERR_NONE | Should be successful |
| 02 | Set EDID version for each HDMI port using dsSetEdidVersion | hdmiPort = dsHDMI_IN_PORT_0 to dsHDMI_IN_PORT_2, edidVersion = HDMI_EDID_VER_14, HDMI_EDID_VER_20 | dsERR_NONE | Should be successful |
| 03 | Get  and compare the EDID version for each HDMI port using dsGetEdidVersion | hdmiPort  | dsERR_NONE | Should be successful |
| 04 | Get EDID bytes info for each HDMI port using dsGetEDIDBytesInfo and compare length with yaml file. | hdmiPort, edid = valid buffer, length = valid buffer | dsERR_NONE | Should be successful |
| 05 | Repeat steps 2 to 4 for all HDMI ports and EDID versions | | dsERR_NONE | Should be successful |
| 06 | Terminate HDMI input module using dsHdmiInTerm | None | dsERR_NONE | Should be successful |


```mermaid
graph TB
    A[dsHdmiInInit] --> |Success| B[dsSetEdidVersion for various ports and edid version]
    A --> |Failure| A1[Test Case Fail: dsHdmiInInit]
    B --> |Success| C[dsGetEdidVersion]
    B --> |Failure| B1[Test Case Fail: dsSetEdidVersion]
    C --> |Success & get and set matches | D[dsGetEDIDBytesInfo]
    C --> |Failure| C1[Test Case Fail: dsGetEdidVersion]
    D --> |Success| E[ParseYAML]
    D --> |Failure| D1[Test Case Fail: dsGetEDIDBytesInfo]
    E --> |Success| F[CompareLength]
    E --> |Failure| E1[Test Case Fail: ParseYAML]
    F --> |Success| G[dsHdmiInTerm]
    F --> |Failure| F1[Test Case Fail: CompareLength]
    G --> |Success| H[Test Case Success]
    G --> |Failure| G1[Test Case Fail: dsHdmiInTerm]
```


### Test 9

|Title|Details|
|--|--|
|Function Name|`test_l2_dsHdmiIn_GetSupportedGameFeaturesList_sink`|
|Description|Make sure that the functionality can list and get the count of all the game features that are supported. Compare the result by parsing the configuration YAML file `Sink_HDMIIN.yaml(gameFeatures/count)`|
|Test Group|Module : 02|
|Test Case ID|009|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

#### Test Procedure :

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize HDMI input using dsHdmiInInit | None | dsERR_NONE | Should be successful |
| 02 | Get the list of supported game features using dsGetSupportedGameFeaturesList | features = valid buffer | dsERR_NONE | Should be successful |
| 03 | Compare the count of game features with the count in the configuration file | features.gameFeatureCount = value from Sink_HDMIIN.yaml(gameFeatures/count) | dsERR_NONE | Should be successful |
| 04 | Terminate HDMI input using dsHdmiInTerm | None | dsERR_NONE | Should be successful |


```mermaid
graph TB
    A[Call dsHdmiInInit API] -->|dsERR_NONE| B[Call dsGetSupportedGameFeaturesList API]
    A -->|Failure| A1[Test case fail]
    B --> C[Verify gameFeatureCount field]
    B -->|Failure| B1[Test case fail]
    C -->|dsERR_NONE| D[Verify gameFeatureList field]
    C -->|Failure| C1[Test case fail]
    D --> E[Call dsHdmiInTerm API]
    D -->|Failure| D1[Test case fail]
    E --> F[Test case success]
    E -->|Failure| E1[Test case fail]
```


### Test 10

|Title|Details|
|--|--|
|Function Name|`test_l2_dsHdmiIn_SetAndGetAllmSupport_sink`|
|Description|Set and Get the `ALLM` support to `EDID` version 2.0 without connecting any source devices.|
|Test Group|Module : 02|
|Test Case ID|10|
|Priority|High|

**Pre-Conditions :**
None

**Dependencies :**
None

**User Interaction :**
If user chose to run the test in interactive mode, then the test case has to be selected via console.

#### Test Procedure :

| Variation / Steps | Description | Test Data | Expected Result | Notes|
| -- | --------- | ---------- | -------------- | ----- |
| 01 | Initialize HDMI input using dsHdmiInInit | None | dsERR_NONE | Should be successful |
| 02 | Set EDID 2.0 ALLM support to true using dsSetEdid2AllmSupport | iHdmiPort = dsHDMI_IN_PORT_0, allmSupport = true | dsERR_NONE | Should be successful |
| 03 | Get EDID 2.0 ALLM support using dsGetEdid2AllmSupport | iHdmiPort = dsHDMI_IN_PORT_0 | dsERR_NONE, allmSupport = true | Should be successful |
| 04 | Set EDID 2.0 ALLM support to false using dsSetEdid2AllmSupport | iHdmiPort = dsHDMI_IN_PORT_0, allmSupport = false | dsERR_NONE | Should be successful |
| 05 | Get EDID 2.0 ALLM support using dsGetEdid2AllmSupport | iHdmiPort = dsHDMI_IN_PORT_0 | dsERR_NONE, allmSupport = false | Should be successful |
| 06 | Terminate HDMI input using dsHdmiInTerm | None | dsERR_NONE | Should be successful |


```mermaid
graph TB
A[Call dsHdmiInInit] -->|Success| B[Call dsSetEdid2AllmSupport with true]
A -->|Failure| A1[Test case fail]
B -->|Success| C[Call dsGetEdid2AllmSupport]
B -->|Failure| B1[Test case fail]
C -->|Success| D[Call dsSetEdid2AllmSupport with false]
C -->|Failure| C1[Test case fail]
D -->|Success| E[Call dsGetEdid2AllmSupport]
D -->|Failure| D1[Test case fail]
E -->|Success| F[Call dsHdmiInTerm]
E -->|Failure| E1[Test case fail]
F -->|Success| G[Test case success]
F -->|Failure| F1[Test case fail]
```