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
 * @addtogroup Device_Settings_HALTEST Device Settings HAL Tests
 * @{
 */

/**
 * @defgroup DS_FPD_HALTEST Device Settings Front Panel Display HAL Tests
 * @{
 */

/**
 * @defgroup DS_FPD_HALTEST_L1 Device Settings Front Panel Display HAL Tests L1 File
 * @{
 * @parblock
 *
 * ### L1 Tests for DS Front Panel Display HAL :
 *
 * Level 1 unit test cases for all APIs of Device Settings Front Panel Display HAL
 *
 * **Pre-Conditions:**  None@n
 * **Dependencies:** None@n
 *
 * Refer to API Definition specification documentation : [ds-front-panel-display_halSpec.md](../../docs/pages/ds-front-panel-display_halSpec.md)
 *
 * @endparblock
 */


/**
 * @file test_l1_dsFPD.c
 *
 */

#include <string.h>
#include <stdlib.h>

#include <ut.h>
#include <ut_log.h>
#include "dsFPD.h"
#include "frontPanelSettings.hpp"
#include "stdbool.h"
#include <ut_kvp_profile.h>
static int gTestGroup = 1;
static int gTestID = 1;


/* Global flags to support features */
static bool extendedEnumsSupported=false; //Default to not supported

#define INDICATOR_COLORS_SIZE_1 (sizeof(kIndicatorColors)/sizeof(dsFPDColorConfig_t))
#define INDICATOR_COLORS_SIZE_2 (sizeof(kIndicatorColors_2)/sizeof(dsFPDColorConfig_t))
#define INDICATOR_COLORS_SIZE_3 (sizeof(kIndicatorColors_3)/sizeof(dsFPDColorConfig_t))

#define INDICATOR_COLORS_SIZE INDICATOR_COLORS_SIZE_1

#define DS_ASSERT_AUTO_TERM_NUMERICAL(value, comparison){\
    if(value != comparison){\
        UT_LOG("\n In %s Comparison: [%d = %d]\n", __FUNCTION__, value, comparison);\
        dsFPTerm();\
        UT_ASSERT_EQUAL(value, comparison);\
    }\
}\

#define DS_ASSERT_AUTO_TERM_STRING(value, comparison){\
    if(strcmp(value, comparison) != 0){\
        UT_LOG("\n In %s Comparison: [%s = %s]\n", __FUNCTION__, value, comparison);\
        dsFPTerm();\
        UT_ASSERT_EQUAL(value, comparison);\
    }\
}\


#define enableFPDIndicators(){\
    dsError_t result;\
    for (int i = 0; i < sizeof(kIndicators) / sizeof(kIndicators[0]); ++i)\
    {\
        UT_LOG("\n In %s , Indicator: [%d]\n", __FUNCTION__, kIndicators[i].id);\
        result = dsSetFPState(kIndicators[i].id, dsFPD_STATE_ON);\
        DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);\
    }\
}\

#define disableFPDIndicators(){\
    dsError_t result;\
    for (int i = 0; i < sizeof(kIndicators) / sizeof(kIndicators[0]); ++i)\
    {\
        result = dsSetFPState(kIndicators[i].id, dsFPD_STATE_OFF);\
        DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);\
    }\
}\

#define CHECK_FOR_EXTENDED_ERROR_CODE( result, enhanced, old )\
{\
   if ( extendedEnumsSupported == true )\
   {\
      UT_ASSERT_EQUAL( enhanced, result );\
   }\
   else\
   {\
       UT_ASSERT_EQUAL( old, result );\
   }\
}

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
    gTestID = 1;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;

    // Variation 01: Call dsFPInit() - initialize the interface for the first time
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Variation 02: Call dsFPTerm() - terminate the interface
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Variation 03: Call dsFPInit() again - reinitialize the interface after termination
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Variation 04: Call dsFPTerm() - terminate the interface once again
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
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
void test_l1_dsFPD_negative_dsFPInit(void)
{
    gTestID = 2;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;

    // Variation 01: Call dsFPInit() - initialize the interface
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Variation 02: Call dsFPInit() again - attempt to initialize an already initialized interface
    result = dsFPInit();
    CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_ALREADY_INITIALIZED, dsERR_NONE);

    // Variation 03: Call dsFPTerm() - terminate the interface
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
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
void test_l1_dsFPD_positive_dsFPTerm(void)
{
    gTestID = 3;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;

    // Variation 01: Call dsFPInit() - initialize the interface
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Variation 02: Call dsFPTerm() - terminate the interface
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Variation 03: Call dsFPInit() - reinitialize the interface
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Variation 04: Call dsFPTerm() - terminate the interface once again
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
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
void test_l1_dsFPD_negative_dsFPTerm(void)
{
    gTestID = 4;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;

    // Variation 01: Call dsFPTerm() - attempt to terminate without initializing the interface
    result = dsFPTerm();
    CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    // Variation 02: Call dsFPInit() - initialize the interface
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Variation 03: Call dsFPTerm() - terminate the interface
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Variation 04: Call dsFPTerm() again - attempt to terminate an already terminated interface
    result = dsFPTerm();
    CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
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
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_positive_dsSetFPState (void)
{
    gTestID = 5;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;

    // Step 01: Initialize
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    
    // Step 02: Call dsSetFPState() with valid inputs
    result = dsSetFPState(dsFPD_INDICATOR_POWER, dsFPD_STATE_OFF);
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    
    // Step 03: Call dsSetFPState() and loop through all valid indicators from kIndicators
    for (int i = 0; i < sizeof(kIndicators) / sizeof(kIndicators[0]); ++i)
    {
        UT_LOG("\n In %s , Indicator: [%d]\n", __FUNCTION__, kIndicators[i].id);
        result = dsSetFPState(kIndicators[i].id, dsFPD_STATE_ON);
        UT_ASSERT_EQUAL(result, dsERR_NONE);
        result = dsSetFPState(kIndicators[i].id, dsFPD_STATE_OFF);
        UT_ASSERT_EQUAL(result, dsERR_NONE);
    }
    
    // Step 04: Terminate
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
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
 * |05|Call dsSetFPState() and loop through the indicators from the diff of kIndicators and dsFPDIndicator_t |eIndicator: [Invalid Indicator], state: dsFPD_STATE_OFF|dsERR_OPERATION_NOT_SUPPORTED|Validate invalid parameter handling for eIndicator|
 * |06|Terminate with dsFPTerm()| |dsERR_NONE|Ensure the system is terminated|
 * |07|Call dsSetFPState() after termination|eIndicator: dsFPD_INDICATOR_POWER, state: dsFPD_STATE_OFF|dsERR_NOT_INITIALIZED|Validate it checks for initialization even after termination|
 * 
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_negative_dsSetFPState (void)
{
    gTestID = 6;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;

    // Step 01: Call dsSetFPState() without initializing
    result = dsSetFPState(dsFPD_INDICATOR_POWER, dsFPD_STATE_OFF);
    CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    // Step 02: Initialize
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Call dsSetFPState() with an invalid eIndicator value
    result = dsSetFPState(dsFPD_INDICATOR_MAX, dsFPD_STATE_OFF);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);
    
    // Step 04: Loop through all valid indicators from kIndicators with an invalid state value
    for (int i = 0; i < sizeof(kIndicators) / sizeof(kIndicators[0]); ++i)
    {
        result = dsSetFPState(kIndicators[i].id, dsFPD_STATE_MAX);
        UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);
    }

    // Step 05: Loop through the indicators from the diff of kIndicators and dsFPDIndicator_t
    for (int i = 0; i < dsFPD_INDICATOR_MAX; ++i)
    {
        bool isIndicatorValid = false;
        for (int j = 0; j < sizeof(kIndicators) / sizeof(kIndicators[0]); ++j)
        {
            if (kIndicators[j].id == i)
            {
                isIndicatorValid = true;
                break;
            }
        }

        if (!isIndicatorValid)
        {
            result = dsSetFPState((dsFPDIndicator_t)i, dsFPD_STATE_OFF);
            UT_ASSERT_EQUAL(result, dsERR_OPERATION_NOT_SUPPORTED);
        }
    }

    // Step 06: Terminate
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    
    // Step 07: Call dsSetFPState() after termination
    result = dsSetFPState(dsFPD_INDICATOR_POWER, dsFPD_STATE_OFF);
    CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
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
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 * 
 */
void test_l1_dsFPD_positive_dsSetFPBlink (void)
{
    gTestID = 7;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;

    // Step 01: Initialize with dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()
    // Step 03: Call dsSetFPBlink() and loop through all valid indicators from kIndicators
    for (int i = 0; i < sizeof(kIndicators) / sizeof(kIndicators[0]); ++i)
    {
        UT_LOG("\n In %s , Indicator: [%d]\n", __FUNCTION__, kIndicators[i].id);
        result = dsSetFPState(kIndicators[i].id, dsFPD_STATE_ON);
        UT_ASSERT_EQUAL(result, dsERR_NONE);
        result = dsSetFPBlink(kIndicators[i].id, 500, 10);
        UT_ASSERT_EQUAL(result, dsERR_NONE);
    }


    // Step 04: Terminate with dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
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
 * |03|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |04|Pass an invalid uBlinkDuration parameter to dsSetFPBlink() for all valid indicators|eIndicator: [Valid Indicator], uBlinkDuration: 20000, uBlinkIterations: 10 |dsERR_INVALID_PARAM|Should validate that the function handles invalid blink duration gracefully|
 * |05|Pass an invalid uBlinkIterations parameter to dsSetFPBlink() for all valid indicators|eIndicator: [Valid Indicator], uBlinkDuration: 500, uBlinkIterations: 200 |dsERR_INVALID_PARAM|Should validate that the function handles invalid blink iterations gracefully|
 * |06|Pass an invalid eIndicator parameter to dsSetFPBlink() |eIndicator: dsFPD_INDICATOR_MAX, uBlinkDuration: 500, uBlinkIterations: 10 |dsERR_INVALID_PARAM|Should validate that the function handles invalid indicator gracefully|
 * |07|Set all valid indicators to dsFPD_STATE_OFF using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_OFF |dsERR_NONE|Ensure the system is initialized|
 * |08|Call dsSetFPBlink() and loop through all valid indicators from kIndicators|eIndicator: [Valid Indicator], uBlinkDuration: 500, uBlinkIterations: 10 |dsERR_OPERATION_NOT_SUPPORTED|Testing if function adheres to pre-condition of FP State being “ON”|
 * |09|Terminate with dsFPTerm()| |dsERR_NONE|Ensure the system is terminated|
 * |10|Attempt to set blink pattern after dsFPTerm() has been called|eIndicator: dsFPD_INDICATOR_POWER, uBlinkDuration: 500, uBlinkIterations: 10 |dsERR_NOT_INITIALIZED|Should fail due to termination|
 * 
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 * 
 */
void test_l1_dsFPD_negative_dsSetFPBlink (void)
{
    gTestID = 8;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;

    // Variation 01: Call dsSetFPBlink() without calling dsFPInit()
    result = dsSetFPBlink(dsFPD_INDICATOR_POWER, 500, 10);
    CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);
    for (int i = 0; i < sizeof(kIndicators) / sizeof(kIndicators[0]); ++i)
    {
        result = dsSetFPBlink(kIndicators[i].id, 500, 10);
	CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);
    }

    // Variation 02: Initialize with dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Variation 03: Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()
    // Variation 04: Pass an invalid uBlinkDuration parameter to dsSetFPBlink()
    // Variation 05: Pass an invalid uBlinkIterations parameter to dsSetFPBlink()
    for (int i = 0; i < sizeof(kIndicators) / sizeof(kIndicators[0]); ++i)
    {
        UT_LOG("\n In %s , Indicator: [%d]\n", __FUNCTION__, kIndicators[i].id);
        result = dsSetFPState(kIndicators[i].id, dsFPD_STATE_ON);
        UT_ASSERT_EQUAL(result, dsERR_NONE);

        result = dsSetFPBlink(kIndicators[i].id, 20000, 10);
        UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

        result = dsSetFPBlink(kIndicators[i].id, 500, 200);
        UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);
    }

    // Variation 06: Pass an invalid eIndicator parameter to dsSetFPBlink()
    result = dsSetFPBlink(dsFPD_INDICATOR_MAX, 500, 10);
         UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);


    // Variation 07: Set all valid indicators to dsFPD_STATE_OFF using dsSetFPState()
    disableFPDIndicators();

    // Variation 08: Call dsSetFPBlink() and loop through all valid indicators from kIndicators
    for (int i = 0; i < sizeof(kIndicators) / sizeof(kIndicators[0]); ++i)
    {
        result = dsSetFPBlink(kIndicators[i].id, 500, 10);
        UT_ASSERT_EQUAL(result, dsERR_OPERATION_NOT_SUPPORTED);
    }

    // Variation 09: Terminate with dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Variation 10: Attempt to set blink pattern after dsFPTerm() has been called
    for (int i = 0; i < sizeof(kIndicators) / sizeof(kIndicators[0]); ++i)
    {
        result = dsSetFPBlink(kIndicators[i].id, 500, 10);
	CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    }
    UT_LOG("\n Out  %s\n",__FUNCTION__);
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
 * |03|Call dsSetFPBrightness() and loop through all valid indicators from kIndicators|eIndicator: [Valid Indicator], eBrightness: 20+5x|dsERR_NONE|Brightness is set without any issues|
 * |04|Terminate with dsFPTerm()| |dsERR_NONE|Ensure the system is terminated|
 * 
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 * 
 */
void test_l1_dsFPD_positive_dsSetFPBrightness (void)
{
    gTestID = 9;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;

    // Step 01: Initialize with dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()
    // Step 03: Call dsSetFPBrightness() and loop through all valid indicators from kIndicators
    for (int i = 0; i < sizeof(kIndicators) / sizeof(kIndicators[0]); ++i)
    {
        UT_LOG("\n In %s , Indicator: [%d]\n", __FUNCTION__, kIndicators[i].id);
        result = dsSetFPState(kIndicators[i].id, dsFPD_STATE_ON);
        UT_ASSERT_EQUAL(result, dsERR_NONE);
        
        result = dsSetFPBrightness(kIndicators[i].id, 0);
        UT_ASSERT_EQUAL(result, dsERR_NONE);
        result = dsSetFPBrightness(kIndicators[i].id, 50);
        UT_ASSERT_EQUAL(result, dsERR_NONE);
        result = dsSetFPBrightness(kIndicators[i].id, 100);
        UT_ASSERT_EQUAL(result, dsERR_NONE);
    }

    // Step 04: Terminate with dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
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
 * |04|Pass an invalid eBrightness parameter to dsSetFPBrightness()|eIndicator: dsFPD_INDICATOR_POWER, eBrightness: 200 |dsERR_INVALID_PARAM|Should validate that the function handles invalid brightness gracefully|
 * |05|Pass an invalid eIndicator parameter to dsSetFPBrightness() |eIndicator: dsFPD_INDICATOR_MAX, eBrightness: 50 |dsERR_INVALID_PARAM|Should validate that the function handles invalid indicator gracefully|
 * |06|Set all valid indicators to dsFPD_STATE_OFF using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_OFF|dsERR_OPERATION_NOT_SUPPORTED|Validate invalid parameter handling for eIndicator|
 * |07|Call dsSetFPBrightness() and loop through all valid indicators from kIndicators|eIndicator: [Valid Indicator], eBrightness: 50 |dsERR_OPERATION_NOT_SUPPORTED|Testing if function adheres to pre-condition of FP State being “ON”|
 * |08|Terminate with dsFPTerm()| |dsERR_NONE|Ensure the system is terminated|
 * |09|Attempt to set brightness after dsFPTerm() has been called|eIndicator: dsFPD_INDICATOR_POWER, eBrightness: 50 |dsERR_NOT_INITIALIZED|Should fail due to termination|
 * 
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 * 
 */
void test_l1_dsFPD_negative_dsSetFPBrightness (void)
{
    gTestID = 10;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;

    // Variation 01: Call dsSetFPBrightness() without calling dsFPInit()
    for (int i = 0; i < sizeof(kIndicators) / sizeof(kIndicators[0]); ++i)
    {
        result = dsSetFPBrightness(kIndicators[i].id, 50);
	CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    }

    // Variation 02: Initialize with dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Variation 03: Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()
    // Variation 04: Pass an invalid eBrightness parameter to dsSetFPBrightness()
    for (int i = 0; i < sizeof(kIndicators) / sizeof(kIndicators[0]); ++i)
    {
        UT_LOG("\n In %s , Indicator: [%d]\n", __FUNCTION__, kIndicators[i].id);
        result = dsSetFPState(kIndicators[i].id, dsFPD_STATE_ON);
        UT_ASSERT_EQUAL(result, dsERR_NONE);
        result = dsSetFPBrightness(kIndicators[i].id, 200);
        UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);
    }

    // Variation 05: Pass an invalid eIndicator parameter to dsSetFPBrightness()
    result = dsSetFPBrightness(dsFPD_INDICATOR_MAX, 50);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);
    

    // Variation 06: Set all valid indicators to dsFPD_STATE_OFF using dsSetFPState()
    for (int i = 0; i < sizeof(kIndicators) / sizeof(kIndicators[0]); ++i)
    {
        result = dsSetFPState(kIndicators[i].id, dsFPD_STATE_OFF);
        UT_ASSERT_EQUAL(result, dsERR_NONE);
    }

    // Variation 07: Call dsSetFPBrightness() and loop through all valid indicators from kIndicators
    for (int i = 0; i < sizeof(kIndicators) / sizeof(kIndicators[0]); ++i)
    {
        result = dsSetFPBrightness(kIndicators[i].id, 50);
        UT_ASSERT_EQUAL(result, dsERR_OPERATION_NOT_SUPPORTED);
    }

    // Variation 08: Terminate with dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Variation 09: Attempt to set brightness after dsFPTerm() has been called
    for (int i = 0; i < sizeof(kIndicators) / sizeof(kIndicators[0]); ++i)
    {
        result = dsSetFPBrightness(kIndicators[i].id, 50);
        CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    }
    UT_LOG("\n Out  %s\n",__FUNCTION__);
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
 * |03|Call dsGetFPBrightness() with specific valid indicator and store the value|eIndicator: dsFPD_INDICATOR_POWER|dsERR_NONE|Brightness is retrieved without any issues|
 * |04|Call dsGetFPBrightness() and loop through all valid indicators from kIndicators|eIndicator: [Valid Indicator]|dsERR_NONE|Ensure consistent readings|
 * |05|Compare the two retrieved brightness values from step 02 and step 03 for dsFPD_INDICATOR_POWER||Brightness values should be equal|Ensuring consistency in retrieved brightness over consecutive calls|
 * |06|Terminate with dsFPTerm()| |dsERR_NONE|Ensure the system is terminated|
 * 
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 * 
 */
void test_l1_dsFPD_positive_dsGetFPBrightness (void)
{
    gTestID = 11;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;
    dsFPDBrightness_t brightness_power_indicator;
    dsFPDBrightness_t brightness_all_indicators[sizeof(kIndicators) / sizeof(kIndicators[0])];
    int indicator_power_index = -1;

    // Step 01: Initialize with dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()
    enableFPDIndicators();

    // Step 03: Call dsGetFPBrightness() with specific valid indicator and store the value
    result = dsGetFPBrightness(dsFPD_INDICATOR_POWER, &brightness_power_indicator);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 04: Call dsGetFPBrightness() and loop through all valid indicators from kIndicators
    for (int i = 0; i < sizeof(kIndicators) / sizeof(kIndicators[0]); ++i)
    {
        result = dsGetFPBrightness(kIndicators[i].id, &brightness_all_indicators[i]);
        UT_ASSERT_EQUAL(result, dsERR_NONE);

        if (kIndicators[i].id == dsFPD_INDICATOR_POWER)
        {
            indicator_power_index = i;
        }
    }

    // Step 05: Compare the two retrieved brightness values from step 02 and step 03 for dsFPD_INDICATOR_POWER
    UT_ASSERT_EQUAL(brightness_power_indicator, brightness_all_indicators[indicator_power_index]);

    // Step 06: Terminate with dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
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
 * |04|Call dsGetFPBrightness() with an invalid pBrightness pointer (NULL)|eIndicator: [Valid indicator], pBrightness: NULL|dsERR_INVALID_PARAM|Ensure it handles NULL pointer input for pBrightness|
 * |05|Call dsGetFPBrightness() with an invalid eIndicator value|eIndicator: dsFPD_INDICATOR_MAX, pBrightness: dsFPDBrightness_t*|dsERR_INVALID_PARAM|Validate invalid parameter handling|
 * |06|Set all valid indicators to dsFPD_STATE_OFF using dsSetFPState() |eIndicator: [Valid Indicator], state: dsFPD_STATE_OFF|dsERR_OPERATION_NOT_SUPPORTED|Validate invalid parameter handling for eIndicator|
 * |07|Call dsGetFPBrightness() and loop through all valid indicators from kIndicators|eIndicator: [Valid Indicator], pBrightness: dsFPDBrightness_t*|dsERR_OPERATION_NOT_SUPPORTED|Ensure it checks for FP state and returns operation not supported when it is "OFF"|
 * |08|Terminate with dsFPTerm()| |dsERR_NONE|Ensure the system is terminated|
 * |09|Call dsGetFPBrightness() after termination|eIndicator: dsFPD_INDICATOR_POWER, pBrightness: dsFPDBrightness_t*|dsERR_NOT_INITIALIZED|Validate it checks for initialization even after termination|
 * 
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 * 
 */
void test_l1_dsFPD_negative_dsGetFPBrightness (void)
{
    gTestID = 12;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;
    dsFPDBrightness_t brightness;

    // Step 01: Call dsGetFPBrightness() without initializing
    result = dsGetFPBrightness(dsFPD_INDICATOR_POWER, &brightness);
    CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);
    for (int i = 0; i < sizeof(kIndicators) / sizeof(kIndicators[0]); ++i)
    {
         result = dsGetFPBrightness(kIndicators[i].id, &brightness);
	 CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);
    }

    // Step 02: Initialize with dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()
    // Step 04: Call dsGetFPBrightness() with an invalid pBrightness value (NULL)
    for (int i = 0; i < sizeof(kIndicators) / sizeof(kIndicators[0]); ++i)
    {
        UT_LOG("\n In %s , Indicator: [%d]\n", __FUNCTION__, kIndicators[i].id);
        result = dsSetFPState(kIndicators[i].id, dsFPD_STATE_ON);
        UT_ASSERT_EQUAL(result, dsERR_NONE);

        result = dsGetFPBrightness(kIndicators[i].id, NULL);
        UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);
    }

    // Step 05: Call dsGetFPBrightness() with an invalid eIndicator value
    result = dsGetFPBrightness(dsFPD_INDICATOR_MAX, &brightness);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);


    // Step 06: Set all valid indicators to dsFPD_STATE_OFF using dsSetFPState()
    for (int i = 0; i < sizeof(kIndicators) / sizeof(kIndicators[0]); ++i)
    {
        result = dsSetFPState(kIndicators[i].id, dsFPD_STATE_OFF);
        UT_ASSERT_EQUAL(result, dsERR_NONE);
    }

    // Step 07: Call dsGetFPBrightness() and loop through all valid indicators
    for (int i = 0; i < sizeof(kIndicators) / sizeof(kIndicators[0]); ++i)
    {
        result = dsGetFPBrightness(kIndicators[i].id, &brightness);
        UT_ASSERT_EQUAL(result, dsERR_OPERATION_NOT_SUPPORTED);
    }

    // Step 08: Terminate with dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 09: Call dsGetFPBrightness() after termination
    for (int i = 0; i < sizeof(kIndicators) / sizeof(kIndicators[0]); ++i)
    {
        result = dsGetFPBrightness(kIndicators[i].id, &brightness);
	CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);
    }
    UT_LOG("\n Out  %s\n",__FUNCTION__);
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
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_positive_dsGetFPState (void)
{
    gTestID = 13;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;
    dsFPDState_t stateForPower, stateForComparison;

    // Step 01: Initialize with dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Call dsGetFPState() with valid eIndicator and state parameters
    result = dsGetFPState(dsFPD_INDICATOR_POWER, &stateForPower);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Call dsGetFPState() once again for dsFPD_INDICATOR_POWER and store results
    result = dsGetFPState(dsFPD_INDICATOR_POWER, &stateForComparison);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 04: Call dsGetFPState() and loop through all valid indicators from kIndicators
    for (int i = 0; i < sizeof(kIndicators) / sizeof(kIndicators[0]); ++i)
    {
        dsFPDState_t currentState;
        result = dsGetFPState(kIndicators[i].id, &currentState);
        UT_ASSERT_EQUAL(result, dsERR_NONE);
    }

    // Step 05: Compare the state retrieved in step 02 and 03
    UT_ASSERT_EQUAL(stateForPower, stateForComparison);

    // Step 06: Terminate with dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
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
 * |05|Call dsGetFPState() and loop through the indicators from the diff of kIndicators and dsFPDIndicator_t |eIndicator: [invalid indicator], state: dsFPDState_t*|dsERR_OPERATION_NOT_SUPPORTED|Validate invalid parameter handling for eIndicator|
 * |06|Terminate with dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * |07|Call dsGetFPState() after termination|eIndicator: dsFPD_INDICATOR_POWER, state: dsFPDState_t*|dsERR_NOT_INITIALIZED|Validate it checks for initialization even after termination|
 * 
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 * 
 */
void test_l1_dsFPD_negative_dsGetFPState (void)
{
    gTestID = 14;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;
    dsFPDState_t state;

    // Step 01: Call dsGetFPState() without initializing (dsFPInit() not called)
    result = dsGetFPState(dsFPD_INDICATOR_POWER, &state);
    CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);
    for (int i = 0; i < sizeof(kIndicators) / sizeof(kIndicators[0]); ++i)
    {
        result = dsGetFPState(kIndicators[i].id, &state);
	CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);
       
    }

    // Step 02: Initialize with dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Call dsGetFPState() with an invalid eIndicator value
    result = dsGetFPState(dsFPD_INDICATOR_MAX, &state);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    // Step 04: Call dsGetFPState() with an invalid state pointer
    for (int i = 0; i < sizeof(kIndicators) / sizeof(kIndicators[0]); ++i)
    {
        result = dsGetFPState(kIndicators[i].id, NULL);
        UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);
    }

    // Step 05: Call dsSetFPState() and loop through the indicators from the diff of kIndicators and dsFPDIndicator_t 
    for (int i = dsFPD_INDICATOR_MESSAGE; i <= dsFPD_INDICATOR_MAX; ++i)
    {
        bool isValidIndicator = false;
        for (int j = 0; j < sizeof(kIndicators) / sizeof(kIndicators[0]); ++j)
        {
            if (kIndicators[j].id == i)
            {
                isValidIndicator = true;
                break;
            }
        }
        if (!isValidIndicator)
        {
            result = dsGetFPState((dsFPDIndicator_t)i, &state);
            UT_ASSERT_EQUAL(result, dsERR_OPERATION_NOT_SUPPORTED);
        }
    }

    // Step 06: Terminate with dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 07: Call dsGetFPState() after termination
    for (int i = 0; i < sizeof(kIndicators) / sizeof(kIndicators[0]); ++i)
    {
        result = dsGetFPState(kIndicators[i].id, &state);
        CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    }
    UT_LOG("\n Out  %s\n",__FUNCTION__);
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
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_positive_dsSetFPColor (void)
{
    gTestID = 15;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;

    // Step 01: Initialize with dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()
    // Step 03: Call dsSetFPColor() with all valid eIndicator and all valid eColor parameters from kIndicators
    for (int i = 0; i < sizeof(kIndicators) / sizeof(kIndicators[0]); ++i)
    {
        UT_LOG("\n In %s , Indicator: [%d]\n", __FUNCTION__, kIndicators[i].id);
        result = dsSetFPState(kIndicators[i].id, dsFPD_STATE_ON);
        UT_ASSERT_EQUAL(result, dsERR_NONE);

        dsFPDColorConfig_t *colors = kIndicators[i].supportedColors;

        // Assuming that the last entry in supportedColors array will have an undefined or NULL color
        for (int j = 0; colors[j].color; ++j) 
        {
            result = dsSetFPColor(kIndicators[i].id, colors[j].color);
            UT_ASSERT_EQUAL(result, dsERR_NONE);
        }
    }

    // Step 04: Terminate with dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
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
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_negative_dsSetFPColor (void)
{
    gTestID = 16;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;

    // List of all colors
    int allColors[] = {
        dsFPD_COLOR_BLUE,
        dsFPD_COLOR_GREEN,
        dsFPD_COLOR_RED,
        dsFPD_COLOR_YELLOW,
        dsFPD_COLOR_ORANGE,
        dsFPD_COLOR_WHITE,
        dsFPD_COLOR_MAX
    };

    // Step 01: Call dsSetFPColor() without initializing
    for (int i = 0; i < sizeof(kIndicators) / sizeof(kIndicators[0]); ++i)
    {
        result = dsSetFPColor(kIndicators[i].id, dsFPD_COLOR_WHITE);
	CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);
    }

    // Step 02: Initialize with dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()
    // Step 04: Call dsSetFPColor() with all valid indicators but invalid colors
    for (int i = 0; i < sizeof(kIndicators) / sizeof(kIndicators[0]); ++i)
    {
        UT_LOG("\n In %s , Indicator: [%d]\n", __FUNCTION__, kIndicators[i].id);
        result = dsSetFPState(kIndicators[i].id, dsFPD_STATE_ON);
        UT_ASSERT_EQUAL(result, dsERR_NONE);

        dsFPDColorConfig_t *colors = kIndicators[i].supportedColors;
        for (int j = 0; j < sizeof(allColors)/sizeof(allColors[0]); ++j)
        {
            int isSupported = 0;
            for (int k = 0; k < INDICATOR_COLORS_SIZE; ++k)
            {

                if (allColors[j] == colors[k].color)
                {
                    isSupported = 1;
                    break;
                }
                
            }
            if (!isSupported)
            {
                result = dsSetFPColor(kIndicators[i].id, allColors[j]);
                UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);
            }
            
        }
    }

    // Step 05: Call dsSetFPColor() with an invalid indicator
    result = dsSetFPColor(dsFPD_INDICATOR_MAX, allColors[0]);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    // Step 06: Set all valid indicators to dsFPD_STATE_OFF using dsSetFPState()
    // Step 07: Call dsSetFPColor() with all indicators when FPD state is OFF
    for (int i = 0; i < sizeof(kIndicators) / sizeof(kIndicators[0]); ++i)
    {
        result = dsSetFPState(kIndicators[i].id, dsFPD_STATE_OFF);
        UT_ASSERT_EQUAL(result, dsERR_NONE);

        dsFPDColorConfig_t *colors = kIndicators[i].supportedColors;

        result = dsSetFPColor(kIndicators[i].id, colors[0].color);
        UT_ASSERT_EQUAL(result, dsERR_OPERATION_NOT_SUPPORTED);
        
    }
   

    // Step 08: Terminate with dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 09: Call dsSetFPColor() after termination
    for (int i = 0; i < sizeof(kIndicators) / sizeof(kIndicators[0]); ++i)
    {
        result = dsSetFPColor(kIndicators[i].id, dsFPD_COLOR_WHITE);
        CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);
    }
    UT_LOG("\n Out  %s\n",__FUNCTION__);
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
 * |02|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |03|Call dsGetFPColor() with all valid indicators|eIndicator: [Valid Indicator], pColor: dsFPDColor_t*|dsERR_NONE|Ensure the function can retrieve color|
 * |04|Call dsGetFPColor() again and compare results|eIndicator: [Valid Indicator], pColor: dsFPDColor_t*|dsERR_NONE and same color as Step 04|Ensure consistency in repeated calls|
 * |05|Terminate with dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * 
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_positive_dsGetFPColor (void)
{
    gTestID = 17;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;
    dsFPDColor_t retrievedColor;

    // Step 01: Initialize with dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Set all valid indicators to dsFPD_STATE_ON using dsSetFPState() 
    // Step 03: Call dsGetFPColor() with all valid indicators
    // Step 04: Call dsGetFPColor() again and compare results
    for (int i = 0; i < sizeof(kIndicators) / sizeof(kIndicators[0]); ++i)
    {
        UT_LOG("\n In %s , Indicator: [%d]\n", __FUNCTION__, kIndicators[i].id);
        result = dsSetFPState(kIndicators[i].id, dsFPD_STATE_ON);
        UT_ASSERT_EQUAL(result, dsERR_NONE);
        dsFPDColor_t previousColor;
        result = dsGetFPColor(kIndicators[i].id, &previousColor);
        UT_ASSERT_EQUAL(result, dsERR_NONE);
        result = dsGetFPColor(kIndicators[i].id, &retrievedColor);
        UT_ASSERT_EQUAL(result, dsERR_NONE);
        UT_ASSERT_EQUAL(retrievedColor, previousColor);
    }

    // Step 05: Terminate with dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
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
 * |03|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |04|Call dsGetFPColor() with a null pointer for pColor|eIndicator: dsFPD_INDICATOR_POWER, pColor: NULL|dsERR_INVALID_PARAM|Validate invalid parameter handling for pColor|
 * |05|Call dsGetFPColor() with an invalid eIndicator value|eIndicator: dsFPD_INDICATOR_MAX, pColor: dsFPDColor_t*|dsERR_INVALID_PARAM|Validate invalid parameter handling for eIndicator|
 * |06|Set all valid indicators to dsFPD_STATE_OFF using dsSetFPState()|eIndicator: [Valid Indicator], State: OFF|dsERR_NONE|Ensure the FPD state is set to OFF|
 * |07|Call dsGetFPColor() with all indicators|eIndicator: [Indicator], pColor: dsFPDColor_t*|dsERR_OPERATION_NOT_SUPPORTED|Validate that function checks if FPD state is OFF|
 * |08|Terminate with dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * |09|Call dsGetFPColor() after termination|eIndicator: dsFPD_INDICATOR_POWER, pColor: dsFPDColor_t*|dsERR_NOT_INITIALIZED|Validate it checks for initialization even after termination|
 * 
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_negative_dsGetFPColor (void)
{
    gTestID = 18;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;
    dsFPDColor_t retrievedColor;

    // Step 01: Call dsGetFPColor() without initializing (dsFPInit() not called)
    for (int i = 0; i < sizeof(kIndicators) / sizeof(kIndicators[0]); ++i)
    {
        result = dsGetFPColor(kIndicators[i].id, &retrievedColor);
	CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);
    }

    // Step 02: Initialize with dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()
    // Step 04: Call dsGetFPColor() with a null pointer for pColor
    for (int i = 0; i < sizeof(kIndicators) / sizeof(kIndicators[0]); ++i)
    {
        UT_LOG("\n In %s , Indicator: [%d]\n", __FUNCTION__, kIndicators[i].id);
        result = dsSetFPState(kIndicators[i].id, dsFPD_STATE_ON);
        UT_ASSERT_EQUAL(result, dsERR_NONE);
        result = dsGetFPColor(kIndicators[i].id, NULL);
        UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);
    }

    // Step 05: Call dsGetFPColor() with an invalid eIndicator value
    result = dsGetFPColor(dsFPD_INDICATOR_MAX, &retrievedColor);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    // Step 06: Set all valid indicators to dsFPD_STATE_OFF using dsSetFPState()
    disableFPDIndicators();

    // Step 07: Call dsGetFPColor() with all indicators
    for (int i = 0; i < dsFPD_INDICATOR_MAX; ++i)
    {
        result = dsGetFPColor(kIndicators[i].id, &retrievedColor);
        UT_ASSERT_EQUAL(result, dsERR_OPERATION_NOT_SUPPORTED);
    }

    // Step 08: Terminate with dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 09: Call dsGetFPColor() after termination
    for (int i = 0; i < sizeof(kIndicators) / sizeof(kIndicators[0]); ++i)
    {
        result = dsGetFPColor(kIndicators[i].id, &retrievedColor);
	CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);
    }
    UT_LOG("\n Out  %s\n",__FUNCTION__);
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
 * |02|Call dsSetFPDMode() and loop through all valid values in dsFPDMode_t|eMode: [Valid Mode]|dsERR_NONE|API should set mode successfully|
 * |03|Terminate using dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 *
 * @note This test case is deprecated. 
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_positive_dsSetFPDMode (void)
{
    gTestID = 19;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;

    // Step 01: Initialize using dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Call dsSetFPDMode() and loop through all valid values in dsFPDMode_t
    for (dsFPDMode_t mode = dsFPD_MODE_ANY; mode < dsFPD_MODE_MAX; ++mode)
    {
        result = dsSetFPDMode(mode);
        UT_ASSERT_EQUAL(result, dsERR_NONE);
    }

    // Step 04: Terminate using dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
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
 * |03|Call dsSetFPDMode() with an invalid parameter|eMode: dsFPD_MODE_MAX|dsERR_INVALID_PARAM|API should validate parameter|
 * |04|Terminate using dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * |05|Call dsSetFPDMode() after termination|eMode: dsFPD_MODE_ANY|dsERR_NOT_INITIALIZED|API should not work after termination|
 * 
 * @note This test case is deprecated.
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_negative_dsSetFPDMode (void)
{
    gTestID = 20;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;

    // Step 01: Call dsSetFPDMode() without initializing the system
    result = dsSetFPDMode(dsFPD_MODE_ANY);
    CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    // Step 02: Initialize using dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Call dsSetFPDMode() with an invalid parameter
    result = dsSetFPDMode(dsFPD_MODE_MAX);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    // Step 04: Terminate using dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 05: Call dsSetFPDMode() after termination
    result = dsSetFPDMode(dsFPD_MODE_ANY);
    CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
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
 * |02|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_CLOCK|dsERR_NONE|API should set mode successfully|
 * |03|Call dsSetFPTime() with valid parameters for 24-hour format|eTimeFormat: dsFPD_TIME_24_HOUR, uHour: 14, uMinutes: 30|dsERR_NONE|Check the function in 24-hour format|
 * |04|Call dsSetFPTime() with valid parameters for 12-hour format|eTimeFormat: dsFPD_TIME_12_HOUR, uHour: 2, uMinutes: 30|dsERR_NONE|Check the function in 12-hour format|
 * |05|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_ANY|dsERR_NONE|API should set mode successfully|
 * |06|Call dsSetFPTime() with valid parameters for 24-hour format|eTimeFormat: dsFPD_TIME_24_HOUR, uHour: 14, uMinutes: 30|dsERR_NONE|Check the function in 24-hour format|
 * |07|Call dsSetFPTime() with valid parameters for 12-hour format|eTimeFormat: dsFPD_TIME_12_HOUR, uHour: 2, uMinutes: 30|dsERR_NONE|Check the function in 12-hour format|
 * |08|Terminate with dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * 
 * @note This test case is deprecated.
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_positive_dsSetFPTime (void)
{
    gTestID = 21;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;

    // Step 01: Initialize with dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Call dsSetFPDMode() with a valid parameter
    result = dsSetFPDMode(dsFPD_MODE_CLOCK);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Call dsSetFPTime() with valid parameters for 24-hour format
    result = dsSetFPTime(dsFPD_TIME_24_HOUR, 14, 30);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 04: Call dsSetFPTime() with valid parameters for 12-hour format
    result = dsSetFPTime(dsFPD_TIME_12_HOUR, 2, 30);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 05: Call dsSetFPDMode() with a valid parameter
    result = dsSetFPDMode(dsFPD_MODE_ANY);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 06: Call dsSetFPTime() with valid parameters for 24-hour format
    result = dsSetFPTime(dsFPD_TIME_24_HOUR, 14, 30);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 07: Call dsSetFPTime() with valid parameters for 12-hour format
    result = dsSetFPTime(dsFPD_TIME_12_HOUR, 2, 30);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 08: Terminate with dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
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
 * |01|Call dsSetFPTime() without initializing (dsFPInit() not called)|eTimeFormat: dsFPD_TIME_24_HOUR, uHour: 14, uMinutes: 30|dsERR_NOT_INITIALIZED|Validate that the function checks for initialization|
 * |02|Initialize with dsFPInit()||dsERR_NONE|Ensure the system is initialized|
 * |03|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_CLOCK|dsERR_NONE|API should set mode successfully|
 * |04|Call dsSetFPTime() with an invalid hour value|eTimeFormat: dsFPD_TIME_24_HOUR, uHour: 25, uMinutes: 30|dsERR_INVALID_PARAM|Validate invalid parameter handling for uHour|
 * |05|Call dsSetFPTime() with an invalid minute value|eTimeFormat: dsFPD_TIME_24_HOUR, uHour: 14, uMinutes: 60|dsERR_INVALID_PARAM|Validate invalid parameter handling for uMinutes|
 * |06|Call dsSetFPTime() with 12hr format and with invalid hour value|eTimeFormat: dsFPD_TIME_12_HOUR, uHour: 14, uMinutes: 30|dsERR_INVALID_PARAM|Check the consistency between eTimeFormat and uHour|
 * |07|Call dsSetFPTime() with 12hr format with invalid minute value|eTimeFormat: dsFPD_TIME_12_HOUR, uHour: 2, uMinutes: 60|dsERR_INVALID_PARAM|Check the consistency between eTimeFormat and uHour|
 * |08|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_ANY|dsERR_NONE|API should set mode successfully|
 * |09|Call dsSetFPTime() with an invalid hour value|eTimeFormat: dsFPD_TIME_24_HOUR, uHour: 25, uMinutes: 30|dsERR_INVALID_PARAM|Validate invalid parameter handling for uHour|
 * |10|Call dsSetFPTime() with an invalid minute value|eTimeFormat: dsFPD_TIME_24_HOUR, uHour: 14, uMinutes: 60|dsERR_INVALID_PARAM|Validate invalid parameter handling for uMinutes|
 * |11|Call dsSetFPTime() with 12hr format and invalid hour value|eTimeFormat: dsFPD_TIME_12_HOUR, uHour: 14, uMinutes: 30|dsERR_INVALID_PARAM|Check the consistency between eTimeFormat and uHour|
 * |12|Call dsSetFPTime() with 12hr format with invalid minute value|eTimeFormat: dsFPD_TIME_12_HOUR, uHour: 2, uMinutes: 60|dsERR_INVALID_PARAM|Check the consistency between eTimeFormat and uHour|
 * |13|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_TEXT|dsERR_NONE|API should set mode successfully|
 * |14|Call dsSetFPTime() with valid parameters for 24-hour format|eTimeFormat: dsFPD_TIME_24_HOUR, uHour: 14, uMinutes: 30|dsERR_OPERATION_NOT_SUPPORTED|Check the function in 24-hour format|
 * |15|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_CLOCK|dsERR_NONE|API should set mode successfully|
 * |16|Terminate with dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * |17|Call dsSetFPTime() after termination|eTimeFormat: dsFPD_TIME_24_HOUR, uHour: 14, uMinutes: 30|dsERR_NOT_INITIALIZED|Validate it checks for initialization even after termination|
 * 
 * @note This test case is deprecated.
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_negative_dsSetFPTime (void)
{
    gTestID = 22;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;

    // Step 01: Call dsSetFPTime() without initializing (dsFPInit() not called)
    result = dsSetFPTime(dsFPD_TIME_24_HOUR, 14, 30);
    CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    // Step 02: Initialize with dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 04: Call dsSetFPDMode() with a valid parameter
    result = dsSetFPDMode(dsFPD_MODE_CLOCK);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Steps 05-08: Validate invalid parameter handling
    result = dsSetFPTime(dsFPD_TIME_24_HOUR, 25, 30);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    result = dsSetFPTime(dsFPD_TIME_24_HOUR, 14, 60);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    result = dsSetFPTime(dsFPD_TIME_12_HOUR, 13, 30);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    result = dsSetFPTime(dsFPD_TIME_12_HOUR, 2, 60);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    // Step 09: Call dsSetFPDMode() with a valid parameter
    result = dsSetFPDMode(dsFPD_MODE_ANY);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Steps 10-13: Validate invalid parameter handling again
    result = dsSetFPTime(dsFPD_TIME_24_HOUR, 25, 30);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    result = dsSetFPTime(dsFPD_TIME_24_HOUR, 14, 60);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    result = dsSetFPTime(dsFPD_TIME_12_HOUR, 13, 30);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    result = dsSetFPTime(dsFPD_TIME_12_HOUR, 2, 60);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    // Step 14: Call dsSetFPDMode() with a valid parameter
    result = dsSetFPDMode(dsFPD_MODE_TEXT);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 15: Call dsSetFPTime() with valid parameters for 24-hour format
    result = dsSetFPTime(dsFPD_TIME_24_HOUR, 14, 30);
    UT_ASSERT_EQUAL(result, dsERR_OPERATION_NOT_SUPPORTED);

    // Step 16: Call dsSetFPDMode() with a valid parameter
    result = dsSetFPDMode(dsFPD_MODE_CLOCK);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 17: Terminate with dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 18: Call dsSetFPTime() after termination
    result = dsSetFPTime(dsFPD_TIME_24_HOUR, 14, 30);
    CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
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
 * |02|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_TEXT|dsERR_NONE|API should set mode successfully|
 * |03|Call dsSetFPText() with valid text|pText: "HELLO"|dsERR_NONE|Check the function with valid text|
 * |04|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_ANY|dsERR_NONE|API should set mode successfully|
 * |05|Call dsSetFPText() with valid text|pText: "HELLO"|dsERR_NONE|Check the function with valid text|
 * |06|Terminate with dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * 
 * @note This test case is deprecated.
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_positive_dsSetFPText (void)
{
    gTestID = 23;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;

    // Step 01: Initialize with dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Call dsSetFPDMode() with a valid parameter for TEXT mode
    result = dsSetFPDMode(dsFPD_MODE_TEXT);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Call dsSetFPText() with valid text for TEXT mode
    result = dsSetFPText("HELLO");
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 04: Call dsSetFPDMode() with a valid parameter for ANY mode
    result = dsSetFPDMode(dsFPD_MODE_ANY);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 05: Call dsSetFPText() with valid text for ANY mode
    result = dsSetFPText("HELLO");
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 06: Terminate with dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
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
 * |03|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_TEXT|dsERR_NONE|API should set mode successfully|
 * |04|Call dsSetFPText() with NULL pointer|pText: NULL|dsERR_INVALID_PARAM|Validate invalid parameter handling for NULL pText|
 * |05|Call dsSetFPText() with text longer than 10 characters|pText: "LONGTEXTHER"|dsERR_INVALID_PARAM|Validate invalid parameter handling for text length|
 * |06|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_ANY|dsERR_NONE|API should set mode successfully|
 * |07|Call dsSetFPText() with NULL pointer|pText: NULL|dsERR_INVALID_PARAM|Validate invalid parameter handling for NULL pText|
 * |08|Call dsSetFPText() with text longer than 10 characters|pText: "LONGTEXTHER"|dsERR_INVALID_PARAM|Validate invalid parameter handling for text length|
 * |09|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_CLOCK|dsERR_NONE|API should set mode successfully|
 * |10|Call dsSetFPText() with valid text|pText: "HELLO"|dsERR_OPERATION_NOT_SUPPORTED|Check the function with valid text|
 * |11|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_TEXT|dsERR_NONE|API should set mode successfully|
 * |12|Terminate with dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * |13|Call dsSetFPText() after termination|pText: "HELLO"|dsERR_NOT_INITIALIZED|Validate it checks for initialization even after termination|
 * 
 * @note This test case is deprecated.
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_negative_dsSetFPText (void)
{
    gTestID = 24;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;

    // Step 01: Call dsSetFPText() without initializing
    result = dsSetFPText("HELLO");
    CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    // Step 02: Initialize with dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Call dsSetFPDMode() with TEXT mode
    result = dsSetFPDMode(dsFPD_MODE_TEXT);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 04: Call dsSetFPText() with NULL pointer
    result = dsSetFPText(NULL);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    // Step 05: Call dsSetFPText() with text longer than 10 characters
    result = dsSetFPText("LONGTEXTHER");
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    // Step 06: Call dsSetFPDMode() with ANY mode
    result = dsSetFPDMode(dsFPD_MODE_ANY);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 07: Call dsSetFPText() with NULL pointer in ANY mode
    result = dsSetFPText(NULL);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    // Step 08: Call dsSetFPText() with text longer than 10 characters in ANY mode
    result = dsSetFPText("LONGTEXTHER");
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    // Step 09: Call dsSetFPDMode() with CLOCK mode
    result = dsSetFPDMode(dsFPD_MODE_CLOCK);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 10: Call dsSetFPText() with valid text in CLOCK mode
    result = dsSetFPText("HELLO");
    UT_ASSERT_EQUAL(result, dsERR_OPERATION_NOT_SUPPORTED);

    // Step 11: Call dsSetFPDMode() back to TEXT mode
    result = dsSetFPDMode(dsFPD_MODE_TEXT);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 12: Terminate with dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 13: Call dsSetFPText() after termination
    result = dsSetFPText("HELLO");
    CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
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
 * |02|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_TEXT|dsERR_NONE|API should set mode successfully|
 * |03|Call dsSetFPTextBrightness() with valid eIndicator and eBrightness|eIndicator: dsFPD_TEXTDISP_TEXT, eBrightness: 70|dsERR_NONE|Check the function with valid parameters|
 * |04|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_ANY|dsERR_NONE|API should set mode successfully|
 * |05|Call dsSetFPTextBrightness() with valid eIndicator and eBrightness|eIndicator: dsFPD_TEXTDISP_TEXT, eBrightness: 70|dsERR_NONE|Check the function with valid parameters|
 * |06|Terminate with dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * 
 * @note This test case is deprecated.
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_positive_dsSetFPTextBrightness(void)
{
    gTestID = 25;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;

    // Step 01: Initialize with dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Call dsSetFPDMode() with TEXT mode
    result = dsSetFPDMode(dsFPD_MODE_TEXT);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Call dsSetFPTextBrightness() with valid eIndicator and eBrightness for TEXT mode
    result = dsSetFPTextBrightness(dsFPD_TEXTDISP_TEXT, 70);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 04: Call dsSetFPDMode() with ANY mode
    result = dsSetFPDMode(dsFPD_MODE_ANY);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 05: Call dsSetFPTextBrightness() with valid eIndicator and eBrightness for ANY mode
    result = dsSetFPTextBrightness(dsFPD_TEXTDISP_TEXT, 70);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 06: Terminate with dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
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
 * |03|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_TEXT|dsERR_NONE|API should set mode successfully|
 * |04|Call dsSetFPTextBrightness() with invalid eBrightness (out of range)|eIndicator: dsFPD_TEXTDISP_TEXT, eBrightness: 110|dsERR_INVALID_PARAM|Validate invalid parameter handling for brightness level|
 * |05|Call dsSetFPTextBrightness() with invalid indicator|eIndicator: dsFPD_TEXTDISP_MAX, eBrightness: 50|dsERR_INVALID_PARAM|Validate invalid parameter handling for brightness level|
 * |06|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_ANY|dsERR_NONE|API should set mode successfully|
 * |07|Call dsSetFPTextBrightness() with invalid eBrightness (out of range)|eIndicator: dsFPD_TEXTDISP_TEXT, eBrightness: 110|dsERR_INVALID_PARAM|Validate invalid parameter handling for brightness level|
 * |08|Call dsSetFPTextBrightness() with invalid indicator|eIndicator: dsFPD_TEXTDISP_MAX, eBrightness: 50|dsERR_INVALID_PARAM|Validate invalid parameter handling for brightness level|
 * |09|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_CLOCK|dsERR_NONE|API should set mode successfully|
 * |10|Call dsSetFPTextBrightness() with valid eIndicator and eBrightness|eIndicator: dsFPD_TEXTDISP_TEXT, eBrightness: 70|dsERR_OPERATION_NOT_SUPPORTED|Check the function with valid parameters|
 * |11|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_TEXT|dsERR_NONE|API should set mode successfully|
 * |12|Terminate with dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * |13|Call dsSetFPTextBrightness() after termination|eIndicator: dsFPD_TEXTDISP_TEXT, eBrightness: 70|dsERR_NOT_INITIALIZED|Validate it checks for initialization even after termination|
 * 
 * @note This test case is deprecated.
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_negative_dsSetFPTextBrightness(void)
{
    gTestID = 26;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;

    // Step 01: Call dsSetFPTextBrightness() without initializing
    result = dsSetFPTextBrightness(dsFPD_TEXTDISP_TEXT, 70);
    CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    // Step 02: Initialize with dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Call dsSetFPDMode() with TEXT mode
    result = dsSetFPDMode(dsFPD_MODE_TEXT);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 04: Call dsSetFPTextBrightness() with invalid eBrightness (out of range)
    result = dsSetFPTextBrightness(dsFPD_TEXTDISP_TEXT, 110);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    // Step 05: Call dsSetFPTextBrightness() with invalid indicator
    result = dsSetFPTextBrightness(dsFPD_TEXTDISP_MAX, 50);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    // Step 06: Call dsSetFPDMode() with ANY mode
    result = dsSetFPDMode(dsFPD_MODE_ANY);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 07: Call dsSetFPTextBrightness() with invalid eBrightness for ANY mode
    result = dsSetFPTextBrightness(dsFPD_TEXTDISP_TEXT, 110);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    // Step 08: Call dsSetFPTextBrightness() with invalid indicator for ANY mode
    result = dsSetFPTextBrightness(dsFPD_TEXTDISP_MAX, 50);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    // Step 09: Call dsSetFPDMode() with CLOCK mode
    result = dsSetFPDMode(dsFPD_MODE_CLOCK);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 10: Call dsSetFPTextBrightness() with valid parameters for CLOCK mode
    result = dsSetFPTextBrightness(dsFPD_TEXTDISP_TEXT, 70);
    UT_ASSERT_EQUAL(result, dsERR_OPERATION_NOT_SUPPORTED);

    // Step 11: Call dsSetFPDMode() with TEXT mode again
    result = dsSetFPDMode(dsFPD_MODE_TEXT);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 12: Terminate with dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 13: Call dsSetFPTextBrightness() after termination
    result = dsSetFPTextBrightness(dsFPD_TEXTDISP_TEXT, 70);
    CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
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
 * |03|Call dsGetFPTextBrightness() with valid eIndicator|eIndicator: dsFPD_TEXTDISP_TEXT, eBrightness: Pointer to brightness variable|dsERR_NONE|Check function retrieves the correct brightness level|
 * |04|Call dsGetFPTextBrightness() with valid eIndicator|eIndicator: dsFPD_TEXTDISP_TEXT, eBrightness: Pointer to brightness variable|dsERR_NONE|Check function retrieves the correct brightness level|
 * |05|Compare the results from step 3/4 and make sure they're the same||Success|The values should be the same|
 * |06|Terminate with dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * 
 * @note This test case is deprecated.
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_positive_dsGetFPTextBrightness(void)
{
    gTestID = 27;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;
    dsFPDBrightness_t brightness1 = 0;
    dsFPDBrightness_t brightness2 = 0;

    // Step 01: Initialize with dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Call dsGetFPTextBrightness() with valid eIndicator
    result = dsGetFPTextBrightness(dsFPD_TEXTDISP_TEXT, &brightness1);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Call dsGetFPTextBrightness() with valid eIndicator again
    result = dsGetFPTextBrightness(dsFPD_TEXTDISP_TEXT, &brightness2);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 04: Compare the results from step 3/4 and make sure they're the same
    UT_ASSERT_EQUAL(brightness1, brightness2);

    // Step 05: Terminate with dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
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
 * |03|Call dsGetFPTextBrightness() with NULL for eBrightness|eIndicator: dsFPD_TEXTDISP_TEXT, eBrightness: NULL|dsERR_INVALID_PARAM|Check function detects NULL pointer parameter|
 * |04|Call dsGetFPTextBrightness() with invalid indicator|eIndicator: dsFPD_TEXTDISP_MAX, eBrightness: NULL|dsERR_INVALID_PARAM|Check function detects NULL pointer parameter|
 * |05|Terminate with dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * |06|Call dsGetFPTextBrightness() after termination|eIndicator: dsFPD_TEXTDISP_TEXT, eBrightness: Pointer to brightness variable|dsERR_NOT_INITIALIZED|Validate it checks for initialization even after termination|
 * 
 * @note This test case is deprecated.
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_negative_dsGetFPTextBrightness(void)
{
    gTestID = 28;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;
    dsFPDBrightness_t brightness;

    // Step 01: Call dsGetFPTextBrightness() without initializing (dsFPInit() not called)
    result = dsGetFPTextBrightness(dsFPD_TEXTDISP_TEXT, &brightness);
    CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    // Step 02: Initialize with dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Call dsGetFPTextBrightness() with NULL for eBrightness
    result = dsGetFPTextBrightness(dsFPD_TEXTDISP_TEXT, NULL);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    // Step 04: Call dsGetFPTextBrightness() with invalid indicator
    result = dsGetFPTextBrightness(dsFPD_TEXTDISP_MAX, NULL);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    // Step 05: Terminate with dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 06: Call dsGetFPTextBrightness() after termination
    result = dsGetFPTextBrightness(dsFPD_TEXTDISP_TEXT, &brightness);
    CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
}

/**
 * @brief Ensure dsFPEnableCLockDisplay() correctly enables/disables the clock display
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
 * |02|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_CLOCK|dsERR_NONE|API should set mode successfully|
 * |03|Enable clock display using dsFPEnableCLockDisplay()|enable: 1|dsERR_NONE|Validate that clock display can be enabled|
 * |04|Disable clock display using dsFPEnableCLockDisplay()|enable: 0|dsERR_NONE|Validate that clock display can be disabled|
 * |05|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_ANY|dsERR_NONE|API should set mode successfully|
 * |06|Enable clock display using dsFPEnableCLockDisplay()|enable: 1|dsERR_NONE|Validate that clock display can be enabled|
 * |07|Disable clock display using dsFPEnableCLockDisplay()|enable: 0|dsERR_NONE|Validate that clock display can be disabled|
 * |08|Terminate with dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * 
 * @note This test case is deprecated.
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_positive_dsFPEnableCLockDisplay(void)
{
    gTestID = 29;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;

    // Step 01: Initialize with dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Call dsSetFPDMode() with a valid parameter
    result = dsSetFPDMode(dsFPD_MODE_CLOCK);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Enable clock display using dsFPEnableCLockDisplay()
    result = dsFPEnableCLockDisplay(1);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 04: Disable clock display using dsFPEnableCLockDisplay()
    result = dsFPEnableCLockDisplay(0);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 05: Call dsSetFPDMode() with a valid parameter
    result = dsSetFPDMode(dsFPD_MODE_ANY);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 06: Enable clock display using dsFPEnableCLockDisplay()
    result = dsFPEnableCLockDisplay(1);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 07: Disable clock display using dsFPEnableCLockDisplay()
    result = dsFPEnableCLockDisplay(0);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 08: Terminate with dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
}

/**
 * @brief Ensure dsFPEnableCLockDisplay() handles error scenarios correctly
 * 
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
 * |01|Call dsFPEnableCLockDisplay() without initializing (dsFPInit() not called)|enable: 1|dsERR_NOT_INITIALIZED|Validate that the function checks for initialization|
 * |02|Initialize with dsFPInit()||dsERR_NONE|Ensure the system is initialized|
 * |03|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_CLOCK|dsERR_NONE|API should set mode successfully|
 * |04|Call dsFPEnableCLockDisplay() with invalid value for enable|enable: 2|dsERR_INVALID_PARAM|Check function detects invalid parameter|
 * |05|Call dsFPEnableCLockDisplay() with invalid value for enable|enable: -1|dsERR_INVALID_PARAM|Check function detects invalid parameter|
 * |06|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_ANY|dsERR_NONE|API should set mode successfully|
 * |07|Call dsFPEnableCLockDisplay() with invalid value for enable|enable: 2|dsERR_INVALID_PARAM|Check function detects invalid parameter|
 * |08|Call dsFPEnableCLockDisplay() with invalid value for enable|enable: -1|dsERR_INVALID_PARAM|Check function detects invalid parameter|
 * |09|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_TEXT|dsERR_NONE|API should set mode successfully|
 * |10|Call dsFPEnableCLockDisplay() with invalid value for enable|enable: 1|dsERR_OPERATION_NOT_SUPPORTED|Check function detects invalid parameter|
 * |11|Terminate with dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * |12|Call dsFPEnableCLockDisplay() after termination|enable: 1|dsERR_NOT_INITIALIZED|Validate it checks for initialization even after termination|
 * 
 * @note This test case is deprecated.
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_negative_dsFPEnableCLockDisplay(void)
{
    gTestID = 30;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;

    // Step 01: Call dsFPEnableCLockDisplay() without initializing
    result = dsFPEnableCLockDisplay(1);
    CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    // Step 02: Initialize with dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Call dsSetFPDMode() with a valid parameter
    result = dsSetFPDMode(dsFPD_MODE_CLOCK);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 04: Call dsFPEnableCLockDisplay() with invalid value for enable
    result = dsFPEnableCLockDisplay(2);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    // Step 05: Call dsFPEnableCLockDisplay() with invalid value for enable
    result = dsFPEnableCLockDisplay(-1);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    // Step 06: Call dsSetFPDMode() with a valid parameter
    result = dsSetFPDMode(dsFPD_MODE_ANY);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 07: Call dsFPEnableCLockDisplay() with invalid value for enable
    result = dsFPEnableCLockDisplay(2);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    // Step 08: Call dsFPEnableCLockDisplay() with invalid value for enable
    result = dsFPEnableCLockDisplay(-1);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    // Step 09: Call dsSetFPDMode() with a valid parameter
    result = dsSetFPDMode(dsFPD_MODE_TEXT);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 10: Call dsFPEnableCLockDisplay() with invalid value for enable
    result = dsFPEnableCLockDisplay(1);
    UT_ASSERT_EQUAL(result, dsERR_OPERATION_NOT_SUPPORTED);

    // Step 11: Terminate with dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 12: Call dsFPEnableCLockDisplay() after termination
    result = dsFPEnableCLockDisplay(1);
    CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
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
 * |02|Call dsSetFPScroll() for horizontal scrolling with valid parameters|uScrollHoldOnDur: 1000, uHorzScrollIterations: 5, uVertScrollIterations: 0|dsERR_NONE|Horizontal scrolling should occur on the display. Observe for text movement from right to left|
 * |03|Call dsSetFPScroll() for vertical scrolling with valid parameters|uScrollHoldOnDur: 1000, uHorzScrollIterations: 0, uVertScrollIterations: 5|dsERR_NONE|Vertical scrolling should occur on the display. Observe for text movement from bottom to top|
 * |04|Call dsSetFPScroll() with minimum valid parameters for quick scrolling|uScrollHoldOnDur: 100, uHorzScrollIterations: 1, uVertScrollIterations: 0|dsERR_NONE|Quick horizontal scrolling should occur on the display|
 * |05|Call dsSetFPScroll() with minimum valid parameters for quick scrolling|uScrollHoldOnDur: 100, uHorzScrollIterations: 0, uVertScrollIterations: 1|dsERR_NONE|Quick horizontal scrolling should occur on the display|
 * |06|Terminate using dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * 
 * @note This test case is deprecated.
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_positive_dsSetFPScroll(void)
{
    gTestID = 31;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;

    // Step 01: Initialize using dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Call dsSetFPScroll() for horizontal scrolling with valid parameters
    result = dsSetFPScroll(1000, 5, 0);
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    // Wait or observer function might be necessary to give testers time to see the display scrolling.

    // Step 03: Call dsSetFPScroll() for vertical scrolling with valid parameters
    result = dsSetFPScroll(1000, 0, 5);
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    // Wait or observer function might be necessary to give testers time to see the display scrolling.

    // Step 04: Call dsSetFPScroll() with minimum valid parameters for quick scrolling
    result = dsSetFPScroll(100, 1, 0);
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    // Wait or observer function might be necessary to give testers time to see the display scrolling.

    // Step 05: Call dsSetFPScroll() with minimum valid parameters for quick scrolling
    result = dsSetFPScroll(100, 0, 1);
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    // Wait or observer function might be necessary to give testers time to see the display scrolling.

    // Step 06: Terminate using dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
}

/**
 * @brief Ensure dsSetFPScroll() handles error scenarios correctly
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
 * |03|Call dsSetFPScroll() with invalid value for uScrollHoldOnDur|uScrollHoldOnDur: 0, uHorzScrollIterations: 5, uVertScrollIterations: 0|dsERR_INVALID_PARAM|Check function detects invalid parameter|
 * |04|Call dsSetFPScroll() with both horizontal and vertical scroll iterations|uScrollHoldOnDur: 1000, uHorzScrollIterations: 5, uVertScrollIterations: 5|dsERR_OPERATION_NOT_SUPPORTED|Validate it detects conflicting scroll directions|
 * |05|Terminate with dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * |06|Call dsSetFPScroll() after termination|uScrollHoldOnDur: 1000, uHorzScrollIterations: 5, uVertScrollIterations: 0|dsERR_NOT_INITIALIZED|Validate it checks for initialization even after termination|
 * 
 * @note This test case is deprecated.
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_negative_dsSetFPScroll(void)
{
    gTestID = 32;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;

    // Step 01: Call dsSetFPScroll() without initializing (dsFPInit() not called)
    result = dsSetFPScroll(1000, 5, 5);
    CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    // Step 02: Initialize with dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Call dsSetFPScroll() with invalid value for uScrollHoldOnDur
    result = dsSetFPScroll(0, 5, 0);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    // Step 04: Call dsSetFPScroll() with both horizontal and vertical scroll iterations
    result = dsSetFPScroll(1000, 5, 5);
    UT_ASSERT_EQUAL(result, dsERR_OPERATION_NOT_SUPPORTED);

    // Step 05: Terminate with dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 06: Call dsSetFPScroll() after termination
    result = dsSetFPScroll(1000, 5, 0);
    CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
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
 * |02|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_CLOCK|dsERR_NONE|API should set mode successfully|
 * |03|Call dsSetFPTimeFormat() with a valid 12-hour format|eTimeFormat: dsFPD_TIME_12_HOUR|dsERR_NONE|Attempt to set time in 12-hour format|
 * |04|Call dsSetFPTimeFormat() with a valid 24-hour format|eTimeFormat: dsFPD_TIME_24_HOUR|dsERR_NONE|Attempt to set time in 24-hour format|
 * |05|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_ANY|dsERR_NONE|API should set mode successfully|
 * |06|Call dsSetFPTimeFormat() with a valid 12-hour format|eTimeFormat: dsFPD_TIME_12_HOUR|dsERR_NONE|Attempt to set time in 12-hour format|
 * |07|Call dsSetFPTimeFormat() with a valid 24-hour format|eTimeFormat: dsFPD_TIME_24_HOUR|dsERR_NONE|Attempt to set time in 24-hour format|
 * |08|Terminate using dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * 
 * @note This test case is deprecated.
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_positive_dsSetFPTimeFormat(void)
{
    gTestID = 33;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;

    // Step 01: Initialize using dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Call dsSetFPDMode() with a valid parameter
    result = dsSetFPDMode(dsFPD_MODE_CLOCK);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Call dsSetFPTimeFormat() with a valid 12-hour format
    result = dsSetFPTimeFormat(dsFPD_TIME_12_HOUR);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 04: Call dsSetFPTimeFormat() with a valid 24-hour format
    result = dsSetFPTimeFormat(dsFPD_TIME_24_HOUR);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 05: Call dsSetFPDMode() with a valid parameter
    result = dsSetFPDMode(dsFPD_MODE_ANY);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 06: Call dsSetFPTimeFormat() with a valid 12-hour format
    result = dsSetFPTimeFormat(dsFPD_TIME_12_HOUR);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 07: Call dsSetFPTimeFormat() with a valid 24-hour format
    result = dsSetFPTimeFormat(dsFPD_TIME_24_HOUR);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 08: Terminate using dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
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
 * |01|Call dsSetFPTimeFormat() without initializing the system|eTimeFormat: dsFPD_TIME_12_HOUR|dsERR_NOT_INITIALIZED|API should not work without initialization|
 * |02|Initialize using dsFPInit()||dsERR_NONE|Ensure the system is initialized|
 * |03|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_CLOCK|dsERR_NONE|API should set mode successfully|
 * |04|Call dsSetFPTimeFormat() with an invalid time format|eTimeFormat: dsFPD_TIME_MAX|dsERR_INVALID_PARAM|API should validate parameter|
 * |05|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_ANY|dsERR_NONE|API should set mode successfully|
 * |06|Call dsSetFPTimeFormat() with an invalid time format|eTimeFormat: dsFPD_TIME_MAX|dsERR_INVALID_PARAM|API should validate parameter|
 * |07|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_TEXT|dsERR_NONE|API should set mode successfully|
 * |08|Call dsSetFPTimeFormat() with a valid 12-hour format|eTimeFormat: dsFPD_TIME_12_HOUR|dsERR_OPERATION_NOT_SUPPORTED|Attempt to set time in 12-hour format|
 * |09|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_CLOCK|dsERR_NONE|API should set mode successfully|
 * |10|Terminate using dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * |11|Call dsSetFPTimeFormat() after termination|eTimeFormat: dsFPD_TIME_24_HOUR|dsERR_NOT_INITIALIZED|API should not work after termination|
 * 
 * @note This test case is deprecated.
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_negative_dsSetFPTimeFormat(void)
{
    gTestID = 34;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;

    // Step 01: Call dsSetFPTimeFormat() without initializing the system
    result = dsSetFPTimeFormat(dsFPD_TIME_12_HOUR);
    CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    // Step 02: Initialize using dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Call dsSetFPDMode() with a valid parameter
    result = dsSetFPDMode(dsFPD_MODE_CLOCK);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 04: Call dsSetFPTimeFormat() with an invalid time format
    result = dsSetFPTimeFormat(dsFPD_TIME_MAX);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    // Step 05: Call dsSetFPDMode() with a valid parameter
    result = dsSetFPDMode(dsFPD_MODE_ANY);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 06: Call dsSetFPTimeFormat() with an invalid time format
    result = dsSetFPTimeFormat(dsFPD_TIME_MAX);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    // Step 07: Call dsSetFPDMode() with a valid parameter
    result = dsSetFPDMode(dsFPD_MODE_TEXT);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 08: Call dsSetFPTimeFormat() with a valid 12-hour format
    result = dsSetFPTimeFormat(dsFPD_TIME_12_HOUR);
    UT_ASSERT_EQUAL(result, dsERR_OPERATION_NOT_SUPPORTED);

    // Step 09: Call dsSetFPDMode() with a valid parameter
    result = dsSetFPDMode(dsFPD_MODE_CLOCK);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 10: Terminate using dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 11: Call dsSetFPTimeFormat() after termination
    result = dsSetFPTimeFormat(dsFPD_TIME_24_HOUR);
    CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
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
 * |02|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_CLOCK|dsERR_NONE|API should set mode successfully|
 * |03|Call dsSetFPTimeFormat() with a valid 12-hour format|eTimeFormat: dsFPD_TIME_12_HOUR|dsERR_NONE|Attempt to set time in 12-hour format|
 * |04|Call dsGetFPTimeFormat() to retrieve the set time format|dsFPDTimeFormat_t*|dsERR_NONE|Should get the previously set time format|
 * |05|Call dsGetFPTimeFormat() to retrieve the new time format|dsFPDTimeFormat_t*|dsERR_NONE|Should get the newly set time format|
 * |06|Compare the results to make sure the returned values are the same||Success|The values should be the same|
 * |07|Terminate using dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 *
 * @note This test case is deprecated.
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_positive_dsGetFPTimeFormat(void)
{
    gTestID = 35;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;
    dsFPDTimeFormat_t initialTimeFormat, setTimeFormat, retrievedTimeFormat;

    // Step 01: Initialize using dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Call dsSetFPDMode() with a valid parameter
    result = dsSetFPDMode(dsFPD_MODE_CLOCK);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Call dsSetFPTimeFormat() with a valid 12-hour format
    setTimeFormat = dsFPD_TIME_12_HOUR;
    result = dsSetFPTimeFormat(setTimeFormat);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 04: Call dsGetFPTimeFormat() to retrieve the set time format
    result = dsGetFPTimeFormat(&initialTimeFormat);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 05: Call dsGetFPTimeFormat() to retrieve the new time format
    result = dsGetFPTimeFormat(&retrievedTimeFormat);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 06: Compare the results to make sure the returned values are the same
    UT_ASSERT_EQUAL(initialTimeFormat, retrievedTimeFormat);
    UT_ASSERT_EQUAL(setTimeFormat, retrievedTimeFormat);

    // Step 07: Terminate using dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
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
 * |03|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_CLOCK|dsERR_NONE|API should set mode successfully|
 * |04|Call dsGetFPTimeFormat() with NULL parameter|pTimeFormat: NULL|dsERR_INVALID_PARAM|API should validate parameter|
 * |05|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_TEXT|dsERR_NONE|API should set mode successfully|
 * |06|Call dsGetFPTimeFormat() to retrieve the set time format|dsFPDTimeFormat_t*|dsERR_OPERATION_NOT_SUPPORTED|Should get the previously set time format|
 * |07|Call dsSetFPDMode() with a valid parameter|eMode: dsFPD_MODE_CLOCK|dsERR_NONE|API should set mode successfully|
 * |08|Terminate using dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * |09|Call dsGetFPTimeFormat() after termination|dsFPDTimeFormat_t*|dsERR_NOT_INITIALIZED|API should not work after termination|
 * 
 * @note This test case is deprecated.
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_negative_dsGetFPTimeFormat(void)
{
    gTestID = 36;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;
    dsFPDTimeFormat_t timeFormat;

    // Step 01: Call dsGetFPTimeFormat() without initializing the system
    result = dsGetFPTimeFormat(&timeFormat);
    CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    // Step 02: Initialize using dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Call dsSetFPDMode() with a valid parameter for CLOCK mode
    result = dsSetFPDMode(dsFPD_MODE_CLOCK);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 04: Call dsGetFPTimeFormat() with NULL parameter
    result = dsGetFPTimeFormat(NULL);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    // Step 05: Call dsSetFPDMode() with a valid parameter for TEXT mode
    result = dsSetFPDMode(dsFPD_MODE_TEXT);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 06: Call dsGetFPTimeFormat() to retrieve the set time format in TEXT mode
    result = dsGetFPTimeFormat(&timeFormat);
    UT_ASSERT_EQUAL(result, dsERR_OPERATION_NOT_SUPPORTED);

    // Step 07: Call dsSetFPDMode() with a valid parameter for CLOCK mode
    result = dsSetFPDMode(dsFPD_MODE_CLOCK);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 08: Terminate using dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 09: Call dsGetFPTimeFormat() after termination
    result = dsGetFPTimeFormat(&timeFormat);
    CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
}

/**
 * @brief Validate the consistent retrieval of supported LED states using dsFPGetSupportedLEDStates()
 * 
 * **Test Group ID:** FPGetSupportedLEDStates: 01@n
 * **Test Case ID:** 037@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** dsFPInit, dsFPTerm, dsFPGetSupportedLEDStates@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|---------|---------------|-----|
 * |01|Initialize using dsFPInit()||dsERR_NONE|Ensure the system is initialized|
 * |02|Retrieve the supported LED states for the first time using dsFPGetSupportedLEDStates()|states1: A valid pointer to an unsigned int|dsERR_NONE and states1 value should be set|First retrieval of supported LED states|
 * |03|Retrieve the supported LED states for the second time using dsFPGetSupportedLEDStates()|states2: A valid pointer to an unsigned int|dsERR_NONE and states2 value should be set|Second retrieval of supported LED states|
 * |04|Compare the values retrieved from states1 and states2||The values of states1 and states2 should be identical|Ensure consistent retrieval of supported LED states|
 * |05|Terminate using dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * 
 * **Notes:**@n
 * This test checks the consistent behavior of the dsFPGetSupportedLEDStates() function by ensuring it returns the same values on multiple calls.
 */
void test_l1_dsFPD_positive_dsFPGetSupportedLEDStates(void)
{
    gTestID = 37;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;
    unsigned int states1 = 0;
    unsigned int states2 = 0;

    // Step 01: Initialize using dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Retrieve the supported LED states for the first time using dsFPGetSupportedLEDStates()
    result = dsFPGetSupportedLEDStates(&states1);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Retrieve the supported LED states for the second time using dsFPGetSupportedLEDStates()
    result = dsFPGetSupportedLEDStates(&states2);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 04: Compare the values retrieved from states1 and states2
    UT_ASSERT_EQUAL(states1, states2);

    // Step 05: Terminate using dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
}

/**
 * @brief Validate the negative scenarios of dsFPGetSupportedLEDStates()
 * 
 * **Test Group ID:** FPGetSupportedLEDStates: 02@n
 * **Test Case ID:** 038@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** dsFPInit, dsFPTerm, dsFPGetSupportedLEDStates@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|---------|---------------|-----|
 * |01|Call dsFPGetSupportedLEDStates() before initialization|states: A valid pointer to an unsigned int|dsERR_NOT_INITIALIZED|API should not work without initialization|
 * |02|Initialize using dsFPInit()||dsERR_NONE|Ensure the system is initialized|
 * |03|Call dsFPGetSupportedLEDStates() with a null pointer|states: NULL|dsERR_INVALID_PARAM|API should validate the parameter and return an error for invalid input|
 * |04|Terminate using dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * |05|Call dsFPGetSupportedLEDStates() after termination|states: A valid pointer to an unsigned int|dsERR_NOT_INITIALIZED|API should not work after termination|
 * 
 * **Notes:**@n
 * Ensure that test steps are adapted based on actual system capabilities and that subsequent tests or use-case scenarios are not inadvertently impacted.
 */
void test_l1_dsFPD_negative_dsFPGetSupportedLEDStates(void)
{
    gTestID = 38;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;
    unsigned int states;

    // Step 01: Call dsFPGetSupportedLEDStates() before initialization
    result = dsFPGetSupportedLEDStates(&states);
    CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    // Step 02: Initialize using dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Call dsFPGetSupportedLEDStates() with a null pointer
    result = dsFPGetSupportedLEDStates(NULL);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    // Step 04: Terminate using dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 05: Call dsFPGetSupportedLEDStates() after termination
    result = dsFPGetSupportedLEDStates(&states);
    CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
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
 * |03|Call dsFPSetLEDState() and loop through all LED states|state: A valid dsFPDLedState_t value|dsERR_NONE|The LED state should be set successfully|
 * |04|Terminate using dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * 
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_positive_dsFPSetLEDState(void)
{
    gTestID = 39;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;
    unsigned int supportedLEDStates;
    dsFPDLedState_t ledState;

    // Step 01: Initialize using dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()
    enableFPDIndicators();

    // Retrieve supported LED states
    result = dsFPGetSupportedLEDStates(&supportedLEDStates);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Call dsFPSetLEDState() and loop through all supported LED states
    for (ledState = 0; ledState < dsFPD_LED_DEVICE_MAX; ledState++)
    {
        if(supportedLEDStates & (1<<ledState)){
            result = dsFPSetLEDState(ledState);
            UT_ASSERT_EQUAL(result, dsERR_NONE);
        }
    }

    // Step 04: Terminate using dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
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
 * |03|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |04|Call dsFPSetLEDState() with an invalid LED state|state: dsFPD_LED_DEVICE_MAX|dsERR_INVALID_PARAM|API should validate the parameter and return an error for invalid input|
 * |05|Terminate using dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * |06|Call dsFPSetLEDState() after termination|state: dsFPD_LED_DEVICE_ACTIVE|dsERR_NOT_INITIALIZED|API should not work after termination|
 * 
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_negative_dsFPSetLEDState(void)
{
    gTestID = 40;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;

    // Step 01: Call dsFPSetLEDState() before initialization
    result = dsFPSetLEDState(dsFPD_LED_DEVICE_ACTIVE);
    CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    // Step 02: Initialize using dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()
    enableFPDIndicators();

    // Step 04: Call dsFPSetLEDState() with an invalid LED state
    result = dsFPSetLEDState(dsFPD_LED_DEVICE_MAX);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    // Step 05: Terminate using dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 06: Call dsFPSetLEDState() after termination
    result = dsFPSetLEDState(dsFPD_LED_DEVICE_ACTIVE);
    CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
}

/**
 * @brief Validate the positive flow of dsFPGetLEDState()
 * 

 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 041@n
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
 * |03|Call dsFPSetLEDState() with valid value|state: dsFPD_LED_DEVICE_ACTIVE|dsERR_NONE|The LED state should be set successfully|
 * |04|Call dsFPGetLEDState() with a valid parameter|state: dsFPDLedState_t*|dsERR_NONE|API should retrieve the current state successfully|
 * |05|Call dsFPGetLEDState() with a valid parameter|state: dsFPDLedState_t*|dsERR_NONE|API should retrieve the current state successfully|
 * |06|Compare the returned values from steps 3/4 ||Success|The values should be the same|
 * |07|Terminate using dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * 
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_positive_dsFPGetLEDState(void)
{
    gTestID = 41;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;
    dsFPDLedState_t ledState1, ledState2;

    // Step 01: Initialize using dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()
    enableFPDIndicators();

    // Step 03: Call dsFPSetLEDState() with a valid value
    result = dsFPSetLEDState(dsFPD_LED_DEVICE_ACTIVE);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 04: Call dsFPGetLEDState() with a valid parameter
    result = dsFPGetLEDState(&ledState1);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 05: Call dsFPGetLEDState() with a valid parameter again
    result = dsFPGetLEDState(&ledState2);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 06: Compare the returned values from steps 3/4
    UT_ASSERT_EQUAL(ledState1, ledState2);

    // Step 07: Terminate using dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
}


/**
 * @brief Validate the negative scenarios of dsFPGetLEDState()
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 042@n
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
 * |02|Initialize using dsFPInit()||dsERR_NONE|Ensure the system is initialized|
 * |03|Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()|eIndicator: [Valid Indicator], state: dsFPD_STATE_ON |dsERR_NONE|Ensure the system is initialized|
 * |04|Call dsFPGetLEDState() with a NULL pointer|state: NULL|dsERR_INVALID_PARAM|API should not accept NULL pointer parameter|
 * |05|Terminate using dsFPTerm()||dsERR_NONE|Ensure the system is terminated|
 * |06|Call dsFPGetLEDState() after termination|state:dsFPDLedState_t*|dsERR_NOT_INITIALIZED|API should not work after termination|
 * 
 * @note Valid indicators can retrieved from id element in kIndicators in the dsFPDSettings.h file
 */
void test_l1_dsFPD_negative_dsFPGetLEDState(void)
{
    gTestID = 42;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;
    dsFPDLedState_t ledState;

    // Step 01: Call dsFPGetLEDState() before initialization
    result = dsFPGetLEDState(&ledState);
    CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    // Step 02: Initialize using dsFPInit()
    result = dsFPInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Set all valid indicators to dsFPD_STATE_ON using dsSetFPState()
    enableFPDIndicators();

    // Step 04: Call dsFPGetLEDState() with a NULL pointer
    result = dsFPGetLEDState(NULL);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    // Step 05: Terminate using dsFPTerm()
    result = dsFPTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 06: Call dsFPGetLEDState() after termination
    result = dsFPGetLEDState(&ledState);
    CHECK_FOR_EXTENDED_ERROR_CODE( result, dsERR_NOT_INITIALIZED, dsERR_NONE);
    UT_LOG("\n Out  %s\n",__FUNCTION__);
}

static UT_test_suite_t * pSuite = NULL;
static UT_test_suite_t * pSuite7Segment = NULL;

/**
 * @brief Register the main test(s) for this module
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
    if ( NULL == pSuite7Segment )
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
        UT_add_test( pSuite, "dsFPSetLEDState_L1_positive" ,test_l1_dsFPD_positive_dsFPSetLEDState );
	UT_add_test( pSuite, "dsFPGetSupportedLEDStates_L1_positive" ,test_l1_dsFPD_positive_dsFPGetSupportedLEDStates );
        UT_add_test( pSuite, "dsFPGetSupportedLEDStates_L1_negative" ,test_l1_dsFPD_negative_dsFPGetSupportedLEDStates );
	UT_add_test( pSuite, "dsFPSetLEDState_L1_negative" ,test_l1_dsFPD_negative_dsFPSetLEDState );
	UT_add_test( pSuite, "dsFPGetLEDState_L1_positive" ,test_l1_dsFPD_positive_dsFPGetLEDState );
	UT_add_test( pSuite, "dsFPGetLEDState_L1_negative" ,test_l1_dsFPD_negative_dsFPGetLEDState );
	

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
	

        extendedEnumsSupported = ut_kvp_getBoolField( ut_kvp_profile_getInstance(), "dsFPD/features/extendedEnumsSupported" );

	return 0;
} 

/** @} */ // End of DS_FPD_HALTEST_L1
/** @} */ // End of DS_FPD_HALTEST
/** @} */ // End of Device_Settings_HALTEST
/** @} */ // End of Device_Settings
/** @} */ // End of HPK
