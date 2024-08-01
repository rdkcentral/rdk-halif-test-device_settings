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
 * @addtogroup DS_Audio_HALTEST Device Settings Audio HAL Tests
 * @{
 */

/**
 * @defgroup DS_Audio_HALTEST_L3 Device Settings Audio HAL Tests L3 File
 * @{
 * @parblock
 *
 * ### L3 Tests for DS Audio HAL :
 *
 * Level 3 unit test cases for all APIs of Device Settings Audio HAL
 *
 * **Pre-Conditions:**  None@n
 * **Dependencies:** None@n
 *
 * Refer to API Definition specification documentation : [ds-audio_halSpec.md](../../docs/pages/ds-audio_halSpec.md)
 *
 * @endparblock
 */


/**
 * @file test_l3_dsAudio.c
 *
 */
#include <ut.h>
#include <ut_log.h>
#include <ut_kvp_profile.h>
#include <stdlib.h>
#include "dsAudio.h"
#include "test_parse_configuration.h"

#define DS_AUDIO_MAX_PORTS         20
#define DS_AUDIO_MAX_DAP           20
#define DS_AUDIO_MAX_MS12_PROFILES 10
#define DS_AUDIO_MAX_MS12_LENGTH   32

/* Type Definitions */

typedef struct _ut_control_keyMapTable_t
{
    char* string;
    int32_t key;
} ut_control_keyMapTable_t;

/* Global Variables */
static int32_t gTestGroup = 3;
static int32_t gTestID    = 1;

static bool                gConnectionStatus = false;
static dsAudioFormat_t     gAudioFormat      = dsAUDIO_FORMAT_NONE;
static dsATMOSCapability_t gAtosCapablity    = dsAUDIO_ATMOS_NOTSUPPORTED;
static bool                gAtmosStatus      = false;

/* Enum mapping tables */

/* dsAudioPortType_t */
const static ut_control_keyMapTable_t dsAudioPortType_mapTable [] = {
  { "dsAUDIOPORT_TYPE_ID_LR",     (int32_t)dsAUDIOPORT_TYPE_ID_LR     },
  { "dsAUDIOPORT_TYPE_HDMI",      (int32_t)dsAUDIOPORT_TYPE_HDMI      },
  { "dsAUDIOPORT_TYPE_SPDIF",     (int32_t)dsAUDIOPORT_TYPE_SPDIF     },
  { "dsAUDIOPORT_TYPE_SPEAKER",   (int32_t)dsAUDIOPORT_TYPE_SPEAKER   },
  { "dsAUDIOPORT_TYPE_HDMI_ARC",  (int32_t)dsAUDIOPORT_TYPE_HDMI_ARC  },
  { "dsAUDIOPORT_TYPE_HEADPHONE", (int32_t)dsAUDIOPORT_TYPE_HEADPHONE },
  { "dsAUDIOPORT_TYPE_MAX",       (int32_t)dsAUDIOPORT_TYPE_MAX       },
  {  NULL, -1 }
};

/* dsAudioFormat_t */
const static ut_control_keyMapTable_t dsAudioFormat_mapTable [] = {
  { "dsAUDIO_FORMAT_NONE",               (int32_t)dsAUDIO_FORMAT_NONE               },
  { "dsAUDIO_FORMAT_PCM",                (int32_t)dsAUDIO_FORMAT_PCM                },
  { "dsAUDIO_FORMAT_DOLBY_AC3",          (int32_t)dsAUDIO_FORMAT_DOLBY_AC3          },
  { "dsAUDIO_FORMAT_DOLBY_EAC3",         (int32_t)dsAUDIO_FORMAT_DOLBY_EAC3         },
  { "dsAUDIO_FORMAT_DOLBY_AC4",          (int32_t)dsAUDIO_FORMAT_DOLBY_AC4          },
  { "dsAUDIO_FORMAT_DOLBY_MAT",          (int32_t)dsAUDIO_FORMAT_DOLBY_MAT          },
  { "dsAUDIO_FORMAT_DOLBY_TRUEHD",       (int32_t)dsAUDIO_FORMAT_DOLBY_TRUEHD       },
  { "dsAUDIO_FORMAT_DOLBY_EAC3_ATMOS",   (int32_t)dsAUDIO_FORMAT_DOLBY_EAC3_ATMOS   },
  { "dsAUDIO_FORMAT_DOLBY_TRUEHD_ATMOS", (int32_t)dsAUDIO_FORMAT_DOLBY_TRUEHD_ATMOS },
  { "dsAUDIO_FORMAT_DOLBY_MAT_ATMOS",    (int32_t)dsAUDIO_FORMAT_DOLBY_MAT_ATMOS    },
  { "dsAUDIO_FORMAT_DOLBY_AC4_ATMOS",    (int32_t)dsAUDIO_FORMAT_DOLBY_AC4_ATMOS    },
  { "dsAUDIO_FORMAT_AAC",                (int32_t)dsAUDIO_FORMAT_AAC                },
  { "dsAUDIO_FORMAT_VORBIS",             (int32_t)dsAUDIO_FORMAT_VORBIS             },
  { "dsAUDIO_FORMAT_WMA",                (int32_t)dsAUDIO_FORMAT_WMA                },
  { "dsAUDIO_FORMAT_UNKNOWN",            (int32_t)dsAUDIO_FORMAT_UNKNOWN            },
  { "dsAUDIO_FORMAT_MAX",                (int32_t)dsAUDIO_FORMAT_MAX                },
  {  NULL, -1 }
};

/* dsATMOSCapability_t */
const static ut_control_keyMapTable_t dsATMOSCapability_mapTable [] = {
  { "dsAUDIO_ATMOS_NOTSUPPORTED",  (int32_t)dsAUDIO_ATMOS_NOTSUPPORTED  },
  { "dsAUDIO_ATMOS_DDPLUSSTREAM",  (int32_t)dsAUDIO_ATMOS_DDPLUSSTREAM  },
  { "dsAUDIO_ATMOS_ATMOSMETADATA", (int32_t)dsAUDIO_ATMOS_ATMOSMETADATA },
  { "dsAUDIO_ATMOS_MAX",           (int32_t)dsAUDIO_ATMOS_MAX           },
  {  NULL, -1 }
};

/* dsAudioARCTypes_t */
const static ut_control_keyMapTable_t dsAudioARCTypes_mapTable [] = {
  { "dsAUDIOARCSUPPORT_NONE", (int32_t)dsAUDIOARCSUPPORT_NONE },
  { "dsAUDIOARCSUPPORT_ARC",  (int32_t)dsAUDIOARCSUPPORT_ARC  },
  { "dsAUDIOARCSUPPORT_eARC", (int32_t)dsAUDIOARCSUPPORT_eARC },
  {  NULL, -1 }
};

/* dsAudioCompression_t */
const static ut_control_keyMapTable_t dsAudioCompression_mapTable [] = {
  { "dsAUDIO_CMP_NONE",   (int32_t)dsAUDIO_CMP_NONE   },
  { "dsAUDIO_CMP_LIGHT",  (int32_t)dsAUDIO_CMP_LIGHT  },
  { "dsAUDIO_CMP_MEDIUM", (int32_t)dsAUDIO_CMP_MEDIUM },
  { "dsAUDIO_CMP_HEAVY",  (int32_t)dsAUDIO_CMP_HEAVY  },
  { "dsAUDIO_CMP_MAX",    (int32_t)dsAUDIO_CMP_MAX    },
  {  NULL, -1 }
};

/* dsAudioStereoMode_t */
const static ut_control_keyMapTable_t dsAudioStereoMode_mapTable [] = {
  { "dsAUDIO_STEREO_UNKNOWN",  (int32_t)dsAUDIO_STEREO_UNKNOWN  },
  { "dsAUDIO_STEREO_MONO",     (int32_t)dsAUDIO_STEREO_MONO     },
  { "dsAUDIO_STEREO_STEREO",   (int32_t)dsAUDIO_STEREO_STEREO   },
  { "dsAUDIO_STEREO_SURROUND", (int32_t)dsAUDIO_STEREO_SURROUND },
  { "dsAUDIO_STEREO_PASSTHRU", (int32_t)dsAUDIO_STEREO_PASSTHRU },
  { "dsAUDIO_STEREO_DD",       (int32_t)dsAUDIO_STEREO_DD       },
  { "dsAUDIO_STEREO_DDPLUS",   (int32_t)dsAUDIO_STEREO_DDPLUS   },
  { "dsAUDIO_STEREO_MAX",      (int32_t)dsAUDIO_STEREO_MAX      },
  {  NULL, -1 }
};

/* dsAudioInput_t */
const static ut_control_keyMapTable_t dsAudioInput_mapTable [] = {
  { "dsAUDIO_INPUT_PRIMARY", (int32_t)dsAUDIO_INPUT_PRIMARY },
  { "dsAUDIO_INPUT_SYSTEM",  (int32_t)dsAUDIO_INPUT_SYSTEM  },
  { "dsAUDIO_INPUT_MAX",     (int32_t)dsAUDIO_INPUT_MAX     },
  {  NULL, -1 }
};

/* dsError_t */
const static ut_control_keyMapTable_t dsError_mapTable [] = {
  { "dsERR_NONE",                    (int32_t)dsERR_NONE                    },
  { "dsERR_GENERAL",                 (int32_t)dsERR_GENERAL                 },
  { "dsERR_INVALID_PARAM",           (int32_t)dsERR_INVALID_PARAM           },
  { "dsERR_INVALID_STATE",           (int32_t)dsERR_INVALID_STATE           },
  { "dsERR_ALREADY_INITIALIZED",     (int32_t)dsERR_ALREADY_INITIALIZED     },
  { "dsERR_NOT_INITIALIZED",         (int32_t)dsERR_NOT_INITIALIZED         },
  { "dsERR_OPERATION_NOT_SUPPORTED", (int32_t)dsERR_OPERATION_NOT_SUPPORTED },
  { "dsERR_RESOURCE_NOT_AVAILABLE",  (int32_t)dsERR_RESOURCE_NOT_AVAILABLE  },
  { "dsERR_OPERATION_FAILED",        (int32_t)dsERR_OPERATION_FAILED        },
  { "dsErr_MAX",                     (int32_t)dsErr_MAX                     },
  {  NULL, -1 }
};

/* bool */
const static ut_control_keyMapTable_t bool_mapTable [] = {
  { "false", (int32_t)false },
  { "true",  (int32_t)true  },
  {  NULL, -1 }
};

/**
 * @brief This functions gets the Enum mapping string.
 *
 * This functions gets the Enum mapping string.
 * &Todo: replace with ut control function
 */
static char* ut_control_GetMapString(const ut_control_keyMapTable_t *conversionMap, int32_t key)
{
    int32_t count = 0;
    while(conversionMap[count].string != NULL){
        if(conversionMap[count].key == key) {
            return conversionMap[count].string;
        }
        count++;
    }
    return "";
}

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

/**
 * @brief Callback function for Headphone connection status.
 *
 * This function is invoked whenever a change occurs in the Headphone connection.
 */
static void audioOutPortConnectCB(dsAudioPortType_t portType, uint32_t uiPortNo, bool isPortCon)
{
    UT_LOG_INFO("Received Connection status callback port: %s, port number: %d, Connection: %s",
                 ut_control_GetMapString(dsAudioPortType_mapTable, portType),uiPortNo,
                 ut_control_GetMapString(bool_mapTable, isPortCon));
    gConnectionStatus = isPortCon;
}

/**
 * @brief Callback function for detecting audio format changes.
 *
 * This function is triggered whenever the audio format of the playback stream changes.
 */
static void audioFormatUpdateCB(dsAudioFormat_t audioFormat)
{
    UT_LOG_INFO("Received Format update callback : %s", ut_control_GetMapString(dsAudioFormat_mapTable, audioFormat));
    gAudioFormat = audioFormat;
}

/**
 * @brief Callback function for detecting ATMOS Capabilities changes.
 *
 * This function is triggered whenever the ATMOS Capabilities changes.
 */
static void atmosCapsChange(dsATMOSCapability_t atmosCaps, bool status)
{
    UT_LOG_INFO("Received ATMOS Capablity Change callback, Capability: %s, Status: %s",
                 ut_control_GetMapString(dsATMOSCapability_mapTable, atmosCaps),
                 ut_control_GetMapString(bool_mapTable, status));
    gAtosCapablity = atmosCaps;
    gAtmosStatus   = status;
}

/**
* @brief This test initializes the dsAudio Module.
*
* This test function initializes the dsAudio Module.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 001@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [dsAudio_L3_Low-Level_TestSpecification.md](../docs/pages/ds-audio_L3_Low-Level_TestSpecification.md)
*/
void test_l3_dsAudio_initialize(void)
{
    gTestID = 1;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;

    /* Initialize the dsAudio Module */
    UT_LOG_INFO("Calling dsAudioPortInit()");
    ret = dsAudioPortInit();
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsAudioPortInit() dsError_t:[%s]", ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsAudioPortInit() dsError_t:[%s]", ut_control_GetMapString(dsError_mapTable, ret));
    }

    if(gSourceType == 0) {
        /* Register connection status callback */
        UT_LOG_INFO("Calling dsAudioOutRegisterConnectCB(CBFunc:[0x%0X])", audioOutPortConnectCB);
        ret = dsAudioOutRegisterConnectCB(audioOutPortConnectCB);
        if (ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed dsAudioOutRegisterConnectCB(CBFunc:[0x%0X]) dsError_t:[%s]",
                        audioOutPortConnectCB, ut_control_GetMapString(dsError_mapTable, ret));
        }
        else {
            UT_LOG_INFO("Result dsAudioOutRegisterConnectCB(CBFunc:[0x%0X]) dsError_t:[%s]",
                        audioOutPortConnectCB, ut_control_GetMapString(dsError_mapTable, ret));
        }

        /* Register ATMOS capabilities change callback */
        UT_LOG_INFO("Calling dsAudioAtmosCapsChangeRegisterCB(cbFun:[0x%0X])", atmosCapsChange);
        ret = dsAudioAtmosCapsChangeRegisterCB (atmosCapsChange);
        if (ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed dsAudioAtmosCapsChangeRegisterCB(cbFun:[0x%0X]) dsError_t:[%s]",
                        atmosCapsChange, ut_control_GetMapString(dsError_mapTable, ret));
        }
        else {
            UT_LOG_INFO("Result dsAudioAtmosCapsChangeRegisterCB(cbFun:[0x%0X]) dsError_t:[%s]",
                        atmosCapsChange, ut_control_GetMapString(dsError_mapTable, ret));
        }
    }

    /* Register audio format change callback */
    UT_LOG_INFO("Calling dsAudioFormatUpdateRegisterCB(cbFun:[0x%0X])", audioFormatUpdateCB);
    ret = dsAudioFormatUpdateRegisterCB(audioFormatUpdateCB);
    if (ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsAudioFormatUpdateRegisterCB(cbFun:[0x%0X]) dsError_t:[%s]",
                      audioFormatUpdateCB, ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsAudioFormatUpdateRegisterCB(cbFun:[0x%0X]) dsError_t:[%s]",
                     audioFormatUpdateCB, ut_control_GetMapString(dsError_mapTable, ret));
    }

    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test enables the dsAudio port.
*
* This test function enables the dsAudio port.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 002@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [dsAudio_L3_Low-Level_TestSpecification.md](../docs/pages/ds-audio_L3_Low-Level_TestSpecification.md)
*/
void test_l3_dsAudio_enable_port(void)
{
    gTestID = 2;
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret   = dsERR_NONE;
    int32_t choice  = -1;
    intptr_t handle = (intptr_t)NULL;
    bool enabled    = false;
    dsAudioPortType_t port = dsAUDIOPORT_TYPE_MAX;

    printf("\ndsAudio Port\n");
    printf("----------------------------------------------------------\n");
    printf("\t#  %-30s%s\n\n","Audio Port", "Index");
    for(int32_t i = 0; i < gDSAudioNumberOfPorts; i++) {
        printf("\t%d.  %-30s%-2d\n", i+1, ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[i].typeid),
                                          gDSAudioPortConfiguration[i].index);
    }
    printf("----------------------------------------------------------\n");
    printf("\nSelect dsAudio Port: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);

    if(choice < 1 || choice > gDSAudioNumberOfPorts) {
        printf("Invalid Port choice\n");
        goto exit;
    }

    port = choice - 1;

    UT_LOG_INFO("Calling dsGetAudioPort(type:[%s], index:[%d], handle:[])",
                 ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                 gDSAudioPortConfiguration[port].index);
    ret = dsGetAudioPort(gDSAudioPortConfiguration[port].typeid, gDSAudioPortConfiguration[port].index, &handle);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                      ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                      gDSAudioPortConfiguration[port].index,
                      handle,
                      ut_control_GetMapString(dsError_mapTable, ret));
        goto exit;
    }
    else {
        UT_LOG_INFO("Result dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                     ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                     gDSAudioPortConfiguration[port].index,
                     handle,
                     ut_control_GetMapString(dsError_mapTable, ret));
    }

    UT_LOG_INFO("Calling dsEnableAudioPort(handle:[0x%0X], enabled:[%s])",
                 handle,
                 ut_control_GetMapString(bool_mapTable, true));
    ret = dsEnableAudioPort(handle, true);
    if (ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsEnableAudioPort(handle:[0x%0X], enabled:[%s]) dsError_t:[%s]",
                      handle,
                      ut_control_GetMapString(bool_mapTable, true),
                      ut_control_GetMapString(dsError_mapTable, ret));
        goto exit;
    }
    else {
        UT_LOG_INFO("Result dsEnableAudioPort(handle:[0x%0X], enabled:[%s]) dsError_t:[%s]",
                     handle,
                     ut_control_GetMapString(bool_mapTable, true),
                     ut_control_GetMapString(dsError_mapTable, ret));
    }

    UT_LOG_INFO("Calling dsIsAudioPortEnabled(handle:[0x%0X], enabled:[])", handle);
    ret = dsIsAudioPortEnabled(handle, &enabled);
    if (ret != dsERR_NONE || !enabled) {
        UT_LOG_ERROR("Failed dsIsAudioPortEnabled(handle:[0x%0X], enabled:[%s]) dsError_t:[%s]",
                      handle, ut_control_GetMapString(bool_mapTable, enabled),
                      ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsIsAudioPortEnabled(handle:[0x%0X], enabled:[%s]) dsError_t:[%s]",
                     handle, ut_control_GetMapString(bool_mapTable, enabled),
                     ut_control_GetMapString(dsError_mapTable, ret));
    }

    if(gDSAudioPortConfiguration[port].typeid == dsAUDIOPORT_TYPE_HDMI_ARC) {
        dsAudioARCStatus_t arcStatus = {0};
        int32_t archType = 0;

        printf("\nSupported ARC Types\n");
        printf("----------------------------------------------------------\n");
        printf("\t#  %-20s\n\n","ARC Type");
        for(int32_t i = dsAUDIOARCSUPPORT_ARC; i <= dsAUDIOARCSUPPORT_eARC; i++) {
            printf("\t%d.  %-20s\n", i, ut_control_GetMapString(dsAudioARCTypes_mapTable, i));
        }
        printf("----------------------------------------------------------\n");
        printf("\nSelect ARC Type: ");
        scanf("%d", &archType);
        readAndDiscardRestOfLine(stdin);

        arcStatus.status = true;
        arcStatus.type   = (dsAudioARCTypes_t)archType;

        UT_LOG_INFO("Calling dsAudioEnableARC(handle:[0x%0X], arcStatus:[.type=%s, .status=%s])",
                    handle,
                    ut_control_GetMapString(dsAudioARCTypes_mapTable, arcStatus.type),
                    ut_control_GetMapString(bool_mapTable, arcStatus.status));
        ret = dsAudioEnableARC(handle, arcStatus);
        if (ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed dsAudioEnableARC(handle:[0x%0X], arcStatus:[.type=%s, .status=%s]) dsError_t:[%s]",
                          handle,
                          ut_control_GetMapString(dsAudioARCTypes_mapTable, arcStatus.type),
                          ut_control_GetMapString(bool_mapTable, arcStatus.status),
                          ut_control_GetMapString(dsError_mapTable, ret));
        }
        else {
            UT_LOG_INFO("Result dsAudioEnableARC(handle:[0x%0X], arcStatus:[.type=%s, .status=%s]) dsError_t:[%s]",
                        handle,
                        ut_control_GetMapString(dsAudioARCTypes_mapTable, arcStatus.type),
                        ut_control_GetMapString(bool_mapTable, arcStatus.status),
                        ut_control_GetMapString(dsError_mapTable, ret));
        }
        UT_LOG_INFO("Calling dsIsAudioPortEnabled(handle:[0x%0X], enabled:[])", handle);
        ret = dsIsAudioPortEnabled(handle, &enabled);
        if (ret != dsERR_NONE || !enabled) {
            UT_LOG_ERROR("Failed dsIsAudioPortEnabled(handle:[0x%0X], enabled:[%s]) dsError_t:[%s]",
                        handle, ut_control_GetMapString(bool_mapTable, enabled),
                        ut_control_GetMapString(dsError_mapTable, ret));
        }
        else {
            UT_LOG_INFO("Result dsIsAudioPortEnabled(handle:[0x%0X], enabled:[%s]) dsError_t:[%s]",
                        handle, ut_control_GetMapString(bool_mapTable, enabled),
                        ut_control_GetMapString(dsError_mapTable, ret));
        }
    }
exit:
    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test disables the dsAudio port.
*
* This test function disables the dsAudio port.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 003@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [dsAudio_L3_Low-Level_TestSpecification.md](../docs/pages/ds-audio_L3_Low-Level_TestSpecification.md)
*/
void test_l3_dsAudio_disable_port(void)
{
    gTestID = 3;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;

    int32_t count   = 0;
    int32_t choice  = -1;
    intptr_t handle = (intptr_t)NULL;
    bool enabled    = false;
    int32_t enable_port[DS_AUDIO_MAX_PORTS] = {0};
    dsAudioPortType_t port = dsAUDIOPORT_TYPE_MAX;

    printf("\nSelect dsAudio Port to Disable\n");
    printf("----------------------------------------------------------\n");
    printf("\t#  %-30s%s\n\n","Audio Port", "Index");
    for(int32_t i = 0; i < gDSAudioNumberOfPorts; i++) {
        ret = dsGetAudioPort(gDSAudioPortConfiguration[i].typeid, gDSAudioPortConfiguration[i].index, &handle);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                          ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[i].typeid),
                          gDSAudioPortConfiguration[i].index,
                          handle,
                          ut_control_GetMapString(dsError_mapTable, ret));
            continue;
        }

        ret = dsIsAudioPortEnabled(handle, &enabled);
        if(enabled == true) {
            enable_port[count] = i;
            printf("\t%d.  %-30s%-2d\n", count+1,
                     ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[i].typeid),
                     gDSAudioPortConfiguration[i].index);
            count++;
        }
    }
    printf("----------------------------------------------------------\n");
    if(count == 0) {
        printf("\nNo Ports Enabled\n");
        goto exit;;
    }

    printf("\nSelect dsAudio Port: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);
    if(choice < 1 || choice > count) {
        printf("Invalid Port choice\n");
        goto exit;
    }

    port = enable_port[choice - 1];

    UT_LOG_INFO("Calling dsGetAudioPort(type:[%s], index:[%d], handle:[])",
                 ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                 gDSAudioPortConfiguration[port].index);
    ret = dsGetAudioPort(gDSAudioPortConfiguration[port].typeid, gDSAudioPortConfiguration[port].index, &handle);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                      ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                      gDSAudioPortConfiguration[port].index,
                      handle,
                      ut_control_GetMapString(dsError_mapTable, ret));
        goto exit;
    }
    else {
        UT_LOG_INFO("Result dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                     ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                     gDSAudioPortConfiguration[port].index,
                     handle,
                     ut_control_GetMapString(dsError_mapTable, ret));
    }

    UT_LOG_INFO("Calling dsEnableAudioPort(handle:[0x%0X], enabled:[%s])",
                 handle,
                 ut_control_GetMapString(bool_mapTable, false));
    ret = dsEnableAudioPort(handle, false);
    if (ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsEnableAudioPort(handle:[0x%0X], enabled:[%s]) dsError_t:[%s]",
                      handle,
                      ut_control_GetMapString(bool_mapTable, false),
                      ut_control_GetMapString(dsError_mapTable, ret));
        goto exit;
    }
    else {
        UT_LOG_INFO("Result dsEnableAudioPort(handle:[0x%0X], enabled:[%s]) dsError_t:[%s]",
                     handle,
                     ut_control_GetMapString(bool_mapTable, false),
                     ut_control_GetMapString(dsError_mapTable, ret));
    }

    UT_LOG_INFO("Calling dsIsAudioPortEnabled(handle:[0x%0X], enabled:[])",
                 handle);
    ret = dsIsAudioPortEnabled(handle, &enabled);
    if (ret != dsERR_NONE || enabled) {
        UT_LOG_ERROR("Failed dsIsAudioPortEnabled(handle:[0x%0X], enabled:[%s]) dsError_t:[%s]",
                     handle, ut_control_GetMapString(bool_mapTable, enabled),
                     ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsIsAudioPortEnabled(handle:[0x%0X], enabled:[%s]) dsError_t:[%s]",
                     handle, ut_control_GetMapString(bool_mapTable, enabled),
                     ut_control_GetMapString(dsError_mapTable, ret));
    }
exit:
    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test checks for headphone connection status.
*
* This test function checks for headphone connection status.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 004@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [dsAudio_L3_Low-Level_TestSpecification.md](../docs/pages/ds-audio_L3_Low-Level_TestSpecification.md)
*/
void test_l3_dsAudio_headphone_connection(void)
{
    gTestID = 4;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret    = dsERR_NONE;
    intptr_t handle  = (intptr_t)NULL;
    bool isConnected = false;

    for(int32_t i = 0; i < gDSAudioNumberOfPorts; i++) {
        if(gDSAudioPortConfiguration[i].typeid != dsAUDIOPORT_TYPE_HEADPHONE) {
            continue;
        }
        UT_LOG_INFO("Calling dsGetAudioPort(type:[%s], index:[%d], handle:[])",
                     ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[i].typeid),
                     gDSAudioPortConfiguration[i].index);
        ret = dsGetAudioPort(gDSAudioPortConfiguration[i].typeid, gDSAudioPortConfiguration[i].index, &handle);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                          ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[i].typeid),
                          gDSAudioPortConfiguration[i].index,
                          handle,
                          ut_control_GetMapString(dsError_mapTable, ret));
            goto exit;
        }
        else {
            UT_LOG_INFO("Result dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                         ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[i].typeid),
                         gDSAudioPortConfiguration[i].index,
                         handle,
                         ut_control_GetMapString(dsError_mapTable, ret));
        }
        break;
    }

    if(handle == (intptr_t)NULL) {
        UT_LOG_ERROR("Platform doesn't support Headphone");
        goto exit;
    }

    UT_LOG_INFO("Calling dsAudioOutIsConnected(handle:[0x%0X], isConnected:[])",
                 handle);
    ret = dsAudioOutIsConnected(handle, &isConnected);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsAudioOutIsConnected(handle:[0x%0X], isConnected:[%s]) dsError_t:[%s]",
                      handle, ut_control_GetMapString(bool_mapTable, isConnected),
                      ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsAudioOutIsConnected(handle:[0x%0X], isConnected:[%s]) dsError_t:[%s]",
                     handle, ut_control_GetMapString(bool_mapTable, isConnected),
                     ut_control_GetMapString(dsError_mapTable, ret));
    }

    UT_LOG_INFO("Headphone Connection status: %s, connection status from Callback: %s",
                     ut_control_GetMapString(bool_mapTable, isConnected),
                     ut_control_GetMapString(bool_mapTable, gConnectionStatus));

exit:
    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test sets the audio compression levels.
*
* This test function sets the audio compression levels.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 005@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [dsAudio_L3_Low-Level_TestSpecification.md](../docs/pages/ds-audio_L3_Low-Level_TestSpecification.md)
*/
void test_l3_dsAudio_audio_compression(void)
{
    gTestID = 5;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;

    int32_t count         = 0;
    int32_t compression   = 0;
    int32_t compression_g = 0;
    int32_t choice        = -1;
    intptr_t handle       = (intptr_t)NULL;
    bool enabled          = false;
    int32_t enable_port[DS_AUDIO_MAX_PORTS] = {0};
    dsAudioPortType_t port = dsAUDIOPORT_TYPE_MAX;

    printf("\nSelect dsAudio Port to Apply Audio Compression\n");
    printf("----------------------------------------------------------\n");
    printf("\t#  %-30s%s\n\n","Audio Port", "Index");
    for(int32_t i = 0; i < gDSAudioNumberOfPorts; i++) {
        if(gDSAudioPortConfiguration[i].no_of_supported_compression == 0) {
            continue;
        }

        ret = dsGetAudioPort(gDSAudioPortConfiguration[i].typeid, gDSAudioPortConfiguration[i].index, &handle);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                          ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[i].typeid),
                          gDSAudioPortConfiguration[i].index,
                          handle,
                          ut_control_GetMapString(dsError_mapTable, ret));
            continue;
        }

        ret = dsIsAudioPortEnabled(handle, &enabled);
        if(enabled == true) {
            enable_port[count] = i;
            printf("\t%d.  %-30s%-2d\n", count+1,
                     ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[i].typeid),
                     gDSAudioPortConfiguration[i].index);
            count++;
        }
    }
    printf("----------------------------------------------------------\n");
    if(count == 0) {
        printf("\nNo Ports Enabled\n");
        goto exit;
    }

    printf("\nSelect dsAudio Port: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);
    if(choice < 1 || choice > count) {
        printf("Invalid Port choice\n");
        goto exit;
    }

    port = enable_port[choice - 1];

    UT_LOG_INFO("Calling dsGetAudioPort(type:[%s], index:[%d], handle:[])",
                 ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                 gDSAudioPortConfiguration[port].index);
    ret = dsGetAudioPort(gDSAudioPortConfiguration[port].typeid, gDSAudioPortConfiguration[port].index, &handle);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                      ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                      gDSAudioPortConfiguration[port].index,
                      handle,
                      ut_control_GetMapString(dsError_mapTable, ret));
        goto exit;
    }
    else {
        UT_LOG_INFO("Result dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                     ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                     gDSAudioPortConfiguration[port].index,
                     handle,
                     ut_control_GetMapString(dsError_mapTable, ret));
    }

    printf("\nCompression Type\n");
    printf("----------------------------------------------------------\n");
    printf("\t#  %-20s\n\n","Compression");
    for(int32_t i = dsAUDIO_CMP_NONE; i < dsAUDIO_CMP_MAX; i++) {
        printf("\t%d.  %-20s\n", i,
                     ut_control_GetMapString(dsAudioCompression_mapTable, i));
    }
    printf("----------------------------------------------------------\n");
    printf("\nSelect Compression: ");
    scanf("%d", &compression);
    readAndDiscardRestOfLine(stdin);
    if(compression < dsAUDIO_CMP_NONE || compression >= dsAUDIO_CMP_MAX) {
        printf("Invalid Compression Type\n");
        goto exit;
    }

    UT_LOG_INFO("Calling dsSetAudioCompression(handle:[0x%0X], compression:[%s])",
                 handle,
                 ut_control_GetMapString(dsAudioCompression_mapTable, compression));
    ret = dsSetAudioCompression(handle, (dsAudioCompression_t)compression);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsSetAudioCompression(handle:[0x%0X], compression:[%s]) dsError_t:[%s]",
                      handle, ut_control_GetMapString(dsAudioCompression_mapTable, compression),
                      ut_control_GetMapString(dsError_mapTable, ret));
        goto exit;
    }
    else {
        UT_LOG_INFO("Result dsSetAudioCompression(handle:[0x%0X], compression:[%s]) dsError_t:[%s]",
                     handle, ut_control_GetMapString(dsAudioCompression_mapTable, compression),
                     ut_control_GetMapString(dsError_mapTable, ret));
    }

    UT_LOG_INFO("Calling dsGetAudioCompression(handle:[0x%0X], compression:[])", handle);
    ret = dsGetAudioCompression(handle, &compression_g);
    if(ret != dsERR_NONE || compression_g != compression) {
        UT_LOG_ERROR("Failed dsGetAudioCompression(handle:[0x%0X], compression:[%s]) dsError_t:[%s]",
                      handle, ut_control_GetMapString(dsAudioCompression_mapTable, compression_g),
                      ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsGetAudioCompression(handle:[0x%0X], compression:[%s]) dsError_t:[%s]",
                        handle, ut_control_GetMapString(dsAudioCompression_mapTable, compression_g),
                        ut_control_GetMapString(dsError_mapTable, ret));
    }
exit:
    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test checks for MS12 DAP features.
*
* This test function checks for MS12 DAP features.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 006@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [dsAudio_L3_Low-Level_TestSpecification.md](../docs/pages/ds-audio_L3_Low-Level_TestSpecification.md)
*/
void test_l3_dsAudio_ms12_dap(void)
{
    gTestID = 6;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret   = dsERR_NONE;
    int32_t count   = 0;
    int32_t choice  = -1;
    intptr_t handle = (intptr_t)NULL;
    bool enabled    = false;
    int32_t enable_port[DS_AUDIO_MAX_PORTS] = {0};
    dsAudioPortType_t port = dsAUDIOPORT_TYPE_MAX;

    printf("\nSelect dsAudio Port to Apply MS12 DAP\n");
    printf("----------------------------------------------------------\n");
    printf("\t#  %-30s%s\n\n","Audio Port", "Index");
    for(int32_t i = 0; i < gDSAudioNumberOfPorts; i++) {
        if(gDSAudioPortConfiguration[i].ms12_capabilites == 0) {
            continue;
        }

        ret = dsGetAudioPort(gDSAudioPortConfiguration[i].typeid, gDSAudioPortConfiguration[i].index, &handle);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                          ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[i].typeid),
                          gDSAudioPortConfiguration[i].index,
                          handle,
                          ut_control_GetMapString(dsError_mapTable, ret));
            continue;
        }

        ret = dsIsAudioPortEnabled(handle, &enabled);
        if(enabled == true) {
            enable_port[count] = i;
            printf("\t%d.  %-30s%-2d\n", count+1,
                     ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[i].typeid),
                     gDSAudioPortConfiguration[i].index);
            count++;
        }
    }
    printf("----------------------------------------------------------\n");
    if(count == 0) {
        printf("\nNo Ports Enabled\n");
        goto exit;
    }

    printf("\nSelect dsAudio Port: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);
    if(choice < 1 || choice > count) {
        printf("Invalid Port choice\n");
        goto exit;
    }

    port = enable_port[choice - 1];

    UT_LOG_INFO("Calling dsGetAudioPort(type:[%s], index:[%d], handle:[])",
                 ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                 gDSAudioPortConfiguration[port].index);
    ret = dsGetAudioPort(gDSAudioPortConfiguration[port].typeid, gDSAudioPortConfiguration[port].index, &handle);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                      ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                      gDSAudioPortConfiguration[port].index,
                      handle,
                      ut_control_GetMapString(dsError_mapTable, ret));
        goto exit;
    }
    else {
        UT_LOG_INFO("Result dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                     ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                     gDSAudioPortConfiguration[port].index,
                     handle,
                     ut_control_GetMapString(dsError_mapTable, ret));
    }

    printf("\nMS12 DAP Feature\n");
    printf("----------------------------------------------------------\n");
    printf("\t#   %-20s\n\n","MS12 DAP Feature");
    printf("\t1.  %-20s\n","DolbyVolume");
    printf("\t2.  %-20s\n","IntelligentEqualizer");
    printf("\t3.  %-20s\n","DialogueEnhancer");
    printf("\t4.  %-20s\n","Volumeleveller");
    printf("\t5.  %-20s\n","BassEnhancer");
    printf("\t6.  %-20s\n","SurroundDecoder");
    printf("\t7.  %-20s\n","DRCMode");
    printf("\t8.  %-20s\n","SurroundVirtualizer");
    printf("\t9.  %-20s\n","MISteering");
    printf("\t10. %-20s\n","GraphicEqualizer");
    printf("\t11. %-20s\n","LEConfig");
    printf("----------------------------------------------------------\n");

    printf("\nSelect MS12 DAP Feature: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1: //DolbyVolume
        {
            bool mode = false, mode_g = false;

            if(!(gDSAudioPortConfiguration[port].ms12_capabilites & dsMS12SUPPORT_DolbyVolume)) {
                UT_LOG_WARNING("%s Port doesn't Support DolbyVolume",
                               ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid));
                break;
            }

            printf("\nDolby Volume[1:Enable, 2:Disable]: ");
            scanf("%d", &choice);
            if(choice < 1 || choice > 2) {
                printf("Invalid Dolby Volume mode\n");
                break;
            }

            mode = (choice == 1) ? true : false;

            UT_LOG_INFO("Calling dsSetDolbyVolumeMode(handle:[0x%0X], mode:[%s])",
                        handle,
                        ut_control_GetMapString(bool_mapTable, mode));
            ret = dsSetDolbyVolumeMode(handle, mode);
            if(ret != dsERR_NONE) {
                UT_LOG_ERROR("Failed dsSetDolbyVolumeMode(handle:[0x%0X], mode:[%s]) dsError_t:[%s]",
                              handle,
                              ut_control_GetMapString(bool_mapTable, mode),
                              ut_control_GetMapString(dsError_mapTable, ret));
                break;
            }
            else {
                UT_LOG_INFO("Result dsSetDolbyVolumeMode(handle:[0x%0X], mode:[%s]) dsError_t:[%s]",
                             handle,
                             ut_control_GetMapString(bool_mapTable, mode),
                             ut_control_GetMapString(dsError_mapTable, ret));
            }

            UT_LOG_INFO("Calling dsGetDolbyVolumeMode(handle:[0x%0X], *mode:[])",
                        handle);
            ret = dsGetDolbyVolumeMode(handle, &mode_g);
            if(ret != dsERR_NONE || mode != mode_g) {
                UT_LOG_ERROR("Failed dsGetDolbyVolumeMode(handle:[0x%0X], *mode:[%s]) dsError_t:[%s]",
                              handle,
                              ut_control_GetMapString(bool_mapTable, mode_g),
                              ut_control_GetMapString(dsError_mapTable, ret));
            }
            else {
                UT_LOG_INFO("Result dsGetDolbyVolumeMode(handle:[0x%0X], *mode:[%s]) dsError_t:[%s]",
                             handle,
                             ut_control_GetMapString(bool_mapTable, mode_g),
                             ut_control_GetMapString(dsError_mapTable, ret));
            }

            break;
        }
        case 2: //IntelligentEqualizer
        {
            int32_t mode = 0, mode_g = 0;

            if(!(gDSAudioPortConfiguration[port].ms12_capabilites & dsMS12SUPPORT_InteligentEqualizer)) {
                UT_LOG_WARNING("%s Port doesn't Support IntelligentEqualizer",
                               ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid));
                break;
            }

            printf("\nIntelligentEqualizer Mode\n");
            printf("----------------------------------------------------------\n");
            printf("\t#   %-20s\n\n","Mode");
            printf("\t0.  %-20s\n","OFF");
            printf("\t1.  %-20s\n","Open");
            printf("\t2.  %-20s\n","Rich");
            printf("\t3.  %-20s\n","Focused");
            printf("\t4.  %-20s\n","Balanced");
            printf("\t5.  %-20s\n","Warm");
            printf("\t6.  %-20s\n","Detailed");
            printf("----------------------------------------------------------\n");

            printf("\nSelect IntelligentEqualizer Mode: ");
            scanf("%d", &mode);

            if(mode < 0 || mode > 6) {
                printf("Invalid IntelligentEqualizer Mode choice\n");
                break;
            }

            UT_LOG_INFO("Calling dsSetIntelligentEqualizerMode(handle:[0x%0X], mode:[%d])",
                        handle, mode);
            ret = dsSetIntelligentEqualizerMode(handle, mode);
            if(ret != dsERR_NONE) {
                UT_LOG_ERROR("Failed dsSetIntelligentEqualizerMode(handle:[0x%0X], mode:[%d]) dsError_t:[%s]",
                              handle, mode,
                              ut_control_GetMapString(dsError_mapTable, ret));
                break;
            }
            else {
                UT_LOG_INFO("Result dsSetIntelligentEqualizerMode(handle:[0x%0X], mode:[%d]) dsError_t:[%s]",
                             handle, mode,
                             ut_control_GetMapString(dsError_mapTable, ret));
            }

            UT_LOG_INFO("Calling dsGetIntelligentEqualizerMode(handle:[0x%0X], mode:[])", handle);
            ret = dsGetIntelligentEqualizerMode(handle, &mode_g);
            if(ret != dsERR_NONE || mode_g != mode) {
                UT_LOG_ERROR("Failed dsGetIntelligentEqualizerMode(handle:[0x%0X], mode:[%d]) dsError_t:[%s]",
                              handle, mode_g,
                              ut_control_GetMapString(dsError_mapTable, ret));
            }
            else {
                UT_LOG_INFO("Result dsGetIntelligentEqualizerMode(handle:[0x%0X], mode:[%d]) dsError_t:[%s]",
                             handle, mode_g,
                             ut_control_GetMapString(dsError_mapTable, ret));
            }
            break;
        }
        case 3: //DialogueEnhancer
        {
            int32_t level = 0, level_g = 0;

            if(!(gDSAudioPortConfiguration[port].ms12_capabilites & dsMS12SUPPORT_DialogueEnhancer)) {
                UT_LOG_WARNING("%s Port doesn't Support DialogueEnhancer",
                               ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid));
                break;
            }

            printf("\nSelect DialogueEnhancer Level[0-16]: ");
            scanf("%d", &level);
            if(level < 0 || level > 16) {
                printf("Invalid DialogueEnhancer Level\n");
                break;
            }

            UT_LOG_INFO("Calling dsSetDialogEnhancement(handle:[0x%0X], level:[%d])",
                        handle, level);
            ret = dsSetDialogEnhancement(handle, level);
            if(ret != dsERR_NONE) {
                UT_LOG_ERROR("Failed dsSetDialogEnhancement(handle:[0x%0X], level:[%d]) dsError_t:[%s]",
                              handle, level,
                              ut_control_GetMapString(dsError_mapTable, ret));
                break;
            }
            else {
                UT_LOG_INFO("Result dsSetDialogEnhancement(handle:[0x%0X], level:[%d]) dsError_t:[%s]",
                             handle, level,
                             ut_control_GetMapString(dsError_mapTable, ret));
            }

            UT_LOG_INFO("Calling dsGetDialogEnhancement(handle:[0x%0X], level:[%d])",
                        handle, level);
            ret = dsGetDialogEnhancement(handle, &level_g);
            if(ret != dsERR_NONE || level_g != level) {
                UT_LOG_ERROR("Failed dsGetDialogEnhancement(handle:[0x%0X], level:[%d]) dsError_t:[%s]",
                              handle, level_g,
                              ut_control_GetMapString(dsError_mapTable, ret));
            }
            else {
                UT_LOG_INFO("Result dsGetDialogEnhancement(handle:[0x%0X], level:[%d]) dsError_t:[%s]",
                             handle, level_g,
                             ut_control_GetMapString(dsError_mapTable, ret));
            }
            break;
        }
        case 4: //Volumeleveller
        {
            dsVolumeLeveller_t volume_level   = {0};
            dsVolumeLeveller_t volume_level_g = {0};

            if(!(gDSAudioPortConfiguration[port].ms12_capabilites & 0x08)) {
                UT_LOG_WARNING("%s Port doesn't Support Volumeleveller",
                               ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid));
                break;
            }

            printf("\nSelect Volumeleveller Mode[0:Off, 1:On, 2:Auto]: ");
            scanf("%d", &volume_level.mode);
            if(volume_level.mode < 0 || volume_level.mode > 2) {
                printf("Invalid Volumeleveller Mode\n");
                break;
            }
            printf("\nSelect Volumeleveller Level[0-10]: ");
            scanf("%d", &volume_level.level);
            if(volume_level.level < 0 || volume_level.level > 10) {
                printf("Invalid Volumeleveller level\n");
                break;
            }

            UT_LOG_INFO("Calling dsSetVolumeLeveller(handle:[0x%0X], volLeveller:[mode:%d, level:%d])",
                         handle, volume_level.mode, volume_level.level);
            ret = dsSetVolumeLeveller(handle, volume_level);
            if(ret != dsERR_NONE) {
                UT_LOG_ERROR("Failed dsSetVolumeLeveller(handle:[0x%0X], volLeveller:[mode:%d, level:%d]) dsError_t:[%s]",
                              handle, volume_level.mode, volume_level.level,
                              ut_control_GetMapString(dsError_mapTable, ret));
                break;
            }
            else {
                UT_LOG_INFO("Result dsSetVolumeLeveller(handle:[0x%0X], volLeveller:[mode:%d, level:%d]) dsError_t:[%s]",
                             handle, volume_level.mode, volume_level.level,
                             ut_control_GetMapString(dsError_mapTable, ret));
            }

            UT_LOG_INFO("Calling dsGetVolumeLeveller(handle:[0x%0X], volLeveller:[])",
                         handle);
            ret = dsGetVolumeLeveller(handle, &volume_level_g);
            if(ret != dsERR_NONE || volume_level_g.mode != volume_level.mode || volume_level_g.level != volume_level.level) {
                UT_LOG_ERROR("Failed dsGetVolumeLeveller(handle:[0x%0X], volLeveller:[mode:%d, level:%d]) dsError_t:[%s]",
                              handle, volume_level_g.mode, volume_level_g.level,
                              ut_control_GetMapString(dsError_mapTable, ret));
            }
            else {
                UT_LOG_INFO("Result dsGetVolumeLeveller(handle:[0x%0X], volLeveller:[mode:%d, level:%d]) dsError_t:[%s]",
                             handle, volume_level_g.mode, volume_level_g.level,
                             ut_control_GetMapString(dsError_mapTable, ret));
            }
            break;
        }
        case 5: //BassEnhancer
        {
            int32_t boost = 0, boost_g = 0;

            if(!(gDSAudioPortConfiguration[port].ms12_capabilites & 0x10)) {
                UT_LOG_WARNING("%s Port doesn't Support BassEnhancer",
                               ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid));
                break;
            }
            printf("\nSelect BassEnhancer Boost[0-100]: ");
            scanf("%d", &boost);
            if(boost < 0 || boost > 100) {
                printf("Invalid BassEnhancer Boost\n");
                break;
            }

            UT_LOG_INFO("Calling dsSetDialogEnhancement(handle:[0x%0X], boost:[%d])",
                        handle, boost);
            ret = dsSetBassEnhancer(handle, boost);
            if(ret != dsERR_NONE) {
                UT_LOG_ERROR("Failed dsSetBassEnhancer(handle:[0x%0X], boost:[%d]) dsError_t:[%s]",
                              handle, boost,
                              ut_control_GetMapString(dsError_mapTable, ret));
                break;
            }
            else {
                UT_LOG_INFO("Result dsSetBassEnhancer(handle:[0x%0X], boost:[%d]) dsError_t:[%s]",
                             handle, boost,
                             ut_control_GetMapString(dsError_mapTable, ret));
            }

            UT_LOG_INFO("Calling dsGetBassEnhancer(handle:[0x%0X], boost:[])", handle);
            ret = dsGetBassEnhancer(handle, &boost_g);
            if(ret != dsERR_NONE || boost != boost_g) {
                UT_LOG_ERROR("Failed dsGetBassEnhancer(handle:[0x%0X], boost:[%d]) dsError_t:[%s]",
                              handle, boost_g,
                              ut_control_GetMapString(dsError_mapTable, ret));
            }
            else {
                UT_LOG_INFO("Result dsGetBassEnhancer(handle:[0x%0X], boost:[%d]) dsError_t:[%s]",
                             handle, boost_g,
                             ut_control_GetMapString(dsError_mapTable, ret));
            }
            break;
        }
        case 6: //SurroundDecoder
        {
            bool mode = false, mode_g = false;

            if(!(gDSAudioPortConfiguration[port].ms12_capabilites & 0x20)) {
                UT_LOG_WARNING("%s Port doesn't Support SurroundDecoder",
                               ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid));
                break;
            }

            printf("\nSurround Decoder[1:Enable, 2:Disable]: ");
            scanf("%d", &choice);
            if(choice < 1 || choice > 2) {
                printf("Invalid choice\n");
                break;
            }

            mode = (choice == 1) ? true : false;

            UT_LOG_INFO("Calling dsEnableSurroundDecoder(handle:[0x%0X], mode:[%s])",
                        handle,
                        ut_control_GetMapString(bool_mapTable, mode));
            ret = dsEnableSurroundDecoder(handle, mode);
            if(ret != dsERR_NONE) {
                UT_LOG_ERROR("Failed dsEnableSurroundDecoder(handle:[0x%0X], mode:[%s]) dsError_t:[%s]",
                              handle,
                              ut_control_GetMapString(bool_mapTable, mode),
                              ut_control_GetMapString(dsError_mapTable, ret));
                break;
            }
            else {
                UT_LOG_INFO("Result dsEnableSurroundDecoder(handle:[0x%0X], mode:[%s]) dsError_t:[%s]",
                             handle,
                             ut_control_GetMapString(bool_mapTable, mode),
                             ut_control_GetMapString(dsError_mapTable, ret));
            }

            UT_LOG_INFO("Calling dsIsSurroundDecoderEnabled(handle:[0x%0X], mode:[])", handle);
            ret = dsIsSurroundDecoderEnabled(handle, &mode_g);
            if(ret != dsERR_NONE || mode != mode_g) {
                UT_LOG_ERROR("Failed dsIsSurroundDecoderEnabled(handle:[0x%0X], mode:[%s]) dsError_t:[%s]",
                              handle,
                              ut_control_GetMapString(bool_mapTable, mode_g),
                              ut_control_GetMapString(dsError_mapTable, ret));
            }
            else {
                UT_LOG_INFO("Result dsIsSurroundDecoderEnabled(handle:[0x%0X], mode:[%s]) dsError_t:[%s]",
                             handle,
                             ut_control_GetMapString(bool_mapTable, mode_g),
                             ut_control_GetMapString(dsError_mapTable, ret));
            }

            break;
        }
        case 7: //DRCMode
        {
            int32_t mode = 0, mode_g = 0;

            if(!(gDSAudioPortConfiguration[port].ms12_capabilites & 0x40)) {
                UT_LOG_WARNING("%s Port doesn't Support DRCMode",
                               ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid));
                break;
            }

            printf("\nSelect DRC Mode[0: DRC Line Mode, 1: DRC RF Mode]: ");
            scanf("%d", &mode);
            if(mode < 0 || mode > 1) {
                printf("Invalid DRC Mode\n");
                break;
            }

            UT_LOG_INFO("Calling dsSetDRCMode(handle:[0x%0X], mode:[%d])",
                         handle, mode);
            ret = dsSetDRCMode(handle, mode);
            if(ret != dsERR_NONE) {
                UT_LOG_ERROR("Failed dsSetDRCMode(handle:[0x%0X], mode:[%d]) dsError_t:[%s]",
                                handle, mode,
                                ut_control_GetMapString(dsError_mapTable, ret));
                break;
            }
            else {
                UT_LOG_INFO("Result dsSetDRCMode(handle:[0x%0X], mode:[%d]) dsError_t:[%s]",
                                handle, mode,
                                ut_control_GetMapString(dsError_mapTable, ret));
            }

            UT_LOG_INFO("Calling dsGetDRCMode(handle:[0x%0X], mode:[])", handle);
            ret = dsGetDRCMode(handle, &mode_g);
            if(ret != dsERR_NONE || mode_g != mode) {
                UT_LOG_ERROR("Failed dsGetDRCMode(handle:[0x%0X], mode:[%d]) dsError_t:[%s]",
                             handle, mode_g,
                             ut_control_GetMapString(dsError_mapTable, ret));
            }
            else {
                UT_LOG_INFO("Result dsGetDRCMode(handle:[0x%0X], mode:[%d]) dsError_t:[%s]",
                             handle, mode_g,
                             ut_control_GetMapString(dsError_mapTable, ret));
            }
            break;
        }
        case 8: //SurroundVirtualizer
        {
            dsSurroundVirtualizer_t surround_virtualize   = {0};
            dsSurroundVirtualizer_t surround_virtualize_g = {0};

            if(!(gDSAudioPortConfiguration[port].ms12_capabilites & 0x80)) {
                UT_LOG_WARNING("%s Port doesn't Support SurroundVirtualizer",
                               ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid));
                break;
            }

            printf("\nSelect SurroundVirtualizer Mode[0:Off, 1:On, 2:Auto]: ");
            scanf("%d", &surround_virtualize.mode);
            if(surround_virtualize.mode < 0 || surround_virtualize.mode > 2) {
                printf("Invalid SurroundVirtualizer Mode\n");
                break;
            }
            printf("\nSelect SurroundVirtualizer Boost[0-96]: ");
            scanf("%d", &surround_virtualize.boost);
            if(surround_virtualize.boost < 0 || surround_virtualize.boost > 10) {
                printf("Invalid Volumeleveller boost\n");
                break;
            }

            UT_LOG_INFO("Calling dsSetSurroundVirtualizer(handle:[0x%0X], virtualizer:[mode:%d, boost:%d])",
                         handle, surround_virtualize.mode, surround_virtualize.boost);
            ret = dsSetSurroundVirtualizer(handle, surround_virtualize);
            if(ret != dsERR_NONE) {
                UT_LOG_ERROR("Failed dsSetSurroundVirtualizer(handle:[0x%0X], virtualizer:[mode:%d, boost:%d]) dsError_t:[%s]",
                              handle, surround_virtualize.mode, surround_virtualize.boost,
                              ut_control_GetMapString(dsError_mapTable, ret));
                break;
            }
            else {
                UT_LOG_INFO("Result dsSetSurroundVirtualizer(handle:[0x%0X], virtualizer:[mode:%d, boost:%d]) dsError_t:[%s]",
                             handle, surround_virtualize.mode, surround_virtualize.boost,
                             ut_control_GetMapString(dsError_mapTable, ret));
            }

            UT_LOG_INFO("Calling dsGetSurroundVirtualizer(handle:[0x%0X], virtualizer:[])",
                         handle, surround_virtualize.mode, surround_virtualize.boost);
            ret = dsGetSurroundVirtualizer(handle, &surround_virtualize_g);
            if(ret != dsERR_NONE || surround_virtualize_g.mode != surround_virtualize.mode || surround_virtualize_g.boost != surround_virtualize.boost) {
                UT_LOG_ERROR("Failed dsGetSurroundVirtualizer(handle:[0x%0X], virtualizer:[mode:%d, boost:%d]) dsError_t:[%s]",
                              handle, surround_virtualize_g.mode, surround_virtualize_g.boost,
                              ut_control_GetMapString(dsError_mapTable, ret));
            }
            else {
                UT_LOG_INFO("Result dsGetSurroundVirtualizer(handle:[0x%0X], virtualizer:[mode:%d, boost:%d]) dsError_t:[%s]",
                             handle, surround_virtualize_g.mode, surround_virtualize_g.boost,
                             ut_control_GetMapString(dsError_mapTable, ret));
            }
            break;
        }
        case 9: //MISteering
        {
            bool mode = false, mode_g = false;

            if(!(gDSAudioPortConfiguration[port].ms12_capabilites & 0x100)) {
                UT_LOG_WARNING("%s Port doesn't Support MISteering",
                               ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid));
                break;
            }

            printf("\nMI Steering[1:Enable, 2:Disable]: ");
            scanf("%d", &choice);
            if(choice < 1 || choice > 2) {
                printf("Invalid choice\n");
                break;
            }

            mode = (choice == 1) ? true : false;

            UT_LOG_INFO("Calling dsSetMISteering(handle:[0x%0X], mode:[%s])",
                        handle,
                        ut_control_GetMapString(bool_mapTable, mode));
            ret = dsSetMISteering(handle, mode);
            if(ret != dsERR_NONE) {
                UT_LOG_ERROR("Failed dsSetMISteering(handle:[0x%0X], mode:[%s]) dsError_t:[%s]",
                              handle,
                              ut_control_GetMapString(bool_mapTable, mode),
                              ut_control_GetMapString(dsError_mapTable, ret));
                break;
            }
            else {
                UT_LOG_INFO("Result dsSetMISteering(handle:[0x%0X], mode:[%s]) dsError_t:[%s]",
                                handle,
                                ut_control_GetMapString(bool_mapTable, mode),
                                ut_control_GetMapString(dsError_mapTable, ret));
            }

            UT_LOG_INFO("Calling dsGetMISteering(handle:[0x%0X], mode:[])", handle);
            ret = dsGetMISteering(handle, &mode_g);
            if(ret != dsERR_NONE || mode != mode_g) {
                UT_LOG_ERROR("Failed dsGetMISteering(handle:[0x%0X], mode:[%s]) dsError_t:[%s]",
                              handle,
                              ut_control_GetMapString(bool_mapTable, mode_g),
                              ut_control_GetMapString(dsError_mapTable, ret));
            }
            else {
                UT_LOG_INFO("Result dsGetMISteering(handle:[0x%0X], *mode:[%s]) dsError_t:[%s]",
                             handle,
                             ut_control_GetMapString(bool_mapTable, mode_g),
                             ut_control_GetMapString(dsError_mapTable, ret));
            }

            break;
        }
        case 10: //GraphicEqualizer
        {
            int32_t mode = 0, mode_g = 0;

            if(!(gDSAudioPortConfiguration[port].ms12_capabilites & 0x200)) {
                UT_LOG_WARNING("%s Port doesn't Support GraphicEqualizer",
                               ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid));
                break;
            }

            printf("\nSelect GraphicEqualizer Mode[0: OFF, 1: EQ Open, 2: EQ Rich, 3: EQ Focused]: ");
            scanf("%d", &mode);
            if(mode < 0 || mode > 3) {
                printf("Invalid GraphicEqualizer Mode\n");
                break;
            }

            UT_LOG_INFO("Calling dsSetGraphicEqualizerMode(handle:[0x%0X], mode:[%d])",
                        handle, mode);
            ret = dsSetGraphicEqualizerMode(handle, mode);
            if(ret != dsERR_NONE) {
                UT_LOG_ERROR("Failed dsSetGraphicEqualizerMode(handle:[0x%0X], mode:[%d]) dsError_t:[%s]",
                              handle, mode,
                              ut_control_GetMapString(dsError_mapTable, ret));
                break;
            }
            else {
                UT_LOG_INFO("Result dsSetGraphicEqualizerMode(handle:[0x%0X], mode:[%d]) dsError_t:[%s]",
                             handle, mode,
                             ut_control_GetMapString(dsError_mapTable, ret));
            }

            UT_LOG_INFO("Calling dsGetGraphicEqualizerMode(handle:[0x%0X], mode:[])", handle);
            ret = dsGetGraphicEqualizerMode(handle, &mode_g);
            if(ret != dsERR_NONE || mode != mode_g) {
                UT_LOG_ERROR("Failed dsGetGraphicEqualizerMode(handle:[0x%0X], mode:[%d]) dsError_t:[%s]",
                              handle, mode_g,
                              ut_control_GetMapString(dsError_mapTable, ret));
            }
            else {
                UT_LOG_INFO("Result dsGetGraphicEqualizerMode(handle:[0x%0X], mode:[%d]) dsError_t:[%s]",
                             handle, mode_g,
                             ut_control_GetMapString(dsError_mapTable, ret));
            }
            break;
        }
        case 11: //LEConfig
        {
            bool mode = false, mode_g = false;

            if(!(gDSAudioPortConfiguration[port].ms12_capabilites & 0x400)) {
                UT_LOG_WARNING("%s Port doesn't Support LEConfig",
                               ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid));
                break;
            }

            printf("\nLE Configuration[1:Enable, 2:Disable]: ");
            scanf("%d", &choice);
            if(choice < 1 || choice > 2) {
                printf("Invalid choice\n");
                break;
            }

            mode = (choice == 1) ? true : false;

            UT_LOG_INFO("Calling dsEnableSurroundDecoder(handle:[0x%0X], mode:[%s])",
                        handle,
                        ut_control_GetMapString(bool_mapTable, mode));
            ret = dsEnableLEConfig(handle, mode);
            if(ret != dsERR_NONE) {
                UT_LOG_ERROR("Failed dsEnableLEConfig(handle:[0x%0X], mode:[%s]) dsError_t:[%s]",
                              handle,
                              ut_control_GetMapString(bool_mapTable, mode),
                              ut_control_GetMapString(dsError_mapTable, ret));
                break;
            }
            else {
                UT_LOG_INFO("Result dsEnableLEConfig(handle:[0x%0X], mode:[%s]) dsError_t:[%s]",
                             handle,
                             ut_control_GetMapString(bool_mapTable, mode),
                             ut_control_GetMapString(dsError_mapTable, ret));
            }

            UT_LOG_INFO("Calling dsGetLEConfig(handle:[0x%0X], mode:[])", handle);
            ret = dsGetLEConfig(handle, &mode_g);
            if(ret != dsERR_NONE || mode != mode_g) {
                UT_LOG_ERROR("Failed dsGetLEConfig(handle:[0x%0X], mode:[%s]) dsError_t:[%s]",
                              handle,
                              ut_control_GetMapString(bool_mapTable, mode_g),
                              ut_control_GetMapString(dsError_mapTable, ret));
            }
            else {
                UT_LOG_INFO("Result dsGetLEConfig(handle:[0x%0X], mode:[%s]) dsError_t:[%s]",
                             handle,
                             ut_control_GetMapString(bool_mapTable, mode_g),
                             ut_control_GetMapString(dsError_mapTable, ret));
            }
            break;
        }
        default:
            printf("Invalid DAP Feature Choice\n");
    }

    readAndDiscardRestOfLine(stdin);
exit:
    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test sets output mode.
*
* This test function sets output mode.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 007@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [dsAudio_L3_Low-Level_TestSpecification.md](../docs/pages/ds-audio_L3_Low-Level_TestSpecification.md)
*/
void test_l3_dsAudio_stereo_mode(void)
{
    gTestID = 7;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret   = dsERR_NONE;
    int32_t count   = 0;
    int32_t mode    = 0;
    int32_t mode_g  = 0;
    int32_t choice  = -1;
    intptr_t handle = (intptr_t)NULL;
    bool enabled    = false;
    dsAudioPortType_t port = dsAUDIOPORT_TYPE_MAX;
    int32_t enable_port[DS_AUDIO_MAX_PORTS] = {0};

    printf("\nSelect dsAudio Port to Set Output Mode\n");
    printf("----------------------------------------------------------\n");
    printf("\t#  %-30s%s\n\n","Audio Port", "Index");
    for(int32_t i = 0; i < gDSAudioNumberOfPorts; i++) {
        ret = dsGetAudioPort(gDSAudioPortConfiguration[i].typeid, gDSAudioPortConfiguration[i].index, &handle);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed to get the port handle for %s", gDSAudioPortConfiguration[i].port_name);
            continue;
        }

        ret = dsIsAudioPortEnabled(handle, &enabled);
        if(enabled == true) {
            enable_port[count] = i;
            printf("\t%d.  %-30s%-2d\n", count+1,
                     ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[i].typeid),
                     gDSAudioPortConfiguration[i].index);
            count++;
        }
    }
    printf("----------------------------------------------------------\n");
    if(count == 0) {
        printf("\nNo Ports Enabled\n");
        goto exit;
    }

    printf("\nSelect dsAudio Port: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);
    if(choice < 1 || choice > count) {
        printf("Invalid Port choice\n");
        goto exit;
    }

    port = enable_port[choice - 1];

    UT_LOG_INFO("Calling dsGetAudioPort(type:[%s], index:[%d], handle:[])",
                 ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                 gDSAudioPortConfiguration[port].index);
    ret = dsGetAudioPort(gDSAudioPortConfiguration[port].typeid, gDSAudioPortConfiguration[port].index, &handle);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                      ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                      gDSAudioPortConfiguration[port].index,
                      handle,
                      ut_control_GetMapString(dsError_mapTable, ret));
        goto exit;
    }
    else {
        UT_LOG_INFO("Result dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                     ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                     gDSAudioPortConfiguration[port].index,
                     handle,
                     ut_control_GetMapString(dsError_mapTable, ret));
    }

    printf("\nStereo Mode\n");
    printf("----------------------------------------------------------\n");
    printf("\t#  %-20s\n\n","Stereo Mode");
    for(int32_t i = dsAUDIO_STEREO_MONO; i < dsAUDIO_STEREO_MAX; i++) {
        printf("\t%d.  %-30s\n", i,
                     ut_control_GetMapString(dsAudioStereoMode_mapTable, i));
    }
    printf("----------------------------------------------------------\n");

    printf("\nSelect Stereo Mode: ");
    scanf("%d", &mode);
    readAndDiscardRestOfLine(stdin);
    if(mode < dsAUDIO_STEREO_MONO || mode > dsAUDIO_STEREO_MAX) {
        printf("Invalid Mode choice\n");
        goto exit;
    }

    UT_LOG_INFO("Calling dsSetStereoMode(handle:[0x%0X], mode:[%s])",
                 handle,
                 ut_control_GetMapString(dsAudioStereoMode_mapTable, mode));
    ret = dsSetStereoMode(handle, (dsAudioStereoMode_t)mode);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsSetStereoMode(handle:[0x%0X], mode:[%s]) dsError_t:[%s]",
                      handle, ut_control_GetMapString(dsAudioStereoMode_mapTable, mode),
                      ut_control_GetMapString(dsError_mapTable, ret));
        goto exit;
    }
    else {
        UT_LOG_INFO("Result dsSetStereoMode(handle:[0x%0X], mode:[%s]) dsError_t:[%s]",
                        handle, ut_control_GetMapString(dsAudioStereoMode_mapTable, mode),
                        ut_control_GetMapString(dsError_mapTable, ret));
    }

    UT_LOG_INFO("Calling dsGetStereoMode(handle:[0x%0X], mode:[])", handle);
    ret = dsGetStereoMode(handle, (dsAudioStereoMode_t *)&mode_g);
    if(ret != dsERR_NONE || mode != mode_g) {
        UT_LOG_ERROR("Failed dsGetStereoMode(handle:[0x%0X], mode:[%s]) dsError_t:[%s]",
                      handle, ut_control_GetMapString(dsAudioStereoMode_mapTable, mode_g),
                      ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsGetStereoMode(handle:[0x%0X], mode:[%s]) dsError_t:[%s]",
                        handle, ut_control_GetMapString(dsAudioStereoMode_mapTable, mode_g),
                        ut_control_GetMapString(dsError_mapTable, ret));
    }
exit:
    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test sets auto output mode.
*
* This test function sets auto output mode.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 008@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [dsAudio_L3_Low-Level_TestSpecification.md](../docs/pages/ds-audio_L3_Low-Level_TestSpecification.md)
*/
void test_l3_dsAudio_stereo_auto_mode(void)
{
    gTestID = 8;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret   = dsERR_NONE;
    int32_t count   = 0;
    int32_t mode    = 0;
    int32_t mode_g  = 0;
    int32_t choice  = -1;
    intptr_t handle = (intptr_t)NULL;
    bool enabled    = false;
    int32_t enable_port[DS_AUDIO_MAX_PORTS] = {0};
    dsAudioPortType_t port = dsAUDIOPORT_TYPE_MAX;

    printf("\nSelect dsAudio Port to Set Output Auto Mode\n");
    printf("----------------------------------------------------------\n");
    printf("\t#  %-30s%s\n\n","Audio Port", "Index");
    for(int32_t i = 0; i < gDSAudioNumberOfPorts; i++) {
        ret = dsGetAudioPort(gDSAudioPortConfiguration[i].typeid, gDSAudioPortConfiguration[i].index, &handle);
        if(ret != dsERR_NONE) {
             UT_LOG_ERROR("Failed dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                          ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[i].typeid),
                          gDSAudioPortConfiguration[i].index,
                          handle,
                          ut_control_GetMapString(dsError_mapTable, ret));
            continue;
        }

        ret = dsIsAudioPortEnabled(handle, &enabled);
        if(enabled == true) {
            enable_port[count] = i;
            printf("\t%d.  %-30s%-2d\n", count+1,
                     ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[i].typeid),
                     gDSAudioPortConfiguration[i].index);
            count++;
        }
    }
    printf("----------------------------------------------------------\n");
    if(count == 0) {
        printf("\nNo Ports Enabled\n");
        return;
    }

    printf("\nSelect dsAudio Port: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);
    if(choice < 1 || choice > count) {
        printf("Invalid Port choice\n");
        goto exit;
    }

    port = enable_port[choice - 1];

    UT_LOG_INFO("Calling dsGetAudioPort(type:[%s], index:[%d], handle:[])",
                 ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                 gDSAudioPortConfiguration[port].index);
    ret = dsGetAudioPort(gDSAudioPortConfiguration[port].typeid, gDSAudioPortConfiguration[port].index, &handle);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                      ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                      gDSAudioPortConfiguration[port].index,
                      handle,
                      ut_control_GetMapString(dsError_mapTable, ret));
        goto exit;
    }
    else {
        UT_LOG_INFO("Result dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                     ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                     gDSAudioPortConfiguration[port].index,
                     handle,
                     ut_control_GetMapString(dsError_mapTable, ret));
    }

    printf("\nStereo Auto Mode[1:Enable, 2:Disable]: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);
    if(choice < 1 || choice > 2) {
        printf("Invalid choice\n");
        goto exit;
    }

    mode = (choice == 1) ? true : false;

    UT_LOG_INFO("Calling dsSetStereoAuto(handle:[0x%0X], autoMode:[%s])",
                handle,
                ut_control_GetMapString(bool_mapTable, mode));
    ret = dsSetStereoAuto(handle, mode);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsSetStereoAuto(handle:[0x%0X], autoMode:[%s]) dsError_t:[%s]",
                        handle, ut_control_GetMapString(bool_mapTable, mode),
                        ut_control_GetMapString(dsError_mapTable, ret));
        goto exit;
    }
    else {
        UT_LOG_INFO("Result dsSetStereoAuto(handle:[0x%0X], autoMode:[%s]) dsError_t:[%s]",
                        handle, ut_control_GetMapString(bool_mapTable, mode),
                        ut_control_GetMapString(dsError_mapTable, ret));
    }

    UT_LOG_INFO("Calling dsGetStereoAuto(handle:[0x%0X], autoMode:[])",
                handle);
    ret = dsGetStereoAuto(handle, &mode_g);
    if(ret != dsERR_NONE || mode_g != mode) {
        UT_LOG_ERROR("Failed dsGetStereoAuto(handle:[0x%0X], autoMode:[%s]) dsError_t:[%s]",
                        handle, ut_control_GetMapString(bool_mapTable, mode_g),
                        ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsGetStereoAuto(handle:[0x%0X], autoMode:[%s]) dsError_t:[%s]",
                        handle, ut_control_GetMapString(bool_mapTable, mode_g),
                        ut_control_GetMapString(dsError_mapTable, ret));
    }

exit:
    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test sets the audio levels.
*
* This test function sets the audio levels.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 009@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [dsAudio_L3_Low-Level_TestSpecification.md](../docs/pages/ds-audio_L3_Low-Level_TestSpecification.md)
*/
void test_l3_dsAudio_set_audio_level(void)
{
    gTestID = 9;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret      = dsERR_NONE;
    int32_t count      = 0;
    float gain_level   = 0;
    float gain_level_g = 0;
    int32_t choice     = -1;
    intptr_t handle    = (intptr_t)NULL;
    bool enabled       = false;
    int32_t enable_port[DS_AUDIO_MAX_PORTS] = {0};
    dsAudioPortType_t port = dsAUDIOPORT_TYPE_MAX;

    printf("\nSelect dsAudio Port to Apply Gain\n");
    printf("----------------------------------------------------------\n");
    printf("\t#  %-30s%s\n\n","Audio Port", "Index");
    for(int32_t i = 0; i < gDSAudioNumberOfPorts; i++) {
        ret = dsGetAudioPort(gDSAudioPortConfiguration[i].typeid, gDSAudioPortConfiguration[i].index, &handle);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                          ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[i].typeid),
                          gDSAudioPortConfiguration[i].index,
                          handle,
                          ut_control_GetMapString(dsError_mapTable, ret));
            continue;
        }

        ret = dsIsAudioPortEnabled(handle, &enabled);
        if(enabled == true) {
            enable_port[count] = i;
            printf("\t%d.  %-30s%-2d\n", count+1,
                     ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[i].typeid),
                     gDSAudioPortConfiguration[i].index);
            count++;
        }
    }
    printf("----------------------------------------------------------\n");
    if(count == 0) {
        printf("\nNo Ports Enabled\n");
        return;
    }

    printf("\nSelect dsAudio Port: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);
    if(choice < 1 || choice > count) {
        printf("Invalid Port choice\n");
        return;
    }

    port = enable_port[choice - 1];

    UT_LOG_INFO("Calling dsGetAudioPort(type:[%s], index:[%d], handle:[])",
                 ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                 gDSAudioPortConfiguration[port].index);
    ret = dsGetAudioPort(gDSAudioPortConfiguration[port].typeid, gDSAudioPortConfiguration[port].index, &handle);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                      ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                      gDSAudioPortConfiguration[port].index,
                      handle,
                      ut_control_GetMapString(dsError_mapTable, ret));
        goto exit;
    }
    else {
        UT_LOG_INFO("Result dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                     ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                     gDSAudioPortConfiguration[port].index,
                     handle,
                     ut_control_GetMapString(dsError_mapTable, ret));
    }

    printf("\nEnter Gain Level[0.0 to 100.0]: ");
    scanf("%f", &gain_level);
    readAndDiscardRestOfLine(stdin);
    if(gain_level < 0 || gain_level > 100) {
        printf("Invalid Audio Gain Level\n");
        goto exit;
    }

    UT_LOG_INFO("Calling dsSetAudioLevel(handle:[0x%0X], level:[%f])",
                 handle, gain_level);
    ret = dsSetAudioLevel(handle, gain_level);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsSetAudioLevel(handle:[0x%0X], level:[%f]) dsError_t:[%s]",
                      handle, gain_level,
                      ut_control_GetMapString(dsError_mapTable, ret));
        goto exit;
    }
    else {
        UT_LOG_INFO("Result dsSetAudioLevel(handle:[0x%0X], level:[%f]) dsError_t:[%s]",
                     handle, gain_level,
                     ut_control_GetMapString(dsError_mapTable, ret));
    }

    UT_LOG_INFO("Calling dsGetAudioLevel(handle:[0x%0X], level:[])", handle);
    ret = dsGetAudioLevel(handle, &gain_level_g);
    if(ret != dsERR_NONE || gain_level_g != gain_level) {
        UT_LOG_ERROR("Failed dsGetAudioLevel(handle:[0x%0X], level:[%f]) dsError_t:[%s]",
                      handle, gain_level_g,
                      ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsGetAudioLevel(handle:[0x%0X], level:[%f]) dsError_t:[%s]",
                     handle, gain_level_g,
                     ut_control_GetMapString(dsError_mapTable, ret));
    }

exit:
    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test sets the audio gain for SPEAKER.
*
* This test function sets the audio levels.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 009@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [dsAudio_L3_Low-Level_TestSpecification.md](../docs/pages/ds-audio_L3_Low-Level_TestSpecification.md)
*/
void test_l3_dsAudio_set_audio_gain(void)
{
    gTestID = 9;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret   = dsERR_NONE;
    intptr_t handle = (intptr_t)NULL;
    bool enabled    = false;
    float gain      = 0.0;
    float gain_g    = 0.0;

    for(int32_t i = 0; i < gDSAudioNumberOfPorts; i++) {
        if(gDSAudioPortConfiguration[i].typeid != dsAUDIOPORT_TYPE_SPEAKER) {
            continue;
        }

        UT_LOG_INFO("Calling dsGetAudioPort(type:[%s], index:[%d], handle:[])",
                    ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[i].typeid),
                    gDSAudioPortConfiguration[i].index);
        ret = dsGetAudioPort(gDSAudioPortConfiguration[i].typeid, gDSAudioPortConfiguration[i].index, &handle);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                        ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[i].typeid),
                        gDSAudioPortConfiguration[i].index,
                        handle,
                        ut_control_GetMapString(dsError_mapTable, ret));
            goto exit;
        }
        else {
            UT_LOG_INFO("Result dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                        ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[i].typeid),
                        gDSAudioPortConfiguration[i].index,
                        handle,
                        ut_control_GetMapString(dsError_mapTable, ret));
        }

        UT_LOG_INFO("Calling dsIsAudioPortEnabled(handle:[0x%0X], enabled:[])",
                     handle);
        ret = dsIsAudioPortEnabled(handle, &enabled);
        if (ret != dsERR_NONE || !enabled) {
            UT_LOG_ERROR("Failed dsIsAudioPortEnabled(handle:[0x%0X], enabled:[%s]) dsError_t:[%s]",
                          handle, ut_control_GetMapString(bool_mapTable, enabled),
                          ut_control_GetMapString(dsError_mapTable, ret));
            goto exit;
        }
        else {
            UT_LOG_INFO("Result dsIsAudioPortEnabled(handle:[0x%0X], enabled:[%s]) dsError_t:[%s]",
                         handle, ut_control_GetMapString(bool_mapTable, enabled),
                         ut_control_GetMapString(dsError_mapTable, ret));
        }
        break;
    }

    printf("\nEnter Gain[-2080.0 to 480.0]: ");
    scanf("%f", &gain);
    readAndDiscardRestOfLine(stdin);

    if(gain < -2080 || gain > 480) {
        printf("Invalid Audio Gain value\n");
        goto exit;
    }

    UT_LOG_INFO("Calling dsSetAudioGain(handle:[0x%0X], gain:[%f])",
                 handle, gain);
    ret = dsSetAudioGain(handle, gain);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsSetAudioGain(handle:[0x%0X], gain:[%f]) dsError_t:[%s]",
                      handle, gain,
                      ut_control_GetMapString(dsError_mapTable, ret));
        goto exit;
    }
    else {
        UT_LOG_INFO("Result dsSetAudioGain(handle:[0x%0X], gain:[%f]) dsError_t:[%s]",
                        handle, gain,
                        ut_control_GetMapString(dsError_mapTable, ret));
    }

    UT_LOG_INFO("Calling dsGetAudioGain(handle:[0x%0X], gain:[])",
                 handle);
    ret = dsGetAudioGain(handle, &gain_g);
    if(ret != dsERR_NONE || gain != gain_g) {
        UT_LOG_ERROR("Failed dsGetAudioGain(handle:[0x%0X], gain:[%f]) dsError_t:[%s]",
                      handle, gain_g,
                      ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsGetAudioGain(handle:[0x%0X], gain:[%f]) dsError_t:[%s]",
                        handle, gain_g,
                        ut_control_GetMapString(dsError_mapTable, ret));
    }
exit:
    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test Mutes or UnMutes the Audio.
*
* This test function Mutes or UnMutes the Audio.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 010@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [dsAudio_L3_Low-Level_TestSpecification.md](../docs/pages/ds-audio_L3_Low-Level_TestSpecification.md)
*/
void test_l3_dsAudio_set_audio_mute(void)
{
    gTestID = 10;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret   = dsERR_NONE;
    int32_t choice  = -1;
    int32_t count   = 0;
    bool mute       = false;
    bool mute_g     = false;
    intptr_t handle = (intptr_t)NULL;
    bool enabled    = false;
    int32_t enable_port[DS_AUDIO_MAX_PORTS] = {0};
    dsAudioPortType_t port = dsAUDIOPORT_TYPE_MAX;

    printf("\nSelect dsAudio Port to Apply Gain\n");
    printf("----------------------------------------------------------\n");
    printf("\t#  %-30s%s\n\n","Audio Port", "Index");
    for(int32_t i = 0; i < gDSAudioNumberOfPorts; i++) {
        ret = dsGetAudioPort(gDSAudioPortConfiguration[i].typeid, gDSAudioPortConfiguration[i].index, &handle);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                          ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[i].typeid),
                          gDSAudioPortConfiguration[i].index,
                          handle,
                          ut_control_GetMapString(dsError_mapTable, ret));
            continue;
        }

        ret = dsIsAudioPortEnabled(handle, &enabled);
        if(enabled == true) {
            enable_port[count] = i;
            printf("\t%d.  %-30s%-2d\n", count+1,
                     ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[i].typeid),
                     gDSAudioPortConfiguration[i].index);
            count++;
        }
    }
    printf("----------------------------------------------------------\n");
    if(count == 0) {
        printf("\nNo Ports Enabled\n");
        goto exit;;
    }

    printf("\nSelect dsAudio Port: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);
    if(choice < 1 || choice > count) {
        printf("Invalid Port choice\n");
        goto exit;
    }

    port = enable_port[choice - 1];

    UT_LOG_INFO("Calling dsGetAudioPort(type:[%s], index:[%d], handle:[])",
                 ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                 gDSAudioPortConfiguration[port].index);
    ret = dsGetAudioPort(gDSAudioPortConfiguration[port].typeid, gDSAudioPortConfiguration[port].index, &handle);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                      ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                      gDSAudioPortConfiguration[port].index,
                      handle,
                      ut_control_GetMapString(dsError_mapTable, ret));
        goto exit;
    }
    else {
        UT_LOG_INFO("Result dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                     ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                     gDSAudioPortConfiguration[port].index,
                     handle,
                     ut_control_GetMapString(dsError_mapTable, ret));
    }

    printf("\nAudio Mute/UnMute[1:Mute, 2:UnMute]: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);
    if(choice < 1 || choice > 2) {
        printf("Invalid Mute choice\n");
        goto exit;
    }

    mute = (choice == 1) ? true : false;

    UT_LOG_INFO("Calling dsSetAudioMute(handle:[0x%0X], mute:[%s])",
                handle,
                ut_control_GetMapString(bool_mapTable, mute));
    ret = dsSetAudioMute(handle, mute);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsSetAudioMute(handle:[0x%0X], mute:[%s]) dsError_t:[%s]",
                        handle,
                        ut_control_GetMapString(bool_mapTable, mute),
                        ut_control_GetMapString(dsError_mapTable, ret));
        goto exit;
    }
    else {
        UT_LOG_INFO("Result dsSetAudioMute(handle:[0x%0X], mute:[%s]) dsError_t:[%s]",
                        handle,
                        ut_control_GetMapString(bool_mapTable, mute),
                        ut_control_GetMapString(dsError_mapTable, ret));
    }

    UT_LOG_INFO("Calling dsIsAudioMute(handle:[0x%0X], muted:[])", handle);
    ret = dsIsAudioMute(handle, &mute_g);
    if(ret != dsERR_NONE || mute != mute_g) {
        UT_LOG_ERROR("Failed dsIsAudioMute(handle:[0x%0X], muted:[%s]) dsError_t:[%s]",
                        handle,
                        ut_control_GetMapString(bool_mapTable, mute_g),
                        ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsIsAudioMute(handle:[0x%0X], muted:[%s]) dsError_t:[%s]",
                        handle,
                        ut_control_GetMapString(bool_mapTable, mute_g),
                        ut_control_GetMapString(dsError_mapTable, ret));
    }

exit:
    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test sets audio delay.
*
* This test function sets audio delay.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 011@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [dsAudio_L3_Low-Level_TestSpecification.md](../docs/pages/ds-audio_L3_Low-Level_TestSpecification.md)
*/
void test_l3_dsAudio_set_audio_delay(void)
{
    gTestID = 11;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret           = dsERR_NONE;
    int32_t choice          = -1;
    intptr_t handle         = (intptr_t)NULL;
    bool enabled            = false;
    int32_t count           = 0;
    uint32_t audioDelayMs   = 0;
    uint32_t audioDelayMs_g = 0;
    int32_t enable_port[DS_AUDIO_MAX_PORTS] = {0};
    dsAudioPortType_t port = dsAUDIOPORT_TYPE_MAX;

    printf("\nSelect dsAudio Port to Apply Delay\n");
    printf("----------------------------------------------------------\n");
    printf("\t#  %-30s%s\n\n","Audio Port", "Index");
    for(int32_t i = 0; i < gDSAudioNumberOfPorts; i++) {
        if(gDSAudioPortConfiguration[i].typeid != dsAUDIOPORT_TYPE_HDMI &&
           gDSAudioPortConfiguration[i].typeid != dsAUDIOPORT_TYPE_HDMI_ARC &&
           gDSAudioPortConfiguration[i].typeid != dsAUDIOPORT_TYPE_SPDIF) {
            continue;
        }
        ret = dsGetAudioPort(gDSAudioPortConfiguration[i].typeid, gDSAudioPortConfiguration[i].index, &handle);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                          ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[i].typeid),
                          gDSAudioPortConfiguration[i].index,
                          handle,
                          ut_control_GetMapString(dsError_mapTable, ret));
            continue;
        }

        ret = dsIsAudioPortEnabled(handle, &enabled);
        if(enabled == true) {
            enable_port[count] = i;
            printf("\t%d.  %-30s%-2d\n", count+1,
                     ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[i].typeid),
                     gDSAudioPortConfiguration[i].index);
            count++;
        }
    }
    printf("----------------------------------------------------------\n");
    if(count == 0) {
        printf("\nNo Ports Enabled\n");
        goto exit;
    }

    printf("\nSelect dsAudio Port: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);
    if(choice < 1 || choice > count) {
        printf("Invalid Port choice\n");
        goto exit;
    }

    port = enable_port[choice - 1];

    UT_LOG_INFO("Calling dsGetAudioPort(type:[%s], index:[%d], handle:[])",
                 ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                 gDSAudioPortConfiguration[port].index);
    ret = dsGetAudioPort(gDSAudioPortConfiguration[port].typeid, gDSAudioPortConfiguration[port].index, &handle);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                      ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                      gDSAudioPortConfiguration[port].index,
                      handle,
                      ut_control_GetMapString(dsError_mapTable, ret));
        goto exit;
    }
    else {
        UT_LOG_INFO("Result dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                     ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                     gDSAudioPortConfiguration[port].index,
                     handle,
                     ut_control_GetMapString(dsError_mapTable, ret));
    }

    printf("\nEnter Audio Delay in milli seconds[0 to 200]: ");
    scanf("%d", &audioDelayMs);
    readAndDiscardRestOfLine(stdin);
    if(audioDelayMs < 0 || audioDelayMs > 200) {
        printf("Invalid Audio Delay\n");
        goto exit;
    }

    UT_LOG_INFO("Calling dsSetAudioDelay(handle:[0x%0X], audioDelayMs:[%d])",
                 handle, audioDelayMs);
    ret = dsSetAudioDelay(handle, audioDelayMs);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsSetAudioDelay(handle:[0x%0X], audioDelayMs:[%d]) dsError_t:[%s]",
                      handle, audioDelayMs,
                      ut_control_GetMapString(dsError_mapTable, ret));
        goto exit;
    }
    else {
        UT_LOG_INFO("Result dsSetAudioDelay(handle:[0x%0X], audioDelayMs:[%d]) dsError_t:[%s]",
                     handle, audioDelayMs,
                     ut_control_GetMapString(dsError_mapTable, ret));
    }

    UT_LOG_INFO("Calling dsGetAudioDelay(handle:[0x%0X], audioDelayMs:[%d])",
                 handle, audioDelayMs);
    ret = dsGetAudioDelay(handle, &audioDelayMs_g);
    if(ret != dsERR_NONE || audioDelayMs != audioDelayMs_g) {
        UT_LOG_ERROR("Failed dsGetAudioDelay(handle:[0x%0X], audioDelayMs:[%d]) dsError_t:[%s]",
                      handle, audioDelayMs_g,
                      ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsGetAudioDelay(handle:[0x%0X], audioDelayMs:[%d]) dsError_t:[%s]",
                     handle, audioDelayMs_g,
                     ut_control_GetMapString(dsError_mapTable, ret));
    }

exit:
    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test gets audio format of playback stream.
*
* This test function gets audio format of playback stream.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 012@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [dsAudio_L3_Low-Level_TestSpecification.md](../docs/pages/ds-audio_L3_Low-Level_TestSpecification.md)
*/
void test_l3_dsAudio_get_audio_format(void)
{
    gTestID = 12;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret   = dsERR_NONE;
    int32_t port    = 0;
    intptr_t handle = (intptr_t)NULL;
    dsAudioFormat_t getAudioFormat = dsAUDIO_FORMAT_NONE;

    UT_LOG_INFO("Calling dsGetAudioPort(type:[%s], index:[%d], handle:[])",
                 ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                 gDSAudioPortConfiguration[port].index);
    ret = dsGetAudioPort(gDSAudioPortConfiguration[port].typeid, gDSAudioPortConfiguration[port].index, &handle);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                      ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                      gDSAudioPortConfiguration[port].index,
                      handle,
                      ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                     ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                     gDSAudioPortConfiguration[port].index,
                     handle,
                     ut_control_GetMapString(dsError_mapTable, ret));
    }

    UT_LOG_INFO("Calling dsGetAudioFormat(handle:[0x%0X], audioFormat:[])", handle);
    ret = dsGetAudioFormat(handle, &getAudioFormat);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsGetAudioFormat(handle:[0x%0X], audioFormat:[%s]) dsError_t:[%s]",
                      handle,
                      ut_control_GetMapString(dsAudioFormat_mapTable, getAudioFormat),
                      ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsGetAudioFormat(handle:[0x%0X], audioFormat:[%s]) dsError_t:[%s]",
                     handle,
                     ut_control_GetMapString(dsAudioFormat_mapTable, getAudioFormat),
                     ut_control_GetMapString(dsError_mapTable, ret));
    }

    UT_LOG_INFO("Audio Format: %s, Audio Format from Callback: %s",
                 ut_control_GetMapString(dsAudioFormat_mapTable, getAudioFormat),
                 ut_control_GetMapString(dsAudioFormat_mapTable, gAudioFormat));

    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test sets atmos mode.
*
* This test function sets atmos mode.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 013@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [dsAudio_L3_Low-Level_TestSpecification.md](../docs/pages/ds-audio_L3_Low-Level_TestSpecification.md)
*/
void test_l3_dsAudio_set_atmos_mode(void)
{
    gTestID = 13;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret   = dsERR_NONE;
    int32_t port    = 0;
    intptr_t handle = (intptr_t)NULL;
    int32_t choice  = 0;
    bool enable     = false;

    UT_LOG_INFO("Calling dsGetAudioPort(type:[%s], index:[%d], handle:[])",
                 ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                 gDSAudioPortConfiguration[port].index);
    ret = dsGetAudioPort(gDSAudioPortConfiguration[port].typeid, gDSAudioPortConfiguration[port].index, &handle);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                      ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                      gDSAudioPortConfiguration[port].index,
                      handle,
                      ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                     ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                     gDSAudioPortConfiguration[port].index,
                     handle,
                     ut_control_GetMapString(dsError_mapTable, ret));
    }

    printf("\nEnable/Disable ATMOS Mode[1:Enable, 2:Disable]: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);
    if(choice < 1 || choice > 2) {
        printf("Invalid ATMOS mode\n");
        goto exit;
    }
    enable = (choice == 1) ? true : false;

    UT_LOG_INFO("Calling dsSetAudioAtmosOutputMode(handle:[0x%0X], enable:[%s])",
                handle,
                ut_control_GetMapString(bool_mapTable, enable));
    ret = dsSetAudioAtmosOutputMode(handle, enable);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsSetAudioAtmosOutputMode(handle:[0x%0X], enable:[%s]) dsError_t:[%s]",
                      handle,
                      ut_control_GetMapString(bool_mapTable, enable),
                      ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsSetAudioAtmosOutputMode(handle:[0x%0X], enable:[%s]) dsError_t:[%s]",
                     handle,
                     ut_control_GetMapString(bool_mapTable, enable),
                     ut_control_GetMapString(dsError_mapTable, ret));
    }
exit:
    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test gets connected device atmos capabilities.
*
* This test function gets connected device atmos capabilities.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 014@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [dsAudio_L3_Low-Level_TestSpecification.md](../docs/pages/ds-audio_L3_Low-Level_TestSpecification.md)
*/
void test_l3_dsAudio_getConnected_atmoscaps(void)
{
    gTestID = 14;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret   = dsERR_NONE;
    int32_t choice  = -1;
    intptr_t handle = (intptr_t)NULL;
    bool enabled    = false;
    int32_t count   = 0;
    int32_t enable_port[DS_AUDIO_MAX_PORTS] = {0};
    dsATMOSCapability_t capability = dsAUDIO_ATMOS_NOTSUPPORTED;
    dsAudioPortType_t port         = dsAUDIOPORT_TYPE_MAX;

    printf("\nSelect dsAudio Port to Get ATMOS Capabilities\n");
    printf("----------------------------------------------------------\n");
    printf("\t#  %-30s%s\n\n","Audio Port", "Index");
    for(int32_t i = 0; i < gDSAudioNumberOfPorts; i++) {
        if(gDSAudioPortConfiguration[i].typeid != dsAUDIOPORT_TYPE_HDMI &&
           gDSAudioPortConfiguration[i].typeid != dsAUDIOPORT_TYPE_HDMI_ARC &&
           gDSAudioPortConfiguration[i].typeid != dsAUDIOPORT_TYPE_SPEAKER) {
            continue;
        }
        ret = dsGetAudioPort(gDSAudioPortConfiguration[i].typeid, gDSAudioPortConfiguration[i].index, &handle);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                          ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[i].typeid),
                          gDSAudioPortConfiguration[i].index,
                          handle,
                          ut_control_GetMapString(dsError_mapTable, ret));
            continue;
        }

        ret = dsIsAudioPortEnabled(handle, &enabled);
        if(enabled == true) {
            enable_port[count] = i;
            printf("\t%d.  %-30s%-2d\n", count+1,
                     ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[i].typeid),
                     gDSAudioPortConfiguration[i].index);
            count++;
        }
    }
    printf("----------------------------------------------------------\n");
    if(count == 0) {
        printf("\nNo Ports Enabled\n");
        goto exit;
    }

    printf("\nSelect dsAudio Port: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);
    if(choice < 1 || choice > count) {
        printf("Invalid Port choice\n");
        goto exit;
    }

    port = enable_port[choice - 1];

    UT_LOG_INFO("Calling dsGetAudioPort(type:[%s], index:[%d], handle:[])",
                 ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                 gDSAudioPortConfiguration[port].index);
    ret = dsGetAudioPort(gDSAudioPortConfiguration[port].typeid, gDSAudioPortConfiguration[port].index, &handle);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                      ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                      gDSAudioPortConfiguration[port].index,
                      handle,
                      ut_control_GetMapString(dsError_mapTable, ret));
        goto exit;
    }
    else {
        UT_LOG_INFO("Result dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                     ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                     gDSAudioPortConfiguration[port].index,
                     handle,
                     ut_control_GetMapString(dsError_mapTable, ret));
    }

    UT_LOG_INFO("Calling dsGetSinkDeviceAtmosCapability(handle:[0x%0X], capability:[])", handle);
    ret = dsGetSinkDeviceAtmosCapability(handle, &capability);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsGetSinkDeviceAtmosCapability(handle:[0x%0X], capability:[%s]) dsError_t:[%s]",
                      handle, ut_control_GetMapString(dsATMOSCapability_mapTable, capability),
                      ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsGetSinkDeviceAtmosCapability(handle:[0x%0X], capability:[%s]) dsError_t:[%s]",
                        handle, ut_control_GetMapString(dsATMOSCapability_mapTable, capability),
                        ut_control_GetMapString(dsError_mapTable, ret));
    }

    UT_LOG_INFO("ATMOS Capability of %s: %s, ATMOS change capablity and Status from Callback: %s, Status: %s",
                 ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                 ut_control_GetMapString(dsATMOSCapability_mapTable, capability),
                 ut_control_GetMapString(dsATMOSCapability_mapTable, gAtosCapablity),
                 ut_control_GetMapString(bool_mapTable, gAtmosStatus));

exit:
    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test sets ms12 profiles.
*
* This test function sets ms12 profiles.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 015@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [dsAudio_L3_Low-Level_TestSpecification.md](../docs/pages/ds-audio_L3_Low-Level_TestSpecification.md)
*/
void test_l3_dsAudio_ms12Profile(void)
{
    gTestID = 15;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret   = dsERR_NONE;
    int32_t choice  = -1;
    intptr_t handle = (intptr_t)NULL;
    bool enabled    = false;
    int32_t count   = 0;
    dsMS12AudioProfileList_t profiles = {0};
    char *profileList[DS_AUDIO_MAX_MS12_PROFILES] = {NULL};
    char profile[DS_AUDIO_MAX_MS12_LENGTH]  = {0};
    int32_t enable_port[DS_AUDIO_MAX_PORTS] = {0};
    dsAudioPortType_t port = dsAUDIOPORT_TYPE_MAX;

    printf("\nSelect dsAudio Port to Apply MS12 Profile\n");
    printf("----------------------------------------------------------\n");
    printf("\t#  %-30s%s\n\n","Audio Port", "Index");
    for(int32_t i = 0; i < gDSAudioNumberOfPorts; i++) {
        ret = dsGetAudioPort(gDSAudioPortConfiguration[i].typeid, gDSAudioPortConfiguration[i].index, &handle);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed to get the port handle for %s", gDSAudioPortConfiguration[i].port_name);
            continue;
        }

        ret = dsGetAudioPort(gDSAudioPortConfiguration[i].typeid, gDSAudioPortConfiguration[i].index, &handle);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                          ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[i].typeid),
                          gDSAudioPortConfiguration[i].index,
                          handle,
                          ut_control_GetMapString(dsError_mapTable, ret));
            continue;
        }

        ret = dsIsAudioPortEnabled(handle, &enabled);
        if(enabled == true) {
            enable_port[count] = i;
            printf("\t%d.  %-30s%-2d\n", count+1,
                     ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[i].typeid),
                     gDSAudioPortConfiguration[i].index);
            count++;
        }
    }
    printf("----------------------------------------------------------\n");
    if(count == 0) {
        printf("\nNo Ports Enabled\n");
        goto exit;
    }

    printf("\nSelect dsAudio Port: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);

    if(choice < 1 || choice > count) {
        printf("Invalid Port choice\n");
        goto exit;
    }

    port = enable_port[choice - 1];

    UT_LOG_INFO("Calling dsGetAudioPort(type:[%s], index:[%d], handle:[])",
                 ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                 gDSAudioPortConfiguration[port].index);
    ret = dsGetAudioPort(gDSAudioPortConfiguration[port].typeid, gDSAudioPortConfiguration[port].index, &handle);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                      ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                      gDSAudioPortConfiguration[port].index,
                      handle,
                      ut_control_GetMapString(dsError_mapTable, ret));
        goto exit;
    }
    else {
        UT_LOG_INFO("Result dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                     ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                     gDSAudioPortConfiguration[port].index,
                     handle,
                     ut_control_GetMapString(dsError_mapTable, ret));
    }

    char* token = strtok(profiles.audioProfileList, " - ");
    int32_t i = 0;

    printf("\nMS12 Profile\n");
    printf("----------------------------------------------------------\n");
    printf("\t#  %-20s\n\n","MS12 Profile");
    while (token != NULL) {
        profileList[i] = token;
        printf("\t%d.  %-20s\n", i+1, profileList[i]);
        token = strtok(NULL, " - ");
        i++;
    }
    printf("----------------------------------------------------------\n");

    printf("\nSelect MS12 Profile: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);

    if(choice < 1 || choice > profiles.audioProfileCount) {
        printf("Invalid profile choice\n");
        goto exit;
    }

    UT_LOG_INFO("Calling dsSetMS12AudioProfile(handle:[0x%0X], profile:[%s])",
                 handle, profileList[choice-1]);
    ret = dsSetMS12AudioProfile(handle, profileList[choice-1]);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsSetMS12AudioProfile(handle:[0x%0X], profile:[%s]) dsError_t:[%s]",
                      handle, profileList[choice-1],
                      ut_control_GetMapString(dsError_mapTable, ret));
        goto exit;
    }
    else {
        UT_LOG_INFO("Result dsSetMS12AudioProfile(handle:[0x%0X], profile:[%s]) dsError_t:[%s]",
                     handle, profileList[choice-1],
                     ut_control_GetMapString(dsError_mapTable, ret));
    }

    UT_LOG_INFO("Calling dsGetMS12AudioProfile(handle:[0x%0X], profile:[])", handle);
    ret = dsGetMS12AudioProfile(handle, profile);
    if(ret != dsERR_NONE || strcmp(profile, profileList[choice-1])) {
        UT_LOG_ERROR("Failed dsGetMS12AudioProfile(handle:[0x%0X], profile:[%s]) dsError_t:[%s]",
                      handle, profile,
                      ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsGetMS12AudioProfile(handle:[0x%0X], profile:[%s]) dsError_t:[%s]",
                     handle, profile,
                     ut_control_GetMapString(dsError_mapTable, ret));
    }

exit:
    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test sets associate audio mixing.
*
* This test function sets associate audio mixing.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 016@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [dsAudio_L3_Low-Level_TestSpecification.md](../docs/pages/ds-audio_L3_Low-Level_TestSpecification.md)
*/
void test_l3_dsAudio_set_associate_audio_mixing(void)
{
    gTestID = 16;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret   = dsERR_NONE;
    int32_t port    = 0;
    intptr_t handle = (intptr_t)NULL;
    int32_t choice  = -1;
    bool mixing     = false;
    bool mixing_g   = false;

    UT_LOG_INFO("Calling dsGetAudioPort(type:[%s], index:[%d], handle:[])",
                 ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                 gDSAudioPortConfiguration[port].index);
    ret = dsGetAudioPort(gDSAudioPortConfiguration[port].typeid, gDSAudioPortConfiguration[port].index, &handle);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                      ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                      gDSAudioPortConfiguration[port].index,
                      handle,
                      ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                     ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                     gDSAudioPortConfiguration[port].index,
                     handle,
                     ut_control_GetMapString(dsError_mapTable, ret));
    }

    printf("\nEnable/Disable Associated Audio Mixing[1:Enable, 2:Disable]: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);
    if(choice < 1 || choice > 2) {
        printf("Invalid Associated Audio Mixing mode\n");
        goto exit;
    }
    mixing = (choice == 1) ? true : false;

    UT_LOG_INFO("Calling dsSetAssociatedAudioMixing(handle:[0x%0X], mixing:[%s])",
                handle,
                ut_control_GetMapString(bool_mapTable, mixing));
    ret = dsSetAssociatedAudioMixing(handle, mixing);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsSetAssociatedAudioMixing(handle:[0x%0X], mixing:[%s]) dsError_t:[%s]",
                      handle,
                      ut_control_GetMapString(bool_mapTable, mixing),
                      ut_control_GetMapString(dsError_mapTable, ret));
        goto exit;
    }
    else {
        UT_LOG_INFO("Result dsSetAssociatedAudioMixing(handle:[0x%0X], mixing:[%s]) dsError_t:[%s]",
                     handle,
                     ut_control_GetMapString(bool_mapTable, mixing),
                     ut_control_GetMapString(dsError_mapTable, ret));
    }

    UT_LOG_INFO("Calling dsGetAssociatedAudioMixing(handle:[0x%0X], mixing:[])", handle);
    ret = dsGetAssociatedAudioMixing(handle, &mixing_g);
    if(ret != dsERR_NONE || mixing_g != mixing) {
        UT_LOG_ERROR("Failed dsGetAssociatedAudioMixing(handle:[0x%0X], mixing:[%s]) dsError_t:[%s]",
                      handle,
                      ut_control_GetMapString(bool_mapTable, mixing_g),
                      ut_control_GetMapString(dsError_mapTable, ret));
        goto exit;
    }
    else {
        UT_LOG_INFO("Result dsGetAssociatedAudioMixing(handle:[0x%0X], mixing:[%s]) dsError_t:[%s]",
                     handle,
                     ut_control_GetMapString(bool_mapTable, mixing_g),
                     ut_control_GetMapString(dsError_mapTable, ret));
    }

    if(mixing == true) {
        int32_t mixerbalance = 0, mixerbalance_g = 0;

        printf("\nSet Fader Control[-32(mute associated audio) to 32(mute main audio)]: ");
        scanf("%d", &mixerbalance);
        readAndDiscardRestOfLine(stdin);
        if(mixerbalance < -32 || mixerbalance > 32) {
            printf("Invalid Fader Control\n");
            goto exit;
        }

        UT_LOG_INFO("Calling dsSetFaderControl(handle:[0x%0X], mixerbalance:[%d])",
                    handle, mixerbalance);
        ret = dsSetFaderControl(handle, mixerbalance);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed dsSetFaderControl(handle:[0x%0X], mixerbalance:[%d]) dsError_t:[%s]",
                          handle, mixerbalance,
                          ut_control_GetMapString(dsError_mapTable, ret));
            goto exit;
        }
        else {
            UT_LOG_INFO("Result dsSetFaderControl(handle:[0x%0X], mixerbalance:[%d]) dsError_t:[%s]",
                         handle, mixerbalance,
                         ut_control_GetMapString(dsError_mapTable, ret));
        }

        UT_LOG_INFO("Calling dsGetFaderControl(handle:[0x%0X], mixerbalance:[])", handle);
        ret = dsGetFaderControl(handle, &mixerbalance_g);
        if(ret != dsERR_NONE || mixerbalance_g != mixerbalance) {
            UT_LOG_ERROR("Failed dsGetFaderControl(handle:[0x%0X], mixerbalance:[%d]) dsError_t:[%s]",
                          handle, mixerbalance_g,
                          ut_control_GetMapString(dsError_mapTable, ret));
        }
        else {
            UT_LOG_INFO("Result dsGetFaderControl(handle:[0x%0X], mixerbalance:[%d]) dsError_t:[%s]",
                         handle, mixerbalance_g,
                         ut_control_GetMapString(dsError_mapTable, ret));
        }
    }

exit:
    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test sets audio mixer levels.
*
* This test function sets audio mixer levels.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 017@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [dsAudio_L3_Low-Level_TestSpecification.md](../docs/pages/ds-audio_L3_Low-Level_TestSpecification.md)
*/
void test_l3_dsAudio_set_audio_mixerlevels(void)
{
    gTestID = 17;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret   = dsERR_NONE;
    int32_t port    = 0;
    intptr_t handle = (intptr_t)NULL;
    int32_t volume  = 0;
    int32_t aInput  = 0;

    UT_LOG_INFO("Calling dsGetAudioPort(type:[%s], index:[%d], handle:[])",
                 ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                 gDSAudioPortConfiguration[port].index);
    ret = dsGetAudioPort(gDSAudioPortConfiguration[port].typeid, gDSAudioPortConfiguration[port].index, &handle);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                      ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                      gDSAudioPortConfiguration[port].index,
                      handle,
                      ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                     ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                     gDSAudioPortConfiguration[port].index,
                     handle,
                     ut_control_GetMapString(dsError_mapTable, ret));
    }

    printf("\nMixer Input\n");
    printf("----------------------------------------------------------\n");
    printf("\t#  %-20s\n\n","Mixer Input");
    for(int32_t i = dsAUDIO_INPUT_PRIMARY ; i < dsAUDIO_INPUT_MAX; i++) {
        printf("\t%d.  %-20s\n", i,
                     ut_control_GetMapString(dsAudioInput_mapTable, i));
    }
    printf("----------------------------------------------------------\n");

    printf("\nSelect Mixer Input: ");
    scanf("%d", &aInput);
    readAndDiscardRestOfLine(stdin);
    if(aInput < dsAUDIO_INPUT_PRIMARY || aInput > dsAUDIO_INPUT_MAX-1) {
        printf("Invalid mixer input\n");
        goto exit;
    }
    printf("\nSet the Volume[0 to 100]: ");
    scanf("%d", &volume);
    readAndDiscardRestOfLine(stdin);
    if(volume < 0 || volume > 100) {
        printf("Invalid volume\n");
        goto exit;
    }

    UT_LOG_INFO("Calling dsSetAudioMixerLevels(handle:[0x%0X], aInput:[%s], volume[%d])",
                 handle,
                 ut_control_GetMapString(dsAudioInput_mapTable, aInput), volume);
    ret = dsSetAudioMixerLevels (handle, (dsAudioInput_t)aInput, volume);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsSetAudioMixerLevels(handle:[0x%0X], aInput:[%s], volume[%d]) dsError_t:[%s]",
                      handle,
                      ut_control_GetMapString(dsAudioInput_mapTable, aInput), volume,
                      ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsSetAudioMixerLevels(handle:[0x%0X], aInput:[%s], volume[%d]) dsError_t:[%s]",
                     handle,
                     ut_control_GetMapString(dsAudioInput_mapTable, aInput), volume,
                     ut_control_GetMapString(dsError_mapTable, ret));
    }

exit:
    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test sets audio language.
*
* This test function sets audio language.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 018@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [dsAudio_L3_Low-Level_TestSpecification.md](../docs/pages/ds-audio_L3_Low-Level_TestSpecification.md)
*/
void test_l3_dsAudio_set_language(void)
{
    gTestID = 18;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret   = dsERR_NONE;
    int32_t port    = 0;
    intptr_t handle = (intptr_t)NULL;
    int32_t language_type = 0;
    char language[4]      = {0};
    char language_g[4]    = {0};

    UT_LOG_INFO("Calling dsGetAudioPort(type:[%s], index:[%d], handle:[])",
                 ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                 gDSAudioPortConfiguration[port].index);
    ret = dsGetAudioPort(gDSAudioPortConfiguration[port].typeid, gDSAudioPortConfiguration[port].index, &handle);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                      ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                      gDSAudioPortConfiguration[port].index,
                      handle,
                      ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                     ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[port].typeid),
                     gDSAudioPortConfiguration[port].index,
                     handle,
                     ut_control_GetMapString(dsError_mapTable, ret));
    }

    printf("\nSelect the Language Type[1: Primary, 2: Secondary]: ");
    scanf("%d", &language_type);
    readAndDiscardRestOfLine(stdin);
    if(language_type < 1 || language_type > 2) {
        printf("Invalid language type\n");
        goto exit;
    }

    printf("\nEnter 3 letter long language as per ISO 639-3: ");
    fgets(language, 4, stdin);
    readAndDiscardRestOfLine(stdin);
    if(language_type == 1) {
        UT_LOG_INFO("Calling dsSetPrimaryLanguage(handle:[0x%0X], pLang:[%s])",
                    handle, language);
        ret = dsSetPrimaryLanguage(handle, language);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed dsSetPrimaryLanguage(handle:[0x%0X], pLang:[%s]) dsError_t:[%s]",
                        handle, language,
                        ut_control_GetMapString(dsError_mapTable, ret));
            goto exit;
        }
        else {
            UT_LOG_INFO("Result dsSetPrimaryLanguage(handle:[0x%0X], pLang:[%s]) dsError_t:[%s]",
                            handle, language,
                            ut_control_GetMapString(dsError_mapTable, ret));
        }

        UT_LOG_INFO("Calling dsGetPrimaryLanguage(handle:[0x%0X], pLang:[])", handle);
        ret = dsGetPrimaryLanguage(handle, language_g);
        if(ret != dsERR_NONE || strcmp(language_g, language)) {
            UT_LOG_ERROR("Failed dsGetPrimaryLanguage(handle:[0x%0X], pLang:[%s]) dsError_t:[%s]",
                        handle, language_g,
                        ut_control_GetMapString(dsError_mapTable, ret));
            goto exit;
        }
        else {
            UT_LOG_INFO("Result dsGetPrimaryLanguage(handle:[0x%0X], pLang:[%s]) dsError_t:[%s]",
                            handle, language_g,
                            ut_control_GetMapString(dsError_mapTable, ret));
        }
    }
    else {
        UT_LOG_INFO("Calling dsSetSecondaryLanguage(handle:[0x%0X], pLang:[%s])",
                    handle, language);
        ret = dsSetSecondaryLanguage(handle, language);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed dsSetSecondaryLanguage(handle:[0x%0X], pLang:[%s]) dsError_t:[%s]",
                        handle, language,
                        ut_control_GetMapString(dsError_mapTable, ret));
            goto exit;
        }
        else {
            UT_LOG_INFO("Result dsSetSecondaryLanguage(handle:[0x%0X], pLang:[%s]) dsError_t:[%s]",
                            handle, language,
                            ut_control_GetMapString(dsError_mapTable, ret));
        }

        UT_LOG_INFO("Calling dsGetSecondaryLanguage(handle:[0x%0X], pLang:[])", handle);
        ret = dsGetSecondaryLanguage(handle, language_g);
        if(ret != dsERR_NONE || strcmp(language_g, language)) {
            UT_LOG_ERROR("Failed dsGetSecondaryLanguage(handle:[0x%0X], pLang:[%s]) dsError_t:[%s]",
                        handle, language_g,
                        ut_control_GetMapString(dsError_mapTable, ret));
            goto exit;
        }
        else {
            UT_LOG_INFO("Result dsGetSecondaryLanguage(handle:[0x%0X], pLang:[%s]) dsError_t:[%s]",
                            handle, language_g,
                            ut_control_GetMapString(dsError_mapTable, ret));
        }
    }

exit:
    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test gets arc type of connected device.
*
* This test function gets arc type of connected device.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 019@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [dsAudio_L3_Low-Level_TestSpecification.md](../docs/pages/ds-audio_L3_Low-Level_TestSpecification.md)
*/
void test_l3_dsAudio_getArc_type(void)
{
    gTestID = 19;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret   = dsERR_NONE;
    intptr_t handle = (intptr_t)NULL;
    int32_t types   = 0;
    bool enabled    = false;

    for(int32_t i = 0; i < gDSAudioNumberOfPorts; i++) {
        if(gDSAudioPortConfiguration[i].typeid != dsAUDIOPORT_TYPE_HDMI_ARC) {
            continue;
        }

        UT_LOG_INFO("Calling dsGetAudioPort(type:[%s], index:[%d], handle:[])",
                    ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[i].typeid),
                    gDSAudioPortConfiguration[i].index);
        ret = dsGetAudioPort(gDSAudioPortConfiguration[i].typeid, gDSAudioPortConfiguration[i].index, &handle);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                        ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[i].typeid),
                        gDSAudioPortConfiguration[i].index,
                        handle,
                        ut_control_GetMapString(dsError_mapTable, ret));
            goto exit;
        }
        else {
            UT_LOG_INFO("Result dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                        ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[i].typeid),
                        gDSAudioPortConfiguration[i].index,
                        handle,
                        ut_control_GetMapString(dsError_mapTable, ret));
        }

        UT_LOG_INFO("Calling dsIsAudioPortEnabled(handle:[0x%0X], enabled:[])",
                     handle);
        ret = dsIsAudioPortEnabled(handle, &enabled);
        if (ret != dsERR_NONE || !enabled) {
            UT_LOG_ERROR("Failed dsIsAudioPortEnabled(handle:[0x%0X], enabled:[%s]) dsError_t:[%s]",
                          handle, ut_control_GetMapString(bool_mapTable, enabled),
                          ut_control_GetMapString(dsError_mapTable, ret));
            goto exit;
        }
        else {
            UT_LOG_INFO("Result dsIsAudioPortEnabled(handle:[0x%0X], enabled:[%s]) dsError_t:[%s]",
                         handle, ut_control_GetMapString(bool_mapTable, enabled),
                         ut_control_GetMapString(dsError_mapTable, ret));
        }
        break;
    }

    UT_LOG_INFO("Calling dsGetSupportedARCTypes(handle:[0x%0X], types:[])", handle);
    ret = dsGetSupportedARCTypes(handle, &types);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsGetSupportedARCTypes(handle:[0x%0X], types:[%s]) dsError_t:[%s]",
                      handle, ut_control_GetMapString(dsAudioARCTypes_mapTable, types),
                      ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsGetSupportedARCTypes(handle:[0x%0X], types:[%s]) dsError_t:[%s]",
                     handle, ut_control_GetMapString(dsAudioARCTypes_mapTable, types),
                     ut_control_GetMapString(dsError_mapTable, ret));
    }

    UT_LOG_INFO("Connected device ARC Type: %s", ut_control_GetMapString(dsAudioARCTypes_mapTable, types));

exit:
    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test sets arc SAD.
*
* This test function sets arc SAD.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 020@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [dsAudio_L3_Low-Level_TestSpecification.md](../docs/pages/ds-audio_L3_Low-Level_TestSpecification.md)
*/
void test_l3_dsAudio_setSAD(void)
{
    gTestID = 20;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret   = dsERR_NONE;
    intptr_t handle = (intptr_t)NULL;
    bool enabled    = false;
    dsAudioSADList_t sad_list = {0}; 

    for(int32_t i = 0; i < gDSAudioNumberOfPorts; i++) {
        if(gDSAudioPortConfiguration[i].typeid != dsAUDIOPORT_TYPE_HDMI_ARC) {
            continue;
        }

        UT_LOG_INFO("Calling dsGetAudioPort(type:[%s], index:[%d], handle:[])",
                    ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[i].typeid),
                    gDSAudioPortConfiguration[i].index);
        ret = dsGetAudioPort(gDSAudioPortConfiguration[i].typeid, gDSAudioPortConfiguration[i].index, &handle);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                        ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[i].typeid),
                        gDSAudioPortConfiguration[i].index,
                        handle,
                        ut_control_GetMapString(dsError_mapTable, ret));
            goto exit;
        }
        else {
            UT_LOG_INFO("Result dsGetAudioPort(type:[%s], index:[%d], handle:[0x%0X]) dsError_t:[%s]",
                        ut_control_GetMapString(dsAudioPortType_mapTable, gDSAudioPortConfiguration[i].typeid),
                        gDSAudioPortConfiguration[i].index,
                        handle,
                        ut_control_GetMapString(dsError_mapTable, ret));
        }

        UT_LOG_INFO("Calling dsIsAudioPortEnabled(handle:[0x%0X], enabled:[])",
                     handle);
        ret = dsIsAudioPortEnabled(handle, &enabled);
        if (ret != dsERR_NONE || !enabled) {
            UT_LOG_ERROR("Failed dsIsAudioPortEnabled(handle:[0x%0X], enabled:[%s]) dsError_t:[%s]",
                         handle, ut_control_GetMapString(bool_mapTable, enabled),
                         ut_control_GetMapString(dsError_mapTable, ret));
            goto exit;
        }
        else {
            UT_LOG_INFO("Result dsIsAudioPortEnabled(handle:[0x%0X], enabled:[%s]) dsError_t:[%s]",
                         handle, ut_control_GetMapString(bool_mapTable, enabled),
                         ut_control_GetMapString(dsError_mapTable, ret));
        }
        break;
    }

    printf("\nEnter SAD List count[1-15]: ");
    scanf("%d", &sad_list.count);
    readAndDiscardRestOfLine(stdin);
    if(sad_list.count < 1 || sad_list.count > 15) {
        printf("Invalid SAD Count\n");
        goto exit;
    }

    for(int32_t i = 0; i < sad_list.count; i++) {
        printf("\nEnter %d SAD Value: ", i);
        scanf("%d", &sad_list.sad[i]);
    }
    readAndDiscardRestOfLine(stdin);

    UT_LOG_INFO("Calling dsAudioSetSAD(handle:[0x%0X], sad_list:[count: %d])",
                 handle, sad_list.count);
    ret = dsAudioSetSAD(handle, sad_list);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsAudioSetSAD(handle:[0x%0X], sad_list:[count: %d]) dsError_t:[%s]",
                      handle, sad_list.count,
                      ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsAudioSetSAD(handle:[0x%0X], sad_list:[count: %d]) dsError_t:[%s]",
                     handle, sad_list.count,
                     ut_control_GetMapString(dsError_mapTable, ret));
    }

exit:
    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test terminates the dsAudio.
*
* This test function terminates the dsAudio.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 021@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [dsAudio_L3_Low-Level_TestSpecification.md](../docs/pages/ds-audio_L3_Low-Level_TestSpecification.md)
*/
void test_l3_dsAudio_terminate(void)
{
    gTestID = 21;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;

    UT_LOG_INFO("Calling dsAudioPortTerm()");
    ret = dsAudioPortTerm();
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsAudioPortTerm() dsError_t:[%s]", ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsAudioPortTerm() dsError_t:[%s]", ut_control_GetMapString(dsError_mapTable, ret));
    }

    UT_LOG_INFO("Out %s", __FUNCTION__);
}

static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main tests for this module
 *
 * @return int32_t - 0 on success, otherwise failure
 */

int32_t test_l3_dsAudio_register(void)
{
    if(gSourceType == 1) {
        // Create the test suite for source type
        pSuite = UT_add_suite("[L3 dsAudio - Source]", NULL, NULL);
        if (pSuite == NULL) {
            UT_LOG_ERROR("Failed to create the test suite");
            return -1;
        }
    }
    else if(gSourceType == 0) {
        // Create the test suite for sink type
        pSuite = UT_add_suite("[L3 dsAudio - Sink]", NULL, NULL);
        if (pSuite == NULL) {
            UT_LOG_ERROR("Failed to create the test suite");
            return -1;
        }
    }
    else {
        UT_LOG_ERROR("Invalid platform type");
        return -1;
    }

    UT_add_test(pSuite, "Initialize dsAudio", test_l3_dsAudio_initialize);
    UT_add_test(pSuite, "Enable Audio Port", test_l3_dsAudio_enable_port);
    UT_add_test(pSuite, "Disable Audio Port", test_l3_dsAudio_disable_port);
    if(gSourceType == 0) {
        UT_add_test(pSuite, "Headphone Connection", test_l3_dsAudio_headphone_connection);
    }
    UT_add_test(pSuite, "Audio Compression", test_l3_dsAudio_audio_compression);
    UT_add_test(pSuite, "MS12 DAP Features", test_l3_dsAudio_ms12_dap);
    UT_add_test(pSuite, "Set Stereo Mode", test_l3_dsAudio_stereo_mode);
    if(gSourceType == 0) {
        UT_add_test(pSuite, "Enable/Disable Stereo Auto", test_l3_dsAudio_stereo_auto_mode);
        UT_add_test(pSuite, "Set Audio Level", test_l3_dsAudio_set_audio_level);
        UT_add_test(pSuite, "Set Audio Gain For Speaker", test_l3_dsAudio_set_audio_gain);
    }
    UT_add_test(pSuite, "Audio Mute/UnMute", test_l3_dsAudio_set_audio_mute);
    UT_add_test(pSuite, "Set Audio Delay", test_l3_dsAudio_set_audio_delay);
    UT_add_test(pSuite, "Get Audio Format", test_l3_dsAudio_get_audio_format);
    UT_add_test(pSuite, "Set ATMOS Output Mode", test_l3_dsAudio_set_atmos_mode);
    UT_add_test(pSuite, "Get ATMOS Capabilities", test_l3_dsAudio_getConnected_atmoscaps);
    if(gSourceType == 0) {
        UT_add_test(pSuite, "Set MS12 Profiles", test_l3_dsAudio_ms12Profile);
    }
    UT_add_test(pSuite, "Set Associate Audio Mixing", test_l3_dsAudio_set_associate_audio_mixing);
    if(gSourceType == 0) {
        UT_add_test(pSuite, "Set Audio Mixer Levels", test_l3_dsAudio_set_audio_mixerlevels);
    }
    UT_add_test(pSuite, "Primary/Secondary Language", test_l3_dsAudio_set_language);
    if(gSourceType == 0) {
        UT_add_test(pSuite, "Get ARC Type", test_l3_dsAudio_getArc_type);
        UT_add_test(pSuite, "Set SAD List", test_l3_dsAudio_setSAD);
    }
    UT_add_test(pSuite, "Terminate dsAudio", test_l3_dsAudio_terminate);

    return 0;
}

/** @} */ // End of DS_Audio_HALTEST_L3
/** @} */ // End of DS_Audio_HALTEST
/** @} */ // End of Device_Settings_HALTEST
/** @} */ // End of Device_Settings
/** @} */ // End of HPK
