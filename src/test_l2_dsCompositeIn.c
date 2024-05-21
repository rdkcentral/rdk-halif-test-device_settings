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
* Ref to API Definition specification documentation : [halSpec.md](../../../docs/halSpec.md)
*/

#include <ut.h>
#include <ut_log.h>
#include <stdlib.h>
#include <time.h>
#include "dsCompositeIn.h"

/**
* @brief Test to verify the number of composite input ports
*
* This test verifies the number of composite input ports by comparing the expected number of ports with the actual number of ports returned by the API. The test is designed to ensure that the API is correctly identifying the number of ports and that the system is correctly configured.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 001@n
*
* **Test Procedure:**
* Refer to UT specification documentation [l2_dsCompositeIn_test_specification.md](l2_dsCompositeIn_test_specification.md)
*/

void test_l2_dsCompositeIn_VerifyCompositeInputPorts(void)
{
    UT_LOG("Entering test_l2_dsCompositeIn_VerifyCompositeInputPorts...");

    dsError_t status;
    uint8_t numInputs;
    uint8_t expectedNumInputs = 2; // This value should be fetched from the configuration file

    // Step 1: Call the pre-requisite API dsCompositeInInit to initialize the COMPOSITE Input module.
    status = dsCompositeInInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    if (status != dsERR_NONE)
    {
        UT_LOG("dsCompositeInInit failed with status: %d", status);
        return;
    }

    // Step 2: Call the API dsCompositeInGetNumberOfInputs to get the number of COMPOSITE Input ports on the specific platform.
    status = dsCompositeInGetNumberOfInputs(&numInputs);
    UT_LOG("Invoked dsCompositeInGetNumberOfInputs() . Return status: %d, numInputs : %d ", status, numInputs);
    // Step 3: Check the return status of the API. If it is not dsERR_NONE, then the API has failed. The test case should fail in this scenario.
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    if (status != dsERR_NONE)
    {
        UT_LOG("dsCompositeInGetNumberOfInputs failed with status: %d", status);
        // Call the post-requisite API dsCompositeInTerm to terminate the COMPOSITE Input module.
        dsCompositeInTerm();
        return;
    }

    // Step 4: If the return status is dsERR_NONE, compare the value of the uint8_t variable with the expected number of COMPOSITE input ports from the configuration file.
    UT_ASSERT_EQUAL(numInputs, expectedNumInputs);
    if (numInputs != expectedNumInputs)
    {
        UT_LOG("Mismatch in number of inputs. Expected: %d, Got: %d", expectedNumInputs, numInputs);
        // Call the post-requisite API dsCompositeInTerm to terminate the COMPOSITE Input module.
        dsCompositeInTerm();
        return;
    }

    // Step 6: Call the post-requisite API dsCompositeInTerm to terminate the COMPOSITE Input module.
    status = dsCompositeInTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    if (status != dsERR_NONE)
    {
        UT_LOG("dsCompositeInTerm failed with status: %d", status);
    }

    UT_LOG("Exiting test_l2_dsCompositeIn_VerifyCompositeInputPorts...");
}

/**
* @brief Test to verify the Composite Input Status
*
* This function tests the Composite Input Status by initializing the COMPOSITE Input module, getting the status, checking the status fields, and then terminating the COMPOSITE Input module.
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

    // Step 1: Call dsCompositeInInit
    ret = dsCompositeInInit();
    UT_LOG("Invoked dsCompositeInInit(). Return status: %d", ret);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);

    if (ret == dsERR_NONE)
    {
        // Step 2: Call dsCompositeInGetStatus
        ret = dsCompositeInGetStatus(&status);
        UT_LOG("Invoked dsCompositeInGetStatus(). Return status: %d", ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);

        if (ret == dsERR_NONE)
        {
            // Step 3: Check 'isPresented' field
            UT_LOG("'isPresented' field is: %d", status.isPresented);
            UT_ASSERT_EQUAL(status.isPresented, false);

            // Step 4: Check 'isPortConnected' field
            for (int i = 0; i < dsCOMPOSITE_IN_PORT_MAX; i++)
            {
                UT_LOG("'isPortConnected' field for port %d is: %d", i, status.isPortConnected[i]);
                UT_ASSERT_EQUAL(status.isPortConnected[i], false);
            }

            // Step 5: Check 'activePort' field
            UT_LOG("'activePort' field is: %d", status.activePort);
            UT_ASSERT_EQUAL(status.activePort, dsCOMPOSITE_IN_PORT_NONE);
        }

        // Step 6: Call dsCompositeInTerm
        ret = dsCompositeInTerm();
        UT_LOG("Invoked dsCompositeInTerm(). Return status: %d", ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
    }

    UT_LOG("Exiting test_l2_dsCompositeIn_VerifyCompositeInputStatus...");
}

/**
* @brief Test for setting and checking composite input port
*
* This function tests the APIs dsCompositeInInit, dsCompositeInSelectPort, dsCompositeInGetStatus, and dsCompositeInTerm. It first initializes the COMPOSITE Input sub-system, then selects a random port for presentation, gets the status of all COMPOSITE Input Status, checks the returned status, and finally terminates the COMPOSITE Input sub-system.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 003@n
*
* **Test Procedure:**
* Refer to UT specification documentation [l2_dsCompositeIn_test_specification.md](l2_dsCompositeIn_test_specification.md)
*/

void test_l2_dsCompositeIn_SetAndCheckCompositeInputPort(void)
{
    UT_LOG("Entering test_l2_dsCompositeIn_SetAndCheckCompositeInputPort...");

    dsError_t ret;
    dsCompositeInStatus_t status;
    dsCompositeInPort_t port;

    // Initialize the COMPOSITE Input sub-system
    ret = dsCompositeInInit();
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG("dsCompositeInInit failed with error: %d", ret);
        return;
    }

    // Select a random port from the available ports
    srand(time(NULL));
    port = rand() % dsCOMPOSITE_IN_PORT_MAX;

    // Set the COMPOSITE Input port for presentation
    ret = dsCompositeInSelectPort(port);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG("dsCompositeInSelectPort failed with error: %d", ret);
        dsCompositeInTerm();
        return;
    }

    // Get the status of all COMPOSITE Input Status
    ret = dsCompositeInGetStatus(&status);
    UT_LOG("Invoked dsCompositeInGetStatus(). Return status: %d ,port status.isPresented : %d, isPortConnected[%d] : %d, activePort: %d ", ret, status.isPresented, port, status.isPortConnected[port], status.activePort);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG("dsCompositeInGetStatus failed with error: %d", ret);
        dsCompositeInTerm();
        return;
    }

    // Check the returned status
    UT_ASSERT_EQUAL(status.isPresented, false);
    UT_ASSERT_EQUAL(status.isPortConnected[port], false);
    UT_ASSERT_EQUAL(status.activePort, port);

    // Terminate the COMPOSITE Input sub-system
    ret = dsCompositeInTerm();
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG("dsCompositeInTerm failed with error: %d", ret);
    }

    UT_LOG("Exiting test_l2_dsCompositeIn_SetAndCheckCompositeInputPort...");
}

/**
* @brief Test for scaling video without selecting COMPOSITE Input port
*
* This function tests the scenario where `dsCompositeInScaleVideo` is called without selecting the COMPOSITE Input port. It first initializes the COMPOSITE Input module using `dsCompositeInInit`, then tries to scale the video using `dsCompositeInScaleVideo`, and finally terminates the COMPOSITE Input module using `dsCompositeInTerm`.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 004@n
*
* **Test Procedure:**
* Refer to UT specification documentation [l2_dsCompositeIn_test_specification.md](l2_dsCompositeIn_test_specification.md)
*/

void test_l2_dsCompositeIn_ScaleVideoWithoutSelectingPort(void)
{
    UT_LOG("Entering test_l2_dsCompositeIn_ScaleVideoWithoutSelectingPort...");

    dsError_t status;
    int32_t x, y, width, height;

    srand(time(0)); // use current time as seed for random generator
    x = rand() % 1000; // assuming the resolution width is 1000
    y = rand() % 1000; // assuming the resolution height is 1000
    width = rand() % (1000 - x); // width should not exceed the resolution width
    height = rand() % (1000 - y); // height should not exceed the resolution height

    status = dsCompositeInInit();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    if (status != dsERR_NONE)
    {
        UT_LOG("dsCompositeInInit failed with status: %d", status);
        return;
    }

    status = dsCompositeInScaleVideo(x, y, width, height);
    UT_LOG("Invoked dsCompositeInScaleVideo(). Return status: %d", status);
    UT_ASSERT_EQUAL(status, dsERR_OPERATION_NOT_SUPPORTED);
    if (status != dsERR_OPERATION_NOT_SUPPORTED)
    {
        UT_LOG("dsCompositeInScaleVideo failed with status: %d", status);
        dsCompositeInTerm();
        return;
    }

    status = dsCompositeInTerm();
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    if (status != dsERR_NONE)
    {
        UT_LOG("dsCompositeInTerm failed with status: %d", status);
    }

    UT_LOG("Exiting test_l2_dsCompositeIn_ScaleVideoWithoutSelectingPort...");
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
    if (pSuite == NULL)
    {
        return -1;
    }
    // List of test function names and strings

    UT_add_test( pSuite, "l2_dsCompositeIn_VerifyCompositeInputPorts", test_l2_dsCompositeIn_VerifyCompositeInputPorts);
    UT_add_test( pSuite, "l2_dsCompositeIn_VerifyCompositeInputStatus", test_l2_dsCompositeIn_VerifyCompositeInputStatus);
    UT_add_test( pSuite, "l2_dsCompositeIn_SetAndCheckCompositeInputPort", test_l2_dsCompositeIn_SetAndCheckCompositeInputPort);
    UT_add_test( pSuite, "l2_dsCompositeIn_ScaleVideoWithoutSelectingPort", test_l2_dsCompositeIn_ScaleVideoWithoutSelectingPort);

    return 0;
}