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
* @file test_l2_dsAudio.c
* @page dsAudio Level 2 Tests
*
* ## Module's Role
* This module includes Level 2 functional tests (success and failure scenarios).
* This is to ensure that the dsAudio APIs meet the requirements across all vendors.
*
* **Pre-Conditions:**  None@n
* **Dependencies:** None@n
*
* Ref to API Definition specification documentation : [dsAudio_halSpec.md](../../docs/pages/dsAudio_halSpec.md)
*/

#include <ut.h>
#include <ut_log.h>

#include <ut_kvp_profile.h>
#include <stdlib.h>
#include "dsAudio.h"

static int gTestGroup = 2;
static int gTestID = 1;

/**
* @brief This test verifies the functionality of enabling, disabling and verifying the status of an audio port.
*
* This test function initializes an audio port, enables it, verifies its status, disables it, and then verifies its status again. This is done for all types of audio ports and for all indices. The test ensures that the audio port can be successfully enabled and disabled, and that the status of the port accurately reflects these changes.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 001@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_EnableDisableAndVerifyAudioPortStatus_sink(void)
{
    gTestID = 1;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;
    intptr_t handle = 0;
    bool enabled = false;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (int type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
    {

        UT_LOG_DEBUG("Invoking dsGetAudioPort with type: %d and index: 0", type);
        ret = dsGetAudioPort(type, 0, &handle);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort failed with error: %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsEnableAudioPort with handle: %ld and enabled: true", handle);
        ret = dsEnableAudioPort(handle, true);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsEnableAudioPort failed with error: %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsIsAudioPortEnabled with handle: %ld", handle);
        ret = dsIsAudioPortEnabled(handle, &enabled);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_ASSERT_EQUAL(enabled, true);
        if (ret != dsERR_NONE || !enabled)
        {
            UT_LOG_ERROR("dsIsAudioPortEnabled failed with error: %d or port is not enabled", ret);
        }

        UT_LOG_DEBUG("Invoking dsEnableAudioPort with handle: %ld and enabled: false", handle);
        ret = dsEnableAudioPort(handle, false);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsEnableAudioPort failed with error: %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsIsAudioPortEnabled with handle: %ld", handle);
        ret = dsIsAudioPortEnabled(handle, &enabled);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_ASSERT_EQUAL(enabled, false);
        if (ret != dsERR_NONE || enabled)
        {
            UT_LOG_ERROR("dsIsAudioPortEnabled failed with error: %d or port is not disabled", ret);
        }
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test verifies the enabling, disabling and status verification of audio port source
*
* This test function initializes the audio port, gets the audio port, enables the audio port, checks if the audio port is enabled, disables the audio port, checks if the audio port is disabled and finally terminates the audio port. The test is designed to ensure the proper functioning of audio port operations.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 002@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_EnableDisableAndVerifyAudioPortStatus_source(void)
{
    gTestID = 2;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;
    intptr_t handle = 0;
    bool enabled = false;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (int i = 0; i < dsAUDIOPORT_TYPE_MAX; i++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort with type %d and index 0", i);
        ret = dsGetAudioPort(i, 0, &handle);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort failed with error %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsEnableAudioPort with handle %ld and enabled true", handle);
        ret = dsEnableAudioPort(handle, true);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsEnableAudioPort failed with error %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsIsAudioPortEnabled with handle %ld", handle);
        ret = dsIsAudioPortEnabled(handle, &enabled);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_ASSERT_EQUAL(enabled, true);
        if (ret != dsERR_NONE || !enabled)
        {
            UT_LOG_ERROR("dsIsAudioPortEnabled failed with error %d or port not enabled", ret);
        }

        UT_LOG_DEBUG("Invoking dsEnableAudioPort with handle %ld and enabled false", handle);
        ret = dsEnableAudioPort(handle, false);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsEnableAudioPort failed with error %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsIsAudioPortEnabled with handle %ld", handle);
        ret = dsIsAudioPortEnabled(handle, &enabled);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_ASSERT_EQUAL(enabled, false);
        if (ret != dsERR_NONE || enabled)
        {
            UT_LOG_ERROR("dsIsAudioPortEnabled failed with error %d or port not disabled", ret);
        }
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test checks the connection status of the headphone sink in the L2 dsAudio module
*
* This test initializes the audio port, gets the audio port for each type, checks if the headphone port is connected, and finally terminates the audio port. The test is designed to verify the correct functioning of the dsAudio module's headphone connection status checking mechanism.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 003@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_CheckHeadphoneConnectionStatus_sink(void)
{
    gTestID = 3;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    bool isConnected;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort with type: %d and index: 0", type);
        ret = dsGetAudioPort(type, 0, &handle);
        UT_LOG_DEBUG("Return status: %d, Handle: %ld", ret, handle);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort failed with error %d", ret);
            continue;
        }

        if (type == dsAUDIOPORT_TYPE_HEADPHONE)
        {
            UT_LOG_DEBUG("Invoking dsAudioOutIsConnected with handle: %ld", handle);
            ret = dsAudioOutIsConnected(handle, &isConnected);
            UT_LOG_DEBUG("Return status: %d, isConnected: %d", ret, isConnected);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            UT_ASSERT_EQUAL(isConnected, false);
            if (ret != dsERR_NONE || isConnected)
            {
                UT_LOG_ERROR("dsAudioOutIsConnected failed with error %d or Audio out is connected", ret);
            }
        }
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to retrieve and verify MS12 capabilities of the audio sink
*
* This test function is designed to retrieve and verify the MS12 capabilities of the audio sink. It initializes the audio port, gets the audio port with a specific type and index, retrieves the MS12 capabilities, and then terminates the audio port.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 004@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_RetrieveAndVerifyMS12Capabilities_sink(void)
{
    gTestID = 4;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t retStatus;
    intptr_t handle;
    int capabilities;
    dsAudioPortType_t type = dsAUDIOPORT_TYPE_SPEAKER;
    int index = 1;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    retStatus = dsAudioPortInit();
    UT_LOG_DEBUG("Return status: %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsGetAudioPort with type: %d and index: %d", type, index);
    retStatus = dsGetAudioPort(type, index, &handle);
    UT_LOG_DEBUG("Return status: %d, Handle: %ld", retStatus, handle);
    UT_ASSERT_EQUAL(retStatus, dsERR_NONE);
    if (retStatus != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetAudioPort failed with error %d", retStatus);
        dsAudioPortTerm();
        return;
    }

    UT_LOG_DEBUG("Invoking dsGetMS12Capabilities with handle: %ld", handle);
    retStatus = dsGetMS12Capabilities(handle, &capabilities);
    UT_LOG_DEBUG("Return status: %d, Capabilities: %d", retStatus, capabilities);
    UT_ASSERT_EQUAL(retStatus, dsERR_NONE);
    if (retStatus != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetMS12Capabilities failed with error %d", retStatus);
        dsAudioPortTerm();
        return;
    }

    UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(capabilities, "Ports/1/MS12_Capabilities");

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    retStatus = dsAudioPortTerm();
    UT_LOG_DEBUG("Return status: %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to retrieve and verify MS12 capabilities of a source
*
* This test aims to retrieve and verify the MS12 capabilities of a source. It initializes the audio port, gets the audio port with a specific type and index, retrieves the MS12 capabilities, and then terminates the audio port. The test ensures that all these operations are successful and the retrieved capabilities match the expected values.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 005@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_RetrieveAndVerifyMS12Capabilities_source(void)
{
    gTestID = 5;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    int capabilities;
    dsAudioPortType_t type = dsAUDIOPORT_TYPE_HDMI;
    int index = 0;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsGetAudioPort with type: %d and index: %d", type, index);
    ret = dsGetAudioPort(type, index, &handle);
    UT_LOG_DEBUG("Return status: %d, Handle: %ld", ret, handle);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetAudioPort failed with error %d", ret);
        dsAudioPortTerm();
        return;
    }

    UT_LOG_DEBUG("Invoking dsGetMS12Capabilities with handle: %ld", handle);
    ret = dsGetMS12Capabilities(handle, &capabilities);
    UT_LOG_DEBUG("Return status: %d, Capabilities: %d", ret, capabilities);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetMS12Capabilities failed with error %d", ret);
        dsAudioPortTerm();
        return;
    }

    UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(capabilities, "Ports/2/MS12_Capabilities");

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to verify the functionality of setting and getting audio compression for different audio port types.
*
* In this test, the dsAudioPortInit function is first invoked to initialize the audio port. Then, for each audio port type, the dsGetAudioPort function is invoked to get the handle of the audio port. For each compression level from 0 to 10, the dsSetAudioCompression function is invoked to set the audio compression level, and the dsGetAudioCompression function is invoked to get the set compression level. The set and got compression levels are then compared to verify if they are equal. Finally, the dsAudioPortTerm function is invoked to terminate the audio port.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 006@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_SetAndGetAudioCompression_sink(void)
{
    gTestID = 6;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    int compression, getCompression;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort with type: %d and index: 0", type);
        ret = dsGetAudioPort(type, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort failed with error: %d", ret);
            continue;
        }

        for (compression = 0; compression <= 10; compression++)
        {
            UT_LOG_DEBUG("Invoking dsSetAudioCompression with handle: %ld and compression: %d", handle, compression);
            ret = dsSetAudioCompression(handle, compression);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetAudioCompression failed with error: %d", ret);
                continue;
            }

            UT_LOG_DEBUG("Invoking dsGetAudioCompression with handle: %ld", handle);
            ret = dsGetAudioCompression(handle, &getCompression);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsGetAudioCompression failed with error: %d", ret);
            }

            UT_LOG_DEBUG("Compression set: %d, Compression got: %d", compression, getCompression);
            UT_ASSERT_EQUAL(compression, getCompression);
        }
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to verify the functionality of setting and getting audio compression in dsAudio API.
*
* In this test, the dsAudioPortInit function is first invoked to initialize the audio port. Then, for each type of audio port, the dsGetAudioPort function is called to get the handle of the audio port. For each compression level from 0 to 10, the dsSetAudioCompression function is used to set the compression level, and the dsGetAudioCompression function is used to get the compression level. The set and get compression levels are then compared to ensure they are equal. Finally, the dsAudioPortTerm function is invoked to terminate the audio port.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 007@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_SetAndGetAudioCompression_source(void)
{
    gTestID = 7;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    int compression, getCompression;
    dsAudioPortType_t portType;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (portType = dsAUDIOPORT_TYPE_ID_LR; portType < dsAUDIOPORT_TYPE_MAX; portType++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort with type: %d and index: 0", portType);
        ret = dsGetAudioPort(portType, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort failed with error: %d", ret);
            continue;
        }

        for (compression = 0; compression <= 10; compression++)
        {
            UT_LOG_DEBUG("Invoking dsSetAudioCompression with handle: %ld and compression: %d", handle, compression);
            ret = dsSetAudioCompression(handle, compression);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetAudioCompression failed with error: %d", ret);
                continue;
            }

            UT_LOG_DEBUG("Invoking dsGetAudioCompression with handle: %ld", handle);
            ret = dsGetAudioCompression(handle, &getCompression);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsGetAudioCompression failed with error: %d", ret);
            }

            UT_LOG_DEBUG("Compression level set: %d, Compression level got: %d", compression, getCompression);
            UT_ASSERT_EQUAL(compression, getCompression);
        }
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test is designed to set and get the Dialog Enhancement for dsAudio
*
* This test sets the Dialog Enhancement for dsAudio and then gets the Dialog Enhancement to verify if the set operation was successful. This is done for all audio port types and for two indexes. The test is designed to ensure the proper functioning of the dsAudio's Dialog Enhancement set and get operations.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 008@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_SetAndGetDialogEnhancement_sink(void)
{
    gTestID = 8;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    int level, getLevel;

    UT_LOG_DEBUG("Invoking dsAudioPortInit()");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort() with type: %d and index: 0", type);
        ret = dsGetAudioPort(type, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort() failed with error: %d", ret);
            continue;
        }

        for (level = 0; level <= 16; level++)
        {
            UT_LOG_DEBUG("Invoking dsSetDialogEnhancement() with handle: %ld and level: %d", handle, level);
            ret = dsSetDialogEnhancement(handle, level);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetDialogEnhancement() failed with error: %d", ret);
                continue;
            }

            UT_LOG_DEBUG("Invoking dsGetDialogEnhancement() with handle: %ld", handle);
            ret = dsGetDialogEnhancement(handle, &getLevel);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsGetDialogEnhancement() failed with error: %d", ret);
            }

            UT_LOG_DEBUG("Returned level: %d", getLevel);
            UT_ASSERT_EQUAL(getLevel, level);
        }
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm()");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to verify the functionality of setting and getting dialog enhancement in dsAudio.
*
* This test sets the Dialog Enhancement for dsAudio and then gets the Dialog Enhancement to verify if the set operation was successful. dsAudioPortInit function is invoked to initialize the audio port. Then, for each type of audio port and for each index, the dsGetAudioPort function is invoked to get the audio port. For each level from 0 to 16, the dsSetDialogEnhancement function is invoked to set the dialog enhancement level, and the dsGetDialogEnhancement function is invoked to get the dialog enhancement level. The level set and the level got are then compared to ensure they are equal. Finally, the dsAudioPortTerm function is invoked to terminate the audio port.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 009@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_SetAndGetDialogEnhancement_source(void)
{
    gTestID = 9;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    int level, getLevel;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort with type: %d and index: 0", type);
        ret = dsGetAudioPort(type, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort failed with error: %d", ret);
            continue;
        }

        for (level = 0; level <= 16; level++)
        {
            UT_LOG_DEBUG("Invoking dsSetDialogEnhancement with handle: %ld and level: %d", handle, level);
            ret = dsSetDialogEnhancement(handle, level);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetDialogEnhancement failed with error: %d", ret);
                continue;
            }

            UT_LOG_DEBUG("Invoking dsGetDialogEnhancement with handle: %ld", handle);
            ret = dsGetDialogEnhancement(handle, &getLevel);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsGetDialogEnhancement failed with error: %d", ret);
            }

            UT_LOG_DEBUG("Returned level: %d", getLevel);
            UT_ASSERT_EQUAL(level, getLevel);
        }
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test is designed to set and get the Dolby volume mode for different audio port types.
*
* This test initializes the audio port, then for each audio port type, it gets the audio port, sets the Dolby volume mode to true, gets the Dolby volume mode and checks if it is true, sets the Dolby volume mode to false, gets the Dolby volume mode and checks if it is false, and finally terminates the audio port. The test is designed to verify the functionality of setting and getting the Dolby volume mode for different audio port types.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 010@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_SetAndGetDolbyVolumeMode_sink(void)
{
    gTestID = 10;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    bool mode;
    dsAudioPortType_t portType;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (portType = dsAUDIOPORT_TYPE_ID_LR; portType < dsAUDIOPORT_TYPE_MAX; portType++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort with type %d and index 0", portType);
        ret = dsGetAudioPort(portType, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort failed with error %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsSetDolbyVolumeMode with handle %ld and mode true", handle);
        ret = dsSetDolbyVolumeMode(handle, true);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsSetDolbyVolumeMode failed with error %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsGetDolbyVolumeMode with handle %ld", handle);
        ret = dsGetDolbyVolumeMode(handle, &mode);
        if (ret != dsERR_NONE || !mode)
        {
            UT_LOG_ERROR("dsGetDolbyVolumeMode failed with error %d and mode %d", ret, mode);
        }

        UT_LOG_DEBUG("Invoking dsSetDolbyVolumeMode with handle %ld and mode false", handle);
        ret = dsSetDolbyVolumeMode(handle, false);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsSetDolbyVolumeMode failed with error %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsGetDolbyVolumeMode with handle %ld", handle);
        ret = dsGetDolbyVolumeMode(handle, &mode);
        if (ret != dsERR_NONE || mode)
        {
            UT_LOG_ERROR("dsGetDolbyVolumeMode failed with error %d and mode %d", ret, mode);
        }
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test function is designed to test the setting and getting of Dolby Volume Mode in dsAudio API.
*
* This function tests the dsAudio API's ability to set and get the Dolby Volume Mode. It does this by initializing the audio port, getting the audio port, setting the Dolby Volume Mode, getting the Dolby Volume Mode, and then terminating the audio port. The function checks for errors at each step and logs them if they occur.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 011@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_SetAndGetDolbyVolumeMode_source(void)
{
    gTestID = 11;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;
    intptr_t handle = 0;
    bool mode = false;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (int i = 0; i < dsAUDIOPORT_TYPE_MAX; i++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort with type: %d and index: 0", i);
        ret = dsGetAudioPort(i, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort failed with error: %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsSetDolbyVolumeMode with handle: %ld and mode: true", handle);
        ret = dsSetDolbyVolumeMode(handle, true);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsSetDolbyVolumeMode failed with error: %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsGetDolbyVolumeMode with handle: %ld", handle);
        ret = dsGetDolbyVolumeMode(handle, &mode);
        if (ret != dsERR_NONE || !mode)
        {
            UT_LOG_ERROR("dsGetDolbyVolumeMode failed with error: %d", ret);
        }

        UT_LOG_DEBUG("Invoking dsSetDolbyVolumeMode with handle: %ld and mode: false", handle);
        ret = dsSetDolbyVolumeMode(handle, false);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsSetDolbyVolumeMode failed with error: %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsGetDolbyVolumeMode with handle: %ld", handle);
        ret = dsGetDolbyVolumeMode(handle, &mode);
        if (ret != dsERR_NONE || mode)
        {
            UT_LOG_ERROR("dsGetDolbyVolumeMode failed with error: %d", ret);
        }
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to set and get the Intelligent Equalizer Mode for dsAudio
*
* In this test, the Intelligent Equalizer Mode for dsAudio is set and then retrieved to verify if the set operation was successful. This is done for all audio port types and for all modes from 0 to 6. The test is crucial to ensure the correct functioning of the Intelligent Equalizer Mode setting and retrieval operations in dsAudio.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 012@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_SetAndGetIntelligentEqualizerMode_sink(void)
{
    gTestID = 12;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;
    intptr_t handle = 0;
    int mode = 0;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort with type %d and index 0", type);
        ret = dsGetAudioPort(type, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort failed with error %d", ret);
            continue;
        }

        for (mode = 0; mode <= 6; mode++)
        {
            UT_LOG_DEBUG("Invoking dsSetIntelligentEqualizerMode with handle %ld and mode %d", handle, mode);
            ret = dsSetIntelligentEqualizerMode(handle, mode);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetIntelligentEqualizerMode failed with error %d", ret);
                continue;
            }

            int getMode = 0;
            UT_LOG_DEBUG("Invoking dsGetIntelligentEqualizerMode with handle %ld", handle);
            ret = dsGetIntelligentEqualizerMode(handle, &getMode);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsGetIntelligentEqualizerMode failed with error %d", ret);
            }

            UT_LOG_DEBUG("Returned mode %d", getMode);
            UT_ASSERT_EQUAL(mode, getMode);
        }
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test for setting and getting the Intelligent Equalizer Mode in dsAudio
*
* This test checks if the Intelligent Equalizer Mode can be set and retrieved correctly in dsAudio. It iterates over all audio port types and modes, setting the mode and then getting it to verify if the set value is correctly retrieved.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 013@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_SetAndGetIntelligentEqualizerMode_source(void)
{
    gTestID = 13;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;
    intptr_t handle = 0;
    int mode = 0;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort with type: %d and index: 0", type);
        ret = dsGetAudioPort(type, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort failed with error: %d", ret);
            continue;
        }

        for (mode = 0; mode <= 6; mode++)
        {
            UT_LOG_DEBUG("Invoking dsSetIntelligentEqualizerMode with handle: %ld and mode: %d", handle, mode);
            ret = dsSetIntelligentEqualizerMode(handle, mode);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetIntelligentEqualizerMode failed with error: %d", ret);
                continue;
            }

            int getMode = 0;
            UT_LOG_DEBUG("Invoking dsGetIntelligentEqualizerMode with handle: %ld", handle);
            ret = dsGetIntelligentEqualizerMode(handle, &getMode);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsGetIntelligentEqualizerMode failed with error: %d", ret);
            }

            UT_LOG_DEBUG("Returned mode: %d", getMode);
            UT_ASSERT_EQUAL(mode, getMode);
        }
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to verify the functionality of setting and getting the volume leveller for a given audio sink
*
* In this test, the dsAudioPortInit function is first invoked to initialize the audio port. Then, for each audio port type, the dsGetAudioPort function is called to get the handle of the audio port. The dsSetVolumeLeveller function is then used to set the volume leveller for the obtained audio port. The dsGetVolumeLeveller function is subsequently called to retrieve the volume leveller that was set. The retrieved volume leveller is then compared with the set volume leveller to verify if they match. Finally, the dsAudioPortTerm function is invoked to terminate the audio port.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 014@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_SetAndGetVolumeLeveller_sink(void)
{
    gTestID = 14;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t retStatus;
    intptr_t handle;
    dsVolumeLeveller_t volLevellerSet = {1, 5}, volLevellerGet;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    retStatus = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    for (dsAudioPortType_t portType = dsAUDIOPORT_TYPE_ID_LR; portType < dsAUDIOPORT_TYPE_MAX; portType++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort with portType: %d and index: 0", portType);
        retStatus = dsGetAudioPort(portType, 0, &handle);
        if (retStatus != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort failed with status: %d", retStatus);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsSetVolumeLeveller with handle: %ld and volLeveller: {mode: %d, level: %d}", handle, volLevellerSet.mode, volLevellerSet.level);
        retStatus = dsSetVolumeLeveller(handle, volLevellerSet);
        if (retStatus != dsERR_NONE)
        {
            UT_LOG_ERROR("dsSetVolumeLeveller failed with status: %d", retStatus);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsGetVolumeLeveller with handle: %ld", handle);
        retStatus = dsGetVolumeLeveller(handle, &volLevellerGet);
        if (retStatus != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetVolumeLeveller failed with status: %d", retStatus);
        }

        UT_LOG_DEBUG("Retrieved volLeveller: {mode: %d, level: %d}", volLevellerGet.mode, volLevellerGet.level);
        UT_ASSERT_EQUAL(volLevellerGet.mode, volLevellerSet.mode);
        UT_ASSERT_EQUAL(volLevellerGet.level, volLevellerSet.level);
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    retStatus = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to validate the setting and getting of volume leveller source in L2 dsAudio
*
* In this test, the dsAudioPortInit function is invoked to initialize the audio port. Then, for each audio port type and index, the dsGetAudioPort function is invoked to get the audio port. For each mode and level, the dsSetVolumeLeveller function is invoked to set the volume leveller. The dsGetVolumeLeveller function is then invoked to get the volume leveller. The mode and level of the set and get volume levellers are then compared. Finally, the dsAudioPortTerm function is invoked to terminate the audio port.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 015@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_SetAndGetVolumeLeveller_source(void)
{
    gTestID = 15;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    dsVolumeLeveller_t volLevellerSet = {1, 5}, volLevellerGet;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (int type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort with type=%d and index=0", type);
        ret = dsGetAudioPort(type, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort failed with status %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsSetVolumeLeveller with handle=%ld and mode=%d, level=%d", handle, volLevellerSet.mode, volLevellerSet.level);
        ret = dsSetVolumeLeveller(handle, volLevellerSet);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsSetVolumeLeveller failed with status %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsGetVolumeLeveller with handle=%ld", handle);
        ret = dsGetVolumeLeveller(handle, &volLevellerGet);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetVolumeLeveller failed with status %d", ret);
        }

        UT_LOG_DEBUG("Returned mode=%d, level=%d and status %d", volLevellerGet.mode, volLevellerGet.level, ret);
        UT_ASSERT_EQUAL(volLevellerGet.mode, volLevellerSet.mode);
        UT_ASSERT_EQUAL(volLevellerGet.level, volLevellerSet.level);
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to validate the setting and getting of Bass Enhancer for audio sink
*
* In this test, the dsAudioPortInit() function is invoked to initialize the audio port. Then, for each type of audio port and for each index, the dsGetAudioPort() function is invoked to get the audio port. A random boost value is set using dsSetBassEnhancer() function and then retrieved using dsGetBassEnhancer() function. The set and retrieved boost values are then compared for equality. Finally, the dsAudioPortTerm() function is invoked to terminate the audio port.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 016@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_SetAndGetBassEnhancer_sink(void)
{
    gTestID = 16;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;
    intptr_t handle = 0;
    int boost = 0;
    int setBoost = 0;

    UT_LOG_DEBUG("Invoking dsAudioPortInit()");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (int i = 0; i < dsAUDIOPORT_TYPE_MAX; i++)
    {

        UT_LOG_DEBUG("Invoking dsGetAudioPort() with type: %d and index: 0", i);
        ret = dsGetAudioPort(i, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort() failed with error: %d", ret);
            continue;
        }
        for (setBoost = 0; setBoost <= 100; setBoost++)
        {
            UT_LOG_DEBUG("Invoking dsSetBassEnhancer() with handle: %ld and boost: %d", handle, setBoost);
            ret = dsSetBassEnhancer(handle, setBoost);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetBassEnhancer() failed with error: %d", ret);
                continue;
            }

            UT_LOG_DEBUG("Invoking dsGetBassEnhancer() with handle: %ld", handle);
            ret = dsGetBassEnhancer(handle, &boost);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsGetBassEnhancer() failed with error: %d", ret);
            }

            UT_LOG_DEBUG("Boost value: %d", boost);
            UT_ASSERT_EQUAL(boost, setBoost);
        }
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm()");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test function is designed to test the setting and getting of Bass Enhancer source in the L2 dsAudio module.
*
* This function tests the dsSetBassEnhancer and dsGetBassEnhancer APIs of the L2 dsAudio module. It iterates over all audio port types and for each type, it sets the Bass Enhancer with a boost value and then gets the Bass Enhancer to verify if the set value is correctly retrieved. This is done to ensure the correct functionality of these APIs.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 017@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_SetAndGetBassEnhancer_source(void)
{
    gTestID = 17;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;
    intptr_t handle = 0;
    int boost = 0;
    int setBoost = 0;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort with type: %d and index: 0", type);
        ret = dsGetAudioPort(type, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort failed with error: %d", ret);
            continue;
        }

        for (setBoost = 0; setBoost <= 100; setBoost++)
        {
            UT_LOG_DEBUG("Invoking dsSetBassEnhancer with handle: %ld and boost: %d", handle, setBoost);
            ret = dsSetBassEnhancer(handle, setBoost);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetBassEnhancer failed with error: %d", ret);
                continue;
            }

            UT_LOG_DEBUG("Invoking dsGetBassEnhancer with handle: %ld", handle);
            ret = dsGetBassEnhancer(handle, &boost);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsGetBassEnhancer failed with error: %d", ret);
            }

            UT_LOG_DEBUG("Boost value: %d", boost);
            UT_ASSERT_EQUAL(boost, setBoost);
        }
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test verifies the enabling and functionality of the Surround Decoder sink in the L2 dsAudio module
*
* This test initializes the dsAudio port, gets the audio port for each type, enables the surround decoder, checks if the surround decoder is enabled, and finally terminates the dsAudio port. The test is designed to ensure that the surround decoder can be successfully enabled and function as expected in the L2 dsAudio module.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 018@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_EnableAndVerifySurroundDecoder_sink(void)
{
    gTestID = 18;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;
    intptr_t handle = 0;
    bool enabled = true;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (int i = dsAUDIOPORT_TYPE_ID_LR; i < dsAUDIOPORT_TYPE_MAX; i++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort with type %d and index 0", i);
        ret = dsGetAudioPort(i, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort failed with error %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsEnableSurroundDecoder with handle %ld and enabled set to true", handle);
        ret = dsEnableSurroundDecoder(handle, enabled);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsEnableSurroundDecoder failed with error %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsIsSurroundDecoderEnabled with handle %ld", handle);
        ret = dsIsSurroundDecoderEnabled(handle, &enabled);
        if (ret != dsERR_NONE || !enabled)
        {
            UT_LOG_ERROR("dsIsSurroundDecoderEnabled failed with error %d or enabled is not set", ret);
        }
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test verifies the functionality of enabling and verifying the surround decoder source in the L2 dsAudio module.
*
* This test function initializes the audio port, gets the audio port for each type and index, enables the surround decoder, checks if the surround decoder is enabled, and finally terminates the audio port. The test is designed to ensure that the surround decoder can be successfully enabled and verified for different types and indexes of audio ports.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 019@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_EnableAndVerifySurroundDecoder_source(void)
{
    gTestID = 19;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;
    intptr_t handle = 0;
    bool enabled = true;

    UT_LOG_DEBUG("Invoking dsAudioPortInit()");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (int type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
    {

        UT_LOG_DEBUG("Invoking dsGetAudioPort() with type: %d and index: 0", type);
        ret = dsGetAudioPort(type, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort() failed with error: %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsEnableSurroundDecoder() with handle: %ld and enabled: %d", handle, enabled);
        ret = dsEnableSurroundDecoder(handle, enabled);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsEnableSurroundDecoder() failed with error: %d", ret);
            continue;
        }

        bool isEnabled = false;
        UT_LOG_DEBUG("Invoking dsIsSurroundDecoderEnabled() with handle: %ld", handle);
        ret = dsIsSurroundDecoderEnabled(handle, &isEnabled);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsIsSurroundDecoderEnabled() failed with error: %d", ret);
        }

        UT_LOG_DEBUG("Surround Decoder enabled status: %d", isEnabled);
        UT_ASSERT_EQUAL(isEnabled, enabled);
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm()");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to verify the functionality of setting and getting DRC mode in dsAudio.
*
* In this test, the dsAudioPortInit() function is invoked to initialize the audio port. Then, for each type of audio port and for each index, the dsGetAudioPort() function is invoked to get the audio port. For each mode (0 and 1), the dsSetDRCMode() function is invoked to set the DRC mode and the dsGetDRCMode() function is invoked to get the DRC mode. The test asserts that the mode set is the same as the mode got. Finally, the dsAudioPortTerm() function is invoked to terminate the audio port.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 020@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_SetAndGetDRCMode_sink(void)
{
    gTestID = 20;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    int mode;
    int getMode;

    UT_LOG_DEBUG("Invoking dsAudioPortInit()");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (int type = 0; type < dsAUDIOPORT_TYPE_MAX; type++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort() with type=%d and index=0", type);
        ret = dsGetAudioPort(type, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort() failed with status: %d", ret);
            continue;
        }

        for (mode = 0; mode <= 1; mode++)
        {
            UT_LOG_DEBUG("Invoking dsSetDRCMode() with handle=%ld and mode=%d", handle, mode);
            ret = dsSetDRCMode(handle, mode);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetDRCMode() failed with status: %d", ret);
                continue;
            }

            UT_LOG_DEBUG("Invoking dsGetDRCMode() with handle=%ld", handle);
            ret = dsGetDRCMode(handle, &getMode);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsGetDRCMode() failed with status: %d", ret);
            }

            UT_LOG_DEBUG("Returned mode: %d", getMode);
            UT_ASSERT_EQUAL(getMode, mode);
        }
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm()");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to set and get the DRC mode for dsAudio
*
* In this test, the DRC mode for dsAudio is set and then retrieved to verify if the set operation was successful. This is done for all audio port types and indices. The test is crucial to ensure the correct functioning of the DRC mode setting and getting operations in the dsAudio API.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 021@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_SetAndGetDRCMode_source(void)
{
    gTestID = 21;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    int mode;

    UT_LOG_DEBUG("Invoking dsAudioPortInit()");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort() with type=%d and index=0", type);
        ret = dsGetAudioPort(type, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort() failed with error: %d", ret);
            continue;
        }

        for (mode = 0; mode <= 1; mode++)
        {
            UT_LOG_DEBUG("Invoking dsSetDRCMode() with handle=%ld and mode=%d", handle, mode);
            ret = dsSetDRCMode(handle, mode);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetDRCMode() failed with error: %d", ret);
                continue;
            }

            int getMode;
            UT_LOG_DEBUG("Invoking dsGetDRCMode() with handle=%ld", handle);
            ret = dsGetDRCMode(handle, &getMode);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsGetDRCMode() failed with error: %d", ret);
            }

            UT_LOG_DEBUG("Returned mode: %d", getMode);
            UT_ASSERT_EQUAL(getMode, mode);
        }
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm()");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to validate the setting and getting of Surround Virtualizer in dsAudio
*
* In this test, the dsAudioPortInit function is invoked to initialize the audio port. Then, for each audio port type and index, the dsGetAudioPort function is invoked to get the audio port handle. The dsSetSurroundVirtualizer function is then invoked to set the surround virtualizer for the obtained handle. The dsGetSurroundVirtualizer function is then invoked to get the surround virtualizer for the same handle. The obtained virtualizer is then compared with the set virtualizer to validate the set and get functionality. Finally, the dsAudioPortTerm function is invoked to terminate the audio port.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 022@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_SetAndGetSurroundVirtualizer_sink(void)
{
    gTestID = 22;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    dsSurroundVirtualizer_t virtualizer = {1, 50}, getVirtualizer;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (int i = dsAUDIOPORT_TYPE_ID_LR; i < dsAUDIOPORT_TYPE_MAX; i++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort with type: %d and index: 0", i);
        ret = dsGetAudioPort(i, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort failed with error: %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsSetSurroundVirtualizer with handle: %ld and virtualizer: {mode: %d, boost: %d}", handle, virtualizer.mode, virtualizer.boost);
        ret = dsSetSurroundVirtualizer(handle, virtualizer);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsSetSurroundVirtualizer failed with error: %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsGetSurroundVirtualizer with handle: %ld", handle);
        ret = dsGetSurroundVirtualizer(handle, &getVirtualizer);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetSurroundVirtualizer failed with error: %d", ret);
        }

        UT_LOG_DEBUG("Received virtualizer: {mode: %d, boost: %d}", getVirtualizer.mode, getVirtualizer.boost);
        UT_ASSERT_EQUAL(getVirtualizer.mode, virtualizer.mode);
        UT_ASSERT_EQUAL(getVirtualizer.boost, virtualizer.boost);
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test for setting and getting the Surround Virtualizer source in L2 dsAudio
*
* This test checks if the Surround Virtualizer source can be set and retrieved correctly in L2 dsAudio. It tests the dsSetSurroundVirtualizer and dsGetSurroundVirtualizer functions for all audio port types and indices. The test ensures that the set and retrieved values match, and that no errors occur during the process.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 023@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_SetAndGetSurroundVirtualizer_source(void)
{
    gTestID = 23;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    dsSurroundVirtualizer_t virtualizer, getVirtualizer;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (int i = 0; i < dsAUDIOPORT_TYPE_MAX; i++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort with type %d and index 0", i);
        ret = dsGetAudioPort(i, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort failed with error %d", ret);
            continue;
        }

        virtualizer.mode = 1;
        virtualizer.boost = rand() % 97;

        UT_LOG_DEBUG("Invoking dsSetSurroundVirtualizer with handle %ld and virtualizer mode %d, boost %d", handle, virtualizer.mode, virtualizer.boost);
        ret = dsSetSurroundVirtualizer(handle, virtualizer);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsSetSurroundVirtualizer failed with error %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsGetSurroundVirtualizer with handle %ld", handle);
        ret = dsGetSurroundVirtualizer(handle, &getVirtualizer);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetSurroundVirtualizer failed with error %d", ret);
        }

        UT_LOG_DEBUG("Received virtualizer mode %d, boost %d", getVirtualizer.mode, getVirtualizer.boost);
        UT_ASSERT_EQUAL(getVirtualizer.mode, virtualizer.mode);
        UT_ASSERT_EQUAL(getVirtualizer.boost, virtualizer.boost);
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to verify the functionality of setting and getting MISteering in dsAudio.
*
* In this test, we initialize the audio port and then for each type of audio port and for each index, we set the MISteering to true and then get the MISteering to verify if it has been set correctly. If any of these operations fail, we log the error and continue with the next iteration. Finally, we terminate the audio port and assert that the operation was successful.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 024@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_SetAndGetMISteering_sink(void)
{
    gTestID = 24;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    bool enabled;
    dsAudioPortType_t type;

    UT_LOG_DEBUG("Invoking dsAudioPortInit()");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
    {

        UT_LOG_DEBUG("Invoking dsGetAudioPort() with type=%d and index=0", type);
        ret = dsGetAudioPort(type, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort() failed with error: %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsSetMISteering() with handle=%ld and enabled=true", handle);
        ret = dsSetMISteering(handle, true);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsSetMISteering() failed with error: %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsGetMISteering() with handle=%ld", handle);
        ret = dsGetMISteering(handle, &enabled);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetMISteering() failed with error: %d", ret);
        }

        UT_LOG_DEBUG("Enabled status: %d", enabled);
        UT_ASSERT_EQUAL(enabled, true);
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm()");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test for setting and getting MISteering source in dsAudio
*
* This test checks if the MISteering source can be set and retrieved correctly in dsAudio. It does this by initializing the audio port, setting the MISteering source, retrieving it and then comparing the set and retrieved values. If they match, the test passes. If not, it fails. This test is important to ensure that the dsAudio API is working as expected.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 025@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_SetAndGetMISteering_source(void)
{
    gTestID = 25;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    bool enabled = true;
    bool getEnabled;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (int i = 0; i < dsAUDIOPORT_TYPE_MAX; i++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort with type: %d and index: 0", i);
        ret = dsGetAudioPort(i, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort failed with error: %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsSetMISteering with handle: %ld and enabled: %d", handle, enabled);
        ret = dsSetMISteering(handle, enabled);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsSetMISteering failed with error: %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsGetMISteering with handle: %ld", handle);
        ret = dsGetMISteering(handle, &getEnabled);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetMISteering failed with error: %d", ret);
        }

        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_ASSERT_EQUAL(getEnabled, enabled);
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to validate the setting and getting of Graphic Equalizer Mode in dsAudio
*
* In this test, the dsAudioPortInit() function is first invoked to initialize the audio port. Then, for each type of audio port and for each index, the dsGetAudioPort() function is invoked to get the audio port. For each mode from 0 to 3, the dsSetGraphicEqualizerMode() function is invoked to set the graphic equalizer mode and the dsGetGraphicEqualizerMode() function is invoked to get the graphic equalizer mode. The mode set and the mode got are then compared to ensure they are equal. Finally, the dsAudioPortTerm() function is invoked to terminate the audio port.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 026@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_SetAndGetGraphicEqualizerMode_sink(void)
{
    gTestID = 26;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;
    intptr_t handle = 0;
    int mode = 0;
    int getMode = 0;

    UT_LOG_DEBUG("Invoking dsAudioPortInit()");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (int type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort() with type: %d and index: 0", type);
        ret = dsGetAudioPort(type, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort() failed with error: %d", ret);
            continue;
        }
        for (mode = 0; mode <= 3; mode++)
        {
            UT_LOG_DEBUG("Invoking dsSetGraphicEqualizerMode() with handle: %ld and mode: %d", handle, mode);
            ret = dsSetGraphicEqualizerMode(handle, mode);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetGraphicEqualizerMode() failed with error: %d", ret);
                continue;
            }

            UT_LOG_DEBUG("Invoking dsGetGraphicEqualizerMode() with handle: %ld", handle);
            ret = dsGetGraphicEqualizerMode(handle, &getMode);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsGetGraphicEqualizerMode() failed with error: %d", ret);
            }

                UT_LOG_DEBUG("Returned mode: %d", getMode);
                UT_ASSERT_EQUAL(mode, getMode);
        }
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm()");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to validate the setting and getting of Graphic Equalizer Mode in dsAudio
*
* In this test, the dsAudioPortInit function is invoked to initialize the audio port. Then, for each audio port type, the dsGetAudioPort function is invoked to get the audio port handle. The dsSetGraphicEqualizerMode function is then invoked to set the graphic equalizer mode. The dsGetGraphicEqualizerMode function is then invoked to get the graphic equalizer mode and it is asserted that the mode is as expected. Finally, the dsAudioPortTerm function is invoked to terminate the audio port.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 027@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_SetAndGetGraphicEqualizerMode_source(void)
{
    gTestID = 27;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;
    intptr_t handle = 0;
    int mode = 0;
    int getmode = 0;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (int i = dsAUDIOPORT_TYPE_ID_LR; i < dsAUDIOPORT_TYPE_MAX; i++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort with type %d and index 0", i);
        ret = dsGetAudioPort(i, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort failed with error %d", ret);
            continue;
        }
        for (mode = 0; mode <= 3; mode++)
        {
            UT_LOG_DEBUG("Invoking dsSetGraphicEqualizerMode with handle %ld and mode:%d", handle, mode);
            ret = dsSetGraphicEqualizerMode(handle, mode);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetGraphicEqualizerMode failed with error %d", ret);
                continue;
            }

            UT_LOG_DEBUG("Invoking dsGetGraphicEqualizerMode with handle %ld", handle);
            ret = dsGetGraphicEqualizerMode(handle, &getmode);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsGetGraphicEqualizerMode failed with error %d", ret);
            }
            UT_ASSERT_EQUAL(mode, getmode );
        }
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to enable, disable and retrieve the LE configuration for the audio sink
*
* In this test, the dsAudioPortInit() function is invoked to initialize the audio port. Then, for each type of audio port and for each index up to 10, the dsGetAudioPort() function is invoked to get the audio port. If successful, the dsEnableLEConfig() function is invoked to enable the LE configuration. The dsGetLEConfig() function is then invoked to retrieve the LE configuration. If successful, the dsEnableLEConfig() function is invoked again to disable the LE configuration. The dsGetLEConfig() function is then invoked again to check if the LE configuration has been disabled. Finally, the dsAudioPortTerm() function is invoked to terminate the audio port.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 028@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_EnableDisableAndRetrieveLEConfig_sink(void)
{
    gTestID = 28;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;
    intptr_t handle = 0;
    bool enable = false;

    UT_LOG_DEBUG("Invoking dsAudioPortInit()");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (int i = 0; i < dsAUDIOPORT_TYPE_MAX; i++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort() with type=%d and index=0", i);
        ret = dsGetAudioPort(i, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort() failed with error: %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsEnableLEConfig() with handle=%ld and enable=true", handle);
        ret = dsEnableLEConfig(handle, true);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsEnableLEConfig() failed with error: %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsGetLEConfig() with handle=%ld", handle);
        ret = dsGetLEConfig(handle, &enable);
        if (ret != dsERR_NONE || !enable)
        {
            UT_LOG_ERROR("dsGetLEConfig() failed with error: %d", ret);
        }

        UT_LOG_DEBUG("Invoking dsEnableLEConfig() with handle=%ld and enable=false", handle);
        ret = dsEnableLEConfig(handle, false);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsEnableLEConfig() failed with error: %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsGetLEConfig() with handle=%ld", handle);
        ret = dsGetLEConfig(handle, &enable);
        if (ret != dsERR_NONE || enable)
        {
            UT_LOG_ERROR("dsGetLEConfig() failed with error: %d", ret);
        }
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm()");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to enable, disable and retrieve the LE configuration for different audio port types.
*
* In this test, the dsAudioPortInit function is first invoked to initialize the audio port. Then, for each audio port type, the dsGetAudioPort function is invoked to get the audio port. If successful, the dsEnableLEConfig function is invoked to enable the LE configuration. The dsGetLEConfig function is then invoked to check if the LE feature is enabled. If successful, the dsEnableLEConfig function is invoked again to disable the LE configuration. The dsGetLEConfig function is then invoked to check if the LE feature is disabled. Finally, the dsAudioPortTerm function is invoked to terminate the audio port.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 029@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_EnableDisableAndRetrieveLEConfig_source(void)
{
    gTestID = 29;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    bool enable;
    dsAudioPortType_t portType;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (portType = dsAUDIOPORT_TYPE_ID_LR; portType < dsAUDIOPORT_TYPE_MAX; portType++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort with type %d and index 0", portType);
        ret = dsGetAudioPort(portType, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort failed with error %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsEnableLEConfig with handle %ld and enable true", handle);
        ret = dsEnableLEConfig(handle, true);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsEnableLEConfig failed with error %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsGetLEConfig with handle %ld", handle);
        ret = dsGetLEConfig(handle, &enable);
        if (ret != dsERR_NONE || !enable)
        {
            UT_LOG_ERROR("dsGetLEConfig failed with error %d or LE feature is not enabled", ret);
        }

        UT_LOG_DEBUG("Invoking dsEnableLEConfig with handle %ld and enable false", handle);
        ret = dsEnableLEConfig(handle, false);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsEnableLEConfig failed with error %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsGetLEConfig with handle %ld", handle);
        ret = dsGetLEConfig(handle, &enable);
        if (ret != dsERR_NONE || enable)
        {
            UT_LOG_ERROR("dsGetLEConfig failed with error %d or LE feature is not disabled", ret);
        }
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to check MS12 decode support for dsAudio
*
* This test checks if the MS12 decode support is available for dsAudio. It initializes the audio port, gets the audio port for each type and index, checks if MS12 decode is available, and finally terminates the audio port. The test is designed to ensure the correct functioning of dsAudio's MS12 decode support.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 030@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_CheckMS12DecodeSupport_sink(void)
{
    gTestID = 30;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    bool hasMS12Decode;
    dsAudioPortType_t type;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_LOG_DEBUG("dsAudioPortInit returned %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort with type %d and index 0", type);
        ret = dsGetAudioPort(type, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort returned %d", ret);
            continue;
        }
        UT_LOG_DEBUG("dsGetAudioPort returned handle %ld", handle);
        if (type == dsAUDIOPORT_TYPE_SPEAKER)
        {
            UT_LOG_DEBUG("Invoking dsIsAudioMS12Decode with handle %ld", handle);
            ret = dsIsAudioMS12Decode(handle, &hasMS12Decode);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsIsAudioMS12Decode returned %d", ret);
            }
            UT_LOG_DEBUG("dsIsAudioMS12Decode returned %d", hasMS12Decode);

            UT_ASSERT_EQUAL_KVP_PROFILE_BOOL(hasMS12Decode, "Ports/1/IsMS12Decode");
        }
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_LOG_DEBUG("dsAudioPortTerm returned %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test checks the support for MS12 Decode in dsAudio
*
* This test initializes the audio port and checks for each type of audio port if MS12 decode is supported or not. It does this by invoking the dsIsAudioMS12Decode function for each port. The test also checks if the dsAudioPortInit and dsAudioPortTerm functions are working as expected.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 031@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_CheckMS12DecodeSupport_source(void)
{
    gTestID = 31;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;
    intptr_t handle = 0;
    bool hasMS12Decode = false;
    dsAudioPortType_t type;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_LOG_DEBUG("dsAudioPortInit returned %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
    {

        UT_LOG_DEBUG("Invoking dsGetAudioPort with type %d and index 0", type);
        ret = dsGetAudioPort(type, 0, &handle);
        UT_LOG_DEBUG("dsGetAudioPort returned handle %ld and status %d", handle, ret);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort failed with status %d", ret);
            continue;
        }
        if (type == dsAUDIOPORT_TYPE_HDMI)
        {
            UT_LOG_DEBUG("Invoking dsIsAudioMS12Decode with handle %ld", handle);
            ret = dsIsAudioMS12Decode(handle, &hasMS12Decode);
            UT_LOG_DEBUG("dsIsAudioMS12Decode returned hasMS12Decode %d and status %d", hasMS12Decode, ret);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsIsAudioMS12Decode failed with status %d", ret);
            }
            UT_ASSERT_EQUAL_KVP_PROFILE_BOOL(hasMS12Decode, "Ports/2/IsMS12Decode");
        }
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);
    UT_LOG_DEBUG("dsAudioPortTerm returned %d", ret);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test checks the support for MS11 decoding in dsAudio
*
* This test initializes the audio port and checks if MS11 decoding is supported for each audio port type. If the decoding is supported, it verifies the obtained values with the values retrieved from the 'Sink_AudioSettings.yaml' file. The test ends by terminating the audio port.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 032@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_CheckMS11DecodeSupport_sink(void)
{
    gTestID = 32;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;
    intptr_t handle = 0;
    bool HasMS11Decode = false;
    dsAudioPortType_t type;
    int index = 0;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for(type = 0; type < dsAUDIOPORT_TYPE_MAX; type++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort with type: %d and index: %d", type, index);
        ret = dsGetAudioPort(type, index, &handle);
        UT_LOG_DEBUG("Return status: %d, handle: %ld", ret, handle);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if(ret != dsERR_NONE)
        {
            continue;
        }
        if (type == dsAUDIOPORT_TYPE_SPEAKER)
        {
            UT_LOG_DEBUG("Invoking dsIsAudioMSDecode with handle: %ld", handle);
            ret = dsIsAudioMSDecode(handle, &HasMS11Decode);
            UT_LOG_DEBUG("Return status: %d, HasMS11Decode: %d", ret, HasMS11Decode);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            UT_ASSERT_EQUAL_KVP_PROFILE_BOOL(HasMS11Decode, "Ports/1/IsMS11Decode");
        }
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test checks the support for MS11 Decode in dsAudio
*
* This test initializes the audio port and checks for the support of MS11 Decode in each audio port. If the support is not found, it logs an error and continues with the next port. The test ends with the termination of the audio port.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 033@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_CheckMS11DecodeSupport_source(void)
{
    gTestID = 33;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;
    intptr_t handle;
    bool HasMS11Decode;
    dsAudioPortType_t type;
    int index = 0;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort with type: %d and index: %d", type, index);
        ret = dsGetAudioPort(type, index, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort failed with error: %d", ret);
            continue;
        }
        if (type == dsAUDIOPORT_TYPE_HDMI)
        {
            UT_LOG_DEBUG("Invoking dsIsAudioMSDecode with handle: %ld", handle);
            ret = dsIsAudioMSDecode(handle, &HasMS11Decode);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsIsAudioMSDecode failed with error: %d", ret);
            }
            UT_ASSERT_EQUAL_KVP_PROFILE_BOOL(HasMS11Decode, "Ports/2/IsMS11Decode");
        }
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to verify the MS12 Audio Profiles for a given sink
*
* This test case verifies the MS12 Audio Profiles for a given sink. It checks if the correct audio profiles are returned for a valid sink. This is important to ensure that the audio profiles are correctly configured and retrieved.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 034@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_VerifyMS12AudioProfiles_sink(void)
{
    gTestID = 34;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    dsMS12AudioProfileList_t profiles;
    int count = 0;
    ut_kvp_status_t status = {0};
    ut_kvp_instance_t *pInstance = NULL;
    char buffer[50];
    char result_kvp[UT_KVP_MAX_ELEMENT_SIZE]={0};


    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsGetAudioPort with dsAUDIOPORT_TYPE_SPEAKER and index 1");
    ret = dsGetAudioPort(dsAUDIOPORT_TYPE_SPEAKER, 1, &handle);
    UT_LOG_DEBUG("Return status: %d, Handle: %ld", ret, handle);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetHDMIARCPortId failed with status: %d", ret);
        UT_LOG_DEBUG("Invoking dsAudioPortTerm");
        dsAudioPortTerm();
        return;
    }

    UT_LOG_DEBUG("Invoking dsGetMS12AudioProfileList with valid handle");
    ret = dsGetMS12AudioProfileList(handle, &profiles);
    UT_LOG_DEBUG("Return status: %d, Profiles: %s, Profile Count: %d", ret, profiles.audioProfileList, profiles.audioProfileCount);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetMS12AudioProfileList failed with status: %d", ret);
        UT_LOG_DEBUG("Invoking dsAudioPortTerm");
        dsAudioPortTerm();
        return;
    }

    //UT_ASSERT_EQUAL_KVP_PROFILE_STRING(profiles.audioProfileList, "Ports/1/MS12_AudioProfiles");
    pInstance = ut_kvp_profile_getInstance();
    count = ut_kvp_getListCount(pInstance,"Ports/1/MS12_AudioProfiles");
    for (int i=0;i<count;i++)
    {
        sprintf(buffer, "Ports/1/MS12_AudioProfiles/%d", i);
        status = ut_kvp_getStringField(pInstance, buffer, result_kvp, UT_KVP_MAX_ELEMENT_SIZE);
        UT_ASSERT(status == UT_KVP_STATUS_SUCCESS );
        if(strstr(profiles.audioProfileList, result_kvp) != NULL)
        {
            UT_PASS("Audioprofile match");
            UT_LOG_DEBUG("%s is in %s", result_kvp, profiles.audioProfileList);
        }
        else
        {
            UT_FAIL("Audioprofile mismatch");
            UT_LOG_DEBUG("%s is not in %s", result_kvp, profiles.audioProfileList);
        }
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to validate the setting and getting of MS12 Audio Profile for different audio ports.
*
* In this test, the dsAudioPortInit() function is first invoked to initialize the audio port. Then, for each type of audio port, the dsGetAudioPort() function is invoked to get the handle of the audio port. The dsGetMS12AudioProfileList() function is then invoked to get the list of MS12 audio profiles. For each profile in the list, the dsSetMS12AudioProfile() function is invoked to set the profile, and the dsGetMS12AudioProfile() function is invoked to get the profile. The set and get profiles are then compared for equality. Finally, the dsAudioPortTerm() function is invoked to terminate the audio port. The test ensures that all these functions work as expected for different types of audio ports and profiles.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 035@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_SetAndGetMS12AudioProfile_sink(void)
{
    gTestID = 35;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    dsMS12AudioProfileList_t profiles;
    char profile[MAX_PROFILE_LIST_BUFFER_LEN];

    UT_LOG_DEBUG("Invoking dsAudioPortInit()");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (int i = 0; i < dsAUDIOPORT_TYPE_MAX; i++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort() with type=%d and index=0", i);
        ret = dsGetAudioPort(i, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort() failed with status=%d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsGetMS12AudioProfileList() with handle=%ld", handle);
        ret = dsGetMS12AudioProfileList(handle, &profiles);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetMS12AudioProfileList() failed with status=%d", ret);
        }

        char *profileName = strtok(profiles.audioProfileList, ",");
        while (profileName != NULL)
        {
            UT_LOG_DEBUG("Invoking dsSetMS12AudioProfile() with handle=%ld and profile=%s", handle, profileName);
            ret = dsSetMS12AudioProfile(handle, profileName);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetMS12AudioProfile() failed with status=%d", ret);
                continue;
            }

            UT_LOG_DEBUG("Invoking dsGetMS12AudioProfile() with handle=%ld", handle);
            ret = dsGetMS12AudioProfile(handle, profile);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsGetMS12AudioProfile() failed with status=%d", ret);
            }

            UT_ASSERT_STRING_EQUAL(profile, profileName);
            profileName = strtok(NULL, ",");
        }
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm()");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test for getting HDMI ARC port ID for sink device
*
* This test function initializes the audio port subsystem, gets the HDMI ARC port ID for the sink device, compares the port ID with the value from the YAML file, and then terminates the audio port subsystem. It uses the Cunit assertion functions to check the return values of the API calls and the macro function to compare the port ID with the value from the YAML file.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 036@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_GetHDMIARCPortId_sink(void)
{
    gTestID = 36;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t retStatus;
    int portId;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    retStatus = dsAudioPortInit();
    UT_LOG_DEBUG("Return status: %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsGetHDMIARCPortId with valid integer pointer");
    retStatus = dsGetHDMIARCPortId(&portId);
    UT_LOG_DEBUG("Return status: %d, Port ID: %d", retStatus, portId);
    UT_ASSERT_EQUAL(retStatus, dsERR_NONE);
    if (retStatus != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetHDMIARCPortId failed with status: %d", retStatus);
        UT_LOG_DEBUG("Invoking dsAudioPortTerm");
        dsAudioPortTerm();
        return;
    }

    UT_LOG_DEBUG("Checking port ID with value from YAML file");
    UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(portId, "Ports/2/Arc_Port");

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    retStatus = dsAudioPortTerm();
    UT_LOG_DEBUG("Return status: %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test for setting and getting the stereo mode of an audio sink
*
* This test checks if the stereo mode of an audio sink can be set and retrieved correctly. It does this by first initializing the audio port, then getting the audio port for each type and index. It then sets the stereo mode for the retrieved audio port and checks if the set mode can be retrieved correctly. If any of these operations fail, it logs an error and continues with the next iteration. Finally, it terminates the audio port and checks if the termination was successful.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 037@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_SetAndGetStereoMode_sink(void)
{
    gTestID = 37;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    dsAudioStereoMode_t getmode ,mode;

    UT_LOG_DEBUG("Invoking dsAudioPortInit()");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (int i = 0; i < dsAUDIOPORT_TYPE_MAX; i++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort() with type=%d and index=0", i);
        ret = dsGetAudioPort(i, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort() failed with status: %d", ret);
            continue;
        }
        for (int j = dsAUDIO_STEREO_MONO; j < dsAUDIO_STEREO_MAX; j++)
        {
            mode = (dsAudioStereoMode_t)j;
            UT_LOG_DEBUG("Invoking dsSetStereoMode() with handle=%ld and mode=%d", handle, mode);
            ret = dsSetStereoMode(handle, mode);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetStereoMode() failed with status: %d", ret);
                continue;
            }

            UT_LOG_DEBUG("Invoking dsGetStereoMode() with handle=%ld", handle);
            ret = dsGetStereoMode(handle, &getmode);
            if (ret != dsERR_NONE)
            {
               UT_LOG_ERROR("dsGetStereoMode() failed with status: %d", ret);
            }

            UT_LOG_DEBUG("Stereo mode: %d and return status: %d", getmode, ret);
            UT_ASSERT_EQUAL(mode, getmode);
        }
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm()");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test for setting and getting the stereo mode of a source in L2 dsAudio
*
* This test checks if the stereo mode of a source can be set and retrieved correctly using the dsAudio API. It iterates over all audio port types and stereo modes, sets the stereo mode, retrieves it and checks if the set and retrieved modes match.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 038@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_SetAndGetStereoMode_source(void)
{
    gTestID = 38;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    dsAudioStereoMode_t mode, getMode;

    UT_LOG_DEBUG("Invoking dsAudioPortInit()");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (int i = 0; i < dsAUDIOPORT_TYPE_MAX; i++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort() with type %d", i);
        ret = dsGetAudioPort(i, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort() failed with status %d", ret);
            continue;
        }

        for (int j = dsAUDIO_STEREO_MONO; j < dsAUDIO_STEREO_MAX; j++)
        {
            mode = (dsAudioStereoMode_t)j;
            UT_LOG_DEBUG("Invoking dsSetStereoMode() with handle %ld and mode %d", handle, mode);
            ret = dsSetStereoMode(handle, mode);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetStereoMode() failed with status %d", ret);
                continue;
            }

            UT_LOG_DEBUG("Invoking dsGetStereoMode() with handle %ld", handle);
            ret = dsGetStereoMode(handle, &getMode);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsGetStereoMode() failed with status %d", ret);
            }

            UT_LOG_DEBUG("Returned mode %d", getMode);
            UT_ASSERT_EQUAL(mode, getMode);
        }
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm()");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to validate the setting and getting of Stereo Auto mode in dsAudio API
*
* This test function tests the setting and getting of Stereo Auto mode in dsAudio API. It first initializes the audio port, then for each audio port type, it gets the audio port, sets the Stereo Auto mode, gets the Stereo Auto mode and validates it. The test is designed to ensure that the dsAudio API's set and get functions for Stereo Auto mode are working as expected.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 039@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_SetAndGetStereoAuto_sink(void)
{
    gTestID = 39;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    int autoMode = 1;
    dsAudioPortType_t portType;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (portType = dsAUDIOPORT_TYPE_ID_LR; portType < dsAUDIOPORT_TYPE_MAX; portType++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort with type %d and index 0", portType);
        ret = dsGetAudioPort(portType, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort failed with error %d", ret);
            continue;
        }
        UT_LOG_DEBUG("Handle: %ld", handle);

        UT_LOG_DEBUG("Invoking dsSetStereoAuto with handle %ld and autoMode %d", handle, autoMode);
        ret = dsSetStereoAuto(handle, autoMode);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsSetStereoAuto failed with error %d", ret);
            continue;
        }

        int getAutoMode;
        UT_LOG_DEBUG("Invoking dsGetStereoAuto with handle %ld", handle);
        ret = dsGetStereoAuto(handle, &getAutoMode);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetStereoAuto failed with error %d", ret);
        }
        UT_LOG_DEBUG("AutoMode: %d", getAutoMode);

        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_ASSERT_EQUAL(getAutoMode, autoMode);
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test for setting and getting audio gain for different audio ports
*
* This test is designed to verify the functionality of setting and getting audio gain for different audio ports. It tests the dsSetAudioGain and dsGetAudioGain functions by setting a range of gain values and then getting the gain value to verify if the set value is correctly retrieved.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 040@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_SetAndGetAudioGain_sink(void)
{
    gTestID = 40;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    float gain, getGain;
    dsAudioPortType_t portType;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (portType = dsAUDIOPORT_TYPE_ID_LR; portType < dsAUDIOPORT_TYPE_MAX; portType++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort with type=%d and index=0", portType);
        ret = dsGetAudioPort(portType, 0, &handle);
        if (ret != dsERR_NONE)
        {
            continue;
        }
        UT_ASSERT_EQUAL(ret, dsERR_NONE);

        for (gain = -2080; gain <= 480; gain += 10)
        {
            UT_LOG_DEBUG("Invoking dsSetAudioGain with handle=%ld and gain=%f", handle, gain);
            ret = dsSetAudioGain(handle, gain);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetAudioGain failed with status=%d", ret);
                continue;
            }
            UT_ASSERT_EQUAL(ret, dsERR_NONE);

            UT_LOG_DEBUG("Invoking dsGetAudioGain with handle=%ld", handle);
            ret = dsGetAudioGain(handle, &getGain);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsGetAudioGain failed with status=%d", ret);
            }
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            UT_ASSERT_EQUAL(gain, getGain);
        }
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to set and get the audio level for a sink
*
* In this test, the audio level for a sink is set and then retrieved to verify if the set operation was successful. This is done for all audio port types and for all ports. The test is crucial to ensure the correct functioning of the audio level setting and getting operations.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 041@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_SetAndGetAudioLevel_sink(void)
{
    gTestID = 41;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    float level, getLevel;
    dsAudioPortType_t portType;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (portType = dsAUDIOPORT_TYPE_ID_LR; portType < dsAUDIOPORT_TYPE_MAX; portType++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort with type=%d and index=0", portType);
        ret = dsGetAudioPort(portType, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort failed with error: %d", ret);
            continue;
        }

        for (level = 0; level <= 100; level++)
        {
            UT_LOG_DEBUG("Invoking dsSetAudioLevel with handle=%ld and level=%f", handle, level);
            ret = dsSetAudioLevel(handle, level);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetAudioLevel failed with error: %d", ret);
                continue;
            }

            UT_LOG_DEBUG("Invoking dsGetAudioLevel with handle=%ld", handle);
            ret = dsGetAudioLevel(handle, &getLevel);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsGetAudioLevel failed with error: %d", ret);
            }

            UT_LOG_DEBUG("Returned level=%f and status=%d", getLevel, ret);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            UT_ASSERT_EQUAL(level, getLevel);
        }
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test verifies the functionality of audio mute in dsAudio API
*
* This test case is designed to verify the audio mute functionality of the dsAudio API. It tests the ability of the API to mute and unmute the audio, and to correctly report the mute status. This is important to ensure that the API is correctly controlling the audio output and that it can accurately report the current mute status.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 042@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_AudioMuteVerification_sink(void)
{
    gTestID = 42;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;
    intptr_t handle = 0;
    bool mute = false;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (int type = 0; type < dsAUDIOPORT_TYPE_MAX; type++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort with type: %d and index: 0", type);
        ret = dsGetAudioPort(type, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort failed with error: %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsSetAudioMute with handle: %ld and mute: true", handle);
        ret = dsSetAudioMute(handle, true);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsSetAudioMute failed with error: %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsIsAudioMute with handle: %ld", handle);
        ret = dsIsAudioMute(handle, &mute);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_ASSERT_EQUAL(mute, true);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsIsAudioMute failed with error: %d", ret);
        }

        UT_LOG_DEBUG("Invoking dsSetAudioMute with handle: %ld and mute: false", handle);
        ret = dsSetAudioMute(handle, false);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsSetAudioMute failed with error: %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsIsAudioMute with handle: %ld", handle);
        ret = dsIsAudioMute(handle, &mute);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_ASSERT_EQUAL(mute, false);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsIsAudioMute failed with error: %d", ret);
        }

    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test verifies the functionality of audio mute in dsAudio API
*
* This test case is designed to verify the audio mute functionality of the dsAudio API. It tests the ability of the API to correctly mute and unmute the audio, and to correctly report the mute status. This is important to ensure that the API is correctly controlling the audio output and that it can accurately report the current mute status.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 043@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_AudioMuteVerification_source(void)
{
    gTestID = 43;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    bool muted;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_LOG_DEBUG("dsAudioPortInit returned %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort with type %d and index 0", type);
        ret = dsGetAudioPort(type, 0, &handle);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_LOG_DEBUG("dsGetAudioPort returned handle %ld and status %d", handle, ret);

        if (ret != dsERR_NONE)
        {
            continue;
        }

        UT_LOG_DEBUG("Invoking dsSetAudioMute with handle %ld and mute true", handle);
        ret = dsSetAudioMute(handle, true);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_LOG_DEBUG("dsSetAudioMute returned status %d", ret);

        UT_LOG_DEBUG("Invoking dsIsAudioMute with handle %ld", handle);
        ret = dsIsAudioMute(handle, &muted);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_ASSERT_EQUAL(muted, true);
        UT_LOG_DEBUG("dsIsAudioMute returned muted %d and status %d", muted, ret);

        UT_LOG_DEBUG("Invoking dsSetAudioMute with handle %ld and mute false", handle);
        ret = dsSetAudioMute(handle, false);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_LOG_DEBUG("dsSetAudioMute returned status %d", ret);

        UT_LOG_DEBUG("Invoking dsIsAudioMute with handle %ld", handle);
        ret = dsIsAudioMute(handle, &muted);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_ASSERT_EQUAL(muted, false);
        UT_LOG_DEBUG("dsIsAudioMute returned muted %d and status %d", muted, ret);
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_LOG_DEBUG("dsAudioPortTerm returned %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to set and get the audio delay for a sink
*
* In this test, the audio delay for a sink is set and then retrieved to verify if the set value is correctly stored and retrieved. This is done for all audio port types. The test is crucial to ensure the correct functioning of audio delay setting and retrieval in the system.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 044@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_SetAndGetAudioDelay_sink(void)
{
    gTestID = 44;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    uint32_t setDelay = 100;
    uint32_t getDelay;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (dsAudioPortType_t port = dsAUDIOPORT_TYPE_ID_LR; port < dsAUDIOPORT_TYPE_MAX; port++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort with port type %d and index 0", port);
        ret = dsGetAudioPort(port, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort failed with error %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsSetAudioDelay with handle and delay %d ms", setDelay);
        ret = dsSetAudioDelay(handle, setDelay);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsSetAudioDelay failed with error %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsGetAudioDelay with handle");
        ret = dsGetAudioDelay(handle, &getDelay);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioDelay failed with error %d", ret);
        }

        UT_LOG_DEBUG("Retrieved audio delay: %d ms", getDelay);
        UT_ASSERT_EQUAL(getDelay, setDelay);
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test for setting and getting audio delay source in L2 dsAudio
*
* This test checks if the audio delay source can be set and retrieved correctly in L2 dsAudio. It tests the dsSetAudioDelay and dsGetAudioDelay functions for all audio port types. If the set and get values match for all types, the test passes.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 045@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_SetAndGetAudioDelay_source(void)
{
    gTestID = 45;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    uint32_t delaySet = 100;
    uint32_t delayGet;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort with type: %d and index: 0", type);
        ret = dsGetAudioPort(type, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort failed with error: %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsSetAudioDelay with handle: %ld and delay: %d", handle, delaySet);
        ret = dsSetAudioDelay(handle, delaySet);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsSetAudioDelay failed with error: %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsGetAudioDelay with handle: %ld", handle);
        ret = dsGetAudioDelay(handle, &delayGet);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioDelay failed with error: %d", ret);
        }

        UT_LOG_DEBUG("Received delay: %d", delayGet);
        UT_ASSERT_EQUAL(delayGet, delaySet);
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test verifies the Atmos capabilities of the sink
*
* In this test, the Atmos capabilities of the sink are verified by initializing the audio port, getting the audio port with type speaker and index 1, getting the sink device Atmos capability, and finally terminating the audio port. The test ensures that all these operations are successful and the returned values are as expected.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 046@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_VerifyAtmosCapabilities_sink(void)
{
    gTestID = 46;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;
    intptr_t handle = 0;
    dsATMOSCapability_t capability;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_LOG_DEBUG("dsAudioPortInit returned %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsGetAudioPort with type=dsAUDIOPORT_TYPE_SPEAKER and index=1");
    ret = dsGetAudioPort(dsAUDIOPORT_TYPE_SPEAKER, 1, &handle);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    UT_LOG_DEBUG("dsGetAudioPort returned %d and handle=%ld", ret, handle);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetAudioPort failed with status: %d", ret);
        UT_LOG_DEBUG("Invoking dsAudioPortTerm");
        dsAudioPortTerm();
        return;
    }

    UT_LOG_DEBUG("Invoking dsGetSinkDeviceAtmosCapability with handle=%ld", handle);
    ret = dsGetSinkDeviceAtmosCapability(handle, &capability);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    UT_LOG_DEBUG("dsGetSinkDeviceAtmosCapability returned %d and capability=%d", ret, capability);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetSinkDeviceAtmosCapability failed with status: %d", ret);
        UT_LOG_DEBUG("Invoking dsAudioPortTerm");
        dsAudioPortTerm();
        return;
    }

    UT_ASSERT_KVP_EQUAL_PROFILE_UINT8(capability, "Ports/1/ATMOS_Capabilities");

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_LOG_DEBUG("dsAudioPortTerm returned %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to verify the functionality of the dsAudio_GetAudioCapabilities_sink API
*
* This test case is designed to validate the dsAudio_GetAudioCapabilities_sink API. The test case will initialize the audio port, get the audio port with type as sink and index as 0, get the audio capabilities with the handle obtained from the previous step, and finally terminate the audio port. The test case will assert the return status of each operation to ensure they are successful.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 047@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_GetAudioCapabilities_sink(void)
{
    gTestID = 47;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t retStatus;
    intptr_t handle;
    int capabilities;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    retStatus = dsAudioPortInit();
    UT_LOG_DEBUG("Return status: %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsGetAudioPort with type as sink and index as 0");
    retStatus = dsGetAudioPort(dsAUDIOPORT_TYPE_SPEAKER, 0, &handle);
    UT_LOG_DEBUG("Return status: %d, Handle: %ld", retStatus, handle);
    UT_ASSERT_EQUAL(retStatus, dsERR_NONE);
    if (retStatus != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetAudioPort failed with status: %d", retStatus);
        UT_LOG_DEBUG("Invoking dsAudioPortTerm");
        dsAudioPortTerm();
        return;
    }

    UT_LOG_DEBUG("Invoking dsGetAudioCapabilities with handle obtained from previous step");
    retStatus = dsGetAudioCapabilities(handle, &capabilities);
    UT_LOG_DEBUG("Return status: %d, Capabilities: %d", retStatus, capabilities);
    UT_ASSERT_EQUAL(retStatus, dsERR_NONE);
    if (retStatus != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetAudioCapabilities failed with status: %d", retStatus);
        UT_LOG_DEBUG("Invoking dsAudioPortTerm");
        dsAudioPortTerm();
        return;
    }

    UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(capabilities, "Audio_Capabilities");

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    retStatus = dsAudioPortTerm();
    UT_LOG_DEBUG("Return status: %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to verify the functionality of the dsAudio_GetAudioCapabilities API
*
* This test case invokes the dsAudio_GetAudioCapabilities API with valid parameters and checks if the API returns the correct audio capabilities. The test case also checks if the API handles error conditions correctly.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 048@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_GetAudioCapabilities_source(void)
{
    gTestID = 48;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;
    intptr_t handle = 0;
    int capabilities = 0;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for(int index = 0; index < dsAUDIOPORT_TYPE_MAX; index++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort with valid parameters");
        ret = dsGetAudioPort(index, 0, &handle);
        UT_LOG_DEBUG("Handle: %ld, Return status: %d", handle, ret);
        if(ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort failed with status: %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsGetAudioCapabilities with handle obtained from previous step");
        ret = dsGetAudioCapabilities(handle, &capabilities);
        UT_LOG_DEBUG("Capabilities: %d, Return status: %d", capabilities, ret);
        if(ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioCapabilities failed with status: %d", ret);
        }

        UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(capabilities, "Audio_Capabilities");
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test function is designed to test the enabling, disabling and retrieval of audio mixing in the dsAudio API.
*
* This test function iterates over all audio ports, enabling and disabling audio mixing, and then retrieving the state to verify the operation was successful. It tests the robustness and correctness of the dsAudio API's audio mixing functionality.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 049@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_EnableDisableRetrieveAudioMixing_sink(void)
{
    gTestID = 49;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;
    intptr_t handle = 0;
    bool mixing = false;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (int type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort with type: %d and index: 0", type);
        ret = dsGetAudioPort(type, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort failed with error: %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsSetAssociatedAudioMixing with handle: %ld and mixing: true", handle);
        ret = dsSetAssociatedAudioMixing(handle, true);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsSetAssociatedAudioMixing failed with error: %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsGetAssociatedAudioMixing with handle: %ld", handle);
        ret = dsGetAssociatedAudioMixing(handle, &mixing);
        if (ret != dsERR_NONE || !mixing)
        {
            UT_LOG_ERROR("dsGetAssociatedAudioMixing failed with error: %d", ret);
        }

        UT_LOG_DEBUG("Invoking dsSetAssociatedAudioMixing with handle: %ld and mixing: false", handle);
        ret = dsSetAssociatedAudioMixing(handle, false);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsSetAssociatedAudioMixing failed with error: %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsGetAssociatedAudioMixing with handle: %ld", handle);
        ret = dsGetAssociatedAudioMixing(handle, &mixing);
        if (ret != dsERR_NONE || mixing)
        {
            UT_LOG_ERROR("dsGetAssociatedAudioMixing failed with error: %d", ret);
        }
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test function is designed to test the enabling, disabling and retrieval of audio mixing source in L2 dsAudio.
*
* This function tests the initialization of audio port, getting the audio port, setting and getting the associated audio mixing for each audio port type. It also tests the termination of audio port. The purpose of this test is to ensure the correct functionality of these operations in the dsAudio API.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 050@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_EnableDisableRetrieveAudioMixing_source(void)
{
    gTestID = 50;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;
    intptr_t handle = 0;
    bool mixing = false;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (int i = dsAUDIOPORT_TYPE_ID_LR; i < dsAUDIOPORT_TYPE_MAX; i++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort with type %d and index 0", i);
        ret = dsGetAudioPort(i, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort failed with error %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsSetAssociatedAudioMixing with handle %ld and mixing true", handle);
        ret = dsSetAssociatedAudioMixing(handle, true);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsSetAssociatedAudioMixing failed with error %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsGetAssociatedAudioMixing with handle %ld", handle);
        ret = dsGetAssociatedAudioMixing(handle, &mixing);
        if (ret != dsERR_NONE || !mixing)
        {
            UT_LOG_ERROR("dsGetAssociatedAudioMixing failed with error %d or mixing is not true", ret);
        }

        UT_LOG_DEBUG("Invoking dsSetAssociatedAudioMixing with handle %ld and mixing false", handle);
        ret = dsSetAssociatedAudioMixing(handle, false);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsSetAssociatedAudioMixing failed with error %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsGetAssociatedAudioMixing with handle %ld", handle);
        ret = dsGetAssociatedAudioMixing(handle, &mixing);
        if (ret != dsERR_NONE || mixing)
        {
            UT_LOG_ERROR("dsGetAssociatedAudioMixing failed with error %d or mixing is not false", ret);
        }
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test function is designed to test the audio port control sink in the L2 dsAudio module.
*
* This function tests the initialization, setting, and termination of the audio port in the L2 dsAudio module. It also tests the associated audio mixing and fader control functionalities. The test is performed for different types of audio ports and for different mixer balance values. The function asserts that all the invoked functions return no error and that the mixer balance value set is the same as the one retrieved.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 051@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_AudioPortControl_sink(void)
{
    gTestID = 51;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    int mixerbalance;

    UT_LOG_DEBUG("Invoking dsAudioPortInit()");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort() with type=%d and index=0", type);
        ret = dsGetAudioPort(type, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort() failed with error: %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsSetAssociatedAudioMixing() with handle=%ld and mixing=true", handle);
        ret = dsSetAssociatedAudioMixing(handle, true);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsSetAssociatedAudioMixing() failed with error: %d", ret);
            continue;
        }

        for (mixerbalance = -32; mixerbalance <= 32; mixerbalance++)
        {
            UT_LOG_DEBUG("Invoking dsSetFaderControl() with handle=%ld and mixerbalance=%d", handle, mixerbalance);
            ret = dsSetFaderControl(handle, mixerbalance);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetFaderControl() failed with error: %d", ret);
                continue;
            }

            int getMixerbalance;
            UT_LOG_DEBUG("Invoking dsGetFaderControl() with handle=%ld", handle);
            ret = dsGetFaderControl(handle, &getMixerbalance);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            UT_ASSERT_EQUAL(getMixerbalance, mixerbalance);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsGetFaderControl() failed with error: %d", ret);
            }
        }
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm()");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test function is designed to test the audio port control source in the L2 dsAudio module.
*
* This function tests the initialization, setting, and retrieval of audio port controls in the L2 dsAudio module. It checks the functionality of dsAudioPortInit, dsGetAudioPort, dsSetAssociatedAudioMixing, dsSetFaderControl, dsGetFaderControl, and dsAudioPortTerm functions. The test is performed for different types of audio ports and for different mixer balance values. The test ensures that the functions return the expected results and that the retrieved mixer balance matches the set value.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 052@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_AudioPortControl_source(void)
{
    gTestID = 52;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    int mixerbalance;
    bool mixing = true;

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (int type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
    {
        UT_LOG_DEBUG("Invoking dsGetAudioPort with type=%d and index=0", type);
        ret = dsGetAudioPort(type, 0, &handle);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsGetAudioPort failed with error: %d", ret);
            continue;
        }

        UT_LOG_DEBUG("Invoking dsSetAssociatedAudioMixing with handle=%ld and mixing=%d", handle, mixing);
        ret = dsSetAssociatedAudioMixing(handle, mixing);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("dsSetAssociatedAudioMixing failed with error: %d", ret);
            continue;
        }

        for (mixerbalance = -32; mixerbalance <= 32; mixerbalance++)
        {
            UT_LOG_DEBUG("Invoking dsSetFaderControl with handle=%ld and mixerbalance=%d", handle, mixerbalance);
            ret = dsSetFaderControl(handle, mixerbalance);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsSetFaderControl failed with error: %d", ret);
                continue;
            }

            int retrievedMixerbalance;
            UT_LOG_DEBUG("Invoking dsGetFaderControl with handle=%ld", handle);
            ret = dsGetFaderControl(handle, &retrievedMixerbalance);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            UT_ASSERT_EQUAL(retrievedMixerbalance, mixerbalance);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("dsGetFaderControl failed with error: %d", ret);
            }
        }
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to validate the setting and getting of primary language in dsAudio
*
* In this test, we initialize the audio port, set a primary language, get the primary language and validate if the set and get languages are same. This is to ensure the dsAudio's set and get primary language functionalities are working as expected.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 053@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_SetAndGetPrimaryLanguage_sink(void)
{
    gTestID = 53;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    const char* setLang = "eng";
    char getLang[4];

    UT_LOG_DEBUG("Invoking dsAudioPortInit()");
    ret = dsAudioPortInit();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsGetAudioPort() with valid parameters");
    ret = dsGetAudioPort(dsAUDIOPORT_TYPE_HDMI, 0, &handle);
    UT_LOG_DEBUG("Return status: %d, Handle: %ld", ret, handle);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetAudioPort failed with status: %d", ret);
        UT_LOG_DEBUG("Invoking dsAudioPortTerm");
        dsAudioPortTerm();
        return;
    }

    UT_LOG_DEBUG("Invoking dsSetPrimaryLanguage() with handle and valid language code");
    ret = dsSetPrimaryLanguage(handle, setLang);
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsSetPrimaryLanguage() failed with status: %d", ret);
        UT_LOG_DEBUG("Invoking dsAudioPortTerm()");
        dsAudioPortTerm();
        return;
    }

    UT_LOG_DEBUG("Invoking dsGetPrimaryLanguage() with handle");
    ret = dsGetPrimaryLanguage(handle, getLang);
    UT_LOG_DEBUG("Return status: %d, Language: %s", ret, getLang);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    UT_ASSERT_STRING_EQUAL(getLang, setLang);

    UT_LOG_DEBUG("Invoking dsAudioPortTerm()");
    ret = dsAudioPortTerm();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to validate the setting and getting of primary language in dsAudio module
*
* In this test, we initialize the dsAudioPort, set a primary language, get the primary language and validate if the set and get languages are same. This is to ensure the dsAudio module's set and get primary language functionalities are working as expected.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 054@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_SetAndGetPrimaryLanguage_source(void)
{
    gTestID = 54;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    const char* setLang = "eng";
    char getLang[4];

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsGetAudioPort with valid parameters");
    ret = dsGetAudioPort(dsAUDIOPORT_TYPE_HDMI, 0, &handle);
    UT_LOG_DEBUG("Return status: %d, Handle: %ld", ret, handle);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetAudioPort failed with status: %d", ret);
        UT_LOG_DEBUG("Invoking dsAudioPortTerm");
        dsAudioPortTerm();
        return;
    }

    UT_LOG_DEBUG("Invoking dsSetPrimaryLanguage with handle and valid language code");
    ret = dsSetPrimaryLanguage(handle, setLang);
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);

    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsSetPrimaryLanguage failed with status: %d", ret);
        UT_LOG_DEBUG("Invoking dsAudioPortTerm");
        dsAudioPortTerm();
        return;
    }

    UT_LOG_DEBUG("Invoking dsGetPrimaryLanguage with handle");
    ret = dsGetPrimaryLanguage(handle, getLang);
    UT_LOG_DEBUG("Return status: %d, Language: %s", ret, getLang);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    UT_ASSERT_STRING_EQUAL(getLang, setLang);

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test for setting and getting the secondary language for the audio port
*
* This function tests the setting and getting of the secondary language for the audio port. It first initializes the audio port, gets the audio port handle, sets the secondary language, gets the secondary language, and finally terminates the audio port. It uses Cunit assertions to check the return values of the API calls.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 055@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_SetAndGetSecondaryLanguage_sink(void)
{
    gTestID = 55;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    const char* setLang = "eng";
    char getLang[4];

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsGetAudioPort with valid parameters");
    ret = dsGetAudioPort(dsAUDIOPORT_TYPE_HDMI, 0, &handle);
    UT_LOG_DEBUG("Return status: %d, Handle: %ld", ret, handle);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetAudioPort failed with status: %d", ret);
        UT_LOG_DEBUG("Invoking dsAudioPortTerm");
        dsAudioPortTerm();
        return;
    }

    UT_LOG_DEBUG("Invoking dsSetSecondaryLanguage with handle and valid language code");
    ret = dsSetSecondaryLanguage(handle, setLang);
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);

    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsSetSecondaryLanguage failed with status: %d", ret);
        UT_LOG_DEBUG("Invoking dsAudioPortTerm");
        dsAudioPortTerm();
        return;
    }

    UT_LOG_DEBUG("Invoking dsGetSecondaryLanguage with handle");
    ret = dsGetSecondaryLanguage(handle, getLang);
    UT_LOG_DEBUG("Return status: %d, Language: %s", ret, getLang);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    UT_ASSERT_STRING_EQUAL(getLang, setLang);

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");
    ret = dsAudioPortTerm();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to validate the setting and getting of secondary language source in L2 dsAudio
*
* In this test, we initialize the audio port, set a secondary language, and then get the secondary language. The test verifies if the set and get operations are successful and if the set and retrieved languages match. This is important to ensure the correct functioning of language setting and retrieval in the L2 dsAudio module.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 056@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsAudio_L2_Low-Level_TestSpecification.md](../../docs/pages/dsAudio_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsAudio_SetAndGetSecondaryLanguage_source(void)
{
    gTestID = 56;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    const char* setLang = "eng";
    char getLang[4];

    UT_LOG_DEBUG("Invoking dsAudioPortInit()");
    ret = dsAudioPortInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsGetAudioPort() with valid parameters");
    ret = dsGetAudioPort(dsAUDIOPORT_TYPE_HDMI, 0, &handle);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetAudioPort() failed with status: %d", ret);
        UT_LOG_DEBUG("Invoking dsAudioPortTerm()");
        dsAudioPortTerm();
        return;
    }
    UT_LOG_DEBUG("Invoking dsSetSecondaryLanguage() with valid parameters");
    ret = dsSetSecondaryLanguage(handle, setLang);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    UT_LOG_DEBUG("Return status: %d", ret);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("dsSetSecondaryLanguage() failed with status: %d", ret);
        UT_LOG_DEBUG("Invoking dsAudioPortTerm()");
        dsAudioPortTerm();
        return;
    }

    UT_LOG_DEBUG("Invoking dsGetSecondaryLanguage() with valid parameters");
    ret = dsGetSecondaryLanguage(handle, getLang);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    UT_LOG_DEBUG("Return status: %d, Secondary Language: %s", ret, getLang);

    if (ret != dsERR_NONE || strcmp(setLang, getLang) != 0)
    {
        UT_LOG_ERROR("dsGetSecondaryLanguage() failed with status: %d", ret);
    }

    UT_LOG_DEBUG("Invoking dsAudioPortTerm()");
    ret = dsAudioPortTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main tests for this module
 *
 * @return int - 0 on success, otherwise failure
 */

int test_dsAudio_l2_register(void)
{
    // Create the test suite
    pSuite = UT_add_suite("[L2 dsAudio]", NULL, NULL);
    if (pSuite == NULL)
    {
        return -1;
    }
    // List of test function names and strings

    UT_add_test( pSuite, "l2_dsAudio_EnableDisableAndVerifyAudioPortStatus_sink", test_l2_dsAudio_EnableDisableAndVerifyAudioPortStatus_sink);
    UT_add_test( pSuite, "l2_dsAudio_EnableDisableAndVerifyAudioPortStatus_source", test_l2_dsAudio_EnableDisableAndVerifyAudioPortStatus_source);
    UT_add_test( pSuite, "l2_dsAudio_CheckHeadphoneConnectionStatus_sink", test_l2_dsAudio_CheckHeadphoneConnectionStatus_sink);
    UT_add_test( pSuite, "l2_dsAudio_RetrieveAndVerifyMS12Capabilities_sink", test_l2_dsAudio_RetrieveAndVerifyMS12Capabilities_sink);
    UT_add_test( pSuite, "l2_dsAudio_RetrieveAndVerifyMS12Capabilities_source", test_l2_dsAudio_RetrieveAndVerifyMS12Capabilities_source);
    UT_add_test( pSuite, "l2_dsAudio_SetAndGetAudioCompression_sink", test_l2_dsAudio_SetAndGetAudioCompression_sink);
    UT_add_test( pSuite, "l2_dsAudio_SetAndGetAudioCompression_source", test_l2_dsAudio_SetAndGetAudioCompression_source);
    UT_add_test( pSuite, "l2_dsAudio_SetAndGetDialogEnhancement_sink", test_l2_dsAudio_SetAndGetDialogEnhancement_sink);
    UT_add_test( pSuite, "l2_dsAudio_SetAndGetDialogEnhancement_source", test_l2_dsAudio_SetAndGetDialogEnhancement_source);
    UT_add_test( pSuite, "l2_dsAudio_SetAndGetDolbyVolumeMode_sink", test_l2_dsAudio_SetAndGetDolbyVolumeMode_sink);
    UT_add_test( pSuite, "l2_dsAudio_SetAndGetDolbyVolumeMode_source", test_l2_dsAudio_SetAndGetDolbyVolumeMode_source);
    UT_add_test( pSuite, "l2_dsAudio_SetAndGetIntelligentEqualizerMode_sink", test_l2_dsAudio_SetAndGetIntelligentEqualizerMode_sink);
    UT_add_test( pSuite, "l2_dsAudio_SetAndGetIntelligentEqualizerMode_source", test_l2_dsAudio_SetAndGetIntelligentEqualizerMode_source);
    UT_add_test( pSuite, "l2_dsAudio_SetAndGetVolumeLeveller_sink", test_l2_dsAudio_SetAndGetVolumeLeveller_sink);
    UT_add_test( pSuite, "l2_dsAudio_SetAndGetVolumeLeveller_source", test_l2_dsAudio_SetAndGetVolumeLeveller_source);
    UT_add_test( pSuite, "l2_dsAudio_SetAndGetBassEnhancer_sink", test_l2_dsAudio_SetAndGetBassEnhancer_sink);
    UT_add_test( pSuite, "l2_dsAudio_SetAndGetBassEnhancer_source", test_l2_dsAudio_SetAndGetBassEnhancer_source);
    UT_add_test( pSuite, "l2_dsAudio_EnableAndVerifySurroundDecoder_sink", test_l2_dsAudio_EnableAndVerifySurroundDecoder_sink);
    UT_add_test( pSuite, "l2_dsAudio_EnableAndVerifySurroundDecoder_source", test_l2_dsAudio_EnableAndVerifySurroundDecoder_source);
    UT_add_test( pSuite, "l2_dsAudio_SetAndGetDRCMode_sink", test_l2_dsAudio_SetAndGetDRCMode_sink);
    UT_add_test( pSuite, "l2_dsAudio_SetAndGetDRCMode_source", test_l2_dsAudio_SetAndGetDRCMode_source);
    UT_add_test( pSuite, "l2_dsAudio_SetAndGetSurroundVirtualizer_sink", test_l2_dsAudio_SetAndGetSurroundVirtualizer_sink);
    UT_add_test( pSuite, "l2_dsAudio_SetAndGetSurroundVirtualizer_source", test_l2_dsAudio_SetAndGetSurroundVirtualizer_source);
    UT_add_test( pSuite, "l2_dsAudio_SetAndGetMISteering_sink", test_l2_dsAudio_SetAndGetMISteering_sink);
    UT_add_test( pSuite, "l2_dsAudio_SetAndGetMISteering_source", test_l2_dsAudio_SetAndGetMISteering_source);
    UT_add_test( pSuite, "l2_dsAudio_SetAndGetGraphicEqualizerMode_sink", test_l2_dsAudio_SetAndGetGraphicEqualizerMode_sink);
    UT_add_test( pSuite, "l2_dsAudio_SetAndGetGraphicEqualizerMode_source", test_l2_dsAudio_SetAndGetGraphicEqualizerMode_source);
    UT_add_test( pSuite, "l2_dsAudio_EnableDisableAndRetrieveLEConfig_sink", test_l2_dsAudio_EnableDisableAndRetrieveLEConfig_sink);
    UT_add_test( pSuite, "l2_dsAudio_EnableDisableAndRetrieveLEConfig_source", test_l2_dsAudio_EnableDisableAndRetrieveLEConfig_source);
    UT_add_test( pSuite, "l2_dsAudio_CheckMS12DecodeSupport_sink", test_l2_dsAudio_CheckMS12DecodeSupport_sink);
    UT_add_test( pSuite, "l2_dsAudio_CheckMS12DecodeSupport_source", test_l2_dsAudio_CheckMS12DecodeSupport_source);
    UT_add_test( pSuite, "l2_dsAudio_CheckMS11DecodeSupport_sink", test_l2_dsAudio_CheckMS11DecodeSupport_sink);
    UT_add_test( pSuite, "l2_dsAudio_CheckMS11DecodeSupport_source", test_l2_dsAudio_CheckMS11DecodeSupport_source);
    UT_add_test( pSuite, "l2_dsAudio_VerifyMS12AudioProfiles_sink", test_l2_dsAudio_VerifyMS12AudioProfiles_sink);
    UT_add_test( pSuite, "l2_dsAudio_SetAndGetMS12AudioProfile_sink", test_l2_dsAudio_SetAndGetMS12AudioProfile_sink);
    UT_add_test( pSuite, "l2_dsAudio_GetHDMIARCPortId_sink", test_l2_dsAudio_GetHDMIARCPortId_sink);
    UT_add_test( pSuite, "l2_dsAudio_SetAndGetStereoMode_sink", test_l2_dsAudio_SetAndGetStereoMode_sink);
    UT_add_test( pSuite, "l2_dsAudio_SetAndGetStereoMode_source", test_l2_dsAudio_SetAndGetStereoMode_source);
    UT_add_test( pSuite, "l2_dsAudio_SetAndGetStereoAuto_sink", test_l2_dsAudio_SetAndGetStereoAuto_sink);
    UT_add_test( pSuite, "l2_dsAudio_SetAndGetAudioGain_sink", test_l2_dsAudio_SetAndGetAudioGain_sink);
    UT_add_test( pSuite, "l2_dsAudio_SetAndGetAudioLevel_sink", test_l2_dsAudio_SetAndGetAudioLevel_sink);
    UT_add_test( pSuite, "l2_dsAudio_AudioMuteVerification_sink", test_l2_dsAudio_AudioMuteVerification_sink);
    UT_add_test( pSuite, "l2_dsAudio_AudioMuteVerification_source", test_l2_dsAudio_AudioMuteVerification_source);
    UT_add_test( pSuite, "l2_dsAudio_SetAndGetAudioDelay_sink", test_l2_dsAudio_SetAndGetAudioDelay_sink);
    UT_add_test( pSuite, "l2_dsAudio_SetAndGetAudioDelay_source", test_l2_dsAudio_SetAndGetAudioDelay_source);
    UT_add_test( pSuite, "l2_dsAudio_VerifyAtmosCapabilities_sink", test_l2_dsAudio_VerifyAtmosCapabilities_sink);
    UT_add_test( pSuite, "l2_dsAudio_GetAudioCapabilities_sink", test_l2_dsAudio_GetAudioCapabilities_sink);
    UT_add_test( pSuite, "l2_dsAudio_GetAudioCapabilities_source", test_l2_dsAudio_GetAudioCapabilities_source);
    UT_add_test( pSuite, "l2_dsAudio_EnableDisableRetrieveAudioMixing_sink", test_l2_dsAudio_EnableDisableRetrieveAudioMixing_sink);
    UT_add_test( pSuite, "l2_dsAudio_EnableDisableRetrieveAudioMixing_source", test_l2_dsAudio_EnableDisableRetrieveAudioMixing_source);
    UT_add_test( pSuite, "l2_dsAudio_AudioPortControl_sink", test_l2_dsAudio_AudioPortControl_sink);
    UT_add_test( pSuite, "l2_dsAudio_AudioPortControl_source", test_l2_dsAudio_AudioPortControl_source);
    UT_add_test( pSuite, "l2_dsAudio_SetAndGetPrimaryLanguage_sink", test_l2_dsAudio_SetAndGetPrimaryLanguage_sink);
    UT_add_test( pSuite, "l2_dsAudio_SetAndGetPrimaryLanguage_source", test_l2_dsAudio_SetAndGetPrimaryLanguage_source);
    UT_add_test( pSuite, "l2_dsAudio_SetAndGetSecondaryLanguage_sink", test_l2_dsAudio_SetAndGetSecondaryLanguage_sink);
    UT_add_test( pSuite, "l2_dsAudio_SetAndGetSecondaryLanguage_source", test_l2_dsAudio_SetAndGetSecondaryLanguage_source);

    return 0;
}