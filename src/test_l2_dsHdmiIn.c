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
 * @addtogroup HPK Hardware Porting Kit
 * @{
 * @par The Hardware Porting Kit
 * HPK is the next evolution of the well-defined Hardware Abstraction Layer
 * (HAL), but augmented with more comprehensive documentation and test suites
 * that OEM or SOC vendors can use to self-certify their ports before taking
 * them to RDKM for validation or to an operator for final integration and
 * deployment. The Hardware Porting Kit effectively enables an OEM and/or SOC
 * vendor to self-certify their own Video Accelerator devices, with minimal RDKM
 * assistance.
 *
 */

/**
 * @addtogroup Device_Settings Device Settings Module
 * @{
 */

/**
 * @addtogroup Device_Settings_HALTEST Device Settings HAL Tests
 * @{
 */

/**
 * @defgroup DS_HDMIIn_HALTEST Device Settings HDMI Input HAL Tests
 * @{
 */

/**
 * @defgroup DS_HDMIIn_HALTEST_L2 Device Settings HDMI Input HAL Tests L2 File
 * @{
 * @parblock
 *
 * ### L2 Tests for DS HDMI Input HAL :
 *
 * Level 2 unit test cases for all APIs of Device Settings HDMI Input HAL
 *
 * **Pre-Conditions:**  None@n
 * **Dependencies:** None@n
 *
 * Refer to API Definition specification documentation : [ds-hdmi-in_halSpec.md](../../docs/pages/ds-hdmi-in_halSpec.md)
 * @endparblock
 */


/**
 * @file test_l2_dsHdmiIn.c
 *
 */

#include <ut.h>
#include <ut_log.h>
#include <ut_kvp_profile.h>
#include <ut_control_plane.h>
#include "dsHdmiIn.h"
#include "test_parse_configuration.h"

#define DS_HDMIIN_KEY_SIZE 64

static int gTestGroup = 2;
static int gTestID = 1;

const static ut_control_keyStringMapping_t dsHdmiInPort_mapTable [] =
{
  { "dsHDMI_IN_PORT_NONE",     (int32_t)dsHDMI_IN_PORT_NONE },
  { "dsHDMI_IN_PORT_0",        (int32_t)dsHDMI_IN_PORT_0    },
  { "dsHDMI_IN_PORT_1",        (int32_t)dsHDMI_IN_PORT_1    },
  { "dsHDMI_IN_PORT_2",        (int32_t)dsHDMI_IN_PORT_2    },
  { "dsHDMI_IN_PORT_3",        (int32_t)dsHDMI_IN_PORT_3    },
  { "dsHDMI_IN_PORT_4",        (int32_t)dsHDMI_IN_PORT_4    },
  { "dsHDMI_IN_PORT_MAX",      (int32_t)dsHDMI_IN_PORT_MAX  },
  {  NULL, -1 }
};

/**
* @brief Test for getting the number of HDMI inputs from the source
*
* This test checks if the function dsHdmiInGetNumberOfInputs correctly retrieves the number of HDMI inputs from the source.
* It first initializes the HDMI input, then retrieves the number of inputs, and finally terminates the HDMI input.
* The test asserts that all these operations return no errors and that the retrieved number of inputs matches the expected value.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 001@n
*
* **Test Procedure:**
* Refer to UT specification documentation [ds-hdmi-in-L2-Low-Level_TestSpec.md](../docs/pages/ds-hdmi-in-L2-Low-Level_TestSpec.md)
*/

void test_l2_dsHdmiIn_GetNumberOfInputs(void)
{
    gTestID = 1;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE; //Initialize to dsERR_NONE.
    uint8_t numberOfInputs = 0; //Initialize to 0.

    UT_LOG_DEBUG("Invoking dsHdmiInInit");
    ret = dsHdmiInInit();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsHdmiInGetNumberOfInputs with valid buffer");
    ret = dsHdmiInGetNumberOfInputs(&numberOfInputs);
    UT_LOG_DEBUG("Number of Inputs: %d, Return status: %d", numberOfInputs, ret);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("Invoking dsHdmiInTerm due to failure of dsHdmiInGetNumberOfInputs");
    }

    UT_ASSERT_KVP_EQUAL_PROFILE_UINT8(numberOfInputs, "dsHdmiIn/numberOfPorts");

    UT_LOG_DEBUG("Invoking dsHdmiInTerm");
    ret = dsHdmiInTerm();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test for getting the status of HDMI input source
*
* This test function initializes the HDMI input subsystem, gets the status of the HDMI input ports, verifies the returned status,
* and then terminates the HDMI input subsystem. It uses the Cunit assertion macros to check the return values of the API calls
* and the values of the returned status structure.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 002@n
*
* **Test Procedure:**
* Refer to UT specification documentation [ds-hdmi-in-L2-Low-Level_TestSpec.md](../docs/pages/ds-hdmi-in-L2-Low-Level_TestSpec.md)
*/

void test_l2_dsHdmiIn_GetStatus(void)
{
    gTestID = 2;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE; // Initialize to dsERR_NONE
    dsHdmiInStatus_t status = {0}; // Initialize all fields to 0
    uint8_t numInputs = 0; // Initialize to 0

    UT_LOG_DEBUG("Invoking dsHdmiInInit()");
    ret = dsHdmiInInit();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsHdmiInGetStatus() with valid status pointer");
    ret = dsHdmiInGetStatus(&status);
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);

    ret = dsHdmiInGetNumberOfInputs(&numInputs);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("Failed to get the number of hdmi inputs\n");
    }
    UT_ASSERT_TRUE(numInputs >= 0 && numInputs <= UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/numberOfPorts"));

    for (int i = dsHDMI_IN_PORT_0; i < numInputs; i++)
    {
        UT_LOG_DEBUG("IsPortConnected: %d\n", status.isPortConnected[i]);
        UT_ASSERT_EQUAL(status.isPortConnected[i], false);
    }

    UT_LOG_DEBUG("isPresented: %d, activePort: %d", status.isPresented, status.activePort);
    UT_ASSERT_EQUAL(status.isPresented, false);
    UT_ASSERT_EQUAL(status.activePort, dsHDMI_IN_PORT_NONE);

    UT_LOG_DEBUG("Invoking dsHdmiInTerm()");
    ret = dsHdmiInTerm();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test verifies the HDMI input port status for a given source
*
* This test function initializes the HDMI input, gets the number of inputs, selects each port,
* gets the status of each port, and finally terminates the HDMI input. The test is designed to
* ensure that the HDMI input port status is correctly reported for each source.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 003@n
*
* **Test Procedure:**
* Refer to UT specification documentation [ds-hdmi-in-L2-Low-Level_TestSpec.md](../docs/pages/ds-hdmi-in-L2-Low-Level_TestSpec.md)
*/

void test_l2_dsHdmiIn_VerifyHdmiInputPortStatus(void)
{
    gTestID = 3;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = 0; //Initialize to 0
    uint8_t numInputs = 0; // Initialize to 0
    dsHdmiInStatus_t status = {0}; //Initialize all fields to 0

    UT_LOG_DEBUG("Invoking dsHdmiInInit()");
    ret = dsHdmiInInit();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsHdmiInGetNumberOfInputs()");

    ret = dsHdmiInGetNumberOfInputs(&numInputs);
    UT_LOG_DEBUG("Number of inputs: %d, Return status: %d", numInputs, ret);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    UT_ASSERT_TRUE(numInputs >= 0 && numInputs <= UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/numberOfPorts"));

    for (uint8_t i = dsHDMI_IN_PORT_0; i < numInputs; i++)
    {
        UT_LOG_DEBUG("Invoking dsHdmiInSelectPort() with port number %d", i);
        ret = dsHdmiInSelectPort(i, false, dsVideoPlane_PRIMARY, false);
        UT_LOG_DEBUG("Return status: %d", ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            continue;
        }

        UT_LOG_DEBUG("Invoking dsHdmiInGetStatus()");
        ret = dsHdmiInGetStatus(&status);
        UT_LOG_DEBUG("Active port: %d, Is presented: %d, Is port connected: %d, Return status: %d", status.activePort, status.isPresented, status.isPortConnected[i], ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_ASSERT_EQUAL(status.activePort, i);
        UT_ASSERT_FALSE(status.isPortConnected[i]);
        UT_ASSERT_FALSE(status.isPresented);
    }

    UT_LOG_DEBUG("Invoking dsHdmiInTerm()");
    ret = dsHdmiInTerm();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test verifies the HDMI ARC Port sink functionality
*
* This test initializes the HDMI input, checks if the HDMI ARC Port is available and validates
* the number of ports and their status. It then terminates the HDMI input. The test is designed
* to ensure the proper functioning of HDMI ARC Port sink.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 004@n
*
* **Test Procedure:**
* Refer to UT specification documentation [ds-hdmi-in-L2-Low-Level_TestSpec.md](../docs/pages/ds-hdmi-in-L2-Low-Level_TestSpec.md)
*/

void test_l2_dsHdmiIn_VerifyHdmiArcPort_sink(void)
{
    gTestID = 4;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t retStatus = dsERR_NONE; //Initialize to dsERR_NONE
    bool isArcPort = false; //Initialize to 0
    dsHdmiInPort_t iPort = dsHDMI_IN_PORT_NONE; //Initialize to default dsHDMI_IN_PORT_NONE
    uint8_t numInputs = 0; // Initialize to 0

    UT_LOG_DEBUG("Invoking dsHdmiInInit");
    retStatus = dsHdmiInInit();
    UT_LOG_DEBUG("Return status: %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    retStatus = dsHdmiInGetNumberOfInputs(&numInputs);
    if (retStatus != dsERR_NONE)
    {
        UT_LOG_ERROR("Failed to get the number of hdmi inputs\n");
    }

    UT_ASSERT_TRUE(numInputs >= 0 && numInputs <= UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/numberOfPorts"));

    for(iPort = dsHDMI_IN_PORT_0; iPort < numInputs; iPort++)
    {
        UT_LOG_DEBUG("Invoking dsIsHdmiARCPort with iPort: %d", iPort);
        retStatus = dsIsHdmiARCPort(iPort, &isArcPort);
        UT_LOG_DEBUG("Return status: %d, isArcPort: %d", retStatus, isArcPort);
        UT_ASSERT_EQUAL(retStatus, dsERR_NONE);
        if(isArcPort == false)
        {
            continue;
        }

        UT_ASSERT_KVP_EQUAL_PROFILE_UINT8(iPort, "dsHdmiIn/HdmiArcPortID");
    }

    UT_LOG_DEBUG("Invoking dsHdmiInTerm");
    retStatus = dsHdmiInTerm();
    UT_LOG_DEBUG("Return status: %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to set and get EDID version and validate EDID length for HDMI input
*
* This test sets the EDID version for HDMI input ports and then gets the EDID version to validate it.
* It also retrieves the EDID bytes info to validate the length. This is done to ensure the correct
* functioning of HDMI input related APIs.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 005@n
*
* **Test Procedure:**
* Refer to UT specification documentation [ds-hdmi-in-L2-Low-Level_TestSpec.md](../docs/pages/ds-hdmi-in-L2-Low-Level_TestSpec.md)
*/

void test_l2_dsHdmiIn_SetAndGetEdidVersionAndValidateEdidLength_sink(void)
{
    gTestID = 5;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;
    uint8_t numInputs = 0; // Initialize to 0
    dsHdmiInPort_t hdmiPort[] = {dsHDMI_IN_PORT_0, dsHDMI_IN_PORT_1, dsHDMI_IN_PORT_2, dsHDMI_IN_PORT_3, dsHDMI_IN_PORT_4};
    tv_hdmi_edid_version_t edidVersion[] = {HDMI_EDID_VER_14, HDMI_EDID_VER_20};
    tv_hdmi_edid_version_t getEdidVersion = HDMI_EDID_VER_MAX;
    char keyString[DS_HDMIIN_KEY_SIZE] = {0};

    UT_LOG_DEBUG("Invoking dsHdmiInInit");
    ret = dsHdmiInInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    ret = dsHdmiInGetNumberOfInputs(&numInputs);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("Failed to get the number of hdmi inputs\n");
    }

    UT_ASSERT_TRUE(numInputs >= 0 && numInputs <= UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/numberOfPorts"));

    for (int i = dsHDMI_IN_PORT_0; i < numInputs; i++)
    {
        tv_hdmi_edid_version_t supportedEdidVersion;

        snprintf(keyString, DS_HDMIIN_KEY_SIZE, "dsHdmiIn/EdidVersion/%d", i);

        supportedEdidVersion = UT_KVP_PROFILE_GET_UINT8(keyString);

        for (int j = HDMI_EDID_VER_14; j < supportedEdidVersion; j++)
        {
            UT_LOG_DEBUG("Invoking dsSetEdidVersion with hdmiPort=%d, edidVersion=%d\n", hdmiPort[i], edidVersion[j]);
            ret = dsSetEdidVersion(hdmiPort[i], edidVersion[j]);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("Failed to set EDID version\n");
                continue;
            }

            UT_LOG_DEBUG("Invoking dsGetEdidVersion with hdmiPort=%d\n", hdmiPort[i]);
            ret = dsGetEdidVersion(hdmiPort[i], &getEdidVersion);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("Failed to get EDID version\n");
            }
            UT_ASSERT_EQUAL(getEdidVersion, edidVersion[j]);
        }
    }

    UT_LOG_DEBUG("Invoking dsHdmiInTerm");
    ret = dsHdmiInTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to verify the supported game features list for HDMI input
*
* In this test, the dsHdmiInInit function is invoked to initialize the HDMI input.
* Then, the dsGetSupportedGameFeaturesList function is called to get the list of
* supported game features. The results are then compared with the expected values
* from the Sink_HDMIIN.yaml profile. Finally, the dsHdmiInTerm function is invoked
* to terminate the HDMI input. The test ensures that all these operations are successful
* and the supported game features list is as expected.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 006@n
*
* **Test Procedure:**
* Refer to UT specification documentation [ds-hdmi-in-L2-Low-Level_TestSpec.md](../docs/pages/ds-hdmi-in-L2-Low-Level_TestSpec.md)
*/

void test_l2_dsHdmiIn_GetSupportedGameFeaturesList_sink(void)
{
    gTestID = 6;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;
    dsSupportedGameFeatureList_t features = {0};

    UT_LOG_DEBUG("Invoking dsHdmiInInit");
    ret = dsHdmiInInit();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsGetSupportedGameFeaturesList with valid buffer");
    ret = dsGetSupportedGameFeaturesList(&features);
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("Invoking dsHdmiInTerm due to failure of dsGetSupportedGameFeaturesList");
    }

    UT_LOG_DEBUG("Game feature count: %d",features.gameFeatureCount);
    UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(features.gameFeatureCount, "dsHdmiIn/gameFeatures/count");

    for ( uint8_t i = 0; i < features.gameFeatureCount; i++ ){
        UT_LOG_DEBUG("Game feature list: %s",features.gameFeatureList);
        UT_ASSERT_KVP_EQUAL_PROFILE_STRING(features.gameFeatureList,"dsHdmiIn/gameFeatures/feature")
    }

    UT_LOG_DEBUG("Invoking dsHdmiInTerm");
    ret = dsHdmiInTerm();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to get HDMI compatibility version and validate 
*
* This test gets the HDMI compatibility version and validate it.
* It is validated with the HDMI compatibility version the platform specific profile file. This is done to ensure the correct
* functioning of HDMI input related APIs.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 007@n
*
* **Test Procedure:**
* Refer to UT specification documentation [ds-hdmi-in-L2-Low-Level_TestSpec.md](../docs/pages/ds-hdmi-in-L2-Low-Level_TestSpec.md)
*/

void test_l2_dsHdmiIn_GetHdmiVersionAndValidate_sink(void)
{
    gTestID = 7;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;
    uint8_t numInputs = 0; // Initialize to 0
    dsHdmiMaxCapabilityVersion_t getVersion = HDMI_COMPATIBILITY_VERSION_MAX;
    char keyString[DS_HDMIIN_KEY_SIZE] = {0};

    UT_LOG_DEBUG("Invoking dsHdmiInInit");
    ret = dsHdmiInInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    ret = dsHdmiInGetNumberOfInputs(&numInputs);
    if (ret != dsERR_NONE)
    {
        UT_LOG_ERROR("Failed to get the number of hdmi inputs\n");
    }

    UT_ASSERT_TRUE(numInputs >= 0 && numInputs <= UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/numberOfPorts"));

    for (int port = dsHDMI_IN_PORT_0; port < numInputs; port++)
    {
        UT_LOG_DEBUG("Invoking dsGetEdidVersion with hdmiPort=%d\n", port);
        ret = dsGetHdmiVersion(port, &getVersion);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_ERROR("Failed to get EDID version\n");
        }
        snprintf(keyString, DS_HDMIIN_KEY_SIZE, "dsHdmiIn/HdmiCompatibilityVersion/%d", port);
        dsHdmiMaxCapabilityVersion_t version = UT_KVP_PROFILE_GET_UINT32(keyString);
        UT_ASSERT_EQUAL(getVersion, version);
    }
    UT_LOG_DEBUG("Invoking dsHdmiInTerm");
    ret = dsHdmiInTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test to enable and disable VRR support for HDMI Input ports
*
* This test enables the VRR support for HDMI input ports and then gets the VRR support of the particular HDMI port to validate whether VRR support is enabled.
* It also disables the VRR support for HDMI input ports and then gets the VRR support of the particular HDMI port to validate whether VRR support is disabled.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 006@n
*
* **Test Procedure:**
* Refer to UT specification documentation [ds-hdmi-in-L2-Low-Level_TestSpec.md](../docs/pages/ds-hdmi-in-L2-Low-Level_TestSpec.md)
*/

void test_l2_dsHdmiIn_SetAndGetVRRSupport_sink(void)
{
    gTestID = 6;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;
    bool vrrSupport_1 = false;
    bool vrrSupport_2 = false;

    uint8_t vrr_supported_ports_count = 0;
    uint8_t vrr_unsupported_ports_count = 0;
    char keyString[DS_HDMIIN_KEY_SIZE] = {0};

    tv_hdmi_edid_version_t ver20 = UT_KVP_PROFILE_GET_UINT32("dsHdmiIn/EdidVersion/1");
    vrr_supported_ports_count = UT_KVP_PROFILE_GET_LIST_COUNT("dsHdmiIn/VrrSupportedPorts");
    vrr_unsupported_ports_count = UT_KVP_PROFILE_GET_LIST_COUNT("dsHdmiIn/VrrUnsupportedPorts");

    UT_LOG_DEBUG("Invoking dsHdmiInInit");
    ret = dsHdmiInInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (int i = 0; i < vrr_unsupported_ports_count; i++)
    {
        memset(keyString, 0, DS_HDMIIN_KEY_SIZE);
        snprintf(keyString, DS_HDMIIN_KEY_SIZE, "dsHdmiIn/VrrUnsupportedPorts/%d", i);
        // Read the unsupported ports from the profile
        char vrr_unsupported_port[DS_HDMIIN_KEY_SIZE] = {0};
        UT_ASSERT_EQUAL(ut_kvp_getStringField(ut_kvp_profile_getInstance(), keyString, vrr_unsupported_port, DS_HDMIIN_KEY_SIZE), UT_KVP_STATUS_SUCCESS);

        UT_LOG_DEBUG("Invoking dsHdmiInSetVRRSupport with hdmiPort=%s and VRR support %d\n", vrr_unsupported_port, vrrSupport_1);
        ret = dsHdmiInSetVRRSupport(UT_Control_GetMapValue(dsHdmiInPort_mapTable, vrr_unsupported_port, 10), vrrSupport_1);
        UT_ASSERT_EQUAL(ret, dsERR_OPERATION_NOT_SUPPORTED);

        UT_LOG_DEBUG("Invoking dsHdmiInGetVRRSupport with hdmiPort=%s\n", vrr_unsupported_port);
        ret = dsHdmiInGetVRRSupport(UT_Control_GetMapValue(dsHdmiInPort_mapTable, vrr_unsupported_port, 10), &vrrSupport_2);
        UT_ASSERT_EQUAL(vrrSupport_2, dsVRR_NONE);
        UT_ASSERT_EQUAL(ret, dsERR_OPERATION_NOT_SUPPORTED);
    }
    for (int i = 0; i < vrr_supported_ports_count; i++)
    {
        memset(keyString, 0, DS_HDMIIN_KEY_SIZE);
        snprintf(keyString, DS_HDMIIN_KEY_SIZE, "dsHdmiIn/VrrSupportedPorts/%d", i);
        // Read the supported ports from the profile
        char vrr_supported_port[DS_HDMIIN_KEY_SIZE] = {0};
        UT_ASSERT_EQUAL(ut_kvp_getStringField(ut_kvp_profile_getInstance(), keyString, vrr_supported_port, DS_HDMIIN_KEY_SIZE), UT_KVP_STATUS_SUCCESS);

        UT_ASSERT_EQUAL(dsSetEdidVersion(UT_Control_GetMapValue(dsHdmiInPort_mapTable, vrr_supported_port, 10), ver20), dsERR_NONE);

        vrrSupport_1 = true; // Set VRR support to true for supported ports
        UT_LOG_DEBUG("Invoking dsHdmiInSetVRRSupport with hdmiPort=%s and VRR support %d\n", vrr_supported_port, vrrSupport_1);
        ret = dsHdmiInSetVRRSupport(UT_Control_GetMapValue(dsHdmiInPort_mapTable, vrr_supported_port, 10), true);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_LOG_DEBUG("Invoking dsHdmiInGetVRRSupport with hdmiPort=%s\n", vrr_supported_port);
        ret = dsHdmiInGetVRRSupport(UT_Control_GetMapValue(dsHdmiInPort_mapTable, vrr_supported_port, 10), &vrrSupport_2);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_ASSERT_EQUAL(vrrSupport_1, vrrSupport_2);

        vrrSupport_1 = false; // Set VRR support to false for supported ports
        UT_LOG_DEBUG("Invoking dsHdmiInSetVRRSupport with hdmiPort=%s and VRR support %d\n", vrr_supported_port, vrrSupport_1);
        ret = dsHdmiInSetVRRSupport(UT_Control_GetMapValue(dsHdmiInPort_mapTable, vrr_supported_port, 10), vrrSupport_1);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_LOG_DEBUG("Invoking dsHdmiInGetVRRSupport with hdmiPort=%s\n", vrr_supported_port);
        ret = dsHdmiInGetVRRSupport(UT_Control_GetMapValue(dsHdmiInPort_mapTable, vrr_supported_port, 10), &vrrSupport_2);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_ASSERT_EQUAL(vrrSupport_1, vrrSupport_2);
    }

    UT_LOG_DEBUG("Invoking dsHdmiInTerm");
    ret = dsHdmiInTerm();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main tests for this module
 *
 * @return int - 0 on success, otherwise failure
 */

int test_l2_dsHdmiIn_register(void)
{
    ut_kvp_status_t status;
    int32_t source_type = 0;

    status = ut_kvp_getStringField(ut_kvp_profile_getInstance(), "dsHdmiIn.Type", gDeviceType, TEST_DS_DEVICE_TYPE_SIZE);

    if (status == UT_KVP_STATUS_SUCCESS ) {
        if (!strncmp(gDeviceType, TEST_TYPE_SOURCE_VALUE, TEST_DS_DEVICE_TYPE_SIZE)) {
            // Create the test suite for source type
            pSuite = UT_add_suite("[L2 dsHdmiIn - Source]", NULL, NULL);
            if (pSuite == NULL)
            {
                return -1;
            }
            source_type = 1;
        }
        else if(!strncmp(gDeviceType, TEST_TYPE_SINK_VALUE, TEST_DS_DEVICE_TYPE_SIZE)) {
            // Create the test suite for sink type
            // Create the test suite for source type
            pSuite = UT_add_suite("[L2 dsHdmiIn - Sink]", NULL, NULL);
            if (pSuite == NULL)
            {
                return -1;
            }
            source_type = 0;
        }
        else {
            UT_LOG_ERROR("Invalid platform type: %s", gDeviceType);
            return -1;
        }
    }
    else {
        UT_LOG_ERROR("Failed to get the platform type");
        return -1;
    }

    // List of test function names and strings
    UT_add_test( pSuite, "GetNumberOfInputs", test_l2_dsHdmiIn_GetNumberOfInputs);
    UT_add_test( pSuite, "GetStatus", test_l2_dsHdmiIn_GetStatus);
    UT_add_test( pSuite, "VerifyHdmiInputPortStatus", test_l2_dsHdmiIn_VerifyHdmiInputPortStatus);

    if ( source_type == 0 ){
        UT_add_test( pSuite, "VerifyHdmiArcPort_sink", test_l2_dsHdmiIn_VerifyHdmiArcPort_sink);
        UT_add_test( pSuite, "SetGetEdidVer_EdidLength_sink", test_l2_dsHdmiIn_SetAndGetEdidVersionAndValidateEdidLength_sink);
        UT_add_test( pSuite, "GetGameFeaturesList_sink", test_l2_dsHdmiIn_GetSupportedGameFeaturesList_sink);
        UT_add_test( pSuite, "GetHdmiVersionValidate_sink", test_l2_dsHdmiIn_GetHdmiVersionAndValidate_sink);
        UT_add_test( pSuite, "SetGetHdmiVRRSupport_sink", test_l2_dsHdmiIn_SetAndGetVRRSupport_sink);
    }

    return 0;
}

/** @} */ // End of DS_HDMIIn_HALTEST_L2
/** @} */ // End of DS_HDMIIn_HALTEST
/** @} */ // End of Device_Settings_HALTEST
/** @} */ // End of Device_Settings
/** @} */ // End of HPK
