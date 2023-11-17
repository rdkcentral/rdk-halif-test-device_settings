/**
*  If not stated otherwise in this file or this component's LICENSE
*  file the following copyright and licenses apply:
*
*  Copyright 2022 RDK Management
*
*  Licensed under the Apache License, Version 2.0 (the License);
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*  http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an AS IS BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*/

/**
 * @addtogroup HPK Hardware Porting Kit
 * @{
 * @par The Hardware Porting Kit
 * HPK is the next evolution of the well-defined Hardware Abstraction Layer
 * (HAL), but augmented with more comprehensive documentation and test suites
 * that OEM or SOC vendors can use to self-certify their ports before taking
 * them to RDKM for validation or to an operator for final integration and
 * deployment. The Hardware Porting Kit effectively enables an OEM and/or SOC
 * vendor to self-certify their own Video Accelerator devices, with minimal RDKM
 * assistance.
 *
 */

/**
 * @addtogroup Device_Settings Device Settings Module
 * @{
 */

/**
 * @addtogroup Device_Settings_HALTEST Device Settings HALTEST
 * @par Application API Specification
 * Described herein are the DeviceSettings HAL types and functions that are part of
 * the Video Port subsystem. The Video Port subsystem manages system-specific HAL operations.
 *  @{
 */

/**
 * @defgroup dsVideoPort_HALTEST Device Settings Video Port HALTEST
 *  @{
 * @par Application API Specification
 * dsVideoPort HAL provides an interface for managing the video port settings for the device settings module.
 */

/**
 * @defgroup DSHAL_VIDEO_HALTEST_L1 Device Settings HAL Video Port L1 test cases
 *  @{
 */

/**
* @file test_l1_dsVideoPort.c
* @page Device Settings
* @subpage dsVideoPort
*
* ## Module's Role
* This module includes Level 1 functional tests (success and failure scenarios)
* This is to ensure that the API meets the operational requirements of the module across all vendors
*
* **Pre-Conditions:**  None
* **Dependencies:** None
*
* Ref to API Definition specification documentation : [ds-video-port_halSpec.md](../../../docs/ds-video-port_halSpec.md)
*/

#include <string.h>
#include <stdlib.h>
#include "dsVideoPort.h"
#include "dsVideoPortSettings.h"

#include <ut.h>
#include <ut_log.h>

/**
 * @brief Ensure dsVideoPortInit() returns correct status codes during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 001@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize the video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |03|Call dsVideoPortInit() - Reinitialize the video port system | | dsERR_NONE | Make sure that the video ports can be reinitialized after termination |
 * |04|Call dsVideoPortTerm() - Re-terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsVideoPortInit(void) {
    dsError_t status;

    // Step 01: Initialize the video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Reinitialize the video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 04: Re-terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}

/**
 * @brief Ensure dsVideoPortInit() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 002@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize the video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsVideoPortInit() - Attempt to initialize again without terminating the first initialization | | dsERR_ALREADY_INITIALIZED | Initialization must fail as it is already initialized |
 * |03|Call dsVideoPortTerm()  - Terminate video port system | | dsERR_NONE | Termination must be successful |
 * 
 * 
 * @note Testing for the `dsERR_RESOURCE_NOT_AVAILABLE` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsVideoPortInit(void) {
    dsError_t status;

    // Step 01: Initialize the video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Attempt to initialize again without terminating the first initialization
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_ALREADY_INITIALIZED);

    // Step 03: Terminate video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Ensure dsVideoPortTerm() returns correct status codes during positive scenarios
 * 
 * **Test Group ID:** Basic: 02@n
 * **Test Case ID:** 001@n
 * 
 * **Pre-Conditions:**None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsVideoPortTerm() - Terminate video port system | | dsERR_NONE | Termination must be successful |
 * |03|Call dsVideoPortInit() - Reinitialize video port system | | dsERR_NONE | Initialization must be successful |
 * |04|Call dsVideoPortTerm() - Re-terminate video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsVideoPortTerm(void) {
    dsError_t status;

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Terminate video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Reinitialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 04: Re-terminate video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Ensure dsVideoPortTerm() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 02@n
 * **Test Case ID:** 002@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortTerm() - Attempt to terminate the video port without prior initialization | | dsERR_NOT_INITIALIZED | Termination must fail as video port is not initialized |
 * |02|Call dsVideoPortInit() - Initialize the video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |04|Call dsVideoPortTerm() - Attempt to terminate the video port again after termination | | dsERR_NOT_INITIALIZED | Termination must fail as video port is not initialized |
 * 
 * 
 * @note Testing for the `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsVideoPortTerm(void) {
    dsError_t status;

    // Step 01: Attempt to terminate the video port without prior initialization
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize the video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 04: Attempt to terminate the video port again after termination
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Ensure dsGetVideoPort() returns correct handles for the available video ports
 * 
 * **Test Group ID:** Basic: 01@p
 * **Test Case ID:** 001@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Get the video port handle for last element , store it in a new variable and compare it with previous step | | dsERR_NONE | Port handle obtained from previous step must be equal to handle obtained in this step
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsGetVideoPort(void) {
    dsError_t status;
    int num_of_ports = 0;
    num_of_ports = (sizeof(kPorts) / sizeof(kPorts[0]);

    intptr_t handle[num_of_ports];
    intptr_t lastHandle;
    intptr_t new_handle;

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
 
    // Step 02: Get the video port handle for valid video port type and index
    for (int i = 0; i < num_of_ports; i++) {
        status = dsGetVideoPort(kPorts[i].id.type, kPorts[i].id.index, &(handle[i]));
        UT_ASSERT_EQUAL(status, dsERR_NONE);
        if(i == num_of_ports-1)
        {
            lastHandle = handle[i];
        }
    }
 
    // Step 03: Compare with the last handle
    status = dsGetVideoPort(kPorts[num_of_ports-1].id.type, kPorts[num_of_ports-1].id.index, &(handle[num_of_ports-1]));
    new_handle = handle[num_of_ports-1];
 
    if(lastHandle == new_handle){
    UT_ASSERT_EQUAL(status, dsERR_NONE);
 
    // Step 04: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}

/**
 * @brief Ensure dsGetVideoPort() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 02@n
 * **Test Case ID:** 002@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetVideoPort() - Attempt to get the Video Port handle without initializing video ports | `type`,`index`= kPorts[0], `handle`= valid handle | dsERR_NOT_INITIALIZED | Get Video Port Handle must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetVideoPort() - by looping through valid port indexes but with invalid type  | type = [not in kPorts] , index = [ loop through kPorts ], handle = [ valid handle ] | dsERR_OPERATION_NOT_SUPPORTED | Operation not supported error must be returned |
 * |04|Call dsGetVideoPort() - by looping through valid types but with invalid index | type = [loop through types in kPorts], index = [ invalid index which is not in kPorts ], handle: [ valid handle ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |05|Call dsGetVideoPort() - by looping through valid types and index but with a NULL handle | type, index: [ loop through kPorts ], handle: [ NULL pointer ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetVideoPort() - Attempt to get the video port handle again after termination | type, index:  [ loop through kPorts ], handle: [ valid handle ] | dsERR_NOT_INITIALIZED | Get Video Port Handle must fail as module is not initialized |
 * 
 * 
 * @note Testing for `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsGetVideoPort(void) {
    dsError_t status;
    int num_of_ports = 0;
    num_of_ports = (sizeof(kPorts) / sizeof(kPorts[0]);

    intptr_t handle[num_of_ports];

    
    // Step 01: Attempt to get the Video Port handle without initializing
    status = dsGetVideoPort(kPorts[0].id.type, kPorts[0].id.index, &(handle[0]));
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Attempt to get the Video Port handle with invalid port type
    for (int i = 0; i < num_of_ports; i++) {
        status = dsGetVideoPort(dsVIDEOPORT_TYPE_MAX, kPorts[i].id.index, &(handle[i]));
        UT_ASSERT_EQUAL(status, dsERR_OPERATION_NOT_SUPPORTED);
    }

    // Step 04: Attempt to get the Video Port handle invalid port index
    for (int i = 0; i < num_of_ports ; i++) {
        status = dsGetVideoPort(kPorts[i].id.type, -1 , &(handle[i]));
        UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);
    }

    // Step 05: NULL handle
    for (int i = 0; i < num_of_ports; i++) {
        status = dsGetVideoPort(handle[i], NULL);
        UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);
    }

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 07: Attempt to get the video port handle again after termination
    status = dsGetVideoPort(kPorts[0].id.type, kPorts[0].id.index, &(handle[0]));
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Ensure dsIsVideoPortEnabled() correctly indicates the enabled status of a video port
 * 
 * **Test Group ID:** Basic: 03@p
 * **Test Case ID:** 003@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |03|Call dsIsVideoPortEnabled - by looping through the acquired port handles to check if a video port is enabled or not and store the values in an array | handle: [valid handle], enabled: [pointer to hold the enabled/disabled status of video port] | dsERR_NONE | Flag which holds the enabled status of Video Port must be returned |
 * |04|Call dsIsVideoPortEnabled - Again by looping through the acquired port handles to check if a video port is enabled or not and store the values in a new array | handle: [valid handle], enabled: [pointer to hold the enabled/disabled status of video port] | dsERR_NONE | Flag which holds the enabled status of Video Port must be returned |
 * |05|Compare the array values and make sure they are equal| | dsERR_NONE | The values must be equal |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsIsVideoPortEnabled(void) {
    dsError_t status;
    int num_of_ports = 0;
    num_of_ports = (sizeof(kPorts) / sizeof(kPorts[0]);

    intptr_t handle[num_of_ports];

    bool isEnabledArray1[num_of_ports];
    bool isEnabledArray2[num_of_ports];

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the port handle for all supported video ports
    for (int i = 0; i < num_of_ports; i++) {
        status = dsGetVideoPort(kPorts[i].id.type, kPorts[i].id.index, &(handle[i]));
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Check if video port is enabled or not
        status = dsIsVideoPortEnabled(handle[i], &isEnabledArray1[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 04: Repeat the check for enabled status
    for (int i = 0; i < num_of_ports; i++) {
        status = dsIsVideoPortEnabled(handle[i], &isEnabledArray2[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 05: Compare the array values
    for (int i = 0; i < num_of_ports; i++) {
        UT_ASSERT_EQUAL(isEnabledArray1[i], isEnabledArray2[i]);
    }

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Ensure dsIsVideoPortEnabled() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 03@n
 * **Test Case ID:** 003@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsIsVideoPortEnabled() - Attempt to check if video port is enabled or not without initializing video ports | handle: [ invalid handle ], connected: [ pointer to hold enabled status]| dsERR_NOT_INITIALIZED | Call to check if video port is enabled or not must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsIsVideoPortEnabled() using an invalid handle but with a valid pointer to hold the enabled status | handle: [ invalid handle ], enabled: [ pointer to hold enabled status] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |05|Call dsIsVideoPortEnabled() by looping through acquired port handles but with a null pointer for enabled status | handle: [ loop through valid handles ], enabled: [ NULL ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsIsVideoPortEnabled() - Attempt to check if video port is enabled or not without initializing video ports| handle: [ valid handle ], connected: [ pointer to hold enabled status] | dsERR_NOT_INITIALIZED | Call to check if video port is enabled or not must fail as module is not initialized |
 * 
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsIsVideoPortEnabled(void) {
    dsError_t status;
    int num_of_ports = 0;
    num_of_ports = (sizeof(kPorts) / sizeof(kPorts[0]);

    intptr_t handle[num_of_ports];

    bool enabled[num_of_ports];

    // Step 01: Attempt to check enabled status without initialization
    status = dsIsVideoPortEnabled(-1, &(enabled[0]));
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Invalid handle check
    status = dsIsVideoPortEnabled(-1, &(enabled[0]));
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get valid video port handle
    for (int i = 0; i < num_of_ports; i++) {
        status = dsGetVideoPort(kPorts[i].id.type, kPorts[i].id.index, &(handle[i]));
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 05: Check enabled status with null pointer
    for (int i = 0; i < num_of_ports; i++) {
        status = dsIsVideoPortEnabled(handle[i], NULL);
        UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);
    }

    // Step 06: Terminate the video port system
    
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 07: Check enabled status after termination
    status = dsIsVideoPortEnabled(handle[0], &enabled);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}

/**
 * @brief Ensure dsIsDisplayConnected() behaves as expected during positive scenarios
 * 
 * **Test Group ID:** Basic: 04@n
 * **Test Case ID:** 004@n
 * 
 * **Pre-Conditions:**@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsIsDisplayConnected() - by looping through the acquired port handles to check if video port is connected to a display or not and store it in an array| handle: [ loop through valid handles ] , connected: [pointer to hold the connection status of Video Port] | dsERR_NONE | Flag which holds the connection status of Video Port must be returned |
 * |04|Call dsIsDisplayConnected() - Again by looping through the acquired port handles to check if video port is connected to a display or not and store it in a new array | handle: [ loop through valid handles ] , connected: [pointer to hold the connection status of Video Port] | dsERR_NONE | Flag which holds the connection status of Video Port must be returned |
 * |05|Compare the array values and make sure they are equal| | dsERR_NONE | The values must be equal |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsIsDisplayConnected(void) {
    dsError_t status;
    int num_of_ports = 0;
    num_of_ports = (sizeof(kPorts) / sizeof(kPorts[0]);

    intptr_t handle[num_of_ports];

    bool isConnectedArray1[num_of_ports];
    bool isConnectedArray2[num_of_ports];

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the video port handle
    for (int i = 0; i < num_of_ports ; i++) {
        status = dsGetVideoPort(kPorts[i].id.type, kPorts[i].id.index, &(handle[i]));
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Check if video port is connected
        status = dsIsDisplayConnected(handle[i], &isConnectedArray1[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 04: Repeat the check for connection status
    for (int i = 0; i < num_of_ports; i++) {
        status = dsIsDisplayConnected(handle[i], &isConnectedArray2[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 05: Compare the array values
    for (int i = 0; i < num_of_ports ; i++) {
        UT_ASSERT_EQUAL(isConnectedArray1[i], isConnectedArray2[i]);
    }

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Ensure dsIsDisplayConnected() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 05@n
 * **Test Case ID:** 005@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsIsDisplayConnected() - Attempt to check if video port is connected without initializing video ports | handle: [ invalid handle ], connected: [ pointer to hold connection status] | dsERR_NOT_INITIALIZED | Call to check if display is connected to video port must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsIsDisplayConnected() using an invalid handle but with a valid pointer to hold the connection status | handle: [ invalid handle ], connected: [ pointer to hold connection status] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |05|Call dsIsDisplayConnected() by looping through acquired port handles but with a null pointer for display connection | handle: [ loop through valid handles ], connected: [ NULL ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsIsDisplayConnected() - Attempt to check if video port is connected without initializing video ports|  handle: [ valid handle ], connected: [ pointer to hold connection status] | dsERR_NOT_INITIALIZED | Call to check if display is connected to video port must fail as module is not initialized |
 * 
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsIsDisplayConnected(void) {
    dsError_t status;
    int num_of_ports = 0;
    num_of_ports = (sizeof(kPorts) / sizeof(kPorts[0]);

    intptr_t handle[num_of_ports];

    bool connected[num_of_ports];
    
    // Step 01: Attempt to check connection status without initialization
    status = dsIsDisplayConnected(-1 , &(connected[0]));
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Invalid handle check
    status = dsIsDisplayConnected(-1, &(connected[0]));
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get valid video port handle
    for (int i = 0; i < num_of_ports; i++) {
        status = dsGetVideoPort(kPorts[i].id.type, kPorts[i].id.index, &(handle[i]));
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 05: Check connection status with null pointer
    for (int i = 0; i < num_of_ports; i++) {
        status = dsIsDisplayConnected(handle[i], NULL);
        UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);
    }

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 07: Check connection status after termination
    status = dsIsDisplayConnected(handle[0], &(connected[0]));
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Positive Test Scenarios for dsIsDisplaySurround()
 * 
 * **Test Group ID:** Basic: 02@p
 * **Test Case ID:** 002@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsIsDisplaySurround() - by looping through the acquired port handles to check if display connected to video port supports the audio surround and store it an array | handle: [ loop through valid handles ] , surround: [pointer to hold the audio surround support] | dsERR_NONE | Audio surround support of Video Port must be returned |
 * |04|Call dsIsDisplaySurround() - Again by looping through the acquired port handles to check if display connected to video port supports the audio surround and store it in a new array| handle: [ loop through valid handles ] , surround: [pointer to hold the audio surround support] | dsERR_NONE | Audio surround support of Video Port must be returned |
 * |05|Compare the array values and make sure they are equal | | dsERR_NONE | The values must be equal |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsIsDisplaySurround(void) {
    dsError_t status;
    int num_of_ports = 0;
    num_of_ports = (sizeof(kPorts) / sizeof(kPorts[0]);

    intptr_t handle[num_of_ports];

    bool isSurroundArray1[num_of_ports];
    bool isSurroundArray2[num_of_ports];
    
    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the video port handle
    for (int i = 0; i < num_of_ports; i++) {
        status = dsGetVideoPort(kPorts[i].id.type, kPorts[i].id.index, &(handle[i]));
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Check if the connected display supports audio surround
        status = dsIsDisplaySurround(handle[i], &isSurroundArray1[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 04: Repeat the check for audio surround support
    for (int i = 0; i < num_of_ports; i++) {
        status = dsIsDisplaySurround(handle[i], &isSurroundArray2[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 05: Compare the array values
    for (int i = 0; i < num_of_ports; i++) {
        UT_ASSERT_EQUAL(isSurroundArray1[i], isSurroundArray2[i]);
    }

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Ensure dsIsDisplaySurround() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 07@n
 * **Test Case ID:** 007@n
 * 
 * **Pre-Conditions:**@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsIsDisplaySurround() - Attempt to check if display connected to video port has surround support without initializing video ports | handle: [ invalid handle ], , surround: [ pointer to hold Audio surround support] | dsERR_NOT_INITIALIZED | Call to check if display connected to video port has surround support must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsIsDisplaySurround() using an invalid handle but with a valid pointer to hold the surround support | handle: [ invalid handle ], surround: [ pointer to hold Audio surround support] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |05|Call dsIsDisplaySurround() by looping through acquired port handles but with a null pointer for audio surround | handle: [ loop through valid handles ], surround: [ NULL ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsIsDisplayConnected() - Attempt to check if display connected to video port has surround support without initializing video ports | handle: [ valid handle ], , surround: [ pointer to hold Audio surround support] | dsERR_NOT_INITIALIZED | Call to check if display connected to video port has surround support must fail as module is not initialized |
 * 
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsIsDisplaySurround(void) {
    dsError_t status;
    int num_of_ports = 0;
    num_of_ports = (sizeof(kPorts) / sizeof(kPorts[0]);

    intptr_t handle[num_of_ports];

    bool surround[num_of_ports];
    

    // Step 01: Attempt to check audio surround support without initialization
    status = dsIsDisplaySurround(-1, &surround[0]);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Invalid handle check
    status = dsIsDisplaySurround(-1, &surround[0]);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get valid video port handle
    for (int i = 0; i < num_of_ports; i++) {
        status = dsGetVideoPort(kPorts[i].id.type, kPorts[i].id.index, &(handle[i]));
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 05: Check audio surround support with null pointer
    for (int i = 0; i < num_of_ports; i++) {
        status = dsIsDisplaySurround(handle[i], NULL);
        UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);
    }

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 07: Check audio surround support after termination
    status = dsIsDisplaySurround(handle[0], &surround[0]);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Positive Test Scenarios for dsGetSurroundMode()
 * 
 * **Test Group ID:** Basic: 03@p
 * **Test Case ID:** 003@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsGetSurroundMode() - by looping through the acquired port handles to get the surround mode of each video port and store it in an array | handle: [ loop through valid handles ] , surround: [pointer to hold the Surround mode] | dsERR_NONE | Surround mode (dsSURROUNDMode_t)of Video Port must be returned |
 * |04|Call dsGetSurroundMode() - Again by looping through the acquired port handles to get the surround mode of each video port and store it in a new array | handle: [ loop through valid handles ] , surround: [pointer to hold the Surround mode] | dsERR_NONE | Surround mode (dsSURROUNDMode_t)of Video Port must be returned |
 * |05|Compare the array values and make sure they are equal | | dsERR_NONE | The values must be equal |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsGetSurroundMode(void) {
    dsError_t status;
    VideoPortHandle handle;
    dsSURROUNDMode_t surroundModeArray1[/* Size matching kPorts array */];
    dsSURROUNDMode_t surroundModeArray2[/* Size matching kPorts array */];
    int kPorts[] = {/* Array of valid port indexes */};
    int portType = /* Valid port type */;

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the video port handle
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetVideoPort(portType, kPorts[i], &handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Get the surround mode of each video port
        status = dsGetSurroundMode(handle, &surroundModeArray1[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 04: Repeat the retrieval of surround mode
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetSurroundMode(handle, &surroundModeArray2[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 05: Compare the array values
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        UT_ASSERT_EQUAL(surroundModeArray1[i], surroundModeArray2[i]);
    }

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Negative Test Scenarios for dsGetSurroundMode()
 * 
 * **Test Group ID:** Basic: 03@n
 * **Test Case ID:** 003@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetSurroundMode() - Attempt to get the surround mode without initializing video ports | handle: [ invalid handle ], surround: [pointer to hold the surround mode] | dsERR_NOT_INITIALIZED | Get surround mode of video ports must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetSurroundMode() using an invalid handle but with a valid pointer to hold the surround mode | handle: [ invalid handle ], surround: [ pointer to hold surround mode] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |05|Call dsGetSurroundMode() by looping through acquired port handles but with a null pointer for surround mode | handle: [ loop through valid handles ], surround: [ NULL ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetSurroundMode() - Attempt to get the surround mode without initializing video ports | handle: [ valid handle ], surround: [pointer to hold the surround mode] | dsERR_NOT_INITIALIZED | Get surround mode of video ports must fail as module is not initialized |
 * 
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsGetSurroundMode(void) {
    dsError_t status;
    VideoPortHandle handle;
    dsSURROUNDMode_t surroundMode;
    int kPorts[] = {/* Array of valid port indexes */};
    int portType = /* Valid port type */;

    // Step 01: Attempt to get surround mode without initialization
    status = dsGetSurroundMode(/* invalid handle */, &surroundMode);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Invalid handle check
    status = dsGetSurroundMode(/* invalid handle */, &surroundMode);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get valid video port handle
    status = dsGetVideoPort(portType, kPorts[0], &handle);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 05: Check surround mode with null pointer
    status = dsGetSurroundMode(handle, NULL);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 07: Attempt to get surround mode after termination
    status = dsGetSurroundMode(handle, &surroundMode);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Positive Test Scenarios for dsIsVideoPortActive()
 * 
 * **Test Group ID:** Basic: 05@p
 * **Test Case ID:** 005@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsIsVideoPortActive() - by looping through the acquired port handles to check whether a video port is active or not for each port and store it in an array| handle: [ loop through valid handles ] , active: [pointer to hold the active status] | dsERR_NONE | Active Status(A Video port is active if it is connected to the active port of sink device) of Video Port must be returned |
 * |04|Call dsIsVideoPortActive() - by looping through the acquired port handles to check whether a video port is active or not for each port and store it in a new array | handle: [ loop through valid handles ] , active: [pointer to hold the active status] | dsERR_NONE | Active Status(A Video port is active if it is connected to the active port of sink device) of Video Port must be returned |
 * |05|Compare the array values and make sure they are equal | | dsERR_NONE | The values must be equal |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsIsVideoPortActive(void) {
    dsError_t status;
    VideoPortHandle handle;
    bool isActiveArray1[/* Size matching kPorts array */];
    bool isActiveArray2[/* Size matching kPorts array */];
    int kPorts[] = {/* Array of valid port indexes */};
    int portType = /* Valid port type */;

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the video port handle
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetVideoPort(portType, kPorts[i], &handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Check whether each video port is active
        status = dsIsVideoPortActive(handle, &isActiveArray1[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 04: Repeat the active status check
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsIsVideoPortActive(handle, &isActiveArray2[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 05: Compare the array values
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        UT_ASSERT_EQUAL(isActiveArray1[i], isActiveArray2[i]);
    }

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Negative Test Scenarios for dsIsVideoPortActive()
 * 
 * **Test Group ID:** Basic: 05@n
 * **Test Case ID:** 005@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsIsVideoPortActive() - Attempt to check whether a video port is active or not without initializing video ports |  handle: [ invalid handle ], active: [pointer to hold the active status of video port] | dsERR_NOT_INITIALIZED | Call to check if video port is active or not must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsIsVideoPortActive() using an invalid handle but with a valid pointer to hold the active status | handle: [ invalid handle ], active: [ pointer to hold active status] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |05|Call dsIsVideoPortActive() by looping through acquired port handles but with a null pointer for active status | handle: [ loop through valid handles ], active: [ NULL ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsIsVideoPortActive() - Attempt to check whether a video port is active or not without initializing video ports | handle: [ valid handle ], active: [pointer to hold the active status of video port] | dsERR_NOT_INITIALIZED | Call to check if video port is active or not must fail as module is not initialized |
 * 
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsIsVideoPortActive(void) {
    dsError_t status;
    VideoPortHandle handle;
    bool active;
    int kPorts[] = {/* Array of valid port indexes */};
    int portType = /* Valid port type */;

    // Step 01: Attempt to check active status without initialization
    status = dsIsVideoPortActive(/* invalid handle */, &active);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Invalid handle check
    status = dsIsVideoPortActive(/* invalid handle */, &active);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get valid video port handle
    status = dsGetVideoPort(portType, kPorts[0], &handle);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 05: Check active status with null pointer
    status = dsIsVideoPortActive(handle, NULL);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 07: Attempt to check active status after termination
    status = dsIsVideoPortActive(handle, &active);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Positive Test Scenarios for dsEnableDTCP()
 * 
 * **Test Group ID:** Basic: 06@p
 * **Test Case ID:** 006@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsEnableDTCP() by looping through the acquired port handles to enable DTCP for ports which support DTCP | handle: [ loop through valid handles ] , contentProtect: [1] (enable DTCP) |dsERR_NONE or dsERR_OPERATION_NOT_SUPPORTED| API must either successfully enable DTCP or indicate that the operation isn't supported if the particular video does not have DTCP support|
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsEnableDTCP(void) {
    dsError_t status;
    VideoPortHandle handle;
    bool isDTCPEnabled;
    int kPorts[] = {/* Array of valid port indexes */};
    int portType = /* Valid port type */;

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the video port handle
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetVideoPort(portType, kPorts[i], &handle);
        UT_ASSERT_TRUE(status == dsERR_NONE);

        // Step 03: Enable DTCP
        status = dsEnableDTCP(handle, true);
        UT_ASSERT_TRUE(status == dsERR_NONE || status == dsERR_OPERATION_NOT_SUPPORTED);
    }

    // Step 04: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Negative Test Scenarios for dsEnableDTCP()
 * 
 * **Test Group ID:** Basic: 06@n
 * **Test Case ID:** 006@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsEnableDTCP() - Attempt to enable DTCP without initializing the video ports | handle: [ invalid handle ], contentProtect: [true = enable DTCP/ false = disable DTCP] | dsERR_NOT_INITIALIZED | Enable DTCP must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsEnableDTCP() using an invalid handle but with a valid DTCP Flag(enable = 1/ disable = 0) | handle: [ invalid handle ], contentProtect: [ Flag to enable/disable DTCP] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |05|Call dsEnableDTCP() Attempt to enable DTCP without initializing the video ports | handle: [ valid handle ], contentProtect: [true = enable DTCP/ false = disable DTCP] | dsERR_NOT_INITIALIZED | Enable DTCP must fail as module is not initialized |
 * 
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsEnableDTCP(void) {
    dsError_t status;
    VideoPortHandle handle = /* Initialize with invalid handle */;
    bool contentProtect = true; // Flag to enable/disable DTCP

    // Step 01: Attempt to enable DTCP without initialization
    status = dsEnableDTCP(handle, contentProtect);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Invalid handle check
    status = dsEnableDTCP(/* invalid handle */, contentProtect);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 05: Attempt to enable DTCP after termination
    status = dsEnableDTCP(handle, contentProtect);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Positive Test Scenarios for dsEnableHDCP()
 * 
 * **Test Group ID:** Basic: 07@p
 * **Test Case ID:** 007@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsEnableHDCP() by looping through the acquired port handles to enable HDCP for ports which support HDCP | handle: [ loop through valid handles ] , contentProtect: [1] (enable HDCP), hdcpKey: [ HDCP key ], keySize: [HDCP key size]|dsERR_NONE or dsERR_OPERATION_NOT_SUPPORTED| API must either successfully enable HDCP or indicate that the operation isn't supported if the particular video does not have HDCP support|
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsEnableHDCP(void) {
    dsError_t status;
    VideoPortHandle handle;
    bool isHDCPEnabled;
    int kPorts[] = {/* Array of valid port indexes */};
    int portType = /* Valid port type */;
    char hdcpKey[HDCP_KEY_MAX_SIZE]; // Assume HDCP_KEY_MAX_SIZE is defined
    int keySize = HDCP_KEY_MAX_SIZE;

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the video port handle
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetVideoPort(portType, kPorts[i], &handle);
        UT_ASSERT_TRUE(status == dsERR_NONE);

        // Step 03: Enable HDCP
        status = dsEnableHDCP(handle, true, hdcpKey, keySize);
        UT_ASSERT_TRUE(status == dsERR_NONE || status == dsERR_OPERATION_NOT_SUPPORTED);

    }

    // Step 04: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Negative Test Scenarios for dsEnableHDCP()
 * 
 * **Test Group ID:** Basic: 07@n
 * **Test Case ID:** 007@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsEnableHDCP() - Attempt to enable HDCP without initializing the video ports | handle: [ invalid handle ], contentProtect: [true = enable/ false = disable], hdcpKey: [valid hdcp key], keySize: [valid key size]| dsERR_NOT_INITIALIZED | Enable HDCP must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsEnableHDCP() - Attempt to enable HDCP with an invalid handle |handle: [ invalid handle ], contentProtect: [true = enable/ false = disable], hdcpKey: [valid hdcp key], keySize: [valid key size (HDCP_KEY_MAX_SIZE)]| dsERR_INVALID_PARAM | Invalid Parameter error must be returned |
 * |04|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |05|Call dsEnableHDCP() by looping through acquired port handles(which support HDCP) with an invalid HDCP key size |handle: [ valid handle ], contentProtect: [true = enable/ false = disable], hdcpKey: [valid hdcp key], keySize: [invalid key size (> HDCP_KEY_MAX_SIZE)| dsERR_INVALID_PARAM | Invalid Parameter error must be returned |
 * |05|Call dsEnableHDCP() by looping through acquired port handles with an NULL hdcpKey pointer |handle: [ valid handle ], contentProtect: [true = enable/ false = disable], hdcpKey: [NULL], keySize: [valid key size] | dsERR_INVALID_PARAM | Invalid Parameter error must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsEnableHDCP() Attempt to enable HDCP without initializing the video ports | handle: [ valid handle ], contentProtect: [true = enable/ false = disable], hdcpKey: [valid hdcp key], keySize: [valid key size] | dsERR_NOT_INITIALIZED | Enable HDCP must fail as module is not initialized |
 * 
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsEnableHDCP(void) {
    dsError_t status;

    // Step 01: Attempt to enable HDCP without initialization
    status = dsEnableHDCP(invalidHandle, true, validHdcpKey, validKeySize);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Attempt to enable HDCP with an invalid handle
    status = dsEnableHDCP(invalidHandle, true, validHdcpKey, HDCP_KEY_MAX_SIZE);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get the video port handle for supported video ports
    for (int i = 0; i < kPortsLength; i++) {
        dsVideoPortHandle_t handle;
        status = dsGetVideoPort(kPorts[i], &handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 05: Enable HDCP with invalid key size
        status = dsEnableHDCP(handle, true, validHdcpKey, invalidKeySize);
        UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

        // Step 06: Enable HDCP with NULL hdcpKey pointer
        status = dsEnableHDCP(handle, true, NULL, validKeySize);
        UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);
    }

    // Step 07: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 08: Attempt to enable HDCP after termination
    status = dsEnableHDCP(validHandle, true, validHdcpKey, validKeySize);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
* @brief Positive Test Scenarios for dsIsDTCPEnabled()
 *
 * **Test Group ID:** Basic: 08@p
 * **Test Case ID:** 008@p
 *
 * **Pre-Conditions:** None@n
 *
 * **Dependencies:** None@n
 *
 * **User Interaction:** None
 *
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video ports of a system | |dsERR_NONE| Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports|
 * |03|Call dsIsDTCPEnabled() by looping through the acquired port handles  and valid pointer to check whether DTCP enabled or not(.ie TRUE / FALSE) and store it in an array | handle : [loop through valid handles] , pContentProtected = [pointer to hold data ]|dsERR_NONE |dsIsDTCPEnabled must return a valid value|
 * |03|Call dsIsDTCPEnabled() by looping through the acquired port handles  and valid pointer to check whether DTCP enabled or not(.ie TRUE / FALSE) and store it in a new array | handle : [loop through valid handles] , pContentProtected = [pointer to hold data ]|dsERR_NONE |dsIsDTCPEnabled must return a valid value|
 * |05|Compare the array values and make sure they are equal | | dsERR_NONE | The values must be equal |
 * |06|Call dsVideoPortTerm() - Terminate the video ports of a system| |dsERR_NONE|Termination must be successful|
 *
 */
void test_l1_dsVideoPort_positive_dsIsDTCPEnabled(void) {
    dsError_t status;
    VideoPortHandle handle;
    bool isDTCPEnabledArray1[/* Size matching kPorts array */];
    bool isDTCPEnabledArray2[/* Size matching kPorts array */];
    int kPorts[] = {/* Array of valid port indexes */};
    int portType = /* Valid port type */;

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the video port handle
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetVideoPort(portType, kPorts[i], &handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Check if DTCP is enabled
        status = dsIsDTCPEnabled(handle, &isDTCPEnabledArray1[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 04: Repeat the check for DTCP status
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsIsDTCPEnabled(handle, &isDTCPEnabledArray2[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 05: Compare the array values
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        UT_ASSERT_EQUAL(isDTCPEnabledArray1[i], isDTCPEnabledArray2[i]);
    }

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Negative Test Scenarios for dsIsDTCPEnabled()
 *
 * **Test Group ID:** Basic: 08@n
 * **Test Case ID:** 008@n
 *
 * **Pre-Conditions:** None@n
 *
 * **Dependencies:** None@n
 * **User Interaction:** None
 *
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsIsDTCPEnabled() - Attempt to get the DTCP status with out initializing video ports| handle [invalid handle] , pContentProtected = [valid pointer]|dsERR_NOT_INITIALIZED| dsIsDTCPEnabled call must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video ports of a system | |dsERR_NONE| Initialization must be successful |
 * |03|Call dsIsDTCPEnabled() - Using an invalid handle but with valid pointer | handle = [invalid handle], pContentProtected = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort()  - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsIsDTCPEnabled() By looping through acquired port handles but with a invalid pointer | handle = [valid handle], pContentProtected = [invalid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video ports of a system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsIsDTCPEnabled() - Again after terminating video ports attempt to get DTCP status | handle= [valid handle] , pContentProtected = [valid pointer] | dsERR_NOT_INITIALIZED | dsIsDTCPEnabled call must fail as module is not initialized |
 *
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsIsDTCPEnabled(void) {
    dsError_t status;
    VideoPortHandle handle = /* Initialize with invalid handle */;
    bool isDTCPEnabled;

    // Step 01: Attempt to get DTCP status without initialization
    status = dsIsDTCPEnabled(handle, &isDTCPEnabled);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Invalid handle check
    status = dsIsDTCPEnabled(/* invalid handle */, &isDTCPEnabled);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get valid video port handle
    status = dsGetVideoPort(portType, kPorts[0], &handle);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 05: Check DTCP status with invalid pointer
    status = dsIsDTCPEnabled(handle, NULL);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 07: Attempt to get DTCP status after termination
    status = dsIsDTCPEnabled(handle, &isDTCPEnabled);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Positive Test Scenarios for dsIsHDCPEnabled()
 * 
 * **Test Group ID:** Basic: 09@p
 * **Test Case ID:** 009@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video ports of a system | |dsERR_NONE| Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports|
 * |03|Call dsIsHDCPEnabled() by looping through the acquired port handles  and checks whether HDCP enabled or not(.ie TRUE / FALSE) and store it in an array | handle : [loop through valid handles] , pContentProtected = [pointer to hold data ] | dsERR_NONE | dsIsHDCPEnabled must return a valid value|
 * |04|Call dsIsHDCPEnabled() by looping through the acquired port handles  and checks whether HDCP enabled or not(.ie TRUE / FALSE) and store it in a new array | handle : [loop through valid handles] , pContentProtected = [pointer to hold data ] | dsERR_NONE | dsIsHDCPEnabled must return a valid value|
 * |05|Compare the array values and make sure they are equal | | dsERR_NONE | The values must be equal |
 * |06|Call dsVideoPortTerm() - Terminate the video ports of a system| |dsERR_NONE|Termination must be successful|
 * 
 */
void test_l1_dsVideoPort_positive_dsIsHDCPEnabled(void) {
    dsError_t status;
    VideoPortHandle handle;
    bool isHDCPEnabledArray1[/* Size matching kPorts array */];
    bool isHDCPEnabledArray2[/* Size matching kPorts array */];
    int kPorts[] = {/* Array of valid port indexes */};
    int portType = /* Valid port type */;

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the video port handle
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetVideoPort(portType, kPorts[i], &handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Check if HDCP is enabled
        status = dsIsHDCPEnabled(handle, &isHDCPEnabledArray1[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 04: Repeat the check for HDCP status
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsIsHDCPEnabled(handle, &isHDCPEnabledArray2[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 05: Compare the array values
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        UT_ASSERT_EQUAL(isHDCPEnabledArray1[i], isHDCPEnabledArray2[i]);
    }

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Negative Test Scenarios for dsIsHDCPEnabled()
 * 
 * **Test Group ID:** Basic: 09@n
 * **Test Case ID:** 009@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsIsHDCPEnabled() - Attempt to get the HDCP status with out initializing video ports| handle [invalid handle] , pContentProtected = [valid pointer]|dsERR_NOT_INITIALIZED| dsIsHDCPEnabled call must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video ports of a system | |dsERR_NONE| Initialization must be successful |
 * |03|Call dsIsHDCPEnabled() - Using an invalid handle but with valid pointer | handle = [invalid handle], pContentProtected = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort()  - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsIsHDCPEnabled() - By looping through acquired port handles but with a invalid pointer | handle = [valid handle], pContentProtected = [invalid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video ports of a system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsIsHDCPEnabled() - Again after terminating video ports attempt to get HDCP status | handle= [valid handle from step 04 ] , pContentProtected = [valid pointer] | dsERR_NOT_INITIALIZED | dsIsHDCPEnabled call must fail as module is not initialized |
 *
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsIsHDCPEnabled(void) {
    dsError_t status;
    bool contentProtected;

    // Step 01: Attempt to get HDCP status without initialization
    status = dsIsHDCPEnabled(invalidHandle, &contentProtected);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Attempt to get HDCP status with an invalid handle
    status = dsIsHDCPEnabled(invalidHandle, &contentProtected);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get the video port handle for supported video ports
    for (int i = 0; i < kPortsLength; i++) {
        dsVideoPortHandle_t handle;
        status = dsGetVideoPort(kPorts[i], &handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 05: Get HDCP status with invalid pointer
        status = dsIsHDCPEnabled(handle, NULL);
        UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);
    }

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 07: Attempt to get HDCP status after termination
    status = dsIsHDCPEnabled(validHandle, &contentProtected);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Positive Test Scenarios for dsEnableVideoPort()
 * 
 * **Test Group ID:** Basic: 10@p
 * **Test Case ID:** 010@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video ports of a system | |dsERR_NONE| Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] | dsERR_NONE | Valid port handle must be returned for all supported video ports|
 * |03|Call dsEnableVideoPort() by looping through the acquired port handles to enable video ports | handle  = [loop through valid handles] , enabled = [TRUE] | dsERR_NONE | Video ports must be enabled |
 * |04|Call dsIsVideoPortEnabled() by looping through the acquired port handles and check if video ports(supported by platform) are enabled | dsERR_NONE | Supported video ports must be enabled |
 * |05|Call dsEnableVideoPort() by looping through the acquired port handles to disable a video ports | handle  = [loop through valid handles] , enabled = [TRUE] | dsERR_NONE | Video ports must be enabled |
 * |06|Call dsIsVideoPortEnabled() by looping through the acquired port handles and check if video ports(supported by platform) are disabled | dsERR_NONE | Supported video ports must be disabled |
 * |07|Call dsVideoPortTerm() - Terminate the video ports of a system| |dsERR_NONE|Termination must be successful|
 * 
 */
void test_l1_dsVideoPort_positive_dsEnableVideoPort(void) {
    dsError_t status;
    VideoPortHandle handle;
    bool isVideoPortEnabled;
    int kPorts[] = {/* Array of valid port indexes */};
    int portType = /* Valid port type */;

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the video port handle
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetVideoPort(portType, kPorts[i], &handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Enable the video port
        status = dsEnableVideoPort(handle, true);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 04: Check if video port is enabled
        status = dsIsVideoPortEnabled(handle, &isVideoPortEnabled);
        UT_ASSERT_TRUE(status == dsERR_NONE && isVideoPortEnabled);

        // Step 05: Disable the video port
        status = dsEnableVideoPort(handle, false);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 06: Check if video port is disabled
        status = dsIsVideoPortEnabled(handle, &isVideoPortEnabled);
        UT_ASSERT_TRUE(status == dsERR_NONE && !isVideoPortEnabled);
    }

    // Step 07: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Negative Test Scenarios for dsEnableVideoPort()
 * 
 * **Test Group ID:** Basic: 10@n
 * **Test Case ID:** 010@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsEnableVideoPort() - Attempt to enable or disable video port  with out initializing video ports| handle [invalid handle] , enabled = [valid bool value]| dsERR_NOT_INITIALIZED| dsEnableVideoPort call must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video ports of a system | |dsERR_NONE| Initialization must be successful |
 * |03|Call dsEnableVideoPort() - Using an invalid handle but with valid enabled value(i.e TRUE/FALSE) | handle = [invalid handle], enabled = [valid bool value] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort()  - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsVideoPortTerm() - Terminate the video ports of a system | | dsERR_NONE | Termination must be successful |
 * |06|Call dsEnableVideoPort() - Again after terminating video ports attempt to enable or disable video port | handle = [valid handle ] , enabled = [valid bool value] | dsERR_NOT_INITIALIZED | dsEnableVideoPort call must fail as module is not initialized |
 * 
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsEnableVideoPort(void) {
    dsError_t status;
    VideoPortHandle handle = /* Initialize with invalid handle */;
    bool enabled = true; // Example value for enabling/disabling the port

    // Step 01: Attempt to enable/disable video port without initialization
    status = dsEnableVideoPort(handle, enabled);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Invalid handle check
    status = dsEnableVideoPort(/* invalid handle */, enabled);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get valid video port handle
    status = dsGetVideoPort(portType, kPorts[0], &handle);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 05: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 06: Attempt to enable/disable video port after termination
    status = dsEnableVideoPort(handle, enabled);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Positive Test Scenarios for dsSetResolution()
 * 
 * **Test Group ID:** Basic: 11@p
 * **Test Case ID:** 011@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video ports of a system | |dsERR_NONE| Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports|
 * |03|Call dsSetResolution() by looping through the acquired port handles and valid resolution pointer to set the video port resolution |handle  = [loop through valid handles] , resolution = [valid pointer]|dsERR_NONE|Resolution must be set successfully|
 * |04|Call dsVideoPortTerm() - Terminate the video ports of a system| |dsERR_NONE|Termination must be successful|
 * 
 */
void test_l1_dsVideoPort_positive_dsSetResolution(void) {
    dsError_t status;
    VideoPortHandle handle;
    dsVideoPortResolution_t resolution; // Assume dsVideoPortResolution_t is defined and has required fields
    int kPorts[] = {/* Array of valid port indexes */};
    int portType = /* Valid port type */;

    // Set a valid resolution configuration in resolution variable here

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the video port handle
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetVideoPort(portType, kPorts[i], &handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Set the resolution for the video port
        status = dsSetResolution(handle, &resolution);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 04: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Negative Test Scenarios for dsSetResolution()
 * 
 * **Test Group ID:** Basic: 11@n
 * **Test Case ID:** 011@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsSetResolution() - Attempt to set the resolution with out initializing video ports| handle = [invalid handle] , resolution = [valid pointer]| dsERR_NOT_INITIALIZED| dsSetResolution call must fail as module is not initialized |
 * |02|dsVideoPortInit() - Initialize video ports of a system | |dsERR_NONE| Initialization must be successful |
 * |03|Call dsSetResolution() - Using an invalid handle but with valid resolution pointer | handle = [invalid handle], resolution = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsSetResolution() - By looping through acquired port handles but with a invalid pointer | handle = [valid handle], resolution = [invalid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video ports of a system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsSetResolution() - Again after terminating video ports attempt to set the resolution | handle= [valid handle from step 04 ] , resolution = [valid pointer] | dsERR_NOT_INITIALIZED | dsSetResolution call must fail as module is not initialized |
 * 
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsSetResolution(void) {
    dsError_t status;
    VideoPortHandle handle = /* Initialize with invalid handle */;
    dsVideoPortResolution_t resolution; // Assume dsVideoPortResolution_t is defined and has required fields

    // Set a valid resolution configuration in resolution variable here

    // Step 01: Attempt to set resolution without initialization
    status = dsSetResolution(handle, &resolution);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Invalid handle check
    status = dsSetResolution(/* invalid handle */, &resolution);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get valid video port handle
    status = dsGetVideoPort(portType, kPorts[0], &handle);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 05: Set resolution with invalid pointer
    status = dsSetResolution(handle, NULL);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 07: Attempt to set resolution after termination
    status = dsSetResolution(handle, &resolution);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Positive Test Scenarios for dsGetResolution()
 * 
 * **Test Group ID:** Basic: 12@p
 * **Test Case ID:** 012@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video ports of a system | |dsERR_NONE| Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports|
 * |03|Call dsGetResolution() by looping through the acquired port handles and valid resolution pointer to retrieve the resolution of a video port and store it in an array | handle  = [loop through valid handles] , resolution = [valid pointer] |dsERR_NONE|Resolution must be retrieved successfully|
 * |04|Call dsGetResolution() Again by looping through the acquired port handles and valid resolution pointer to retrieve the resolution of a video port and store it in a new array | handle  = [loop through valid handles] , resolution = [valid pointer] |dsERR_NONE|Resolution must be retrieved successfully|
 * |05|Compare the array values and make sure they are equal | | dsERR_NONE | The values must be equal |
 * |06|Call dsVideoPortTerm() - Terminate the video ports of a system| |dsERR_NONE|Termination must be successful|
 * 
 */
void test_l1_dsVideoPort_positive_dsGetResolution(void) {
    dsError_t status;
    VideoPortHandle handle;
    dsVideoPortResolution_t resolutionArray1[/* Size matching kPorts array */];
    dsVideoPortResolution_t resolutionArray2[/* Size matching kPorts array */];
    int kPorts[] = {/* Array of valid port indexes */};
    int portType = /* Valid port type */;

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the video port handle
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetVideoPort(portType, kPorts[i], &handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Retrieve the resolution of the video port
        status = dsGetResolution(handle, &resolutionArray1[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 04: Repeat the retrieval of resolution
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetResolution(handle, &resolutionArray2[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 05: Compare the array values
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        // Assuming a function or operator to compare dsVideoPortResolution_t structures
        UT_ASSERT_TRUE(compareResolutions(resolutionArray1[i], resolutionArray2[i]));
    }

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Negative Test Scenarios for dsGetResolution()
 * 
 * **Test Group ID:** Basic: 12@n
 * **Test Case ID:** 012@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetResolution() - Attempt to get the resolution without initializing video ports| handle = [invalid handle] , resolution = [valid pointer]| dsERR_NOT_INITIALIZED| Get Resolution call must fail as module is not initialized |
 * |02|dsVideoPortInit() - Initialize video ports of a system | |dsERR_NONE| Initialization must be successful |
 * |03|Call dsGetResolution() - Using an invalid handle but with valid resolution pointer | handle = [invalid handle], resolution = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |04|Call dsGetResolution() - By looping through acquired port handles but with a invalid pointer | handle = [valid handle], resolution = [invalid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |05|Call dsVideoPortTerm() - Terminate the video ports of a system | | dsERR_NONE | Termination must be successful |
 * |06|Call dsGetResolution() - Again after terminating video ports attempt to get the resolution of video ports | handle = [valid handle] , resolution = [valid pointer] | dsERR_NOT_INITIALIZED | Get Resolution call must fail as module is not initialized |
 * 
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsGetResolution(void) {
    dsError_t status;
    VideoPortHandle handle = /* Initialize with invalid handle */;
    dsVideoPortResolution_t resolution;

    // Step 01: Attempt to get resolution without initialization
    status = dsGetResolution(handle, &resolution);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Invalid handle check
    status = dsGetResolution(/* invalid handle */, &resolution);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get valid video port handle
    status = dsGetVideoPort(portType, kPorts[0], &handle);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 05: Get resolution with invalid pointer
    status = dsGetResolution(handle, NULL);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 07: Attempt to get resolution after termination
    status = dsGetResolution(handle, &resolution);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Positive Test Scenarios for dsSetActiveSource()
 * 
 * **Test Group ID:** Basic: 13@p
 * **Test Case ID:** 013@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video ports of a system | |dsERR_NONE| Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports|
 * |03|Call dsSetActiveSource() by looping through the acquired port handles and set the video port as active source | handle  = [loop through valid handles] |dsERR_NONE|The video port must be set as the active source successfully|
 * |04|dsVideoPortTerm() - Terminate the video ports of a system| |dsERR_NONE|Termination must be successful|
 * 
 */
void test_l1_dsVideoPort_positive_dsSetActiveSource(void) {
    dsError_t status;
    VideoPortHandle handle;
    int kPorts[] = {/* Array of valid port indexes */};
    int portType = /* Valid port type */;

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the video port handle
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetVideoPort(portType, kPorts[i], &handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Set the video port as the active source
        status = dsSetActiveSource(handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 04: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Negative Test Scenarios for dsSetActiveSource()
 * 
 * **Test Group ID:** Basic: 13@n
 * **Test Case ID:** 013@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsSetActiveSource() - Attempt to set the active source with out initializing video ports| handle =  [invalid handle] | dsERR_NOT_INITIALIZED| dsSetActiveSource call must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video ports of a system | |dsERR_NONE| Initialization must be successful |
 * |03|Call dsSetActiveSource() - Using an invalid handle attempt to set active source | handle = [invalid handle] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort()  - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsVideoPortTerm() - Terminate the video ports of a system | | dsERR_NONE | Termination must be successful |
 * |06|Call dsSetActiveSource()  - Again after terminating video ports attempt to set the active source | handle= [valid handle ] | dsERR_NOT_INITIALIZED | dsSetActiveSource call must fail as module is not initialized |
 * 
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsSetActiveSource(void) {
    dsError_t status;
    VideoPortHandle handle = /* Initialize with invalid handle */;

    // Step 01: Attempt to set active source without initialization
    status = dsSetActiveSource(handle);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Invalid handle check
    status = dsSetActiveSource(/* invalid handle */);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get valid video port handle
    status = dsGetVideoPort(portType, kPorts[0], &handle);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 05: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 06: Attempt to set active source after termination
    status = dsSetActiveSource(handle);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Positive Test Scenarios for dsVideoFormatUpdateRegisterCB()
 * 
 * **Test Group ID:** Basic: 04@p
 * **Test Case ID:** 004@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsVideoFormatUpdateRegisterCB() - Register a valid Video Format update callback | cb = [valid callback function] | dsERR_NONE | Video Format Update callback registration must be successful |
 * |03|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsVideoFormatUpdateRegisterCB(void) {
    dsError_t status;

    // Assume dsVideoFormatUpdateCB_t is defined and a valid callback function is implemented
    dsVideoFormatUpdateCB_t validCallback = validVideoFormatUpdateCallback;

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Register a valid Video Format update callback
    status = dsVideoFormatUpdateRegisterCB(validCallback);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Negative Test Scenarios for dsVideoFormatUpdateRegisterCB()
 * 
 * **Test Group ID:** Basic: 04@n
 * **Test Case ID:** 004@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoFormatUpdateRegisterCB() - Attempt to register for video format update callback without initializing the video ports | cb = [valid callback function ] | dsERR_NOT_INITIALIZED | Callback registration must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsVideoFormatUpdateRegisterCB() with an invalid callback (NULL)| cb = NULL | dsERR_INVALID_PARAM | Invalid paramter error must be returned |
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |05|Call dsVideoFormatUpdateRegisterCB() - Attempt to register for video format update callback without initializing the video ports | cb = [valid callback function ] | dsERR_NOT_INITIALIZED | Callback registration must fail as module is not initialized |
 * 
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsVideoFormatUpdateRegisterCB(void) {
    dsError_t status;

    // Assume dsVideoFormatUpdateCB_t is defined
    dsVideoFormatUpdateCB_t validCallback = validVideoFormatUpdateCallback;

    // Step 01: Attempt to register callback without initialization
    status = dsVideoFormatUpdateRegisterCB(validCallback);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Register with invalid callback (NULL)
    status = dsVideoFormatUpdateRegisterCB(NULL);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 05: Attempt to register callback after termination
    status = dsVideoFormatUpdateRegisterCB(validCallback);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Positive Test Scenarios for dsRegisterHdcpStatusCallback()
 * 
 * **Test Group ID:** Basic: 14@p
 * **Test Case ID:** 014@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsRegisterHdcpStatusCallback() - Register a valid HDCP status change callback |handle = [valid handle], cb = [Callback function] | dsERR_NONE | Callback must be registered successfully |
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsRegisterHdcpStatusCallback(void) {
    dsError_t status;
    VideoPortHandle handle;
    int kPorts[] = {/* Array of valid port indexes */};
    int portType = /* Valid port type */;

    // Assume dsHdcpStatusCallback_t is defined and a valid callback function is implemented
    dsHdcpStatusCallback_t validHdcpStatusCallback = myHdcpStatusCallbackFunction;

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the video port handle and register HDCP status callback
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetVideoPort(portType, kPorts[i], &handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Register HDCP status change callback
        status = dsRegisterHdcpStatusCallback(handle, validHdcpStatusCallback);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 04: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Negative Test Scenarios for dsRegisterHdcpStatusCallback()
 * 
 * **Test Group ID:** Basic: 14@n
 * **Test Case ID:** 014@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsRegisterHdcpStatusCallback() - Attempt to register HDCP status change callback without initializing the video ports | handle= [invalid handle], cb = [valid callback function] | dsERR_NOT_INITIALIZED | Callback Registration for HDCP status change must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsRegisterHdcpStatusCallback() with an invalid handle but with a valid callback function as parameter | handle= [invalid handle], cb = [valid callback function] | dsERR_INVALID_PARAM | Invalid Parameter error must be returned |
 * |04|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |05|Call dsRegisterHdcpStatusCallback() with a valid handle and a NULL callback function | handle= [valid handle], cb = NULL | dsERR_INVALID_PARAM | Invalid Parameter error must be returned |
 * |05|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |06|Call dsRegisterHdcpStatusCallback() - Attempt to register HDCP status change callback without initializing the video ports | handle= [valid handle], cb = [valid callback function] | dsERR_NOT_INITIALIZED | Callback Registration for HDCP status change must fail as module is not initialized |
 * 
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsRegisterHdcpStatusCallback(void) {
    dsError_t status;
    VideoPortHandle handle = /* Initialize with invalid handle */;

    // Assume dsHdcpStatusCallback_t is defined
    dsHdcpStatusCallback_t validHdcpStatusCallback = myHdcpStatusCallbackFunction;

    // Step 01: Attempt to register HDCP status callback without initialization
    status = dsRegisterHdcpStatusCallback(handle, validHdcpStatusCallback);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Invalid handle check
    status = dsRegisterHdcpStatusCallback(/* invalid handle */, validHdcpStatusCallback);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get valid video port handle
    status = dsGetVideoPort(portType, kPorts[0], &handle);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 05: Register HDCP status callback with NULL callback function
    status = dsRegisterHdcpStatusCallback(handle, NULL);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 07: Attempt to register HDCP status callback after termination
    status = dsRegisterHdcpStatusCallback(handle, validHdcpStatusCallback);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Positive Test Scenarios for dsGetHDCPStatus()
 * 
 * **Test Group ID:** Basic: 15@p
 * **Test Case ID:** 015@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsGetHDCPStatus() by looping through the acquired port handles and valid pointer to retrieve HDCP status and store it in an array | handle  = [valid handles] status = [valid pointer] | dsERR_NONE | The HDCP status must be successfully fetched and stored in the given pointer|
 * |04|Call dsGetHDCPStatus() - Again by looping through the acquired port handles and valid pointer to retrieve HDCP status and  store it in a new array | handle  = [valid handles] status = [valid pointer] | dsERR_NONE | The HDCP status must be successfully fetched and stored in the given pointer|
 * |05|Compare the array values and make sure they are equal | | dsERR_NONE | The values must be equal |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsGetHDCPStatus(void) {
    dsError_t status;
    VideoPortHandle handle;
    dsHDCPStatus_t hdcpStatusArray1[/* Size matching kPorts array */];
    dsHDCPStatus_t hdcpStatusArray2[/* Size matching kPorts array */];
    int kPorts[] = {/* Array of valid port indexes */};
    int portType = /* Valid port type */;

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the video port handle
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetVideoPort(portType, kPorts[i], &handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Retrieve the HDCP status
        status = dsGetHDCPStatus(handle, &hdcpStatusArray1[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 04: Repeat the retrieval of HDCP status
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetHDCPStatus(handle, &hdcpStatusArray2[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 05: Compare the array values
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        UT_ASSERT_EQUAL(hdcpStatusArray1[i], hdcpStatusArray2[i]);
    }

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Negative Test Scenarios for dsGetHDCPStatus()
 * 
 * **Test Group ID:** Basc: 15@n
 * **Test Case ID:** 015@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetHDCPStatus() Attempt to get the HDCP status  with out initializing video ports| handle = [invalid handle] , status = [valid pointer]| dsERR_NOT_INITIALIZED| dsGetHDCPStatus call must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetHDCPStatus() Using an invalid handle but with valid status pointer | handle = [invalid handle], status = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports|
 * |04|Call dsGetHDCPStatus() By looping through acquired port handles but with a invalid pointer | handle = [valid handle], status = [invalid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |05|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |06|Call dsGetHDCPStatus() Again after terminating video ports attempt to get the status of video ports | handle= [valid handle ] , status = [valid pointer] | dsERR_NOT_INITIALIZED | dsGetHDCPStatus call must fail as module is not initialized |
 * 
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsGetHDCPStatus(void) {
    dsError_t status;
    VideoPortHandle handle = /* Initialize with invalid handle */;
    dsHDCPStatus_t hdcpStatus;

    // Step 01: Attempt to get HDCP status without initialization
    status = dsGetHDCPStatus(handle, &hdcpStatus);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Invalid handle check
    status = dsGetHDCPStatus(/* invalid handle */, &hdcpStatus);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get valid video port handle
    status = dsGetVideoPort(portType, kPorts[0], &handle);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 05: Get HDCP status with invalid pointer
    status = dsGetHDCPStatus(handle, NULL);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 07: Attempt to get HDCP status after termination
    status = dsGetHDCPStatus(handle, &hdcpStatus);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}



/**
 * @brief Positive Test Scenarios for dsGetHDCPProtocol()
 * 
 * **Test Group ID:** Basic: 16@p
 * **Test Case ID:** 016@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsGetHDCPProtocol() by looping through the acquired suported port handles and valid pointer to retrieve the protocol version  of a video port and store it in an array |handle  = [valid handles] , protocolVersion = [valid pointer] |dsERR_NONE|The HDCP protocol version must be successfully fetched |
 * |04|Call dsGetHDCPProtocol() -Again by looping through the acquired suported port handles and valid pointer to retrieve the protocol version  of a video port and store it in a new array |handle  = [valid handles] , protocolVersion = [valid pointer] |dsERR_NONE|The HDCP protocol version must be successfully fetched |
 * |05|Compare the array values and make sure they are equal | | dsERR_NONE | The values must be equal |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsGetHDCPProtocol(void) {
    dsError_t status;
    VideoPortHandle handle;
    HDCPProtocol_t protocolVersionArray1[/* Size matching kPorts array */];
    HDCPProtocol_t protocolVersionArray2[/* Size matching kPorts array */];
    int kPorts[] = {/* Array of valid port indexes */};
    int portType = /* Valid port type */;

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the video port handle
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetVideoPort(portType, kPorts[i], &handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Retrieve the HDCP protocol version
        status = dsGetHDCPProtocol(handle, &protocolVersionArray1[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 04: Repeat the retrieval of HDCP protocol version
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetHDCPProtocol(handle, &protocolVersionArray2[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 05: Compare the array values
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        UT_ASSERT_EQUAL(protocolVersionArray1[i], protocolVersionArray2[i]);
    }

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}

/**
 * @brief Negative Test Scenarios for dsGetHDCPProtocol()
 * 
 * **Test Group ID:** Basic: 16@n
 * **Test Case ID:** 016@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetHDCPProtocol()  Attempt to get the HDCP protocol version with out initializing video ports| handle = [invalid handle] , protocolVersion = [valid pointer]| dsERR_NOT_INITIALIZED| dsGetHDCPProtocol call must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetHDCPProtocol() Using an invalid handle but with valid pointer | handle = [invalid handle], protocolVersion = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports|
 * |05|Call dsGetHDCPProtocol() By looping through acquired supported port handles but with a invalid pointer | handle = [valid handle], protocolVersion = [invalid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetHDCPProtocol() Again after terminating video ports attempt to get the HDCP protocol version of video ports | handle= [ valid handle ] , protocolVersion = [valid pointer] | dsERR_NOT_INITIALIZED | dsGetHDCPProtocol call must fail as module is not initialized |
 * 
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsGetHDCPProtocol(void) {
    dsError_t status;
    VideoPortHandle handle = /* Initialize with invalid handle */;
    HDCPProtocol_t protocolVersion; // Assume HDCPProtocol_t is defined

    // Step 01: Attempt to get HDCP protocol without initialization
    status = dsGetHDCPProtocol(handle, &protocolVersion);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Invalid handle check
    status = dsGetHDCPProtocol(/* invalid handle */, &protocolVersion);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get valid video port handle
    status = dsGetVideoPort(/* valid port type */, /* valid port index */, &handle);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 05: Get HDCP protocol with invalid pointer
    status = dsGetHDCPProtocol(handle, NULL);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 07: Attempt to get HDCP protocol after termination
    status = dsGetHDCPProtocol(handle, &protocolVersion);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Positive Test Scenarios for dsGetHDCPReceiverProtocol()
 * 
 * **Test Group ID:** Basic: 17@p
 * **Test Case ID:** 017@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 *
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsGetHDCPReceiverProtocol() by looping through the acquired supported port handles and valid pointer to retrieve the sink device protocol version of a video port and store it in an array |handle  = [loop through valid handles] , protocolVersion = [valid pointer] |dsERR_NONE|The Receiver HDCP protocol version must be successfully fetched and stored in the given pointer|
 * |04|Call dsGetHDCPReceiverProtocol() - Again by looping through the acquired supported port handles and valid pointer to retrieve the sink device protocol version of a video port and store it in a new array |handle  = [loop through valid handles] , protocolVersion = [valid pointer] |dsERR_NONE|The Receiver HDCP protocol version must be successfully fetched and stored in the given pointer|
 * |05|Compare the array values and make sure they are equal | | dsERR_NONE | The values must be equal |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsGetHDCPReceiverProtocol(void) {
    dsError_t status;
    VideoPortHandle handle;
    HDCPProtocol_t protocolVersionArray1[/* Size matching kPorts array */];
    HDCPProtocol_t protocolVersionArray2[/* Size matching kPorts array */];
    int kPorts[] = {/* Array of valid port indexes */};
    int portType = /* Valid port type */;

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the video port handle
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetVideoPort(portType, kPorts[i], &handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Retrieve the Receiver HDCP protocol version
        status = dsGetHDCPReceiverProtocol(handle, &protocolVersionArray1[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 04: Repeat the retrieval of Receiver HDCP protocol version
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetHDCPReceiverProtocol(handle, &protocolVersionArray2[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 05: Compare the array values
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        UT_ASSERT_EQUAL(protocolVersionArray1[i], protocolVersionArray2[i]);
    }

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Negative Test Scenarios for dsGetHDCPReceiverProtocol()
 * 
 * **Test Group ID:** Basic: 17@n
 * **Test Case ID:** 017@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 *
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetHDCPReceiverProtocol()  Attempt to get the sink device HDCP protocol version of sink device with out initializing video ports| handle = [invalid handle] , protocolVersion = [valid pointer]| dsERR_NOT_INITIALIZED| dsGetHDCPReceiverProtocol call must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetHDCPReceiverProtocol() Using an invalid handle but with valid pointer | handle = [invalid handle], protocolVersion = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports|
 * |05|Call dsGetHDCPReceiverProtocol() By looping through acquired supported port handles but with a invalid pointer | handle = [valid handle], protocolVersion = [invalid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetHDCPReceiverProtocol() Again after terminating video ports attempt to get the sink device HDCP protocol version of video ports | handle= [valid handle ] , protocolVersion = [valid pointer] | dsERR_NOT_INITIALIZED | dsGetHDCPReceiverProtocol call must fail as module is not initialized |
 * 
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsGetHDCPReceiverProtocol(void) {
    dsError_t status;
    VideoPortHandle handle = /* Initialize with invalid handle */;
    HDCPProtocol_t receiverProtocolVersion; // Assume HDCPProtocol_t is defined

    // Step 01: Attempt to get Receiver HDCP protocol without initialization
    status = dsGetHDCPReceiverProtocol(handle, &receiverProtocolVersion);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Invalid handle check
    status = dsGetHDCPReceiverProtocol(/* invalid handle */, &receiverProtocolVersion);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get valid video port handle
    status = dsGetVideoPort(/* valid port type */, /* valid port index */, &handle);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 05: Get Receiver HDCP protocol with invalid pointer
    status = dsGetHDCPReceiverProtocol(handle, NULL);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 07: Attempt to get Receiver HDCP protocol after termination
    status = dsGetHDCPReceiverProtocol(handle, &receiverProtocolVersion);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Positive Test Scenarios for dsGetHDCPCurrentProtocol()
 * 
 * **Test Group ID:** Basic: 18@p
 * **Test Case ID:** 018@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 *
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsGetHDCPCurrentProtocol() by looping through the acquired supported port handles and valid pointer to retrieve the current negotiated protocol version  of a video port and store it in an array |handle  = [valid handles] , protocolVersion = [valid pointer] |dsERR_NONE|The current HDCP protocol version must be successfully fetched |
 * |04|Call dsGetHDCPCurrentProtocol() -Again by looping through the acquired supported port handles and valid pointer to retrieve the current negotiated protocol version of a video port and store it in a new array |handle  = [valid handles] , protocolVersion = [valid pointer] |dsERR_NONE|The current HDCP protocol version must be successfully fetched |
 * |05|Compare the array values and make sure they are equal | | dsERR_NONE | The values must be equal |
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsGetHDCPCurrentProtocol(void) {
    dsError_t status;
    VideoPortHandle handle;
    HDCPProtocol_t currentProtocolArray1[/* Size matching kPorts array */];
    HDCPProtocol_t currentProtocolArray2[/* Size matching kPorts array */];
    int kPorts[] = {/* Array of valid port indexes */};
    int portType = /* Valid port type */;

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the video port handle
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetVideoPort(portType, kPorts[i], &handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Retrieve the current negotiated HDCP protocol version
        status = dsGetHDCPCurrentProtocol(handle, &currentProtocolArray1[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 04: Repeat the retrieval of current HDCP protocol version
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetHDCPCurrentProtocol(handle, &currentProtocolArray2[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 05: Compare the array values
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        UT_ASSERT_EQUAL(currentProtocolArray1[i], currentProtocolArray2[i]);
    }

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Negative Test Scenarios for dsGetHDCPCurrentProtocol()
 * 
 * **Test Group ID:** Basic: 18@n
 * **Test Case ID:** 018@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 *
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetHDCPCurrentProtocol()  Attempt to get the current negotiated HDCP protocol version with out initializing video ports| handle = [invalid handle] , protocolVersion = [valid pointer]| dsERR_NOT_INITIALIZED| dsGetHDCPCurrentProtocol call must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetHDCPCurrentProtocol() Using an invalid handle but with valid pointer | handle = [invalid handle], protocolVersion = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports|
 * |05|Call dsGetHDCPCurrentProtocol() By looping through acquired supported port handles but with a invalid pointer | handle = [valid handle], protocolVersion = [invalid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetHDCPCurrentProtocol() Again after terminating video ports attempt to get the current negotiated  HDCP protocol version of video ports | handle= [valid handle ] , protocolVersion = [valid pointer] | dsERR_NOT_INITIALIZED | dsGetHDCPCurrentProtocol call must fail as module is not initialized |
 *
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsGetHDCPCurrentProtocol(void) {
    dsError_t status;
    VideoPortHandle handle = /* Initialize with invalid handle */;
    HDCPProtocol_t currentProtocolVersion; // Assume HDCPProtocol_t is defined

    // Step 01: Attempt to get current negotiated HDCP protocol without initialization
    status = dsGetHDCPCurrentProtocol(handle, &currentProtocolVersion);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Invalid handle check
    status = dsGetHDCPCurrentProtocol(/* invalid handle */, &currentProtocolVersion);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get valid video port handle
    status = dsGetVideoPort(/* valid port type */, /* valid port index */, &handle);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 05: Get current HDCP protocol with invalid pointer
    status = dsGetHDCPCurrentProtocol(handle, NULL);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 07: Attempt to get current negotiated HDCP protocol after termination
    status = dsGetHDCPCurrentProtocol(handle, &currentProtocolVersion);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Positive Test Scenarios for dsGetTVHDRCapabilities()
 * 
 * **Test Group ID:** Basic: 20@p
 * **Test Case ID:** 020@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video ports of a system | |dsERR_NONE| Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports|
 * |03|Call dsGetTVHDRCapabilities() by looping through the acquired port handles and valid pointer to retrieve the HDR capabilities of a video port and store it in an array | handle  = [loop through valid handles] , capabilities = [valid pointer] |dsERR_NONE|The HDR capabilities must be successfully fetched and stored in the given pointer|
 * |04|Call dsGetTVHDRCapabilities() -Again by looping through the acquired port handles and valid pointer to retrieve the HDR capabilities of a video port and store it in a new array | handle  = [loop through valid handles] , capabilities = [valid pointer] |dsERR_NONE|The HDR capabilities must be successfully fetched and stored in the given pointer|
 * |05|Compare the array values and make sure they are equal | | dsERR_NONE | The values must be equal |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsGetTVHDRCapabilities(void) {
    dsError_t status;
    VideoPortHandle handle;
    TVHDRCapabilities_t capabilitiesArray1[/* Size matching kPorts array */];
    TVHDRCapabilities_t capabilitiesArray2[/* Size matching kPorts array */];
    int kPorts[] = {/* Array of valid port indexes */};
    int portType = /* Valid port type */;

    // Assume TVHDRCapabilities_t is defined and represents the HDR capabilities

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the video port handle
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetVideoPort(portType, kPorts[i], &handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Retrieve the HDR capabilities
        status = dsGetTVHDRCapabilities(handle, &capabilitiesArray1[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 04: Repeat the retrieval of HDR capabilities
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetTVHDRCapabilities(handle, &capabilitiesArray2[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 05: Compare the array values
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        // Assuming a function or method to compare TVHDRCapabilities_t
        UT_ASSERT_TRUE(compareHDRCapabilities(capabilitiesArray1[i], capabilitiesArray2[i]));
    }

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Negative Test Scenarios for dsGetTVHDRCapabilities()
 * 
 * **Test Group ID:** Basic: 20@n
 * **Test Case ID:** 020@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetTVHDRCapabilities() Attempt to get the HDR capabilites  with out initializing video ports| handle = [invalid handle] , capabilities = [valid pointer]| dsERR_NOT_INITIALIZED| dsGetTVHDRCapabilities call must fail as module is not initialized |
 * |02|dsVideoPortInit() - Initialize video ports of a system | |dsERR_NONE| Initialization must be successful |
 * |03|Call dsGetTVHDRCapabilities() Using an invalid handle but with valid pointer | handle = [invalid handle], capabilities = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports|
 * |04|Call dsGetTVHDRCapabilities() By looping through acquired port handles but with a invalid pointer | handle = [valid handle], capabilities = [invalid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |05|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |06|Call dsGetTVHDRCapabilities() Again after terminating video ports attempt to get the HDR capabilites of video ports | handle= [valid handle ] , capabilities = [valid pointer] | dsERR_NOT_INITIALIZED | dsGetTVHDRCapabilities call must fail as module is not initialized |
 * 
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsGetTVHDRCapabilities(void) {
    dsError_t status;
    VideoPortHandle handle = /* Initialize with invalid handle */;
    TVHDRCapabilities_t capabilities; // Assume TVHDRCapabilities_t is defined

    // Step 01: Attempt to get HDR capabilities without initialization
    status = dsGetTVHDRCapabilities(handle, &capabilities);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Invalid handle check
    status = dsGetTVHDRCapabilities(/* invalid handle */, &capabilities);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get valid video port handle
    status = dsGetVideoPort(/* valid port type */, /* valid port index */, &handle);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 05: Get HDR capabilities with invalid pointer
    status = dsGetTVHDRCapabilities(handle, NULL);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 07: Attempt to get HDR capabilities after termination
    status = dsGetTVHDRCapabilities(handle, &capabilities);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Positive Test Scenarios for dsSupportedTvResolutions()
 * 
 * **Test Group ID:** Basic: 30@p
 * **Test Case ID:** 030@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 *
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video ports of a system | |dsERR_NONE| Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports|
 * |03|Call dsSupportedTvResolutions() by looping through the acquired port handles and valid pointer to retrieve the resolutions of a video port and store it in an array |handle  = [loop through valid handles] , resolutions = [valid pointer] |dsERR_NONE|Resolutions must be set successfully|
 * |04|Call dsSupportedTvResolutions() -Again by looping through the acquired port handles and valid pointer to retrieve the resolutions of a video port and store it in a new array |handle  = [loop through valid handles] , resolutions = [valid pointer] |dsERR_NONE|Resolutions must be set successfully|
 * |05|Compare the array values and make sure they are equal | | dsERR_NONE | The values must be equal |
 * |06|Call dsVideoPortTerm() - Terminate the video ports of a system| |dsERR_NONE|Termination must be successful|
 * 
 */
void test_l1_dsVideoPort_positive_dsSupportedTvResolutions(void) {
    dsError_t status;
    VideoPortHandle handle;
    TvResolutions_t resolutionsArray1[/* Size matching kPorts array */];
    TvResolutions_t resolutionsArray2[/* Size matching kPorts array */];
    int kPorts[] = {/* Array of valid port indexes */};
    int portType = /* Valid port type */;

    // Assume TvResolutions_t is defined and represents the TV resolutions

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the video port handle
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetVideoPort(portType, kPorts[i], &handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Retrieve the supported TV resolutions
        status = dsSupportedTvResolutions(handle, &resolutionsArray1[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 04: Repeat the retrieval of supported TV resolutions
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsSupportedTvResolutions(handle, &resolutionsArray2[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 05: Compare the array values
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        // Assuming a function or method to compare TvResolutions_t
        UT_ASSERT_TRUE(compareTvResolutions(resolutionsArray1[i], resolutionsArray2[i]));
    }

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Negative Test Scenarios for dsSupportedTvResolutions()
 * 
 * **Test Group ID:** Basic: 30@n
 * **Test Case ID:** 030@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 *
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsSupportedTvResolutions() - Attempt to get the supported resolutions with out initializing video ports| handle =  [invalid handle] , resolutions = [valid pointer]| dsERR_NOT_INITIALIZED| dsSupportedTvResolutions call must fail as module is not initialized |
 * |02|dsVideoPortInit() - Initialize video ports of a system | |dsERR_NONE| Initialization must be successful |
 * |03|Call dsSupportedTvResolutions() - Using an invalid handle but with valid resolutions pointer | handle = [invalid handle], resolutions = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort() Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |04|Call dsSupportedTvResolutions() - By looping through acquired port handles but with a invalid pointer | handle = [valid handle], resolutions = [invalid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |05|Call dsVideoPortTerm() - Terminate the video ports of a system | | dsERR_NONE | Termination must be successful |
 * |06|Call dsSupportedTvResolutions() - Again after terminating video ports attempt to get the supported resolutions of video ports | handle= [valid handle ] , resolutions = [valid pointer] | dsERR_NOT_INITIALIZED | dsSupportedTvResolutions call must fail as module is not initialized |
 * 
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsSupportedTvResolutions(void) {
    dsError_t status;
    VideoPortHandle handle = /* Initialize with invalid handle */;
    TvResolutions_t resolutions; // Assume TvResolutions_t is defined

    // Step 01: Attempt to get supported resolutions without initialization
    status = dsSupportedTvResolutions(handle, &resolutions);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Invalid handle check
    status = dsSupportedTvResolutions(/* invalid handle */, &resolutions);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get valid video port handle
    status = dsGetVideoPort(/* valid port type */, /* valid port index */, &handle);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 05: Get supported resolutions with invalid pointer
    status = dsSupportedTvResolutions(handle, NULL);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 07: Attempt to get supported resolutions after termination
    status = dsSupportedTvResolutions(handle, &resolutions);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Positive Test Scenarios for dsSetForceDisable4KSupport()
 * 
 * **Test Group ID:** Basic: 40@p
 * **Test Case ID:** 040@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsSetForceDisable4KSupport() by looping through the acquired port handles and valid value to Set the 4K support to be forcefully disabled or not | handle  = [loop through valid handles] , disable= [valid value] | dsERR_NONE | The 4K support must be successfully disabled or not |
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsSetForceDisable4KSupport(void) {
    dsError_t status;
    VideoPortHandle handle;
    int kPorts[] = {/* Array of valid port indexes */};
    int portType = /* Valid port type */;
    bool disable4K = /* Valid value to disable or not disable 4K support */;

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the video port handle
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetVideoPort(portType, kPorts[i], &handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Set force disable 4K support
        status = dsSetForceDisable4KSupport(handle, disable4K);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 04: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Negative Test Scenarios for dsSetForceDisable4KSupport()
 * 
 * **Test Group ID:** Basic: 40@n
 * **Test Case ID:** 040@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsSetForceDisable4KSupport() Attempt to disable or not to disable 4K support with out initializing video ports| handle = [invalid handle] , disable = [valid value]| dsERR_NOT_INITIALIZED| dsSetForceDisable4KSupport call must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetForceDisable4KSupport() Using an invalid handle but with valid disable parameter value | handle = [invalid handle], disable = [valid value] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort() Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |06|Call dsSetForceDisable4KSupport() Again after terminating video ports attempt to disable or not to disable 4k support of video ports | handle= [valid handle ] , disable = [valid value] | dsERR_NOT_INITIALIZED | dsSetForceDisable4KSupport call must fail as module is not initialized |
 * 
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsSetForceDisable4KSupport(void) {
    dsError_t status;
    VideoPortHandle handle = /* Initialize with invalid handle */;
    bool disable4K = /* Valid value to disable or not disable 4K support */;

    // Step 01: Attempt to set force disable 4K support without initialization
    status = dsSetForceDisable4KSupport(handle, disable4K);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Invalid handle check
    status = dsSetForceDisable4KSupport(/* invalid handle */, disable4K);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get valid video port handle
    status = dsGetVideoPort(/* valid port type */, /* valid port index */, &handle);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 05: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 06: Attempt to set force disable 4K support after termination
    status = dsSetForceDisable4KSupport(handle, disable4K);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Positive Test Scenarios for dsGetForceDisable4KSupport()
 * 
 * **Test Group ID:** Basic: 50@p
 * **Test Case ID:** 050@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 *
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call  dsGetForceDisable4KSupport() by looping through the acquired port handles and valid pointer to get the 4K support disabled or not and store it in an array | handle  = [loop through valid handles] , disable= [valid pointer] | dsERR_NONE | The 4K support disabled or not must be successfully retrieved |
 * |04|Call  dsGetForceDisable4KSupport() -Again by looping through the acquired port handles and valid pointer to get the 4K support disabled or not and store it in a new array | handle  = [loop through valid handles] , disable= [valid pointer] | dsERR_NONE | The 4K support disabled or not must be successfully retrieved |
 * |05|Compare the array values and make sure they are equal | | dsERR_NONE | The values must be equal |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful | 
 * 
 */
void test_l1_dsVideoPort_positive_dsGetForceDisable4KSupport(void) {
    dsError_t status;
    VideoPortHandle handle;
    int kPorts[] = {/* Array of valid port indexes */};
    int portType = /* Valid port type */;
    bool disable4KArray1[/* Size matching kPorts array */];
    bool disable4KArray2[/* Size matching kPorts array */];

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the video port handle
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetVideoPort(portType, kPorts[i], &handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Retrieve whether 4K support is disabled
        status = dsGetForceDisable4KSupport(handle, &disable4KArray1[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 04: Repeat the retrieval
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetForceDisable4KSupport(handle, &disable4KArray2[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 05: Compare the array values
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        UT_ASSERT_EQUAL(disable4KArray1[i], disable4KArray2[i]);
    }

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Negative Test Scenarios for dsGetForceDisable4KSupport()
 * 
 * **Test Group ID:** Basic: 50@n
 * **Test Case ID:** 050@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 *
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetForceDisable4KSupport() Attempt to get 4k support disable or not with out initializing video ports| handle = [invalid handle] , disable = [valid pointer]| dsERR_NOT_INITIALIZED| dsGetForceDisable4KSupport call must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetForceDisable4KSupport() Using an invalid handle but with valid pointer | handle = [invalid handle], disable = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort() Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsGetForceDisable4KSupport() By looping through acquired port handles but with a invalid pointer | handle = [valid handle], disable = [invalid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetForceDisable4KSupport() Again after terminating video ports attempt to get whether 4K support of video ports disabled or not | handle= [valid handle ] , disable = [valid pointer] | dsERR_NOT_INITIALIZED | dsGetForceDisable4KSupport call must fail as module is not initialized | 
 * 
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsGetForceDisable4KSupport(void) {
    dsError_t status;
    VideoPortHandle handle = /* Initialize with invalid handle */;
    bool disable4K; // To store the result

    // Step 01: Attempt to get 4K support status without initialization
    status = dsGetForceDisable4KSupport(handle, &disable4K);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Invalid handle check
    status = dsGetForceDisable4KSupport(/* invalid handle */, &disable4K);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get valid video port handle
    status = dsGetVideoPort(/* valid port type */, /* valid port index */, &handle);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 05: Get 4K support status with invalid pointer
    status = dsGetForceDisable4KSupport(handle, NULL);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 07: Attempt to get 4K support status after termination
    status = dsGetForceDisable4KSupport(handle, &disable4K);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Positive Test Scenarios for dsGetVideoEOTF()
 * 
 * **Test Group ID:** Basic: 60@p
 * **Test Case ID:** 060@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsGetVideoEOTF() by looping through the acquired port handles and valid pointer to retrieve the current Electro-Optical Transfer Function (EOTF) value and store it in an array | handle = [loop through ports] , video_eotf = [valid pointer] |dsERR_NONE | Valid EOTF value must return a valid EOTF value of the specified video port|
 * |04|Call dsGetVideoEOTF() -Again by looping through the acquired port handles and valid pointer to retrieve the current Electro-Optical Transfer Function (EOTF) value and store it in a new array | handle = [loop through ports] , video_eotf = [valid pointer] |dsERR_NONE | Valid EOTF value must return a valid EOTF value of the specified video port|
 * |05|Compare the array values and make sure they are equal | | dsERR_NONE | The values must be equal |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsGetVideoEOTF(void) {
    dsError_t status;
    VideoPortHandle handle;
    VideoEOTF_t eotfArray1[/* Size matching kPorts array */];
    VideoEOTF_t eotfArray2[/* Size matching kPorts array */];
    int kPorts[] = {/* Array of valid port indexes */};
    int portType = /* Valid port type */;

    // Assume VideoEOTF_t is defined and represents the EOTF value

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the video port handle
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetVideoPort(portType, kPorts[i], &handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Retrieve the EOTF value
        status = dsGetVideoEOTF(handle, &eotfArray1[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 04: Repeat the retrieval of EOTF value
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetVideoEOTF(handle, &eotfArray2[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 05: Compare the array values
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        UT_ASSERT_EQUAL(eotfArray1[i], eotfArray2[i]);
    }

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Negative Test Scenarios for dsGetVideoEOTF()
 * 
 * **Test Group ID:** Basic: 60@n
 * **Test Case ID:** 060@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetVideoEOTF() Attempt to get the EOTF  with out initializing video ports| handle = [invalid handle] , video_eotf = [valid pointer] | dsERR_NOT_INITIALIZED| dsGetVideoEOTF call must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetVideoEOTF() Using an invalid handle but with valid pointer | handle = [invalid handle], video_eotf = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort() Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsGetVideoEOTF() By looping through acquired port handles but with a invalid pointer | handle = [valid handle], video_eotf = [invalid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetVideoEOTF() Again after terminating video ports attempt to get the EOTF of video ports | handle= [invalid handle ] , video_eotf = [valid pointer] | dsERR_NOT_INITIALIZED | dsGetVideoEOTF call must fail as module is not initialized |
 * 
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsGetVideoEOTF(void) {
    dsError_t status;
    VideoPortHandle handle = /* Initialize with invalid handle */;
    VideoEOTF_t eotf; // To store the EOTF value

    // Step 01: Attempt to get EOTF without initialization
    status = dsGetVideoEOTF(handle, &eotf);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Invalid handle check
    status = dsGetVideoEOTF(/* invalid handle */, &eotf);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get valid video port handle
    status = dsGetVideoPort(/* valid port type */, /* valid port index */, &handle);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 05: Get EOTF value with invalid pointer
    status = dsGetVideoEOTF(handle, NULL);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 07: Attempt to get EOTF after termination
    status = dsGetVideoEOTF(handle, &eotf);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Positive Test Scenarios for dsGetMatrixCoefficients()
 * 
 * **Test Group ID:** Basic: 70@p
 * **Test Case ID:** 070@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsGetMatrixCoefficients() by looping through the acquired port handles and valid resolution pointer to retrieve the current matrix coefficients of a specified port  and store it in an array |handle  = [loop through valid handles] , matrix_coefficients = [valid pointer] |dsERR_NONE|must return a valid matrix coefficient value of the specified video port|
 * |04|Call dsGetMatrixCoefficients() -Again by looping through the acquired port handles and valid resolution pointer to retrieve the current matrix coefficients of a specified port and store it in a new array |handle  = [loop through valid handles] , matrix_coefficients = [valid pointer] |dsERR_NONE|must return a valid matrix coefficient value of the specified video port|
 * |05|Compare the array values and make sure they are equal | | dsERR_NONE | The values must be equal |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsGetMatrixCoefficients(void) {
    dsError_t status;
    VideoPortHandle handle;
    MatrixCoefficients_t matrixCoefficientsArray1[/* Size matching kPorts array */];
    MatrixCoefficients_t matrixCoefficientsArray2[/* Size matching kPorts array */];
    int kPorts[] = {/* Array of valid port indexes */};
    int portType = /* Valid port type */;

    // Assume MatrixCoefficients_t is defined and represents matrix coefficients

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the video port handle
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetVideoPort(portType, kPorts[i], &handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Retrieve the matrix coefficients
        status = dsGetMatrixCoefficients(handle, &matrixCoefficientsArray1[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 04: Repeat the retrieval of matrix coefficients
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetMatrixCoefficients(handle, &matrixCoefficientsArray2[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 05: Compare the array values
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        UT_ASSERT_EQUAL(matrixCoefficientsArray1[i], matrixCoefficientsArray2[i]);
    }

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Negative Test Scenarios for dsGetMatrixCoefficients()
 * 
 * **Test Group ID:** Basic: 70@n
 * **Test Case ID:** 070@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetMatrixCoefficients() Attempt to get the matrix coefficients with out initializing video ports| handle = [invalid handle] , matrix_coefficients = [valid pointer]| dsERR_NOT_INITIALIZED| dsGetMatrixCoefficients call must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetMatrixCoefficients() Using an invalid handle but with valid pointer | handle = [invalid handle], matrix_coefficients = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort() Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsGetMatrixCoefficients() By looping through acquired port handles but with a invalid pointer | handle = [valid handle], matrix_coefficients = [invalid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetMatrixCoefficients() Again after terminating video ports attempt to get the matrix coefficients  of video ports | handle= [ valid handle ] , matrix_coefficients = [valid pointer] | dsERR_NOT_INITIALIZED | dsGetMatrixCoefficients call must fail as module is not initialized |
 * 
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsGetMatrixCoefficients(void) {
    dsError_t status;
    VideoPortHandle handle = /* Initialize with invalid handle */;
    MatrixCoefficients_t matrixCoefficients; // To store the matrix coefficients

    // Step 01: Attempt to get matrix coefficients without initialization
    status = dsGetMatrixCoefficients(handle, &matrixCoefficients);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Invalid handle check
    status = dsGetMatrixCoefficients(/* invalid handle */, &matrixCoefficients);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get valid video port handle
    status = dsGetVideoPort(/* valid port type */, /* valid port index */, &handle);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 05: Get matrix coefficients with invalid pointer
    status = dsGetMatrixCoefficients(handle, NULL);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 07: Attempt to get matrix coefficients after termination
    status = dsGetMatrixCoefficients(handle, &matrixCoefficients);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Positive Test Scenarios for dsGetColorDepth()
 * 
 * **Test Group ID:** Basic: 80@p
 * **Test Case ID:** 080@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsGetColorDepth() by looping through the acquired port handles and valid pointer to retrieve the current color depth  & store in an array | handle  = [loop through valid handles] , color_depth = [valid pointer] | dsERR_NONE | must return a valid color depth value of the specified video port|
 * |04|Call dsGetColorDepth() -Again by looping through the acquired port handles and valid pointer to retrieve the current color depth & store it in a new array | handle  = [loop through valid handles] , color_depth = [valid pointer] | dsERR_NONE | must return a valid color depth value of the specified video port|
 * |05|Compare the array values and make sure they are equal | | dsERR_NONE | The values must be equal |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsGetColorDepth(void) {
    dsError_t status;
    VideoPortHandle handle;
    ColorDepth_t colorDepthArray1[/* Size matching kPorts array */];
    ColorDepth_t colorDepthArray2[/* Size matching kPorts array */];
    int kPorts[] = {/* Array of valid port indexes */};
    int portType = /* Valid port type */;

    // Assume ColorDepth_t is defined and represents the color depth

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the video port handle
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetVideoPort(portType, kPorts[i], &handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Retrieve the color depth
        status = dsGetColorDepth(handle, &colorDepthArray1[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 04: Repeat the retrieval of color depth
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetColorDepth(handle, &colorDepthArray2[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 05: Compare the array values
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        UT_ASSERT_EQUAL(colorDepthArray1[i], colorDepthArray2[i]);
    }

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Negative Test Scenarios for dsGetColorDepth()
 * 
 * **Test Group ID:** Basic: 80@n
 * **Test Case ID:** 080@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetColorDepth() Attempt to get the color depth with out initializing video ports| handle = [invalid handle] , color_depth = [valid pointer]| dsERR_NOT_INITIALIZED| dsGetColorDepth call must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetColorDepth() Using an invalid handle but with valid pointer | handle = [invalid handle], color_depth = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort() Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsGetColorDepth() By looping through acquired port handles but with a invalid pointer | handle = [valid handle], color_depth = [invalid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetColorDepth() Again after terminating video ports attempt to get the color depth of video ports | handle= [invalid handle] , color_depth = [valid pointer] | dsERR_NOT_INITIALIZED | dsGetColorDepth call must fail as module is not initialized |
 * 
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsGetColorDepth(void) {
    dsError_t status;
    VideoPortHandle handle = /* Initialize with invalid handle */;
    ColorDepth_t colorDepth; // To store the color depth

    // Step 01: Attempt to get color depth without initialization
    status = dsGetColorDepth(handle, &colorDepth);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Invalid handle check
    status = dsGetColorDepth(/* invalid handle */, &colorDepth);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get valid video port handle
    status = dsGetVideoPort(/* valid port type */, /* valid port index */, &handle);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 05: Get color depth with invalid pointer
    status = dsGetColorDepth(handle, NULL);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 07: Attempt to get color depth after termination
    status = dsGetColorDepth(handle, &colorDepth);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Positive Test Scenarios for dsGetColorSpace()
 * 
 * **Test Group ID:** Basic: 90@p
 * **Test Case ID:** 090@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsGetColorSpace() by looping through the acquired port handles and valid pointer to retrieve the current color space setting of video port & store it in an array |handle  = [loop through valid handles] , color_space = [valid pointer] |Valid color space value|must return a valid color space setting of the specified video port|
 * |04|Call dsGetColorSpace() -Again by looping through the acquired port handles and valid pointer to retrieve the current color space setting of video port & store it in a new array |handle  = [loop through valid handles] , color_space = [valid pointer] |Valid color space value|must return a valid color space setting of the specified video port|
 * |05|Compare the array values and make sure they are equal | | dsERR_NONE | The values must be equal |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsGetColorSpace(void) {
    dsError_t status;
    VideoPortHandle handle;
    ColorSpace_t colorSpaceArray1[/* Size matching kPorts array */];
    ColorSpace_t colorSpaceArray2[/* Size matching kPorts array */];
    int kPorts[] = {/* Array of valid port indexes */};
    int portType = /* Valid port type */;

    // Assume ColorSpace_t is defined and represents the color space

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the video port handle
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetVideoPort(portType, kPorts[i], &handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Retrieve the color space
        status = dsGetColorSpace(handle, &colorSpaceArray1[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 04: Repeat the retrieval of color space
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetColorSpace(handle, &colorSpaceArray2[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 05: Compare the array values
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        UT_ASSERT_EQUAL(colorSpaceArray1[i], colorSpaceArray2[i]);
    }

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}

/**
 * @brief Negative Test Scenarios for dsGetColorSpace()
 * 
 * **Test Group ID:** Basic: 90@n
 * **Test Case ID:** 090@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetColorSpace() Attempt to get the color space with out initializing video ports| handle = [invalid handle] , color_space = [valid pointer]| dsERR_NOT_INITIALIZED| dsGetColorSpace call must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetColorSpace() Using an invalid handle but with valid pointer | handle = [invalid handle], color_space = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort() Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsGetColorSpace() By looping through acquired port handles but with a invalid pointer | handle = [valid handle], color_space = [invalid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetColorSpace() Again after terminating video ports attempt to get the color space of video ports | handle= [invalid handle] , color_space = [valid pointer] | dsERR_NOT_INITIALIZED | dsGetColorSpace call must fail as module is not initialized |
 * 
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsGetColorSpace(void) {
    dsError_t status;
    VideoPortHandle handle = /* Initialize with invalid handle */;
    ColorSpace_t colorSpace; // To store the color space

    // Step 01: Attempt to get color space without initialization
    status = dsGetColorSpace(handle, &colorSpace);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Invalid handle check
    status = dsGetColorSpace(/* invalid handle */, &colorSpace);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get valid video port handle
    status = dsGetVideoPort(/* valid port type */, /* valid port index */, &handle);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 05: Get color space with invalid pointer
    status = dsGetColorSpace(handle, NULL);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 07: Attempt to get color space after termination
    status = dsGetColorSpace(handle, &colorSpace);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}

/**
 * @brief Positive Test Scenarios for dsGetQuantizationRange()
 * 
 * **Test Group ID:** Basic: 100@p
 * **Test Case ID:** 100@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsGetQuantizationRange() by looping through the acquired port handles and valid pointer to retrieve the current quantization range & store it in an array |handle  = [loop through valid handles] , quantization_range = [valid pointer] |dsERR_NONE | must return a valid quantization range of the specified video port|
 * |04|Call dsGetQuantizationRange() -Again by looping through the acquired port handles and valid pointer to retrieve the current quantization range & store it in a new array |handle  = [loop through valid handles] , quantization_range = [valid pointer] |dsERR_NONE | must return a valid quantization range of the specified video port|
 * |05|Compare the array values and make sure they are equal | | dsERR_NONE | The values must be equal |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsGetQuantizationRange(void) {
    dsError_t status;
    VideoPortHandle handle;
    QuantizationRange_t quantizationRangeArray1[/* Size matching kPorts array */];
    QuantizationRange_t quantizationRangeArray2[/* Size matching kPorts array */];
    int kPorts[] = {/* Array of valid port indexes */};
    int portType = /* Valid port type */;

    // Assume QuantizationRange_t is defined and represents the quantization range

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the video port handle
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetVideoPort(portType, kPorts[i], &handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Retrieve the quantization range
        status = dsGetQuantizationRange(handle, &quantizationRangeArray1[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 04: Repeat the retrieval of quantization range
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetQuantizationRange(handle, &quantizationRangeArray2[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 05: Compare the array values
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        UT_ASSERT_EQUAL(quantizationRangeArray1[i], quantizationRangeArray2[i]);
    }

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}

/**
 * @brief Negative Test Scenarios for dsGetQuantizationRange()
 * 
 * **Test Group ID:** Basic: 100@n
 * **Test Case ID:** 100@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetQuantizationRange() Attempt to get the quantization range with out initializing video ports| handle = [invalid handle] , quantization_range = [valid pointer]| dsERR_NOT_INITIALIZED| dsGetQuantizationRange call must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetQuantizationRange() Using an invalid handle but with valid pointer | handle = [invalid handle], quantization_range = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort() Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsGetQuantizationRange() By looping through acquired port handles but with a invalid pointer | handle = [valid handle], quantization_range = [invalid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetQuantizationRange() Again after terminating video ports attempt to get the quantization of video ports | handle= [valid handle from step 04 ] , quantization_range = [valid pointer] | dsERR_NOT_INITIALIZED | dsGetQuantizationRange call must fail as module is not initialized |
 * 
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsGetQuantizationRange(void) {
    dsError_t status;
    VideoPortHandle handle = /* Initialize with invalid handle */;
    QuantizationRange_t quantizationRange; // To store the quantization range

    // Step 01: Attempt to get quantization range without initialization
    status = dsGetQuantizationRange(handle, &quantizationRange);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Invalid handle check
    status = dsGetQuantizationRange(/* invalid handle */, &quantizationRange);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get valid video port handle
    status = dsGetVideoPort(/* valid port type */, /* valid port index */, &handle);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 05: Get quantization range with invalid pointer
    status = dsGetQuantizationRange(handle, NULL);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 07: Attempt to get quantization range after termination
    status = dsGetQuantizationRange(handle, &quantizationRange);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Positive Test Scenarios for dsGetCurrentOutputSettings()
 * 
 * **Test Group ID:** Basic: 101@p
 * **Test Case ID:** 101@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsGetCurrentOutputSettings() by looping through the acquired port handles and valid pointer to retrieve the current output settings and store it in an array | handle= [loop through valid handles] , video_eotf = [valid EOTF pointer], matrix_coefficients = = [valid matrix coefficient pointer], color_space = [valid color space pointer], color_depth = [valid color depth pointer], quantization_range = [valid quantization range pointer]| dsERR_NONE and valid settings| All the output settings for the specified video port must be returned |
 * |04|Call dsGetCurrentOutputSettings() -Again by looping through the acquired port handles and valid pointer to retrieve the current output settings and store it in a new array | handle= [loop through valid handles] , video_eotf = [valid EOTF pointer], matrix_coefficients = = [valid matrix coefficient pointer], color_space = [valid color space pointer], color_depth = [valid color depth pointer], quantization_range = [valid quantization range pointer]| dsERR_NONE and valid settings| All the output settings for the specified video port must be returned |
 * |05|Compare the array values and make sure they are equal | | dsERR_NONE | The values must be equal |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsGetCurrentOutputSettings(void) {
    dsError_t status;
    VideoPortHandle handle;
    OutputSettings settingsArray1[/* Size matching kPorts array */];
    OutputSettings settingsArray2[/* Size matching kPorts array */];
    int kPorts[] = {/* Array of valid port indexes */};
    int portType = /* Valid port type */;

    // Assume OutputSettings is a struct that includes EOTF, matrix coefficients, color space, color depth, and quantization range

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the video port handle
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetVideoPort(portType, kPorts[i], &handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Retrieve the current output settings
        status = dsGetCurrentOutputSettings(handle, &settingsArray1[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 04: Repeat the retrieval of output settings
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetCurrentOutputSettings(handle, &settingsArray2[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 05: Compare the array values
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        UT_ASSERT_TRUE(compareOutputSettings(settingsArray1[i], settingsArray2[i])); // Assume compareOutputSettings is defined
    }

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Negative Test Scenarios for dsGetCurrentOutputSettings()
 * 
 * **Test Group ID:** Basic: 101@n
 * **Test Case ID:** 101@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetCurrentOutputSettings() - Attempt to get the current output settings without initializing the video ports | handle = [invalid handle],  video_eotf = [valid EOTF pointer], matrix_coefficients = = [valid matrix coefficient pointer], color_space = [valid color space pointer], color_depth = [valid color depth pointer], quantization_range = [valid quantization range pointer] | dsERR_NOT_INITIALIZED | Get Output settings must fail as module is not initialized|
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetCurrentOutputSettings() with an invalid handle but with valid pointers for output settings |handle = [valid handle], video_eotf = [valid EOTF pointer], matrix_coefficients = = [valid matrix coefficient pointer], color_space = [valid color space pointer], color_depth = [valid color depth pointer], quantization_range = [valid quantization range pointer] |dsERR_INVALID_PARAM| Invalid parameter error must be returned |
 * |04|Call dsGetCurrentOutputSettings() with an valid handle but invalid pointer for parameters | handle = [valid handle], NULL pointers for some or all parameters|dsERR_INVALID_PARAM| Invalid parameter error must be returned |
 * |05|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |06|Call dsGetCurrentOutputSettings() - Attempt to get the current output settings without initializing the video ports | handle = [valid handle],  video_eotf = [valid EOTF pointer], matrix_coefficients = = [valid matrix coefficient pointer], color_space = [valid color space pointer], color_depth = [valid color depth pointer], quantization_range = [valid quantization range pointer] | dsERR_NOT_INITIALIZED | Get Output settings must fail as module is not initialized|
 * 
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsGetCurrentOutputSettings(void) {
    dsError_t status;
    VideoPortHandle handle = /* Initialize with invalid handle */;
    OutputSettings settings; // To store the output settings

    // Step 01: Attempt to get output settings without initialization
    status = dsGetCurrentOutputSettings(handle, &settings);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Invalid handle check
    status = dsGetCurrentOutputSettings(/* invalid handle */, &settings);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get valid video port handle
    status = dsGetVideoPort(/* valid port type */, /* valid port index */, &handle);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 05: Get output settings with invalid pointer
    status = dsGetCurrentOutputSettings(handle, NULL); // Assumed that all pointers are NULL
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 07: Attempt to get output settings after termination
    status = dsGetCurrentOutputSettings(handle, &settings);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Positive Test Scenarios for dsIsOutputHDR()
 * 
 * **Test Group ID:** Basic: 102@p
 * **Test Case ID:** 102@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsIsOutputHDR() - by looping through acquired port handles to check if the video output is HDR or not & store it in an array |  handle = [valid handle], hdr = [valid pointer to hold hdr status value](true = HDR) | dsERR_NONE | Flag which holds the HDR status( @a true if Video Output is HDR and @a false otherwise ) of Video Port must be returned |
 * |04|Call dsIsOutputHDR() - Again by looping through acquired port handles to check if the video output is HDR or not & store it in a new array |  handle = [valid handle], hdr = [valid pointer to hold hdr status value](true = HDR) | dsERR_NONE | Flag which holds the HDR status( @a true if Video Output is HDR and @a false otherwise ) of Video Port must be returned |
 * |05|Compare the array values and make sure they are equal | | dsERR_NONE | The values must be equal |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 * 
 */
void test_l1_dsVideoPort_positive_dsIsOutputHDR(void) {
    dsError_t status;
    VideoPortHandle handle;
    bool hdrArray1[/* Size matching kPorts array */];
    bool hdrArray2[/* Size matching kPorts array */];
    int kPorts[] = {/* Array of valid port indexes */};
    int portType = /* Valid port type */;

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the video port handle
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsGetVideoPort(portType, kPorts[i], &handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Check HDR status
        status = dsIsOutputHDR(handle, &hdrArray1[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 04: Repeat the HDR status check
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        status = dsIsOutputHDR(handle, &hdrArray2[i]);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 05: Compare the array values
    for (int i = 0; i < sizeof(kPorts) / sizeof(kPorts[0]); i++) {
        UT_ASSERT_EQUAL(hdrArray1[i], hdrArray2[i]);
    }

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Negative Test Scenarios for dsIsOutputHDR()
 * 
 * **Test Group ID:** Basic: 102@n
 * **Test Case ID:** 102@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsIsOutputHDR() - Attempt to check if video output is HDR or not without initializing video ports | handle: [ invalid handle ], hdr: [ pointer to hold HDR status]| dsERR_NOT_INITIALIZED | Call to check if video output is HDR or not must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsIsOutputHDR() using an invalid handle but with a valid pointer to hold the HDR status | handle: [ invalid handle ], hdr: [ pointer to hold HDR status] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |05|Call dsIsOutputHDR() by looping through acquired port handles but with a null pointer for HDR status | handle: [ loop through valid handles ], hdr: [ NULL ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsIsOutputHDR() - Attempt to check if video output is HDR or not without initializing video ports | handle: [ valid handle ], hdr: [ pointer to hold HDR status] | dsERR_NOT_INITIALIZED | Call to check if video output is HDR or not must fail as module is not initialized |
 * 
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsIsOutputHDR(void) {
    dsError_t status;
    VideoPortHandle handle = /* Initialize with invalid handle */;
    bool hdrStatus;

    // Step 01: Attempt to check HDR status without initialization
    status = dsIsOutputHDR(handle, &hdrStatus);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Invalid handle check
    status = dsIsOutputHDR(/* invalid handle */, &hdrStatus);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get valid video port handle
    status = dsGetVideoPort(/* valid port type */, /* valid port index */, &handle);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 05: Check HDR status with null pointer
    status = dsIsOutputHDR(handle, NULL);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 07: Attempt to check HDR status after termination
    status = dsIsOutputHDR(handle, &hdrStatus);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Positive Test Scenarios for dsResetOutputToSDR()
 * 
 * **Test Group ID:** Basic: 103@p
 * **Test Case ID:** 103@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|dsResetOutputToSDR() - To reset the video output to SDR | | dsERR_NONE | Video Output must be resetted to SDR |
 * |03|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 * 
 */
void test_l1_dsVideoPort_positive_dsResetOutputToSDR(void) {
    dsError_t status;

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Reset video output to SDR
    status = dsResetOutputToSDR();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Negative Test Scenarios for dsResetOutputToSDR()
 * 
 * **Test Group ID:** Basic: 103@n
 * **Test Case ID:** 103@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsResetOutputToSDR() - Attempt to reset the video output to SDR without initializing the video ports | dsERR_NOT_INITIALIZED | Reset Video output to SDR must fail as video port is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |04|Call dsResetOutputToSDR() - Again attempt to reset the video output to SDR after terminating the video ports | dsERR_NOT_INITIALIZED| Reset Video output to SDR must fail as video port is not initialized |
 * 
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsResetOutputToSDR(void) {
    dsError_t status;

    // Step 01: Attempt reset without initialization
    status = dsResetOutputToSDR();
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 04: Attempt reset after termination
    status = dsResetOutputToSDR();
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Positive Test Scenarios for dsSetHdmiPreference()
 * 
 * **Test Group ID:** Basic: 104@p
 * **Test Case ID:** 104@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned for all supported video ports|
 * |03|Call dsSetHdmiPreference() - by looping through the acquired port handles and set the HDMI preference from dsHdcpProtocolVersion_t | handle = [Valid handle], hdcpCurrentProtocol=[valid HDCP Protocol] | dsERR_NONE | HDMI Preference must be set successfully |
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsSetHdmiPreference(void) {
    dsError_t status;

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the port handle for all supported video ports
    // Loop through kPorts to get each handle
    for (int i = 0; i < kPortsLength; i++) {
        dsVideoPortHandle_t handle;
        status = dsGetVideoPort(kPorts[i], &handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Set the HDMI preference
        dsHdcpProtocolVersion_t hdcpCurrentProtocol = /* valid HDCP Protocol */;
        status = dsSetHdmiPreference(handle, hdcpCurrentProtocol);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 04: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Negative Test Scenarios for dsSetHdmiPreference()
 * 
 * **Test Group ID:** Basic: 104@n
 * **Test Case ID:** 104@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsSetHdmiPreference() - Attempt to set the HDMI Preference without initializing the video ports | handle = [invalid handle], hdcpCurrentProtocol = [valid pointer] | dsERR_NOT_INITIALIZED | Set Hdmi Preference must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetHdmiPreference() - Using an invalid handle but with valid HDCP Protcol pointer | handle = [invalid handle], hdcpCurrentProtocol = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] | dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsSetHdmiPreference() - by looping through the acquired port handles and set the HDMI preference from dsHdcpProtocolVersion_t | handle = [Valid handle], hdcpCurrentProtocol=[valid HDCP Protocol] | dsERR_NONE | HDMI Preference must be set successfully |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsSetHdmiPreference() - Attempt to set the HDMI Preference without initializing the video ports | handle = [valid handle], hdcpCurrentProtocol = [valid pointer] | dsERR_NOT_INITIALIZED | Set Hdmi Preference must fail as module is not initialized |
 * 
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsSetHdmiPreference(void) {
    dsError_t status;

    // Step 01: Attempt set HDMI preference without initialization
    status = dsSetHdmiPreference(invalidHandle, validHdcpProtocol);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Set HDMI preference with invalid handle
    status = dsSetHdmiPreference(invalidHandle, validHdcpProtocol);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get the port handle for all supported video ports
    dsVideoPortHandle_t validHandle;
    status = dsGetVideoPort(/* valid type and index */, &validHandle);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 05: Set HDMI preference with valid handle and HDCP protocol
    status = dsSetHdmiPreference(validHandle, validHdcpProtocol);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 07: Attempt set HDMI preference after termination
    status = dsSetHdmiPreference(validHandle, validHdcpProtocol);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Positive Test Scenarios for dsGetHdmiPreference()
 * 
 * **Test Group ID:** Basic: 105@p
 * **Test Case ID:** 105@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsGetHdmiPreference() - by looping through the acquired port handles to get the HDMI Preference of each video ports which supports HDCP & store it in an array | handle = [valid handle], hdcpCurrentProtocol = [valid pointer] | dsERR_NONE |  The Current HDMI Preference must be returned |
 * |04|Call dsGetHdmiPreference() - Again by looping through the acquired port handles to get the HDMI Preference of each video ports which supports HDCP & store it in a new array | handle = [valid handle], hdcpCurrentProtocol = [valid pointer] | dsERR_NONE |  The Current HDMI Preference must be returned |
 * |05|Compare the array values and make sure they are equal | | dsERR_NONE | The values must be equal |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsGetHdmiPreference(void) {
    dsError_t status;

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the port handle for all supported video ports
    for (int i = 0; i < kPortsLength; i++) {
        dsVideoPortHandle_t handle;
        status = dsGetVideoPort(kPorts[i], &handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Get the HDMI preference
        dsHdcpProtocolVersion_t hdcpCurrentProtocol;
        status = dsGetHdmiPreference(handle, &hdcpCurrentProtocol);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
        // Store the protocol in an array for comparison later

        // Step 04: Repeat getting HDMI preference
        dsHdcpProtocolVersion_t newHdcpCurrentProtocol;
        status = dsGetHdmiPreference(handle, &newHdcpCurrentProtocol);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
        // Store this protocol in a new array for comparison
    }

    // Step 05: Compare the array values and make sure they are equal

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Negative Test Scenarios for dsGetHdmiPreference()
 * 
 * **Test Group ID:** Basic: 105@n
 * **Test Case ID:** 105@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetHdmiPreference() - Attempt to get the HDMI Preference without prior initializing the video ports| handle = [invalid handle], hdcpCurrentProtocol = [valid pointer] | dsERR_NOT_INITIALIZED | Get HDMI Preference of video ports must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetHdmiPreference() - Using an invalid handle but with valid HDCP Protcol pointer | handle = [invalid handle], hdcpCurrentProtocol = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] | dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsGetHdmiPreference() - by looping through the acquired port handles and get the HDMI preference | handle = [Valid handle], hdcpCurrentProtocol = [valid HDCP Protocol(from dsHdcpProtocolVersion_t)] | dsERR_NONE | Valid HDMI Preference must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsSetHdmiPreference() - Attempt to get the HDMI Preference without initializing the video ports | handle = [valid handle], hdcpCurrentProtocol = [valid pointer] | dsERR_NOT_INITIALIZED | Get Hdmi Preference must fail as module is not initialized |
 * 
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsGetHdmiPreference(void) {
    dsError_t status;

    // Step 01: Attempt to get HDMI preference without initialization
    dsHdcpProtocolVersion_t hdcpCurrentProtocol;
    status = dsGetHdmiPreference(invalidHandle, &hdcpCurrentProtocol);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Get HDMI preference with invalid handle
    status = dsGetHdmiPreference(invalidHandle, &hdcpCurrentProtocol);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get the port handle for all supported video ports
    dsVideoPortHandle_t validHandle;
    status = dsGetVideoPort(/* valid type and index */, &validHandle);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 05: Get HDMI preference with valid handle
    status = dsGetHdmiPreference(validHandle, &hdcpCurrentProtocol);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 07: Attempt to get HDMI preference after termination
    status = dsGetHdmiPreference(validHandle, &hdcpCurrentProtocol);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Positive Test Scenarios for dsGetIgnoreEDIDStatus()
 * 
 * **Test Group ID:** Basic: 106@p
 * **Test Case ID:** 106@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsGetIgnoreEDIDStatus() by looping through acquired handles and valid pointer to get IgnoreEDID status & store it in an array |handle=[valid handle] ,status=[valid pointer] |dsERR_NONE | must successfully get the IgnoreEDID status|
 * |04|Call dsGetIgnoreEDIDStatus() - Again by looping through acquired handles and valid pointer to get IgnoreEDID status & store it in a new array |handle=[valid handle] ,status=[valid pointer] |dsERR_NONE | must successfully get the IgnoreEDID status|
 * |05|Compare the array values and make sure they are equal | | dsERR_NONE | The values must be equal |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsGetIgnoreEDIDStatus(void) {
    dsError_t status;

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the port handle for supported video ports
    for (int i = 0; i < kPortsLength; i++) {
        dsVideoPortHandle_t handle;
        status = dsGetVideoPort(kPorts[i], &handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Get IgnoreEDID status
        bool ignoreEDIDStatus;
        status = dsGetIgnoreEDIDStatus(handle, &ignoreEDIDStatus);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
        // Store the status in an array for comparison later

        // Step 04: Repeat getting IgnoreEDID status
        bool newIgnoreEDIDStatus;
        status = dsGetIgnoreEDIDStatus(handle, &newIgnoreEDIDStatus);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
        // Store this status in a new array for comparison
    }

    // Step 05: Compare the array values and make sure they are equal

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Negative Test Scenarios for dsGetIgnoreEDIDStatus()
 * 
 * **Test Group ID:** Basic: 106@n
 * **Test Case ID:** 106@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetIgnoreEDIDStatus() without prior initialization of video ports| handle=[invalid handle] ,status=[invalid pointer] |dsERR_NOT_INITIALIZED|call must be fail as module is not initialzed|
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetIgnoreEDIDStatus() with an invalid handle but with valid pointer|handle=[invalid handle] ,status=[valid pointer]|dsERR_INVALID_PARAM|Invalid parameter must be returned|
 * |04|Call dsGetVideoPort() Get the port handle for all supported video ports on the platform  |type , index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsGetIgnoreEDIDStatus() by looping through valid handles with a NULL status pointer | handle=[valid handle] , status=[NULL pointer]|dsERR_INVALID_PARAM|Invalid parameter must be returned|
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetIgnoreEDIDStatus()  Again after terminating video ports | handle=[valid handle from step 04 ] , status=[valid pointer] | dsERR_NOT_INITIALIZED | call must fail as module is not initialized |
 * 
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsGetIgnoreEDIDStatus(void) {
    dsError_t status;

    // Step 01: Attempt to get IgnoreEDID status without initialization
    bool ignoreEDIDStatus;
    status = dsGetIgnoreEDIDStatus(invalidHandle, &ignoreEDIDStatus);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Get IgnoreEDID status with invalid handle
    status = dsGetIgnoreEDIDStatus(invalidHandle, &ignoreEDIDStatus);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get the port handle for supported video ports
    dsVideoPortHandle_t validHandle;
    status = dsGetVideoPort(/* valid type and index */, &validHandle);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 05: Get IgnoreEDID status with valid handle but null pointer
    status = dsGetIgnoreEDIDStatus(validHandle, NULL);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 07: Attempt to get IgnoreEDID status after termination
    status = dsGetIgnoreEDIDStatus(validHandle, &ignoreEDIDStatus);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Positive Test Scenarios for dsSetBackgroundColor()
 * 
 * **Test Group ID:** Basic: 107@p
 * **Test Case ID:** 107@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsSetBackgroundColor by looping through the acquired prots and valid color values| handle=[Valid handle], color=[valid values] | dsERR_NONE|Background color must be set successfully|
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsSetBackgroundColor(void) {
    dsError_t status;

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the port handle for supported video ports
    for (int i = 0; i < kPortsLength; i++) {
        dsVideoPortHandle_t handle;
        status = dsGetVideoPort(kPorts[i], &handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Set background color
        // Assuming color is a predefined structure or value
        dsColor_t color = {/* valid color values */};
        status = dsSetBackgroundColor(handle, color);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 04: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Negative Test Scenarios for dsSetBackgroundColor()
 * 
 * **Test Group ID:** Basic: 107@n
 * **Test Case ID:** 107@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsSetBackgroundColor() without prior initialization of video ports| handle=[inValid handle], color=[valid values] |dsERR_NOT_INITIALIZED|call must fail as module not initialized|
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetBackgroundColor()  with an invalid handle and valid color values |handle=[inValid handle], color=[valid values]|dsERR_INVALID_PARAM|Invalid parameter must return |
 * |04|Call dsGetVideoPort() Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsSetBackgroundColor() by looping through acquired handles and invalid color value|handle=[valid handle], color=[Invalid color value|dsERR_INVALID_PARAM|Invalid parameter must return|
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsSetBackgroundColor() after termination video ports |handle= [valid handle from step 04 ] , color= [valid values] | dsERR_NOT_INITIALIZED | call must fail as module is not initialized |
 *
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsSetBackgroundColor(void) {
    dsError_t status;

    // Step 01: Attempt to set background color without initialization
    dsColor_t color = {/* valid color values */};
    status = dsSetBackgroundColor(invalidHandle, color);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Set background color with invalid handle
    status = dsSetBackgroundColor(invalidHandle, color);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get the port handle for supported video ports
    dsVideoPortHandle_t validHandle;
    status = dsGetVideoPort(/* valid type and index */, &validHandle);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 05: Set background color with valid handle but invalid color
    // Assuming invalidColor is a predefined structure or value
    dsColor_t invalidColor = {/* invalid color values */};
    status = dsSetBackgroundColor(validHandle, invalidColor);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 07: Attempt to set background color after termination
    status = dsSetBackgroundColor(validHandle, color);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Positive Test Scenarios for dsSetForceHDRMode()
 * 
 * **Test Group ID:** Basic: 109@p
 * **Test Case ID:** 109@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsSetForceHDRMode() by looping through acquired handles and valid mode values|handle=[valid handle], mode=[valid values]|dsERR_NONE|HDR mode must be set successfully|
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsSetForceHDRMode(void) {
    dsError_t status;

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the port handle for supported video ports
    for (int i = 0; i < kPortsLength; i++) {
        dsVideoPortHandle_t handle;
        status = dsGetVideoPort(kPorts[i], &handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Set HDR mode
        // Assuming mode is a predefined structure or value
        dsHDRMode_t mode = {/* valid HDR mode values */};
        status = dsSetForceHDRMode(handle, mode);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 04: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Negative Test Scenarios for dsSetForceHDRMode()
 * 
 * **Test Group ID:** Basic: 109@n
 * **Test Case ID:** 109@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsSetForceHDRMode() without prior initialization of video ports| handle=[invalid handle], mode=[valid values] |dsERR_NOT_INITIALIZED|call must fail as module not initialized|
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetForceHDRMode() with an invalid handle and valid mode values|handle=[inValid handle], mode=[valid values]|dsERR_INVALID_PARAM|Invalid parameter must return|
 * |04|Call dsGetVideoPort() Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsSetForceHDRMode() by looping through acquired handles and valid mode values|handle=[Valid handle], mode=[invalid values]|dsERR_INVALID_PARAM|Invalid parameter must return|
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsSetForceHDRMode() after termination video ports |handle=[valid handle from step 04 ] , mode=[valid values] | dsERR_NOT_INITIALIZED | call must fail as module is not initialized |
 * 
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsSetForceHDRMode(void) {
    dsError_t status;

    // Step 01: Attempt to set HDR mode without initialization
    dsHDRMode_t mode = {/* valid HDR mode values */};
    status = dsSetForceHDRMode(invalidHandle, mode);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Set HDR mode with invalid handle
    status = dsSetForceHDRMode(invalidHandle, mode);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get the port handle for supported video ports
    dsVideoPortHandle_t validHandle;
    status = dsGetVideoPort(/* valid type and index */, &validHandle);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 05: Set HDR mode with invalid mode values
    // Assuming invalidMode is a predefined structure or value
    dsHDRMode_t invalidMode = {/* invalid HDR mode values */};
    status = dsSetForceHDRMode(validHandle, invalidMode);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 07: Attempt to set HDR mode after termination
    status = dsSetForceHDRMode(validHandle, mode);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Positive Test Scenarios for dsColorDepthCapabilities()
 * 
 * **Test Group ID:** Basic: 110@p
 * **Test Case ID:** 110@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsColorDepthCapabilities() by looping through the acquired ports and valid pointer to get the color depth capabilities & store it in an array |handle=[vallid handle], colorDepthCapability=[valid pointer] |dsERR_NONE  Color depth capabilities must be retrieved successfully|
 * |04|Call dsColorDepthCapabilities() -Again by looping through the acquired ports and valid pointer to get the color depth capabilities & store it in a new array |handle=[vallid handle], colorDepthCapability=[valid pointer] |dsERR_NONE  Color depth capabilities must be retrieved successfully|
 * |05|Compare the array values and make sure they are equal | | dsERR_NONE | The values must be equal |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsColorDepthCapabilities(void) {
    dsError_t status;

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the port handle for supported video ports
    for (int i = 0; i < kPortsLength; i++) {
        dsVideoPortHandle_t handle;
        status = dsGetVideoPort(kPorts[i], &handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Get color depth capabilities
        dsColorDepth_t colorDepthCapability;
        status = dsColorDepthCapabilities(handle, &colorDepthCapability);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
        // Storing in an array for comparison
        arrayOfCapabilities[i] = colorDepthCapability;

        // Step 04: Repeating to get capabilities for new array
        dsColorDepth_t newColorDepthCapability;
        status = dsColorDepthCapabilities(handle, &newColorDepthCapability);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
        newArrayOfCapabilities[i] = newColorDepthCapability;
    }

    // Step 05: Compare array values
    UT_ASSERT_ARRAY_EQUAL(arrayOfCapabilities, newArrayOfCapabilities, kPortsLength);

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Negative Test Scenarios for dsColorDepthCapabilities()
 * 
 * **Test Group ID:** Basic: 110@n
 * **Test Case ID:** 110@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsColorDepthCapabilities() without prior initialization of video ports|handle=[invalid handle], colorDepthCapability=[valid pointer]|dsERR_NOT_INITIALIZED|call must fail as module not initialized|
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsColorDepthCapabilities() with an invalid handle and valid pointer |handle=[valid handle], colorDepthCapability=[valid pointer] |dsERR_INVALID_PARAM|Invalid parameter must be returned |
 * |04|Call dsGetVideoPort() Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |04|Call dsColorDepthCapabilities() by looping through acquired handles and invalid pointer | handle=[valid handle], colorDepthCapability=[Invalid pointer]|dsERR_INVALID_PARAM|Invalid parameter must return|
 * |05|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |06|Call dsColorDepthCapabilities() after terminating videop ports |handle= [valid handle from step 04 ] , colorDepthCapability= [valid pointer] | dsERR_NOT_INITIALIZED|call must fail as module not initialized |
 * 
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsColorDepthCapabilities(void) {
    dsError_t status;

    // Step 01: Attempt to get capabilities without initialization
    dsColorDepth_t colorDepthCapability;
    status = dsColorDepthCapabilities(invalidHandle, &colorDepthCapability);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Get capabilities with invalid handle
    status = dsColorDepthCapabilities(invalidHandle, &colorDepthCapability);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get the port handle for supported video ports
    dsVideoPortHandle_t validHandle;
    status = dsGetVideoPort(/* valid type and index */, &validHandle);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 05: Get capabilities with invalid pointer
    status = dsColorDepthCapabilities(validHandle, NULL);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 07: Attempt to get capabilities after termination
    status = dsColorDepthCapabilities(validHandle, &colorDepthCapability);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Positive Test Scenarios for dsGetPreferredColorDepth()
 * 
 * **Test Group ID:** Basic: 130@p
 * **Test Case ID:** 130@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsGetPreferredColorDepth by looping through acquired handles and valid pointer to get the preferred color depth of each port & store it in an array |handle=[valid handle] , colorDepth=[valid pointer]|dsERR_NONE|Preferred Color depth must be retrieved successfully|
 * |04|Call dsGetPreferredColorDepth - Again by looping through acquired handles and valid pointer to get the preferred color depth of each port & store it in a new array |handle=[valid handle] , colorDepth=[valid pointer]|dsERR_NONE|Preferred Color depth must be retrieved successfully|
 * |05|Compare the array values and make sure they are equal | | dsERR_NONE | The values must be equal |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsGetPreferredColorDepth(void) {
    dsError_t status;

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the port handle for supported video ports
    for (int i = 0; i < kPortsLength; i++) {
        dsVideoPortHandle_t handle;
        status = dsGetVideoPort(kPorts[i], &handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Get preferred color depth
        dsColorDepth_t colorDepth;
        status = dsGetPreferredColorDepth(handle, &colorDepth);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
        // Storing in an array for comparison
        arrayOfColorDepths[i] = colorDepth;

        // Step 04: Repeat to get color depth for new array
        dsColorDepth_t newColorDepth;
        status = dsGetPreferredColorDepth(handle, &newColorDepth);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
        newArrayOfColorDepths[i] = newColorDepth;
    }

    // Step 05: Compare array values
    UT_ASSERT_ARRAY_EQUAL(arrayOfColorDepths, newArrayOfColorDepths, kPortsLength);

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Negative Test Scenarios for dsGetPreferredColorDepth()
 * 
 * **Test Group ID:** Basic: 130@n
 * **Test Case ID:** 130@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetPreferredColorDepth() without prior initialization of video ports|handle=[invalid handle] , colorDepth=[valid pointer]|dsERR_NOT_INITIALIZED|call must fail as module is not initialized|
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetPreferredColorDepth() with an invalid handle and with valid pointer|handle=[invalid handle] , colorDepth=[valid pointer]|dsERR_INVALID_PARAM|Invalid parameter must be returned|
 * |04|Call dsGetVideoPort() Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsGetPreferredColorDepth() by looping through valid handes and with invalid pointer|handle=[valid handle] , colorDepth=[invalid pointer]|dsERR_INVALID_PARAM|Invalid parameter must be returned|
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetPreferredColorDepth() after terminating video ports |handle=[valid handle] , colorDepth=[valid pointer] |dsERR_NOT_INITIALIZED|call must fail as module is not initialized|
 *
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsGetPreferredColorDepth(void) {
    dsError_t status;

    // Step 01: Attempt to get color depth without initialization
    dsColorDepth_t colorDepth;
    status = dsGetPreferredColorDepth(invalidHandle, &colorDepth);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Get color depth with invalid handle
    status = dsGetPreferredColorDepth(invalidHandle, &colorDepth);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get the port handle for supported video ports
    dsVideoPortHandle_t validHandle;
    status = dsGetVideoPort(/* valid type and index */, &validHandle);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 05: Get color depth with invalid pointer
    status = dsGetPreferredColorDepth(validHandle, NULL);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 07: Attempt to get color depth after termination
    status = dsGetPreferredColorDepth(validHandle, &colorDepth);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


/**
 * @brief Positive Test Scenarios for dsSetPreferredColorDepth()
 * 
 * **Test Group ID:** Basic: 120@p
 * **Test Case ID:** 120@p
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsSetPreferredColorDepth() by looping through the acquired handles and Valid colorDepth values|handle=[invalid handle] , colorDepth=[valid values] |dsERR_NONE|Color depth must be set successfully|
 * |05|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsSetPreferredColorDepth(void) {
    dsError_t status;

    // Step 01: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 02: Get the port handle for supported video ports
    for (int i = 0; i < kPortsLength; i++) {
        dsVideoPortHandle_t handle;
        status = dsGetVideoPort(kPorts[i], &handle);
        UT_ASSERT_EQUAL(status, dsERR_NONE);

        // Step 03: Set preferred color depth
        dsColorDepth_t validColorDepth = /* Define valid color depth */;
        status = dsSetPreferredColorDepth(handle, validColorDepth);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }

    // Step 05: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


/**
 * @brief Negative Test Scenarios for dsSetPreferredColorDepth()
 * 
 * **Test Group ID:** Basic: 120@n
 * **Test Case ID:** 120@n
 * 
 * **Pre-Conditions:** None@n
 * 
 * **Dependencies:** None@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsSetPreferredColorDepth() without prior initialization of video ports|handle=[invalid handle] , colorDepth=[valid values]|dsERR_NOT_INITIALIZED|call must fail as module not initialized|
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetPreferredColorDepth() with an invalid handle with valid color depth values|handle=[Invalid handle],colorDepth=[valid values]|dsERR_INVALID_PARAM|Invalid parameter must be return|
 * |04|Call dsGetVideoPort() Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsSetPreferredColorDepth() by looping through valid handles  with an unsupported colorDepth value|handle=[valid handle],colorDepth=[invalid values]|dsERR_OPERATION_NOT_SUPPORTED|Invalid parameter must be return|
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsSetPreferredColorDepth() after terminating video ports|handle=[valid handle] , colorDepth=[valid values]|dsERR_NOT_INITIALIZED|call must fail as module not initialized|
 * 
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenarios.
 */
void test_l1_dsVideoPort_negative_dsSetPreferredColorDepth(void) {
    dsError_t status;

    // Step 01: Attempt to set color depth without initialization
    dsColorDepth_t validColorDepth = /* Define valid color depth */;
    status = dsSetPreferredColorDepth(invalidHandle, validColorDepth);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize video port system
    status = dsVideoPortInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 03: Set color depth with invalid handle
    status = dsSetPreferredColorDepth(invalidHandle, validColorDepth);
    UT_ASSERT_EQUAL(status, dsERR_INVALID_PARAM);

    // Step 04: Get the port handle for supported video ports
    dsVideoPortHandle_t validHandle;
    status = dsGetVideoPort(/* valid type and index */, &validHandle);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 05: Set unsupported color depth
    dsColorDepth_t unsupportedColorDepth = /* Define unsupported color depth */;
    status = dsSetPreferredColorDepth(validHandle, unsupportedColorDepth);
    UT_ASSERT_EQUAL(status, dsERR_OPERATION_NOT_SUPPORTED);

    // Step 06: Terminate the video port system
    status = dsVideoPortTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    // Step 07: Attempt to set color depth after termination
    status = dsSetPreferredColorDepth(validHandle, validColorDepth);
    UT_ASSERT_EQUAL(status, dsERR_NOT_INITIALIZED);
}


static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main test(s) for this module
 *
 * @return int - 0 on success, otherwise failure
 */
int test_l1_dsVideoPort_register ( void )
{
	/* add a suite to the registry */
	pSuite = UT_add_suite( "[L1 dsVideoPort]", NULL, NULL );
	if ( NULL == pSuite )
	{
		return -1;
	}	

	UT_add_test( pSuite, "dsVideoPortInit_L1_positive" ,test_l1_dsVideoPort_positive_dsVideoPortInit );
	UT_add_test( pSuite, "dsVideoPortInit_L1_negative" ,test_l1_dsVideoPort_negative_dsVideoPortInit );
	UT_add_test( pSuite, "dsVideoPortTerm_L1_positive" ,test_l1_dsVideoPort_positive_dsVideoPortTerm );
	UT_add_test( pSuite, "dsVideoPortTerm_L1_negative" ,test_l1_dsVideoPort_negative_dsVideoPortTerm );
	UT_add_test( pSuite, "dsGetVideoPort_L1_positive" ,test_l1_dsVideoPort_positive_dsGetVideoPort );
	UT_add_test( pSuite, "dsGetVideoPort_L1_negative" ,test_l1_dsVideoPort_negative_dsGetVideoPort );
	UT_add_test( pSuite, "dsIsVideoPortEnabled_L1_positive" ,test_l1_dsVideoPort_positive_dsIsVideoPortEnabled );
	UT_add_test( pSuite, "dsIsVideoPortEnabled_L1_negative" ,test_l1_dsVideoPort_negative_dsIsVideoPortEnabled );
	UT_add_test( pSuite, "dsIsDisplayConnected_L1_positive" ,test_l1_dsVideoPort_positive_dsIsDisplayConnected );
	UT_add_test( pSuite, "dsIsDisplayConnected_L1_negative" ,test_l1_dsVideoPort_negative_dsIsDisplayConnected );
	UT_add_test( pSuite, "dsIsDisplaySurround_L1_positive" ,test_l1_dsVideoPort_positive_dsIsDisplaySurround );
	UT_add_test( pSuite, "dsIsDisplaySurround_L1_negative" ,test_l1_dsVideoPort_negative_dsIsDisplaySurround );
	UT_add_test( pSuite, "dsGetSurroundMode_L1_positive" ,test_l1_dsVideoPort_positive_dsGetSurroundMode );
	UT_add_test( pSuite, "dsGetSurroundMode_L1_negative" ,test_l1_dsVideoPort_negative_dsGetSurroundMode );
	UT_add_test( pSuite, "dsVideoFormatUpdateRegisterCB_L1_positive" ,test_l1_dsVideoPort_positive_dsVideoFormatUpdateRegisterCB );
	UT_add_test( pSuite, "dsVideoFormatUpdateRegisterCB_L1_negative" ,test_l1_dsVideoPort_negative_dsVideoFormatUpdateRegisterCB );
	UT_add_test( pSuite, "dsIsVideoPortActive_L1_positive" ,test_l1_dsVideoPort_positive_dsIsVideoPortActive );
	UT_add_test( pSuite, "dsIsVideoPortActive_L1_negative" ,test_l1_dsVideoPort_negative_dsIsVideoPortActive );
	UT_add_test( pSuite, "dsEnableDTCP_L1_positive" ,test_l1_dsVideoPort_positive_dsEnableDTCP );
	UT_add_test( pSuite, "dsEnableDTCP_L1_negative" ,test_l1_dsVideoPort_negative_dsEnableDTCP );
	UT_add_test( pSuite, "dsEnableHDCP_L1_positive" ,test_l1_dsVideoPort_positive_dsEnableHDCP );
	UT_add_test( pSuite, "dsEnableHDCP_L1_negative" ,test_l1_dsVideoPort_negative_dsEnableHDCP );
	UT_add_test( pSuite, "dsIsDTCPEnabled_L1_positive" ,test_l1_dsVideoPort_positive_dsIsDTCPEnabled );
	UT_add_test( pSuite, "dsIsDTCPEnabled_L1_negative" ,test_l1_dsVideoPort_negative_dsIsDTCPEnabled );
	UT_add_test( pSuite, "dsIsHDCPEnabled_L1_positive" ,test_l1_dsVideoPort_positive_dsIsHDCPEnabled );
	UT_add_test( pSuite, "dsIsHDCPEnabled_L1_negative" ,test_l1_dsVideoPort_negative_dsIsHDCPEnabled );
	UT_add_test( pSuite, "dsEnableVideoPort_L1_positive" ,test_l1_dsVideoPort_positive_dsEnableVideoPort );
	UT_add_test( pSuite, "dsEnableVideoPort_L1_negative" ,test_l1_dsVideoPort_negative_dsEnableVideoPort );
	UT_add_test( pSuite, "dsSetResolution_L1_positive" ,test_l1_dsVideoPort_positive_dsSetResolution );
	UT_add_test( pSuite, "dsSetResolution_L1_negative" ,test_l1_dsVideoPort_negative_dsSetResolution );
	UT_add_test( pSuite, "dsGetResolution_L1_positive" ,test_l1_dsVideoPort_positive_dsGetResolution );
	UT_add_test( pSuite, "dsGetResolution_L1_negative" ,test_l1_dsVideoPort_negative_dsGetResolution );
	UT_add_test( pSuite, "dsSetActiveSource_L1_positive" ,test_l1_dsVideoPort_positive_dsSetActiveSource );
	UT_add_test( pSuite, "dsSetActiveSource_L1_negative" ,test_l1_dsVideoPort_negative_dsSetActiveSource );
	UT_add_test( pSuite, "dsRegisterHdcpStatusCallback_L1_positive" ,test_l1_dsVideoPort_positive_dsRegisterHdcpStatusCallback );
	UT_add_test( pSuite, "dsRegisterHdcpStatusCallback_L1_negative" ,test_l1_dsVideoPort_negative_dsRegisterHdcpStatusCallback );
	UT_add_test( pSuite, "dsGetHDCPStatus_L1_positive" ,test_l1_dsVideoPort_positive_dsGetHDCPStatus );
	UT_add_test( pSuite, "dsGetHDCPStatus_L1_negative" ,test_l1_dsVideoPort_negative_dsGetHDCPStatus );
	UT_add_test( pSuite, "dsGetHDCPProtocol_L1_positive" ,test_l1_dsVideoPort_positive_dsGetHDCPProtocol );
	UT_add_test( pSuite, "dsGetHDCPProtocol_L1_negative" ,test_l1_dsVideoPort_negative_dsGetHDCPProtocol );
	UT_add_test( pSuite, "dsGetHDCPReceiverProtocol_L1_positive" ,test_l1_dsVideoPort_positive_dsGetHDCPReceiverProtocol );
	UT_add_test( pSuite, "dsGetHDCPReceiverProtocol_L1_negative" ,test_l1_dsVideoPort_negative_dsGetHDCPReceiverProtocol );
	UT_add_test( pSuite, "dsGetHDCPCurrentProtocol_L1_positive" ,test_l1_dsVideoPort_positive_dsGetHDCPCurrentProtocol );
	UT_add_test( pSuite, "dsGetHDCPCurrentProtocol_L1_negative" ,test_l1_dsVideoPort_negative_dsGetHDCPCurrentProtocol );
	UT_add_test( pSuite, "dsGetTVHDRCapabilities_L1_positive" ,test_l1_dsVideoPort_positive_dsGetTVHDRCapabilities );
	UT_add_test( pSuite, "dsGetTVHDRCapabilities_L1_negative" ,test_l1_dsVideoPort_negative_dsGetTVHDRCapabilities );
	UT_add_test( pSuite, "dsSupportedTvResolutions_L1_positive" ,test_l1_dsVideoPort_positive_dsSupportedTvResolutions );
	UT_add_test( pSuite, "dsSupportedTvResolutions_L1_negative" ,test_l1_dsVideoPort_negative_dsSupportedTvResolutions );
	UT_add_test( pSuite, "dsSetForceDisable4KSupport_L1_positive" ,test_l1_dsVideoPort_positive_dsSetForceDisable4KSupport );
	UT_add_test( pSuite, "dsSetForceDisable4KSupport_L1_negative" ,test_l1_dsVideoPort_negative_dsSetForceDisable4KSupport );
	UT_add_test( pSuite, "dsGetForceDisable4KSupport_L1_positive" ,test_l1_dsVideoPort_positive_dsGetForceDisable4KSupport );
	UT_add_test( pSuite, "dsGetForceDisable4KSupport_L1_negative" ,test_l1_dsVideoPort_negative_dsGetForceDisable4KSupport );
	UT_add_test( pSuite, "dsGetVideoEOTF_L1_positive" ,test_l1_dsVideoPort_positive_dsGetVideoEOTF );
	UT_add_test( pSuite, "dsGetVideoEOTF_L1_negative" ,test_l1_dsVideoPort_negative_dsGetVideoEOTF );
	UT_add_test( pSuite, "dsGetMatrixCoefficients_L1_positive" ,test_l1_dsVideoPort_positive_dsGetMatrixCoefficients );
	UT_add_test( pSuite, "dsGetMatrixCoefficients_L1_negative" ,test_l1_dsVideoPort_negative_dsGetMatrixCoefficients );
	UT_add_test( pSuite, "dsGetColorDepth_L1_positive" ,test_l1_dsVideoPort_positive_dsGetColorDepth );
	UT_add_test( pSuite, "dsGetColorDepth_L1_negative" ,test_l1_dsVideoPort_negative_dsGetColorDepth );
	UT_add_test( pSuite, "dsGetColorSpace_L1_positive" ,test_l1_dsVideoPort_positive_dsGetColorSpace );
	UT_add_test( pSuite, "dsGetColorSpace_L1_negative" ,test_l1_dsVideoPort_negative_dsGetColorSpace );
	UT_add_test( pSuite, "dsGetQuantizationRange_L1_positive" ,test_l1_dsVideoPort_positive_dsGetQuantizationRange );
	UT_add_test( pSuite, "dsGetQuantizationRange_L1_negative" ,test_l1_dsVideoPort_negative_dsGetQuantizationRange );
	UT_add_test( pSuite, "dsGetCurrentOutputSettings_L1_positive" ,test_l1_dsVideoPort_positive_dsGetCurrentOutputSettings );
	UT_add_test( pSuite, "dsGetCurrentOutputSettings_L1_negative" ,test_l1_dsVideoPort_negative_dsGetCurrentOutputSettings );
	UT_add_test( pSuite, "dsIsOutputHDR_L1_positive" ,test_l1_dsVideoPort_positive_dsIsOutputHDR );
	UT_add_test( pSuite, "dsIsOutputHDR_L1_negative" ,test_l1_dsVideoPort_negative_dsIsOutputHDR );
	UT_add_test( pSuite, "dsResetOutputToSDR_L1_positive" ,test_l1_dsVideoPort_positive_dsResetOutputToSDR );
	UT_add_test( pSuite, "dsResetOutputToSDR_L1_negative" ,test_l1_dsVideoPort_negative_dsResetOutputToSDR );
	UT_add_test( pSuite, "dsSetHdmiPreference_L1_positive" ,test_l1_dsVideoPort_positive_dsSetHdmiPreference );
	UT_add_test( pSuite, "dsSetHdmiPreference_L1_negative" ,test_l1_dsVideoPort_negative_dsSetHdmiPreference );
	UT_add_test( pSuite, "dsGetHdmiPreference_L1_positive" ,test_l1_dsVideoPort_positive_dsGetHdmiPreference );
	UT_add_test( pSuite, "dsGetHdmiPreference_L1_negative" ,test_l1_dsVideoPort_negative_dsGetHdmiPreference );
	UT_add_test( pSuite, "dsGetIgnoreEDIDStatus_L1_positive" ,test_l1_dsVideoPort_positive_dsGetIgnoreEDIDStatus );
	UT_add_test( pSuite, "dsGetIgnoreEDIDStatus_L1_negative" ,test_l1_dsVideoPort_negative_dsGetIgnoreEDIDStatus );
	UT_add_test( pSuite, "dsSetBackgroundColor_L1_positive" ,test_l1_dsVideoPort_positive_dsSetBackgroundColor );
	UT_add_test( pSuite, "dsSetBackgroundColor_L1_negative" ,test_l1_dsVideoPort_negative_dsSetBackgroundColor );
	UT_add_test( pSuite, "dsSetForceHDRMode_L1_positive" ,test_l1_dsVideoPort_positive_dsSetForceHDRMode );
	UT_add_test( pSuite, "dsSetForceHDRMode_L1_negative" ,test_l1_dsVideoPort_negative_dsSetForceHDRMode );
	UT_add_test( pSuite, "dsColorDepthCapabilities_L1_positive" ,test_l1_dsVideoPort_positive_dsColorDepthCapabilities );
	UT_add_test( pSuite, "dsColorDepthCapabilities_L1_negative" ,test_l1_dsVideoPort_negative_dsColorDepthCapabilities );
	UT_add_test( pSuite, "dsGetPreferredColorDepth_L1_positive" ,test_l1_dsVideoPort_positive_dsGetPreferredColorDepth );
	UT_add_test( pSuite, "dsGetPreferredColorDepth_L1_negative" ,test_l1_dsVideoPort_negative_dsGetPreferredColorDepth );
	UT_add_test( pSuite, "dsSetPreferredColorDepth_L1_positive" ,test_l1_dsVideoPort_positive_dsSetPreferredColorDepth );
	UT_add_test( pSuite, "dsSetPreferredColorDepth_L1_negative" ,test_l1_dsVideoPort_negative_dsSetPreferredColorDepth );
	

	return 0;
} 

/** @} */ // End of DS HAL Video Port L1 tests
/** @} */ // End of DS Video Port HALTEST
/** @} */ // End of Device Settings HAL
/** @} */ // End of Device Settings Module
/** @} */ // End of HPK
