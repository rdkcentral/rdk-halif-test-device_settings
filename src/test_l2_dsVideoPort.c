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
* Ref to API Definition specification documentation : [ds-video-port_halSpec.md](../../docs/pages/ds-video-port_halSpec.md)
*/

#include <ut.h>
#include <ut_log.h>
#include <ut_kvp_profile.h>
#include "dsVideoPort.h"

static int gTestGroup = 2;
static int gTestID = 1;

/**
* @brief This test aims to verify the functionality of enabling and disabling the video port.
*
* In this test, the video port subsystem is initialized and each type of video port is looped through. For each video port, the handle is retrieved, the status of the port is checked, and if the port is disabled, it is enabled. The status of the port is then checked again to confirm that it is enabled. Finally, the video port subsystem is terminated.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 001@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_EnableDisableVideoPort(void)
{
    gTestID = 1;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    bool enabled;

    // Initialize the Video Port sub-system
    ret = dsVideoPortInit();
    UT_LOG_DEBUG("Invoking dsVideoPortInit()");
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    // Loop through each type of video port
    for (dsVideoPortType_t type = dsVIDEOPORT_TYPE_RF; type < dsVIDEOPORT_TYPE_MAX; type++)
    {
        // Get the handle for the video port
        ret = dsGetVideoPort(type, 0, &handle);
        UT_LOG_DEBUG("Invoking dsGetVideoPort() with type=%d and index=0", type);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetVideoPort failed with error: %d\n", ret);
            continue;
        }

        // Check if the video port is enabled
        ret = dsIsVideoPortEnabled(handle, &enabled);
        UT_LOG_DEBUG("Invoking dsIsVideoPortEnabled() with handle=%ld", handle);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsIsVideoPortEnabled failed with error: %d\n", ret);
            continue;
        }

        // If the video port is disabled, enable it
        if (!enabled)
        {
            ret = dsEnableVideoPort(handle, true);
            UT_LOG_DEBUG("Invoking dsEnableVideoPort() with handle=%ld and enabled=true", handle);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsEnableVideoPort failed with error: %d\n", ret);
                continue;
            }

            // Check if the video port is now enabled
            ret = dsIsVideoPortEnabled(handle, &enabled);
            UT_LOG_DEBUG("Invoking dsIsVideoPortEnabled() with handle=%ld", handle);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsIsVideoPortEnabled failed with error: %d\n", ret);
            }
            UT_ASSERT_EQUAL(enabled, true);
        }
    }

    // Terminate the Video Port sub-system
    ret = dsVideoPortTerm();
    UT_LOG_DEBUG("Invoking dsVideoPortTerm()");
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test verifies the display connection status of the video port
*
* This test function initializes the video port, gets the video port with HDMI type, checks if the display is connected and if the video port is active, and finally terminates the video port. The purpose of this test is to ensure that the video port functions are working as expected and the display connection status is correctly reported.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 002@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_VerifyDisplayConnectionStatus(void)
{
    gTestID = 2;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    bool connected, active;

    // Step 1: Call dsVideoPortInit
    UT_LOG_DEBUG("Invoking dsVideoPortInit()");
    ret = dsVideoPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    // Loop through each type of video port
    for (dsVideoPortType_t type = dsVIDEOPORT_TYPE_RF; type < dsVIDEOPORT_TYPE_MAX; type++)
    {
        // Get the handle for the video port
        ret = dsGetVideoPort(type, 0, &handle);
        UT_LOG_DEBUG("Invoking dsGetVideoPort() with type=%d and index=0", type);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetVideoPort failed with error: %d\n", ret);
            continue;
        }

        // Step 3: Call dsIsDisplayConnected
        UT_LOG_DEBUG("Invoking dsIsDisplayConnected() with handle obtained from dsGetVideoPort");
        ret = dsIsDisplayConnected(handle, &connected);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_ASSERT_EQUAL(connected, false);
        if (ret != dsERR_NONE || connected != false)
        {
            UT_LOG_ERROR("dsIsDisplayConnected failed with error: %d, connected: %d\n", ret, connected);
        }

        // Step 4: Call dsIsVideoPortActive
        UT_LOG_DEBUG("Invoking dsIsVideoPortActive() with handle obtained from dsGetVideoPort");
        ret = dsIsVideoPortActive(handle, &active);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_ASSERT_EQUAL(active, false);
        if (ret != dsERR_NONE || active != false)
        {
            UT_LOG_ERROR("dsIsVideoPortActive failed with error: %d, active: %d\n", ret, active);
        }
    }

    // Step 5: Call dsVideoPortTerm
    UT_LOG_DEBUG("Invoking dsVideoPortTerm()");
    ret = dsVideoPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to verify the DisplaySurround sink in L2 dsVideoPort
*
* This test verifies if the DisplaySurround sink is correctly initialized, retrieved and terminated in the L2 dsVideoPort. It also checks if the value obtained from the API dsIsDisplaySurround() matches with the value retrieved from the YAML configuration file.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 003@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_VerifyDisplaySurround_sink(void)
{
    gTestID = 3;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t retStatus;
    intptr_t handle;
    bool surround;

    // Step 1: Call dsVideoPortInit()
    retStatus = dsVideoPortInit();
    UT_LOG_DEBUG("Invoking dsVideoPortInit()");
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    // Loop through each type of video port
    for (dsVideoPortType_t type = dsVIDEOPORT_TYPE_RF; type < dsVIDEOPORT_TYPE_MAX; type++)
    {
        // Get the handle for the video port
        retStatus = dsGetVideoPort(type, 0, &handle);
        UT_LOG_DEBUG("Invoking dsGetVideoPort() with type=%d and index=0", type);
        UT_ASSERT_EQUAL(retStatus, dsERR_NONE);
        if (retStatus != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetVideoPort failed with error: %d\n", retStatus);
            continue;
        }

        // Step 3: Call dsIsDisplaySurround()
        retStatus = dsIsDisplaySurround(handle, &surround);
        UT_LOG_DEBUG("Invoking dsIsDisplaySurround() with handle obtained from dsGetVideoPort()");
        UT_ASSERT_EQUAL(retStatus, dsERR_NONE);
        if (retStatus != dsERR_NONE)
        {
            UT_LOG_ERROR("dsIsDisplaySurround failed with error: %d\n", retStatus);
        }

        // Step 4: Retrieve the value from the YAML configuration file
        UT_LOG_DEBUG("Retrieving and comparing value from YAML configuration file 'Panel_4K_VideoPort.yaml' at the path 'Ports/1/Display_surrond' ");
        UT_ASSERT_EQUAL_KVP_PROFILE_BOOL(surround, "Ports/1/Display_surrond");
    }

    // Step 6: Call dsVideoPortTerm()
    retStatus = dsVideoPortTerm();
    UT_LOG_DEBUG("Invoking dsVideoPortTerm()");
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to verify the surround mode capabilities of a video source
*
* This test verifies the surround mode capabilities of a video source by initializing the video port,
* getting the video port, checking if the display supports surround, getting the surround mode if supported,
* and finally terminating the video port. The test asserts that each of these operations return no error.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 004@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_VerifySurroundModeCapabilities_source(void)
{
    gTestID = 4;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    bool surround;
    int surroundMode;

    // Step 1: Call dsVideoPortInit()
    UT_LOG_DEBUG("Invoking dsVideoPortInit()");
    ret = dsVideoPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    // Loop through each type of video port
    for (dsVideoPortType_t type = dsVIDEOPORT_TYPE_RF; type < dsVIDEOPORT_TYPE_MAX; type++)
    {
        // Get the handle for the video port
        ret = dsGetVideoPort(type, 0, &handle);
        UT_LOG_DEBUG("Invoking dsGetVideoPort() with type=%d and index=0", type);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetVideoPort failed with error: %d\n", ret);
            continue;
        }

        // Step 3: Call dsIsDisplaySurround()
        UT_LOG_DEBUG("Invoking dsIsDisplaySurround() with handle=%ld", handle);
        ret = dsIsDisplaySurround(handle, &surround);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsIsDisplaySurround failed with error: %d\n", ret);
        }

        // Step 4: Call dsGetSurroundMode() if surround is supported
        if (surround)
        {
            UT_LOG_DEBUG("Invoking dsGetSurroundMode() with handle=%ld", handle);
            ret = dsGetSurroundMode(handle, &surroundMode);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsGetSurroundMode failed with error: %d\n", ret);
            }
            // Step 5: Verify the obtained surround mode with the configuration file
            // This step is not implemented here as it depends on the specific configuration file and its parsing
        }
    }

    // Step 6: Call dsVideoPortTerm()
    UT_LOG_DEBUG("Invoking dsVideoPortTerm()");
    ret = dsVideoPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to validate the setting and getting of video port properties in the L2 dsVideoPort module.
*
* In this test, we initialize the dsVideoPort module, get a handle to the HDMI video port, and then set and get various video port properties. We then compare the set and retrieved properties to ensure they match. This is done for all possible combinations of pixel resolution, aspect ratio, stereoscopic mode, and frame rate. The test concludes by terminating the dsVideoPort module.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 005@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_SetAndGetVideoPortProperties_source(void)
{
    gTestID = 5;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    dsVideoPortResolution_t setResolution, getResolution;

    ret = dsVideoPortInit();
    UT_LOG_DEBUG("Invoking dsVideoPortInit()");
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    // Loop through each type of video port
    for (dsVideoPortType_t type = dsVIDEOPORT_TYPE_RF; type < dsVIDEOPORT_TYPE_MAX; type++)
    {
        // Get the handle for the video port
        ret = dsGetVideoPort(type, 0, &handle);
        UT_LOG_DEBUG("Invoking dsGetVideoPort() with type=%d and index=0", type);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetVideoPort failed with error: %d\n", ret);
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
                        setResolution.pixelResolution = i;
                        setResolution.aspectRatio = j;
                        setResolution.stereoScopicMode = k;
                        setResolution.frameRate = l;
                        setResolution.interlaced = false;

                        ret = dsSetResolution(handle, &setResolution);
                        UT_LOG_DEBUG("Invoking dsSetResolution() with handle and setResolution");
                        UT_ASSERT_EQUAL(ret, dsERR_NONE);
                        if (ret != dsERR_NONE)
                        {
                            UT_LOG_ERROR("dsSetResolution failed with error: %d\n", ret);
                            continue;
                        }

                        ret = dsGetResolution(handle, &getResolution);
                        UT_LOG_DEBUG("Invoking dsGetResolution() with handle and getResolution");
                        UT_ASSERT_EQUAL(ret, dsERR_NONE);
                        if (ret != dsERR_NONE)
                        {
                            UT_LOG_ERROR("dsGetResolution failed with error: %d\n", ret);
                        }

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
    ret = dsVideoPortTerm();
    UT_LOG_DEBUG("Invoking dsVideoPortTerm()");
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to verify the supported TV resolutions
*
* This test verifies the supported TV resolutions by invoking the necessary APIs and checking their return values. It also compares the value obtained from the dsSupportedTvResolutions API with the value retrieved from the YAML file.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 006@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/
void test_l2_dsVideoPort_VerifySupportedTvResolutions(void)
{
    gTestID = 6;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    int resolutions;

    // Step 1: Call dsVideoPortInit
    UT_LOG_DEBUG("Invoking dsVideoPortInit()");
    ret = dsVideoPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    // Loop through each type of video port
    for (dsVideoPortType_t type = dsVIDEOPORT_TYPE_RF; type < dsVIDEOPORT_TYPE_MAX; type++)
    {
        // Get the handle for the video port
        ret = dsGetVideoPort(type, 0, &handle);
        UT_LOG_DEBUG("Invoking dsGetVideoPort() with type=%d and index=0", type);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetVideoPort failed with error: %d\n", ret);
            continue;
        }

        // Step 3: Call dsSupportedTvResolutions
        UT_LOG_DEBUG("Invoking dsSupportedTvResolutions() with handle obtained from dsGetVideoPort");
        ret = dsSupportedTvResolutions(handle, &resolutions);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsSupportedTvResolutions failed with error: %d\n", ret);
            dsVideoPortTerm();
            return;
        }

        // Step 4 and 5: Compare the value obtained from dsSupportedTvResolutions with the value retrieved from the YAML file
        UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(resolutions, "Ports/1/Supported_tv_resolutions_capabilities");
    }

    // Step 6: Call dsVideoPortTerm
    UT_LOG_DEBUG("Invoking dsVideoPortTerm()");
    ret = dsVideoPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to verify the HDR capabilities of the video port
*
* This test aims to get and verify the HDR capabilities of the video port. It does so by comparing the HDR capabilities obtained from the API and the YAML file. This is important to ensure the correct functioning of the video port and its compatibility with HDR.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 007@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_GetAndVerifyHDRCapabilities(void)
{
    gTestID = 7;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    int capabilities;

    // Step 1: Call dsVideoPortInit()
    ret = dsVideoPortInit();
    UT_LOG_INFO("Invoking dsVideoPortInit() returned %d\n", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    // Loop through each type of video port
    for (dsVideoPortType_t type = dsVIDEOPORT_TYPE_RF; type < dsVIDEOPORT_TYPE_MAX; type++)
    {
        // Get the handle for the video port
        ret = dsGetVideoPort(type, 0, &handle);
        UT_LOG_DEBUG("Invoking dsGetVideoPort() with type=%d and index=0", type);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetVideoPort failed with error: %d\n", ret);
            continue;
        }

        // Step 3: Call dsGetTVHDRCapabilities()
        ret = dsGetTVHDRCapabilities(handle, &capabilities);
        UT_LOG_INFO("Invoking dsGetTVHDRCapabilities() with handle %ld returned %d and capabilities %d\n", handle, ret, capabilities);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetTVHDRCapabilities failed with error: %d\n", ret);
        }

        // Step 4: Retrieve the value from the YAML file
        UT_LOG_INFO("Comparing HDR capabilities obtained from API and YAML file");
        UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(capabilities, "Ports/1/hdr_capabilities");
    }

    // Step 6: Call dsVideoPortTerm()
    ret = dsVideoPortTerm();
    UT_LOG_INFO("Invoking dsVideoPortTerm() returned %d\n", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test for setting and getting the force disable 4K support in dsVideoPort
*
* This test verifies the functionality of setting and getting the force disable 4K support in dsVideoPort.
* It initializes the video port subsystem, loops through each type of video port, gets the handle of the video port,
* forcefully disables 4K support, verifies if 4K support is forcefully disabled, and finally terminates the video port subsystem.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 008@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_SetAndGetForceDisable4KSupport(void)
{
    gTestID = 8;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t retStatus;
    intptr_t handle;
    bool disable;
    dsVideoPortType_t type;

    // Initialize the video port subsystem
    retStatus = dsVideoPortInit();
    UT_LOG_DEBUG("Invoking dsVideoPortInit()");
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    // Loop through each type of video port
    for (type = dsVIDEOPORT_TYPE_RF; type < dsVIDEOPORT_TYPE_MAX; type++)
    {
        // Get the handle of the video port
        retStatus = dsGetVideoPort(type, 0, &handle);
        UT_LOG_DEBUG("Invoking dsGetVideoPort() with type: %d, index: 0", type);
        UT_ASSERT_EQUAL(retStatus, dsERR_NONE);
        if (retStatus != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetVideoPort failed with error: %d\n", retStatus);
            continue;
        }

        // Forcefully disable 4K support
        retStatus = dsSetForceDisable4KSupport(handle, true);
        UT_LOG_DEBUG("Invoking dsSetForceDisable4KSupport() with handle: %ld, disable: true", handle);
        UT_ASSERT_EQUAL(retStatus, dsERR_NONE);
        if (retStatus != dsERR_NONE)
        {
            UT_LOG_ERROR("dsSetForceDisable4KSupport failed with error: %d\n", retStatus);
            continue;
        }

        // Verify if 4K support is forcefully disabled
        retStatus = dsGetForceDisable4KSupport(handle, &disable);
        UT_LOG_DEBUG("Invoking dsGetForceDisable4KSupport() with handle: %ld", handle);
        UT_ASSERT_EQUAL(retStatus, dsERR_NONE);
        if (retStatus != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetForceDisable4KSupport failed with error: %d\n", retStatus);
        }
        UT_ASSERT_EQUAL(disable, true);
    }

    // Terminate the video port subsystem
    retStatus = dsVideoPortTerm();
    UT_LOG_DEBUG("Invoking dsVideoPortTerm()");
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test function is designed to check the HDCP status of the dsVideoPort
*
* This function tests the HDCP status of the dsVideoPort by invoking the necessary APIs and checking their return values. It also logs the progress of the test and any errors that occur. The purpose of this test is to ensure the correct functioning of the HDCP status retrieval process.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 009@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_CheckHDCPStatus(void)
{
    gTestID = 9;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    dsHdcpStatus_t status;

    // Step 1: Call dsVideoPortInit()
    UT_LOG_DEBUG("Invoking dsVideoPortInit()");
    ret = dsVideoPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    // Loop through each type of video port
    for (dsVideoPortType_t type = dsVIDEOPORT_TYPE_RF; type < dsVIDEOPORT_TYPE_MAX; type++)
    {
        // Get the handle of the video port
        ret = dsGetVideoPort(type, 0, &handle);
        UT_LOG_DEBUG("Invoking dsGetVideoPort() with type: %d, index: 0", type);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetVideoPort failed with error: %d\n", ret);
            continue;
        }

        // Step 3: Call dsGetHDCPStatus()
        UT_LOG_DEBUG("Invoking dsGetHDCPStatus() with handle=%ld", handle);
        ret = dsGetHDCPStatus(handle, &status);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetHDCPStatus() failed with error: %d\n", ret);
        }

        // Step 4: Verify HDCP status
        UT_LOG_DEBUG("HDCP status: %d\n", status);
        UT_ASSERT_TRUE(status == dsHDCP_STATUS_AUTHENTICATED || status == dsHDCP_STATUS_UNPOWERED || status == dsHDCP_STATUS_PORTDISABLED);
    }
    // Step 5: Call dsVideoPortTerm()
    UT_LOG_DEBUG("Invoking dsVideoPortTerm()");
    ret = dsVideoPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to verify the HDCP Protocol Status of the L2 dsVideoPort
*
* This test verifies the HDCP Protocol Status of the L2 dsVideoPort. It initializes the video port subsystem, gets the video port handle, retrieves the HDCP protocol version, compares it with the value from the YAML file, and finally terminates the video port subsystem. The test ensures that all these operations are successful and the HDCP protocol version matches the expected value.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 010@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_VerifyHDCPProtocolStatus(void)
{
    gTestID = 10;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    dsHdcpProtocolVersion_t protocolVersion;

    // Step 1: Call dsVideoPortInit
    UT_LOG_DEBUG("Invoking dsVideoPortInit()");
    ret = dsVideoPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    // Loop through each type of video port
    for (dsVideoPortType_t type = dsVIDEOPORT_TYPE_RF; type < dsVIDEOPORT_TYPE_MAX; type++)
    {
        // Get the handle of the video port
        ret = dsGetVideoPort(type, 0, &handle);
        UT_LOG_DEBUG("Invoking dsGetVideoPort() with type: %d, index: 0", type);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetVideoPort failed with error: %d\n", ret);
            continue;
        }

        // Step 3: Call dsGetHDCPProtocol
        UT_LOG_DEBUG("Invoking dsGetHDCPProtocol() with handle=%ld", handle);
        ret = dsGetHDCPProtocol(handle, &protocolVersion);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("Failed to get HDCP protocol version\n");
        }

        // Step 4 and 5: Compare the HDCP protocol version with the value from YAML file
        UT_ASSERT_KVP_EQUAL_PROFILE_UINT8(protocolVersion, "Ports/1/hdcp_protocol_version");
    }
    // Step 6: Call dsVideoPortTerm
    UT_LOG_DEBUG("Invoking dsVideoPortTerm()");
    ret = dsVideoPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test checks the functionality of setting and getting HDMI preference in dsVideoPort
*
* This test initializes the dsVideoPort, sets the HDMI preference for each port type and HDCP protocol version, gets the HDMI preference and checks if it matches the set value. The test is performed for all port types and HDCP protocol versions. Finally, it terminates the dsVideoPort. The test ensures that the HDMI preference is correctly set and retrieved for all combinations of port types and HDCP protocol versions.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 011@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_SetAndGetHdmiPreference(void)
{
    gTestID = 11;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;
    intptr_t handle;
    dsHdcpProtocolVersion_t hdcpCurrentProtocol, hdcpCurrentProtocolGet;

    ret = dsVideoPortInit();
    UT_LOG_INFO("Invoking dsVideoPortInit()");
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    dsVideoPortType_t portTypes[] = {dsVIDEOPORT_TYPE_RF, dsVIDEOPORT_TYPE_BB, dsVIDEOPORT_TYPE_SVIDEO, dsVIDEOPORT_TYPE_1394, dsVIDEOPORT_TYPE_DVI, dsVIDEOPORT_TYPE_COMPONENT, dsVIDEOPORT_TYPE_HDMI, dsVIDEOPORT_TYPE_HDMI_INPUT, dsVIDEOPORT_TYPE_INTERNAL};
    dsHdcpProtocolVersion_t hdcpVersions[] = {dsHDCP_VERSION_1X, dsHDCP_VERSION_2X};

    for(int i = 0; i < sizeof(portTypes)/sizeof(dsVideoPortType_t); i++)
    {
        ret = dsGetVideoPort(portTypes[i], 0, &handle);
        UT_LOG_INFO("Invoking dsGetVideoPort() with port type %d", portTypes[i]);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("Failed to get video port handle\n");
            continue;
        }

        for(int j = 0; j < sizeof(hdcpVersions)/sizeof(dsHdcpProtocolVersion_t); j++)
        {
            hdcpCurrentProtocol = hdcpVersions[j];
            ret = dsSetHdmiPreference(handle, &hdcpCurrentProtocol);
            UT_LOG_INFO("Invoking dsSetHdmiPreference() with HDCP protocol version %d", hdcpCurrentProtocol);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("Failed to set HDCP protocol version\n");
                continue;
            }

            ret = dsGetHdmiPreference(handle, &hdcpCurrentProtocolGet);
            UT_LOG_INFO("Invoking dsGetHdmiPreference() and received HDCP protocol version %d", hdcpCurrentProtocolGet);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("Failed to get HDCP protocol version\n");
            }
            UT_ASSERT_EQUAL(hdcpCurrentProtocol, hdcpCurrentProtocolGet);
        }
    }

    ret = dsVideoPortTerm();
    UT_LOG_INFO("Invoking dsVideoPortTerm()");
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test for getting the color space of a video port
*
* This test verifies if the dsGetColorSpace API is able to successfully retrieve the color space of a video port. The color space value obtained is then compared with the value in the configuration YAML file to ensure correctness.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 012@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_GetColorSpace(void)
{
    gTestID = 12;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    dsDisplayColorSpace_t color_space;

    // Step 1: Call dsVideoPortInit
    ret = dsVideoPortInit();
    UT_LOG_INFO("Invoking dsVideoPortInit()");
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    // Loop through each type of video port
    for (dsVideoPortType_t type = dsVIDEOPORT_TYPE_RF; type < dsVIDEOPORT_TYPE_MAX; type++)
    {
        // Get the handle of the video port
        ret = dsGetVideoPort(type, 0, &handle);
        UT_LOG_DEBUG("Invoking dsGetVideoPort() with type: %d, index: 0", type);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetVideoPort failed with error: %d\n", ret);
            continue;
        }
        // Step 3: Call dsGetColorSpace
        ret = dsGetColorSpace(handle, &color_space);
        UT_LOG_DEBUG("Invoking dsGetColorSpace with handle: %ld\n", handle);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("Failed to get color space\n");
        }

        // Step 4: Compare the color space value with the value in the configuration YAML file
        UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(color_space, "Ports/1/colorspaces");
    }
    // Step 5: Call dsVideoPortTerm
    ret = dsVideoPortTerm();
    UT_LOG_INFO("Invoking dsVideoPortTerm()");
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to check the color depth capabilities of the sink device
*
* This function tests the color depth capabilities of the sink device by initializing the video port subsystem, getting the video port, checking the color depth capabilities, comparing the obtained capabilities with the values in the configuration YAML file, and finally terminating the video port subsystem. The function uses CUnit assertions to validate the return values of the API calls.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 013@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_CheckColorDepthCapabilities(void)
{
    gTestID = 13;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;
    intptr_t handle = 0;
    unsigned int colorDepthCapability = 0;

    // Step 1: Call dsVideoPortInit
    ret = dsVideoPortInit();
    UT_LOG_INFO("Invoking dsVideoPortInit()");
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    // Loop through each type of video port
    for (dsVideoPortType_t type = dsVIDEOPORT_TYPE_RF; type < dsVIDEOPORT_TYPE_MAX; type++)
    {
        // Get the handle of the video port
        ret = dsGetVideoPort(type, 0, &handle);
        UT_LOG_DEBUG("Invoking dsGetVideoPort() with type: %d, index: 0", type);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetVideoPort failed with error: %d\n", ret);
            continue;
        }

        // Step 3: Call dsColorDepthCapabilities
        ret = dsColorDepthCapabilities(handle, &colorDepthCapability);
        UT_LOG_DEBUG("Invoking dsColorDepthCapabilities with handle: %ld\n", handle);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("Failed to get color depth capabilities with error: %d\n", ret);
        }

        // Step 4: Compare the obtained color depth capabilities with the values in the configuration YAML file
        UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(colorDepthCapability, "Ports/1/Supported_color_depth_capabilities");
    }

    // Step 5: Call dsVideoPortTerm
    ret = dsVideoPortTerm();
    UT_LOG_INFO("Invoking dsVideoPortTerm()");
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test verifies the color depth of the video port
*
* In this test, the color depth of the video port is retrieved and checked. This is done to ensure that the video port is functioning correctly and is able to provide the correct color depth.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 014@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_VerifyColorDepth(void)
{
    gTestID = 14;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    unsigned int color_depth;
    dsVideoPortType_t type;

    ret = dsVideoPortInit();
    UT_LOG_INFO("Invoking dsVideoPortInit()");
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (type = dsVIDEOPORT_TYPE_RF; type < dsVIDEOPORT_TYPE_MAX; type++)
    {
        ret = dsGetVideoPort(type, 0, &handle);
        UT_LOG_DEBUG("Invoking dsGetVideoPort() with type= %d and index=0",type);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("Failed to get video port handle for type %d\n", type);
            continue;
        }

        ret = dsGetColorDepth(handle, &color_depth);
        UT_LOG_DEBUG("Invoking dsGetColorDepth with handle: %ld\n", handle);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("Failed to get color depth for video port type %d\n", type);
        }

        UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(color_depth, "color_depth");
    }

    ret = dsVideoPortTerm();
    UT_LOG_INFO("Invoking dsVideoPortTerm()");
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to verify the functionality of setting and getting the preferred color depth in dsVideoPort.
*
* In this test, the dsVideoPortInit function is first called to initialize the video port. Then, the dsGetVideoPort function is called to get the video port handle. The dsSetPreferredColorDepth function is then used to set the preferred color depth. The dsGetPreferredColorDepth function is used to get the color depth that was set. The set and get color depths are then compared to ensure they match. Finally, the dsVideoPortTerm function is called to terminate the video port.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 015@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_SetAndGetPreferredColorDepth_source(void)
{
    gTestID = 15;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    dsDisplayColorDepth_t colorDepth = dsDISPLAY_COLORDEPTH_8BIT;
    dsDisplayColorDepth_t getColorDepth;

    // Step 1: Call dsVideoPortInit
    UT_LOG_DEBUG("Invoking dsVideoPortInit()");
    ret = dsVideoPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    // Loop through each type of video port
    for (dsVideoPortType_t type = dsVIDEOPORT_TYPE_RF; type < dsVIDEOPORT_TYPE_MAX; type++)
    {
        // Get the handle of the video port
        ret = dsGetVideoPort(type, 0, &handle);
        UT_LOG_DEBUG("Invoking dsGetVideoPort() with type: %d, index: 0", type);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetVideoPort failed with error: %d\n", ret);
            continue;
        }

        // Step 3: Call dsSetPreferredColorDepth
        UT_LOG_DEBUG("Invoking dsSetPreferredColorDepth() with handle=%ld and colorDepth=%d", handle, colorDepth);
        ret = dsSetPreferredColorDepth(handle, colorDepth);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
        UT_LOG_ERROR("Failed to set preferred Color depth error: %d\n", ret);
        continue;
       }

        // Step 4: Call dsGetPreferredColorDepth
        UT_LOG_DEBUG("Invoking dsGetPreferredColorDepth() with handle=%ld", handle);
        ret = dsGetPreferredColorDepth(handle, &getColorDepth);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("Failed to get preferred Color depth error: %d\n", ret);
        }

        // Step 5: Compare the color depth value set in step 3 with the value obtained in step 4
        UT_LOG_DEBUG("Comparing set color depth=%d with get color depth=%d", colorDepth, getColorDepth);
        UT_ASSERT_EQUAL(colorDepth, getColorDepth);
    }

    // Step 6: Call dsVideoPortTerm
    UT_LOG_DEBUG("Invoking dsVideoPortTerm()");
    ret = dsVideoPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to verify the quantization range of the video port sink
*
* This test initializes the video port subsystem, gets the video port handle, retrieves the quantization range, and compares it with the value from a YAML file. It then terminates the video port subsystem. The test ensures that the video port subsystem and its APIs function as expected.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 016@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_VerifyQuantizationRange(void)
{
    gTestID = 16;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;
    intptr_t handle = 0;
    dsDisplayQuantizationRange_t quantization_range;

    // Step 1: Call dsVideoPortInit
    ret = dsVideoPortInit();
    UT_LOG_DEBUG("Invoking dsVideoPortInit()");
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    // Loop through each type of video port
    for (dsVideoPortType_t type = dsVIDEOPORT_TYPE_RF; type < dsVIDEOPORT_TYPE_MAX; type++)
    {
        // Get the handle of the video port
        ret = dsGetVideoPort(type, 0, &handle);
        UT_LOG_DEBUG("Invoking dsGetVideoPort() with type: %d, index: 0", type);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetVideoPort failed with error: %d\n", ret);
            continue;
        }

        // Step 3: Call dsGetQuantizationRange
        ret = dsGetQuantizationRange(handle, &quantization_range);
        UT_LOG_DEBUG("Invoking dsGetQuantizationRange() with handle=%ld", handle);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("Failed to get quantization range with error: %d\n", ret);
        }

        // Step 4: Compare the quantization range with the value from YAML file
        UT_ASSERT_KVP_EQUAL_PROFILE_UINT8(quantization_range, "Ports/1/quantization_ranges");
    }
    // Step 6: Call dsVideoPortTerm
    ret = dsVideoPortTerm();
    UT_LOG_DEBUG("Invoking dsVideoPortTerm()");
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test function is designed to test the dsVideoPort_GetMatrixCoefficients API
*
* This test function follows the steps outlined in the test case, invoking the necessary APIs and checking their return values using the CUnit assertion macros. It also logs the progress of the test using the provided logging functions.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 017@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsVideoPort_L2_Low-Level_TestSpecification.md](../../docs/pages/dsVideoPort_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsVideoPort_GetMatrixCoefficients(void)
{
    gTestID = 17;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    dsDisplayMatrixCoefficients_t matrix_coefficients;

    // Step 1: Call dsVideoPortInit
    UT_LOG_DEBUG("Invoking dsVideoPortInit");
    ret = dsVideoPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    // Loop through each type of video port
    for (dsVideoPortType_t type = dsVIDEOPORT_TYPE_RF; type < dsVIDEOPORT_TYPE_MAX; type++)
    {
        // Get the handle of the video port
        ret = dsGetVideoPort(type, 0, &handle);
        UT_LOG_DEBUG("Invoking dsGetVideoPort() with type: %d, index: 0", type);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetVideoPort failed with error: %d\n", ret);
            continue;
        }

        // Step 3: Call dsGetMatrixCoefficients
        UT_LOG_DEBUG("Invoking dsGetMatrixCoefficients with handle obtained from previous step");
        ret = dsGetMatrixCoefficients(handle, &matrix_coefficients);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetMatrixCoefficients failed with error: %d\n", ret);
        }

        UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(matrix_coefficients, "Ports/1/matrix_coefficients");
    }

    // Step 5: Call dsVideoPortTerm
    UT_LOG_DEBUG("Invoking dsVideoPortTerm");
    ret = dsVideoPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

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
    if (pSuite == NULL)
    {
        return -1;
    }
    // List of test function names and strings

    UT_add_test( pSuite, "l2_dsVideoPort_EnableDisableVideoPort", test_l2_dsVideoPort_EnableDisableVideoPort);
    UT_add_test( pSuite, "l2_dsVideoPort_VerifyDisplayConnectionStatus", test_l2_dsVideoPort_VerifyDisplayConnectionStatus);
    UT_add_test( pSuite, "l2_dsVideoPort_VerifyDisplaySurround_sink", test_l2_dsVideoPort_VerifyDisplaySurround_sink);
    UT_add_test( pSuite, "l2_dsVideoPort_VerifySurroundModeCapabilities_source", test_l2_dsVideoPort_VerifySurroundModeCapabilities_source);
    UT_add_test( pSuite, "l2_dsVideoPort_SetAndGetVideoPortProperties_source", test_l2_dsVideoPort_SetAndGetVideoPortProperties_source);
    UT_add_test( pSuite, "l2_dsVideoPort_VerifySupportedTvResolutions", test_l2_dsVideoPort_VerifySupportedTvResolutions);
    UT_add_test( pSuite, "l2_dsVideoPort_GetAndVerifyHDRCapabilities", test_l2_dsVideoPort_GetAndVerifyHDRCapabilities);
    UT_add_test( pSuite, "l2_dsVideoPort_SetAndGetForceDisable4KSupport", test_l2_dsVideoPort_SetAndGetForceDisable4KSupport);
    UT_add_test( pSuite, "l2_dsVideoPort_CheckHDCPStatus", test_l2_dsVideoPort_CheckHDCPStatus);
    UT_add_test( pSuite, "l2_dsVideoPort_VerifyHDCPProtocolStatus", test_l2_dsVideoPort_VerifyHDCPProtocolStatus);
    UT_add_test( pSuite, "l2_dsVideoPort_SetAndGetHdmiPreference", test_l2_dsVideoPort_SetAndGetHdmiPreference);
    UT_add_test( pSuite, "l2_dsVideoPort_GetColorSpace", test_l2_dsVideoPort_GetColorSpace);
    UT_add_test( pSuite, "l2_dsVideoPort_CheckColorDepthCapabilities", test_l2_dsVideoPort_CheckColorDepthCapabilities);
    UT_add_test( pSuite, "l2_dsVideoPort_VerifyColorDepth", test_l2_dsVideoPort_VerifyColorDepth);
    UT_add_test( pSuite, "l2_dsVideoPort_SetAndGetPreferredColorDepth_source", test_l2_dsVideoPort_SetAndGetPreferredColorDepth_source);
    UT_add_test( pSuite, "l2_dsVideoPort_VerifyQuantizationRange", test_l2_dsVideoPort_VerifyQuantizationRange);
    UT_add_test( pSuite, "l2_dsVideoPort_GetMatrixCoefficients", test_l2_dsVideoPort_GetMatrixCoefficients);

    return 0;
}