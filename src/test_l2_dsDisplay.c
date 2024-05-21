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
* Ref to API Definition specification documentation : [halSpec.md](../../../docs/halSpec.md)
*/

#include <ut.h>
#include <ut_log.h>
#include <stdlib.h>
#include "dsDisplay.h"

/**
* @brief This test validates the EDID of a display
*
* This test initializes the display, gets the display handle, retrieves the EDID and EDID bytes, and then terminates the display. The obtained EDID and EDID bytes are expected to be validated with predefined values.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 001@n
*
* **Test Procedure:**
* Refer to UT specification documentation [l2_dsDisplay_test_specification.md](l2_dsDisplay_test_specification.md)
*/

void test_l2_dsDisplay_ValidateEDID(void)
{
    UT_LOG("Entering test_l2_dsDisplay_ValidateEDID...");

    dsError_t ret;
    intptr_t handle;
    dsDisplayEDID_t *edid = (dsDisplayEDID_t*)malloc(sizeof(dsDisplayEDID_t));
    unsigned char *edidBuffer = (unsigned char *)malloc(1024);
    int length;

    // Step 1
    ret = dsDisplayInit();
    UT_LOG("Invoked dsDisplayInit(). Return status: %d", ret);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);

    if (ret == dsERR_NONE)
    {
        // Step 2
        ret = dsGetDisplay(dsVIDEOPORT_TYPE_HDMI, 0, &handle);
        UT_LOG("Invoked dsGetDisplay() with dsVIDEOPORT_TYPE_HDMI and index 0. Return status: %d, Handle: %ld", ret, handle);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);

        if (ret == dsERR_NONE)
        {
            // Step 3
            ret = dsGetEDID(handle, edid);
            UT_LOG("Invoked dsGetEDID() with handle. Return status: %d", ret);
            UT_LOG("Parameter values ; productCode : %d , serialNumber :%d, manufactureYear : %d, manufactureWeek : %d, hdmiDeviceType : %d, isRepeater : %d, physicalAddressA :%d, physicalAddressB : %d, physicalAddressC : %d, physicalAddressD : %d, numOfSupportedResolution : %d, monitorName :%s ", edid->productCode, edid->serialNumber, edid->manufactureYear, edid->manufactureWeek, edid->hdmiDeviceType, edid->isRepeater, edid->physicalAddressA, edid->physicalAddressB, edid->physicalAddressC, edid->physicalAddressD, edid->numOfSupportedResolution, edid->monitorName );
            UT_ASSERT_EQUAL(ret, dsERR_NONE);

            // Step 4
            // Validate the obtained EDID information with the predefined EDID value.
            // This step is not implemented as it requires predefined EDID value.

            // Step 5
            ret = dsGetEDIDBytes(handle, edidBuffer, &length);
            UT_LOG("Invoked dsGetEDIDBytes() with handle. Return status: %d, EDID Buffer Length: %d", ret, length);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);

            // Step 6
            // Validate the obtained EDID buffer with the predefined EDID buffer.
            // This step is not implemented as it requires predefined EDID buffer.
        }

        // Step 7
        ret = dsDisplayTerm();
        UT_LOG("Invoked dsDisplayTerm(). Return status: %d", ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
    }

    UT_LOG("Exiting test_l2_dsDisplay_ValidateEDID...");
}

/**
* @brief This test checks the default aspect ratio of the display
*
* This test initializes the display, gets the display handle for HDMI port, checks the aspect ratio of the display and then terminates the display. The purpose of this test is to ensure that the default aspect ratio of the display is 16x9.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 002@n
*
* **Test Procedure:**
* Refer to UT specification documentation [l2_dsDisplay_test_specification.md](l2_dsDisplay_test_specification.md)
*/

void test_l2_dsDisplay_TestDefaultAspectRatio(void)
{
    UT_LOG("Entering test_l2_dsDisplay_TestDefaultAspectRatio...");

    dsError_t ret;
    intptr_t handle;
    dsVideoAspectRatio_t aspectRatio;

    // Step 1: Call dsDisplayInit API
    ret = dsDisplayInit();
    UT_LOG("Invoking dsDisplayInit(). Return status: %d", ret);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);

    if (ret == dsERR_NONE) {
        // Step 2: Call dsGetDisplay API
        ret = dsGetDisplay(dsVIDEOPORT_TYPE_HDMI, 0, &handle);
        UT_LOG("Invoking dsGetDisplay() with vType: dsVIDEOPORT_TYPE_HDMI and index: 0. Return status: %d", ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);

        if (ret == dsERR_NONE) {
            // Step 3: Call dsGetDisplayAspectRatio API
            ret = dsGetDisplayAspectRatio(handle, &aspectRatio);
            UT_LOG("Invoking dsGetDisplayAspectRatio() with handle: %ld. Return status: %d, Aspect Ratio: %d", handle, ret, aspectRatio);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            UT_ASSERT_EQUAL(aspectRatio, dsVIDEO_ASPECT_RATIO_16x9);
        }

        // Step 4: Call dsDisplayTerm API
        ret = dsDisplayTerm();
        UT_LOG("Invoking dsDisplayTerm(). Return status: %d", ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
    }

    UT_LOG("Exiting test_l2_dsDisplay_TestDefaultAspectRatio...");
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
    if (pSuite == NULL) {
        return -1;
    }
    // List of test function names and strings

    UT_add_test( pSuite, "l2_dsDisplay_ValidateEDID", test_l2_dsDisplay_ValidateEDID);
    UT_add_test( pSuite, "l2_dsDisplay_TestDefaultAspectRatio", test_l2_dsDisplay_TestDefaultAspectRatio);

    return 0;
}