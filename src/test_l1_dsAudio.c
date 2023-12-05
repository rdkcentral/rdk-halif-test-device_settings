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
 * the Host subsystem. The Host subsystem manages system-specific HAL operations.
 *  @{
 */

/**
 * @defgroup dsAudio_HALTEST Device Settings Audio HALTEST
 *  @{
 * @par Application API Specification
 * dsHost HAL provides an interface for managing the host settings for the device settings module
 */

/**
 * @defgroup DSHAL_AUDIO_HALTEST_L1 Device Settings HAL Audio L1 test cases
 *  @{
 */

/**
 * @file test_l1_dsAudio.c
 * @page Device Settings
 * @subpage dsAudio
 *
 * ## Module's Role
 * This module includes Level 1 functional tests (success and failure scenarios)
 * This is to ensure that the API meets the operational requirements of the dsAudio across all vendors
 *
 * **Pre-Conditions:**  None
 * **Dependencies:** None
 *
 * Ref to API Definition specification documentation : [ds-audio_halSpec.md](../../../docs/ds-audio_halSpec.md)
 */

#include <string.h>
#include <stdlib.h>
#include "dsAudio.h"
#include "dsAudioSettings.h"
#include <ut.h>
#include <ut_log.h>

#define NUM_OF_PORTS (sizeof(kPorts) / sizeof(kPorts[0]))
#define MAX_PROFILE_NAME_LEN 10
#define INT_ARRAY_INIT 0

#define DS_ASSERT_AUTO_TERM_NUMERICAL(value, comparison){\
	if(value != comparison){\
		UT_LOG("\n In %s Comparison: [%s = %s]\n", __FUNCTION__, value, comparison);\
		dsAudioPortTerm();\
		UT_FAIL();\
	}\
}\

#define DS_ASSERT_AUTO_TERM_NOT_EQUAL(value, comparison){\
	if(value == comparison){\
		UT_LOG("\n In %s Comparison: [%s = %s]\n", __FUNCTION__, value, comparison);\
		dsAudioPortTerm();\
		UT_FAIL();\
	}\
}\

#define DS_ASSERT_AUTO_TERM_STRING(value, comparison){\
	if(value != comparison){\
		UT_LOG("\n In %s Comparison: [%s = %s]\n", __FUNCTION__, value, comparison);\
		dsAudioPortTerm();\
		UT_FAIL();\
	}\
}\

static int gTestGroup = 1;
static int gTestID = 1;
intptr_t null_handle = 0;

/**
 * @brief Ensure dsAudioPortInit() returns correct status codes during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 001@n
 * 
 * **Pre-Conditions:**@n
 * The device has audio ports present.
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE | Termination must be successful |
 * |03|Call dsAudioPortInit() - Reinitialize audio ports again after termination | | dsERR_NONE | Make sure that the audio ports can be reinitialized after termination |
 * |04|Call dsAudioPortTerm() - Terminate audio ports after reinitialization | | dsERR_NONE | Termination must be successful after reinitialization |
 * 
 */
void test_l1_dsAudio_positive_dsAudioPortInit (void)
{
	gTestID = 1;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	// Step 01: Call dsAudioPortInit() Initialize dsAudio
	dsError_t result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Call dsAudioPortTerm() Terminate dsAudio
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Call dsAudioPortInit() Initialize dsAudio
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 04: Call dsAudioPortTerm() Terminate dsAudio again
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	UT_LOG("\n Out  %s\n",__FUNCTION__);
}

/**
 * @brief Ensure dsAudioPortInit() returns correct error codes during negative scenarios
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
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful as it is the first call |
 * |02|Call dsAudioPortInit() - Attempt to initialize audio ports again without terminating the previous initialization | | dsERR_ALREADY_INITIALIZED | Initialization must fail as it is already initialized |
 * |03|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE | Termination must be successful |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions. 
 */
void test_l1_dsAudio_negative_dsAudioPortInit (void)
{
	gTestID = 2;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	// Step 01: Call dsAudioPortInit() Initialize dsAudio
	dsError_t result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Call dsAudioPortInit() Attempt to initialize dsAudio again
	result = dsAudioPortInit();
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_ALREADY_INITIALIZED);


	// Step 03: Call dsAudioPortTerm() Terminate dsAudio
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	UT_LOG("\n Out  %s\n",__FUNCTION__);
}

/**
 * @brief Ensure dsAudioPortTerm() returns correct status codes during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 003@n
 * 
 * **Pre-Conditions:**@n
 * None
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE | Termination should be successful after initialization |
 * |03|Call dsAudioPortInit() - Initialize audio ports again after termination | | dsERR_NONE | Initialization should pass |
 * |04|Call dsAudioPortTerm() - Terminate audio ports after reinitialization | | dsERR_NONE |  Termination should be successful after re-initialization |
 * 
 */
void test_l1_dsAudio_positive_dsAudioPortTerm (void)
{
	gTestID = 3;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	// Step 01: dsAudioPortInit() Initialize dsAudio
	dsError_t result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: dsAudioPortTerm() Terminate dsAudio
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: dsAudioPortInit() Initialize dsAudio again
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 04: dsAudioPortTerm() Terminate dsAudio
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	UT_LOG("\n Out  %s\n",__FUNCTION__);
}

/**
 * @brief Ensure dsAudioPortTerm() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 004@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortTerm() - Attempt to terminate dsAudio | | dsERR_NOT_INITIALIZED | Termination should fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE | Termination should be successful after initialization |
 * |04|Call dsAudioPortTerm() - Attempt to terminate dsAudio | | dsERR_NOT_INITIALIZED | Termination should fail as module is not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and  dsERR_GENERAL might be challenging as they require specific platform conditions.
 * 
 */
void test_l1_dsAudio_negative_dsAudioPortTerm (void)
{
	gTestID = 4;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	// Step 01: dsAudioPortTerm() Attempt to terminate dsAudio without initialization
	dsError_t result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: dsAudioPortInit() Initialize dsAudio
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: dsAudioPortTerm() Terminate dsAudio after initialization
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 04: dsAudioPortTerm() Attempt to terminate dsAudio again
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	UT_LOG("\n Out  %s\n",__FUNCTION__);
}

/**
 * @brief Ensure dsGetAudioPort() returns valid audio port handle during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 005@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * @note - kPorts is available in dsAudioSettings.h file. Please refer (../../docs/pages/dsAudioSettings_template.h) for sample
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Get the audio port handle for valid audio port type and valid index | type, index = [Loop through kPorts] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned |
 * |03|Get the audio port handle for last element , store it in a new variable and compare it with previous step | | dsERR_NONE | Port handle obtained from previous step must be equal to handle obtained in this step
 * |04|Call dsAudioPortTerm() Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 *
 */
void test_l1_dsAudio_positive_dsGetAudioPort(void) {
	// Setting test case ID and logging at the start
	gTestID = 5;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t  result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	intptr_t  lastHandle , newHandle;

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Loop through kPorts to get audio port handle
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Remember last handle for comparison in next step
		if (i == (NUM_OF_PORTS-1)) {
			lastHandle = handle[i];
		}
	}

	// Step 03: Compare with the last element
	result = dsGetAudioPort(kPorts[NUM_OF_PORTS-1].id.type, kPorts[NUM_OF_PORTS-1].id.index, &newHandle);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result,dsERR_NONE);
	// previous handle comparison
	DS_ASSERT_AUTO_TERM_NUMERICAL(lastHandle, newHandle);

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}

/**
 * @brief Ensure dsGetAudioPort() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 006@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetAudioPort() - Attempt to get the Audio Port handle without initializing audio ports | `type`,`index`= kPorts[0], `handle`= valid handle | dsERR_NOT_INITIALIZED | Get Audio Port Handle must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetAudioPort() - by looping through valid port indexes but with invalid type  | type = [not in kPorts] , index = [ loop through kPorts ], handle = [ valid handle ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetAudioPort() - by looping through valid types but with invalid index | type = [loop through types in kPorts], index = [ invalid index which is not in kPorts ], handle: [ valid handle ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |05|Call dsGetAudioPort() - by looping through valid types and index but with a NULL handle | type, index: [ loop through kPorts ], handle: [ NULL pointer ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetAudioPort() - Attempt to get the audio port handle again after termination | type, index:  [ loop through kPorts ], handle: [ valid handle ] | dsERR_NOT_INITIALIZED | Get Audio Port Handle must fail as module is not initialized |
 * 
 * @note  Testing for the dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL  might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsAudio_negative_dsGetAudioPort(void) {
	// Logging at the start
	gTestID = 6;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t  result;
	intptr_t  handle[NUM_OF_PORTS]={INT_ARRAY_INIT};

	// Step 01: Attempt to get the Audio Port handle without initializing
	result = dsGetAudioPort(kPorts[0].id.type, kPorts[0].id.index, &handle[0]);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Invalid type
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(dsAUDIOPORT_TYPE_MAX, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);
	}

	// Step 04: Invalid index
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, -1 , &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 05: NULL handle
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to get the audio port handle after termination
	result = dsGetAudioPort(kPorts[0].id.type, kPorts[0].id.index, &handle[0]);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetAudioEncoding() returns correct audio encoding during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 007@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetAudioEncoding() by looping through the acquired port handles to get the audio encoding of each port in a array | handle: [ loop through valid handles ] , encoding: [pointer to hold the encoding] | dsERR_NONE | A valid audio encoding must be returned |
 * |04|Call dsGetAudioEncoding() by looping through the acquired port handles to get the audio encoding of each port in a new array | handle: [loop through valid handles ] , encoding: [pointer to hold the encoding] | dsERR_NONE | A valid audio encoding must be returned |
 * |05|Compare the array values and make sure they are equal| | dsERR_NONE | The values must be equal |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetAudioEncoding(void) {
	// Logging at the start
	gTestID = 7;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t  result;
	intptr_t  handle[NUM_OF_PORTS]={INT_ARRAY_INIT};
	dsAudioEncoding_t encodingarray1[NUM_OF_PORTS];
	dsAudioEncoding_t encodingarray2[NUM_OF_PORTS];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);
	} 

	// Step 03: Loop through all encoding options and get audio encoding for each port in array1
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioEncoding(handle[i], &encodingarray1[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
	}  

	// Step 04:Loop through all encoding options and get audio encoding for each port in array2
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioEncoding(handle[i], &encodingarray2[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
	}

	// Step 05: Compare the array values
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		DS_ASSERT_AUTO_TERM_NUMERICAL(encodingarray1[i], encodingarray2[i]);
	}


	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetAudioEncoding() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 008@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetAudioEncoding() - Get the audio encoding without initializing audio ports | handle: [invalid handle]| dsERR_NOT_INITIALIZED | Get audio encoding must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetAudioEncoding() using an invalid handle | handle: [invalid handle], encoding: [ pointer to hold the encoding ] | dsERR_INVALID_PARAM | TInvalid parameter error must be returned |
 * |04|Call dsGetAudioPort() Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsGetAudioEncoding() by looping through acquired port handles but with a null encoding pointer | handle: [ loop through valid handles ], encoding: [ NULL ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned when NULL pointer is passed for encoding |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetAudioEncoding() - Attempt to get the audio encoding type after terminating audio ports | handle: [ valid handle ], encoding: [ pointer to hold the encoding ] | dsERR_NOT_INITIALIZED | Get audio encoding must fail as module is not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetAudioEncoding(void) {
	// Logging at the start
	gTestID = 8;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t  result;
	intptr_t  handle[NUM_OF_PORTS]={INT_ARRAY_INIT};

	dsAudioEncoding_t encoding[NUM_OF_PORTS];

	// Step 01: Get audio encoding without initializing
	result = dsGetAudioEncoding(-1, &encoding[0]);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Get audio encoding using an invalid handle
	result = dsGetAudioEncoding(handle[0], &encoding[0]);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04 and 05: Get port handle and test with NULL encoding pointer
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Get audio encoding with NULL encoding pointer
		result = dsGetAudioEncoding(handle[i] , NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to get the audio encoding type after termination
	result = dsGetAudioEncoding(handle[0], &encoding[0]);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetAudioEncoding() sets the audio encoding correctly for all valid enum values during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 009@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsSetAudioEncoding() by looping through the acquired port handles and set the supported encoding values (by looping through kSupportedEncodings) for each audio ports | handle: [valid handles ], encoding: [ Loop through kSupportedEncodings values ] | dsERR_NONE | Supported encoding values must be set for each audio port |
 * |04|Call dsAudioPortTerm() - Terminate audio ports| | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsSetAudioEncoding(void) {
	// Logging at the start
	gTestID = 9;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t  result;
	intptr_t  handle[NUM_OF_PORTS]={INT_ARRAY_INIT};

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Set supported encoding values for each audio port
		if(kPorts[i].id.type == dsAUDIOPORT_TYPE_SPDIF) {
			for (int j = 0; j < sizeof(kSupportedSPDIFEncodings) / sizeof(kSupportedSPDIFEncodings[0]); j++) {
				result = dsSetAudioEncoding(handle[i],kSupportedSPDIFEncodings[j]);
				// Check for sccess
				DS_ASSERT_AUTO_TERM_NUMERICAL(result , dsERR_NONE);
			}//end of j for loop
		} else if(kPorts[i].id.type == dsAUDIOPORT_TYPE_HEADPHONE) {
			for (int j = 0; j < sizeof(kSupportedHEADPHONEEncodings) / sizeof(kSupportedHEADPHONEEncodings[0]); j++) {
				result = dsSetAudioEncoding(handle[i], kSupportedHEADPHONEEncodings[j]);
				// Check for success
				DS_ASSERT_AUTO_TERM_NUMERICAL(result , dsERR_NONE);
			}//end of j for loop
		} else if(kPorts[i].id.type == dsAUDIOPORT_TYPE_SPEAKER) {
			for (int j = 0; j < sizeof(kSupportedSPEAKEREncodings) / sizeof(kSupportedSPEAKEREncodings[0]); j++) {
				result = dsSetAudioEncoding(handle[i], kSupportedHEADPHONEEncodings[j]);
				// Check for success 
				DS_ASSERT_AUTO_TERM_NUMERICAL(result , dsERR_NONE);
			}//end of j for loop
		} else if(kPorts[i].id.type == dsAUDIOPORT_TYPE_HDMI_ARC) {
			for (int j = 0; j < sizeof(kSupportedARCEncodings) / sizeof(kSupportedARCEncodings[0]); j++) {
				result = dsSetAudioEncoding(handle[i], kSupportedHEADPHONEEncodings[j]);
				// Check for success 
				DS_ASSERT_AUTO_TERM_NUMERICAL(result , dsERR_NONE);
			}//end of j for loop
		}
	}//end of i for loop

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetAudioEncoding() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 010@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsSetAudioEncoding() - Attempt to get the Audio Port handle without initializing audio ports | handle: [ invalid handle ] encoding:[valid value] | dsERR_NOT_INITIALIZED | Set Audio Encoding must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports| | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetAudioEncoding() using an invalid handle but with a valid encoding type | handle: [ invalid handle ] , encoding : [ valid dsAudioEncoding_t value ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsSetAudioEncoding() - Loop through the acquired port handles and set an encoding type that is not part of the dsAudioEncoding_t(out of bounds) | handle: [ valid handle ], encoding: [ invalid encoding value ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsAudioPortTerm() - Terminate audio ports| | dsERR_NONE | Termination must be successful |
 * |07|Call dsSetAudioEncoding() again after terminating audio ports | handle: [ valid handle ] , encoding: [ valid dsAudioEncoding_t value ] | dsERR_NOT_INITIALIZED | Set Audio Encoding must fail as module is not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsSetAudioEncoding(void) {
	// Logging at the start
	gTestID = 10;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t  handle[NUM_OF_PORTS]={INT_ARRAY_INIT};

	// Step 01: Attempt to set Audio Encoding without initializing
	result = dsSetAudioEncoding(-1 , kSupportedSPEAKEREncodings[0]);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to set audio encoding using an invalid handle
	result = dsSetAudioEncoding(handle[0], kSupportedSPEAKEREncodings[0]); // Replace with invalid handle
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Attempt to set an out-of-bounds encoding value
		result = dsSetAudioEncoding(handle[i], dsAUDIO_ENC_MAX); // Replace with an invalid encoding value
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to set Audio Encoding after termination
	result = dsSetAudioEncoding(handle[0], kSupportedSPEAKEREncodings[0]); // Replace with valid handle and encoding
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetAudioFormat() retrieves the audio format correctly during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 011@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetAudioFormat() by looping through the acquired port handles to get the audio format of each port in array | handle: [ loop through valid handles ] , audioFormat: [pointer to hold the audio format] | dsERR_NONE | A valid audio encoding must be returned |
 * |04|Call dsGetAudioFormat() by looping through the acquired port handles to get the audio format of each port in new array | handle: [ loop through valid handles ] , audioFormat: [pointer to hold the audio format] | dsERR_NONE | A valid audio encoding must be returned |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetAudioFormat(void) {
	// Logging at the start
	gTestID = 11;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t  handle[NUM_OF_PORTS]={INT_ARRAY_INIT};

	dsAudioFormat_t audioFormatarray1[NUM_OF_PORTS];
	dsAudioFormat_t audioFormatarray2[NUM_OF_PORTS];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Get the audio format of each port
		result = dsGetAudioFormat(handle[i], &audioFormatarray1[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		UT_ASSERT_TRUE(audioFormatarray1[i] >= dsAUDIO_FORMAT_NONE && audioFormatarray1[i] < dsAUDIO_FORMAT_MAX); // Valid format check
	}


	// Step 04:Loop through all encoding options and get audio format for each port in array2
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioFormat(handle[i], &audioFormatarray2[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
	}

	// Step 05: Compare the array values
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		DS_ASSERT_AUTO_TERM_NUMERICAL(audioFormatarray1[i], audioFormatarray2[i]);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetAudioFormat() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 012@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetAudioFormat() - Attempt to get audio format without initializing audio ports | handle: [ invalid handle ], audioFormat: [pointer to hold audio format] | dsERR_NOT_INITIALIZED | Get Audio Format must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetAudioFormat() using an invalid handle but with a valid pointer to hold the audio format | handle: [ invalid handle ], audioFormat: [ pointer ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsGetAudioFormat() by looping through acquired port handles but with a null pointer for audio format | handle: [ loop through valid handles ], encoding: [ NULL ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE | Terminates the audio ports |
 * |07|Call dsGetAudioFormat() - Attempt to get audio format after terminating audio ports | handle: [ valid handle ] , audioFormat= [ pointer to hold audio format ]  | dsERR_NOT_INITIALIZED | Get Audio Format must fail as module is not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetAudioFormat(void) {
	// Logging at the start
	gTestID = 12;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t  handle[NUM_OF_PORTS]={INT_ARRAY_INIT};
	dsAudioFormat_t audioFormat[NUM_OF_PORTS];

	// Step 01: Attempt to get audio format without initializing
	result = dsGetAudioFormat(-1, &audioFormat[0]);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to get audio format using an invalid handle
	result = dsGetAudioFormat(handle[0], &audioFormat[0]);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Attempt to get audio format with a null pointer for audio format
		result = dsGetAudioFormat(handle[i], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to get audio format after termination
	result = dsGetAudioFormat(handle[0], &audioFormat[0]); // Replace with valid handle
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetAudioCompression() retrieves the audio compression level correctly during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 013@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetAudioCompression() by looping through the acquired port handles to get the audio compression level of each port | handle: [ loop through valid handles ], compression: [ pointer to hold the audio compression level ] | dsERR_NONE and compression value in range [0,10] | Audio compression should be retrieved correctly |
 * |04|Call dsGetAudioCompression() by looping through the acquired port handles to get the audio compression level of each port in new array | handle: [ loop through valid handles ], compression: [ pointer to hold the audio compression level ] | dsERR_NONE and compression value in range [0,10] | Audio compression should be retrieved correctly |
 * |05|Compare the array values and make sure they are equal| | dsERR_NONE | The values must be equal |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE | Should Pass |
 * 
 */
void test_l1_dsAudio_positive_dsGetAudioCompression(void) {
	// Logging at the start
	gTestID = 13;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	int  compression[NUM_OF_PORTS];
	int  compression1[NUM_OF_PORTS];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Get the audio compression level of each port
		result = dsGetAudioCompression(handle[i], &compression[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		//Step 04: Get the audio compression level of each port	in new array
		result = dsGetAudioCompression(handle[i], &compression1[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		//Step 05: Compare the compression levels of arrays
		DS_ASSERT_AUTO_TERM_NUMERICAL(compression[i], compression1[i]);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetAudioCompression() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 014@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetAudioCompression() - Attempt to get audio compression without initializing audio ports | handle: [ invalid handle ], compression: [ pointer to hold the audio compression ] | dsERR_NOT_INITIALIZED | Get audio compression must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetAudioCompression() using an invalid handle but with a valid pointer to hold the audio compression | handle: [ invalid handle ], compression: [ pointer ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetAudioPort() Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsGetAudioCompression() by looping through acquired port handles but with a null pointer for audio compression | handle: [ loop through valid handles ], compression: [ NULL ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsAudioPortTerm() Terminate audio ports | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetAudioCompression() - Attempt to get audio compression again after terminating audio ports | handle: [ valid handle from step 04 ] , compression: [ pointer ] | dsERR_NOT_INITIALIZED | Get audio compression must fail as module is not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetAudioCompression(void) {
	// Logging at the start
	gTestID = 14;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	int compression[NUM_OF_PORTS];

	// Step 01: Attempt to get audio compression without initializing
	result = dsGetAudioCompression(-1, &compression[0]); // Replace with valid handle
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to get audio compression using an invalid handle
	result = dsGetAudioCompression(handle[0], &compression[0]); 
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);
	}

	// Step 05: Attempt to get audio compression with a null pointer for audio compression
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioCompression(handle[i], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to get audio compression after termination
	result = dsGetAudioCompression(handle[0], &compression[0]);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetAudioCompression() sets the audio compression level correctly during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 015@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsSetAudioCompression() by looping through the acquired port handles and set the minimum audio compression level for each port | handle: [ valid handle ], compression: [ 0 ] | dsERR_NONE | Audio compression must be set correctly |
 * |04|Call dsSetAudioCompression() by looping through the acquired port handles and set the maximum audio compression level for each port | handle: [ valid handle ], compression: [ 10 ] | dsERR_NONE | Audio compression must be set correctly |
 * |05|Call dsSetAudioCompression() by looping through the acquired port handles and set the mid value audio compression level for each port | handle: [ valid handle ], compression: [ 5 ] | dsERR_NONE | Audio compression must be set correctly |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsSetAudioCompression(void) {
	// Logging at the start
	gTestID = 15;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	int min_compression = 0, max_compression = 10, mid_compression = 5;

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Set minimum audio compression level
		result = dsSetAudioCompression(handle[i], min_compression);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Step 04: Set maximum audio compression level
		result = dsSetAudioCompression(handle[i],max_compression);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Step 05: Set mid-value audio compression level
		result = dsSetAudioCompression(handle[i], mid_compression);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetAudioCompression() returns the correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 016@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n	
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsSetAudioCompression() using an invalid handle but with a valid compression value | handle: [ invalid value ], compression: [ valid dsAudioCompression_t value ] | dsERR_NOT_INITIALIZED | Set Audio Compression must return invalid parameter as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetAudioCompression() using an invalid hanlde and valid compression | handle: [ invalid handle ], compression: [valid value ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsSetAudioCompression() by looping through the acquired port handles but with out of range compression value(-10) | handle: [ valid handle ], compression: [ -10 ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsSetAudioCompression() by looping through the acquired port handles but with out of range compression value(20) | handle: [ valid handle ], compression: [ 20 ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |07|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE | Termination must be successful |
 * |08|Call dsSetAudioCompression() again after terminating audio ports | handle: [ valid handle ], compression: [ valid dsAudioCompression_t value ] | dsERR_NOT_INITIALIZED | Set Audio Compression must return invalid parameter as module is not initialized |
 *
 *@note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions. 
 */
void test_l1_dsAudio_negative_dsSetAudioCompression(void) {
	// Logging at the start
	gTestID = 16;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	int max_compression = 10, out_of_range_pos = 20, out_of_range_neg = -10;

	// Step 01: Attempt to set audio compression with an invalid handle
	result = dsSetAudioCompression(-1, max_compression);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to set audio compression with an invalid handle 
	result = dsSetAudioCompression(handle[0], max_compression);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Set out of range compression value (-10)
		result = dsSetAudioCompression(handle[i], out_of_range_neg);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

		// Step 06: Set out of range compression value (20)
		result = dsSetAudioCompression(handle[i], out_of_range_pos);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 07: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 08: Attempt to set audio compression after termination
	result = dsSetAudioCompression(handle[0], max_compression);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetDialogEnhancement() returns correct Dialog enhancement levels during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 017@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit()- Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetDialogEnhancement() by looping through the acquired port handles to get the dialog enhancement levels for each port | handle: [ valid handle ], level: [ pointer to hold dialog enhancement level ] | dsERR_NONE and value of `level` in the range [0,16] | Dialog Enhancement level should be retrieved correctly |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetDialogEnhancement(void) {
	// Logging at the start
	gTestID = 17;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	int dialogEnhancementLevel[NUM_OF_PORTS];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		UT_ASSERT_EQUAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);
	}

	// Step 03: Get the dialog enhancement levels for each port
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetDialogEnhancement(handle[i], &dialogEnhancementLevel[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		UT_ASSERT_TRUE(dialogEnhancementLevel[i] >= 0 && dialogEnhancementLevel[i] <= 16); // Valid level range check
	}

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetDialogEnhancement() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 018@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetDialogEnhancement() without initializing audio ports | handle=[invalid handle], level=[valid pointer] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized|
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetDialogEnhancement() using an invalid handle but with valid pointer| handle=[invalid handle], level=[valid pointer] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be r     eturned for all supported audio ports |
 * |05|Call dsGetDialogEnhancement() by looping through acquired valid handle but with invalid pointer| handle=[valid handle], level=[NULL] | dsERR_INVALID_PARAM | Invalid parameter error must be returned|
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsGetDialogEnhancement again after terminating audio ports | handle=[valid handle], level=[valid pointer] | dsERR_NOT_INITIALIZED | call must fail as module is not initialized|
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetDialogEnhancement(void) {
	// Logging at the start
	gTestID = 18;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	int dialogEnhancementLevel[NUM_OF_PORTS];

	// Step 01: Attempt to get dialog enhancement without initializing
	result = dsGetDialogEnhancement(-1, &dialogEnhancementLevel[0]);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to get dialog enhancement using an invalid handle
	result = dsGetDialogEnhancement(handle[0], &dialogEnhancementLevel[0]);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Attempt to get dialog enhancement with a null pointer
		result = dsGetDialogEnhancement(handle[i], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to get dialog enhancement after termination
	result = dsGetDialogEnhancement(handle[0], &dialogEnhancementLevel[0]);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetDialogEnhancement retrieves the Dialog Enhancement level correctly during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 019@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsSetDialogEnhancement()  by looping through the acquired handle and set the minimum dialog enhancement level | handle=[valid handle], level=[valid 0] | dsERR_NONE | Dialog Enhancement level should be set correctly |
 * |04|Call dsSetDialogEnhancement()  by looping through the acquired handle and set the maximum dialog enhancement level | handle=[valid handle], level=[valid 16] | dsERR_NONE | Dialog Enhancement level should be set correctly |
 * |05|Call dsSetDialogEnhancement()  by looping through the acquired handle and set the median dialog enhancement level | handle=[valid handle], level=[valid 8] | dsERR_NONE | Dialog Enhancement level should be set correctly |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsSetDialogEnhancement(void) {
	// Logging at the start
	gTestID = 19;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	int min_de_level = 0, max_de_level = 16, mid_de_level = 8;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Set Dialog Enhancement level - Min DE Level(0)
		result = dsSetDialogEnhancement(handle[i], min_de_level);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Step 04: Set Dialog Enhancement level - Max DE Level(16)
		result = dsSetDialogEnhancement(handle[i], max_de_level);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Step 05: Set Dialog Enhancement level - Mid DE Level(16)
		result = dsSetDialogEnhancement(handle[i], mid_de_level);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetDialogEnhancement() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 020@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsSetDialogEnhancement() without initializing audio ports | handle=[invalid handle],level=[valid value] |dsERR_NOT_INITIALIZED |call must fail as module not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetDialogEnhancement() using an invalid handle but with valid value(i.e 0 to 16) | handle=[invalid handle], level=[valid value]| dsERR_INVALID_PARAM |Invalid parameter must return|
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsSetDialogEnhancement() by looping through acquired valid handle but with invalid value(i.e > 16) | handle=[valid handle], level=[20]| dsERR_INVALID_PARAM |Invalid parameter must return|
 * |06|Call dsSetDialogEnhancement() by looping through acquired valid handle but with invalid value(i.e <0) | handle=[valid handle], level=[-10]| dsERR_INVALID_PARAM |Invalid parameter must return|
 * |07|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |08|Call dsSetDialogEnhancement() again after terminating audio ports | handle=[valid handle], level=[valid value] | dsERR_NOT_INITIALIZED |call must fail as module not initialized|
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsSetDialogEnhancement(void) {
	// Logging at the start
	gTestID = 20;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	int valid_de_level = 10, invalid_de_level_pos = 20, invalid_de_level_neg = -10;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};

	// Step 01: Attempt to set dialog enhancement without initializing
	result = dsSetDialogEnhancement(-1, valid_de_level); // Assume INVALID_HANDLE is an invalid handle
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to set dialog enhancement using an invalid handle
	result = dsSetDialogEnhancement(handle[0], valid_de_level);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Attempt to set dialog enhancement with an invalid level(20)
		result = dsSetDialogEnhancement(handle[i], invalid_de_level_pos);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

		// Step 06: Attempt to set dialog enhancement with an invalid level(-10)
		result = dsSetDialogEnhancement(handle[i], invalid_de_level_neg);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 07: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 08: Attempt to set dialog enhancement after termination
	result = dsSetDialogEnhancement(handle[0], valid_de_level); 
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetDolbyVolumeMode() retrieves the Dolby Volume Mode status correctly during positive scenarios.
 *
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 021@n
 *
 * **Dependencies:** None@n
 * **User Interaction:** None
 *
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetDolbyVolumeMode() by looping through the acquired port handles and valid pointer to get the Dolby Volume mode of each port | handle: [valid handle], mode: [valid pointer] | dsERR_NONE | Dolby Volume Mode  should be retrieved correctly |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Termination must be successful |
 *
 */
void test_l1_dsAudio_positive_dsGetDolbyVolumeMode(void) {
	// Logging at the start
	gTestID = 21;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t  result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};

	bool dolbyVolumeMode[NUM_OF_PORTS];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Get the Dolby Volume mode for each port
		result = dsGetDolbyVolumeMode(handle[i], &dolbyVolumeMode[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
	}

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetDolbyVolumeMode() returns correct error codes during negative scenarios.
 *
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 022@n
 *
 * **Dependencies:** None@n
 * **User Interaction:** None
 *
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetDolbyVolumeMode() - Attempt to get dolby volume mode without initializing audio ports | handle: [any value], mode: [valid pointer] | dsERR_NOT_INITIALIZED | get dolby audio mode  must fail as module is not initialized |
 * |02|Call dsAudioPortInit() -Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetDolbyVolumeMode() using an invalid handle but with a valid pointer to hold the volume  mode | handle: [ invalid handle ], mode: [ pointer ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetAudioPort() Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsGetDolbyVolumeMode() by looping through acquired port handles but with a null pointer for dolby volume mode | handle: [valid handle], mode: [ NULL ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsAudioPortTerm() Terminate audio ports | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetDolbyVolumeMode() Attempt to get dolby volume mode  again after terminating audio ports | handle: [ valid handle from step 04 ] , mode: [ pointer ] | dsERR_NOT_INITIALIZED | get dolby volume  mode  must fail as module is not initialized |
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetDolbyVolumeMode(void) {
	// Logging at the start
	gTestID = 22;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};

	bool dolbyVolumeMode[NUM_OF_PORTS];

	// Step 01: Attempt to get Dolby Volume mode without initializing
	result = dsGetDolbyVolumeMode(-1, &dolbyVolumeMode[0]);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to get Dolby Volume mode using an invalid handle
	result = dsGetDolbyVolumeMode(handle[0], &dolbyVolumeMode[0]);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Attempt to get Dolby Volume mode with a null pointer
		result = dsGetDolbyVolumeMode(handle[i], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to get Dolby Volume mode after termination
	result = dsGetDolbyVolumeMode(handle[0], &dolbyVolumeMode[0]);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetDolbyVolumeMode() sets the Dolby Volume Mode status correctly during positive scenarios.
 *
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 023@n
 *
 * **Dependencies:** None@n
 * **User Interaction:** None
 *
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |04|By looping through the acquired handles ,get the handles for the  audio ports which supports DolbyVolume Mode.
 * |03|Call dsSetDolbyVolumeMode() by looping through the acquired supported port handles and valid modes (i.e TRUE or FALSE) | handle: [valid handles], modes: [valid modes]) for each port] | dsERR_NONE | dolby volume mode  must be set correctly |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Termination must be successful |
 *
 */
void test_l1_dsAudio_positive_dsSetDolbyVolumeMode(void) {
	// Logging at the start
	gTestID = 23;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	bool mode = true;

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Set Dolby Volume Mode for each port and for each valid mode
		result = dsSetDolbyVolumeMode(handle[i], mode);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
	}

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetDolbyVolumeMode() returns correct error codes during negative scenarios.
 *
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 024@n
 *
 * **Dependencies:** None@n
 * **User Interaction:** None
 *
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsSetDolbyVolumeMode() - Attempt to set the Dolby Volume Mode without initializing audio ports | handle=[any value], mode=[0/1] (OFF/ON) | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() -Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetDolbyVolumeMode() - using an invalid handle with valid mode(i.e TRUE or FALSE)| handle = [invalid hanlde], mode = [valid mode] | dsERR_INVALID_PARAM | Should Pass |
 |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |06|Call dsSetDolbyVolumeMode() again after terminating audio ports attempt to set Dolby Volume Mode  | handle = [valid handle] , mode = [valid mode](True/FALSE) | dsERR_NOT_INITIALIZED | Should Pass |
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsSetDolbyVolumeMode(void) {
	// Logging at the start
	gTestID = 24;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	bool validMode = true; // Assuming 'true' as a valid mode

	// Step 01: Attempt to set the Dolby Volume Mode without initializing
	result = dsSetDolbyVolumeMode(-1, validMode);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to set Dolby Volume Mode using an invalid handle
	result = dsSetDolbyVolumeMode(handle[0], validMode);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);
	}

	// Step 05: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 06: Attempt to set Dolby Volume Mode after termination
	result = dsSetDolbyVolumeMode(handle[0], validMode);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetIntelligentEqualizerMode() retrieves the Intelligent Equalizer Mode correctly during positive scenarios.
 *
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 025@n
 *
 * **Dependencies:** None@n
 * **User Interaction:** None
 *
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetIntelligentEqualizerMode by looping through the acquired port handles to get the IntelligentEqualizer Mode of each port | handle = [valid handles], mode = [valid pointer]| dsERR_NONE and a valid mode will be 0 to 6 | Ensure that the returned mode value corresponds to the settings in the system |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Termination must be successful |
 *
 */
void test_l1_dsAudio_positive_dsGetIntelligentEqualizerMode(void) {
	// Logging at the start
	gTestID = 25;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	int intelligentEqualizerMode[NUM_OF_PORTS];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		UT_ASSERT_EQUAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Get the Intelligent Equalizer Mode for each port
		result = dsGetIntelligentEqualizerMode(handle[i], &intelligentEqualizerMode[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		UT_ASSERT_TRUE(intelligentEqualizerMode[i] >= 0 && intelligentEqualizerMode[i] <= 6); // Valid mode range check
	}

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetIntelligentEqualizerMode() returns correct error codes during negative scenarios.
 *
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 026@n
 *
 * **Dependencies:** None@n
 * **User Interaction:** None
 *
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetIntelligentEqualizerMode() Attempt to get the IntelligentEqualizerMode with out Initilizing audio ports  | handle = [valid handle], mode = [pointer to hold the mode value | dsERR_NOT_INITIALIZED |Get Intelligent Equalizer Mode must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetIntelligentEqualizerMode() using an invalid handle but with valid mode pointer | handle = [invalid handle] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetAudioPort() Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsGetIntelligentEqualizerMode() by looping through acquired port handles but with a null pointer to get  Intelligent Equalizer Mode   | handle: [ loop through valid handles ], mode: [ NULL ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetIntelligentEqualizerMode() again after terminating audio ports attempt to get the Intelligent Equalizer Mode  | handle = [valid handle from step 04] mode=[valid pointer]| dsERR_NOT_INITIALIZED | Get Intelligent Equalizer Mode must fail as module is not initialized |
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetIntelligentEqualizerMode(void) {
	// Logging at the start
	gTestID = 26;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	int intelligentEqualizerMode[NUM_OF_PORTS];

	// Step 01: Attempt to get Intelligent Equalizer Mode without initializing
	result = dsGetIntelligentEqualizerMode(-1, &intelligentEqualizerMode[0]);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to get Intelligent Equalizer Mode using an invalid handle
	result = dsGetIntelligentEqualizerMode(handle[0], &intelligentEqualizerMode[0]);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Attempt to get Intelligent Equalizer Mode with a null pointer
		result = dsGetIntelligentEqualizerMode(handle[i], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to get Intelligent Equalizer Mode after termination
	result = dsGetIntelligentEqualizerMode(handle[0], &intelligentEqualizerMode[0]);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetIntelligentEqualizerMode() sets the Intelligent Equalizer Mode correctly during positive scenarios.
 *
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 027@n
 *
 * **Dependencies:** None@n
 * **User Interaction:** None
 *
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|call dsSetIntelligentEqualizerMode() by looping through the acquired port handles and set a valid  IntelligentEqualizer Mode (i.e 0 to 6) for each audio port | handle = [loop through valid handle] mode = [vaild mode] for each port| dsERR_NONE | IntelligentEqualizer Mode must be set correctly |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Termination must be successful |
 *
 */
void test_l1_dsAudio_positive_dsSetIntelligentEqualizerMode(void) {
	// Logging at the start
	gTestID = 27;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t  result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Set Intelligent Equalizer Mode for each port with a valid mode (0 to 6)
		for (int mode = 0; mode <= 6; mode++) {
			result = dsSetIntelligentEqualizerMode(handle[i], mode);
			DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		}
	}

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetIntelligentEqualizerMode() returns correct error codes during negative scenarios.
 *
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 028@n
 *
 * **Dependencies:** None@n
 * **User Interaction:** None
 *
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsSetIntelligentEqualizerMode() Attempt to get the IntelligentEqualizerMode with out Initilizing audio ports  | handle = [valid handle], mode = [valid mode] vaild mode 0 to 6| dsERR_NOT_INITIALIZED |Set Intelligent Equalizer Mode must fail as module is not initialized |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetIntelligentEqualizerMode() using an invalid handle with valid mode (i.e 0 to 6)| handle = [invalid hanlde], mode = [vaild mode] | dsERR_INVALID_PARAM | Set IntelligentEqualizerMode must return invalid paramerter |
 * |04|Call dsGetAudioPort() Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsSetIntelligentEqualizerMode() by looping through acquired port handles but with a invalid mode value(<0 or >6) to set  Intelligent Equalizer Mode for each port | handle: [ loop through valid handles ], mode: [ invalid mode ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Termination should be successful |
 * |07|Call dsSetIntelligentEqualizerMode() again again after terminating audio ports attempt to set IntelligentEqualizer Mode  | handle = [valid handle] , mode = [valid mode](0 to 6) | dsERR_NOT_INITIALIZED | Set Intelligent Equalizer Mode must fail as module is not initialized  |
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsSetIntelligentEqualizerMode(void) {
	// Logging at the start
	gTestID = 28;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	int valid_mode = 0, invalid_mode = -1; 

	// Step 01: Attempt to set Intelligent Equalizer Mode without initializing
	result = dsSetIntelligentEqualizerMode(-1, valid_mode);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to set Intelligent Equalizer Mode using an invalid handle
	result = dsSetIntelligentEqualizerMode(handle[0], valid_mode);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Attempt to set Intelligent Equalizer Mode with an invalid mode value
		result = dsSetIntelligentEqualizerMode(handle[i], invalid_mode);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to set Intelligent Equalizer Mode after termination
	result = dsSetIntelligentEqualizerMode(handle[0], valid_mode);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetVolumeLeveller() retrieves the Volume Leveller settings correctly during positive scenarios.
 *
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 029@n
 *
 * **Dependencies:** None@n
 * **User Interaction:** None
 *
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|call dsGetVolumeLeveller() by looping through the acquired port handles to get the Volume Leveller settings of each port | handle = [loop through valid handles], volLeveller =[valid pointer to hold mode and level] | dsERR_NONE | Ensure that the volume leveller settings are retrieved correctly |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Termination must be successful |
 *
 */
void test_l1_dsAudio_positive_dsGetVolumeLeveller(void) {
	// Logging at the start
	gTestID = 29;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	dsVolumeLeveller_t volLeveller[NUM_OF_PORTS];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Get the Volume Leveller settings for each port
		result = dsGetVolumeLeveller(handle[i], &volLeveller[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
	}

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetVolumeLeveller() returns correct error codes during negative scenarios.
 *
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 030@n
 *
 * **Dependencies:** None@n
 * **User Interaction:** None
 *
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetVolumeLeveller() Attempt to get VolumeLeveller settings without initializing audio ports | handle =[vaild handle], volLeveller =[valid pointer to hold Volume Levellersetting] | dsERR_NOT_INITIALIZED | Get VolumeLeveller must fail as module not initialized |
 * |02|Call dsAudioPortInit() Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetVolumeLeveller() using an invalid handle but with a valid pointer to hold the VolumeLeveller settings | handle = [invalid handle], volLeveller =valid pointer to hold data]| dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetAudioPort() Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsGetVolumeLeveller() by looping through acquired port handles but with a null pointer | handle = [valid handle from step 04] , volLeveller = [invalid pointer] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetVolumeLeveller() again after terminating audio ports try to get VolumeLeveller settings | handle = [valid handle from step 04], volLeveller = [valid pointer] | dsERR_NOT_INITIALIZED | Get VolumeLeveller must fail as module not initialized |
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetVolumeLeveller(void) {
	// Logging at the start
	gTestID = 30;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	dsVolumeLeveller_t volLeveller[NUM_OF_PORTS];

	// Step 01: Attempt to get Volume Leveller settings without initializing
	result = dsGetVolumeLeveller(-1, &volLeveller[0]);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to get Volume Leveller settings using an invalid handle
	result = dsGetVolumeLeveller(handle[0], &volLeveller[0]);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);
	}

	// Step 05: Attempt to get Volume Leveller settings with a null pointer
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetVolumeLeveller(handle[i], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to get Volume Leveller settings after termination
	result = dsGetVolumeLeveller(handle[0], &volLeveller[0]);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetVolumeLeveller() sets the Volume Leveller settings correctly during positive scenarios.
 *
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 031@n
 *
 * **Dependencies:** None@n
 * **User Interaction:** None
 *
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsSetVolumeLeveller() by looping through the acquired port handles and set VolumeLeveller with valid mode and level for each audio port(the range of mode is (0,1,2) and range of level is (0 to 10)) | handle = [loop through valid handle] , volLeveller = [valid mode and level] | dsERR_NONE | Ensure that the volume leveller settings are set correctly |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Termination must be successful |
 *
 */
void test_l1_dsAudio_positive_dsSetVolumeLeveller(void) {
	// Logging at the start
	gTestID = 31;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS];
	dsVolumeLeveller_t volLeveller;

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Set Volume Leveller with valid mode and level for each audio port
		// Assuming dsVolumeLeveller_t is a struct or similar with mode and level fields
		for (int mode = 0; mode <= 2; mode++) {
			for (int level = 0; level <= 10; level++) {
				volLeveller.mode = mode;
				volLeveller.level = level;
				result = dsSetVolumeLeveller(handle[i], volLeveller);
				DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
			} // end of level for loop
		} // end of mode for loop
	} // end of i for loop

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetVolumeLeveller() returns correct error codes during negative scenarios.
 *
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 032@n
 *
 * **Dependencies:** None@n
 * **User Interaction:** None
 *
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsSetVolumeLeveller() Attempt to set the Volume Leveller without initializing audio ports | handle=[valid value], volLeveller=[valid mode and level] | dsERR_NOT_INITIALIZED | set Volume Leveller must fail as module is not initialized |
 * |02|Call dsAudioPortInit() Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetVolumeLeveller() using an invalid handle but with valid volLeveller values (i.e valid mode is 0 to 2 and valid level is 0 to 10) | handle = [invalid handle], volLeveller = [valid mode and level] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetAudioPort() Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsSetVolumeLeveller() by looping through acquired port handles but with a invalid mode of Volume Leveller settings (i.e invalid mode < 0 or > 2 valid level(0 to 12) | handle = [valid handle from step 04], volLeveller = [invalid mode and level] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |06|Call dsSetVolumeLeveller() by looping through acquired port handles but with a invalid level of Volume Leveller settings (i.e valid mode (0 to 2) invalid level < 0 or >12 | handle = [valid handle from step 04], volLeveller = [invalid mode and level] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |07|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Termination must be successful |
 * |08|Call dsSetVolumeLeveller() again after terminating audio ports attempt to set the Volume Leveller settings | handle= [valid handle from step 04 ] , volLeveller = [valid mode and level] | dsERR_NOT_INITIALIZED | set Volume Leveller must fail as module is not initialized |
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsSetVolumeLeveller(void) {
	// Logging at the start
	gTestID = 32;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	dsVolumeLeveller_t volLeveller;
	int valid_mode = 2, valid_level = 10, invalid_mode = -1, invalid_level = 20;

	// Step 01: Attempt to set Volume Leveller without initializing
	volLeveller.mode = valid_mode;
	volLeveller.level = valid_level;
	result = dsSetVolumeLeveller(-1, volLeveller);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to set Volume Leveller using an invalid handle
	result = dsSetVolumeLeveller(handle[0], volLeveller);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);
	}

	// Step 05: Attempt to set Volume Leveller with a invalid mode
	volLeveller.mode = invalid_mode;
	volLeveller.level = valid_level;
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsSetVolumeLeveller(handle[i], volLeveller);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}


	// Step 06: Attempt to set Volume Leveller with a invalid level
	volLeveller.mode = valid_mode;
	volLeveller.level = invalid_level;
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsSetVolumeLeveller(handle[i], volLeveller);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 07: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 08: Attempt to set Volume Leveller after termination
	volLeveller.mode = valid_mode;
	volLeveller.level = valid_level;
	result = dsSetVolumeLeveller(handle[0],volLeveller);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetBassEnhancer() retrieves the Bass Enhancer settings correctly during positive scenarios.
 *
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 033@n
 *
 * **Dependencies:** None@n
 * **User Interaction:** None
 *
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|dsGetBassEnhancer() by looping through the acquired port handles to get the Bass Enhancer of each port in a array| handle = [loop through valid handles], boost = [valid pointer to retrieve value] | dsERR_NONE and valid values ranging from 0 to 100 | Ensure that the Bass Enhancer value is retrieved correctly |
 * |04|dsGetBassEnhancer() by looping through the acquired port handles to get the Bass Enhancer of each port in a new array| handle = [loop through valid handles], boost = [valid pointer to retrieve value] | dsERR_NONE and valid values ranging from 0 to 100 | Ensure that the Bass Enhancer value is retrieved correctly |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Termination must be successful |
 *
 */
void test_l1_dsAudio_positive_dsGetBassEnhancer(void) {
	// Logging at the start
	gTestID = 33;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	int boostarray1[NUM_OF_PORTS];
	int boostarray2[NUM_OF_PORTS];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Get the Bass Enhancer of each port
		result = dsGetBassEnhancer(handle[i], &boostarray1[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		UT_ASSERT_TRUE(boostarray1[i] >= 0 && boostarray1[i] <= 100); // Valid range check for boost
	}

	// Step 04: Get the Bass Enhancer of each port in a new array
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetBassEnhancer(handle[i], &boostarray2[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		UT_ASSERT_TRUE(boostarray1[i] >= 0 && boostarray2[i] <= 100); // Valid range check for boost
	}

	// Step 05: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetBassEnhancer() returns correct error codes during negative scenarios.
 *
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 034@n
 *
 * **Dependencies:** None@n
 * **User Interaction:** None
 *
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetBassEnhancer() Attempt to get the BassEnhancer with out Initilizing audio ports  | handle = [valid handle], mode = [pointer to hold the value] | dsERR_NOT_INITIALIZED |Get BassEnhancer must fail as module is not initialized |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetBassEnhancer() using an invalid handle but with valid pointer | handle =[invalid handle], boost = [pointer to retrieve value] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetAudioPort() Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsGetBassEnhancer() by looping through acquired port handles but with a null pointer to get Bass Enhancer | handle =[valid handle from step 04], boost =[NULL pointer] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |06|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetBassEnhancer() again after terminating audio ports attempt to get the Bass Enhancer on audio ports | handle =[valid handle from step 04], boost =[pointer to retrieve value] | dsERR_NOT_INITIALIZED | Get BassEnhancer must fail as module is not initialized |
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetBassEnhancer(void) {
	// Logging at the start
	gTestID = 34;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS]= {INT_ARRAY_INIT};
	int boost;

	// Step 01: Attempt to get Bass Enhancer without initializing
	result = dsGetBassEnhancer(-1, &boost);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to get Bass Enhancer using an invalid handle
	result = dsGetBassEnhancer(handle[0], &boost);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Attempt to get Bass Enhancer with a null pointer
		result = dsGetBassEnhancer(handle[i], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to get Bass Enhancer after termination
	result = dsGetBassEnhancer(handle[0], &boost);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetBassEnhancer() sets the Bass Enhancer settings correctly during positive scenarios.
 *
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 035@n
 *
 * **Dependencies:** None@n
 * **User Interaction:** None
 *
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsSetBassEnhancer() by looping through the acquired port handles and set BassEnhancer for each audio port with valid range(i.e 0 to 100) | handle =[loop through valid handles], boost =[valid value] | dsERR_NONE | Ensure that the Bass Enhancer value is set correctly |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Termination must be successful |
 *
 */
void test_l1_dsAudio_positive_dsSetBassEnhancer(void) {
	// Logging at the start
	gTestID = 35;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	int boost, min_boost = 0, max_boost = 100, mid_boost = 50;

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Set Bass Enhancer for each audio port with valid range (0 to 100)
		result = dsSetBassEnhancer(handle[i], min_boost);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		result = dsSetBassEnhancer(handle[i], max_boost);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		result = dsSetBassEnhancer(handle[i], mid_boost);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
	}

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetBassEnhancer() returns correct error codes during negative scenarios.
 *
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 036@n
 *
 * **Dependencies:** None@n
 * **User Interaction:** None
 *
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsSetBassEnhancer() Attempt to set the Bass Enhancer  without initializing audio ports | handle=[valid value], boost=[valid value] | dsERR_NOT_INITIALIZED | set Bass Enhancer  must fail as module is not initialized |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetBassEnhancer() using an invalid handle but with valid boost values (i.e valid boost values is 0 to 100) | handle = [invalid handle], boost =[valid value] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |04|Call dsGetAudioPort() Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsSetBassEnhancer() by looping through acquired port handles but with a invalid boost value (i.e < 0 or > 100) | handle = [valid handle from step 04], boost =[invalid value] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |06|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Termination must be successful |
 * |07|Call dsSetBassEnhancer() again after terminating audio ports attempt to set Bass Enhancer | handle = [valid handle from step 04], boost =[valid value] | dsERR_NOT_INITIALIZED |  set Bass Enhancer  must fail as module is not initialized |
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsSetBassEnhancer(void) {
	// Logging at the start
	gTestID = 36;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	int boost = 75, invalidBoost_pos = 101, invalidBoost_neg = -20; 

	// Step 01: Attempt to set Bass Enhancer without initializing
	result = dsSetBassEnhancer(-1, boost); 
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to set Bass Enhancer using an invalid handle
	result = dsSetBassEnhancer(handle[0], boost);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Attempt to set Bass Enhancer with an invalid boost value
		result = dsSetBassEnhancer(handle[i], invalidBoost_pos);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

		result = dsSetBassEnhancer(handle[i], invalidBoost_neg);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to set Bass Enhancer after termination
	result = dsSetBassEnhancer(handle[0], boost);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsIsSurroundDecoderEnabled() retrieves the Surround Decoder status correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 037@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsIsSurroundDecoderEnabled() by looping through the acquired port handles and vaild pointer | handle = [valid handle] , enabled = [valid pointer] | dsERR_NONE | Ensure that the Surround Decoder must return  the enabled or disaled for each port |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsIsSurroundDecoderEnabled(void) {
	// Logging at the start
	gTestID = 37;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS];
	bool surroundDecoderEnabled[NUM_OF_PORTS];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Check if the Surround Decoder is enabled for each port
		result = dsIsSurroundDecoderEnabled(handle[i], &surroundDecoderEnabled[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
	}

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsIsSurroundDecoderEnabled() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 038@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsIsSurroundDecoderEnabled()  with out Initilizing audio ports  | handle = [invalid handle], enabled = [valid pointer] | dsERR_NOT_INITIALIZED |dsIsSurroundDecoderEnabled call  must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsIsSurroundDecoderEnabled() using an invalid handle and valid pointer | handle = [invalid handle] , enabled = [valid pointer] | dsERR_INVALID_PARAM | Invalid parameter must be returned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsIsSurroundDecoderEnabled()  by looping through acquired port handles but with a null pointer |handle = [valid handle] , enabled = [NULL] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsIsSurroundDecoderEnabled() after terminating audio ports | handle: [ valid handle from step 04 ] , enabled = [ valid pointer ] | dsERR_NOT_INITIALIZED | dsIsSurroundDecoderEnabled call must fail as module is not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsIsSurroundDecoderEnabled(void) {
	// Logging at the start
	gTestID = 38;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	bool surroundDecoderEnabled;

	// Step 01: Attempt to check Surround Decoder status without initializing
	result = dsIsSurroundDecoderEnabled(-1, &surroundDecoderEnabled);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to check Surround Decoder status using an invalid handle
	result = dsIsSurroundDecoderEnabled(handle[0], &surroundDecoderEnabled);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Attempt to check Surround Decoder status with a null pointer
		result = dsIsSurroundDecoderEnabled(handle[i], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to check Surround Decoder status after termination
	result = dsIsSurroundDecoderEnabled(handle[0], &surroundDecoderEnabled);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsEnableSurroundDecoder() sets the Surround Decoder status correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 039@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsEnableSurroundDecoder() by looping through the acquired port handles and vaild value(i.e TRUE / FALSE) | handle = [valid handle] , enabled = [valid value] | dsERR_NONE | Ensure that the Surround Decoder enabled or disabled |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsEnableSurroundDecoder(void) {
	// Logging at the start
	gTestID = 39;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	bool enabledValue = true;

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Enable Surround Decoder for each port
		result = dsEnableSurroundDecoder(handle[i], enabledValue);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
	}

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsEnableSurroundDecoder() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 040@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsEnableSurroundDecoder() without initializing audio ports | handle = [valid handle] , enabled = [valid value] | dsERR_NOT_INITIALIZED |dsEnableSurroundDecoder call must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsEnableSurroundDecoder() using an invalid handle and valid value (.ie TRUE or FALSE) | handle = [invalid handle], enabled = [valid value] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsEnableSurroundDecoder() after terminating audio ports | handle = [valid handle from step 04], enabled = [valid value] | dsERR_NOT_INITIALIZED |dsEnableSurroundDecoder call must fail as module is not initialized |
 *
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsEnableSurroundDecoder(void) {
	// Logging at the start
	gTestID = 40;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS]= {INT_ARRAY_INIT};
	bool enabled = true; 

	// Step 01: Attempt to enable Surround Decoder without initializing
	result = dsEnableSurroundDecoder(-1, enabled);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to enable Surround Decoder using an invalid handle
	result = dsEnableSurroundDecoder(handle[0], enabled);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);
	}

	// Step 05: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 06: Attempt to enable Surround Decoder after termination
	result = dsEnableSurroundDecoder(handle[0], enabled);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetDRCMode() retrieves the DRC Mode correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 041@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetDRCMode() by looping through the acquired port handles and valid pointer to get the DRC mode of each port in a array | handle: [ valid handles ] , mode: [valid pointer] | dsERR_NONE | A valid DRC mode must be returned |
 * |04|Call dsGetDRCMode() by looping through the acquired port handles and valid pointer to get the DRC mode of each port in a new array | handle: [ valid handles ] , mode: [valid pointer] | dsERR_NONE | A valid DRC mode must be returned |
 * |05|Compare the array values and make sure they are equal| | dsERR_NONE | The values must be equal |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetDRCMode(void) {
	// Logging at the start
	gTestID = 41;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	int drcModearray1[NUM_OF_PORTS];
	int drcModearray2 [NUM_OF_PORTS];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Get the DRC mode for each port
		result = dsGetDRCMode(handle[i], &drcModearray1[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result ,dsERR_NONE);
	}

	// Step 04: Get the DRC mode for each port in new array
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetDRCMode(handle[i], &drcModearray2[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result ,dsERR_NONE);
	} 

	//Step 05: compare the values of drcMode arrays
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		DS_ASSERT_AUTO_TERM_NUMERICAL(drcModearray1[i], drcModearray2[i]);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetDRCMode() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 042@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetDRCMode() without initializing audio ports | handle = [invalid handle] , mode = [valid pointer] | dsERR_NOT_INITIALIZED | dsGetDRCMode call must failas module not initialized|
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetDRCMode() using an invalid handle and valid pointer |handle: [ invalid handle ] , mode : [ valid pointer ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsGetDRCMode() using an valid handle and invalid pointer |handle: [ invalid handle ] , mode : [ invalid pointer ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsGetDRCMode() again after terminating audio ports | handle = [valid handle from step 04] , mode = [valid pointer] | dsERR_NOT_INITIALIZED | dsGetDRCMode call must fail as module not initialized|
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetDRCMode(void) {
	// Logging at the start
	gTestID = 42;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	int drcMode;

	// Step 01: Attempt to get DRC Mode without initializing
	result = dsGetDRCMode(-1, &drcMode);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to get DRC Mode using an invalid handle
	result = dsGetDRCMode(handle[0], &drcMode);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Attempt to get DRC Mode with an invalid pointer
		result = dsGetDRCMode(handle[i], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to get DRC Mode after termination
	result = dsGetDRCMode(handle[0], &drcMode);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetDRCMode() sets the DRC Mode correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 043@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsSetDRCMode() by looping through the acquired port handled and valid value (i.e 0 or 1) | handle = [valid handle] , mode = [valid value] | dsERR_NONE | The DRC Mode should be successfully set |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsSetDRCMode(void) {
	// Logging at the start
	gTestID = 43;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	int mode = 1; 

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Set DRC Mode for each port with valid values
		result = dsSetDRCMode(handle[i], mode);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result , dsERR_NONE);

	}

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetDRCMode() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 044@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsSetDRCMode() without initializing audio ports | handle = [invalid handle] , mode = [valid value] | dsERR_NOT_INITIALIZED | dsSetDRCMode call must fail as module not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetDRCMode() using an invalid handle and valid value (i.e 0 or 1) | handle = [invalid handle],  mode = [valid value] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsSetDRCMode() by looping through valid handle and invalid mode values (i.e < 0 or > 1) | handle = [valid handle] , mode = [invalid value] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |07|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |08|Call dsSetDRCMode() again after terminating audio ports attempt to set DRC mode | handle = [valid handle from step 04] , mode =[valid value] | dsERR_NOT_INITIALIZED | dsSetDRCMode call must fail as module not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsSetDRCMode(void) {
	// Logging at the start
	gTestID = 44;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	int validMode = 1, invalidMode = 2;

	// Step 01: Attempt to set DRC Mode without initializing
	result = dsSetDRCMode(-1, validMode); // Assume INVALID_HANDLE is an invalid handle
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to set DRC Mode using an invalid handle
	result = dsSetDRCMode(handle[0], validMode);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Attempt to set DRC Mode with an invalid mode value
		result = dsSetDRCMode(handle[i], invalidMode);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 07: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 08: Attempt to set DRC Mode after termination
	result = dsSetDRCMode(handle[0], validMode);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetSurroundVirtualizer() retrieves the Surround Virtualizer level correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 045@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetSurroundVirtualizer() Loop through the acquired port handles with valid pointer to get SurroundVirtualizer values in array | handle = [valid handle] , virtualizer = [valid pointer] | dsERR_NONE | dsGetSurroundVirtualizer must return valid values  |
 * |04|Call dsGetSurroundVirtualizer() Loop through the acquired port handles with valid pointer to get SurroundVirtualizer values in new array | handle = [valid handle] , virtualizer = [valid pointer] | dsERR_NONE | dsGetSurroundVirtualizer must return valid values  |
 * |05|Compare the array values and make sure they are equal| | dsERR_NONE | The values must be equal |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetSurroundVirtualizer(void) {
	// Logging at the start
	gTestID = 45;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	dsSurroundVirtualizer_t surroundVirtualizerarray1[NUM_OF_PORTS];
	dsSurroundVirtualizer_t surroundVirtualizerarray2[NUM_OF_PORTS];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Get the Surround Virtualizer level for each port
		result = dsGetSurroundVirtualizer(handle[i], &surroundVirtualizerarray1[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

	}

	// Step 04: Get the Surround Virtualizer level for each port
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetSurroundVirtualizer(handle[i], &surroundVirtualizerarray1[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
	}

	//Step 05: compare the values of surroundVirtualizer arrays
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		DS_ASSERT_AUTO_TERM_NUMERICAL(surroundVirtualizerarray1[i].mode, surroundVirtualizerarray2[i].mode);
		DS_ASSERT_AUTO_TERM_NUMERICAL(surroundVirtualizerarray1[i].boost, surroundVirtualizerarray2[i].boost);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetSurroundVirtualizer() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 046@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetSurroundVirtualizer() without initializing audio ports | handle = [invalid handle] , virtualizer = [valid pointer] | dsERR_NOT_INITIALIZED |dsGetSurroundVirtualizer must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetSurroundVirtualizer() using an invalid handle and valid pointer | handle = [invalid handle] , virtualizer = [valid pointer] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsGetSurroundVirtualizer() by looping through the acquired port handled but with invalid pointer | handle = [valid handle ] , virtualizer = [invalid pointer] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsGetSurroundVirtualizer() again after terminating audio ports  | handle = [valid handle from step 04] , virtualizer = [valid pointer] | dsERR_NOT_INITIALIZED | dsGetSurroundVirtualizer must fail as module is not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetSurroundVirtualizer(void) {
	// Logging at the start
	gTestID = 46;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	dsSurroundVirtualizer_t virtualizerLevel;

	// Step 01: Attempt to get Surround Virtualizer without initializing
	result = dsGetSurroundVirtualizer(-1, &virtualizerLevel);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to get Surround Virtualizer using an invalid handle
	result = dsGetSurroundVirtualizer(handle[0], &virtualizerLevel);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Attempt to get Surround Virtualizer with an invalid pointer
		result = dsGetSurroundVirtualizer(handle[i], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to get Surround Virtualizer after termination
	result = dsGetSurroundVirtualizer(handle[0], &virtualizerLevel);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetSurroundVirtualizer() sets the Surround Virtualizer level correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 047@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsSetSurroundVirtualizer() by looping through acquired handle with valid virtualizer values(i.e mode (0 to 2) and boost (0 to 96)) | handle = [valid handles] , virtualizer = [valid mode and boost values] | dsERR_NONE | dsSetSurroundVirtualizer must set the valid values |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsSetSurroundVirtualizer(void) {
	// Logging at the start
	gTestID = 47;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);


	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT}; 
	int boost_min = 0, boost_max = 96, boost_mid = 48;
	dsSurroundVirtualizer_t virtualizer;

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Set Surround Virtualizer with valid mode and boost values for each port
		for (int mode = 0; mode <= 2; mode++) {
			virtualizer.mode = mode;
			virtualizer.boost = boost_min;
			result = dsSetSurroundVirtualizer(handle[i], virtualizer);
			DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

			virtualizer.mode = mode;
			virtualizer.boost = boost_max;
			result = dsSetSurroundVirtualizer(handle[i], virtualizer);
			DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

			virtualizer.mode = mode;
			virtualizer.boost = boost_mid;
			result = dsSetSurroundVirtualizer(handle[i], virtualizer);
			DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		}
	}

	// Step 05: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetSurroundVirtualizer() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 048@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsSetSurroundVirtualizer() without initializing audio ports | handle = [invalid handle] , virtualizer = [valid values | dsERR_NOT_INITIALIZED | dsSetSurroundVirtualizer call must fail as module not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetSurroundVirtualizer() using an invalid handle and valid virtualizer values (i.e mode (0 to 2) and boost (0 to 96))  | handle = [invalid handle] , virtualizer = [valid values] | dsERR_INVALID_PARAM | Invalid parameter should be returned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsSetSurroundVirtualizer() by looping through valid handles and invalid virtualizer values (i.e invalid mode (< 0 or > 2) and  valid boost (0 to 96))  | handle = [valid handle] , virtualizer = [invalid values] | dsERR_INVALID_PARAM | Invalid parameter should be returned |
 * |06|Call dsSetSurroundVirtualizer() by looping through valid handles and invalid virtualizer values (i.e valid mode (0 to 2) and invalid boost (< 0 or > 96))  | handle = [valid handle] , virtualizer = [invalid values] | dsERR_INVALID_PARAM | Invalid parameter should be returned |
 * |07|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |08|Call dsSetSurroundVirtualizer() again after terminating audio ports | handle = [valid handle from step 04] , virtualizer = [valid values] | dsERR_NOT_INITIALIZED | dsSetSurroundVirtualizer call must fail as module not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsSetSurroundVirtualizer(void) {
	// Logging at the start
	gTestID = 48;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	dsSurroundVirtualizer_t virtualizer;
	int valid_mode = 2, valid_boost = 96, invalid_mode = -1, invalid_boost = 100;

	// Step 01: Attempt to set Surround Virtualizer without initializing
	virtualizer.mode = valid_mode;
	virtualizer.boost = valid_boost;
	result = dsSetSurroundVirtualizer(-1, virtualizer);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to set Surround Virtualizer using an invalid handle
	result = dsSetSurroundVirtualizer(handle[0], virtualizer);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Attempt to set Surround Virtualizer with invalid mode value
		virtualizer.mode = invalid_mode;
		virtualizer.boost = valid_boost;
		result = dsSetSurroundVirtualizer(handle[i], virtualizer);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

		
		// Step 06: Attempt to set Surround Virtualizer with invalid boost value
		virtualizer.mode = valid_mode;
		virtualizer.boost = invalid_boost;
		result = dsSetSurroundVirtualizer(handle[i], virtualizer);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 07: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 08: Attempt to set Surround Virtualizer after termination
	virtualizer.mode = valid_mode;
	virtualizer.boost = valid_boost;
	result = dsSetSurroundVirtualizer(handle[0], virtualizer);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetMISteering() retrieves the MI Steering status correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 049@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetMISteering() by looping through the acquired port handles to get the Media Intelligent Steering of each port in array| handle: [ loop through valid handles ] , enabled: [pointer to hold the MI Steering enabled/disabled value] | dsERR_NONE | MI Steering enabled/disabled status must be returned |
 * |04|Call dsGetMISteering() by looping through the acquired port handles to get the Media Intelligent Steering of each port in a new array| handle: [ loop through valid handles ] , enabled: [pointer to hold the MI Steering enabled/disabled value] | dsERR_NONE | MI Steering enabled/disabled status must be returned |
 * |05|Compare the array values and make sure they are equal| | dsERR_NONE | The values must be equal |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetMISteering(void) {
	// Logging at the start
	gTestID = 49;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	bool miSteeringEnabledarray1[NUM_OF_PORTS];
	bool miSteeringEnabledarray2[NUM_OF_PORTS];


	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Get the MI Steering status for each port
		result = dsGetMISteering(handle[i], &miSteeringEnabledarray1[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
	}

	// Step 04: Get the MI Steering status for each port in new array
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetMISteering(handle[i], &miSteeringEnabledarray1[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
	}

	//Step 05: compare the values of miSteeringEnabled arrays
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		DS_ASSERT_AUTO_TERM_NUMERICAL(miSteeringEnabledarray1[i], miSteeringEnabledarray2[i]);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetMISteering() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 050@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetMISteering() without initializing audio ports | handle = [invalid handle] , enabled = [valid pointer] | dsERR_NOT_INITIALIZED | dsGetMISteering call must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetMISteering() using an invalid handle but with valid pointer | handle = [invalid handle] , enabled = [valid pointer] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsGetMISteering() using an valid handle but with invalid pointer | handle = [invalid handle] , enabled = [invalid pointer] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsGetMISteering() again after terminating audio ports | handle = [valid handle from step 04] , enabled = [valid pointer] | dsERR_NOT_INITIALIZED | dsGetMISteering call must fail as module is not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetMISteering(void) {
	// Logging at the start
	gTestID = 50;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	bool miSteeringEnabled;

	// Step 01: Attempt to get MI Steering without initializing
	result = dsGetMISteering(-1, &miSteeringEnabled);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to get MI Steering using an invalid handle
	result = dsGetMISteering(handle[0], &miSteeringEnabled);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Attempt to get MI Steering with an invalid pointer
		result = dsGetMISteering(handle[0], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to get MI Steering after termination
	result = dsGetMISteering(handle[0], &miSteeringEnabled);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}

/**
 * @brief Ensure dsSetMISteering() sets the MI Steering status correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 051@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 *
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsSetMISteering() by looping through the acquired port handles and vaild value(i.e TRUE / FALSE) | handle = [valid handle] , enabled = [valid value] | dsERR_NONE | Ensure that the MI steering sets properly enabled or disabled |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful | 
 * 
 */
void test_l1_dsAudio_positive_dsSetMISteering(void) {
	// Logging at the start
	gTestID = 51;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result = {INT_ARRAY_INIT};
	intptr_t handle[NUM_OF_PORTS];
	bool enabledValue = true;

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Enable or Disable MI Steering for each port
		result = dsSetMISteering(handle[i], enabledValue);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
	}

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetMISteering() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 052@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsSetMISteering() without initializing audio ports | handle = [invalid handle] , enabled = [valid value] | dsERR_NOT_INITIALIZED |dsSetMISteering call must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetMISteering() using an invalid handle and valid value (.ie TRUE or FALSE) | handle = [invalid handle], enabled = [valid value] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsSetMISteering() after terminating audio ports | handle = [valid handle from step 04], enabled = [valid value] | dsERR_NOT_INITIALIZED | dsSetMISteering call must fail as module is not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsSetMISteering(void) {
	// Logging at the start
	gTestID = 52;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	bool enabled = true;

	// Step 01: Attempt to set MI Steering without initializing
	result = dsSetMISteering(-1, enabled);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to set MI Steering using an invalid handle
	result = dsSetMISteering(handle[0], enabled);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);
	}

	// Step 05: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 06: Attempt to set MI Steering after termination
	result = dsSetMISteering(handle[0], enabled);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetGraphicEqualizerMode() retrieves the Graphic Equalizer Mode correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 053@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetGraphicEqualizerMode() by looping through the acquired port handles to get the Graphic Equalizer Mode of each port in array| handle: [valid handles ] , mode: [valid pointer] | dsERR_NONE | A valid Graphic Equalizer Mode must be returned |
 * |04|Call dsGetGraphicEqualizerMode() by looping through the acquired port handles to get the Graphic Equalizer Mode of each port in new array | handle: [valid handles ] , mode: [valid pointer] | dsERR_NONE | A valid Graphic Equalizer Mode must be returned |
 * |05|Compare the array values and make sure they are equal| | dsERR_NONE | The values must be equal |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetGraphicEqualizerMode(void) {
	// Logging at the start
	gTestID = 53;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	int graphicEqModearray1[NUM_OF_PORTS];
	int graphicEqModearray2[NUM_OF_PORTS];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Get the Graphic Equalizer Mode for each port
		result = dsGetGraphicEqualizerMode(handle[i], &graphicEqModearray1[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		UT_ASSERT_TRUE(graphicEqModearray1[i] >= 0 && graphicEqModearray1[i] <= 3);
	}

	// Step 04: Get the Graphic Equalizer Mode for each port in new array
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetGraphicEqualizerMode(handle[i], &graphicEqModearray2[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		UT_ASSERT_TRUE(graphicEqModearray2[i] >= 0 && graphicEqModearray2[i] <= 3);    
	}

	//Step 05: compare the values of graphicEqModea tarrays
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		DS_ASSERT_AUTO_TERM_NUMERICAL(graphicEqModearray1[i], graphicEqModearray2[i]);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetGraphicEqualizerMode() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 054@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetGraphicEqualizerMode() without initializing audio ports | handle = [any value] mode = [valid pointer] | dsERR_NOT_INITIALIZED |dsGetGraphicEqualizerMode call must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetGraphicEqualizerMode() using an invalid handle and valid pointer | handle = [invalid handle] , mode = [valid pointer] | dsERR_INVALID_PARAM |Invalid parameter error must be returned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsGetGraphicEqualizerMode() using an valid handle and invalid pointer | handle = [valid handle] , mode = [invalid pointer] | dsERR_INVALID_PARAM |Invalid parameter error must be returned |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsGetGraphicEqualizerMode() again after terminating audio ports | handle = [valid handle from step 04] , mode = [valid pointer] | dsERR_NOT_INITIALIZED | dsGetGraphicEqualizerMode call must fail as module is not initialized  |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetGraphicEqualizerMode(void) {
	// Logging at the start
	gTestID = 54;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	int graphicEqMode;

	// Step 01: Attempt to get Graphic Equalizer Mode without initializing
	result = dsGetGraphicEqualizerMode(-1, &graphicEqMode);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to get Graphic Equalizer Mode using an invalid handle
	result = dsGetGraphicEqualizerMode(handle[0], &graphicEqMode);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Attempt to get Graphic Equalizer Mode with an invalid pointer
		result = dsGetGraphicEqualizerMode(handle[i], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to get Graphic Equalizer Mode after termination
	result = dsGetGraphicEqualizerMode(handle[0], &graphicEqMode);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetGraphicEqualizerMode() sets the Graphic Equalizer Mode correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 055@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsSetGraphicEqualizerMode() by looping through valid handles and vaild mode value (i.e 0 to 3) | handle = [valid handle], mode = [valid value] | dsERR_NONE |dsSetGraphicEqualizerMode must set the valid values |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsSetGraphicEqualizerMode(void) {
	// Logging at the start
	gTestID = 55;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	int validModes[] = {0, 1, 2, 3}; // Array of valid Graphic Equalizer modes

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Set Graphic Equalizer Mode for each port
		for (int j = 0; j < sizeof(validModes)/sizeof(validModes[0]); j++) {
			result = dsSetGraphicEqualizerMode(handle[i], validModes[j]);
			DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		}
	}

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetGraphicEqualizerMode() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 056@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsSetGraphicEqualizerMode() without initializing audio ports | handle = [any value], mode = [any valid value] | dsERR_NOT_INITIALIZED | dsSetGraphicEqualizerMode call must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetGraphicEqualizerMode() using an invalid handle and valid mode value (i.e 0 to 3) | handle = [invalid handle], mode = [valid values] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsSetGraphicEqualizerMode() by looping through valid handles and using an invalid mode value(i.e < 0 or >3) | handle = [valid handle], mode = [invalid value] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsSetGraphicEqualizerMode() again after terminating audio ports | handle = [valid handle obtained at setp4], mode = [any valid value] | dsERR_NOT_INITIALIZED | dsSetGraphicEqualizerMode call must fail as module is not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsSetGraphicEqualizerMode(void) {
	// Logging at the start
	gTestID = 56;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	int valid_mode = 2, invalid_mode_neg = -1, invalid_mode_pos = 4;

	// Step 01: Attempt to set Graphic Equalizer Mode without initializing
	result = dsSetGraphicEqualizerMode(-1, valid_mode);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to set Graphic Equalizer Mode using an invalid handle
	result = dsSetGraphicEqualizerMode(handle[0], valid_mode);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Attempt to set Graphic Equalizer Mode with an invalid mode value
		result = dsSetGraphicEqualizerMode(handle[i], invalid_mode_neg);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

		result = dsSetGraphicEqualizerMode(handle[i], invalid_mode_pos);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to set Graphic Equalizer Mode after termination
	result = dsSetGraphicEqualizerMode(handle[0], valid_mode);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetMS12AudioProfileList() retrieves the list of supported MS12 audio profiles correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 057@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetMS12AudioProfileList() by looping through the acquired port handles to get the list of supported MS12 audio profiles of each port in array | handle: [valid handles] , profiles: [valid pointer] | dsERR_NONE | List of supported MS12 audio profiles must be returned |
 * |04|Verify that the profiles list is valid and is not empty | | Non-empty list of profiles | |
 * |05|Call dsGetMS12AudioProfileList() by looping through the acquired port handles to get the list of supported MS12 audio profiles of each port in new  array | handle: [valid handles] , profiles: [valid pointer] | dsERR_NONE | List of supported MS12 audio profiles must be returned |
 * |06|Verify that the profiles list is valid and is not empty | | Non-empty list of profiles | |
 * |07|Compare the array values and make sure they are equal| | dsERR_NONE | The values must be equal |
 * |08|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetMS12AudioProfileList(void) {
	// Logging at the start
	gTestID = 57;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	dsMS12AudioProfileList_t profileListarray1[NUM_OF_PORTS];
	dsMS12AudioProfileList_t profileListarray2[NUM_OF_PORTS];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Get the list of supported MS12 audio profiles for each port
		result = dsGetMS12AudioProfileList(handle[i], &profileListarray1[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Step 04: Verify that the profiles list is valid and not empty
		DS_ASSERT_AUTO_TERM_NUMERICAL(profileListarray1[i].audioProfileCount, 0);
		DS_ASSERT_AUTO_TERM_NUMERICAL(strlen(profileListarray1[i].audioProfileList), 0);
	}

	// Step 05: Get the list of supported MS12 audio profiles for each port in new array
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetMS12AudioProfileList(handle[i], &profileListarray2[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Step 06: Verify that the profiles list is valid and not empty
		DS_ASSERT_AUTO_TERM_NUMERICAL(profileListarray2[i].audioProfileCount, 0);
		DS_ASSERT_AUTO_TERM_NUMERICAL(strlen(profileListarray2[i].audioProfileList), 0);    
	}

	//Step 07: compare the values of profileList arrays
	for (int i = 0; i < NUM_OF_PORTS; i++) {

		DS_ASSERT_AUTO_TERM_STRING(profileListarray1[i].audioProfileList, profileListarray2[i].audioProfileList);
		DS_ASSERT_AUTO_TERM_NUMERICAL(profileListarray1[i].audioProfileCount, profileListarray2[i].audioProfileCount);
	}

	// Step 08: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetMS12AudioProfileList() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 058@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetMS12AudioProfileList() without initializing audio ports | handle=[any value], profiles=[valid pointer] | dsERR_NOT_INITIALIZED | dsGetMS12AudioProfileList call must fail as module not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetMS12AudioProfileList() using an invalid handle and valid pointer | handle = [invalid handle], profiles=[valid pointer] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsGetMS12AudioProfileList() by looping through the obtained handles , with a null pointer for profiles | handle =[valid handle], profiles = [NULL] | dsERR_INVALID_PARAM |  Invalid parameter error must be returned |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsGetMS12AudioProfileList() again after terminating audio ports | handle=[valid handle], profiles=[valid pointer] | dsERR_NOT_INITIALIZED | dsGetMS12AudioProfileList call must fail as module not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetMS12AudioProfileList(void) {
	// Logging at the start
	gTestID = 58;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	dsMS12AudioProfileList_t profileList;

	// Step 01: Attempt to get MS12 Audio Profile List without initializing
	result = dsGetMS12AudioProfileList(-1, &profileList);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to get MS12 Audio Profile List using an invalid handle
	result = dsGetMS12AudioProfileList(handle[0], &profileList);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Attempt to get MS12 Audio Profile List with a null pointer
		result = dsGetMS12AudioProfileList(handle[i], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to get MS12 Audio Profile List after termination
	result = dsGetMS12AudioProfileList(handle[0], &profileList);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetMS12AudioProfile() retrieves the current audio profile configured correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 059@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetMS12AudioProfile() by looping through the acquired port handles to get the current audio profile configured for each port | handle: [valid handles ] , profile: [vaild pointer] | dsERR_NONE | The audio profile configured must be returned |
 * |04|Verify that the profile string is valid and is not empty | | Non-empty profile string | |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetMS12AudioProfile(void) {
	// Logging at the start
	gTestID = 59;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {NUM_OF_PORTS};
	char currentProfile[MAX_PROFILE_NAME_LEN];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		if(handle[i] == dsAUDIOPORT_TYPE_SPEAKER) {
			// Step 03: Get the current MS12 audio profile for Speaker. MS12 Audio Profile is supported only on SPEAKER Port
			result = dsGetMS12AudioProfile(handle[i], currentProfile);
			DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

			// Step 04: Verify that the profile string is valid and not empty
			DS_ASSERT_AUTO_TERM_NOT_EQUAL(strlen(currentProfile), 0);
		}

		else {
			result = dsGetMS12AudioProfile(handle[i], currentProfile);
			DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_OPERATION_NOT_SUPPORTED);
		}
	}

	// Step 05: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetMS12AudioProfile() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 060@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetMS12AudioProfile() without initializing audio ports | handle =[any value], profile=[valid pointer] | dsERR_NOT_INITIALIZED |dsGetMS12AudioProfile call must fail as module is not intialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetMS12AudioProfile() using an invalid handle and valid pointer | handle=[invalid handle] , pointer=[valid pointer] | dsERR_INVALID_PARAM | Invalid parameter error must be returned|
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsGetMS12AudioProfile() by looping through valid handles and with a null pointer for profile | handle=[valid handle], profile=[NULL] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsGetMS12AudioProfile() again after terminating audio ports | handle=[valid handle],profile=[valid pointer] | dsERR_NOT_INITIALIZED | dsGetMS12AudioProfile call must fail as module is not intialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetMS12AudioProfile(void) {
	// Logging at the start
	gTestID = 60;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS];
	char currentProfile[MAX_PROFILE_NAME_LEN];

	// Step 01: Attempt to get MS12 Audio Profile without initializing
	result = dsGetMS12AudioProfile(-1, currentProfile);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to get MS12 Audio Profile using an invalid handle
	result = dsGetMS12AudioProfile(handle[0], currentProfile);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get the port handle for all supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Attempt to get MS12 Audio Profile with a null pointer
		if(handle[i] == dsAUDIOPORT_TYPE_SPEAKER) {
			result = dsGetMS12AudioProfile(handle[i], NULL);
			DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
		}
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to get MS12 Audio Profile after termination
	result = dsGetMS12AudioProfile(handle[0], currentProfile);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}

/**
 * @brief Ensure dsGetStereoMode() retrieves the correct stereo mode during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 61@n
 * 
 * **Dependencies:** Audio device should be connected and working properly.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetStereoMode() by looping through the acquired port handles and valid pointer to get the stereo mode setting of each port in array| handle: [ valid handles ] , stereoMode: [valid pointer] | dsERR_NONE | A valid stereo Mode in dsAudioStereoMode_t must be returned |
 * |04|Call dsGetStereoMode() by looping through the acquired port handles and valid pointer to get the stereo mode setting of each port in new array| handle: [ valid handles ] , stereoMode: [valid pointer] | dsERR_NONE | A valid stereo Mode in dsAudioStereoMode_t must be returned |
 * |05|Compare the values and make sure they are equal| | dsERR_NONE | The values must be equal |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetStereoMode(void) {
	// Logging at the start
	gTestID = 61;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	dsAudioStereoMode_t stereoMode1[NUM_OF_PORTS];
	dsAudioStereoMode_t stereoMode2[NUM_OF_PORTS];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Steps 02 to 05: Loop through kPorts and retrieve stereo mode
	for (int i = 0; i < NUM_OF_PORTS; ++i) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Retrieve the stereo mode - first time
		result = dsGetStereoMode(handle[i], &stereoMode1[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Step 04: Retrieve the stereo mode - second time
		result = dsGetStereoMode(handle[i], &stereoMode2[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Step 05: Compare the values
		DS_ASSERT_AUTO_TERM_NUMERICAL(stereoMode1[i], stereoMode2[i]);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetStereoMode() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 62@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsGetStereoMode() without initializing audio ports | handle=[invalid handle] ,stereoMode=[valid pointer]| dsERR_NOT_INITIALIZED | dsGetStereoMode call must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetStereoMode() using an invalid handle and valid pointer | handle=[invalid handle] , stereoMode=[valid pointer] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsGetStereoMode() by looping through the obtained handles and  a NULL pointer for stereoMode in dsGetStereoMode() | handle=[valid handle], stereoMode=[NULL] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsGetStereoMode() again after terminating audio ports | handle=[valid handle], stereoMode=[valid pointer] | dsERR_NOT_INITIALIZED | dsGetStereoMode call must fail as module is not initialized  |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetStereoMode(void) {
	// Logging at the start
	gTestID = 62;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	dsAudioStereoMode_t stereoMode;

	// Step 01: Attempt to get stereo mode without initializing
	result = dsGetStereoMode(-1, &stereoMode);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to get stereo mode using an invalid handle
	result = dsGetStereoMode(handle[0], &stereoMode);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get a valid handle
	for (int i = 0; i < NUM_OF_PORTS; ++i) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Attempt to get stereo mode with a NULL pointer
		result = dsGetStereoMode(handle[i], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports and try again
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to get stereo mode again after termination
	result = dsGetStereoMode(handle[0], &stereoMode);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetStereoMode() sets the stereo mode correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 63@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsSetStereoMode() by looping through acquired handles and valid mode values| handle=[valid handles], mode = [valid values] | dsERR_NONE | Stereo mode should be set successfully |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsSetStereoMode(void) {
	// Logging at the start
	gTestID = 63;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02 to 03: Loop through kPorts and set stereo mode
	for (int i = 0; i < NUM_OF_PORTS; ++i) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Set the stereo mode
		for(dsAudioStereoMode_t stereo_mode = dsAUDIO_STEREO_UNKNOWN; stereo_mode < dsAUDIO_STEREO_MAX; stereo_mode++) {
			result = dsSetStereoMode(handle[i], stereo_mode);
			DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		}
	}

	// Step 05: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetStereoMode() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 64@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsSetStereoMode() without initializing audio ports | handle=[any value], mode=[valid mode value] | dsERR_NOT_INITIALIZED | dsSetStereoMode call must fail as module is not initializes |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetStereoMode() using an invalid handle and valid mode values | handle=[invalid handle], mode=[valid value] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |04|Call dsSetStereoMode() by looping through valid handles and invalid mode(i.e out of range value) | handle =[valid handle], mode=[invalid value] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsSetStereoMode() again after terminating audio ports | handle=[valid handle], mode=[valid value] | dsERR_NOT_INITIALIZED | dsSetStereoMode call must fail as module is not initializes |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsSetStereoMode(void) {
	// Logging at the start
	gTestID = 64;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};

	// Step 01: Attempt to set stereo mode without initializing
	result = dsSetStereoMode(-1, dsAUDIO_STEREO_SURROUND); 
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to set stereo mode using an invalid handle
	result = dsSetStereoMode(handle[0], dsAUDIO_STEREO_SURROUND);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get a valid handle
	for (int i = 0; i < NUM_OF_PORTS; ++i) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 04: Attempt to set stereo mode with an invalid mode
		result = dsSetStereoMode(handle[i], dsAUDIO_STEREO_MAX);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 05: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	result = dsSetStereoMode(handle[0], dsAUDIO_STEREO_SURROUND);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetStereoAuto() retrieves the auto mode correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 65@n
 * 
 * **Dependencies:** Audio device should be connected and working properly.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetStereoAuto() by looping through the acquired port handles and valid pointer to get the current auto mode of each port in array | handle: [valid handles ] , autoMode: [valid pointer] | dsERR_NONE |The current auto mode of audio port must be returned |
 * |04|Call dsGetStereoAuto() by looping through the acquired port handles and valid pointer to get the current auto mode of each port in new array | handle: [valid handles ] , autoMode:[valid pointer] | dsERR_NONE |The current auto mode of audio port must be returned |
 * |05|Compare the values and make sure they are equal| | dsERR_NONE | The values must be equal |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetStereoAuto(void) {
	// Logging at the start
	gTestID = 65;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	int autoMode[NUM_OF_PORTS], autoModeNew[NUM_OF_PORTS];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02 to 04: Loop through kPorts and retrieve auto mode
	for (int i = 0; i < NUM_OF_PORTS; ++i) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Get the current auto mode
		result = dsGetStereoAuto(handle[i], &autoMode[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Step 04: Get the current auto mode in a new variable for comparison
		result = dsGetStereoAuto(handle[i], &autoModeNew[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Step 05: Compare the values
		DS_ASSERT_AUTO_TERM_NUMERICAL(autoMode[i], autoModeNew[i]);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}

/**
 * @brief Ensure dsGetStereoAuto() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 66@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsGetStereoAuto() without initializing audio ports | handle=[any value], autoMode=[valid pointer] | dsERR_NOT_INITIALIZED | call must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetStereoAuto() using an invalid handle and valid mode pointer | handle=[invalid handle] , autoMode=[valid pointer] | dsERR_INVALID_PARAM | Invalid parameter error must be returned|
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsGetStereoAuto() by looping through valid handles and invalid autoMode pointer | handle=[valid handle], autoMode=[NULL] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsGetStereoAuto() again after terminating audio ports | handle=[valid handle], autoMode=[valid pointer] | dsERR_NOT_INITIALIZED | call must fail as module is not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetStereoAuto(void) {
	// Logging at the start
	gTestID = 66;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {NUM_OF_PORTS};
	int autoMode;

	// Step 01: Attempt to get stereo auto without initializing
	result = dsGetStereoAuto(-1, &autoMode);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to get stereo auto using an invalid handle
	result = dsGetStereoAuto(handle[0], &autoMode);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get a valid handle
	for (int i = 0; i < NUM_OF_PORTS; ++i) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Attempt to get stereo auto with a NULL pointer
		result = dsGetStereoAuto(handle[i], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	//Step 07: Attempt to get Stereo Auto after termination
	result = dsGetStereoAuto(handle[0], &autoMode);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetStereoAuto() sets the auto mode correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 67@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsSetStereoAuto() by looping through acquired ports and with valid automode (i.e(0 or 1) TRUE/FALSE)| handle=[valid handle], autoMode=[valid value] | dsERR_NONE | Auto mode should be set to Enabled/Disabled successfully |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsSetStereoAuto(void) {
	// Logging at the start
	gTestID = 67;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {NUM_OF_PORTS};
	int autoMode = 1;

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02 to 03: Loop through kPorts and set auto mode
	for (int i = 0; i < NUM_OF_PORTS; ++i) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Set auto mode for each port
		result = dsSetStereoAuto(handle[i], autoMode);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
	}

	// Step 05: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetStereoAuto() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 68@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsSetStereoAuto() without initializing audio ports | handle=[invalid handle], autoMode=[valid mode] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetStereoAuto() using an invalid handle but with valid autoMode value(i.e TRUE/FALSE) | handle=[invalid handle], autoMode=[valid value] | dsERR_INVALID_PARAM | Invalid parameter must be returned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsSetStereoAuto() using an valid handle but with invalid autoMode value(-1) | handle=[valid handle], autoMode=[invalid value] | dsERR_INVALID_PARAM | Invalid parameter must be returned |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsSetStereoAuto() again after terminating audio ports | handle=[valid handle], autoMode=[valid value]| dsERR_NOT_INITIALIZED |call must fail as module is not initialized|
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsSetStereoAuto(void) {
	// Logging at the start
	gTestID = 68;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {NUM_OF_PORTS};
	int autoMode = 1, invalidAutoMode = -1;

	// Step 01: Attempt to set stereo auto without initializing
	result = dsSetStereoAuto(-1, autoMode);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to set stereo auto using an invalid handle
	result = dsSetStereoAuto(handle[0], autoMode);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get a valid handle
	for (int i = 0; i < NUM_OF_PORTS; ++i) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		//Step 05: Set a invalid auto mode
		result = dsSetStereoAuto(handle[i], invalidAutoMode);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to set auto mode after terminating audio ports
	result = dsSetStereoAuto(handle[0], autoMode);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}

/**
 * @brief Ensure dsGetAudioGain() retrieves the audio gain correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 69@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetAudioGain() by looping through the acquired port handles and get the audio gain of each port in array | handle: [ valid handles ] , gain: [pointer] | dsERR_NONE | A valid audio gain value(-2080 to 480) must be returned |
 * |04|Call dsGetAudioGain() by looping through the acquired port handles and get the audio gain of each port in another array | handle: [ valid handles ] , gain: [pointer] | dsERR_NONE | A valid audio gain value(-2080 to 480) must be returned |
 * |05|Compare the values and make sure they are equal| | dsERR_NONE | The values must be equal |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetAudioGain(void) {
	// Logging at the start
	gTestID = 69; 
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {NUM_OF_PORTS};
	float gainarray[NUM_OF_PORTS];
	float gainarray1[NUM_OF_PORTS];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Steps 02 to 03: Loop through kPorts to get audio gain
	for (int i = 0; i < NUM_OF_PORTS; ++i) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Get audio gain for each port
		result = dsGetAudioGain(handle[i], &gainarray[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		UT_ASSERT_TRUE(gainarray[i] >= -2080 && gainarray[i] <= 480);

		// Step 03: Get audio gain for each port in new array
		result = dsGetAudioGain(handle[i], &gainarray1[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		UT_ASSERT_TRUE(gainarray1[i] >= -2080 && gainarray1[i] <= 480);

		//compare the values of gain arrays
		DS_ASSERT_AUTO_TERM_NUMERICAL(gainarray[i], gainarray1[i]);
	}

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}

/**
 * @brief Ensure dsGetAudioGain() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 70@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsGetAudioGain() without initializing audio ports | handle=[invalid handle], gain=[pointer] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetAudioGain() using an invalid handle and valid pointer |handle=[invalid hanlde], gain=[pointer] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsGetAudioGain() by looping through the acquired valid handle with a NULL gain pointer | handle=[valid handle], gain=[NULL] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsGetAudioGain() again after terminating audio ports |handle=[valid handle], gain=[pointer] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetAudioGain(void) {
	// Logging at the start
	gTestID = 70;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	float gain;

	// Step 01: Attempt to get audio gain without initializing
	result = dsGetAudioGain(-1, &gain);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to get audio gain using an invalid handle
	result = dsGetAudioGain(handle[0], &gain);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get a valid handle
	for (int i = 0; i < NUM_OF_PORTS; ++i) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Attempt to get audio gain using a valid handle but null pointer for gain
		result = dsGetAudioGain(handle[i], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports and try again
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to get the Audio Gain after termination
	result = dsGetAudioGain(handle[0], &gain);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetAudioGain() sets the audio gain correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 71@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsSetAudioGain() by looping through the ports and with valid gain value |handle=[valid handle], gain=[valid value] | dsERR_NONE | Gain should be set successfully |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsSetAudioGain(void) {
	// Logging at the start
	gTestID = 71;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	float gain_min = -2080, gain_max = 480, gain_mid = -200;

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02 to 03: Loop through kPorts and set audio gain
	for (int i = 0; i < NUM_OF_PORTS; ++i) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Set audio gain for each port
		result = dsSetAudioGain(handle[i], gain_min);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		result = dsSetAudioGain(handle[i], gain_max);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		result = dsSetAudioGain(handle[i], gain_mid);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
	}

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetAudioGain() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 72@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsSetAudioGain() without initializing audio ports | handle=[invalid handle], gain=[valid value] | dsERR_NOT_INITIALIZED |call must fail as module not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetAudioGain() using an invalid handle with valid gain value | handle=[invalid handle], gain=[valid value] |dsERR_INVALID_PARAM |Invalid parameter must return |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsSetAudioGain() by looping through acquired handles with an out of range gain value(not in range 2080 to 480) | handle=[valid handle], gain=[invalid value] | dsERR_INVALID_PARAM| Invalid parameter must return|
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsSetAudioGain() again after terminating audio ports | handle=[valid handle], gain=[valid value] | dsERR_NOT_INITIALIZED |call must fail as module not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsSetAudioGain(void) {
	// Logging at the start
	gTestID = 72;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	float gainValue = 200, invalid_gain_neg = -3000, invalid_gain_pos = 500;

	// Step 01: Attempt to set audio gain without initializing
	result = dsSetAudioGain(-1, gainValue);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to set audio gain using an invalid handle
	result = dsSetAudioGain(handle[0], gainValue);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get a valid handle
	for (int i = 0; i < NUM_OF_PORTS; ++i) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Attempt to set audio gain using a valid handle but out of range gain value
		result = dsSetAudioGain(handle[i], invalid_gain_neg);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

		result = dsSetAudioGain(handle[i], invalid_gain_pos);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt t set audio gain after termination
	result = dsSetAudioGain(handle[0], gainValue);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetAudioDB() retrieves the audio dB level correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 073@n
 * 
 * **Dependencies:** Audio device should be connected and working properly.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetAudioDB() by looping through the acquired port handles to get the audio dB level of each port in array| handle: [ loop through valid handles ] , db: [pointer to hold the audio dB level] | dsERR_NONE | A valid audio dB level( -1450 to 180 dB ) must be returned |
 * |04|Call dsGetAudioDB() by looping through the acquired port handles to get the audio dB level of each port in new array| handle: [valid handles], db: [pointer to hold the audio dB level] | dsERR_NONE | A valid audio dB level( -1450 to 180 dB ) must be returned |
 * |05|Compare the values and make sure they are equal| | dsERR_NONE | The values must be equal |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetAudioDB(void) {
	// Logging at the start
	gTestID = 73;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS];

	float dbArray1[NUM_OF_PORTS], dbArray2[NUM_OF_PORTS];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Steps 02 to 05: Loop through kPorts to get audio dB levels
	for (int i = 0; i < NUM_OF_PORTS; ++i) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Get audio dB for each port in array 1
		result = dsGetAudioDB(handle[i], &dbArray1[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		UT_ASSERT_TRUE(dbArray1[i] >= -1450 && dbArray1[i] <= 180); // comparing if the values obtained are within the dB range

		// Step 04: Get audio dB for each port in array 2
		result = dsGetAudioDB(handle[i], &dbArray2[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		UT_ASSERT_TRUE(dbArray2[i] >= -1450 && dbArray2[i] <= 180); // comparing if the values obtained are within the dB range

		// Step 05: Compare and make sure they are equal
		DS_ASSERT_AUTO_TERM_NUMERICAL(dbArray1[i], dbArray2[i]);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetAudioDB() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 74@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsGetAudioDB() without initializing audio ports | handle=[invalid handle], db=[pointer] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetAudioDB() using an invalid handle and valid pointer |handle=[invalid hanlde], db=[pointer] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsGetAudioDB() by looping through the acquired valid handle with a NULL gain pointer |handle=[valid handle], db=[NULL] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |05|Call dsGetAudioDB() again after terminating audio ports |handle=[valid handle], db=[pointer] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized|
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetAudioDB(void) {
	// Logging at the start
	gTestID = 74;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	float db;

	// Step 01: Attempt to call dsGetAudioDB without initializing audio ports
	result = dsGetAudioDB(-1, &db);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to call dsGetAudioDB with invalid handle
	result = dsGetAudioDB(handle[0], &db);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get a valid handle
	for (int i = 0; i < NUM_OF_PORTS; ++i) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Attempt to call dsGetAudioDB with a NULL pointer for db
		result = dsGetAudioDB(handle[i], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to call dsGetAudioDB after audio ports have been terminated
	result = dsGetAudioDB(handle[0], &db);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetAudioDB() sets the audio dB level correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 75@n
 * 
 * **Dependencies:**None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsSetAudioDB() by looping through acquired port handles and valid db value in expected range(i.e Max dB is 180 and Min dB is -1450) | handle=[valid handle], db=[valid value] | dsERR_NONE | dB level should be set successfully |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsSetAudioDB(void) {
	// Logging at the start
	gTestID = 75;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	float db_max = 180, db_min = -1450, db_mid = -500;

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Get a valid handle
	for (int i = 0; i < NUM_OF_PORTS; ++i) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Set the audio dB level for the acquired port handle
		result = dsSetAudioDB(handle[i], db_max);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		result = dsSetAudioDB(handle[i], db_min);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		result = dsSetAudioDB(handle[i], db_mid);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
	}

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetAudioDB() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 076@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsSetAudioDB() without initializing audio ports | handle=[invalid handle], db=[valid value] | dsERR_NOT_INITIALIZED |call must fail as module not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetAudioDB() using an invalid handle with valid gain value | handle=[invalid handle], db=[valid value] |dsERR_INVALID_PARAM |Invalid parameter must return |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |04|Call dsSetAudioDB() by looping through acquired handles with an out of range db value(i.e >180 and <-1450) | handle=[valid handle], db=[invalid value] | dsERR_INVALID_PARAM| Invalid parameter must return|
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsSetAudioDB() again after terminating audio ports | handle=[valid handle], db=[valid value] | dsERR_NOT_INITIALIZED |call must fail as module not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsSetAudioDB(void) {
	// Logging at the start
	gTestID = 76;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	float valid_db = 100, invalid_db_neg = -1500, invalid_db_pos = 200;

	// Step 01: Attempt to call dsSetAudioDB without initializing audio ports
	result = dsSetAudioDB(-1, valid_db);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to call dsSetAudioDB with invalid handle
	result = dsSetAudioDB(handle[0], valid_db);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get a valid handle
	for (int i = 0; i < NUM_OF_PORTS; ++i) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Attempt to call dsSetAudioDB with an out of range db value
		result = dsSetAudioDB(handle[i], invalid_db_neg); 
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

		result = dsSetAudioDB(handle[i], invalid_db_pos); 
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to call dsSetAudioDB after audio ports have been terminated
	result = dsSetAudioDB(handle[0], valid_db);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Logging at the end
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetAudioLevel() retrieves the audio volume level correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 077@n
 * 
 * **Dependencies:**.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetAudioLevel() by looping through the acquired port handles to get the current audio/volume level of each port in array| handle: [ loop through valid handles ] , level: [pointer to hold the audio level] | dsERR_NONE | A valid audio/volume level(0 to 100) must be returned |
 * |04||Call dsGetAudioLevel() by looping through the acquired port handles to get the current audio/volume level of each port in new array| handle: [ loop through valid handles ] , level: [pointer to hold the audio level] | dsERR_NONE | A valid audio/volume level(0 to 100) must be returned |
 * |05|Compare the values and make sure they are equal| | dsERR_NONE | The values must be equal |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetAudioLevel(void) {
	// Start of the test
	gTestID = 77; 
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};

	float audioLevel1[NUM_OF_PORTS];
	float audioLevel2[NUM_OF_PORTS];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Get port handles 
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Get the audio level values
		result = dsGetAudioLevel(handle[i], &audioLevel1[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		UT_ASSERT_TRUE(audioLevel1[i] >= 0 && audioLevel1[i] <= 100);

		// Step 04: Retrieve audio levels again 
		result = dsGetAudioLevel(handle[i], &audioLevel2[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		UT_ASSERT_TRUE(audioLevel2[i] >= 0 && audioLevel2[i] <= 100);
	}

	// Step 05: Compare values
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		DS_ASSERT_AUTO_TERM_NUMERICAL(audioLevel1[i], audioLevel2[i]);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}

/**
 * @brief Ensure dsGetAudioLevel() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 078@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsGetAudioLevel() without initializing audio ports | handle=[invalid handle], level=[pointer] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetAudioLevel() using an invalid handle and valid pointer |handle=[invalid hanlde], level=[pointer] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|CalldsGetAudioLevel() by looping through the acquired valid handle with a NULL gain pointer |handle=[valid handle], level=[NULL] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsGetAudioLevel() again after terminating audio ports |handle=[valid handle], level=[pointer] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized|
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetAudioLevel(void) {
	// Start of the test
	gTestID = 78;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};

	float audioLevel;

	// Step 01: Attempt to get audio level without initializing audio ports
	result = dsGetAudioLevel(-1, &audioLevel);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to get audio level with invalid handle
	result = dsGetAudioLevel(handle[0], &audioLevel);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04 : Get a valid handle 
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Attempt to get audio level with NULL pointer     
		result = dsGetAudioLevel(handle[i], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to get audio level after terminating audio ports
	result = dsGetAudioLevel(handle[0], &audioLevel);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetAudioLevel() sets the audio volume level correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 079@n
 * 
 * **Dependencies:** Audio device should be connected and working properly.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsSetAudioLevel() by looping through the acquired port handles and valid value(i.e 0 to 100) | handle=[valid handle], level=[valid value] | dsERR_NONE | Volume level should be set successfully |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsSetAudioLevel(void) {
	// Start of the test
	gTestID = 79;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	float minAudioLevel = 0, maxAudioLevel = 100, midAudioLevel = 50; 

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02 and 03: Get port handles and set audio levels
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		result = dsSetAudioLevel(handle[i], minAudioLevel);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		result = dsSetAudioLevel(handle[i], maxAudioLevel);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		result = dsSetAudioLevel(handle[i], midAudioLevel);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
	}

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}

/**
 * @brief Ensure dsSetAudioLevel() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 080@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsSetAudioLevel() without initializing audio ports | handle=[invalid handle], level=[valid value] | dsERR_NOT_INITIALIZED |call must fail as module not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetAudioLevel() using an invalid handle with valid level value | handle=[invalid handle], level=[valid value] |dsERR_INVALID_PARAM |Invalid parameter must return |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsSetAudioLevel() by looping through acquired handles with an out of range level value(i.e <0 or >100)) | handle=[valid handle], level=[invalid value] | dsERR_INVALID_PARAM| Invalid parameter must return|
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsSetAudioLevel() again after terminating audio ports | handle=[valid handle], level=[valid value] | dsERR_NOT_INITIALIZED |call must fail as module not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsSetAudioLevel(void) {
	// Start of the test
	gTestID = 80;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	float audio_level = 50, invalid_audio_level_neg = -10, invalid_audio_level_pos = 120;

	// Step 01: Attempt to set audio level without initializing audio ports
	result = dsSetAudioLevel(-1, audio_level);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to set audio level with invalid handle
	result = dsSetAudioLevel(handle[0], audio_level);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04 : Get a valid handle 
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05 : Attempt to set Audio level with invalid values
		result = dsSetAudioLevel(handle[i], invalid_audio_level_neg); 
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

		result = dsSetAudioLevel(handle[i], invalid_audio_level_pos); 
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to set audio level after terminating audio ports
	result = dsSetAudioLevel(handle[0], audio_level);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetAudioMaxDB() retrieves the maximum audio dB level correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 81@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetAudioMaxDB() by looping through the acquired port handles to get the maximum audio dB of each port in array| handle: [ loop through valid handles ] , maxDb: [pointer to hold the maximum audio dB value] | dsERR_NONE | A valid maximum audio dB value(maximum value can be 180 dB) must be returned |
 * |04|Call dsGetAudioMaxDB() by looping through the acquired port handles to get the maximum audio dB of each port in new  array| handle: [ loop through valid handles ] , maxDb: [pointer to hold the maximum audio dB value] | dsERR_NONE | A valid maximum audio dB value(maximum value can be 180 dB) must be returned |
 * |05|Compare the values and make sure they are equal| | dsERR_NONE | The values must be equal |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetAudioMaxDB(void) {
	// Start of the test
	gTestID = 81;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	float maxDbArray1[NUM_OF_PORTS]; 
	float maxDbArray2[NUM_OF_PORTS]; 

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02 and 03: Get port handles and retrieve max dB values
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		result = dsGetAudioMaxDB(handle[i], &maxDbArray1[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		UT_ASSERT_TRUE(maxDbArray1[i] <= 180); // Checks whether max dB value is not beyond 180

		result = dsGetAudioMaxDB(handle[i], &maxDbArray2[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		UT_ASSERT_TRUE(maxDbArray2[i] <= 180); // Checks whether max dB value is not beyond 180
	}

	// Step 05: Compare the values from both arrays
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		DS_ASSERT_AUTO_TERM_NUMERICAL(maxDbArray1[i], maxDbArray2[i]);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetAudioMaxDB() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 082@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsGetAudioMaxDB() without initializing audio ports | handle=[invalid handle], maxDb=[pointer] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetAudioMaxDB() using an invalid handle and valid pointer |handle=[invalid hanlde], maxDb=[pointer] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsGetAudioMaxDB() by looping through the acquired valid handle with a NULL gain pointer |handle=[valid handle], maxDb=[NULL] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsGetAudioMaxDB() again after terminating audio ports |handle=[valid handle], maxDb=[pointer] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized|
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetAudioMaxDB(void) {
	// Start of the test
	gTestID = 82;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	float maxDb;

	// Step 01: Attempt to get max dB without initializing audio ports
	result = dsGetAudioMaxDB(-1, &maxDb);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to get max dB with invalid handle
	result = dsGetAudioMaxDB(handle[0], &maxDb);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get a valid handle 
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05 : Attempt to get Audio Max dB with a NULL pointer
		result = dsGetAudioMaxDB(handle[i], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to get max dB after terminating audio ports
	result = dsGetAudioMaxDB(handle[0], &maxDb);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetAudioMinDB() retrieves the minimum audio dB level correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 083@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetAudioMinDB() by looping through the acquired port handles to get the minimum audio dB of each port in array| handle: [ loop through valid handles ] , minDb: [pointer to hold the minimum audio dB value] | dsERR_NONE | A valid minimum audio dB value(minimum value can be -1450 dB) must be returned |
 * |04|Call dsGetAudioMinDB() by looping through the acquired port handles to get the minimum audio dB of each port in new array| handle: [ loop through valid handles ] , minDb: [pointer to hold the minimum audio dB value] | dsERR_NONE | A valid minimum audio dB value(minimum value can be -1450 dB) must be returned |
 * |05|Compare the values and make sure they are equal| | dsERR_NONE | The values must be equal |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetAudioMinDB(void) {
	// Start of the test
	gTestID = 83;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	float minDbArray1[NUM_OF_PORTS]; // First array for min dB values
	float minDbArray2[NUM_OF_PORTS]; // Second array for min dB values

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02 : Get port handles
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Retrieve min dB values
		result = dsGetAudioMinDB(handle[i], &minDbArray1[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		UT_ASSERT_TRUE(minDbArray1[i] >= -1450);

		// Step 04: Retrieve min dB values again and store it in a new array
		result = dsGetAudioMinDB(handle[i], &minDbArray2[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		UT_ASSERT_TRUE(minDbArray2[i] >= -1450);

		// Step 05: Compare the values
		UT_ASSERT_EQUAL(minDbArray1[i], minDbArray2[i]);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetAudioMinDB() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 084@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsGetAudioMinDB() without initializing audio ports | handle=[invalid handle], minDb=[pointer] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetAudioMinDB() using an invalid handle and valid pointer |handle=[invalid hanlde], minDb=[pointer] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsGetAudioMinDB() by looping through the acquired valid handle with a NULL gain pointer |handle=[valid handle], minDb=[NULL] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsGetAudioMinDB() again after terminating audio ports |handle=[valid handle], minDb=[pointer] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized|
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetAudioMinDB(void) {
	// Start of the test
	gTestID = 84;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	float minDb;

	// Step 01: Attempt to get min dB without initializing audio ports
	result = dsGetAudioMinDB(-1, &minDb);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to get min dB with invalid handle
	result = dsGetAudioMinDB(handle[0], &minDb);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get a valid handle
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Attempt to get Audio Min dB with a NULL pointer
		result = dsGetAudioMinDB(handle[i], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to get min dB after terminating audio ports
	result = dsGetAudioMinDB(handle[0], &minDb);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetAudioOptimalLevel() retrieves the optimal audio level correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 085@n
 * 
 * **Dependencies:** Audio device should be connected and working properly.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetAudioOptimalLevel() by looping through the acquired port handles to get the optimal audio level (dB) of each port in array| handle: [ loop through valid handles ] , optimalLevel: [pointer to hold the optimal audio level] | dsERR_NONE | A valid optimum audio dB value( -1450 dB to 180 dB) must be returned - platform specific |
 * |04|Call dsGetAudioOptimalLevel() by looping through the acquired port handles to get the optimal audio level (dB) of each port in new array| handle: [ loop through valid handles ] , optimalLevel: [pointer to hold the optimal audio level] | dsERR_NONE | A valid optimum audio dB value( -1450 dB to 180 dB) must be returned - platform specific |
 * |05|Compare the values and make sure they are equal| | dsERR_NONE | The values must be equal |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetAudioOptimalLevel(void) {
	// Start of the test
	gTestID = 85;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	float optimalLevelArray1[NUM_OF_PORTS];
	float optimalLevelArray2[NUM_OF_PORTS];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02 : Get port handles 
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Retrieve optimal dB levels
		result = dsGetAudioOptimalLevel(handle[i], &optimalLevelArray1[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Step 04: Retrieve optimal dB levels and store it in a new array
		result = dsGetAudioOptimalLevel(handle[i], &optimalLevelArray2[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Step 05: Compare the values
		DS_ASSERT_AUTO_TERM_NUMERICAL(optimalLevelArray1[i], optimalLevelArray2[i]);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetAudioOptimalLevel() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 086@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsGetAudioOptimalLevel() without initializing audio ports|handle=[invalid handle], optimalLevel=[pointer]|dsERR_NOT_INITIALIZED |call must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetAudioOptimalLevel() using an invalid handle and valid pointer |handle=[invalid hanlde], optimalLevel=[pointer] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsGetAudioOptimalLevel() by looping through the acquired valid handle with a NULL gain pointer |handle=[valid handle], optimalLevel=[NULL] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsGetAudioOptimalLevel() again after terminating audio ports |handle=[valid handle], optimalLevel=[pointer] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized|
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetAudioOptimalLevel(void) {
	// Start of the test
	gTestID = 86;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	float optimalLevel;

	// Step 01: Attempt to get optimal dB without initializing audio ports
	result = dsGetAudioOptimalLevel(-1, &optimalLevel);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to get optimal dB with invalid handle
	result = dsGetAudioOptimalLevel(handle[0], &optimalLevel);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get a valid handle 
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05 :Attempt to get optimal level with a NULL pointer
		result = dsGetAudioOptimalLevel(handle[i], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to get optimal dB after terminating audio ports
	result = dsGetAudioOptimalLevel(handle[0], &optimalLevel);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetAudioDelay() retrieves the audio delay correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 087@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetAudioDelay() by looping through the acquired port handles to get the audio audio delay (in ms) of each port in array | handle: [ loop through valid handles ] , audioDelayMs: [ pointer to hold the audio delay ] | dsERR_NONE | A valid audio delay value(0 to 200 ms) must be returned |
 * |04|Call dsGetAudioDelay() by looping through the acquired port handles to get the audio audio delay (in ms) of each port in new array | handle: [ loop through valid handles ] , audioDelayMs: [ pointer to hold the audio delay ] | dsERR_NONE | A valid audio delay value(0 to 200 ms) must be returned |
 * |05|Compare the values and make sure they are equal| | dsERR_NONE | The values must be equal |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetAudioDelay(void) {
	// Start of the test
	gTestID = 87;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	uint32_t audioDelayArray1[NUM_OF_PORTS];
	uint32_t audioDelayArray2[NUM_OF_PORTS];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02 : Get port handles
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03 : Retrieve audio delay
		result = dsGetAudioDelay(handle[i], &audioDelayArray1[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		UT_ASSERT_TRUE(audioDelayArray1[i] >= 0 && audioDelayArray1[i] <= 200);

		// Step 04 : Retrieve audio delay and store it in a new array
		result = dsGetAudioDelay(handle[i], &audioDelayArray2[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		UT_ASSERT_TRUE(audioDelayArray2[i] >= 0 && audioDelayArray2[i] <= 200);

		// Step 05: Compare the values
		DS_ASSERT_AUTO_TERM_NUMERICAL(audioDelayArray1[i], audioDelayArray2[i]);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetAudioDelay() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 088@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsGetAudioDelay() without initializing audio ports | handle=[invalid handle], audioDelayMs=[pointer] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetAudioDelay() using an invalid handle and valid pointer |handle=[invalid hanlde], audioDelayMs=[pointer] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsGetAudioDelay() by looping through the acquired valid handle with a NULL gain pointer |handle=[valid handle], audioDelayMs=[NULL] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsGetAudioDelay() again after terminating audio ports |handle=[valid handle], audioDelayMs=[pointer] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized|
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetAudioDelay(void) {
	// Start of the test
	gTestID = 88;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	uint32_t audioDelay;

	// Step 01: Attempt to get audio delay without initializing audio ports
	result = dsGetAudioDelay(-1, &audioDelay);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to get audio delay with invalid handle
	result = dsGetAudioDelay(handle[0], &audioDelay);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get Valid port handles
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Attempt to get Audio delay with NULL param
		result = dsGetAudioDelay(handle[i], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to get audio delay after terminating audio ports
	result = dsGetAudioDelay(handle[0], &audioDelay);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetAudioDelay() sets the audio delay correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 089@n
 * 
 * **Dependencies:**@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsSetAudioDelay() by looping through the acquired port handle and valid audio delay value(.ie value in milliseconds) | handle=[valid handle], audioDelayMs=[valid value] | dsERR_NONE | call should set audio delay successfully |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsSetAudioDelay(void) {
	// Start of the test
	gTestID = 89;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	uint32_t audio_delay_min = 0, audio_delay_mid = 100, audio_delay_max = 200;

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02 : Get port handles 
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Set audio delay
		result = dsSetAudioDelay(handle[i], audio_delay_min);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		result = dsSetAudioDelay(handle[i], audio_delay_mid);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		result = dsSetAudioDelay(handle[i], audio_delay_max);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
	}

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetAudioDelay() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 090@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsSetAudioDelay() without initializing audio ports | handle=[invalid handle], audioDelayMs=[valid value] | dsERR_NOT_INITIALIZED |call must fail as module not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetAudioDelay() using an invalid handle with valid audio delay value(i.e milliseconds) | handle=[invalid handle], audioDelayMs=[valid value] |dsERR_INVALID_PARAM |Invalid parameter must return |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsSetAudioDelay() using a valid handle but with invalid audio delay values(i.e milliseconds) | handle=[valid handle], audioDelayMs=[invalid value] |dsERR_INVALID_PARAM |Invalid parameter must return |
 * |07|Call dsSetAudioDelay() again after terminating audio ports | handle=[valid handle], audioDelayMs=[valid value] | dsERR_NOT_INITIALIZED |call must fail as module not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsSetAudioDelay(void) {
	// Start of the test
	gTestID = 90;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS];
	uint32_t audio_delay = 100, invalid_audio_delay = 300;

	// Step 01: Attempt to set audio delay without initializing audio ports
	result = dsSetAudioDelay(-1, audio_delay);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to set audio delay 
	result = dsSetAudioDelay(handle[0], audio_delay);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04 : Get port handles 
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Attempt to set invalid audio delay 
		result = dsSetAudioDelay(handle[i], invalid_audio_delay);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

		// Step 04: Terminate audio ports
		result = dsAudioPortTerm();
		UT_ASSERT_EQUAL(result, dsERR_NONE);

		// Step 05: Attempt to set audio delay after terminating audio ports
		result = dsSetAudioDelay(handle[0], audio_delay);
		UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

		// End of the test
		UT_LOG("\n Out %s\n", __FUNCTION__);
	}
}

/**
 * @brief Ensure dsGetAudioDelayOffset() retrieves the audio delay offset correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 091@n
 * 
 * **Dependencies:**@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetAudioDelayOffset() by looping through the acquired port handles to get the audio audio delay offset(in milliseconds) of each port | handle: [valid handles] , audioDelayOffsetMs:[valid pointer ] | dsERR_NONE | A valid audio delay offset value must be returned |
 * |04||03|Call dsGetAudioDelayOffset() by looping through the acquired port handles to get the audio audio delay offset(in milliseconds) of each port  and store it in a new array | handle: [valid handles] , audioDelayOffsetMs:[valid pointer ] | dsERR_NONE | A valid audio delay offset value must be returned |
 * |05|Compare the values and make sure they are equal| | dsERR_NONE | The values must be equal |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetAudioDelayOffset(void) {
	// Start of the test
	gTestID = 91;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	uint32_t audioDelayOffsetMs1[NUM_OF_PORTS];
	uint32_t audioDelayOffsetMs2[NUM_OF_PORTS];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02 : Get port handles 
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Retrieve audio delay offset    
		result = dsGetAudioDelayOffset(handle[i], &audioDelayOffsetMs1[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Step 04: Retrieve audio delay offset    
		result = dsGetAudioDelayOffset(handle[i], &audioDelayOffsetMs2[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Step 05: Compare the values
		DS_ASSERT_AUTO_TERM_NUMERICAL(audioDelayOffsetMs1[i], audioDelayOffsetMs2[i]);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetAudioDelayOffset() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 092@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsGetAudioDelayOffset() without initializing audio ports | handle=[invalid handle], audioDelayOffsetMs=[valid pointer] | dsERR_NOT_INITIALIZED |call must fail as module not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetAudioDelayOffset() using an invalid handle with valid delay offset value | handle=[invalid handle], audioDelayOffsetMs=[valid pointer] |dsERR_INVALID_PARAM |Invalid parameter must return |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsGetAudioDelayOffset() by looping through the acquired valid handle with a NULL delay offset pointer |handle=[valid handle], audioDelayOffsetMs=[NULL] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsGetAudioDelayOffset() again after terminating audio ports |handle=[valid handle], audioDelayOffsetMs=[pointer] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized|
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetAudioDelayOffset(void) {
	// Start of the test
	gTestID = 92;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	uint32_t audioDelayOffsetMs;

	// Step 01: Attempt to retrieve audio delay offset without initializing audio ports
	result = dsGetAudioDelayOffset(-1, &audioDelayOffsetMs);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to retrieve audio delay offset with invalid handle
	result = dsGetAudioDelayOffset(handle[0], &audioDelayOffsetMs);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04 : Get the port handles
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Attempt to retrieve audio delay offset using NULL pointer
		result = dsGetAudioDelayOffset(handle[i], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NOT_INITIALIZED);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to retrieve audio delay offset after terminating audio ports
	result = dsGetAudioDelayOffset(handle[0], &audioDelayOffsetMs);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}

/**
 * @brief Ensure dsSetAudioDelayOffset() sets the audio delay offset correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 093@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsSetAudioDelayOffset() by looping through acquired port handles and valid audio delay offset value(i.e milliseconds) | handle=[valid handle], audioDelayOffsetMs=[valid value] | dsERR_NONE | audio delay offset should be successfully set |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsSetAudioDelayOffset(void) {
	// Start of the test
	gTestID = 93;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	uint32_t audioDelayOffsetMs = 200;

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02 : Get port handles 
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03 : set audio delay offset
		result = dsSetAudioDelayOffset(handle[i], audioDelayOffsetMs);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
	}

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetAudioDelayOffset() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 094@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsSetAudioDelayOffset() without initializing audio ports | handle=[invalid handle], audioDelayOffsetMs=[valid value] | dsERR_NOT_INITIALIZED |call must fail as module not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetAudioDelayOffset() using an invalid handle with valid audio delay offset value(i.e milliseconds) | handle=[invalid handle], audioDelayOffsetMs=[valid value] |dsERR_INVALID_PARAM |Invalid parameter must return |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsSetAudioDelayOffset() using an valid handle with invalid audio delay offset value(i.e milliseconds) | handle=[valid handle], audioDelayOffsetMs=[invalid value] |dsERR_INVALID_PARAM |Invalid parameter must return |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsSetAudioDelayOffset() again after terminating audio ports | handle=[valid handle], audioDelayOffsetMs=[valid value] | dsERR_NOT_INITIALIZED |call must fail as module not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsSetAudioDelayOffset(void) {
	// Start of the test
	gTestID = 94;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	dsError_t result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	uint32_t audio_delay_offset = 200 , invalid_audio_delay_offset= 300; 

	// Step 01: Attempt to set audio delay offset without initializing audio ports
	result = dsSetAudioDelayOffset(-1, audio_delay_offset);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to set audio delay offset with invalid handle
	result = dsSetAudioDelayOffset(handle[0], audio_delay_offset);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get the port handles
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05 : Set audio delay offset with invalid audio delay offset values
		result = dsSetAudioDelayOffset(handle[i], invalid_audio_delay_offset);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to set audio delay offset after terminating audio ports
	result = dsSetAudioDelayOffset(handle[0], audio_delay_offset);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}

/**
 * @brief Ensure dsSetAudioAtmosOutputMode() sets the Audio ATMOS output mode correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 95@n
 * 
 * **Dependencies:** Audio device should be connected and working properly.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsSetAudioAtmosOutputMode() - by looping through the acquired port handles to enable Audio ATMOS output mode | handle = [valid handle], enable = [TRUE] | dsERR_NONE | Atmos mode must be enabled for all supported audio ports |
 * |04|Call dsSetAudioAtmosOutputMode() - by looping through the acquired port handles to disable Audio ATMOS output mode | handle = [valid handle], enable = [FALSE] | dsERR_NONE | Atmos mode must be enabled for all supported audio ports |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsSetAudioAtmosOutputMode(void) {
	// Start of the test
	gTestID = 95; // Assuming Test Case ID is 238
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	bool enable = true , disable = false;

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02, 03 and 04: Get port handles and set ATMOS Output mode
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Enable ATMOS Output mode
		result = dsSetAudioAtmosOutputMode(handle[i], enable);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Disable ATMOS Output mode
		result = dsSetAudioAtmosOutputMode(handle[i], disable);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
	}

	// Step 05: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetAudioAtmosOutputMode() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 96@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsSetAudioAtmosOutputMode() - Attempt to set the audio ATMOS output mode without initializing audio ports | handle = [invalid handle], enable = [TRUE] | dsERR_NOT_INITIALIZED | Set ATMOS Output mode must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetAudioAtmosOutputMode() using an invalid handle with valid value| handle = [invalid handle], enable = [TRUE] | dsERR_INVALID_PARAM | Invalid parameter error must be returned  |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsSetAudioAtmosOutputMode() - Again attempt to set the audio ATMOS output mode without initializing audio ports | handle = [valid handle], enable = [TRUE] | dsERR_NOT_INITIALIZED | Set ATMOS Output mode must fail as module is not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED, dsERR_GENERAL and  might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsSetAudioAtmosOutputMode(void) {
	// Start of the test
	gTestID = 96;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	bool valid_value = true;

	// Step 01: Attempt to set ATMOS Output mode without initializing audio ports
	result = dsSetAudioAtmosOutputMode(-1, valid_value);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to set ATMOS Output mode with invalid handle
	result = dsSetAudioAtmosOutputMode(handle[0], valid_value);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	//Step 04 : Get audio port handles
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);
	}

	// Step 05: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 06: Attempt to set ATMOS Output mode after terminating audio ports
	result = dsSetAudioAtmosOutputMode(handle[0], valid_value);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetSinkDeviceAtmosCapability() retrieves the ATMOS capability correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 97@n
 * 
 * **Dependencies:**@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetSinkDeviceAtmosCapability() by looping through the acquired port handles to get the  ATMOS capability of sink device connected to each port in array | handle: [ valid handles ] , capability: [vaild pointer to hold the ATMOS capability] | dsERR_NONE | A valid ATMOS capability of sink device must be returned |
 * |04|Call dsGetSinkDeviceAtmosCapability() by looping through the acquired port handles to get the  ATMOS capability of sink device connected to each port in new array | handle: [valid handles ] , capability: [pointer to hold the ATMOS capability] | dsERR_NONE | A valid ATMOS capability of sink device must be returned |
 * |05|Compare the array values and make sure they are equal| | dsERR_NONE | The values must be equal |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetSinkDeviceAtmosCapability(void) {
	// Start of the test
	gTestID = 97; // Assuming Test Case ID is 240
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	dsATMOSCapability_t atmosCapability[NUM_OF_PORTS];
	dsATMOSCapability_t atmosCapability1[NUM_OF_PORTS];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02 Get audio port handles
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		//Step 03 : Get ATMOS capability of ports in array
		result = dsGetSinkDeviceAtmosCapability(handle[i], &atmosCapability[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		//Step 04 : Get ATMOS capability of ports in new array
		result = dsGetSinkDeviceAtmosCapability(handle[i], &atmosCapability1[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		//Step 05 : compare the atomos capability of arrays
		DS_ASSERT_AUTO_TERM_NUMERICAL(atmosCapability[i], atmosCapability1[i]);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetSinkDeviceAtmosCapability() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 98@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsGetSinkDeviceAtmosCapability() - Attempt to get the ATMOS capability of sink device without initializing audio ports | handle = [ invalid handle], capability = [valid pointer to hold the ATMOS capability] | dsERR_NOT_INITIALIZED | Get Atmos capability of sink device must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetSinkDeviceAtmosCapability() using an invalid handle | handle = [invalid handle], capability = [valid pointer to hold ATMOS capability] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsGetSinkDeviceAtmosCapability() - by looping through acquired port handles with NULL pointer for ATMOS capability | handle = [loop through valid handles], capability = [NULL] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsGetSinkDeviceAtmosCapability() - Again attempt to get the ATMOS capability of sink device after terminating audio ports | handle = [valid handle], capability = [valid pointer to hold the ATMOS capability] | dsERR_NOT_INITIALIZED | Get Atmos capability of sink device must fail as module is not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetSinkDeviceAtmosCapability(void) {
	// Start of the test
	gTestID = 98;
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t handle [NUM_OF_PORTS] = {NUM_OF_PORTS};
	dsATMOSCapability_t atmosCapability;

	// Step 01: Attempt to get ATMOS capability without initializing audio ports
	result = dsGetSinkDeviceAtmosCapability(-1, &atmosCapability);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to get ATMOS capability with invalid handle
	result = dsGetSinkDeviceAtmosCapability(handle[0], &atmosCapability);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get audio ports handles
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		
		// Step 05: Attempt to get ATMOS capability with Null capability pointer
		result = dsGetSinkDeviceAtmosCapability(handle[i], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}    

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to get ATMOS capability after terminating audio ports
	result = dsGetSinkDeviceAtmosCapability(handle[0], &atmosCapability);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsIsAudioLoopThru() retrieves the loop-through status correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 99@n
 * 
 * **Dependencies:** Audio device should be connected and working properly.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ], handle = [valid handle]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsIsAudioLoopThru() by looping through the acquired port handles to check if the audio port is configured for loop-through or not & store it in an array | handle: [ loop through valid handles ] , loopThru: [pointer to hold the status of loop-through feature] | dsERR_NONE | Status of loop-through feature for the specified audio port must be returned |
 * |04|Call dsIsAudioLoopThru() Again by looping through the acquired port handles to check if the audio port is configured for loop-through or not & store it in a new array | handle: [ loop through valid handles ] , loopThru: [pointer to hold the status of loop-through feature] | dsERR_NONE | Status of loop-through feature for the specified audio port must be returned |
 * |05|Compare the array values and make sure they are equal | | dsERR_NONE | The values must be equal |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 *
 */
void test_l1_dsAudio_positive_dsIsAudioLoopThru(void) {
	// Start of the test
	gTestID = 99; // Assuming Test Case ID is 99
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	bool loopThruArray1[NUM_OF_PORTS], loopThruArray2[NUM_OF_PORTS];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02 and 03: Get port handles and check Loop-Thru status
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Check Loop-Thru status
		result = dsIsAudioLoopThru(handle[i], &loopThruArray1[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
	}

	// Step 04: Check Loop-Thru status again
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsIsAudioLoopThru(handle[i], &loopThruArray2[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		// Step 05: Compare the values
		DS_ASSERT_AUTO_TERM_NUMERICAL(loopThruArray1[i], loopThruArray2[i]);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsIsAudioLoopThru() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 100@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsIsAudioLoopThru() - Attempt to check if audio port is configured for loop through without initializing audio ports | handle = [invalid handle], loopThru: [pointer to hold the status of loop-through feature] | dsERR_NOT_INITIALIZED | Call to check if Loop through is enabled must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsIsAudioLoopThru() using an invalid handle | handle = [invalid handle], loopThru: [pointer to hold the status of loop-through feature] | dsERR_INVALID_PARAM | Invalid Parameter error must be returned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsIsAudioLoopThru() - by looping through the acquired port handles but with a NULL pointer for loopThru param | handle = [Loop through valid handles], loopThru: [NULL] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsIsAudioLoopThru() - Attempt to check if audio port is configured for loop through again after terminating audio ports | handle = [valid handle], loopThru: [pointer to hold the status of loop-through feature] | dsERR_NOT_INITIALIZED | Call to check if Loop through is enabled must fail as module is not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsIsAudioLoopThru(void) {
	// Start of the test
	gTestID = 100; // Assuming Test Case ID is 100
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	bool loopThru;

	// Step 01: Attempt to check Loop-Thru status without initializing audio ports
	result = dsIsAudioLoopThru(-1, &loopThru);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to check Loop-Thru status with invalid handle
	result = dsIsAudioLoopThru(handle[0], &loopThru);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Loop through kPorts to get audio port handle
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);
	}

	// Step 05: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to check Loop-Thru status after terminating audio ports
	result = dsIsAudioLoopThru(handle[0], &loopThru);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsIsAudioMute() retrieves the mute status correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 101@n
 * 
 * **Dependencies:** Audio device should be connected and working properly.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsIsAudioMute() by looping through the acquired port handles to check if the audio is muted or not on each port & store the values in an array | handle: [ loop through valid handles ] , muted: [pointer to hold the mute status](TRUE/FALSE) | dsERR_NONE | Mute status of the specified audio port must be returned |
 * |04|Call dsIsAudioMute() - Again by looping through the acquired port handles to check if the audio is muted or not on each port & store the values in a new array | handle: [ loop through valid handles ] , muted: [pointer to hold the mute status] | dsERR_NONE | Mute status of the specified audio port must be returned |
 * |05|Compare the array values and make sure they are equal| | dsERR_NONE | The values must be equal |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsIsAudioMute(void) {
	// Start of the test
	gTestID = 101; // Assuming Test Case ID is 101
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	bool muteStatusArray1[NUM_OF_PORTS], muteStatusArray2[NUM_OF_PORTS];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02:Get port handles and check Mute status
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03:Get  Mute status in array
		result = dsIsAudioMute(handle[i], &muteStatusArray1[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Step 04:Get  Mute status in array
		result = dsIsAudioMute(handle[i], &muteStatusArray2[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Step 05:Compare Mute status in arrays
		DS_ASSERT_AUTO_TERM_NUMERICAL(muteStatusArray1[i], muteStatusArray1[i]);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsIsAudioMute() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 102@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsIsAudioMute() - Attempt to get the mute status of Audio ports without initializing audio ports | handle = [invalid handle], muted = [valid pointer to hold the mute status](TRUE/FALSE) | dsERR_NOT_INITIALIZED | Call to check if audio port is muted or not must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsIsAudioMute() using an invalid handle but with a valid pointer to mute status | handle = [invalid handle], muted = [pointer to hold the mute status] | dsERR_INVALID_PARAM | Invalid Parameter error must be returned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsIsAudioMute() by looping through the acquired port handles with a NULL pointer for mute status | handle = [valid handle], muted = [NULL pointer] | dsERR_INVALID_PARAM | Invalid Parameter error must be returned | 
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful | 
 * |07|Call dsIsAudioMute() again after terminating audio ports | handle = [valid handle from previous step], muted = [pointer to hold the mute status] | dsERR_NOT_INITIALIZED | Call to check if audio port is muted or not must fail as module is not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsIsAudioMute(void) {
	// Start of the test
	gTestID = 102; // Assuming Test Case ID is 102
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	bool muted;

	// Step 01: Attempt to check Mute status without initializing audio ports
	result = dsIsAudioMute(-1, &muted);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to check Mute status with invalid handle
	result = dsIsAudioMute(handle[0], &muted);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 02: Loop through kPorts to get audio port handle
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);
	}

	// Step 05: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to check Mute status after terminating audio ports
	result = dsIsAudioMute(handle[0], &muted);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsIsAudioPortEnabled() retrieves the enable status correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 103@n
 * 
 * **Dependencies:** Audio device should be connected and working properly.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ], handle = [valid handle]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsIsAudioPortEnabled() by looping through the acquired port handles to check if the corresponding audio port is enabled or not & store the values in an array | handle: [ loop through valid handles ] , enabled: [ pointer to hold the audio port enabled / disabled state(TRUE/FALSE)] | dsERR_NONE | Audio port enabled(TRUE)/disabled(FALSE) state must be returned |
 * |04|Call dsIsAudioPortEnabled() - Again by looping through the acquired port handles to check if the corresponding audio port is enabled or not & store the values in a new array | handle: [ loop through valid handles ] , enabled: [ pointer to hold the audio port enabled / disabled state(TRUE/FALSE)] | dsERR_NONE | Audio port enabled(TRUE)/disabled(FALSE) state must be returned |
 * |05|Compare the array values and make sure they are equal| | dsERR_NONE | The values must be equal |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsIsAudioPortEnabled(void) {
	// Start of the test
	gTestID = 103; // Assuming Test Case ID is 103
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	bool enabledStatusArray1[NUM_OF_PORTS], enabledStatusArray2[NUM_OF_PORTS];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02 and 03: Get port handles and check Enabled status
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Get Enabled status in array
		result = dsIsAudioPortEnabled(handle[i], &enabledStatusArray1[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Step 04: Check Enabled status again
		result = dsIsAudioPortEnabled(handle[i], &enabledStatusArray2[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Step 05: Compare the values
		DS_ASSERT_AUTO_TERM_NUMERICAL(enabledStatusArray1[i], enabledStatusArray2[i]);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsIsAudioPortEnabled() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 104@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsIsAudioPortEnabled() - Attempt to check if Audio port is enabled or not without initializing audio ports | handle = [invalid handle], enabled: [ valid pointer to hold the audio port enabled / disabled state] | dsERR_NOT_INITIALIZED | Call to check if Audio Port is enabled or not must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsIsAudioPortEnabled() using an invalid handle but with a valid pointer to hold the enabled status | handle = [invalid handle],  enabled: [ valid pointer to hold the audio port enabled / disabled state] | dsERR_INVALID_PARAM | Invalid Parameter error must be returned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ], handle = [valid handle]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsIsAudioPortEnabled() using an valid handle but with a NULL pointer to hold the enabled status | handle = [valid handle],  enabled: [ NULL pointer] | dsERR_INVALID_PARAM | Invalid Parameter error must be returned |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsIsAudioPortEnabled() - Attempt to check if Audio port is enabled or not again after terminating audio ports | handle = [invalid handle], enabled: [ valid pointer to hold the audio port enabled / disabled state] | dsERR_NOT_INITIALIZED | Call to check if Audio Port is enabled or not must fail as module is not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsIsAudioPortEnabled(void) {
	// Start of the test
	gTestID = 104; // Assuming Test Case ID is 104
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t handle[NUM_OF_PORTS] =  {INT_ARRAY_INIT};
	bool isEnabled;

	// Step 01: Attempt to check Enabled status without initializing audio ports
	result = dsIsAudioPortEnabled(-1, &isEnabled);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to check Enabled status with invalid handle
	result = dsIsAudioPortEnabled(handle[0], &isEnabled);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Loop through kPorts to get audio port handle
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);
	}

	// Step 05: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to check Enabled status after terminating audio ports
	result = dsIsAudioPortEnabled(handle[0], &isEnabled);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsEnableAudioPort() sets the audio port state correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 105@n
 * 
 * **Dependencies:** Audio device should be connected and working properly.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsEnableAudioPort() by looping through the acquired port handles to enable audio port | handle: [ loop through valid handles ] , enable: [TRUE] | dsERR_NONE | Supported audio ports must be enabled |
 * |04|Call dsEnableAudioPort() by looping through the acquired port handles to disable audio port | handle: [ loop through valid handles ] , enable: [FALSE] | dsERR_NONE | Supported audio ports must be disabled |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsEnableAudioPort(void) {
	// Start of the test
	gTestID = 105; // Assuming Test Case ID is 105
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	bool enabledStatus;

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02, 03, and 04: Get port handles, enable them, and verify
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		result = dsEnableAudioPort(handle[i], true);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Verify enable status
		result = dsIsAudioPortEnabled(handle[i], &enabledStatus);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		UT_ASSERT_TRUE(enabledStatus);
	}

	// Step 05 and 06: Disable audio ports and verify
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsEnableAudioPort(handle[i], false);
		UT_ASSERT_EQUAL(result, dsERR_NONE);

		// Verify disable status
		result = dsIsAudioPortEnabled(handle[i], &enabledStatus);
		UT_ASSERT_EQUAL(result, dsERR_NONE);
		UT_ASSERT_FALSE(enabledStatus);
	}

	// Step 07: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsEnableAudioPort() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 106@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsEnableAudioPort() - Attempt to enable/disable audio ports without initializing audio ports | handle = [invalid handle] , enabled = [TRUE] | dsERR_NOT_INITIALIZED | Call to Enable / Disable the Audio Ports must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |04|Call dsEnableAudioPort() using an invalid handle but with a valid enable | handle = [invalid handle], enabled = [TRUE] | dsERR_INVALID_PARAM | Invalid Parameter error must be returned |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsEnableAudioPort() - Attempt to enable/disable audio ports again after terminating audio ports | handle = [invalid handle] , enabled = [TRUE] | dsERR_NOT_INITIALIZED | Call to Enable / Disable the Audio Ports must fail as module is not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsEnableAudioPort(void) {
	// Start of the test
	gTestID = 106; // Assuming Test Case ID is 106
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};

	// Step 01: Attempt to enable/disable audio ports without initializing
	result = dsEnableAudioPort(-1, true);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to enable/disable with invalid handle
	result = dsEnableAudioPort(handle[0], true);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Loop through kPorts to get audio port handle
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);
	}

	// Step 05: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 06: Attempt to enable/disable after terminating
	result = dsEnableAudioPort(handle[0], true);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsEnableMS12Config() sets the MS12 features correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 107@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ], handle = [valid handle]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsEnableMS12Config() by looping through the acquired port handles and enable MS12 configs(from dsMS12FEATURE_t) for each port| handle = [loop through valid handles], feature = [ loop through dsMS12FEATURE_t] , enable = [TRUE] | dsERR_NONE | All MS12 Features must be enabled for all supported audio ports |
 * |04|Call dsEnableMS12Config() by looping through the acquired port handles and disable MS12 configs(from dsMS12FEATURE_t) for each port| handle = [loop through valid handles], feature = [ loop through dsMS12FEATURE_t] , enable = [FALSE] | dsERR_NONE | All MS12 Features must be disabled for all supported audio ports |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsEnableMS12Config(void) {
	// Start of the test
	gTestID = 107; // Assuming Test Case ID is 107
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Steps 02 to 04: Enable and disable MS12 Config for each port
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Loop through all MS12 features
		for (dsMS12FEATURE_t feature = dsMS12FEATURE_DAPV2; feature <= dsMS12FEATURE_MAX ; feature++) {
			// Enable MS12 Config
			result = dsEnableMS12Config(handle[i], feature, true);
			DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

			// Disable MS12 Config
			result = dsEnableMS12Config(handle[i], feature, false);
			DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		}
	}

	// Step 05: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsEnableMS12Config() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 108@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsEnableMS12Config() - Attempt to enable MS12 Configs without initializing audio ports | handle = [invalid handle], feature = [loop through dsMS12FEATURE_t], enable = [TRUE] | dsERR_NOT_INITIALIZED | Enable MS12 Configs must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsEnableMS12Config() using an invalid handle | handle = [invalid handle], feature = [loop through dsMS12FEATURE_t], enable = [TRUE] | dsERR_INVALID_PARAM | Invalid Parameter error must be returned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ], handle = [valid handle]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsEnableMS12Config() using an unsupported MS12 feature  | handle = [valid value], feature = [invalid MS12 feature(which are not in dsMS12FEATURE_t)], enable = [TRUE] | dsERR_OPERATION_NOT_SUPPORTED | Operation not supported error must be returned |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsEnableMS12Config() - Attempt to enable MS12 Configs again after terminating audio ports | handle = [valid handle from previous step], feature = [loop through dsMS12FEATURE_t], enable = [TRUE] | dsERR_NOT_INITIALIZED | Enable MS12 Configs must fail as module is not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsEnableMS12Config(void) {
	// Start of the test
	gTestID = 108; // Assuming Test Case ID is 108
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};

	// Step 01: Attempt to enable MS12 Configs without initializing
	result = dsEnableMS12Config(-1, dsMS12FEATURE_DAPV2 , true);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to enable with invalid handle
	result = dsEnableMS12Config(handle[0], dsMS12FEATURE_DAPV2, true);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Loop through kPorts to get audio port handle
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Attempt to enable an unsupported MS12 feature
		result = dsEnableMS12Config(handle[i], dsMS12FEATURE_MAX , true); // Assuming UNSUPPORTED_MS12_FEATURE is defined
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_OPERATION_NOT_SUPPORTED);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to enable MS12 Configs after terminating
	result = dsEnableMS12Config(handle[0], dsMS12FEATURE_DAPV2, true);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsEnableLEConfig() sets the Loudness Equivalence (LE) feature correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 109@n
 * 
 * **Dependencies:** Audio device should be connected and working properly.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsEnableLEConfig() by looping through the acquired port handles to enable the LE feature | handle = [loop through valid handles], enable = [TRUE] | dsERR_NONE | Loudness Equivalence must be enabled for all supported audio ports |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsEnableLEConfig(void) {
	// Start of the test
	gTestID = 109; // Assuming Test Case ID is 109
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	bool enabled;

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Steps 02 to 03: Enable LE Config for each port
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Enable LE Config
		result = dsEnableLEConfig(handle[i], true);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

	}

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsEnableLEConfig() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 110@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsEnableLEConfig() - Attempt to enable LE without initializing audio ports | handle = [invalid handle],  enable = [TRUE] | dsERR_NOT_INITIALIZED | Call to dsEnableLEConfig() must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsEnableLEConfig() using an invalid handle but with a valid enable parameter | handle = [invalid handle], enable = [TRUE] | dsERR_INVALID_PARAM | Invalid Parameter error must be returned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE | Termination must be successful |
 * |06|Call dsEnableLEConfig() - Attempt to enable LE again after terminating audio ports | handle = [valid handle from previous step], enable = [FALSE] | dsERR_NOT_INITIALIZED | Call to dsEnableLEConfig() must fail as module is not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsEnableLEConfig(void) {
	// Start of the test
	gTestID = 110; // Assuming Test Case ID is 110
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};

	// Step 01: Attempt to enable LE without initializing
	result = dsEnableLEConfig(-1, true);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to enable with invalid handle
	result = dsEnableLEConfig(handle[0], true);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Loop through kPorts to get audio port handle
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);
	}

	// Step 05: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 06: Attempt to enable LE after terminating
	result = dsEnableLEConfig(handle[0], false);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetLEConfig() retrieves the Loudness Equivalence (LE) feature status correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 111@n
 * 
 * **Dependencies:** Audio device should be connected and LE features are supported.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetLEConfig() by looping through the acquired port handles to get the Loudness Equivalence feature of each port in array| handle: [ loop through valid handles ] , enable: [ pointer to hold the status of LE feature(enabled/disabled) ] | dsERR_NONE | Loudness Equivalence enabled/disabled status must be returned |
 * |04|Call dsGetLEConfig() by looping through the acquired port handles to get the Loudness Equivalence feature of each port in new array | handle: [ valid handles ] , enable: [ pointer to hold the status of LE feature(enabled/disabled) ] | dsERR_NONE | Loudness Equivalence enabled/disabled status must be returned |
 * |05|Compare the array values and make sure they are equal| | dsERR_NONE | The values must be equal |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetLEConfig(void) {
	// Start of the test
	gTestID = 111; // Assuming Test Case ID is 111
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	bool leconfigarray[NUM_OF_PORTS];
	bool leconfigarray1[NUM_OF_PORTS];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Steps 02: Get audio port handle
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Retrieve LE Config
		result = dsGetLEConfig(handle[i], &leconfigarray[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Step 04: Retrieve LE Config
		result = dsGetLEConfig(handle[i], &leconfigarray1[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Step 05: compare leconfigarray array values
		DS_ASSERT_AUTO_TERM_NUMERICAL(leconfigarray[i], leconfigarray1[i]);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetLEConfig() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 112@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsGetLEConfig() - Attempt to get the LE Config of audio ports without initializing audio ports | handle = [invalid handle], enable: [ pointer to hold the status of LE feature]  | dsERR_NOT_INITIALIZED | Get LE Config must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetLEConfig() using an invalid handle | handle = [invalid handle], enable: [ pointer to hold the status of LE feature] | dsERR_INVALID_PARAM | Invalid Parameter error must be returned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsGetLEConfig() by looping through acquired port handles but with NULL pointer for enabled param | handle = [invalid handle], enable = [NULL] | dsERR_INVALID_PARAM | Invalid Parameter error must be returned |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsGetLEConfig() - Attempt to get the LE Config of audio ports again after terminating audio ports | handle = [valid handle from previous step], enable = [ pointer to hold the status of LE feature]  | dsERR_NOT_INITIALIZED | Get LE Config must fail as module is not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetLEConfig(void) {
	// Start of the test
	gTestID = 112; // Assuming Test Case ID is 112
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	bool enable;

	// Step 01: Attempt to get LE Config without initializing
	result = dsGetLEConfig(-1, &enable);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to get LE Config with invalid handle
	result = dsGetLEConfig(handle[0], &enable);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Loop through kPorts to get audio port handle
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		//Setp 05:Attempt to get LE Config with NULL pointer
		result = dsGetLEConfig(handle[i], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to get LE Config after terminating
	result = dsGetLEConfig(handle[0], &enable);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetMS12AudioProfile() sets the MS12 audio profile correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 113@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsSetMS12AudioProfile() - by looping through the acquired handles and set a valid MS12 audio profile | handle = [loop through valid handles], profile = [valid profile from _dsMS12AudioProfileList_t] | dsERR_NONE | MS12 Audio Profile must be set properly for all supported audio ports |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsSetMS12AudioProfile(void) {
	// Start of the test
	gTestID = 113; // Assuming Test Case ID is 113
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	char *validProfile = "YourValidMS12Profile"; // Replace with a valid profile from _dsMS12AudioProfileList_t

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Steps 02 and 03: Get port handle and set MS12 audio profile for each port
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);


		// Set MS12 Audio Profile
		result = dsSetMS12AudioProfile(handle[i], validProfile);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Add additional logging or checks if needed
	}

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetMS12AudioProfile() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 114@n
 * **Test Case ID:** 114@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsSetMS12AudioProfile() - Attempt to set MS12 Audio profile without initializing audio ports | handle = [invalid handle], profile = [a valid MS12 audio profile](from _dsMS12AudioProfileList_t) | dsERR_NOT_INITIALIZED | Set MS12 audio profile must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetMS12AudioProfile() using an invalid handle but with a valid MS12 audio profile | handle = [invalid handle], profile = [a valid MS12 audio profile](from _dsMS12AudioProfileList_t)  | dsERR_INVALID_PARAM | Invalid Parameter error must be retrurned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ] , handle = [valid handle] | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsSetMS12AudioProfile() using a null profile string | handle = [valid handle], profile = [NULL] | dsERR_INVALID_PARAM | Invalid Parameter error must be returned |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsSetMS12AudioProfile() -  Attempt to set MS12 Audio profile again after terminating audio ports | handle = [valid handle from previous step], profile = [a valid MS12 audio profile](from _dsMS12AudioProfileList_t) | dsERR_NOT_INITIALIZED | Set MS12 audio profile must fail as module is not initialized |
 * 
 */
void test_l1_dsAudio_negative_dsSetMS12AudioProfile(void) {
	// Start of the test
	gTestID = 114; // Assuming Test Case ID is 114
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	char *validProfile = "YourValidMS12Profile"; // Replace with a valid profile from _dsMS12AudioProfileList_t

	// Step 01: Attempt to set MS12 Audio Profile without initializing
	result = dsSetMS12AudioProfile(-1, validProfile);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to set MS12 Audio Profile with invalid handle
	result = dsSetMS12AudioProfile(handle[0], validProfile);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Loop through kPorts to get audio port handle
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Attempt to set MS12 Audio Profile with null profile string
		result = dsSetMS12AudioProfile(handle[i], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}  

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to set MS12 Audio Profile after terminating
	result = dsSetMS12AudioProfile(handle[0], validProfile);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetAudioDucking() sets the audio ducking level correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 115@n
 * 
 * **Dependencies:**.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsSetAudioDucking() by looping though acquired port handles and valid in range action values(i.e 0 or 1) ,in range type values(i.e 0 or 1) , level(0 to 100) values | handle=[valid handle], action=[valid value], type=[valid value], level=[valid value] | dsERR_NONE |audio ducking values should be successfully set |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsSetAudioDucking(void) {
	// Start of the test
	gTestID = 115; // Assuming Test Case ID is 115
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	dsAudioDuckingAction_t action;
	dsAudioDuckingType_t   type;
	unsigned char level = 100;

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Steps 02 and 03: Get port handle and set audio ducking for each port
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);        

		for (type = dsAUDIO_DUCKINGTYPE_ABSOLUTE ; type < dsAudio_DUCKINGTYPE_MAX ; type++ ) {
			for(action = dsAUDIO_DUCKINGACTION_START ; action < dsAudio_DUCKINGACTION_MAX ; action++){
				// Set Audio Ducking - Replace with valid action, type, level values
				result = dsSetAudioDucking(handle[i], action, type, level);
				DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

			}// end of type for loop
		} // end of action for loop
	}

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetAudioDucking() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 116@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsSetAudioDucking() without initializing audio ports | handle=[invalid handle], action=[valid value], type=[valid value], level=[valid value] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized|
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetAudioDucking() using an invalid handle with valid action, type, and level values | handle=[invalid hadle], action=[valid value], type=[valid value], level=[valid value] | dsERR_INVALID_PARAM | Invalid parameter must return |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsSetAudioDucking() by loopint through acquired handles  with invalid action vales(out of range)  but with valid type and  level values | handle=[invalid hadle], action=[invalid value], type=[valid value], level=[valid value] | dsERR_INVALID_PARAM | Invalid parameter must return |
 * |06|Call dsSetAudioDucking() by loopint through acquired handles  with invalid type  vales(out of range)  but with valid action and  level values | handle=[invalid hadle], action=[valid value], type=[invalid value], level=[valid value] | dsERR_INVALID_PARAM | Invalid parameter must return |
 * |07|Call dsSetAudioDucking() by loopint through acquired handles  with invalid levels  vales( <0 or >100)  but with valid action and type values | handle=[invalid hadle], action=[valid value], type=[valid value], level=[invalid value] | dsERR_INVALID_PARAM | Invalid parameter must return |
 * |08|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |09|Call dsSetAudioDucking() again after terminating audio ports | handle=[valid handle], action=[valid value], type=[valid value], level=[valid value] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized |
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions
 */
void test_l1_dsAudio_negative_dsSetAudioDucking(void) {
	// Start of the test
	gTestID = 116; // Assuming Test Case ID is 116
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	dsAudioDuckingAction_t  valid_action = dsAUDIO_DUCKINGACTION_START;
	dsAudioDuckingAction_t  invalid_action = dsAudio_DUCKINGACTION_MAX;

	dsAudioDuckingType_t vaild_type = dsAUDIO_DUCKINGTYPE_ABSOLUTE;
	dsAudioDuckingType_t invaild_type = dsAudio_DUCKINGTYPE_MAX;

	unsigned char valid_level = 100;
	unsigned char invalid_level = 110;

	// Step 01: Attempt to set Audio Ducking without initializing
	result = dsSetAudioDucking(-1, valid_action, vaild_type, valid_level);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Steps 03: Test with invalid handle
	result = dsSetAudioDucking(handle[0], valid_action, vaild_type, valid_level);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Loop through kPorts to get audio port handle
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: set ducking with invalid action
		result = dsSetAudioDucking(handle[i], invalid_action, vaild_type, valid_level);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

		// Step 06: set ducking with invalid type
		result = dsSetAudioDucking(handle[i], valid_action, vaild_type, valid_level);
		UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

		// Step 07: set ducking with invalid level
		result = dsSetAudioDucking(handle[i], valid_action, vaild_type, valid_level);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}    


	// Step 08: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 09: Attempt to set Audio Ducking after terminating
	result = dsSetAudioDucking(handle[0], valid_action, vaild_type, valid_level);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsEnableLoopThru() sets loop-through mode correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 117@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsEnableLoopThru() bylooping through the acquired ports with valid loopthru value(i.e true), Enable loop-through | handle=[valid handle], loopThru=[true] | dsERR_NONE |loop through should be enabled properly |
 * |04|Call dsEnableLoopThru() bylooping through the acquired ports with valid loopthru value(i.e false), Disable loop-through | handle=[valid handles], loopThru=[false] | dsERR_NONE |loop through should be disabled properly |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsEnableLoopThru(void) {
	// Start of the test
	gTestID = 117; // Assuming Test Case ID is 117
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Steps 02 to 04: Get port handle, enable and disable loop-through for each port
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Enable Loop-through
		result = dsEnableLoopThru(handle[i], true);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Disable Loop-through
		result = dsEnableLoopThru(handle[i], false);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Add additional logging or checks if needed
	}

	// Step 05: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsEnableLoopThru() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 118@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsEnableLoopThru() without initializing audio ports | handle=[invalid handle], loopThru=[valid value] | dsERR_NOT_INITIALIZED |call must fail as module not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsEnableLoopThru() using an invalid handle with valid loop thru values(i.e TRUE/FALSE) | handle=[invalid handle], loopThru=[valid value] |dsERR_INVALID_PARAM |Invalid parameter must return |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsEnableLoopThru() again after terminating audio ports | handle=[valid handle], loopThru=[valid value] | dsERR_NOT_INITIALIZED |call must fail as module not initialized |
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions 
 */
void test_l1_dsAudio_negative_dsEnableLoopThru(void) {
	// Start of the test
	gTestID = 118; // Assuming Test Case ID is 118
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};

	// Step 01: Attempt to enable loop-through without initializing
	result = dsEnableLoopThru(-1, true);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Test with invalid handle
	result = dsEnableLoopThru(handle[0], true);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Loop through kPorts to get audio port handle
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);
	}    

	// Step 05: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 06: Attempt to enable loop-through after terminating
	result = dsEnableLoopThru(handle[0], true);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetAudioMute() mutes or un-mutes an audio port correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 119@n
 * 
 * **Dependencies:** Audio device should be connected.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsSetAudioMute() by looping through acquired port handle and valid mute value (i.e TRUE/FALSE)| handle=[valid handle], mute=[valid value] | dsERR_NONE |mute/unmute value should be set successfully |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsSetAudioMute(void) {
	// Start of the test
	gTestID = 119; // Assuming Test Case ID is 119
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};     
	bool mute = true , unmute = false;   

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Steps 02 and 03: Get port handle and set mutei , unmute for each port
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE); 
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Set Mute
		result = dsSetAudioMute(handle[i], mute);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Unmute
		result = dsSetAudioMute(handle[i], unmute);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Add additional logging or checks if needed
	}

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetAudioMute() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 120@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsSetAudioMute() without initializing audio ports | handle=[invalid handle], mute=[valid value] | dsERR_NOT_INITIALIZED |call must fail as module not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetAudioMute() using an invalid handle with valid mute value(i.e TRUE/FALSE) | handle=[invalid handle], mute=[valid value] | dsERR_INVALID_PARAM |Invalid parameter must return|
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsSetAudioMute() again after terminating audio ports | handle=[valid handle], mute=[valid value] | dsERR_NOT_INITIALIZED |call must fail as module not initialized |
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions 
 */
void test_l1_dsAudio_negative_dsSetAudioMute(void) {
	// Start of the test
	gTestID = 120; // Assuming Test Case ID is 120
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	bool valid_value = true;

	// Step 01: Attempt to set mute without initializing
	result = dsSetAudioMute(-1, valid_value);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Test with invalid handle
	result = dsSetAudioMute(handle[0], valid_value);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Loop through kPorts to get audio port handle
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);
	}

	// Step 05: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 06: Attempt to set mute after terminating
	result = dsSetAudioMute(handle[0], true);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsIsAudioMSDecode() correctly checks for Dolby MS11 Multistream Decode support during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 121@n
 * 
 * **Dependencies:**@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsIsAudioMSDecode() by looping through the acquired port handles to check if corresponding audio port supports Dolby MS11 Multistream decode or not | handle: [ loop through valid handles ] , HasMS11Decode: [pointer to hold the MS11 Multistream Decode setting] | dsERR_NONE | MS11 Multistream Decode setting(true if audio port supports Dolby MS11 Multistream Decoding or @a false otherwise ) must be returned |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsIsAudioMSDecode(void) {
	// Start of the test
	gTestID = 121; // Assuming Test Case ID is 121
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	bool hasMS11Decode[NUM_OF_PORTS];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Steps 02 and 03: Get port handle and check for MS11 Multistream Decode
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		result = dsIsAudioMSDecode(handle[i], &hasMS11Decode[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		// Add check for hasMS11Decode if needed
	}

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsIsAudioMSDecode() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 122@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsIsAudioMSDecode() without initializing audio ports | handle=[invalid handle], HasMS11Decode=[valid pointer] |dsERR_NOT_INITIALIZED |call must fail as module not initialized|
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsIsAudioMSDecode() using an invalid handle and valid pointer |handle=[invalid hanlde], HasMS11Decode=[valid pointer] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsIsAudioMSDecode() by looping through the acquired valid handle with a NULL gain pointer |handle=[valid handle], HasMS11Decode=[NULL] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsIsAudioMSDecode() again after terminating audio ports | handle=[valid handle], HasMS11Decode=[valid pointer] | dsERR_NOT_INITIALIZED | call must fail as module not initialized |
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions
 */
void test_l1_dsAudio_negative_dsIsAudioMSDecode(void) {
	// Start of the test
	gTestID = 122; // Assuming Test Case ID is 122
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	bool hasMS11Decode;

	// Step 01: Attempt to check MS11 Decode without initializing
	result = dsIsAudioMSDecode(-1, &hasMS11Decode);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Test with invalid handle
	result = dsIsAudioMSDecode(handle[0], &hasMS11Decode);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Loop through kPorts to get audio port handle
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Test with valid handle and invalid pointer
		result = dsIsAudioMSDecode(handle[i], &hasMS11Decode);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to check MS11 Decode after terminating
	result = dsIsAudioMSDecode(handle[0], &hasMS11Decode);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsIsAudioMS12Decode() correctly checks for Dolby MS12 Multistream Decode support during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 123@n
 * 
 * **Dependencies:**@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsIsAudioMS12Decode() by looping through the acquired port handles to check if corresponding audio port supports Dolby MS12 Multistream decode or not | handle: [ loop through valid handles ] , hasMS12Decode: [pointer to hold the MS12 Multistream Decode setting] | dsERR_NONE | MS12 Multistream Decode setting(true if audio port supports Dolby MS12 Multistream Decoding or @a false otherwise ) must be returned |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsIsAudioMS12Decode(void) {
	// Start of the test
	gTestID = 123; // Assuming Test Case ID is 123
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	bool hasMS12Decode[NUM_OF_PORTS];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Steps 02 and 03: Get port handle and check for MS12 Multistream Decode
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		result = dsIsAudioMS12Decode(handle[i], &hasMS12Decode[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		// Add check for hasMS12Decode if needed
	}

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsIsAudioMS12Decode() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 124@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsIsAudioMS12Decode() without initializing audio ports | handle=[invalid handle], HasMS12Decode=[valid pointer] |dsERR_NOT_INITIALIZED |call must fail as module not initialized|
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsIsAudioMS12Decode() using an invalid handle and valid pointer |handle=[invalid hanlde], HasMS12Decode=[valid pointer] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsIsAudioMS12Decode() by looping through the acquired valid handle with a NULL gain pointer |handle=[valid handle], HasMS12Decode=[NULL] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsIsAudioMS12Decode() again after terminating audio ports | handle=[valid handle], hasMS12Decode=[valid pointer] | dsERR_NOT_INITIALIZED | call must fail as module not initialized |
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions
 */
void test_l1_dsAudio_negative_dsIsAudioMS12Decode(void) {
	// Start of the test
	gTestID = 124; // Assuming Test Case ID is 124
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	bool hasMS12Decode;

	// Step 01: Attempt to check MS12 Decode without initializing
	result = dsIsAudioMS12Decode(-1, &hasMS12Decode);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Test with invalid handle
	result = dsIsAudioMS12Decode(handle[0], &hasMS12Decode);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Loop through kPorts to get audio port handle
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Test with valid handle and NULL pointer
		result = dsIsAudioMS12Decode(handle[i], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to check MS12 Decode after terminating
	result = dsIsAudioMS12Decode(handle[0], &hasMS12Decode);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsAudioOutIsConnected() correctly checks for audio output port connection during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 125@n
 * 
 * **Dependencies:**@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsAudioOutIsConnected() by looping through the acquired port handles to get the connection status of each audio port | handle: [ loop through valid handles ] , isConnected: [pointer to hold the encodingaudio port connection status] | dsERR_NONE | A valid connection status of audio output port (true if audio port is connected and @a false if Not Connected) must be returned |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsAudioOutIsConnected(void) {
	// Start of the test
	gTestID = 125; // Assuming Test Case ID is 125
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	bool isConnected[NUM_OF_PORTS];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Steps 02 and 03: Get port handle and check connection status
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		result = dsAudioOutIsConnected(handle[i], &isConnected[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		// Optionally check isConnected value
	}

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsAudioOutIsConnected() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 126@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioOutIsConnected() without initializing audio ports | handle=[invalid handle], isConnected=[valid pointer] |dsERR_NOT_INITIALIZED |call must fail as module not initialized|
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsAudioOutIsConnected() using an invalid handle and valid pointer |handle=[invalid hanlde], isConnected=[valid pointer] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsAudioOutIsConnected() by looping through the acquired valid handle with a NULL gain pointer |handle=[valid handle], isConnected=[NULL] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsAudioOutIsConnected() again after terminating audio ports | handle=[valid handle] , isConnected=[valid pointer] | dsERR_NOT_INITIALIZED |call must fail as module not initialized|
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions
 */
void test_l1_dsAudio_negative_dsAudioOutIsConnected(void) {
	// Start of the test
	gTestID = 126; // Assuming Test Case ID is 126
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	bool isConnected;

	// Step 01: Attempt to check connection status without initializing
	result = dsAudioOutIsConnected(-1, &isConnected);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Test with invalid handle
	result = dsAudioOutIsConnected(handle[0], &isConnected);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Loop through kPorts to get audio port handle
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Test with Null pointer
		result = dsAudioOutIsConnected(handle[i], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Attempt to check connection status after terminating
	result = dsAudioOutIsConnected(handle[0], &isConnected);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsAudioOutRegisterConnectCB() correctly registers for the audio output connect event during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 127@n
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Register the audio output connect callback using dsAudioOutRegisterConnectCB() | `CBFunc`=test callback function | dsERR_NONE | Should Pass |
 * |03|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */

/*callback function*/
void testAudioOutConnectCallbackFunction(dsAudioPortType_t type, unsigned int index, bool isConnected)
{
	/* call back */
}

void test_l1_dsAudio_positive_dsAudioOutRegisterConnectCB(void) {
	// Start of the test
	gTestID = 127; // Assuming Test Case ID is 127
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;

	dsAudioOutPortConnectCB_t connectcb = &testAudioOutConnectCallbackFunction;

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Register the audio output connect callback
	result = dsAudioOutRegisterConnectCB(connectcb);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

	// Step 03: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsAudioOutRegisterConnectCB() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 128@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioOutRegisterConnectCB() without initializing audio ports | `CBFunc`=NULL | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsAudioOutRegisterConnectCB() using a NULL callback function | `CBFunc`=NULL | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_negative_dsAudioOutRegisterConnectCB(void) {
	// Start of the test
	gTestID = 128; // Assuming Test Case ID is 128
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;

	// Step 01: Attempt to register callback without initializing ports
	result = dsAudioOutRegisterConnectCB(NULL);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to register a NULL callback
	result = dsAudioOutRegisterConnectCB(NULL);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsAudioFormatUpdateRegisterCB() correctly registers for the audio format update event during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 129@n
 * 
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Register the audio format update callback using dsAudioFormatUpdateRegisterCB() | `cbFun`=test callback function | dsERR_NONE | Should Pass |
 * |03|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */

/* call back */
void testAudioFormatUpdateCallbackFunction(dsAudioFormat_t format)
{
	/* stub callback */
}

void test_l1_dsAudio_positive_dsAudioFormatUpdateRegisterCB(void) {
	// Start of the test
	gTestID = 129; // Assuming Test Case ID is 129
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;

	dsAudioFormatUpdateCB_t format_update = &testAudioFormatUpdateCallbackFunction;

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Register the audio format update callback
	result = dsAudioFormatUpdateRegisterCB(format_update);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

	// Step 03: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsAudioFormatUpdateRegisterCB() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 130@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioFormatUpdateRegisterCB() without initializing audio ports | `cbFun`=NULL | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsAudioFormatUpdateRegisterCB() using a NULL callback function | `cbFun`=NULL | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_negative_dsAudioFormatUpdateRegisterCB(void) {
	// Start of the test
	gTestID = 130; // Assuming Test Case ID is 130
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;

	// Step 01: Attempt to register callback without initializing ports
	result = dsAudioFormatUpdateRegisterCB(NULL);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Attempt to register a NULL callback
	result = dsAudioFormatUpdateRegisterCB(NULL);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}

/**
 * @brief Ensure dsGetAudioCapabilities() correctly fetches the supported audio capabilities during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 131@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetAudioCapabilities() by looping through the acquired port handles to get the supported Audio capabilities of each port in array | handle: [ loop through valid handles ] , capabilities: [pointer to hold the Bitwise OR-ed value of supported Audio standards] | dsERR_NONE | Bitwise-ORed value of supported Audio standards(dsAudioCapabilities_t) must be returned |
 * |04|Call dsGetAudioCapabilities() by looping through the acquired port handles to get the supported Audio capabilities of each port in new array | handle: [ loop through valid handles ] , capabilities: [pointer to hold the Bitwise OR-ed value of supported Audio standards] | dsERR_NONE | Bitwise-ORed value of supported Audio standards(dsAudioCapabilities_t) must be returned |
 * |05|Compare the array values and make sure they are equal| | dsERR_NONE | The values must be equal |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetAudioCapabilities(void) {
	// Start of the test
	gTestID = 131; // Assuming Test Case ID is 131
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	int capabilities[NUM_OF_PORTS], capabilities1[NUM_OF_PORTS];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

	// Step 02: Get audio ports handles
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i] , null_handle);

		// Step 03: Get audio capabilities in an array
		result = dsGetAudioCapabilities(handle[i], &capabilities[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Step 04: Get audio capabilities in an array
		result = dsGetAudioCapabilities(handle[i], &capabilities1[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Step 05:compare audio capabilities of arrays
		DS_ASSERT_AUTO_TERM_NUMERICAL(capabilities[i] , capabilities1[i]);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetAudioCapabilities() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 132@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsGetAudioCapabilities() without initializing audio ports | handle=[invalid handle], capabilities=[valid pointer] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetAudioCapabilities() using an invalid handle and valid pointer |handle=[invalid hanlde], capabilities=[valid pointer] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsGetAudioCapabilities() by looping through the acquired valid handle with a NULL capabilities pointer |handle=[valid handle], capabilities=[NULL] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |05|Call dsGetAudioCapabilities() again after terminating audio ports | handle=[valid handle] , capabilities=[valid pointer] | dsERR_NOT_INITIALIZED | call must fail as module is not initialized  |
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions 
 */
void test_l1_dsAudio_negative_dsGetAudioCapabilities(void) {
	// Start of the test
	gTestID = 132; // Assuming Test Case ID is 275
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result , capabilities;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};

	// Step 01: Call without initializing
	result = dsGetAudioCapabilities(-1, &capabilities);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Call with invalid handle
	result = dsGetAudioCapabilities(handle[0], &capabilities);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Fetch a valid handle
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Call with NULL capabilities pointer
		result = dsGetAudioCapabilities(handle[i], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Call again after terminating
	result = dsGetAudioCapabilities(handle[0], &capabilities);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetMS12Capabilities() correctly fetches the supported MS12 capabilities during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 133@n
 * 
 * **Dependencies:** Audio device should be connected and should have known MS12 capabilities.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetMS12Capabilities() by looping through the acquired port handles to get the supported MS12 capabilities of each port in an array | handle: [ loop through valid handles ] , capabilities: [pointer to hold the Bitwise OR-ed value of supported MS12 standards] | dsERR_NONE | Bitwise-OR-ed value of supported MS12 standards(dsMS12Capabilities_t) must be returned |
 * |04|Call dsGetMS12Capabilities() by looping through the acquired port handles to get the supported MS12 capabilities of each port in a new array | handle: [ loop through valid handles ] , capabilities: [pointer to hold the Bitwise OR-ed value of supported MS12 standards] | dsERR_NONE | Bitwise-OR-ed value of supported MS12 standards(dsMS12Capabilities_t) must be returned |
 * |05|Compare the array values and make sure they are equal| | dsERR_NONE | The values must be equal |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetMS12Capabilities(void) {
	// Start of the test
	gTestID = 133; // Assuming Test Case ID is 133
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	int ms12Capabilities[NUM_OF_PORTS], ms12Capabilities1[NUM_OF_PORTS];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Loop through supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		// Fetch port handle
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Get MS12 capabilities
		result = dsGetMS12Capabilities(handle[i], &ms12Capabilities[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Step 04: Get MS12 capabilities in new array
		result = dsGetMS12Capabilities(handle[i], &ms12Capabilities1[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		//Step 05: Compare MS12 capabilities
		DS_ASSERT_AUTO_TERM_NUMERICAL(ms12Capabilities[i] , ms12Capabilities1[i]);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetMS12Capabilities() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 134@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsGetMS12Capabilities() without initializing audio ports | handle=[invalid handle], capabilities=[valid pointer] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetMS12Capabilities() using an invalid handle and valid pointer |handle=[invalid hanlde], capabilities=[valid pointer] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsGetMS12Capabilities() by looping through the acquired valid handle with a NULL capabilities pointer |handle=[valid handle], capabilities=[NULL] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsGetMS12Capabilities() again after terminating audio ports | handle=[valid handle] , capabilities=[valid pointer] | dsERR_NOT_INITIALIZED | call must fail as module is not initialized  |
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions 
 */
void test_l1_dsAudio_negative_dsGetMS12Capabilities(void) {
	// Start of the test
	gTestID = 134; // Assuming Test Case ID is 134
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	int ms12Capabilities;

	// Step 01: Call without initializing
	result = dsGetMS12Capabilities(-1, &ms12Capabilities);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Call with invalid handle
	result = dsGetMS12Capabilities(handle[0], &ms12Capabilities);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Loop through kPorts to get audio port handle
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Call with NULL capabilities pointer
		result = dsGetMS12Capabilities(handle[i], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Call again after terminating
	result = dsGetMS12Capabilities(handle[0], &ms12Capabilities);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}

/**
 * @brief Ensure dsResetDialogEnhancement() correctly resets the dialog enhancement to platform-specific default value during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 135@n
 * 
 * **Dependencies:**@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsResetDialogEnhancement() by looping through the acquired valid handles to  Reset dialog enhancement | handle=[valid handle] | dsERR_NONE | dialog enchancement should reset successfully |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsResetDialogEnhancement(void) {
	// Start of the test
	gTestID = 135; // Assuming Test Case ID is 135
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Loop through supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Reset dialog enhancement
		result = dsResetDialogEnhancement(handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

	}

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsResetDialogEnhancement() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 136@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsResetDialogEnhancement() without initializing audio ports | handle=[invalid handle] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsResetDialogEnhancement() using an invalid handle |handle=[invalid hanlde] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |05|Call dsResetDialogEnhancement() again after terminating audio ports | handle=[valid handle]| dsERR_NOT_INITIALIZED | call must fail as module is not initialized |
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions 
 */
void test_l1_dsAudio_negative_dsResetDialogEnhancement(void) {
	// Start of the test
	gTestID = 136; // Assuming Test Case ID is 136
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};

	// Step 01: Call without initializing
	result = dsResetDialogEnhancement(-1);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Call with invalid handle
	result = dsResetDialogEnhancement(handle[0]);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Loop through kPorts to get audio port handle
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

	}

	// Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 05: Call again after terminating
	result = dsResetDialogEnhancement(handle[0]);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsResetBassEnhancer() correctly resets the bass enhancer to platform-specific default value during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 137@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsResetBassEnhancer() by looping through the valid handles to reset bass enhancer| handle=[valid handle] | dsERR_NONE | bass enhancer should reset successfully |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsResetBassEnhancer(void) {
	// Start of the test
	gTestID = 137; // Assuming Test Case ID is 137
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Loop through supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		// Fetch port handle
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Reset bass enhancer
		result = dsResetBassEnhancer(handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

	}

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsResetBassEnhancer() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 138@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsResetBassEnhancer() without initializing audio ports | handle=[invalid handle] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsResetBassEnhancer() using an invalid handle |handle=[invalid hanlde] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsResetBassEnhancer() again after terminating audio ports | handle=[valid handle] | dsERR_NOT_INITIALIZED | call must fail as module is not initialized |
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions 
 */
void test_l1_dsAudio_negative_dsResetBassEnhancer(void) {
	// Start of the test
	gTestID = 138; // Assuming Test Case ID is 138
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};

	// Step 01: Call without initializing
	result = dsResetBassEnhancer(-1);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Call with invalid handle
	result = dsResetBassEnhancer(handle[0]);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Loop through kPorts to get audio port handle
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);
	}

	// Step 05: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 06: Call again after terminating
	result = dsResetBassEnhancer(handle[0]);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}

/**
 * @brief Ensure dsResetSurroundVirtualizer() correctly resets the surround virtualizer to platform-specific default value during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 139@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsResetSurroundVirtualizer() by looping through the acquired port handles to reset surround virtualizer | handle=[valid handle] | dsERR_NONE | surround virtualizer should be resuccessfully reset |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsResetSurroundVirtualizer(void) {
	// Start of the test
	gTestID = 139; // Assuming Test Case ID is 139
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Loop through supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Reset surround virtualizer
		result = dsResetSurroundVirtualizer(handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

	}

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsResetSurroundVirtualizer() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 140@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsResetSurroundVirtualizer() without initializing audio ports | handle=[invalid handle] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsResetSurroundVirtualizer() using an invalid handle |handle=[invalid hanlde] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsResetSurroundVirtualizer() again after terminating audio ports | handle=[valid handle] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized|
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions 
 */
void test_l1_dsAudio_negative_dsResetSurroundVirtualizer(void) {
	// Start of the test
	gTestID = 140; // Assuming Test Case ID is 140
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};

	// Step 01: Call without initializing
	result = dsResetSurroundVirtualizer(-1);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Call with invalid handle
	result = dsResetSurroundVirtualizer(handle[0]);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Loop through kPorts to get audio port handle
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);
	}

	// Step 05: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 06: Call again after terminating
	result = dsResetSurroundVirtualizer(handle[0]);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}

/**
 * @brief Ensure dsResetVolumeLeveller() correctly resets the Dolby volume leveller to platform-specific default volume level during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 141@n
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsResetVolumeLeveller() by loopig through the acquired handles to reset Dolby volume leveller | handle=[valid handle] | dsERR_NONE |volume leveller should be successfully reset |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsResetVolumeLeveller(void) {
	// Start of the test
	gTestID = 141; // Assuming Test Case ID is 141
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Loop through supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		// Fetch port handle
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		UT_ASSERT_EQUAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Reset volume leveller
		result = dsResetVolumeLeveller(handle[i]);
		UT_ASSERT_EQUAL(result, dsERR_NONE);

	}

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsResetVolumeLeveller() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 142@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsResetVolumeLeveller()  without initializing audio ports | handle=[invalid handle] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsResetVolumeLeveller() using an invalid handle |handle=[invalid hanlde] | dsERR_INVALID_PARAM |Invalid parameter error must be returned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsResetVolumeLeveller() again after terminating audio ports | handle=[valid handle] | dsERR_NOT_INITIALIZED | call must fail as module is not initialized  |
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions 
 */
void test_l1_dsAudio_negative_dsResetVolumeLeveller(void) {
	// Start of the test
	gTestID = 142; // Assuming Test Case ID is 142
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};

	// Step 01: Call without initializing
	result = dsResetVolumeLeveller(-1);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Call with invalid handle
	result = dsResetVolumeLeveller(handle[0]);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Loop through kPorts to get audio port handle
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);
	}

	// Step 05: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 06: Call again after terminating
	result = dsResetVolumeLeveller(handle[0]);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}

/**
 * @brief Ensure dsSetAssociatedAudioMixing() correctly enables/disables the associated audio mixing feature during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 145@n
 * 
 * **Dependencies:** Audio device should be connected.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsSetAssociatedAudioMixing() by looping through acquired valid handles and valid mixing values(i.e TRUE) to enable associated audio mixing feature | handle=[valid handle], mixing=[valid value] | dsERR_NONE | audio mixing feature should be successfully set to enable |
 * |04|Call dsSetAssociatedAudioMixing() by looping through acquired valid handles and valid mixing values(i.e FALSE) to disable associated audio mixing feature | handle=[valid handle], mixing=[valid value] | dsERR_NONE | audio mixing feature should be successfully set to disable |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsSetAssociatedAudioMixing(void) {
	// Start of the test
	gTestID = 145; // Assuming Test Case ID is 145
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Loop through supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Enable associated audio mixing
		result = dsSetAssociatedAudioMixing(handle[i], true); // Enable mixing
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Step 04: Disable associated audio mixing
		result = dsSetAssociatedAudioMixing(handle[i], false); // Disable mixing
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
	}

	// Step 05: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetAssociatedAudioMixing() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 146@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsSetAssociatedAudioMixing() without initializing audio ports | handle=[invalid handle], mixing=[valid value] | dsERR_NOT_INITIALIZED |call must fail as module not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetAssociatedAudioMixing() using an invalid handle with valid audio mixing value(i.e TRUE/FALSE) | handle=[invalid handle], mixing=[valid value] |dsERR_INVALID_PARAM |Invalid parameter must return |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsSetAssociatedAudioMixing() again after terminating audio ports | handle=[valid handle], mixing=[valid value] | dsERR_NOT_INITIALIZED |call must fail as module not initialized |
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions 
 */
void test_l1_dsAudio_negative_dsSetAssociatedAudioMixing(void) {
	// Start of the test
	gTestID = 146; // Assuming Test Case ID is 146
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};

	// Step 01: Call without initializing
	result = dsSetAssociatedAudioMixing(-1, true); // Example invalid handle
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Call with invalid handle
	result = dsSetAssociatedAudioMixing(handle[0], true); // Example invalid handle
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NOT_INITIALIZED);

	// Step 04: Loop through kPorts to get audio port handle
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);
	}

	// Step 05: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 06: Call again after terminating
	result = dsSetAssociatedAudioMixing(handle[0], true);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetAssociatedAudioMixing() correctly fetches the status of the associated audio mixing feature during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 147@n
 * 
 * **Dependencies:**@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetAssociatedAudioMixing() by looping through the acquired port handles to get the audio mixing status(enabled/disabled) of each port | handle: [ loop through valid handles ] , mixing: [pointer to hold the Audio Mixing status(@a true if enabled and @a false if disabled)] | dsERR_NONE | A valid audio mixing status(enabled or disabled) must be returned |
 * |04|Call dsGetAssociatedAudioMixing() by looping through the acquired port handles to get the audio mixing status(enabled/disabled) of each port in new array | handle: [ loop through valid handles ] , mixing: [pointer to hold the Audio Mixing status(@a true if enabled and @a false if disabled)] | dsERR_NONE | A valid audio mixing status(enabled or disabled) must be returned |
 * |05|Compare the array values and make sure they are equal| | dsERR_NONE | The values must be equal |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetAssociatedAudioMixing(void) {
	// Start of the test
	gTestID = 147; // Assuming Test Case ID is 147
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	bool mixing[NUM_OF_PORTS];
	bool mixing1[NUM_OF_PORTS];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Loop through supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Get audio mixing status
		result = dsGetAssociatedAudioMixing(handle[i], &mixing[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Step 04: Get audio mixing status in new array
		result = dsGetAssociatedAudioMixing(handle[i], &mixing1[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Step 06: Compare audio mixing status in arrays
		DS_ASSERT_AUTO_TERM_NUMERICAL(mixing[i], mixing1[i]);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetAssociatedAudioMixing() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 148@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsGetAssociatedAudioMixing() without initializing audio ports | handle=[invalid handle], mixing=[pointer] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized|
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetAssociatedAudioMixing() using an invalid handle and valid pointer |handle=[invalid hanlde], mixing=[pointer] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsGetAssociatedAudioMixing() by looping through the acquired valid handle with a NULL mixing pointer |handle=[valid handle], mixing=[NULL] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsGetAssociatedAudioMixing() again after terminating audio ports | handle`=[valid handle], mixing=[valid pointer] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized|
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions
 */
void test_l1_dsAudio_negative_dsGetAssociatedAudioMixing(void) {
	// Start of the test
	gTestID = 148; // Assuming Test Case ID is 148
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	bool mixing;

	// Step 01: Call without initializing
	result = dsGetAssociatedAudioMixing(-1, &mixing);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Call without initializing
	result = dsGetAssociatedAudioMixing(handle[0], &mixing);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NOT_INITIALIZED);

	// Step 04: Loop through kPorts to get audio port handle
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Call with NULL mixing pointer
		result = dsGetAssociatedAudioMixing(handle[i], &mixing);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Call again after terminating
	result = dsGetAssociatedAudioMixing(handle[0], &mixing);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}

/**
 * @brief Ensure dsSetFaderControl() correctly sets the mixer balance between main and associated audio during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 149@n
 * 
 * **Dependencies:**@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsSetFaderControl() by looping through the valid handles and valid mixer balance(i.e -32)| handle=[valid handle], mixerbalance=[-32] | dsERR_NONE | mixer balance should be successfully set the value |
 * |04|Call dsSetFaderControl() by looping through the valid handles and valid mixer balance(i.e +32 ) | handle=[valid handle], mixerbalance=[+32] | dsERR_NONE | mixer balance should be successfully set the value |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsSetFaderControl(void) {
	// Start of the test
	gTestID = 149; // Assuming Test Case ID is 149
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	int mixerbalance_neg = -32 ,mixerbalance_pos = 32;
	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Loop through supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Set mixer balance to -32
		result = dsSetFaderControl(handle[i], mixerbalance_neg);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Step 04: Set mixer balance to +32
		result = dsSetFaderControl(handle[i], mixerbalance_pos);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

	}

	// Step 05: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}



/**
 * @brief Ensure dsSetFaderControl() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 150@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsSetFaderControl() without initializing audio ports | handle=[invalid handle], mixerbalance=[valid value] | dsERR_NOT_INITIALIZED |call must fail as module not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetFaderControl() using an invalid handle with valid mixerbalance value(i.e -32 or +32) | handle=[invalid handle], mixerbalance=[valid value] |dsERR_INVALID_PARAM |Invalid parameter must return |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |04|Call dsSetFaderControl() by looping through acquired handles with an out of range mixerbalance value(i.e <-32 or >+32) | handle=[valid handle], mixerbalance=[invalid value] | dsERR_INVALID_PARAM| Invalid parameter must return|
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsSetFaderControl() again after terminating audio ports | handle=[valid handle], mixerbalance=[valid value] | dsERR_NOT_INITIALIZED |call must fail as module not initialized |
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions
 */
void test_l1_dsAudio_negative_dsSetFaderControl(void) {
	// Start of the test
	gTestID = 150; // Assuming Test Case ID is 150
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	int invalidMixerBalance = 100;                     // invalid mixer balance value

	// Step 01: Call without initializing
	int mixerBalance = 0; //valid value
	result = dsSetFaderControl(-1, mixerBalance);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Call with invalid handle
	result = dsSetFaderControl(handle[0], mixerBalance);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Loop through kPorts to get audio port handle
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Call with out of range mixer balance
		result = dsSetFaderControl(handle[i], invalidMixerBalance);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06:Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Call again after terminating
	result = dsSetFaderControl(handle[0], mixerBalance);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetFaderControl() correctly fetches the mixer balance between main and associated audio during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 151@n
 * 
 * **Dependencies:**@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetFaderControl() by looping through the acquired port handles to get the the mixer balance between main and associated audio of each port | handle: [ loop through valid handles ] , mixerbalance: [pointer to hold the mixer balance value(-32 to +32)] | dsERR_NONE | A valid audio mixer balance value must be returned |
 * |04|Call dsGetFaderControl() by looping through the acquired port handles to get the the mixer balance between main and associated audio of each port in new array| handle: [ loop through valid handles ] , mixerbalance: [pointer to hold the mixer balance value(-32 to +32)] | dsERR_NONE | A valid audio mixer balance value must be returned |
 * |05|Compare the array values and make sure they are equal| | dsERR_NONE | The values must be equal |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetFaderControl(void) {
	// Start of the test
	gTestID = 151; // Assuming Test Case ID is 151
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	int mixerBalance[NUM_OF_PORTS];
	int mixerBalance1[NUM_OF_PORTS];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Loop through supported audio ports
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Get mixer balance
		result = dsGetFaderControl(handle[i], &mixerBalance[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Step 04: Get mixer balance in other array
		result = dsGetFaderControl(handle[i], &mixerBalance1[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Step 05:Compare the  mixer balance in arrays
		DS_ASSERT_AUTO_TERM_NUMERICAL(mixerBalance[i], mixerBalance1[i]);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetFaderControl() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 152@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsGetFaderControl() without initializing audio ports | handle=[invalid handle], mixerbalance=[pointer] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetFaderControl() using an invalid handle and valid pointer |handle=[invalid hanlde], mixerbalance=[valid pointer] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsGetFaderControl() by looping through the acquired valid handle with a NULL mixerbalance pointer |handle=[valid handle], mixerbalance=[NULL] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsGetFaderControl() again after terminating audio ports | handle=[valid handle] , mixerbalance=[valid pointer] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized |
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions 
 */
void test_l1_dsAudio_negative_dsGetFaderControl(void) {
	// Start of the test
	gTestID = 152; // Assuming Test Case ID is 152
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	int mixerBalance;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};

	// Step 01: Call dsGetFaderControl() without initializing audio ports
	result = dsGetFaderControl(-1, &mixerBalance);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Call dsGetFaderControl() using an invalid handle
	result = dsGetFaderControl(handle[0], &mixerBalance);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get valid port handle
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Call dsGetFaderControl() with a NULL mixer balance pointer
		result = dsGetFaderControl(handle[i], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Call dsGetFaderControl() after terminating audio ports
	result = dsGetFaderControl(handle[0], &mixerBalance); // using last valid handle obtained
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetPrimaryLanguage() correctly sets the AC4 Primary language during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 153@n
 * 
 * **Dependencies:** Audio device should be connected.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsSetPrimaryLanguage() looping through the acquired ports and valid pointer to set an AC4 primary language  | handle=[valid handle], pLang=[ENG] | dsERR_NONE | primary langauage should be set successfully |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsSetPrimaryLanguage(void) {
	// Start of the test
	gTestID = 153; // Assuming Test Case ID is 153
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	const char *primaryLanguage = "ENG"; // Assuming "ENG" is a valid language code

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Get valid port handles and set primary language
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 03: Set AC4 primary language
		result = dsSetPrimaryLanguage(handle[i], primaryLanguage);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
	}

	// Step 07: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetPrimaryLanguage() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 154@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsSetPrimaryLanguage() without initializing audio ports | handle=[valid handle], pLang=[ENG] | dsERR_NOT_INITIALIZED | call must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetPrimaryLanguage() using an invalid handle with valid pLang pointer | handle=[invalid handle], pLang=[ENG] | dsERR_INVALID_PARAM or dsERR_OPERATION_NOT_SUPPORTED |Invalid parameter must be returned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsSetPrimaryLanguage() by looping through the valid handles and  passing NULL as the language pointer | handle=[valid handle] , pLang=[NULL] | dsERR_INVALID_PARAM | Invalid parameter must be returned |
 * |06|Call dsSetPrimaryLanguage() passing an unsupported language code | handle=[valid handle], pLang=[XYZ] | dsERR_INVALID_PARAM |Invalid parameter must be returned  |
 * |07|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |08|Call dsSetPrimaryLanguage() again after terminating audio ports | handle=[valid handle], pLang=[ENG] | dsERR_NOT_INITIALIZED | call must fail as module is not initialized |
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions 
 */
void test_l1_dsAudio_negative_dsSetPrimaryLanguage(void) {
	// Start of the test
	gTestID = 154; // Assuming Test Case ID is 154
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	const char *invalidLanguage = "XYZ"; // Assuming "XYZ" is an invalid language code

	// Step 01: Call without initializing audio ports
	result = dsSetPrimaryLanguage(-1, "ENG");
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Call with invalid handle
	result = dsSetPrimaryLanguage(handle[0], "ENG");
	DS_ASSERT_AUTO_TERM_NUMERICAL(result , dsERR_INVALID_PARAM);

	// Step 04: Get a valid port handles
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 04: Call with NULL language pointer
		result = dsSetPrimaryLanguage(handle[i], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

		// Step 05: Call with unsupported language code
		result = dsSetPrimaryLanguage(handle[i], invalidLanguage);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Call after terminating audio ports
	result = dsSetPrimaryLanguage(handle[0], "ENG");
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetPrimaryLanguage() correctly fetches the AC4 Primary language during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 155@n
 * 
 * **Dependencies:**@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetPrimaryLanguage() by looping through the acquired port handles to get the AC4 Primary language of each port | handle: [ loop through valid handles ] , pLang: [pointer to hold the AC4 Primary language code] | dsERR_NONE | A valid 3 letter AC4 Primary language code must be returned |
 * |04|Call dsGetPrimaryLanguage() by looping through the acquired port handles to get the AC4 Primary language of each port in new array | handle: [ loop through valid handles ] , pLang: [pointer to hold the AC4 Primary language code] | dsERR_NONE | A valid 3 letter AC4 Primary language code must be returned |
 * |05|Compare the array values and make sure they are equal| | dsERR_NONE | The values must be equal |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetPrimaryLanguage(void) {
	// Start of the test
	gTestID = 155; // Assuming Test Case ID is 155
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int array_size = 4; // Assuming 3 letter language code plus null terminator
	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	char primaryLanguage[array_size], primaryLanguage1[array_size];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02 and 03: Get valid port handles and fetch primary language
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Fetch AC4 Primary language in array
		result = dsGetPrimaryLanguage(handle[i], primaryLanguage);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Step 04: Fetch AC4 Primary language in new array
		result = dsGetPrimaryLanguage(handle[i], primaryLanguage1);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Step 05 : compare the primaryLanguage arrays
		DS_ASSERT_AUTO_TERM_NUMERICAL(primaryLanguage, primaryLanguage1);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetPrimaryLanguage() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 156@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsGetPrimaryLanguage() without initializing audio ports | handle=[valid handle], pLang=[valid pointer] | dsERR_NOT_INITIALIZED | call must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetPrimaryLanguage() using an invalid handle with valid pLang pointer | handle=[invalid handle], pLang=[valid pointer] | dsERR_INVALID_PARAM |Invalid parameter must be returned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsGetPrimaryLanguage() by looping through the valid handles and  passing NULL as the language pointer | handle=[valid handle] , pLang=[NULL] | dsERR_INVALID_PARAM | Invalid parameter must be returned |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsGetPrimaryLanguage() again after terminating audio ports |handle=[valid handle] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized |
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions
 */
void test_l1_dsAudio_negative_dsGetPrimaryLanguage(void) {
	// Start of the test
	gTestID = 156; // Assuming Test Case ID is 156
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	char primaryLanguage[4];

	// Step 01: Call without initializing audio ports
	result = dsGetPrimaryLanguage(-1, primaryLanguage);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Call with invalid handle
	result = dsGetPrimaryLanguage(handle[0], primaryLanguage);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get a valid port handle
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Call with NULL language pointer
		result = dsGetPrimaryLanguage(handle[i], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Call after terminating audio ports
	result = dsGetPrimaryLanguage(handle[0], primaryLanguage);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetSecondaryLanguage() correctly sets the AC4 Secondary language during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 157@n
 * 
 * **Dependencies:**@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsSetSecondaryLanguage() by looping through acquired port handles and valid sLang string | handle=[valid handles], sLang=[ENG] | dsERR_NONE | secondary language should be successfully set |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsSetSecondaryLanguage(void) {
	// Start of the test
	gTestID = 157; // Assuming Test Case ID is 157
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02 and 03: Get valid port handles and set secondary language
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Set Secondary language
		result = dsSetSecondaryLanguage(handle[i], "ENG");
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
	}

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsSetSecondaryLanguage() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 158@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsSetSecondaryLanguage() without initializing audio ports | handle=[valid handle], sLang=[ENG] | dsERR_NOT_INITIALIZED | call must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetSecondaryLanguage() using an invalid handle with valid sLang pointer | handle=[invalid handle], sLang=[ENG] | dsERR_INVALID_PARAM |Invalid parameter must be returned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsSetSecondaryLanguage() by looping through the valid handles and  passing NULL as the language pointer | handle=[valid handle] , sLang=[NULL] | dsERR_INVALID_PARAM | Invalid parameter must be returned |
 * |06|Call dsSetSecondaryLanguage() by looping through the valid handles and  unsupported language code | handle=[valid handle], sLang=[XYZ] | dsERR_INVALID_PARAM |Invalid parameter must be returned  |
 * |07|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |08|Call dsSetSecondaryLanguage() again after terminating audio ports | handle=[valid handle] , sLang=[ENG] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized |
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions
 */
void test_l1_dsAudio_negative_dsSetSecondaryLanguage(void) {
	// Start of the test
	gTestID = 158; // Assuming Test Case ID is 158
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};

	// Step 01: Call without initializing audio ports
	result = dsSetSecondaryLanguage(-1, "ENG");
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Call with invalid handle
	result = dsSetSecondaryLanguage(handle[0], "ENG");
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Get a valid port handle
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Call with NULL language pointer
		result = dsSetSecondaryLanguage(handle[i], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

		// Step 06: Call with unsupported language code
		result = dsSetSecondaryLanguage(handle[i], "XYZ");
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 07: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 08: Call after terminating audio ports
	result = dsSetSecondaryLanguage(handle[0], "ENG");
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetSecondaryLanguage() correctly fetches the AC4 Secondary language during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 159@n
 * 
 * **Dependencies:**@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetSecondaryLanguage() by looping through the acquired port handles to get the AC4 Secondary language of each port | handle: [ loop through valid handles ] , sLang: [pointer to hold the AC4 Secondary language code] | dsERR_NONE | A valid 3 letter AC4 Secondary language code must be returned |
 * |04|Call dsGetSecondaryLanguage() by looping through the acquired port handles to get the AC4 Secondary language of each port in a new array | handle: [ loop through valid handles ] , sLang: [pointer to hold the AC4 Secondary language code] | dsERR_NONE | A valid 3 letter AC4 Secondary language code must be returned |
 * |05|Compare the array values and make sure they are equal| | dsERR_NONE | The values must be equal |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetSecondaryLanguage(void) {
	// Start of the test
	gTestID = 159; // Assuming Test Case ID is 159
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);


	int result , array_size = 4;        //Assuming a 3 letter language code plus null terminator
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	char languageCode[array_size] , languageCode1[array_size];

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02 and 03: Get valid port handles and fetch secondary language
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Get Secondary language in a array
		result = dsGetSecondaryLanguage(handle[i], languageCode);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Step 04 : Get Secondary language in a new array
		result = dsGetSecondaryLanguage(handle[i], languageCode1);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

		// Step 05 : Get Secondary language in a new array
		DS_ASSERT_AUTO_TERM_NUMERICAL(languageCode, languageCode1);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetSecondaryLanguage() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 160@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsGetSecondaryLanguage() without initializing audio ports | handle=[valid handle], sLang=[valid pointer] | dsERR_NOT_INITIALIZED | call must fail as module is not initialized|
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetSecondaryLanguage() using an invalid handle with valid pLang pointer | handle=[invalid handle], sLang=[valid pointer] | dsERR_INVALID_PARAM |Invalid parameter must be returned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |04|Call dsGetSecondaryLanguage() by looping through the valid handles and  passing NULL as the language pointer | handle=[valid handle] , pLang=[NULL] | dsERR_INVALID_PARAM | Invalid parameter must be returned |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsGetSecondaryLanguage() again after terminating audio ports | handle=[valid handle] | dsERR_NOT_INITIALIZED | call must fail as module is not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions
 */
void test_l1_dsAudio_negative_dsGetSecondaryLanguage(void) {
	// Start of the test
	gTestID = 160; // Assuming Test Case ID is 160
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	intptr_t  handle[NUM_OF_PORTS] = {INT_ARRAY_INIT};
	char languageCode[4];

	// Step 01: Call without initializing audio ports
	result = dsGetSecondaryLanguage(-1, languageCode);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Call with invalid handle
	result = dsGetSecondaryLanguage(handle[0], languageCode);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Loop through kPorts to get audio port handle
	for (int i = 0; i < NUM_OF_PORTS; i++) {
		result = dsGetAudioPort(kPorts[i].id.type, kPorts[i].id.index, &handle[i]);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
		DS_ASSERT_AUTO_TERM_NOT_EQUAL(handle[i], null_handle);

		// Step 05: Call with NULL language pointer
		result = dsGetSecondaryLanguage(handle[0], NULL);
		DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
	}

	// Step 06: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 07: Call after terminating audio ports
	result = dsGetSecondaryLanguage(handle[0], languageCode);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetHDMIARCPortId() correctly fetches the audio HDMI ARC port ID during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 161@n
 * 
 * **Dependencies:** HDMI device should be connected and supports ARC.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Fetch the audio HDMI ARC port ID using dsGetHDMIARCPortId() | | dsERR_NONE and a valid port ID | Should Pass |
 * |03|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetHDMIARCPortId(void) {
	// Start of the test
	gTestID = 161; // Assuming Test Case ID is 161
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;
	int portId;

	// Step 01: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 02: Fetch the HDMI ARC port ID
	result = dsGetHDMIARCPortId(&portId);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
	UT_ASSERT_TRUE(portId >= 0);                // Assuming valid port ID is a non-negative integer

	// Step 03: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetHDMIARCPortId() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 162@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsGetHDMIARCPortId() without initializing audio ports | | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetHDMIARCPortId() passing NULL as the port ID pointer | `portId`=NULL | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |05|Call dsGetHDMIARCPortId() again after terminating audio ports | | dsERR_NOT_INITIALIZED | Should Pass |
 * 
 */
void test_l1_dsAudio_negative_dsGetHDMIARCPortId(void) {
	// Start of the test
	gTestID = 162; // Assuming Test Case ID is 162
	UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

	int result;

	// Step 01: Call without initializing audio ports
	result = dsGetHDMIARCPortId(NULL);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// Step 02: Initialize audio ports
	result = dsAudioPortInit();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 03: Call with NULL port ID pointer
	result = dsGetHDMIARCPortId(NULL);
	DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

	// Step 04: Terminate audio ports
	result = dsAudioPortTerm();
	UT_ASSERT_EQUAL(result, dsERR_NONE);

	// Step 05: Call after terminating audio ports
	result = dsGetHDMIARCPortId(NULL);
	UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

	// End of the test
	UT_LOG("\n Out %s\n", __FUNCTION__);
}


static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main test(s) for this module
 *
 * @return int - 0 on success, otherwise failure
 */
int test_l1_dsAudio_register ( void )
{
	/* add a suite to the registry */
	pSuite = UT_add_suite( "[L1 dsAudio]", NULL, NULL );
	if ( NULL == pSuite )
	{
		return -1;
	}	

	UT_add_test( pSuite, "dsAudioPortInit_L1_positive" ,test_l1_dsAudio_positive_dsAudioPortInit );
	UT_add_test( pSuite, "dsAudioPortInit_L1_negative" ,test_l1_dsAudio_negative_dsAudioPortInit );
	UT_add_test( pSuite, "dsAudioPortTerm_L1_positive" ,test_l1_dsAudio_positive_dsAudioPortTerm );
	UT_add_test( pSuite, "dsAudioPortTerm_L1_negative" ,test_l1_dsAudio_negative_dsAudioPortTerm );
	UT_add_test( pSuite, "dsGetAudioPort_L1_positive" ,test_l1_dsAudio_positive_dsGetAudioPort );
	UT_add_test( pSuite, "dsGetAudioPort_L1_negative" ,test_l1_dsAudio_negative_dsGetAudioPort );
	UT_add_test( pSuite, "dsGetAudioEncoding_L1_positive" ,test_l1_dsAudio_positive_dsGetAudioEncoding );
	UT_add_test( pSuite, "dsGetAudioEncoding_L1_negative" ,test_l1_dsAudio_negative_dsGetAudioEncoding );
	UT_add_test( pSuite, "dsSetAudioEncoding_L1_positive" ,test_l1_dsAudio_positive_dsSetAudioEncoding );
	UT_add_test( pSuite, "dsSetAudioEncoding_L1_negative" ,test_l1_dsAudio_negative_dsSetAudioEncoding );
	UT_add_test( pSuite, "dsGetAudioFormat_L1_positive" ,test_l1_dsAudio_positive_dsGetAudioFormat );
	UT_add_test( pSuite, "dsGetAudioFormat_L1_negative" ,test_l1_dsAudio_negative_dsGetAudioFormat );
	UT_add_test( pSuite, "dsGetAudioCompression_L1_positive" ,test_l1_dsAudio_positive_dsGetAudioCompression );
	UT_add_test( pSuite, "dsGetAudioCompression_L1_negative" ,test_l1_dsAudio_negative_dsGetAudioCompression );
	UT_add_test( pSuite, "dsSetAudioCompression_L1_positive" ,test_l1_dsAudio_positive_dsSetAudioCompression );
	UT_add_test( pSuite, "dsSetAudioCompression_L1_negative" ,test_l1_dsAudio_negative_dsSetAudioCompression );
	UT_add_test( pSuite, "dsGetDialogEnhancement_L1_positive" ,test_l1_dsAudio_positive_dsGetDialogEnhancement );
	UT_add_test( pSuite, "dsGetDialogEnhancement_L1_negative" ,test_l1_dsAudio_negative_dsGetDialogEnhancement );
	UT_add_test( pSuite, "dsSetDialogEnhancement_L1_positive" ,test_l1_dsAudio_positive_dsSetDialogEnhancement );
	UT_add_test( pSuite, "dsSetDialogEnhancement_L1_negative" ,test_l1_dsAudio_negative_dsSetDialogEnhancement );
	UT_add_test( pSuite, "dsGetDolbyVolumeMode_L1_positive" ,test_l1_dsAudio_positive_dsGetDolbyVolumeMode );
	UT_add_test( pSuite, "dsGetDolbyVolumeMode_L1_negative" ,test_l1_dsAudio_negative_dsGetDolbyVolumeMode );
	UT_add_test( pSuite, "dsSetDolbyVolumeMode_L1_positive" ,test_l1_dsAudio_positive_dsSetDolbyVolumeMode );
	UT_add_test( pSuite, "dsSetDolbyVolumeMode_L1_negative" ,test_l1_dsAudio_negative_dsSetDolbyVolumeMode );
	UT_add_test( pSuite, "dsGetIntelligentEqualizerMode_L1_positive" ,test_l1_dsAudio_positive_dsGetIntelligentEqualizerMode );
	UT_add_test( pSuite, "dsGetIntelligentEqualizerMode_L1_negative" ,test_l1_dsAudio_negative_dsGetIntelligentEqualizerMode );
	UT_add_test( pSuite, "dsSetIntelligentEqualizerMode_L1_positive" ,test_l1_dsAudio_positive_dsSetIntelligentEqualizerMode );
	UT_add_test( pSuite, "dsSetIntelligentEqualizerMode_L1_negative" ,test_l1_dsAudio_negative_dsSetIntelligentEqualizerMode );
	UT_add_test( pSuite, "dsGetVolumeLeveller_L1_positive" ,test_l1_dsAudio_positive_dsGetVolumeLeveller );
	UT_add_test( pSuite, "dsGetVolumeLeveller_L1_negative" ,test_l1_dsAudio_negative_dsGetVolumeLeveller );
	UT_add_test( pSuite, "dsSetVolumeLeveller_L1_positive" ,test_l1_dsAudio_positive_dsSetVolumeLeveller );
	UT_add_test( pSuite, "dsSetVolumeLeveller_L1_negative" ,test_l1_dsAudio_negative_dsSetVolumeLeveller );
	UT_add_test( pSuite, "dsGetBassEnhancer_L1_positive" ,test_l1_dsAudio_positive_dsGetBassEnhancer );
	UT_add_test( pSuite, "dsGetBassEnhancer_L1_negative" ,test_l1_dsAudio_negative_dsGetBassEnhancer );
	UT_add_test( pSuite, "dsSetBassEnhancer_L1_positive" ,test_l1_dsAudio_positive_dsSetBassEnhancer );
	UT_add_test( pSuite, "dsSetBassEnhancer_L1_negative" ,test_l1_dsAudio_negative_dsSetBassEnhancer );
	UT_add_test( pSuite, "dsIsSurroundDecoderEnabled_L1_positive" ,test_l1_dsAudio_positive_dsIsSurroundDecoderEnabled );
	UT_add_test( pSuite, "dsIsSurroundDecoderEnabled_L1_negative" ,test_l1_dsAudio_negative_dsIsSurroundDecoderEnabled );
	UT_add_test( pSuite, "dsEnableSurroundDecoder_L1_positive" ,test_l1_dsAudio_positive_dsEnableSurroundDecoder );
	UT_add_test( pSuite, "dsEnableSurroundDecoder_L1_negative" ,test_l1_dsAudio_negative_dsEnableSurroundDecoder );
	UT_add_test( pSuite, "dsGetDRCMode_L1_positive" ,test_l1_dsAudio_positive_dsGetDRCMode );
	UT_add_test( pSuite, "dsGetDRCMode_L1_negative" ,test_l1_dsAudio_negative_dsGetDRCMode );
	UT_add_test( pSuite, "dsSetDRCMode_L1_positive" ,test_l1_dsAudio_positive_dsSetDRCMode );
	UT_add_test( pSuite, "dsSetDRCMode_L1_negative" ,test_l1_dsAudio_negative_dsSetDRCMode );
	UT_add_test( pSuite, "dsGetSurroundVirtualizer_L1_positive" ,test_l1_dsAudio_positive_dsGetSurroundVirtualizer );
	UT_add_test( pSuite, "dsGetSurroundVirtualizer_L1_negative" ,test_l1_dsAudio_negative_dsGetSurroundVirtualizer );
	UT_add_test( pSuite, "dsSetSurroundVirtualizer_L1_positive" ,test_l1_dsAudio_positive_dsSetSurroundVirtualizer );
	UT_add_test( pSuite, "dsSetSurroundVirtualizer_L1_negative" ,test_l1_dsAudio_negative_dsSetSurroundVirtualizer );
	UT_add_test( pSuite, "dsGetMISteering_L1_positive" ,test_l1_dsAudio_positive_dsGetMISteering );
	UT_add_test( pSuite, "dsGetMISteering_L1_negative" ,test_l1_dsAudio_negative_dsGetMISteering );
	UT_add_test( pSuite, "dsSetMISteering_L1_positive" ,test_l1_dsAudio_positive_dsSetMISteering );
	UT_add_test( pSuite, "dsSetMISteering_L1_negative" ,test_l1_dsAudio_negative_dsSetMISteering );
	UT_add_test( pSuite, "dsGetGraphicEqualizerMode_L1_positive" ,test_l1_dsAudio_positive_dsGetGraphicEqualizerMode );
	UT_add_test( pSuite, "dsGetGraphicEqualizerMode_L1_negative" ,test_l1_dsAudio_negative_dsGetGraphicEqualizerMode );
	UT_add_test( pSuite, "dsSetGraphicEqualizerMode_L1_positive" ,test_l1_dsAudio_positive_dsSetGraphicEqualizerMode );
	UT_add_test( pSuite, "dsSetGraphicEqualizerMode_L1_negative" ,test_l1_dsAudio_negative_dsSetGraphicEqualizerMode );
	UT_add_test( pSuite, "dsGetMS12AudioProfileList_L1_positive" ,test_l1_dsAudio_positive_dsGetMS12AudioProfileList );
	UT_add_test( pSuite, "dsGetMS12AudioProfileList_L1_negative" ,test_l1_dsAudio_negative_dsGetMS12AudioProfileList );
	UT_add_test( pSuite, "dsGetMS12AudioProfile_L1_positive" ,test_l1_dsAudio_positive_dsGetMS12AudioProfile );
	UT_add_test( pSuite, "dsGetMS12AudioProfile_L1_negative" ,test_l1_dsAudio_negative_dsGetMS12AudioProfile );
	UT_add_test( pSuite, "dsGetStereoMode_L1_positive" ,test_l1_dsAudio_positive_dsGetStereoMode );
	UT_add_test( pSuite, "dsGetStereoMode_L1_negative" ,test_l1_dsAudio_negative_dsGetStereoMode );
	UT_add_test( pSuite, "dsSetStereoMode_L1_positive" ,test_l1_dsAudio_positive_dsSetStereoMode );
	UT_add_test( pSuite, "dsSetStereoMode_L1_negative" ,test_l1_dsAudio_negative_dsSetStereoMode );
	UT_add_test( pSuite, "dsGetStereoAuto_L1_positive" ,test_l1_dsAudio_positive_dsGetStereoAuto );
	UT_add_test( pSuite, "dsGetStereoAuto_L1_negative" ,test_l1_dsAudio_negative_dsGetStereoAuto );
	UT_add_test( pSuite, "dsSetStereoAuto_L1_positive" ,test_l1_dsAudio_positive_dsSetStereoAuto );
	UT_add_test( pSuite, "dsSetStereoAuto_L1_negative" ,test_l1_dsAudio_negative_dsSetStereoAuto );
	UT_add_test( pSuite, "dsGetAudioGain_L1_positive" ,test_l1_dsAudio_positive_dsGetAudioGain );
	UT_add_test( pSuite, "dsGetAudioGain_L1_negative" ,test_l1_dsAudio_negative_dsGetAudioGain );
	UT_add_test( pSuite, "dsSetAudioGain_L1_positive" ,test_l1_dsAudio_positive_dsSetAudioGain );
	UT_add_test( pSuite, "dsSetAudioGain_L1_negative" ,test_l1_dsAudio_negative_dsSetAudioGain );
	UT_add_test( pSuite, "dsGetAudioDB_L1_positive" ,test_l1_dsAudio_positive_dsGetAudioDB );
	UT_add_test( pSuite, "dsGetAudioDB_L1_negative" ,test_l1_dsAudio_negative_dsGetAudioDB );
	UT_add_test( pSuite, "dsSetAudioDB_L1_positive" ,test_l1_dsAudio_positive_dsSetAudioDB );
	UT_add_test( pSuite, "dsSetAudioDB_L1_negative" ,test_l1_dsAudio_negative_dsSetAudioDB );
	UT_add_test( pSuite, "dsGetAudioLevel_L1_positive" ,test_l1_dsAudio_positive_dsGetAudioLevel );
	UT_add_test( pSuite, "dsGetAudioLevel_L1_negative" ,test_l1_dsAudio_negative_dsGetAudioLevel );
	UT_add_test( pSuite, "dsSetAudioLevel_L1_positive" ,test_l1_dsAudio_positive_dsSetAudioLevel );
	UT_add_test( pSuite, "dsSetAudioLevel_L1_negative" ,test_l1_dsAudio_negative_dsSetAudioLevel );
	UT_add_test( pSuite, "dsGetAudioMaxDB_L1_positive" ,test_l1_dsAudio_positive_dsGetAudioMaxDB );
	UT_add_test( pSuite, "dsGetAudioMaxDB_L1_negative" ,test_l1_dsAudio_negative_dsGetAudioMaxDB );
	UT_add_test( pSuite, "dsGetAudioMinDB_L1_positive" ,test_l1_dsAudio_positive_dsGetAudioMinDB );
	UT_add_test( pSuite, "dsGetAudioMinDB_L1_negative" ,test_l1_dsAudio_negative_dsGetAudioMinDB );
	UT_add_test( pSuite, "dsGetAudioOptimalLevel_L1_positive" ,test_l1_dsAudio_positive_dsGetAudioOptimalLevel );
	UT_add_test( pSuite, "dsGetAudioOptimalLevel_L1_negative" ,test_l1_dsAudio_negative_dsGetAudioOptimalLevel );
	UT_add_test( pSuite, "dsGetAudioDelay_L1_positive" ,test_l1_dsAudio_positive_dsGetAudioDelay );
	UT_add_test( pSuite, "dsGetAudioDelay_L1_negative" ,test_l1_dsAudio_negative_dsGetAudioDelay );
	UT_add_test( pSuite, "dsSetAudioDelay_L1_positive" ,test_l1_dsAudio_positive_dsSetAudioDelay );
	UT_add_test( pSuite, "dsSetAudioDelay_L1_negative" ,test_l1_dsAudio_negative_dsSetAudioDelay );
	UT_add_test( pSuite, "dsGetAudioDelayOffset_L1_positive" ,test_l1_dsAudio_positive_dsGetAudioDelayOffset );
	UT_add_test( pSuite, "dsGetAudioDelayOffset_L1_negative" ,test_l1_dsAudio_negative_dsGetAudioDelayOffset );
	UT_add_test( pSuite, "dsSetAudioDelayOffset_L1_positive" ,test_l1_dsAudio_positive_dsSetAudioDelayOffset );
	UT_add_test( pSuite, "dsSetAudioDelayOffset_L1_negative" ,test_l1_dsAudio_negative_dsSetAudioDelayOffset );
	UT_add_test( pSuite, "dsSetAudioAtmosOutputMode_L1_positive" ,test_l1_dsAudio_positive_dsSetAudioAtmosOutputMode );
	UT_add_test( pSuite, "dsSetAudioAtmosOutputMode_L1_negative" ,test_l1_dsAudio_negative_dsSetAudioAtmosOutputMode );
	UT_add_test( pSuite, "dsGetSinkDeviceAtmosCapability_L1_positive" ,test_l1_dsAudio_positive_dsGetSinkDeviceAtmosCapability );
	UT_add_test( pSuite, "dsGetSinkDeviceAtmosCapability_L1_negative" ,test_l1_dsAudio_negative_dsGetSinkDeviceAtmosCapability );
	UT_add_test( pSuite, "dsIsAudioLoopThru_L1_positive" ,test_l1_dsAudio_positive_dsIsAudioLoopThru );
	UT_add_test( pSuite, "dsIsAudioLoopThru_L1_negative" ,test_l1_dsAudio_negative_dsIsAudioLoopThru );
	UT_add_test( pSuite, "dsIsAudioMute_L1_positive" ,test_l1_dsAudio_positive_dsIsAudioMute );
	UT_add_test( pSuite, "dsIsAudioMute_L1_negative" ,test_l1_dsAudio_negative_dsIsAudioMute );
	UT_add_test( pSuite, "dsIsAudioPortEnabled_L1_positive" ,test_l1_dsAudio_positive_dsIsAudioPortEnabled );
	UT_add_test( pSuite, "dsIsAudioPortEnabled_L1_negative" ,test_l1_dsAudio_negative_dsIsAudioPortEnabled );
	UT_add_test( pSuite, "dsEnableAudioPort_L1_positive" ,test_l1_dsAudio_positive_dsEnableAudioPort );
	UT_add_test( pSuite, "dsEnableAudioPort_L1_negative" ,test_l1_dsAudio_negative_dsEnableAudioPort );
	UT_add_test( pSuite, "dsEnableMS12Config_L1_positive" ,test_l1_dsAudio_positive_dsEnableMS12Config );
	UT_add_test( pSuite, "dsEnableMS12Config_L1_negative" ,test_l1_dsAudio_negative_dsEnableMS12Config );
	UT_add_test( pSuite, "dsEnableLEConfig_L1_positive" ,test_l1_dsAudio_positive_dsEnableLEConfig );
	UT_add_test( pSuite, "dsEnableLEConfig_L1_negative" ,test_l1_dsAudio_negative_dsEnableLEConfig );
	UT_add_test( pSuite, "dsGetLEConfig_L1_positive" ,test_l1_dsAudio_positive_dsGetLEConfig );
	UT_add_test( pSuite, "dsGetLEConfig_L1_negative" ,test_l1_dsAudio_negative_dsGetLEConfig );
	UT_add_test( pSuite, "dsSetMS12AudioProfile_L1_positive" ,test_l1_dsAudio_positive_dsSetMS12AudioProfile );
	UT_add_test( pSuite, "dsSetMS12AudioProfile_L1_negative" ,test_l1_dsAudio_negative_dsSetMS12AudioProfile );
	UT_add_test( pSuite, "dsSetAudioDucking_L1_positive" ,test_l1_dsAudio_positive_dsSetAudioDucking );
	UT_add_test( pSuite, "dsSetAudioDucking_L1_negative" ,test_l1_dsAudio_negative_dsSetAudioDucking );
	UT_add_test( pSuite, "dsEnableLoopThru_L1_positive" ,test_l1_dsAudio_positive_dsEnableLoopThru );
	UT_add_test( pSuite, "dsEnableLoopThru_L1_negative" ,test_l1_dsAudio_negative_dsEnableLoopThru );
	UT_add_test( pSuite, "dsSetAudioMute_L1_positive" ,test_l1_dsAudio_positive_dsSetAudioMute );
	UT_add_test( pSuite, "dsSetAudioMute_L1_negative" ,test_l1_dsAudio_negative_dsSetAudioMute );
	UT_add_test( pSuite, "dsIsAudioMSDecode_L1_positive" ,test_l1_dsAudio_positive_dsIsAudioMSDecode );
	UT_add_test( pSuite, "dsIsAudioMSDecode_L1_negative" ,test_l1_dsAudio_negative_dsIsAudioMSDecode );
	UT_add_test( pSuite, "dsIsAudioMS12Decode_L1_positive" ,test_l1_dsAudio_positive_dsIsAudioMS12Decode );
	UT_add_test( pSuite, "dsIsAudioMS12Decode_L1_negative" ,test_l1_dsAudio_negative_dsIsAudioMS12Decode );
	UT_add_test( pSuite, "dsAudioOutIsConnected_L1_positive" ,test_l1_dsAudio_positive_dsAudioOutIsConnected );
	UT_add_test( pSuite, "dsAudioOutIsConnected_L1_negative" ,test_l1_dsAudio_negative_dsAudioOutIsConnected );
	UT_add_test( pSuite, "dsAudioOutRegisterConnectCB_L1_positive" ,test_l1_dsAudio_positive_dsAudioOutRegisterConnectCB );
	UT_add_test( pSuite, "dsAudioOutRegisterConnectCB_L1_negative" ,test_l1_dsAudio_negative_dsAudioOutRegisterConnectCB );
	UT_add_test( pSuite, "dsAudioFormatUpdateRegisterCB_L1_positive" ,test_l1_dsAudio_positive_dsAudioFormatUpdateRegisterCB );
	UT_add_test( pSuite, "dsAudioFormatUpdateRegisterCB_L1_negative" ,test_l1_dsAudio_negative_dsAudioFormatUpdateRegisterCB );
	UT_add_test( pSuite, "dsGetAudioCapabilities_L1_positive" ,test_l1_dsAudio_positive_dsGetAudioCapabilities );
	UT_add_test( pSuite, "dsGetAudioCapabilities_L1_negative" ,test_l1_dsAudio_negative_dsGetAudioCapabilities );
	UT_add_test( pSuite, "dsGetMS12Capabilities_L1_positive" ,test_l1_dsAudio_positive_dsGetMS12Capabilities );
	UT_add_test( pSuite, "dsGetMS12Capabilities_L1_negative" ,test_l1_dsAudio_negative_dsGetMS12Capabilities );
	UT_add_test( pSuite, "dsResetDialogEnhancement_L1_positive" ,test_l1_dsAudio_positive_dsResetDialogEnhancement );
	UT_add_test( pSuite, "dsResetDialogEnhancement_L1_negative" ,test_l1_dsAudio_negative_dsResetDialogEnhancement );
	UT_add_test( pSuite, "dsResetBassEnhancer_L1_positive" ,test_l1_dsAudio_positive_dsResetBassEnhancer );
	UT_add_test( pSuite, "dsResetBassEnhancer_L1_negative" ,test_l1_dsAudio_negative_dsResetBassEnhancer );
	UT_add_test( pSuite, "dsResetSurroundVirtualizer_L1_positive" ,test_l1_dsAudio_positive_dsResetSurroundVirtualizer );
	UT_add_test( pSuite, "dsResetSurroundVirtualizer_L1_negative" ,test_l1_dsAudio_negative_dsResetSurroundVirtualizer );
	UT_add_test( pSuite, "dsResetVolumeLeveller_L1_positive" ,test_l1_dsAudio_positive_dsResetVolumeLeveller );
	UT_add_test( pSuite, "dsResetVolumeLeveller_L1_negative" ,test_l1_dsAudio_negative_dsResetVolumeLeveller );
	UT_add_test( pSuite, "dsSetAssociatedAudioMixing_L1_positive" ,test_l1_dsAudio_positive_dsSetAssociatedAudioMixing );
	UT_add_test( pSuite, "dsSetAssociatedAudioMixing_L1_negative" ,test_l1_dsAudio_negative_dsSetAssociatedAudioMixing );
	UT_add_test( pSuite, "dsGetAssociatedAudioMixing_L1_positive" ,test_l1_dsAudio_positive_dsGetAssociatedAudioMixing );
	UT_add_test( pSuite, "dsGetAssociatedAudioMixing_L1_negative" ,test_l1_dsAudio_negative_dsGetAssociatedAudioMixing );
	UT_add_test( pSuite, "dsSetFaderControl_L1_positive" ,test_l1_dsAudio_positive_dsSetFaderControl );
	UT_add_test( pSuite, "dsSetFaderControl_L1_negative" ,test_l1_dsAudio_negative_dsSetFaderControl );
	UT_add_test( pSuite, "dsGetFaderControl_L1_positive" ,test_l1_dsAudio_positive_dsGetFaderControl );
	UT_add_test( pSuite, "dsGetFaderControl_L1_negative" ,test_l1_dsAudio_negative_dsGetFaderControl );
	UT_add_test( pSuite, "dsSetPrimaryLanguage_L1_positive" ,test_l1_dsAudio_positive_dsSetPrimaryLanguage );
	UT_add_test( pSuite, "dsSetPrimaryLanguage_L1_negative" ,test_l1_dsAudio_negative_dsSetPrimaryLanguage );
	UT_add_test( pSuite, "dsGetPrimaryLanguage_L1_positive" ,test_l1_dsAudio_positive_dsGetPrimaryLanguage );
	UT_add_test( pSuite, "dsGetPrimaryLanguage_L1_negative" ,test_l1_dsAudio_negative_dsGetPrimaryLanguage );
	UT_add_test( pSuite, "dsSetSecondaryLanguage_L1_positive" ,test_l1_dsAudio_positive_dsSetSecondaryLanguage );
	UT_add_test( pSuite, "dsSetSecondaryLanguage_L1_negative" ,test_l1_dsAudio_negative_dsSetSecondaryLanguage );
	UT_add_test( pSuite, "dsGetSecondaryLanguage_L1_positive" ,test_l1_dsAudio_positive_dsGetSecondaryLanguage );
	UT_add_test( pSuite, "dsGetSecondaryLanguage_L1_negative" ,test_l1_dsAudio_negative_dsGetSecondaryLanguage );
	UT_add_test( pSuite, "dsGetHDMIARCPortId_L1_positive" ,test_l1_dsAudio_positive_dsGetHDMIARCPortId );
	UT_add_test( pSuite, "dsGetHDMIARCPortId_L1_negative" ,test_l1_dsAudio_negative_dsGetHDMIARCPortId );


	return 0;
} 
