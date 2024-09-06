
/**
*  If not stated otherwise in this file or this component's LICENSE
*  file the following copyright and licenses apply:
*
*  Copyright 2022 RDK Management
*
*  Licensed under the Apache License, Version 2.0 (the License);
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*  http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an AS IS BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
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
 * @defgroup DS_Display_HALTEST Device Settings Display HAL Tests
 * @{
 */

/**
 * @defgroup DS_Display_HALTEST_L3 Device Settings Display HAL Tests L3 File
 * @{
 * @parblock
 *
 * ### L1 Tests for DS Display HAL :
 *
 * Level 3 unit test cases for all APIs of Device Settings Display HAL
 *
 * **Pre-Conditions:**  None@n
 * **Dependencies:** None@n
 *
 * Refer to API Definition specification documentation : [ds-display_halSpec.md](../../docs/pages/ds-display_halSpec.md)
 *
 * @endparblock
 */

/**
 * @file test_l3_dsDisplay.c
 *
 */

#include <string.h>
#include <stdlib.h>

#include <ut.h>
#include <ut_log.h>
#include <ut_kvp_profile.h>
#include <ut_control_plane.h>
#include "stdint.h"
#include "dsDisplay.h"
#include "test_parse_configuration.h"

#define UT_LOG_MENU_INFO UT_LOG_INFO

#define DS_ASSERT assert

/* Global Variables */

static int32_t gTestGroup = 3;
static int32_t gTestID    = 1;
static intptr_t displayHandle = 0;

/* Enum mapping tables */

/* dsError_t */
const static ut_control_keyStringMapping_t errorMappingTable[] = {
    {"dsERR_NONE", (int32_t)dsERR_NONE},
    {"dsERR_GENERAL", (int32_t)dsERR_GENERAL},
    {"dsERR_INVALID_PARAM", (int32_t)dsERR_INVALID_PARAM},
    {"dsERR_INVALID_STATE", (int32_t)dsERR_INVALID_STATE},
    {"dsERR_ALREADY_INITIALIZED", (int32_t)dsERR_ALREADY_INITIALIZED},
    {"dsERR_NOT_INITIALIZED", (int32_t)dsERR_NOT_INITIALIZED},
    {"dsERR_OPERATION_NOT_SUPPORTED", (int32_t)dsERR_OPERATION_NOT_SUPPORTED},
    {"dsERR_RESOURCE_NOT_AVAILABLE", (int32_t)dsERR_RESOURCE_NOT_AVAILABLE},
    {"dsERR_OPERATION_FAILED", (int32_t)dsERR_OPERATION_FAILED},
    {"dsErr_MAX", (int32_t)dsErr_MAX},
    {NULL, -1}
};

/* dsVideoPortType_t */
const static ut_control_keyStringMapping_t videoPortTypeMappingTable[] = {
    {"dsVIDEOPORT_TYPE_RF", (int32_t)dsVIDEOPORT_TYPE_RF},
    {"dsVIDEOPORT_TYPE_BB", (int32_t)dsVIDEOPORT_TYPE_BB},
    {"dsVIDEOPORT_TYPE_SVIDEO", (int32_t)dsVIDEOPORT_TYPE_SVIDEO},
    {"dsVIDEOPORT_TYPE_1394", (int32_t)dsVIDEOPORT_TYPE_1394},
    {"dsVIDEOPORT_TYPE_DVI", (int32_t)dsVIDEOPORT_TYPE_DVI},
    {"dsVIDEOPORT_TYPE_COMPONENT", (int32_t)dsVIDEOPORT_TYPE_COMPONENT},
    {"dsVIDEOPORT_TYPE_HDMI", (int32_t)dsVIDEOPORT_TYPE_HDMI},
    {"dsVIDEOPORT_TYPE_HDMI_INPUT", (int32_t)dsVIDEOPORT_TYPE_HDMI_INPUT},
    {"dsVIDEOPORT_TYPE_INTERNAL", (int32_t)dsVIDEOPORT_TYPE_INTERNAL},
    {"dsVIDEOPORT_TYPE_MAX", (int32_t)dsVIDEOPORT_TYPE_MAX},
    {NULL, -1}
};

/* dsDisplayEvent_t */
const static ut_control_keyStringMapping_t displayEventMappingTable[] = {
    {"dsDISPLAY_EVENT_CONNECTED", (int32_t)dsDISPLAY_EVENT_CONNECTED},
    {"dsDISPLAY_EVENT_DISCONNECTED", (int32_t)dsDISPLAY_EVENT_DISCONNECTED},
    {"dsDISPLAY_RXSENSE_ON", (int32_t)dsDISPLAY_RXSENSE_ON},
    {"dsDISPLAY_RXSENSE_OFF", (int32_t)dsDISPLAY_RXSENSE_OFF},
    {"dsDISPLAY_HDCPPROTOCOL_CHANGE", (int32_t)dsDISPLAY_HDCPPROTOCOL_CHANGE},
    {"dsDISPLAY_EVENT_MAX", (int32_t)dsDISPLAY_EVENT_MAX},
    {NULL, -1}
};

/* dsVideoAspectRatio_t */
const static ut_control_keyStringMapping_t dsVideoAspect_RatioMappingTable[] = {
    {"dsVIDEO_ASPECT_RATIO_4x3", (int32_t)dsVIDEO_ASPECT_RATIO_4x3},
    {"dsVIDEO_ASPECT_RATIO_16x9", (int32_t)dsVIDEO_ASPECT_RATIO_16x9},
    {"dsVIDEO_ASPECT_RATIO_MAX", (int32_t)dsVIDEO_ASPECT_RATIO_MAX},
    {NULL, -1}
};

/**
 * @brief Callback function for display events.
 *
 * This function is invoked when a display event occurs, providing information about the event type.
 */
void DisplayEventCallback(intptr_t handle, dsDisplayEvent_t event, void* eventData)
{
    UT_LOG_INFO("DisplayEventCallback dsDisplayEvent_t:[%s] ", UT_Control_GetMapString(displayEventMappingTable, event));
}

/**
 * @brief This test initializes the dsDisplay Module.
 *
 * This test function initializes the dsDisplay Module.
 *
 * **Test Group ID:** 03@n
 * **Test Case ID:** 001@n
 *
 * **Test Procedure:**
 * Refer to Test specification documentation
 * [ds-display_L3_Low-Level_TestSpecification.md](../../docs/pages/ds-display_L3_Low-Level_TestSpecification.md)
 */
void dsDisplay_Init()
{
    gTestID = 1;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);

    dsError_t status   = dsERR_NONE;

    UT_LOG_INFO("Calling dsDisplayInit()");
    status = dsDisplayInit();
    UT_LOG_INFO("Result dsDisplayInit() dsError_t=[%s]", UT_Control_GetMapString(errorMappingTable, status));
    DS_ASSERT(status == dsERR_NONE);

    UT_LOG_INFO("Out %s", __FUNCTION__);

}

/**
 * @brief This test terminates the dsDisplay Module.
 *
 * This test function terminates the dsDisplay Module.
 *
 * **Test Group ID:** 03@n
 * **Test Case ID:** 002@n
 *
 * **Test Procedure:**
 * Refer to Test specification documentation
 * [ds-display_L3_Low-Level_TestSpecification.md](../../docs/pages/ds-display_L3_Low-Level_TestSpecification.md)
 */
void dsDisplay_Term()
{
    gTestID = 2;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);

    dsError_t status   = dsERR_NONE;

    UT_LOG_INFO("Calling dsDisplayTerm()");
    status = dsDisplayTerm();
    UT_LOG_INFO("Result dsDisplayTerm() dsError_t=[%s]", UT_Control_GetMapString(errorMappingTable, status));
    DS_ASSERT(status == dsERR_NONE);

    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
 * @brief Retrieves the display handle based on user-selected video port.
 *
 * Allows the user to select a video port and retrieves the corresponding display handle.
 *
 * **Test Group ID:** 03@n
 * **Test Case ID:** 003@n
 *
 * **Test Procedure:**
 * Refer to Test specification documentation
 * [ds-display_L3_Low-Level_TestSpecification.md](../../docs/pages/ds-display_L3_Low-Level_TestSpecification.md)
 */
static void dsGetDisplay_getHandle()
{
    gTestID = 3;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);

    dsError_t status   = dsERR_NONE;
    int32_t choice,port;

    UT_LOG_INFO(" \t  Supported Video Port are:");
    UT_LOG_INFO("------------------------------------------");
    for (port = 0; port < gDSvideoPort_NumberOfPorts; port++) {
        UT_LOG_INFO("\t%d.  %-20s\n", port+1, UT_Control_GetMapString(videoPortTypeMappingTable, gDSVideoPortConfiguration[port].typeid));
    }
    UT_LOG_INFO("------------------------------------------");
    UT_LOG_INFO(" Select the Video Port:");
    scanf("%d", &choice);
    port = choice - 1;
    UT_LOG_INFO("Port %d choice %d ",port,choice);
    if(choice < 1 || choice > gDSvideoPort_NumberOfPorts) {
        UT_LOG_ERROR("Invalid Port choice\n");
        return;
    }

    UT_LOG_INFO("Calling dsGetDisplay(IN:type:[%s],IN:index:[%d])", UT_Control_GetMapString(videoPortTypeMappingTable, gDSVideoPortConfiguration[port].typeid));
    status = dsGetDisplay(gDSVideoPortConfiguration[port].typeid, gDSVideoPortConfiguration[port].index, &displayHandle);

    UT_LOG_INFO("Result dsGetDisplay(Handle:[0x%0X]]) dsError_t=[%s]", displayHandle, UT_Control_GetMapString(errorMappingTable, status));
    DS_ASSERT(status == dsERR_NONE);

    UT_LOG_INFO("Out %s", __FUNCTION__);

}

/**
 * @brief Retrieves Extended Display Identification Data (EDID) for the display.
 *
 * Retrieves the EDID information for the display associated with the selected handle.
 *
 * **Test Group ID:** 03@n
 * **Test Case ID:** 004@n
 *
 * **Test Procedure:**
 * Refer to Test specification documentation
 * [ds-display_L3_Low-Level_TestSpecification.md](../../docs/pages/ds-display_L3_Low-Level_TestSpecification.md)
 */
void dsDisplay_GetEDID() 
{
    gTestID = 4;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);

    dsError_t status = dsERR_NONE;
    dsDisplayEDID_t *edid =NULL;

    dsGetDisplay_getHandle();

    if (displayHandle == -1) {
        UT_LOG_ERROR("Failed to get display handle\n");
        return;
    }

    edid = (dsDisplayEDID_t *)malloc(sizeof(dsDisplayEDID_t));
    if (edid == NULL) {
        UT_LOG_ERROR("Failed to allocate memory for edid\n");
        return;
    }

    UT_LOG_INFO("Calling dsGetEDID(IN:handle:[0x%0X]])", displayHandle);
    status = dsGetEDID(displayHandle, edid);

    if (status != dsERR_NONE) {
        UT_LOG_ERROR("dsGetEDID failed with error: %d", status);
        free(edid);
        return;
    }

    UT_LOG_INFO("Result dsGetEDID(dsDisplayEDID_t(productCode:[%d], serialNumber:[%d], manufactureYear:[%d], manufactureWeek:[%d], hdmiDeviceType:[%s], isRepeater:[%s], physicalAddressA:[%u], physicalAddressB:[%u], physicalAddressC:[%u], physicalAddressD:[%u], numOfSupportedResolution:[%d], monitorName:[%s])", \
             edid->productCode, edid->serialNumber, edid->manufactureYear, edid->manufactureWeek, edid->hdmiDeviceType, edid->isRepeater, edid->physicalAddressA, edid->physicalAddressB, edid->physicalAddressC, edid->physicalAddressD, edid->numOfSupportedResolution, edid->monitorName);
    DS_ASSERT(status == dsERR_NONE);

    free(edid);

    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
 * @brief Retrieves the Extended Display Identification Data (EDID) bytes for the display.
 *
 * Retrieves the EDID data bytes for the display associated with the selected handle.
 *
 * **Test Group ID:** 03@n
 * **Test Case ID:** 005@n
 *
 * **Test Procedure:**
 * Refer to Test specification documentation
 * [ds-display_L3_Low-Level_TestSpecification.md](../../docs/pages/ds-display_L3_Low-Level_TestSpecification.md)
 */
void dsDisplay_GetEDIDBytes()
{
    gTestID = 5;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);

    dsError_t status = dsERR_NONE;
    int length = 0;
    unsigned char *edid = NULL;

    dsGetDisplay_getHandle();

    UT_LOG_INFO("Calling dsGetEDID(Handle:[0x%0X]])", displayHandle);
    status = dsGetEDIDBytes(displayHandle, edid, &length);

    UT_LOG_INFO("Result dsGetEDIDBytes()  dsError_t=[%s]", UT_Control_GetMapString(errorMappingTable, status));
    DS_ASSERT(status == dsERR_NONE);

    UT_LOG_INFO("Out %s", __FUNCTION__);

}

/**
 * @brief Retrieves the aspect ratio of the display.
 *
 * Retrieves the aspect ratio of the display.
 *
 * **Test Group ID:** 03@n
 * **Test Case ID:** 006@n
 *
 * **Test Procedure:**
 * Refer to Test specification documentation
 * [ds-display_L3_Low-Level_TestSpecification.md](../../docs/pages/ds-display_L3_Low-Level_TestSpecification.md)
 */
void GetDisplay_AspectRatio()
{
    gTestID = 6;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);

    dsError_t status   = dsERR_NONE;
    dsVideoAspectRatio_t displayAspectRatio;
  
    dsGetDisplay_getHandle();

    UT_LOG_INFO("Calling dsGetEDID(IN:handle:[0x%0X]) ", displayHandle);
    status = dsGetDisplayAspectRatio(displayHandle, &displayAspectRatio);

    UT_LOG_INFO("Result dsGetDisplayAspectRatio(dsVideoAspectRatio_t:[%s], dsError_t=[%s])", UT_Control_GetMapString(dsVideoAspect_RatioMappingTable, displayAspectRatio), UT_Control_GetMapString(errorMappingTable, status));

    DS_ASSERT(status == dsERR_NONE);

    UT_LOG_INFO("Out %s", __FUNCTION__);

}

/**
 * @brief This test registers a callback function for display events.
 *
 * Registers a callback function to handle display events associated with the display handle.
 *
 * **Test Group ID:** 03@n
 * **Test Case ID:** 007@n
 *
 * **Test Procedure:**
 * Refer to Test specification documentation
 * [ds-display_L3_Low-Level_TestSpecification.md](../../docs/pages/ds-display_L3_Low-Level_TestSpecification.md)
 */
void RegisterDisplayEventCallback()
{
    gTestID = 7;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);

    dsError_t status   = dsERR_NONE;

    dsGetDisplay_getHandle();

    UT_LOG_INFO("Calling dsGetEDID(IN:handle:[0x%0X]) ", displayHandle);

    status = dsRegisterDisplayEventCallback(displayHandle,(dsDisplayEventCallback_t)DisplayEventCallback);

    UT_LOG_INFO("Result dsRegisterDisplayEventCallback() dsError_t=[%s]", UT_Control_GetMapString(errorMappingTable, status));
    DS_ASSERT(status == dsERR_NONE);

    UT_LOG_INFO("Out %s", __FUNCTION__);
}

static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main tests for this module
 *
 * @return int - 0 on success, otherwise failure
 */

int test_l3_dsDisplay_register (void)
{
    /* add a suite to the registry */
    pSuite = UT_add_suite( "[L3 dsDisplay]", NULL, NULL );
    if ( NULL == pSuite)
    {
        return -1;
    }

    //Create the test suite
    UT_add_test( pSuite, "dsDisplay Init", dsDisplay_Init);
    UT_add_test( pSuite, "dsDisplay Term", dsDisplay_Term);
    UT_add_test( pSuite, "dsDisplay GetEDID", dsDisplay_GetEDID);
    UT_add_test( pSuite, "dsDisplay GetEDIDBytes", dsDisplay_GetEDIDBytes);
    UT_add_test( pSuite, "GetDisplay AspectRatio",GetDisplay_AspectRatio);
    UT_add_test( pSuite, "RegisterDisplay_EventCallback",RegisterDisplayEventCallback);

    return 0;
}


/** @} */ // End of DS_Display_HALTEST_L3
/** @} */ // End of DS_Display_HALTEST
/** @} */ // End of Device_Settings_HALTEST
/** @} */ // End of Device_Settings
/** @} */ // End of HPK
