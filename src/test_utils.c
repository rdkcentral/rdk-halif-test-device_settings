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
 * @defgroup Device_Settings_UTILS Device Settings HAL Tests Utility File
 * @{
 * @parblock
 *
 * ### Utility functions for Device Settings HAL :
 *
 * Utility functions required for the module across all vendors.
 *
 * **Pre-Conditions:**  None @n
 * **Dependencies:** None @n
 *
 * @endparblock
 *
 */

/**
* @file test_utils.c
*
*/
#include <ut.h>
#include <ut_log.h>
#include <ut_kvp_profile.h>
#include <stdlib.h>

#include "test_utils.h"

/* Global Variables */
int32_t gSourceType = -1;

int32_t gDSModule = 0x0;

char gDeviceType[TEST_UTIL_DEVICE_TYPE_SIZE]      = {0};
char gDeviceName[TEST_UTIL_DEVICE_NAME_SIZE]      = {0};

dsVideoDeviceConfiguration_t* gDSVideoDeviceConfiguration = NULL;
int32_t gDSvideoDevice_NumVideoDevices;


/* Parse Video Device Configuration file */
static int test_utils_parse_dsVideoDevice()
{
    char key_string[TEST_UTIL_KVP_SIZE];
    ut_kvp_status_t status;

    gDSvideoDevice_NumVideoDevices = ut_kvp_getUInt16Field( ut_kvp_profile_getInstance(), "dsVideoDevice/NumVideoDevices" );

    UT_LOG("gDSvideoDevice_NumVideoDevices: %d",gDSvideoDevice_NumVideoDevices);
    gDSVideoDeviceConfiguration = (dsVideoDeviceConfiguration_t*) calloc(gDSvideoDevice_NumVideoDevices, sizeof(dsVideoDeviceConfiguration_t));
    if(gDSVideoDeviceConfiguration == NULL) {
         UT_LOG_ERROR("Failed to allocate memory for Video Port configuration structure");
         return -1;
    }


    for(int i = 0; i < gDSvideoDevice_NumVideoDevices; i++) {
        if(gSourceType == 1){
            snprintf(key_string, TEST_UTIL_KVP_SIZE, "dsVideoDevice/Device/%d/SupportedDFCs" , i+1);
            gDSVideoDeviceConfiguration[i].NoOfSupportedDFCs = ut_kvp_getListCount(ut_kvp_profile_getInstance(), key_string);
            UT_LOG("NoOfSupportedDFCs: %d",gDSVideoDeviceConfiguration[i].NoOfSupportedDFCs);

            // loop to get supported SupportedDFCs in array
            for(int j = 0; j < gDSVideoDeviceConfiguration[i].NoOfSupportedDFCs; j++) {
                snprintf(key_string, TEST_UTIL_KVP_SIZE, "dsVideoDevice/Device/%d/SupportedDFCs/%d" , i+1 , j);
                gDSVideoDeviceConfiguration[i].SupportedDFCs[j] = ut_kvp_getUInt32Field(ut_kvp_profile_getInstance(), key_string);
                UT_LOG("SupportedDFCs: %d",gDSVideoDeviceConfiguration[i].SupportedDFCs[j]);
            }
        }

        snprintf(key_string, TEST_UTIL_KVP_SIZE, "dsVideoDevice/Device/%d/DefaultDFC" , i+1);
        gDSVideoDeviceConfiguration[i].DefaultDFC = ut_kvp_getUInt32Field(ut_kvp_profile_getInstance(), key_string );
	    UT_LOG("gDSVideoDeviceConfiguration[i].DefaultDFC :%d",gDSVideoDeviceConfiguration[i].DefaultDFC);

        snprintf(key_string, TEST_UTIL_KVP_SIZE, "dsVideoDevice/Device/%d/HDRCapabilities" , i+1);
        gDSVideoDeviceConfiguration[i].HDRCapabilities = ut_kvp_getUInt32Field(ut_kvp_profile_getInstance(), key_string );
	    UT_LOG("gDSVideoDeviceConfiguration[i].HDRCapabilities :%d",gDSVideoDeviceConfiguration[i].HDRCapabilities);

        snprintf(key_string, TEST_UTIL_KVP_SIZE, "dsVideoDevice/Device/%d/SupportedVideoCodingFormats" , i+1);
        gDSVideoDeviceConfiguration[i].SupportedVideoCodingFormats = ut_kvp_getUInt32Field(ut_kvp_profile_getInstance(), key_string );
	    UT_LOG("SupportedVideoCodingFormats: %d ",gDSVideoDeviceConfiguration[i].SupportedVideoCodingFormats);

        if(gSourceType == 0){
            snprintf(key_string, TEST_UTIL_KVP_SIZE, "dsVideoDevice/Device/%d/SupportedDisplayFramerate" , i+1);
            gDSVideoDeviceConfiguration[i].NoOfSupportedDFR = ut_kvp_getListCount(ut_kvp_profile_getInstance(), key_string);
            UT_LOG("NoOfSupportedDFR: %d ",gDSVideoDeviceConfiguration[i].NoOfSupportedDFR);
            // loop to get supported SupportedDFR in array
            for(int j = 0; j < gDSVideoDeviceConfiguration[i].NoOfSupportedDFR; j++) {
                snprintf(key_string, TEST_UTIL_KVP_SIZE, "dsVideoDevice/Device/%d/SupportedDisplayFramerate/%d" , i+1 , j);
                status = ut_kvp_getStringField(ut_kvp_profile_getInstance(), key_string, gDSVideoDeviceConfiguration[i].SupportedDisplayFramerate, sizeof(gDSVideoDeviceConfiguration[i].SupportedDisplayFramerate));
                UT_LOG("SupportedDisplayFramerate: %s ",gDSVideoDeviceConfiguration[i].SupportedDisplayFramerate);
            }
        }

        UT_LOG("gSourceType %d ",gSourceType);
        /* check for only source */
        if(gSourceType == 1){
            snprintf(key_string, TEST_UTIL_KVP_SIZE, "dsVideoDevice/Device/%d/VideoCodecInfo/num_entries" , i+1);
            gDSVideoDeviceConfiguration[i].num_codec_entries = ut_kvp_getUInt32Field(ut_kvp_profile_getInstance(), key_string );
            UT_LOG("num_codec_entries %d",gDSVideoDeviceConfiguration[i].num_codec_entries);

            //snprintf(key_string, TEST_UTIL_KVP_SIZE, "dsVideoDevice/Device/%d/VideoCodecInfo/VideoCodec0/level" , i+1);
            //status = ut_kvp_getStringField(ut_kvp_profile_getInstance(), key_string, gDSVideoDeviceConfiguration[i].level, sizeof(key_string));
            //snprintf(key_string, TEST_UTIL_KVP_SIZE, "dsVideoDevice/Device/%d/VideoCodecInfo/VideoCodec0/level" , i+1);
            //gDSVideoDeviceConfiguration[i].level = ut_kvp_getUInt32Field(ut_kvp_profile_getInstance(), key_string );
            //UT_LOG("gDSVideoDeviceConfiguration[i].level:%d",gDSVideoDeviceConfiguration[i].level);
            snprintf(key_string, TEST_UTIL_KVP_SIZE, "dsVideoDevice/Device/%d/VideoCodecInfo/VideoCodec0/profile" , i+1);
            gDSVideoDeviceConfiguration[i].profile = ut_kvp_getUInt32Field(ut_kvp_profile_getInstance(), key_string );
            UT_LOG("gDSVideoDeviceConfiguration[i].profile :%d",gDSVideoDeviceConfiguration[i].profile);
        }
    }

    if(status);//warning fix
    return 0;
}

/* Parse configuration file */
int test_utils_parseConfig()
{
    ut_kvp_status_t status;
    
    status = ut_kvp_getStringField(ut_kvp_profile_getInstance(), "dsVideoDevice/Type", gDeviceType, TEST_UTIL_DEVICE_TYPE_SIZE);
    UT_LOG_DEBUG("gDeviceType: %s ",gDeviceType);
    if (status == UT_KVP_STATUS_SUCCESS ) {
        if (!strncmp(gDeviceType, TEST_UTIL_TYPE_SOURCE_VALUE, TEST_UTIL_DEVICE_TYPE_SIZE)) {
            gSourceType = 1;
        }
        else if(!strncmp(gDeviceType, TEST_UTIL_TYPE_SINK_VALUE, TEST_UTIL_DEVICE_TYPE_SIZE)) {
            gSourceType = 0;
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

    gDSModule = ut_kvp_getUInt32Field(ut_kvp_profile_getInstance(), "dsVideoDevice/Module");
    UT_LOG_DEBUG("gDSModule: %d dsVideoDevice:%d ",gDSModule,dsVideoDevice);
    if(gDSModule & dsVideoDevice) {
        status = test_utils_parse_dsVideoDevice();
        if (status != UT_KVP_STATUS_SUCCESS ) {
            UT_LOG_ERROR("Failed to parse dsAudio configurations");
            return -1;
        }
    }

    return 0;
}

void test_utils_parseConfig_term()
{
    if(gDSVideoDeviceConfiguration) {
        free(gDSVideoDeviceConfiguration);
    }
}

/** @} */ // End of Device_Settings_UTILS
/** @} */ // End of Device_Settings_HALTEST
/** @} */ // End of Device_Settings
/** @} */ // End of HPK
