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
* @file TODO: test_l1_dsHdmiIn.c
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
 * @brief Ensure dsHdmiInInit() correctly initializes the HDMI input sub-system during positive scenarios.
 * 
 * @todo fix test group/test case
 * @todo Update description (in test procedure)
 * @todo Note retvals that cannot be tested easily in negative cases
 * @todo make sure we call after termination
 * 
 * **Test Group ID:** Basic: 74@n
 * **Test Case ID:** 306@n
 * 
 * **Dependencies:** HDMI input hardware is properly connected and functioning.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsHdmiInInit() for the first time | dsERR_NONE | Should Pass |
 * |02|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after initialization |
 * |03|Call dsHdmiInInit() for the first time | dsERR_NONE | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after initialization |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInInit (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInInit() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 74@n
 * **Test Case ID:** 307@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsHdmiInInit() for the first time | dsERR_NONE | Should Pass |
 * |02|Call dsHdmiInInit() again without terminating the HDMI input sub-system | dsERR_ALREADY_INITIALIZED | Should Pass |
 * |03|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInInit (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInTerm() correctly terminates the HDMI input sub-system during positive scenarios.
 * 
 * **Test Group ID:** Basic: 75@n
 * **Test Case ID:** 308@n
 * 
 * **Dependencies:** HDMI input hardware is properly connected and functioning.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsHdmiInInit() for the first time | dsERR_NONE | Should Pass |
 * |02|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after initialization |
 * |03|Call dsHdmiInInit() for the first time | dsERR_NONE | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after initialization |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInTerm (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInTerm() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 75@n
 * **Test Case ID:** 309@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsHdmiInTerm() without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Call dsHdmiInInit() for the first time | dsERR_NONE | Should Pass |
 * |03|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after initialization |
 * |04|Call dsHdmiInTerm() without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 */

void test_l1_dsHdmiIn_negative_dsHdmiInTerm (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInGetNumberOfinputs() correctly fetches the number of HDMI input ports during positive scenarios.
 * 
 * **Test Group ID:** Basic: 76@n
 * **Test Case ID:** 310@n
 * 
 * **Dependencies:** HDMI input hardware is properly connected and functioning.@n
 *                   The HDMI input sub-system has been initialized using dsHdmiInInit().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |02|Call dsHdmiInGetNumberOfinputs() to fetch the number of HDMI input ports | dsERR_NONE | Number should be between 0 and max number of inputs defined in dsHdmiInPort_t |
 * |03|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInGetNumberOfinputs (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInGetNumberOfinputs() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 76@n
 * **Test Case ID:** 311@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsHdmiInGetNumberOfinputs() without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |03|Call dsHdmiInGetNumberOfinputs() with NULL as the parameter | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInGetNumberOfinputs (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInGetStatus() correctly fetches the HDMI input port status during positive scenarios.
 * 
 * **Test Group ID:** Basic: 78@n
 * **Test Case ID:** 320@n
 * 
 * **Dependencies:** HDMI input hardware is properly connected and functioning.@n
 *                   The HDMI input sub-system has been initialized using dsHdmiInInit().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |02|Allocate memory for dsHdmiInStatus_t and call dsHdmiInGetStatus() | dsERR_NONE | Status information should be populated. Validate the output structure |
 * |03|Check if `isPresented` is either TRUE or FALSE | - | Only valid values are TRUE or FALSE |
 * |04|Check if `activePort` is within range, between `dsHDMI_IN_PORT_NONE` and `dsHDMI_IN_PORT_MAX` | - | It should be |
 * |05|Loop through `isPortConnected` and check if each value is either TRUE or FALSE | - | Only valid values are TRUE or FALSE |
 * |06|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInGetStatus (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInGetStatus() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 78@n
 * **Test Case ID:** 321@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsHdmiInGetStatus() without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |03|Call dsHdmiInGetStatus() with NULL as the parameter | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInGetStatus (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInSelectPort() correctly selects an HDMI input port during positive scenarios.
 * 
 * **Test Group ID:** Basic: 82@n
 * **Test Case ID:** 325@n
 * 
 * **Dependencies:** HDMI input hardware is properly connected and functioning.@n
 *                   The HDMI input sub-system has been initialized using dsHdmiInInit().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |02|Select HDMI input port `dsHDMI_IN_PORT_0` using dsHdmiInSelectPort() | dsERR_NONE | Port 0 should be selected |
 * |03|Select HDMI input port `dsHDMI_IN_PORT_1` using dsHdmiInSelectPort() | dsERR_NONE | Port 1 should be selected |
 * |04|Select HDMI input port `dsHDMI_IN_PORT_2` using dsHdmiInSelectPort() | dsERR_NONE | Port 2 should be selected |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInSelectPort (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInSelectPort() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 82@n
 * **Test Case ID:** 326@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Select HDMI input port `dsHDMI_IN_PORT_0` without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |03|Select HDMI input port `dsHDMI_IN_PORT_MAX` which is out of range | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInSelectPort (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInScaleVideo() correctly scales the HDMI input video during positive scenarios.
 * 
 * **Test Group ID:** Basic: 83@n
 * **Test Case ID:** 327@n
 * 
 * **Dependencies:** HDMI input hardware is properly connected and functioning.@n
 *                   The HDMI input sub-system has been initialized using dsHdmiInInit().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |02|Scale HDMI input video with x=100, y=100, width=800, height=600 using dsHdmiInScaleVideo() | dsERR_NONE | Video should be scaled |
 * |03|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInScaleVideo (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInScaleVideo() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 83@n
 * **Test Case ID:** 328@n
 * 
 * **Dependencies:** Assuming device resolution is 1920x1080@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Scale HDMI input video with x=0, y=0, width=2000, height=600 (width is greater than device resolution) without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |03|Scale HDMI input video with x=0, y=0, width=2000, height=600 (width is greater than device resolution) | dsERR_INVALID_PARAM | Should Pass |
 * |04|Scale HDMI input video with negative x or y coordinates, e.g., x=-100, y=0, width=800, height=600 | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInScaleVideo (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInSelectZoomMode() correctly updates the zoom mode during positive scenarios.
 * 
 * **Test Group ID:** Basic: 84@n
 * **Test Case ID:** 329@n
 * 
 * **Dependencies:** HDMI input hardware is properly connected and functioning.@n
 *                   The HDMI input sub-system has been initialized using dsHdmiInInit().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |02|Update zoom mode to `dsVIDEO_ZOOM_NONE` using dsHdmiInSelectZoomMode() | dsERR_NONE | Zoom mode should be updated |
 * |03|Update zoom mode to `dsVIDEO_ZOOM_FULL` using dsHdmiInSelectZoomMode() | dsERR_NONE | Zoom mode should be updated |
 * |...|...|...|...|
 * |n|Update zoom mode to `dsVIDEO_ZOOM_MAX - 1` using dsHdmiInSelectZoomMode() | dsERR_NONE | Zoom mode should be updated |
 * |n+1|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */

void test_l1_dsHdmiIn_positive_dsHdmiInSelectZoomMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInSelectZoomMode() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 84@n
 * **Test Case ID:** 330@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Update zoom mode to `dsVIDEO_ZOOM_NONE` without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |03|Update zoom mode to `dsVIDEO_ZOOM_MAX` (out of range) using dsHdmiInSelectZoomMode() | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInSelectZoomMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInGetCurrentVideoMode() correctly retrieves the current HDMI video mode during positive scenarios.
 * 
 * **Test Group ID:** Basic: 85@n
 * **Test Case ID:** 331@n
 * 
 * **Dependencies:** HDMI input hardware is properly connected and functioning.@n
 *                   The HDMI input sub-system has been initialized using dsHdmiInInit().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |02|Retrieve the current HDMI video mode using dsHdmiInGetCurrentVideoMode() | dsERR_NONE | Video mode should be retrieved |
 * |03|Ensure returned video mode details (resolution, aspect ratio, etc.) match expected settings | - | Ensure accuracy |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInGetCurrentVideoMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInGetCurrentVideoMode() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 85@n
 * **Test Case ID:** 332@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Retrieve the current HDMI video mode without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |03|Retrieve the current HDMI video mode with NULL `resolution` pointer using dsHdmiInGetCurrentVideoMode() | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInGetCurrentVideoMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInRegisterConnectCB() correctly registers a callback during positive scenarios.
 * 
 * **Test Group ID:** Basic: 86@n
 * **Test Case ID:** 333@n
 * 
 * **Dependencies:** HDMI input hardware is properly connected and functioning.@n
 *                   The HDMI input sub-system has been initialized using dsHdmiInInit().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |02|Register a valid HDMI input hot plug callback using dsHdmiInRegisterConnectCB() | dsERR_NONE | Callback should be registered |
 * |03|Trigger HDMI hot plug event and ensure registered callback gets called | - | Callback should execute |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInRegisterConnectCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInRegisterConnectCB() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 86@n
 * **Test Case ID:** 334@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Register a callback without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |03|Register NULL as HDMI input hot plug callback using dsHdmiInRegisterConnectCB() | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInRegisterConnectCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInRegisterSignalChangeCB() correctly registers a callback during positive scenarios.
 * 
 * **Test Group ID:** Basic: 87@n
 * **Test Case ID:** 335@n
 * 
 * **Dependencies:** HDMI input hardware is properly connected and functioning.@n
 *                   The HDMI input sub-system has been initialized using dsHdmiInInit().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |02|Register a valid HDMI input Signal change callback using dsHdmiInRegisterSignalChangeCB() | dsERR_NONE | Callback should be registered |
 * |03|Trigger HDMI Signal Change event and ensure registered callback gets called | - | Callback should execute |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInRegisterSignalChangeCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInRegisterSignalChangeCB() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 87@n
 * **Test Case ID:** 336@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Register a callback without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |03|Register NULL as HDMI input Signal change callback using dsHdmiInRegisterSignalChangeCB() | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInRegisterSignalChangeCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInRegisterStatusChangeCB() correctly registers a callback during positive scenarios.
 * 
 * **Test Group ID:** Basic: 88@n
 * **Test Case ID:** 337@n
 * 
 * **Dependencies:** HDMI input hardware is properly connected and functioning.@n
 *                   The HDMI input sub-system has been initialized using dsHdmiInInit().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |02|Register a valid HDMI input Status change callback using dsHdmiInRegisterStatusChangeCB() | dsERR_NONE | Callback should be registered |
 * |03|Trigger HDMI Status Change event and ensure registered callback gets called | - | Callback should execute |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInRegisterStatusChangeCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInRegisterStatusChangeCB() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 88@n
 * **Test Case ID:** 338@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Register a callback without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |03|Register NULL as HDMI input Status change callback using dsHdmiInRegisterStatusChangeCB() | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInRegisterStatusChangeCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInRegisterVideoModeUpdateCB() correctly registers a callback during positive scenarios.
 * 
 * **Test Group ID:** Basic: 89@n
 * **Test Case ID:** 339@n
 * 
 * **Dependencies:** HDMI input hardware is properly connected and functioning.@n
 *                   The HDMI input sub-system has been initialized using dsHdmiInInit().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |02|Register a valid HDMI input video mode change callback using dsHdmiInRegisterVideoModeUpdateCB() | dsERR_NONE | Callback should be registered |
 * |03|Trigger HDMI video mode Change event by changing video resolution and ensure registered callback gets called | - | Callback should execute |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInRegisterVideoModeUpdateCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInRegisterVideoModeUpdateCB() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 89@n
 * **Test Case ID:** 340@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Register a callback without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |03|Register NULL as HDMI input video mode change callback using dsHdmiInRegisterVideoModeUpdateCB() | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */

void test_l1_dsHdmiIn_negative_dsHdmiInRegisterVideoModeUpdateCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInRegisterAllmChangeCB() correctly registers a callback during positive scenarios.
 * 
 * **Test Group ID:** Basic: 90@n
 * **Test Case ID:** 341@n
 * 
 * **Dependencies:** HDMI input hardware supports ALLM and is functioning properly.@n
 *                   The HDMI input sub-system has been initialized using dsHdmiInInit().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |02|Register a valid HDMI input ALLM Mode change callback using dsHdmiInRegisterAllmChangeCB() | dsERR_NONE | Callback should be registered |
 * |03|Trigger HDMI ALLM Mode Change event and ensure registered callback gets called | - | Callback should execute |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInRegisterAllmChangeCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInRegisterAllmChangeCB() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 90@n
 * **Test Case ID:** 342@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Register a callback without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |03|Register NULL as HDMI input ALLM Mode change callback using dsHdmiInRegisterAllmChangeCB() | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInRegisterAllmChangeCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInRegisterAVLatencyChangeCB() correctly registers a callback during positive scenarios.
 * 
 * **Test Group ID:** Basic: 91@n
 * **Test Case ID:** 343@n
 * 
 * **Dependencies:** HDMI input hardware supports AV Latency and is functioning properly.@n
 *                   The HDMI input sub-system has been initialized using dsHdmiInInit().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |02|Register a valid HDMI input AV Latency change callback using dsHdmiInRegisterAVLatencyChangeCB() | dsERR_NONE | Callback should be registered |
 * |03|Trigger HDMI AV Latency Change event and ensure registered callback gets called | - | Callback should execute |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInRegisterAVLatencyChangeCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInRegisterAVLatencyChangeCB() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 91@n
 * **Test Case ID:** 344@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Register a callback without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |03|Register NULL as HDMI input AV Latency change callback using dsHdmiInRegisterAVLatencyChangeCB() | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInRegisterAVLatencyChangeCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInRegisterAviContentTypeChangeCB() correctly registers a callback during positive scenarios.
 * 
 * **Test Group ID:** Basic: 92@n
 * **Test Case ID:** 345@n
 * 
 * **Dependencies:** HDMI input hardware supports AVI content type and is functioning properly.@n
 *                   The HDMI input sub-system has been initialized using dsHdmiInInit().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |02|Register a valid HDMI input AVI Content type change callback using dsHdmiInRegisterAviContentTypeChangeCB() | dsERR_NONE | Callback should be registered |
 * |03|Trigger HDMI AVI Content Type Change event and ensure registered callback gets called | - | Callback should execute |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInRegisterAviContentTypeChangeCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsHdmiInRegisterAviContentTypeChangeCB() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 92@n
 * **Test Case ID:** 346@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Register a callback without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |03|Register NULL as HDMI input AVI Content type change callback using dsHdmiInRegisterAviContentTypeChangeCB() | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInRegisterAviContentTypeChangeCB (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsIsHdmiARCPort() correctly checks for an HDMI ARC port during positive scenarios.
 * 
 * **Test Group ID:** Basic: 93@n
 * **Test Case ID:** 347@n
 * 
 * **Dependencies:** The HDMI input sub-system has been initialized using dsHdmiInInit().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |02|Check if a valid HDMI port is an ARC port using dsIsHdmiARCPort() | dsERR_NONE | Should successfully check for ARC capability |
 * |03|Check the returned `isArcPort` value | - | Ensure it returns the correct status based on hardware setup |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsIsHdmiARCPort (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsIsHdmiARCPort() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 93@n
 * **Test Case ID:** 348@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Check if a port is an ARC port without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |03|Check with an invalid port value (e.g., negative or beyond max device-specific value) using dsIsHdmiARCPort() | dsERR_INVALID_PARAM | Should Pass |
 * |04|Pass NULL for the `isArcPort` parameter and check a valid port using dsIsHdmiARCPort() | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_negative_dsIsHdmiARCPort (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetEDIDBytesInfo() correctly retrieves the EDID bytes information during positive scenarios.
 * 
 * **Test Group ID:** Basic: 94@n
 * **Test Case ID:** 349@n
 * 
 * **Dependencies:** The HDMI input sub-system has been initialized using dsHdmiInInit().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |02|Retrieve EDID bytes information for a valid HDMI port using dsGetEDIDBytesInfo() | dsERR_NONE | Should return EDID bytes information successfully |
 * |03|Check the validity of returned `edid` bytes | - | `edid` bytes should be valid based on device configuration |
 * |04|Ensure the `length` matches the expected value | - | `length` should be within the range of 0 to 256 |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsGetEDIDBytesInfo (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetEDIDBytesInfo() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 94@n
 * **Test Case ID:** 350@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Retrieve EDID bytes information without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |03|Pass NULL for the `edid` and `length` parameters and check using dsGetEDIDBytesInfo() | dsERR_INVALID_PARAM | Should Pass |
 * |04|Use an invalid HDMI port to retrieve EDID bytes information using dsGetEDIDBytesInfo() | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_negative_dsGetEDIDBytesInfo (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetHDMISPDInfo() correctly retrieves the HDMI SPD information during positive scenarios.
 * 
 * **Test Group ID:** Basic: 95@n
 * **Test Case ID:** 351@n
 * 
 * **Dependencies:** The HDMI input sub-system has been initialized using dsHdmiInInit().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |02|Retrieve HDMI SPD information for a valid HDMI port using dsGetHDMISPDInfo() | dsERR_NONE | Should return HDMI SPD information successfully |
 * |03|Check the validity of the returned `data` | - | `data` bytes should be valid based on device configuration |
 * |04|Ensure the data size does not exceed sizeof(dsSpd_infoframe_st) | - | Data size should be within the expected range |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsGetHDMISPDInfo (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetHDMISPDInfo() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 95@n
 * **Test Case ID:** 352@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Retrieve HDMI SPD information without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |03|Pass NULL for the `data` parameter and check using dsGetHDMISPDInfo() | dsERR_INVALID_PARAM | Should Pass |
 * |04|Use an invalid HDMI port to retrieve HDMI SPD information using dsGetHDMISPDInfo() | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_negative_dsGetHDMISPDInfo (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetEdidVersion() correctly sets the EDID version during positive scenarios.
 * 
 * **Test Group ID:** Basic: 96@n
 * **Test Case ID:** 353@n
 * 
 * **Dependencies:** The HDMI input sub-system has been initialized using dsHdmiInInit().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |02|Set EDID version for a valid HDMI port using dsSetEdidVersion() | dsERR_NONE | Should set EDID version successfully |
 * |03|Retrieve the EDID version for the same HDMI port using dsGetEdidVersion() | dsERR_NONE & matching EDID version | Should return the same EDID version as set in step 2 |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsSetEdidVersion (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetEdidVersion() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 96@n
 * **Test Case ID:** 354@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Set EDID version without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |03|Use an invalid HDMI port to set EDID version using dsSetEdidVersion() | dsERR_INVALID_PARAM | Should Pass |
 * |04|Use an invalid EDID version to set using dsSetEdidVersion() | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_negative_dsSetEdidVersion (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetEdidVersion() correctly retrieves the EDID version during positive scenarios.
 * 
 * **Test Group ID:** Basic: 97@n
 * **Test Case ID:** 355@n
 * 
 * **Dependencies:** The HDMI input sub-system has been initialized using dsHdmiInInit() and the EDID version has been set using dsSetEdidVersion().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |02|Set a known EDID version for a valid HDMI port using dsSetEdidVersion() | dsERR_NONE | Should Pass |
 * |03|Retrieve the EDID version for the same HDMI port using dsGetEdidVersion() | dsERR_NONE & matching EDID version | Should return the same EDID version as set in step 2 |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsGetEdidVersion (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetEdidVersion() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 97@n
 * **Test Case ID:** 356@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Retrieve EDID version without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |03|Use an invalid HDMI port to retrieve EDID version using dsGetEdidVersion() | dsERR_INVALID_PARAM | Should Pass |
 * |04|Use NULL for the `iEdidVersion` parameter and check using dsGetEdidVersion() | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_negative_dsGetEdidVersion (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAllmStatus() correctly retrieves the ALLM status during positive scenarios.
 * 
 * **Test Group ID:** Basic: 98@n
 * **Test Case ID:** 357@n
 * 
 * **Dependencies:** The HDMI input sub-system has been initialized using dsHdmiInInit().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |02|Retrieve the ALLM status for a valid HDMI port using dsGetAllmStatus() | dsERR_NONE | Should retrieve ALLM status successfully |
 * |03|Validate the returned status is either true or false | True or False | Ensure consistency |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsGetAllmStatus (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAllmStatus() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 98@n
 * **Test Case ID:** 358@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Retrieve ALLM status without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |03|Use an invalid HDMI port to retrieve ALLM status using dsGetAllmStatus() | dsERR_INVALID_PARAM | Should Pass |
 * |04|Use NULL for the `allmStatus` parameter and check using dsGetAllmStatus() | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_negative_dsGetAllmStatus (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetSupportedGameFeaturesList() correctly retrieves the list of supported game features during positive scenarios.
 * 
 * **Test Group ID:** Basic: 99@n
 * **Test Case ID:** 359@n
 * 
 * **Dependencies:** The HDMI input sub-system has been initialized using dsHdmiInInit().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |02|Retrieve the list of supported game features using dsGetSupportedGameFeaturesList() | dsERR_NONE | Should retrieve list successfully |
 * |03|Validate the returned list for its consistency and expected values | List contains expected features | Ensure features match documentation/specifications |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsGetSupportedGameFeaturesList (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetSupportedGameFeaturesList() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 99@n
 * **Test Case ID:** 360@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Retrieve the list of supported game features without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |03|Use NULL for the `features` parameter and check using dsGetSupportedGameFeaturesList() | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_negative_dsGetSupportedGameFeaturesList (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAVLatency() correctly retrieves the current AV latency during positive scenarios.
 * 
 * **Test Group ID:** Basic: 100@n
 * **Test Case ID:** 361@n
 * 
 * **Dependencies:** The HDMI input sub-system has been initialized using dsHdmiInInit().@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |02|Retrieve the current AV latency using dsGetAVLatency() | dsERR_NONE | Should retrieve AV latency values successfully |
 * |03|Validate the returned audio latency is within the range [0, 500ms] | 0ms <= audio_latency <= 500ms | Ensure consistency |
 * |04|Validate the returned video latency is within the range [0, 500ms] | 0ms <= video_latency <= 500ms | Ensure consistency |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsGetAVLatency (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetAVLatency() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 100@n
 * **Test Case ID:** 362@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Retrieve the current AV latency without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |03|Use NULL for the `audio_latency` parameter and check using dsGetAVLatency() | dsERR_INVALID_PARAM | Should Pass |
 * |04|Use NULL for the `video_latency` parameter and check using dsGetAVLatency() | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsGetAVLatency() with both parameters as NULL | dsERR_INVALID_PARAM | Should Pass |
 * |06|Call dsHdmiInTerm() to ensure deinitialization | dsERR_NONE | Clean up after test |
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
