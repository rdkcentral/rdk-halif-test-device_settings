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
* @file test_l2_dsHdmiIn.c
* @page dsHdmiIn Level 2 Tests
*
* ## Module's Role
* This module includes Level 2 functional tests (success and failure scenarios).
* This is to ensure that the dsHdmiIn APIs meet the requirements across all vendors.
*
* **Pre-Conditions:**  None@n
* **Dependencies:** None@n
*
* Ref to API Definition specification documentation : [dsHdmiIn_halSpec.md](../../docs/pages/dsHdmiIn_halSpec.md)
*/

#include <ut.h>
#include <ut_log.h>
#include <ut_kvp_profile.h>
#include "dsHdmiIn.h"

static int gTestGroup = 2;
static int gTestID = 1;

/**
* @brief Test for getting the number of HDMI inputs
*
* This test case validates the functionality of dsHdmiInGetNumberOfInputs API. It checks if the API is able to successfully return the number of HDMI inputs. The test is designed to ensure the robustness and reliability of the API.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 001@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsHdmiIn_L2_Low-Level_TestSpecification.md](../../docs/pages/dsHdmiIn_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsHdmiIn_GetNumberOfInputs_sink(void)
{
    gTestID = 1;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t retStatus = dsERR_NONE; //Initialize to dsERR_NONE.
    uint8_t pNumberOfinputs = 0; //Initialize to 0.

    UT_LOG_DEBUG("Invoking dsHdmiInInit");
    retStatus = dsHdmiInInit();
    UT_LOG_DEBUG("Return status: %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsHdmiInGetNumberOfInputs with valid buffer");
    retStatus = dsHdmiInGetNumberOfInputs(&pNumberOfinputs);
    UT_LOG_DEBUG("Number of HDMI input ports: %d, Return status: %d", pNumberOfinputs, retStatus);
    UT_ASSERT_EQUAL(retStatus, dsERR_NONE);
    if (retStatus != dsERR_NONE)
    {
        UT_LOG_DEBUG("Invoking dsHdmiInTerm due to failure of dsHdmiInGetNumberOfInputs");
        retStatus = dsHdmiInTerm();
        UT_LOG_DEBUG("Return status: %d", retStatus);
        return;
    }

    UT_ASSERT_KVP_EQUAL_PROFILE_UINT8(pNumberOfinputs, "HDMIIN/HdmiInputPort/numberOfPorts");

    UT_LOG_DEBUG("Invoking dsHdmiInTerm");
    retStatus = dsHdmiInTerm();
    UT_LOG_DEBUG("Return status: %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test for getting the number of HDMI inputs from the source
*
* This test checks if the function dsHdmiInGetNumberOfInputs correctly retrieves the number of HDMI inputs from the source. It first initializes the HDMI input, then retrieves the number of inputs, and finally terminates the HDMI input. The test asserts that all these operations return no errors and that the retrieved number of inputs matches the expected value.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 002@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsHdmiIn_L2_Low-Level_TestSpecification.md](../../docs/pages/dsHdmiIn_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsHdmiIn_GetNumberOfInputs_source(void)
{
    gTestID = 2;
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
        UT_LOG_DEBUG("Invoking dsHdmiInTerm due to failure of dsHdmiInGetNumberOfInputs");
        ret = dsHdmiInTerm();
        UT_LOG_DEBUG("Return status: %d", ret);
        return;
    }

    UT_ASSERT_KVP_EQUAL_PROFILE_UINT8(numberOfInputs, "HDMIIN/HdmiInputPort/numberOfPorts");

    UT_LOG_DEBUG("Invoking dsHdmiInTerm");
    ret = dsHdmiInTerm();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test for the function dsHdmiIn_GetStatus_sink
*
* This test checks if the function dsHdmiIn_GetStatus_sink correctly initializes, gets the status, and terminates the HDMI input. It also checks if the status of the HDMI input is as expected.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 003@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsHdmiIn_L2_Low-Level_TestSpecification.md](../../docs/pages/dsHdmiIn_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsHdmiIn_GetStatus_sink(void)
{
    dsError_t retStatus = dsERR_NONE; // Initialize to dsERR_NONE
    dsHdmiInStatus_t status = { 0 }; // Initialize all fields to 0

    gTestID = 3;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    UT_LOG_DEBUG("Invoking dsHdmiInInit");
    retStatus = dsHdmiInInit();
    UT_LOG_DEBUG("Return status: %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsHdmiInGetStatus with valid buffer");
    retStatus = dsHdmiInGetStatus(&status);
    UT_LOG_DEBUG("Return status: %d", retStatus);
    UT_ASSERT_EQUAL(retStatus, dsERR_NONE);

    UT_LOG_DEBUG("isPresented: %d, activePort: %d", status.isPresented, status.activePort);
    UT_ASSERT_EQUAL(status.isPresented, false);
    UT_ASSERT_EQUAL(status.activePort, dsHDMI_IN_PORT_NONE);

    for (int i = 0; i < dsHDMI_IN_PORT_MAX; i++)
    {
        UT_LOG_DEBUG("isPortConnected[%d]: %d", i, status.isPortConnected[i]);
        UT_ASSERT_EQUAL(status.isPortConnected[i], false);
    }

    UT_LOG_DEBUG("Invoking dsHdmiInTerm");
    retStatus = dsHdmiInTerm();
    UT_LOG_DEBUG("Return status: %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Test for getting the status of HDMI input source
*
* This test function initializes the HDMI input subsystem, gets the status of the HDMI input ports, verifies the returned status, and then terminates the HDMI input subsystem. It uses the Cunit assertion macros to check the return values of the API calls and the values of the returned status structure.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 004@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsHdmiIn_L2_Low-Level_TestSpecification.md](../../docs/pages/dsHdmiIn_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsHdmiIn_GetStatus_source(void)
{
    gTestID = 4;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE; // Initialize to dsERR_NONE
    dsHdmiInStatus_t status = {0}; // Initialize all fields to 0

    UT_LOG_DEBUG("Invoking dsHdmiInInit()");
    ret = dsHdmiInInit();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsHdmiInGetStatus() with valid status pointer");
    ret = dsHdmiInGetStatus(&status);
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);

    UT_LOG_DEBUG("isPresented: %d, activePort: %d", status.isPresented, status.activePort);
    UT_ASSERT_EQUAL(status.isPresented, false);
    for (int i = 0; i < dsHDMI_IN_PORT_MAX; i++)
    {
        UT_ASSERT_EQUAL(status.isPortConnected[i], false);
    }
    UT_ASSERT_EQUAL(status.activePort, dsHDMI_IN_PORT_NONE);

    UT_LOG_DEBUG("Invoking dsHdmiInTerm()");
    ret = dsHdmiInTerm();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test verifies the HDMI input port status for a sink device
*
* This test function initializes the HDMI input, gets the number of inputs, selects each port, gets the status of each port, and finally terminates the HDMI input. It checks for any errors at each step and asserts the expected results. This is done to ensure the HDMI input port status functionality is working as expected for a sink device.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 005@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsHdmiIn_L2_Low-Level_TestSpecification.md](../../docs/pages/dsHdmiIn_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsHdmiIn_VerifyHdmiInputPortStatus_sink(void)
{
    dsError_t ret = dsERR_NONE; // Initialize to dsERR_NONE
    uint8_t numInputs = 0; // Initialize to 0
    dsHdmiInStatus_t status = {0}; // Initialize all fields to 0
    dsHdmiInPort_t port = dsHDMI_IN_PORT_NONE; // Initialize to dsHDMI_IN_PORT_NONE

    gTestID = 5;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    UT_LOG_DEBUG("Invoking dsHdmiInInit");
    ret = dsHdmiInInit();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsHdmiInGetNumberOfInputs with valid buffer");
    ret = dsHdmiInGetNumberOfInputs(&numInputs);
    UT_LOG_DEBUG("Number of inputs: %d, Return status: %d", numInputs, ret);
    UT_ASSERT_EQUAL(ret, dsERR_NONE);
    UT_ASSERT_TRUE(numInputs >= 0 && numInputs <= dsHDMI_IN_PORT_MAX);

    for (port = dsHDMI_IN_PORT_0; port < numInputs; port++)
    {
        UT_LOG_DEBUG("Invoking dsHdmiInSelectPort with port: %d, audioMix: false, evideoPlaneType: dsVideoPlane_PRIMARY, topMost: false", port);
        ret = dsHdmiInSelectPort(port, false, dsVideoPlane_PRIMARY, false);
        UT_LOG_DEBUG("Return status: %d", ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);

        if (ret != dsERR_NONE)
        {
            continue;
        }

        UT_LOG_DEBUG("Invoking dsHdmiInGetStatus with valid buffer");
        ret = dsHdmiInGetStatus(&status);
        UT_LOG_DEBUG("isPresented: %d, isPortConnected: %d, activePort: %d, Return status: %d", status.isPresented, status.isPortConnected[port], status.activePort, ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_ASSERT_EQUAL(status.activePort, port);
        UT_ASSERT_FALSE(status.isPresented);
        UT_ASSERT_FALSE(status.isPortConnected[port]);
    }

    UT_LOG_DEBUG("Invoking dsHdmiInTerm");
    ret = dsHdmiInTerm();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test verifies the HDMI input port status for a given source
*
* This test function initializes the HDMI input, gets the number of inputs, selects each port, gets the status of each port, and finally terminates the HDMI input. The test is designed to ensure that the HDMI input port status is correctly reported for each source.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 006@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsHdmiIn_L2_Low-Level_TestSpecification.md](../../docs/pages/dsHdmiIn_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsHdmiIn_VerifyHdmiInputPortStatus_source(void)
{
    gTestID = 6;
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
    UT_ASSERT_TRUE(numInputs >= 0 && numInputs <= dsHDMI_IN_PORT_MAX);

    for (uint8_t i = 0; i < numInputs; i++)
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
* This test initializes the HDMI input, checks if the HDMI ARC Port is available and validates the number of ports and their status. It then terminates the HDMI input. The test is designed to ensure the proper functioning of HDMI ARC Port sink.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 007@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsHdmiIn_L2_Low-Level_TestSpecification.md](../../docs/pages/dsHdmiIn_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsHdmiIn_VerifyHdmiArcPort_sink(void)
{
    gTestID = 7;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t retStatus = dsERR_NONE; //Initialize to dsERR_NONE
    bool isArcPort = false; //Initialize to 0
    dsHdmiInPort_t iPort = dsHDMI_IN_PORT_NONE; //Initialize to default dsHDMI_IN_PORT_NONE

    UT_LOG_DEBUG("Invoking dsHdmiInInit");
    retStatus = dsHdmiInInit();
    UT_LOG_DEBUG("Return status: %d", retStatus);
    UT_ASSERT_EQUAL_FATAL(retStatus, dsERR_NONE);

    for(iPort = dsHDMI_IN_PORT_0; iPort < dsHDMI_IN_PORT_MAX; iPort++)
    {
        UT_LOG_DEBUG("Invoking dsIsHdmiARCPort with iPort: %d", iPort);
        retStatus = dsIsHdmiARCPort(iPort, &isArcPort);
        UT_LOG_DEBUG("Return status: %d, isArcPort: %d", retStatus, isArcPort);
        if((retStatus != dsERR_NONE) || (isArcPort == false))
        {
            UT_LOG_ERROR("Port %d is not an dsIsHdmiARCPort : %d", iPort, retStatus);
            continue;
        }

        UT_ASSERT_KVP_EQUAL_PROFILE_UINT8(iPort, "HDMIIN/HdmiArcPort/portNumber");
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
* This test sets the EDID version for HDMI input ports and then gets the EDID version to validate it. It also retrieves the EDID bytes info to validate the length. This is done to ensure the correct functioning of HDMI input related APIs.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 008@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsHdmiIn_L2_Low-Level_TestSpecification.md](../../docs/pages/dsHdmiIn_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsHdmiIn_SetAndGetEdidVersionAndValidateEdidLength_sink(void)
{
    gTestID = 8;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;
    dsHdmiInPort_t hdmiPort[] = {dsHDMI_IN_PORT_0, dsHDMI_IN_PORT_1, dsHDMI_IN_PORT_2};
    tv_hdmi_edid_version_t edidVersion[] = {HDMI_EDID_VER_14, HDMI_EDID_VER_20};
    tv_hdmi_edid_version_t getEdidVersion = HDMI_EDID_VER_MAX;
    unsigned char edid[256] = { 0 };
    int length = 0;

    UT_LOG_DEBUG("Invoking dsHdmiInInit");
    ret = dsHdmiInInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for (int i = dsHDMI_IN_PORT_0; i < dsHDMI_IN_PORT_2; i++)
    {
        for (int j = HDMI_EDID_VER_14; j < HDMI_EDID_VER_MAX; j++)
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

            UT_LOG_DEBUG("Invoking dsGetEDIDBytesInfo with hdmiPort=%d\n", hdmiPort[i]);
            ret = dsGetEDIDBytesInfo(hdmiPort[i], edid, &length);
            UT_ASSERT_EQUAL(ret, dsERR_NONE);
            if (ret != dsERR_NONE)
            {
                UT_LOG_ERROR("Failed to get EDID bytes info\n");
            }
            UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(length, "HDMIIN/EDID_Data/edidbytesLength");
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
* In this test, the dsHdmiInInit function is invoked to initialize the HDMI input. Then, the dsGetSupportedGameFeaturesList function is called to get the list of supported game features. The results are then compared with the expected values from the Sink_HDMIIN.yaml profile. Finally, the dsHdmiInTerm function is invoked to terminate the HDMI input. The test ensures that all these operations are successful and the supported game features list is as expected.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 009@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsHdmiIn_L2_Low-Level_TestSpecification.md](../../docs/pages/dsHdmiIn_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsHdmiIn_GetSupportedGameFeaturesList_sink(void)
{
    gTestID = 9;
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
        UT_LOG_DEBUG("Invoking dsHdmiInTerm due to failure of dsGetSupportedGameFeaturesList");
        ret = dsHdmiInTerm();
        UT_LOG_DEBUG("Return status: %d", ret);
        return;
    }

    UT_LOG_DEBUG("Game feature count: %d",features.gameFeatureCount);
    UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(features.gameFeatureCount, "HDMIIN/gameFeatures/count");

    for ( uint8_t i = 0; i < features.gameFeatureCount; i++ ){
        UT_LOG_DEBUG("Game feature list: %s",features.gameFeatureList);
        UT_ASSERT_KVP_EQUAL_PROFILE_STRING(features.gameFeatureList,"HDMIIN/gameFeatures/feature")
    }

    UT_LOG_DEBUG("Invoking dsHdmiInTerm");
    ret = dsHdmiInTerm();
    UT_LOG_DEBUG("Return status: %d", ret);
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief This test aims to verify the functionality of setting and getting the ALLM support for HDMI input.
*
* In this test, the dsHdmiInInit function is first invoked to initialize the HDMI input. Then, the dsSetEdid2AllmSupport function is called to set the ALLM support for HDMI input to true. The dsGetEdid2AllmSupport function is then called to get the current ALLM support status, which should be true. The same process is repeated with the ALLM support set to false. Finally, the dsHdmiInTerm function is invoked to terminate the HDMI input. The test ensures that all these operations return no error.
*
* **Test Group ID:** 02@n
* **Test Case ID:** 010@n
*
* **Test Procedure:**
* Refer to UT specification documentation [dsHdmiIn_L2_Low-Level_TestSpecification.md](../../docs/pages/dsHdmiIn_L2_Low-Level_TestSpecification.md)
*/

void test_l2_dsHdmiIn_SetAndGetAllmSupport_sink(void)
{
    dsError_t ret = dsERR_NONE;
    bool allmSupport = false;
    dsHdmiInPort_t iHdmiPort = dsHDMI_IN_PORT_0;

    gTestID = 10;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    UT_LOG_DEBUG("Invoking dsHdmiInInit");
    ret = dsHdmiInInit();
    UT_ASSERT_EQUAL_FATAL(ret, dsERR_NONE);

    for ( iHdmiPort = dsHDMI_IN_PORT_0; iHdmiPort < dsHDMI_IN_PORT_MAX; iHdmiPort++ ){

        UT_LOG_DEBUG("Invoking dsSetEdid2AllmSupport with iHdmiPort set to %d and allmSupport set to true", iHdmiPort);
        ret = dsSetEdid2AllmSupport(iHdmiPort, true);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_DEBUG("Invoking dsHdmiInTerm due to failure of dsSetEdid2AllmSupport");
            ret = dsHdmiInTerm();
            UT_LOG_DEBUG("Return status: %d", ret);
            return;
        }

        UT_LOG_DEBUG("Invoking dsGetEdid2AllmSupport with iHdmiPort set to %d", iHdmiPort);
        ret = dsGetEdid2AllmSupport(iHdmiPort, &allmSupport);
        UT_LOG_DEBUG("allmSupport: %d and return status: %d", allmSupport, ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_ASSERT_EQUAL(allmSupport, true);

        UT_LOG_DEBUG("Invoking dsSetEdid2AllmSupport with iHdmiPort set to %d and allmSupport set to false", iHdmiPort);
        ret = dsSetEdid2AllmSupport(iHdmiPort, false);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        if (ret != dsERR_NONE)
        {
            UT_LOG_DEBUG("Invoking dsHdmiInTerm due to failure of dsSetEdid2AllmSupport");
            ret = dsHdmiInTerm();
            UT_LOG_DEBUG("Return status: %d", ret);
            return;
        }

        UT_LOG_DEBUG("Invoking dsGetEdid2AllmSupport with iHdmiPort set to %d", iHdmiPort);
        ret = dsGetEdid2AllmSupport(iHdmiPort, &allmSupport);
        UT_LOG_DEBUG("allmSupport: %d and return status: %d", allmSupport, ret);
        UT_ASSERT_EQUAL(ret, dsERR_NONE);
        UT_ASSERT_EQUAL(allmSupport, false);
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
    // Create the test suite
    pSuite = UT_add_suite("[L2 dsHdmiIn]", NULL, NULL);
    if (pSuite == NULL)
    {
        return -1;
    }
    // List of test function names and strings

    UT_add_test( pSuite, "l2_dsHdmiIn_GetNumberOfInputs_sink", test_l2_dsHdmiIn_GetNumberOfInputs_sink);
    UT_add_test( pSuite, "l2_dsHdmiIn_GetNumberOfInputs_source", test_l2_dsHdmiIn_GetNumberOfInputs_source);
    UT_add_test( pSuite, "l2_dsHdmiIn_GetStatus_sink", test_l2_dsHdmiIn_GetStatus_sink);
    UT_add_test( pSuite, "l2_dsHdmiIn_GetStatus_source", test_l2_dsHdmiIn_GetStatus_source);
    UT_add_test( pSuite, "l2_dsHdmiIn_VerifyHdmiInputPortStatus_sink", test_l2_dsHdmiIn_VerifyHdmiInputPortStatus_sink);
    UT_add_test( pSuite, "l2_dsHdmiIn_VerifyHdmiInputPortStatus_source", test_l2_dsHdmiIn_VerifyHdmiInputPortStatus_source);
    UT_add_test( pSuite, "l2_dsHdmiIn_VerifyHdmiArcPort_sink", test_l2_dsHdmiIn_VerifyHdmiArcPort_sink);
    UT_add_test( pSuite, "l2_dsHdmiIn_SetAndGetEdidVersionAndValidateEdidLength_sink", test_l2_dsHdmiIn_SetAndGetEdidVersionAndValidateEdidLength_sink);
    UT_add_test( pSuite, "l2_dsHdmiIn_GetSupportedGameFeaturesList_sink", test_l2_dsHdmiIn_GetSupportedGameFeaturesList_sink);
    UT_add_test( pSuite, "l2_dsHdmiIn_SetAndGetAllmSupport_sink", test_l2_dsHdmiIn_SetAndGetAllmSupport_sink);

    return 0;
}