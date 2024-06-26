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
 * @defgroup Device_Settings_PARSE_CONFIG Device Settings HAL Tests parse configuration File
 * @{
 * @parblock
 *
 * ### Parse configuration functions for Device Settings HAL :
 *
 * Parse configuration functions required for the module across all vendors.
 *
 * **Pre-Conditions:**  None @n
 * **Dependencies:** None @n
 *
 * @endparblock
 *
 */

/**
* @file test_parse_configuration.c
*
*/
#include <ut.h>
#include <ut_log.h>
#include <ut_kvp_profile.h>
#include <stdlib.h>

#include "test_parse_configuration.h"

/* Global Variables */
int32_t gSourceType = -1;
int32_t gDSModule = dsNone;

char gDeviceType[TEST_DEVICE_TYPE_SIZE]      = {0};


/* Parse configuration file */
int test_parse_configuration()
{
    ut_kvp_status_t status;
    char szReturnedString[UT_KVP_MAX_ELEMENT_SIZE];
#if 0
    status = ut_kvp_getStringField(ut_kvp_profile_getInstance(), "dsAudio/Type", szReturnedString, UT_KVP_MAX_ELEMENT_SIZE);
    if(status == UT_KVP_STATUS_SUCCESS) {
        gDSModule |= dsAudioPort;
        status = test_dsAudio_parse_configuration();
        if(status != UT_KVP_STATUS_SUCCESS) {
            UT_LOG_ERROR("Failed to parse audio configuration file");
            return -1;
        }
    }
#endif
    status = ut_kvp_getStringField(ut_kvp_profile_getInstance(), "dsVideoDevice/Type", szReturnedString, UT_KVP_MAX_ELEMENT_SIZE);
    if(status == UT_KVP_STATUS_SUCCESS) {
        gDSModule |= dsVideoDevice;
        status = test_dsVideoDevice_parse_configuration();
        if(status != UT_KVP_STATUS_SUCCESS) {
            UT_LOG_ERROR("Failed to parse video device configuration file");
            return -1;
        }
    }
#if 0
    status = ut_kvp_getStringField(ut_kvp_profile_getInstance(), "dsVideoPort/Type", szReturnedString, UT_KVP_MAX_ELEMENT_SIZE);
    if(status == UT_KVP_STATUS_SUCCESS) {
        gDSModule |= dsVideoPort;
        status = test_dsVideoPort_parse_configuration();
        if(status != UT_KVP_STATUS_SUCCESS) {
            UT_LOG_ERROR("Failed to parse video port configuration file");
            return -1;
        }
    }

    status = ut_kvp_getStringField(ut_kvp_profile_getInstance(), "dsCompositeIn/Type", szReturnedString, UT_KVP_MAX_ELEMENT_SIZE);
    if(status == UT_KVP_STATUS_SUCCESS) {
        gDSModule |= dsComposite;
    }

    status = ut_kvp_getStringField(ut_kvp_profile_getInstance(), "dsFPD/Type", szReturnedString, UT_KVP_MAX_ELEMENT_SIZE);
    if(status == UT_KVP_STATUS_SUCCESS) {
        gDSModule |= dsFPD;
    }

    status = ut_kvp_getStringField(ut_kvp_profile_getInstance(), "dsDisplay/Type", szReturnedString, UT_KVP_MAX_ELEMENT_SIZE);
    if(status == UT_KVP_STATUS_SUCCESS) {
        gDSModule |= dsDisplay;
    }

    status = ut_kvp_getStringField(ut_kvp_profile_getInstance(), "dsHost/Type", szReturnedString, UT_KVP_MAX_ELEMENT_SIZE);
    if(status == UT_KVP_STATUS_SUCCESS) {
        gDSModule |= dsHost;
    }

    status = ut_kvp_getStringField(ut_kvp_profile_getInstance(), "dsHdmiIn/Type", szReturnedString, UT_KVP_MAX_ELEMENT_SIZE);
    if(status == UT_KVP_STATUS_SUCCESS) {
        gDSModule |= dsHdmiIn;
    }
#endif
    return 0;
}

void test_parse_configuration_term()
{
    //test_dsAudio_parse_configuration_term();
    //test_dsVideoPort_parse_configuration_term();
    test_dsVideoDevice_parse_configuration_term();
}

/** @} */ // End of Device_Settings_PARSE_CONFIG
/** @} */ // End of Device_Settings_HALTEST
/** @} */ // End of Device_Settings
/** @} */ // End of HPK