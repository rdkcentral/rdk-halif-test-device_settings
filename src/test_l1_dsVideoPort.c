/**
*  If not stated otherwise in this file or this component's Licenses.txt
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize the video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |03|Call dsVideoPortInit() - Reinitialize the video port system | | dsERR_NONE | Make sure that the video ports can be reinitialized after termination |
 * |04|Call dsVideoPortTerm() - Re-terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsVideoPortInit (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize the video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsVideoPortInit() - Attempt to initialize again without terminating the first initialization | | dsERR_ALREADY_INITIALIZED | Initialization must fail as it is already initialized |
 * |03|Call dsVideoPortTerm()  - Terminate video port system | | dsERR_NONE | Termination must be successful |
 * 
 * **Additional Notes:**@n
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsVideoPortInit (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsVideoPortTerm() - Terminate video port system | | dsERR_NONE | Termination must be successful |
 * |03|Call dsVideoPortInit() - Reinitialize video port system | | dsERR_NONE | Initialization must be successful |
 * |04|Call dsVideoPortTerm() - Re-terminate video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsVideoPortTerm (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortTerm() - Attempt to terminate the video port without prior initialization | | dsERR_NOT_INITIALIZED | Termination must fail as video port is not initialized |
 * |02|Call dsVideoPortInit() - Initialize the video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |04|Call dsVideoPortTerm() - Attempt to terminate the video port again after termination | | dsERR_NOT_INITIALIZED | Termination must fail as video port is not initialized |
 * 
 * **Additional Notes:**@n
 * - Simulating the system in such a way to get `dsERR_GENERAL` from dsVideoPortTerm() might be challenging, as it relates to an undefined platform error.
 */
void test_l1_dsVideoPort_negative_dsVideoPortTerm (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Get the video port handle for last element , store it in a new variable and compare it with previous step | | dsERR_NONE | Port handle obtained from previous step must be equal to handle obtained in this step
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsGetVideoPort (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetVideoPort() - Attempt to get the Video Port handle without initializing video ports | `type`,`index`= kPorts[0], `handle`= valid handle | dsERR_NOT_INITIALIZED | Get Video Port Handle must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetVideoPort() - by looping through valid port indexes but with invalid type  | type = [not in kPorts] , index = [ loop through kPorts ], handle = [ valid handle ] | dsERR_OPERATION_NOT_SUPPORTED | Operation not supported error must be returned |
 * |04|Call dsGetVideoPort() - by looping through valid types but with invalid index | type = [loop through types in kPorts], index = [ invalid index which is not in kPorts ], handle: [ valid handle ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |05|Call dsGetVideoPort() - by looping through valid types and index but with a NULL handle | type, index: [ loop through kPorts ], handle: [ NULL pointer ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetVideoPort() - Attempt to get the video port handle again after termination | type, index:  [ loop through kPorts ], handle: [ valid handle ] | dsERR_NOT_INITIALIZED | Get Video Port Handle must fail as module is not initialized |
 * 
 * **Additional Notes:**@n
 * - Ensure to reset the system to its initial state after each test.
 * - Simulating the system in such a way to get `dsERR_GENERAL` from dsGetVideoPort() might be challenging, as it relates to an undefined platform error.
 */
void test_l1_dsVideoPort_negative_dsGetVideoPort (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |03|Call dsIsVideoPortEnabled - by looping through the acquired port handles to check if a video port is enabled or not | handle: [valid handle], enabled: [pointer to hold the enabled/disabled status of video port] | dsERR_NONE | Flag which holds the enabled status of Video Port must be returned |
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsIsVideoPortEnabled (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsIsVideoPortEnabled() - Attempt to check if video port is enabled or not without initializing video ports | handle: [ valid handle ], connected: [ pointer to hold enabled status]| dsERR_NOT_INITIALIZED | Call to check if video port is enabled or not must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsIsVideoPortEnabled() using an invalid handle but with a valid pointer to hold the enabled status | handle: [ invalid handle ], enabled: [ pointer to hold enabled status] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |05|Call dsIsVideoPortEnabled() by looping through acquired port handles but with a null pointer for enabled status | handle: [ loop through valid handles ], enabled: [ NULL ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsIsVideoPortEnabled() - Attempt to check if video port is enabled or not without initializing video ports| handle: [ valid handle ], connected: [ pointer to hold enabled status] | dsERR_NOT_INITIALIZED | Call to check if video port is enabled or not must fail as module is not initialized |
 * 
 * **Additional Notes:**@n
 * - The test should be careful while handling null pointers and invalid handles.
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsIsVideoPortEnabled (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsIsDisplayConnected() - by looping through the acquired port handles to check if video port is connected to a display or not | handle: [ loop through valid handles ] , connected: [pointer to hold the connection status of Video Port] | dsERR_NONE | Flag which holds the connection status of Video Port must be returned |
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsIsDisplayConnected (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsIsDisplayConnected() - Attempt to check if video port is connected without initializing video ports | handle: [ valid handle ], connected: [ pointer to hold connection status] | dsERR_NOT_INITIALIZED | Call to check if display is connected to video port must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsIsDisplayConnected() using an invalid handle but with a valid pointer to hold the connection status | handle: [ invalid handle ], connected: [ pointer to hold connection status] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |05|Call dsIsDisplayConnected() by looping through acquired port handles but with a null pointer for display connection | handle: [ loop through valid handles ], connected: [ NULL ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsIsDisplayConnected() - Attempt to check if video port is connected without initializing video ports|  handle: [ valid handle ], connected: [ pointer to hold connection status] | dsERR_NOT_INITIALIZED | Call to check if display is connected to video port must fail as module is not initialized |
 * 
 * **Additional Notes:**@n
 * - The test should be careful while handling null pointers and invalid handles.
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsIsDisplayConnected (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsIsDisplaySurround() - by looping through the acquired port handles to check if display connected to video port supports the audio surround | handle: [ loop through valid handles ] , surround: [pointer to hold the audio surround support] | dsERR_NONE | Audio surround support of Video Port must be returned |
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsIsDisplaySurround (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsIsDisplaySurround() - Attempt to check if display connected to video port has surround support without initializing video ports | handle: [ valid handle ], , surround: [ pointer to hold Audio surround support] | dsERR_NOT_INITIALIZED | Call to check if display connected to video port has surround support must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsIsDisplaySurround() using an invalid handle but with a valid pointer to hold the surround support | handle: [ invalid handle ], surround: [ pointer to hold Audio surround support] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |05|Call dsIsDisplaySurround() by looping through acquired port handles but with a null pointer for audio surround | handle: [ loop through valid handles ], surround: [ NULL ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsIsDisplayConnected() - Attempt to check if display connected to video port has surround support without initializing video ports | handle: [ valid handle ], , surround: [ pointer to hold Audio surround support] | dsERR_NOT_INITIALIZED | Call to check if display connected to video port has surround support must fail as module is not initialized |
 * 
 * **Additional Notes:**@n
 * - The test should be careful while handling null pointers and invalid handles.
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsIsDisplaySurround (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsGetSurroundMode() - by looping through the acquired port handles to get the surround mode of each video port | handle: [ loop through valid handles ] , surround: [pointer to hold the Surround mode] | dsERR_NONE | Surround mode (dsSURROUNDMode_t)of Video Port must be returned |
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsGetSurroundMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetSurroundMode() - Attempt to get the surround mode without initializing video ports | handle: [ valid handle ], surround: [pointer to hold the surround mode] | dsERR_NOT_INITIALIZED | Get surround mode of video ports must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetSurroundMode() using an invalid handle but with a valid pointer to hold the surround mode | handle: [ invalid handle ], surround: [ pointer to hold surround mode] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |05|Call dsGetSurroundMode() by looping through acquired port handles but with a null pointer for surround mode | handle: [ loop through valid handles ], surround: [ NULL ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetSurroundMode() - Attempt to get the surround mode without initializing video ports | handle: [ valid handle ], surround: [pointer to hold the surround mode] | dsERR_NOT_INITIALIZED | Get surround mode of video ports must fail as module is not initialized |
 * 
 * **Additional Notes:**@n
 * - Handle validation and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsGetSurroundMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsIsVideoPortActive() - by looping through the acquired port handles to check whether a video port is active or not for each port | handle: [ loop through valid handles ] , active: [pointer to hold the active status] | dsERR_NONE | Active Status(A Video port is active if it is connected to the active port of sink device) of Video Port must be returned |
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsIsVideoPortActive (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsIsVideoPortActive() - Attempt to check whether a video port is active or not without initializing video ports |  handle: [ valid handle ], active: [pointer to hold the active status of video port] | dsERR_NOT_INITIALIZED | Call to check if video port is active or not must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsIsVideoPortActive() using an invalid handle but with a valid pointer to hold the active status | handle: [ invalid handle ], active: [ pointer to hold active status] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |05|Call dsIsVideoPortActive() by looping through acquired port handles but with a null pointer for active status | handle: [ loop through valid handles ], active: [ NULL ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsIsVideoPortActive() - Attempt to check whether a video port is active or not without initializing video ports | handle: [ valid handle ], active: [pointer to hold the active status of video port] | dsERR_NOT_INITIALIZED | Call to check if video port is active or not must fail as module is not initialized |
 * 
 * **Additional Notes:**@n
 * - Handle validation and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsIsVideoPortActive (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsEnableDTCP() by looping through the acquired port handles to enable DTCP for each port | handle: [ loop through valid handles ] , contentProtect: [1] (enable DTCP) |dsERR_NONE or dsERR_OPERATION_NOT_SUPPORTED| API should either successfully enable DTCP or indicate that the operation isn't supported if the particular video does not have DTCP support|
 * |04|Call dsIsDTCPEnabled() - by looping through the acquired port handles to check if DTCP is enabled (ports which support DTCP)|handle: [ loop through valid handles ], pContentProtected: [ pointer to hold DTCP status ]| dsERR_NONE | DTCP must be enabled |
 * |05|Call dsEnableDTCP() by looping through the acquired port handles to disable DTCP for each port | handle: [ loop through valid handles ] , contentProtect: [0] (disable DTCP) |dsERR_NONE or dsERR_OPERATION_NOT_SUPPORTED| API should either successfully disable DTCP or indicate that the operation isn't supported if the particular video does not have DTCP support|
 * |06|Call dsIsDTCPEnabled() - by looping through the acquired port handles to check if DTCP is disabled (ports which support DTCP)|handle: [ loop through valid handles ], pContentProtected: [ pointer to hold DTCP status ]| dsERR_NONE | DTCP must be disabled |
 * |08|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsEnableDTCP (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsEnableDTCP() - Attempt to enable DTCP without initializing the video ports | handle: [ valid handle ], contentProtect: [true = enable DTCP/ false = disable DTCP] | dsERR_NOT_INITIALIZED | Enable DTCP must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsEnableDTCP() using an invalid handle but with a valid DTCP Flag(enable = 1/ disable = 0) | handle: [ invalid handle ], contentProtect: [ Flag to enable/disable DTCP] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |05|Call dsEnableDTCP() Attempt to enable DTCP without initializing the video ports | handle: [ valid handle ], contentProtect: [true = enable DTCP/ false = disable DTCP] | dsERR_NOT_INITIALIZED | Enable DTCP must fail as module is not initialized |
 * 
 * **Additional Notes:**@n
 * - Handle validation and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsEnableDTCP (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsEnableHDCP() by looping through the acquired port handles to enable HDCP for each port | handle: [ loop through valid handles ] , contentProtect: [1] (enable HDCP), hdcpKey: [ HDCP key ], keySize: [HDCP key size]|dsERR_NONE or dsERR_OPERATION_NOT_SUPPORTED| API should either successfully enable HDCP or indicate that the operation isn't supported if the particular video does not have HDCP support|
 * |04|Call dsIsHDCPEnabled() - by looping through the acquired port handles to check if HDCP is enabled (ports which support DTCP)|handle: [ loop through valid handles ], pContentProtected: [ pointer to hold DTCP status ]| dsERR_NONE | DTCP must be enabled |
 * |05|Call dsEnableHDCP() by looping through the acquired port handles to disable HDCP for each port | handle: [ loop through valid handles ] , contentProtect: [0] (disable HDCP) |dsERR_NONE or dsERR_OPERATION_NOT_SUPPORTED| API should either successfully disable HDCP or indicate that the operation isn't supported if the particular video does not have HDCP support|
 * |06|Call dsIsHDCPEnabled() - by looping through the acquired port handles to check if HDCP is disabled (ports which support HDCP)|handle: [ loop through valid handles ], pContentProtected: [ pointer to hold HDCP status ]| dsERR_NONE | HDCP must be disabled |
 * |08|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsEnableHDCP (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsEnableHDCP() - Attempt to enable DTCP without initializing the video ports | handle: [ valid handle ], contentProtect: [true = enable/ false = disable], hdcpKey: [valid hdcp key], keySize: [valid key size]| dsERR_NOT_INITIALIZED | Enable HDCP must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsEnableHDCP() - Attempt to enable HDCP with an invalid handle |handle: [ invalid handle ], contentProtect: [true = enable/ false = disable], hdcpKey: [valid hdcp key], keySize: [valid key size (HDCP_KEY_MAX_SIZE)]| dsERR_INVALID_PARAM | Invalid Parameter error must be returned |
 * |04|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |05|Call dsEnableHDCP() by looping through acquired port handles with an invalid HDCP key size |handle: [ valid handle ], contentProtect: [true = enable/ false = disable], hdcpKey: [valid hdcp key], keySize: [valid key size (> HDCP_KEY_MAX_SIZE)| dsERR_INVALID_PARAM | Invalid Parameter error must be returned |
 * |05|Call dsEnableHDCP() by looping through acquired port handles with an NULL hdcpKey pointer |handle: [ valid handle ], contentProtect: [true = enable/ false = disable], hdcpKey: [NULL], keySize: [valid key size (> HDCP_KEY_MAX_SIZE)| dsERR_INVALID_PARAM | Invalid Parameter error must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsEnableHDCP() Attempt to enable DTCP without initializing the video ports | handle: [ valid handle ], contentProtect: [true = enable/ false = disable], hdcpKey: [valid hdcp key], keySize: [valid key size] | dsERR_NOT_INITIALIZED | Enable HDCP must fail as module is not initialized |
 * 
 * **Additional Notes:**@n
 * - Handle validation, module initialization checks, and key size validation are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsEnableHDCP (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video ports of a system | |dsERR_NONE| Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports|
 * |03|Call dsIsDTCPEnabled() by looping through the acquired port handles  and valid pointer to check whether DTCP enabled or not(.ie TRUE / FALSE) | handle : [loop through valid handles] , pContentProtected = [pointer to hold data ]|dsERR_NONE |dsIsDTCPEnabled should return a valid value|
 * |04|Call dsVideoPortTerm() - Terminate the video ports of a system| |dsERR_NONE|Termination must be successful|
 *
 */
void test_l1_dsVideoPort_positive_dsIsDTCPEnabled (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsIsDTCPEnabled() - Attempt to get the DTCP status with out initializing video ports| handle [valid handle] , pContentProtected = [valid pointer]|dsERR_NOT_INITIALIZED| dsIsDTCPEnabled call should fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video ports of a system | |dsERR_NONE| Initialization must be successful |
 * |03|Call dsIsDTCPEnabled() - Using an invalid handle but with valid pointer | handle = [invalid handle], pContentProtected = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort()  - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsIsDTCPEnabled() By looping through acquired port handles but with a invalid pointer | handle = [valid handle], pContentProtected = [invalid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video ports of a system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsIsDTCPEnabled() - Again after terminating video ports attempt to get DTCP status | handle= [valid handle from step 04 ] , pContentProtected = [valid pointer] | dsERR_NOT_INITIALIZED | dsIsDTCPEnabled call should fail as module is not initialized |
 *
 * **Additional Notes:**@n
 * - Handle validation and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsIsDTCPEnabled (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video ports of a system | |dsERR_NONE| Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports|
 * |03|Call dsIsHDCPEnabled() by looping through the acquired port handles  and checks whether HDCP enabled or not(.ie TRUE / FALSE) | handle : [loop through valid handles] , pContentProtected = [pointer to hold data ] | dsERR_NONE | dsIsHDCPEnabled should return a valid value|
 * |04|Call dsVideoPortTerm() - Terminate the video ports of a system| |dsERR_NONE|Termination must be successful|
 * 
 */
void test_l1_dsVideoPort_positive_dsIsHDCPEnabled (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsIsHDCPEnabled() - Attempt to get the HDCP status with out initializing video ports| handle [valid handle] , pContentProtected = [valid pointer]|dsERR_NOT_INITIALIZED| dsIsHDCPEnabled call should fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video ports of a system | |dsERR_NONE| Initialization must be successful |
 * |03|Call dsIsHDCPEnabled() - Using an invalid handle but with valid pointer | handle = [invalid handle], pContentProtected = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort()  - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsIsHDCPEnabled() - By looping through acquired port handles but with a invalid pointer | handle = [valid handle], pContentProtected = [invalid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video ports of a system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsIsHDCPEnabled() - Again after terminating video ports attempt to get HDCP status | handle= [valid handle from step 04 ] , pContentProtected = [valid pointer] | dsERR_NOT_INITIALIZED | dsIsHDCPEnabled call should fail as module is not initialized |
 *
 * **Additional Notes:**@n
 * - Handle validation and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsIsHDCPEnabled (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video ports of a system | |dsERR_NONE| Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] | dsERR_NONE | Valid port handle must be returned for all supported video ports|
 * |03|Call dsEnableVideoPort() by looping through the acquired port handles and valid enabled parameter value (i.e TRUE/FALSE) to enable or disable a video port | handle  = [loop through valid handles] , enabled = [valid bool value] | dsERR_NONE | dsEnableVideoPort should return a valid value|
 * |04|Call dsVideoPortTerm() - Terminate the video ports of a system| |dsERR_NONE|Termination must be successful|
 * 
 */
void test_l1_dsVideoPort_positive_dsEnableVideoPort (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsEnableVideoPort() - Attempt to enable or disable video port  with out initializing video ports| handle [valid handle] , enabled = [valid bool value]| dsERR_NOT_INITIALIZED| dsEnableVideoPort call should fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video ports of a system | |dsERR_NONE| Initialization must be successful |
 * |03|Call dsEnableVideoPort() - Using an invalid handle but with valid enabled value(i.e TRUE/FALSE) | handle = [invalid handle], enabled = [valid bool value] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort()  - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsVideoPortTerm() - Terminate the video ports of a system | | dsERR_NONE | Termination must be successful |
 * |06|Call dsEnableVideoPort() - Again after terminating video ports attempt to enable or disable video port | handle = [valid handle from step 04 ] , enabled = [valid bool value] | dsERR_NOT_INITIALIZED | dsEnableVideoPort call should fail as module is not initialized |
 * 
 * **Additional Notes:**@n
 * - Handle validation and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsEnableVideoPort (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video ports of a system | |dsERR_NONE| Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports|
 * |03|Call dsGetVideoPort() by looping through the acquired port handles and valid resolution pointer to Set the video port resolution |handle  = [loop through valid handles] , resolution = [valid pointer]|dsERR_NONE|Resolution should be set successfully|
 * |04|Call dsVideoPortTerm() - Terminate the video ports of a system| |dsERR_NONE|Termination must be successful|
 * 
 */
void test_l1_dsVideoPort_positive_dsSetResolution (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsSetResolution() - Attempt to set the resolution with out initializing video ports| handle = [valid handle] , resolution = [valid pointer]| dsERR_NOT_INITIALIZED| dsSetResolution call should fail as module is not initialized |
 * |02|dsVideoPortInit() - Initialize video ports of a system | |dsERR_NONE| Initialization must be successful |
 * |03|Call dsSetResolution() - Using an invalid handle but with valid resolution pointer | handle = [invalid handle], resolution = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsSetResolution() - By looping through acquired port handles but with a invalid pointer | handle = [valid handle], resolution = [invalid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video ports of a system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsSetResolution() - Again after terminating video ports attempt to set the resolution | handle= [valid handle from step 04 ] , resolution = [valid pointer] | dsERR_NOT_INITIALIZED | dsSetResolution call should fail as module is not initialized |
 * 
 * **Additional Notes:**@n
 * - Handle validation and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsSetResolution (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video ports of a system | |dsERR_NONE| Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports|
 * |03|Call dsGetResolution() by looping through the acquired port handles and valid resolution pointer to retrieve the resolution of a video port | handle  = [loop through valid handles] , resolution = [valid pointer] |dsERR_NONE|Resolution should be set successfully|
 * |06|Call dsVideoPortTerm() - Terminate the video ports of a system| |dsERR_NONE|Termination must be successful|
 * 
 */
void test_l1_dsVideoPort_positive_dsGetResolution (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetResolution() - Attempt to get the resolution without initializing video ports| handle = [valid handle] , resolution = [valid pointer]| dsERR_NOT_INITIALIZED| Get Resolution call must fail as module is not initialized |
 * |02|dsVideoPortInit() - Initialize video ports of a system | |dsERR_NONE| Initialization must be successful |
 * |03|Call dsGetResolution() - Using an invalid handle but with valid resolution pointer | handle = [invalid handle], resolution = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |04|Call dsGetResolution() - By looping through acquired port handles but with a invalid pointer | handle = [valid handle], resolution = [invalid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |05|Call dsVideoPortTerm() - Terminate the video ports of a system | | dsERR_NONE | Termination must be successful |
 * |06|Call dsGetResolution() - Again after terminating video ports attempt to get the resolution of video ports | handle = [valid handle] , resolution = [valid pointer] | dsERR_NOT_INITIALIZED | Get Resolution call must fail as module is not initialized |
 * 
 * **Additional Notes:**@n
 * - Handle validation and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsGetResolution (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video ports of a system | |dsERR_NONE| Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports|
 * |03|Call dsSetActiveSource() by looping through the acquired port handles and set the video port as active source | handle  = [loop through valid handles] |dsERR_NONE|The video port should be set as the active source successfully|
 * |04|dsVideoPortTerm() - Terminate the video ports of a system| |dsERR_NONE|Termination must be successful|
 * 
 */
void test_l1_dsVideoPort_positive_dsSetActiveSource (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsSetActiveSource() - Attempt to set the active source with out initializing video ports| handle =  [valid handle] | dsERR_NOT_INITIALIZED| dsSetActiveSource call should fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video ports of a system | |dsERR_NONE| Initialization must be successful |
 * |03|Call dsSetActiveSource() - Using an invalid handle attempt to set active source | handle = [invalid handle] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort()  - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsVideoPortTerm() - Terminate the video ports of a system | | dsERR_NONE | Termination must be successful |
 * |06|Call dsSetActiveSource()  - Again after terminating video ports attempt to set the active source | handle= [valid handle from step 04 ] | dsERR_NOT_INITIALIZED | dsSetActiveSource call should fail as module is not initialized |
 * 
 * **Additional Notes:**@n
 * - Handle validation and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsSetActiveSource (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsVideoFormatUpdateRegisterCB() - Register a valid Video Format update callback | cb = [valid callback function] | dsERR_NONE | Video Format Update callback registration must be successful |
 * |03|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsVideoFormatUpdateRegisterCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoFormatUpdateRegisterCB() - Attempt to register for video format update callback without initializing the video ports | cb = [valid callback function ] | dsERR_NOT_INITIALIZED | Callback registration must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsVideoFormatUpdateRegisterCB() with an invalid callback (NULL)| cb = NULL | dsERR_INVALID_PARAM | Invalid paramter error must be returned |
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |05|Call dsVideoFormatUpdateRegisterCB() - Attempt to register for video format update callback without initializing the video ports | cb = [valid callback function ] | dsERR_NOT_INITIALIZED | Callback registration must fail as module is not initialized |
 * 
 * **Additional Notes:** None
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsVideoFormatUpdateRegisterCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsRegisterHdcpStatusCallback() - Register a valid HDCP status change callback |handle = [valid handle], cb = [Callback function] | dsERR_NONE | Callback must be registered successfully |
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsRegisterHdcpStatusCallback (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsRegisterHdcpStatusCallback() - Attempt to register HDCP status change callback without initializing the video ports | handle= [valid handle], cb = [valid callback function] | dsERR_NOT_INITIALIZED | Callback Registration for HDCP status change must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsRegisterHdcpStatusCallback() with an invalid handle but with a valid callback function as parameter | handle= [invalid handle], cb = [valid callback function] | dsERR_INVALID_PARAM | Invalid Parameter error must be returned |
 * |04|Call dsRegisterHdcpStatusCallback() with a valid handle and a NULL callback function | handle= [valid handle], cb = NULL | dsERR_INVALID_PARAM | Invalid Parameter error must be returned |
 * |05|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |06|Call dsRegisterHdcpStatusCallback() - Attempt to register HDCP status change callback without initializing the video ports | handle= [valid handle], cb = [valid callback function] | dsERR_NOT_INITIALIZED | Callback Registration for HDCP status change must fail as module is not initialized |
 * 
 * **Additional Notes:** None
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsRegisterHdcpStatusCallback (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsGetHDCPStatus() by looping through the acquired port handles and valid pointer to retrieve HDCP status | handle  = [valid handles] status = [valid pointer] | dsERR_NONE | The HDCP status should be successfully fetched and stored in the given pointer|
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsGetHDCPStatus (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetHDCPStatus() Attempt to get the HDCP status  with out initializing video ports| handle = [invalid handle] , status = [valid pointer]| dsERR_NOT_INITIALIZED| dsGetHDCPStatus call should fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetHDCPStatus() Using an invalid handle but with valid status pointer | handle = [invalid handle], status = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports|
 * |04|Call dsGetHDCPStatus() By looping through acquired port handles but with a invalid pointer | handle = [valid handle], status = [invalid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |05|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |06|Call dsGetHDCPStatus() Again after terminating video ports attempt to get the status of video ports | handle= [valid handle from step 04 ] , status = [valid pointer] | dsERR_NOT_INITIALIZED | dsGetHDCPStatus call should fail as module is not initialized |
 * 
 * **Additional Notes:**@n
 * - Handle validation , NULL pointer checks, and module initialization checks are crucial for the robustness of the API.
 * - Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsGetHDCPStatus (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsGetHDCPProtocol() by looping through the acquired suported port handles and valid pointer to retrieve the protocol version  of a video port |handle  = [valid handles] , protocolVersion = [valid pointer] |dsERR_NONE|The HDCP protocol version should be successfully fetched |
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsGetHDCPProtocol (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetHDCPProtocol()  Attempt to get the HDCP protocol version with out initializing video ports| handle = [invalid handle] , protocolVersion = [valid pointer]| dsERR_NOT_INITIALIZED| dsGetHDCPProtocol call should fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetHDCPProtocol() Using an invalid handle but with valid pointer | handle = [invalid handle], protocolVersion = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports|
 * |05|Call dsGetHDCPProtocol() By looping through acquired supported port handles but with a invalid pointer | handle = [valid handle], protocolVersion = [invalid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetHDCPProtocol() Again after terminating video ports attempt to get the HDCP protocol version of video ports | handle= [valid handle from step 04 ] , protocolVersion = [valid pointer] | dsERR_NOT_INITIALIZED | dsGetHDCPProtocol call should fail as module is not initialized |
 * 
 * **Additional Notes:**@n
 * - Handle validation, NULL pointer checks, and module initialization checks are crucial for the robustness of the API.
 * - @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsGetHDCPProtocol (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsGetHDCPReceiverProtocol() by looping through the acquired supported port handles and valid pointer to retrieve the sink device protocol version  of a video port |handle  = [loop through valid handles] , protocolVersion = [valid pointer] |dsERR_NONE|The Receiver HDCP protocol version should be successfully fetched and stored in the given pointer|
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsGetHDCPReceiverProtocol (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetHDCPReceiverProtocol()  Attempt to get the sink device HDCP protocol version of sink device with out initializing video ports| handle = [invalid handle] , protocolVersion = [valid pointer]| dsERR_NOT_INITIALIZED| dsGetHDCPReceiverProtocol call should fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetHDCPReceiverProtocol() Using an invalid handle but with valid pointer | handle = [invalid handle], protocolVersion = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports|
 * |05|Call dsGetHDCPReceiverProtocol() By looping through acquired supported port handles but with a invalid pointer | handle = [valid handle], protocolVersion = [invalid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetHDCPReceiverProtocol() Again after terminating video ports attempt to get the sink device HDCP protocol version of video ports | handle= [valid handle from step 04 ] , protocolVersion = [valid pointer] | dsERR_NOT_INITIALIZED | dsGetHDCPReceiverProtocol call should fail as module is not initialized |
 * 
 * **Additional Notes:**@n
 * - Handle validation, NULL pointer checks, and module initialization checks are crucial for the robustness of the API.
 * - @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsGetHDCPReceiverProtocol (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsGetHDCPCurrentProtocol() by looping through the acquired supported port handles and valid pointer to retrieve the current negotiated protocol version  of a video port |handle  = [valid handles] , protocolVersion = [valid pointer] |dsERR_NONE|The current HDCP protocol version should be successfully fetched |
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsGetHDCPCurrentProtocol (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetHDCPCurrentProtocol()  Attempt to get the current negotiated HDCP protocol version with out initializing video ports| handle = [valid handle] , protocolVersion = [valid pointer]| dsERR_NOT_INITIALIZED| dsGetHDCPCurrentProtocol call should fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetHDCPCurrentProtocol() Using an invalid handle but with valid pointer | handle = [invalid handle], protocolVersion = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports|
 * |05|Call dsGetHDCPCurrentProtocol() By looping through acquired supported port handles but with a invalid pointer | handle = [valid handle], protocolVersion = [invalid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetHDCPCurrentProtocol() Again after terminating video ports attempt to get the current negotiated  HDCP protocol version of video ports | handle= [valid handle from step 04 ] , protocolVersion = [valid pointer] | dsERR_NOT_INITIALIZED | dsGetHDCPCurrentProtocol call should fail as module is not initialized |
 *
 * 
 * **Additional Notes:**@n
 * - Handle validation, NULL pointer checks, and module initialization checks are crucial for the robustness of the API.
 * - @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsGetHDCPCurrentProtocol (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video ports of a system | |dsERR_NONE| Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports|
 * |03|Call dsGetTVHDRCapabilities() by looping through the acquired port handles and valid pointer to retrieve the HDR capabilities of a video port | handle  = [loop through valid handles] , capabilities = [valid pointer] |dsERR_NONE|The HDR capabilities should be successfully fetched and stored in the given pointer|
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsGetTVHDRCapabilities (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetTVHDRCapabilities() Attempt to get the HDR capabilites  with out initializing video ports| handle = [invalid handle] , capabilities = [valid pointer]| dsERR_NOT_INITIALIZED| dsGetTVHDRCapabilities call should fail as module is not initialized |
 * |02|dsVideoPortInit() - Initialize video ports of a system | |dsERR_NONE| Initialization must be successful |
 * |03|Call dsGetTVHDRCapabilities() Using an invalid handle but with valid pointer | handle = [invalid handle], capabilities = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports|
 * |04|Call dsGetTVHDRCapabilities() By looping through acquired port handles but with a invalid pointer | handle = [valid handle], capabilities = [invalid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |05|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |06|Call dsGetTVHDRCapabilities() Again after terminating video ports attempt to get the HDR capabilites of video ports | handle= [valid handle from step 04 ] , capabilities = [valid pointer] | dsERR_NOT_INITIALIZED | dsGetTVHDRCapabilities call should fail as module is not initialized |
 * 
 * **Additional Notes:**@n
 * - Handle validation, NULL pointer checks, and module initialization checks are crucial for the robustness of the API.
 * - @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsGetTVHDRCapabilities (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video ports of a system | |dsERR_NONE| Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports|
 * |03|Call dsSupportedTvResolutions() by looping through the acquired port handles and valid pointer to retrieve the resolutions of a video port |handle  = [loop through valid handles] , resolutions = [valid pointer] |dsERR_NONE|Resolutions should be set successfully|
 * |06|Call dsVideoPortTerm() - Terminate the video ports of a system| |dsERR_NONE|Termination must be successful|
 * 
 */
void test_l1_dsVideoPort_positive_dsSupportedTvResolutions (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsSupportedTvResolutions() - Attempt to get the supported resolutions with out initializing video ports| handle =  [invalid handle] , resolutions = [valid pointer]| dsERR_NOT_INITIALIZED| dsSupportedTvResolutions call should fail as module is not initialized |
 * |02|dsVideoPortInit() - Initialize video ports of a system | |dsERR_NONE| Initialization must be successful |
 * |03|Call dsSupportedTvResolutions() - Using an invalid handle but with valid resolutions pointer | handle = [invalid handle], resolutions = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort() Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |04|Call dsSupportedTvResolutions() - By looping through acquired port handles but with a invalid pointer | handle = [valid handle], resolutions = [invalid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |05|Call dsVideoPortTerm() - Terminate the video ports of a system | | dsERR_NONE | Termination must be successful |
 * |06|Call dsSupportedTvResolutions() - Again after terminating video ports attempt to get the supported resolutions of video ports | handle= [valid handle from step 04 ] , resolutions = [valid pointer] | dsERR_NOT_INITIALIZED | dsSupportedTvResolutions call should fail as module is not initialized |
 * 
 * **Additional Notes:**@n
 * - Handle validation, NULL pointer checks, and module initialization checks are crucial for the robustness of the API.
 * - @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsSupportedTvResolutions (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call  dsSetForceDisable4KSupport() by looping through the acquired port handles and valid value to Set the 4K support to be forcefully disabled or not | handle  = [loop through valid handles] , disable= [valid value] | dsERR_NONE | The 4K support should be successfully disabled or not |
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsSetForceDisable4KSupport (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsSetForceDisable4KSupport() Attempt to disable or not to disable 4K support with out initializing video ports| handle = [invalid handle] , disable = [valid value]| dsERR_NOT_INITIALIZED| dsSetForceDisable4KSupport call should fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetForceDisable4KSupport() Using an invalid handle but with valid disable parameter value | handle = [invalid handle], disable = [valid value] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort() Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |06|Call dsSetForceDisable4KSupport() Again after terminating video ports attempt to disable or not to disable 4k support of video ports | handle= [valid handle from step 04 ] , disable = [valid value] | dsERR_NOT_INITIALIZED | dsSetForceDisable4KSupport call should fail as module is not initialized |
 * 
 * **Additional Notes:**@n
 * - Handle validation and module initialization checks are crucial for the robustness of the API.
 * - @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsSetForceDisable4KSupport (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call  dsGetForceDisable4KSupport() by looping through the acquired port handles and valid pointer to get the 4K support disabled or not | handle  = [loop through valid handles] , disable= [valid pointer] | dsERR_NONE | The 4K support disabled or not should be successfully retrieved |
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful | 
 * 
 */
void test_l1_dsVideoPort_positive_dsGetForceDisable4KSupport (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetForceDisable4KSupport() Attempt to get 4k support disable or not with out initializing video ports| handle = [valid handle] , disable = [valid pointer]| dsERR_NOT_INITIALIZED| dsGetForceDisable4KSupport call should fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetForceDisable4KSupport() Using an invalid handle but with valid pointer | handle = [invalid handle], disable = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort() Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsGetForceDisable4KSupport() By looping through acquired port handles but with a invalid pointer | handle = [valid handle], disable = [invalid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetForceDisable4KSupport() Again after terminating video ports attempt to get whether 4K support of video ports disabled or not | handle= [valid handle from step 04 ] , disable = [valid pointer] | dsERR_NOT_INITIALIZED | dsGetForceDisable4KSupport call should fail as module is not initialized | 
 * 
 * **Additional Notes:**@n
 * - Handle validation, pointer validation, and module initialization checks are crucial for the robustness of the API.
 * - @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsGetForceDisable4KSupport (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsGetVideoEOTF() by looping through the acquired port handles and valid pointer Retrieve the current Electro-Optical Transfer Function (EOTF) value | handle = [loop through ports] , video_eotf = [valid pointer] |dsERR_NONE | Valid EOTF value Should return a valid EOTF value of the specified video port|
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsGetVideoEOTF (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetVideoEOTF() Attempt to get the EOTF  with out initializing video ports| handle = [valid handle] , video_eotf = [invalid pointer] | dsERR_NOT_INITIALIZED| dsGetVideoEOTF call should fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetVideoEOTF() Using an invalid handle but with valid pointer | handle = [invalid handle], video_eotf = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort() Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsGetVideoEOTF() By looping through acquired port handles but with a invalid pointer | handle = [valid handle], video_eotf = [invalid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetVideoEOTF() Again after terminating video ports attempt to get the EOTF of video ports | handle= [valid handle from step 04 ] , video_eotf = [valid pointer] | dsERR_NOT_INITIALIZED | dsGetVideoEOTF call should fail as module is not initialized |
 * 
 * **Additional Notes:**@n
 * - Handle validation, pointer validation, and module initialization checks are crucial for the robustness of the API.
 * - @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsGetVideoEOTF (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsGetMatrixCoefficients() by looping through the acquired port handles and valid resolution pointer to Retrieve the current matrix coefficients of a specified port |handle  = [loop through valid handles] , matrix_coefficients = [valid pointer] |dsERR_NONE|Should return a valid matrix coefficient value of the specified video port|
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsGetMatrixCoefficients (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetMatrixCoefficients() Attempt to get the matrix coefficients with out initializing video ports| handle = [invalid handle] , matrix_coefficients = [valid pointer]| dsERR_NOT_INITIALIZED| dsGetMatrixCoefficients call should fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetMatrixCoefficients() Using an invalid handle but with valid pointer | handle = [invalid handle], matrix_coefficients = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort() Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsGetMatrixCoefficients() By looping through acquired port handles but with a invalid pointer | handle = [valid handle], matrix_coefficients = [invalid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetMatrixCoefficients() Again after terminating video ports attempt to get the matrix coefficients  of video ports | handle= [valid handle from step 04 ] , matrix_coefficients = [valid pointer] | dsERR_NOT_INITIALIZED | dsGetMatrixCoefficients call should fail as module is not initialized |
 * 
 * **Additional Notes:**@n
 * - Handle validation, pointer validation, and module initialization checks are crucial for the robustness of the API.
 * - @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsGetMatrixCoefficients (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsGetColorDepth() by looping through the acquired port handles and valid pointer to retrieve the current color depth  | handle  = [loop through valid handles] , color_depth = [valid pointer] | dsERR_NONE | Should return a valid color depth value of the specified video port|
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsGetColorDepth (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetColorDepth() Attempt to get the color depth with out initializing video ports| handle = [invalid handle] , color_depth = [valid pointer]| dsERR_NOT_INITIALIZED| dsGetColorDepth call should fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetColorDepth() Using an invalid handle but with valid pointer | handle = [invalid handle], color_depth = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort() Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsGetColorDepth() By looping through acquired port handles but with a invalid pointer | handle = [valid handle], color_depth = [invalid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetColorDepth() Again after terminating video ports attempt to get the color depth of video ports | handle= [valid handle from step 04 ] , color_depth = [valid pointer] | dsERR_NOT_INITIALIZED | dsGetColorDepth call should fail as module is not initialized |
 * 
 * **Additional Notes:**@n
 * - Handle validation, pointer validation, and module initialization checks are crucial for the robustness of the API.
 * - @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsGetColorDepth (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsGetColorSpace() by looping through the acquired port handles and valid pointer to retrieve the current color space setting of video port |handle  = [loop through valid handles] , color_space = [valid pointer] |Valid color space value|Should return a valid color space setting of the specified video port|
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsGetColorSpace (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetColorSpace() Attempt to get the color space with out initializing video ports| handle = [invalid handle] , color_space = [valid pointer]| dsERR_NOT_INITIALIZED| dsGetColorSpace call should fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetColorSpace() Using an invalid handle but with valid pointer | handle = [invalid handle], color_space = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort() Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsGetColorSpace() By looping through acquired port handles but with a invalid pointer | handle = [valid handle], color_space = [invalid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetColorSpace() Again after terminating video ports attempt to get the color space of video ports | handle= [valid handle from step 04 ] , color_space = [valid pointer] | dsERR_NOT_INITIALIZED | dsGetColorSpace call should fail as module is not initialized |
 * 
 * **Additional Notes:**@n
 * - Handle validation, pointer validation, and module initialization checks are crucial for the robustness of the API.
 * - @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsGetColorSpace (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsGetQuantizationRange() by looping through the acquired port handles and valid pointer to retrieve the current quantization range |handle  = [loop through valid handles] , quantization_range = [valid pointer] |dsERR_NONE | Should return a valid quantization range of the specified video port|
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsGetQuantizationRange (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetQuantizationRange() Attempt to get the quantization range with out initializing video ports| handle = [invalid handle] , quantization_range = [valid pointer]| dsERR_NOT_INITIALIZED| dsGetQuantizationRange call should fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetQuantizationRange() Using an invalid handle but with valid pointer | handle = [invalid handle], quantization_range = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort() Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsGetQuantizationRange() By looping through acquired port handles but with a invalid pointer | handle = [valid handle], quantization_range = [invalid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetQuantizationRange() Again after terminating video ports attempt to get the quantization of video ports | handle= [valid handle from step 04 ] , quantization_range = [valid pointer] | dsERR_NOT_INITIALIZED | dsGetQuantizationRange call should fail as module is not initialized |
 * 
 * **Additional Notes:**@n
 * - Handle validation, pointer validation, and module initialization checks are crucial for the robustness of the API.
 * - @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsGetQuantizationRange (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsGetCurrentOutputSettings() by looping through the acquired port handles and valid pointer to retrieve the current output settings | handle= [loop through valid handles] , video_eotf = [valid EOTF pointer], matrix_coefficients = = [valid matrix coefficient pointer], color_space = [valid color space pointer], color_depth = [valid color depth pointer], quantization_range = [valid quantization range pointer]| dsERR_NONE and valid settings| All the output settings for the specified video port must be returned |
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsGetCurrentOutputSettings (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetCurrentOutputSettings() - Attempt to get the current output settings without initializing the video ports | handle = [valid handle],  video_eotf = [valid EOTF pointer], matrix_coefficients = = [valid matrix coefficient pointer], color_space = [valid color space pointer], color_depth = [valid color depth pointer], quantization_range = [valid quantization range pointer] | dsERR_NOT_INITIALIZED | Get Output settings must fail as module is not initialized|
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetCurrentOutputSettings() with an invalid handle but with valid pointers for output settings |handle = [valid handle], video_eotf = [valid EOTF pointer], matrix_coefficients = = [valid matrix coefficient pointer], color_space = [valid color space pointer], color_depth = [valid color depth pointer], quantization_range = [valid quantization range pointer] |dsERR_INVALID_PARAM| Invalid parameter error must be returned |
 * |04|Call dsGetCurrentOutputSettings() with an valid handle but invalid pointer for parameters | handle = [valid handle], NULL pointers for some or all parameters|dsERR_INVALID_PARAM| Invalid parameter error must be returned |
 * |05|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |06|Call dsGetCurrentOutputSettings() - Attempt to get the current output settings without initializing the video ports | handle = [valid handle],  video_eotf = [valid EOTF pointer], matrix_coefficients = = [valid matrix coefficient pointer], color_space = [valid color space pointer], color_depth = [valid color depth pointer], quantization_range = [valid quantization range pointer] | dsERR_NOT_INITIALIZED | Get Output settings must fail as module is not initialized|
 * 
 * **Additional Notes:** 
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsGetCurrentOutputSettings (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsIsOutputHDR() - by looping through acquired port handles to check if the video output is HDR or not |  handle = [valid handle], hdr = [valid pointer to hold hdr status value](true = HDR) | dsERR_NONE | Flag which holds the HDR status( @a true if Video Output is HDR and @a false otherwise ) of Video Port must be returned |
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 * 
 */
void test_l1_dsVideoPort_positive_dsIsOutputHDR (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsIsOutputHDR() - Attempt to check if video output is HDR or not without initializing video ports | handle: [ valid handle ], hdr: [ pointer to hold HDR status]| dsERR_NOT_INITIALIZED | Call to check if video output is HDR or not must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsIsOutputHDR() using an invalid handle but with a valid pointer to hold the HDR status | handle: [ invalid handle ], hdr: [ pointer to hold HDR status] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |05|Call dsIsOutputHDR() by looping through acquired port handles but with a null pointer for HDR status | handle: [ loop through valid handles ], hdr: [ NULL ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsIsOutputHDR() - Attempt to check if video output is HDR or not without initializing video ports | handle: [ valid handle ], hdr: [ pointer to hold HDR status] | dsERR_NOT_INITIALIZED | Call to check if video output is HDR or not must fail as module is not initialized |
 * 
 * **Additional Notes:** 
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsIsOutputHDR (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|dsResetOutputToSDR() - To reset the video output to SDR | | dsERR_NONE | Video Output must be resetted to SDR |
 * |03|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 * 
 */
void test_l1_dsVideoPort_positive_dsResetOutputToSDR (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsResetOutputToSDR() - Attempt to reset the video output to SDR without initializing the video ports | dsERR_NOT_INITIALIZED | Reset Video output to SDR must fail as video port is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |04|Call dsResetOutputToSDR() - Again attempt to reset the video output to SDR after terminating the video ports | dsERR_NOT_INITIALIZED| Reset Video output to SDR must fail as video port is not initialized |
 * 
 * **Additional Notes:** 
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsResetOutputToSDR (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned for all supported video ports|
 * |03|Call dsSetHdmiPreference() - by looping through the acquired port handles and set the HDMI preference from dsHdcpProtocolVersion_t | handle = [Valid handle], hdcpCurrentProtocol=[valid HDCP Protocol] | dsERR_NONE | HDMI Preference should be set successfully |
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsSetHdmiPreference (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsSetHdmiPreference() - Attempt to set the HDMI Preference without initializing the video ports | dsERR_NOT_INITIALIZED | Set Hdmi Preference should fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetHdmiPreference() - Using an invalid handle but with valid HDCP Protcol pointer | handle = [invalid handle], hdcpCurrentProtocol = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] | dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsSetHdmiPreference() - by looping through the acquired port handles and set the HDMI preference from dsHdcpProtocolVersion_t | handle = [Valid handle], hdcpCurrentProtocol=[valid HDCP Protocol] | dsERR_NONE | HDMI Preference should be set successfully |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsSetHdmiPreference() - Attempt to set the HDMI Preference without initializing the video ports | dsERR_NOT_INITIALIZED | Set Hdmi Preference should fail as module is not initialized |
 * 
 * **Additional Notes:**@n
 * - dsVideoPortTerm() should always be called to ensure that the video port system is properly shut down and all resources are released.
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsSetHdmiPreference (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsGetHdmiPreference() - by looping through the acquired port handles to get the HDMI Preference of each video ports which supports HDCP | handle = [valid handle], hdcpCurrentProtocol = [valid pointer] | dsERR_NONE |  The Current HDMI Preference must be returned |
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsGetHdmiPreference (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetHdmiPreference() - Attempt to get the HDMI Preference without prior initializing the video ports| dsERR_NOT_INITIALIZED | Get HDMI Preference of video ports must fail as module is not initialized |
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetHdmiPreference() - Using an invalid handle but with valid HDCP Protcol pointer | handle = [invalid handle], hdcpCurrentProtocol = [valid pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetVideoPort() - Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] | dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsGetHdmiPreference() - by looping through the acquired port handles and get the HDMI preference | handle = [Valid handle], hdcpCurrentProtocol = [valid HDCP Protocol(from dsHdcpProtocolVersion_t)] | dsERR_NONE | Valid HDMI Preference must be returned |
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsSetHdmiPreference() - Attempt to get the HDMI Preference without initializing the video ports | dsERR_NOT_INITIALIZED | Get Hdmi Preference should fail as module is not initialized |
 * 
 * **Additional Notes:**@n
 * - Handle validation and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called to ensure that the video port system is properly shut down and all resources are released.
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsGetHdmiPreference (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsGetIgnoreEDIDStatus() by looping through acquired handles and valid pointer to get IgnoreEDID status |handle=[valid handle] ,status=[valid pointer] |dsERR_NONE | Should successfully get the IgnoreEDID status|
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsGetIgnoreEDIDStatus (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetIgnoreEDIDStatus() without prior initialization of video ports|handle=[invalid handle] ,status=[invalid pointer]|dsERR_NOT_INITIALIZED|call must be fail as module is not initialzed|
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetIgnoreEDIDStatus() with an invalid handle but with valid pointer|handle=[invalid handle] ,status=[valid pointer]|dsERR_INVALID_PARAM|Invalid parameter must be returned|
 * |04|Call dsGetVideoPort() Get the port handle for all supported video ports on the platform  |type , index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsGetIgnoreEDIDStatus() by looping through valid handles with a NULL status pointer | handle=[valid handle] , status=[NULL pointer]|dsERR_INVALID_PARAM|Invalid parameter must be returned|
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetIgnoreEDIDStatus()  Again after terminating video ports | handle=[valid handle from step 04 ] , status=[valid pointer] | dsERR_NOT_INITIALIZED | call should fail as module is not initialized |
 * 
 * **Additional Notes:**@n
 * - Handle validation and module initialization checks are crucial for the robustness of the API.
 * - @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 * - dsVideoPortTerm() should always be called to ensure that the video port system is properly shut down and all resources are released.
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsGetIgnoreEDIDStatus (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsSetBackgroundColor by looping through the acquired prots and valid color values| handle=[Valid handle], color=[valid values] | dsERR_NONE|Background color should be set successfully|
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsSetBackgroundColor (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsSetBackgroundColor() without prior initialization of video ports|handle=[inValid handle], color=[valid values]|dsERR_NOT_INITIALIZED|call must fail as module not initialized|
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetBackgroundColor()  with an invalid handle and valid color values |handle=[inValid handle], color=[valid values]|dsERR_INVALID_PARAM|Invalid parameter must return |
 * |04|Call dsGetVideoPort() Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsSetBackgroundColor() by looping through acquired handles and invalid color value|handle=[valid handle], color=[Invalid color value|dsERR_INVALID_PARAM|Invalid parameter must return|
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsSetBackgroundColor() after termination video ports |handle= [valid handle from step 04 ] , color= [valid values] | dsERR_NOT_INITIALIZED | call should fail as module is not initialized |
 *
 * **Additional Notes:**@n
 * - Handle validation and module initialization checks are crucial for the robustness of the API.
 * - @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 * - dsVideoPortTerm() should always be called to ensure that the video port system is properly shut down and all resources are released.
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsSetBackgroundColor (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsSetForceHDRMode() by looping through acquired handles and valid mode values|handle=[valid handle], mode=[valid values]|dsERR_NONE|HDR mode should be set successfully|
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsSetForceHDRMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsSetForceHDRMode() without prior initialization of video ports|handle=[inValid handle], mode=[valid values]|dsERR_NOT_INITIALIZED|call must fail as module not initialized|
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetForceHDRMode() with an invalid handle and valid mode values|handle=[inValid handle], mode=[valid values]|dsERR_INVALID_PARAM|Invalid parameter must return|
 * |04|Call dsGetVideoPort() Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsSetForceHDRMode() by looping through acquired handles and valid mode values|handle=[Valid handle], mode=[invalid values]|dsERR_INVALID_PARAM|Invalid parameter must return|
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsSetForceHDRMode() after termination video ports |handle=[valid handle from step 04 ] , mode=[valid values] | dsERR_NOT_INITIALIZED | call should fail as module is not initialized |
 * 
 * **Additional Notes:**@n
 * - Handle validation and module initialization checks are crucial for the robustness of the API.
 * - @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 * - dsVideoPortTerm() should always be called to ensure that the video port system is properly shut down and all resources are released.
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsSetForceHDRMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsColorDepthCapabilities() by looping through the acquired ports and valid pointer|handle=[vallid handle], colorDepthCapability=[valid pointer] |dsERR_NONE  Color depth capabilities should be retrieved successfully|
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsColorDepthCapabilities (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsColorDepthCapabilities() without prior initialization of video ports|handle=[inValid handle], colorDepthCapability=[valid pointer]|dsERR_NOT_INITIALIZED|call must fail as module not initialized|
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsColorDepthCapabilities() with an invalid handle and valid pointer |handle=[valid handle], colorDepthCapability=[valid pointer] |dsERR_INVALID_PARAM|Invalid parameter must be returned |
 * |04|Call dsGetVideoPort() Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |04|Call dsColorDepthCapabilities() by looping through acquired handles and invalid pointer | handle=[valid handle], colorDepthCapability=[Invalid pointer]|dsERR_INVALID_PARAM|Invalid parameter must return|
 * |05|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |06|Call dsColorDepthCapabilities() after terminating videop ports |handle= [valid handle from step 04 ] , colorDepthCapability= [valid pointer] | dsERR_NOT_INITIALIZED|call must fail as module not initialized |
 * 
 * **Additional Notes:**@n
 * - Handle validation, module initialization checks, and null pointer checks are crucial for the robustness of the API.
 * - @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 * - dsVideoPortTerm() should always be called to ensure that the video port system is properly shut down and all resources are released.
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsColorDepthCapabilities (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsGetPreferredColorDepth by looping through acquired handles and valid pointer |handle=[valid handle] , colorDepth=[valid pointer]|dsERR_NONE|Preferred Color depth should be retrieved successfully|
 * |04|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsGetPreferredColorDepth (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetPreferredColorDepth() without prior initialization of video ports|handle=[invalid handle] , colorDepth=[valid pointer]|dsERR_NOT_INITIALIZED|call must fail as module is not initialized|
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetPreferredColorDepth() with an invalid handle and with valid pointer|handle=[invalid handle] , colorDepth=[valid pointer]|dsERR_INVALID_PARAM|Invalid parameter must be returned|
 * |04|Call dsGetVideoPort() Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsGetPreferredColorDepth() by looping through valid handes and with invalid pointer|handle=[valid handle] , colorDepth=[invalid pointer]|dsERR_INVALID_PARAM|Invalid parameter must be returned|
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetPreferredColorDepth() after terminating video ports |handle=[valid handle] , colorDepth=[valid pointer] |dsERR_NOT_INITIALIZED|call must fail as module is not initialized|
 *
 * **Additional Notes:**@n
 * - Handle validation and module initialization checks are crucial for the robustness of the API.
 * - @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 * - dsVideoPortTerm() should always be called to ensure that the video port system is properly shut down and all resources are released.
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsGetPreferredColorDepth (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetVideoPort() - Get the video port handle for valid video port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Call dsSetPreferredColorDepth() by looping through the acquired handles and Valid colorDepth values|handle=[invalid handle] , colorDepth=[valid values] |dsERR_NONE|Color depth should be set successfully|
 * |05|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsVideoPort_positive_dsSetPreferredColorDepth (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsSetPreferredColorDepth() without prior initialization of video ports|handle=[invalid handle] , colorDepth=[valid values]|dsERR_NOT_INITIALIZED|call should fail as module not initialized|
 * |02|Call dsVideoPortInit() - Initialize video port system | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetPreferredColorDepth() with an invalid handle with valid color depth values|handle=[Invalid handle],colorDepth=[valid values]|dsERR_INVALID_PARAM|Invalid parameter should be return|
 * |04|Call dsGetVideoPort() Get the port handle for all supported video ports on the platform  |type ,  index = [ Loop through kPorts ] |dsERR_NONE | Valid port handle must be returned for all supported video ports |
 * |05|Call dsSetPreferredColorDepth() by looping through valid handles  with an unsupported colorDepth value|handle=[valid handle],colorDepth=[invalid values]|dsERR_OPERATION_NOT_SUPPORTED|Invalid parameter should be return|
 * |06|Call dsVideoPortTerm() - Terminate the video port system | | dsERR_NONE | Termination must be successful |
 * |07|Call dsSetPreferredColorDepth() after terminating video ports|handle=[valid handle] , colorDepth=[valid values]|dsERR_NOT_INITIALIZED|call should fail as module not initialized|
 * 
 * **Additional Notes:**@n
 * - Handle validation, module initialization checks, and support checks for color depths are crucial for the robustness of the API.
 * - @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 * - dsVideoPortTerm() should always be called to ensure that the video port system is properly shut down and all resources are released.
 * - Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsVideoPort_negative_dsSetPreferredColorDepth (void)
{
	UT_FAIL(This function needs to be implemented!); 
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