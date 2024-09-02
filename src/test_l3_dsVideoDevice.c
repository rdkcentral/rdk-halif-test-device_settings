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
#include <ut_kvp.h>

#include "test_parse_configuration.h"
#include "dsVideoDevice.h"


intptr_t gHandle = 0;

// Define the Mapping struct
typedef struct {
    char* String;
    int32_t value;
} mapping_key_t;

// Mapping table for dsError_t
const static mapping_key_t  dsErrorMappingTable[] = {
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
const static mapping_key_t dsVideoZoomMappingTable[] = {
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
const static mapping_key_t dsVideoCodingFormatMappingTable[] = {
    {"dsVIDEO_CODEC_MPEGHPART2", (int32_t)dsVIDEO_CODEC_MPEGHPART2},
    {"dsVIDEO_CODEC_MPEG4PART10", (int32_t)dsVIDEO_CODEC_MPEG4PART10},
    {"dsVIDEO_CODEC_MPEG2", (int32_t)dsVIDEO_CODEC_MPEG2},
    {"dsVIDEO_CODEC_MAX", (int32_t)dsVIDEO_CODEC_MAX},
    {NULL, -1}
};

// Mapping table for dsVideoCodecHevcProfiles_t
const static mapping_key_t dsVideoCodecHevcProfilesMappingTable[] = {
    {"dsVIDEO_CODEC_HEVC_PROFILE_MAIN", (int32_t)dsVIDEO_CODEC_HEVC_PROFILE_MAIN},
    {"dsVIDEO_CODEC_HEVC_PROFILE_MAIN10", (int32_t)dsVIDEO_CODEC_HEVC_PROFILE_MAIN10},
    {"dsVIDEO_CODEC_HEVC_PROFILE_MAINSTILLPICTURE", (int32_t)dsVIDEO_CODEC_HEVC_PROFILE_MAINSTILLPICTURE},
    {"dsVIDEO_CODEC_HEVC_MAX", (int32_t)dsVIDEO_CODEC_HEVC_MAX},
    {NULL, -1}
};


// Mapping table for boolean values
const static mapping_key_t  boolMappingTable[] = {
    {"true", (int32_t)true},
    {"false", (int32_t)false},
    {NULL, -1}
};

static char* mapToString(const mapping_key_t* mappingTable, int32_t value) {
    if (mappingTable == NULL)
    {
        return NULL;
    }
    for (int32_t i = 0; mappingTable[i].String!=NULL; i++) {
        if (mappingTable[i].value == value) {
            return mappingTable[i].String;
        }
    }
    return "Unknown value";
}


/*callback*/
void dsVideoDevice_FrameratePreChange(unsigned int tSecond)
{
	UT_LOG_INFO("FrameratePreChange callback tSecond:[%d]",tSecond);
}

void dsVideoDevice_FrameratePostChange(unsigned int tSecond)
{
	UT_LOG_INFO("FrameratePostChange callback tSecond:[%d]",tSecond);
}

static void dsVideoDevice_getHandle()
{
    dsError_t status   = dsERR_NONE;
    int32_t choice,device;

    for (device = 0; device < gDSvideoDevice_NumVideoDevices; device++) {
        UT_LOG_INFO("Calling dsGetVideoDevice(index:[%d])",device);
        status = dsGetVideoDevice(device,&gHandle);
        UT_LOG_INFO("Result dsGetVideodevice(Handle:[0x%0X]]) dsError_t=[%s]", gHandle, mapToString(dsErrorMappingTable, status));
        UT_ASSERT_EQUAL(status, dsERR_NONE);
        if (status != dsERR_NONE) {
            UT_LOG_ERROR("dsGetVideodevice failed with error: %d", status);
        }
    }

}

void dsVideoDevice_Init()
{
    dsError_t status   = dsERR_NONE;

    UT_LOG_INFO("Calling dsVideoDeviceInit()");
    status = dsVideoDeviceInit();
    UT_LOG_INFO("Result dsVideoDeviceInit() dsError_t=[%s]", mapToString(dsErrorMappingTable, status));
    UT_ASSERT_EQUAL_FATAL(status, dsERR_NONE);
    dsVideoDevice_getHandle();
	dsRegisterFrameratePreChangeCB(dsVideoDevice_FrameratePreChange);
	dsRegisterFrameratePostChangeCB(dsVideoDevice_FrameratePostChange);

}

void dsVideoDevice_Term()
{
    dsError_t status   = dsERR_NONE;

    UT_LOG_INFO("Calling dsVideoDevice_Term()");
    status = dsVideoDeviceTerm();
    UT_LOG_INFO("Result dsVideoDeviceTerm() dsError_t=[%s]",  mapToString(dsErrorMappingTable, status));
    UT_ASSERT_EQUAL_FATAL(status, dsERR_NONE);
}

void dsVideoDevice_SetZoomMode()
{
    dsError_t status   = dsERR_NONE;
	int32_t choice,i,j;

	UT_LOG_INFO(" \t  Supported Zoom Modes are:");
	for (i = 0; i < gDSvideoDevice_NumVideoDevices; ++i) {
	    for (j = 0; j <gDSVideoDeviceConfiguration[i].NoOfSupportedDFCs; ++j) {
			UT_LOG_INFO("\t%d.  %-20s ", gDSVideoDeviceConfiguration[i].SupportedDFCs[j], mapToString(dsVideoZoomMappingTable, gDSVideoDeviceConfiguration[i].SupportedDFCs[j]));
        }
	}

	UT_LOG_INFO("------------------------------------------");
    UT_LOG_INFO(" Select the Zoom mode:");
    scanf("%d", &choice);

	UT_LOG_INFO("Calling dsSetDFC(Handle:[0x%0X]],dsVideoZoom_t:[%s])",gHandle, \
	                mapToString(dsVideoZoomMappingTable, choice));
	status = dsSetDFC(gHandle, choice);
	UT_LOG_INFO("Result dsSetDFC(), dsError_t=[%s]", mapToString(dsErrorMappingTable, status));
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}

void dsVideoDevice_SetDisplayFramerate()
{
    dsError_t status   = dsERR_NONE;
	int32_t choice,i,j;

    UT_LOG_INFO(" \t  Supported Display Framerate are:");
	for (i = 0; i < gDSvideoDevice_NumVideoDevices; ++i) {
	    for (j = 0; j <gDSVideoDeviceConfiguration[i].NoOfSupportedDFR; j++) {
			UT_LOG_INFO("\t%d.  %-20s ", j, gDSVideoDeviceConfiguration[i].SupportedDisplayFramerate[j]);
        }
	}

	UT_LOG_INFO("------------------------------------------");
    UT_LOG_INFO(" Select the Display Framerate :");
    scanf("%d", &choice);

	UT_LOG_INFO("Calling dsSetDisplayframerate(Handle:[0x%0X]],framerate:[%s])",gHandle, gDSVideoDeviceConfiguration[i-1].SupportedDisplayFramerate[choice]);
	status = dsSetDisplayframerate(gHandle, gDSVideoDeviceConfiguration[i].SupportedDisplayFramerate[choice]);
	UT_LOG_INFO("Result dsSetDisplayframerate(), dsError_t=[%s]", mapToString(dsErrorMappingTable, status));
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}

void dsVideoDevice_GetVideoCodecInfo()
{
    dsError_t status   = dsERR_NONE;
    dsVideoCodingFormat_t codec = dsVIDEO_CODEC_MPEGHPART2;
    dsVideoCodecInfo_t codecInfo;

    UT_LOG_INFO(" \t  Supported Display Framerate are:");
    for (i = 0; i < gDSvideoDevice_NumVideoDevices; ++i) {
	    for(codec = dsVIDEO_CODEC_MPEGHPART2 ; codec < dsVIDEO_CODEC_MAX; )
        {
            if(!(gDSVideoDeviceConfiguration[i].SupportedVideoCodingFormats & codec))
            {
                UT_LOG_INFO("\t%d.  %-20s ", codec, mapToString(dsVideoCodingFormatMappingTable, gDSVideoDeviceConfiguration[i].SupportedVideoCodingFormats));
                continue;
            }
	}

	UT_LOG_INFO("Calling dsGetVideoCodecInfo(Handle:[0x%0X]])",gHandle);
	status = dsGetVideoCodecInfo(handle, codec, &codecInfo);
	UT_LOG_INFO("Result dsGetVideoCodecInfo(), dsError_t=[%s]", mapToString(dsErrorMappingTable, status));
    UT_ASSERT_EQUAL(status, dsERR_NONE);
}


static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main tests for this module
 *
 * @return int - 0 on success, otherwise failure
 */

int test_l3_dsVideoDevice_register(void)
{
    if(gSourceType == 0) {
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

    UT_add_test( pSuite, "dsVideoDevice_Init", dsVideoDevice_Init);
    UT_add_test( pSuite, "dsVideoDevice_Term", dsVideoDevice_Term);

    if(gSourceType == 0) {
        UT_add_test( pSuite, "SetDisplayFramerate", dsVideoDevice_SetDisplayFramerate);
    }

    if(gSourceType == 1) {
        UT_add_test( pSuite, "SetZoomMode", dsVideoDevice_SetZoomMode);
    }

    return 0;
}

/** @} */ // End of DS_VideoDevice_HALTEST_L3
/** @} */ // End of DS_VideoDevice_HALTEST
/** @} */ // End of Device_Settings_HALTEST
/** @} */ // End of Device_Settings
/** @} */ // End of HPK