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
* @file test_l2_dsHost.c
* @page dsHost Level 2 Tests
*
* ## Module's Role
* This module includes Level 2 functional tests (success and failure scenarios).
* This is to ensure that the dsHost APIs meet the requirements across all vendors.
*
* **Pre-Conditions:**  None@n
* **Dependencies:** None@n
*
* Ref to API Definition specification documentation : [ds-host_halSpec.md](../../docs/pages/ds-host_halSpec.md)
*/

#include <ut.h>
#include <ut_log.h>
#include <ut_kvp_profile.h>
#include "dsHost.h"

static int gTestGroup = 2;
static int gTestID = 1;

/**
* @brief Test for getting CPU temperature from the Host HAL sub-system
*
* This test function initializes the Host HAL sub-system, gets the CPU temperature, checks if the temperature is within the valid range, and then terminates the Host sub-system. It uses the provided macro to check if the returned CPU temperature is equal to the value specified in the 'Sink_HostSettings.yaml' configuration file. If any of the API calls fail, the test function will immediately return, as indicated by the use of the UT_ASSERT_EQUAL_FATAL macro.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 001@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsHost_L2_Low-Level_TestSpecification.md](../../docs/pages/dsHost_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsHost_GetCPUTemperature_sink(void)
{
    gTestID = 1;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t retStatus;
    float cpuTemperature;

    UT_LOG_DEBUG("Invoking dsHostInit with no input parameters");
    retStatus = dsHostInit();
    UT_LOG_DEBUG("Return status: %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsGetCPUTemperature with valid buffer");
    retStatus = dsGetCPUTemperature(&cpuTemperature);
    UT_LOG_DEBUG("CPU Temperature: %f, Return status: %d", cpuTemperature, retStatus);
    UT_ASSERT_EQUAL(retStatus, dsERR_NONE);
    if (retStatus != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetCPUTemperature failed with status: %d", retStatus);
        UT_LOG_DEBUG("Invoking dsHostTerm");
        dsHostTerm();
        return;
    }

    //TODO : kvp profile support for float type is not available
    UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(cpuTemperature, "cpuTemperature");

    UT_LOG_DEBUG("Invoking dsHostTerm with no input parameters");
    retStatus = dsHostTerm();
    UT_LOG_DEBUG("Return status: %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test for getting CPU temperature from the Host HAL sub-system
*
* This test function initializes the Host HAL sub-system, gets the CPU temperature, checks the returned value, and terminates the Host sub-system. It uses the provided macro to compare the returned CPU temperature with the value specified in the configuration files. The function logs all the operations and checks the return status of each API call.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 002@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsHost_L2_Low-Level_TestSpecification.md](../../docs/pages/dsHost_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsHost_GetCPUTemperature_source(void)
{
    gTestID = 2;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t retStatus;
    float cpuTemperature;

    UT_LOG_DEBUG("Invoking dsHostInit");
    retStatus = dsHostInit();
    UT_LOG_DEBUG("Return status: %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsGetCPUTemperature");
    retStatus = dsGetCPUTemperature(&cpuTemperature);
    UT_LOG_DEBUG("CPU Temperature: %f, Return status: %d", cpuTemperature, retStatus);
    UT_ASSERT_EQUAL(retStatus, dsERR_NONE);
    if (retStatus != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetCPUTemperature failed with status: %d", retStatus);
        UT_LOG_DEBUG("Invoking dsHostTerm");
        dsHostTerm();
        return;
    }

    //TODO : kvp profile support for float type is not available
    UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(cpuTemperature, "cpuTemperature");

    UT_LOG_DEBUG("Invoking dsHostTerm");
    retStatus = dsHostTerm();
    UT_LOG_DEBUG("Return status: %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to get and verify the SoC ID from the Host HAL sub-system
*
* This test function initializes the Host HAL sub-system, gets the SoC ID, verifies it with the value from the configuration file, and then terminates the Host HAL sub-system. It uses the provided macro to compare the SoC ID with the value from the configuration file. The function logs all the steps and checks the return values of the API calls.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 003@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsHost_L2_Low-Level_TestSpecification.md](../../docs/pages/dsHost_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsHost_GetAndVerifySocID_sink(void)
{
    gTestID = 3;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    char socID[20];

    UT_LOG_DEBUG("Invoking dsHostInit with no input parameters");
    ret = dsHostInit();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsGetSocIDFromSDK with valid buffer");
    ret = dsGetSocIDFromSDK(socID);
    UT_LOG_DEBUG("Return status: %d, socID: %s", ret, socID);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetSocIDFromSDK failed with status: %d", ret);
        UT_LOG_DEBUG("Invoking dsHostTerm");
        dsHostTerm();
        return;
    }

    UT_ASSERT_KVP_EQUAL_PROFILE_STRING(socID, "socID");

    UT_LOG_DEBUG("Invoking dsHostTerm with no input parameters");
    ret = dsHostTerm();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to get and verify the SocID from the source
*
* In this test, the dsHostInit function is invoked to initialize the host. Then, the dsGetSocIDFromSDK function is called to get the SocID from the SDK. The SocID is then verified against the expected value from the configuration files. Finally, the dsHostTerm function is invoked to terminate the host. The test ensures that all these operations are successful.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 004@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsHost_L2_Low-Level_TestSpecification.md](../../docs/pages/dsHost_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsHost_GetAndVerifySocID_source(void)
{
    gTestID = 4;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    char socID[20];

    UT_LOG_DEBUG("Invoking dsHostInit");
    ret = dsHostInit();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsGetSocIDFromSDK with valid buffer");
    ret = dsGetSocIDFromSDK(socID);
    UT_LOG_DEBUG("socID: %s, return status: %d", socID, ret);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetSocIDFromSDK failed with status: %d", ret);
        UT_LOG_DEBUG("Invoking dsHostTerm");
        dsHostTerm();
        return;
    }

    UT_ASSERT_KVP_EQUAL_PROFILE_STRING(socID, "socID");

    UT_LOG_DEBUG("Invoking dsHostTerm");
    ret = dsHostTerm();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test validates the Host EDID sink of the L2 dsHost module
*
* This test function initializes the dsHost module, retrieves the Host EDID, validates the retrieved EDID and length, and then terminates the dsHost module. The purpose of this test is to ensure that the dsHost module correctly retrieves and validates the Host EDID.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 005@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsHost_L2_Low-Level_TestSpecification.md](../../docs/pages/dsHost_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsHost_ValidateHostEDID_sink(void)
{
    gTestID = 5;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    unsigned char edid[EDID_MAX_DATA_SIZE];
    int length;

    UT_LOG_DEBUG("Invoking dsHostInit with no input parameters");
    ret = dsHostInit();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsGetHostEDID with valid pointers for edid and length");
    ret = dsGetHostEDID(edid, &length);
    UT_LOG_DEBUG("Return status: %d, EDID: %s, Length: %d", ret, edid, length);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetHostEDID failed with status: %d", ret);
        UT_LOG_DEBUG("Invoking dsHostTerm");
        dsHostTerm();
        return;
    }

    //TODO : kvp profile support for array type is not available
    UT_ASSERT_KVP_EQUAL_PROFILE_STRING(edid, "edidBytes");
    UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(length, "edidbytesLength");

    UT_LOG_DEBUG("Invoking dsHostTerm with no input parameters");
    ret = dsHostTerm();
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

int test_dsHost_l2_register(void)
{
    // Create the test suite
    pSuite = UT_add_suite("[L2 dsHost]", NULL, NULL);
    if (pSuite == NULL)
    {
        return -1;
    }
    // List of test function names and strings

    UT_add_test( pSuite, "l2_dsHost_GetCPUTemperature_sink", test_l2_dsHost_GetCPUTemperature_sink);
    UT_add_test( pSuite, "l2_dsHost_GetCPUTemperature_source", test_l2_dsHost_GetCPUTemperature_source);
    UT_add_test( pSuite, "l2_dsHost_GetAndVerifySocID_sink", test_l2_dsHost_GetAndVerifySocID_sink);
    UT_add_test( pSuite, "l2_dsHost_GetAndVerifySocID_source", test_l2_dsHost_GetAndVerifySocID_source);
    UT_add_test( pSuite, "l2_dsHost_ValidateHostEDID_sink", test_l2_dsHost_ValidateHostEDID_sink);

    return 0;
}