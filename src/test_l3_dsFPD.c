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
 * @defgroup DS_FPD_HALTEST_L3 Device Settings Front Panel Display HAL Tests L3 File
 * @{
 * @parblock
 *
 * ### L3 Tests for DS Front Panel Display HAL :
 *
 * ## Module's Role
 * This module includes Level 3 functional test interfaces.
 * This Test Interfaces provides a scope to create a User Test cases for Device Settigns Front Panel modules that can be either Manual or automated scripts.
 *
 * **Pre-Conditions:**  None@n
 * **Dependencies:** None@n
 *
 * Refer to API Definition specification documentation : [hdmi-cec_halSpec.md](../../docs/pages/ds-front-panel-display_High-Level_TestSpec.md)
 *
 * @endparblock
 */


/**
 * @file test_l3_dsFPD.c
 *
 */

#include <ut.h>
#include <ut_log.h>
#include <ut_kvp_profile.h>
#include "dsFPD.h"

#define TIMEOUT 5
#define REPLY_TIMEOUT 5
#define DS_FPD_KEY_SIZE 128

static int gTestGroup = 3;
static int gTestID = 1;

typedef struct _stringkey_mapping
{
    char* stringValue;
    int32_t keyCode;
} stringkey_mapping;

const static stringkey_mapping dsFrontPanelIndicatorTable[] = {
    {"dsFPD_INDICATOR_MESSAGE", (int32_t)dsFPD_INDICATOR_MESSAGE},
    {"dsFPD_INDICATOR_POWER", (int32_t)dsFPD_INDICATOR_POWER},
    {"dsFPD_INDICATOR_RECORD", (int32_t)dsFPD_INDICATOR_RECORD},
    {"dsFPD_INDICATOR_REMOTE", (int32_t)dsFPD_INDICATOR_REMOTE},
    {"dsFPD_INDICATOR_RFBYPASS", (int32_t)dsFPD_INDICATOR_RFBYPASS},
    {"dsFPD_INDICATOR_MAX", (int32_t)dsFPD_INDICATOR_MAX},
    {NULL, -1}
};

const static stringkey_mapping dsFrontPanelStateTable[] = {
    {"dsFPD_STATE_OFF", (int32_t)dsFPD_STATE_OFF},
    {"dsFPD_STATE_ON", (int32_t)dsFPD_STATE_ON},
    {"dsFPD_STATE_MAX", (int32_t)dsFPD_STATE_MAX}
};
const static stringkey_mapping dsFrontPanelColorTable[] = {
    {"dsFPD_COLOR_BLUE", (int32_t)(0x0000FF)},
    {"dsFPD_COLOR_GREEN", (int32_t)(0x00FF00)},
    {"dsFPD_COLOR_RED", (int32_t)(0xFF0000)},
    {"dsFPD_COLOR_YELLOW", (int32_t)(0xFFFFE0)},
    {"dsFPD_COLOR_ORANGE", (int32_t)(0xFF8C00)},
    {"dsFPD_COLOR_WHITE", (int32_t)(0xFFFFFF)},
    {NULL, -1}
};
const static stringkey_mapping dsFrontPanelLEDState[] = {
    {"dsFPD_LED_DEVICE_NONE", (int32_t)dsFPD_LED_DEVICE_NONE},
    {"dsFPD_LED_DEVICE_ACTIVE", (int32_t)dsFPD_LED_DEVICE_ACTIVE},
    {"dsFPD_LED_DEVICE_STANDBY", (int32_t)dsFPD_LED_DEVICE_STANDBY},
    {"dsFPD_LED_DEVICE_WPS_CONNECTING", (int32_t)dsFPD_LED_DEVICE_WPS_CONNECTING},
    {"dsFPD_LED_DEVICE_WPS_CONNECTED", (int32_t)dsFPD_LED_DEVICE_WPS_CONNECTED},
    {"dsFPD_LED_DEVICE_WPS_ERROR", (int32_t)dsFPD_LED_DEVICE_WPS_ERROR},
    {"dsFPD_LED_DEVICE_FACTORY_RESET", (int32_t)dsFPD_LED_DEVICE_FACTORY_RESET},
    {"dsFPD_LED_DEVICE_USB_UPGRADE", (int32_t)dsFPD_LED_DEVICE_USB_UPGRADE},
    {"dsFPD_LED_DEVICE_SOFTWARE_DOWNLOAD_ERROR", (int32_t)dsFPD_LED_DEVICE_SOFTWARE_DOWNLOAD_ERROR},
    {"dsFPD_LED_DEVICE_MAX", (int32_t)dsFPD_LED_DEVICE_MAX},
    {NULL, -1}
};



/**
 * @brief This functions gets the Enum mapping string.
 *
 * This functions gets the Enum mapping string.
 *
 */
static char* mapKeyToString(const stringkey_mapping* keyMappingTable, int32_t keyCode) {
    if (keyMappingTable == NULL) {
        return NULL;
    }

    for (int32_t i = 0; keyMappingTable[i].stringValue != NULL; i++) {
        if (keyMappingTable[i].keyCode == keyCode) {
            return keyMappingTable[i].stringValue;
        }
    }

    return "Unknown value";
}

/**
* @brief Initialization of the Device settings - Front Panel Module
*
* This test provides a scope to open the Front Panel module and preserve the handle.

*
* **Test Group ID:** 03@n
*
* **Test Case ID:** 001@n
*
* **Pre-Conditions:** None@n
*
* **Dependencies:** None@n
*
* **User Interaction:** @n
* User or Automation tool should select the Test 1 to before running any test.
*
*/

void test_l3_dsFPD_hal_Init(void)
{
   gTestID = 1;
   dsError_t status = dsERR_NONE;

   UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

   // Step 1: Call dsFPInit()
   UT_LOG_INFO("Calling dsFPInit()");
   status = dsFPInit();
   if (status != dsERR_NONE)
   {
       UT_LOG_ERROR("Failed to Invoke HdmiCecOpen()");
   }

   UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test provides a scope to add the sink logical address. Usually it shall be zero.
*
* This test case provides a scope to add the available sink logical address
* to a Device under test.
*
* Note:
* This applies only for the Sink Devices.
* Source devices will get the logical address during CEC open.
*
* **Test Group ID:** 02@n
*
* **Test Case ID:** 002@n
*
* **Pre-Conditions:** @n
* HDMI-CEC Module should be intialized through Test 1 before calling this test.
*
* **Dependencies:** None@n
*
* **User Interaction:** @n
* User or Automation tool should select the Test 2 and provide the logical address.
*
*/
void test_l3_dsFPD_hal_SetFPBlink(void)
{
    gTestID = 2;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t status = dsERR_NONE;
    int32_t eIndicator;
    int32_t indicatorType = 0;
    uint32_t uBlinkDuration;
    uint32_t uBlinkIterations;
    int32_t dsFPDNumberOfIndicators = UT_KVP_PROFILE_GET_UINT32("dsFPD/Number_of_Indicators");
    char buffer[DS_FPD_KEY_SIZE];

    UT_LOG_INFO(" \t  Supported Indicators are:");
    UT_LOG_INFO("------------------------------------------");
    for (int indicator = 1; indicator <= dsFPDNumberOfIndicators; indicator++) {
        snprintf(buffer, DS_FPD_KEY_SIZE, "dsFPD/SupportedFPDIndicators/%d/Indicator_Type", indicator);
        indicatorType = UT_KVP_PROFILE_GET_UINT32(buffer);
        UT_LOG_INFO("\t%d.  %-20s\n", indicatorType, mapKeyToString(dsFrontPanelIndicatorTable, indicatorType));
    }
    UT_LOG_INFO("----------------------------------------------------------");
    UT_LOG_INFO("Select Indicator : ");
    scanf("%d", &eIndicator);

    UT_LOG_INFO("----------------------------------------------------------");
    UT_LOG_INFO("Enter Blink Duration in ms: ");
    scanf("%d", &uBlinkDuration);

    UT_LOG_INFO("----------------------------------------------------------");
    UT_LOG_INFO("Enter Blink iteration: ");
    scanf("%d", &uBlinkIterations);

    /* Check that the Indicator is valid */
    UT_LOG_INFO("Calling dsSetFPBlink(IN:Indicator:[0x%d], IN:Blink Duration in ms:[%d], IN:Blink Iteration:[%d]" \
                                        ,eIndicator,uBlinkDuration,uBlinkIterations);
    status = dsSetFPBlink((dsFPDIndicator_t)eIndicator,uBlinkDuration,uBlinkIterations);

    if (status != dsERR_NONE)
    {
        UT_LOG_ERROR("Failed  dsSetFPBlink(IN:Indicator:[0x%d], IN:Blink Duration in ms:[%d], IN:Blink Iteration:[%d]" \
                                        ,eIndicator,uBlinkDuration,uBlinkIterations);
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}
/**
* @brief This test provides a scope to add the sink logical address. Usually it shall be zero.
*
* This test case provides a scope to add the available sink logical address
* to a Device under test.
*
* Note:
* This applies only for the Sink Devices.
* Source devices will get the logical address during CEC open.
*
* **Test Group ID:** 02@n
*
* **Test Case ID:** 002@n
*
* **Pre-Conditions:** @n
* HDMI-CEC Module should be intialized through Test 1 before calling this test.
*
* **Dependencies:** None@n
*
* **User Interaction:** @n
* User or Automation tool should select the Test 2 and provide the logical address.
*
*/
void test_l3_dsFPD_hal_SetFPBrightness(void)
{
    gTestID = 2;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t status = dsERR_NONE;
    int32_t eIndicator;
    int32_t indicatorType = 0;
    uint32_t uBrightness;
    int32_t dsFPDNumberOfIndicators = UT_KVP_PROFILE_GET_UINT32("dsFPD/Number_of_Indicators");
    char buffer[DS_FPD_KEY_SIZE];

    UT_LOG_INFO(" \t  Supported Indicators are:");
    UT_LOG_INFO("------------------------------------------");
    for (int indicator = 1; indicator <= dsFPDNumberOfIndicators; indicator++) {
        snprintf(buffer, DS_FPD_KEY_SIZE, "dsFPD/SupportedFPDIndicators/%d/Indicator_Type", indicator);
        indicatorType = UT_KVP_PROFILE_GET_UINT32(buffer);
        UT_LOG_INFO("\t%d.  %-20s\n", indicatorType, mapKeyToString(dsFrontPanelIndicatorTable, indicatorType));
    }
    UT_LOG_INFO("----------------------------------------------------------");
    UT_LOG_INFO("Select Indicator : ");
    scanf("%d", &eIndicator);

    UT_LOG_INFO("----------------------------------------------------------");
    UT_LOG_INFO("Enter LED Brightness (Range: 0-100): ");
    scanf("%d", &uBrightness);

    /* Check that the Indicator is valid */
    UT_LOG_INFO("Calling dsSetFPBrightness(IN:Indicator:[0x%d], IN:Brightness:[%d]" \
                                                ,eIndicator,uBrightness);
    status = dsSetFPBrightness((dsFPDIndicator_t)eIndicator,uBrightness);

    if (status != dsERR_NONE)
    {
        UT_LOG_INFO("Calling dsSetFPBrightness(IN:Indicator:[0x%d], IN:Brightness:[%d]" \
                                                               ,eIndicator,uBrightness);
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}
/**
* @brief This test provides a scope to add the sink logical address. Usually it shall be zero.
*
* This test case provides a scope to add the available sink logical address
* to a Device under test.
*
* Note:
* This applies only for the Sink Devices.
* Source devices will get the logical address during CEC open.
*
* **Test Group ID:** 02@n
*
* **Test Case ID:** 002@n
*
* **Pre-Conditions:** @n
* HDMI-CEC Module should be intialized through Test 1 before calling this test.
*
* **Dependencies:** None@n
*
* **User Interaction:** @n
* User or Automation tool should select the Test 2 and provide the logical address.
*
*/
void test_l3_dsFPD_hal_SetFPState(void)
{
    gTestID = 2;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t status = dsERR_NONE;
    int32_t eIndicator;
    int32_t indicatorType = 0;
    uint32_t uState = 0;
    int32_t dsFPDNumberOfIndicators = UT_KVP_PROFILE_GET_UINT32("dsFPD/Number_of_Indicators");
    char buffer[DS_FPD_KEY_SIZE];

    UT_LOG_INFO(" \t  Supported Indicators are:");
    UT_LOG_INFO("------------------------------------------");
    for (int indicator = 1; indicator <= dsFPDNumberOfIndicators; indicator++) {
        snprintf(buffer, DS_FPD_KEY_SIZE, "dsFPD/SupportedFPDIndicators/%d/Indicator_Type", indicator);
        indicatorType = UT_KVP_PROFILE_GET_UINT32(buffer);
        UT_LOG_INFO("\t%d.  %-20s\n", indicatorType, mapKeyToString(dsFrontPanelIndicatorTable, indicatorType));
    }
    UT_LOG_INFO("----------------------------------------------------------");
    UT_LOG_INFO("Select Indicator : ");
    scanf("%d", &eIndicator);

    UT_LOG_INFO(" \t  Supported Front Panel States are:");
    UT_LOG_INFO("------------------------------------------");
    for (int state = 0; state < ((sizeof(dsFrontPanelStateTable)/sizeof(dsFrontPanelStateTable[0]))-1); state++) {
        UT_LOG_INFO("\t%d.  %-20s\n", state, mapKeyToString(dsFrontPanelStateTable, state));
    }
    UT_LOG_INFO("----------------------------------------------------------");
    UT_LOG_INFO("Select State : ");
    scanf("%d", &eIndicator);

    /* Check that the Indicator is valid */
    UT_LOG_INFO("Calling dsSetFPState(IN:Indicator:[0x%d], IN:State:[%d]" \
                                                ,eIndicator,uState);
    status = dsSetFPState((dsFPDIndicator_t)eIndicator,(dsFPDState_t)uState);

    if (status != dsERR_NONE)
    {
        UT_LOG_INFO("Calling dsSetFPBrightness(IN:Indicator:[0x%d], IN:Brightness:[%d]" \
                                                               ,eIndicator,uState);
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}
/**
* @brief This test provides a scope to add the sink logical address. Usually it shall be zero.
*
* This test case provides a scope to add the available sink logical address
* to a Device under test.
*
* Note:
* This applies only for the Sink Devices.
* Source devices will get the logical address during CEC open.
*
* **Test Group ID:** 02@n
*
* **Test Case ID:** 002@n
*
* **Pre-Conditions:** @n
* HDMI-CEC Module should be intialized through Test 1 before calling this test.
*
* **Dependencies:** None@n
*
* **User Interaction:** @n
* User or Automation tool should select the Test 2 and provide the logical address.
*
*/
void test_l3_dsFPD_hal_SetFPColor(void)
{
    gTestID = 2;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t status = dsERR_NONE;
    int32_t eIndicator;
    int32_t indicatorType = 0;
    uint32_t uColor;
    uint32_t uSupportedColor= 0;
    uint32_t numOfSupportedColors;
    int32_t dsFPDNumberOfIndicators = UT_KVP_PROFILE_GET_UINT32("dsFPD/Number_of_Indicators");
    char buffer[DS_FPD_KEY_SIZE];

    UT_LOG_INFO(" \t  Supported Indicators are:");
    UT_LOG_INFO("------------------------------------------");
    for (int indicator = 1; indicator <= dsFPDNumberOfIndicators; indicator++) {
        snprintf(buffer, DS_FPD_KEY_SIZE, "dsFPD/SupportedFPDIndicators/%d/Indicator_Type", indicator);
        indicatorType = UT_KVP_PROFILE_GET_UINT32(buffer);
        UT_LOG_INFO("\t%d.  %-20s\n", indicatorType, mapKeyToString(dsFrontPanelIndicatorTable, indicatorType));
    }
    UT_LOG_INFO("----------------------------------------------------------");
    UT_LOG_INFO("Select Indicator : ");
    scanf("%d", &eIndicator);

    UT_LOG_INFO(" \t  Supported Front Panel color for the state %s are:",mapKeyToString(dsFrontPanelIndicatorTable, eIndicator));
    UT_LOG_INFO("------------------------------------------");

    for (int indicator = 1; indicator <= dsFPDNumberOfIndicators; indicator++) {
        snprintf(buffer, DS_FPD_KEY_SIZE, "dsFPD/SupportedFPDIndicators/%d/Indicator_Type", indicator);
        indicatorType = UT_KVP_PROFILE_GET_UINT32(buffer);
        if(indicatorType == eIndicator)
        {
            snprintf(buffer, DS_FPD_KEY_SIZE, "dsFPD/SupportedFPDIndicators/%d/supportedColors", eIndicator);
            numOfSupportedColors = UT_KVP_PROFILE_GET_LIST_COUNT(buffer);
            for (int j = 0; j < numOfSupportedColors; j++)
            {
                snprintf(buffer, DS_FPD_KEY_SIZE, "dsFPD/SupportedFPDIndicators/%d/supportedColors/%d", eIndicator,j);
                uSupportedColor = UT_KVP_PROFILE_GET_UINT32(buffer);
                UT_LOG_INFO("\t0X%06X.  %-20s\n", uSupportedColor, mapKeyToString(dsFrontPanelColorTable, uSupportedColor));
            }
        }
    }
    UT_LOG_INFO("----------------------------------------------------------");
    UT_LOG_INFO("Select Color: ");
    scanf("%X", &uColor);

    /* Check that the Indicator is valid */
    UT_LOG_INFO("Calling SetFPColor(IN:Indicator:[0x%d], IN:Color:[%X]" \
                                                ,eIndicator,uColor);
    status = dsSetFPColor((dsFPDIndicator_t)eIndicator,uColor);

    if (status != dsERR_NONE)
    {
        UT_LOG_INFO("Calling dsSetFPColor(IN:Indicator:[0x%d], IN:Color:[%d]" \
                                                               ,eIndicator,uColor);
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}
/**
* @brief Termination of the Device settings - Front Panel Module
*
* This test provides a scope to open the Front Panel module and preserve the handle.

*
* **Test Group ID:** 03@n
*
* **Test Case ID:** 002@n
*
* **Pre-Conditions:** None@n
*
* **Dependencies:** None@n
*
* **User Interaction:** @n
* User or Automation tool should select the Test 1 to before running any test.
*
*/

void test_l3_dsFPD_hal_Term(void)
{
   gTestID = 1;
   dsError_t status = dsERR_NONE;

   UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

   // Step 1: Call dsFPInit()
   UT_LOG_INFO("Calling dsFPInit()");
   status = dsFPInit();
   if (status != dsERR_NONE)
   {
       UT_LOG_ERROR("Failed to Invoke ()");
   }

   UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main tests for this module
 *
 * @return int - 0 on success, otherwise failure
 */
int test_register_dsFPD_hal_l3_tests(void)
{
    // Create the test suite
    pSuite = UT_add_suite("[L3 Front Panel Functions] ", NULL, NULL);
    if (pSuite == NULL)
    {
        return -1;
    }
    // List of test function names and strings

    UT_add_test( pSuite, "L3_Init_dsFPD", test_l3_dsFPD_hal_Init);
    UT_add_test( pSuite, "L3_SetState_dsFPD", test_l3_dsFPD_hal_SetFPState);
    UT_add_test( pSuite, "L3_SetBrightness_dsFPD", test_l3_dsFPD_hal_SetFPBrightness);
    UT_add_test( pSuite, "L3_SetColor_dsFPD", test_l3_dsFPD_hal_SetFPColor);
    UT_add_test( pSuite, "L3_SetBlink_dsFPD", test_l3_dsFPD_hal_SetFPBlink);
    UT_add_test( pSuite, "L3_Term_dsFPD", test_l3_dsFPD_hal_Term);

    return 0;
}

/** @} */ // End of DS_FPD_HALTEST_L3
/** @} */ // End of DS_FPD_HALTEST
/** @} */ // End of Device_Settings_HALTEST
/** @} */ // End of Device_Settings
/** @} */ // End of HPK
