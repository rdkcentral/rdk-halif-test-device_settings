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
* @file test_l2_dsVideoPort.c
* @page dsVideoPort Level 2 Tests
*
* ## Module's Role
* This module includes Level 2 functional tests (success and failure scenarios).
* This is to ensure that the dsVideoPort APIs meet the requirements across all vendors.
*
* **Pre-Conditions:**  None@n
* **Dependencies:** None@n
*
* Ref to API Definition specification documentation : [dsVideoPort_halSpec.md](../../docs/pages/dsVideoPort_halSpec.md)
*/

#include <ut.h>
#include <ut_log.h>
#include <ut_kvp_profile.h>
#include "dsVideoPort.h"

static int gTestGroup = 2;
static int gTestID = 1;

/**
* @brief This test aims to enable disabled video ports and verify their status
*
* In this test, we initialize the video port, get the video port for each type, check if it's enabled. If not, we enable it and verify if it's enabled successfully.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 001@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_EnableDisabledVideoPorts_sink(void)
{
    gTestID = 1;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    bool enabled;

    UT_LOG_DEBUG("Invoking dsVideoPortInit()");
    ret = dsVideoPortInit();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (dsVideoPortType_t type = dsVIDEOPORT_TYPE_RF; type < dsVIDEOPORT_TYPE_MAX; type++)
    {
        UT_LOG_DEBUG("Invoking dsGetVideoPort() with type: %d and index: 0", type);
        ret = dsGetVideoPort(type, 0, &handle);
        UT_LOG_DEBUG("Return status: %d, Handle: %ld", ret, handle);
		UT_ASSERT_EQUAL(ret, dsERR_NONE);
		if (ret != dsERR_NONE)
		{
			UT_LOG_ERROR("dsGetVideoPort failed with ret: %d", ret);
            continue;
		}

        UT_LOG_DEBUG("Invoking dsIsVideoPortEnabled() with handle: %ld", handle);
        ret = dsIsVideoPortEnabled(handle, &enabled);
        UT_LOG_DEBUG("Return status: %d, Enabled: %d", ret, enabled);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);

        if (!enabled)
        {
            UT_LOG_DEBUG("Invoking dsEnableVideoPort() with handle: %ld and enabled: true", handle);
            ret = dsEnableVideoPort(handle, true);
            UT_LOG_DEBUG("Return status: %d", ret);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);

            UT_LOG_DEBUG("Invoking dsIsVideoPortEnabled() with handle: %ld", handle);
            ret = dsIsVideoPortEnabled(handle, &enabled);
            UT_LOG_DEBUG("Return status: %d, Enabled: %d", ret, enabled);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            UT_ASSERT_EQUAL(enabled, true);
        }
    }

    UT_LOG_DEBUG("Invoking dsVideoPortTerm()");
    ret = dsVideoPortTerm();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to enable the disabled video ports and verify their status
*
* In this test, the dsVideoPortInit function is invoked to initialize the video port. Then, for each type of video port, the dsGetVideoPort function is invoked to get the video port. If the video port is obtained successfully, the dsIsVideoPortEnabled function is invoked to check if the video port is enabled. If the video port is not enabled, the dsEnableVideoPort function is invoked to enable the video port and the status is verified again. Finally, the dsVideoPortTerm function is invoked to terminate the video port.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 002@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_EnableDisabledVideoPorts_source(void)
{
    dsError_t ret = dsERR_NONE;
    intptr_t handle = 0;
    bool enabled = false;
    gTestID = 2;

    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    UT_LOG_DEBUG("Invoking dsVideoPortInit");
    ret = dsVideoPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);
    UT_LOG_DEBUG("dsVideoPortInit returned %d", ret);

    for (dsVideoPortType_t type = dsVIDEOPORT_TYPE_RF; type < dsVIDEOPORT_TYPE_MAX; type++)
    {
        UT_LOG_DEBUG("Invoking dsGetVideoPort with type %d and index 0", type);
        ret = dsGetVideoPort(type, 0, &handle);
        UT_LOG_DEBUG("dsGetVideoPort returned handle %ld and status %d", handle, ret);
		UT_ASSERT_EQUAL(ret, dsERR_NONE);
		if (ret != dsERR_NONE)
		{
			UT_LOG_ERROR("dsGetVideoPort failed with ret: %d", ret);
            continue;
		}

        UT_LOG_DEBUG("Invoking dsIsVideoPortEnabled with handle %ld", handle);
        ret = dsIsVideoPortEnabled(handle, &enabled);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_LOG_DEBUG("dsIsVideoPortEnabled returned enabled %d and status %d", enabled, ret);

        if (!enabled)
        {
            UT_LOG_DEBUG("Invoking dsEnableVideoPort with handle %ld and enabled true", handle);
            ret = dsEnableVideoPort(handle, true);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            UT_LOG_DEBUG("dsEnableVideoPort returned status %d", ret);

            UT_LOG_DEBUG("Invoking dsIsVideoPortEnabled with handle %ld", handle);
            ret = dsIsVideoPortEnabled(handle, &enabled);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            UT_ASSERT_EQUAL(enabled, true);
            UT_LOG_DEBUG("dsIsVideoPortEnabled returned enabled %d and status %d", enabled, ret);
        }
    }

    UT_LOG_DEBUG("Invoking dsVideoPortTerm");
    ret = dsVideoPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);
    UT_LOG_DEBUG("dsVideoPortTerm returned %d", ret);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test verifies the display and port status of the sink in the L2 dsVideoPort
*
* This test function initializes the video port, gets the video port for each type, checks if the display is connected and if the video port is active, and finally terminates the video port. The test is designed to ensure that the video port functionalities are working as expected.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 003@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_VerifyDisplayAndPortStatus_sink(void)
{
    gTestID = 3;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    bool connected, active;
    dsVideoPortType_t type;
    int index = 0;

    UT_LOG_DEBUG("Invoking dsVideoPortInit");
    ret = dsVideoPortInit();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (type = dsVIDEOPORT_TYPE_RF; type < dsVIDEOPORT_TYPE_MAX; type++) {
        UT_LOG_DEBUG("Invoking dsGetVideoPort with type: %d and index: %d", type, index);
        ret = dsGetVideoPort(type, index, &handle);
        UT_LOG_DEBUG("Return status: %d, Handle: %ld", ret, handle);
		UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
		{
			UT_LOG_ERROR("dsGetVideoPort failed with ret: %d", ret);
            continue;
		}

        UT_LOG_DEBUG("Invoking dsIsDisplayConnected with handle: %ld", handle);
        ret = dsIsDisplayConnected(handle, &connected);
        UT_LOG_DEBUG("Return status: %d, Connected: %d", ret, connected);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_ASSERT_EQUAL(connected, false);

        UT_LOG_DEBUG("Invoking dsIsVideoPortActive with handle: %ld", handle);
        ret = dsIsVideoPortActive(handle, &active);
        UT_LOG_DEBUG("Return status: %d, Active: %d", ret, active);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_ASSERT_EQUAL(active, false);
    }

    UT_LOG_DEBUG("Invoking dsVideoPortTerm");
    ret = dsVideoPortTerm();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to verify the display and port status of the L2 dsVideoPort
*
* This test verifies the display and port status of the L2 dsVideoPort. It checks if the display is connected and if the video port is active. This is important to ensure the correct functioning of the video port.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 004@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_VerifyDisplayAndPortStatus_source(void)
{
    static int gTestID = 4;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    bool connected, active;
    dsVideoPortType_t type;

    UT_LOG_DEBUG("Invoking dsVideoPortInit");
    ret = dsVideoPortInit();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (type = dsVIDEOPORT_TYPE_RF; type < dsVIDEOPORT_TYPE_MAX; type++)
    {
        UT_LOG_DEBUG("Invoking dsGetVideoPort with type: %d and index: 0", type);
        ret = dsGetVideoPort(type, 0, &handle);
        UT_LOG_DEBUG("Handle: %ld, Return status: %d", handle, ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
		if (ret != dsERR_NONE)
		{
			UT_LOG_ERROR("dsGetVideoPort failed with ret: %d", ret);
            continue;
		}

        UT_LOG_DEBUG("Invoking dsIsDisplayConnected with handle: %ld", handle);
        ret = dsIsDisplayConnected(handle, &connected);
        UT_LOG_DEBUG("Connected: %d, Return status: %d", connected, ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_ASSERT_EQUAL(connected, false);

        UT_LOG_DEBUG("Invoking dsIsVideoPortActive with handle: %ld", handle);
        ret = dsIsVideoPortActive(handle, &active);
        UT_LOG_DEBUG("Active: %d, Return status: %d", active, ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_ASSERT_EQUAL(active, false);
    }

    UT_LOG_DEBUG("Invoking dsVideoPortTerm");
    ret = dsVideoPortTerm();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to retrieve and verify the surround mode capabilities of the video port sink
*
* In this test, the dsVideoPortInit() function is invoked to initialize the video port. Then, the dsGetVideoPort() function is called with dsVIDEOPORT_TYPE_INTERNAL and index 0 to get the video port. The dsIsDisplaySurround() function is then invoked with the obtained handle to check if the display is in surround mode. The result is then compared with the expected value. Finally, the dsVideoPortTerm() function is invoked to terminate the video port.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 005@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_RetrieveAndVerifySurroundModeCapabilities_sink(void)
{
    gTestID = 5;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    bool surround;
    bool checkValue;

    UT_LOG_DEBUG("Invoking dsVideoPortInit()");
    ret = dsVideoPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);
    UT_LOG_DEBUG("dsVideoPortInit() returned %d", ret);

    UT_LOG_DEBUG("Invoking dsGetVideoPort() with dsVIDEOPORT_TYPE_INTERNAL and index 0");
    ret = dsGetVideoPort(dsVIDEOPORT_TYPE_INTERNAL, 0, &handle);
    UT_LOG_DEBUG("dsGetVideoPort() returned %d and handle %ld", ret, handle);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
	if (ret != dsERR_NONE)
	{
		UT_LOG_ERROR("dsGetVideoPort failed with ret: %d", ret);
        ret = dsVideoPortTerm();
        UT_LOG_DEBUG("dsVideoPortTerm returned %d", ret);
        return;
	}

    UT_LOG_DEBUG("Invoking dsIsDisplaySurround() with handle %ld", handle);
    ret = dsIsDisplaySurround(handle, &surround);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    UT_LOG_DEBUG("dsIsDisplaySurround() returned %d and surround %d", ret, surround);

    checkValue = surround;
    UT_ASSERT_KVP_EQUAL_PROFILE_BOOL(checkValue, "Ports/1/Display_surrond");

    UT_LOG_DEBUG("Invoking dsVideoPortTerm()");
    ret = dsVideoPortTerm();
	UT_LOG_DEBUG("dsVideoPortTerm() returned %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test verifies the display surround source in L2 dsVideoPort
*
* This test function initializes the video port, gets the video port with HDMI and index 0, checks if the display is in surround mode,
* if yes, it gets the surround mode and compares it with the expected value. Finally, it terminates the video port.
* The purpose of this test is to ensure that the display surround source is correctly set and retrieved in the L2 dsVideoPort.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 006@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_VerifyDisplaySurround_source(void)
{
    gTestID = 6;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    bool surround;
    int surround_mode;

    UT_LOG_DEBUG("Invoking dsVideoPortInit()");
    ret = dsVideoPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsGetVideoPort() with HDMI and index 0");
    ret = dsGetVideoPort(dsVIDEOPORT_TYPE_HDMI, 0, &handle);
    UT_LOG_DEBUG("Handle: %ld and return status: %d", handle, ret);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
	if (ret != dsERR_NONE)
	{
		UT_LOG_ERROR("dsGetVideoPort failed with ret: %d", ret);
        ret = dsVideoPortTerm();
        UT_LOG_DEBUG("dsVideoPortTerm returned %d", ret);
        return;
	}

    UT_LOG_DEBUG("Invoking dsIsDisplaySurround() with valid handle");
    ret = dsIsDisplaySurround(handle, &surround);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    UT_LOG_DEBUG("Surround: %d and return status: %d", surround, ret);

    if (surround) {
        UT_LOG_DEBUG("Invoking dsGetSurroundMode() with valid handle");
        ret = dsGetSurroundMode(handle, &surround_mode);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_LOG_DEBUG("Surround mode: %d and return status: %d", surround_mode, ret);

        UT_ASSERT_KVP_EQUAL_PROFILE_BOOL(surround, "Ports/1/Display_surrond");
    }

    UT_LOG_DEBUG("Invoking dsVideoPortTerm()");
    ret = dsVideoPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test for setting and getting the resolution of a video source
*
* This test checks if the dsSetResolution and dsGetResolution functions work as expected. It sets the resolution of a video source and then gets the resolution to verify if the set resolution is correctly applied. This is done for all possible combinations of pixel resolution, aspect ratio, stereoscopic mode, and frame rate.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 007@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_SetAndGetResolution_source(void)
{
    gTestID = 7;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    dsVideoPortResolution_t setResolution, getResolution;
    dsVideoPortType_t type;

    UT_LOG_DEBUG("Invoking dsVideoPortInit()");
    ret = dsVideoPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (type = dsVIDEOPORT_TYPE_RF; type < dsVIDEOPORT_TYPE_MAX; type++)
    {
        UT_LOG_DEBUG("Invoking dsGetVideoPort() with type: %d and index: 0", type);
        ret = dsGetVideoPort(type, 0, &handle);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
		if (ret != dsERR_NONE)
		{
			UT_LOG_ERROR("dsGetVideoPort failed with ret: %d", ret);
            continue;
		}

        for (int i = dsVIDEO_PIXELRES_720x480; i < dsVIDEO_PIXELRES_MAX; i++)
        {
            for (int j = dsVIDEO_ASPECT_RATIO_4x3; j < dsVIDEO_ASPECT_RATIO_MAX; j++)
            {
                for (int k = dsVIDEO_SSMODE_UNKNOWN; k < dsVIDEO_SSMODE_MAX; k++)
                {
                    for (int l = dsVIDEO_FRAMERATE_UNKNOWN; l < dsVIDEO_FRAMERATE_MAX; l++)
                    {
                        strcpy(setResolution.name, "TestResolution");
                        setResolution.pixelResolution = i;
                        setResolution.aspectRatio = j;
                        setResolution.stereoScopicMode = k;
                        setResolution.frameRate = l;
                        setResolution.interlaced = false;

                        UT_LOG_DEBUG("Invoking dsSetResolution() with handle and setResolution");
                        ret = dsSetResolution(handle, &setResolution);
                        UT_ASSERT_EQUAL(ret, dsERR_NONE);
                        if (ret != dsERR_NONE)
                        {
                            UT_LOG_ERROR("dsSetResolution() failed with status: %d", ret);
                            continue;
                        }

                        UT_LOG_DEBUG("Invoking dsGetResolution() with handle and getResolution");
                        ret = dsGetResolution(handle, &getResolution);
                        UT_ASSERT_EQUAL(ret, dsERR_NONE);
                        if (ret != dsERR_NONE)
                        {
                            UT_LOG_ERROR("dsGetResolution() failed with status: %d", ret);
                            continue;
                        }

                        UT_LOG_DEBUG("Comparing setResolution and getResolution");
                        UT_ASSERT_EQUAL(setResolution.pixelResolution, getResolution.pixelResolution);
                        UT_ASSERT_EQUAL(setResolution.aspectRatio, getResolution.aspectRatio);
                        UT_ASSERT_EQUAL(setResolution.stereoScopicMode, getResolution.stereoScopicMode);
                        UT_ASSERT_EQUAL(setResolution.frameRate, getResolution.frameRate);
                        UT_ASSERT_EQUAL(setResolution.interlaced, getResolution.interlaced);
				    }
                }
            }
        }
    }

    UT_LOG_DEBUG("Invoking dsVideoPortTerm()");
    ret = dsVideoPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to verify the supported TV resolutions for a sink
*
* This test verifies if the dsVideoPort API correctly identifies and returns the supported TV resolutions for a sink. The test is crucial to ensure the correct functioning of the video port in different resolution settings.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 008@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_VerifySupportedTvResolutions_sink(void)
{
    gTestID = 8;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t retStatus;
    intptr_t handle;
    int resolutions;

    UT_LOG_DEBUG("Invoking dsVideoPortInit");
    retStatus = dsVideoPortInit();
    UT_LOG_DEBUG("Returned status: %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsGetVideoPort with type: dsVIDEOPORT_TYPE_INTERNAL and index: 0");
    retStatus = dsGetVideoPort(dsVIDEOPORT_TYPE_INTERNAL, 0, &handle);
    UT_LOG_DEBUG("Returned status: %d, handle: %ld", retStatus, handle);
    UT_ASSERT_EQUAL(retStatus, dsERR_NONE);
    if (retStatus != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetVideoPort failed with ret: %d", retStatus);
        retStatus = dsVideoPortTerm();
        UT_LOG_DEBUG("dsVideoPortTerm returned %d", retStatus);
        return;
    }

    UT_LOG_DEBUG("Invoking dsSupportedTvResolutions with handle: %ld", handle);
    retStatus = dsSupportedTvResolutions(handle, &resolutions);
    UT_LOG_DEBUG("Returned status: %d, resolutions: %d", retStatus, resolutions);
    UT_ASSERT_EQUAL(retStatus, dsERR_NONE);
    UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(resolutions, "Ports/1/Supported_tv_resolutions_capabilities");

    UT_LOG_DEBUG("Invoking dsVideoPortTerm");
    retStatus = dsVideoPortTerm();
    UT_LOG_DEBUG("Returned status: %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to verify the supported TV resolutions for a given video source
*
* This test case verifies the supported TV resolutions for a given video source by invoking the dsVideoPortInit, dsGetVideoPort, dsSupportedTvResolutions, and dsVideoPortTerm functions. The test ensures that these functions return the expected results and that the supported TV resolutions match the expected capabilities.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 009@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_VerifySupportedTvResolutions_source(void)
{
    gTestID = 9;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    int resolutions;

    UT_LOG_DEBUG("Invoking dsVideoPortInit");
    ret = dsVideoPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);
    UT_LOG_DEBUG("Return status: %d", ret);

    UT_LOG_DEBUG("Invoking dsGetVideoPort with type=dsVIDEOPORT_TYPE_HDMI and index=1");
    ret = dsGetVideoPort(dsVIDEOPORT_TYPE_HDMI, 1, &handle);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    UT_LOG_DEBUG("Return status: %d, handle: %ld", ret, handle);
    if (ret != dsERR_NONE)
    {
		UT_LOG_ERROR("dsGetVideoPort failed with ret: %d", ret);
        ret = dsVideoPortTerm();
        UT_LOG_DEBUG("dsVideoPortTerm returned %d", ret);
        return;
    }

    UT_LOG_DEBUG("Invoking dsSupportedTvResolutions with handle=%ld", handle);
    ret = dsSupportedTvResolutions(handle, &resolutions);
    UT_LOG_DEBUG("Return status: %d, resolutions: %d", ret, resolutions);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(resolutions, "Ports/1/Supported_tv_resolutions_capabilities");

    UT_LOG_DEBUG("Invoking dsVideoPortTerm");
    ret = dsVideoPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);
    UT_LOG_DEBUG("Return status: %d", ret);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test for getting HDR capabilities of the sink
*
* This test verifies if the dsGetTVHDRCapabilities() function can successfully get the HDR capabilities of the sink. The test first initializes the video port, gets the video port with dsVIDEOPORT_TYPE_INTERNAL and index 0, then gets the HDR capabilities. It asserts that all these operations return dsERR_NONE, and that the obtained capabilities match the expected value.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 010@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_GetHDRCapabilities_sink(void)
{
    gTestID = 10;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    int capabilities;

    UT_LOG_DEBUG("Invoking dsVideoPortInit()");
    ret = dsVideoPortInit();
    UT_LOG_DEBUG("Returned status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsGetVideoPort() with dsVIDEOPORT_TYPE_INTERNAL and index 0");
    ret = dsGetVideoPort(dsVIDEOPORT_TYPE_INTERNAL, 0, &handle);
    UT_LOG_DEBUG("Returned status: %d, handle: %ld", ret, handle);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
	if (ret != dsERR_NONE)
    {
		UT_LOG_ERROR("dsGetVideoPort failed with ret: %d", ret);
        ret = dsVideoPortTerm();
        UT_LOG_DEBUG("dsVideoPortTerm returned %d", ret);
        return;
    }

    UT_LOG_DEBUG("Invoking dsGetTVHDRCapabilities() with handle: %ld", handle);
    ret = dsGetTVHDRCapabilities(handle, &capabilities);
    UT_LOG_DEBUG("Returned status: %d, capabilities: %d", ret, capabilities);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);

    UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(capabilities, "Ports/1/hdr_capabilities");

    UT_LOG_DEBUG("Invoking dsVideoPortTerm()");
    ret = dsVideoPortTerm();
    UT_LOG_DEBUG("Returned status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to verify the function dsVideoPort_GetHDRCapabilities for source
*
* This test verifies if the function dsVideoPort_GetHDRCapabilities correctly retrieves the HDR capabilities of the source. The test first initializes the video port, then gets the video port with type as HDMI, and finally retrieves the HDR capabilities. The obtained capabilities are then compared with the expected values.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 011@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_GetHDRCapabilities_source(void)
{
    gTestID = 11;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;
    intptr_t handle = 0;
    int capabilities = 0;

    UT_LOG_DEBUG("Invoking dsVideoPortInit");
    ret = dsVideoPortInit();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsGetVideoPort with type as dsVIDEOPORT_TYPE_HDMI");
    ret = dsGetVideoPort(dsVIDEOPORT_TYPE_HDMI, 0, &handle);
    UT_LOG_DEBUG("Return status: %d, Handle: %ld", ret, handle);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
	if (ret != dsERR_NONE)
    {
		UT_LOG_ERROR("dsGetVideoPort failed with ret: %d", ret);
        ret = dsVideoPortTerm();
        UT_LOG_DEBUG("dsVideoPortTerm returned %d", ret);
        return;
    }

    UT_LOG_DEBUG("Invoking dsGetTVHDRCapabilities with handle obtained from previous step");
    ret = dsGetTVHDRCapabilities(handle, &capabilities);
    UT_LOG_DEBUG("Return status: %d, Capabilities: %d", ret, capabilities);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);

    UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(capabilities, "Ports/1/hdr_capabilities");

    UT_LOG_DEBUG("Invoking dsVideoPortTerm");
    ret = dsVideoPortTerm();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test for setting and getting the ForceDisable4KSupport for a video port
*
* This test verifies the functionality of the dsSetForceDisable4KSupport() and dsGetForceDisable4KSupport() APIs.
* It checks if the APIs are able to correctly set and retrieve the ForceDisable4KSupport status for a video port.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 012@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_SetAndGetForceDisable4KSupport_sink(void)
{
    gTestID = 12;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    bool disable;

    UT_LOG_DEBUG("Invoking dsVideoPortInit()");
    ret = dsVideoPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);
    UT_LOG_DEBUG("dsVideoPortInit() returned %d", ret);

    for (int type = dsVIDEOPORT_TYPE_RF; type < dsVIDEOPORT_TYPE_MAX; type++)
    {
        UT_LOG_DEBUG("Invoking dsGetVideoPort() with type: %d and index: 0", type);
        ret = dsGetVideoPort(type, 0, &handle);
        UT_LOG_DEBUG("Handle: %ld, Return status: %d", handle, ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
		if (ret != dsERR_NONE)
        {
		    UT_LOG_ERROR("dsGetVideoPort failed with ret: %d", ret);
            continue;
        }
        for (int i = 0; i < 2; i++) {
	        disable = (i == 0) ? true : false;
            UT_LOG_DEBUG("Invoking dsSetForceDisable4KSupport() with handle: %ld, disable: %d", handle, disable);
            ret = dsSetForceDisable4KSupport(handle, disable);
		    UT_ASSERT_EQUAL(ret, dsERR_NONE);
            UT_LOG_DEBUG("Return status: %d", ret);

            bool getDisable;
            UT_LOG_DEBUG("Invoking dsGetForceDisable4KSupport() with handle: %ld", handle);
            ret = dsGetForceDisable4KSupport(handle, &getDisable);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            UT_ASSERT_EQUAL(getDisable, disable);
            UT_LOG_DEBUG("Disable: %d, Return status: %d", disable, ret);
        }
    }

    UT_LOG_DEBUG("Invoking dsVideoPortTerm()");
    ret = dsVideoPortTerm();
    UT_LOG_DEBUG("dsVideoPortTerm() returned %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to validate the setting and getting of ForceDisable4KSupport in dsVideoPort
*
* This test function tests the setting and getting of ForceDisable4KSupport in dsVideoPort. It first initializes the video port, then gets the video port with valid parameters. It then sets the ForceDisable4KSupport and gets the same to validate if the set value is correctly retrieved. The test is performed for both true and false values of ForceDisable4KSupport. Finally, it terminates the video port. The test is designed to ensure the correct functioning of the dsSetForceDisable4KSupport and dsGetForceDisable4KSupport functions.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 013@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_SetAndGetForceDisable4KSupport_source(void)
{
    gTestID = 13;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    bool disable;

    UT_LOG_DEBUG("Invoking dsVideoPortInit()");
    ret = dsVideoPortInit();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (int type = dsVIDEOPORT_TYPE_RF; type < dsVIDEOPORT_TYPE_MAX; type++)
    {
        UT_LOG_DEBUG("Invoking dsGetVideoPort() with type: %d and index: 0", type);
        ret = dsGetVideoPort(type, 0, &handle);
        UT_LOG_DEBUG("Handle: %ld, Return status: %d", handle, ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
		if (ret != dsERR_NONE)
        {
		    UT_LOG_ERROR("dsGetVideoPort failed with ret: %d", ret);
            continue;
        }
        for (int i = 0; i < 2; i++) {
	        disable = (i == 0) ? true : false;
            UT_LOG_DEBUG("Invoking dsSetForceDisable4KSupport() with handle: %ld, disable: %d", handle, disable);
            ret = dsSetForceDisable4KSupport(handle, disable);
		    UT_ASSERT_EQUAL(ret, dsERR_NONE);
            UT_LOG_DEBUG("Return status: %d", ret);

            bool getDisable;
            UT_LOG_DEBUG("Invoking dsGetForceDisable4KSupport() with handle: %ld", handle);
            ret = dsGetForceDisable4KSupport(handle, &getDisable);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            UT_ASSERT_EQUAL(getDisable, disable);
            UT_LOG_DEBUG("Disable: %d, Return status: %d", disable, ret);
        }
    }

    UT_LOG_DEBUG("Invoking dsVideoPortTerm()");
    ret = dsVideoPortTerm();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test checks the HDCP status of the video port
*
* This test initializes the video port, gets the video port handle for each type, checks the HDCP status and finally terminates the video port. The test is designed to verify if the HDCP status is authenticated for each video port type.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 014@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_GetHDCPStatus_sink(void)
{
    gTestID = 14;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    dsHdcpStatus_t status;

    UT_LOG_DEBUG("Invoking dsVideoPortInit()");
    ret = dsVideoPortInit();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (int type = dsVIDEOPORT_TYPE_RF; type < dsVIDEOPORT_TYPE_MAX; type++)
    {
        UT_LOG_DEBUG("Invoking dsGetVideoPort with type: %d and index: 0", type);
        ret = dsGetVideoPort(type, 0, &handle);
        UT_LOG_DEBUG("Handle: %ld, Return status: %d", handle, ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
		if (ret != dsERR_NONE)
        {
		    UT_LOG_ERROR("dsGetVideoPort failed with ret: %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsGetHDCPStatus() with handle: %ld", handle);
        ret = dsGetHDCPStatus(handle, &status);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetHDCPStatus() failed with error: %d", ret);
            continue;
        }
        UT_LOG_DEBUG("Return status: %d, HDCP Status: %d", ret, status);
        UT_ASSERT_EQUAL(status, dsHDCP_STATUS_AUTHENTICATED);
        if (status != dsHDCP_STATUS_AUTHENTICATED) {
            UT_LOG_ERROR("HDCP status is not authenticated. Status: %d", status);
        }
    }

    UT_LOG_DEBUG("Invoking dsVideoPortTerm()");
    ret = dsVideoPortTerm();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test for getting HDCP status from a source
*
* This test is designed to verify the functionality of the dsGetHDCPStatus() API. It checks if the HDCP status can be successfully retrieved from a source. The test involves initializing the video port, getting the video port with valid parameters, getting the HDCP status with a valid handle, and finally terminating the video port. The test asserts that all these operations return no error and that the HDCP status is either unpowered or port disabled.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 015@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_GetHDCPStatus_source(void)
{
    gTestID = 15;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    dsHdcpStatus_t status;

    UT_LOG_DEBUG("Invoking dsVideoPortInit()");
    ret = dsVideoPortInit();
	UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (int i = dsVIDEOPORT_TYPE_RF; i < dsVIDEOPORT_TYPE_MAX; i++)
    {
        UT_LOG_DEBUG("Invoking dsGetVideoPort() with valid parameters");
        ret = dsGetVideoPort(i, 0, &handle);
        UT_LOG_DEBUG("Handle: %ld, Return status: %d", handle, ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
		if (ret != dsERR_NONE)
        {
		    UT_LOG_ERROR("dsGetVideoPort failed with ret: %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsGetHDCPStatus() with valid handle");
        ret = dsGetHDCPStatus(handle, &status);
		UT_ASSERT_EQUAL(ret, dsERR_NONE);

        UT_LOG_DEBUG("HDCP status: %d", status);
		UT_ASSERT_TRUE(status == dsHDCP_STATUS_UNPOWERED || status == dsHDCP_STATUS_PORTDISABLED);
        if (status != dsHDCP_STATUS_UNPOWERED || status != dsHDCP_STATUS_PORTDISABLED) {
            UT_LOG_ERROR("HDCP status is not unpowered or portdisabled. Status: %d", status);
        }
    }

    UT_LOG_DEBUG("Invoking dsVideoPortTerm()");
    ret = dsVideoPortTerm();
	UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to verify the HDCP Protocol Status for sink
*
* This test case verifies the HDCP Protocol Status for sink by invoking the dsVideoPortInit, dsGetVideoPort, dsGetHDCPProtocol and dsVideoPortTerm APIs. The HDCP protocol version obtained from the API is compared with the one retrieved from the yaml file.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 016@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_VerifyHDCPProtocolStatus_sink(void)
{
    gTestID = 16;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t retStatus;
    intptr_t handle;
    dsHdcpProtocolVersion_t protocolVersion;

    UT_LOG_DEBUG("Invoking dsVideoPortInit");
    retStatus = dsVideoPortInit();
    UT_LOG_DEBUG("Return status: %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsGetVideoPort with dsVIDEOPORT_TYPE_INTERNAL and index 0");
    retStatus = dsGetVideoPort(dsVIDEOPORT_TYPE_INTERNAL, 0, &handle);
    UT_LOG_DEBUG("Return status: %d, Handle: %ld", retStatus, handle);
    UT_ASSERT_EQUAL(retStatus, dsERR_NONE);
    if (retStatus != dsERR_NONE)
    {
	UT_LOG_ERROR("dsGetVideoPort failed with ret: %d", retStatus);
        retStatus = dsVideoPortTerm();
        UT_LOG_DEBUG("dsVideoPortTerm returned %d", retStatus);
        return;
    }

    UT_LOG_DEBUG("Invoking dsGetHDCPProtocol with handle: %ld", handle);
    retStatus = dsGetHDCPProtocol(handle, &protocolVersion);
    UT_LOG_DEBUG("Return status: %d, Protocol Version: %d", retStatus, protocolVersion);
    UT_ASSERT_EQUAL(retStatus, dsERR_NONE);
    UT_ASSERT_KVP_EQUAL_PROFILE_UINT8(protocolVersion, "Ports/1/hdcp_protocol_version");

    UT_LOG_DEBUG("Invoking dsVideoPortTerm");
    retStatus = dsVideoPortTerm();
    UT_LOG_DEBUG("Return status: %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test verifies the HDCP Protocol Status for a video source
*
* This test initializes the video port, gets the video port with HDMI as type and 0 as index, gets the HDCP protocol with the handle obtained from dsGetVideoPort, and finally terminates the video port. The test is designed to ensure the correct functioning of the HDCP protocol status retrieval for a video source.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 017@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_VerifyHDCPProtocolStatus_source(void)
{
    gTestID = 17;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    dsHdcpProtocolVersion_t protocolVersion;

    UT_LOG_DEBUG("Invoking dsVideoPortInit");
    ret = dsVideoPortInit();
	UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsGetVideoPort with dsVIDEOPORT_TYPE_HDMI as type and 0 as index");
    ret = dsGetVideoPort(dsVIDEOPORT_TYPE_HDMI, 0, &handle);
	UT_LOG_DEBUG("Handle: %ld, Return status: %d", handle, ret);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
	if (ret != dsERR_NONE)
    {
		UT_LOG_ERROR("dsGetVideoPort failed with ret: %d", ret);
        ret = dsVideoPortTerm();
        UT_LOG_DEBUG("dsVideoPortTerm returned %d", ret);
        return;
    }

    UT_LOG_DEBUG("Invoking dsGetHDCPProtocol with handle obtained from dsGetVideoPort");
    ret = dsGetHDCPProtocol(handle, &protocolVersion);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    UT_LOG_DEBUG("HDCP Protocol Version: %d, Return status: %d", protocolVersion, ret);
    UT_ASSERT_KVP_EQUAL_PROFILE_UINT8(protocolVersion, "Ports/1/hdcp_protocol_version");

    UT_LOG_DEBUG("Invoking dsVideoPortTerm");
    ret = dsVideoPortTerm();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to set and get the HDMI preference for a video port
*
* In this test, the HDMI preference for each type of video port is set and then retrieved to verify if the set operation was successful. This is done for all types of HDCP protocol versions. The test is important to ensure the correct functioning of the HDMI preference setting and getting operations for different types of video ports and HDCP protocol versions.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 018@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_SetAndGetHdmiPreference_sink(void)
{
    gTestID = 18;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    dsHdcpProtocolVersion_t hdcpCurrentProtocol, hdcpCurrentProtocolGet;
    dsVideoPortType_t type;
    int index = 0;

    UT_LOG_DEBUG("Invoking dsVideoPortInit");
    ret = dsVideoPortInit();
	UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (type = dsVIDEOPORT_TYPE_RF; type < dsVIDEOPORT_TYPE_MAX; type++)
    {
        UT_LOG_DEBUG("Invoking dsGetVideoPort with type: %d and index: %d", type, index);
        ret = dsGetVideoPort(type, index, &handle);
		UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetVideoPort failed with ret: %d", ret);
			continue;
        }

        for (hdcpCurrentProtocol = dsHDCP_VERSION_1X; hdcpCurrentProtocol < dsHDCP_VERSION_MAX; hdcpCurrentProtocol++)
        {
            UT_LOG_DEBUG("Invoking dsSetHdmiPreference with handle: %ld and hdcpCurrentProtocol: %d", handle, hdcpCurrentProtocol);
            ret = dsSetHdmiPreference(handle, &hdcpCurrentProtocol);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetHdmiPreference failed with error: %d", ret);
                continue;
            }

            UT_LOG_DEBUG("Invoking dsGetHdmiPreference with handle: %ld", handle);
            ret = dsGetHdmiPreference(handle, &hdcpCurrentProtocolGet);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsGetHdmiPreference failed with error: %d", ret);
                continue;
            }

            UT_LOG_DEBUG("HDCP protocol version set: %d, HDCP protocol version get: %d", hdcpCurrentProtocol, hdcpCurrentProtocolGet);
            UT_ASSERT_EQUAL(hdcpCurrentProtocol, hdcpCurrentProtocolGet);
        }
    }

    UT_LOG_DEBUG("Invoking dsVideoPortTerm");
    ret = dsVideoPortTerm();
	UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to validate the setting and getting of HDMI preference in dsVideoPort
*
* This test function tests the setting and getting of HDMI preference in dsVideoPort. It does this by initializing the video port, getting the video port with different types, setting the HDMI preference with different HDCP protocol versions, getting the HDMI preference and comparing the set and got HDCP protocol versions, and finally terminating the video port. The test is designed to ensure that the HDMI preference setting and getting functionalities are working as expected.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 019@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_SetAndGetHdmiPreference_source(void)
{
    gTestID = 19;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    dsHdcpProtocolVersion_t hdcpCurrentProtocol, hdcpCurrentProtocolGet;
    dsVideoPortType_t type;
    int index = 0;

    UT_LOG_DEBUG("Invoking dsVideoPortInit");
    ret = dsVideoPortInit();
	UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (type = dsVIDEOPORT_TYPE_RF; type < dsVIDEOPORT_TYPE_MAX; type++)
    {
        UT_LOG_DEBUG("Invoking dsGetVideoPort with type: %d and index: %d", type, index);
        ret = dsGetVideoPort(type, index, &handle);
		UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetVideoPort failed with error: %d", ret);
            continue;
        }

        for (hdcpCurrentProtocol = dsHDCP_VERSION_1X; hdcpCurrentProtocol < dsHDCP_VERSION_MAX; hdcpCurrentProtocol++)
        {
            UT_LOG_DEBUG("Invoking dsSetHdmiPreference with handle: %ld and hdcpCurrentProtocol: %d", handle, hdcpCurrentProtocol);
            ret = dsSetHdmiPreference(handle, &hdcpCurrentProtocol);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetHdmiPreference failed with error: %d", ret);
                continue;
            }

            UT_LOG_DEBUG("Invoking dsGetHdmiPreference with handle: %ld", handle);
            ret = dsGetHdmiPreference(handle, &hdcpCurrentProtocolGet);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsGetHdmiPreference failed with error: %d", ret);
                continue;
            }

            UT_LOG_DEBUG("HDCP protocol version set: %d, HDCP protocol version got: %d", hdcpCurrentProtocol, hdcpCurrentProtocolGet);
            UT_ASSERT_EQUAL(hdcpCurrentProtocol, hdcpCurrentProtocolGet);
        }
    }

    UT_LOG_DEBUG("Invoking dsVideoPortTerm");
    ret = dsVideoPortTerm();
	UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to verify the functionality of dsVideoPort_GetColorSpace_sink
*
* This test is designed to check the correct operation of the dsVideoPort_GetColorSpace_sink function. It does this by initializing the video port, getting the video port with type as dsVIDEOPORT_TYPE_INTERNAL and index as 0, then getting the color space with the handle obtained from the previous step. The test asserts that all these operations return dsERR_NONE, indicating successful operation. The color space obtained is then compared with the expected value.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 020@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_GetColorSpace_sink(void)
{
    gTestID = 20;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    dsDisplayColorSpace_t color_space;

    UT_LOG_DEBUG("Invoking dsVideoPortInit()");
    ret = dsVideoPortInit();
    UT_LOG_DEBUG("dsVideoPortInit() returned %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsGetVideoPort() with type as dsVIDEOPORT_TYPE_INTERNAL and index as 0");
    ret = dsGetVideoPort(dsVIDEOPORT_TYPE_INTERNAL, 0, &handle);
	UT_ASSERT_EQUAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetVideoPort failed with error: %d", ret);
	    ret = dsVideoPortTerm();
        UT_LOG_DEBUG("dsVideoPortTerm returned %d", ret);
        return;
    }

    UT_LOG_DEBUG("Invoking dsGetColorSpace() with handle obtained from previous step");
    ret = dsGetColorSpace(handle, &color_space);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    UT_LOG_DEBUG("dsGetColorSpace() returned color_space %d and status %d", color_space, ret);

    UT_ASSERT_KVP_EQUAL_PROFILE_UINT8(color_space, "Ports/1/colorspaces");

    UT_LOG_DEBUG("Invoking dsVideoPortTerm()");
    ret = dsVideoPortTerm();
	UT_LOG_DEBUG("dsVideoPortTerm() returned %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to verify the functionality of the dsVideoPort_GetColorSpace API
*
* This test case is designed to validate the dsVideoPort_GetColorSpace API. The test case will initialize the video port, get the video port with type as HDMI and index as 0, get the color space using the handle obtained from the previous step, and finally terminate the video port. The test case will assert the return status of each API call to ensure they are executed successfully.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 021@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_GetColorSpace_source(void)
{
    gTestID = 21;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t retStatus;
    intptr_t handle;
    dsDisplayColorSpace_t color_space;

    UT_LOG_DEBUG("Invoking dsVideoPortInit()");
    retStatus = dsVideoPortInit();
    UT_LOG_DEBUG("dsVideoPortInit() returned %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsGetVideoPort() with type as dsVIDEOPORT_TYPE_HDMI and index as 0");
    retStatus = dsGetVideoPort(dsVIDEOPORT_TYPE_HDMI, 0, &handle);
    UT_LOG_DEBUG("Handle obtained: %ld", handle);
    UT_ASSERT_EQUAL(retStatus, dsERR_NONE);
    if (retStatus != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetVideoPort failed with error: %d", retStatus);
	retStatus = dsVideoPortTerm();
        UT_LOG_DEBUG("dsVideoPortTerm returned %d", retStatus);
        return;
    }

    UT_LOG_DEBUG("Invoking dsGetColorSpace() with handle obtained from previous step");
    retStatus = dsGetColorSpace(handle, &color_space);
    UT_ASSERT_EQUAL(retStatus, dsERR_NONE);
    UT_LOG_DEBUG("Color space obtained: %d", color_space);
    UT_ASSERT_KVP_EQUAL_PROFILE_UINT8(color_space, "Ports/1/colorspaces");

    UT_LOG_DEBUG("Invoking dsVideoPortTerm()");
    retStatus = dsVideoPortTerm();
	UT_LOG_DEBUG("dsVideoPortTerm() returned %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to check the color depth capabilities of the video port
*
* This test checks the color depth capabilities of the video port by invoking the dsVideoPortInit, dsGetVideoPort, dsColorDepthCapabilities, and dsVideoPortTerm functions. The test verifies that all these functions return the expected status and that the color depth capability matches the expected value.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 022@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_CheckColorDepthCapabilities_sink(void)
{
    gTestID = 22;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t retStatus;
    intptr_t handle;
    unsigned int colorDepthCapability;

    UT_LOG_DEBUG("Invoking dsVideoPortInit");
    retStatus = dsVideoPortInit();
    UT_LOG_DEBUG("Return status: %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsGetVideoPort with dsVIDEOPORT_TYPE_INTERNAL and index 0");
    retStatus = dsGetVideoPort(dsVIDEOPORT_TYPE_INTERNAL, 0, &handle);
    UT_LOG_DEBUG("Return status: %d, Handle: %ld", retStatus, handle);
    UT_ASSERT_EQUAL(retStatus, dsERR_NONE);
    if (retStatus != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetVideoPort failed with error: %d", retStatus);
	retStatus = dsVideoPortTerm();
        UT_LOG_DEBUG("dsVideoPortTerm returned %d", retStatus);
        return;
    }

    UT_LOG_DEBUG("Invoking dsColorDepthCapabilities with handle");
    retStatus = dsColorDepthCapabilities(handle, &colorDepthCapability);
    UT_LOG_DEBUG("Return status: %d, Color Depth Capability: %u", retStatus, colorDepthCapability);
    UT_ASSERT_EQUAL(retStatus, dsERR_NONE);
    UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(colorDepthCapability, "Ports/1/Supported_color_depth_capabilities");

    UT_LOG_DEBUG("Invoking dsVideoPortTerm");
    retStatus = dsVideoPortTerm();
    UT_LOG_DEBUG("Return status: %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to check the color depth capabilities of a source device
*
* This function tests the color depth capabilities of a source device. It first initializes the video port subsystem, then gets the handle of the video port for the HDMI source device. It then gets the color depth capabilities of the video port and compares it with the value retrieved from the 'Source_4K_VideoPort.yaml' file. Finally, it terminates the video port subsystem.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 023@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_CheckColorDepthCapabilities_source(void)
{
    gTestID = 23;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t retStatus;
    intptr_t handle;
    unsigned int colorDepthCapability;
    dsVideoPortType_t type = dsVIDEOPORT_TYPE_HDMI;
    int index = 0;

    UT_LOG_DEBUG("Invoking dsVideoPortInit");
    retStatus = dsVideoPortInit();
    UT_LOG_DEBUG("Return status: %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsGetVideoPort with type: %d and index: %d", type, index);
    retStatus = dsGetVideoPort(type, index, &handle);
    UT_LOG_DEBUG("Return status: %d, Handle: %ld", retStatus, handle);
    UT_ASSERT_EQUAL(retStatus, dsERR_NONE);
    if (retStatus != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetVideoPort failed with error: %d", retStatus);
	retStatus = dsVideoPortTerm();
        UT_LOG_DEBUG("dsVideoPortTerm returned %d", retStatus);
        return;
    }

    UT_LOG_DEBUG("Invoking dsColorDepthCapabilities with handle: %ld", handle);
    retStatus = dsColorDepthCapabilities(handle, &colorDepthCapability);
    UT_LOG_DEBUG("Return status: %d, Color Depth Capability: %u", retStatus, colorDepthCapability);
    UT_ASSERT_EQUAL(retStatus, dsERR_NONE);
    UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(colorDepthCapability, "Ports/1/Supported_color_depth_capabilities");

    UT_LOG_DEBUG("Invoking dsVideoPortTerm");
    retStatus = dsVideoPortTerm();
    UT_LOG_DEBUG("Return status: %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to verify the functionality of the dsVideoPort_GetColorDepth_sink API
*
* In this test, the dsVideoPort_GetColorDepth_sink API is tested to ensure it correctly retrieves the color depth of the video port. The test involves initializing the video port, getting the video port with type=dsVIDEOPORT_TYPE_INTERNAL and index=0, getting the color depth, and then terminating the video port. The test asserts that all these operations return dsERR_NONE, indicating successful execution.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 024@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_GetColorDepth_sink(void)
{
    gTestID = 24;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    unsigned int color_depth;

    UT_LOG_DEBUG("Invoking dsVideoPortInit()");
    ret = dsVideoPortInit();
    UT_LOG_DEBUG("dsVideoPortInit() returned %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsGetVideoPort() with type=dsVIDEOPORT_TYPE_INTERNAL and index=0");
    ret = dsGetVideoPort(dsVIDEOPORT_TYPE_INTERNAL, 0, &handle);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    UT_LOG_DEBUG("dsGetVideoPort() returned handle=%ld and status=%d", handle, ret);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetVideoPort failed with error: %d", ret);
	    ret = dsVideoPortTerm();
        UT_LOG_DEBUG("dsVideoPortTerm returned %d", ret);
        return;
    }

    UT_LOG_DEBUG("Invoking dsGetColorDepth() with handle=%ld", handle);
    ret = dsGetColorDepth(handle, &color_depth);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    UT_LOG_DEBUG("dsGetColorDepth() returned color_depth=%u and status=%d", color_depth, ret);

    UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(color_depth, "color_depth");

    UT_LOG_DEBUG("Invoking dsVideoPortTerm()");
    ret = dsVideoPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);
    UT_LOG_DEBUG("dsVideoPortTerm() returned %d", ret);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test for getting the color depth of a video source
*
* This test verifies if the dsGetColorDepth() function can successfully get the color depth of a video source. The color depth is compared with the value retrieved from a YAML file to ensure correctness.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 025@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_GetColorDepth_source(void)
{
    gTestID = 25;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    unsigned int color_depth;

    UT_LOG_DEBUG("Invoking dsVideoPortInit()");
    ret = dsVideoPortInit();
	UT_LOG_DEBUG("dsVideoPortInit() returned %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsGetVideoPort() with type as dsVIDEOPORT_TYPE_HDMI and index as 0");
    ret = dsGetVideoPort(dsVIDEOPORT_TYPE_HDMI, 0, &handle);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    UT_LOG_DEBUG("dsGetVideoPort() returned handle %ld and status %d", handle, ret);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetVideoPort failed with error: %d", ret);
	    ret = dsVideoPortTerm();
        UT_LOG_DEBUG("dsVideoPortTerm returned %d", ret);
        return;
    }

    UT_LOG_DEBUG("Invoking dsGetColorDepth() with handle obtained from previous step");
    ret = dsGetColorDepth(handle, &color_depth);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    UT_LOG_DEBUG("dsGetColorDepth() returned color depth %u and status %d", color_depth, ret);
    UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(color_depth, "color_depth");

    UT_LOG_DEBUG("Invoking dsVideoPortTerm()");
    ret = dsVideoPortTerm();
	UT_LOG_DEBUG("dsVideoPortTerm() returned %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test for setting and getting the preferred color depth of a video port
*
* This test verifies if the dsSetPreferredColorDepth and dsGetPreferredColorDepth functions work as expected.
* It sets a preferred color depth for a video port and then retrieves it to check if the set and retrieved values match.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 026@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/
void test_l2_dsVideoPort_SetAndGetPreferredColorDepth_source(void)
{
    gTestID = 26;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;
    intptr_t handle = 0;
    dsDisplayColorDepth_t colorDepthSet, colorDepthGet;

    UT_LOG_DEBUG("Invoking dsVideoPortInit()");
    ret = dsVideoPortInit();
	UT_LOG_DEBUG("dsVideoPortInit() returned %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (int i = dsVIDEOPORT_TYPE_RF; i < dsVIDEOPORT_TYPE_MAX; i++)
    {
        UT_LOG_DEBUG("Invoking dsGetVideoPort() with type %d and index 0", i);
        ret = dsGetVideoPort(i, 0, &handle);
		UT_ASSERT_EQUAL(ret, dsERR_NONE);
		UT_LOG_DEBUG("dsGetVideoPort() returned handle %ld and status %d", handle, ret);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetVideoPort failed with error: %d", ret);
	        continue;
        }

        for (int j = dsDISPLAY_COLORDEPTH_8BIT; j <= dsDISPLAY_COLORDEPTH_AUTO; j++)
        {
            colorDepthSet = j;
            UT_LOG_DEBUG("Invoking dsSetPreferredColorDepth() with handle %ld and colorDepth %d", handle, colorDepthSet);
            ret = dsSetPreferredColorDepth(handle, colorDepthSet);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetPreferredColorDepth() failed with error %d", ret);
                continue;
            }

            UT_LOG_DEBUG("Invoking dsGetPreferredColorDepth() with handle %ld", handle);
            ret = dsGetPreferredColorDepth(handle, &colorDepthGet);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsGetPreferredColorDepth() failed with error %d", ret);
                continue;
            }

            UT_LOG_DEBUG("Color depth set: %d, Color depth got: %d", colorDepthSet, colorDepthGet);
            UT_ASSERT_EQUAL(colorDepthSet, colorDepthGet);
        }
    }

    UT_LOG_DEBUG("Invoking dsVideoPortTerm()");
    ret = dsVideoPortTerm();
	UT_LOG_DEBUG("dsVideoPortTerm() returned %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to verify the functionality of dsVideoPort_GetQuantizationRange_sink
*
* This test case is designed to test the dsVideoPort_GetQuantizationRange_sink function. It checks if the function correctly initializes the video port, gets the video port with dsVIDEOPORT_TYPE_INTERNAL as type and 0 as index, gets the quantization range with the handle obtained from the previous step, and finally terminates the video port. The test asserts that all these operations return dsERR_NONE, indicating successful execution.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 027@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_GetQuantizationRange_sink(void)
{
    gTestID = 27;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    dsDisplayQuantizationRange_t quantization_range;

    UT_LOG_DEBUG("Invoking dsVideoPortInit()");
    ret = dsVideoPortInit();
	UT_LOG_DEBUG("dsVideoPortInit() returned %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsGetVideoPort() with dsVIDEOPORT_TYPE_INTERNAL as type and 0 as index");
    ret = dsGetVideoPort(dsVIDEOPORT_TYPE_INTERNAL, 0, &handle);
	UT_LOG_DEBUG("Handle: %ld", handle);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
	if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetVideoPort failed with error: %d", ret);
	    ret = dsVideoPortTerm();
        UT_LOG_DEBUG("dsVideoPortTerm returned %d", ret);
        return;
    }

    UT_LOG_DEBUG("Invoking dsGetQuantizationRange() with handle obtained from previous step");
    ret = dsGetQuantizationRange(handle, &quantization_range);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    UT_LOG_DEBUG("Quantization Range: %d", quantization_range);

    UT_ASSERT_KVP_EQUAL_PROFILE_UINT8(quantization_range, "Ports/1/quantization_ranges");

    UT_LOG_DEBUG("Invoking dsVideoPortTerm()");
    ret = dsVideoPortTerm();
	UT_LOG_DEBUG("dsVideoPortTerm() returned %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test for getting the quantization range of a video source
*
* This test verifies if the dsGetQuantizationRange() function can successfully get the quantization range of a video source. The function is tested by initializing the video port, getting the video port with HDMI type and index 0, and then getting the quantization range. The test asserts if the return values of these functions are as expected.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 028@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_GetQuantizationRange_source(void)
{
    gTestID = 28;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    dsDisplayQuantizationRange_t quantization_range;

    UT_LOG_DEBUG("Invoking dsVideoPortInit()");
    ret = dsVideoPortInit();
	UT_LOG_DEBUG("dsVideoPortInit() returned %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsGetVideoPort() with dsVIDEOPORT_TYPE_HDMI as type and 0 as index");
    ret = dsGetVideoPort(dsVIDEOPORT_TYPE_HDMI, 0, &handle);
    UT_LOG_DEBUG("Handle: %ld, Return status: %d", handle, ret);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
	if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetVideoPort failed with error: %d", ret);
	    ret = dsVideoPortTerm();
        UT_LOG_DEBUG("dsVideoPortTerm returned %d", ret);
        return;
    }

    UT_LOG_DEBUG("Invoking dsGetQuantizationRange() with handle obtained from dsGetVideoPort()");
    ret = dsGetQuantizationRange(handle, &quantization_range);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    UT_LOG_DEBUG("Quantization range: %d, Return status: %d", quantization_range, ret);

    UT_ASSERT_KVP_EQUAL_PROFILE_UINT8(quantization_range, "Ports/1/quantization_ranges");

    UT_LOG_DEBUG("Invoking dsVideoPortTerm()");
    ret = dsVideoPortTerm();
	UT_LOG_DEBUG("dsVideoPortTerm() returned %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test for dsVideoPort_GetMatrixCoefficients_sink API
*
* This test case is designed to validate the functionality of the dsVideoPort_GetMatrixCoefficients_sink API.
* The test case invokes the API and checks if it returns the correct matrix coefficients for the video port.
* The returned value is then compared with the expected value retrieved from the 'Sink_4K_VideoPort.yaml' file.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 029@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_GetMatrixCoefficients_sink(void)
{
    gTestID = 29;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;
    intptr_t handle = 0;
    dsDisplayMatrixCoefficients_t matrix_coefficients;

    UT_LOG_DEBUG("Invoking dsVideoPortInit");
    ret = dsVideoPortInit();
	UT_LOG_DEBUG("dsVideoPortInit() returned %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsGetVideoPort with type=dsVIDEOPORT_TYPE_INTERNAL and index=1");
    ret = dsGetVideoPort(dsVIDEOPORT_TYPE_INTERNAL, 1, &handle);
    UT_LOG_DEBUG("Handle: %ld, Return status: %d", handle, ret);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
	if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetVideoPort failed with error: %d", ret);
	    ret = dsVideoPortTerm();
        UT_LOG_DEBUG("dsVideoPortTerm returned %d", ret);
        return;
    }

    UT_LOG_DEBUG("Invoking dsGetMatrixCoefficients with handle obtained from dsGetVideoPort");
    ret = dsGetMatrixCoefficients(handle, &matrix_coefficients);
    UT_LOG_DEBUG("Matrix Coefficients: %d, Return Status: %d", matrix_coefficients, ret);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);

    UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(matrix_coefficients, "Ports/1/matrix_coefficients");

    UT_LOG_DEBUG("Invoking dsVideoPortTerm");
    ret = dsVideoPortTerm();
	UT_LOG_DEBUG("dsVideoPortTerm() returned %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to verify the functionality of dsVideoPort_GetMatrixCoefficients API
*
* This test case verifies the functionality of dsVideoPort_GetMatrixCoefficients API. The test case initializes the video port, gets the video port handle, retrieves the matrix coefficients and verifies it with the expected value. The test case also ensures that the API returns the correct status codes at each step.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 030@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_GetMatrixCoefficients_source(void)
{
    gTestID = 30;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t retStatus;
    intptr_t handle;
    dsDisplayMatrixCoefficients_t matrix_coefficients;

    UT_LOG_DEBUG("Invoking dsVideoPortInit()");
    retStatus = dsVideoPortInit();
    UT_LOG_DEBUG("Return status: %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsGetVideoPort() with type as dsVIDEOPORT_TYPE_HDMI and index as 1");
    retStatus = dsGetVideoPort(dsVIDEOPORT_TYPE_HDMI, 1, &handle);
    UT_LOG_DEBUG("Return status: %d, Handle: %ld", retStatus, handle);
    UT_ASSERT_EQUAL(retStatus, dsERR_NONE);
    if (retStatus != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetVideoPort failed with error: %d", retStatus);
	retStatus = dsVideoPortTerm();
        UT_LOG_DEBUG("dsVideoPortTerm returned %d", retStatus);
        return;
    }

    UT_LOG_DEBUG("Invoking dsGetMatrixCoefficients() with handle obtained from previous step");
    retStatus = dsGetMatrixCoefficients(handle, &matrix_coefficients);
    UT_LOG_DEBUG("Return status: %d, Matrix Coefficients: %d", retStatus, matrix_coefficients);
    UT_ASSERT_EQUAL(retStatus, dsERR_NONE);
    UT_ASSERT_EQUAL(matrix_coefficients, dsDISPLAY_MATRIXCOEFFICIENT_UNKNOWN);
    UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(matrix_coefficients, "Ports/1/matrix_coefficients");

    UT_LOG_DEBUG("Invoking dsVideoPortTerm()");
    retStatus = dsVideoPortTerm();
    UT_LOG_DEBUG("Return status: %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main tests for this module
 *
 * @return int - 0 on success, otherwise failure
 */

int test_dsVideoPort_l2_register(void)
{
    // Create the test suite
    pSuite = UT_add_suite("[L2 dsVideoPort]", NULL, NULL);
    if (pSuite == NULL) {
        return -1;
    }
    // List of test function names and strings

    UT_add_test( pSuite, "l2_dsVideoPort_EnableDisabledVideoPorts_sink", test_l2_dsVideoPort_EnableDisabledVideoPorts_sink);
    UT_add_test( pSuite, "l2_dsVideoPort_EnableDisabledVideoPorts_source", test_l2_dsVideoPort_EnableDisabledVideoPorts_source);
    UT_add_test( pSuite, "l2_dsVideoPort_VerifyDisplayAndPortStatus_sink", test_l2_dsVideoPort_VerifyDisplayAndPortStatus_sink);
    UT_add_test( pSuite, "l2_dsVideoPort_VerifyDisplayAndPortStatus_source", test_l2_dsVideoPort_VerifyDisplayAndPortStatus_source);
    UT_add_test( pSuite, "l2_dsVideoPort_RetrieveAndVerifySurroundModeCapabilities_sink", test_l2_dsVideoPort_RetrieveAndVerifySurroundModeCapabilities_sink);
    UT_add_test( pSuite, "l2_dsVideoPort_VerifyDisplaySurround_source", test_l2_dsVideoPort_VerifyDisplaySurround_source);
    UT_add_test( pSuite, "l2_dsVideoPort_SetAndGetResolution_source", test_l2_dsVideoPort_SetAndGetResolution_source);
    UT_add_test( pSuite, "l2_dsVideoPort_VerifySupportedTvResolutions_sink", test_l2_dsVideoPort_VerifySupportedTvResolutions_sink);
    UT_add_test( pSuite, "l2_dsVideoPort_VerifySupportedTvResolutions_source", test_l2_dsVideoPort_VerifySupportedTvResolutions_source);
    UT_add_test( pSuite, "l2_dsVideoPort_GetHDRCapabilities_sink", test_l2_dsVideoPort_GetHDRCapabilities_sink);
    UT_add_test( pSuite, "l2_dsVideoPort_GetHDRCapabilities_source", test_l2_dsVideoPort_GetHDRCapabilities_source);
    UT_add_test( pSuite, "l2_dsVideoPort_SetAndGetForceDisable4KSupport_sink", test_l2_dsVideoPort_SetAndGetForceDisable4KSupport_sink);
    UT_add_test( pSuite, "l2_dsVideoPort_SetAndGetForceDisable4KSupport_source", test_l2_dsVideoPort_SetAndGetForceDisable4KSupport_source);
    UT_add_test( pSuite, "l2_dsVideoPort_GetHDCPStatus_sink", test_l2_dsVideoPort_GetHDCPStatus_sink);
    UT_add_test( pSuite, "l2_dsVideoPort_GetHDCPStatus_source", test_l2_dsVideoPort_GetHDCPStatus_source);
    UT_add_test( pSuite, "l2_dsVideoPort_VerifyHDCPProtocolStatus_sink", test_l2_dsVideoPort_VerifyHDCPProtocolStatus_sink);
    UT_add_test( pSuite, "l2_dsVideoPort_VerifyHDCPProtocolStatus_source", test_l2_dsVideoPort_VerifyHDCPProtocolStatus_source);
    UT_add_test( pSuite, "l2_dsVideoPort_SetAndGetHdmiPreference_sink", test_l2_dsVideoPort_SetAndGetHdmiPreference_sink);
    UT_add_test( pSuite, "l2_dsVideoPort_SetAndGetHdmiPreference_source", test_l2_dsVideoPort_SetAndGetHdmiPreference_source);
    UT_add_test( pSuite, "l2_dsVideoPort_GetColorSpace_sink", test_l2_dsVideoPort_GetColorSpace_sink);
    UT_add_test( pSuite, "l2_dsVideoPort_GetColorSpace_source", test_l2_dsVideoPort_GetColorSpace_source);
    UT_add_test( pSuite, "l2_dsVideoPort_CheckColorDepthCapabilities_sink", test_l2_dsVideoPort_CheckColorDepthCapabilities_sink);
    UT_add_test( pSuite, "l2_dsVideoPort_CheckColorDepthCapabilities_source", test_l2_dsVideoPort_CheckColorDepthCapabilities_source);
    UT_add_test( pSuite, "l2_dsVideoPort_GetColorDepth_sink", test_l2_dsVideoPort_GetColorDepth_sink);
    UT_add_test( pSuite, "l2_dsVideoPort_GetColorDepth_source", test_l2_dsVideoPort_GetColorDepth_source);
    UT_add_test( pSuite, "l2_dsVideoPort_SetAndGetPreferredColorDepth_source", test_l2_dsVideoPort_SetAndGetPreferredColorDepth_source);
    UT_add_test( pSuite, "l2_dsVideoPort_GetQuantizationRange_sink", test_l2_dsVideoPort_GetQuantizationRange_sink);
    UT_add_test( pSuite, "l2_dsVideoPort_GetQuantizationRange_source", test_l2_dsVideoPort_GetQuantizationRange_source);
    UT_add_test( pSuite, "l2_dsVideoPort_GetMatrixCoefficients_sink", test_l2_dsVideoPort_GetMatrixCoefficients_sink);
    UT_add_test( pSuite, "l2_dsVideoPort_GetMatrixCoefficients_source", test_l2_dsVideoPort_GetMatrixCoefficients_source);

    return 0;
}
