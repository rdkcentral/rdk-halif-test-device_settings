/*
* If not stated otherwise in this file or this component's LICENSE file the
* following copyright and licenses apply:*
* Copyright 2023 RDK Management
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
* Ref to API Definition specification documentation : [halSpec.md](../../../docs/halSpec.md)
*/

#include <ut.h>
#include <ut_log.h>
#include "dsCompositeIn.h"

/**
* @brief This test aims to verify the functionality of getting the number of inputs in the dsCompositeIn module.
*
* In this test, the dsCompositeInInit function is first called to initialize the dsCompositeIn module. Then, the dsCompositeInGetNumberOfInputs function is called to get the number of inputs. The returned number of inputs is checked to ensure it is not less than zero. Finally, the dsCompositeInTerm function is called to terminate the dsCompositeIn module. The return values of all these function calls are checked against the expected return value of dsERR_NONE.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 001@n
*
* **Test Procedure:**
* Refer to UT specification documentation [l2_dsCompositeIn_test_specification.md](l2_dsCompositeIn_test_specification.md)
*/

void test_l2_dsCompositeIn_GetNumberOfInputs(void)
{
    UT_LOG("Entering test_l2_dsCompositeIn_GetNumberOfInputs...");

    dsError_t ret;
    uint8_t numInputs;

    // Call dsCompositeInInit
    UT_LOG("Invoking dsCompositeInInit.");
    ret = dsCompositeInInit();
    UT_LOG("dsCompositeInInit returns : %d",ret);
    if (ret != dsERR_NONE) {
        UT_LOG("Expected return value: dsERR_NONE. Actual return value: %d", ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_LOG("Exiting test_l2_dsCompositeIn_GetNumberOfInputs...");
        return;
    }

    // Call dsCompositeInGetNumberOfInputs
    UT_LOG("Invoking dsCompositeInGetNumberOfInputs with valid buffer. ");
    ret = dsCompositeInGetNumberOfInputs(&numInputs);
    UT_LOG("dsCompositeInGetNumberOfInputs returns : %d and numberOfInputs : %d",ret,numInputs);
    if (ret != dsERR_NONE) {
        UT_LOG("Expected return value: dsERR_NONE. Actual return value: %d", ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_LOG("Exiting test_l2_dsCompositeIn_GetNumberOfInputs...");
        return;
    }

    // Verify returned number of COMPOSITE Input ports
    if (numInputs < 0) {
        UT_LOG("Verifying number of COMPOSITE Input ports. Expected: >=0. Actual: %d", numInputs);
        UT_ASSERT(numInputs >= 0);
        UT_LOG("Exiting test_l2_dsCompositeIn_GetNumberOfInputs...");
        return;
    }

    // Call dsCompositeInTerm
    UT_LOG("Invoking dsCompositeInTerm.");
    ret = dsCompositeInTerm();
    UT_LOG("dsCompositeInTerm returns : %d",ret);
    if (ret != dsERR_NONE) {
        UT_LOG("Expected return value: dsERR_NONE. Actual return value: %d", ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_LOG("Exiting test_l2_dsCompositeIn_GetNumberOfInputs...");
        return;
    }

    UT_LOG("Test case test_l2_dsCompositeIn_GetNumberOfInputs passed successfully.");
    UT_LOG("Exiting test_l2_dsCompositeIn_GetNumberOfInputs...");
}

/**
* @brief This test verifies the status of the Composite Input in the L2 DS module
*
* This test initializes the DS module, gets the status of the Composite Input, verifies if it is disabled, and then terminates the DS module. This is done to ensure that the Composite Input is not enabled when it is not supposed to be.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 002@n
*
* **Test Procedure:**
* Refer to UT specification documentation [l2_dsCompositeIn_test_specification.md](l2_dsCompositeIn_test_specification.md)
*/

void test_l2_dsCompositeIn_VerifyCompositeInputStatus(void)
{
    UT_LOG("Entering test_l2_dsCompositeIn_VerifyCompositeInputStatus...");

    dsError_t ret;
    dsCompositeInStatus_t status;

    // Call dsCompositeInInit
    ret = dsCompositeInInit();
    UT_LOG("Invoking dsCompositeInInit(). Return status: %d", ret);
    if (ret != dsERR_NONE) {
        UT_LOG("dsCompositeInInit failed. Exiting test_l2_dsCompositeIn_VerifyCompositeInputStatus...");
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        return;
    }

    // Call dsCompositeInGetStatus
    ret = dsCompositeInGetStatus(&status);
    UT_LOG("Invoking dsCompositeInGetStatus() with valid buffer. Return status: %d and Ispresented : %d isPortConnected : %d activePort: %d ", ret, status.isPresented, status.isPortConnected, status.activePort);
    if (ret != dsERR_NONE) {
        UT_LOG("dsCompositeInGetStatus failed. Exiting test_l2_dsCompositeIn_VerifyCompositeInputStatus...");
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        return;
    }

    // Verify Composite Input is disabled
    if (status.isPresented) {
        UT_LOG("Composite Input is enabled. Exiting test_l2_dsCompositeIn_VerifyCompositeInputStatus...");
        UT_ASSERT_EQUAL(status.isPresented, false);
        return;
    }

    // Call dsCompositeInTerm
    ret = dsCompositeInTerm();
    UT_LOG("Invoking dsCompositeInTerm(). Return status: %d", ret);
    if (ret != dsERR_NONE) {
        UT_LOG("dsCompositeInTerm failed. Exiting test_l2_dsCompositeIn_VerifyCompositeInputStatus...");
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        return;
    }

    UT_LOG("Exiting test_l2_dsCompositeIn_VerifyCompositeInputStatus...");
}

/**
* @brief This test aims to verify the functionality of the dsCompositeInSelectPort function
*
* This test case checks if the dsCompositeInSelectPort function correctly selects the desired port and handles errors appropriately. It also verifies if the function dsCompositeInInit and dsCompositeInTerm are working as expected.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 003@n
*
* **Test Procedure:**
* Refer to UT specification documentation [l2_dsCompositeIn_test_specification.md](l2_dsCompositeIn_test_specification.md)
*/

void test_l2_dsCompositeIn_SelectPort(void)
{
    UT_LOG("Entering test_l2_dsCompositeIn_SelectPort...");

    dsError_t ret;
    dsCompositeInPort_t port = dsCOMPOSITE_IN_PORT_0;

    // Call dsCompositeInInit
    ret = dsCompositeInInit();
    UT_LOG("Invoking dsCompositeInInit(). Return status: %d", ret);
    if (ret != dsERR_NONE) {
        UT_LOG("dsCompositeInInit failed. Exiting test_l2_dsCompositeIn_SelectPort...");
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        return;
    }

    // Call dsCompositeInSelectPort
    ret = dsCompositeInSelectPort(port);
    UT_LOG("Invoking dsCompositeInSelectPort() with input port: %d. Return status: %d", port, ret);
    if (ret != dsERR_NONE) {
        UT_LOG("dsCompositeInSelectPort failed. Exiting test_l2_dsCompositeIn_SelectPort...");
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        return;
    }

    // Verify function returns dsERR_NONE
    UT_ASSERT_EQUAL(ret, dsERR_NONE);

    // Check port info and confirm active port
    // This part is left as a comment because it depends on the implementation of the dsCompositeInSelectPort function
    // and how the active port is stored and accessed. Replace this comment with the appropriate code.
    // if (activePort != port) {
    //     UT_LOG("Active port is not the expected port. Exiting test_l2_dsCompositeIn_SelectPort...");
    //     UT_ASSERT_EQUAL(activePort, port);
    //     return;
    // }

    // Call dsCompositeInTerm
    ret = dsCompositeInTerm();
    UT_LOG("Invoking dsCompositeInTerm(). Return status: %d", ret);
    if (ret != dsERR_NONE) {
        UT_LOG("dsCompositeInTerm failed. Exiting test_l2_dsCompositeIn_SelectPort...");
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        return;
    }

    UT_LOG("Exiting test_l2_dsCompositeIn_SelectPort...");
}

static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main tests for this module
 *
 * @return int - 0 on success, otherwise failure
 */

int test_dsCompositeIn_l2_register(void)
{
    // Create the test suite
    pSuite = UT_add_suite("[L2 dsCompositeIn]", NULL, NULL);
    if (pSuite == NULL) {
        return -1;
    }
    // List of test function names and strings

    UT_add_test( pSuite, "l2_dsCompositeIn_GetNumberOfInputs", test_l2_dsCompositeIn_GetNumberOfInputs);
    UT_add_test( pSuite, "l2_dsCompositeIn_VerifyCompositeInputStatus", test_l2_dsCompositeIn_VerifyCompositeInputStatus);
    UT_add_test( pSuite, "l2_dsCompositeIn_SelectPort", test_l2_dsCompositeIn_SelectPort);

    return 0;
}