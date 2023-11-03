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
* @file TODO: test_l1_dsVideoPort.c
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
 * dsAudioPort system has not been initialized.
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio port system | | dsERR_NONE | Should Pass |
 * |02|Call dsAudioPortTerm() - Terminate audio port system | | dsERR_NONE | Should Pass |
 * |03|Call dsAudioPortInit() - Reinitialize audio port system | | dsERR_NONE | Should Pass |
 * |04|Call dsAudioPortTerm() - Re-terminate audio port system | | dsERR_NONE | Should Pass |
 * 
 */
void test_l1_dsVideoPort_positive_dsVideoPortInit (void)
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
 * Varying depending on the specific test.
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio port system | | dsERR_NONE | Should Pass |
 * |02|Call dsAudioPortInit() again without terminating the first initialization | | dsERR_ALREADY_INITIALIZED | Should Fail |
 * |03|Call dsAudioPortTerm() without initializing system first | | dsERR_NOT_INITIALIZED | Should Fail |
 * 
 * **Additional Notes:**@n
 * - Simulating `dsERR_RESOURCE_NOT_AVAILABLE` might be challenging in a controlled environment as it involves controlling the system's available resources.
 * - Simulating `dsERR_GENERAL` can also be difficult because it's an undefined platform error. The specifics might vary depending on the platform and the exact nature of the error.
 */
void test_l1_dsVideoPort_negative_dsVideoPortInit (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsAudioPortTerm() returns correct error codes during positive scenarios
 * 
 * **Test Group ID:** Basic: 02@n
 * **Test Case ID:** 001@n
 * 
 * **Pre-Conditions:**@n
 * dsAudioPort system has been initialized.
 * 
 * **Dependencies:** dsAudioPortInit()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsAudioPortInit() - Initialize audio port system | | dsERR_NONE | Should Pass |
 * |02|Call dsAudioPortTerm() - Terminate audio port system | | dsERR_NONE | Should Pass |
 * |03|Call dsAudioPortInit() - Reinitialize audio port system | | dsERR_NONE | Should Pass |
 * |04|Call dsAudioPortTerm() - Re-terminate audio port system | | dsERR_NONE | Should Pass |
 * 
 */
void test_l1_dsVideoPort_positive_dsVideoPortTerm (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsAudioPortTerm() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 02@n
 * **Test Case ID:** 002@n
 * 
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsAudioPortInit()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsAudioPortTerm() without prior initialization | | dsERR_NOT_INITIALIZED | Should Fail |
 * |02|Call dsAudioPortInit() - Initialize audio port system | | dsERR_NONE | Should Pass |
 * |03|Call dsAudioPortTerm() - Terminate audio port system | | dsERR_NONE | Should Pass |
 * |04|Call dsAudioPortTerm() again | | dsERR_NOT_INITIALIZED | Should Fail |
 * 
 * **Additional Notes:**@n
 * - Simulating the system in such a way to get `dsERR_GENERAL` from dsAudioPortTerm() might be challenging, as it relates to an undefined platform error.
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
 * **Pre-Conditions:**@n
 * - System should be initialized properly.
 * 
 * **Dependencies:** dsVideoPortInit()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | N/A | dsERR_NONE | Should Pass |
 * |02|Loop through all valid video port enums and call dsGetVideoPort() | [Valid enum name] | Either a valid handle or dsERR_OPERATION_NOT_SUPPORTED | Should Pass for available ports and Fail for unsupported ones |
 * |03|Call dsVideoPortTerm() - Terminate video port system | N/A | dsERR_NONE | Should Pass |
 * 
 * **Additional Notes:**@n
 * - Only loop up to dsVIDEOPORT_TYPE_INTERNAL and not till dsVIDEOPORT_TYPE_MAX as the latter is out of range.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetVideoPort() without prior initialization | dsVIDEOPORT_TYPE_HDMI, 0 | dsERR_NOT_INITIALIZED | Should Fail |
 * |02|Call dsVideoPortInit() - Initialize video port system | N/A | dsERR_NONE | Should Pass |
 * |03|Call dsGetVideoPort() with invalid video port type (out of range) | dsVIDEOPORT_TYPE_MAX | dsERR_INVALID_PARAM | Should Fail |
 * |04|Call dsGetVideoPort() with a negative index | dsVIDEOPORT_TYPE_HDMI, -1 | dsERR_INVALID_PARAM | Should Fail |
 * |05|Call dsGetVideoPort() with a very high index (assumed out of range) | dsVIDEOPORT_TYPE_HDMI, 9999 | dsERR_INVALID_PARAM | Should Fail |
 * |06|Call dsVideoPortTerm() - Terminate video port system | N/A | dsERR_NONE | Should Pass |
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
 * **Pre-Conditions:**@n
 * - System should be initialized properly.
 * 
 * **Dependencies:** dsVideoPortInit(), dsGetVideoPort()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() - Initialize video port system | N/A | dsERR_NONE | Should Pass |
 * |02|Loop through all valid video port enums and get handle via dsGetVideoPort() | [Valid enum name] | Either dsERR_NONE or dsERR_OPERATION_NOT_SUPPORTED | Should Pass for available ports |
 * |03|For each successful handle from step 02, check the enabled status with dsIsVideoPortEnabled() | Handle from dsGetVideoPort() | dsERR_NONE with corresponding enabled status | Should Pass for available ports, this step should be executed within the same loop as step 02 |
 * |04|Call dsVideoPortTerm() - Terminate video port system | N/A | dsERR_NONE | Should Pass |
 * 
 * **Additional Notes:**@n
 * - Only loop up to dsVIDEOPORT_TYPE_INTERNAL and not till dsVIDEOPORT_TYPE_MAX as the latter is out of range.
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
 * **Pre-Conditions:**@n
 * - System should be initialized properly.
 * 
 * **Dependencies:** dsVideoPortInit(), dsGetVideoPort()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsIsVideoPortEnabled() without prior initialization and any handle | Random/Invalid handle | dsERR_NOT_INITIALIZED | Should Fail |
 * |02|Call dsVideoPortInit() - Initialize video port system | N/A | dsERR_NONE | Should Pass |
 * |03|Call dsGetVideoPort() for HDMI Input to get a valid handle | dsVIDEOPORT_TYPE_HDMI_INPUT, Index 0 | dsERR_NONE with handle | Should Pass |
 * |04|Pass an invalid/random handle to dsIsVideoPortEnabled() | Random/Invalid handle | dsERR_INVALID_PARAM | Should Fail |
 * |05|Pass a null pointer for the `enabled` parameter to dsIsVideoPortEnabled() | Valid handle from step 03, NULL pointer | dsERR_INVALID_PARAM | Should Fail |
 * |06|Call dsVideoPortTerm() - Terminate video port system | N/A | dsERR_NONE | Should Pass |
 * |07|After termination, call dsIsVideoPortEnabled() with the handle from step 03 | Handle from step 03 | dsERR_NOT_INITIALIZED | Should Fail |
 * 
 * **Additional Notes:**@n
 * - The test should be careful while handling null pointers and invalid handles.
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
 * - System should be initialized properly.
 * 
 * **Dependencies:** dsVideoPortInit(), dsGetVideoPort()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoPortInit() to initialize video port system | N/A | dsERR_NONE | Should Pass |
 * |02|Iterate through valid video port enums and retrieve their handles using dsGetVideoPort() | [Valid enum name] | dsERR_NONE with handle | Loop through each enum |
 * |03|For each handle from step 02, call dsIsDisplayConnected() | Handle from step 02 | dsERR_NONE and either `true` or `false` for the `connected` flag | Should happen in the same loop as step 02 |
 * |04|Call dsVideoPortTerm() to terminate video port system | N/A | dsERR_NONE | Should Pass |
 * 
 * **Additional Notes:**@n
 * - Depending on the setup, the function might return either `true` or `false` for the `connected` flag, both are valid.
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
 * **Pre-Conditions:**@n
 * - System should be initialized properly.
 * 
 * **Dependencies:** dsVideoPortInit(), dsGetVideoPort()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsIsDisplayConnected() without any initialization | Random/Invalid handle | dsERR_NOT_INITIALIZED | Should Fail |
 * |02|Call dsVideoPortInit() to initialize the video port system | N/A | dsERR_NONE | Should Pass |
 * |03|Retrieve a valid handle for dsVIDEOPORT_TYPE_HDMI_INPUT using dsGetVideoPort() | dsVIDEOPORT_TYPE_HDMI_INPUT, Index 0 | dsERR_NONE with handle | Should Pass |
 * |04|Pass an invalid/random handle to dsIsDisplayConnected() | Random/Invalid handle | dsERR_INVALID_PARAM | Should Fail |
 * |05|Pass a null pointer for the `connected` parameter to dsIsDisplayConnected() | Valid handle from step 03, NULL pointer | dsERR_INVALID_PARAM | Should Fail |
 * |06|Call dsVideoPortTerm() to terminate the video port system | N/A | dsERR_NONE | Should Pass |
 * |07|After termination, call dsIsDisplayConnected() with the handle from step 03 | Handle from step 03 | dsERR_NOT_INITIALIZED | Should Fail |
 * 
 * **Additional Notes:**@n
 * - The test should be careful while handling null pointers and invalid handles.
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
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * - A valid video port handle is obtained via dsGetVideoPort().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsIsDisplaySurround() with a valid handle|Handle from dsGetVideoPort()|dsERR_NONE|Should Pass|
 * |02|Call dsIsDisplaySurround() again with the same valid handle|Handle from dsGetVideoPort()|dsERR_NONE|Should Pass|
 * |03|Verify the first result of dsIsDisplaySurround()|Result from step 01|True or False|Should match with the capability of the connected display|
 * |04|Verify the second result of dsIsDisplaySurround()|Result from step 02|True or False|Should match with the capability of the connected display|
 * |05|Compare the results of dsIsDisplaySurround() from step 3 and step 4|Results from step 3 and step 4|Results should be the same|Consistency check|
 * |06|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - The results from dsIsDisplaySurround() should remain consistent across multiple calls for the same video port.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * - System should be initialized properly.
 * 
 * **Dependencies:** dsVideoPortInit(), dsGetVideoPort()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsIsDisplaySurround() without any initialization | Random/Invalid handle | dsERR_NOT_INITIALIZED | Should Fail |
 * |02|Call dsVideoPortInit() to initialize the video port system | N/A | dsERR_NONE | Should Pass |
 * |03|Retrieve a valid handle for dsVIDEOPORT_TYPE_HDMI_INPUT using dsGetVideoPort() | dsVIDEOPORT_TYPE_HDMI_INPUT, Index 0 | dsERR_NONE with handle | Should Pass |
 * |04|Pass an invalid/random handle to dsIsDisplaySurround() | Random/Invalid handle | dsERR_INVALID_PARAM | Should Fail |
 * |05|Pass a null pointer for the `surround` parameter to dsIsDisplaySurround() | Valid handle from step 03, NULL pointer | dsERR_INVALID_PARAM | Should Fail |
 * |06|Call dsVideoPortTerm() to terminate the video port system | N/A | dsERR_NONE | Should Pass |
 * |07|After termination, call dsIsDisplaySurround() with the handle from step 03 | Handle from step 03 | dsERR_NOT_INITIALIZED | Should Fail |
 * 
 * **Additional Notes:**@n
 * - The test should be careful while handling null pointers and invalid handles.
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
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * - A valid video port handle is obtained via dsGetVideoPort().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetSurroundMode() with a valid handle|Handle from dsGetVideoPort()|dsERR_NONE|Should Pass|
 * |02|Call dsGetSurroundMode() again with the same valid handle|Handle from dsGetVideoPort()|dsERR_NONE|Should Pass|
 * |03|Verify the first result of dsGetSurroundMode()|Surround mode from step 01|Value from ::dsSURROUNDMode_t|Should match with the surround mode of the video port|
 * |04|Verify the second result of dsGetSurroundMode()|Surround mode from step 02|Value from ::dsSURROUNDMode_t|Should match with the surround mode of the video port|
 * |05|Compare the results of dsGetSurroundMode() from step 3 and step 4|Results from step 3 and step 4|Results should be the same|Consistency check|
 * |06|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - The surround mode results from dsGetSurroundMode() should remain consistent across multiple calls for the same video port.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit() and dsGetVideoPort()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetSurroundMode() without prior initialization or without valid handle| |dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Get a valid handle for video port using dsVIDEOPORT_TYPE_HDMI_INPUT|dsVIDEOPORT_TYPE_HDMI_INPUT|dsERR_NONE|Should Pass|
 * |04|Call dsGetSurroundMode() with an invalid handle|Invalid Handle|dsERR_INVALID_PARAM|Should Fail|
 * |05|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * |06|Call dsGetSurroundMode() after termination|Handle from step 03|dsERR_NOT_INITIALIZED|Should Fail|
 * 
 * **Additional Notes:**@n
 * - Handle validation and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
 */
void test_l1_dsVideoPort_negative_dsGetSurroundMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Positive Test Scenarios for dsVideoFormatUpdateRegisterCB()
 * 
 * **Test Group ID:** Basic: 04@p
 * **Test Case ID:** 004@p
 * 
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Define a valid callback function|Sample callback function|N/A|Should be a valid function|
 * |02|Register the defined callback using dsVideoFormatUpdateRegisterCB()|Callback function from step 01|dsERR_NONE|Should Pass|
 * |03|Verify if the callback gets triggered upon Video Format update events|Trigger Video Format update (not part of this API)|Callback should be called|Functional check of the registered callback|
 * |04|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - Step 3's trigger might be platform or environment specific.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsVideoFormatUpdateRegisterCB() without prior initialization|NULL or Valid callback|dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Call dsVideoFormatUpdateRegisterCB() with an invalid callback (NULL)|NULL|dsERR_INVALID_PARAM|Should Fail|
 * |04|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * |05|Call dsVideoFormatUpdateRegisterCB() after termination|Valid Callback|dsERR_NOT_INITIALIZED|Should Fail|
 * 
 * **Additional Notes:**@n
 * - Handle validation and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
 */
void test_l1_dsVideoPort_negative_dsVideoFormatUpdateRegisterCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Positive Test Scenarios for dsIsVideoPortActive()
 * 
 * **Test Group ID:** Basic: 05@p
 * **Test Case ID:** 005@p
 * 
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |02|Obtain a valid video port handle using dsGetVideoPort()|[Valid enum name]|Valid handle|Should return a handle to a video port|
 * |03|Check if the video port is active using dsIsVideoPortActive()|Handle from step 02|dsERR_NONE|API should return the active status of the video port|
 * |04|Call dsIsVideoPortActive() again with the handle from step 02|Handle from step 02|Same active status as step 03|Multiple calls should return consistent results|
 * |05|Compare the returned active statuses from step 03 and step 04|Results from step 03 and 04|They should match|Ensuring consistent results|
 * |06|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - Step 3's result might be environment or setup specific. The test might need adjustment depending on the current setup.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit(), dsGetVideoPort()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsIsVideoPortActive() without prior initialization|NULL or Valid active pointer|dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Call dsIsVideoPortActive() with an invalid handle|Invalid handle|dsERR_INVALID_PARAM|Should Fail|
 * |04|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * |05|Call dsIsVideoPortActive() after termination|Valid handle|dsERR_NOT_INITIALIZED|Should Fail|
 * 
 * **Additional Notes:**@n
 * - Handle validation and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * - dsIsDTCPEnabled()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |02|Obtain a valid video port handle using dsGetVideoPort()|[Valid enum name]|Valid handle|Should return a handle to a video port|
 * |03|Enable the DTCP for the video port using dsEnableDTCP()|Handle from step 02, true|dsERR_NONE or dsERR_OPERATION_NOT_SUPPORTED|API should either successfully enable DTCP or indicate that the operation isn't supported|
 * |04|If step 03 passed, verify using dsIsDTCPEnabled()|Handle from step 02|DTCP should be enabled| |
 * |05|Disable the DTCP for the video port using dsEnableDTCP()|Handle from step 02, false|dsERR_NONE or dsERR_OPERATION_NOT_SUPPORTED|API should either successfully disable DTCP or indicate that the operation isn't supported|
 * |06|If step 05 passed, verify using dsIsDTCPEnabled()|Handle from step 02|DTCP should be disabled| |
 * |07|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - Step 03 and 05 might fail with dsERR_OPERATION_NOT_SUPPORTED if the connected video port doesn't support DTCP. The subsequent verification step should be skipped in such a case.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit(), dsGetVideoPort()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsEnableDTCP() without prior initialization|NULL or Valid handle, true/false|dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Call dsEnableDTCP() with an invalid handle|Invalid handle, true/false|dsERR_INVALID_PARAM|Should Fail|
 * |04|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * |05|Call dsEnableDTCP() after termination|Valid handle, true/false|dsERR_NOT_INITIALIZED|Should Fail|
 * 
 * **Additional Notes:**@n
 * - Handle validation and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * - dsIsHDCPEnabled()
 * - dsGetHDCPStatus()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |02|Obtain a valid video port handle using dsGetVideoPort()|[Valid enum name]|Valid handle|Should return a handle to a video port|
 * |03|Enable the HDCP for the video port using dsEnableHDCP()|Handle from step 02, true, Valid HDCP key, HDCP_KEY_MAX_SIZE|dsERR_NONE or dsERR_OPERATION_NOT_SUPPORTED|API should either successfully enable HDCP or indicate that the operation isn't supported|
 * |04|If step 03 passed, verify using dsIsHDCPEnabled() and dsGetHDCPStatus()|Handle from step 02|HDCP should be enabled, and status should indicate the correct state| |
 * |05|Disable the HDCP for the video port using dsEnableHDCP()|Handle from step 02, false, Valid HDCP key, HDCP_KEY_MAX_SIZE|dsERR_NONE or dsERR_OPERATION_NOT_SUPPORTED|API should either successfully disable HDCP or indicate that the operation isn't supported|
 * |06|If step 05 passed, verify using dsIsHDCPEnabled()|Handle from step 02|HDCP should be disabled| |
 * |07|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - Step 03 and 05 might fail with dsERR_OPERATION_NOT_SUPPORTED if the connected video port doesn't support HDCP. The subsequent verification step should be skipped in such a case.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit(), dsGetVideoPort()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsEnableHDCP() without prior initialization|NULL or Valid handle, true/false, HDCP Key, HDCP_KEY_MAX_SIZE|dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Call dsEnableHDCP() with an invalid handle|Invalid handle, true/false, HDCP Key, HDCP_KEY_MAX_SIZE|dsERR_INVALID_PARAM|Should Fail|
 * |04|Call dsEnableHDCP() with an invalid HDCP key size|Valid handle, true/false, HDCP Key, Invalid Key Size|dsERR_INVALID_PARAM|Should Fail|
 * |05|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * |06|Call dsEnableHDCP() after termination|Valid handle, true/false, HDCP Key, HDCP_KEY_MAX_SIZE|dsERR_NOT_INITIALIZED|Should Fail|
 * 
 * **Additional Notes:**@n
 * - Handle validation, module initialization checks, and key size validation are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * - dsEnableDTCP()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |02|Obtain a valid video port handle using dsGetVideoPort()|[Valid enum name]|Valid handle|Should return a handle to a video port|
 * |03|Check DTCP status using dsIsDTCPEnabled() before enabling it|Handle from step 02|dsERR_NONE or dsERR_OPERATION_NOT_SUPPORTED, @a false if the operation was successful|API should return that DTCP is not enabled or indicate that the operation isn't supported|
 * |04|Enable the DTCP for the video port using dsEnableDTCP()|Handle from step 02, true|dsERR_NONE or dsERR_OPERATION_NOT_SUPPORTED|API should either successfully enable DTCP or indicate that the operation isn't supported|
 * |05|Check DTCP status using dsIsDTCPEnabled() after enabling it|Handle from step 02|dsERR_NONE and @a true|DTCP should be enabled|
 * |06|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - Step 03 and 04 might fail with dsERR_OPERATION_NOT_SUPPORTED if the connected video port doesn't support DTCP. The subsequent verification step should be skipped in such a case.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit(), dsGetVideoPort()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsIsDTCPEnabled() without prior initialization|NULL or Valid handle|dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Call dsIsDTCPEnabled() with an invalid handle|Invalid handle|dsERR_INVALID_PARAM|Should Fail|
 * |04|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * |05|Call dsIsDTCPEnabled() after termination|Valid handle|dsERR_NOT_INITIALIZED|Should Fail|
 * 
 * **Additional Notes:**@n
 * - Handle validation and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * - dsEnableHDCP()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |02|Obtain a valid video port handle using dsGetVideoPort()|[Valid enum name]|Valid handle|Should return a handle to a video port|
 * |03|Check HDCP status using dsIsHDCPEnabled() before enabling it|Handle from step 02|dsERR_NONE or dsERR_OPERATION_NOT_SUPPORTED, @a false if the operation was successful|API should return that HDCP is not enabled or indicate that the operation isn't supported|
 * |04|Enable the HDCP for the video port using dsEnableHDCP()|Handle from step 02, true, valid HDCP key, valid key size|dsERR_NONE or dsERR_OPERATION_NOT_SUPPORTED|API should either successfully enable HDCP or indicate that the operation isn't supported|
 * |05|Check HDCP status using dsIsHDCPEnabled() after enabling it|Handle from step 02|dsERR_NONE and @a true|HDCP should be enabled|
 * |06|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - Step 03 and 04 might fail with dsERR_OPERATION_NOT_SUPPORTED if the connected video port doesn't support HDCP. The subsequent verification step should be skipped in such a case.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit(), dsGetVideoPort()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsIsHDCPEnabled() without prior initialization|NULL or Valid handle|dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Call dsIsHDCPEnabled() with an invalid handle|Invalid handle|dsERR_INVALID_PARAM|Should Fail|
 * |04|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * |05|Call dsIsHDCPEnabled() after termination|Valid handle|dsERR_NOT_INITIALIZED|Should Fail|
 * 
 * **Additional Notes:**@n
 * - Handle validation and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * - dsIsVideoPortEnabled()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |02|Obtain a valid video port handle using dsGetVideoPort()|[Valid enum name]|Valid handle|Should return a handle to a video port|
 * |03|Enable the video port using dsEnableVideoPort()|Handle from step 02, true|dsERR_NONE|Video port should be enabled|
 * |04|Verify the video port is enabled using dsIsVideoPortEnabled()|Handle from step 02|dsERR_NONE and @a true|Video port should be reported as enabled|
 * |05|Disable the video port using dsEnableVideoPort()|Handle from step 02, false|dsERR_NONE|Video port should be disabled|
 * |06|Verify the video port is disabled using dsIsVideoPortEnabled()|Handle from step 02|dsERR_NONE and @a false|Video port should be reported as disabled|
 * |07|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit(), dsGetVideoPort()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsEnableVideoPort() without prior initialization|NULL or Valid handle, true/false|dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Call dsEnableVideoPort() with an invalid handle|Invalid handle, true/false|dsERR_INVALID_PARAM|Should Fail|
 * |04|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * |05|Call dsEnableVideoPort() after termination|Valid handle, true/false|dsERR_NOT_INITIALIZED|Should Fail|
 * 
 * **Additional Notes:**@n
 * - Handle validation and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * - dsGetResolution()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |02|Obtain a valid video port handle using dsGetVideoPort()|[Valid enum name]|Valid handle|Should return a handle to a video port|
 * |03|Set the video port resolution using dsSetResolution()|Handle from step 02, Valid resolution|dsERR_NONE|Resolution should be set successfully|
 * |04|Verify the video port resolution using dsGetResolution()|Handle from step 02|dsERR_NONE and the set resolution|Resolution should match the one set in step 03|
 * |05|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - It might be helpful to include a set of valid resolutions to use for step 03.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit(), dsGetVideoPort()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsSetResolution() without prior initialization|NULL or Valid handle, Valid resolution|dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Call dsSetResolution() with an invalid handle|Invalid handle, Valid resolution|dsERR_INVALID_PARAM|Should Fail|
 * |04|Call dsSetResolution() with a NULL resolution parameter|Valid handle, NULL|dsERR_INVALID_PARAM|Should Fail|
 * |05|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * |06|Call dsSetResolution() after termination|Valid handle, Valid resolution|dsERR_NOT_INITIALIZED|Should Fail|
 * 
 * **Additional Notes:**@n
 * - Handle validation and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * - dsSetResolution()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |02|Obtain a valid video port handle using dsGetVideoPort()|[Valid enum name]|Valid handle|Should return a handle to a video port|
 * |03|Set a known video port resolution using dsSetResolution()|Handle from step 02, Known resolution|dsERR_NONE|Resolution should be set successfully|
 * |04|Retrieve the video port resolution using dsGetResolution()|Handle from step 02, Pointer to store resolution|dsERR_NONE and the known resolution|Retrieved resolution should match the one set in step 03|
 * |05|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - Step 03 can be repeated with various resolutions to ensure different settings are correctly fetched.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit(), dsGetVideoPort()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetResolution() without prior initialization|NULL or Valid handle, Valid resolution pointer|dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Call dsGetResolution() with an invalid handle|Invalid handle, Valid resolution pointer|dsERR_INVALID_PARAM|Should Fail|
 * |04|Call dsGetResolution() with a NULL resolution pointer|Valid handle, NULL|dsERR_INVALID_PARAM|Should Fail|
 * |05|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * |06|Call dsGetResolution() after termination|Valid handle, Valid resolution pointer|dsERR_NOT_INITIALIZED|Should Fail|
 * 
 * **Additional Notes:**@n
 * - Handle validation and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * - dsIsVideoPortActive()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |02|Obtain a valid video port handle using dsGetVideoPort()|[Valid enum name]|Valid handle|Should return a handle to a video port|
 * |03|Set the video port as active source using dsSetActiveSource()|Handle from step 02|dsERR_NONE|The video port should be set as the active source successfully|
 * |04|Check if the video port is the active source using dsIsVideoPortActive()|Handle from step 02|dsERR_NONE and @a true|The function should confirm the video port is the active source|
 * |05|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - Step 03 can be expanded to test multiple video ports if available.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit(), dsGetVideoPort()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsSetActiveSource() without prior initialization|NULL or Valid handle|dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Call dsSetActiveSource() with an invalid handle|Invalid handle|dsERR_INVALID_PARAM|Should Fail|
 * |04|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * |05|Call dsSetActiveSource() after termination|Valid handle|dsERR_NOT_INITIALIZED|Should Fail|
 * 
 * **Additional Notes:**@n
 * - Handle validation and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
 */
void test_l1_dsVideoPort_negative_dsSetActiveSource (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Positive Test Scenarios for dsRegisterHdcpStatusCallback()
 * 
 * **Test Group ID:** Basic: 14@p
 * **Test Case ID:** 014@p
 * 
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |02|Obtain a valid video port handle using dsGetVideoPort()|[Valid enum name]|Valid handle|Should return a handle to a video port|
 * |03|Register a valid HDCP status change callback using dsRegisterHdcpStatusCallback()|Handle from step 02, Valid callback function|dsERR_NONE|Callback should be registered successfully|
 * |04|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - A valid HDCP status change callback can be a simple function that logs the received HDCP status.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit(), dsGetVideoPort()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsRegisterHdcpStatusCallback() without prior initialization|NULL or Valid handle, Valid callback function|dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Call dsRegisterHdcpStatusCallback() with an invalid handle|Invalid handle, Valid callback function|dsERR_INVALID_PARAM|Should Fail|
 * |04|Call dsRegisterHdcpStatusCallback() with a NULL callback function|Valid handle, NULL callback|dsERR_INVALID_PARAM|Should Fail|
 * |05|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * |06|Call dsRegisterHdcpStatusCallback() after termination|Valid handle, Valid callback function|dsERR_NOT_INITIALIZED|Should Fail|
 * 
 * **Additional Notes:**@n
 * - Handle validation and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |02|Obtain a valid video port handle using dsGetVideoPort()|[Valid enum name]|Valid handle|Should return a handle to a video port|
 * |03|Get the HDCP status of the video port using dsGetHDCPStatus()|Handle from step 02, Valid HDCP status pointer|dsERR_NONE|The status should be successfully fetched and stored in the given pointer|
 * |04|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - A valid HDCP status pointer can be a simple pointer pointing to an HDCP status variable.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
 */
void test_l1_dsVideoPort_positive_dsGetHDCPStatus (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Negative Test Scenarios for dsGetHDCPStatus()
 * 
 * **Test Group ID:** Basic: 15@n
 * **Test Case ID:** 015@n
 * 
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit(), dsGetVideoPort()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetHDCPStatus() without prior initialization|NULL or Valid handle, Valid HDCP status pointer|dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Call dsGetHDCPStatus() with an invalid handle|Invalid handle, Valid HDCP status pointer|dsERR_INVALID_PARAM|Should Fail|
 * |04|Call dsGetHDCPStatus() with a NULL HDCP status pointer|Valid handle, NULL HDCP status pointer|dsERR_INVALID_PARAM|Should Fail|
 * |05|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * |06|Call dsGetHDCPStatus() after termination|Valid handle, Valid HDCP status pointer|dsERR_NOT_INITIALIZED|Should Fail|
 * 
 * **Additional Notes:**@n
 * - Handle validation, NULL pointer checks, and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |02|Obtain a valid video port handle using dsGetVideoPort()|[Valid enum name]|Valid handle|Should return a handle to a video port|
 * |03|Get the HDCP protocol version using dsGetHDCPProtocol()|Handle from step 02, Valid HDCP protocol version pointer|dsERR_NONE|The HDCP protocol version should be successfully fetched and stored in the given pointer|
 * |04|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - A valid HDCP protocol version pointer can be a simple pointer pointing to an HDCP protocol version variable.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit(), dsGetVideoPort()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetHDCPProtocol() without prior initialization|NULL or Valid handle, Valid HDCP protocol version pointer|dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Call dsGetHDCPProtocol() with an invalid handle|Invalid handle, Valid HDCP protocol version pointer|dsERR_INVALID_PARAM|Should Fail|
 * |04|Call dsGetHDCPProtocol() with a NULL HDCP protocol version pointer|Valid handle, NULL HDCP protocol version pointer|dsERR_INVALID_PARAM|Should Fail|
 * |05|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * |06|Call dsGetHDCPProtocol() after termination|Valid handle, Valid HDCP protocol version pointer|dsERR_NOT_INITIALIZED|Should Fail|
 * 
 * **Additional Notes:**@n
 * - Handle validation, NULL pointer checks, and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * - The device being tested is a source device.
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |02|Obtain a valid video port handle using dsGetVideoPort()|[Valid enum name]|Valid handle|Should return a handle to a video port|
 * |03|Get the HDCP protocol version of the connected sink device using dsGetHDCPReceiverProtocol()|Handle from step 02, Valid HDCP protocol version pointer|dsERR_NONE|The HDCP protocol version should be successfully fetched and stored in the given pointer|
 * |04|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - A valid HDCP protocol version pointer can be a simple pointer pointing to an HDCP protocol version variable.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit(), dsGetVideoPort()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetHDCPReceiverProtocol() without prior initialization|NULL or Valid handle, Valid HDCP protocol version pointer|dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Call dsGetHDCPReceiverProtocol() with an invalid handle|Invalid handle, Valid HDCP protocol version pointer|dsERR_INVALID_PARAM|Should Fail|
 * |04|Call dsGetHDCPReceiverProtocol() with a NULL HDCP protocol version pointer|Valid handle, NULL HDCP protocol version pointer|dsERR_INVALID_PARAM|Should Fail|
 * |05|Simulate a sink device and attempt to invoke dsGetHDCPReceiverProtocol()|Valid handle, Valid HDCP protocol version pointer|dsERR_OPERATION_NOT_SUPPORTED|Should return not supported error, indicating a sink device shouldn't invoke this API|
 * |06|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * |07|Call dsGetHDCPReceiverProtocol() after termination|Valid handle, Valid HDCP protocol version pointer|dsERR_NOT_INITIALIZED|Should Fail|
 * 
 * **Additional Notes:**@n
 * - Handle validation, NULL pointer checks, and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |02|Obtain a valid video port handle using dsGetVideoPort()|[Valid enum name]|Valid handle|Should return a handle to a video port|
 * |03|Get the current negotiated HDCP protocol version using dsGetHDCPCurrentProtocol()|Handle from step 02, Valid HDCP protocol version pointer|dsERR_NONE|The HDCP protocol version should be successfully fetched and stored in the given pointer|
 * |04|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - A valid HDCP protocol version pointer can be a simple pointer pointing to an HDCP protocol version variable.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit(), dsGetVideoPort()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetHDCPCurrentProtocol() without prior initialization|NULL or Valid handle, Valid HDCP protocol version pointer|dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Call dsGetHDCPCurrentProtocol() with an invalid handle|Invalid handle, Valid HDCP protocol version pointer|dsERR_INVALID_PARAM|Should Fail|
 * |04|Call dsGetHDCPCurrentProtocol() with a NULL HDCP protocol version pointer|Valid handle, NULL HDCP protocol version pointer|dsERR_INVALID_PARAM|Should Fail|
 * |05|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * |06|Call dsGetHDCPCurrentProtocol() after termination|Valid handle, Valid HDCP protocol version pointer|dsERR_NOT_INITIALIZED|Should Fail|
 * 
 * **Additional Notes:**@n
 * - Handle validation, NULL pointer checks, and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * - Video port system (TV) is successfully initialized via dsVideoPortInit().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize video port system (TV) using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |02|Obtain a valid video port handle (TV) using dsGetVideoPort()|[Valid enum name]|Valid handle|Should return a handle to a video port|
 * |03|Get the HDR capabilities using dsGetTVHDRCapabilities()|Handle from step 02, Valid HDR capabilities pointer|dsERR_NONE|The HDR capabilities should be successfully fetched and stored in the given pointer|
 * |04|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - A valid HDR capabilities pointer can be a simple pointer pointing to an integer variable.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit(), dsGetVideoPort()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetTVHDRCapabilities() without prior initialization|NULL or Valid handle, Valid HDR capabilities pointer|dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system (TV) using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Call dsGetTVHDRCapabilities() with an invalid handle|Invalid handle, Valid HDR capabilities pointer|dsERR_INVALID_PARAM|Should Fail|
 * |04|Call dsGetTVHDRCapabilities() with a NULL HDR capabilities pointer|Valid handle, NULL HDR capabilities pointer|dsERR_INVALID_PARAM|Should Fail|
 * |05|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * |06|Call dsGetTVHDRCapabilities() after termination|Valid handle, Valid HDR capabilities pointer|dsERR_NOT_INITIALIZED|Should Fail|
 * 
 * **Additional Notes:**@n
 * - Handle validation, NULL pointer checks, and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * - Video port system (TV) is successfully initialized via dsVideoPortInit().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize video port system (TV) using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |02|Obtain a valid video port handle (TV) using dsGetVideoPort()|[Valid enum name]|Valid handle|Should return a handle to a video port|
 * |03|Get the supported TV resolutions using dsSupportedTvResolutions()|Handle from step 02, Valid resolutions pointer|dsERR_NONE|The supported resolutions should be successfully fetched and stored in the given pointer|
 * |04|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - A valid resolutions pointer can be a simple pointer pointing to an integer variable.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit(), dsGetVideoPort()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsSupportedTvResolutions() without prior initialization|NULL or Valid handle, Valid resolutions pointer|dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system (TV) using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Call dsSupportedTvResolutions() with an invalid handle|Invalid handle, Valid resolutions pointer|dsERR_INVALID_PARAM|Should Fail|
 * |04|Call dsSupportedTvResolutions() with a NULL resolutions pointer|Valid handle, NULL resolutions pointer|dsERR_INVALID_PARAM|Should Fail|
 * |05|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * |06|Call dsSupportedTvResolutions() after termination|Valid handle, Valid resolutions pointer|dsERR_NOT_INITIALIZED|Should Fail|
 * 
 * **Additional Notes:**@n
 * - Handle validation, NULL pointer checks, and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |02|Obtain a valid video port handle using dsGetVideoPort()|[Valid enum name]|Valid handle|Should return a handle to a video port|
 * |03|Set the 4K support to be forcefully disabled using dsSetForceDisable4KSupport()|Handle from step 02, true|dsERR_NONE|The 4K support should be successfully disabled|
 * |04|Set the 4K support to not be forcefully disabled using dsSetForceDisable4KSupport()|Handle from step 02, false|dsERR_NONE|The 4K support should not be forcefully disabled|
 * |05|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit(), dsGetVideoPort()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsSetForceDisable4KSupport() without prior initialization|NULL or Valid handle, true|dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Call dsSetForceDisable4KSupport() with an invalid handle|Invalid handle, true|dsERR_INVALID_PARAM|Should Fail|
 * |04|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * |05|Call dsSetForceDisable4KSupport() after termination|Valid handle, true|dsERR_NOT_INITIALIZED|Should Fail|
 * 
 * **Additional Notes:**@n
 * - Handle validation and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * - dsSetForceDisable4KSupport()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |02|Obtain a valid video port handle using dsGetVideoPort()|[Valid enum name]|Valid handle|Should return a handle to a video port|
 * |03|Forcefully disable 4K support using dsSetForceDisable4KSupport()|Handle from step 02, true|dsERR_NONE|4K support should be disabled|
 * |04|Check if 4K support is disabled using dsGetForceDisable4KSupport()|Handle from step 02|true|Should return true indicating 4K support is disabled|
 * |05|Do not forcefully disable 4K support using dsSetForceDisable4KSupport()|Handle from step 02, false|dsERR_NONE|4K support should not be forcefully disabled|
 * |06|Check if 4K support is disabled using dsGetForceDisable4KSupport()|Handle from step 02|false|Should return false indicating 4K support is not disabled|
 * |07|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit(), dsGetVideoPort(), dsSetForceDisable4KSupport()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetForceDisable4KSupport() without prior initialization|NULL or Valid handle|dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Call dsGetForceDisable4KSupport() with an invalid handle|Invalid handle|dsERR_INVALID_PARAM|Should Fail|
 * |04|Call dsGetForceDisable4KSupport() without a valid pointer for disable|Valid handle, NULL|dsERR_INVALID_PARAM|Should Fail|
 * |05|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * |06|Call dsGetForceDisable4KSupport() after termination|Valid handle|dsERR_NOT_INITIALIZED|Should Fail|
 * 
 * **Additional Notes:**@n
 * - Handle validation, pointer validation, and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |02|Obtain a valid video port handle using dsGetVideoPort()|[Valid enum name]|Valid handle|Should return a handle to a video port|
 * |03|Retrieve the current Electro-Optical Transfer Function (EOTF) value using dsGetVideoEOTF()|Handle from step 02|Valid EOTF value|Should return a valid EOTF value of the specified video port|
 * |04|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit(), dsGetVideoPort()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetVideoEOTF() without prior initialization|NULL or Valid handle|dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Call dsGetVideoEOTF() with an invalid handle|Invalid handle|dsERR_INVALID_PARAM|Should Fail|
 * |04|Call dsGetVideoEOTF() without a valid pointer for video_eotf|Valid handle, NULL|dsERR_INVALID_PARAM|Should Fail|
 * |05|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * |06|Call dsGetVideoEOTF() after termination|Valid handle|dsERR_NOT_INITIALIZED|Should Fail|
 * 
 * **Additional Notes:**@n
 * - Handle validation, pointer validation, and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |02|Obtain a valid video port handle using dsGetVideoPort()|[Valid enum name]|Valid handle|Should return a handle to a video port|
 * |03|Retrieve the current matrix coefficient value using dsGetMatrixCoefficients()|Handle from step 02|Valid matrix coefficients value|Should return a valid matrix coefficient value of the specified video port|
 * |04|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit(), dsGetVideoPort()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetMatrixCoefficients() without prior initialization|NULL or Valid handle|dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Call dsGetMatrixCoefficients() with an invalid handle|Invalid handle|dsERR_INVALID_PARAM|Should Fail|
 * |04|Call dsGetMatrixCoefficients() without a valid pointer for matrix_coefficients|Valid handle, NULL|dsERR_INVALID_PARAM|Should Fail|
 * |05|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * |06|Call dsGetMatrixCoefficients() after termination|Valid handle|dsERR_NOT_INITIALIZED|Should Fail|
 * 
 * **Additional Notes:**@n
 * - Handle validation, pointer validation, and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |02|Obtain a valid video port handle using dsGetVideoPort()|[Valid enum name]|Valid handle|Should return a handle to a video port|
 * |03|Retrieve the current color depth value using dsGetColorDepth()|Handle from step 02|Valid color depth value|Should return a valid color depth value of the specified video port|
 * |04|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit(), dsGetVideoPort()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetColorDepth() without prior initialization|NULL or Valid handle|dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Call dsGetColorDepth() with an invalid handle|Invalid handle|dsERR_INVALID_PARAM|Should Fail|
 * |04|Call dsGetColorDepth() without a valid pointer for color_depth|Valid handle, NULL|dsERR_INVALID_PARAM|Should Fail|
 * |05|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * |06|Call dsGetColorDepth() after termination|Valid handle|dsERR_NOT_INITIALIZED|Should Fail|
 * 
 * **Additional Notes:**@n
 * - Handle validation, pointer validation, and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |02|Obtain a valid video port handle using dsGetVideoPort()|[Valid enum name]|Valid handle|Should return a handle to a video port|
 * |03|Retrieve the current color space setting using dsGetColorSpace()|Handle from step 02|Valid color space value|Should return a valid color space setting of the specified video port|
 * |04|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit(), dsGetVideoPort()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetColorSpace() without prior initialization|NULL or Valid handle|dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Call dsGetColorSpace() with an invalid handle|Invalid handle|dsERR_INVALID_PARAM|Should Fail|
 * |04|Call dsGetColorSpace() without a valid pointer for color_space|Valid handle, NULL|dsERR_INVALID_PARAM|Should Fail|
 * |05|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * |06|Call dsGetColorSpace() after termination|Valid handle|dsERR_NOT_INITIALIZED|Should Fail|
 * 
 * **Additional Notes:**@n
 * - Handle validation, pointer validation, and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |02|Obtain a valid video port handle using dsGetVideoPort()|[Valid enum name]|Valid handle|Should return a handle to a video port|
 * |03|Retrieve the current quantization range using dsGetQuantizationRange()|Handle from step 02|Valid quantization range|Should return a valid quantization range of the specified video port|
 * |04|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit(), dsGetVideoPort()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetQuantizationRange() without prior initialization|NULL or Valid handle|dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Call dsGetQuantizationRange() with an invalid handle|Invalid handle|dsERR_INVALID_PARAM|Should Fail|
 * |04|Call dsGetQuantizationRange() without a valid pointer for quantization_range|Valid handle, NULL|dsERR_INVALID_PARAM|Should Fail|
 * |05|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * |06|Call dsGetQuantizationRange() after termination|Valid handle|dsERR_NOT_INITIALIZED|Should Fail|
 * 
 * **Additional Notes:**@n
 * - Handle validation, pointer validation, and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |02|Obtain a valid video port handle using dsGetVideoPort()|[Valid enum name]|Valid handle|Should return a handle to a video port|
 * |03|Retrieve the current output settings using dsGetCurrentOutputSettings()|Handle from step 02, Valid Pointers|dsERR_NONE and valid settings|Should return all the required output settings of the specified video port|
 * |04|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit(), dsGetVideoPort()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetCurrentOutputSettings() without prior initialization|NULL or Valid handle, Valid Pointers|dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Call dsGetCurrentOutputSettings() with an invalid handle|Invalid handle, Valid Pointers|dsERR_INVALID_PARAM|Should Fail|
 * |04|Call dsGetCurrentOutputSettings() without a valid pointer for parameters|Valid handle, NULL pointers for some or all parameters|dsERR_INVALID_PARAM|Should Fail|
 * |05|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * |06|Call dsGetCurrentOutputSettings() after termination|Valid handle, Valid Pointers|dsERR_NOT_INITIALIZED|Should Fail|
 * 
 * **Additional Notes:**@n
 * - Handle validation, pointer validation, and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |02|Obtain a valid video port handle using dsGetVideoPort()|[Valid enum name]|Valid handle|Should return a handle to a video port|
 * |03|Check if the video output is HDR using dsIsOutputHDR()|Handle from step 02, Valid Pointer|dsERR_NONE and HDR status|Should return whether the video output is HDR or not|
 * |04|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit(), dsGetVideoPort()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsIsOutputHDR() without prior initialization|NULL or Valid handle, Valid Pointer|dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Call dsIsOutputHDR() with an invalid handle|Invalid handle, Valid Pointer|dsERR_INVALID_PARAM|Should Fail|
 * |04|Call dsIsOutputHDR() without a valid pointer for parameter|Valid handle, NULL pointer|dsERR_INVALID_PARAM|Should Fail|
 * |05|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * |06|Call dsIsOutputHDR() after termination|Valid handle, Valid Pointer|dsERR_NOT_INITIALIZED|Should Fail|
 * 
 * **Additional Notes:**@n
 * - Handle validation, pointer validation, and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |02|Reset the video output to SDR using dsResetOutputToSDR()| |dsERR_NONE|Should successfully reset to SDR|
 * |03|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsResetOutputToSDR() without prior initialization||dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * |04|Call dsResetOutputToSDR() after termination||dsERR_NOT_INITIALIZED|Should Fail|
 * 
 * **Additional Notes:**@n
 * - Handle validation and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * - A valid video port handle is acquired via dsGetVideoPort().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * - dsGetHdmiPreference()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |02|Acquire a valid video port handle using dsGetVideoPort()| |Valid handle|Should acquire a valid handle|
 * |03|Set HDMI preference using dsSetHdmiPreference()|Choose a valid HDCP protocol version from ::dsHdcpProtocolVersion_t|dsERR_NONE|Should successfully set the HDMI preference|
 * |04|Get HDMI preference using dsGetHdmiPreference()| |Should match the previously set HDCP protocol version|Verify correct setting|
 * |05|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsSetHdmiPreference() without prior initialization||dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Set HDMI preference using dsSetHdmiPreference() with an invalid handle|Invalid handle|dsERR_INVALID_PARAM|Should Fail|
 * |04|Set HDMI preference using dsSetHdmiPreference() with a NULL protocol version pointer|NULL pointer|dsERR_INVALID_PARAM|Should Fail|
 * |05|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - Handle validation and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * - A valid video port handle is acquired via dsGetVideoPort().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * - dsSetHdmiPreference()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |02|Acquire a valid video port handle using dsGetVideoPort()| |Valid handle|Should acquire a valid handle|
 * |03|Set HDMI preference using dsSetHdmiPreference()|Choose a valid HDCP protocol version from ::dsHdcpProtocolVersion_t|dsERR_NONE|Should successfully set the HDMI preference|
 * |04|Get HDMI preference using dsGetHdmiPreference()| |Should match the previously set HDCP protocol version|Verify correct setting|
 * |05|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetHdmiPreference() without prior initialization||dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Get HDMI preference using dsGetHdmiPreference() with an invalid handle|Invalid handle|dsERR_INVALID_PARAM|Should Fail|
 * |04|Get HDMI preference using dsGetHdmiPreference() with a NULL protocol version pointer|NULL pointer|dsERR_INVALID_PARAM|Should Fail|
 * |05|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - Handle validation and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * - A valid video port handle is acquired via dsGetVideoPort().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |02|Acquire a valid video port handle using dsGetVideoPort()| |Valid handle|Should acquire a valid handle|
 * |03|Get IgnoreEDID status using dsGetIgnoreEDIDStatus()| |A status value of either true or false|Should successfully get the IgnoreEDID status|
 * |04|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetIgnoreEDIDStatus() without prior initialization||dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Get IgnoreEDID status using dsGetIgnoreEDIDStatus() with an invalid handle|Invalid handle|dsERR_INVALID_PARAM|Should Fail|
 * |04|Get IgnoreEDID status using dsGetIgnoreEDIDStatus() with a NULL status pointer|NULL pointer|dsERR_INVALID_PARAM|Should Fail|
 * |05|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - Handle validation and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * - A valid video port handle is acquired via dsGetVideoPort().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |02|Acquire a valid video port handle using dsGetVideoPort()| |Valid handle|Should acquire a valid handle|
 * |03|Set background color using dsSetBackgroundColor()|Valid color value|dsERR_NONE|Background color should be set successfully|
 * |04|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - It would be ideal if there is a way to visually inspect the result to confirm that the background color is correctly set.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsSetBackgroundColor() without prior initialization||dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Set background color using dsSetBackgroundColor() with an invalid handle|Invalid handle|dsERR_INVALID_PARAM|Should Fail|
 * |04|Set background color using dsSetBackgroundColor() with an invalid color value|Invalid color value|dsERR_INVALID_PARAM|Should Fail|
 * |05|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - Handle validation and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * - A valid video port handle is acquired via dsGetVideoPort().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |02|Acquire a valid video port handle using dsGetVideoPort()| |Valid handle|Should acquire a valid handle|
 * |03|Set HDR mode using dsSetForceHDRMode()|Valid HDR mode|dsERR_NONE|HDR mode should be set successfully|
 * |04|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - It would be ideal if there is a way to visually inspect the result to confirm that the force HDR mode is correctly set.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsSetForceHDRMode() without prior initialization||dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Set HDR mode using dsSetForceHDRMode() with an invalid handle|Invalid handle|dsERR_INVALID_PARAM|Should Fail|
 * |04|Set HDR mode using dsSetForceHDRMode() with an invalid HDR mode|Invalid HDR mode|dsERR_INVALID_PARAM|Should Fail|
 * |05|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - Handle validation and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * - A valid video port handle is acquired via dsGetVideoPort().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |02|Acquire a valid video port handle using dsGetVideoPort()| |Valid handle|Should acquire a valid handle|
 * |03|Get color depth capabilities using dsColorDepthCapabilities()| |dsERR_NONE and valid OR-ed colorDepthCapability value|Color depth capabilities should be retrieved successfully|
 * |04|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - Depending on the platform, different color depth capabilities might be returned. It's essential to validate the result against the expected capabilities of the tested platform.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsColorDepthCapabilities() without prior initialization||dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Get color depth capabilities using dsColorDepthCapabilities() with an invalid handle|Invalid handle|dsERR_INVALID_PARAM|Should Fail|
 * |04|Get color depth capabilities using dsColorDepthCapabilities() with a NULL pointer for colorDepthCapability|NULL|dsERR_INVALID_PARAM|Should Fail|
 * |05|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - Handle validation, module initialization checks, and null pointer checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * - A valid video port handle is acquired via dsGetVideoPort().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * - dsSetPreferredColorDepth()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |02|Acquire a valid video port handle using dsGetVideoPort()| |Valid handle|Should acquire a valid handle|
 * |03|Set a known color depth using dsSetPreferredColorDepth()|A valid colorDepth|dsERR_NONE|Color depth should be set successfully|
 * |04|Retrieve the color depth using dsGetPreferredColorDepth()| |The same colorDepth value set in step 03|Should match the set value|
 * |05|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - Depending on the platform and hardware, certain color depths might not be supported. Always validate against the expected capabilities of the tested platform.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetPreferredColorDepth() without prior initialization||dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Retrieve the color depth using dsGetPreferredColorDepth() with an invalid handle|Invalid handle|dsERR_INVALID_PARAM|Should Fail|
 * |04|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - Handle validation and module initialization checks are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * - Video port system is successfully initialized via dsVideoPortInit().
 * - A valid video port handle is acquired via dsGetVideoPort().
 * 
 * **Dependencies:**@n
 * - dsVideoPortInit()
 * - dsGetVideoPort()
 * 
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |02|Acquire a valid video port handle using dsGetVideoPort()| |Valid handle|Should acquire a valid handle|
 * |03|Set preferred color depth using dsSetPreferredColorDepth()|Valid colorDepth|dsERR_NONE|Color depth should be set successfully|
 * |04|Verify the set value using dsGetPreferredColorDepth()| |The same colorDepth value set in step 03|Should match the set value|
 * |05|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - Depending on the platform and hardware, certain color depths might not be supported. Always validate against the expected capabilities of the tested platform.
 * - dsVideoPortTerm() should always be called at the end of the test to ensure that the video port system is properly shut down and all resources are released.
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
 * **Pre-Conditions:**@n
 * Varying depending on the specific test.
 * 
 * **Dependencies:** dsVideoPortInit()@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsSetPreferredColorDepth() without prior initialization||dsERR_NOT_INITIALIZED|Should Fail|
 * |02|Initialize video port system using dsVideoPortInit()| |dsERR_NONE|Should Pass|
 * |03|Set preferred color depth using dsSetPreferredColorDepth() with an invalid handle|Invalid handle|dsERR_INVALID_PARAM|Should Fail|
 * |04|Set preferred color depth using dsSetPreferredColorDepth() with an unsupported colorDepth value|Unsupported colorDepth value|dsERR_OPERATION_NOT_SUPPORTED|Should Fail|
 * |05|Terminate the video port system| |dsERR_NONE|All resources should be released properly|
 * 
 * **Additional Notes:**@n
 * - Handle validation, module initialization checks, and support checks for color depths are crucial for the robustness of the API.
 * - dsVideoPortTerm() should always be called to ensure that the video port system is properly shut down and all resources are released.
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
