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
* @brief This test validates the EDID (Extended Display Identification Data) of the L2 DS Display
*
* This test initializes the DS Display, gets the display handle, validates the EDID, gets the EDID buffer and length, and finally compares the EDID value and buffer. This is done to ensure the correct functioning of the DS Display and its EDID.
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

    // Initialize DS Display
    ret = dsDisplayInit();
    UT_LOG("Invoking dsDisplayInit returns : %d",ret);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE) {
        UT_LOG("dsDisplayInit failed with error: %d", ret);
        return;
    }

    // Get Display Handle
    ret = dsGetDisplay(dsVIDEOPORT_TYPE_HDMI, 0, &handle);
    UT_LOG("Invoking dsGetDisplay returns : %d and handle :%d",ret, handle);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE) {
        UT_LOG("dsGetDisplay failed with error: %d", ret);
        return;
    }

    // Validate EDID
    ret = dsGetEDID(handle, edid);
    UT_LOG("Invoking dsGetEDID returns : %d",ret);
    UT_LOG("Parameter values ; productCode : %d , serialNumber :%d, manufactureYear : %d, manufactureWeek : %d, hdmiDeviceType : %d, isRepeater : %d, physicalAddressA :%d, physicalAddressB : %d, physicalAddressC : %d, physicalAddressD : %d, numOfSupportedResolution : %d, monitorName :%s ", edid->productCode, edid->serialNumber, edid->manufactureYear, edid->manufactureWeek, edid->hdmiDeviceType, edid->isRepeater, edid->physicalAddressA, edid->physicalAddressB, edid->physicalAddressC, edid->physicalAddressD, edid->numOfSupportedResolution, edid->monitorName );
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE) {
        UT_LOG("dsGetEDID failed with error: %d", ret);
        return;
    }

    // Get EDID Buffer and Length
    UT_LOG("Invoking dsGetEDIDBytes returns : %d and length : %d  edidBuffer : %s",ret,length, edidBuffer);
    ret = dsGetEDIDBytes(handle, edidBuffer, &length);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE) {
        UT_LOG("dsGetEDIDBytes failed with error: %d", ret);
        return;
    }

    // Compare EDID Value and Buffer
    UT_ASSERT_EQUAL(memcmp(edidBuffer, &edid, length), 0);
    if (memcmp(edidBuffer, &edid, length) != 0) {
        UT_LOG("EDID Value and Buffer do not match");
        return;
    }

    // Call dsDisplayTerm
    ret = dsDisplayTerm();
    UT_LOG("Invoking dsDisplayTerm(). Return status: %d", ret);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE) {
        UT_LOG("dsDisplayTerm failed. Exiting test_l2_dsDisplay_ValidateEDID...");
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        return;
    }
    free(edid);
    free(edidBuffer);
    UT_LOG("Exiting test_l2_dsDisplay_ValidateEDID...");
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

    return 0;
}