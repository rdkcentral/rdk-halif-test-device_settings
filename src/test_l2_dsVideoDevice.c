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
* @file test_l2_dsVideoDevice.c
* @page dsVideoDevice Level 2 Tests
*
* ## Module's Role
* This module includes Level 2 functional tests (success and failure scenarios).
* This is to ensure that the dsVideoDevice APIs meet the requirements across all vendors.
*
* **Pre-Conditions:**  None@n
* **Dependencies:** None@n
*
* Ref to API Definition specification documentation : [dsVideoDevice_halSpec.md](../../docs/pages/dsVideoDevice_halSpec.md)
*/

#include <ut.h>
#include <ut_log.h>
#include <ut_kvp_profile.h>
#include "dsVideoDevice.h"

static int gTestGroup = 2;
static int gTestID = 1;

int MAX_DEVICES = 1;

/**
* @brief Test for setting and getting DFC source in dsVideoDevice
*
* This test case is designed to verify the functionality of setting and getting DFC source in dsVideoDevice.
* The test involves initializing the video device, getting the video device, setting the DFC, getting the DFC and terminating the video device.
* The test asserts that the DFC set is the same as the DFC get.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 001@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoDevice_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoDevice_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoDevice_SetAndGetDFC_source(void)
{
    dsError_t retStatus;
    intptr_t handle;
    dsVideoZoom_t dfc, dfc_get;
    ut_kvp_instance_t *pInstance = NULL;
    char buffer[50];
    int count = 0;

    gTestID = 1;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    UT_LOG_DEBUG("Invoking dsVideoDeviceInit");
    retStatus = dsVideoDeviceInit();
    UT_LOG_DEBUG("Return status: %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    for(int index = 0; index < MAX_DEVICES; index++)
    {
        UT_LOG_DEBUG("Invoking dsGetVideoDevice with index: %d", index);
        retStatus = dsGetVideoDevice(index, &handle);
        UT_LOG_DEBUG("Return status: %d, Handle: %ld", retStatus, handle);
        UT_ASSERT_EQUAL(retStatus, dsERR_NONE);
        if (retStatus != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetVideoDevice failed with status: %d", retStatus);
            continue;
        }

        pInstance = ut_kvp_profile_getInstance();
        count = ut_kvp_getListCount(pInstance,"VideoDevice/VideoDevice0/SupportedDFCs");
        for (int i=0;i<count;i++)
        {
            sprintf(buffer, "VideoDevice/VideoDevice0/SupportedDFCs/%d", i);
            dfc = ut_kvp_getUInt32Field( pInstance, buffer);

            UT_LOG_DEBUG("Invoking dsSetDFC with handle: %ld, dfc: %d", handle, dfc);
            retStatus = dsSetDFC(handle, dfc);
            UT_LOG_DEBUG("Return status: %d", retStatus);
            UT_ASSERT_EQUAL(retStatus, dsERR_NONE);

            if (retStatus != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetDFC failed with status: %d", retStatus);
                continue;
            }

            UT_LOG_DEBUG("Invoking dsGetDFC with handle: %ld", handle);
            retStatus = dsGetDFC(handle, &dfc_get);
            UT_LOG_DEBUG("Return status: %d, dfc_get: %d", retStatus, dfc_get);
            UT_ASSERT_EQUAL(retStatus, dsERR_NONE);

            UT_ASSERT_EQUAL(dfc, dfc_get);
        }
    }
    UT_LOG_DEBUG("Invoking dsVideoDeviceTerm");
    retStatus = dsVideoDeviceTerm();
    UT_LOG_DEBUG("Return status: %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to verify the HDR capabilities of the video device
*
* In this test, the HDR capabilities of the video device are retrieved and checked against the expected capabilities. This is done to ensure that the video device is functioning as expected and can support the required HDR capabilities.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 002@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoDevice_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoDevice_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoDevice_GetHDRCapabilities_sink(void)
{
    gTestID = 2;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    int capabilities;

    UT_LOG_DEBUG("Invoking dsVideoDeviceInit");
    ret = dsVideoDeviceInit();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for(int index = 0; index < MAX_DEVICES; index++)
    {
        UT_LOG_DEBUG("Invoking dsGetVideoDevice with index: %d", index);
        ret = dsGetVideoDevice(index, &handle);
        UT_LOG_DEBUG("Return status: %d, Handle: %ld", ret, handle);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetVideoDevice failed with status: %d", ret);
            UT_LOG_DEBUG("Invoking dsVideoDeviceTerm");
            dsVideoDeviceTerm();
            return;
        }

        UT_LOG_DEBUG("Invoking dsGetHDRCapabilities with handle: %ld", handle);
        ret = dsGetHDRCapabilities(handle, &capabilities);
        UT_LOG_DEBUG("Return status: %d, Capabilities: %d", ret, capabilities);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);

        UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(capabilities, "VideoDevice/VideoDevice0/HDRCapabilities");
    }
    UT_LOG_DEBUG("Invoking dsVideoDeviceTerm");
    ret = dsVideoDeviceTerm();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to verify the HDR capabilities of the video device source
*
* In this test, the HDR capabilities of the video device source are retrieved and validated. The test ensures that the dsGetHDRCapabilities function works as expected and returns the correct HDR capabilities for each video device.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 003@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoDevice_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoDevice_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoDevice_GetHDRCapabilities_source(void)
{
    gTestID = 3;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;
    intptr_t handle = 0;
    int capabilities = 0;

    UT_LOG_DEBUG("Invoking dsVideoDeviceInit");
    ret = dsVideoDeviceInit();
    UT_LOG_DEBUG("dsVideoDeviceInit returned %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for(int index = 0; index < MAX_DEVICES; index++)
    {
        UT_LOG_DEBUG("Invoking dsGetVideoDevice with index %d", index);
        ret = dsGetVideoDevice(index, &handle);
        UT_LOG_DEBUG("dsGetVideoDevice returned handle %ld and status %d", handle, ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if(ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetVideoDevice failed with error %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsGetHDRCapabilities with handle %ld", handle);
        ret = dsGetHDRCapabilities(handle, &capabilities);
        UT_LOG_DEBUG("dsGetHDRCapabilities returned capabilities %d and status %d", capabilities, ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);

        UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(capabilities, "VideoDevice/VideoDevice0/HDRCapabilities");
    }
    UT_LOG_DEBUG("Invoking dsVideoDeviceTerm");
    ret = dsVideoDeviceTerm();
    UT_LOG_DEBUG("dsVideoDeviceTerm returned %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test checks the functionality of getting supported video coding formats for a sink device
*
* This test initializes the video device, gets the video device for each index, checks the supported video coding formats for each device and finally terminates the video device. The test ensures that all the API calls return the expected status and the supported video coding formats are as expected.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 004@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoDevice_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoDevice_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoDevice_GetSupportedVideoCodingFormats_sink(void)
{
    gTestID = 4;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t retStatus;
    intptr_t handle;
    unsigned int supported_formats;

    UT_LOG_DEBUG("Invoking dsVideoDeviceInit()");
    retStatus = dsVideoDeviceInit();
    UT_LOG_DEBUG("Return status: %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    for(int index = 0; index < MAX_DEVICES; index++)
    {
        UT_LOG_DEBUG("Invoking dsGetVideoDevice() with index: %d", index);
        retStatus = dsGetVideoDevice(index, &handle);
        UT_LOG_DEBUG("Return status: %d, Handle: %ld", retStatus, handle);
        UT_ASSERT_EQUAL(retStatus, dsERR_NONE);
        UT_ASSERT_PTR_NOT_NULL(handle);
        if(retStatus != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetVideoDevice failed with error %d", retStatus);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsGetSupportedVideoCodingFormats() with handle: %ld", handle);
        retStatus = dsGetSupportedVideoCodingFormats(handle, &supported_formats);
        UT_LOG_DEBUG("Return status: %d, Supported formats: %u", retStatus, supported_formats);
        UT_ASSERT_EQUAL(retStatus, dsERR_NONE);

        UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(supported_formats, "VideoDevice/VideoDevice0/SupportedVideoCodingFormats");
    }
    UT_LOG_DEBUG("Invoking dsVideoDeviceTerm()");
    retStatus = dsVideoDeviceTerm();
    UT_LOG_DEBUG("Return status: %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test checks the functionality of getting supported video coding formats from a video device
*
* This test initializes a video device, retrieves the handle of the device, and then checks if the device supports certain video coding formats. The test is designed to ensure that the video device correctly identifies the supported video coding formats.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 005@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoDevice_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoDevice_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoDevice_GetSupportedVideoCodingFormats_source(void)
{
    static int gTestID = 5;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;
    intptr_t handle = 0;
    unsigned int supported_formats = 0;

    UT_LOG_DEBUG("Invoking dsVideoDeviceInit");
    ret = dsVideoDeviceInit();
    UT_LOG_DEBUG("dsVideoDeviceInit returned %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for(int index = 0; index < MAX_DEVICES; index++)
    {
        UT_LOG_DEBUG("Invoking dsGetVideoDevice with index %d", index);
        ret = dsGetVideoDevice(index, &handle);
        UT_LOG_DEBUG("dsGetVideoDevice returned handle %ld and status %d", handle, ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_ASSERT_PTR_NOT_NULL(handle);
        if(ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetVideoDevice failed with error %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsGetSupportedVideoCodingFormats with handle %ld", handle);
        ret = dsGetSupportedVideoCodingFormats(handle, &supported_formats);
        UT_LOG_DEBUG("dsGetSupportedVideoCodingFormats returned supported_formats %u and status %d", supported_formats, ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);

        UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(supported_formats, "VideoDevice/VideoDevice0/SupportedVideoCodingFormats");
    }
    UT_LOG_DEBUG("Invoking dsVideoDeviceTerm");
    ret = dsVideoDeviceTerm();
    UT_LOG_DEBUG("dsVideoDeviceTerm returned %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test for getting video codec information from a source
*
* This test verifies if the dsGetVideoCodecInfo function can successfully retrieve video codec information from a source. It checks if the function returns the correct status and if the retrieved information matches the expected values.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 006@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoDevice_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoDevice_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoDevice_GetVideoCodecInfo_source(void)
{
    gTestID = 6;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t retStatus;
    intptr_t handle;
    dsVideoCodecInfo_t info;
    dsVideoCodingFormat_t codec = dsVIDEO_CODEC_MPEGHPART2;
    int j = 1;

    UT_LOG_DEBUG("Invoking dsVideoDeviceInit");
    retStatus = dsVideoDeviceInit();
    UT_LOG_DEBUG("dsVideoDeviceInit return status: %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    for(int index = 0; index < MAX_DEVICES; index++)
    {
        UT_LOG_DEBUG("Invoking dsGetVideoDevice with index: %d", index);
        retStatus = dsGetVideoDevice(index, &handle);
        UT_ASSERT_EQUAL(retStatus, dsERR_NONE);
        UT_LOG_DEBUG("dsGetVideoDevice return status: %d, handle: %ld", retStatus, handle);
        if(retStatus != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetVideoDevice failed with error %d", retStatus);
            continue;
        }

        for(codec = dsVIDEO_CODEC_MPEGHPART2 ; codec < dsVIDEO_CODEC_MAX; )
        {
            UT_LOG_DEBUG("Invoking dsGetVideoCodecInfo with handle: %ld, codec: %d", handle, codec);
            retStatus = dsGetVideoCodecInfo(handle, codec, &info);
            UT_ASSERT_EQUAL(retStatus, dsERR_NONE);
            UT_LOG_DEBUG("dsGetVideoCodecInfo return status: %d, num_entries: %d", retStatus, info.num_entries);

            UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(info.num_entries, "VideoDevice/VideoDevice0/VideoCodecInfo/num_entries");
            for(int i = 0; i < info.num_entries; i++)
            {
                UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(info.entries->profile,"VideoDevice/VideoDevice0/VideoCodecInfo/VideoCodec0/profile");
                UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(info.entries->level,"VideoDevice/VideoDevice0/VideoCodecInfo/VideoCodec0/level");
            }
            codec = (0x01 << (j++));
        }
    }
    UT_LOG_DEBUG("Invoking dsVideoDeviceTerm");
    retStatus = dsVideoDeviceTerm();
    UT_LOG_DEBUG("dsVideoDeviceTerm return status: %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to verify the setting and getting of display framerate for dsVideoDevice
*
* This test case is designed to validate the functionality of dsSetDisplayframerate and dsGetCurrentDisplayframerate APIs.
* The test involves setting a display framerate for a video device and then getting the current display framerate to verify if the set value is correctly retrieved.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 007@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoDevice_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoDevice_L2_Low-Level_TestSpecification.md)
*/
void test_l2_dsVideoDevice_SetAndVerifyDisplayframerate_sink(void)
{
    gTestID = 7;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    char getframerate[50] = {0};
    ut_kvp_status_t status = {0};
    int count = 0;
    ut_kvp_instance_t *pInstance = NULL;
    char buffer[80];
    char result_kvp[UT_KVP_MAX_ELEMENT_SIZE]={0};

    UT_LOG_DEBUG("Invoking dsVideoDeviceInit");
    ret = dsVideoDeviceInit();
    UT_LOG_DEBUG("dsVideoDeviceInit return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for(int index = 0; index < MAX_DEVICES; index++)
    {
        UT_LOG_DEBUG("Invoking dsGetVideoDevice with index :%d",index);
        ret = dsGetVideoDevice(index, &handle);
        UT_LOG_DEBUG("dsGetVideoDevice return status: %d, handle: %ld", ret, handle);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if(ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetVideoDevice failed with error %d", ret);
            continue;
        }

        //Read framerate from config file
        pInstance = ut_kvp_profile_getInstance();
        count = ut_kvp_getListCount(pInstance,"VideoDevice/VideoDevice0/SupportedDisplayframerate");
        for (int i=0;i<count;i++)
        {
            sprintf(buffer, "VideoDevice/VideoDevice0/SupportedDisplayframerate/%d", i);
            status = ut_kvp_getStringField(pInstance, buffer, result_kvp, UT_KVP_MAX_ELEMENT_SIZE);
            UT_ASSERT(status == UT_KVP_STATUS_SUCCESS );

            UT_LOG_DEBUG("Invoking dsSetDisplayframerate with handle: %ld", handle);
            ret = dsSetDisplayframerate(handle, result_kvp);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            UT_LOG_DEBUG("dsSetDisplayframerate return status: %d", ret);
            if(ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsGetVideoDevice failed with error %d", ret);
                continue;
            }

            UT_LOG_DEBUG("Invoking dsGetCurrentDisplayframerate with handle: %ld", handle);
            ret = dsGetCurrentDisplayframerate(handle, getframerate);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            UT_ASSERT_STRING_EQUAL(result_kvp, getframerate);
            UT_LOG_DEBUG("dsGetCurrentDisplayframerate return status: %d, framerate: %s", ret, getframerate);
        }
    }
    UT_LOG_DEBUG("Invoking dsVideoDeviceTerm");
    ret = dsVideoDeviceTerm();
    UT_LOG_DEBUG("dsVideoDeviceTerm return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main tests for this module
 *
 * @return int - 0 on success, otherwise failure
 */

int test_dsVideoDevice_l2_register(void)
{
    // Create the test suite
    pSuite = UT_add_suite("[L2 dsVideoDevice]", NULL, NULL);
    if (pSuite == NULL)
    {
        return -1;
    }
    // List of test function names and strings

    UT_add_test( pSuite, "l2_dsVideoDevice_SetAndGetDFC_source", test_l2_dsVideoDevice_SetAndGetDFC_source);
    UT_add_test( pSuite, "l2_dsVideoDevice_GetHDRCapabilities_sink", test_l2_dsVideoDevice_GetHDRCapabilities_sink);
    UT_add_test( pSuite, "l2_dsVideoDevice_GetHDRCapabilities_source", test_l2_dsVideoDevice_GetHDRCapabilities_source);
    UT_add_test( pSuite, "l2_dsVideoDevice_GetSupportedVideoCodingFormats_sink", test_l2_dsVideoDevice_GetSupportedVideoCodingFormats_sink);
    UT_add_test( pSuite, "l2_dsVideoDevice_GetSupportedVideoCodingFormats_source", test_l2_dsVideoDevice_GetSupportedVideoCodingFormats_source);
    UT_add_test( pSuite, "l2_dsVideoDevice_GetVideoCodecInfo_source", test_l2_dsVideoDevice_GetVideoCodecInfo_source);
    UT_add_test( pSuite, "l2_dsVideoDevice_SetAndVerifyDisplayframerate_sink", test_l2_dsVideoDevice_SetAndVerifyDisplayframerate_sink);

    return 0;
}