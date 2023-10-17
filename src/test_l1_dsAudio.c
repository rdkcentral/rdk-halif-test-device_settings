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
* @file TODO: test_l1_dsAudio.c
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
 * @brief Ensure dsAudioPortInit() returns correct error codes during positive scenarios
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
 * |01|Call dsAudioPortInit() - initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsAudioPortTerm() - terminate audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsAudioPortInit() - initialize audio ports again after termination | | dsERR_NONE | Should Pass |
 * |04|Call dsAudioPortTerm() - terminate audio ports after reinitialization | | dsERR_NONE | Should Pass |
 * 
 */
void test_l1_dsAudio_positive_dsAudioPortInit (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |01|Call dsAudioPortInit() - initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsAudioPortInit() again without terminating the previous initialization | | dsERR_ALREADY_INITIALIZED | Should Fail |
 * |03|Call dsAudioPortTerm() - terminate audio ports | | dsERR_NONE | Should Pass |
 * 
 * @note Tests for a headless gateway device, which would return dsERR_OPERATION_NOT_SUPPORTED, are not included here but should be considered in a real-world scenario.
 */
void test_l1_dsAudio_negative_dsAudioPortInit (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsAudioPortTerm() returns correct error codes during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 003@n
 * 
 * **Pre-Conditions:**@n
 * dsAudioPortInit() was successfully called before.
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsAudioPortTerm() - terminate audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsAudioPortInit() - initialize audio ports again after termination | | dsERR_NONE | Should Pass |
 * |04|Call dsAudioPortTerm() - terminate audio ports after reinitialization | | dsERR_NONE | Should Pass |
 * 
 */
void test_l1_dsAudio_positive_dsAudioPortTerm (void)
{
	UT_FAIL(This function needs to be implemented!); 
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
 * |01|Call dsAudioPortTerm() without initializing the audio ports using dsAudioPortInit() | | dsERR_NOT_INITIALIZED | Should Fail |
 * |02|Call dsAudioPortInit() - initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsAudioPortTerm() - terminate audio ports | | dsERR_NONE | Should Pass |
 * |04|Call dsAudioPortTerm() again without re-initializing | | dsERR_NOT_INITIALIZED | Should Fail |
 * 
 */
void test_l1_dsAudio_negative_dsAudioPortTerm (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAudioPort() returns correct error codes during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 005@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Request an available audio port handle with HDMI type and valid index | `type`=dsAUDIOPORT_TYPE_HDMI, `index`=valid value, `handle`=valid pointer | dsERR_NONE | Should Pass |
 * |03|Request an available audio port handle with SPDIF type and valid index | `type`=dsAUDIOPORT_TYPE_SPDIF, `index`=valid value, `handle`=valid pointer | dsERR_NONE | Should Pass |
 * |04|Request an available audio port handle with AV type and valid index | `type`=dsAUDIOPORT_TYPE_AV, `index`=valid value, `handle`=valid pointer | dsERR_NONE | Should Pass |
 * |05|Call dsAudioPortTerm() - terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsGetAudioPort() without initializing audio ports with dsAudioPortInit() | `type`=dsAUDIOPORT_TYPE_HDMI, `index`=valid value, `handle`=valid pointer | dsERR_NOT_INITIALIZED | Should Fail |
 * |02|Call dsAudioPortInit() - initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsGetAudioPort() with an invalid type | `type`=value outside defined types, `index`=valid value, `handle`=valid pointer | dsERR_INVALID_PARAM | Should Fail |
 * |04|Call dsGetAudioPort() with a valid type but invalid index | `type`=dsAUDIOPORT_TYPE_HDMI, `index`=value outside valid range, `handle`=valid pointer | dsERR_INVALID_PARAM | Should Fail |
 * |05|Call dsGetAudioPort() passing a NULL handle | `type`=dsAUDIOPORT_TYPE_HDMI, `index`=valid value, `handle`=NULL | dsERR_INVALID_PARAM | Should Fail |
 * |06|Call dsGetAudioPort() after initializing but mimic an underlying platform error scenario | `type`=dsAUDIOPORT_TYPE_HDMI, `index`=valid value, `handle`=valid pointer (but where a platform error can occur) | dsERR_GENERAL | This will need a setup where the underlying platform can generate an error |
 * |07|Call dsAudioPortTerm() - terminate audio ports | | dsERR_NONE | Clean up |
 * |08|Call dsGetAudioPort() again after termination | `type`=dsAUDIOPORT_TYPE_HDMI, `index`=valid value, `handle`=valid pointer | dsERR_NOT_INITIALIZED | Should Fail |
 * 
 * **Notes:** Testing for the `dsERR_OPERATION_NOT_SUPPORTED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsAudio_negative_dsGetAudioPort (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAudioEncoding() returns correct encoding during positive scenarios
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
 * |01|Call dsAudioPortInit() | | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available audio port handle | | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Call dsGetAudioEncoding() using the acquired handle to get the audio encoding | `handle`=acquired from previous step, `encoding`=valid pointer | dsERR_NONE | Check the returned encoding value to ensure it's valid |
 * |04|Call dsAudioPortTerm() | | | dsERR_NONE | Should Pass |
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
 * |01|Call dsGetAudioEncoding() without initializing audio ports | `handle`=any value, `encoding`=valid pointer | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() | | | dsERR_NONE | Should Pass |
 * |03|Call dsGetAudioEncoding() using an invalid handle | `handle`=invalid value, `encoding`=valid pointer | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsGetAudioPort() to get a valid handle | | | dsERR_NONE and a valid handle | Required for next step |
 * |05|Call dsGetAudioEncoding() with a valid handle but a null encoding pointer | `handle`=acquired from previous step, `encoding`=NULL | dsERR_INVALID_PARAM | Should Pass |
 * |06|Call dsAudioPortTerm() | | | dsERR_NONE | Should Pass |
 * |07|Call dsGetAudioEncoding() again after terminating audio ports | `handle`=valid handle from step 04, `encoding`=valid pointer | dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetAudioEncoding (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetAudioEncoding() sets the encoding correctly for all valid enum values during positive scenarios
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
 * |01|Call dsAudioPortInit() | | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available audio port handle | | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Call dsSetAudioEncoding() using the acquired handle and set encoding to each valid encoding type in dsAudioEncoding_t | `handle`=acquired from previous step, `encoding`=Iterate through all valid dsAudioEncoding_t values | dsERR_NONE for each encoding type | Encoding should be set correctly for each type |
 * |04|Call dsAudioPortTerm() | | | dsERR_NONE | Should Pass |
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
 * |01|Call dsSetAudioEncoding() without initializing audio ports | `handle`=any value, `encoding`=a valid dsAudioEncoding_t value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() | | | dsERR_NONE | Should Pass |
 * |03|Call dsSetAudioEncoding() using an invalid handle | `handle`=invalid value, `encoding`=a valid dsAudioEncoding_t value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsGetAudioPort() to get a valid handle | | | dsERR_NONE and a valid handle | Required for next step |
 * |05|Call dsSetAudioEncoding() with an encoding value that is not part of the dsAudioEncoding_t enum (out of bounds) | `handle`=acquired from previous step, `encoding`=invalid encoding value | dsERR_INVALID_PARAM | Should Pass |
 * |06|Call dsAudioPortTerm() | | | dsERR_NONE | Should Pass |
 * |07|Call dsSetAudioEncoding() again after terminating audio ports | `handle`=valid handle from step 04, `encoding`=a valid dsAudioEncoding_t value | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Call dsGetAudioFormat() using the acquired handle and retrieve the audio format | `handle`=acquired from previous step, `audioFormat`=pointer to hold the format | dsERR_NONE and a valid audioFormat value from the dsAudioFormat_t enum | Audio format should be retrieved correctly |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsGetAudioFormat() without initializing audio ports | `handle`=any value, `audioFormat`=pointer | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsGetAudioFormat() using an invalid handle | `handle`=invalid value, `audioFormat`=pointer | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsGetAudioPort() to get a valid handle | | dsERR_NONE and a valid handle | Required for next step |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |06|Call dsGetAudioFormat() again after terminating audio ports | `handle`=valid handle from step 04, `audioFormat`=pointer | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Call dsGetAudioCompression() using the acquired handle and retrieve the audio compression | `handle`=acquired from previous step, `compression`=pointer to hold the compression level | dsERR_NONE and compression value in range [0,10] | Audio compression should be retrieved correctly |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsGetAudioCompression() without initializing audio ports | `handle`=any value, `compression`=pointer | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsGetAudioCompression() using an invalid handle | `handle`=invalid value, `compression`=pointer | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsGetAudioPort() to get a valid handle | | dsERR_NONE and a valid handle | Required for next step |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |06|Call dsGetAudioCompression() again after terminating audio ports | `handle`=valid handle from step 04, `compression`=pointer | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Call dsSetAudioCompression() using the acquired handle and set the audio compression to the minimum level | `handle`=acquired from previous step, `compression`=0 | dsERR_NONE | Audio compression should be set correctly |
 * |04|Call dsSetAudioCompression() using the acquired handle and set the audio compression to the maximum level | `handle`=acquired from previous step, `compression`=10 | dsERR_NONE | Audio compression should be set correctly |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * 
 */
void test_l1_dsAudio_positive_dsSetAudioCompression (void)
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Call dsSetAudioCompression() using the acquired handle and set the audio compression to the minimum level | `handle`=acquired from previous step, `compression`=0 | dsERR_NONE | Audio compression should be set correctly |
 * |04|Call dsSetAudioCompression() using the acquired handle and set the audio compression to the maximum level | `handle`=acquired from previous step, `compression`=10 | dsERR_NONE | Audio compression should be set correctly |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * 
 */
void test_l1_dsAudio_negative_dsSetAudioCompression (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetAudioCompression() returns correct error codes during negative scenarios
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
 * |01|Call dsSetAudioCompression() without initializing audio ports | `handle`=any value, `compression`=any valid value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsSetAudioCompression() using an invalid handle | `handle`=invalid value, `compression`=any valid value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsSetAudioCompression() using a valid handle but out of range compression value | `handle`=valid handle, `compression`=value <0 or >10 | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsGetAudioPort() to get a valid handle | | dsERR_NONE and a valid handle | Required for next step |
 * |06|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |07|Call dsSetAudioCompression() again after terminating audio ports | `handle`=valid handle from step 05, `compression`=any valid value | dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_positive_dsGetDialogEnhancement (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetAudioCompression() returns correct error codes during negative scenarios
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
 * |01|Call dsSetAudioCompression() without initializing audio ports | `handle`=any value, `compression`=any valid value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsSetAudioCompression() using an invalid handle | `handle`=invalid value, `compression`=any valid value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsSetAudioCompression() using a valid handle but out of range compression value | `handle`=valid handle, `compression`=value <0 or >10 | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsGetAudioPort() to get a valid handle | | dsERR_NONE and a valid handle | Required for next step |
 * |06|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |07|Call dsSetAudioCompression() again after terminating audio ports | `handle`=valid handle from step 05, `compression`=any valid value | dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetDialogEnhancement (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetDialogEnhancement() retrieves the Dialog Enhancement level correctly during positive scenarios
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Call dsGetDialogEnhancement() using the acquired handle | `handle`=acquired from previous step, `level`=pointer to integer variable | dsERR_NONE and value of `level` in the range [0,16] | Dialog Enhancement level should be retrieved correctly |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * 
 */
void test_l1_dsAudio_positive_dsSetDialogEnhancement (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetDialogEnhancement() returns correct error codes during negative scenarios
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
 * |01|Call dsGetDialogEnhancement() without initializing audio ports | `handle`=any value, `level`=pointer to integer variable | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsGetDialogEnhancement() using an invalid handle | `handle`=invalid value, `level`=pointer to integer variable | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsGetAudioPort() to get a valid handle | | dsERR_NONE and a valid handle | Required for next step |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |06|Call dsGetDialogEnhancement() again after terminating audio ports | `handle`=valid handle from step 04, `level`=pointer to integer variable | dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsSetDialogEnhancement (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetDialogEnhancement() sets the Dialog Enhancement level correctly during positive scenarios.
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Iterate over each Dialog Enhancement level from 0 to 16 and call dsSetDialogEnhancement() for each | `handle`=acquired from previous step, `level`=0 to 16 | dsERR_NONE for each iteration | Dialog Enhancement level should be set correctly for each value |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * 
 */
void test_l1_dsAudio_positive_dsGetDolbyVolumeMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetDialogEnhancement() returns correct error codes during negative scenarios.
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
 * |01|Call dsSetDialogEnhancement() without initializing audio ports | `handle`=any value, `level`=any valid level | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsSetDialogEnhancement() using an invalid handle | `handle`=invalid value, `level`=any valid level | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsSetDialogEnhancement() using an invalid level (<0 or >16) | `handle`=any value, `level`= <0 or >16 | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsGetAudioPort() to get a valid handle | | dsERR_NONE and a valid handle | Required for next step |
 * |06|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |07|Call dsSetDialogEnhancement() again after terminating audio ports | `handle`=valid handle from step 05, `level`=any valid level | dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetDolbyVolumeMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetDolbyVolumeMode() retrieves the Dolby Audio Mode status correctly during positive scenarios.
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Call dsGetDolbyVolumeMode() using the obtained handle| `handle`=acquired from previous step, `mode`=address of a bool variable | dsERR_NONE | Should retrieve Dolby Audio Mode status correctly |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * 
 */
void test_l1_dsAudio_positive_dsSetDolbyVolumeMode (void)
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
 * |01|Call dsGetDolbyVolumeMode() without initializing audio ports | `handle`=any value, `mode`=address of a bool variable | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsGetDolbyVolumeMode() using an invalid handle | `handle`=invalid value, `mode`=address of a bool variable | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsGetDolbyVolumeMode() with NULL for the mode pointer | `handle`=any value, `mode`=NULL | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsGetAudioPort() to get a valid handle | | dsERR_NONE and a valid handle | Required for next step |
 * |06|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |07|Call dsGetDolbyVolumeMode() again after terminating audio ports | `handle`=valid handle from step 05, `mode`=address of a bool variable | dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsSetDolbyVolumeMode (void)
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Set Dolby Volume Mode to OFF using the obtained handle | `handle`=acquired from previous step, `mode`=0 (OFF) | dsERR_NONE | Dolby Volume Mode should be set to OFF |
 * |04|Set Dolby Volume Mode to ON using the obtained handle | `handle`=acquired from previous step, `mode`=1 (ON) | dsERR_NONE | Dolby Volume Mode should be set to ON |
 * |05|Set Dolby Volume Mode to AUTO using the obtained handle | `handle`=acquired from previous step, `mode`=2 (AUTO) | dsERR_NONE | Dolby Volume Mode should be set to AUTO |
 * |06|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * 
 */
void test_l1_dsAudio_positive_dsGetIntelligentEqualizerMode (void)
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
 * |01|Call dsSetDolbyVolumeMode() without initializing audio ports | `handle`=any value, `mode`=0 (OFF) | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsSetDolbyVolumeMode() using an invalid handle | `handle`=invalid value, `mode`=1 (ON) | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsSetDolbyVolumeMode() using an invalid mode value | `handle`=valid handle, `mode`=invalid value (e.g., 3) | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsGetAudioPort() to get a valid handle | | dsERR_NONE and a valid handle | Required for next step |
 * |06|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |07|Call dsSetDolbyVolumeMode() again after terminating audio ports | `handle`=valid handle from step 05, `mode`=0 (OFF) | dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsGetIntelligentEqualizerMode (void)
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Retrieve Intelligent Equalizer Mode using the obtained handle | `handle`=acquired from previous step | dsERR_NONE and a valid mode between 0 to 6 | Ensure that the returned mode value corresponds to the settings in the system |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * 
 */
void test_l1_dsAudio_positive_dsSetIntelligentEqualizerMode (void)
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
 * |01|Call dsGetIntelligentEqualizerMode() without initializing audio ports | `handle`=any value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsGetIntelligentEqualizerMode() using an invalid handle | `handle`=invalid value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsGetIntelligentEqualizerMode() with null pointer for mode | `handle`=valid handle, `mode`=NULL | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsGetAudioPort() to get a valid handle | | dsERR_NONE and a valid handle | Required for next step |
 * |06|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |07|Call dsGetIntelligentEqualizerMode() again after terminating audio ports | `handle`=valid handle from step 05 | dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 */
void test_l1_dsAudio_negative_dsSetIntelligentEqualizerMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
* @brief TODO: Describe the objective of the test
*
* TODO: Add the description of what is tested and why in this test@n
*
* **Test Group ID:** TODO: Basic (for L1): 01 / Module (L2): 02 / Stress (L2): 03)@n
* **Test Case ID:** TODO: Add the ID of the test case so that it can be logically tracked in the logs@n
* @n
* **Pre-Conditions:** TODO: Add pre-conditions, if any@n
* **Dependencies:** TODO: Add dependencies for this test, if any@n
* **User Interaction:** TODO: Add any user interactions required during this test, if any
* @n
* **Test Procedure:**@n
* TODO: Add the steps to run this test and add a line in the below table for each input variation tried in this function.@n
* | Variation / Step | Description | Test Data | Expected Result | Notes |
* | :-------: | ------------- | --------- | --------------- | ----- |
* | 01 | First set of conditions | What is input data to be tested | How to gauge success, is it a success variable? | Should be successful |
*/
void test_l1_dsAudio_positive_dsGetVolumeLeveller (void)
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Retrieve Volume Leveller using the obtained handle | `handle`=acquired from previous step, `volLeveller`=valid pointer | dsERR_NONE | Ensure that the volume leveller settings are retrieved correctly |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * 
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Set Volume Leveller using the obtained handle | `handle`=acquired from previous step, `volLeveller`=valid settings | dsERR_NONE | Ensure that the volume leveller settings are set correctly |
 * |04|Retrieve the Volume Leveller settings to verify | `handle`=acquired from previous step, `volLeveller`=pointer to check the set values | dsERR_NONE and the values should match step 03 | Verification step |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsSetVolumeLeveller() without initializing audio ports | `handle`=any value, `volLeveller`=valid settings | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsSetVolumeLeveller() using an invalid handle | `handle`=invalid value, `volLeveller`=valid settings | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsGetAudioPort() to get a valid handle | | dsERR_NONE and a valid handle | Required for next step |
 * |05|Set invalid Volume Leveller settings | `handle`=valid handle from step 04, `volLeveller`=invalid settings | dsERR_INVALID_PARAM | Specific invalid settings need to be defined |
 * |06|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |07|Call dsSetVolumeLeveller() again after terminating audio ports | `handle`=valid handle from step 04, `volLeveller`=valid settings | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Retrieve the Bass Enhancer settings using the obtained handle | `handle`=acquired from previous step, `boost`=pointer to retrieve value | dsERR_NONE | Ensure that the Bass Enhancer value is retrieved correctly |
 * |04|Check if the retrieved value is within the expected range | `boost` value | Value between 0 to 100 | Verification step |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsGetBassEnhancer() without initializing audio ports | `handle`=any value, `boost`=pointer to retrieve value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsGetBassEnhancer() using an invalid handle | `handle`=invalid value, `boost`=pointer to retrieve value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsGetAudioPort() to get a valid handle | | dsERR_NONE and a valid handle | Required for next step |
 * |05|Call dsGetBassEnhancer() with a null pointer for boost | `handle`=valid handle from step 04, `boost`=NULL | dsERR_INVALID_PARAM | Should Pass |
 * |06|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |07|Call dsGetBassEnhancer() again after terminating audio ports | `handle`=valid handle from step 04, `boost`=pointer to retrieve value | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Set the Bass Enhancer settings using the obtained handle with a valid boost value | `handle`=acquired from previous step, `boost`=50 | dsERR_NONE | Ensure that the Bass Enhancer value is set correctly |
 * |04|Retrieve the Bass Enhancer settings to verify if the value was set correctly | Use dsGetBassEnhancer() | Boost value should be 50 | Verification step |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsSetBassEnhancer() without initializing audio ports | `handle`=any value, `boost`=50 | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsSetBassEnhancer() using an invalid handle | `handle`=invalid value, `boost`=50 | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsGetAudioPort() to get a valid handle | | dsERR_NONE and a valid handle | Required for next step |
 * |05|Call dsSetBassEnhancer() with a boost value outside the valid range (negative value) | `handle`=valid handle from step 04, `boost`=-10 | dsERR_INVALID_PARAM | Should Pass |
 * |06|Call dsSetBassEnhancer() with a boost value outside the valid range (exceeding 100) | `handle`=valid handle from step 04, `boost`=110 | dsERR_INVALID_PARAM | Should Pass |
 * |07|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |08|Call dsSetBassEnhancer() again after terminating audio ports | `handle`=valid handle from step 04, `boost`=50 | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Enable the Surround Decoder using dsEnableSurroundDecoder() | `handle`=acquired from previous step | dsERR_NONE | Ensure that the Surround Decoder is enabled |
 * |04|Retrieve the Surround Decoder status using the obtained handle | `handle`=acquired from previous step | Value of *enabled should be true | Verification step |
 * |05|Disable the Surround Decoder using dsEnableSurroundDecoder() | `handle`=acquired from previous step | dsERR_NONE | Ensure that the Surround Decoder is disabled |
 * |06|Retrieve the Surround Decoder status again using the obtained handle | `handle`=acquired from previous step | Value of *enabled should be false | Verification step |
 * |07|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsIsSurroundDecoderEnabled() without initializing audio ports | `handle`=any value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsIsSurroundDecoderEnabled() using an invalid handle | `handle`=invalid value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsGetAudioPort() to get a valid handle | | dsERR_NONE and a valid handle | Required for next step |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |06|Call dsIsSurroundDecoderEnabled() again after terminating audio ports | `handle`=valid handle from step 04 | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Enable the Surround Decoder using the obtained handle | `handle`=acquired from previous step, `enabled`=true | dsERR_NONE | Ensure that the Surround Decoder is enabled |
 * |04|Retrieve the Surround Decoder status using dsIsSurroundDecoderEnabled() | `handle`=acquired from previous step | Value of *enabled should be true | Verification step |
 * |05|Disable the Surround Decoder using the obtained handle | `handle`=acquired from previous step, `enabled`=false | dsERR_NONE | Ensure that the Surround Decoder is disabled |
 * |06|Retrieve the Surround Decoder status using dsIsSurroundDecoderEnabled() | `handle`=acquired from previous step | Value of *enabled should be false | Verification step |
 * |07|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsEnableSurroundDecoder() without initializing audio ports | `handle`=any value, `enabled`=true | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsEnableSurroundDecoder() using an invalid handle | `handle`=invalid value, `enabled`=true | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsGetAudioPort() to get a valid handle | | dsERR_NONE and a valid handle | Required for next step |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |06|Call dsEnableSurroundDecoder() again after terminating audio ports | `handle`=valid handle from step 04, `enabled`=true | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Set the DRC Mode to DRC line mode using dsSetDRCMode() | `handle`=acquired from previous step, `mode`=0 | dsERR_NONE | Ensure that the DRC Mode is set to DRC line mode |
 * |04|Retrieve the DRC Mode using dsGetDRCMode() | `handle`=acquired from previous step | Value of *mode should be 0 | Verification step |
 * |05|Set the DRC Mode to DRC RF mode using dsSetDRCMode() | `handle`=acquired from previous step, `mode`=1 | dsERR_NONE | Ensure that the DRC Mode is set to DRC RF mode |
 * |06|Retrieve the DRC Mode using dsGetDRCMode() | `handle`=acquired from previous step | Value of *mode should be 1 | Verification step |
 * |07|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsGetDRCMode() without initializing audio ports | `handle`=any value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsGetDRCMode() using an invalid handle | `handle`=invalid value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsGetAudioPort() to get a valid handle | | dsERR_NONE and a valid handle | Required for next step |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |06|Call dsGetDRCMode() again after terminating audio ports | `handle`=valid handle from step 04 | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Set the DRC Mode to DRC line mode using dsSetDRCMode() | `handle`=acquired from previous step, `mode`=0 | dsERR_NONE | Ensure that the DRC Mode is set to DRC line mode |
 * |04|Retrieve the DRC Mode using dsGetDRCMode() to verify | `handle`=acquired from previous step | Value of *mode should be 0 | Verification step |
 * |05|Set the DRC Mode to DRC RF mode using dsSetDRCMode() | `handle`=acquired from previous step, `mode`=1 | dsERR_NONE | Ensure that the DRC Mode is set to DRC RF mode |
 * |06|Retrieve the DRC Mode using dsGetDRCMode() to verify | `handle`=acquired from previous step | Value of *mode should be 1 | Verification step |
 * |07|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsSetDRCMode() without initializing audio ports | `handle`=any value, `mode`=any value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsSetDRCMode() using an invalid handle | `handle`=invalid value, `mode`=0 | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsSetDRCMode() using invalid mode values (not 0 or 1) | `handle`=valid handle, `mode`=any value not in [0,1] | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsGetAudioPort() to get a valid handle | | dsERR_NONE and a valid handle | Required for next step |
 * |06|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |07|Call dsSetDRCMode() again after terminating audio ports | `handle`=valid handle from step 05, `mode`=0 | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Set a known Surround Virtualizer level using dsSetSurroundVirtualizer() | `handle`=acquired from previous step, `virtualizer`=a known setting | dsERR_NONE | Prep step to ensure a known state |
 * |04|Retrieve the Surround Virtualizer level using dsGetSurroundVirtualizer() | `handle`=acquired from previous step | Value of *virtualizer should match the known setting | Verification step |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsGetSurroundVirtualizer() without initializing audio ports | `handle`=any value, `virtualizer`=NULL or any pointer | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsGetSurroundVirtualizer() using an invalid handle | `handle`=invalid value, `virtualizer`=any pointer | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsGetSurroundVirtualizer() using NULL for `virtualizer` | `handle`=valid handle, `virtualizer`=NULL | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsGetAudioPort() to get a valid handle | | dsERR_NONE and a valid handle | Required for next step |
 * |06|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |07|Call dsGetSurroundVirtualizer() again after terminating audio ports | `handle`=valid handle from step 05, `virtualizer`=any pointer | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Set a known Surround Virtualizer level using dsSetSurroundVirtualizer() | `handle`=acquired from previous step, `virtualizer`=a known setting | dsERR_NONE | Verification step |
 * |04|Retrieve the Surround Virtualizer level using dsGetSurroundVirtualizer() | `handle`=acquired from previous step | Value of *virtualizer should match the known setting | Cross verification step |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsSetSurroundVirtualizer() without initializing audio ports | `handle`=any value, `virtualizer`=a valid value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsSetSurroundVirtualizer() using an invalid handle | `handle`=invalid value, `virtualizer`=a valid value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsGetAudioPort() to get a valid handle | | dsERR_NONE and a valid handle | Required for next step |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |06|Call dsSetSurroundVirtualizer() again after terminating audio ports | `handle`=valid handle from step 04, `virtualizer`=a valid value | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Enable MI Steering using dsSetMISteering() | `handle`=acquired from previous step, `enabled`=true | dsERR_NONE | Setup for next step |
 * |04|Retrieve the MI Steering status using dsGetMISteering() | `handle`=acquired from previous step | Value of *enabled should be true | Cross verification step |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsGetMISteering() without initializing audio ports | `handle`=any value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsGetMISteering() using an invalid handle | `handle`=invalid value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsGetAudioPort() to get a valid handle | | dsERR_NONE and a valid handle | Required for next step |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |06|Call dsGetMISteering() again after terminating audio ports | `handle`=valid handle from step 04 | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Enable MI Steering using dsSetMISteering() | `handle`=acquired from previous step, `enabled`=true | dsERR_NONE | |
 * |04|Retrieve the MI Steering status using dsGetMISteering() | `handle`=acquired from previous step | Value of *enabled should be true | Cross verification step |
 * |05|Disable MI Steering using dsSetMISteering() | `handle`=acquired from previous step, `enabled`=false | dsERR_NONE | |
 * |06|Retrieve the MI Steering status again using dsGetMISteering() | `handle`=acquired from previous step | Value of *enabled should be false | Cross verification step |
 * |07|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsSetMISteering() without initializing audio ports | `handle`=any value, `enabled`=true | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsSetMISteering() using an invalid handle | `handle`=invalid value, `enabled`=true | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsGetAudioPort() to get a valid handle | | dsERR_NONE and a valid handle | Required for next step |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |06|Call dsSetMISteering() again after terminating audio ports | `handle`=valid handle from step 04, `enabled`=true | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Set the Graphic Equalizer Mode using dsSetGraphicEqualizerMode() | `handle`=acquired from previous step, `mode`=1 (EQ Open) | dsERR_NONE | |
 * |04|Retrieve the Graphic Equalizer Mode using dsGetGraphicEqualizerMode() | `handle`=acquired from previous step | Value of *mode should be 1 | Cross verification step |
 * |05|Set the Graphic Equalizer Mode using dsSetGraphicEqualizerMode() | `handle`=acquired from previous step, `mode`=2 (EQ Rich) | dsERR_NONE | |
 * |06|Retrieve the Graphic Equalizer Mode again using dsGetGraphicEqualizerMode() | `handle`=acquired from previous step | Value of *mode should be 2 | Cross verification step |
 * |07|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsGetGraphicEqualizerMode() without initializing audio ports | `handle`=any value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsGetGraphicEqualizerMode() using an invalid handle | `handle`=invalid value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsGetAudioPort() to get a valid handle | | dsERR_NONE and a valid handle | Required for next step |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |06|Call dsGetGraphicEqualizerMode() again after terminating audio ports | `handle`=valid handle from step 04 | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Set the Graphic Equalizer Mode using dsSetGraphicEqualizerMode() | `handle`=acquired from previous step, `mode`=1 (EQ Open) | dsERR_NONE | |
 * |04|Retrieve the Graphic Equalizer Mode using dsGetGraphicEqualizerMode() | `handle`=acquired from previous step | Value of mode should be 1 | Cross verification step |
 * |05|Set the Graphic Equalizer Mode using dsSetGraphicEqualizerMode() | `handle`=acquired from previous step, `mode`=2 (EQ Rich) | dsERR_NONE | |
 * |06|Retrieve the Graphic Equalizer Mode again using dsGetGraphicEqualizerMode() | `handle`=acquired from previous step | Value of mode should be 2 | Cross verification step |
 * |07|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsSetGraphicEqualizerMode() without initializing audio ports | `handle`=any value, `mode`=any valid value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsSetGraphicEqualizerMode() using an invalid handle | `handle`=invalid value, `mode`=any valid value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsSetGraphicEqualizerMode() using an invalid mode value | `handle`=valid handle, `mode`=invalid value (e.g. 5) | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |06|Call dsSetGraphicEqualizerMode() again after terminating audio ports | `handle`=valid handle, `mode`=any valid value | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Retrieve the list of supported MS12 audio profiles using dsGetMS12AudioProfileList() | `handle`=acquired from previous step | dsERR_NONE and a valid list of profiles | The profiles list should be populated |
 * |04|Verify that the profiles list is valid and is not empty | | Non-empty list of profiles | |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsGetMS12AudioProfileList() without initializing audio ports | `handle`=any value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsGetMS12AudioProfileList() using an invalid handle | `handle`=invalid value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsGetMS12AudioProfileList() with a null pointer for profiles | `handle`=valid handle, `profiles`=NULL | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |06|Call dsGetMS12AudioProfileList() again after terminating audio ports | `handle`=valid handle | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Retrieve the current audio profile configured using dsGetMS12AudioProfile() | `handle`=acquired from previous step | dsERR_NONE and a valid profile | The profile string should be populated |
 * |04|Verify that the profile string is valid and is not empty | | Non-empty profile string | |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsGetMS12AudioProfile() without initializing audio ports | `handle`=any value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsGetMS12AudioProfile() using an invalid handle | `handle`=invalid value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsGetMS12AudioProfile() with a null pointer for profile | `handle`=valid handle, `profile`=NULL | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |06|Call dsGetMS12AudioProfile() again after terminating audio ports | `handle`=valid handle | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available ARC/eARC port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Retrieve the supported ARC types of the connected ARC/eARC device using dsGetSupportedARCTypes() | `handle`=acquired from previous step | dsERR_NONE and valid types | The types should be populated |
 * |04|Verify that the types value is valid (based on expected ARC types) | | Valid ARC types | |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsGetSupportedARCTypes() using an invalid handle | `handle`=invalid value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsGetSupportedARCTypes() with a null pointer for types | `handle`=valid handle, `types`=NULL | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available ARC/eARC port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Retrieve the SADs from CEC for the connected ARC device and populate the sad_list | | Valid sad_list | |
 * |04|Set the SAD using dsAudioSetSAD() | `handle`=acquired from previous step, `sad_list`=populated SADs | dsERR_NONE | The SAD should be set correctly |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsAudioSetSAD() using an invalid handle | `handle`=invalid value, `sad_list`=valid | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioSetSAD() with invalid SAD values | `handle`=valid handle, `sad_list`=invalid | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available ARC/eARC port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Enable ARC using dsAudioEnableARC() | `handle`=acquired from previous step, `arcStatus`=enable | dsERR_NONE | ARC/eARC should be enabled |
 * |04|Disable ARC using dsAudioEnableARC() | `handle`=acquired from previous step, `arcStatus`=disable | dsERR_NONE | ARC/eARC should be disabled |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsAudioEnableARC() using an invalid handle | `handle`=invalid value, `arcStatus`=enable | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioEnableARC() with invalid arcStatus values | `handle`=valid handle, `arcStatus`=invalid value | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Retrieve stereo mode using dsGetStereoMode() | `handle`=acquired from previous step | dsERR_NONE and the valid stereoMode | Correct stereo mode should be returned |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsGetStereoMode() without initializing audio ports | `handle`=any value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsGetStereoMode() using an invalid handle | `handle`=invalid value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Provide a NULL pointer for stereoMode in dsGetStereoMode() | `handle`=valid handle, `stereoMode`=NULL | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |06|Call dsGetStereoMode() again after terminating audio ports | `handle`=valid handle | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Set stereo mode using dsSetStereoMode() | `handle`=acquired from previous step, `mode`=valid mode value from dsAudioStereoMode_t | dsERR_NONE | Stereo mode should be set successfully |
 * |04|Retrieve stereo mode using dsGetStereoMode() to validate the mode was set | `handle`=acquired from previous step | dsERR_NONE and mode should match the set value | Ensure correct mode is set |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsSetStereoMode() without initializing audio ports | `handle`=any value, `mode`=valid mode value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsSetStereoMode() using an invalid handle | `handle`=invalid value, `mode`=valid mode value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Set an invalid stereo mode using dsSetStereoMode() | `handle`=valid handle, `mode`=invalid mode value | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |06|Call dsSetStereoMode() again after terminating audio ports | `handle`=valid handle, `mode`=valid mode value | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Retrieve stereo auto mode using dsGetStereoAuto() | `handle`=acquired from previous step | dsERR_NONE and autoMode should be either 0 or 1 | Auto mode should be retrieved successfully |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsGetStereoAuto() without initializing audio ports | `handle`=any value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsGetStereoAuto() using an invalid handle | `handle`=invalid value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Retrieve auto mode using a NULL pointer for autoMode in dsGetStereoAuto() | `handle`=valid handle, `autoMode`=NULL | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |06|Call dsGetStereoAuto() again after terminating audio ports | `handle`=valid handle | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Set auto mode to Disabled using dsSetStereoAuto() | `handle`=acquired from previous step, `autoMode`=0 | dsERR_NONE | Auto mode should be set to Disabled successfully |
 * |04|Set auto mode to Enabled using dsSetStereoAuto() | `handle`=acquired from previous step, `autoMode`=1 | dsERR_NONE | Auto mode should be set to Enabled successfully |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsSetStereoAuto() without initializing audio ports | `handle`=any value, `autoMode`=0 | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsSetStereoAuto() using an invalid handle | `handle`=invalid value, `autoMode`=0 | dsERR_INVALID_PARAM | Should Pass |
 * |04|Set auto mode to an invalid value (other than 0 or 1) using dsSetStereoAuto() | `handle`=valid handle, `autoMode`=any value other than 0 or 1 | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |06|Call dsSetStereoAuto() again after terminating audio ports | `handle`=valid handle, `autoMode`=0 | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Retrieve audio gain using dsGetAudioGain() | `handle`=acquired from previous step | dsERR_NONE and the gain should be a valid float value | Should retrieve the gain value successfully |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsGetAudioGain() without initializing audio ports | `handle`=any value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsGetAudioGain() using an invalid handle | `handle`=invalid value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsGetAudioGain() with a NULL gain pointer | `handle`=valid handle, `gain`=NULL | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |06|Call dsGetAudioGain() again after terminating audio ports | `handle`=valid handle | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Set audio gain using dsSetAudioGain() | `handle`=acquired from previous step, `gain`=some valid float value | dsERR_NONE | Gain should be set successfully |
 * |04|Retrieve the gain using dsGetAudioGain() to confirm it was set correctly | `handle`=acquired from previous step | dsERR_NONE and the retrieved gain should match the set gain | Should Pass |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsSetAudioGain() without initializing audio ports | `handle`=any value, `gain`=some valid float value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsSetAudioGain() using an invalid handle | `handle`=invalid value, `gain`=some valid float value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Set audio gain using dsSetAudioGain() with an out of range gain value | `handle`=valid handle, `gain`=out of range value (once the range is defined) | dsERR_INVALID_PARAM or dsERR_OPERATION_NOT_SUPPORTED | Should Pass |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |06|Call dsSetAudioGain() again after terminating audio ports | `handle`=valid handle, `gain`=some valid float value | dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
 * @note Setting and testing out of range gain values might require an additional procedure, once the range is defined.
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Retrieve the audio dB level using dsGetAudioDB() | `handle`=acquired from previous step | dsERR_NONE and a valid dB level in expected range (once defined) | dB level should be retrieved successfully |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsGetAudioDB() without initializing audio ports | `handle`=any value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsGetAudioDB() using an invalid handle | `handle`=invalid value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |05|Call dsGetAudioDB() again after terminating audio ports | `handle`=valid handle from earlier step | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Set a known dB level using dsSetAudioDB() | `handle`=acquired from previous step, `db`=any valid value in expected range (once defined) | dsERR_NONE | dB level should be set successfully |
 * |04|Retrieve the set dB level using dsGetAudioDB() | `handle`=acquired from step 2 | dsERR_NONE and the dB level should match the value set in step 3 | Should Pass |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsSetAudioDB() without initializing audio ports | `handle`=any value, `db`=any valid value in expected range | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsSetAudioDB() using an invalid handle | `handle`=invalid value, `db`=any valid value in expected range | dsERR_INVALID_PARAM | Should Pass |
 * |04|Set an out-of-range dB level using dsSetAudioDB() | `handle`=valid handle, `db`=value outside expected range (once defined) | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |06|Call dsSetAudioDB() again after terminating audio ports | `handle`=valid handle from earlier step, `db`=any valid value | dsERR_NOT_INITIALIZED | Should Pass |
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
 * **Dependencies:** Audio device should be connected and working properly.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Retrieve the current audio level using dsGetAudioLevel() | `handle`=acquired from previous step | dsERR_NONE and the audio level value between 0 and 100 | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsGetAudioLevel() without initializing audio ports | `handle`=any value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsGetAudioLevel() using an invalid handle | `handle`=invalid value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |05|Call dsGetAudioLevel() again after terminating audio ports | `handle`=valid handle from earlier step | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Set a known volume level using dsSetAudioLevel() | `handle`=acquired from previous step, `level`=any valid value between 0 and 100 | dsERR_NONE | Volume level should be set successfully |
 * |04|Retrieve the set volume level using dsGetAudioLevel() | `handle`=acquired from step 2 | dsERR_NONE and the volume level should match the value set in step 3 | Should Pass |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsSetAudioLevel() without initializing audio ports | `handle`=any value, `level`=any valid value between 0 and 100 | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsSetAudioLevel() using an invalid handle | `handle`=invalid value, `level`=any valid value between 0 and 100 | dsERR_INVALID_PARAM | Should Pass |
 * |04|Set an out-of-range volume level using dsSetAudioLevel() | `handle`=valid handle, `level`=value outside the range 0-100 | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |06|Call dsSetAudioLevel() again after terminating audio ports | `handle`=valid handle from earlier step, `level`=any valid value | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Retrieve the maximum audio dB level using dsGetAudioMaxDB() | `handle`=acquired from previous step | dsERR_NONE and a valid max dB value (platform specific) | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsGetAudioMaxDB() without initializing audio ports | `handle`=any value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsGetAudioMaxDB() using an invalid handle | `handle`=invalid value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |05|Call dsGetAudioMaxDB() again after terminating audio ports | `handle`=valid handle from earlier step | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Retrieve the minimum audio dB level using dsGetAudioMinDB() | `handle`=acquired from previous step | dsERR_NONE and a valid min dB value (platform specific) | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsGetAudioMinDB() without initializing audio ports | `handle`=any value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsGetAudioMinDB() using an invalid handle | `handle`=invalid value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |05|Call dsGetAudioMinDB() again after terminating audio ports | `handle`=valid handle from earlier step | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Retrieve the optimal audio level using dsGetAudioOptimalLevel() | `handle`=acquired from previous step | dsERR_NONE and a valid optimal level value (platform specific) | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsGetAudioOptimalLevel() without initializing audio ports | `handle`=any value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsGetAudioOptimalLevel() using an invalid handle | `handle`=invalid value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |05|Call dsGetAudioOptimalLevel() again after terminating audio ports | `handle`=valid handle from earlier step | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Retrieve the audio delay using dsGetAudioDelay() | `handle`=acquired from previous step | dsERR_NONE and a valid audio delay value (in milliseconds) | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsGetAudioDelay() without initializing audio ports | `handle`=any value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsGetAudioDelay() using an invalid handle | `handle`=invalid value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |05|Call dsGetAudioDelay() again after terminating audio ports | `handle`=valid handle from earlier step | dsERR_NOT_INITIALIZED | Should Pass |
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
 * **Dependencies:** Audio device should be connected and working properly.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Set an audio delay using dsSetAudioDelay() | `handle`=acquired from previous step, `audioDelayMs`= 100 | dsERR_NONE | Should Pass |
 * |04|Retrieve the set audio delay using dsGetAudioDelay() | `handle`=acquired from previous step | dsERR_NONE and audioDelayMs should match the value set | Should Pass |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsSetAudioDelay() without initializing audio ports | `handle`=any value, `audioDelayMs`= 100 | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsSetAudioDelay() using an invalid handle | `handle`=invalid value, `audioDelayMs`= 100 | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |05|Call dsSetAudioDelay() again after terminating audio ports | `handle`=valid handle from earlier step, `audioDelayMs`= 100 | dsERR_NOT_INITIALIZED | Should Pass |
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
 * **Dependencies:** Audio device should be connected and working properly.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Retrieve the audio delay offset using dsGetAudioDelayOffset() | `handle`=acquired from previous step | dsERR_NONE and a valid audio delay offset value (platform specific) | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsGetAudioDelayOffset() without initializing audio ports | `handle`=any value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsGetAudioDelayOffset() using an invalid handle | `handle`=invalid value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |05|Call dsGetAudioDelayOffset() again after terminating audio ports | `handle`=valid handle from earlier step | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Set an audio delay offset using dsSetAudioDelayOffset() | `handle`=acquired from previous step, `audioDelayOffsetMs`= 100 | dsERR_NONE | Should Pass |
 * |04|Retrieve the set audio delay offset using dsGetAudioDelayOffset() | `handle`=acquired from previous step | dsERR_NONE and audioDelayOffsetMs should match the value set | Should Pass |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsSetAudioDelayOffset() without initializing audio ports | `handle`=any value, `audioDelayOffsetMs`= 100 | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsSetAudioDelayOffset() using an invalid handle | `handle`=invalid value, `audioDelayOffsetMs`= 100 | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |05|Call dsSetAudioDelayOffset() again after terminating audio ports | `handle`=valid handle from earlier step, `audioDelayOffsetMs`= 100 | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Set the Audio ATMOS output mode to enabled using dsSetAudioAtmosOutputMode() | `handle`=acquired from previous step, `enable`=true | dsERR_NONE | Should Pass |
 * |04|Set the Audio ATMOS output mode to disabled using dsSetAudioAtmosOutputMode() | `handle`=acquired from previous step, `enable`=false | dsERR_NONE | Should Pass |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsSetAudioAtmosOutputMode() without initializing audio ports | `handle`=any value, `enable`=true | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsSetAudioAtmosOutputMode() using an invalid handle | `handle`=invalid value, `enable`=true | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |05|Call dsSetAudioAtmosOutputMode() again after terminating audio ports | `handle`=valid handle from earlier step, `enable`=true | dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might be challenging as they require specific platform conditions.
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
 * **Dependencies:** Audio device should be connected and working properly.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Get the ATMOS capability using dsGetSinkDeviceAtmosCapability() | `handle`=acquired from previous step | dsERR_NONE and a valid capability value from dsATMOSCapability_t | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsGetSinkDeviceAtmosCapability() without initializing audio ports | `handle`=any value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsGetSinkDeviceAtmosCapability() using an invalid handle | `handle`=invalid value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |05|Call dsGetSinkDeviceAtmosCapability() again after terminating audio ports | `handle`=valid handle from earlier step | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Get the loop-through status using dsIsAudioLoopThru() | `handle`=acquired from previous step | dsERR_NONE and a valid boolean value (true or false) for loopThru | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsIsAudioLoopThru() without initializing audio ports | `handle`=any value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsIsAudioLoopThru() using an invalid handle | `handle`=invalid value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |05|Call dsIsAudioLoopThru() again after terminating audio ports | `handle`=valid handle from earlier step | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Get the mute status using dsIsAudioMute() | `handle`=acquired from previous step | dsERR_NONE and a valid boolean value (true or false) for muted | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsIsAudioMute() without initializing audio ports | `handle`=any value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsIsAudioMute() using an invalid handle | `handle`=invalid value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |05|Call dsIsAudioMute() again after terminating audio ports | `handle`=valid handle from earlier step | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Get the enable status using dsIsAudioPortEnabled() | `handle`=acquired from previous step | dsERR_NONE and a valid boolean value (true or false) for enabled | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsIsAudioPortEnabled() without initializing audio ports | `handle`=any value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsIsAudioPortEnabled() using an invalid handle | `handle`=invalid value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |05|Call dsIsAudioPortEnabled() again after terminating audio ports | `handle`=valid handle from earlier step | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Enable the audio port using dsEnableAudioPort() | `handle`=acquired from previous step, `enabled`=true | dsERR_NONE | Should Pass |
 * |04|Disable the audio port using dsEnableAudioPort() | `handle`=acquired from previous step, `enabled`=false | dsERR_NONE | Should Pass |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsEnableAudioPort() without initializing audio ports | `handle`=any value, `enabled`=true | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsEnableAudioPort() using an invalid handle | `handle`=invalid value, `enabled`=true | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |05|Call dsEnableAudioPort() again after terminating audio ports | `handle`=valid handle from earlier step, `enabled`=false | dsERR_NOT_INITIALIZED | Should Pass |
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
 * **Dependencies:** Audio device should be connected and MS12 features are supported.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Enable a specific MS12 feature using dsEnableMS12Config() | `handle`=acquired from previous step, `feature`=Any supported feature, `enable`=true | dsERR_NONE | Should Pass |
 * |04|Disable the same MS12 feature using dsEnableMS12Config() | `handle`=acquired from previous step, `feature`=The feature from the previous step, `enable`=false | dsERR_NONE | Should Pass |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsEnableMS12Config() without initializing audio ports | `handle`=any value, `feature`=Any value, `enable`=true | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsEnableMS12Config() using an invalid handle | `handle`=invalid value, `feature`=Any valid feature, `enable`=true | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsEnableMS12Config() using an unsupported feature (if applicable) | `handle`=valid value, `feature`=Unsupported feature, `enable`=true | dsERR_OPERATION_NOT_SUPPORTED | Only if the platform has unsupported features |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |06|Call dsEnableMS12Config() again after terminating audio ports | `handle`=valid handle from earlier step, `feature`=Any valid feature, `enable`=false | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Enable the LE feature using dsEnableLEConfig() | `handle`=acquired from previous step, `enable`=true | dsERR_NONE | Should Pass |
 * |04|Disable the LE feature using dsEnableLEConfig() | `handle`=acquired from previous step, `enable`=false | dsERR_NONE | Should Pass |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsEnableLEConfig() without initializing audio ports | `handle`=any value, `enable`=true | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsEnableLEConfig() using an invalid handle | `handle`=invalid value, `enable`=true | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |05|Call dsEnableLEConfig() again after terminating audio ports | `handle`=valid handle from earlier step, `enable`=false | dsERR_NOT_INITIALIZED | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Enable the LE feature using dsEnableLEConfig() | `handle`=acquired from previous step, `enable`=true | dsERR_NONE | Should Pass |
 * |04|Retrieve the LE feature status using dsGetLEConfig() | `handle`=acquired from previous step | dsERR_NONE and `enable`=true | Should Pass |
 * |05|Disable the LE feature using dsEnableLEConfig() | `handle`=acquired from previous step, `enable`=false | dsERR_NONE | Should Pass |
 * |06|Retrieve the LE feature status again using dsGetLEConfig() | `handle`=acquired from previous step | dsERR_NONE and `enable`=false | Should Pass |
 * |07|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsGetLEConfig() without initializing audio ports | `handle`=any value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsGetLEConfig() using an invalid handle | `handle`=invalid value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |05|Call dsGetLEConfig() again after terminating audio ports | `handle`=valid handle from earlier step | dsERR_NOT_INITIALIZED | Should Pass |
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
 * **Dependencies:** Audio device should be connected and MS12 audio profile features are supported.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Set a valid MS12 audio profile using dsSetMS12AudioProfile() | `handle`=acquired from previous step, `profile`=any valid value from _dsMS12AudioProfileList_t | dsERR_NONE | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsSetMS12AudioProfile() without initializing audio ports | `handle`=any value, `profile`=any value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsSetMS12AudioProfile() using an invalid handle | `handle`=invalid value, `profile`=any value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsSetMS12AudioProfile() using a null profile string | `handle`=valid value, `profile`=NULL | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |06|Call dsSetMS12AudioProfile() again after terminating audio ports | `handle`=valid handle from earlier step, `profile`=any value | dsERR_NOT_INITIALIZED | Should Pass |
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
 * **Dependencies:** Audio device should be connected and audio ducking features are supported.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Set the audio ducking level using dsSetAudioDucking() | `handle`=acquired from previous step, `action`=valid value, `type`=valid value, `level`=any valid value between 0 and 100 | dsERR_NONE | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsSetAudioDucking() without initializing audio ports | `handle`=any value, `action`=valid value, `type`=valid value, `level`=valid value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsSetAudioDucking() using an invalid handle | `handle`=invalid value, `action`=valid value, `type`=valid value, `level`=valid value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsSetAudioDucking() using a value outside the 0-100 range for `level` | `handle`=valid value, `action`=valid value, `type`=valid value, `level`=101 | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |06|Call dsSetAudioDucking() again after terminating audio ports | `handle`=valid handle from earlier step, `action`=valid value, `type`=valid value, `level`=valid value | dsERR_NOT_INITIALIZED | Should Pass |
 * 
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Enable loop-through using dsEnableLoopThru() | `handle`=acquired from previous step, `loopThru`=true | dsERR_NONE | Should Pass |
 * |04|Disable loop-through using dsEnableLoopThru() | `handle`=acquired from previous step, `loopThru`=false | dsERR_NONE | Should Pass |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsEnableLoopThru() without initializing audio ports | `handle`=any value, `loopThru`=true | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsEnableLoopThru() using an invalid handle | `handle`=invalid value, `loopThru`=true | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |05|Call dsEnableLoopThru() again after terminating audio ports | `handle`=valid handle from earlier step, `loopThru`=true | dsERR_NOT_INITIALIZED | Should Pass |
 * 
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Mute the audio using dsSetAudioMute() | `handle`=acquired from previous step, `mute`=true | dsERR_NONE | Should Pass |
 * |04|Un-mute the audio using dsSetAudioMute() | `handle`=acquired from previous step, `mute`=false | dsERR_NONE | Should Pass |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsSetAudioMute() without initializing audio ports | `handle`=any value, `mute`=true | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsSetAudioMute() using an invalid handle | `handle`=invalid value, `mute`=true | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |05|Call dsSetAudioMute() again after terminating audio ports | `handle`=valid handle from earlier step, `mute`=true | dsERR_NOT_INITIALIZED | Should Pass |
 * 
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
 * **Dependencies:** Audio device should be connected and should have a known Dolby MS11 Multistream Decode support status.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Check for MS11 decode support using dsIsAudioMSDecode() | `handle`=acquired from previous step, `HasMS11Decode`=pointer to a bool variable | dsERR_NONE and the returned boolean value should match the known status | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsIsAudioMSDecode() without initializing audio ports | `handle`=any value, `HasMS11Decode`=NULL | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsIsAudioMSDecode() using an invalid handle | `handle`=invalid value, `HasMS11Decode`=pointer to a bool variable | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |05|Call dsIsAudioMSDecode() again after terminating audio ports | `handle`=valid handle from earlier step, `HasMS11Decode`=pointer to a bool variable | dsERR_NOT_INITIALIZED | Should Pass |
 * 
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
 * **Dependencies:** Audio device should be connected and should have a known Dolby MS12 Multistream Decode support status.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Check for MS12 decode support using dsIsAudioMS12Decode() | `handle`=acquired from previous step, `hasMS12Decode`=pointer to a bool variable | dsERR_NONE and the returned boolean value should match the known status | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsIsAudioMS12Decode() without initializing audio ports | `handle`=any value, `hasMS12Decode`=NULL | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsIsAudioMS12Decode() using an invalid handle | `handle`=invalid value, `hasMS12Decode`=pointer to a bool variable | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |05|Call dsIsAudioMS12Decode() again after terminating audio ports | `handle`=valid handle from earlier step, `hasMS12Decode`=pointer to a bool variable | dsERR_NOT_INITIALIZED | Should Pass |
 * 
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
 * **Dependencies:** Audio device should be connected and should have a known connection status.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Check audio port connection status using dsAudioOutIsConnected() | `handle`=acquired from previous step, `isConnected`=pointer to a bool variable | dsERR_NONE and the returned boolean value should match the known connection status | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsAudioOutIsConnected() without initializing audio ports | `handle`=any value, `isConnected`=NULL | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsAudioOutIsConnected() using an invalid handle | `handle`=invalid value, `isConnected`=pointer to a bool variable | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |05|Call dsAudioOutIsConnected() again after terminating audio ports | `handle`=valid handle from earlier step, `isConnected`=pointer to a bool variable | dsERR_NOT_INITIALIZED | Should Pass |
 * 
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Register the audio output connect callback using dsAudioOutRegisterConnectCB() | `CBFunc`=test callback function | dsERR_NONE | Should Pass |
 * |03|Simulate an audio output connect event, e.g., plugging in an audio device | | The test callback function should be triggered with the correct status | Ensure the callback behavior matches expected behavior |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsAudioOutRegisterConnectCB() using a NULL callback function | `CBFunc`=NULL | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Register the audio format update callback using dsAudioFormatUpdateRegisterCB() | `cbFun`=test callback function | dsERR_NONE | Should Pass |
 * |03|Simulate an audio format update event, e.g., switching to a different audio format | | The test callback function should be triggered with the correct status | Ensure the callback behavior matches expected behavior |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsAudioFormatUpdateRegisterCB() using a NULL callback function | `cbFun`=NULL | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Fetch audio capabilities using dsGetAudioCapabilities() | `handle`=acquired from previous step, `capabilities`=pointer to an int variable | dsERR_NONE and the returned capabilities value should match known capabilities for the platform | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsGetAudioCapabilities() without initializing audio ports | `handle`=any value, `capabilities`=NULL | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsGetAudioCapabilities() using an invalid handle | `handle`=invalid value, `capabilities`=pointer to an int variable | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |05|Call dsGetAudioCapabilities() again after terminating audio ports | `handle`=valid handle from earlier step, `capabilities`=pointer to an int variable | dsERR_NOT_INITIALIZED | Should Pass |
 * 
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Fetch MS12 capabilities using dsGetMS12Capabilities() | `handle`=acquired from previous step, `capabilities`=pointer to an int variable | dsERR_NONE and the returned capabilities value should match known MS12 capabilities for the platform | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsGetMS12Capabilities() without initializing audio ports | `handle`=any value, `capabilities`=NULL | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsGetMS12Capabilities() using an invalid handle | `handle`=invalid value, `capabilities`=pointer to an int variable | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |05|Call dsGetMS12Capabilities() again after terminating audio ports | `handle`=valid handle from earlier step, `capabilities`=pointer to an int variable | dsERR_NOT_INITIALIZED | Should Pass |
 * 
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
 * **Dependencies:** Audio device should be connected and support dialog enhancement functionalities.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Reset dialog enhancement using dsResetDialogEnhancement() | `handle`=acquired from previous step | dsERR_NONE | Should Pass |
 * |04|Verify if the dialog enhancement setting has been reset to platform-specific default value | | Matches the expected default value for the platform | Manual verification or using a separate API if available |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsResetDialogEnhancement() without initializing audio ports | `handle`=any value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsResetDialogEnhancement() using an invalid handle | `handle`=invalid value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |05|Call dsResetDialogEnhancement() again after terminating audio ports | `handle`=valid handle from earlier step | dsERR_NOT_INITIALIZED | Should Pass |
 * 
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Reset bass enhancer using dsResetBassEnhancer() | `handle`=acquired from previous step | dsERR_NONE | Should Pass |
 * |04|Verify if the bass enhancer setting has been reset to platform-specific default value | | Matches the expected default value for the platform | Manual verification or using a separate API if available |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsResetBassEnhancer() without initializing audio ports | `handle`=any value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsResetBassEnhancer() using an invalid handle | `handle`=invalid value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |05|Call dsResetBassEnhancer() again after terminating audio ports | `handle`=valid handle from earlier step | dsERR_NOT_INITIALIZED | Should Pass |
 * 
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Reset surround virtualizer using dsResetSurroundVirtualizer() | `handle`=acquired from previous step | dsERR_NONE | Should Pass |
 * |04|Verify if the surround virtualizer setting has been reset to platform-specific default value | | Matches the expected default value for the platform | Manual verification or using a separate API if available |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsResetSurroundVirtualizer() without initializing audio ports | `handle`=any value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsResetSurroundVirtualizer() using an invalid handle | `handle`=invalid value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |05|Call dsResetSurroundVirtualizer() again after terminating audio ports | `handle`=valid handle from earlier step | dsERR_NOT_INITIALIZED | Should Pass |
 * 
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Reset Dolby volume leveller using dsResetVolumeLeveller() | `handle`=acquired from previous step | dsERR_NONE | Should Pass |
 * |04|Verify if the Dolby volume leveller setting has been reset to platform-specific default value | | Matches the expected default volume level for the platform | Manual verification or using a separate API if available |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsResetVolumeLeveller() without initializing audio ports | `handle`=any value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsResetVolumeLeveller() using an invalid handle | `handle`=invalid value | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |05|Call dsResetVolumeLeveller() again after terminating audio ports | `handle`=valid handle from earlier step | dsERR_NOT_INITIALIZED | Should Pass |
 * 
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Override MS12 audio profile setting using dsSetMS12AudioProfileSetttingsOverride() | `handle`=acquired from previous step, `profileState`=ADD, `profileName`=valid profile, `profileSettingsName`=valid setting name, `profileSettingValue`=valid setting value | dsERR_NONE | Should Pass |
 * |04|Verify the overridden MS12 audio profile setting | | Setting matches the overridden value | Manual verification or using a separate API if available |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsSetMS12AudioProfileSetttingsOverride() using invalid profileState | `handle`=valid, `profileState`=invalid value, other params=valid | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsSetMS12AudioProfileSetttingsOverride() using invalid profileName | `handle`=valid, `profileName`=invalid value, other params=valid | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsSetMS12AudioProfileSetttingsOverride() using invalid profileSettingsName | `handle`=valid, `profileSettingsName`=invalid value, other params=valid | dsERR_INVALID_PARAM | Should Pass |
 * |06|Call dsSetMS12AudioProfileSetttingsOverride() using invalid profileSettingValue | `handle`=valid, `profileSettingValue`=invalid value, other params=valid | dsERR_INVALID_PARAM | Should Pass |
 * |07|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |08|Call dsSetMS12AudioProfileSetttingsOverride() again after terminating audio ports | `handle`=valid handle from earlier step, other params=valid | dsERR_NOT_INITIALIZED | Should Pass |
 * 
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Enable associated audio mixing feature using dsSetAssociatedAudioMixing() | `handle`=acquired from previous step, `mixing`=true | dsERR_NONE | Should Pass |
 * |04|Verify the associated audio mixing feature is enabled | Use dsGetAssociatedAudioMixing() or equivalent | Mixing feature is enabled | Manual verification or using the API |
 * |05|Disable associated audio mixing feature using dsSetAssociatedAudioMixing() | `handle`=acquired from previous step, `mixing`=false | dsERR_NONE | Should Pass |
 * |06|Verify the associated audio mixing feature is disabled | Use dsGetAssociatedAudioMixing() or equivalent | Mixing feature is disabled | Manual verification or using the API |
 * |07|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsSetAssociatedAudioMixing() without initializing audio ports | `handle`=any value, `mixing`=true | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsSetAssociatedAudioMixing() using invalid handle | `handle`=invalid value, `mixing`=true | dsERR_INVALID_PARAM or dsERR_OPERATION_NOT_SUPPORTED | Should Pass |
 * |04|Enable/Disable associated audio mixing feature in a rapid sequence to test thread safety | Repeatedly toggle `mixing`=true/false | No crashes or unexpected behavior | It tests the thread safety indirectly |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |06|Call dsSetAssociatedAudioMixing() again after terminating audio ports | `handle`=valid handle from earlier step, `mixing`=true | dsERR_NOT_INITIALIZED | Should Pass |
 * 
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
 * **Dependencies:** Audio device should be connected.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Call dsGetAssociatedAudioMixing() to fetch the mixing status | `handle`=acquired from previous step | dsERR_NONE and correct `mixing` value | Should Pass |
 * |04|Toggle the associated audio mixing feature using dsSetAssociatedAudioMixing() | `handle`=acquired from previous step, `mixing`=opposite of previously fetched status | dsERR_NONE | Should Pass |
 * |05|Call dsGetAssociatedAudioMixing() again to validate the updated status | `handle`=acquired from previous step | dsERR_NONE and updated `mixing` value | Should Pass |
 * |06|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsGetAssociatedAudioMixing() without initializing audio ports | `handle`=any value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsGetAssociatedAudioMixing() using an invalid handle | `handle`=invalid value | dsERR_INVALID_PARAM or dsERR_OPERATION_NOT_SUPPORTED | Should Pass |
 * |04|Call dsGetAssociatedAudioMixing() passing NULL as the mixing pointer | `handle`=valid handle from earlier step, `mixing`=NULL | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |06|Call dsGetAssociatedAudioMixing() again after terminating audio ports | `handle`=valid handle from earlier step | dsERR_NOT_INITIALIZED | Should Pass |
 * 
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
 * **Dependencies:** Audio device should be connected.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Set a mixer balance value using dsSetFaderControl() | `handle`=acquired from previous step, `mixerbalance`=-32 | dsERR_NONE | Should Pass |
 * |04|Verify the set value using dsGetFaderControl() or equivalent | | mixerbalance=-32 | Manual verification or using the API |
 * |05|Set another mixer balance value using dsSetFaderControl() | `handle`=acquired from previous step, `mixerbalance`=+32 | dsERR_NONE | Should Pass |
 * |06|Verify the set value using dsGetFaderControl() or equivalent | | mixerbalance=+32 | Manual verification or using the API |
 * |07|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsSetFaderControl() without initializing audio ports | `handle`=any value, `mixerbalance`=any valid value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsSetFaderControl() using an invalid handle | `handle`=invalid value, `mixerbalance`=any valid value | dsERR_INVALID_PARAM or dsERR_OPERATION_NOT_SUPPORTED | Should Pass |
 * |04|Call dsSetFaderControl() with mixer balance value out of valid range | `handle`=valid handle from earlier step, `mixerbalance`=any value outside (-32 to +32) | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |06|Call dsSetFaderControl() again after terminating audio ports | `handle`=valid handle from earlier step, `mixerbalance`=any valid value | dsERR_NOT_INITIALIZED | Should Pass |
 * 
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
 * **Dependencies:** Audio device should be connected.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Set a mixer balance value using dsSetFaderControl() | `handle`=acquired from previous step, `mixerbalance`=-32 | dsERR_NONE | Should Pass |
 * |04|Retrieve the set mixer balance value using dsGetFaderControl() | `handle`=acquired from previous step | dsERR_NONE and `mixerbalance`=-32 | Should Pass |
 * |05|Set another mixer balance value using dsSetFaderControl() | `handle`=acquired from previous step, `mixerbalance`=+32 | dsERR_NONE | Should Pass |
 * |06|Retrieve the updated mixer balance value using dsGetFaderControl() | `handle`=acquired from previous step | dsERR_NONE and `mixerbalance`=+32 | Should Pass |
 * |07|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsGetFaderControl() without initializing audio ports | `handle`=any value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsGetFaderControl() using an invalid handle | `handle`=invalid value | dsERR_INVALID_PARAM or dsERR_OPERATION_NOT_SUPPORTED | Should Pass |
 * |04|Call dsGetFaderControl() passing NULL as the mixerbalance pointer | `handle`=valid handle from earlier step, `mixerbalance`=NULL | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |06|Call dsGetFaderControl() again after terminating audio ports | `handle`=valid handle from earlier step | dsERR_NOT_INITIALIZED | Should Pass |
 * 
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Set an AC4 primary language using dsSetPrimaryLanguage() | `handle`=acquired from previous step, `pLang`="ENG" | dsERR_NONE | Should Pass |
 * |04|Retrieve the set language using dsGetPrimaryLanguage() or equivalent | `handle`=acquired from previous step | dsERR_NONE and language="ENG" | Manual verification or using the API |
 * |05|Set another AC4 primary language using dsSetPrimaryLanguage() | `handle`=acquired from previous step, `pLang`="FRE" | dsERR_NONE | Should Pass |
 * |06|Retrieve the updated language using dsGetPrimaryLanguage() or equivalent | `handle`=acquired from previous step | dsERR_NONE and language="FRE" | Manual verification or using the API |
 * |07|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsSetPrimaryLanguage() without initializing audio ports | `handle`=any value, `pLang`="ENG" | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsSetPrimaryLanguage() using an invalid handle | `handle`=invalid value, `pLang`="ENG" | dsERR_INVALID_PARAM or dsERR_OPERATION_NOT_SUPPORTED | Should Pass |
 * |04|Call dsSetPrimaryLanguage() passing NULL as the language pointer | `handle`=valid handle from earlier step, `pLang`=NULL | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsSetPrimaryLanguage() passing an unsupported language code | `handle`=valid handle from earlier step, `pLang`="XYZ" | dsERR_INVALID_PARAM or dsERR_OPERATION_NOT_SUPPORTED | Should Pass |
 * |06|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |07|Call dsSetPrimaryLanguage() again after terminating audio ports | `handle`=valid handle from earlier step, `pLang`="ENG" | dsERR_NOT_INITIALIZED | Should Pass |
 * 
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
 * **Dependencies:** Audio device should be connected.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Set an AC4 primary language using dsSetPrimaryLanguage() | `handle`=acquired from previous step, `pLang`="ENG" | dsERR_NONE | Should Pass |
 * |04|Retrieve the set language using dsGetPrimaryLanguage() | `handle`=acquired from previous step | dsERR_NONE and `pLang`="ENG" | Should Pass |
 * |05|Set another AC4 primary language using dsSetPrimaryLanguage() | `handle`=acquired from previous step, `pLang`="FRE" | dsERR_NONE | Should Pass |
 * |06|Retrieve the updated language using dsGetPrimaryLanguage() | `handle`=acquired from previous step | dsERR_NONE and `pLang`="FRE" | Should Pass |
 * |07|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsGetPrimaryLanguage() without initializing audio ports | `handle`=any value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsGetPrimaryLanguage() using an invalid handle | `handle`=invalid value | dsERR_INVALID_PARAM or dsERR_OPERATION_NOT_SUPPORTED | Should Pass |
 * |04|Call dsGetPrimaryLanguage() passing NULL as the language pointer | `handle`=valid handle from earlier step, `pLang`=NULL | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |06|Call dsGetPrimaryLanguage() again after terminating audio ports | `handle`=valid handle from earlier step | dsERR_NOT_INITIALIZED | Should Pass |
 * 
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
 * **Dependencies:** Audio device should be connected.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Set an AC4 secondary language using dsSetSecondaryLanguage() | `handle`=acquired from previous step, `sLang`="ENG" | dsERR_NONE | Should Pass |
 * |04|Retrieve the set language using dsGetSecondaryLanguage() or equivalent | `handle`=acquired from previous step | dsERR_NONE and `sLang`="ENG" | Manual verification or using the API |
 * |05|Set another AC4 secondary language using dsSetSecondaryLanguage() | `handle`=acquired from previous step, `sLang`="FRE" | dsERR_NONE | Should Pass |
 * |06|Retrieve the updated language using dsGetSecondaryLanguage() or equivalent | `handle`=acquired from previous step | dsERR_NONE and `sLang`="FRE" | Manual verification or using the API |
 * |07|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsSetSecondaryLanguage() without initializing audio ports | `handle`=any value, `sLang`="ENG" | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsSetSecondaryLanguage() using an invalid handle | `handle`=invalid value, `sLang`="ENG" | dsERR_INVALID_PARAM or dsERR_OPERATION_NOT_SUPPORTED | Should Pass |
 * |04|Call dsSetSecondaryLanguage() passing NULL as the language pointer | `handle`=valid handle from earlier step, `sLang`=NULL | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsSetSecondaryLanguage() passing an unsupported language code | `handle`=valid handle from earlier step, `sLang`="XYZ" | dsERR_INVALID_PARAM or dsERR_OPERATION_NOT_SUPPORTED | Should Pass |
 * |06|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |07|Call dsSetSecondaryLanguage() again after terminating audio ports | `handle`=valid handle from earlier step, `sLang`="ENG" | dsERR_NOT_INITIALIZED | Should Pass |
 * 
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
 * **Dependencies:** Audio device should be connected.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAudioPort() to request an available output audio port handle | | dsERR_NONE and a valid handle | Should Pass |
 * |03|Set an AC4 secondary language using dsSetSecondaryLanguage() | `handle`=acquired from previous step, `sLang`="ENG" | dsERR_NONE | Should Pass |
 * |04|Retrieve the set language using dsGetSecondaryLanguage() | `handle`=acquired from previous step | dsERR_NONE and `sLang`="ENG" | Should Pass |
 * |05|Set another AC4 secondary language using dsSetSecondaryLanguage() | `handle`=acquired from previous step, `sLang`="FRE" | dsERR_NONE | Should Pass |
 * |06|Retrieve the updated language using dsGetSecondaryLanguage() | `handle`=acquired from previous step | dsERR_NONE and `sLang`="FRE" | Should Pass |
 * |07|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |01|Call dsGetSecondaryLanguage() without initializing audio ports | `handle`=any value | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsGetSecondaryLanguage() using an invalid handle | `handle`=invalid value | dsERR_INVALID_PARAM or dsERR_OPERATION_NOT_SUPPORTED | Should Pass |
 * |04|Call dsGetSecondaryLanguage() passing NULL as the language pointer | `handle`=valid handle from earlier step, `sLang`=NULL | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
 * |06|Call dsGetSecondaryLanguage() again after terminating audio ports | `handle`=valid handle from earlier step | dsERR_NOT_INITIALIZED | Should Pass |
 * 
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
 * |01|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |02|Fetch the audio HDMI ARC port ID using dsGetHDMIARCPortId() | | dsERR_NONE and a valid port ID | Should Pass |
 * |03|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
 * |02|Call dsAudioPortInit() to initialize audio ports | | dsERR_NONE | Should Pass |
 * |03|Call dsGetHDMIARCPortId() passing NULL as the port ID pointer | `portId`=NULL | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsAudioPortTerm() to terminate audio ports | | dsERR_NONE | Should Pass |
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
