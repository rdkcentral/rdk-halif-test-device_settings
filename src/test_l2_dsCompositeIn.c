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
* @file test_l2_dsCompositeIn.c
* @page dsCompositeIn Level 2 Tests
*
* ## Module's Role
* This module includes Level 2 functional tests (success and failure scenarios).
* This is to ensure that the dsCompositeIn APIs meet the requirements across all vendors.
*
* **Pre-Conditions:**  None@n
* **Dependencies:** None@n
*
* Ref to API Definition specification documentation : [ds-composite-in_halSpec.md](../../docs/pages/ds-composite-in_halSpec.md)
*/

#include <ut.h>
#include <ut_log.h>
#include <ut_kvp_profile.h>
#include "dsCompositeIn.h"

static int gTestGroup = 2;
static int gTestID = 1;

/**
* @brief Test for getting the number of COMPOSITE Input ports
*
* This test function initializes the COMPOSITE Input module, gets the number of COMPOSITE Input ports, compares the returned value with the value from the YAML file, and then terminates the COMPOSITE Input module.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 001@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsCompositeIn_L2_Low-Level_TestSpecification.md](../../docs/pages/dsCompositeIn_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsCompositeIn_GetNumberOfInputs(void)
{
    gTestID = 1;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE; // Initialize the return status to dsERR_NONE.
    uint8_t numInputs = 0; // Initialize to 0.

    // Call the pre-requisite API dsCompositeInInit to initialize the COMPOSITE Input module.
    ret = dsCompositeInInit();
    UT_LOG_DEBUG("Invoking dsCompositeInInit\n");
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    // Call the API dsCompositeInGetNumberOfInputs and pass a pointer to a uint8_t variable to store the number of COMPOSITE Input ports.
    ret = dsCompositeInGetNumberOfInputs(&numInputs);
    UT_LOG_DEBUG("Invoking dsCompositeInGetNumberOfInputs with valid buffer\n");

    // Check the return status of dsCompositeInGetNumberOfInputs. It should return dsERR_NONE for success. Any other return value indicates an error.
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("Failed to get number of COMPOSITE Input ports with error: %d\n", ret);
        // Call the post-requisite API dsCompositeInTerm to terminate the COMPOSITE Input module.
        dsCompositeInTerm();
        return;
    }

    //composite Input number of inputs
    UT_LOG_INFO("Composite Number of Inputs: %d\n", numInputs);

    // Compare the value returned by dsCompositeInGetNumberOfInputs with the value retrieved from the YAML file. They should match.
    UT_ASSERT_KVP_EQUAL_PROFILE_UINT8(numInputs, "composite_input_configurations/number_of_ports");

    // Call the post-requisite API dsCompositeInTerm to terminate the COMPOSITE Input module.
    ret = dsCompositeInTerm();
    UT_LOG_DEBUG("Invoking dsCompositeInTerm\n");
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test verifies the status of the Composite Input
*
* This test function initializes the Composite Input, gets its status, checks if it is in disable status and then terminates the Composite Input. The purpose of this test is to ensure that the Composite Input is functioning as expected.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 002@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsCompositeIn_L2_Low-Level_TestSpecification.md](../../docs/pages/dsCompositeIn_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsCompositeIn_VerifyCompositeInputStatus(void)
{
    gTestID = 2;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE; // Initialize the return status to dsERR_NONE.
    dsCompositeInStatus_t status = { 0 }; // Initialize all fields to 0

    UT_LOG_DEBUG("Invoking dsCompositeInInit()");
    ret = dsCompositeInInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsCompositeInGetStatus()");
    ret = dsCompositeInGetStatus(&status);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsCompositeInGetStatus failed with error: %d\n", ret);
        dsCompositeInTerm(); // Call post-requisite API on failure
        return;
    }

    UT_LOG_INFO("IsPresented: %d, IsPortConnected[0]: %d, IsPortConnected[1]: %d, activePort: %d\n",
                                                                            status.isPresented,
                                                                            status.isPortConnected[dsCOMPOSITE_IN_PORT_0],
                                                                            status.isPortConnected[dsCOMPOSITE_IN_PORT_1],
                                                                            status.activePort);

    UT_ASSERT_EQUAL(status.isPresented, false);
    UT_ASSERT_EQUAL(status.isPortConnected[dsCOMPOSITE_IN_PORT_0], false);
    UT_ASSERT_EQUAL(status.isPortConnected[dsCOMPOSITE_IN_PORT_1], false);
    UT_ASSERT_EQUAL(status.activePort, dsCOMPOSITE_IN_PORT_NONE);

    UT_LOG_DEBUG("Invoking dsCompositeInTerm()");
    ret = dsCompositeInTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to verify the selection and status of Composite In Port
*
* This test verifies the functionality of Composite In Port selection and its status. It checks if the port is initialized, selected, and terminated correctly. It also checks the status of the port after selection.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 003@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsCompositeIn_L2_Low-Level_TestSpecification.md](../../docs/pages/dsCompositeIn_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsCompositeIn_VerifyCompositeInPortSelectionAndStatus(void)
{
    gTestID = 3;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE; // Initialize the return status to dsERR_NONE.
    dsCompositeInStatus_t status = { 0 }; // Initialize all fields to 0.
    uint8_t numberOfInputs = 0; // Initialize to 0.

    ret = dsCompositeInInit();
    UT_LOG_DEBUG("Invoking dsCompositeInInit()");
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    ret = dsCompositeInGetNumberOfInputs(&numberOfInputs);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("Failed to get the number of composite inputs\n");
        dsCompositeInTerm();
        return;
    }

    for (dsCompositeInPort_t port = dsCOMPOSITE_IN_PORT_0; port < numberOfInputs; port++)
    {
        ret = dsCompositeInSelectPort(port);
        UT_LOG_DEBUG("Invoking dsCompositeInSelectPort()");
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("Failed to select COMPOSITE Input port %d\n", port);
            continue;
        }

        ret = dsCompositeInGetStatus(&status);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("Failed to get status of COMPOSITE Input ports\n");
        }

        UT_LOG_INFO("IsPresented: %d, IsPortConnected[0]: %d, activePort: %d\n",
                                                                status.isPresented,
                                                                status.isPortConnected[port],
                                                                status.activePort);

        UT_ASSERT_EQUAL(status.activePort, port);
        UT_ASSERT_EQUAL(status.isPresented, false);
        UT_ASSERT_EQUAL(status.isPortConnected[port], false);
    }

    ret = dsCompositeInTerm();
    UT_LOG_DEBUG("Invoking dsCompositeInTerm()");
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main tests for this module
 *
 * @return int - 0 on success, otherwise failure
 */

int test_l2_dsCompositeIn_register(void)
{
    // Create the test suite
    pSuite = UT_add_suite("[L2 dsCompositeIn sink devices]", NULL, NULL);
    if (pSuite == NULL)
    {
        return -1;
    }
    // List of test function names and strings

    UT_add_test( pSuite, "l2_dsCompositeIn_GetNumberOfInputs", test_l2_dsCompositeIn_GetNumberOfInputs);
    UT_add_test( pSuite, "l2_dsCompositeIn_VerifyCompositeInputStatus", test_l2_dsCompositeIn_VerifyCompositeInputStatus);
    UT_add_test( pSuite, "l2_dsCompositeIn_VerifyCompositeInPortSelectionAndStatus", test_l2_dsCompositeIn_VerifyCompositeInPortSelectionAndStatus);

    return 0;
}
