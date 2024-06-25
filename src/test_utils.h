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
* @file test_utils.h
*
*/
#ifndef __TEST_UTILS_H__
#define __TEST_UTILS_H__

#include "dsVideoPort.h"

#define TEST_UTIL_KVP_SIZE             256
#define TEST_UTIL_DEVICE_TYPE_SIZE     8
#define TEST_UTIL_DEVICE_NAME_SIZE     64
#define TEST_UTIL_DS_MODULE_NAME_SIZE  32

#define TEST_UTIL_TYPE_SOURCE_VALUE     "source"
#define TEST_UTIL_TYPE_SINK_VALUE       "sink"

#define DS_VIDEO_PORT_NAME_SIZE        32
#define dsVideoPortRESOLUTION_NUMMAX 32

/* Video Port configuration */
typedef struct _dsVideoPortConfiguration_t {
    uint16_t typeid;
    uint16_t index;
    char     port_name[DS_VIDEO_PORT_NAME_SIZE];
    bool     dtcp_supported;
    bool     hdcp_supported;
    int32_t  numSupportedResolutions;
    dsVideoPortResolution_t supportedResolutons[dsVideoPortRESOLUTION_NUMMAX];
    char     defaultResolution[TEST_UTIL_DEVICE_NAME_SIZE];
    int32_t  colorspaces;
    int32_t  Supported_color_depth_capabilities;
    bool     DisplaySurround;
    int32_t  SurroundMode;
    int32_t  Supported_tv_resolutions_capabilities;
    int32_t  hdr_capabilities;
    int32_t  hdcp_protocol_version;
    int32_t  quantization_ranges;
    int32_t  matrix_coefficients;
}dsVideoPortConfiguration_t;

typedef enum _dsModule_t {
    dsAudioPort   = (0x1 << 0),
    dsVideoPort   = (0x1 << 1),
    dsComposite   = (0x1 << 2),
    dsHdmiIn      = (0x1 << 3),
    dsVideoDevice = (0x1 << 4),
    dsDisplay     = (0x1 << 5),
    dsFPD         = (0x1 << 6),
    dsHost        = (0x1 << 7),
}dsModule_t;

/* Global variables */
extern char    gDeviceType[TEST_UTIL_DEVICE_TYPE_SIZE];
extern char    gDeviceName[TEST_UTIL_DEVICE_NAME_SIZE];
extern int32_t gSourceType;
extern int32_t gDSModule;

extern dsVideoPortConfiguration_t* gDSVideoPortConfiguration;
extern int32_t gDSvideoPort_NumberOfPorts;
extern int32_t gDSvideoPort_color_depth;
extern int32_t gDSvideoPort_connectedAOP;
//extern char    gDSvideoPort_defaultResolution[TEST_UTIL_DEVICE_NAME_SIZE];

/*Function prototypes */
int test_utils_parseConfig();
void test_utils_parseConfig_term();

#endif //__TEST_UTILS_H__
/** @} */ // End of Device_Settings_UTILS
/** @} */ // End of Device_Settings_HALTEST
/** @} */ // End of Device_Settings
/** @} */ // End of HPK