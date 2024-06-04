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
* @file test_l2_dsDisplay.c
* @page dsDisplay Level 2 Tests
*
* ## Module's Role
* This module includes Level 2 functional tests (success and failure scenarios).
* This is to ensure that the dsDisplay APIs meet the requirements across all vendors.
*
* **Pre-Conditions:**  None@n
* **Dependencies:** None@n
*
* Ref to API Definition specification documentation : [ds-display_halSpec.md](../../docs/pages/ds-display_halSpec.md)
*/

#include <ut.h>
#include <ut_log.h>
#include <ut_kvp_profile.h>
#include "dsDisplay.h"

static int gTestGroup = 2;
static int gTestID = 1;
/**
* @brief This test aims to retrieve and validate the EDID of a sink in the L2 dsDisplay module
*
* This test function tests the retrieval and validation of the Extended Display Identification Data (EDID) of a sink in the L2 dsDisplay module. It ensures that the functions dsDisplayInit, dsGetDisplay, dsGetEDID, dsGetEDIDBytes, and dsDisplayTerm are working as expected.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 001@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsDisplay_L2_Low-Level_TestSpecification.md](../../docs/pages/dsDisplay_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsDisplay_RetrieveAndValidateEDID_sink(void)
{
    gTestID = 1;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    dsDisplayEDID_t edid;
    unsigned char edidBytes[MAX_EDID_BYTES_LEN];
    int length;

    // Step 1: Call dsDisplayInit
    ret = dsDisplayInit();
    UT_LOG_INFO("Invoked dsDisplayInit(), returned: %d\n", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    // Step 2: Call dsGetDisplay
    ret = dsGetDisplay(dsVIDEOPORT_TYPE_INTERNAL, 0, &handle);
    UT_LOG_INFO("Invoked dsGetDisplay() with dsVIDEOPORT_TYPE_INTERNAL and index 0, returned: %d, handle: %ld\n", ret, handle);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        // Call dsDisplayTerm if dsGetEDID fails
        dsDisplayTerm();
        return;
    }

    // Step 3: Call dsGetEDID
    ret = dsGetEDID(handle, &edid);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    UT_LOG_INFO("Invoked dsGetEDID() with handle %ld, returned: %d, productCode: %d\n", handle, ret, edid.productCode);
    UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(edid.productCode, "EDID_Data/productCode");
    if (ret != dsERR_NONE)
    {
        // Call dsDisplayTerm if dsGetEDID fails
        dsDisplayTerm();
        return;
    }

    // Step 4: Call dsGetEDIDBytes
    ret = dsGetEDIDBytes(handle, edidBytes, &length);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    UT_LOG_INFO("Invoked dsGetEDIDBytes() with handle %ld, returned: %d, Manufacturer ID: %d\n", handle, ret, edidBytes[8] << 8 | edidBytes[9]);
    //TODOs : Need KVP support for array handling
    UT_ASSERT_KVP_EQUAL_PROFILE_UINT16(edidBytes[8] << 8 | edidBytes[9], "EDID_Data/edidBytes");

    if (ret != dsERR_NONE)
    {
        // Call dsDisplayTerm if dsGetEDIDBytes fails
        dsDisplayTerm();
        return;
    }

    // Step 5: Call dsDisplayTerm
    ret = dsDisplayTerm();
    UT_LOG_INFO("Invoked dsDisplayTerm(), returned: %d\n", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to verify the default aspect ratio of the source in the L2 dsDisplay module
*
* In this test, the dsDisplayInit(), dsGetDisplay(), dsGetDisplayAspectRatio(), and dsDisplayTerm() functions are called in sequence to check the default aspect ratio of the source. The test verifies that the aspect ratio is dsVIDEO_ASPECT_RATIO_16x9. If any of the function calls fail or the aspect ratio is not as expected, the test fails.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 002@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsDisplay_L2_Low-Level_TestSpecification.md](../../docs/pages/dsDisplay_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsDisplay_TestDefaultAspectRatio_source(void)
{
    gTestID = 2;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    dsVideoAspectRatio_t aspectRatio;

    // Step 1: Call dsDisplayInit()
    UT_LOG_DEBUG("Invoking dsDisplayInit()");
    ret = dsDisplayInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    // Step 2: Call dsGetDisplay()
    UT_LOG_DEBUG("Invoking dsGetDisplay() with dsVIDEOPORT_TYPE_HDMI and index 0");
    ret = dsGetDisplay(dsVIDEOPORT_TYPE_HDMI, 0, &handle);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetDisplay() failed with error: %d\n", ret);
        dsDisplayTerm();
        return;
    }

    // Step 3: Call dsGetDisplayAspectRatio()
    UT_LOG_DEBUG("Invoking dsGetDisplayAspectRatio() with handle obtained from dsGetDisplay()");
    ret = dsGetDisplayAspectRatio(handle, &aspectRatio);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    UT_ASSERT_EQUAL(aspectRatio, dsVIDEO_ASPECT_RATIO_16x9);
    if (ret != dsERR_NONE || aspectRatio != dsVIDEO_ASPECT_RATIO_16x9)
    {
        UT_LOG_ERROR("dsGetDisplayAspectRatio() failed with error: %d\n", ret);
        dsDisplayTerm();
        return;
    }

    // Step 4: Verify aspect ratio
    UT_LOG_DEBUG("Verifying that the aspect ratio is dsVIDEO_ASPECT_RATIO_16x9");
    UT_ASSERT_EQUAL(aspectRatio, dsVIDEO_ASPECT_RATIO_16x9);

    // Step 5: Call dsDisplayTerm()
    UT_LOG_DEBUG("Invoking dsDisplayTerm()");
    ret = dsDisplayTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main tests for this module
 *
 * @return int - 0 on success, otherwise failure
 */

int test_dsDisplay_l2_register(void)
{
    // Create the test suite
    pSuite = UT_add_suite("[L2 dsDisplay]", NULL, NULL);
    if (pSuite == NULL)
    {
        return -1;
    }
    // List of test function names and strings

    UT_add_test( pSuite, "l2_dsDisplay_RetrieveAndValidateEDID_sink", test_l2_dsDisplay_RetrieveAndValidateEDID_sink);
    UT_add_test( pSuite, "l2_dsDisplay_TestDefaultAspectRatio_source", test_l2_dsDisplay_TestDefaultAspectRatio_source);

    return 0;
}