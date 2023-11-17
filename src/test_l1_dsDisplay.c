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
 * @addtogroup Device_Settings_HAL Device Settings HAL
 * @par Application API Specification
 * Described herein are the DeviceSettings HAL types and functions that are part of
 * the Display subsystem. The Display subsystem manages system-specific HAL operations.
 *  @{
 */

/**
*   @defgroup dsDisplay_HALTEST DS Display HALTEST
 *  @{
 * @par Application API Specification
 * dsDisplay HAL provides an interface for managing the Display settings for the device settings module
 */

/**
 * @defgroup dsDisplay_HALTESTS_L1 DS Display HAL Tests L1 File
 *  @{
 */

/**
* @file test_l1_dsDisplay.c
* @page Device Settings
* @subpage Display
*
* ## Module's Role
* This module includes Level 1 functional tests (success and failure scenarios)
* This is to ensure that the API meets the operational requirements of the Power Manager across all vendors
*
* **Pre-Conditions:**  None@n
* **Dependencies:** None@n
*
* Ref to API Definition specification documentation : [ds-display_halSpec.md](../../../docs/pages/ds-display_halSpec.md)
*/


#include <string.h>
#include <stdlib.h>

#include <ut.h>
#include <ut_log.h>

/**
 * @brief Ensure dsDisplayInit() initializes the DS Display sub-system correctly during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 001@n
 * 
 * **Pre-Conditions:**@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsDisplayInit() to initialize the module| | dsERR_NONE | Initialization should succeed |
 * |02|Terminate the DS Display sub-system with dsDisplayTerm() | | dsERR_NONE | Termination should succeed |
 * |03|Call dsDisplayInit() to initialize the module| | dsERR_NONE | Initialization should succeed |
 * |04|Terminate the DS Display sub-system with dsDisplayTerm() | | dsERR_NONE | Termination should succeed |
 * 
 */
void test_l1_dsDisplay_positive_dsDisplayInit (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsDisplayInit() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 002@n
 * 
 * **Pre-Conditions:**@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize the module with dsDisplayInit() | | dsERR_NONE | Initialization should succeed |
 * |02|Call dsDisplayInit() again to check if it returns an error when the module is already initialized | | dsERR_ALREADY_INITIALIZED | Should return error indicating the module is already initialized |
 * |03|Terminate the module with dsDisplayTerm() | | dsERR_NONE | Termination should succeed |
 * 
 * @note Scenarios like dsERR_GENERAL are not included in this test plan due to the challenges in realistic simulation. Each test case is functionally independent with proper initialization and termination steps.
 */
void test_l1_dsDisplay_negative_dsDisplayInit (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsDisplayTerm() terminates the display sub-system correctly during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 003@n
 * 
 * **Pre-Conditions:**@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize the display sub-system with dsDisplayInit() | | dsERR_NONE | Initialization should succeed |
 * |02|Terminate the display sub-system with dsDisplayTerm() | | dsERR_NONE | Termination should succeed |
 * |03|Reinitialize the display sub-system with dsDisplayInit() to check for reinitialization capability | | dsERR_NONE | Reinitialization should succeed |
 * |04|Terminate the display sub-system again with dsDisplayTerm() to confirm termination capability | | dsERR_NONE | Termination should succeed again |
 * 
 */
void test_l1_dsDisplay_positive_dsDisplayTerm (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsDisplayTerm() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 004@n
 * 
 * **Pre-Conditions:**@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsDisplayTerm() without initializing the display sub-system | | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * |02|Initialize the display sub-system with dsDisplayInit() | | dsERR_NONE | Initialization should succeed |
 * |03|Terminate the display sub-system with dsDisplayTerm() | | dsERR_NONE | Termination should succeed |
 * |04|Call dsDisplayTerm() again after termination | | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * 
 * @note The ability to test scenarios like dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might require specific setup or environment configuration.
 */
void test_l1_dsDisplay_negative_dsDisplayTerm (void)
{
	UT_FAIL(This function needs to be implemented!); 
}


/**
 * @brief Ensure dsGetDisplay() retrieves the handle of the connected display device correctly during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 005@n
 * 
 * **Pre-Conditions:**@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize the display sub-system with dsDisplayInit() | | dsERR_NONE | Initialization should succeed |
 * |02|Call dsGetDisplay() Loop through all based on kPorts |vType: [Valid Port Type], int, intptr_t*  | dsERR_NONE and valid handle | Handle of the display device should be retrieved successfully |
 * |03|Call a the last value again, and compare the results |  |Success | The values should be the same |
 * |04|Terminate the display sub-system with dsDisplayTerm() | | dsERR_NONE | Termination should succeed |
 * 
 * @note valid ports can be retrieved from kPorts which can be retrieved from dsVideoPortSettings.
 */
void test_l1_dsDisplay_positive_dsGetDisplay (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetDisplay() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 006@n
 * 
 * **Pre-Conditions:**@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetDisplay() without initializing the display sub-system | vType: [Valid Port Type], int=1, intptr_t* | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * |02|Initialize the display sub-system with dsDisplayInit() | | dsERR_NONE | Initialization should succeed |
 * |03|Call dsGetDisplay() with invalid parameter video type | vType: dsVIDEOPORT_TYPE_MAX, int=1, intptr_t* | dsERR_INVALID_PARAM | Should return error indicating invalid parameters |
 * |04|Call dsGetDisplay() with invalid index | vType: [Valid Port Type], int=-1, intptr_t* | dsERR_INVALID_PARAM | Should return error indicating invalid parameters |
 * |05|Call dsGetDisplay() with NULL | vType:dsVIDEOPORT_TYPE_HDMI, int=1, NULL | dsERR_INVALID_PARAM | Should return error indicating invalid parameters |
 * |06|Terminate the display sub-system with dsDisplayTerm() | | dsERR_NONE | Termination should succeed |
 * |07|Call dsGetDisplay() without initializing the display sub-system |vType: [Valid Port Type], int=1, intptr_t* | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * 
 * @note The ability to test scenarios like dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might require specific setup or environment configuration.
 * @note valid ports can be retrieved from kPorts which can be retrieved from dsVideoPortSettings.
 */
void test_l1_dsDisplay_negative_dsGetDisplay (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetEDID() retrieves the EDID information correctly during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 007@n
 * 
 * **Pre-Conditions:**@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize the display sub-system and get a display device handle | | dsERR_NONE | Initialization and handle retrieval should succeed |
 * |02|Call dsGetDisplay() Loop through all valid ports in kPorts[]|vType: [Valid Port Type]_INPUT, int, intptr_t*  | dsERR_NONE and valid handle | Handle of the display device should be retrieved successfully |
 * |03|Call dsGetEDID() with the obtained display device handle | intptr_t handle, dsDisplayEDID_t *edid | dsERR_NONE and valid EDID info | EDID information should be retrieved successfully |
 * |04|Call dsGetEDID() with the obtained display device handle | intptr_t handle, dsDisplayEDID_t *edid | dsERR_NONE and valid EDID info | EDID information should be retrieved successfully |
 * |05|Compare the returned results |  | Success | The values should be the same |
 * |06|Terminate the display sub-system with dsDisplayTerm() | | dsERR_NONE | Termination should succeed |
 * 
 * @note valid ports can be retrieved from kPorts which can be retrieved from dsVideoPortSettings.
 * 
 */
void test_l1_dsDisplay_positive_dsGetEDID (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetEDID() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 008@n
 * 
 * **Pre-Conditions:**@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetEDID() without initializing the display sub-system or obtaining a handle | intptr_t handle, dsDisplayEDID_t *edid | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * |02|Initialize the display sub-system and obtain a display device handle | | dsERR_NONE | Initialization and handle retrieval should succeed |
 * |03|Call dsGetDisplay() Loop through all valid ports in kPorts[]|vType: [Valid Port Type]_INPUT, int, intptr_t*  | dsERR_NONE and valid handle | Handle of the display device should be retrieved successfully |
 * |04|Call dsGetEDID() with an invalid handle | intptr_t -1, dsDisplayEDID_t *edid | dsERR_INVALID_PARAM | Should return error indicating invalid handle |
 * |05|Call dsGetEDID() with a NULL dsDisplayEDID_t | intptr_t handle, NULL | dsERR_INVALID_PARAM | Should return error indicating invalid handle |
 * |06|Terminate the display sub-system with dsDisplayTerm() | | dsERR_NONE | Termination should succeed |
 * |07|Call dsGetEDID() without initializing the display sub-system or obtaining a handle | | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * 
 * @note The ability to test scenarios like dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might require specific setup or environment configuration.
 * @note valid ports can be retrieved from kPorts which can be retrieved from dsVideoPortSettings.
 * 
 */
void test_l1_dsDisplay_negative_dsGetEDID (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetEDIDBytes() retrieves the EDID buffer and length correctly during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 009@n
 * 
 * **Pre-Conditions:**@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize the display sub-system and get a display device handle | | dsERR_NONE | Initialization and handle retrieval should succeed |
 * |02|Call dsGetDisplay() Loop through all valid ports in kPorts[]|vType: [Valid Port Type]_INPUT, int, intptr_t*  | dsERR_NONE and valid handle | Handle of the display device should be retrieved successfully |
 * |03|Allocate memory for the EDID buffer and call dsGetEDIDBytes() with the obtained handle | intptr_t handle, unsigned char *edid, int *length | dsERR_NONE, valid EDID data, and length | EDID buffer and length should be retrieved successfully |
 * |04|Allocate memory for the EDID buffer and call dsGetEDIDBytes() with the obtained handle | intptr_t handle, unsigned char *edid, int *length | dsERR_NONE, valid EDID data, and length | EDID buffer and length should be retrieved successfully |
 * |05|Verify that the return results are the same |  | Success | The results should be the same  |
 * |06|Free the allocated EDID buffer and terminate the display sub-system with dsDisplayTerm() | | dsERR_NONE | Memory deallocation and termination should succeed |
 * 
 * @note valid ports can be retrieved from kPorts which can be retrieved from dsVideoPortSettings.
 * 
 */
void test_l1_dsDisplay_positive_dsGetEDIDBytes (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetEDIDBytes() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 010@n
 * 
 * **Pre-Conditions:**@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetEDIDBytes() without initializing the display sub-system or obtaining a handle | intptr_t handle, unsigned char *edid, int *length | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * |02|Initialize the display sub-system and obtain a display device handle | | dsERR_NONE | Initialization and handle retrieval should succeed |
 * |03|Call dsGetDisplay() Loop through all valid ports in kPorts[]|vType: [Valid Port Type]_INPUT, int, intptr_t*  | dsERR_NONE and valid handle | Handle of the display device should be retrieved successfully |
 * |04|Call dsGetEDIDBytes() with an invalid handle | intptr_t -1, unsigned char *edid, int *length | dsERR_INVALID_PARAM | Should return error indicating invalid parameters |
 * |05|Call dsGetEDIDBytes() with null edid | intptr_t -1, NULL, int *length | dsERR_INVALID_PARAM | Should return error indicating invalid parameters |
 * |06|Call dsGetEDIDBytes() with null length | intptr_t -1, unsigned char *edid, NULL | dsERR_INVALID_PARAM | Should return error indicating invalid parameters |
 * |07|Terminate the display sub-system with dsDisplayTerm() | | dsERR_NONE | Termination should succeed |
 * |08|Call dsGetEDIDBytes() without initializing the display sub-system or obtaining a handle | intptr_t handle, unsigned char *edid, int *length | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * 
 * @note The ability to test scenarios like dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might require specific setup or environment configuration. Ensure proper memory management in the test setup.
 * @note valid ports can be retrieved from kPorts which can be retrieved from dsVideoPortSettings.
 * 
 */
void test_l1_dsDisplay_negative_dsGetEDIDBytes (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetDisplayAspectRatio() retrieves the aspect ratio correctly during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 011@n
 * 
 * **Pre-Conditions:**@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize the display sub-system and get a display device handle | | dsERR_NONE | Initialization and handle retrieval should succeed |
 * |02|Call dsGetDisplay() Loop through all valid ports in kPorts[]|vType: [Valid Port Type]_INPUT, int, intptr_t*  | dsERR_NONE and valid handle | Handle of the display device should be retrieved successfully |
 * |03|Call dsGetDisplayAspectRatio() with the obtained display device handle | intptr_t handle, dsVideoAspectRatio_t *aspectRatio | dsERR_NONE and valid aspect ratio | Aspect ratio of the display device should be retrieved successfully |
 * |04|Call dsGetDisplayAspectRatio() with the obtained display device handle | intptr_t handle, dsVideoAspectRatio_t *aspectRatio | dsERR_NONE and valid aspect ratio | Aspect ratio of the display device should be retrieved successfully |
 * |05|Compare the results, and make sure the returned values are the same |  | Success | The values should be the same |
 * |06|Terminate the display sub-system with dsDisplayTerm() | | dsERR_NONE | Termination should succeed |
 * 
 * @note valid ports can be retrieved from kPorts which can be retrieved from dsVideoPortSettings.
 * 
 */
void test_l1_dsDisplay_positive_dsGetDisplayAspectRatio (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetDisplayAspectRatio() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 012@n
 * 
 * **Pre-Conditions:**@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetDisplayAspectRatio() without initializing the display sub-system or obtaining a handle | intptr_t handle, dsVideoAspectRatio_t *aspectRatio | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * |02|Initialize the display sub-system and obtain a display device handle | | dsERR_NONE | Initialization and handle retrieval should succeed |
 * |03|Call dsGetDisplay() Loop through all valid ports in kPorts[]|vType: [Valid Port Type]_INPUT, int, intptr_t*  | dsERR_NONE and valid handle | Handle of the display device should be retrieved successfully |
 * |04|Call dsGetDisplayAspectRatio() with an invalid handle| NULL, dsVideoAspectRatio_t *aspectRatio | dsERR_INVALID_PARAM | Should return error indicating invalid handle |
 * |05|Call dsGetDisplayAspectRatio() with an NULL aspectRatio | intptr_t handle, NULL | dsERR_INVALID_PARAM | Should return error indicating invalid handle |
 * |06|Terminate the display sub-system with dsDisplayTerm() | | dsERR_NONE | Termination should succeed |
 * |07|Call dsGetDisplayAspectRatio() without initializing the display sub-system or obtaining a handle | intptr_t handle, dsVideoAspectRatio_t *aspectRatio  | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * 
 * @note The ability to test scenarios like dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might require specific setup or environment configuration.
 * @note valid ports can be retrieved from kPorts which can be retrieved from dsVideoPortSettings.
 * 
 */
void test_l1_dsDisplay_negative_dsGetDisplayAspectRatio (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsRegisterDisplayEventCallback() registers the callback correctly during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 013@n
 * 
 * **Pre-Conditions:**@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize the display sub-system and get a display device handle | | dsERR_NONE | Initialization and handle retrieval should succeed |
 * |02|Call dsGetDisplay() Loop through all valid ports in kPorts[]|vType: [Valid Port Type]_INPUT, int, intptr_t*  | dsERR_NONE and valid handle | Handle of the display device should be retrieved successfully |
 * |03|Call dsRegisterDisplayEventCallback() with the obtained display device handle and a valid callback function | Valid handle and callback function | dsERR_NONE | Callback registration should succeed |
 * |04|Terminate the display sub-system with dsDisplayTerm() | | dsERR_NONE | Termination should succeed |
 * 
 * @note valid ports can be retrieved from kPorts which can be retrieved from dsVideoPortSettings.
 * 
 */
void test_l1_dsDisplay_positive_dsRegisterDisplayEventCallback (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsRegisterDisplayEventCallback() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 014@n
 * 
 * **Pre-Conditions:**@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsRegisterDisplayEventCallback() without initializing the display sub-system or obtaining a handle |Valid handle and callback function | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * |02|Initialize the display sub-system and obtain a display device handle | | dsERR_NONE | Initialization and handle retrieval should succeed |
 * |03|Call dsGetDisplay() Loop through all valid ports in kPorts[]|vType: [Valid Port Type]_INPUT, int, intptr_t*  | dsERR_NONE and valid handle | Handle of the display device should be retrieved successfully |
 * |04|Call dsRegisterDisplayEventCallback() with an NULL handle | NULL, callback function | dsERR_INVALID_PARAM | Should return error indicating invalid parameters |
 * |04|Call dsRegisterDisplayEventCallback() with an NULL callback function | Valid handle,  NULL | dsERR_INVALID_PARAM | Should return error indicating invalid parameters |
 * |05|Terminate the display sub-system with dsDisplayTerm() | | dsERR_NONE | Termination should succeed |
 * |06|Call dsRegisterDisplayEventCallback() without initializing the display sub-system or obtaining a handle | Valid handle and callback function| dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * 
 * @note The ability to test scenarios like dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might require specific setup or environment configuration.
 */
void test_l1_dsDisplay_negative_dsRegisterDisplayEventCallback (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main test(s) for this module
 *
 * @return int - 0 on success, otherwise failure
 */
int test_l1_dsDisplay_register ( void )
{
	/* add a suite to the registry */
	pSuite = UT_add_suite( "[L1 dsDisplay]", NULL, NULL );
	if ( NULL == pSuite )
	{
		return -1;
	}	

	UT_add_test( pSuite, "dsDisplayInit_L1_positive" ,test_l1_dsDisplay_positive_dsDisplayInit );
	UT_add_test( pSuite, "dsDisplayInit_L1_negative" ,test_l1_dsDisplay_negative_dsDisplayInit );
	UT_add_test( pSuite, "dsDisplayTerm_L1_positive" ,test_l1_dsDisplay_positive_dsDisplayTerm );
	UT_add_test( pSuite, "dsDisplayTerm_L1_negative" ,test_l1_dsDisplay_negative_dsDisplayTerm );
	UT_add_test( pSuite, "dsGetDisplay_L1_positive" ,test_l1_dsDisplay_positive_dsGetDisplay );
	UT_add_test( pSuite, "dsGetDisplay_L1_negative" ,test_l1_dsDisplay_negative_dsGetDisplay );
	UT_add_test( pSuite, "dsGetEDID_L1_positive" ,test_l1_dsDisplay_positive_dsGetEDID );
	UT_add_test( pSuite, "dsGetEDID_L1_negative" ,test_l1_dsDisplay_negative_dsGetEDID );
	UT_add_test( pSuite, "dsGetEDIDBytes_L1_positive" ,test_l1_dsDisplay_positive_dsGetEDIDBytes );
	UT_add_test( pSuite, "dsGetEDIDBytes_L1_negative" ,test_l1_dsDisplay_negative_dsGetEDIDBytes );
	UT_add_test( pSuite, "dsGetDisplayAspectRatio_L1_positive" ,test_l1_dsDisplay_positive_dsGetDisplayAspectRatio );
	UT_add_test( pSuite, "dsGetDisplayAspectRatio_L1_negative" ,test_l1_dsDisplay_negative_dsGetDisplayAspectRatio );
	UT_add_test( pSuite, "dsRegisterDisplayEventCallback_L1_positive" ,test_l1_dsDisplay_positive_dsRegisterDisplayEventCallback );
	UT_add_test( pSuite, "dsRegisterDisplayEventCallback_L1_negative" ,test_l1_dsDisplay_negative_dsRegisterDisplayEventCallback );
	

	return 0;
} 


/** @} */ // End of DS Display HAL Tests L1 File
/** @} */ // End of DS Display HALTEST
/** @} */ // End of Device Settings HAL
/** @} */ // End of Device Settings Module
/** @} */ // End of HPK