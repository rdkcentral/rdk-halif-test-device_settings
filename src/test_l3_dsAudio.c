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

#define DS_AUDIO_MAX_PORTS 20
#define DS_AUDIO_MAX_DAP 20
#define DS_AUDIO_MAX_MS12_PROFILES 10

static int32_t gTestGroup = 3;
static int32_t gTestID    = 1;

static int32_t gConnectionStatus = -1;
static dsAudioFormat_t gAudioFormat = dsAUDIO_FORMAT_NONE;
static dsATMOSCapability_t gAtosCapablity = dsAUDIO_ATMOS_NOTSUPPORTED;
static bool gAtmosStatus = false;

void readAndDiscardRestOfLine(FILE* in)
{
   int c;
   while ( (c = fgetc(in)) != EOF && c != '\n');
}

static void audioOutPortConnectCB(dsAudioPortType_t portType, uint32_t uiPortNo, bool isPortCon)
{
    UT_LOG_DEBUG("Received Connection status callback port: %d, port number: %d, Connection: %d", portType, uiPortNo, isPortCon);
    gConnectionStatus = isPortCon;
}

static void audioFormatUpdateCB(dsAudioFormat_t audioFormat)
{
    UT_LOG_DEBUG("Received Format update callback : %d", audioFormat);
    gAudioFormat = audioFormat;
}

static void atmosCapsChange(dsATMOSCapability_t atmosCaps, bool status)
{
    UT_LOG_DEBUG("Received ATMOS Capablity Change callback, Capability: %d, Status: %d", atmosCaps, status);
    gAtosCapablity = atmosCaps;
    gAtmosStatus = status;
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
    dsError_t ret;
    gTestID = 1;

    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    UT_LOG_DEBUG("Invoking dsAudioPortInit");
    ret = dsAudioPortInit();
    UT_LOG_DEBUG("Return status: %d", ret);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed to initialize dsAudio: %d", ret);
    }

    UT_LOG_DEBUG("Invoking dsAudioOutRegisterConnectCB");
    ret = dsAudioOutRegisterConnectCB(audioOutPortConnectCB);
    UT_LOG_DEBUG("Return status: %d", ret);

    if (ret != dsERR_NONE) {
        UT_LOG_ERROR("dsAudioOutRegisterConnectCB failed with error %d", ret);
    }

    UT_LOG_DEBUG("Invoking dsAudioFormatUpdateRegisterCB");
    ret = dsAudioFormatUpdateRegisterCB(audioFormatUpdateCB);
    if (ret != dsERR_NONE) {
        UT_LOG_ERROR("dsAudioFormatUpdateRegisterCB failed with error %d", ret);
    }

    UT_LOG_DEBUG("Invoking dsAudioAtmosCapsChangeRegisterCB ");
    ret = dsAudioAtmosCapsChangeRegisterCB (atmosCapsChange);
    if (ret != dsERR_NONE) {
        UT_LOG_ERROR("dsAudioAtmosCapsChangeRegisterCB  failed with error %d", ret);
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
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
    dsError_t ret;
    dsAudioPortType_t port;
    int32_t choice;
    intptr_t handle;
    bool enabled    = false;

    printf("\nSelect dsAudio Port\n");
    printf("------------------------------------------\n");
    printf("\t#  %-20s%s\n\n","Audio Port", "Index");
    for(int32_t i = 0; i < gDSAudioNumberOfPorts; i++) {
        printf("\t%d.  %-20s%-2d\n", i+1, gDSAudioPortConfiguration[i].port_name,
                                          gDSAudioPortConfiguration[i].index);
    }
    printf("------------------------------------------\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);

    if(choice < 1 || choice > gDSAudioNumberOfPorts) {
        printf("Invalid Port choice\n");
        return;
    }

    port = choice - 1;

    UT_LOG_DEBUG("Invoking dsGetAudioPort");
    ret = dsGetAudioPort(gDSAudioPortConfiguration[port].typeid, gDSAudioPortConfiguration[port].index, &handle);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed to get the port handle for %s", gDSAudioPortConfiguration[port].port_name);
        return;
    }

    UT_LOG_DEBUG("Invoking dsEnableAudioPort with handle: %p and enabled: true", handle);
    ret = dsEnableAudioPort(handle, true);
    if (ret != dsERR_NONE) {
        UT_LOG_ERROR("dsEnableAudioPort failed with error: %d", ret);
        return;
    }

    UT_LOG_DEBUG("Invoking dsIsAudioPortEnabled with handle: %p", handle);
    ret = dsIsAudioPortEnabled(handle, &enabled);
    if (ret != dsERR_NONE || !enabled) {
        UT_LOG_ERROR("dsIsAudioPortEnabled failed with error: %d or port is not enabled", ret);
    }

    if(gDSAudioPortConfiguration[port].typeid == dsAUDIOPORT_TYPE_HDMI_ARC) {
        dsAudioARCStatus_t arcStatus;
        int32_t archType;

        printf("\nSelect ARC Type[1: ARC, 2: EARC] ");

        scanf("%d", &archType);
        arcStatus.type = archType;
        readAndDiscardRestOfLine(stdin);

        arcStatus.status = true;

        ret = dsAudioEnableARC(handle, arcStatus);
        if (ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed to enable ARC port: %d", ret);
            return;
        }
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
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
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t ret;
    dsAudioPortType_t port;
    int32_t choice;
    intptr_t handle;
    bool enabled    = false;
    int32_t enable_port[DS_AUDIO_MAX_PORTS] = {0};
    int32_t count = 0;

    printf("\nSelect dsAudio Port to Disable\n");
    printf("------------------------------------------\n");
    printf("\t#  %-20s%s\n\n","Audio Port", "Index");
    for(int32_t i = 0; i < gDSAudioNumberOfPorts; i++) {
        ret = dsGetAudioPort(gDSAudioPortConfiguration[i].typeid, gDSAudioPortConfiguration[i].index, &handle);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed to get the port handle for %s", gDSAudioPortConfiguration[i].port_name);
            continue;
        }

        ret = dsIsAudioPortEnabled(handle, &enabled);

        if(enabled == true) {
            enable_port[count] = i;
            printf("\t%d.  %-20s%-2d\n", count+1, gDSAudioPortConfiguration[i].port_name,
                                              gDSAudioPortConfiguration[i].index);
            count++;
        }
    }
    printf("------------------------------------------\n");
    if(count == 0) {
        printf("\nNo Ports Enabled\n");
        return;
    }

    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);

    if(choice < 1 || choice > count) {
        printf("Invalid Port choice\n");
        return;
    }

    port = enable_port[choice - 1];

    UT_LOG_DEBUG("Invoking dsGetAudioPort");
    ret = dsGetAudioPort(gDSAudioPortConfiguration[port].typeid, gDSAudioPortConfiguration[port].index, &handle);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed to get the port handle for %s", gDSAudioPortConfiguration[port].port_name);
        return;
    }

    UT_LOG_DEBUG("Invoking dsEnableAudioPort with handle: %p and enabled: false", handle);
    ret = dsEnableAudioPort(handle, false);
    if (ret != dsERR_NONE) {
        UT_LOG_ERROR("dsEnableAudioPort failed with error: %d", ret);
        return;
    }

    UT_LOG_DEBUG("Invoking dsIsAudioPortEnabled with handle: %p", handle);
    ret = dsIsAudioPortEnabled(handle, &enabled);
    if (ret != dsERR_NONE || enabled) {
        UT_LOG_ERROR("dsIsAudioPortEnabled failed with error: %d or port is enabled", ret);
        return;
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
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
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t ret;
    intptr_t handle = (intptr_t)NULL;
    bool isConnected = false;

    for(int32_t i = 0; i < gDSAudioNumberOfPorts; i++) {
        if(gDSAudioPortConfiguration[i].typeid != dsAUDIOPORT_TYPE_HEADPHONE) {
            continue;
        }
        UT_LOG_DEBUG("Invoking dsGetAudioPort");
        ret = dsGetAudioPort(gDSAudioPortConfiguration[i].typeid, gDSAudioPortConfiguration[i].index, &handle);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed to get the port handle for %s", gDSAudioPortConfiguration[i].port_name);
            return;
        }
    }

    if(handle == (intptr_t)NULL) {
        UT_LOG_ERROR("Platform doesn't support Headphone");
        return;
    }

    ret = dsAudioOutIsConnected(handle, &isConnected);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed to get the connection status");
        return;
    }

    UT_LOG_DEBUG("Headphone Connection status: %d, connection status from Callback: %d", isConnected, gConnectionStatus);

    gConnectionStatus = -1;

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
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
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t ret;
    dsAudioPortType_t port;
    int32_t choice;
    intptr_t handle;
    bool enabled    = false;
    int32_t enable_port[DS_AUDIO_MAX_PORTS] = {0};
    int32_t count = 0;
    int32_t compression = 0;

    printf("\nSelect dsAudio Port to Apply Audio Compression\n");
    printf("------------------------------------------\n");
    printf("\t#  %-20s%s\n\n","Audio Port", "Index");
    for(int32_t i = 0; i < gDSAudioNumberOfPorts; i++) {
        if(gDSAudioPortConfiguration[i].no_of_supported_compression == 0) {
            continue;
        }

        ret = dsGetAudioPort(gDSAudioPortConfiguration[i].typeid, gDSAudioPortConfiguration[i].index, &handle);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed to get the port handle for %s", gDSAudioPortConfiguration[i].port_name);
            continue;
        }

        ret = dsIsAudioPortEnabled(handle, &enabled);

        if(enabled == true) {
            enable_port[count] = i;
            printf("\t%d.  %-20s%-2d\n", count+1, gDSAudioPortConfiguration[i].port_name,
                                              gDSAudioPortConfiguration[i].index);
            count++;
        }
    }
    printf("------------------------------------------\n");
    if(count == 0) {
        printf("\nNo Ports Enabled\n");
        return;
    }

    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);

    if(choice < 1 || choice > count) {
        printf("Invalid Port choice\n");
        return;
    }

    port = enable_port[choice - 1];

    UT_LOG_DEBUG("Invoking dsGetAudioPort");
    ret = dsGetAudioPort(gDSAudioPortConfiguration[port].typeid, gDSAudioPortConfiguration[port].index, &handle);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed to get the port handle for %s", gDSAudioPortConfiguration[port].port_name);
        return;
    }

    printf("\n\nSelect Compression Type[0: None, 1: Light, 2: Medium, 3: Heavy]: ");
    scanf("%d", &compression);
    readAndDiscardRestOfLine(stdin);
    if(compression < 0 || compression > 3) {
        printf("Invalid Compression Type\n");
        return;
    }

    ret = dsSetAudioCompression(handle, compression);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed to set Audio Compression for %s", gDSAudioPortConfiguration[port].port_name);
        return;
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
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
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t ret;
    dsAudioPortType_t port;
    int32_t choice;
    intptr_t handle;
    bool enabled    = false;
    int32_t enable_port[DS_AUDIO_MAX_PORTS] = {0};
    int32_t count = 0;

    printf("\nSelect dsAudio Port to Apply MS12 DAP\n");
    printf("------------------------------------------\n");
    printf("\t#  %-20s%s\n\n","Audio Port", "Index");
    for(int32_t i = 0; i < gDSAudioNumberOfPorts; i++) {
        if(gDSAudioPortConfiguration[i].ms12_capabilites == 0) {
            continue;
        }

        ret = dsGetAudioPort(gDSAudioPortConfiguration[i].typeid, gDSAudioPortConfiguration[i].index, &handle);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed to get the port handle for %s", gDSAudioPortConfiguration[i].port_name);
            continue;
        }

        ret = dsIsAudioPortEnabled(handle, &enabled);

        if(enabled == true) {
            enable_port[count] = i;
            printf("\t%d.  %-20s%-2d\n", count+1, gDSAudioPortConfiguration[i].port_name,
                                              gDSAudioPortConfiguration[i].index);
            count++;
        }
    }
    printf("------------------------------------------\n");
    if(count == 0) {
        printf("\nNo Ports Enabled\n");
        return;
    }

    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);

    if(choice < 1 || choice > count) {
        printf("Invalid Port choice\n");
        return;
    }

    port = enable_port[choice - 1];

    UT_LOG_DEBUG("Invoking dsGetAudioPort");
    ret = dsGetAudioPort(gDSAudioPortConfiguration[port].typeid, gDSAudioPortConfiguration[port].index, &handle);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed to get the port handle for %s", gDSAudioPortConfiguration[port].port_name);
        return;
    }

    printf("\nSelect MS12 DAP Feature\n");
    printf("------------------------------------------\n");
    printf("\t#   %-20s\n\n","MS12 DAP Feature");
    printf("\t1.  %-20s\n","DolbyVolume");
    printf("\t2.  %-20s\n","InteligentEqualizer");
    printf("\t3.  %-20s\n","DialogueEnhancer");
    printf("\t4.  %-20s\n","Volumeleveller");
    printf("\t5.  %-20s\n","BassEnhancer");
    printf("\t6.  %-20s\n","SurroundDecoder");
    printf("\t7.  %-20s\n","DRCMode");
    printf("\t8.  %-20s\n","SurroundVirtualizer");
    printf("\t9.  %-20s\n","MISteering");
    printf("\t10. %-20s\n","GraphicEqualizer");
    printf("\t11. %-20s\n","LEConfig");
    printf("------------------------------------------\n");
    if(count == 0) {
        printf("\nNo Ports Enabled\n");
        return;
    }

    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1: //DolbyVolume
        {
            bool mode = false;

            printf("\nDolby Volume[1:Enable, 2:Disable]: ");
            scanf("%d", &choice);
            if(choice < 1 || choice > 2) {
                printf("Invalid choice\n");
                break;
            }

            if(choice == 1) {
                UT_LOG_DEBUG("Enabling dolby volume mode for the port: %s", gDSAudioPortConfiguration[port].port_name);
                ret = dsSetDolbyVolumeMode(handle, true);
                if(ret != dsERR_NONE) {
                    UT_LOG_ERROR("Failed to set the dolby volume mode to true for %s", gDSAudioPortConfiguration[port].port_name);
                }
                ret = dsGetDolbyVolumeMode(handle, &mode);
                if(ret != dsERR_NONE || mode == false) {
                    UT_LOG_ERROR("Failed to get the Dolby Volume mode for %s", gDSAudioPortConfiguration[port].port_name);
                }
            }
            else if(choice == 2) {
                UT_LOG_DEBUG("Disabling dolby volume mode for the port: %s", gDSAudioPortConfiguration[port].port_name);
                ret = dsSetDolbyVolumeMode(handle, false);
                if(ret != dsERR_NONE) {
                    UT_LOG_ERROR("Failed to set the dolby volume mode to true for %s", gDSAudioPortConfiguration[port].port_name);
                }
                ret = dsGetDolbyVolumeMode(handle, &mode);
                if(ret != dsERR_NONE || mode == true) {
                    UT_LOG_ERROR("Failed to get the Dolby Volume mode for %s", gDSAudioPortConfiguration[port].port_name);
                }
            }
            break;
        }
        case 2: //InteligentEqualizer
        {
            int32_t mode;

            printf("\nSelect InteligentEqualizer Mode\n");
            printf("------------------------------------------\n");
            printf("\t#   %-20s\n\n","Mode");
            printf("\t1.  %-20s\n","OFF");
            printf("\t2.  %-20s\n","Open");
            printf("\t3.  %-20s\n","Rich");
            printf("\t4.  %-20s\n","Focused");
            printf("\t5.  %-20s\n","Balanced");
            printf("\t6.  %-20s\n","Warm");
            printf("\t7.  %-20s\n","Detailed");
            printf("------------------------------------------\n");

            printf("\nEnter your choice: ");
            scanf("%d", &mode);

            if(mode < 1 || mode > 7) {
                printf("Invalid Mode choice\n");
                break;
            }

            UT_LOG_DEBUG("Set Inteliigent Equalizer mode %d for the port: %s", mode-1, gDSAudioPortConfiguration[port].port_name);
            ret = dsSetIntelligentEqualizerMode(handle, mode-1);
            if(ret != dsERR_NONE) {
                UT_LOG_ERROR("Failed to set Inteliigent Equalizer mode to %d for %s", mode-1, gDSAudioPortConfiguration[port].port_name);
            }
            break;
        }
        case 3: //DialogueEnhancer
        {
            int32_t level;

            printf("\nSelect DialogueEnhancer Level[0-16]: ");
            scanf("%d", &level);
            if(level < 0 || level > 16) {
                printf("Invalid DialogueEnhancer Level\n");
                break;
            }

            UT_LOG_DEBUG("Set DialogueEnhancer Level %d for the port: %s", level, gDSAudioPortConfiguration[port].port_name);
            ret = dsSetDialogEnhancement(handle, level);
            if(ret != dsERR_NONE) {
                UT_LOG_ERROR("Failed to set DialogueEnhancer Level %d for %s", level, gDSAudioPortConfiguration[port].port_name);
            }
            break;
        }
        case 4: //Volumeleveller
        {
            dsVolumeLeveller_t volume_level;

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

            UT_LOG_DEBUG("Set Volumeleveller mode: %d Level: %d for the port: %s", volume_level.mode, volume_level.level,
                                                                                   gDSAudioPortConfiguration[port].port_name);
            ret = dsSetVolumeLeveller(handle, volume_level);
            if(ret != dsERR_NONE) {
                UT_LOG_ERROR("Failed to Set Volumeleveller mode: %d Level: %d for the port: %s", volume_level.mode, volume_level.level,
                                                                                   gDSAudioPortConfiguration[port].port_name);
            }
            break;
        }
        case 5: //BassEnhancer
        {
            int32_t boost;

            printf("\nSelect BassEnhancer Boost[0-100]: ");
            scanf("%d", &boost);
            if(boost < 0 || boost > 100) {
                printf("Invalid BassEnhancer Boost\n");
                break;
            }

            UT_LOG_DEBUG("Set BassEnhancer Boost %d for the port: %s", boost, gDSAudioPortConfiguration[port].port_name);
            ret = dsSetBassEnhancer(handle, boost);
            if(ret != dsERR_NONE) {
                UT_LOG_ERROR("Failed to Set BassEnhancer Boost %d for the port: %s", boost, gDSAudioPortConfiguration[port].port_name);
            }
            break;
        }
        case 6: //SurroundDecoder
        {
            bool mode = false;

            printf("\nSurround Decoder[1:Enable, 2:Disable]: ");
            scanf("%d", &choice);
            if(choice < 1 || choice > 2) {
                printf("Invalid choice\n");
                break;
            }

            if(choice == 1) {
                UT_LOG_DEBUG("Enabling SurroundDecoder mode for the port: %s", gDSAudioPortConfiguration[port].port_name);
                ret = dsEnableSurroundDecoder(handle, true);
                if(ret != dsERR_NONE) {
                    UT_LOG_ERROR("Failed to set SurroundDecoder mode to true for %s", gDSAudioPortConfiguration[port].port_name);
                }
                ret = dsIsSurroundDecoderEnabled(handle, &mode);
                if(ret != dsERR_NONE || mode == false) {
                    UT_LOG_ERROR("Failed to Enable the SurroundDecoder mode for %s", gDSAudioPortConfiguration[port].port_name);
                }
            }
            else if(choice == 2) {
                UT_LOG_DEBUG("Disabling SurroundDecoder mode for the port: %s", gDSAudioPortConfiguration[port].port_name);
                ret = dsEnableSurroundDecoder(handle, false);
                if(ret != dsERR_NONE) {
                    UT_LOG_ERROR("Failed to set SurroundDecoder mode to false for %s", gDSAudioPortConfiguration[port].port_name);
                }
                ret = dsIsSurroundDecoderEnabled(handle, &mode);
                if(ret != dsERR_NONE || mode == true) {
                    UT_LOG_ERROR("Failed to disable the SurroundDecoder mode for %s", gDSAudioPortConfiguration[port].port_name);
                }
            }
            break;
        }
        case 7: //DRCMode
        {
            int32_t mode;

            printf("\nSelect DRC Mode[0: DRC Line Mode, 1: DRC RF Mode]: ");
            scanf("%d", &mode);
            if(mode < 0 || mode > 1) {
                printf("Invalid DRC Mode\n");
                break;
            }

            UT_LOG_DEBUG("Set DRC Mode %d to the port: %s", mode, gDSAudioPortConfiguration[port].port_name);
            ret = dsSetDRCMode(handle, mode);
            if(ret != dsERR_NONE) {
                UT_LOG_ERROR("Failed to Set DRC Mode %d to the port: %s", mode, gDSAudioPortConfiguration[port].port_name);
            }
            break;
        }
        case 8: //SurroundVirtualizer
        {
            dsSurroundVirtualizer_t surround_virtualize;

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

            UT_LOG_DEBUG("Set SurroundVirtualizer mode: %d Boost: %d for the port: %s", surround_virtualize.mode, surround_virtualize.boost,
                                                                                   gDSAudioPortConfiguration[port].port_name);
            ret = dsSetSurroundVirtualizer(handle, surround_virtualize);
            if(ret != dsERR_NONE) {
                UT_LOG_ERROR("Failed to Set SurroundVirtualizer mode: %d Boost: %d for the port: %s", surround_virtualize.mode, surround_virtualize.boost,
                                                                                   gDSAudioPortConfiguration[port].port_name);
            }
            break;
        }
        case 9: //MISteering
        {
            bool mode = false;

            printf("\nMI Steering[1:Enable, 2:Disable]: ");
            scanf("%d", &choice);
            if(choice < 1 || choice > 2) {
                printf("Invalid choice\n");
                break;
            }

            if(choice == 1) {
                UT_LOG_DEBUG("Enabling MISteering mode for the port: %s", gDSAudioPortConfiguration[port].port_name);
                ret = dsSetMISteering(handle, true);
                if(ret != dsERR_NONE) {
                    UT_LOG_ERROR("Failed to set MISteering mode to true for %s", gDSAudioPortConfiguration[port].port_name);
                }
                ret = dsGetMISteering(handle, &mode);
                if(ret != dsERR_NONE || mode == false) {
                    UT_LOG_ERROR("Failed to enable the MISteering for %s", gDSAudioPortConfiguration[port].port_name);
                }
            }
            else if(choice == 2) {
                UT_LOG_DEBUG("Disabling MISteering mode for the port: %s", gDSAudioPortConfiguration[port].port_name);
                ret = dsSetMISteering(handle, false);
                if(ret != dsERR_NONE) {
                    UT_LOG_ERROR("Failed to set MISteering mode to false for %s", gDSAudioPortConfiguration[port].port_name);
                }
                ret = dsGetMISteering(handle, &mode);
                if(ret != dsERR_NONE || mode == true) {
                    UT_LOG_ERROR("Failed to disable the MISteering for %s", gDSAudioPortConfiguration[port].port_name);
                }
            }

            break;
        }
        case 10: //GraphicEqualizer
        {
            int32_t mode;

            printf("\nSelect GraphicEqualizer Mode[0: OFF, 1: EQ Open, 2: EQ Rich, 3: EQ Focused]: ");
            scanf("%d", &mode);
            if(mode < 0 || mode > 3) {
                printf("Invalid GraphicEqualizer Mode\n");
                break;
            }

            UT_LOG_DEBUG("Set GraphicEqualizer Mode %d to the port: %s", mode, gDSAudioPortConfiguration[port].port_name);
            ret = dsSetGraphicEqualizerMode(handle, mode);
            if(ret != dsERR_NONE) {
                UT_LOG_ERROR("Failed to Set GraphicEqualizer Mode %d to the port: %s", mode, gDSAudioPortConfiguration[port].port_name);
            }
            break;
        }
        case 11: //LEConfig
        {
            bool mode = false;

            printf("\nLE Configuration[1:Enable, 2:Disable]: ");
            scanf("%d", &choice);
            if(choice < 1 || choice > 2) {
                printf("Invalid choice\n");
                break;
            }

            if(choice == 1) {
                UT_LOG_DEBUG("Enabling LEConfig mode for the port: %s", gDSAudioPortConfiguration[port].port_name);
                ret = dsEnableLEConfig(handle, true);
                if(ret != dsERR_NONE) {
                    UT_LOG_ERROR("Failed to set LEConfig mode to true for %s", gDSAudioPortConfiguration[port].port_name);
                }
                ret = dsGetLEConfig(handle, &mode);
                if(ret != dsERR_NONE || mode == false) {
                    UT_LOG_ERROR("Failed to Enable the LEConfig for %s", gDSAudioPortConfiguration[port].port_name);
                }
            }
            else if(choice == 2) {
                UT_LOG_DEBUG("Disabling LEConfig mode for the port: %s", gDSAudioPortConfiguration[port].port_name);
                ret = dsEnableLEConfig(handle, false);
                if(ret != dsERR_NONE) {
                    UT_LOG_ERROR("Failed to set LEConfig mode to false for %s", gDSAudioPortConfiguration[port].port_name);
                }
                ret = dsGetLEConfig(handle, &mode);
                if(ret != dsERR_NONE || mode == true) {
                    UT_LOG_ERROR("Failed to Disable the LEConfig for %s", gDSAudioPortConfiguration[port].port_name);
                }
            }
            break;
        }
        default:
            printf("Invalid DAP Feature choice\n");
    }

    readAndDiscardRestOfLine(stdin);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
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
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    dsAudioPortType_t port;
    int32_t choice;
    intptr_t handle;
    bool enabled    = false;
    int32_t enable_port[DS_AUDIO_MAX_PORTS] = {0};
    int32_t count = 0;
    int32_t mode;

    printf("\nSelect dsAudio Port to Set Output Mode\n");
    printf("------------------------------------------\n");
    printf("\t#  %-20s%s\n\n","Audio Port", "Index");
    for(int32_t i = 0; i < gDSAudioNumberOfPorts; i++) {
        ret = dsGetAudioPort(gDSAudioPortConfiguration[i].typeid, gDSAudioPortConfiguration[i].index, &handle);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed to get the port handle for %s", gDSAudioPortConfiguration[i].port_name);
            continue;
        }

        ret = dsIsAudioPortEnabled(handle, &enabled);

        if(enabled == true) {
            enable_port[count] = i;
            printf("\t%d.  %-20s%-2d\n", count+1, gDSAudioPortConfiguration[i].port_name,
                                              gDSAudioPortConfiguration[i].index);
            count++;
        }
    }
    printf("------------------------------------------\n");
    if(count == 0) {
        printf("\nNo Ports Enabled\n");
        return;
    }

    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);
    if(choice < 1 || choice > count) {
        printf("Invalid Port choice\n");
        return;
    }

    port = enable_port[choice - 1];
    UT_LOG_DEBUG("Invoking dsGetAudioPort");
    ret = dsGetAudioPort(gDSAudioPortConfiguration[port].typeid, gDSAudioPortConfiguration[port].index, &handle);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed to get the port handle for %s", gDSAudioPortConfiguration[port].port_name);
        return;
    }

    printf("\nSelect Stereo Mode\n");
    printf("------------------------------------------\n");
    printf("\t#   %-20s\n\n","Mono");
    printf("\t1.  %-20s\n","Stereo");
    printf("\t2.  %-20s\n","Surround");
    printf("\t3.  %-20s\n","PassThru");
    printf("\t4.  %-20s\n","DD");
    printf("\t5.  %-20s\n","DD+");
    printf("------------------------------------------\n");

    printf("\nEnter your choice: ");
    scanf("%d", &mode);
    readAndDiscardRestOfLine(stdin);
    if(mode < 1 || mode > 5) {
        printf("Invalid Mode choice\n");
        return;
    }

    UT_LOG_DEBUG("Set Stereo Mode for the port: %s", gDSAudioPortConfiguration[port].port_name);
    ret = dsSetStereoMode(handle, mode);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed to set Stereo mode to %d for %s", mode, gDSAudioPortConfiguration[port].port_name);
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
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
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    dsAudioPortType_t port;
    int32_t choice;
    intptr_t handle;
    bool enabled    = false;
    int32_t enable_port[DS_AUDIO_MAX_PORTS] = {0};
    int32_t count = 0;
    char mode;

    printf("\nSelect dsAudio Port to Set Output Auto Mode\n");
    printf("------------------------------------------\n");
    printf("\t#  %-20s%s\n\n","Audio Port", "Index");
    for(int32_t i = 0; i < gDSAudioNumberOfPorts; i++) {
        ret = dsGetAudioPort(gDSAudioPortConfiguration[i].typeid, gDSAudioPortConfiguration[i].index, &handle);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed to get the port handle for %s", gDSAudioPortConfiguration[i].port_name);
            continue;
        }

        ret = dsIsAudioPortEnabled(handle, &enabled);

        if(enabled == true) {
            enable_port[count] = i;
            printf("\t%d.  %-20s%-2d\n", count+1, gDSAudioPortConfiguration[i].port_name,
                                              gDSAudioPortConfiguration[i].index);
            count++;
        }
    }
    printf("------------------------------------------\n");
    if(count == 0) {
        printf("\nNo Ports Enabled\n");
        return;
    }

    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);
    if(choice < 1 || choice > count) {
        printf("Invalid Port choice\n");
        return;
    }

    port = enable_port[choice - 1];
    UT_LOG_DEBUG("Invoking dsGetAudioPort");
    ret = dsGetAudioPort(gDSAudioPortConfiguration[port].typeid, gDSAudioPortConfiguration[port].index, &handle);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed to get the port handle for %s", gDSAudioPortConfiguration[port].port_name);
        return;
    }

    printf("\nEnable Stereo Auto[y/n]: ");
    scanf("%c", &mode);
    readAndDiscardRestOfLine(stdin);
    if(mode == 'y' || mode == 'Y') {
        UT_LOG_DEBUG("Enable Stereo Auto for the port: %s", gDSAudioPortConfiguration[port].port_name);
        ret = dsSetStereoAuto(handle, true);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed to Enable Stereo Autofor %s", gDSAudioPortConfiguration[port].port_name);
        }
    }
    else if(mode == 'n' || mode == 'N')
    {
        UT_LOG_DEBUG("Disable Stereo Auto for the port: %s", gDSAudioPortConfiguration[port].port_name);
        ret = dsSetStereoAuto(handle, false);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed to Disable Stereo Autofor %s", gDSAudioPortConfiguration[port].port_name);
        }
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
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
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    dsAudioPortType_t port;
    int32_t choice;
    intptr_t handle;
    bool enabled    = false;
    int32_t enable_port[DS_AUDIO_MAX_PORTS] = {0};
    int32_t count = 0;

    printf("\nSelect dsAudio Port to Apply Gain\n");
    printf("------------------------------------------\n");
    printf("\t#  %-20s%s\n\n","Audio Port", "Index");
    for(int32_t i = 0; i < gDSAudioNumberOfPorts; i++) {
        ret = dsGetAudioPort(gDSAudioPortConfiguration[i].typeid, gDSAudioPortConfiguration[i].index, &handle);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed to get the port handle for %s", gDSAudioPortConfiguration[i].port_name);
            continue;
        }

        ret = dsIsAudioPortEnabled(handle, &enabled);

        if(enabled == true) {
            enable_port[count] = i;
            printf("\t%d.  %-20s%-2d\n", count+1, gDSAudioPortConfiguration[i].port_name,
                                              gDSAudioPortConfiguration[i].index);
            count++;
        }
    }
    printf("------------------------------------------\n");
    if(count == 0) {
        printf("\nNo Ports Enabled\n");
        return;
    }

    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);
    if(choice < 1 || choice > count) {
        printf("Invalid Port choice\n");
        return;
    }

    port = enable_port[choice - 1];

    UT_LOG_DEBUG("Invoking dsGetAudioPort");
    ret = dsGetAudioPort(gDSAudioPortConfiguration[port].typeid, gDSAudioPortConfiguration[port].index, &handle);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed to get the %s", gDSAudioPortConfiguration[port].port_name);
        return;
    }

    printf("\nSelect Type\n");
    printf("------------------------------------------\n");
    printf("\t#  Gain Type\n\n");
    printf("\t1. Audio Gain [-2080.0 - 480.0]\n");
    printf("\t2. Audio Gain Level [0 - 100]\n");
    printf("------------------------------------------\n");

    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        float gain;
        float gain_level;
        case 1:
            printf("\nEnter Gain[-2080 to 480]: ");
            scanf("%f", &gain);
            if(gain < -2080 || gain > 480) {
                printf("Invalid Audio Gain value\n");
                break;
            }
            UT_LOG_DEBUG("Invoking dsSetAudioGain with gain: %f", gain);
            ret = dsSetAudioGain(handle, gain);
            if(ret != dsERR_NONE) {
                UT_LOG_ERROR("Failed to set the gain to %s", gDSAudioPortConfiguration[port].port_name);
                break;
            }
            break;
        case 2:
            printf("\nEnter Gain Level[0 to 100]: ");
            scanf("%f", &gain_level);
            if(gain_level < 0 || gain_level > 100) {
                printf("Invalid Audio Gain Level\n");
                break;
            }
            UT_LOG_DEBUG("Invoking dsSetAudioLevel with gain level: %f", gain_level);
            ret = dsSetAudioLevel(handle, gain_level);
            if(ret != dsERR_NONE) {
                UT_LOG_ERROR("Failed to set the gain level to %s", gDSAudioPortConfiguration[port].port_name);
                break;
            }
            break;
        default:
            printf("Invalid Audio Gain choice\n");
            break;
    }
    readAndDiscardRestOfLine(stdin);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
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
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    dsAudioPortType_t port;
    int32_t choice;
    intptr_t handle;
    bool enabled    = false;
    int32_t enable_port[DS_AUDIO_MAX_PORTS] = {0};
    int32_t count = 0;
    bool mute;

    printf("\nSelect dsAudio Port to Apply Gain\n");
    printf("------------------------------------------\n");
    printf("\t#  %-20s%s\n\n","Audio Port", "Index");
    for(int32_t i = 0; i < gDSAudioNumberOfPorts; i++) {
        ret = dsGetAudioPort(gDSAudioPortConfiguration[i].typeid, gDSAudioPortConfiguration[i].index, &handle);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed to get the port handle for %s", gDSAudioPortConfiguration[i].port_name);
            continue;
        }

        ret = dsIsAudioPortEnabled(handle, &enabled);

        if(enabled == true) {
            enable_port[count] = i;
            printf("\t%d.  %-20s%-2d\n", count+1, gDSAudioPortConfiguration[i].port_name,
                                              gDSAudioPortConfiguration[i].index);
            count++;
        }
    }
    printf("------------------------------------------\n");
    if(count == 0) {
        printf("\nNo Ports Enabled\n");
        return;
    }

    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);
    if(choice < 1 || choice > count) {
        printf("Invalid Port choice\n");
        return;
    }

    port = enable_port[choice - 1];

    UT_LOG_DEBUG("Invoking dsGetAudioPort");
    ret = dsGetAudioPort(gDSAudioPortConfiguration[port].typeid, gDSAudioPortConfiguration[port].index, &handle);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed to get the %s", gDSAudioPortConfiguration[port].port_name);
        return;
    }

    printf("\nAudio Mute/Unmute[1:Mute, 2:UnMute]: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);
    if(choice < 1 || choice > 2) {
        printf("Invalid Mute choice\n");
        return;
    }

    if(choice == 1) {
        ret = dsSetAudioMute(handle, true);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed to set the mute to true for %s", gDSAudioPortConfiguration[port].port_name);
        }
        ret = dsIsAudioMute(handle, &mute);
        if(ret != dsERR_NONE || mute == false) {
            UT_LOG_ERROR("Failed to Set Audio Mute for %s", gDSAudioPortConfiguration[port].port_name);
        }
    }
    else if(choice == 2) {
        ret = dsSetAudioMute(handle, false);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed to set the mute to true for %s", gDSAudioPortConfiguration[port].port_name);
        }
        ret = dsIsAudioMute(handle, &mute);
        if(ret != dsERR_NONE || mute == true) {
            UT_LOG_ERROR("Failed to Set Audio UnMute for %s", gDSAudioPortConfiguration[port].port_name);
        }
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
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
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    dsAudioPortType_t port;
    int32_t choice;
    intptr_t handle;
    bool enabled    = false;
    int32_t enable_port[DS_AUDIO_MAX_PORTS] = {0};
    int32_t count = 0;
    uint32_t audioDelayMs = 0;

    printf("\nSelect dsAudio Port to Apply Delay\n");
    printf("------------------------------------------\n");
    printf("\t#  %-20s%s\n\n","Audio Port", "Index");
    for(int32_t i = 0; i < gDSAudioNumberOfPorts; i++) {
        if(gDSAudioPortConfiguration[i].typeid != dsAUDIOPORT_TYPE_HDMI &&
           gDSAudioPortConfiguration[i].typeid != dsAUDIOPORT_TYPE_HDMI_ARC &&
           gDSAudioPortConfiguration[i].typeid != dsAUDIOPORT_TYPE_SPDIF) {
            continue;
        }
        ret = dsGetAudioPort(gDSAudioPortConfiguration[i].typeid, gDSAudioPortConfiguration[i].index, &handle);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed to get the port handle for %s", gDSAudioPortConfiguration[i].port_name);
            continue;
        }

        ret = dsIsAudioPortEnabled(handle, &enabled);

        if(enabled == true) {
            enable_port[count] = i;
            printf("\t%d.  %-20s%-2d\n", count+1, gDSAudioPortConfiguration[i].port_name,
                                              gDSAudioPortConfiguration[i].index);
            count++;
        }
    }
    printf("------------------------------------------\n");
    if(count == 0) {
        printf("\nNo Ports Enabled\n");
        return;
    }

    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);
    if(choice < 1 || choice > count) {
        printf("Invalid Port choice\n");
        return;
    }

    port = enable_port[choice - 1];

    UT_LOG_DEBUG("Invoking dsGetAudioPort");
    ret = dsGetAudioPort(gDSAudioPortConfiguration[port].typeid, gDSAudioPortConfiguration[port].index, &handle);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed to get the %s", gDSAudioPortConfiguration[port].port_name);
        return;
    }

    printf("\nEnter Audio Delay in milli seconds[0 to 200]: ");
    scanf("%d", &audioDelayMs);
    readAndDiscardRestOfLine(stdin);
    if(audioDelayMs < 0 || audioDelayMs > 200) {
        printf("Invalid Audio Delay\n");
        return;
    }

    ret = dsSetAudioDelay(handle, audioDelayMs);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed to set audio delay to %s", gDSAudioPortConfiguration[port].port_name);
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
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
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t ret;
    int32_t index = 0;
    intptr_t handle;
    dsAudioFormat_t getAudioFormat;

    UT_LOG_DEBUG("Invoking dsGetAudioPort");
    ret = dsGetAudioPort(gDSAudioPortConfiguration[index].typeid, gDSAudioPortConfiguration[index].index, &handle);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed to get the port handle for %s", gDSAudioPortConfiguration[index].port_name);
    }

    UT_LOG_DEBUG("Invoking dsGetAudioFormat");
    ret = dsGetAudioFormat(handle, &getAudioFormat);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed to get the format");
    }

    UT_LOG_DEBUG("Audio Format: %d, Audio Format from Callback: %d", getAudioFormat, gAudioFormat);

    gAudioFormat = dsAUDIO_FORMAT_NONE;

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
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
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t ret;
    int32_t index = 0;
    intptr_t handle;
    int32_t choice = 0;

    UT_LOG_DEBUG("Invoking dsGetAudioPort");
    ret = dsGetAudioPort(gDSAudioPortConfiguration[index].typeid, gDSAudioPortConfiguration[index].index, &handle);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed to get the port handle for %s", gDSAudioPortConfiguration[index].port_name);
    }
    printf("\nEnable/Disable ATMOS Mode[1:Enable, 2:Disable]: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);

    if(choice == 1) {
        ret = dsSetAudioAtmosOutputMode(handle, true);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed to Enable ATMOS mode");
        }
    }
    else if(choice == 2) {
        ret = dsSetAudioAtmosOutputMode(handle, false);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed to Disable ATMOS mode");
        }
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
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
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    dsAudioPortType_t port;
    int32_t choice;
    intptr_t handle;
    bool enabled    = false;
    int32_t enable_port[DS_AUDIO_MAX_PORTS] = {0};
    int32_t count = 0;
    dsATMOSCapability_t capability = dsAUDIO_ATMOS_NOTSUPPORTED;

    printf("\nSelect dsAudio Port to Get ATMOS Capabilities\n");
    printf("------------------------------------------\n");
    printf("\t#  %-20s%s\n\n","Audio Port", "Index");
    for(int32_t i = 0; i < gDSAudioNumberOfPorts; i++) {
        if(gDSAudioPortConfiguration[i].typeid != dsAUDIOPORT_TYPE_HDMI &&
           gDSAudioPortConfiguration[i].typeid != dsAUDIOPORT_TYPE_HDMI_ARC) {
            continue;
        }
        ret = dsGetAudioPort(gDSAudioPortConfiguration[i].typeid, gDSAudioPortConfiguration[i].index, &handle);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed to get the port handle for %s", gDSAudioPortConfiguration[i].port_name);
            continue;
        }

        ret = dsIsAudioPortEnabled(handle, &enabled);

        if(enabled == true) {
            enable_port[count] = i;
            printf("\t%d.  %-20s%-2d\n", count+1, gDSAudioPortConfiguration[i].port_name,
                                              gDSAudioPortConfiguration[i].index);
            count++;
        }
    }
    printf("------------------------------------------\n");
    if(count == 0) {
        printf("\nNo Ports Enabled\n");
        return;
    }

    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);
    if(choice < 1 || choice > count) {
        printf("Invalid Port choice\n");
        return;
    }

    port = enable_port[choice - 1];

    UT_LOG_DEBUG("Invoking dsGetAudioPort");
    ret = dsGetAudioPort(gDSAudioPortConfiguration[port].typeid, gDSAudioPortConfiguration[port].index, &handle);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed to get the %s", gDSAudioPortConfiguration[port].port_name);
        return;
    }

    ret = dsGetSinkDeviceAtmosCapability(handle, &capability);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed to get the ATMOS caps of %s", gDSAudioPortConfiguration[port].port_name);
        return;
    }
    UT_LOG_DEBUG("ATMOS Capability of %s: %d, ATMOS change capablity and Status from Callback: %d, Statu: %d", capability, gAtosCapablity, gAtmosStatus);

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
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

    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    dsAudioPortType_t port;
    int32_t choice;
    intptr_t handle;
    bool enabled    = false;
    int32_t enable_port[DS_AUDIO_MAX_PORTS] = {0};
    int32_t count = 0;
    dsMS12AudioProfileList_t profiles;
    char *profileList[DS_AUDIO_MAX_MS12_PROFILES];

    printf("\nSelect dsAudio Port to Apply MS12 Profile\n");
    printf("------------------------------------------\n");
    printf("\t#  %-20s%s\n\n","Audio Port", "Index");
    for(int32_t i = 0; i < gDSAudioNumberOfPorts; i++) {
        ret = dsGetAudioPort(gDSAudioPortConfiguration[i].typeid, gDSAudioPortConfiguration[i].index, &handle);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed to get the port handle for %s", gDSAudioPortConfiguration[i].port_name);
            continue;
        }

        ret = dsGetMS12AudioProfileList(handle, &profiles);
        if((ret != dsERR_NONE) || (profiles.audioProfileCount <= 0)) {
            continue;
        }

        ret = dsIsAudioPortEnabled(handle, &enabled);

        if(enabled == true) {
            enable_port[count] = i;
            printf("\t%d.  %-20s%-2d\n", count+1, gDSAudioPortConfiguration[i].port_name,
                                              gDSAudioPortConfiguration[i].index);
            count++;
        }
    }
    printf("------------------------------------------\n");
    if(count == 0) {
        printf("\nNo Ports Enabled\n");
        return;
    }

    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);

    if(choice < 1 || choice > count) {
        printf("Invalid Port choice\n");
        return;
    }

    port = enable_port[choice - 1];

    UT_LOG_DEBUG("Invoking dsGetAudioPort");
    ret = dsGetAudioPort(gDSAudioPortConfiguration[port].typeid, gDSAudioPortConfiguration[port].index, &handle);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed to get the port handle for %s", gDSAudioPortConfiguration[port].port_name);
        return;
    }

    ret = dsGetMS12AudioProfileList(handle, &profiles);
    if((ret != dsERR_NONE) || (profiles.audioProfileCount <= 0)) {
        UT_LOG_ERROR("Failed to get audio profile list %s", gDSAudioPortConfiguration[port].port_name);
        return;
    }

    char* token = strtok(profiles.audioProfileList, " - ");
    int32_t i = 0;

    printf("\nSelect MS12 Profile\n");
    printf("------------------------------------------\n");
    printf("\t#  %-20s\n\n","MS12 Profile");
    while (token != NULL) {
        profileList[i] = token;
        printf("\t%d.  %-20s\n", i+1, profileList[i]);
        token = strtok(NULL, " - ");
        i++;
    }
    printf("------------------------------------------\n");

    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);

    if(choice < 1 || choice > profiles.audioProfileCount) {
        printf("Invalid profile choice\n");
        return;
    }

    ret = dsSetMS12AudioProfile(handle, profileList[choice-1]);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed to set audio profile %s for port %s", profiles.audioProfileList[choice-1], gDSAudioPortConfiguration[port].port_name);
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
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

    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    int32_t index = 0;
    intptr_t handle;
    bool mode;

    UT_LOG_DEBUG("Invoking dsGetAudioPort");
    ret = dsGetAudioPort(gDSAudioPortConfiguration[index].typeid, gDSAudioPortConfiguration[index].index, &handle);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed to get the port handle for %s", gDSAudioPortConfiguration[index].port_name);
    }

    ret = dsGetAssociatedAudioMixing(handle, &mode);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed to get the AssociatedAudioMixing status");
        return;
    }
    if(mode == false) {
        int32_t mixerbalance;
        UT_LOG_DEBUG("Enable AssociatedAudioMixing");
        ret = dsSetAssociatedAudioMixing(handle, true);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed to Enable AssociatedAudioMixing");
        }
        printf("\nSet Fader Control[-32(mute associated audio) to 32(mute main audio)]: ");
        scanf("%d", &mixerbalance);
        readAndDiscardRestOfLine(stdin);
        if(mixerbalance < -32 || mixerbalance > 32) {
            printf("Invalid Fader Control\n");
            return;
        }
        ret = dsSetFaderControl(handle, mixerbalance);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed to set Fader Control");
        }
    }
    else {
        UT_LOG_DEBUG("Disabling AssociatedAudioMixing");
        ret = dsSetAssociatedAudioMixing(handle, false);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed to Disabling AssociatedAudioMixing");
        }
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
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
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    int32_t index = 0;
    intptr_t handle;
    int32_t volume;
    int32_t aInput;

    UT_LOG_DEBUG("Invoking dsGetAudioPort");
    ret = dsGetAudioPort(gDSAudioPortConfiguration[index].typeid, gDSAudioPortConfiguration[index].index, &handle);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed to get the port handle for %s", gDSAudioPortConfiguration[index].port_name);
    }

    printf("\nSelect the mixer input[0: Primary, 1: System]: ");
    scanf("%d", &aInput);
    readAndDiscardRestOfLine(stdin);
    if(aInput < 0 || aInput > 1) {
        printf("Invalid mixer input\n");
        return;
    }
    printf("\nSet the Volume[0 to 100]: ");
    scanf("%d", &volume);
    readAndDiscardRestOfLine(stdin);
    if(volume < 0 || volume > 100) {
        printf("Invalid volume\n");
        return;
    }

    ret = dsSetAudioMixerLevels (handle, (dsAudioInput_t)aInput, volume);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed to Set the mixer level %d for %d input", volume, aInput);
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
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
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t ret;
    int32_t index = 0;
    intptr_t handle;
    int32_t language_type;
    char language[4] = {0};

    UT_LOG_DEBUG("Invoking dsGetAudioPort");
    ret = dsGetAudioPort(gDSAudioPortConfiguration[index].typeid, gDSAudioPortConfiguration[index].index, &handle);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed to get the port handle for %s", gDSAudioPortConfiguration[index].port_name);
    }

    printf("\nSelect the Language Type[1: Primary, 2: Secondary]: ");
    scanf("%d", &language_type);
    readAndDiscardRestOfLine(stdin);
    if(language_type < 1 || language_type > 2) {
        printf("Invalid language type\n");
        return;
    }

    printf("\nEnter 3 letter long language as per ISO 639-3: ");
    fgets(language, 4, stdin);
    readAndDiscardRestOfLine(stdin);
    if(language_type == 1) {
        ret = dsSetPrimaryLanguage(handle, language);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed to set Primary language %s", language);
        }
    }
    else {
        ret = dsSetSecondaryLanguage(handle, language);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed to set Secondary language %s", language);
        }
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
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
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    int32_t types = 0;
    bool enabled = false;

    for(int32_t i = 0; i < gDSAudioNumberOfPorts; i++) {
        if(gDSAudioPortConfiguration[i].typeid != dsAUDIOPORT_TYPE_HDMI_ARC) {
            continue;
        }
        ret = dsGetAudioPort(gDSAudioPortConfiguration[i].typeid, gDSAudioPortConfiguration[i].index, &handle);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed to get the port handle for %s", gDSAudioPortConfiguration[i].port_name);
            return;
        }

        break;
    }

    ret = dsIsAudioPortEnabled(handle, &enabled);

    if(enabled == false) {
        UT_LOG_ERROR("ARC Port is not enabled: %d", ret);
        return;
    }

    ret = dsGetSupportedARCTypes(handle, &types);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed to get the ARC Type %d", ret);
        return;
    }

    if(types == dsAUDIOARCSUPPORT_ARC) {
        printf("Connected Device ARC Type is: ARC\n");
    }
    else if(types == dsAUDIOARCSUPPORT_eARC ) {
        printf("Connected Device ARC Type is: eARC\n");
    }
    else {
        printf("Connected Device ARC Type is: Invalid\n");
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
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
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret;
    intptr_t handle;
    bool enabled = false;
    dsAudioSADList_t sad_list; 

    for(int32_t i = 0; i < gDSAudioNumberOfPorts; i++) {
        if(gDSAudioPortConfiguration[i].typeid != dsAUDIOPORT_TYPE_HDMI_ARC) {
            continue;
        }
        ret = dsGetAudioPort(gDSAudioPortConfiguration[i].typeid, gDSAudioPortConfiguration[i].index, &handle);
        if(ret != dsERR_NONE) {
            UT_LOG_ERROR("Failed to get the port handle for %s", gDSAudioPortConfiguration[i].port_name);
            return;
        }

        break;
    }

    ret = dsIsAudioPortEnabled(handle, &enabled);
    if(enabled == false || (ret != dsERR_NONE)) {
        UT_LOG_ERROR("ARC Port is not enabled: %d", ret);
        return;
    }

    printf("\nEnter SAD List count[1-15]: ");
    scanf("%d", &sad_list.count);
    readAndDiscardRestOfLine(stdin);
    if(sad_list.count < 1 || sad_list.count > 15) {
        printf("Invalid SAD Count\n");
        return;
    }

    for(int32_t i = 0; i < sad_list.count; i++) {
        printf("\nEnter %d SAD Value: ", i);
        scanf("%d", &sad_list.sad[i]);
    }
    readAndDiscardRestOfLine(stdin);

    ret = dsAudioSetSAD(handle, sad_list);
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed to set the SAD %d", ret);
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
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
    UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t ret;

    UT_LOG_DEBUG("Invoking dsAudioPortTerm");

    ret = dsAudioPortTerm();
    UT_LOG_DEBUG("Return status: %d", ret);
    if(ret != dsERR_NONE) {
        UT_LOG_DEBUG("Failed to terminate dsAudio: %d", ret);
    }

    UT_LOG_INFO("Out %s\n", __FUNCTION__);
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
    }
    UT_add_test(pSuite, "Audio Mute/Unmute", test_l3_dsAudio_set_audio_mute);
    UT_add_test(pSuite, "Set Audio Delay", test_l3_dsAudio_set_audio_delay);
    UT_add_test(pSuite, "Get Audio Format", test_l3_dsAudio_get_audio_format);
    UT_add_test(pSuite, "Set ATMOS Output Mode", test_l3_dsAudio_set_atmos_mode);
    UT_add_test(pSuite, "Get ATMOS Capabilities", test_l3_dsAudio_getConnected_atmoscaps);
    if(gSourceType == 0) {
        UT_add_test(pSuite, "Set MS12 Profiles", test_l3_dsAudio_ms12Profile);
    }
    UT_add_test(pSuite, "Set Associate Audio Mixing", test_l3_dsAudio_set_associate_audio_mixing);
    UT_add_test(pSuite, "Set Audio Mixer Levels", test_l3_dsAudio_set_audio_mixerlevels);
    UT_add_test(pSuite, "Primary/Seconday Language", test_l3_dsAudio_set_language);
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
