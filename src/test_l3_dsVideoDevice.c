/**
*  If not stated otherwise in this file or this component's LICENSE
*  file the following copyright and licenses apply:
*
*  Copyright 2024 RDK Management
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
 * @addtogroup HPK Hardware deviceing Kit
 * @{
 * @par The Hardware deviceing Kit
 * HPK is the next evolution of the well-defined Hardware Abstraction Layer
 * (HAL), but augmented with more comprehensive documentation and test suites
 * that OEM or SOC vendors can use to self-certify their devices before taking
 * them to RDKM for validation or to an operator for final integration and
 * deployment. The Hardware deviceing Kit effectively enables an OEM and/or SOC
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
 * @defgroup DS_VideoDevice_HALTEST Device Settings Video Device HAL Tests
 * @{
 */

/**
 * @defgroup DS_VideoDevice_HALTEST_L3 Device Settings Video Device HAL Tests L3 File
 * @{
 * @parblock
 *
 * ### L3 Tests for DS Video Device HAL :
 *
 * Level 3 test cases for all APIs of Device Settings Video Device HAL
 *
 * **Pre-Conditions:**  None@n
 * **Dependencies:** None@n
 *
 * Refer to API Definition specification documentation : [ds-video-device_halSpec.md](../../docs/pages/ds-video-device_halSpec.md)
 *
 * @endparblock
 */

/**
 * @file test_l3_dsVideoDevice.c
 *
 */

#include <stdlib.h>
#include <stdbool.h>
#include <ut.h>
#include <ut_log.h>
#include <ut_kvp_profile.h>
#include <ut_control_plane.h>
#include <ut_kvp.h>

#include "test_parse_configuration.h"
#include "dsVideoDevice.h"


#define DS_ASSERT(actual,expected) assert(actual==expected)
#define UT_LOG_MENU_INFO UT_LOG_INFO

intptr_t gHandle = 0;
int32_t gSelectedVideoDevice = 0;

/* currently it support only one video deice as per HAL spec*/
int num_of_devices = 1; 

/* Global Variables */
static int32_t gTestGroup = 3;
static int32_t gTestID    = 1;

// Mapping table for dsError_t
const static ut_control_keyStringMapping_t  dsErrorMappingTable[] = {
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

// Mapping table for dsVideoZoom_t
const static ut_control_keyStringMapping_t dsVideoZoomMappingTable[] = {
    {"dsVIDEO_ZOOM_UNKNOWN", (int32_t)dsVIDEO_ZOOM_UNKNOWN},
    {"dsVIDEO_ZOOM_NONE", (int32_t)dsVIDEO_ZOOM_NONE},
    {"dsVIDEO_ZOOM_FULL", (int32_t)dsVIDEO_ZOOM_FULL},
    {"dsVIDEO_ZOOM_LB_16_9", (int32_t)dsVIDEO_ZOOM_LB_16_9},
    {"dsVIDEO_ZOOM_LB_14_9", (int32_t)dsVIDEO_ZOOM_LB_14_9},
    {"dsVIDEO_ZOOM_CCO", (int32_t)dsVIDEO_ZOOM_CCO},
    {"dsVIDEO_ZOOM_PAN_SCAN", (int32_t)dsVIDEO_ZOOM_PAN_SCAN},
    {"dsVIDEO_ZOOM_LB_2_21_1_ON_4_3", (int32_t)dsVIDEO_ZOOM_LB_2_21_1_ON_4_3},
    {"dsVIDEO_ZOOM_LB_2_21_1_ON_16_9", (int32_t)dsVIDEO_ZOOM_LB_2_21_1_ON_16_9},
    {"dsVIDEO_ZOOM_PLATFORM", (int32_t)dsVIDEO_ZOOM_PLATFORM},
    {"dsVIDEO_ZOOM_16_9_ZOOM", (int32_t)dsVIDEO_ZOOM_16_9_ZOOM},
    {"dsVIDEO_ZOOM_PILLARBOX_4_3", (int32_t)dsVIDEO_ZOOM_PILLARBOX_4_3},
    {"dsVIDEO_ZOOM_WIDE_4_3", (int32_t)dsVIDEO_ZOOM_WIDE_4_3},
    {"dsVIDEO_ZOOM_MAX", (int32_t)dsVIDEO_ZOOM_MAX},
    {NULL, -1}
};

// Mapping table for dsVideoCodingFormat_t
const static ut_control_keyStringMapping_t dsVideoCodingFormatMappingTable[] = {
    {"dsVIDEO_CODEC_MPEGHPART2", (int32_t)dsVIDEO_CODEC_MPEGHPART2},
    {"dsVIDEO_CODEC_MPEG4PART10", (int32_t)dsVIDEO_CODEC_MPEG4PART10},
    {"dsVIDEO_CODEC_MPEG2", (int32_t)dsVIDEO_CODEC_MPEG2},
    {"dsVIDEO_CODEC_MAX", (int32_t)dsVIDEO_CODEC_MAX},
    {NULL, -1}
};

// Mapping table for dsVideoCodecHevcProfiles_t
const static ut_control_keyStringMapping_t dsVideoCodecHevcProfilesMappingTable[] = {
    {"dsVIDEO_CODEC_HEVC_PROFILE_MAIN", (int32_t)dsVIDEO_CODEC_HEVC_PROFILE_MAIN},
    {"dsVIDEO_CODEC_HEVC_PROFILE_MAIN10", (int32_t)dsVIDEO_CODEC_HEVC_PROFILE_MAIN10},
    {"dsVIDEO_CODEC_HEVC_PROFILE_MAINSTILLPICTURE", (int32_t)dsVIDEO_CODEC_HEVC_PROFILE_MAINSTILLPICTURE},
    {"dsVIDEO_CODEC_HEVC_MAX", (int32_t)dsVIDEO_CODEC_HEVC_MAX},
    {NULL, -1}
};

// Mapping table for dsVideoFrameRate_t
const static ut_control_keyStringMapping_t dsVideoFrameRateTable[] = {
    {"dsVIDEO_FRAMERATE_UNKNOWN", (int32_t)dsVIDEO_FRAMERATE_UNKNOWN},
    {"dsVIDEO_FRAMERATE_24", (int32_t)dsVIDEO_FRAMERATE_24},
    {"dsVIDEO_FRAMERATE_25", (int32_t)dsVIDEO_FRAMERATE_25},
    {"dsVIDEO_FRAMERATE_30", (int32_t)dsVIDEO_FRAMERATE_30},
    {"dsVIDEO_FRAMERATE_60", (int32_t)dsVIDEO_FRAMERATE_60},
    {"dsVIDEO_FRAMERATE_23dot98", (int32_t)dsVIDEO_FRAMERATE_23dot98},
    {"dsVIDEO_FRAMERATE_29dot97", (int32_t)dsVIDEO_FRAMERATE_29dot97},
    {"dsVIDEO_FRAMERATE_50", (int32_t)dsVIDEO_FRAMERATE_50},
    {"dsVIDEO_FRAMERATE_59dot94", (int32_t)dsVIDEO_FRAMERATE_59dot94},
    {"dsVIDEO_FRAMERATE_MAX", (int32_t)dsVIDEO_FRAMERATE_MAX},
    {NULL, -1}
};

/**
 * @brief This function clears the stdin buffer.
 *
 * This function clears the stdin buffer.
 */
void readAndDiscardRestOfLine(FILE* in)
{
    int c;
    while ( (c = fgetc(in)) != EOF && c != '\n');
}

/*FrameratePreChange callback*/
void dsVideoDevice_FrameratePreChange(unsigned int tSecond)
{
    UT_LOG_INFO("FrameratePreChange callback tSecond:[%d]",tSecond);
}

/*FrameratePostChange callback*/
void dsVideoDevice_FrameratePostChange(unsigned int tSecond)
{
    UT_LOG_INFO("FrameratePostChange callback tSecond:[%d]",tSecond);
}

static void dsVideoDevice_getHandle()
{
    dsError_t status   = dsERR_NONE;
    int32_t device;

    UT_LOG_MENU_INFO(" Supported Video Device:");
    for (device = 0; device < num_of_devices; device++)
    {
        UT_LOG_MENU_INFO("\t%d.  VideoDevice%d ", device, device);
    }
    UT_LOG_MENU_INFO("------------------------------------------");
    UT_LOG_MENU_INFO(" Select the Video Device:");
    scanf("%d", &gSelectedVideoDevice);
    readAndDiscardRestOfLine(stdin);
    UT_LOG_INFO("Calling dsGetVideoDevice(IN:index:[%d], OUT:Handle[%p])", gSelectedVideoDevice, &gHandle);
    status = dsGetVideoDevice(gSelectedVideoDevice, &gHandle);
    UT_LOG_INFO("Result dsGetVideodevice(IN:index:[0x%0d], OUT:Handle[%d]) dsError_t=[%s]",gSelectedVideoDevice, \
                                    gHandle, UT_Control_GetMapString(dsErrorMappingTable, status));
    DS_ASSERT(status, dsERR_NONE);
    if (status != dsERR_NONE)
    {
        UT_LOG_ERROR("dsGetVideodevice failed with error: %d", status);
    }
}

/**
* @brief Initialization of the Device settings - Video Device Module
*
* This test provides a scope to Intialize the Video Device module.
* **Test Group ID:** 03@n
* **Test Case ID:** 001@n
*
* **Pre-Conditions:** None@n
*
* **Dependencies:** None@n
*
* **User Interaction:** @n
* User or Automation tool should select VideoDevice_Init before running any test.
*
*/
void test_l3_dsVideoDevice_Init()
{
    gTestID = 1;
    dsError_t status   = dsERR_NONE;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);

    UT_LOG_INFO("Calling dsVideoDeviceInit()");
    status = dsVideoDeviceInit();
    UT_LOG_INFO("Result dsVideoDeviceInit() OUT: dsError_t=[%s]", UT_Control_GetMapString(dsErrorMappingTable, status));
    DS_ASSERT(status, dsERR_NONE);
    UT_LOG_INFO("Calling dsRegisterFrameratePreChangeCB()");
    status = dsRegisterFrameratePreChangeCB(dsVideoDevice_FrameratePreChange);
    UT_LOG_INFO("Result dsRegisterFrameratePreChangeCB() OUT:dsError_t=[%s]", UT_Control_GetMapString(dsErrorMappingTable, status));
    DS_ASSERT(status, dsERR_NONE);
    UT_LOG_INFO("Calling dsRegisterFrameratePostChangeCB()");
    status = dsRegisterFrameratePostChangeCB(dsVideoDevice_FrameratePostChange);
    UT_LOG_INFO("Result dsRegisterFrameratePostChangeCB() OUT:dsError_t=[%s]", UT_Control_GetMapString(dsErrorMappingTable, status));
    DS_ASSERT(status, dsERR_NONE);
    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief Termination of the Device settings - Video Device Module
*
* This test provides a scope to Terminate the Video Device module.
* **Test Group ID:** 03@n
* **Test Case ID:** 011@n
* **Pre-Conditions:** None@n
*
* **Dependencies:** None@n
*
* **User Interaction:** @n
* User or Automation tool should select VideoDevice_Term at end of every test.
*
*/
void test_l3_dsVideoDevice_Term()
{
    gTestID = 11;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);
    dsError_t status   = dsERR_NONE;

    UT_LOG_INFO("Calling dsVideoDevice_Term()");
    status = dsVideoDeviceTerm();
    UT_LOG_INFO("Result dsVideoDeviceTerm() OUT:dsError_t=[%s]",  UT_Control_GetMapString(dsErrorMappingTable, status));
    DS_ASSERT(status, dsERR_NONE);
    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief Set Zoom mode of Source device
*
* This test sets zoom mode of video device seected.
* **Test Group ID:** 03@n
* **Test Case ID:** 002@n
* **Pre-Conditions:** None@n
* VideoDevice_init Should be called before calling this test
*
* **Dependencies:** None@n
*
* **User Interaction:** @n
* User or Automation tool should select SetZoomMode from list
*
*/

void test_l3_dsVideoDevice_SetZoomMode()
{
    dsError_t status   = dsERR_NONE;
    gTestID = 2;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);
    int32_t choice,j;

    dsVideoDevice_getHandle();
    UT_LOG_MENU_INFO(" \t  Supported Zoom Modes are:");
    for (j = 0; j <= dsVIDEO_ZOOM_MAX; j++)
    {
        UT_LOG_MENU_INFO("\t%d.  %-20s ", j, \
                    UT_Control_GetMapString(dsVideoZoomMappingTable, j));
    }

    UT_LOG_MENU_INFO("------------------------------------------");
    UT_LOG_MENU_INFO(" Select the Zoom mode:");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);

    UT_LOG_INFO("Calling dsSetDFC(IN:Handle:[0x%0X],IN:dsVideoZoom_t:[%s])",gHandle, \
                    UT_Control_GetMapString(dsVideoZoomMappingTable, choice));
    status = dsSetDFC(gHandle, choice);
    UT_LOG_INFO("Result dsSetDFC(), OUT:dsError_t=[%s]", UT_Control_GetMapString(dsErrorMappingTable, status));
    DS_ASSERT(status, dsERR_NONE);
    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief Set Device Frame Rate of Sink device
*
* This test sets frame rate of video device selected.
* **Test Group ID:** 03@n
* **Test Case ID:** 003@n
* **Pre-Conditions:** None@n
* VideoDevice_init Should be called before calling this test
*
* **Dependencies:** None@n
*
* **User Interaction:** @n
* User or Automation tool should select SetDisplayFrameRate from list
*
*/
void test_l3_dsVideoDevice_SetDisplayFramerate()
{
    gTestID = 3;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);
    dsError_t status   = dsERR_NONE;
    int32_t choice,j;

    dsVideoDevice_getHandle();
    UT_LOG_MENU_INFO(" \t  Supported Display Framerate are:");
    for (j = 0; j <= dsVIDEO_FRAMERATE_MAX; j++)
    {
        UT_LOG_MENU_INFO("\t%d.  %-20s ", j, UT_Control_GetMapString(dsVideoFrameRateTable, j));
    }

    UT_LOG_MENU_INFO("------------------------------------------");
    UT_LOG_MENU_INFO(" Select the Display Framerate :");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);

    UT_LOG_INFO("Calling dsSetDisplayframerate(IN:Handle:[0x%0X],IN:framerate:[%s])",gHandle, \
                        UT_Control_GetMapString(dsVideoFrameRateTable, choice));

    // This need to check
    status = dsSetDisplayframerate(gHandle, UT_Control_GetMapString(dsVideoFrameRateTable, choice));
    UT_LOG_INFO("Result dsSetDisplayframerate(), OUT:dsError_t=[%s]", UT_Control_GetMapString(dsErrorMappingTable, status));
    DS_ASSERT(status, dsERR_NONE);
    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief Set Frame Rate Mode of Sink device
*
* This test sets Frame rate mode of video device selected.
* **Test Group ID:** 03@n
* **Test Case ID:** 004@n
* **Pre-Conditions:** None@n
* VideoDevice_init Should be called before calling this test
*
* **Dependencies:** None@n
*
* **User Interaction:** @n
* User or Automation tool should select SetFRFMode from list
*
*/
void test_l3_dsVideoDevice_SetFRFMode()
{
    gTestID = 4;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);
    dsError_t status   = dsERR_NONE;
    int32_t choice,j;

    dsVideoDevice_getHandle();
    UT_LOG_MENU_INFO(" \t  Supported Display FRF Mode are:");
    for (j = 0; j < 2; j++)
    {
        UT_LOG_MENU_INFO("\t%d.  %-20s ", j,((j==0)?"Disable":"Enable"));
    }

    UT_LOG_MENU_INFO("------------------------------------------");
    UT_LOG_MENU_INFO(" Select the Display FRF Mode :");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);

    UT_LOG_INFO("Calling dsSetFRFMode(IN:Handle:[0x%0X],IN:framerate:[%s])",gHandle, \
                                                                ((choice==0)?"Disable":"Enable"));
    status = dsSetFRFMode(gHandle, choice);
    UT_LOG_INFO("Result dsSetFRFMode(), OUT:dsError_t=[%s]", UT_Control_GetMapString(dsErrorMappingTable, status));
    DS_ASSERT(status, dsERR_NONE);
    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief Get Video Codec info from source device
*
* This test gets Video Codec Info of video device seected.
* **Test Group ID:** 03@n
* **Test Case ID:** 005@n
* **Pre-Conditions:** None@n
* VideoDevice_init Should be called before calling this test
*
* **Dependencies:** None@n
*
* **User Interaction:** @n
* User or Automation tool should select GetVideoCodecInfo from list
*
*/
void test_l3_dsVideoDevice_GetVideoCodecInfo()
{
    gTestID = 5;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);
    dsError_t status   = dsERR_NONE;
    dsVideoCodecInfo_t codecInfo;
    int32_t choice,i,j;

    dsVideoDevice_getHandle();
    UT_LOG_MENU_INFO(" \t  Supported Video Codec Info:");
    for (i = 0; i <= dsVIDEO_CODEC_MAX;i++)
    {        
            UT_LOG_MENU_INFO("\t%d.  %-20s ", i, UT_Control_GetMapString(dsVideoCodingFormatMappingTable, i));
    }
    UT_LOG_MENU_INFO("------------------------------------------");
    UT_LOG_MENU_INFO(" Select the Codec for Info :");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);
    UT_LOG_INFO("Calling dsGetVideoCodecInfo(IN:Handle:[0x%0X],IN:Codec[%s], OUT:CodecInfo)",gHandle,\
                                    UT_Control_GetMapString(dsVideoCodingFormatMappingTable, choice));
    status = dsGetVideoCodecInfo(gHandle, (dsVideoCodingFormat_t)choice, &codecInfo);
    UT_LOG_INFO("Result dsGetVideoCodecInfo(), OUT:dsError_t=[%s], OUT:number of Entires=[%d]", \
            UT_Control_GetMapString(dsErrorMappingTable, status),codecInfo.num_entries);
    for(j = 0; j< codecInfo.num_entries; j++)
    {
            UT_LOG_INFO("OUT:CodecProfile[%-20s]",UT_Control_GetMapString(dsVideoCodecHevcProfilesMappingTable, \
                                               (int32_t)codecInfo.entries[j].profile));
    }
    DS_ASSERT(status, dsERR_NONE);
    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief Get Supported Video Coding formats
*
* This test gets supported video coding formats of the device
* **Test Group ID:** 03@n
* **Test Case ID:** 006@n
* **Pre-Conditions:** None@n
* VideoDevice_init Should be called before calling this test
*
* **Dependencies:** None@n
*
* **User Interaction:** @n
* User or Automation tool should select GetSupportedVideoCodingFormat from list
*
*/
void test_l3_dsVideoDevice_GetSupportedVideoCodingFormat()
{
    gTestID = 6;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);
    dsError_t status   = dsERR_NONE;
    uint32_t supportedFormat = 0;

    dsVideoDevice_getHandle();
    UT_LOG_INFO("Calling dsGetSupportedVideoCodingFormats(IN:Handle[%d],OUT:supportedFormat)",gHandle);
    status = dsGetSupportedVideoCodingFormats(gHandle, &supportedFormat);
    UT_LOG_INFO("Result dsGetSupportedVideoCodingFormats(), OUT:dsError_t=[%s] OUT:supportedFormat=[0x08%x]", \
                                                UT_Control_GetMapString(dsErrorMappingTable, status), supportedFormat);
    DS_ASSERT(status, dsERR_NONE);
    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief Get Supported HDR capabilities
*
* This test gets supported HDR capabilities of the device
* **Test Group ID:** 03@n
* **Test Case ID:** 007@n
* **Pre-Conditions:** None@n
* VideoDevice_init Should be called before calling this test
*
* **Dependencies:** None@n
*
* **User Interaction:** @n
* User or Automation tool should select GetHDRCapabilities from list
*
*/
void test_l3_dsVideoDevice_GetHDRCapabilities()
{
    gTestID = 7;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);
    dsError_t status   = dsERR_NONE;
    int32_t HDRCapabilities = 0;

    dsVideoDevice_getHandle();
    UT_LOG_INFO("Calling dsGetHDRCapabilities(IN:Handle[%d],OUT:HDRCapabilities)",gHandle);
    status = dsGetHDRCapabilities(gHandle, &HDRCapabilities);
    UT_LOG_INFO("Result dsGetHDRCapabilities(), OUT:dsError_t=[%s] OUT:HDRCapabilites=[0x08%x]", \
                                                UT_Control_GetMapString(dsErrorMappingTable, status), HDRCapabilities);
    DS_ASSERT(status, dsERR_NONE);
    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
 * @brief Get Current Frame Rate Mode
 *
 * This test gets Current Frame Rate mode of the device
 * **Test Group ID:** 03@n
 * **Test Case ID:** 008@n
 * **Pre-Conditions:** None@n
 * VideoDevice_init Should be called before calling this test
 *
 * **Dependencies:** None@n
 *
 * **User Interaction:** @n
 * User or Automation tool should selected GetFRFMode from list
 *
 */
void test_l3_dsVideoDevice_dsGetFRFMode()
{
    gTestID = 8;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);
    dsError_t status   = dsERR_NONE;
    int32_t frfMode = 0;

    dsVideoDevice_getHandle();
    UT_LOG_INFO("Calling dsGetFRFMode(IN:Handle[%d],OUT:frfMode)",gHandle);
    status = dsGetFRFMode(gHandle, &frfMode);
    UT_LOG_INFO("Result dsGetFRFMode(), OUT:dsError_t=[%s] OUT:frfMode=[0x08%d]", \
                                                UT_Control_GetMapString(dsErrorMappingTable, status), frfMode);
    DS_ASSERT(status, dsERR_NONE);
    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
 * @brief Get Current Frame Rate 
 *
 * This test gets Current Frame Rate of the device
 * **Test Group ID:** 03@n
 * **Test Case ID:** 009@n
 * **Pre-Conditions:** None@n
 * VideoDevice_init Should be called before calling this test
 *
 * **Dependencies:** None@n
 *
 * **User Interaction:** @n
 * User or Automation tool should selected GetCurrentDisplayframerate from list
 *
 */
void test_l3_dsVideoDevice_dsGetCurrentDisplayframerate()
{
    gTestID = 9;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);
    dsError_t status   = dsERR_NONE;
    char currentFrameRate[dsVIDEO_FRAMERATE_MAX];

    dsVideoDevice_getHandle();
    UT_LOG_INFO("Calling dsGetCurrentDisplayframerate(IN:Handle[%d],OUT:currentFrameRate)",gHandle);
    status = dsGetCurrentDisplayframerate(gHandle, currentFrameRate);
    UT_LOG_INFO("Result dsGetCurrentDisplayframerate(), OUT:dsError_t=[%s] OUT:currentFrameRate=[%s]", \
                                                UT_Control_GetMapString(dsErrorMappingTable, status), currentFrameRate);
    DS_ASSERT(status, dsERR_NONE);
    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
 * @brief Get Current Zoom Mode 
 *
 * This test gets Current Zoom Mode of the device
 * **Test Group ID:** 03@n
 * **Test Case ID:** 010@n
 * **Pre-Conditions:** None@n
 * VideoDevice_init Should be called before calling this test
 *
 * **Dependencies:** None@n
 *
 * **User Interaction:** @n
 * User or Automation tool should selected GetZoomMode from list
 *
 */
void test_l3_dsVideoDevice_dsGetZoomMode()
{
    gTestID = 10;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);
    dsError_t status   = dsERR_NONE;
    dsVideoZoom_t dfc;

    dsVideoDevice_getHandle();
    UT_LOG_INFO("Calling dsGetDFC(IN:Handle[%d],OUT:dfc)",gHandle);
    status = dsGetDFC(gHandle, &dfc);
    UT_LOG_INFO("Result dsGetDFC(), OUT:dsError_t=[%s] OUT:CurrentZoomMode=[%s]", \
                                                UT_Control_GetMapString(dsErrorMappingTable, status), \
                                                UT_Control_GetMapString(dsVideoZoomMappingTable,(int32_t) dfc));
    DS_ASSERT(status, dsERR_NONE);
    UT_LOG_INFO("Out %s", __FUNCTION__);
}
static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main tests for this module
 *
 * @return int - 0 on success, otherwise failure
 */

int test_l3_dsVideoDevice_register(void)
{
    if(gSourceType == 0) 
    {
        // Create the test suite
        pSuite = UT_add_suite("[L3 dsVideoDevice - Sink]", NULL, NULL);
    }
    else
    {
        // Create the test suite
        pSuite = UT_add_suite("[L3 dsVideoDevice - Source]", NULL, NULL);
    }

    if (pSuite == NULL)
    {
        return -1;
    }

    UT_add_test( pSuite, "VideoDevice_Init", test_l3_dsVideoDevice_Init);
    UT_add_test( pSuite, "VideoDevice_Term", test_l3_dsVideoDevice_Term);
    UT_add_test( pSuite, "GetHDRCapabilities", test_l3_dsVideoDevice_GetHDRCapabilities);
    UT_add_test( pSuite, "GetSupportedVideoCodingFormat", test_l3_dsVideoDevice_GetSupportedVideoCodingFormat);

    if(gSourceType == 0) 
    {
        UT_add_test( pSuite, "SetDisplayFramerate", test_l3_dsVideoDevice_SetDisplayFramerate);
        UT_add_test( pSuite, "GetCurrentDisplayframerate", test_l3_dsVideoDevice_dsGetCurrentDisplayframerate);
        UT_add_test( pSuite, "SetFRFMode", test_l3_dsVideoDevice_SetFRFMode);
        UT_add_test( pSuite, "dsGetFRFMode", test_l3_dsVideoDevice_dsGetFRFMode);
    }

    if(gSourceType == 1)
    {
        UT_add_test( pSuite, "SetZoomMode", test_l3_dsVideoDevice_SetZoomMode);
        UT_add_test( pSuite, "GetZoomMode", test_l3_dsVideoDevice_dsGetZoomMode);
        UT_add_test( pSuite, "GetVideoCodecInfo", test_l3_dsVideoDevice_GetVideoCodecInfo);
    }

    return 0;
}

/** @} */ // End of DS_VideoDevice_HALTEST_L3
/** @} */ // End of DS_VideoDevice_HALTEST
/** @} */ // End of Device_Settings_HALTEST
/** @} */ // End of Device_Settings
/** @} */ // End of HPK
