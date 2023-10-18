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
* @file test_l1_dsHdmiIn.c
* @page Device Settings
* @subpage HdmiIn
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
 * @brief Ensure dsHdmiInInit() correctly initializes the HDMI input sub-system during positive scenarios.
 * 
 * @todo fix test group/test case
 * @todo Update description (in test procedure)
 * @todo Note retvals that cannot be tested easily in negative cases
 * @todo make sure we call after termination
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 001@n
 * 
 * **Dependencies:** HDMI input hardware is properly connected and functioning.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsHdmiInInit() for the first time | | dsERR_NONE | Should Pass |
 * |02|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after initialization |
 * |03|Call dsHdmiInInit() again | | dsERR_NONE | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after initialization |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInInit (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInInit() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 002@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsHdmiInInit() for the first time | | dsERR_NONE | Should Pass |
 * |02|Call dsHdmiInInit() again without terminating the HDMI input sub-system | | dsERR_ALREADY_INITIALIZED | Should Pass |
 * |03|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInInit (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInTerm() correctly terminates the HDMI input sub-system during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 003@n
 * 
 * **Dependencies:** HDMI input hardware is properly connected and functioning.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsHdmiInInit() for the first time | | dsERR_NONE | Should Pass |
 * |02|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after initialization |
 * |03|Call dsHdmiInInit() again | | dsERR_NONE | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after initialization |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInTerm (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInTerm() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 004@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsHdmiInTerm() without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsHdmiInInit() for the first time | | dsERR_NONE | Should Pass |
 * |03|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after initialization |
 * |04|Call dsHdmiInTerm() without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 */

void test_l1_dsHdmiIn_negative_dsHdmiInTerm (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInGetNumberOfinputs() correctly fetches the number of HDMI input ports during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 005@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Call dsHdmiInGetNumberOfinputs() to fetch the number of HDMI input ports |pNumberOfinputs: uint8_t*| dsERR_NONE | Number should be between 0 and max number of inputs defined in dsHdmiInPort_t |
 * |03|Call dsHdmiInGetNumberOfinputs() to fetch the number of HDMI input ports |pNumberOfinputs: uint8_t*| dsERR_NONE | Number should be between 0 and max number of inputs defined in dsHdmiInPort_t |
 * |04|Compare the results to make sure they are equal || Success | The values should be equal |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInGetNumberOfinputs (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInGetNumberOfinputs() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 006@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsHdmiInGetNumberOfinputs() without initializing the HDMI input sub-system |pNumberOfinputs: uint8_t*| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsHdmiInGetNumberOfinputs() with NULL as the parameter |pNumberOfinputs: NULL| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |05|Call dsHdmiInGetNumberOfinputs() after termination of the HDMI input sub-system |pNumberOfinputs: uint8_t*| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note The return values dsERR_OPERATION_NOT_SUPPORTED and dsERR_OPERATION_FAILED may be difficult to test in a simulated environment
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInGetNumberOfinputs (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInGetStatus() correctly fetches the HDMI input port status during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 007@n
 * 
 * **Dependencies:** None.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Allocate memory for dsHdmiInStatus_t and call dsHdmiInGetStatus() |dsHdmiInStatus_t*| dsERR_NONE | Status information should be populated. Validate the output structure |
 * |03|Allocate memory for dsHdmiInStatus_t and call dsHdmiInGetStatus() |dsHdmiInStatus_t*| dsERR_NONE | Status information should be populated. Validate the output structure |
 * |04|Compare the returned values to make sure they are equal || Success | The values should be the same |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInGetStatus (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInGetStatus() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 008@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsHdmiInGetStatus() without initializing the HDMI input sub-system |dsHdmiInStatus_t*| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsHdmiInGetStatus() with NULL as the parameter |NULL| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |05|Call dsHdmiInGetStatus() after terminating the HDMI input sub-system |dsHdmiInStatus_t*| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note The return values dsERR_OPERATION_NOT_SUPPORTED and dsERR_OPERATION_FAILED may be difficult to test in a simulated environment
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInGetStatus (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInSelectPort() correctly selects an HDMI input port during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 009@n
 * 
 * **Dependencies:** None.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Call dsHdmiInSelectPort() |dsHDMI_IN_PORT_0| dsERR_NONE | Port 0 should be selected |
 * |03|Call dsHdmiInSelectPort() |dsHDMI_IN_PORT_1| dsERR_NONE | Port 1 should be selected |
 * |04|Call dsHdmiInSelectPort() |dsHDMI_IN_PORT_2| dsERR_NONE | Port 2 should be selected |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInSelectPort (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInSelectPort() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 010@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsHdmiInSelectPort() without initializing the HDMI input sub-system |dsHDMI_IN_PORT_0| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsHdmiInSelectPort() with invalid value |dsHDMI_IN_PORT_MAX| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |05|Call dsHdmiInSelectPort() after terminating the HDMI input sub-system |dsHDMI_IN_PORT_0| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note The return values dsERR_OPERATION_NOT_SUPPORTED and dsERR_OPERATION_FAILED may be difficult to test in a simulated environment
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInSelectPort (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInScaleVideo() correctly scales the HDMI input video during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 011@n
 * 
 * **Dependencies:** HDMI input hardware is properly connected and functioning.@n
 *                   The HDMI input sub-system has been initialized using dsHdmiInInit().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Scale HDMI input video using dsHdmiInScaleVideo() |x=0, y=0, width=800, height=600| dsERR_NONE | Video should be scaled |
 * |03|Scale HDMI input video using dsHdmiInScaleVideo() |x=10, y=10, width=1000, height=800| dsERR_NONE | Video should be scaled |
 * |04|Scale HDMI input video using dsHdmiInScaleVideo() |x=-10, y=-10, width=800, height=600| dsERR_NONE | Video should be scaled |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInScaleVideo (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInScaleVideo() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 012@n
 * 
 * **Dependencies:** HDMI input hardware is properly connected and functioning.@n
 *                   The HDMI input sub-system has been initialized using dsHdmiInInit().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|dsHdmiInScaleVideo() without initializing the HDMI input sub-system |x=0, y=0, width=800, height=600| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|dsHdmiInScaleVideo()  |x=0, y=0, width=2000, height=600 | dsERR_INVALID_PARAM | Should Pass |
 * |04|dsHdmiInScaleVideo() with out of bounds|x=-1000, y=0, width=800, height=600| dsERR_INVALID_PARAM | Should Pass |
 * |05|dsHdmiInScaleVideo() with out of bounds|x=0, y=0, width=-800, height=600| dsERR_INVALID_PARAM | Should Pass |
 * |06|dsHdmiInScaleVideo() with out of bounds|x=0, y=0, width=800, height=-600| dsERR_INVALID_PARAM | Should Pass |
 * |07|dsHdmiInScaleVideo() with out of bounds|x=0, y=-1000, width=800, height=600| dsERR_INVALID_PARAM | Should Pass |
 * |08|dsHdmiInScaleVideo() with out of bounds|x=0, y=20000, width=800, height=600| dsERR_INVALID_PARAM | Should Pass |
 * |09|dsHdmiInScaleVideo() with out of bounds|x=20000, y=0, width=800, height=600| dsERR_INVALID_PARAM | Should Pass |
 * |10|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |11|dsHdmiInScaleVideo() after terminating the HDMI input sub-system |x=0, y=0, width=800, height=600| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note The return values dsERR_OPERATION_NOT_SUPPORTED and dsERR_OPERATION_FAILED may be difficult to test in a simulated environment
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInScaleVideo (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInSelectZoomMode() correctly updates the zoom mode during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 013@n
 * 
 * **Dependencies:** HDMI input hardware is properly connected and functioning.@n
 *                   The HDMI input sub-system has been initialized using dsHdmiInInit().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Call dsHdmiInSelectZoomMode() |dsVIDEO_ZOOM_NONE| dsERR_NONE | Zoom mode should be updated |
 * |03|Call dsHdmiInSelectZoomMode() |dsVIDEO_ZOOM_FULL| dsERR_NONE | Zoom mode should be updated |
 * |04|Call dsHdmiInSelectZoomMode() |dsVIDEO_ZOOM_LB_16_9| dsERR_NONE | Zoom mode should be updated |
 * |05|Call dsHdmiInSelectZoomMode() |dsVIDEO_ZOOM_LB_14_9| dsERR_NONE | Zoom mode should be updated |
 * |06|Call dsHdmiInSelectZoomMode() |dsVIDEO_ZOOM_CCO| dsERR_NONE | Zoom mode should be updated |
 * |07|Call dsHdmiInSelectZoomMode() |dsVIDEO_ZOOM_PAN_SCAN| dsERR_NONE | Zoom mode should be updated |
 * |08|Call dsHdmiInSelectZoomMode() |dsVIDEO_ZOOM_LB_2_21_1_ON_4_3| dsERR_NONE | Zoom mode should be updated |
 * |09|Call dsHdmiInSelectZoomMode() |dsVIDEO_ZOOM_LB_2_21_1_ON_16_9| dsERR_NONE | Zoom mode should be updated |
 * |10|Call dsHdmiInSelectZoomMode() |dsVIDEO_ZOOM_PLATFORM| dsERR_NONE | Zoom mode should be updated |
 * |11|Call dsHdmiInSelectZoomMode() |dsVIDEO_ZOOM_16_9_ZOOM| dsERR_NONE | Zoom mode should be updated |
 * |12|Call dsHdmiInSelectZoomMode() |dsVIDEO_ZOOM_PILLARBOX_4_3| dsERR_NONE | Zoom mode should be updated |
 * |13|Call dsHdmiInSelectZoomMode() |dsVIDEO_ZOOM_WIDE_4_3| dsERR_NONE | Zoom mode should be updated |
 * |14|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */

void test_l1_dsHdmiIn_positive_dsHdmiInSelectZoomMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInSelectZoomMode() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 014@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsHdmiInSelectZoomMode() without initializing the HDMI input sub-system |dsVIDEO_ZOOM_NONE| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsHdmiInSelectZoomMode() with invalid value |dsVIDEO_ZOOM_MAX| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |05|Call dsHdmiInSelectZoomMode() without terminating the HDMI input sub-system |dsVIDEO_ZOOM_NONE| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note The return values dsERR_OPERATION_NOT_SUPPORTED and dsERR_OPERATION_FAILED may be difficult to test in a simulated environment
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInSelectZoomMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInGetCurrentVideoMode() correctly retrieves the current HDMI video mode during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 015@n
 * 
 * **Dependencies:** HDMI input hardware is properly connected and functioning.@n
 *                   The HDMI input sub-system has been initialized using dsHdmiInInit().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Retrieve the current HDMI video mode using dsHdmiInGetCurrentVideoMode() |dsVideoPortResolution_t*| dsERR_NONE | Video mode should be retrieved |
 * |03|Retrieve the current HDMI video mode using dsHdmiInGetCurrentVideoMode() |dsVideoPortResolution_t*| dsERR_NONE | Video mode should be retrieved |
 * |04|Ensure returned values are the same| |Success| The values should be the same |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInGetCurrentVideoMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInGetCurrentVideoMode() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 016@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsHdmiInGetCurrentVideoMode() without initializing the HDMI input sub-system |dsVideoPortResolution_t*| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|dsHdmiInGetCurrentVideoMode() with NULL `resolution` pointer |NULL} dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |05|Call dsHdmiInGetCurrentVideoMode() after terminating the HDMI input sub-system |dsVideoPortResolution_t*| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note The return values dsERR_OPERATION_NOT_SUPPORTED and dsERR_OPERATION_FAILED may be difficult to test in a simulated environment
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInGetCurrentVideoMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInRegisterConnectCB() correctly registers a callback during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 017@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Call dsHdmiInRegisterConnectCB() |dsHdmiInConnectCB_t| dsERR_NONE | Callback should be registered |
 * |03|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInRegisterConnectCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInRegisterConnectCB() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 018@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01| Call dsHdmiInRegisterConnectCB() without initializing the HDMI input sub-system |dsHdmiInConnectCB_t| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsHdmiInRegisterConnectCB() with invalid input |NULL| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |05| Call dsHdmiInRegisterConnectCB() after termination the HDMI input sub-system |dsHdmiInConnectCB_t| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note The return values dsERR_OPERATION_NOT_SUPPORTED and dsERR_OPERATION_FAILED may be difficult to test in a simulated environment
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInRegisterConnectCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInRegisterSignalChangeCB() correctly registers a callback during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 019@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Call dsHdmiInRegisterSignalChangeCB() |dsHdmiInSignalChangeCB_t| dsERR_NONE | Callback should be registered |
 * |03|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInRegisterSignalChangeCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInRegisterSignalChangeCB() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 020@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsHdmiInRegisterSignalChangeCB() without initializing the HDMI input sub-system |dsHdmiInSignalChangeCB_t| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsHdmiInRegisterSignalChangeCB() with invalid input |NULL| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |05|Call dsHdmiInRegisterSignalChangeCB() after terminating the HDMI input sub-system |dsHdmiInSignalChangeCB_t| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note The return values dsERR_OPERATION_NOT_SUPPORTED and dsERR_OPERATION_FAILED may be difficult to test in a simulated environment
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInRegisterSignalChangeCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInRegisterStatusChangeCB() correctly registers a callback during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 021@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Call dsHdmiInRegisterStatusChangeCB() with valid input |dsHdmiInStatusChangeCB_t| dsERR_NONE | Callback should be registered |
 * |03|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInRegisterStatusChangeCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInRegisterStatusChangeCB() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 022@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsHdmiInRegisterStatusChangeCB() without initializing the HDMI input sub-system |dsHdmiInStatusChangeCB_t| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsHdmiInRegisterStatusChangeCB() with invalid input |NULL| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |05|Call dsHdmiInRegisterStatusChangeCB() after termination the HDMI input sub-system |dsHdmiInStatusChangeCB_t| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note The return values dsERR_OPERATION_NOT_SUPPORTED and dsERR_OPERATION_FAILED may be difficult to test in a simulated environment
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInRegisterStatusChangeCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInRegisterVideoModeUpdateCB() correctly registers a callback during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 023@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Call dsHdmiInRegisterVideoModeUpdateCB() with valid inputs |dsHdmiInVideoModeUpdateCB_t| dsERR_NONE | Callback should be registered |
 * |03|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInRegisterVideoModeUpdateCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInRegisterVideoModeUpdateCB() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 024@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsHdmiInRegisterVideoModeUpdateCB() without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsHdmiInRegisterVideoModeUpdateCB() with invalid input |NULL| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |05|Call dsHdmiInRegisterVideoModeUpdateCB() after terminating the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note The return values dsERR_OPERATION_NOT_SUPPORTED and dsERR_OPERATION_FAILED may be difficult to test in a simulated environment
 * 
 */

void test_l1_dsHdmiIn_negative_dsHdmiInRegisterVideoModeUpdateCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInRegisterAllmChangeCB() correctly registers a callback during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 025@n
 * 
 * **Dependencies:** HDMI input hardware supports ALLM and is functioning properly.@n
 *                   The HDMI input sub-system has been initialized using dsHdmiInInit().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Call dsHdmiInRegisterAllmChangeCB() with valid input |dsHdmiInAllmChangeCB_t| dsERR_NONE | Callback should be registered |
 * |03|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInRegisterAllmChangeCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInRegisterAllmChangeCB() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 026@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsHdmiInRegisterAllmChangeCB() without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsHdmiInRegisterAllmChangeCB() with invalid input |NULL| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |05|Call dsHdmiInRegisterAllmChangeCB() after terminating the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note The return values dsERR_OPERATION_NOT_SUPPORTED and dsERR_OPERATION_FAILED may be difficult to test in a simulated environment
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInRegisterAllmChangeCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInRegisterAVLatencyChangeCB() correctly registers a callback during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 027@n
 * 
 * **Dependencies:** HDMI input hardware supports AV Latency and is functioning properly.@n
 *                   The HDMI input sub-system has been initialized using dsHdmiInInit().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Call dsHdmiInRegisterAVLatencyChangeCB() with valid input |dsAVLatencyChangeCB_t| dsERR_NONE | Callback should be registered |
 * |03|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInRegisterAVLatencyChangeCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInRegisterAVLatencyChangeCB() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 028@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsHdmiInRegisterAVLatencyChangeCB() without initializing the HDMI input sub-system |dsAVLatencyChangeCB_t| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsHdmiInRegisterAVLatencyChangeCB() with invalid input |NULL| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |05|Call dsHdmiInRegisterAVLatencyChangeCB() after terminating the HDMI input sub-system |dsAVLatencyChangeCB_t| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note The return values dsERR_OPERATION_NOT_SUPPORTED and dsERR_OPERATION_FAILED may be difficult to test in a simulated environment
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInRegisterAVLatencyChangeCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInRegisterAviContentTypeChangeCB() correctly registers a callback during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 029@n
 * 
 * **Dependencies:** HDMI input hardware supports AVI content type and is functioning properly.@n
 *                   The HDMI input sub-system has been initialized using dsHdmiInInit().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Call dsHdmiInRegisterAviContentTypeChangeCB() with valid input |dsHdmiInAviContentTypeChangeCB_t| dsERR_NONE | Callback should be registered |
 * |03|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInRegisterAviContentTypeChangeCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInRegisterAviContentTypeChangeCB() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 030@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsHdmiInRegisterAviContentTypeChangeCB() without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsHdmiInRegisterAviContentTypeChangeCB() with invalid input |NULL| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |05|Call dsHdmiInRegisterAviContentTypeChangeCB() after terminating the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note The return values dsERR_OPERATION_NOT_SUPPORTED and dsERR_OPERATION_FAILED may be difficult to test in a simulated environment
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInRegisterAviContentTypeChangeCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsIsHdmiARCPort() correctly checks for an HDMI ARC port during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 031@n
 * 
 * **Dependencies:** The HDMI input sub-system has been initialized using dsHdmiInInit().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Call dsIsHdmiARCPort() with valid input |dsHDMI_IN_PORT_0, bool*| dsERR_NONE | Should successfully check for ARC capability |
 * |03|Call dsIsHdmiARCPort() with valid input |dsHDMI_IN_PORT_1, bool*| dsERR_NONE | Should successfully check for ARC capability |
 * |04|Call dsIsHdmiARCPort() with valid input |dsHDMI_IN_PORT_2, bool*| dsERR_NONE | Should successfully check for ARC capability |
 * |05|Call dsIsHdmiARCPort() with valid input |dsHDMI_IN_PORT_2, bool*| dsERR_NONE | Should successfully check for ARC capability |
 * |06|Compare the values of steps 4 and 5 to make sure they equal one another || Success | The values should be equal |
 * |07|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsIsHdmiARCPort (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsIsHdmiARCPort() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 032@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsIsHdmiARCPort() without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsIsHdmiARCPort() with invalid value |dsHDMI_IN_PORT_MAX, bool*| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsIsHdmiARCPort() with invalid value |dsHDMI_IN_PORT_0, NULL| dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 * @note The return values dsERR_OPERATION_NOT_SUPPORTED and dsERR_OPERATION_FAILED may be difficult to test in a simulated environment
 * 
 */
void test_l1_dsHdmiIn_negative_dsIsHdmiARCPort (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetEDIDBytesInfo() correctly retrieves the EDID bytes information during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 033@n
 * 
 * **Dependencies:** The HDMI input sub-system has been initialized using dsHdmiInInit().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Call dsGetEDIDBytesInfo() with valid inputs |dsHDMI_IN_PORT_0, unsigned char**, int*| dsERR_NONE | Should return EDID bytes information successfully |
 * |03|Call dsGetEDIDBytesInfo() with valid inputs |dsHDMI_IN_PORT_1, unsigned char**, int*| dsERR_NONE | Should return EDID bytes information successfully |
 * |04|Call dsGetEDIDBytesInfo() with valid inputs |dsHDMI_IN_PORT_2, unsigned char**, int*| dsERR_NONE | Should return EDID bytes information successfully |
 * |05|Call dsGetEDIDBytesInfo() with valid inputs |dsHDMI_IN_PORT_2, unsigned char**, int*| dsERR_NONE | Should return EDID bytes information successfully |
 * |06|Compare the results and make sure they are the same | | Success | The values should be the same |
 * |07|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsGetEDIDBytesInfo (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetEDIDBytesInfo() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 034@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetEDIDBytesInfo() without initializing the HDMI input sub-system |dsHDMI_IN_PORT_0, unsigned char**, int*| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsGetEDIDBytesInfo() with invalid value |dsHDMI_IN_PORT_MAX, unsigned char**, int*| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsGetEDIDBytesInfo() with invalid value |dsHDMI_IN_PORT_0, NULL, int*| dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsGetEDIDBytesInfo() with invalid value |dsHDMI_IN_PORT_0, unsigned char**, NULL| dsERR_INVALID_PARAM | Should Pass |
 * |06|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |07|Call dsGetEDIDBytesInfo() after termination the HDMI input sub-system |dsHDMI_IN_PORT_0, unsigned char**, int*| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note The return values dsERR_OPERATION_NOT_SUPPORTED and dsERR_OPERATION_FAILED may be difficult to test in a simulated environment
 * 
 */
void test_l1_dsHdmiIn_negative_dsGetEDIDBytesInfo (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetHDMISPDInfo() correctly retrieves the HDMI SPD information during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 035@n
 * 
 * **Dependencies:** The HDMI input sub-system has been initialized using dsHdmiInInit().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Call dsGetHDMISPDInfo() with valid input |dsHDMI_IN_PORT_0, unsigned char**| dsERR_NONE | Should return HDMI SPD information successfully |
 * |03|Call dsGetHDMISPDInfo() with valid input |dsHDMI_IN_PORT_1, unsigned char**| dsERR_NONE | Should return HDMI SPD information successfully |
 * |04|Call dsGetHDMISPDInfo() with valid input |dsHDMI_IN_PORT_2, unsigned char**| dsERR_NONE | Should return HDMI SPD information successfully |
 * |05|Call dsGetHDMISPDInfo() with valid input |dsHDMI_IN_PORT_2, unsigned char**| dsERR_NONE | Should return HDMI SPD information successfully |
 * |06|Compare values from step 4/5 and make sure they're the same || Success | The values should be the same |
 * |07|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsGetHDMISPDInfo (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetHDMISPDInfo() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 036@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetHDMISPDInfo() without initializing the HDMI input sub-system |dsHDMI_IN_PORT_0, unsigned char**| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsGetHDMISPDInfo() with invalid values |dsHDMI_IN_PORT_MAX, unsigned char**| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsGetHDMISPDInfo() with invalid values |dsHDMI_IN_PORT_0, NULL| dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |06|Call dsGetHDMISPDInfo() after terminating the HDMI input sub-system |dsHDMI_IN_PORT_0, unsigned char**| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note The return values dsERR_OPERATION_NOT_SUPPORTED and dsERR_OPERATION_FAILED may be difficult to test in a simulated environment
 * 
 */
void test_l1_dsHdmiIn_negative_dsGetHDMISPDInfo (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetEdidVersion() correctly sets the EDID version during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 037@n
 * 
 * **Dependencies:** The HDMI input sub-system has been initialized using dsHdmiInInit().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Call dsSetEdidVersion() with valid values |dsHDMI_IN_PORT_0, HDMI_EDID_VER_14| dsERR_NONE | Should set EDID version successfully |
 * |03|Call dsSetEdidVersion() with valid values |dsHDMI_IN_PORT_0, HDMI_EDID_VER_20| dsERR_NONE | Should set EDID version successfully |
 * |04|Call dsSetEdidVersion() with valid values |dsHDMI_IN_PORT_1, HDMI_EDID_VER_14| dsERR_NONE | Should set EDID version successfully |
 * |05|Call dsSetEdidVersion() with valid values |dsHDMI_IN_PORT_2, HDMI_EDID_VER_14| dsERR_NONE | Should set EDID version successfully |
 * |06|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsSetEdidVersion (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetEdidVersion() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 038@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsSetEdidVersion() without initializing the HDMI input sub-system |dsHDMI_IN_PORT_0, HDMI_EDID_VER_14| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsSetEdidVersion() with invalid inputs |dsHDMI_IN_PORT_MAX, HDMI_EDID_VER_14| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsSetEdidVersion() with invalid inputs |dsHDMI_IN_PORT_0, HDMI_EDID_VER_MAX| dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |06|Call dsSetEdidVersion() without initializing the HDMI input sub-system |dsHDMI_IN_PORT_0, HDMI_EDID_VER_14| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note The return values dsERR_OPERATION_NOT_SUPPORTED and dsERR_OPERATION_FAILED may be difficult to test in a simulated environment
 * 
 */
void test_l1_dsHdmiIn_negative_dsSetEdidVersion (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetEdidVersion() correctly retrieves the EDID version during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 039@n
 * 
 * **Dependencies:** The HDMI input sub-system has been initialized using dsHdmiInInit() and the EDID version has been set using dsSetEdidVersion().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Call dsSetEdidVersion() with valid values |dsHDMI_IN_PORT_0, tv_hdmi_edid_version_t*| dsERR_NONE | Should Pass |
 * |03|Call dsSetEdidVersion() with valid values |dsHDMI_IN_PORT_1, tv_hdmi_edid_version_t*| dsERR_NONE | Should Pass |
 * |04|Call dsSetEdidVersion() with valid values |dsHDMI_IN_PORT_2, tv_hdmi_edid_version_t*| dsERR_NONE | Should Pass |
 * |05|Call dsSetEdidVersion() with valid values |dsHDMI_IN_PORT_0, tv_hdmi_edid_version_t*| dsERR_NONE | Should Pass |
 * |06|Compare the values from steps 4/5 and make sure they match || Success | The values should be the same |
 * |07|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsGetEdidVersion (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetEdidVersion() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 040@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetEdidVersion() without initializing the HDMI input sub-system |dsHDMI_IN_PORT_0, tv_hdmi_edid_version_t*| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsGetEdidVersion() with invalid inputs |dsHDMI_IN_PORT_MAX, tv_hdmi_edid_version_t*| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsGetEdidVersion() with invalid inputs |dsHDMI_IN_PORT_0, NULL| dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |06|Call dsGetEdidVersion() without initializing the HDMI input sub-system |dsHDMI_IN_PORT_0, tv_hdmi_edid_version_t*| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note The return values dsERR_OPERATION_NOT_SUPPORTED and dsERR_OPERATION_FAILED may be difficult to test in a simulated environment
 * 
 */
void test_l1_dsHdmiIn_negative_dsGetEdidVersion (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAllmStatus() correctly retrieves the ALLM status during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 041@n
 * 
 * **Dependencies:** The HDMI input sub-system has been initialized using dsHdmiInInit().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAllmStatus() with valid inputs |dsHDMI_IN_PORT_0, bool*| dsERR_NONE | Should retrieve ALLM status successfully |
 * |03|Call dsGetAllmStatus() with valid inputs |dsHDMI_IN_PORT_1, bool*| dsERR_NONE | Should retrieve ALLM status successfully |
 * |04|Call dsGetAllmStatus() with valid inputs |dsHDMI_IN_PORT_2, bool*| dsERR_NONE | Should retrieve ALLM status successfully |
 * |05|Call dsGetAllmStatus() with valid inputs |dsHDMI_IN_PORT_2, bool*| dsERR_NONE | Should retrieve ALLM status successfully |
 * |06|Compare the results of steps 4/5 and make sure they are the same || Success | The returned values should be the same |
 * |07|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsGetAllmStatus (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAllmStatus() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 042@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetAllmStatus() without initializing the HDMI input sub-system |dsHDMI_IN_PORT_0, bool*| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsGetAllmStatus() without valid inputs |dsHDMI_IN_PORT_MAX, bool*| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsGetAllmStatus() without valid inputs |dsHDMI_IN_PORT_0, NULL| dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |06|Call dsGetAllmStatus() after termination the HDMI input sub-system |dsHDMI_IN_PORT_0, bool*| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note The return values dsERR_OPERATION_NOT_SUPPORTED and dsERR_OPERATION_FAILED may be difficult to test in a simulated environment
 * 
 */
void test_l1_dsHdmiIn_negative_dsGetAllmStatus (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetSupportedGameFeaturesList() correctly retrieves the list of supported game features during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 043@n
 * 
 * **Dependencies:** The HDMI input sub-system has been initialized using dsHdmiInInit().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Call dsGetSupportedGameFeaturesList() with valid inputs |dsSupportedGameFeatureList_t*| dsERR_NONE | Should retrieve list successfully |
 * |03|Call dsGetSupportedGameFeaturesList() with valid inputs |dsSupportedGameFeatureList_t*| dsERR_NONE | Should retrieve list successfully |
 * |04|Compare the returns of steps 2/3 and make sure they compare || Success | Make sure the returned are values |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsGetSupportedGameFeaturesList (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetSupportedGameFeaturesList() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 044@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetSupportedGameFeaturesList() without initializing the HDMI input sub-system |dsSupportedGameFeatureList_t*| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsGetSupportedGameFeaturesList() with invalid input |NULL| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |05|Call dsGetSupportedGameFeaturesList() after termination the HDMI input sub-system |dsSupportedGameFeatureList_t*| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note The return values dsERR_OPERATION_NOT_SUPPORTED and dsERR_OPERATION_FAILED may be difficult to test in a simulated environment
 * 
 */
void test_l1_dsHdmiIn_negative_dsGetSupportedGameFeaturesList (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAVLatency() correctly retrieves the current AV latency during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 045@n
 * 
 * **Dependencies:** The HDMI input sub-system has been initialized using dsHdmiInInit().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Call dsHdmiInSelectPort() |dsHDMI_IN_PORT_0| dsERR_NONE | Port 0 should be selected |
 * |03|Call dsGetAVLatency() with valid input |int*, int*| dsERR_NONE | Should retrieve AV latency values successfully |
 * |04|Call dsGetAVLatency() with valid input |int*, int*| dsERR_NONE | Should retrieve AV latency values successfully |
 * |05|Validate the returns of steps 2/3 and verify that they are the same| | Success | The same values should be the same. |
 * |06|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsGetAVLatency (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAVLatency() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 046@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetAVLatency() without initializing the HDMI input sub-system |int*, int*| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsGetAVLatency() with valid inputs |NULL, int*| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsGetAVLatency() with valid inputs |int*, NULL| dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |06|Call dsGetAVLatency() after terminating the HDMI input sub-system |int*, int*| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note The return values dsERR_OPERATION_NOT_SUPPORTED and dsERR_OPERATION_FAILED may be difficult to test in a simulated environment
 * 
 */
void test_l1_dsHdmiIn_negative_dsGetAVLatency (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main test(s) for this module
 *
 * @return int - 0 on success, otherwise failure
 */
int test_l1_dsHdmiIn_register ( void )
{
	/* add a suite to the registry */
	pSuite = UT_add_suite( "[L1 dsHdmiIn]", NULL, NULL );
	if ( NULL == pSuite )
	{
		return -1;
	}	

	UT_add_test( pSuite, "dsHdmiInInit_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInInit );
	UT_add_test( pSuite, "dsHdmiInInit_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInInit );
	UT_add_test( pSuite, "dsHdmiInTerm_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInTerm );
	UT_add_test( pSuite, "dsHdmiInTerm_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInTerm );
	UT_add_test( pSuite, "dsHdmiInGetNumberOfinputs_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInGetNumberOfinputs );
	UT_add_test( pSuite, "dsHdmiInGetNumberOfinputs_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInGetNumberOfinputs );
	UT_add_test( pSuite, "dsHdmiInGetStatus_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInGetStatus );
	UT_add_test( pSuite, "dsHdmiInGetStatus_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInGetStatus );
	UT_add_test( pSuite, "dsHdmiInSelectPort_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInSelectPort );
	UT_add_test( pSuite, "dsHdmiInSelectPort_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInSelectPort );
	UT_add_test( pSuite, "dsHdmiInScaleVideo_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInScaleVideo );
	UT_add_test( pSuite, "dsHdmiInScaleVideo_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInScaleVideo );
	UT_add_test( pSuite, "dsHdmiInSelectZoomMode_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInSelectZoomMode );
	UT_add_test( pSuite, "dsHdmiInSelectZoomMode_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInSelectZoomMode );
	UT_add_test( pSuite, "dsHdmiInGetCurrentVideoMode_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInGetCurrentVideoMode );
	UT_add_test( pSuite, "dsHdmiInGetCurrentVideoMode_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInGetCurrentVideoMode );
	UT_add_test( pSuite, "dsHdmiInRegisterConnectCB_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInRegisterConnectCB );
	UT_add_test( pSuite, "dsHdmiInRegisterConnectCB_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInRegisterConnectCB );
	UT_add_test( pSuite, "dsHdmiInRegisterSignalChangeCB_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInRegisterSignalChangeCB );
	UT_add_test( pSuite, "dsHdmiInRegisterSignalChangeCB_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInRegisterSignalChangeCB );
	UT_add_test( pSuite, "dsHdmiInRegisterStatusChangeCB_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInRegisterStatusChangeCB );
	UT_add_test( pSuite, "dsHdmiInRegisterStatusChangeCB_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInRegisterStatusChangeCB );
	UT_add_test( pSuite, "dsHdmiInRegisterVideoModeUpdateCB_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInRegisterVideoModeUpdateCB );
	UT_add_test( pSuite, "dsHdmiInRegisterVideoModeUpdateCB_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInRegisterVideoModeUpdateCB );
	UT_add_test( pSuite, "dsHdmiInRegisterAllmChangeCB_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInRegisterAllmChangeCB );
	UT_add_test( pSuite, "dsHdmiInRegisterAllmChangeCB_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInRegisterAllmChangeCB );
	UT_add_test( pSuite, "dsHdmiInRegisterAVLatencyChangeCB_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInRegisterAVLatencyChangeCB );
	UT_add_test( pSuite, "dsHdmiInRegisterAVLatencyChangeCB_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInRegisterAVLatencyChangeCB );
	UT_add_test( pSuite, "dsHdmiInRegisterAviContentTypeChangeCB_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInRegisterAviContentTypeChangeCB );
	UT_add_test( pSuite, "dsHdmiInRegisterAviContentTypeChangeCB_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInRegisterAviContentTypeChangeCB );
	UT_add_test( pSuite, "dsIsHdmiARCPort_L1_positive" ,test_l1_dsHdmiIn_positive_dsIsHdmiARCPort );
	UT_add_test( pSuite, "dsIsHdmiARCPort_L1_negative" ,test_l1_dsHdmiIn_negative_dsIsHdmiARCPort );
	UT_add_test( pSuite, "dsGetEDIDBytesInfo_L1_positive" ,test_l1_dsHdmiIn_positive_dsGetEDIDBytesInfo );
	UT_add_test( pSuite, "dsGetEDIDBytesInfo_L1_negative" ,test_l1_dsHdmiIn_negative_dsGetEDIDBytesInfo );
	UT_add_test( pSuite, "dsGetHDMISPDInfo_L1_positive" ,test_l1_dsHdmiIn_positive_dsGetHDMISPDInfo );
	UT_add_test( pSuite, "dsGetHDMISPDInfo_L1_negative" ,test_l1_dsHdmiIn_negative_dsGetHDMISPDInfo );
	UT_add_test( pSuite, "dsSetEdidVersion_L1_positive" ,test_l1_dsHdmiIn_positive_dsSetEdidVersion );
	UT_add_test( pSuite, "dsSetEdidVersion_L1_negative" ,test_l1_dsHdmiIn_negative_dsSetEdidVersion );
	UT_add_test( pSuite, "dsGetEdidVersion_L1_positive" ,test_l1_dsHdmiIn_positive_dsGetEdidVersion );
	UT_add_test( pSuite, "dsGetEdidVersion_L1_negative" ,test_l1_dsHdmiIn_negative_dsGetEdidVersion );
	UT_add_test( pSuite, "dsGetAllmStatus_L1_positive" ,test_l1_dsHdmiIn_positive_dsGetAllmStatus );
	UT_add_test( pSuite, "dsGetAllmStatus_L1_negative" ,test_l1_dsHdmiIn_negative_dsGetAllmStatus );
	UT_add_test( pSuite, "dsGetSupportedGameFeaturesList_L1_positive" ,test_l1_dsHdmiIn_positive_dsGetSupportedGameFeaturesList );
	UT_add_test( pSuite, "dsGetSupportedGameFeaturesList_L1_negative" ,test_l1_dsHdmiIn_negative_dsGetSupportedGameFeaturesList );
	UT_add_test( pSuite, "dsGetAVLatency_L1_positive" ,test_l1_dsHdmiIn_positive_dsGetAVLatency );
	UT_add_test( pSuite, "dsGetAVLatency_L1_negative" ,test_l1_dsHdmiIn_negative_dsGetAVLatency );
	

	return 0;
} 
