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

#include <ut.h>
#include <ut_log.h>

static int gTestGroup = 1;
static int gTestID = 1;


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
    UT_LOG("Step 01: Initialize dsAudio -> Expected: dsERR_NONE, Got: %d\n", result);

    // Step 02: Call dsAudioPortTerm() Terminate dsAudio
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("Step 02: Terminate dsAudio -> Expected: dsERR_NONE, Got: %d\n", result);

    // Step 03: Call dsAudioPortInit() Initialize dsAudio
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("Step 03: Initialize dsAudio again -> Expected: dsERR_NONE, Got: %d\n", result);

    // Step 04: Call dsAudioPortTerm() Terminate dsAudio again
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("Step 04: Terminate dsAudio again -> Expected: dsERR_NONE, Got: %d\n", result);
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
 * @note Tests for a headless gateway device, which would return dsERR_OPERATION_NOT_SUPPORTED, dsERR_GENERAL are not included here but should be considered in a real-world scenario for the platforms that doesn't support Audio Port.
 */
void test_l1_dsAudio_negative_dsAudioPortInit (void)
{
	gTestID = 2;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
	
    // Step 01: Call dsAudioPortInit() Initialize dsAudio
    dsError_t result = dsAudioPortInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("Step 01: Initialize dsAudio -> Expected: dsERR_NONE, Got: %d\n", result);

    // Step 02: Call dsAudioPortInit() Attempt to initialize dsAudio again
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL(result, dsERR_ALREADY_INITIALIZED);
    UT_LOG("Step 02: Attempt to initialize dsAudio again -> Expected: dsERR_ALREADY_INITIALIZED, Got: %d\n", result);

    // Step 03: Call dsAudioPortTerm() Terminate dsAudio
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("Step 03: Terminate dsAudio -> Expected: dsERR_NONE, Got: %d\n", result);
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
    UT_LOG("Step 01: Initialize dsAudio -> Expected: dsERR_NONE, Got: %d\n", result);

    // Step 02: dsAudioPortTerm() Terminate dsAudio
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("Step 02: Terminate dsAudio -> Expected: dsERR_NONE, Got: %d\n", result);

    // Step 03: dsAudioPortInit() Initialize dsAudio again
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("Step 03: Initialize dsAudio again -> Expected: dsERR_NONE, Got: %d\n", result);

    // Step 04: dsAudioPortTerm() Terminate dsAudio
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("Step 04: Terminate dsAudio again -> Expected: dsERR_NONE, Got: %d\n", result);
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
 * @note dsERR_OPERATION_NOT_SUPPORTED is not included here but should be considered in a real-world scenario for the platforms that doesn't support Audio Port .
 * 
 */
void test_l1_dsAudio_negative_dsAudioPortTerm (void)
{
	gTestID = 4;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
	
    // Step 01: dsAudioPortTerm() Attempt to terminate dsAudio without initialization
    dsError_t result = dsAudioPortTerm();
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);
    UT_LOG("Step 01: Attempt to terminate dsAudio without initialization -> Expected: dsERR_NOT_INITIALIZED, Got: %d\n", result);

    // Step 02: dsAudioPortInit() Initialize dsAudio
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("Step 02: Initialize dsAudio -> Expected: dsERR_NONE, Got: %d\n", result);

    // Step 03: dsAudioPortTerm() Terminate dsAudio after initialization
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("Step 03: Terminate dsAudio after initialization -> Expected: dsERR_NONE, Got: %d\n", result);

    // Step 04: dsAudioPortTerm() Attempt to terminate dsAudio again
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);
    UT_LOG("Step 04: Attempt to terminate dsAudio again -> Expected: dsERR_NOT_INITIALIZED, Got: %d\n", result);
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
 * @todo - add note wherever kPorts is used
 * 
 * @todo - check the dsAUDIOPORT_TYPE_NUM_MAX in code, see where it is used(Sample file). If it is 2, are we allocating memory for 4 elements
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
void test_l1_dsAudio_positive_dsGetAudioPort (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAudioPort() returns correct error codes during negative scenarios
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
 * |01|Call dsGetAudioPort() - Attempt to get the Audio Port handle without initializing audio ports | `type`,`index`= kPorts[0], `handle`= valid handle | dsERR_NOT_INITIALIZED | Get Audio Port Handle must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetAudioPort() - by looping through valid port indexes but with invalid type  | type = [not in kPorts] , index = [ loop through kPorts ], handle = [ valid handle ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetAudioPort() - by looping through valid types but with invalid index | type = [loop through types in kPorts], index = [ invalid index which is not in kPorts ], handle: [ valid handle ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |05|Call dsGetAudioPort() - by looping through valid types and index but with a NULL handle | type, index: [ loop through kPorts ], handle: [ NULL pointer ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetAudioPort() - Attempt to get the audio port handle again after termination | type, index:  [ loop through kPorts ], handle: [ valid handle ] | dsERR_NOT_INITIALIZED | Get Audio Port Handle must fail as module is not initialized |
 * 
 * @note  Testing for the `dsERR_OPERATION_NOT_SUPPORTED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsAudio_negative_dsGetAudioPort (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAudioEncoding() returns correct audio encoding during positive scenarios
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
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetAudioEncoding() by looping through the acquired port handles to get the audio encoding of each port | handle: [ loop through valid handles ] , encoding: [pointer to hold the encoding] | dsERR_NONE | A valid audio encoding must be returned |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetAudioEncoding (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAudioEncoding() returns correct error codes during negative scenarios
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
 * |01|Call dsGetAudioEncoding() - Get the audio encoding without initializing audio ports | handle: [valid handle]| dsERR_NOT_INITIALIZED | Get audio encoding must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetAudioEncoding() using an invalid handle | handle: [invalid handle], encoding: [ pointer to hold the encoding ] | dsERR_INVALID_PARAM | TInvalid parameter error must be returned |
 * |04|Call dsGetAudioPort() Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsGetAudioEncoding() by looping through acquired port handles but with a null encoding pointer | handle: [ loop through valid handles ], encoding: [ NULL ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned when NULL pointer is passed for encoding |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetAudioEncoding() - Attempt to get the audio encoding type after terminating audio ports | handle: [ valid handle ], encoding: [ pointer to hold the encoding ] | dsERR_NOT_INITIALIZED | Get audio encoding must fail as module is not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetAudioEncoding (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetAudioEncoding() sets the audio encoding correctly for all valid enum values during positive scenarios
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
 * |01|Call dsAudioPortInit() Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsSetAudioEncoding() by looping through the acquired port handles and set the supported encoding values (by looping through kSupportedEncodings) for each audio ports | handle: [valid handles ], encoding: [ Loop through kSupportedEncodings values ] | dsERR_NONE if supports or dsERR_GENERAL if not supported  | Supported encoding values must be set for each audio port |
 * |04|Call dsAudioPortTerm() - Terminate audio ports| | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsSetAudioEncoding (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetAudioEncoding() returns correct error codes during negative scenarios
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
 * |01|Call dsSetAudioEncoding() - Attempt to get the Audio Port handle without initializing audio ports | type,index: [ kPorts[0] ], handle: [ valid handle ] | dsERR_NOT_INITIALIZED | Set Audio Encoding must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports| | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetAudioEncoding() using an invalid handle but with a valid encoding type | handle: [ invalid handle ] , encoding : [ valid dsAudioEncoding_t value ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsSetAudioEncoding() - Loop through the acquired port handles and set an encoding type that is not part of the dsAudioEncoding_t(out of bounds) | handle: [ valid handle ], encoding: [ invalid encoding value ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsAudioPortTerm() - Terminate audio ports| | dsERR_NONE | Termination must be successful |
 * |07|Call dsSetAudioEncoding() again after terminating audio ports | handle: [ valid handle ] , encoding: [ valid dsAudioEncoding_t value ] | dsERR_NOT_INITIALIZED | Set Audio Encoding must fail as module is not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsSetAudioEncoding (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAudioFormat() retrieves the audio format correctly during positive scenarios
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
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetAudioFormat() by looping through the acquired port handles to get the audio format of each port | handle: [ loop through valid handles ] , audioFormat: [pointer to hold the audio format] | dsERR_NONE | A valid audio encoding must be returned |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetAudioFormat (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAudioFormat() returns correct error codes during negative scenarios
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
 * |01|Call dsGetAudioFormat() - Attempt to get audio format without initializing audio ports | handle: [ valid handle ], audioFormat: [pointer to hold audio format] | dsERR_NOT_INITIALIZED | Get Audio Format must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetAudioFormat() using an invalid handle but with a valid pointer to hold the audio format | handle: [ invalid handle ], audioFormat: [ pointer ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsGetAudioFormat() by looping through acquired port handles but with a null pointer for audio format | handle: [ loop through valid handles ], encoding: [ NULL ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE | Terminates the audio ports |
 * |07|Call dsGetAudioFormat() - Attempt to get audio format after terminating audio ports | handle: [ valid handle ] , audioFormat= [ pointer to hold audio format ]  | dsERR_NOT_INITIALIZED | Get Audio Format must fail as module is not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetAudioFormat (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAudioCompression() retrieves the audio compression level correctly during positive scenarios
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
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetAudioCompression() by looping through the acquired port handles to get the audio compression level of each port | handle: [ loop through valid handles ], compression: [ pointer to hold the audio compression level ] | dsERR_NONE and compression value in range [0,10] | Audio compression should be retrieved correctly |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE | Should Pass |
 * 
 */
void test_l1_dsAudio_positive_dsGetAudioCompression (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAudioCompression() returns correct error codes during negative scenarios
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
 * |01|Call dsGetAudioCompression() - Attempt to get audio compression without initializing audio ports | handle: [ valid handle ], compression: [ pointer to hold the audio compression ] | dsERR_NOT_INITIALIZED | Get audio compression must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetAudioCompression() using an invalid handle but with a valid pointer to hold the audio compression | handle: [ invalid handle ], compression: [ pointer ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetAudioPort() Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsGetAudioCompression() by looping through acquired port handles but with a null pointer for audio compression | handle: [ loop through valid handles ], compression: [ NULL ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsAudioPortTerm() Terminate audio ports | | dsERR_NONE | Termination must be successful |
 * |07|Call dsGetAudioCompression() - Attempt to get audio compression again after terminating audio ports | handle: [ valid handle from step 04 ] , compression: [ pointer ] | dsERR_NOT_INITIALIZED | Get audio compression must fail as module is not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetAudioCompression (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetAudioCompression() sets the audio compression level correctly during positive scenarios
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
 * |01|Call dsAudioPortInit() Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsSetAudioCompression() by looping through the acquired port handles and set the minimum audio compression level for each port | handle: [ valid handle ], compression: [ 0 ] | dsERR_NONE | Audio compression must be set correctly |
 * |04|Call dsSetAudioCompression() by looping through the acquired port handles and set the maximum audio compression level for each port | handle: [ valid handle ], compression: [ 10 ] | dsERR_NONE | Audio compression must be set correctly |
 * |05|Call dsSetAudioCompression() by looping through the acquired port handles and set the mid value audio compression level for each port | handle: [ valid handle ], compression: [ 5 ] | dsERR_NONE | Audio compression must be set correctly |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsSetAudioCompression (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetAudioCompression() returns the correct error codes during negative scenarios
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
 * |01|Call dsSetAudioCompression() using an invalid handle but with a valid compression value | handle: [ invalid value ], compression: [ valid dsAudioCompression_t value ] | dsERR_INVALID_PARAM | Set Audio Compression must return invalid parameter as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |04|Call dsSetAudioCompression() by looping through the acquired port handles but with out of range compression value(-10) | handle: [ valid handle ], compression: [ -10 ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |05|Call dsSetAudioCompression() by looping through the acquired port handles but with out of range compression value(20) | handle: [ valid handle ], compression: [ 20 ] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE | Termination must be successful |
 * |07|Call dsSetAudioCompression() again after terminating audio ports | handle: [ valid handle ], compression: [ valid dsAudioCompression_t value ] | dsERR_NOT_INITIALIZED | Set Audio Compression must return invalid parameter as module is not initialized |
 * 
 */
void test_l1_dsAudio_negative_dsSetAudioCompression (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetDialogEnhancement() returns correct Dialog enhancement levels during positive scenarios
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
 * |01|Call dsAudioPortInit()- Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetDialogEnhancement() by looping through the acquired port handles to get the dialog enhancement levels for each port | handle: [ valid handle ], level: [ pointer to hold dialog enhancement level ] | dsERR_NONE and value of `level` in the range [0,16] | Dialog Enhancement level should be retrieved correctly |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE | Termination must be successful |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_positive_dsGetDialogEnhancement (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetDialogEnhancement() returns correct error codes during negative scenarios
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
 * |01|Call dsGetDialogEnhancement() without initializing audio ports | handle=[invalid handle], level=[valid pointer] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized|
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetDialogEnhancement() using an invalid handle but with valid pointer| handle=[invalid handle], level=[valid pointer] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be r     eturned for all supported audio ports |
 * |04|Call dsGetDialogEnhancement() by looping through acquired valid handle but with invalid pointer| handle=[valid handle], level=[NULL] | dsERR_INVALID_PARAM | Invalid parameter error must be returned|
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsGetDialogEnhancement again after terminating audio ports | handle=[valid handle], level=[valid pointer] | dsERR_NOT_INITIALIZED | call must fail as module is not initialized|
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetDialogEnhancement (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetDialogEnhancement retrieves the Dialog Enhancement level correctly during positive scenarios
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
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsSetDialogEnhancement()  by looping through the acquired handle and valid (i.e 0 to 16) | handle=[valid handle], level=[valid value] | dsERR_NONE and value of `level` in the range [0,16] | Dialog Enhancement level should be retrieved correctly |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsSetDialogEnhancement (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetDialogEnhancement() returns correct error codes during negative scenarios
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
 * |01|Call dsSetDialogEnhancement() without initializing audio ports | handle=[invalid handle],level=[valid value] |dsERR_NOT_INITIALIZED |call must fail as module not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetDialogEnhancement() using an invalid handle but with valid value(i.e 0 to 16) | handle=[invalid handle], level=[valid value]| dsERR_INVALID_PARAM |Invalid parameter must return|
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsSetDialogEnhancement() by looping through acquired valid handle but with invalid value(i.e <0 to >16) | handle=[valid handle], level=[invalid value]| dsERR_INVALID_PARAM |Invalid parameter must return|
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsSetDialogEnhancement() again after terminating audio ports | handle=[valid handle], level=[valid value] | dsERR_NOT_INITIALIZED |call must fail as module not initialized|
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsSetDialogEnhancement (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetDolbyVolumeMode() retrieves the Dolby Volume Mode status correctly during positive scenarios.
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
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetDolbyVolumeMode() by looping through the acquired port handles and valid pointer to get the Dolby Volume mode of each port | handle: [valid handle], mode: [valid pointer] | dsERR_NONE | Dolby Volume Mode  should be retrieved correctly |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Termination must be successful |
 *
 */
void test_l1_dsAudio_positive_dsGetDolbyVolumeMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetDolbyVolumeMode() returns correct error codes during negative scenarios.
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
void test_l1_dsAudio_negative_dsGetDolbyVolumeMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetDolbyVolumeMode() sets the Dolby Volume Mode status correctly during positive scenarios.
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
 * |01|Call dsAudioPortInit() Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |04|By looping through the acquired handles ,get the handles for the  audio ports which supports DolbyVolume Mode.
 * |03|Call dsSetDolbyVolumeMode() by looping through the acquired supported port handles and valid modes (i.e TRUE or FALSE) | handle: [valid handles], modes: [valid modes]) for each port] | dsERR_NONE | dolby volume mode  must be set correctly |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Termination must be successful |
 *
 */
void test_l1_dsAudio_positive_dsSetDolbyVolumeMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetDolbyVolumeMode() returns correct error codes during negative scenarios.
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
 * |01|Call dsSetDolbyVolumeMode() - Attempt to set the Dolby Volume Mode without initializing audio ports | handle=[any value], mode=[0/1] (OFF/ON) | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() -Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetDolbyVolumeMode() -using an invalid handle with valid mode(i.e TRUE or FALSE)| handle = [invalid hanlde], mode = [valid mode] | dsERR_INVALID_PARAM | Should Pass |
   |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |07|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |08|Call dsSetDolbyVolumeMode() again after terminating audio ports attempt to set Dolby Volume Mode  | handle = [valid handle] , mode = [valid mode](True/FALSE) | dsERR_NOT_INITIALIZED | Should Pass |
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsSetDolbyVolumeMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetIntelligentEqualizerMode() retrieves the Intelligent Equalizer Mode correctly during positive scenarios.
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
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetIntelligentEqualizerMode by looping through the acquired port handles to get the IntelligentEqualizer Mode of each port | handle = [valid handles], mode = [valid pointer]| dsERR_NONE and a valid mode will be 0 to 6 | Ensure that the returned mode value corresponds to the settings in the system |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Termination must be successful |
 *
 */
void test_l1_dsAudio_positive_dsGetIntelligentEqualizerMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetIntelligentEqualizerMode() returns correct error codes during negative scenarios.
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
void test_l1_dsAudio_negative_dsGetIntelligentEqualizerMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetIntelligentEqualizerMode() sets the Intelligent Equalizer Mode correctly during positive scenarios.
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
 * |01|Call dsAudioPortInit() Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|call dsSetIntelligentEqualizerMode() by looping through the acquired port handles and set a valid  IntelligentEqualizer Mode (i.e 0 to 6) for each audio port | handle = [loop through valid handle] mode = [vaild mode] for each port| dsERR_NONE | IntelligentEqualizer Mode must be set correctly |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Termination must be successful |
 *
 */
void test_l1_dsAudio_positive_dsSetIntelligentEqualizerMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetIntelligentEqualizerMode() returns correct error codes during negative scenarios.
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
void test_l1_dsAudio_negative_dsSetIntelligentEqualizerMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetVolumeLeveller() retrieves the Volume Leveller settings correctly during positive scenarios.
 *
 * **Test Group ID:** Basic: 03@n
 * **Test Case ID:** 036@n
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
void test_l1_dsAudio_positive_dsGetVolumeLeveller (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetVolumeLeveller() returns correct error codes during negative scenarios.
 *
 * **Test Group ID:** Basic: 04@n
 * **Test Case ID:** 039@n
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
void test_l1_dsAudio_negative_dsGetVolumeLeveller (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetVolumeLeveller() sets the Volume Leveller settings correctly during positive scenarios.
 *
 * **Test Group ID:** Basic: 04@n
 * **Test Case ID:** 038@n
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
void test_l1_dsAudio_positive_dsSetVolumeLeveller (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetVolumeLeveller() returns correct error codes during negative scenarios.
 *
 * **Test Group ID:** Basic: 04@n
 * **Test Case ID:** 039@n
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
 * |05|Call dsSetVolumeLeveller() by looping through acquired port handles but with a invalid Volume Leveller settings (i.e invalid mode < 0 or > 2 invalid level < 0 or >12 | handle = [valid handle from step 04], volLeveller = [invalid mode and level] | dsERR_INVALID_PARAM | Invalid paramerter must be returned |
 * |06|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Termination must be successful |
 * |07|Call dsSetVolumeLeveller() again after terminating audio ports attempt to set the Volume Leveller settings | handle= [valid handle from step 04 ] , volLeveller = [valid mode and level] | dsERR_NOT_INITIALIZED | set Volume Leveller must fail as module is not initialized |
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsSetVolumeLeveller (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetBassEnhancer() retrieves the Bass Enhancer settings correctly during positive scenarios.
 *
 * **Test Group ID:** Basic: 05@n
 * **Test Case ID:** 040@n
 *
 * **Dependencies:** None@n
 * **User Interaction:** None
 *
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|dsGetBassEnhancer() by looping through the acquired port handles to get the Bass Enhancer of each port| handle = [loop through valid handles], boost = [valid pointer to retrieve value] | dsERR_NONE and valid values ranging from 0 to 100 | Ensure that the Bass Enhancer value is retrieved correctly |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Termination must be successful |
 *
 */
void test_l1_dsAudio_positive_dsGetBassEnhancer (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetBassEnhancer() returns correct error codes during negative scenarios.
 *
 * **Test Group ID:** Basic: 05@n
 * **Test Case ID:** 041@n
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
void test_l1_dsAudio_negative_dsGetBassEnhancer (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetBassEnhancer() sets the Bass Enhancer settings correctly during positive scenarios.
 *
 * **Test Group ID:** Basic: 06@n
 * **Test Case ID:** 045@n
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
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Termination must be successful |
 *
 */
void test_l1_dsAudio_positive_dsSetBassEnhancer (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetBassEnhancer() returns correct error codes during negative scenarios.
 *
 * **Test Group ID:** Basic: 06@n
 * **Test Case ID:** 046@n
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
void test_l1_dsAudio_negative_dsSetBassEnhancer (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsIsSurroundDecoderEnabled() retrieves the Surround Decoder status correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 07@n
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
 * |03|Call dsIsSurroundDecoderEnabled() by looping through the acquired port handles and vaild pointer | handle = [valid handle] , enabled = [valid pointer] | dsERR_NONE | Ensure that the Surround Decoder must return  the enabled or disaled for each port |
 * |07|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsIsSurroundDecoderEnabled (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsIsSurroundDecoderEnabled() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 07@n
 * **Test Case ID:** 048@n
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
void test_l1_dsAudio_negative_dsIsSurroundDecoderEnabled (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsEnableSurroundDecoder() sets the Surround Decoder status correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 08@n
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
 * |03|Call dsEnableSurroundDecoder() by looping through the acquired port handles and vaild value(i.e TRUE / FALSE) | handle = [valid handle] , enabled = [valid value] | dsERR_NONE | Ensure that the Surround Decoder enabled or disabled |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsEnableSurroundDecoder (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsEnableSurroundDecoder() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 08@n
 * **Test Case ID:** 058@n
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
void test_l1_dsAudio_negative_dsEnableSurroundDecoder (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetDRCMode() retrieves the DRC Mode correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 09@n
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
 * |03|Call dsGetDRCMode() by looping through the acquired port handles and valid pointer to get the DRC mode of each port | handle: [ valid handles ] , mode: [valid pointer] | dsERR_NONE if port supports or dsERR_INVALID_PARAM if port don't supports  | A valid DRC mode must be returned |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetDRCMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetDRCMode() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 09@n
 * **Test Case ID:** 060@n
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
void test_l1_dsAudio_negative_dsGetDRCMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetDRCMode() sets the DRC Mode correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 10@n
 * **Test Case ID:** 061@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsSetDRCMode() by looping through the acquired port handled and valid value (i.e 0 or 1) | handle = [valid handle] , mode = [valid value] | dsERR_NONE if port supports or dsERR_INVALID_PARAM if port don't supports | The DRC Mode should be successfully set |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsSetDRCMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetDRCMode() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 10@n
 * **Test Case ID:** 062@n
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
void test_l1_dsAudio_negative_dsSetDRCMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetSurroundVirtualizer() retrieves the Surround Virtualizer level correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 10@n
 * **Test Case ID:** 071@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetSurroundVirtualizer() Loop through the acquired port handles with valid pointer | handle = [valid handle] , virtualizer = [valid pointer] | dsERR_NONE | dsGetSurroundVirtualizer must return valid values  |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetSurroundVirtualizer (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetSurroundVirtualizer() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 10@n
 * **Test Case ID:** 072@n
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
void test_l1_dsAudio_negative_dsGetSurroundVirtualizer (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetSurroundVirtualizer() sets the Surround Virtualizer level correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 10@n
 * **Test Case ID:** 073@n
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
void test_l1_dsAudio_positive_dsSetSurroundVirtualizer (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetSurroundVirtualizer() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 10@n
 * **Test Case ID:** 074@n
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
 * |05|Call dsSetSurroundVirtualizer() by looping through valid handles and invalid virtualizer values (i.e mode (< 0 or > 2) and boost (< 0 or > 96))  | handle = [valid handle] , virtualizer = [invalid values] | dsERR_INVALID_PARAM | Invalid parameter should be returned |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsSetSurroundVirtualizer() again after terminating audio ports | handle = [valid handle from step 04] , virtualizer = [valid values] | dsERR_NOT_INITIALIZED | dsSetSurroundVirtualizer call must fail as module not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsSetSurroundVirtualizer (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetMISteering() retrieves the MI Steering status correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 10@n
 * **Test Case ID:** 075@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetMISteering() by looping through the acquired port handles to get the Media Intelligent Steering of each port | handle: [ loop through valid handles ] , enabled: [pointer to hold the MI Steering enabled/disabled value] | dsERR_NONE | MI Steering enabled/disabled status must be returned |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetMISteering (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetMISteering() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 10@n
 * **Test Case ID:** 076@n
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
void test_l1_dsAudio_negative_dsGetMISteering (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetMISteering() sets the MI Steering status correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 10@n
 * **Test Case ID:** 077@n
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
void test_l1_dsAudio_positive_dsSetMISteering (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetMISteering() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 10@n
 * **Test Case ID:** 078@n
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
void test_l1_dsAudio_negative_dsSetMISteering (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetGraphicEqualizerMode() retrieves the Graphic Equalizer Mode correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 11@n
 * **Test Case ID:** 079@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetGraphicEqualizerMode() by looping through the acquired port handles to get the Graphic Equalizer Mode of each port | handle: [valid handles ] , mode: [valid pointer] | dsERR_NONE | A valid Graphic Equalizer Mode must be returned |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetGraphicEqualizerMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetGraphicEqualizerMode() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 11@n
 * **Test Case ID:** 080@n
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
 * |o5|Call dsGetGraphicEqualizerMode() using an valid handle and invalid pointer | handle = [valid handle] , mode = [invalid pointer] | dsERR_INVALID_PARAM |Invalid parameter error must be returned |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsGetGraphicEqualizerMode() again after terminating audio ports | handle = [valid handle from step 04] , mode = [valid pointer] | dsERR_NOT_INITIALIZED | dsGetGraphicEqualizerMode call must fail as module is not initialized  |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetGraphicEqualizerMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetGraphicEqualizerMode() sets the Graphic Equalizer Mode correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 12@n
 * **Test Case ID:** 081@n
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
void test_l1_dsAudio_positive_dsSetGraphicEqualizerMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetGraphicEqualizerMode() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 12@n
 * **Test Case ID:** 082@n
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
void test_l1_dsAudio_negative_dsSetGraphicEqualizerMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetMS12AudioProfileList() retrieves the list of supported MS12 audio profiles correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 13@n
 * **Test Case ID:** 083@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetMS12AudioProfileList() by looping through the acquired port handles to get the list of supported MS12 audio profiles of each port | handle: [valid handles] , profiles: [valid pointer] | dsERR_NONE | List of supported MS12 audio profiles must be returned |
 * |04|Verify that the profiles list is valid and is not empty | | Non-empty list of profiles | |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetMS12AudioProfileList (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetMS12AudioProfileList() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 13@n
 * **Test Case ID:** 084@n
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
 * |04|Call dsGetMS12AudioProfileList() by looping through the obtained handles , with a null pointer for profiles | handle =[valid handle], profiles = [NULL] | dsERR_INVALID_PARAM |  Invalid parameter error must be returned |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsGetMS12AudioProfileList() again after terminating audio ports | handle=[valid handle], profiles=[valid pointer] | dsERR_NOT_INITIALIZED | dsGetMS12AudioProfileList call must fail as module not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetMS12AudioProfileList (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetMS12AudioProfile() retrieves the current audio profile configured correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 14@n
 * **Test Case ID:** 085@n
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
void test_l1_dsAudio_positive_dsGetMS12AudioProfile (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetMS12AudioProfile() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 14@n
 * **Test Case ID:** 086@n
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
void test_l1_dsAudio_negative_dsGetMS12AudioProfile (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetSupportedARCTypes() retrieves the supported ARC types of the connected ARC/eARC device correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 15@n
 * **Test Case ID:** 087@n
 * 
 * **Dependencies:** ARC/eARC device should be connected and working properly.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() to request an available ARC/eARC port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Retrieve the supported ARC types of the connected ARC/eARC device using dsGetSupportedARCTypes() | `handle`=acquired from previous step | dsERR_NONE and valid types | The types should be populated |
 * |04|Verify that the types value is valid (based on expected ARC types) | | Valid ARC types | |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetSupportedARCTypes (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetSupportedARCTypes() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 15@n
 * **Test Case ID:** 088@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetSupportedARCTypes() without initializing audio ports | `handle`=any value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetSupportedARCTypes() using an invalid handle | `handle`=invalid value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsGetSupportedARCTypes() with a null pointer for types | `handle`=valid handle, `types`=NULL | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsGetSupportedARCTypes() again after terminating audio ports | `handle`=valid handle | dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetSupportedARCTypes (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsAudioSetSAD() sets the Short Audio Descriptor correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 20@n
 * **Test Case ID:** 099@n
 * 
 * **Dependencies:** ARC device should be connected and working properly. Ensure CEC is enabled.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() to request an available ARC/eARC port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Retrieve the SADs from CEC for the connected ARC device and populate the sad_list | | Valid sad_list | |
 * |04|Set the SAD using dsAudioSetSAD() | `handle`=acquired from previous step, `sad_list`=populated SADs | dsERR_NONE | The SAD should be set correctly |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsAudioSetSAD (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsAudioSetSAD() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 20@n
 * **Test Case ID:** 100@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioSetSAD() without initializing audio ports | `handle`=any value, `sad_list`=valid | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsAudioSetSAD() using an invalid handle | `handle`=invalid value, `sad_list`=valid | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioSetSAD() with invalid SAD values | `handle`=valid handle, `sad_list`=invalid | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsAudioSetSAD() again after terminating audio ports | `handle`=valid handle, `sad_list`=valid | dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsAudioSetSAD (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsAudioEnableARC() enables or disables ARC/EARC correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 21@n
 * **Test Case ID:** 101@n
 * 
 * **Dependencies:** ARC/eARC device should be connected and working properly. Ensure CEC is enabled.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() to request an available ARC/eARC port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Enable ARC using dsAudioEnableARC() | `handle`=acquired from previous step, `arcStatus`=enable | dsERR_NONE | ARC/eARC should be enabled |
 * |04|Disable ARC using dsAudioEnableARC() | `handle`=acquired from previous step, `arcStatus`=disable | dsERR_NONE | ARC/eARC should be disabled |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsAudioEnableARC (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsAudioEnableARC() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 21@n
 * **Test Case ID:** 102@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioEnableARC() without initializing audio ports | `handle`=any value, `arcStatus`=enable | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsAudioEnableARC() using an invalid handle | `handle`=invalid value, `arcStatus`=enable | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioEnableARC() with invalid arcStatus values | `handle`=valid handle, `arcStatus`=invalid value | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsAudioEnableARC() again after terminating audio ports | `handle`=valid handle, `arcStatus`=enable | dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsAudioEnableARC (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetStereoMode() retrieves the correct stereo mode during positive scenarios.
 * 
 * **Test Group ID:** Basic: 22@n
 * **Test Case ID:** 201@n
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
void test_l1_dsAudio_positive_dsGetStereoMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetStereoMode() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 22@n
 * **Test Case ID:** 202@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsGetStereoMode() without initializing audio ports | handle=[any value] ,stereoMode=[valid pointer]| dsERR_NOT_INITIALIZED | dsGetStereoMode call must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetStereoMode() using an invalid handle and valid pointer | handle=[invalid handle] , stereoMode=[valid pointer] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsGetStereoMode() by looping through the obtained handles and  a NULL pointer for stereoMode in dsGetStereoMode() | handle=[valid handle], stereoMode=[NULL] | dsERR_INVALID_PARAM | Invalid parameter error must be returned |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsGetStereoMode() again after terminating audio ports | handle=[valid handle], stereoMode=[valid pointer] | dsERR_NOT_INITIALIZED | dsGetStereoMode call must fail as module is not initialized  |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetStereoMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetStereoMode() sets the stereo mode correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 23@n
 * **Test Case ID:** 203@n
 * 
 * **Dependencies:** Audio device should be connected and working properly.@n
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
void test_l1_dsAudio_positive_dsSetStereoMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetStereoMode() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 23@n
 * **Test Case ID:** 204@n
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
void test_l1_dsAudio_negative_dsSetStereoMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetStereoAuto() retrieves the auto mode correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 25@n
 * **Test Case ID:** 205@n
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
void test_l1_dsAudio_positive_dsGetStereoAuto (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetStereoAuto() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 25@n
 * **Test Case ID:** 206@n
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
void test_l1_dsAudio_negative_dsGetStereoAuto (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetStereoAuto() sets the auto mode correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 26@n
 * **Test Case ID:** 210@n
 * 
 * **Dependencies:** Audio device should be connected and working properly.@n
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
void test_l1_dsAudio_positive_dsSetStereoAuto (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetStereoAuto() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 26@n
 * **Test Case ID:** 211@n
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
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsSetStereoAuto() again after terminating audio ports | handle=[valid handle], autoMode=[valid value]| dsERR_NOT_INITIALIZED |call must fail as module is not initialized|
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsSetStereoAuto (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAudioGain() retrieves the audio gain correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 27@n
 * **Test Case ID:** 212@n
 * 
 * **Dependencies:** Audio device should be connected and working properly.@n
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
void test_l1_dsAudio_positive_dsGetAudioGain (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAudioGain() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 27@n
 * **Test Case ID:** 213@n
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
 * |04|Call dsGetAudioGain() by looping through the acquired valid handle with a NULL gain pointer |handle=[valid handle], gain=[NULL] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsGetAudioGain() again after terminating audio ports |handle=[valid handle], gain=[pointer] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 * @note Testing the actual range values of gain might require an additional procedure, once the spec for the range is defined by Amit/Deekshit.
 */
void test_l1_dsAudio_negative_dsGetAudioGain (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetAudioGain() sets the audio gain correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 28@n
 * **Test Case ID:** 214@n
 * 
 * **Dependencies:** Audio device should be connected and working properly.@n
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
void test_l1_dsAudio_positive_dsSetAudioGain (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetAudioGain() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 28@n
 * **Test Case ID:** 215@n
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
 * |04|Call dsSetAudioGain() by looping through acquired handles with an out of range gain value(not in range 2080 to 480) | handle=[valid handle], gain=[invalid value] | dsERR_INVALID_PARAM| Invalid parameter must return|
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsSetAudioGain() again after terminating audio ports | handle=[valid handle], gain=[valid value] | dsERR_NOT_INITIALIZED |call must fail as module not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsSetAudioGain (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAudioDB() retrieves the audio dB level correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 29@n
 * **Test Case ID:** 216@n
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
void test_l1_dsAudio_positive_dsGetAudioDB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAudioDB() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 29@n
 * **Test Case ID:** 217@n
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
void test_l1_dsAudio_negative_dsGetAudioDB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetAudioDB() sets the audio dB level correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 30@n
 * **Test Case ID:** 218@n
 * 
 * **Dependencies:** Audio device should be connected and working properly.@n
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
void test_l1_dsAudio_positive_dsSetAudioDB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetAudioDB() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 30@n
 * **Test Case ID:** 219@n
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
void test_l1_dsAudio_negative_dsSetAudioDB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAudioLevel() retrieves the audio volume level correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 31@n
 * **Test Case ID:** 220@n
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
void test_l1_dsAudio_positive_dsGetAudioLevel (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAudioLevel() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 31@n
 * **Test Case ID:** 221@n
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
void test_l1_dsAudio_negative_dsGetAudioLevel (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetAudioLevel() sets the audio volume level correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 32@n
 * **Test Case ID:** 222@n
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
void test_l1_dsAudio_positive_dsSetAudioLevel (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetAudioLevel() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 32@n
 * **Test Case ID:** 223@n
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
void test_l1_dsAudio_negative_dsSetAudioLevel (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAudioMaxDB() retrieves the maximum audio dB level correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 33@n
 * **Test Case ID:** 224@n
 * 
 * **Dependencies:** Audio device should be connected and working properly.@n
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
void test_l1_dsAudio_positive_dsGetAudioMaxDB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAudioMaxDB() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 33@n
 * **Test Case ID:** 225@n
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
 * |05|Call dsGetAudioPort() by looping through the acquired valid handle with a NULL gain pointer |handle=[valid handle], maxDb=[NULL] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsGetAudioMaxDB() again after terminating audio ports |handle=[valid handle], maxDb=[pointer] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized|
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetAudioMaxDB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAudioMinDB() retrieves the minimum audio dB level correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 34@n
 * **Test Case ID:** 226@n
 * 
 * **Dependencies:** Audio device should be connected and working properly.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetAudioMinDB() by looping through the acquired port handles to get the minimum audio dB of each port in array| handle: [ loop through valid handles ] , minDb: [pointer to hold the minimum audio dB value] | dsERR_NONE | A valid minimum audio dB value(minimum value can be -1450 dB) must be returned |
 * |04|Call dsGetAudioMinDB() by looping through the acquired port handles to get the minimum audio dB of each port in new array| handle: [ loop through valid handles ] , minDb: [pointer to hold the minimum audio dB value] | dsERR_NONE | A valid minimum audio dB value(minimum value can be -1450 dB) must be returned |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetAudioMinDB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAudioMinDB() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 34@n
 * **Test Case ID:** 227@n
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
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |05|Call dsGetAudioMinDB() again after terminating audio ports |handle=[valid handle], minDb=[pointer] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized|
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetAudioMinDB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAudioOptimalLevel() retrieves the optimal audio level correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 35@n
 * **Test Case ID:** 228@n
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
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetAudioOptimalLevel (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAudioOptimalLevel() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 35@n
 * **Test Case ID:** 229@n
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
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsGetAudioOptimalLevel() again after terminating audio ports |handle=[valid handle], optimalLevel=[pointer] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized|
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetAudioOptimalLevel (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAudioDelay() retrieves the audio delay correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 36@n
 * **Test Case ID:** 230@n
 * 
 * **Dependencies:** Audio device should be connected and working properly.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetAudioDelay() by looping through the acquired port handles to get the audio audio delay (in ms) of each port in array | handle: [ loop through valid handles ] , audioDelayMs: [ pointer to hold the audio delay ] | dsERR_NONE | A valid audio delay value(0 to 200 ms) must be returned |
 * |04|Call dsGetAudioDelay() by looping through the acquired port handles to get the audio audio delay (in ms) of each port in new array | handle: [ loop through valid handles ] , audioDelayMs: [ pointer to hold the audio delay ] | dsERR_NONE | A valid audio delay value(0 to 200 ms) must be returned |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetAudioDelay (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAudioDelay() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 36@n
 * **Test Case ID:** 231@n
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
void test_l1_dsAudio_negative_dsGetAudioDelay (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetAudioDelay() sets the audio delay correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 37@n
 * **Test Case ID:** 232@n
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
void test_l1_dsAudio_positive_dsSetAudioDelay (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetAudioDelay() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 37@n
 * **Test Case ID:** 233@n
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
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |05|Call dsSetAudioDelay() again after terminating audio ports | handle=[valid handle], audioDelayMs=[valid value] | dsERR_NOT_INITIALIZED |call must fail as module not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsSetAudioDelay (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAudioDelayOffset() retrieves the audio delay offset correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 38@n
 * **Test Case ID:** 234@n
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
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetAudioDelayOffset (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAudioDelayOffset() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 38@n
 * **Test Case ID:** 235@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsGetAudioDelayOffset() without initializing audio ports | handle=[invalid handle], audioDelayOffsetMs=[valid pointer] | dsERR_NOT_INITIALIZED |call must fail as module not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsGetAudioDelayOffset() using an invalid handle with valid gain value | handle=[invalid handle], audioDelayOffsetMs=[valid pointer] |dsERR_INVALID_PARAM |Invalid parameter must return |
 * |04|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |05|Call dsGetAudioDelayOffset() by looping through the acquired valid handle with a NULL gain pointer |handle=[valid handle], audioDelayOffsetMs=[NULL] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |05|Call dsGetAudioDelayOffset() again after terminating audio ports |handle=[valid handle], audioDelayOffsetMs=[pointer] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized|
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetAudioDelayOffset (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetAudioDelayOffset() sets the audio delay offset correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 39@n
 * **Test Case ID:** 236@n
 * 
 * **Dependencies:** Audio device should be connected and working properly.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsSetAudioDelayOffset() by looping through acquired port handles and valid audio delay offset value(i.e milliseconds) | handle=[valid handle], audioDelayOffsetMs=[valid value] | dsERR_NONE | audio delay offset should be successfully set |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsSetAudioDelayOffset (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetAudioDelayOffset() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 39@n
 * **Test Case ID:** 237@n
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
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |05|Call dsSetAudioDelayOffset() again after terminating audio ports | handle=[valid handle], audioDelayOffsetMs=[valid value] | dsERR_NOT_INITIALIZED |call must fail as module not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsSetAudioDelayOffset (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetAudioAtmosOutputMode() sets the Audio ATMOS output mode correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 40@n
 * **Test Case ID:** 238@n
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
void test_l1_dsAudio_positive_dsSetAudioAtmosOutputMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetAudioAtmosOutputMode() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 40@n
 * **Test Case ID:** 239@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsSetAudioAtmosOutputMode() - Attempt to set the audio ATMOS output mode without initializing audio ports | handle = [invalid handle], enable = [TRUE] | dsERR_NOT_INITIALIZED | Set ATMOS Output mode must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetAudioAtmosOutputMode() using an invalid handle | handle = [invalid handle], enable = [TRUE] | dsERR_INVALID_PARAM | Invalid parameter error must be returned  |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |05|Call dsSetAudioAtmosOutputMode() - Again attempt to set the audio ATMOS output mode without initializing audio ports | handle = [valid handle], enable = [TRUE] | dsERR_NOT_INITIALIZED | Set ATMOS Output mode must fail as module is not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED, dsERR_GENERAL and  might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsSetAudioAtmosOutputMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetSinkDeviceAtmosCapability() retrieves the ATMOS capability correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 41@n
 * **Test Case ID:** 240@n
 * 
 * **Dependencies:**@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetSinkDeviceAtmosCapability() by looping through the acquired port handles to get the  ATMOS capability of sink device connected to each port | handle: [ loop through valid handles ] , capability: [pointer to hold the ATMOS capability] | dsERR_NONE | A valid ATMOS capability of sink device must be returned |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetSinkDeviceAtmosCapability (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetSinkDeviceAtmosCapability() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 41@n
 * **Test Case ID:** 241@n
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
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsGetSinkDeviceAtmosCapability() - Again attempt to get the ATMOS capability of sink device after terminating audio ports | handle = [valid handle], capability = [valid pointer to hold the ATMOS capability] | dsERR_NOT_INITIALIZED | Get Atmos capability of sink device must fail as module is not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetSinkDeviceAtmosCapability (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsIsAudioLoopThru() retrieves the loop-through status correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 42@n
 * **Test Case ID:** 242@n
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
void test_l1_dsAudio_positive_dsIsAudioLoopThru (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsIsAudioLoopThru() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 42@n
 * **Test Case ID:** 243@n
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
void test_l1_dsAudio_negative_dsIsAudioLoopThru (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsIsAudioMute() retrieves the mute status correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 43@n
 * **Test Case ID:** 244@n
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
void test_l1_dsAudio_positive_dsIsAudioMute (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsIsAudioMute() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 43@n
 * **Test Case ID:** 245@n
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
void test_l1_dsAudio_negative_dsIsAudioMute (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsIsAudioPortEnabled() retrieves the enable status correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 44@n
 * **Test Case ID:** 246@n
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
void test_l1_dsAudio_positive_dsIsAudioPortEnabled (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsIsAudioPortEnabled() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 44@n
 * **Test Case ID:** 247@n
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
void test_l1_dsAudio_negative_dsIsAudioPortEnabled (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsEnableAudioPort() sets the audio port state correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 45@n
 * **Test Case ID:** 248@n
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
 * |04|Call dsIsAudioPortEnabled() by looping through the acquired port handles and check if all the audio ports are enabled | handle: [ loop through valid handles ], enabled : [pointer to hold audio port enabled status] | dsERR_NONE | Supported audio ports must be enabled |
 * |05|Call dsEnableAudioPort() by looping through the acquired port handles to disable audio port | handle: [ loop through valid handles ] , enable: [FALSE] | dsERR_NONE | Supported audio ports must be disabled |
 * |06|Call dsIsAudioPortEnabled() by looping through the acquired port handles and check if all the audio ports are disabled | handle: [ loop through valid handles ], enabled : [pointer to hold audio port enabled status] | dsERR_NONE | Supported audio ports must be disabled |
 * |07|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsEnableAudioPort (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsEnableAudioPort() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 45@n
 * **Test Case ID:** 249@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsEnableAudioPort() - Attempt to enable/disable audio ports without initializing audio ports | handle = [invalid handle] , enabled = [TRUE] | dsERR_NOT_INITIALIZED | Call to Enable / Disable the Audio Ports must fail as module is not initialized |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsEnableAudioPort() using an invalid handle but with a valid enable | handle = [invalid handle], enabled = [TRUE] | dsERR_INVALID_PARAM | Invalid Parameter error must be returned |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |05|Call dsEnableAudioPort() - Attempt to enable/disable audio ports again after terminating audio ports | handle = [invalid handle] , enabled = [TRUE] | dsERR_NOT_INITIALIZED | Call to Enable / Disable the Audio Ports must fail as module is not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsEnableAudioPort (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsEnableMS12Config() sets the MS12 features correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 46@n
 * **Test Case ID:** 250@n
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
void test_l1_dsAudio_positive_dsEnableMS12Config (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsEnableMS12Config() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 46@n
 * **Test Case ID:** 251@n
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
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsEnableMS12Config() - Attempt to enable MS12 Configs again after terminating audio ports | handle = [valid handle from previous step], feature = [loop through dsMS12FEATURE_t], enable = [TRUE] | dsERR_NOT_INITIALIZED | Enable MS12 Configs must fail as module is not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsEnableMS12Config (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsEnableLEConfig() sets the Loudness Equivalence (LE) feature correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 47@n
 * **Test Case ID:** 252@n
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
 * |04|Call dsGetLEConfig() by looping through the acquired port handles and verify if LE feature is enabled in all supported audio ports | handle = [loop through valid handles], enabled = [pointer to hold LE enabled status] | Loudness Equivalence must be enabled for all supported audio ports |
 * |05|Call dsEnableLEConfig() by looping through the acquired port handles to disable the LE feature | handle = [loop through valid handles], enable = [FALSE] | dsERR_NONE | Loudness Equivalence must be disabled for all supported audio ports |
 * |06|Call dsGetLEConfig() by looping through the acquired port handles and verify if LE feature is disabled in all supported audio ports | handle = [loop through valid handles], enabled = [pointer to hold LE enabled status] | Loudness Equivalence must be disabled for all supported audio ports |
 * |07|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsEnableLEConfig (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsEnableLEConfig() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 47@n
 * **Test Case ID:** 253@n
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
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE | Termination must be successful |
 * |05|Call dsEnableLEConfig() - Attempt to enable LE again after terminating audio ports | handle = [valid handle from previous step], enable = [FALSE] | dsERR_NOT_INITIALIZED | Call to dsEnableLEConfig() must fail as module is not initialized |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsEnableLEConfig (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetLEConfig() retrieves the Loudness Equivalence (LE) feature status correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 48@n
 * **Test Case ID:** 254@n
 * 
 * **Dependencies:** Audio device should be connected and LE features are supported.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetLEConfig() by looping through the acquired port handles to get the Loudness Equivalence feature of each port | handle: [ loop through valid handles ] , enable: [ pointer to hold the status of LE feature(enabled/disabled) ] | dsERR_NONE | Loudness Equivalence enabled/disabled status must be returned |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetLEConfig (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetLEConfig() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 48@n
 * **Test Case ID:** 255@n
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
void test_l1_dsAudio_negative_dsGetLEConfig (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetMS12AudioProfile() sets the MS12 audio profile correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 49@n
 * **Test Case ID:** 256@n
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
void test_l1_dsAudio_positive_dsSetMS12AudioProfile (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetMS12AudioProfile() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 49@n
 * **Test Case ID:** 257@n
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
void test_l1_dsAudio_negative_dsSetMS12AudioProfile (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetAudioDucking() sets the audio ducking level correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 50@n
 * **Test Case ID:** 258@n
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
void test_l1_dsAudio_positive_dsSetAudioDucking (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetAudioDucking() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 50@n
 * **Test Case ID:** 259@n
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
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsSetAudioDucking() again after terminating audio ports | handle=[valid handle], action=[valid value], type=[valid value], level=[valid value] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized |
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions
 */
void test_l1_dsAudio_negative_dsSetAudioDucking (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsEnableLoopThru() sets loop-through mode correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 51@n
 * **Test Case ID:** 260@n
 * 
 * **Dependencies:** Audio device should be connected and loop-through features are supported.@n
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
void test_l1_dsAudio_positive_dsEnableLoopThru (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsEnableLoopThru() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 51@n
 * **Test Case ID:** 261@n
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
void test_l1_dsAudio_negative_dsEnableLoopThru (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetAudioMute() mutes or un-mutes an audio port correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 52@n
 * **Test Case ID:** 262@n
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
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsSetAudioMute (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetAudioMute() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 52@n
 * **Test Case ID:** 263@n
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
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |05|Call dsSetAudioMute() again after terminating audio ports | handle=[valid handle], mute=[valid value] | dsERR_NOT_INITIALIZED |call must fail as module not initialized |
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions 
 */
void test_l1_dsAudio_negative_dsSetAudioMute (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsIsAudioMSDecode() correctly checks for Dolby MS11 Multistream Decode support during positive scenarios.
 * 
 * **Test Group ID:** Basic: 53@n
 * **Test Case ID:** 264@n
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
void test_l1_dsAudio_positive_dsIsAudioMSDecode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsIsAudioMSDecode() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 53@n
 * **Test Case ID:** 265@n
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
void test_l1_dsAudio_negative_dsIsAudioMSDecode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsIsAudioMS12Decode() correctly checks for Dolby MS12 Multistream Decode support during positive scenarios.
 * 
 * **Test Group ID:** Basic: 54@n
 * **Test Case ID:** 266@n
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
void test_l1_dsAudio_positive_dsIsAudioMS12Decode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsIsAudioMS12Decode() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 54@n
 * **Test Case ID:** 267@n
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
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |05|Call dsIsAudioMS12Decode() again after terminating audio ports | handle=[valid handle], hasMS12Decode=[valid pointer] | dsERR_NOT_INITIALIZED | call must fail as module not initialized |
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions
 */
void test_l1_dsAudio_negative_dsIsAudioMS12Decode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsAudioOutIsConnected() correctly checks for audio output port connection during positive scenarios.
 * 
 * **Test Group ID:** Basic: 55@n
 * **Test Case ID:** 268@n
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
void test_l1_dsAudio_positive_dsAudioOutIsConnected (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsAudioOutIsConnected() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 55@n
 * **Test Case ID:** 269@n
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
void test_l1_dsAudio_negative_dsAudioOutIsConnected (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsAudioOutRegisterConnectCB() correctly registers for the audio output connect event during positive scenarios.
 * 
 * **Test Group ID:** Basic: 56@n
 * **Test Case ID:** 270@n
 * 
 * **Dependencies:** Callback function should be prepared to handle the audio output connect event.@n
 * **User Interaction:** Ensure that the test environment allows for simulating connection events, e.g., plugging/unplugging an audio device.
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Register the audio output connect callback using dsAudioOutRegisterConnectCB() | `CBFunc`=test callback function | dsERR_NONE | Should Pass |
 * |03|Simulate an audio output connect event, e.g., plugging in an audio device | | The test callback function should be triggered with the correct status | Ensure the callback behavior matches expected behavior |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsAudioOutRegisterConnectCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsAudioOutRegisterConnectCB() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 56@n
 * **Test Case ID:** 271@n
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
void test_l1_dsAudio_negative_dsAudioOutRegisterConnectCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsAudioFormatUpdateRegisterCB() correctly registers for the audio format update event during positive scenarios.
 * 
 * **Test Group ID:** Basic: 57@n
 * **Test Case ID:** 272@n
 * 
 * **Dependencies:** Callback function should be prepared to handle the audio format update event.@n
 * **User Interaction:** Ensure that the test environment allows for simulating format update events, e.g., switching audio formats.
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Register the audio format update callback using dsAudioFormatUpdateRegisterCB() | `cbFun`=test callback function | dsERR_NONE | Should Pass |
 * |03|Simulate an audio format update event, e.g., switching to a different audio format | | The test callback function should be triggered with the correct status | Ensure the callback behavior matches expected behavior |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsAudioFormatUpdateRegisterCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsAudioFormatUpdateRegisterCB() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 57@n
 * **Test Case ID:** 273@n
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
void test_l1_dsAudio_negative_dsAudioFormatUpdateRegisterCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAudioCapabilities() correctly fetches the supported audio capabilities during positive scenarios.
 * 
 * **Test Group ID:** Basic: 58@n
 * **Test Case ID:** 274@n
 * 
 * **Dependencies:** Audio device should be connected and should have known capabilities.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetAudioCapabilities() by looping through the acquired port handles to get the supported Audio capabilities of each port | handle: [ loop through valid handles ] , capabilities: [pointer to hold the Bitwise OR-ed value of supported Audio standards] | dsERR_NONE | Bitwise-ORed value of supported Audio standards(dsAudioCapabilities_t) must be returned |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetAudioCapabilities (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAudioCapabilities() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 58@n
 * **Test Case ID:** 275@n
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
void test_l1_dsAudio_negative_dsGetAudioCapabilities (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetMS12Capabilities() correctly fetches the supported MS12 capabilities during positive scenarios.
 * 
 * **Test Group ID:** Basic: 59@n
 * **Test Case ID:** 276@n
 * 
 * **Dependencies:** Audio device should be connected and should have known MS12 capabilities.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsGetMS12Capabilities() by looping through the acquired port handles to get the supported MS12 capabilities of each port | handle: [ loop through valid handles ] , capabilities: [pointer to hold the Bitwise OR-ed value of supported MS12 standards] | dsERR_NONE | Bitwise-OR-ed value of supported MS12 standards(dsMS12Capabilities_t) must be returned |
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetMS12Capabilities (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetMS12Capabilities() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 59@n
 * **Test Case ID:** 277@n
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
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |05|Call dsGetMS12Capabilities() again after terminating audio ports | handle=[valid handle] , capabilities=[valid pointer] | dsERR_NOT_INITIALIZED | call must fail as module is not initialized  |
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions 
 */
void test_l1_dsAudio_negative_dsGetMS12Capabilities (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsResetDialogEnhancement() correctly resets the dialog enhancement to platform-specific default value during positive scenarios.
 * 
 * **Test Group ID:** Basic: 60@n
 * **Test Case ID:** 278@n
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
void test_l1_dsAudio_positive_dsResetDialogEnhancement (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsResetDialogEnhancement() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 60@n
 * **Test Case ID:** 279@n
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
void test_l1_dsAudio_negative_dsResetDialogEnhancement (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsResetBassEnhancer() correctly resets the bass enhancer to platform-specific default value during positive scenarios.
 * 
 * **Test Group ID:** Basic: 61@n
 * **Test Case ID:** 280@n
 * 
 * **Dependencies:** Audio device should be connected and support bass enhancement functionalities.@n
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
void test_l1_dsAudio_positive_dsResetBassEnhancer (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsResetBassEnhancer() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 61@n
 * **Test Case ID:** 281@n
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
void test_l1_dsAudio_negative_dsResetBassEnhancer (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsResetSurroundVirtualizer() correctly resets the surround virtualizer to platform-specific default value during positive scenarios.
 * 
 * **Test Group ID:** Basic: 62@n
 * **Test Case ID:** 282@n
 * 
 * **Dependencies:** Audio device should be connected and support surround virtualizer functionalities.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsResetSurroundVirtualizer() by looping through the acquired port handles to reset surround virtualizer | handle=[valid handle] | dsERR_NONE | surround virtualizer should be resuccessfully reset |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsResetSurroundVirtualizer (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsResetSurroundVirtualizer() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 62@n
 * **Test Case ID:** 283@n
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
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |05|Call dsResetSurroundVirtualizer() again after terminating audio ports | handle=[valid handle] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized|
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions 
 */
void test_l1_dsAudio_negative_dsResetSurroundVirtualizer (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsResetVolumeLeveller() correctly resets the Dolby volume leveller to platform-specific default volume level during positive scenarios.
 * 
 * **Test Group ID:** Basic: 63@n
 * **Test Case ID:** 284@n
 * 
 * **Dependencies:** Audio device should be connected and support Dolby volume levelling functionalities.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsResetVolumeLeveller() by loopig through the acquired handles to reset Dolby volume leveller | handle=[valid handle] | dsERR_NONE |volume leveller should be successfully reset |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsResetVolumeLeveller (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsResetVolumeLeveller() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 63@n
 * **Test Case ID:** 285@n
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
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |05|Call dsResetVolumeLeveller() again after terminating audio ports | handle=[valid handle] | dsERR_NOT_INITIALIZED | call must fail as module is not initialized  |
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions 
 */
void test_l1_dsAudio_negative_dsResetVolumeLeveller (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetMS12AudioProfileSetttingsOverride() correctly overrides the specific MS12 audio setting of the specified profile during positive scenarios.
 * 
 * **Test Group ID:** Basic: 64@n
 * **Test Case ID:** 286@n
 * 
 * **Dependencies:** Audio device should be connected and support MS12 audio profiles.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Override MS12 audio profile setting using dsSetMS12AudioProfileSetttingsOverride() | `handle`=acquired from previous step, `profileState`=ADD, `profileName`=valid profile, `profileSettingsName`=valid setting name, `profileSettingValue`=valid setting value | dsERR_NONE | Should Pass |
 * |04|Verify the overridden MS12 audio profile setting | | Setting matches the overridden value | Manual verification or using a separate API if available |
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsSetMS12AudioProfileSetttingsOverride (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetMS12AudioProfileSetttingsOverride() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 64@n
 * **Test Case ID:** 287@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsSetMS12AudioProfileSetttingsOverride() without initializing audio ports | `handle`=any value, other params=valid | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |03|Call dsSetMS12AudioProfileSetttingsOverride() using invalid profileState | `handle`=valid, `profileState`=invalid value, other params=valid | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsSetMS12AudioProfileSetttingsOverride() using invalid profileName | `handle`=valid, `profileName`=invalid value, other params=valid | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsSetMS12AudioProfileSetttingsOverride() using invalid profileSettingsName | `handle`=valid, `profileSettingsName`=invalid value, other params=valid | dsERR_INVALID_PARAM | Should Pass |
 * |06|Call dsSetMS12AudioProfileSetttingsOverride() using invalid profileSettingValue | `handle`=valid, `profileSettingValue`=invalid value, other params=valid | dsERR_INVALID_PARAM | Should Pass |
 * |07|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |08|Call dsSetMS12AudioProfileSetttingsOverride() again after terminating audio ports | `handle`=valid handle from earlier step, other params=valid | dsERR_NOT_INITIALIZED | Should Pass |
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions 
 */
void test_l1_dsAudio_negative_dsSetMS12AudioProfileSetttingsOverride (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetAssociatedAudioMixing() correctly enables/disables the associated audio mixing feature during positive scenarios.
 * 
 * **Test Group ID:** Basic: 65@n
 * **Test Case ID:** 288@n
 * 
 * **Dependencies:** Audio device should be connected.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio ports | | dsERR_NONE | Initialization must be successful |
 * |02|Call dsGetAudioPort() - Get the port handle for all supported audio ports on the platform | type ,  index = [ Loop through kPorts ]  | dsERR_NONE | Valid port handle must be returned for all supported audio ports |
 * |03|Call dsSetAssociatedAudioMixing() by looping through acquired valid handles and valid mixing values(i.e TRUE /FALSE) to enable/disable associated audio mixing feature | handle=[valid handle], mixing=[valid value] | dsERR_NONE | audio mixing feature should be successfully set to enable or disable |
 * |07|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsSetAssociatedAudioMixing (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetAssociatedAudioMixing() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 65@n
 * **Test Case ID:** 289@n
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
void test_l1_dsAudio_negative_dsSetAssociatedAudioMixing (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAssociatedAudioMixing() correctly fetches the status of the associated audio mixing feature during positive scenarios.
 * 
 * **Test Group ID:** Basic: 66@n
 * **Test Case ID:** 290@n
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
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetAssociatedAudioMixing (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAssociatedAudioMixing() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 66@n
 * **Test Case ID:** 291@n
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
 * |04|Call dsGetAssociatedAudioMixing() by looping through the acquired valid handle with a NULL mixing pointer |handle=[valid handle], mixing=[NULL] | dsERR_INVALID_PARAM |Invalid parameter error must be returned|
 * |05|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |06|Call dsGetAssociatedAudioMixing() again after terminating audio ports | handle`=[valid handle], mixing=[valid pointer] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized|
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions
 */
void test_l1_dsAudio_negative_dsGetAssociatedAudioMixing (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetFaderControl() correctly sets the mixer balance between main and associated audio during positive scenarios.
 * 
 * **Test Group ID:** Basic: 67@n
 * **Test Case ID:** 292@n
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
void test_l1_dsAudio_positive_dsSetFaderControl (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetFaderControl() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 67@n
 * **Test Case ID:** 293@n
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
void test_l1_dsAudio_negative_dsSetFaderControl (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetFaderControl() correctly fetches the mixer balance between main and associated audio during positive scenarios.
 * 
 * **Test Group ID:** Basic: 68@n
 * **Test Case ID:** 294@n
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
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetFaderControl (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetFaderControl() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 68@n
 * **Test Case ID:** 295@n
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
void test_l1_dsAudio_negative_dsGetFaderControl (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetPrimaryLanguage() correctly sets the AC4 Primary language during positive scenarios.
 * 
 * **Test Group ID:** Basic: 69@n
 * **Test Case ID:** 296@n
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
 * |07|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsSetPrimaryLanguage (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetPrimaryLanguage() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 69@n
 * **Test Case ID:** 297@n
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
 * |04|Call dsSetPrimaryLanguage() by looping through the valid handles and  passing NULL as the language pointer | handle=[valid handle] , pLang=[NULL] | dsERR_INVALID_PARAM | Invalid parameter must be returned |
 * |05|Call dsSetPrimaryLanguage() passing an unsupported language code | handle=[valid handle], pLang=[XYZ] | dsERR_INVALID_PARAM |Invalid parameter must be returned  |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsSetPrimaryLanguage() again after terminating audio ports | handle=[valid handle], pLang=[ENG] | dsERR_NOT_INITIALIZED | call must fail as module is not initialized |
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions 
 */
void test_l1_dsAudio_negative_dsSetPrimaryLanguage (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetPrimaryLanguage() correctly fetches the AC4 Primary language during positive scenarios.
 * 
 * **Test Group ID:** Basic: 70@n
 * **Test Case ID:** 298@n
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
 * |04|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetPrimaryLanguage (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetPrimaryLanguage() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 70@n
 * **Test Case ID:** 299@n
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
void test_l1_dsAudio_negative_dsGetPrimaryLanguage (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetSecondaryLanguage() correctly sets the AC4 Secondary language during positive scenarios.
 * 
 * **Test Group ID:** Basic: 71@n
 * **Test Case ID:** 300@n
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
void test_l1_dsAudio_positive_dsSetSecondaryLanguage (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetSecondaryLanguage() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 71@n
 * **Test Case ID:** 301@n
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
 * |04|Call dsSetSecondaryLanguage() by looping through the valid handles and  passing NULL as the language pointer | handle=[valid handle] , sLang=[NULL] | dsERR_INVALID_PARAM | Invalid parameter must be returned |
 * |05|Call dsSetSecondaryLanguage() by looping through the valid handles and  unsupported language code | handle=[valid handle], sLang=[XYZ] | dsERR_INVALID_PARAM |Invalid parameter must be returned  |
 * |06|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * |07|Call dsSetSecondaryLanguage() again after terminating audio ports | handle=[valid handle] , sLang=[ENG] | dsERR_NOT_INITIALIZED |call must fail as module is not initialized |
 *
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions
 */
void test_l1_dsAudio_negative_dsSetSecondaryLanguage (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetSecondaryLanguage() correctly fetches the AC4 Secondary language during positive scenarios.
 * 
 * **Test Group ID:** Basic: 72@n
 * **Test Case ID:** 302@n
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
 * |07|Call dsAudioPortTerm() - Terminate audio ports | | dsERR_NONE |  Termination must be successful |
 * 
 */
void test_l1_dsAudio_positive_dsGetSecondaryLanguage (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetSecondaryLanguage() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 72@n
 * **Test Case ID:** 303@n
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
void test_l1_dsAudio_negative_dsGetSecondaryLanguage (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetHDMIARCPortId() correctly fetches the audio HDMI ARC port ID during positive scenarios.
 * 
 * **Test Group ID:** Basic: 73@n
 * **Test Case ID:** 304@n
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
void test_l1_dsAudio_positive_dsGetHDMIARCPortId (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetHDMIARCPortId() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 73@n
 * **Test Case ID:** 305@n
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
void test_l1_dsAudio_negative_dsGetHDMIARCPortId (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
	UT_add_test( pSuite, "dsGetSupportedARCTypes_L1_positive" ,test_l1_dsAudio_positive_dsGetSupportedARCTypes );
	UT_add_test( pSuite, "dsGetSupportedARCTypes_L1_negative" ,test_l1_dsAudio_negative_dsGetSupportedARCTypes );
	UT_add_test( pSuite, "dsAudioSetSAD_L1_positive" ,test_l1_dsAudio_positive_dsAudioSetSAD );
	UT_add_test( pSuite, "dsAudioSetSAD_L1_negative" ,test_l1_dsAudio_negative_dsAudioSetSAD );
	UT_add_test( pSuite, "dsAudioEnableARC_L1_positive" ,test_l1_dsAudio_positive_dsAudioEnableARC );
	UT_add_test( pSuite, "dsAudioEnableARC_L1_negative" ,test_l1_dsAudio_negative_dsAudioEnableARC );
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
	UT_add_test( pSuite, "dsSetMS12AudioProfileSetttingsOverride_L1_positive" ,test_l1_dsAudio_positive_dsSetMS12AudioProfileSetttingsOverride );
	UT_add_test( pSuite, "dsSetMS12AudioProfileSetttingsOverride_L1_negative" ,test_l1_dsAudio_negative_dsSetMS12AudioProfileSetttingsOverride );
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
