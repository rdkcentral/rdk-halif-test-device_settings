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


dsVideoPortConfiguration_t* gDSVideoPortConfiguration = NULL;
int32_t gDSvideoPort_NumberOfPorts = 0;
int32_t gDSvideoPort_color_depth = 0;
int32_t gDSvideoPort_connectedAOP = 0;
//char    gDSvideoPort_defaultResolution[TEST_UTIL_DEVICE_NAME_SIZE] = {0};

/* Parse Video Configuration file */
static int test_utils_parse_dsVideoPort()
{
    char key_string[TEST_UTIL_KVP_SIZE];
    ut_kvp_status_t status;

    gDSvideoPort_NumberOfPorts    = ut_kvp_getUInt32Field( ut_kvp_profile_getInstance(), "dsVideoPort/Number_of_ports" );
    gDSvideoPort_color_depth      = ut_kvp_getUInt16Field( ut_kvp_profile_getInstance(), "dsVideoPort/color_depth" );
    gDSvideoPort_connectedAOP     = ut_kvp_getUInt16Field( ut_kvp_profile_getInstance(), "dsVideoPort/connectedAOP" );

    gDSVideoPortConfiguration = (dsVideoPortConfiguration_t*) calloc(gDSvideoPort_NumberOfPorts, sizeof(dsVideoPortConfiguration_t));
    if(gDSVideoPortConfiguration == NULL) {
        UT_LOG_ERROR("Failed to allocate memory for Video Port configuration structure");
        return -1;
    }

    for(int i = 0; i < gDSvideoPort_NumberOfPorts; i++) {

        snprintf(key_string, TEST_UTIL_KVP_SIZE, "dsVideoPort/Ports/%d/Typeid" , i+1);
        gDSVideoPortConfiguration[i].typeid = ut_kvp_getUInt32Field(ut_kvp_profile_getInstance(), key_string);

        snprintf(key_string, TEST_UTIL_KVP_SIZE, "dsVideoPort/Ports/%d/Index" , i+1);
        gDSVideoPortConfiguration[i].index = ut_kvp_getUInt32Field(ut_kvp_profile_getInstance(), key_string );

        snprintf(key_string, TEST_UTIL_KVP_SIZE, "dsVideoPort/Ports/%d/Name" , i+1);
        status = ut_kvp_getStringField(ut_kvp_profile_getInstance(), key_string, gDSVideoPortConfiguration[i].port_name, DS_VIDEO_PORT_NAME_SIZE);

        snprintf(key_string, TEST_UTIL_KVP_SIZE, "dsVideoPort/Ports/%d/dtcp_supported" , i+1);
        gDSVideoPortConfiguration[i].dtcp_supported = ut_kvp_getBoolField( ut_kvp_profile_getInstance(), key_string );

        snprintf(key_string, TEST_UTIL_KVP_SIZE, "dsVideoPort/Ports/%d/hdcp_supported" , i+1);
        gDSVideoPortConfiguration[i].hdcp_supported = ut_kvp_getBoolField( ut_kvp_profile_getInstance(), key_string );

        snprintf(key_string, TEST_UTIL_KVP_SIZE, "dsVideoPort/Ports/%d/numSupportedResolutions" , i+1 );
        gDSVideoPortConfiguration[i].numSupportedResolutions = ut_kvp_getUInt32Field(ut_kvp_profile_getInstance(), key_string);

        snprintf(key_string, TEST_UTIL_KVP_SIZE, "dsVideoPort/Ports/%d/defaultResolution" , i+1);
        status = ut_kvp_getStringField(ut_kvp_profile_getInstance(), key_string, gDSVideoPortConfiguration[i].defaultResolution, TEST_UTIL_DEVICE_NAME_SIZE);

        snprintf(key_string, TEST_UTIL_KVP_SIZE, "dsVideoPort/Ports/%d/colorspaces" , i+1 );
        gDSVideoPortConfiguration[i].colorspaces = ut_kvp_getUInt32Field(ut_kvp_profile_getInstance(), key_string);

        snprintf(key_string, TEST_UTIL_KVP_SIZE, "dsVideoPort/Ports/%d/Supported_color_depth_capabilities" , i+1 );
        gDSVideoPortConfiguration[i].Supported_color_depth_capabilities = ut_kvp_getUInt32Field(ut_kvp_profile_getInstance(), key_string);

        snprintf(key_string, TEST_UTIL_KVP_SIZE, "dsVideoPort/Ports/%d/DisplaySurround" , i+1);
        gDSVideoPortConfiguration[i].DisplaySurround = ut_kvp_getBoolField( ut_kvp_profile_getInstance(), key_string );

        snprintf(key_string, TEST_UTIL_KVP_SIZE, "dsVideoPort/Ports/%d/SurroundMode" , i+1 );
        gDSVideoPortConfiguration[i].SurroundMode = ut_kvp_getUInt32Field(ut_kvp_profile_getInstance(), key_string);

        snprintf(key_string, TEST_UTIL_KVP_SIZE, "dsVideoPort/Ports/%d/Supported_tv_resolutions_capabilities" , i+1 );
        gDSVideoPortConfiguration[i].Supported_tv_resolutions_capabilities = ut_kvp_getUInt32Field(ut_kvp_profile_getInstance(), key_string);

        snprintf(key_string, TEST_UTIL_KVP_SIZE, "dsVideoPort/Ports/%d/hdr_capabilities" , i+1 );
        gDSVideoPortConfiguration[i].hdr_capabilities = ut_kvp_getUInt32Field(ut_kvp_profile_getInstance(), key_string);

        snprintf(key_string, TEST_UTIL_KVP_SIZE, "dsVideoPort/Ports/%d/hdcp_protocol_version" , i+1 );
        gDSVideoPortConfiguration[i].hdcp_protocol_version = ut_kvp_getUInt32Field(ut_kvp_profile_getInstance(), key_string);

        snprintf(key_string, TEST_UTIL_KVP_SIZE, "dsVideoPort/Ports/%d/quantization_ranges" , i+1 );
        gDSVideoPortConfiguration[i].quantization_ranges = ut_kvp_getUInt32Field(ut_kvp_profile_getInstance(), key_string);

        snprintf(key_string, TEST_UTIL_KVP_SIZE, "dsVideoPort/Ports/%d/matrix_coefficients" , i+1 );
        gDSVideoPortConfiguration[i].matrix_coefficients = ut_kvp_getUInt32Field(ut_kvp_profile_getInstance(), key_string);

    }
    if(status);//warning fix
    return 0;
}

/* Parse configuration file */
int test_utils_parseConfig()
{
    ut_kvp_status_t status;

    status = ut_kvp_getStringField(ut_kvp_profile_getInstance(), "dsVideoPort/Type", gDeviceType, TEST_UTIL_DEVICE_TYPE_SIZE);
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

    status = ut_kvp_getStringField(ut_kvp_profile_getInstance(), "dsVideoPort/Name", gDeviceName, TEST_UTIL_DEVICE_NAME_SIZE);

    UT_LOG_DEBUG("Device Type: %s, Device Name: %s", gDeviceType, gDeviceName);

    gDSModule = ut_kvp_getUInt32Field(ut_kvp_profile_getInstance(), "dsVideoPort/Module");
    UT_LOG_DEBUG("gDSModule: %d dsVideoPort:%d ",gDSModule,dsVideoPort);
    if(gDSModule & dsVideoPort) {
        status = test_utils_parse_dsVideoPort();
        if (status != UT_KVP_STATUS_SUCCESS ) {
            UT_LOG_ERROR("Failed to parse dsAudio configurations");
            return -1;
        }
    }

    return 0;
}

void test_utils_parseConfig_term()
{
    if(gDSVideoPortConfiguration) {
        free(gDSVideoPortConfiguration);
    }
}

/** @} */ // End of Device_Settings_UTILS
/** @} */ // End of Device_Settings_HALTEST
/** @} */ // End of Device_Settings
/** @} */ // End of HPK