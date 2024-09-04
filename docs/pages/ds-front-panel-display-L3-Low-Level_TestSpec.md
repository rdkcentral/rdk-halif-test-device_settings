# Front Panel Display L3 Test Document for Sink Devices.

## Table of Contents
- [Acronyms, Terms and Abbreviations](#acronyms-terms-and-abbreviations)
- [Description](#description)
- [Component Runtime Execution Requirements](#component-runtime-execution-requirements)
  - [Initialization and Startup]

## Overview
This document provides an overview of the L3 testing requirements for the module `Front Panel Display`. It outlines the scope of testing, objectives, External devices, specific test requirements,  expected deliverables, and approaches to satisfy the L3 Test requirement.  

## Acronyms, Terms and Abbreviations
- `FP`      - Front Panel
- `FPD`     - Front Panel Display
- `ds`      - Device Settings.
- `LED`     - Light Emitting Devices
- `dsFPD`   - Device Settings Front Panel Display
- `HAL`    -  Hardware Abstraction layer
- `API`    -  Application Program Interface
- `SoC`    -  System on Chip
- `DUT`    -  Device Under Test


## References
- Light detector :
- `HAL` interface file: https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/include/dsFPD.h


## Module Description
`Front Panel Display` provides a set of APIs to control the `FP`discrete `LED`s existing on a platform.
- It facilitates the communication to `FP` `LED`s, aiding in their configuration and utilization within the system. The `LED`s is controlled by the caller based on the platform requirements.
Interface specification is available here: [ds-fdp HAl Spec](https://github.com/rdkcentral/rdk-halif-device_settings/blob/main/docs/pages/ds-front-panel-display_halSpec.md)

### Front Panel Display L3 Test Functionality

```mermaid
graph TB
C[PC] <--> A
A[Pulse-Eight CEC Adaptor ] <--> |HDMI| B[TV]  
```

## Test Functionalities

#### LED State Test
Note: All the below tests should be carried out on all `LED` indicators.

#### LED Brightness Test
Note: All the below tests should be carried out on all `LED` indicators.
  
#### LED Color Test
Note: All the below tests should be carried out on all `LED` indicators.

# Test 1: Message Transmission and Reception Test - Unicast messages

Functionality: 

| Title                         | Details                                          |
|-------------------------------|--------------------------------------------------|
| Function Name                 | `test_l3_hdmi_cec_sink_tx_rx_test`              |
| Description                   | This test shall validate the Tx, and Rx CEC Commands between the `DUT`and CEC Adaptor connected on a network |
| Test Group                    | 03                                               |
| Test Case ID                  | 002                                              |
| Priority                      | High                                             |

**Pre-Conditions:**

**Dependencies:**

**User Interaction:**

**RAFT Requirements:**
- RAFT shall initiate the test by reading and validating the LA and PA.
- RAFT shall initiate the commands to send the CEC OSD command with the string data as read from the hdmicec_sinktest.yml file.
- RAFT shall provide a means to enter the LA for the test and any other data required during the test.
- RAFT shall consider reading and give input to the test wherever required. 
  
**Sequence Diagram**
```mermaid
sequenceDiagram
    participant DUT
    participant CEC Adaptor
    participant RAFT/user
    RAFT/user->>CEC Adaptor: Read and validate LA and PA 
    RAFT/user->>DUT: Start the HAL test
    DUT->>DUT: Set receive Callback
    CEC Adaptor->>DUT: Send "GetCECVersion" before adding the logical address
    RAFT/user->>RAFT/user: No response or ack should be received.
    DUT->>DUT: Wait for the RAFT/user to signal to provide ack received or not.
    RAFT/user->>DUT: RAFT/user to signal the test to move ahead
    DUT->>DUT: Check no RxCallback has been received and decide whether the test passes or fails
    DUT->>DUT: Add Logical Address
    DUT->>DUT: Wait for User/RAFT to enter the logical address
    RAFT/user->>DUT: RAFT/user to provide the logical address 
    DUT->>CEC Adaptor: Send "GetCECVersion"
    CEC Adaptor->>DUT: Send the "CEC Version"
    DUT->>DUT: Validate CEC Version
    DUT->>DUT: Wait for User/RAFT to signal the start of the next test
    RAFT/user->>DUT: RAFT/user to signal the test to move ahead
    RAFT/user->>CEC Adaptor: Command to send CEC OSD Command
    CEC Adaptor->>DUT: Send CEC OSD Command
    DUT->>DUT: Validate the received command
    RAFT/user->>RAFT/user: Read the CEC acknowledgment received and validate
    DUT->>DUT: Wait for User/RAFT to enter the acknowledgment confirmation and decide Test Pass/Fail
    RAFT/user->>DUT: RAFT/user to provide the test result
    CEC Adaptor->>DUT: Send "GetCECVersion" to an LA other than `DUT`(0x01 to 0x0E). Repeat these 4 steps for all the addresses sent.
    DUT->>DUT: Wait for User/RAFT to signal when the CEC adaptor has sent a CEC message.
    RAFT/user->>DUT: RAFT/user to signal the test to move ahead
    DUT->>DUT: Test fails if it has received any message.
    RAFT/user->>RAFT/user: No CEC acknowledgment is received after CEC Frames are sent.   
```

#### Test Procedure 

| Variation / Steps | Description | Test Data | Expected Result | Notes |
|-------------------|-------------|-----------|------------------|-------|

# Test 2: Transmit and Receive CEC broadcast Commands 

Functionality: 
| Title                         | Details                                          |
|-------------------------------|--------------------------------------------------|
| Function Name                 | `test_l3_hdmi_cec_sink_broadcast_test`              |
| Description                   | This test shall validate the broadcast CEC Commands between the `DUT`, and the CEC Adaptor connected on a network |
| Test Group                    | 03                                               |
| Test Case ID                  | 003                                              |
| Priority                      | High                                             |

**Pre-Conditions:**

**Dependencies:**

**User Interaction:**

**RAFT Requirements:**
- RAFT shall initiate the commands to send the standby command.
- RAFT shall consider reading and give input to the test wherever required. 
    
**Sequence Diagram**
```mermaid
sequenceDiagram
    participant DUT
    participant CEC Adaptor
    participant RAFT/user
    RAFT/user->>CEC Adaptor: Read and validate LA and PA (device ready) 
    RAFT/user->>DUT: Start the HAL test
    DUT->>DUT: Add Logical Address
    DUT->>DUT: Set receive Callback
    DUT->>CEC Adaptor: Broadcast "standby"
    RAFT/user->>CEC Adaptor: Validate the CEC Command received on the `CEC` adaptor
    DUT->>DUT: Wait for the input from RAFT/user to provide the test result
    RAFT/user->>DUT: Provide the Test result of standby data received by it.
    DUT->>DUT: Wait for the input from RAFT/user to send a broadcast command
    RAFT/user->>DUT: RAFT/user to signal the test to move ahead
    RAFT->>CEC Adaptor: Broadcast "standby" command
    RAFT/user->>DUT: Signal the command to validate the data RAFT/user broadcasted and received by DUT.
    CEC Adaptor->> DUT: Broadcast the standby command
    DUT-->>DUT: Validate the received command
```

#### Test Procedure 

| Variation / Steps | Description | Test Data | Expected Result | Notes |
|-------------------|-------------|-----------|------------------|-------|
# Test 3: Stress Test

Functionality: 
| Title                         | Details                                          |
|-------------------------------|--------------------------------------------------|
| Function Name                 | `test_l3_hdmi_cec_tx_rx_osd_cmd_repeatedly`              |
| Description                   | Transmit and Receive CEC OSD Command with buffer data continuously 10 times to prove the robustness of these API.                       |
| Test Group                    | 03                                               |
| Test Case ID                  | 004                                              |
| Priority                      | High                                             |

**Pre-Conditions:**
**Dependencies:**

**User Interaction:**
**RAFT Requirements:**
- RAFT shall initiate the commands to send the OSD command and validate the acknowledgments
- RAFT shall consider reading and give input to the test wherever required. 
  
**Sequence Diagram**
```mermaid
sequenceDiagram
    participant DUT
    participant CEC Adaptor
    participant RAFT
    RAFT/user->>CEC Adaptor: Read and validate LA and PA 
    RAFT/user->>DUT: Start the HAL test
    DUT->>DUT: Add Logical Address
    DUT->>DUT: Set receive Callback
    RAFT/user->>CEC Adaptor: Command to send CEC OSD Command for 10 times
    CEC Adaptor->>DUT: Send CEC OSD Command for 10 times
    RAFT/user->>DUT: To signal the Test to start receiving the OSD data.
    RAFT/user->>RAFT/user: To validate the acknowledgment received each time when sent the CEC Frame.
    DUT-->>DUT: Validate the received command for 10 times
    RAFT/user->>DUT: DUT to wait till the RAFT/user provides the data ack result
    RAFT/user->>DUT: RAFT/user to signal the test to move ahead with the ack result
    DUT->>CEC Adaptor: Send CEC OSD Command for 10 times
    RAFT/user->>RAFT/user: To validate the OSD Command received on the CEC Adaptor
    RAFT/user->>DUT: DUT to wait till the RAFT/user provides the data ack result
    RAFT/user->>DUT: RAFT/user to signal the test with result
    DUT->>DUT: To decide the final result based on the RAFT/user result and its own result.
```


