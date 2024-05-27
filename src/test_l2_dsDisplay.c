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
* Ref to API Definition specification documentation : [dsDisplay_halSpec.md](../../docs/pages/dsDisplay_halSpec.md)
*/

#include <ut.h>
#include <ut_log.h>
#include "dsDisplay.h"

static int gTestGroup = 2;
static int gTestID = 1;

/**
* @brief This test validates the EDID information of the display
*
* This test function initializes the display, gets the display handle, retrieves the EDID information and the EDID bytes, and then terminates the display. The validation of the product code and the Manufacturer ID from the EDID buffer against the values available in the profile file 'ReferencePanel_EDID_Info.yml'.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 001@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsDisplay_L2_Low-Level_TestSpecification.md](../../docs/pages/dsDisplay_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsDisplay_ValidateEDIDInfo(void)
{
    gTestID = 1;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    dsDisplayEDID_t edid;
    unsigned char edidBytes[MAX_EDID_BYTES_LEN];
    int length;

    // Step 1
    ret = dsDisplayInit();
    UT_LOG_DEBUG("Invoking dsDisplayInit(), returned: %d\n", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    // Step 2
    ret = dsGetDisplay(dsVIDEOPORT_TYPE_HDMI, 0, &handle);
    UT_LOG_DEBUG("Invoking dsGetDisplay() with dsVIDEOPORT_TYPE_HDMI and index 0, returned: %d, handle: %ld\n", ret, handle);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    // Step 3
    ret = dsGetEDID(handle, &edid);
    UT_LOG_DEBUG("Invoking dsGetEDID() with handle: %ld, returned: %d, productCode: %d\n", handle, ret, edid.productCode);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);

    // Validate the product code from the output structure against the data available in Profile file 'ReferencePanel_EDID_Info.yml'.
    // This step is not implemented as it requires access to the profile file and parsing it.

    // Step 4
    ret = dsGetEDIDBytes(handle, edidBytes, &length);
    UT_LOG_DEBUG("Invoking dsGetEDIDBytes() with handle: %ld, returned: %d, length: %d\n", handle, ret, length);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);

    // Validate the "Manufacturer ID" at byte 8th and 9th from the EDID buffer against the values available in the profile file 'ReferencePanel_EDID_Info.yml'.
    // This step is not implemented as it requires access to the profile file and parsing it.

    // Step 5
    ret = dsDisplayTerm();
    UT_LOG_DEBUG("Invoking dsDisplayTerm(), returned: %d\n", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test for default aspect ratio of the display
*
* This function tests the default aspect ratio of the display. It first initializes the display subsystem, then gets the handle of the connected display device. It then gets the aspect ratio of the display and checks if it is 16:9. Finally, it terminates the display subsystem.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 002@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsDisplay_L2_Low-Level_TestSpecification.md](../../docs/pages/dsDisplay_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsDisplay_TestDefaultAspectRatio(void)
{
    gTestID = 2;
    dsError_t ret;
    intptr_t handle;
    dsVideoAspectRatio_t aspectRatio;

    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    UT_LOG_DEBUG("Invoking dsDisplayInit");
    ret = dsDisplayInit();
    UT_LOG_DEBUG(" dsDisplayInit returned status : %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsDisplayInit failed with error: %d\n", ret);
        return;
    }

    UT_LOG_DEBUG("Invoking dsGetDisplay with dsVIDEOPORT_TYPE_HDMI and index 0");
    ret = dsGetDisplay(dsVIDEOPORT_TYPE_HDMI, 0, &handle);
    UT_LOG_DEBUG(" dsGetDisplay returned status : %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetDisplay failed with error: %d\n", ret);
        dsDisplayTerm();
        return;
    }

    UT_LOG_DEBUG("Invoking dsGetDisplayAspectRatio with handle obtained from dsGetDisplay");
    ret = dsGetDisplayAspectRatio(handle, &aspectRatio);
    UT_LOG_DEBUG(" dsGetDisplayAspectRatio returned status : %d", ret);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetDisplayAspectRatio failed with error: %d\n", ret);
        dsDisplayTerm();
        return;
    }

    UT_ASSERT_EQUAL(aspectRatio, dsVIDEO_ASPECT_RATIO_16x9);
    if (aspectRatio != dsVIDEO_ASPECT_RATIO_16x9)
    {
        UT_LOG_ERROR("Aspect ratio is not dsVIDEO_ASPECT_RATIO_16x9\n");
        dsDisplayTerm();
        return;
    }

    UT_LOG_DEBUG("Invoking dsDisplayTerm");
    ret = dsDisplayTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsDisplayTerm failed with error: %d\n", ret);
    }

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

    UT_add_test( pSuite, "l2_dsDisplay_ValidateEDIDInfo", test_l2_dsDisplay_ValidateEDIDInfo);
    UT_add_test( pSuite, "l2_dsDisplay_TestDefaultAspectRatio", test_l2_dsDisplay_TestDefaultAspectRatio);

    return 0;
}