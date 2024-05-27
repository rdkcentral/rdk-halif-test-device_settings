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
#include "dsCompositeIn.h"

static int gTestGroup = 2;
static int gTestID = 1;

/**
* @brief This test aims to verify the functionality of the dsCompositeInGetNumberOfInputs API
*
* This test case checks if the dsCompositeInGetNumberOfInputs API is able to correctly return the number of COMPOSITE input ports. The test involves initializing the COMPOSITE Input module, invoking the API, and comparing the returned value with the expected number of COMPOSITE input ports obtained from a configuration YAML file. The test case is considered passed if the values match, otherwise it is failed.
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
    dsError_t ret;
    uint8_t numInputs;
    uint8_t expectedNumInputs = 1;
    //yaml_file_t file;
    //yaml_node_t *node;

    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    // Step 1: Call the pre-requisite API dsCompositeInInit to initialize the COMPOSITE Input module.
    ret = dsCompositeInInit();
    UT_LOG_DEBUG("Invoking dsCompositeInInit, status : %d",ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsCompositeInInit failed with error: %d\n", ret);
        return;
    }

    // Step 2: Declare a variable of type uint8_t to hold the number of COMPOSITE input ports.
    // Step 3: Call the API dsCompositeInGetNumberOfInputs with the address of the declared variable as the parameter.
    ret = dsCompositeInGetNumberOfInputs(&numInputs);
    UT_LOG_DEBUG("Invoking dsCompositeInGetNumberOfInputs with valid buffer, status : %d  numOfInputs :%d",ret, numInputs);

    // Step 4: Check the return status of the API. If it is not dsERR_NONE, then the API has failed. Handle the error based on the error code.
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsCompositeInGetNumberOfInputs failed with error: %d\n", ret);
        // Call the post-requisite API dsCompositeInTerm to terminate the COMPOSITE Input module.
        dsCompositeInTerm();
        return;
    }

    // Step 5: If the API call is successful, the number of COMPOSITE input ports will be stored in the declared variable.
    // Step 6: Parse the configuration YAML file 'ReferencePanel_AVInput_Info.yaml' and get the expected number of COMPOSITE input ports.
    //file = yaml_file_open("ReferencePanel_AVInput_Info.yaml");
    //node = yaml_file_find_node(file, "COMPOSITE_INPUT_PORTS");
    //expectedNumInputs = yaml_node_as_uint8(node);

    // Step 7: Compare the value obtained from the API with the expected value from the YAML file. If they match, the test case is passed. Otherwise, the test case is failed.
    UT_ASSERT_EQUAL(numInputs, expectedNumInputs);
    if (numInputs != expectedNumInputs)
    {
        UT_LOG_ERROR("Mismatch in number of COMPOSITE input ports. Expected: %d, Got: %d\n", expectedNumInputs, numInputs);
    }

    // Step 8: Call the post-requisite API dsCompositeInTerm to terminate the COMPOSITE Input module.
    ret = dsCompositeInTerm();
    UT_LOG_DEBUG("Invoking dsCompositeInTerm, status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsCompositeInTerm failed with error: %d\n", ret);
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test verifies the status of Composite Input
*
* This test initializes the COMPOSITE Input module, then gets the status of all COMPOSITE Input Status, checks the 'isPresented' field, and finally terminates the COMPOSITE Input module. It uses UT_ASSERT_EQUAL and UT_ASSERT_EQUAL_FATAL to check the return values of the APIs and the 'isPresented' field. It also logs the progress of the test case using UT_LOG_INFO, UT_LOG_DEBUG, and UT_LOG_ERROR.
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
    dsError_t ret;
    dsCompositeInStatus_t status;

    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    ret = dsCompositeInInit();
    UT_LOG_DEBUG("Invoking dsCompositeInInit, status : %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsCompositeInInit failed with error: %d\n", ret);
        return;
    }

    ret = dsCompositeInGetStatus(&status);
    UT_LOG_DEBUG("Invoking dsCompositeInGetStatus with valid buffer, status : %d", ret);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsCompositeInGetStatus failed with error: %d\n", ret);
        dsCompositeInTerm(); // Call post-requisite API in case of failure
        return;
    }

    UT_ASSERT_EQUAL(status.isPresented, false);
    UT_ASSERT_EQUAL(status.isPortConnected[dsCOMPOSITE_IN_PORT_0], false);
    UT_ASSERT_EQUAL(status.isPortConnected[dsCOMPOSITE_IN_PORT_1], false);
    UT_ASSERT_EQUAL(status.activePort, dsCOMPOSITE_IN_PORT_NONE);

    ret = dsCompositeInTerm();
    UT_LOG_DEBUG("Invoking dsCompositeInTerm, status : %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsCompositeInTerm failed with error: %d\n", ret);
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test for setting and checking composite input port
*
* This test case initializes the COMPOSITE Input sub-system, sets the COMPOSITE Input port for presentation, gets the status of all COMPOSITE Input Status, checks the returned status structure, and finally terminates the COMPOSITE Input sub-system. If any of the API calls fail, it logs an error and terminates the COMPOSITE Input sub-system if necessary.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 003@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsCompositeIn_L2_Low-Level_TestSpecification.md](../../docs/pages/dsCompositeIn_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsCompositeIn_SetAndCheckCompositeInputPort(void)
{
    gTestID = 3;
    dsError_t ret;
    dsCompositeInPort_t Port = dsCOMPOSITE_IN_PORT_0;
    dsCompositeInStatus_t status;

    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    ret = dsCompositeInInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("Failed to initialize COMPOSITE Input sub-system\n");
        return;
    }

    ret = dsCompositeInSelectPort(Port);
    UT_LOG_DEBUG("Invoking dsCompositeInSelectPort with Port: %d\n", Port);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("Failed to set COMPOSITE Input port for presentation\n");
        dsCompositeInTerm();
        return;
    }

    ret = dsCompositeInGetStatus(&status);
    UT_LOG_DEBUG("Invoking dsCompositeInGetStatus\n");
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("Failed to get the status of all COMPOSITE Input Status\n");
        dsCompositeInTerm();
        return;
    }

    UT_ASSERT_EQUAL(status.isPresented, false);
    UT_ASSERT_EQUAL(status.isPortConnected[Port], false);
    UT_ASSERT_EQUAL(status.activePort, Port);

    ret = dsCompositeInTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("Failed to terminate COMPOSITE Input sub-system\n");
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test for scaling video without selecting COMPOSITE Input port
*
* This function tests the scenario where the COMPOSITE Input port is not selected before scaling the video. It checks if the appropriate error code is returned in this case.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 004@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsCompositeIn_L2_Low-Level_TestSpecification.md](../../docs/pages/dsCompositeIn_L2_Low-Level_TestSpecification.md)
*/
void test_l2_dsCompositeIn_ScaleVideoWithoutSelectingPort(void)
{
    gTestID = 4;
    dsError_t retStatus;
    int32_t x = 10, y = 10, width = 100, height = 100;

    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    // Step 1: Call the pre-requisite API dsCompositeInInit()
    UT_LOG_DEBUG("Invoking dsCompositeInInit()");
    retStatus = dsCompositeInInit();
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);
    if (retStatus != dsERR_NONE)
    {
        UT_LOG_ERROR("dsCompositeInInit() failed with status: %d", retStatus);
    }

    // Step 2: Call the API dsCompositeInScaleVideo()
    UT_LOG_DEBUG("Invoking dsCompositeInScaleVideo() with x=%d, y=%d, width=%d, height=%d", x, y, width, height);
    retStatus = dsCompositeInScaleVideo(x, y, width, height);
    UT_ASSERT_EQUAL(retStatus, dsERR_OPERATION_NOT_SUPPORTED);
    if (retStatus != dsERR_OPERATION_NOT_SUPPORTED)
    {
        UT_LOG_ERROR("dsCompositeInScaleVideo() failed with status: %d", retStatus);
        // Call the post-requisite API dsCompositeInTerm() if dsCompositeInScaleVideo() fails
        dsCompositeInTerm();
    }

    // Step 3: Call the post-requisite API dsCompositeInTerm()
    UT_LOG_DEBUG("Invoking dsCompositeInTerm()");
    retStatus = dsCompositeInTerm();
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);
    if (retStatus != dsERR_NONE)
    {
        UT_LOG_ERROR("dsCompositeInTerm() failed with status: %d", retStatus);
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
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

    UT_add_test( pSuite, "l2_dsCompositeIn_GetNumberOfInputs", test_l2_dsCompositeIn_GetNumberOfInputs);
    UT_add_test( pSuite, "l2_dsCompositeIn_VerifyCompositeInputStatus", test_l2_dsCompositeIn_VerifyCompositeInputStatus);
    UT_add_test( pSuite, "l2_dsCompositeIn_SetAndCheckCompositeInputPort", test_l2_dsCompositeIn_SetAndCheckCompositeInputPort);
    UT_add_test( pSuite, "l2_dsCompositeIn_ScaleVideoWithoutSelectingPort", test_l2_dsCompositeIn_ScaleVideoWithoutSelectingPort);

    return 0;
}