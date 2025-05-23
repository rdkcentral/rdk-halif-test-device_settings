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
 * @defgroup DS_VideoDevice_HALTEST Device Settings Video Device HAL Tests
 * @{
 */

/**
 * @defgroup DS_VideoDevice_HALTEST_PARSE_CONFIG_HEADER Device Settings Video Device Parse Config Header File
 * @{
 * @parblock
 *
 * ### Configuration Header file for DS Video Device test suit :
 *
 *  DS Video Device Parse Configuration Header file
 *
 * @endparblock
 */

/**
* @file test_dsVideoDevice_parse_configuration.h
*
*/
#ifndef __TEST_DS_VIDEO_DEVICE_PARSE_CONFIG_H__
#define __TEST_DS_VIDEO_DEVICE_PARSE_CONFIG_H__

#include <dsVideoDevice.h>

#define DS_VIDEO_DEVICE_KVP_SIZE              128
#define DS_VIDEO_DEVICE_PORT_NAME_SIZE        32
#define DS_VIDEO_DEVICE_MAX_FRAMERATE_LIST 10
#define DS_VIDEO_DEVICE_MAX_FRAMERATE_LEN  32
#define DS_VIDEO_DEVICE_NAME_SIZE             64

#define DS_VIDEO_DEVICE_MODULE_NAME    "dsVideoDevice"

/* Video Device configuration */
typedef struct 
{
    int32_t  NoOfSupportedDFCs;
    dsVideoZoom_t  SupportedDFCs[dsVIDEO_ZOOM_MAX];
    dsVideoZoom_t  DefaultDFC;
    int32_t  HDRCapabilities;
    uint32_t SupportedVideoCodingFormats;
    int32_t  NoOfSupportedDFR;
    char     SupportedDisplayFramerate[DS_VIDEO_DEVICE_MAX_FRAMERATE_LIST][DS_VIDEO_DEVICE_MAX_FRAMERATE_LEN];
    int32_t  num_codec_entries;
    float    level;
    dsVideoCodecHevcProfiles_t  profile;
}dsVideoDeviceConfiguration_t;

/* Global variables */
extern dsVideoDeviceConfiguration_t* gDSVideoDeviceConfiguration;
extern char gDSVideoDeviceName[];
extern int32_t gDSvideoDevice_NumVideoDevices;

/*Function prototypes */
int test_dsVideoDevice_parse_configuration();
void test_dsVideoDevice_parse_configuration_term();

#endif //__TEST_DS_VIDEO_DEVICE_PARSE_CONFIG_H__

/** @} */ // End of DS_VideoDevice_HALTEST_PARSE_CONFIG_HEADER
/** @} */ // End of DS_VideoDevice_HALTEST
/** @} */ // End of Device_Settings_HALTEST
/** @} */ // End of Device_Settings
/** @} */ // End of HPK
