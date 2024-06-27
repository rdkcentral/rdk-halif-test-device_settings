/*
* If not stated otherwise in this file or this component's LICENSE file the
* following copyright and licenses apply:*
* Copyright 2024 RDK Management
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/**
* @file test_l2_dsFPD.c
* @page dsFPD Level 2 Tests
*
* ## Module's Role
* This module includes Level 2 functional tests (success and failure scenarios).
* This is to ensure that the dsFPD APIs meet the requirements across all vendors.
*
* **Pre-Conditions:**  None@n
* **Dependencies:** None@n
*
* Ref to API Definition specification documentation : [dsFPD_halSpec.md](../../docs/pages/dsFPD_halSpec.md)
*/

#include <ut.h>
#include <ut_log.h>
#include <ut_kvp_profile.h>
#include "dsFPD.h"
#include <stdlib.h>

static int gTestGroup = 2;
static int gTestID = 1;

/**
* @brief This test function is designed to test the functionality of the Front Panel Display (FPD) indicators.
*
* This test function iterates over the supported FPD indicators, gets their current state, sets their state to ON if it's OFF, sets the brightness of the LED, verifies the brightness, and finally terminates the FPD sub-module. The purpose of this test is to ensure that the FPD indicators are functioning as expected and that the associated functions are working correctly.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 001@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsFPD_L2_Low-Level_TestSpecification.md](../../docs/pages/dsFPD_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsFPD_SetFPstateON_SetBrightness_sink(void)
{
    gTestID = 1;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    dsFPDState_t state;
    dsFPDBrightness_t brightness;
    dsFPDBrightness_t getbrightness;
    dsFPDBrightness_t minBrightness;
    dsFPDBrightness_t maxBrightness;
    dsFPDIndicator_t eIndicator;
    int count = 0;
    char buffer[50];
    char minbuffer[50], maxbuffer[50];
    ut_kvp_instance_t *pInstance = NULL;

    // Initialize the Front Panel Display (FPD) sub-module
    UT_LOG_DEBUG("Invoking dsFPInit()");
    ret = dsFPInit();
    UT_LOG_DEBUG("dsFPInit returned : %d",ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    pInstance = ut_kvp_profile_getInstance();
    count = ut_kvp_getListCount(pInstance,"dsFPD/SupportedFPDIndicators");
    for (int i=0;i<count;i++)
    {
        sprintf(buffer, "dsFPD/SupportedFPDIndicators/%d", i);
        eIndicator = ut_kvp_getUInt32Field( pInstance, buffer);

        // Get the current state of the FP
        UT_LOG_DEBUG("Invoking dsGetFPState() with eIndicator=%d", eIndicator);
        ret = dsGetFPState(eIndicator, &state);
        UT_LOG_DEBUG("dsGetFPState() returned state=%d and status=%d", state, ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetFPState failed with status: %d", ret);
            continue;
        }

        // If the current state of the FP is OFF, set it to ON
        if (state == dsFPD_STATE_OFF)
        {
            UT_LOG_DEBUG("Invoking dsSetFPState() with eIndicator=%d and state=dsFPD_STATE_ON", eIndicator);
            ret = dsSetFPState(eIndicator, dsFPD_STATE_ON);
            UT_LOG_DEBUG("dsSetFPState() returned status=%d", ret);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetFPState failed with status: %d", ret);
                continue;
            }
        }

        // Set the brightness of the LED
        sprintf(minbuffer, "dsFPD/%d/MIN_BRIGHTNESS",eIndicator);
        minBrightness = ut_kvp_getUInt32Field( pInstance, minbuffer);
        sprintf(maxbuffer, "dsFPD/%d/MAX_BRIGHTNESS",eIndicator);
        maxBrightness = ut_kvp_getUInt32Field( pInstance, maxbuffer);
        brightness = minBrightness + rand() % (maxBrightness+1 - minBrightness);
        UT_LOG_DEBUG("Invoking dsSetFPBrightness() with eIndicator=%d and eBrightness=%d", eIndicator, brightness);
        ret = dsSetFPBrightness(eIndicator, brightness);
        UT_LOG_DEBUG("dsSetFPBrightness() returned status=%d", ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsSetFPBrightness failed with status: %d", ret);
            continue;
        }

        // Verify the brightness of the LED
        UT_LOG_DEBUG("Invoking dsGetFPBrightness() with eIndicator=%d", eIndicator);
        ret = dsGetFPBrightness(eIndicator, &getbrightness);
        UT_LOG_DEBUG("dsGetFPBrightness() returned brightness=%d and status=%d", getbrightness, ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_ASSERT_EQUAL(brightness, getbrightness);
        if (ret != dsERR_NONE || brightness != getbrightness)
        {
            UT_LOG_ERROR("Mismatch in set and get brightness");
        }
    }

    // Terminate the Front Panel Display (FPD) sub-module
    UT_LOG_DEBUG("Invoking dsFPTerm()");
    ret = dsFPTerm();
    UT_LOG_DEBUG("TvTerm returned : %d",ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test function is designed to test the functionality of the Front Panel Display (FPD) sub-module in the L2 layer.
*
* This test function iterates over the supported FPD indicators, checks their current state, and if OFF, sets them to ON. It also sets the brightness of the discrete LED within the specified range and verifies the set brightness. The function finally terminates the FPD sub-module. The test is designed to ensure that the FPD sub-module functions as expected and can handle the operations correctly.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 002@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsFPD_L2_Low-Level_TestSpecification.md](../../docs/pages/dsFPD_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsFPD_SetFPstateON_SetBrightness_source(void)
{
    gTestID = 2;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

     dsError_t ret;
    dsFPDState_t state;
    dsFPDBrightness_t brightness;
    dsFPDBrightness_t getbrightness;
    dsFPDBrightness_t minBrightness;
    dsFPDBrightness_t maxBrightness;
    dsFPDIndicator_t eIndicator;
    int count = 0;
    char buffer[50];
    char minbuffer[50], maxbuffer[50];
    ut_kvp_instance_t *pInstance = NULL;

    // Initialize the Front Panel Display (FPD) sub-module
    UT_LOG_DEBUG("Invoking dsFPInit()");
    ret = dsFPInit();
    UT_LOG_DEBUG("dsFPInit returned : %d",ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    pInstance = ut_kvp_profile_getInstance();
    count = ut_kvp_getListCount(pInstance,"dsFPD/SupportedFPDIndicators");
    for (int i=0;i<count;i++)
    {
        sprintf(buffer, "dsFPD/SupportedFPDIndicators/%d", i);
        eIndicator = ut_kvp_getUInt32Field( pInstance, buffer);

        // Get the current state of the FP
        UT_LOG_DEBUG("Invoking dsGetFPState() with eIndicator=%d", eIndicator);
        ret = dsGetFPState(eIndicator, &state);
        UT_LOG_DEBUG("dsGetFPState() returned state=%d and status=%d", state, ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetFPState failed with status: %d", ret);
            continue;
        }

        // If the current state of the FP is OFF, set it to ON
        if (state == dsFPD_STATE_OFF)
        {
            UT_LOG_DEBUG("Invoking dsSetFPState() with eIndicator=%d and state=dsFPD_STATE_ON", eIndicator);
            ret = dsSetFPState(eIndicator, dsFPD_STATE_ON);
            UT_LOG_DEBUG("dsSetFPState() returned status=%d", ret);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetFPState failed with status: %d", ret);
                continue;
            }
        }

        // Set the brightness of the LED
        sprintf(minbuffer, "dsFPD/%d/MIN_BRIGHTNESS",eIndicator);
        minBrightness = ut_kvp_getUInt32Field( pInstance, minbuffer);
        sprintf(maxbuffer, "dsFPD/%d/MAX_BRIGHTNESS",eIndicator);
        maxBrightness = ut_kvp_getUInt32Field( pInstance, maxbuffer);
        brightness = minBrightness + rand() % (maxBrightness+1 - minBrightness);
        UT_LOG_DEBUG("Invoking dsSetFPBrightness() with eIndicator=%d and eBrightness=%d", eIndicator, brightness);
        ret = dsSetFPBrightness(eIndicator, brightness);
        UT_LOG_DEBUG("dsSetFPBrightness() returned status=%d", ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsSetFPBrightness failed with status: %d", ret);
            continue;
        }

        // Verify the brightness of the LED
        UT_LOG_DEBUG("Invoking dsGetFPBrightness() with eIndicator=%d", eIndicator);
        ret = dsGetFPBrightness(eIndicator, &getbrightness);
        UT_LOG_DEBUG("dsGetFPBrightness() returned brightness=%d and status=%d", getbrightness, ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_ASSERT_EQUAL(brightness, getbrightness);
        if (ret != dsERR_NONE || brightness != getbrightness)
        {
            UT_LOG_ERROR("Mismatch in set and get brightness");
        }
    }

    // Terminate the Front Panel Display (FPD) sub-module
    UT_LOG_DEBUG("Invoking dsFPTerm()");
    ret = dsFPTerm();
    UT_LOG_DEBUG("TvTerm returned : %d",ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to verify the functionality of dsFPD_IterateAndSetFPDIndicators
*
* This test case verifies the functionality of dsFPD_IterateAndSetFPDIndicators API. It checks if the API is able to iterate over the supported FPD indicators and set the state and brightness of each indicator correctly.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 003@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsFPD_L2_Low-Level_TestSpecification.md](../../docs/pages/dsFPD_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsFPD_SetFPstateOFF_SetBrightness_sink(void)
{
    gTestID = 3;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    dsFPDState_t state;
    dsFPDBrightness_t eBrightness;
    dsFPDIndicator_t eIndicator;
    int count = 0;
    char buffer[50];
    ut_kvp_instance_t *pInstance = NULL;

    // Initialize the Front Panel Display (FPD) sub-module
    UT_LOG_DEBUG("Invoking dsFPInit()");
    ret = dsFPInit();
    UT_LOG_DEBUG("dsFPInit returned : %d",ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    pInstance = ut_kvp_profile_getInstance();
    count = ut_kvp_getListCount(pInstance,"dsFPD/SupportedFPDIndicators");
    for (int i=0;i<count;i++)
    {
        sprintf(buffer, "dsFPD/SupportedFPDIndicators/%d", i);
        eIndicator = ut_kvp_getUInt32Field( pInstance, buffer);

        // Get the current state of the FP
        UT_LOG_DEBUG("Invoking dsGetFPState() with eIndicator=%d", eIndicator);
        ret = dsGetFPState(eIndicator, &state);
        UT_LOG_DEBUG("dsGetFPState() returned state=%d and status=%d", state, ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetFPState failed with status: %d", ret);
            continue;
        }

        // If the current state of the FP is ON, set it to OFF
        if (state == dsFPD_STATE_ON)
        {
            UT_LOG_DEBUG("Invoking dsSetFPState() with eIndicator=%d and state=dsFPD_STATE_OFF", eIndicator);
            ret = dsSetFPState(eIndicator, dsFPD_STATE_OFF);
            UT_LOG_DEBUG("dsSetFPState() returned status=%d", ret);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetFPState failed with status: %d", ret);
                continue;
            }
        }

        // Set the brightness of the discrete LED (0-100)
        eBrightness = rand() % 101;
        UT_LOG_DEBUG("Invoking dsSetFPBrightness() with eIndicator=%d and eBrightness=%d", eIndicator, eBrightness);
        ret = dsSetFPBrightness(eIndicator, eBrightness);
        UT_LOG_DEBUG("dsSetFPBrightness() returned status=%d", ret);
        UT_ASSERT_EQUAL(ret, dsERR_OPERATION_NOT_SUPPORTED);
        if (ret != dsERR_OPERATION_NOT_SUPPORTED)
        {
            UT_LOG_ERROR("dsSetFPBrightness failed with status: %d", ret);
        }
    }

    // Terminate the Front Panel Display sub-module
    UT_LOG_DEBUG("Invoking dsFPTerm()");
    ret = dsFPTerm();
    UT_LOG_DEBUG("dsFPTerm() returned status=%d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test function is designed to iterate and set FPD indicators in the L2 module.
*
* This function tests the initialization, state retrieval, state setting, brightness setting, and termination of FPD indicators in the L2 module. It is important to ensure that these operations are functioning correctly for the proper operation of the L2 module.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 004@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsFPD_L2_Low-Level_TestSpecification.md](../../docs/pages/dsFPD_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsFPD_SetFPstateOFF_SetBrightness_source(void)
{
    gTestID = 4;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    dsFPDState_t state;
    dsFPDBrightness_t eBrightness;
    dsFPDIndicator_t eIndicator;
    int count = 0;
    char buffer[50];
    ut_kvp_instance_t *pInstance = NULL;

    // Initialize the Front Panel Display (FPD) sub-module
    UT_LOG_DEBUG("Invoking dsFPInit()");
    ret = dsFPInit();
    UT_LOG_DEBUG("dsFPInit returned : %d",ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    pInstance = ut_kvp_profile_getInstance();
    count = ut_kvp_getListCount(pInstance,"dsFPD/SupportedFPDIndicators");
    for (int i=0;i<count;i++)
    {
        sprintf(buffer, "dsFPD/SupportedFPDIndicators/%d", i);
        eIndicator = ut_kvp_getUInt32Field( pInstance, buffer);

        // Get the current state of the FP
        UT_LOG_DEBUG("Invoking dsGetFPState() with eIndicator=%d", eIndicator);
        ret = dsGetFPState(eIndicator, &state);
        UT_LOG_DEBUG("dsGetFPState() returned state=%d and status=%d", state, ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetFPState failed with status: %d", ret);
            continue;
        }

        // If the current state of the FP is ON, set it to OFF
        if (state == dsFPD_STATE_ON)
        {
            UT_LOG_DEBUG("Invoking dsSetFPState() with eIndicator=%d and state=dsFPD_STATE_OFF", eIndicator);
            ret = dsSetFPState(eIndicator, dsFPD_STATE_OFF);
            UT_LOG_DEBUG("dsSetFPState() returned status=%d", ret);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetFPState failed with status: %d", ret);
                continue;
            }
        }

        // Set the brightness of the discrete LED (0-100)
        eBrightness = rand() % 101;
        UT_LOG_DEBUG("Invoking dsSetFPBrightness() with eIndicator=%d and eBrightness=%d", eIndicator, eBrightness);
        ret = dsSetFPBrightness(eIndicator, eBrightness);
        UT_LOG_DEBUG("dsSetFPBrightness() returned status=%d", ret);
        UT_ASSERT_EQUAL(ret, dsERR_OPERATION_NOT_SUPPORTED);
        if (ret != dsERR_OPERATION_NOT_SUPPORTED)
        {
            UT_LOG_ERROR("dsSetFPBrightness failed with status: %d", ret);
        }
    }

    // Terminate the Front Panel Display sub-module
    UT_LOG_DEBUG("Invoking dsFPTerm()");
    ret = dsFPTerm();
    UT_LOG_DEBUG("dsFPTerm() returned status=%d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test function is designed to test the functionality of the dsFPD_IterateAndSetFPDIndicators API
*
* This test function invokes the dsFPD_IterateAndSetFPDIndicators API and checks if the API is able to iterate and set the FPD indicators correctly. The test function also checks if the API returns the correct error codes when expected.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 005@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsFPD_L2_Low-Level_TestSpecification.md](../../docs/pages/dsFPD_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsFPD_SetFPstateOFF_SetBlink_sink(void)
{
    gTestID = 5;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    dsFPDState_t state;
    dsFPDIndicator_t eIndicator;
    int count = 0;
    char buffer[50];
    ut_kvp_instance_t *pInstance = NULL;

    // Initialize the Front Panel Display (FPD) sub-module
    UT_LOG_DEBUG("Invoking dsFPInit()");
    ret = dsFPInit();
    UT_LOG_DEBUG("dsFPInit returned : %d",ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    pInstance = ut_kvp_profile_getInstance();
    count = ut_kvp_getListCount(pInstance,"dsFPD/SupportedFPDIndicators");
    for (int i=0;i<count;i++)
    {
        sprintf(buffer, "dsFPD/SupportedFPDIndicators/%d", i);
        eIndicator = ut_kvp_getUInt32Field( pInstance, buffer);

        // Get the current state of the FP
        UT_LOG_DEBUG("Invoking dsGetFPState() with eIndicator=%d", eIndicator);
        ret = dsGetFPState(eIndicator, &state);
        UT_LOG_DEBUG("dsGetFPState() returned state=%d and status=%d", state, ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetFPState failed with status: %d", ret);
            continue;
        }

        // If the current state of the FP is ON, set it to OFF
        if (state == dsFPD_STATE_ON)
        {
            UT_LOG_DEBUG("Invoking dsSetFPState() with eIndicator=%d and state=dsFPD_STATE_OFF", eIndicator);
            ret = dsSetFPState(eIndicator, dsFPD_STATE_OFF);
            UT_LOG_DEBUG("dsSetFPState() returned status=%d", ret);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetFPState failed with status: %d", ret);
                continue;
            }
        }

        UT_LOG_DEBUG("Invoking dsSetFPBlink() with eIndicator=%d, uBlinkDuration= 500, uBlinkIterations= 10", eIndicator);
        ret = dsSetFPBlink(eIndicator, 500, 10);
        UT_LOG_DEBUG("dsSetFPBlink() returned status=%d", ret);
        UT_ASSERT_EQUAL(ret, dsERR_OPERATION_NOT_SUPPORTED);
        if (ret != dsERR_OPERATION_NOT_SUPPORTED)
        {
            UT_LOG_ERROR("dsSetFPBlink() failed with status=%d", ret);

        }
    }
    UT_LOG_DEBUG("Invoking dsFPTerm()");
    ret = dsFPTerm();
    UT_LOG_DEBUG("dsFPTerm() returned status=%d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to verify the functionality of dsFPD APIs
*
* This test function initializes the Front Panel Display (FPD) sub-module, iterates over the supported FPD indicators, checks the current state of each indicator, sets the state to OFF if it is ON, sets the blink functionality of the discrete LED, and finally terminates the FPD sub-module. The function uses Cunit assertions to verify the return values of the API calls.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 006@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsFPD_L2_Low-Level_TestSpecification.md](../../docs/pages/dsFPD_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsFPD_SetFPstateOFF_SetBlink_source(void)
{
    gTestID = 6;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    dsFPDState_t state;
    dsFPDIndicator_t eIndicator;
    int count = 0;
    char buffer[50];
    ut_kvp_instance_t *pInstance = NULL;

    // Initialize the Front Panel Display (FPD) sub-module
    UT_LOG_DEBUG("Invoking dsFPInit()");
    ret = dsFPInit();
    UT_LOG_DEBUG("dsFPInit returned : %d",ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    pInstance = ut_kvp_profile_getInstance();
    count = ut_kvp_getListCount(pInstance,"dsFPD/SupportedFPDIndicators");
    for (int i=0;i<count;i++)
    {
        sprintf(buffer, "dsFPD/SupportedFPDIndicators/%d", i);
        eIndicator = ut_kvp_getUInt32Field( pInstance, buffer);

        // Get the current state of the FP
        UT_LOG_DEBUG("Invoking dsGetFPState() with eIndicator=%d", eIndicator);
        ret = dsGetFPState(eIndicator, &state);
        UT_LOG_DEBUG("dsGetFPState() returned state=%d and status=%d", state, ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetFPState failed with status: %d", ret);
            continue;
        }

        // If the current state of the FP is ON, set it to OFF
        if (state == dsFPD_STATE_ON)
        {
            UT_LOG_DEBUG("Invoking dsSetFPState() with eIndicator=%d and state=dsFPD_STATE_OFF", eIndicator);
            ret = dsSetFPState(eIndicator, dsFPD_STATE_OFF);
            UT_LOG_DEBUG("dsSetFPState() returned status=%d", ret);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetFPState failed with status: %d", ret);
                continue;
            }
        }

        UT_LOG_DEBUG("Invoking dsSetFPBlink() with eIndicator=%d, uBlinkDuration= 500, uBlinkIterations= 10", eIndicator);
        ret = dsSetFPBlink(eIndicator, 500, 10);
        UT_LOG_DEBUG("dsSetFPBlink() returned status=%d", ret);
        UT_ASSERT_EQUAL(ret, dsERR_OPERATION_NOT_SUPPORTED);
        if (ret != dsERR_OPERATION_NOT_SUPPORTED)
        {
            UT_LOG_ERROR("dsSetFPBlink() failed with status=%d", ret);

        }
    }
    UT_LOG_DEBUG("Invoking dsFPTerm()");
    ret = dsFPTerm();
    UT_LOG_DEBUG("dsFPTerm() returned status=%d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test function is designed to iterate and set FPD indicators
*
* This test function iterates over all FPD indicators and sets their state and color. It tests the functionality of dsFPInit, dsGetFPState, dsSetFPState, dsSetFPColor, dsGetFPColor, and dsFPTerm functions. The test ensures that these functions return the expected results and the FPD indicators are set correctly.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 007@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsFPD_L2_Low-Level_TestSpecification.md](../../docs/pages/dsFPD_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsFPD_SetFPstateON_Multi_SetColor_sink(void)
{
    gTestID = 7;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    dsFPDState_t state;
    dsFPDColor_t color;
    dsFPDColor_t getcolor;
    dsFPDIndicator_t eIndicator;
    int count = 0;
    int mode = 0;
    int numOfSuppportedColors = 0;
    char buffer[50];
    char colorbuffer[50];
    char supportedColorbuffer[50];
    ut_kvp_instance_t *pInstance = NULL;

    // Initialize the Front Panel Display (FPD) sub-module
    UT_LOG_DEBUG("Invoking dsFPInit()");
    ret = dsFPInit();
    UT_LOG_DEBUG("dsFPInit returned : %d",ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    pInstance = ut_kvp_profile_getInstance();
    count = ut_kvp_getListCount(pInstance,"dsFPD/SupportedFPDIndicators");
    for (int i=0;i<count;i++)
    {
        sprintf(buffer, "dsFPD/SupportedFPDIndicators/%d", i);
        eIndicator = ut_kvp_getUInt32Field( pInstance, buffer);

        // Get the current state of the FP
        UT_LOG_DEBUG("Invoking dsGetFPState() with eIndicator=%d", eIndicator);
        ret = dsGetFPState(eIndicator, &state);
        UT_LOG_DEBUG("dsGetFPState() returned state=%d and status=%d", state, ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetFPState failed with status: %d", ret);
            continue;
        }

        // If the current state of the FP is OFF, set it to ON
        if (state == dsFPD_STATE_OFF)
        {
            UT_LOG_DEBUG("Invoking dsSetFPState() with eIndicator=%d and state=dsFPD_STATE_ON", eIndicator);
            ret = dsSetFPState(eIndicator, dsFPD_STATE_ON);
            UT_LOG_DEBUG("dsSetFPState() returned status=%d", ret);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetFPState failed with status: %d", ret);
                continue;
            }
        }
        //Check the indicator supports multi-colored
        sprintf(colorbuffer, "dsFPD/%d/DEFAULT_COLOR_MODE",eIndicator);
        mode = ut_kvp_getUInt32Field(pInstance,colorbuffer);
        UT_LOG_DEBUG("Default color mode from profile file : %d", mode);

        //set and get different colors supported by the discrete `LED`
        if (mode == 1)
        {
            UT_LOG_DEBUG("The indicator supports multicolored");
            sprintf(supportedColorbuffer, "dsFPD/%d/supportedColors",eIndicator);
            numOfSuppportedColors = ut_kvp_getListCount(pInstance,supportedColorbuffer);
            for (int j=0;j<numOfSuppportedColors;j++)
            {
                sprintf(buffer,"dsFPD/%d/supportedColors/%d", eIndicator, j);
                color = ut_kvp_getUInt32Field( pInstance, buffer);
                UT_LOG_DEBUG("Invoking dsSetFPColor with eIndicator: %d and color: %d", eIndicator, color);
                ret = dsSetFPColor(eIndicator, color);
                UT_LOG_DEBUG("Return status: %d", ret);
                UT_ASSERT_EQUAL(ret, dsERR_NONE);
                if (ret != dsERR_NONE)
                {
                    UT_LOG_ERROR("dsSetFPColor failed with status: %d", ret);
                    continue;
                }

                ret = dsGetFPColor(eIndicator, &getcolor);
                UT_LOG_DEBUG("Invoking dsGetFPColor with eIndicator: %d", eIndicator);
                UT_LOG_DEBUG("Color: %d and return status: %d", getcolor, ret);
                UT_ASSERT_EQUAL(ret, dsERR_NONE);
                UT_ASSERT_EQUAL(color, getcolor);
                if (ret != dsERR_NONE || color != getcolor)
                {
                    UT_LOG_ERROR("Mismatch in set and get color");
                }
            }
        }
        else
        {
            UT_LOG_DEBUG("The indicator supports only single color");
        }
    }

    ret = dsFPTerm();
    UT_LOG_DEBUG("Invoking dsFPTerm");
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test function is designed to test the iteration and setting of FPD indicators in the L2 module.
*
* This function tests the initialization, state retrieval, state setting, color setting, and color retrieval of FPD indicators. It also tests the termination of the FPD. The test is designed to ensure that the FPD indicators are functioning correctly and that the L2 module is able to handle these operations without errors.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 008@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsFPD_L2_Low-Level_TestSpecification.md](../../docs/pages/dsFPD_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsFPD_SetFPstateON_Multi_SetColor_source(void)
{
    gTestID = 8;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    dsFPDState_t state;
    dsFPDColor_t color;
    dsFPDColor_t getcolor;
    dsFPDIndicator_t eIndicator;
    int count = 0;
    int mode = 0;
    int numOfSuppportedColors = 0;
    char buffer[50];
    char colorbuffer[50];
    char supportedColorbuffer[50];
    ut_kvp_instance_t *pInstance = NULL;

    // Initialize the Front Panel Display (FPD) sub-module
    UT_LOG_DEBUG("Invoking dsFPInit()");
    ret = dsFPInit();
    UT_LOG_DEBUG("dsFPInit returned : %d",ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    pInstance = ut_kvp_profile_getInstance();
    count = ut_kvp_getListCount(pInstance,"dsFPD/SupportedFPDIndicators");
    for (int i=0;i<count;i++)
    {
        sprintf(buffer, "dsFPD/SupportedFPDIndicators/%d", i);
        eIndicator = ut_kvp_getUInt32Field( pInstance, buffer);

        // Get the current state of the FP
        UT_LOG_DEBUG("Invoking dsGetFPState() with eIndicator=%d", eIndicator);
        ret = dsGetFPState(eIndicator, &state);
        UT_LOG_DEBUG("dsGetFPState() returned state=%d and status=%d", state, ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetFPState failed with status: %d", ret);
            continue;
        }

        // If the current state of the FP is OFF, set it to ON
        if (state == dsFPD_STATE_OFF)
        {
            UT_LOG_DEBUG("Invoking dsSetFPState() with eIndicator=%d and state=dsFPD_STATE_ON", eIndicator);
            ret = dsSetFPState(eIndicator, dsFPD_STATE_ON);
            UT_LOG_DEBUG("dsSetFPState() returned status=%d", ret);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetFPState failed with status: %d", ret);
                continue;
            }
        }
        //Check the indicator supports multi-colored
        sprintf(colorbuffer, "dsFPD/%d/DEFAULT_COLOR_MODE",eIndicator);
        mode = ut_kvp_getUInt32Field(pInstance,colorbuffer);
        UT_LOG_DEBUG("Default color mode from profile file : %d", mode);

        //set and get different colors supported by the discrete `LED`
        if (mode == 1)
        {
            UT_LOG_DEBUG("The indicator supports multicolored");
            sprintf(supportedColorbuffer, "dsFPD/%d/supportedColors",eIndicator);
            numOfSuppportedColors = ut_kvp_getListCount(pInstance,supportedColorbuffer);
            for (int j=0;j<numOfSuppportedColors;j++)
            {
                sprintf(buffer,"dsFPD/%d/supportedColors/%d", eIndicator, j);
                color = ut_kvp_getUInt32Field( pInstance, buffer);
                UT_LOG_DEBUG("Invoking dsSetFPColor with eIndicator: %d and color: %d", eIndicator, color);
                ret = dsSetFPColor(eIndicator, color);
                UT_LOG_DEBUG("Return status: %d", ret);
                UT_ASSERT_EQUAL(ret, dsERR_NONE);
                if (ret != dsERR_NONE)
                {
                    UT_LOG_ERROR("dsSetFPColor failed with status: %d", ret);
                    continue;
                }

                ret = dsGetFPColor(eIndicator, &getcolor);
                UT_LOG_DEBUG("Invoking dsGetFPColor with eIndicator: %d", eIndicator);
                UT_LOG_DEBUG("Color: %d and return status: %d", getcolor, ret);
                UT_ASSERT_EQUAL(ret, dsERR_NONE);
                UT_ASSERT_EQUAL(color, getcolor);
                if (ret != dsERR_NONE || color != getcolor)
                {
                    UT_LOG_ERROR("Mismatch in set and get color");
                }
            }
        }
        else
        {
            UT_LOG_DEBUG("The indicator supports only single color");
        }
    }

    ret = dsFPTerm();
    UT_LOG_DEBUG("Invoking dsFPTerm");
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to iterate over the supported Front Panel Display (FPD) indicators and check their current state
*
* This test function iterates over the supported Front Panel Display (FPD) indicators and checks their current state. If the state is ON, it sets it to OFF and then tries to set the color functionality of the discrete LED. It checks that the dsSetFPColor() API returns `dsERR_OPERATION_NOT_SUPPORTED`. Finally, it terminates the Front Panel Display sub-module.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 009@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsFPD_L2_Low-Level_TestSpecification.md](../../docs/pages/dsFPD_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsFPD_SetFPstateOFF_SetColor_sink(void)
{
    gTestID = 9;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    dsFPDState_t state;
    dsFPDColor_t eColor;
    dsFPDIndicator_t eIndicator;
    int count = 0;
    int numOfSuppportedColors = 0;
    char buffer[50];
    ut_kvp_instance_t *pInstance = NULL;
    char supportedColorbuffer[50];

    // Initialize the Front Panel Display (FPD) sub-module
    UT_LOG_DEBUG("Invoking dsFPInit()");
    ret = dsFPInit();
    UT_LOG_DEBUG("dsFPInit returned : %d",ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    pInstance = ut_kvp_profile_getInstance();
    count = ut_kvp_getListCount(pInstance,"dsFPD/SupportedFPDIndicators");
    for (int i=0;i<count;i++)
    {
        sprintf(buffer, "dsFPD/SupportedFPDIndicators/%d", i);
        eIndicator = ut_kvp_getUInt32Field( pInstance, buffer);

        // Get the current state of the FP
        UT_LOG_DEBUG("Invoking dsGetFPState() with eIndicator=%d", eIndicator);
        ret = dsGetFPState(eIndicator, &state);
        UT_LOG_DEBUG("dsGetFPState() returned state=%d and status=%d", state, ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetFPState failed with status: %d", ret);
            continue;
        }

        // If the current state of the FP is ON, set it to OFF
        if (state == dsFPD_STATE_ON)
        {
            UT_LOG_DEBUG("Invoking dsSetFPState() with eIndicator=%d and state=dsFPD_STATE_OFF", eIndicator);
            ret = dsSetFPState(eIndicator, dsFPD_STATE_OFF);
            UT_LOG_DEBUG("dsSetFPState() returned status=%d", ret);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetFPState failed with status: %d", ret);
                continue;
            }
        }

        sprintf(supportedColorbuffer, "dsFPD/%d/supportedColors",eIndicator);
        numOfSuppportedColors = ut_kvp_getListCount(pInstance,supportedColorbuffer);
        for (int j=0;j<numOfSuppportedColors;j++)
        {
            sprintf(buffer,"dsFPD/%d/supportedColors/%d", eIndicator, j);
            eColor = ut_kvp_getUInt32Field( pInstance, buffer);
            UT_LOG_DEBUG("Invoking dsSetFPColor with eIndicator: %d and color: %d", eIndicator, eColor);
            ret = dsSetFPColor(eIndicator, eColor);
            UT_LOG_DEBUG("Return status: %d", ret);
            UT_ASSERT_EQUAL(ret, dsERR_OPERATION_NOT_SUPPORTED);
            if (ret != dsERR_OPERATION_NOT_SUPPORTED)
            {
                UT_LOG_ERROR("dsSetFPColor failed with status: %d", ret);
                continue;
            }
        }
    }

    UT_LOG_DEBUG("Invoking dsFPTerm");
    ret = dsFPTerm();
    UT_LOG_DEBUG("dsFPTerm returned status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test function is designed to test the functionality of the dsFPD_IterateAndSetFPDIndicators_source API
*
* This test function invokes the dsFPD_IterateAndSetFPDIndicators_source API and checks if it correctly initializes, gets the state, sets the state and color, and terminates the Front Panel Display (FPD) indicators. The test asserts that the API returns the correct status codes and that the state and color of the FPD indicators are set as expected.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 010@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsFPD_L2_Low-Level_TestSpecification.md](../../docs/pages/dsFPD_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsFPD_SetFPstateOFF_SetColor_source(void)
{
    gTestID = 10;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    dsFPDState_t state;
    dsFPDColor_t eColor;
    dsFPDIndicator_t eIndicator;
    int count = 0;
    int numOfSuppportedColors = 0;
    char buffer[50];
    ut_kvp_instance_t *pInstance = NULL;
    char supportedColorbuffer[50];

    // Initialize the Front Panel Display (FPD) sub-module
    UT_LOG_DEBUG("Invoking dsFPInit()");
    ret = dsFPInit();
    UT_LOG_DEBUG("dsFPInit returned : %d",ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    pInstance = ut_kvp_profile_getInstance();
    count = ut_kvp_getListCount(pInstance,"dsFPD/SupportedFPDIndicators");
    for (int i=0;i<count;i++)
    {
        sprintf(buffer, "dsFPD/SupportedFPDIndicators/%d", i);
        eIndicator = ut_kvp_getUInt32Field( pInstance, buffer);

        // Get the current state of the FP
        UT_LOG_DEBUG("Invoking dsGetFPState() with eIndicator=%d", eIndicator);
        ret = dsGetFPState(eIndicator, &state);
        UT_LOG_DEBUG("dsGetFPState() returned state=%d and status=%d", state, ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetFPState failed with status: %d", ret);
            continue;
        }

        // If the current state of the FP is ON, set it to OFF
        if (state == dsFPD_STATE_ON)
        {
            UT_LOG_DEBUG("Invoking dsSetFPState() with eIndicator=%d and state=dsFPD_STATE_OFF", eIndicator);
            ret = dsSetFPState(eIndicator, dsFPD_STATE_OFF);
            UT_LOG_DEBUG("dsSetFPState() returned status=%d", ret);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetFPState failed with status: %d", ret);
                continue;
            }
        }

        sprintf(supportedColorbuffer, "dsFPD/%d/supportedColors",eIndicator);
        numOfSuppportedColors = ut_kvp_getListCount(pInstance,supportedColorbuffer);
        for (int j=0;j<numOfSuppportedColors;j++)
        {
            sprintf(buffer,"dsFPD/%d/supportedColors/%d", eIndicator, j);
            eColor = ut_kvp_getUInt32Field( pInstance, buffer);
            UT_LOG_DEBUG("Invoking dsSetFPColor with eIndicator: %d and color: %d", eIndicator, eColor);
            ret = dsSetFPColor(eIndicator, eColor);
            UT_LOG_DEBUG("Return status: %d", ret);
            UT_ASSERT_EQUAL(ret, dsERR_OPERATION_NOT_SUPPORTED);
            if (ret != dsERR_OPERATION_NOT_SUPPORTED)
            {
                UT_LOG_ERROR("dsSetFPColor failed with status: %d", ret);
                continue;
            }
        }
    }

    UT_LOG_DEBUG("Invoking dsFPTerm");
    ret = dsFPTerm();
    UT_LOG_DEBUG("dsFPTerm returned status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to iterate and check FPD indicators
*
* This test function iterates over all FPD indicators and checks their state and color. It tests the functionality of dsFPInit(), dsGetFPState(), dsSetFPState(), dsSetFPColor(), and dsFPTerm() functions. The test is designed to ensure that these functions are working as expected and handling the FPD indicators correctly.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 011@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsFPD_L2_Low-Level_TestSpecification.md](../../docs/pages/dsFPD_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsFPD_SetFPstateON_Single_SetColor_sink(void)
{
    gTestID = 11;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    dsFPDState_t state;
    dsFPDColor_t color;
    dsFPDIndicator_t eIndicator;
    int count = 0;
    int mode = 0;
    int numOfSuppportedColors = 0;
    char buffer[50];
    ut_kvp_instance_t *pInstance = NULL;
    char colorbuffer[50];
    char supportedColorbuffer[50];

    // Initialize the Front Panel Display (FPD) sub-module
    UT_LOG_DEBUG("Invoking dsFPInit()");
    ret = dsFPInit();
    UT_LOG_DEBUG("dsFPInit returned : %d",ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    pInstance = ut_kvp_profile_getInstance();
    count = ut_kvp_getListCount(pInstance,"dsFPD/SupportedFPDIndicators");
    for (int i=0;i<count;i++)
    {
        sprintf(buffer, "dsFPD/SupportedFPDIndicators/%d", i);
        eIndicator = ut_kvp_getUInt32Field( pInstance, buffer);

        // Get the current state of the FP
        UT_LOG_DEBUG("Invoking dsGetFPState() with eIndicator=%d", eIndicator);
        ret = dsGetFPState(eIndicator, &state);
        UT_LOG_DEBUG("dsGetFPState() returned state=%d and status=%d", state, ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetFPState failed with status: %d", ret);
            continue;
        }

        // If the current state of the FP is OFF, set it to ON
        if (state == dsFPD_STATE_OFF)
        {
            UT_LOG_DEBUG("Invoking dsSetFPState() with eIndicator=%d and state=dsFPD_STATE_ON", eIndicator);
            ret = dsSetFPState(eIndicator, dsFPD_STATE_ON);
            UT_LOG_DEBUG("dsSetFPState() returned status=%d", ret);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetFPState failed with status: %d", ret);
                continue;
            }
        }
        //Check the indicator supports single-coloured
        sprintf(colorbuffer, "dsFPD/%d/DEFAULT_COLOR_MODE",eIndicator);
        mode = ut_kvp_getUInt32Field(pInstance,colorbuffer);
        UT_LOG_DEBUG("Default color mode from profile file : %d", mode);

        //set the color functionality of discrete `LED`
        if (mode == 0)
        {
            UT_LOG_DEBUG("The indicator supports singlecolored");
            sprintf(supportedColorbuffer, "dsFPD/%d/supportedColors",eIndicator);
            numOfSuppportedColors = ut_kvp_getListCount(pInstance,supportedColorbuffer);
            for (int j=0;j<numOfSuppportedColors;j++)
            {
                sprintf(buffer,"dsFPD/%d/supportedColors/%d", eIndicator, j);
                color = ut_kvp_getUInt32Field( pInstance, buffer);
                UT_LOG_DEBUG("Invoking dsSetFPColor with eIndicator: %d and color: %d", eIndicator, color);
                ret = dsSetFPColor(eIndicator, color);
                UT_LOG_DEBUG("Return status: %d", ret);
                UT_ASSERT_EQUAL(ret, dsERR_OPERATION_NOT_SUPPORTED);
                if (ret != dsERR_OPERATION_NOT_SUPPORTED)
                {
                    UT_LOG_ERROR("dsSetFPColor failed with status: %d", ret);
                }
            }
        }
        else
        {
            UT_LOG_DEBUG("The indicator supports multi color");
        }
    }

    ret = dsFPTerm();
    UT_LOG_DEBUG("Invoking dsFPTerm");
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test function is designed to iterate and check FPD indicators in L2 dsFPD module
*
* This test function iterates over all FPD indicators and checks their state and color. It tests the functionality of dsFPInit, dsGetFPState, dsSetFPState, dsSetFPColor, and dsFPTerm functions in the L2 dsFPD module. The test is designed to ensure that these functions are working as expected and handling the FPD indicators correctly.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 012@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsFPD_L2_Low-Level_TestSpecification.md](../../docs/pages/dsFPD_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsFPD_SetFPstateON_Single_SetColor_source(void)
{
    gTestID = 12;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    dsFPDState_t state;
    dsFPDColor_t color;
    dsFPDIndicator_t eIndicator;
    int count = 0;
    int mode = 0;
    int numOfSuppportedColors = 0;
    char buffer[50];
    ut_kvp_instance_t *pInstance = NULL;
    char colorbuffer[50];
    char supportedColorbuffer[50];

    // Initialize the Front Panel Display (FPD) sub-module
    UT_LOG_DEBUG("Invoking dsFPInit()");
    ret = dsFPInit();
    UT_LOG_DEBUG("dsFPInit returned : %d",ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    pInstance = ut_kvp_profile_getInstance();
    count = ut_kvp_getListCount(pInstance,"dsFPD/SupportedFPDIndicators");
    for (int i=0;i<count;i++)
    {
        sprintf(buffer, "dsFPD/SupportedFPDIndicators/%d", i);
        eIndicator = ut_kvp_getUInt32Field( pInstance, buffer);

        // Get the current state of the FP
        UT_LOG_DEBUG("Invoking dsGetFPState() with eIndicator=%d", eIndicator);
        ret = dsGetFPState(eIndicator, &state);
        UT_LOG_DEBUG("dsGetFPState() returned state=%d and status=%d", state, ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetFPState failed with status: %d", ret);
            continue;
        }

        // If the current state of the FP is OFF, set it to ON
        if (state == dsFPD_STATE_OFF)
        {
            UT_LOG_DEBUG("Invoking dsSetFPState() with eIndicator=%d and state=dsFPD_STATE_ON", eIndicator);
            ret = dsSetFPState(eIndicator, dsFPD_STATE_ON);
            UT_LOG_DEBUG("dsSetFPState() returned status=%d", ret);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetFPState failed with status: %d", ret);
                continue;
            }
        }
        //Check the indicator supports single-coloured
        sprintf(colorbuffer,"dsFPD/%d/DEFAULT_COLOR_MODE",eIndicator);
        mode = ut_kvp_getUInt32Field(pInstance,colorbuffer);
        UT_LOG_DEBUG("Default color mode from profile file : %d", mode);

        //set the color functionality of discrete `LED`
        if (mode == 0)
        {
            UT_LOG_DEBUG("The indicator supports singlecolored");
            sprintf(supportedColorbuffer, "dsFPD/%d/supportedColors",eIndicator);
            numOfSuppportedColors = ut_kvp_getListCount(pInstance,supportedColorbuffer);
            for (int j=0;j<numOfSuppportedColors;j++)
            {
                sprintf(buffer,"dsFPD/%d/supportedColors/%d", eIndicator, j);
                color = ut_kvp_getUInt32Field( pInstance, buffer);
                UT_LOG_DEBUG("Invoking dsSetFPColor with eIndicator: %d and color: %d", eIndicator, color);
                ret = dsSetFPColor(eIndicator, color);
                UT_LOG_DEBUG("Return status: %d", ret);
                UT_ASSERT_EQUAL(ret, dsERR_OPERATION_NOT_SUPPORTED);
                if (ret != dsERR_OPERATION_NOT_SUPPORTED)
                {
                    UT_LOG_ERROR("dsSetFPColor failed with status: %d", ret);
                }
            }
        }
        else
        {
            UT_LOG_DEBUG("The indicator supports multi color");
        }
    }

    ret = dsFPTerm();
    UT_LOG_DEBUG("Invoking dsFPTerm");
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test verifies the LED state transitions in the dsFPD module
*
* This test function invokes the necessary APIs in the dsFPD module to transition through different LED states and verifies their return status and output values. It also includes logging and error handling as per the rules.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 013@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsFPD_L2_Low-Level_TestSpecification.md](../../docs/pages/dsFPD_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsFPD_VerifyLEDStateTransitions_sink(void)
{
    gTestID = 13;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

   dsError_t ret;
    unsigned int supportedStates;
    dsFPDLedState_t state, getState;

    UT_LOG_DEBUG("Invoking dsFPInit");
    ret = dsFPInit();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsFPGetSupportedLEDStates with valid buffer");
    ret = dsFPGetSupportedLEDStates(&supportedStates);
    UT_LOG_DEBUG("Supported states: %u, Return status: %d", supportedStates, ret);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);

    UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(supportedStates, "dsFPD/SupportedLEDStates");

    for (state = dsFPD_LED_DEVICE_NONE; state < dsFPD_LED_DEVICE_MAX; state++)
    {
        if (!(supportedStates & (1 << state)))
            continue;

        UT_LOG_DEBUG("Invoking dsFPSetLEDState with state: %d", state);
        ret = dsFPSetLEDState(state);
        UT_LOG_DEBUG("Return status: %d", ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsFPSetLEDState failed for state: %d", state);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsFPGetLEDState with valid buffer");
        ret = dsFPGetLEDState(&getState);
        UT_LOG_DEBUG("Current state: %d, Return status: %d", getState, ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsFPGetLEDState failed for state: %d", state);
            continue;
        }

        UT_ASSERT_EQUAL(state, getState);
        if (state != getState)
        {
            UT_LOG_ERROR("Mismatch in set and get state : %d", state);
        }
    }

    UT_LOG_DEBUG("Invoking dsFPTerm");
    ret = dsFPTerm();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test verifies the LED state transitions in the L2 dsFPD module
*
* This test function initializes the dsFPD module, retrieves the supported LED states, sets each supported LED state,
* retrieves the current LED state, and verifies that the set and retrieved states match. It then terminates the dsFPD module.
* This test is important to ensure that the LED state transitions are functioning correctly in the L2 dsFPD module.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 014@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsFPD_L2_Low-Level_TestSpecification.md](../../docs/pages/dsFPD_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsFPD_VerifyLEDStateTransitions_source(void)
{
    gTestID = 14;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    unsigned int supportedStates;
    dsFPDLedState_t state, getState;

    UT_LOG_DEBUG("Invoking dsFPInit");
    ret = dsFPInit();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsFPGetSupportedLEDStates with valid buffer");
    ret = dsFPGetSupportedLEDStates(&supportedStates);
    UT_LOG_DEBUG("Supported states: %u, Return status: %d", supportedStates, ret);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);

    UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(supportedStates, "dsFPD/SupportedLEDStates");

    for (state = dsFPD_LED_DEVICE_NONE; state < dsFPD_LED_DEVICE_MAX; state++)
    {
        if (!(supportedStates & (1 << state)))
            continue;

        UT_LOG_DEBUG("Invoking dsFPSetLEDState with state: %d", state);
        ret = dsFPSetLEDState(state);
        UT_LOG_DEBUG("Return status: %d", ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsFPSetLEDState failed for state: %d", state);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsFPGetLEDState with valid buffer");
        ret = dsFPGetLEDState(&getState);
        UT_LOG_DEBUG("Current state: %d, Return status: %d", getState, ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsFPGetLEDState failed for state: %d", state);
            continue;
        }

        UT_ASSERT_EQUAL(state, getState);
        if (state != getState)
        {
            UT_LOG_ERROR("Mismatch in set and get state : %d", state);
        }
    }

    UT_LOG_DEBUG("Invoking dsFPTerm");
    ret = dsFPTerm();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main tests for this module
 *
 * @return int - 0 on success, otherwise failure
 */

int test_dsFPD_l2_register(void)
{
    // Create the test suite
    pSuite = UT_add_suite("[L2 dsFPD]", NULL, NULL);
    if (pSuite == NULL)
    {
        return -1;
    }
    // List of test function names and strings

    UT_add_test( pSuite, "l2_dsFPD_SetFPstateON_SetBrightness_sink", test_l2_dsFPD_SetFPstateON_SetBrightness_sink);
    UT_add_test( pSuite, "l2_dsFPD_SetFPstateON_SetBrightness_source", test_l2_dsFPD_SetFPstateON_SetBrightness_source);
    UT_add_test( pSuite, "l2_dsFPD_SetFPstateOFF_SetBrightness_sink", test_l2_dsFPD_SetFPstateOFF_SetBrightness_sink);
    UT_add_test( pSuite, "l2_dsFPD_SetFPstateOFF_SetBrightness_source", test_l2_dsFPD_SetFPstateOFF_SetBrightness_source);
    UT_add_test( pSuite, "l2_dsFPD_SetFPstateOFF_SetBlink_sink", test_l2_dsFPD_SetFPstateOFF_SetBlink_sink);
    UT_add_test( pSuite, "l2_dsFPD_SetFPstateOFF_SetBlink_source", test_l2_dsFPD_SetFPstateOFF_SetBlink_source);
    UT_add_test( pSuite, "l2_dsFPD_SetFPstateON_Multi_SetColor_sink", test_l2_dsFPD_SetFPstateON_Multi_SetColor_sink);
    UT_add_test( pSuite, "l2_dsFPD_SetFPstateON_Multi_SetColor_source", test_l2_dsFPD_SetFPstateON_Multi_SetColor_source);
    UT_add_test( pSuite, "l2_dsFPD_SetFPstateOFF_SetColor_sink", test_l2_dsFPD_SetFPstateOFF_SetColor_sink);
    UT_add_test( pSuite, "l2_dsFPD_SetFPstateOFF_SetColor_source", test_l2_dsFPD_SetFPstateOFF_SetColor_source);
    UT_add_test( pSuite, "l2_dsFPD_SetFPstateON_Single_SetColor_sink", test_l2_dsFPD_SetFPstateON_Single_SetColor_sink);
    UT_add_test( pSuite, "l2_dsFPD_SetFPstateON_Single_SetColor_source", test_l2_dsFPD_SetFPstateON_Single_SetColor_source);
    UT_add_test( pSuite, "l2_dsFPD_VerifyLEDStateTransitions_sink", test_l2_dsFPD_VerifyLEDStateTransitions_sink);
    UT_add_test( pSuite, "l2_dsFPD_VerifyLEDStateTransitions_source", test_l2_dsFPD_VerifyLEDStateTransitions_source);

    return 0;
}