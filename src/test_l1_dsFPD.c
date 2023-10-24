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
* @file test_l1_dsFPD.c
* @page Device Settings
* @subpage Front Panel Display
*
* ## Module's Role
* This module includes Level 1 functional tests (success and failure scenarios)
* This is to ensure that the API meets the operational requirements of the Power Manager across all vendors
*
* **Pre-Conditions:**  None@n
* **Dependencies:** None@n
*
* Ref to API Definition specification documentation : [ds-front-panel-display_halSpec.md](../../../docs/pages/ds-front-panel-display_halSpec.md)
*/

#include <string.h>
#include <stdlib.h>

#include <ut.h>
#include <ut_log.h>

/**
 * @brief Ensure dsFPInit() returns correct error codes during positive scenarios
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
 * |01|Call dsFPInit() - initialize the interface for the first time | | dsERR_NONE | Should Pass |
 * |02|Call dsFPTerm() - terminate the interface | | dsERR_NONE | Should Pass |
 * |03|Call dsFPInit() again - reinitialize the interface after termination | | dsERR_NONE | Should confirm the interface can be reinitialized after termination |
 * |04|Call dsFPTerm() - terminate the interface once again | | dsERR_NONE | Should Pass |
 * 
 */
void test_l1_dsFPD_positive_dsFPInit (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsFPInit() handles error scenarios gracefully
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
 * |01|Call dsFPInit() - initialize the interface | | dsERR_NONE | Should Pass |
 * |02|Call dsFPInit() again - attempt to initialize an already initialized interface | | dsERR_ALREADY_INITIALIZED | Should confirm that the function handles double initialization attempts gracefully |
 * |03|Call dsFPTerm() - terminate the interface | | dsERR_NONE | Should Pass |
 * 
 */
void test_l1_dsFPD_negative_dsFPInit (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsFPTerm() returns correct error codes during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 003@n
 * 
 * **Pre-Conditions:**@n
 * The interface is correctly initialized with dsFPInit().
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsFPInit() - initialize the interface | | dsERR_NONE | Should Pass |
 * |02|Call dsFPTerm() - terminate the interface | | dsERR_NONE | Should Pass |
 * |03|Call dsFPInit() - reinitialize the interface | | dsERR_NONE | Should Pass |
 * |04|Call dsFPTerm() - terminate the interface once again | | dsERR_NONE | Should Pass |
 * 
 */
void test_l1_dsFPD_positive_dsFPTerm (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsFPTerm() handles error scenarios gracefully
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 004@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsFPTerm() - attempt to terminate without initializing the interface | | dsERR_NOT_INITIALIZED | Should confirm the function handles termination attempts without initialization gracefully |
 * |02|Call dsFPInit() - initialize the interface | | dsERR_NONE | Should Pass |
 * |03|Call dsFPTerm() - terminate the interface | | dsERR_NONE | Should Pass |
 * |04|Call dsFPTerm() again - attempt to terminate an already terminated interface | | dsERR_NOT_INITIALIZED | Should confirm the function handles double termination attempts gracefully |
 * 
 */
void test_l1_dsFPD_negative_dsFPTerm (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetFPState() correctly sets the Front Panel Display LED state
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 005@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize with dsFPInit()| |dsERR_NONE|Ensure the system is initialized|
 * |02|Call dsSetFPState() with valid inputs|eIndicator: dsFPD_INDICATOR_POWER, state: dsFPD_STATE_OFF|dsERR_NONE| |
 * |03|Call dsSetFPState() and loop through all valid indicators from kIndicators|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON|dsERR_NONE| |
 * |04|Terminate with dsFPTerm()| |dsERR_NONE|Ensure the system is terminated|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_positive_dsSetFPState (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetFPState() handles error scenarios correctly
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 006@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsSetFPState() without initializing (dsFPInit() not called)|eIndicator: dsFPD_INDICATOR_POWER, state: dsFPD_STATE_OFF|dsERR_NOT_INITIALIZED|Validate that the function checks for initialization|
 * |02|Initialize with dsFPInit()| |dsERR_NONE|Ensure the system is initialized|
 * |03|Call dsSetFPState() with an invalid eIndicator value|eIndicator: dsFPD_INDICATOR_MAX, state: dsFPD_STATE_OFF|dsERR_INVALID_PARAM|Validate invalid parameter handling for eIndicator|
 * |04|Call dsSetFPState() and loop through all valid indicators from kIndicators with an invalid state value|eIndicator: [Valid Indicator], state: dsFPD_STATE_MAX|Validate invalid parameter handling for state|
 * |03|Call dsSetFPState() and loop through the indicators from the diff of kIndicators and dsFPDIndicator_t |eIndicator: [Invalid Indicator], state: dsFPD_STATE_OFF|dsERR_OPERATION_NOT_SUPPORTED|Validate invalid parameter handling for eIndicator|
 * |05|Terminate with dsFPTerm()| |dsERR_NONE|Ensure the system is terminated|
 * |06|Call dsSetFPState() after termination|eIndicator: dsFPD_INDICATOR_POWER, state: dsFPD_STATE_OFF|dsERR_NOT_INITIALIZED|Validate it checks for initialization even after termination|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_negative_dsSetFPState (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetFPBlink() sets the blink pattern successfully
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 007@n
 * 
 * **Pre-Conditions:**@n
 * dsFPInit() must be called and FP State must be "ON".
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize with dsFPInit()| |dsERR_NONE|Ensure the system is initialized|
 * |02|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |03|Call dsSetFPBlink() and loop through all valid indicators from kIndicators| eIndicator: [Valid Indicator], uBlinkDuration: 500, uBlinkIterations: 10 |dsERR_NONE|Should validate that the blink setup works correctly|
 * |04|Terminate with dsFPTerm()| |dsERR_NONE|Ensure the system is terminated|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 * 
 */
void test_l1_dsFPD_positive_dsSetFPBlink (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetFPBlink() handles error scenarios gracefully
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 008@n
 * 
 * **Pre-Conditions:**@n
 * dsFPInit() may or may not be called based on variation.
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsSetFPBlink() without calling dsFPInit() |eIndicator: dsFPD_INDICATOR_POWER, uBlinkDuration: 500, uBlinkIterations: 10 |dsERR_NOT_INITIALIZED|Should validate that the function handles call without initialization|
 * |02|Initialize with dsFPInit()| |dsERR_NONE|Ensure the system is initialized|
 * |02|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |03|Pass an invalid eIndicator parameter to dsSetFPBlink() |eIndicator: dsFPD_INDICATOR_MAX, uBlinkDuration: 500, uBlinkIterations: 10 |dsERR_INVALID_PARAM|Should validate that the function handles invalid indicator gracefully|
 * |04|Pass an invalid uBlinkDuration parameter to dsSetFPBlink()|eIndicator: dsFPD_INDICATOR_POWER, uBlinkDuration: 20000, uBlinkIterations: 10 |dsERR_INVALID_PARAM|Should validate that the function handles invalid blink duration gracefully|
 * |05|Pass an invalid uBlinkIterations parameter to dsSetFPBlink()|eIndicator: dsFPD_INDICATOR_POWER, uBlinkDuration: 500, uBlinkIterations: 200 |dsERR_INVALID_PARAM|Should validate that the function handles invalid blink iterations gracefully|
 * |02|Set all valid indicators to dsFPD_STATE_OFF using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_OFF |dsERR_NONE|Ensure the system is initialized|
 * |06|Call dsSetFPBlink() and loop through all valid indicators from kIndicators|eIndicator: [Valid Indicator], uBlinkDuration: 500, uBlinkIterations: 10 |dsERR_OPERATION_NOT_SUPPORTED|Testing if function adheres to pre-condition of FP State being “ON”|
 * |07|Terminate with dsFPTerm()| |dsERR_NONE|Ensure the system is terminated|
 * |08|Attempt to set blink pattern after dsFPTerm() has been called|eIndicator: dsFPD_INDICATOR_POWER, uBlinkDuration: 500, uBlinkIterations: 10 |dsERR_NOT_INITIALIZED|Should fail due to termination|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 * 
 */
void test_l1_dsFPD_negative_dsSetFPBlink (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetFPBrightness() sets the brightness level correctly under positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 009@n
 * 
 * **Pre-Conditions:**@n
 * dsFPInit() must be called and FP State must be "ON" before calling this API.
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize with dsFPInit()| |dsERR_NONE|Ensure the system is initialized|
 * |02|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |02|Call dsSetBrightness() and loop through all valid indicators from kIndicators|eIndicator: [Valid Indicator], eBrightness: 50+5x|dsERR_NONE|Brightness is set without any issues|
 * |03|Terminate with dsFPTerm()| |dsERR_NONE|Ensure the system is terminated|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 * 
 */
void test_l1_dsFPD_positive_dsSetFPBrightness (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetFPBrightness() handles error scenarios gracefully
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 010@n
 * 
 * **Pre-Conditions:**@n
 * dsFPInit() may or may not be called based on variation.
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsSetFPBrightness() without calling dsFPInit() |eIndicator: dsFPD_INDICATOR_POWER, eBrightness: 50 |dsERR_NOT_INITIALIZED|Should validate that the function handles call without initialization|
 * |02|Initialize with dsFPInit()| |dsERR_NONE|Ensure the system is initialized|
 * |03|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |04|Pass an invalid eIndicator parameter to dsSetFPBrightness() |eIndicator: dsFPD_INDICATOR_MAX, eBrightness: 50 |dsERR_INVALID_PARAM|Should validate that the function handles invalid indicator gracefully|
 * |05|Pass an invalid eBrightness parameter to dsSetFPBrightness()|eIndicator: dsFPD_INDICATOR_POWER, eBrightness: 200 |dsERR_INVALID_PARAM|Should validate that the function handles invalid brightness gracefully|
 * |06|Set all valid indicators to dsFPD_STATE_OFF using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_OFF|dsERR_OPERATION_NOT_SUPPORTED|Validate invalid parameter handling for eIndicator|
 * |07|Call dsSetFPBrightness() and loop through all valid indicators from kIndicators|eIndicator: [Valid Indicator], eBrightness: 50 |dsERR_OPERATION_NOT_SUPPORTED|Testing if function adheres to pre-condition of FP State being “ON”|
 * |08|Terminate with dsFPTerm()| |dsERR_NONE|Ensure the system is terminated|
 * |09|Attempt to set brightness after dsFPTerm() has been called|eIndicator: dsFPD_INDICATOR_POWER, eBrightness: 50 |dsERR_NOT_INITIALIZED|Should fail due to termination|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 * 
 */
void test_l1_dsFPD_negative_dsSetFPBrightness (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetFPBrightness() retrieves the brightness level correctly under positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 011@n
 * 
 * **Pre-Conditions:**@n
 * dsFPInit() must be called and FP State must be "ON" before calling this API.
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize with dsFPInit()| |dsERR_NONE|Ensure the system is initialized|
 * |02|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |02|Call dsGetFPBrightness() with specific valid indicator and store the value|eIndicator: dsFPD_INDICATOR_POWER|dsERR_NONE|Brightness is retrieved without any issues|
 * |03|Call dsGetFPBrightness() and loop through all valid indicators from kIndicators|eIndicator: [Valid Indicator]|dsERR_NONE|Ensure consistent readings|
 * |04|Compare the two retrieved brightness values from step 02 and step 03 for dsFPD_INDICATOR_POWER||Brightness values should be equal|Ensuring consistency in retrieved brightness over consecutive calls|
 * |05|Terminate with dsFPTerm()| |dsERR_NONE|Ensure the system is terminated|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 * 
 */
void test_l1_dsFPD_positive_dsGetFPBrightness (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetFPBrightness() handles error scenarios correctly
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 012@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetFPBrightness() without initializing (dsFPInit() not called)|eIndicator: dsFPD_INDICATOR_POWER, pBrightness: dsFPDBrightness_t*|dsERR_NOT_INITIALIZED|Validate that the function checks for initialization|
 * |02|Initialize with dsFPInit()| |dsERR_NONE|Ensure the system is initialized|
 * |03|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |04|Call dsGetFPBrightness() with an invalid eIndicator value|eIndicator: dsFPD_INDICATOR_MAX, pBrightness: dsFPDBrightness_t*|dsERR_INVALID_PARAM|Validate invalid parameter handling|
 * |05|Call dsGetFPBrightness() with an invalid pBrightness value (NULL)|eIndicator: dsFPD_INDICATOR_POWER, pBrightness: NULL|dsERR_INVALID_PARAM|Ensure it handles NULL pointer input for pBrightness|
 * |06|Set all valid indicators to dsFPD_STATE_OFF using dsSetFPState() |eIndicator: [Valid Indicator], state: dsFPD_STATE_OFF|dsERR_OPERATION_NOT_SUPPORTED|Validate invalid parameter handling for eIndicator|
 * |07|Call dsGetFPBrightness() and loop through all valid indicators from kIndicators|eIndicator: [Valid Indicator], pBrightness: dsFPDBrightness_t*|dsERR_OPERATION_NOT_SUPPORTED|Ensure it checks for FP state and returns operation not supported when it is "OFF"|
 * |08|Terminate with dsFPTerm()| |dsERR_NONE|Ensure the system is terminated|
 * |09|Call dsGetFPBrightness() after termination|eIndicator: dsFPD_INDICATOR_POWER, pBrightness: dsFPDBrightness_t*|dsERR_NOT_INITIALIZED|Validate it checks for initialization even after termination|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 * 
 */
void test_l1_dsFPD_negative_dsGetFPBrightness (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetFPState() retrieves the correct state
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 013@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize with dsFPInit()||dsERR_NONE|Ensure the system is initialized|
 * |02|Call dsGetFPState() with valid eIndicator and state parameters|eIndicator: dsFPD_INDICATOR_POWER, state: dsFPDState_t*|dsERR_NONE|Ensure that the function can retrieve the state|
 * |03|Call dsGetFPState() once again for all and store results|eIndicator: dsFPD_INDICATOR_POWER, state: dsFPDState_t*|dsERR_NONE|Retrieve the state for comparison in next step|
 * |04|Call dsGetFPState() and loop through all valid indicators from kIndicators|eIndicator: [Valid Indicator], state: dsFPDState_t*|dsERR_NONE|Ensure that the function can retrieve the state|
 * |05|Compare the state retrieved in step 02 and 03||The states should be the same|Ensure that repeated calls provide consistent output|
 * |06|Terminate with dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_positive_dsGetFPState (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetFPState() handles error scenarios correctly
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 014@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetFPState() without initializing (dsFPInit() not called)|eIndicator: dsFPD_INDICATOR_POWER, state: dsFPDState_t*|dsERR_NOT_INITIALIZED|Validate that the function checks for initialization|
 * |02|Initialize with dsFPInit()||dsERR_NONE|Ensure the system is initialized|
 * |03|Call dsGetFPState() with an invalid eIndicator value|eIndicator: dsFPD_INDICATOR_MAX, state: dsFPDState_t*|dsERR_INVALID_PARAM|Validate invalid parameter handling for eIndicator|
 * |04|Call dsGetFPState() with an invalid state pointer|eIndicator: [Valid Indicator], state: NULL|dsERR_INVALID_PARAM|Validate invalid parameter handling for state|
 * |03|Call dsSetFPState() and loop through the indicators from the diff of kIndicators and dsFPDIndicator_t |eIndicator: dsFPD_INDICATOR_MAX, state: dsFPD_STATE_OFF|dsERR_OPERATION_NOT_SUPPORTED|Validate invalid parameter handling for eIndicator|
 * |05|Terminate with dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * |06|Call dsGetFPState() after termination|eIndicator: dsFPD_INDICATOR_POWER, state: dsFPDState_t*|dsERR_NOT_INITIALIZED|Validate it checks for initialization even after termination|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 * 
 */

void test_l1_dsFPD_negative_dsGetFPState (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetFPColor() sets the color correctly
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 015@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize with dsFPInit()||dsERR_NONE|Ensure the system is initialized|
 * |02|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |03|Call dsSetFPColor() with all valid eIndicator and all valid eColor parameters from kIndidicators|eIndicator: [Valid Indicator], eColor: [Valid Color]|dsERR_NONE|Ensure that the function can set the color|
 * |04|Terminate with dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_positive_dsSetFPColor (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetFPColor() handles error scenarios correctly
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 016@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsSetFPColor() without initializing (dsFPInit() not called)|eIndicator: dsFPD_INDICATOR_POWER, eColor: [Valid Color]|dsERR_NOT_INITIALIZED|Validate that the function checks for initialization|
 * |02|Initialize with dsFPInit()||dsERR_NONE|Ensure the system is initialized|
 * |03|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |04|Call dsSetFPColor() and loop all valid indicators with all invalid colors based on kIndicators|eIndicator: [Valid Indicator], eColor: [Invalid Color]|dsERR_INVALID_PARAM|Validate invalid parameter handling for eColor|
 * |05|Call dsSetFPColor() and with invalid indictator|eIndicator: dsFPD_INDICATOR_MAX, eColor: [Invalid Color]|dsERR_INVALID_PARAM|Validate invalid parameter handling for eColor|
 * |06|Set all valid indicators to dsFPD_STATE_OFF using dsSetFPState()|eIndicator: [Valid Indicator], State: OFF|dsERR_NONE|Ensure the FPD state is set to OFF|
 * |07|Call dsSetFPColor() with all indicators|eIndicator: [Indicator], eColor: [Valid Color]|dsERR_OPERATION_NOT_SUPPORTED|Validate that function checks if FPD state is OFF|
 * |08|Terminate with dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * |09|Call dsSetFPColor() after termination|eIndicator: dsFPD_INDICATOR_POWER, eColor: [Valid Color]|dsERR_NOT_INITIALIZED|Validate it checks for initialization even after termination|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_negative_dsSetFPColor (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetFPColor() correctly retrieves the color of a Front Panel Display LED
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 017@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize with dsFPInit()||dsERR_NONE|Ensure the system is initialized|
 * |02|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState() and reading all the valid configurations|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |03|Call dsGetFPColor() with all valid indicators|eIndicator: [Valid Indicator], pColor: dsFPDColor_t*|dsERR_NONE|Ensure the function can retrieve color|
 * |04|Verify that the color retrieved matches the known color set in Step 02|Color from Step 03: [Retrieved Color]|Colors should match|[Retrieved Color] should be [Known Color]|
 * |05|Call dsGetFPColor() again and compare results|eIndicator: [Valid Indicator], pColor: dsFPDColor_t*|dsERR_NONE and same color as Step 04|Ensure consistency in repeated calls|
 * |06|Terminate with dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_positive_dsGetFPColor (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetFPColor() handles error scenarios correctly
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 018@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetFPColor() without initializing (dsFPInit() not called)|eIndicator: dsFPD_INDICATOR_POWER, pColor: dsFPDColor_t*|dsERR_NOT_INITIALIZED|Validate that the function checks for initialization|
 * |02|Initialize with dsFPInit()||dsERR_NONE|Ensure the system is initialized|
 * |02|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |03|Call dsGetFPColor() with an invalid eIndicator value|eIndicator: dsFPD_INDICATOR_MAX, pColor: dsFPDColor_t*|dsERR_INVALID_PARAM|Validate invalid parameter handling for eIndicator|
 * |04|Call dsGetFPColor() with a null pointer for pColor|eIndicator: dsFPD_INDICATOR_POWER, pColor: NULL|dsERR_INVALID_PARAM|Validate invalid parameter handling for pColor|
 * |05|Set all valid indicators to dsFPD_STATE_OFF using dsSetFPState()|eIndicator: [Valid Indicator], State: OFF|dsERR_NONE|Ensure the FPD state is set to OFF|
 * |06|Call dsGetFPColor() with all indicators|eIndicator: [Indicator], pColor: dsFPDColor_t*|dsERR_OPERATION_NOT_SUPPORTED|Validate that function checks if FPD state is OFF|
 * |07|Terminate with dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * |08|Call dsGetFPColor() after termination|eIndicator: dsFPD_INDICATOR_POWER, pColor: dsFPDColor_t*|dsERR_NOT_INITIALIZED|Validate it checks for initialization even after termination|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_negative_dsGetFPColor (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Validate the positive flow of dsSetFPDMode()
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 19@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|---------|---------------|-----|
 * |01|Initialize using dsFPInit()||dsERR_NONE|Ensure the system is initialized|
 * |02|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |03|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_ANY|dsERR_NONE|API should set mode successfully|
 * |04|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_TEXT|dsERR_NONE|API should set mode successfully|
 * |05|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_CLOCK|dsERR_NONE|API should set mode successfully|
 * |06|Terminate using dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_positive_dsSetFPDMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Validate the robustness and boundary conditions of dsSetFPDMode()
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 020@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|---------|---------------|-----|
 * |01|Call dsSetFPDMode() without initializing the system|eMode: dsFPD_MODE_ANY|dsERR_NOT_INITIALIZED|API should not work without initialization|
 * |02|Initialize using dsFPInit()||dsERR_NONE|Ensure the system is initialized|
 * |02|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |03|Call dsSetFPDMode() with an invalid parameter|eMode: dsFPD_MODE_MAX|dsERR_INVALID_PARAM|API should validate parameter|
 * |04|Set all valid indicators to dsFPD_STATE_OFF using dsSetFPState() if applicable|Using a separate function or mechanism if available|dsERR_NONE|Ensure the FP state is "OFF"|
 * |05|Call dsSetFPDMode() while FP State is "OFF"|eMode: dsFPD_MODE_ANY|dsERR_OPERATION_NOT_SUPPORTED|API should not operate when FP state is "OFF"|
 * |07|Terminate using dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * |08|Call dsSetFPDMode() after termination|eMode: dsFPD_MODE_ANY|dsERR_NOT_INITIALIZED|API should not work after termination|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_negative_dsSetFPDMode (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetFPTime() correctly sets the time on 7-Segment Front Panel Display LEDs
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 021@n
 * 
 * **Pre-Conditions:**@n
 * 7-Segment display LEDs are present on the device and dsFPD_MODE_CLOCK is supported.
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize with dsFPInit()||dsERR_NONE|Ensure the system is initialized|
 * |02|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |03|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_CLOCK|dsERR_NONE|API should set mode successfully|
 * |04|Call dsSetFPTime() with valid parameters for 24-hour format|eTimeFormat: dsFPD_TIME_24_HOUR, uHour: 14, uMinutes: 30|dsERR_NONE|Check the function in 24-hour format|
 * |05|Call dsSetFPTime() with valid parameters for 12-hour format|eTimeFormat: dsFPD_TIME_12_HOUR, uHour: 2, uMinutes: 30|dsERR_NONE|Check the function in 12-hour format|
 * |06|Terminate with dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_positive_dsSetFPTime (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetFPTime() handles error scenarios correctly
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 022@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsSetFPTime() without initializing (dsFPInit() not called)|eTimeFormat: 24hrs, uHour: 14, uMinutes: 30|dsERR_NOT_INITIALIZED|Validate that the function checks for initialization|
 * |02|Initialize with dsFPInit()||dsERR_NONE|Ensure the system is initialized|
 * |03|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |04|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_CLOCK|dsERR_NONE|API should set mode successfully|
 * |05|Call dsSetFPTime() with an invalid hour value|eTimeFormat: 24hrs, uHour: 25, uMinutes: 30|dsERR_INVALID_PARAM|Validate invalid parameter handling for uHour|
 * |06|Call dsSetFPTime() with an invalid minute value|eTimeFormat: 24hrs, uHour: 14, uMinutes: 60|dsERR_INVALID_PARAM|Validate invalid parameter handling for uMinutes|
 * |07|Call dsSetFPTime() with 12hr format and hour value > 12|eTimeFormat: 12hrs, uHour: 14, uMinutes: 30|dsERR_INVALID_PARAM|Check the consistency between eTimeFormat and uHour|
 * |08|Call dsSetFPTime() with 12hr format with invalid minute value|eTimeFormat: 12hrs, uHour: 2, uMinutes: 60|dsERR_INVALID_PARAM|Check the consistency between eTimeFormat and uHour|
 * |09|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_TEXT|dsERR_NONE|API should set mode successfully|
 * |10|Call dsSetFPTime() with valid parameters for 24-hour format|eTimeFormat: dsFPD_TIME_24_HOUR, uHour: 14, uMinutes: 30|dsERR_OPERATION_NOT_SUPPORTED|Check the function in 24-hour format|
 * |11|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_CLOCK|dsERR_NONE|API should set mode successfully|
 * |12|Set all valid indicators to dsFPD_STATE_OFF using dsSetFPState()|eIndicator: [Valid Indicator], State: OFF|dsERR_NONE|Ensure the FPD state is set to OFF|
 * |13|Call dsSetFPTime() with FP state set to "OFF"|eTimeFormat: 24hrs, uHour: 14, uMinutes: 30|dsERR_OPERATION_NOT_SUPPORTED|Validate that function checks if FPD state is OFF|
 * |14|Terminate with dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * |15|Call dsSetFPTime() after termination|eTimeFormat: 24hrs, uHour: 14, uMinutes: 30|dsERR_NOT_INITIALIZED|Validate it checks for initialization even after termination|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_negative_dsSetFPTime (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetFPText() correctly sets the text on 7-Segment Front Panel Display LEDs
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 023@n
 * 
 * **Pre-Conditions:**@n
 * 7-Segment display LEDs are present on the device and dsFPD_MODE_TEXT is supported.
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize with dsFPInit()||dsERR_NONE|Ensure the system is initialized|
 * |02|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |03|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_TEXT|dsERR_NONE|API should set mode successfully|
 * |04|Call dsSetFPText() with valid text|pText: "HELLO"|dsERR_NONE|Check the function with valid text|
 * |05|Validate the FP display shows the correct text||"HELLO" is displayed|Use appropriate tools/methods for validation|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_positive_dsSetFPText (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetFPText() handles error scenarios correctly
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 024@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsSetFPText() without initializing (dsFPInit() not called)|pText: "HELLO"|dsERR_NOT_INITIALIZED|Validate that the function checks for initialization|
 * |02|Initialize with dsFPInit()||dsERR_NONE|Ensure the system is initialized|
 * |03|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |04|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_TEXT|dsERR_NONE|API should set mode successfully|
 * |05|Call dsSetFPText() with NULL pointer|pText: NULL|dsERR_INVALID_PARAM|Validate invalid parameter handling for NULL pText|
 * |06|Call dsSetFPText() with text longer than 10 characters|pText: "LONGTEXTHERE"|dsERR_INVALID_PARAM|Validate invalid parameter handling for text length|
 * |07|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_CLOCK|dsERR_NONE|API should set mode successfully|
 * |08|Call dsSetFPText() with valid text|pText: "HELLO"|dsERR_OPERATION_NOT_SUPPORTED|Check the function with valid text|
 * |09|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_TEXT|dsERR_NONE|API should set mode successfully|
 * |10|Set all valid indicators to dsFPD_STATE_OFF using dsSetFPState()|eIndicator: [Valid Indicator], State: OFF|dsERR_NONE|Ensure the FPD state is set to OFF|
 * |11|Call dsSetFPText() with FP state set to "OFF"|pText: "HELLO"|dsERR_OPERATION_NOT_SUPPORTED|Validate that function checks if FPD state is OFF|
 * |12|Terminate with dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * |13|Call dsSetFPText() after termination|pText: "HELLO"|dsERR_NOT_INITIALIZED|Validate it checks for initialization even after termination|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_negative_dsSetFPText (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetFPTextBrightness() correctly sets the brightness of 7-Segment Front Panel Display LEDs
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 025@n
 * 
 * **Pre-Conditions:**@n
 * 7-Segment display LEDs are present on the device and dsFPD_MODE_TEXT is supported.
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize with dsFPInit()||dsERR_NONE|Ensure the system is initialized|
 * |02|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |03|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_TEXT|dsERR_NONE|API should set mode successfully|
 * |04|Call dsSetFPTextBrightness() with valid eIndicator and eBrightness|eIndicator: dsFPD_TEXTDISP_TEXT, eBrightness: 70|dsERR_NONE|Check the function with valid parameters|
 * |05|Validate the FP display shows the correct brightness level||Brightness level 70 is set|Use appropriate tools/methods for validation|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_positive_dsSetFPTextBrightness (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetFPTextBrightness() handles error scenarios correctly
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 026@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsSetFPTextBrightness() without initializing (dsFPInit() not called)|eIndicator: dsFPD_TEXTDISP_TEXT, eBrightness: 70|dsERR_NOT_INITIALIZED|Validate that the function checks for initialization|
 * |02|Initialize with dsFPInit()||dsERR_NONE|Ensure the system is initialized|
 * |03|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |04|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_TEXT|dsERR_NONE|API should set mode successfully|
 * |05|Call dsSetFPTextBrightness() with invalid eBrightness (out of range)|eIndicator: dsFPD_TEXTDISP_TEXT, eBrightness: 110|dsERR_INVALID_PARAM|Validate invalid parameter handling for brightness level|
 * |06|Call dsSetFPTextBrightness() with invalid indicator|eIndicator: dsFPD_TEXTDISP_MAX, eBrightness: 110|dsERR_INVALID_PARAM|Validate invalid parameter handling for brightness level|
 * |07|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_CLOCK|dsERR_NONE|API should set mode successfully|
 * |08|Call dsSetFPTextBrightness() with valid eIndicator and eBrightness|eIndicator: dsFPD_TEXTDISP_TEXT, eBrightness: 70|dsERR_OPERATION_NOT_SUPPORTED|Check the function with valid parameters|
 * |09|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_TEXT|dsERR_NONE|API should set mode successfully|
 * |10|Set all valid indicators to dsFPD_STATE_OFF using dsSetFPState()|eIndicator: [Valid Indicator], State: OFF|dsERR_NONE|Ensure the FPD state is set to OFF|
 * |11|Call dsSetFPTextBrightness() with all indicators|eIndicator: [Indicator], eBrightness: 70|dsERR_OPERATION_NOT_SUPPORTED|Validate that function checks if FPD state is OFF|
 * |12|Terminate with dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * |13|Call dsSetFPTextBrightness() after termination|eIndicator: dsFPD_TEXTDISP_TEXT, eBrightness: 70|dsERR_NOT_INITIALIZED|Validate it checks for initialization even after termination|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_negative_dsSetFPTextBrightness (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetFPTextBrightness() correctly gets the brightness of 7-Segment Front Panel Display LEDs
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 027@n
 * 
 * **Pre-Conditions:**@n
 * 7-Segment display LEDs are present on the device and dsFPD_MODE_TEXT is supported.
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize with dsFPInit()||dsERR_NONE|Ensure the system is initialized|
 * |02|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |03|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_TEXT|dsERR_NONE|API should set mode successfully|
 * |04|Call dsGetFPTextBrightness() with valid eIndicator|eIndicator: dsFPD_TEXTDISP_TEXT, eBrightness: Pointer to brightness variable|dsERR_NONE|Check function retrieves the correct brightness level|
 * |05|Call dsGetFPTextBrightness() with valid eIndicator|eIndicator: dsFPD_TEXTDISP_TEXT, eBrightness: Pointer to brightness variable|dsERR_NONE|Check function retrieves the correct brightness level|
 * |06|Compare the results from step 4/5 and make sure they're the same||Success|The values should be the same|
 * |07|Terminate with dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_positive_dsGetFPTextBrightness (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsGetFPTextBrightness() handles error scenarios correctly
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 028@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetFPTextBrightness() without initializing (dsFPInit() not called)|eIndicator: dsFPD_TEXTDISP_TEXT, eBrightness: Pointer to brightness variable|dsERR_NOT_INITIALIZED|Validate that the function checks for initialization|
 * |02|Initialize with dsFPInit()||dsERR_NONE|Ensure the system is initialized|
 * |03|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |04|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_TEXT|dsERR_NONE|API should set mode successfully|
 * |05|Call dsGetFPTextBrightness() with NULL for eBrightness|eIndicator: dsFPD_TEXTDISP_TEXT, eBrightness: NULL|dsERR_INVALID_PARAM|Check function detects NULL pointer parameter|
 * |06|Call dsGetFPTextBrightness() with invalid indicator|eIndicator: dsFPD_TEXTDISP_MAX, eBrightness: NULL|dsERR_INVALID_PARAM|Check function detects NULL pointer parameter|
 * |07|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_CLOCK|dsERR_NONE|API should set mode successfully|
 * |08|Call dsGetFPTextBrightness() with valid eIndicator|eIndicator: dsFPD_TEXTDISP_TEXT, eBrightness: Pointer to brightness variable|dsERR_OPERATION_NOT_SUPPORTED|Check function retrieves the correct brightness level|
 * |09|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_TEXT|dsERR_NONE|API should set mode successfully|
 * |10|Set all valid indicators to dsFPD_STATE_OFF using dsSetFPState()|eIndicator: [Valid Indicator], State: OFF|dsERR_NONE|Ensure the FPD state is set to OFF|
 * |11|Call dsGetFPTextBrightness() with all indicators|eIndicator: [Valid Indicator], eBrightness: Pointer to brightness variable|dsERR_OPERATION_NOT_SUPPORTED|Validate that function checks if FPD state is OFF|
 * |12|Terminate with dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * |13|Call dsGetFPTextBrightness() after termination|eIndicator: dsFPD_TEXTDISP_TEXT, eBrightness: Pointer to brightness variable|dsERR_NOT_INITIALIZED|Validate it checks for initialization even after termination|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_negative_dsGetFPTextBrightness (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsFPEnableClockDisplay() correctly enables/disables the clock display
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 029@n
 * 
 * **Pre-Conditions:**@n
 * The device supports 7-Segment display LEDs and clock display is available.
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize with dsFPInit()||dsERR_NONE|Ensure the system is initialized|
 * |02|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |03|Enable clock display using dsFPEnableClockDisplay()|enable: 1|dsERR_NONE|Validate that clock display can be enabled|
 * |04|Disable clock display using dsFPEnableClockDisplay()|enable: 0|dsERR_NONE|Validate that clock display can be disabled|
 * |05|Terminate with dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_positive_dsFPEnableCLockDisplay (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsFPEnableClockDisplay() handles error scenarios correctly
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 030@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsFPEnableClockDisplay() without initializing (dsFPInit() not called)|enable: 1|dsERR_NOT_INITIALIZED|Validate that the function checks for initialization|
 * |02|Initialize with dsFPInit()||dsERR_NONE|Ensure the system is initialized|
 * |03|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |04|Call dsFPEnableClockDisplay() with invalid value for enable|enable: 2|dsERR_INVALID_PARAM|Check function detects invalid parameter|
 * |05|Set all valid indicators to dsFPD_STATE_OFF using dsSetFPState()|Using a separate function or mechanism if available|dsERR_NONE|Simulate FP state being "OFF"|
 * |06|Call dsFPEnableClockDisplay() with FP State "OFF"|enable: 1|dsERR_OPERATION_NOT_SUPPORTED|Check that operation is not supported when FP State is "OFF"|
 * |07|Terminate with dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * |08|Call dsFPEnableClockDisplay() after termination|enable: 1|dsERR_NOT_INITIALIZED|Validate it checks for initialization even after termination|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_negative_dsFPEnableCLockDisplay (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetFPScroll() successfully sets scrolling on the 7-segment display
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 031@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None
 * **User Interaction:** Observe the Front Panel Display LEDs
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|---------|---------------|-----|
 * |01|Initialize using dsFPInit()||dsERR_NONE|Ensure the system is initialized|
 * |02|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |02|Set FP State to "ON" if applicable|Using a separate function or mechanism if available|dsERR_NONE|Ensure the FP state is "ON"|
 * |03|Call dsSetFPScroll() for horizontal scrolling with valid parameters|uScrollHoldOnDur: 1000, uHorzScrollIterations: 5, uVertScrollIterations: 0|dsERR_NONE|Horizontal scrolling should occur on the display. Observe for text movement from right to left|
 * |04|Wait for the duration of the scroll|||Allow time for the text to scroll horizontally|
 * |05|Call dsSetFPScroll() for vertical scrolling with valid parameters|uScrollHoldOnDur: 1000, uHorzScrollIterations: 0, uVertScrollIterations: 5|dsERR_NONE|Vertical scrolling should occur on the display. Observe for text movement from bottom to top|
 * |06|Wait for the duration of the scroll|||Allow time for the text to scroll vertically|
 * |07|Call dsSetFPScroll() with minimum valid parameters for quick scrolling|uScrollHoldOnDur: 100, uHorzScrollIterations: 1, uVertScrollIterations: 0|dsERR_NONE|Quick horizontal scrolling should occur on the display|
 * |08|Wait for the duration of the scroll|||Allow time for the quick scroll|
 * |09|Terminate using dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_positive_dsSetFPScroll (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetFPScroll() handles error scenarios correctly
 * 
 * @todo do we have a max number on duration or iterations?
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 032@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|---------|---------------|-----|
 * |01|Call dsSetFPScroll() without initializing (dsFPInit() not called)|uScrollHoldOnDur: 1000, uHorzScrollIterations: 5, uVertScrollIterations: 5|dsERR_NOT_INITIALIZED|Validate that the function checks for initialization|
 * |02|Initialize with dsFPInit()||dsERR_NONE|Ensure the system is initialized|
 * |02|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |03|Call dsSetFPScroll() with invalid value for uScrollHoldOnDur|uScrollHoldOnDur: 0, uHorzScrollIterations: 5, uVertScrollIterations: 5|dsERR_INVALID_PARAM|Check function detects invalid parameter|
 * |04|Call dsSetFPScroll() with both horizontal and vertical scroll iterations|uScrollHoldOnDur: 1000, uHorzScrollIterations: 5, uVertScrollIterations: 5|dsERR_INVALID_PARAM|Validate it detects conflicting scroll directions|
 * |05|Set all valid indicators to dsFPD_STATE_OFF using dsSetFPState()|Using a separate function or mechanism if available|dsERR_NONE|Simulate FP state being "OFF"|
 * |06|Call dsSetFPScroll() with FP State "OFF"|uScrollHoldOnDur: 1000, uHorzScrollIterations: 5, uVertScrollIterations: 0|dsERR_OPERATION_NOT_SUPPORTED|Check that operation is not supported when FP State is "OFF"|
 * |08|Terminate with dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * |09|Call dsSetFPScroll() after termination|uScrollHoldOnDur: 1000, uHorzScrollIterations: 5, uVertScrollIterations: 0|dsERR_NOT_INITIALIZED|Validate it checks for initialization even after termination|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_negative_dsSetFPScroll (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Ensure dsSetFPTimeFormat() successfully sets the time format on the 7-segment display
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 033@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|---------|---------------|-----|
 * |01|Initialize using dsFPInit()||dsERR_NONE|Ensure the system is initialized|
 * |02|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |03|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_CLOCK|dsERR_NONE|API should set mode successfully|
 * |04|Call dsSetFPTimeFormat() with a valid 12-hour format|eTimeFormat: 12_HOUR_FORMAT|dsERR_NONE|Attempt to set time in 12-hour format|
 * |05|Call dsSetFPTimeFormat() with a valid 24-hour format|eTimeFormat: 24_HOUR_FORMAT|dsERR_NONE|Attempt to set time in 24-hour format|
 * |06|Terminate using dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_positive_dsSetFPTimeFormat (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Validate the robustness and boundary conditions of dsSetFPTimeFormat()
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 034@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|---------|---------------|-----|
 * |01|Call dsSetFPTimeFormat() without initializing the system|eTimeFormat: 12_HOUR_FORMAT|dsERR_NOT_INITIALIZED|API should not work without initialization|
 * |02|Initialize using dsFPInit()||dsERR_NONE|Ensure the system is initialized|
 * |03|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |04|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_CLOCK|dsERR_NONE|API should set mode successfully|
 * |05|Call dsSetFPTimeFormat() with an invalid time format|eTimeFormat: INVALID_FORMAT|dsERR_INVALID_PARAM|API should validate parameter|
 * |06|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_TEXT|dsERR_NONE|API should set mode successfully|
 * |07|Call dsSetFPTimeFormat() with a valid 12-hour format|eTimeFormat: 12_HOUR_FORMAT|dsERR_OPERATION_NOT_SUPPORTED|Attempt to set time in 12-hour format|
 * |08|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_CLOCK|dsERR_NONE|API should set mode successfully|
 * |09|Set all valid indicators to dsFPD_STATE_OFF using dsSetFPState() if applicable|Using a separate function or mechanism if available|dsERR_NONE|Ensure the FP state is "OFF"|
 * |10|Call dsSetFPTimeFormat() while FP State is "OFF"|eTimeFormat: 12_HOUR_FORMAT|dsERR_OPERATION_NOT_SUPPORTED|API should not operate when FP state is "OFF"|
 * |11|Terminate using dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * |12|Call dsSetFPTimeFormat() after termination|eTimeFormat: 24_HOUR_FORMAT|dsERR_NOT_INITIALIZED|API should not work after termination|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_negative_dsSetFPTimeFormat (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Validate the functionality of dsGetFPTimeFormat()
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 035@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|---------|---------------|-----|
 * |01|Initialize using dsFPInit()||dsERR_NONE|Ensure the system is initialized|
 * |02|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |03|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_CLOCK|dsERR_NONE|API should set mode successfully|
 * |04|Call dsGetFPTimeFormat() to retrieve the set time format|dsFPDTimeFormat_t*|dsERR_NONE|Should get the previously set time format|
 * |05|Call dsGetFPTimeFormat() to retrieve the new time format|dsFPDTimeFormat_t*|dsERR_NONE|Should get the newly set time format|
 * |06|Compare the results to make sure the returned values are the same||Success|The values should be the same|
 * |07|Terminate using dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_positive_dsGetFPTimeFormat (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Validate the robustness and boundary conditions of dsGetFPTimeFormat()
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 036@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|---------|---------------|-----|
 * |01|Call dsGetFPTimeFormat() without initializing the system|dsFPDTimeFormat_t*|dsERR_NOT_INITIALIZED|API should not work without initialization|
 * |02|Initialize using dsFPInit()||dsERR_NONE|Ensure the system is initialized|
 * |02|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |03|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_CLOCK|dsERR_NONE|API should set mode successfully|
 * |03|Call dsGetFPTimeFormat() with NULL parameter|pTimeFormat: NULL|dsERR_INVALID_PARAM|API should validate parameter|
 * |03|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_TEXT|dsERR_NONE|API should set mode successfully|
 * |04|Call dsGetFPTimeFormat() to retrieve the set time format|dsFPDTimeFormat_t*|dsERR_OPERATION_NOT_SUPPORTED|Should get the previously set time format|
 * |03|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_CLOCK|dsERR_NONE|API should set mode successfully|
 * |04|Set all valid indicators to dsFPD_STATE_OFF using dsSetFPState() if applicable|Using a separate function or mechanism if available|dsERR_NONE|Ensure the FP state is "OFF"|
 * |05|Call dsGetFPTimeFormat() while FP State is "OFF"|dsFPDTimeFormat_t*|dsERR_OPERATION_NOT_SUPPORTED|API should not operate when FP state is "OFF"|
 * |07|Terminate using dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * |08|Call dsGetFPTimeFormat() after termination|dsFPDTimeFormat_t*|dsERR_NOT_INITIALIZED|API should not work after termination|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_negative_dsGetFPTimeFormat (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Validate the positive flow of dsFPGetLEDState()
 * 
 * @todo Do we need set dsSetFPState here?
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 037@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|---------|---------------|-----|
 * |01|Initialize using dsFPInit()||dsERR_NONE|Ensure the system is initialized|
 * |02|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |03|Call dsFPGetLEDState() with a valid parameter|state: dsFPDLedState_t*|dsERR_NONE|API should retrieve the current state successfully|
 * |04|Call dsFPGetLEDState() with a valid parameter|state: dsFPDLedState_t*|dsERR_NONE|API should retrieve the current state successfully|
 * |05|Compare the returned values from steps 3/4 ||Success|The values should be the same|
 * |06|Terminate using dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_positive_dsFPGetLEDState (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Validate the negative scenarios of dsFPGetLEDState()
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 038@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** dsFPInit, dsFPTerm, dsFPGetLEDState@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|---------|---------------|-----|
 * |01|Call dsFPGetLEDState() before initialization|state: dsFPDLedState_t*|dsERR_NOT_INITIALIZED|API should not work without initialization|
 * |02|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |03|Initialize using dsFPInit()||dsERR_NONE|Ensure the system is initialized|
 * |04|Call dsFPGetLEDState() with a NULL pointer|state: NULL|dsERR_INVALID_PARAM|API should not accept NULL pointer parameter|
 * |05|Terminate using dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * |06|Call dsFPGetLEDState() after termination|state:dsFPDLedState_t*|dsERR_NOT_INITIALIZED|API should not work after termination|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_negative_dsFPGetLEDState (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Validate the positive scenarios of dsFPSetLEDState()
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 039@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|---------|---------------|-----|
 * |01|Initialize using dsFPInit()||dsERR_NONE|Ensure the system is initialized|
 * |02|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |02|Call dsFPSetLEDState() and loop through all LED states|state: A valid dsFPDLedState_t value|dsERR_NONE|The LED state should be set successfully|
 * |03|Terminate using dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_positive_dsFPSetLEDState (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

/**
 * @brief Validate the negative scenarios of dsFPSetLEDState()
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 040@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|---------|---------------|-----|
 * |01|Call dsFPSetLEDState() before initialization|state: dsFPD_LED_DEVICE_ACTIVE|dsERR_NOT_INITIALIZED|API should not work without initialization|
 * |02|Initialize using dsFPInit()||dsERR_NONE|Ensure the system is initialized|
 * |02|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |03|Call dsFPSetLEDState() with an invalid LED state|state: dsFPD_LED_DEVICE_MAX|dsERR_INVALID_PARAM|API should validate the parameter and return an error for invalid input|
 * |04|Terminate using dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * |05|Call dsFPSetLEDState() after termination|state: dsFPD_LED_DEVICE_ACTIVE|dsERR_NOT_INITIALIZED|API should not work after termination|
 * 
 * @note Valid indicators can retrieved from kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_negative_dsFPSetLEDState (void)
{
	UT_FAIL(This function needs to be implemented!); 
}

static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main test(s) for this module
 * 
 * @todo SPlit out all tests that use 7-segment displays into their own suite, and perform the check with kTextDisplays here to determine if we access that test suite.
 *
 * @return int - 0 on success, otherwise failure
 */
int test_l1_dsFPD_register ( void )
{
	/* add a suite to the registry */
	pSuite = UT_add_suite( "[L1 dsFPD]", NULL, NULL );
    pSuite7Segment = UT_add_suite( "[L1 dsFPD 7Segment]", NULL, NULL );
	if ( NULL == pSuite )
	{
		return -1;
	}	

	UT_add_test( pSuite, "dsFPInit_L1_positive" ,test_l1_dsFPD_positive_dsFPInit );
	UT_add_test( pSuite, "dsFPInit_L1_negative" ,test_l1_dsFPD_negative_dsFPInit );
    UT_add_test( pSuite, "dsFPTerm_L1_positive" ,test_l1_dsFPD_positive_dsFPTerm );
	UT_add_test( pSuite, "dsFPTerm_L1_negative" ,test_l1_dsFPD_negative_dsFPTerm );
    UT_add_test( pSuite, "dsSetFPState_L1_positive" ,test_l1_dsFPD_positive_dsSetFPState );
	UT_add_test( pSuite, "dsSetFPState_L1_negative" ,test_l1_dsFPD_negative_dsSetFPState );
	UT_add_test( pSuite, "dsSetFPBlink_L1_positive" ,test_l1_dsFPD_positive_dsSetFPBlink );
	UT_add_test( pSuite, "dsSetFPBlink_L1_negative" ,test_l1_dsFPD_negative_dsSetFPBlink );
	UT_add_test( pSuite, "dsSetFPBrightness_L1_positive" ,test_l1_dsFPD_positive_dsSetFPBrightness );
	UT_add_test( pSuite, "dsSetFPBrightness_L1_negative" ,test_l1_dsFPD_negative_dsSetFPBrightness );
	UT_add_test( pSuite, "dsGetFPBrightness_L1_positive" ,test_l1_dsFPD_positive_dsGetFPBrightness );
	UT_add_test( pSuite, "dsGetFPBrightness_L1_negative" ,test_l1_dsFPD_negative_dsGetFPBrightness );
	UT_add_test( pSuite, "dsGetFPState_L1_positive" ,test_l1_dsFPD_positive_dsGetFPState );
	UT_add_test( pSuite, "dsGetFPState_L1_negative" ,test_l1_dsFPD_negative_dsGetFPState );
	UT_add_test( pSuite, "dsSetFPColor_L1_positive" ,test_l1_dsFPD_positive_dsSetFPColor );
	UT_add_test( pSuite, "dsSetFPColor_L1_negative" ,test_l1_dsFPD_negative_dsSetFPColor );
	UT_add_test( pSuite, "dsGetFPColor_L1_positive" ,test_l1_dsFPD_positive_dsGetFPColor );
	UT_add_test( pSuite, "dsGetFPColor_L1_negative" ,test_l1_dsFPD_negative_dsGetFPColor );
	UT_add_test( pSuite, "dsFPGetLEDState_L1_positive" ,test_l1_dsFPD_positive_dsFPGetLEDState );
	UT_add_test( pSuite, "dsFPGetLEDState_L1_negative" ,test_l1_dsFPD_negative_dsFPGetLEDState );
	UT_add_test( pSuite, "dsFPSetLEDState_L1_positive" ,test_l1_dsFPD_positive_dsFPSetLEDState );
	UT_add_test( pSuite, "dsFPSetLEDState_L1_negative" ,test_l1_dsFPD_negative_dsFPSetLEDState );



    UT_add_test( pSuite7Segment, "dsSetFPDMode_L1_positive" ,test_l1_dsFPD_positive_dsSetFPDMode );
	UT_add_test( pSuite7Segment, "dsSetFPDMode_L1_negative" ,test_l1_dsFPD_negative_dsSetFPDMode );
	UT_add_test( pSuite7Segment, "dsSetFPTime_L1_positive" ,test_l1_dsFPD_positive_dsSetFPTime );
	UT_add_test( pSuite7Segment, "dsSetFPTime_L1_negative" ,test_l1_dsFPD_negative_dsSetFPTime );
	UT_add_test( pSuite7Segment, "dsSetFPText_L1_positive" ,test_l1_dsFPD_positive_dsSetFPText );
	UT_add_test( pSuite7Segment, "dsSetFPText_L1_negative" ,test_l1_dsFPD_negative_dsSetFPText );
	UT_add_test( pSuite7Segment, "dsSetFPTextBrightness_L1_positive" ,test_l1_dsFPD_positive_dsSetFPTextBrightness );
	UT_add_test( pSuite7Segment, "dsSetFPTextBrightness_L1_negative" ,test_l1_dsFPD_negative_dsSetFPTextBrightness );
	UT_add_test( pSuite7Segment, "dsGetFPTextBrightness_L1_positive" ,test_l1_dsFPD_positive_dsGetFPTextBrightness );
	UT_add_test( pSuite7Segment, "dsGetFPTextBrightness_L1_negative" ,test_l1_dsFPD_negative_dsGetFPTextBrightness );
	UT_add_test( pSuite7Segment, "dsFPEnableCLockDisplay_L1_positive" ,test_l1_dsFPD_positive_dsFPEnableCLockDisplay );
	UT_add_test( pSuite7Segment, "dsFPEnableCLockDisplay_L1_negative" ,test_l1_dsFPD_negative_dsFPEnableCLockDisplay );
	UT_add_test( pSuite7Segment, "dsSetFPScroll_L1_positive" ,test_l1_dsFPD_positive_dsSetFPScroll );
	UT_add_test( pSuite7Segment, "dsSetFPScroll_L1_negative" ,test_l1_dsFPD_negative_dsSetFPScroll );
	UT_add_test( pSuite7Segment, "dsSetFPTimeFormat_L1_positive" ,test_l1_dsFPD_positive_dsSetFPTimeFormat );
	UT_add_test( pSuite7Segment, "dsSetFPTimeFormat_L1_negative" ,test_l1_dsFPD_negative_dsSetFPTimeFormat );
	UT_add_test( pSuite7Segment, "dsGetFPTimeFormat_L1_positive" ,test_l1_dsFPD_positive_dsGetFPTimeFormat );
	UT_add_test( pSuite7Segment, "dsGetFPTimeFormat_L1_negative" ,test_l1_dsFPD_negative_dsGetFPTimeFormat );
	

	return 0;
} 
