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
* @file TODO: test_l1_dsHost.c
* @page module_name TODO: Required field, name of the main module
* @subpage sub_page_name TODO: Add a function group if relevant
*
* ## Module's Role
* TODO: Explain the module's role in the system in general
* This is to ensure that the API meets the operational requirements of the module across all vendors.
*
* **Pre-Conditions:**  TODO: Add pre-conditions if any@n
* **Dependencies:** TODO: Add dependencies if any@n
*
* Ref to API Definition specification documentation : [halSpec.md](../../../docs/halSpec.md)
*/

#include <string.h>
#include <stdlib.h>

#include <ut.h>
#include <ut_log.h>

/**
 * @brief Ensure dsHostInit() returns correct error codes during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 001@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsHostInit() for the first time | | dsERR_NONE | Initialization should pass as it's the first call |
 * |02|Call dsHostTerm() to terminate the initialized module | | dsERR_NONE | Termination should be successful after initialization |
 * |03|Call dsHostInit() again after termination | | dsERR_NONE | Initialization should pass after termination |
 * |04|Call dsHostTerm() again to terminate the initialized module | | dsERR_NONE | Termination should be successful after initialization |
 * 
 */
void test_l1_dsHost_positive_dsHostInit (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHostInit() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 002@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsHostInit() for the first time | | dsERR_NONE | Initialization should pass as it's the first call |
 * |02|Call dsHostInit() again without terminating | | dsERR_ALREADY_INITIALIZED | Initialization should fail as it's already initialized |
 * 
 * **Additional Notes:**
 * - Testing for dsERR_GENERAL might be challenging as it represents undefined platform errors. Such errors can be hard to simulate consistently in a controlled testing environment.
 */
void test_l1_dsHost_negative_dsHostInit (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHostTerm() returns correct error codes during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 003@n
 * 
 * **Pre-Conditions:**@n
 * Module has been initialized using dsHostInit().
 * 
 * **Dependencies:** dsHostInit()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize the module using dsHostInit() | | dsERR_NONE | Initialization should pass |
 * |02|Call dsHostTerm() to terminate the initialized module | | dsERR_NONE | Termination should be successful after initialization |
 * |03|Initialize the module again using dsHostInit() | | dsERR_NONE | Initialization should pass |
 * |04|Call dsHostTerm() again to terminate the initialized module | | dsERR_NONE | Termination should be successful after re-initialization |
 * 
 */
void test_l1_dsHost_positive_dsHostTerm (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHostTerm() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 004@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** dsHostInit()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsHostTerm() without prior initialization | | dsERR_NOT_INITIALIZED | Termination should fail as module is not initialized |
 * 
 * **Additional Notes:**
 * - Testing for dsERR_GENERAL in dsHostTerm() might be challenging as it represents undefined platform errors. Such errors can be hard to simulate consistently in a controlled testing environment.
 */
void test_l1_dsHost_negative_dsHostTerm (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetCPUTemperature() returns correct error codes during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 005@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize the module using dsHostInit() | | dsERR_NONE | Initialization should pass |
 * |02|Call dsGetCPUTemperature() with valid pointer to store temperature | Valid float pointer | dsERR_NONE | Temperature value should be fetched successfully |
 * |03|Terminate the module using dsHostTerm() | | dsERR_NONE | Termination should be successful |
 * 
 */
void test_l1_dsHost_positive_dsGetCPUTemperature (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetCPUTemperature() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 006@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetCPUTemperature() without prior initialization | Valid float pointer | dsERR_NOT_INITIALIZED | Fetching temperature should fail as module is not initialized |
 * |02|Initialize the module using dsHostInit() | | dsERR_NONE | Initialization should pass |
 * |03|Call dsGetCPUTemperature() with NULL pointer | NULL | dsERR_INVALID_PARAM | Should return invalid parameter error |
 * |04|Terminate the module using dsHostTerm() | | dsERR_NONE | Termination should be successful |
 * |05|Call dsGetCPUTemperature() after termination | Valid float pointer | dsERR_NOT_INITIALIZED | Fetching temperature should fail as module is terminated |
 * 
 * **Additional Notes:**
 * - Testing for dsERR_GENERAL and dsERR_OPERATION_NOT_SUPPORTED in dsGetCPUTemperature() might be challenging as these represent undefined platform errors or specific hardware constraints. Such errors can be hard to simulate consistently in a controlled testing environment.
 */
void test_l1_dsHost_negative_dsGetCPUTemperature (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetSocIDFromSDK() returns correct error codes during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 007@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize the module using dsHostInit() | | dsERR_NONE | Initialization should pass |
 * |02|Call dsGetSocIDFromSDK() with a valid pointer to store the SOC ID | Valid char pointer (size of 8 bytes) | dsERR_NONE | SOC ID should be fetched successfully |
 * |03|Terminate the module using dsHostTerm() | | dsERR_NONE | Termination should be successful |
 * 
 */
void test_l1_dsHost_positive_dsGetSocIDFromSDK (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetSocIDFromSDK() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 008@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetSocIDFromSDK() without prior initialization | Valid char pointer (size of 8 bytes) | dsERR_NOT_INITIALIZED | Fetching SOC ID should fail as module is not initialized |
 * |02|Initialize the module using dsHostInit() | | dsERR_NONE | Initialization should pass |
 * |03|Call dsGetSocIDFromSDK() with NULL pointer | NULL | dsERR_INVALID_PARAM | Should return invalid parameter error |
 * |04|Terminate the module using dsHostTerm() | | dsERR_NONE | Termination should be successful |
 * |05|Call dsGetSocIDFromSDK() after termination | Valid char pointer (size of 8 bytes) | dsERR_NOT_INITIALIZED | Fetching SOC ID should fail as module is terminated |
 * 
 * **Additional Notes:**
 * - Testing for dsERR_GENERAL and dsERR_OPERATION_NOT_SUPPORTED in dsGetSocIDFromSDK() might be challenging as these represent undefined platform
void test_l1_dsHost_negative_dsGetSocIDFromSDK (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetHostEDID() returns correct error codes during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 009@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize the module using dsHostInit() | | dsERR_NONE | Initialization should pass |
 * |02|Call dsGetHostEDID() with valid pointers for edid and length | Valid unsigned char pointer, valid int pointer | dsERR_NONE | EDID and its length should be fetched successfully |
 * |03|Terminate the module using dsHostTerm() | | dsERR_NONE | Termination should be successful |
 * 
 */
void test_l1_dsHost_positive_dsGetHostEDID (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetHostEDID() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 010@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetHostEDID() without prior initialization | Valid unsigned char pointer, valid int pointer | dsERR_NOT_INITIALIZED | Fetching EDID should fail as module is not initialized |
 * |02|Initialize the module using dsHostInit() | | dsERR_NONE | Initialization should pass |
 * |03|Call dsGetHostEDID() with NULL pointers | NULL, NULL | dsERR_INVALID_PARAM | Should return invalid parameter error |
 * |04|Terminate the module using dsHostTerm() | | dsERR_NONE | Termination should be successful |
 * |05|Call dsGetHostEDID() after termination | Valid unsigned char pointer, valid int pointer | dsERR_NOT_INITIALIZED | Fetching EDID should fail as module is terminated |
 * 
 * **Additional Notes:**
 * - Testing for dsERR_GENERAL and dsERR_OPERATION_NOT_SUPPORTED in dsGetHostEDID() might be challenging as these represent undefined platform errors or specific hardware constraints. Such errors can be hard to simulate consistently in a controlled testing environment.
 */
void test_l1_dsHost_negative_dsGetHostEDID (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main test(s) for this module
 *
 * @return int - 0 on success, otherwise failure
 */
int test_l1_dsHost_register ( void )
{
	/* add a suite to the registry */
	pSuite = UT_add_suite( "[L1 dsHost]", NULL, NULL );
	if ( NULL == pSuite )
	{
		return -1;
	}	

	UT_add_test( pSuite, "dsHostInit_L1_positive" ,test_l1_dsHost_positive_dsHostInit );
	UT_add_test( pSuite, "dsHostInit_L1_negative" ,test_l1_dsHost_negative_dsHostInit );
	UT_add_test( pSuite, "dsHostTerm_L1_positive" ,test_l1_dsHost_positive_dsHostTerm );
	UT_add_test( pSuite, "dsHostTerm_L1_negative" ,test_l1_dsHost_negative_dsHostTerm );
	UT_add_test( pSuite, "dsGetCPUTemperature_L1_positive" ,test_l1_dsHost_positive_dsGetCPUTemperature );
	UT_add_test( pSuite, "dsGetCPUTemperature_L1_negative" ,test_l1_dsHost_negative_dsGetCPUTemperature );
	UT_add_test( pSuite, "dsGetSocIDFromSDK_L1_positive" ,test_l1_dsHost_positive_dsGetSocIDFromSDK );
	UT_add_test( pSuite, "dsGetSocIDFromSDK_L1_negative" ,test_l1_dsHost_negative_dsGetSocIDFromSDK );
	UT_add_test( pSuite, "dsGetHostEDID_L1_positive" ,test_l1_dsHost_positive_dsGetHostEDID );
	UT_add_test( pSuite, "dsGetHostEDID_L1_negative" ,test_l1_dsHost_negative_dsGetHostEDID );
	

	return 0;
} 
