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
 * @defgroup DS_HDMIIn_HALTEST Device Settings HDMI Input HAL Tests
 * @{
 */

/**
 * @defgroup DS_HDMIIn_HALTEST_L1 Device Settings HDMI Input HAL Tests L1 File
 * @{
 * @parblock
 *
 * ### L1 Tests for DS HDMI Input HAL :
 *
 * Level 1 unit test cases for all APIs of Device Settings HDMI Input HAL
 *
 * **Pre-Conditions:**  None@n
 * **Dependencies:** None@n
 *
 * Refer to API Definition specification documentation : [ds-hdmi-in_halSpec.md](../../docs/pages/ds-hdmi-in_halSpec.md)
 * @endparblock
 */


/**
 * @file test_l3_dsHdmiIn.c
 *
 */

#include <string.h>
#include <stdlib.h>
#include "dsHdmiIn.h"

#include <ut.h>
#include <ut_log.h>
#include <ut_kvp_profile.h>
#include "test_parse_configuration.h"


/* Type Definitions */
typedef struct _ut_control_keyMapTable_t
{
    char* string;
    int32_t key;
} ut_control_keyMapTable_t;

/* Global Variables */
static int32_t gTestGroup = 3;
static int32_t gTestID    = 1;

static bool                    gConnectionStatus = false;
static dsHdmiInSignalStatus_t  gSignalStatus  = dsHDMI_IN_SIGNAL_STATUS_NONE;
static dsVideoPortResolution_t gVideoresolution;
static bool                    gAllmmode      = false;
static int64_t                 gaudio_latency = 0;
static int64_t                 gvideo_latency = 0;
static dsAviContentType_t      gavi_content_type;
static dsHdmiInStatus_t        gStatusChange;

/* Enum mapping tables */
/* dsHdmiInPort_t */
const static ut_control_keyMapTable_t dsHdmiInPort_mapTable [] = {
  { "dsHDMI_IN_PORT_NONE",     (int32_t)dsHDMI_IN_PORT_NONE },
  { "dsHDMI_IN_PORT_0",        (int32_t)dsHDMI_IN_PORT_0    },
  { "dsHDMI_IN_PORT_1",        (int32_t)dsHDMI_IN_PORT_1    },
  { "dsHDMI_IN_PORT_2",        (int32_t)dsHDMI_IN_PORT_2    },
  { "dsHDMI_IN_PORT_MAX",      (int32_t)dsHDMI_IN_PORT_MAX  },
  {  NULL, -1 }
};

/* dsHdmiInSignalStatus_t */
const static ut_control_keyMapTable_t dsHdmiInSignalStatus_mapTable [] = {
  { "dsHDMI_IN_SIGNAL_STATUS_NONE",            (int32_t)dsHDMI_IN_SIGNAL_STATUS_NONE         },
  { "dsHDMI_IN_SIGNAL_STATUS_NOSIGNAL",        (int32_t)dsHDMI_IN_SIGNAL_STATUS_NOSIGNAL     },
  { "dsHDMI_IN_SIGNAL_STATUS_UNSTABLE",        (int32_t)dsHDMI_IN_SIGNAL_STATUS_UNSTABLE     },
  { "dsHDMI_IN_SIGNAL_STATUS_NOTSUPPORTED",    (int32_t)dsHDMI_IN_SIGNAL_STATUS_NOTSUPPORTED },
  { "dsHDMI_IN_SIGNAL_STATUS_STABLE",          (int32_t)dsHDMI_IN_SIGNAL_STATUS_STABLE       },
  { "dsHDMI_IN_SIGNAL_STATUS_MAX",             (int32_t)dsHDMI_IN_SIGNAL_STATUS_MAX          },
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

/* dsVideoResolution_t */
const static ut_control_keyMapTable_t dsVideoResolution_mapTable [] = {
  { "dsVIDEO_PIXELRES_720x480",      (int32_t)dsVIDEO_PIXELRES_720x480   },
  { "dsVIDEO_PIXELRES_720x576",      (int32_t)dsVIDEO_PIXELRES_720x576   },
  { "dsVIDEO_PIXELRES_1280x720",     (int32_t)dsVIDEO_PIXELRES_1280x720  },
  { "dsVIDEO_PIXELRES_1366x768",     (int32_t)dsVIDEO_PIXELRES_1366x768  },
  { "dsVIDEO_PIXELRES_1920x1080",    (int32_t)dsVIDEO_PIXELRES_1920x1080 },
  { "dsVIDEO_PIXELRES_3840x2160",    (int32_t)dsVIDEO_PIXELRES_3840x2160 },
  { "dsVIDEO_PIXELRES_4096x2160",    (int32_t)dsVIDEO_PIXELRES_4096x2160 },
  { "dsVIDEO_PIXELRES_MAX",          (int32_t)dsVIDEO_PIXELRES_MAX       },
  {  NULL, -1 }
};

/* dsVideoAspectRatio_t */
const static ut_control_keyMapTable_t dsVideoAspectRatio_mapTable [] = {
  { "dsVIDEO_ASPECT_RATIO_4x3",     (int32_t)dsVIDEO_ASPECT_RATIO_4x3  },
  { "dsVIDEO_ASPECT_RATIO_16x9",    (int32_t)dsVIDEO_ASPECT_RATIO_16x9 },
  { "dsVIDEO_ASPECT_RATIO_MAX",     (int32_t)dsVIDEO_ASPECT_RATIO_MAX  },
  {  NULL, -1 }
};

/* dsVideoStereoScopicMode_t */
const static ut_control_keyMapTable_t dsVideoStereoScopicMode_mapTable [] = {
  { "dsVIDEO_SSMODE_UNKNOWN",            (int32_t)dsVIDEO_SSMODE_UNKNOWN            },
  { "dsVIDEO_SSMODE_2D",                 (int32_t)dsVIDEO_SSMODE_2D                 },
  { "dsVIDEO_SSMODE_3D_SIDE_BY_SIDE",    (int32_t)dsVIDEO_SSMODE_3D_SIDE_BY_SIDE    },
  { "dsVIDEO_SSMODE_3D_TOP_AND_BOTTOM",  (int32_t)dsVIDEO_SSMODE_3D_TOP_AND_BOTTOM  },
  { "dsVIDEO_SSMODE_MAX",                (int32_t)dsVIDEO_SSMODE_MAX                },
  {  NULL, -1 }
};

/* dsVideoFrameRate_t */
const static ut_control_keyMapTable_t dsVideoFrameRate_mapTable [] = {
  { "dsVIDEO_FRAMERATE_UNKNOWN",         (int32_t)dsVIDEO_FRAMERATE_UNKNOWN },
  { "dsVIDEO_FRAMERATE_24",              (int32_t)dsVIDEO_FRAMERATE_24      },
  { "dsVIDEO_FRAMERATE_25",              (int32_t)dsVIDEO_FRAMERATE_25      },
  { "dsVIDEO_FRAMERATE_30",              (int32_t)dsVIDEO_FRAMERATE_30      },
  { "dsVIDEO_FRAMERATE_60",              (int32_t)dsVIDEO_FRAMERATE_60      },
  { "dsVIDEO_FRAMERATE_23dot98",         (int32_t)dsVIDEO_FRAMERATE_23dot98 },
  { "dsVIDEO_FRAMERATE_29dot97",         (int32_t)dsVIDEO_FRAMERATE_29dot97 },
  { "dsVIDEO_FRAMERATE_50",              (int32_t)dsVIDEO_FRAMERATE_50      },
  { "dsVIDEO_FRAMERATE_59dot94",         (int32_t)dsVIDEO_FRAMERATE_59dot94 },
  { "dsVIDEO_FRAMERATE_MAX",             (int32_t)dsVIDEO_FRAMERATE_MAX     },
  {  NULL, -1 }
};

/* dsAviContentType_t */
const static ut_control_keyMapTable_t dsAviContentType_mapTable [] = {
  { "dsAVICONTENT_TYPE_GRAPHICS",    (int32_t)dsAVICONTENT_TYPE_GRAPHICS },
  { "dsAVICONTENT_TYPE_PHOTO",       (int32_t)dsAVICONTENT_TYPE_PHOTO    },
  { "dsAVICONTENT_TYPE_CINEMA",      (int32_t)dsAVICONTENT_TYPE_CINEMA   },
  { "dsAVICONTENT_TYPE_GAME",        (int32_t)dsAVICONTENT_TYPE_GAME     },
  { "dsAVICONTENT_TYPE_INVALID",     (int32_t)dsAVICONTENT_TYPE_INVALID  },
  { "dsAVICONTENT_TYPE_MAX",         (int32_t)dsAVICONTENT_TYPE_MAX      },
  {  NULL, -1 }
};

/* dsVideoPlaneType_t */
const static ut_control_keyMapTable_t dsVideoPlaneType_mapTable [] = {
  { "dsVideoPlane_PRIMARY",     (int32_t)dsVideoPlane_PRIMARY   },
  { "dsVideoPlane_SECONDARY",   (int32_t)dsVideoPlane_SECONDARY },
  { "dsVideoPlane_MAX",         (int32_t)dsVideoPlane_MAX       },
  {  NULL, -1 }
};

/* dsVideoZoom_t */
const static ut_control_keyMapTable_t dsVideoZoom_mapTable [] = {
  { "dsVIDEO_ZOOM_UNKNOWN",          (int32_t)dsVIDEO_ZOOM_UNKNOWN           },
  { "dsVIDEO_ZOOM_NONE",             (int32_t)dsVIDEO_ZOOM_NONE              },
  { "dsVIDEO_ZOOM_FULL",             (int32_t)dsVIDEO_ZOOM_FULL              },
  { "dsVIDEO_ZOOM_LB_16_9",          (int32_t)dsVIDEO_ZOOM_LB_16_9           },
  { "dsVIDEO_ZOOM_LB_14_9",          (int32_t)dsVIDEO_ZOOM_LB_14_9           },
  { "dsVIDEO_ZOOM_CCO",              (int32_t)dsVIDEO_ZOOM_CCO               },
  { "dsVIDEO_ZOOM_PAN_SCAN",         (int32_t)dsVIDEO_ZOOM_PAN_SCAN          },
  { "dsVIDEO_ZOOM_LB_2_21_1_ON_4_3", (int32_t)dsVIDEO_ZOOM_LB_2_21_1_ON_4_3  },
  { "dsVIDEO_ZOOM_LB_2_21_1_ON_16_9",(int32_t)dsVIDEO_ZOOM_LB_2_21_1_ON_16_9 },
  { "dsVIDEO_ZOOM_PLATFORM",         (int32_t)dsVIDEO_ZOOM_PLATFORM          },
  { "dsVIDEO_ZOOM_16_9_ZOOM",        (int32_t)dsVIDEO_ZOOM_16_9_ZOOM         },
  { "dsVIDEO_ZOOM_PILLARBOX_4_3",    (int32_t)dsVIDEO_ZOOM_PILLARBOX_4_3     },
  { "dsVIDEO_ZOOM_WIDE_4_3",         (int32_t)dsVIDEO_ZOOM_WIDE_4_3          },
  { "dsVIDEO_ZOOM_MAX",              (int32_t)dsVIDEO_ZOOM_MAX               },
  {  NULL, -1 }
};

/* tv_hdmi_edid_version_t */
const static ut_control_keyMapTable_t tv_hdmi_edid_version_mapTable [] = {
  { "HDMI_EDID_VER_14",     (int32_t)HDMI_EDID_VER_14  },
  { "HDMI_EDID_VER_20",     (int32_t)HDMI_EDID_VER_20  },
  { "HDMI_EDID_VER_MAX",    (int32_t)HDMI_EDID_VER_MAX },
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
 * @brief Callback function for HdmiIn connection status.
 *
 * This function is invoked whenever a change occurs in the Hdmi connection.
 */
static void hdmiInConnectCB(dsHdmiInPort_t Port, bool isPortConnected)
{
    UT_LOG_INFO("Received Connection status callback port: %s, Connection: %s",
                 ut_control_GetMapString(dsHdmiInPort_mapTable, Port),
                 ut_control_GetMapString(bool_mapTable, isPortConnected));

    gConnectionStatus = isPortConnected;
}

/**
 * @brief Callback function for HdmiIn signal change.
 *
 * This function is invoked whenever a signal change occurs in the Hdmi connection.
 */
static void hdmiInSignalChangeCB(dsHdmiInPort_t port, dsHdmiInSignalStatus_t sigStatus)
{
    UT_LOG_INFO("Received SignalChange status callback port: %s, sigstatus: %s",
                 ut_control_GetMapString(dsHdmiInPort_mapTable, port),
                 ut_control_GetMapString(dsHdmiInSignalStatus_mapTable, sigStatus));

    gSignalStatus = sigStatus;
}

/**
 * @brief Callback function for HdmiIn status change.
 *
 * This function is invoked whenever a status change occurs in the Hdmi connection.
 */
static void hdmiInStatusChangeCB(dsHdmiInStatus_t inputStatus)
{
    UT_LOG_INFO("Received statuschange callback isPresented: %s, activeport: %s",
                 ut_control_GetMapString(bool_mapTable, inputStatus.isPresented),
                 ut_control_GetMapString(dsHdmiInPort_mapTable, inputStatus.activePort));

    for(int i = 0 ; i < dsHDMI_IN_PORT_MAX ; i++) {
         
         if(!(inputStatus.isPresented))
                 continue;

         UT_LOG_INFO("Received statuschange callback isPortConnected: %s, activeport: %s",
                 ut_control_GetMapString(bool_mapTable, inputStatus.isPortConnected[i]),
                 ut_control_GetMapString(dsHdmiInPort_mapTable, inputStatus.activePort));
    }

    gStatusChange = inputStatus;
}

/**
 * @brief Callback function for HdmiIn Video Mode change.
 *
 * This function is invoked whenever a Video Mode change occurs in the Hdmi connection.
 */
static void hdmiInVideoModeUpdateCB(dsHdmiInPort_t port, dsVideoPortResolution_t videoResolution)
{
    UT_LOG_INFO("Received videomode change callback port:%s resolution name: %s, pixelResolution: %s\t" 
                 "aspectRatio:%s, stereoScopicMode:%s, frameRate:%s, interlaced:%s\t",
                 ut_control_GetMapString(dsHdmiInPort_mapTable, port),
                 videoResolution.name, 
                 ut_control_GetMapString(dsVideoResolution_mapTable, videoResolution.pixelResolution),
                 ut_control_GetMapString(dsVideoAspectRatio_mapTable, videoResolution.aspectRatio),
                 ut_control_GetMapString(dsVideoStereoScopicMode_mapTable, videoResolution.stereoScopicMode),
                 ut_control_GetMapString(dsVideoFrameRate_mapTable, videoResolution.frameRate),
                 ut_control_GetMapString(bool_mapTable, videoResolution.interlaced));

                 gVideoresolution = videoResolution;
}

/**
 * @brief Callback function for HdmiIn Allmmode change.
 *
 * This function is invoked whenever a Allmmode change occurs in the Hdmi connection.
 */
static void hdmiInAllmChangeCB(dsHdmiInPort_t port, bool allm_mode )
{
    UT_LOG_INFO("Received AllmChange status callback port: %s, sigstatus: %s",
                 ut_control_GetMapString(dsHdmiInPort_mapTable, port),
                 ut_control_GetMapString(bool_mapTable, allm_mode));

    gAllmmode = allm_mode;
}

/**
 * @brief Callback function for HdmiIn Allmmode change.
 *
 * This function is invoked whenever a Allmmode change occurs in the Hdmi connection.
 */
static void hdmiInAVLatencyChangeCB(int audio_latency, int video_latency)
{
    UT_LOG_INFO("Received AVlatencyChange status callback audio_latency: %d\t"
                 "video_latency:%d \t", audio_latency , video_latency);

    gaudio_latency = audio_latency;
    gvideo_latency = video_latency;
}

/**
 * @brief Callback function for HdmiIn Allmmode change.
 *
 * This function is invoked whenever a Allmmode change occurs in the Hdmi connection.
 */
static void hdmiInAviContentTypeChangeCB(dsHdmiInPort_t port, dsAviContentType_t avi_content_type)
{
    UT_LOG_INFO("Received AviContentType change callback port: %s, avi_content_type: %d\t"
                 "video_latency:%d\t",
                 ut_control_GetMapString(dsHdmiInPort_mapTable, port),
                 ut_control_GetMapString(dsAviContentType_mapTable, avi_content_type)),

    gavi_content_type = avi_content_type;
}


/**
* @brief This test initializes the HdmiIn Module.
*
* This test function initializes the HdmiIn Module.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 001@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [ds-hdmi-in_halSpec.md](../../docs/pages/ds-hdmi-in_halSpec.md)
*/
void test_l3_HdmiIn_initialize(void)
{
    gTestID = 1;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;

    /* Initialize the HdmiIn Module */
    UT_LOG_INFO("Calling dsHdmiInInit()");
    ret = dsHdmiInInit();
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsHdmiInInit() dsError_t:[%s]", ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsHdmiInInit() dsError_t:[%s]", ut_control_GetMapString(dsError_mapTable, ret));
    }

    /* Register connection status callback */
    UT_LOG_INFO("Calling dsHdmiInRegisterConnectCB(CBFunc:[0x%0X])", hdmiInConnectCB);
    ret = dsHdmiInRegisterConnectCB(hdmiInConnectCB);
    if (ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsHdmiInRegisterConnectCB(CBFunc:[0x%0X]) dsError_t:[%s]",
                        hdmiInConnectCB, ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsHdmiInRegisterConnectCB(CBFunc:[0x%0X]) dsError_t:[%s]",
                        hdmiInConnectCB, ut_control_GetMapString(dsError_mapTable, ret));
    }

    /* Register Signal change callback */
    UT_LOG_INFO("Calling dsHdmiInRegisterSignalChangeC(cbFun:[0x%0X])", hdmiInSignalChangeCB);
    ret = dsHdmiInRegisterSignalChangeCB(hdmiInSignalChangeCB);
    if (ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsHdmiInRegisterSignalChangeC(cbFun:[0x%0X]) dsError_t:[%s]",
                        hdmiInSignalChangeCB, ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsHdmiInRegisterSignalChangeC(cbFun:[0x%0X]) dsError_t:[%s]",
                        hdmiInSignalChangeCB, ut_control_GetMapString(dsError_mapTable, ret));
    }

    /* Register Status change callback */
    UT_LOG_INFO("Calling dsHdmiInRegisterStatusChangeCB(cbFun:[0x%0X])", hdmiInStatusChangeCB);
    ret = dsHdmiInRegisterStatusChangeCB(hdmiInStatusChangeCB);
    if (ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsHdmiInRegisterStatusChangeCB(cbFun:[0x%0X]) dsError_t:[%s]",
                        hdmiInStatusChangeCB, ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsHdmiInRegisterStatusChangeCB(cbFun:[0x%0X]) dsError_t:[%s]",
                        hdmiInStatusChangeCB, ut_control_GetMapString(dsError_mapTable, ret));
    }

    /* Register Video Mode Update callback */
    UT_LOG_INFO("Calling dsHdmiInRegisterVideoModeUpdateCB(cbFun:[0x%0X])", hdmiInVideoModeUpdateCB);
    ret = dsHdmiInRegisterVideoModeUpdateCB(hdmiInVideoModeUpdateCB);
    if (ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsHdmiInRegisterVideoModeUpdateCB(cbFun:[0x%0X]) dsError_t:[%s]",
                        hdmiInVideoModeUpdateCB, ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsHdmiInRegisterVideoModeUpdateCB(cbFun:[0x%0X]) dsError_t:[%s]",
                        hdmiInVideoModeUpdateCB, ut_control_GetMapString(dsError_mapTable, ret));
    }

    /* Register Allm changes callback */
    UT_LOG_INFO("Calling dsHdmiInRegisterAllmChangeCB(cbFun:[0x%0X])", hdmiInAllmChangeCB);
    ret = dsHdmiInRegisterAllmChangeCB(hdmiInAllmChangeCB);
    if (ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsHdmiInRegisterAllmChangeCB(cbFun:[0x%0X]) dsError_t:[%s]",
                        hdmiInAllmChangeCB, ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsHdmiInRegisterAllmChangeCB(cbFun:[0x%0X]) dsError_t:[%s]",
                        hdmiInAllmChangeCB, ut_control_GetMapString(dsError_mapTable, ret));
    }

    /* Register AV latency changes callback */
    UT_LOG_INFO("Calling dsHdmiInRegisterAVLatencyChangeCB(cbFun:[0x%0X])", hdmiInAVLatencyChangeCB);
    ret = dsHdmiInRegisterAVLatencyChangeCB(hdmiInAVLatencyChangeCB);
    if (ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsHdmiInRegisterAVLatencyChangeCB(cbFun:[0x%0X]) dsError_t:[%s]",
                        hdmiInAVLatencyChangeCB, ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsHdmiInRegisterAVLatencyChangeCB(cbFun:[0x%0X]) dsError_t:[%s]",
                        hdmiInAVLatencyChangeCB, ut_control_GetMapString(dsError_mapTable, ret));
    }

    /* Register AVI Content changes callback */
    UT_LOG_INFO("Calling dsHdmiInRegisterAviContentTypeChangeCB(cbFun:[0x%0X])", hdmiInAviContentTypeChangeCB);
    ret = dsHdmiInRegisterAviContentTypeChangeCB(hdmiInAviContentTypeChangeCB);
    if (ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsHdmiInRegisterAviContentTypeChangeCB(cbFun:[0x%0X]) dsError_t:[%s]",
                        hdmiInAviContentTypeChangeCB, ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsHdmiInRegisterAviContentTypeChangeCB(cbFun:[0x%0X]) dsError_t:[%s]",
                        hdmiInAviContentTypeChangeCB, ut_control_GetMapString(dsError_mapTable, ret));
    }

    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test get number of input ports.
*
* This test function gets HdmiInput ports on platform.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 002@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [ds-hdmi-in_halSpec.md](../../docs/pages/ds-hdmi-in_halSpec.md)
*/
void test_l3_HdmiIn_get_inputports(void)
{
    gTestID = 2;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    uint8_t numInputs = 0;
    dsError_t ret   = dsERR_NONE;

    UT_LOG_INFO("Calling dsHdmiInGetNumberOfInputs");
    ret = dsHdmiInGetNumberOfInputs(&numInputs);
    if(ret != dsERR_NONE)
    {
       UT_LOG_ERROR("Result: Failed to Get NumberOfInputsPorts:[%s]",ut_control_GetMapString(dsError_mapTable, ret));
    } else {
       UT_LOG_INFO("Result: NumberOfInputsPorts:[%d]",numInputs);
       if(!numInputs)
           UT_LOG_INFO("Result: Platform does not supports HdmiIn Ports");
    }

    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test get number of input ports.
*
* This test function gets HdmiInput ports on platform.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 003@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [ds-hdmi-in_halSpec.md](../../docs/pages/ds-hdmi-in_halSpec.md)
*/
void test_l3_HdmiIn_get_status(void)
{
    gTestID = 3;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret   = dsERR_NONE;
    dsHdmiInStatus_t inputstatus;
    
    UT_LOG_INFO("Calling dsHdmiInGetStatus");
    ret = dsHdmiInGetStatus(&inputstatus);
    if(ret != dsERR_NONE)
    {
        UT_LOG_ERROR("Result: Failed to Get HDMI input port status:[%s]",ut_control_GetMapString(dsError_mapTable, ret));
    } else {
             UT_LOG_INFO("Result HDMI input port status isPresented: %s, activeport: %s",
                 ut_control_GetMapString(bool_mapTable, inputstatus.isPresented),
                 ut_control_GetMapString(dsHdmiInPort_mapTable, inputstatus.activePort));

             for(int i = 0 ; i < dsHDMI_IN_PORT_MAX ; i++) {

                  if(!(inputstatus.isPresented))
                     continue;

                  UT_LOG_INFO("Result: HDMI port connected info isPortConnected: %s, activeport: %s",
                     ut_control_GetMapString(bool_mapTable, inputstatus.isPortConnected[i]),
                     ut_control_GetMapString(dsHdmiInPort_mapTable, inputstatus.activePort));
             }
    } 
    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test to select port.
*
* This test function selects HdmiInput port on platform.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 004@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [ds-hdmi-in_halSpec.md](../../docs/pages/ds-hdmi-in_halSpec.md)
*/
void test_l3_HdmiIn_select_port(void)
{
    gTestID = 4;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    
    dsError_t ret   = dsERR_NONE;
    dsHdmiInPort_t port = dsHDMI_IN_PORT_MAX;
    int32_t select; 
    bool audmix;
    dsVideoPlaneType_t videoplanetype;
    bool topmost;
    uint8_t numInputPorts = 0;
 
    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/numberOfPorts");

    printf(" \n================Please Select Inputs==================\n");

    printf("\n*******Enter the port number to select*******\n");
    scanf("%d", &select);
    readAndDiscardRestOfLine(stdin);

    if(select <= 0 || select > numInputPorts) 
    {
       printf("\nInvalid port selected\n");
       goto exit;    
    }

    port = select;

    printf("\n*******Enter the audiomix to select*******\t"
                     "Acceptable inputs are:\t"
                     "true (i.e 1)\t"
                     "false(i.e 0)\t"                    
            "******************************************\n");
    scanf("%d", &select);
    readAndDiscardRestOfLine(stdin);
    if(select < 0 || select > 1)
    {
       printf("\nInvalid audmix selected\n");
       goto exit;
    }
   
    audmix = (bool)select;

    printf("\n*******Enter the videoplanetype to select*******\n");
    for(dsVideoPlaneType_t i = dsVideoPlane_PRIMARY ; i < dsVideoPlane_MAX ; i++)
    {
          UT_LOG_INFO("\n Available videoplane type: %s, videoplane number: %d \n",
                 ut_control_GetMapString(dsVideoPlaneType_mapTable,i));
    }
    printf("\n**************************************************\n");
    scanf("%d", &select);
    readAndDiscardRestOfLine(stdin);
    if(select < 0 || select >= dsVideoPlane_MAX)
    {
       printf("\nInvalid video plane type selected\n");
       goto exit;
    }

    videoplanetype = (dsVideoPlaneType_t)select;

    printf("\n*******Enter the topmost to select*******\t"
                     "Acceptable inputs are:\t"
                     "true (i.e 1)\t"
                     "false(i.e 0)\t"
            "******************************************\n");
    scanf("%d", &select);
    readAndDiscardRestOfLine(stdin);
    if(select < 0 || select > 1)
    {
       printf("\nInvalid audmix selected\n");
       goto exit;
    }
    
    topmost = (bool)select;

    ret = dsHdmiInSelectPort(port , audmix , videoplanetype , topmost);
    if(ret != dsERR_NONE)
    {
       UT_LOG_ERROR("Result: Failed to select the Hdmi input port:[%s]",ut_control_GetMapString(dsError_mapTable, ret));
    } else {
           UT_LOG_INFO("Result : dsHdmiInSelectPort: %s, portnumber: %d",
                 ut_control_GetMapString(dsHdmiInPort_mapTable, port), port);
    }
       
exit:
UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test to scale video.
*
* This test function is to scale video of selected HdmiInput port on platform.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 005@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [ds-hdmi-in_halSpec.md](../../docs/pages/ds-hdmi-in_halSpec.md)
*/
void test_l3_HdmiIn_scale_video(void)
{
    gTestID = 5;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret   = dsERR_NONE;
    int32_t x = 0 , y = 0, width = 0 , height = 0;

    printf(" \n================Please Select Inputs==================\n");
    
    printf("\n*******Enter the x coordinate to select*******\t"
                     "Acceptable inputs are:\t"
                     "Min is 0\t"
                     "Max is based on the current resolution\t"
              "**********************************************\n");
   scanf("%d",&x);
   readAndDiscardRestOfLine(stdin);
   if(x < 0)
   {
      printf("\n invalid x coordinate selected \n");
      goto exit;
   }

   printf("\n*******Enter the y coordinate to select*******\t"
                     "Acceptable inputs are:\t"
                     "Min is 0\t"
                     "Max is based on the current resolution\t"
             "**********************************************\n");
   scanf("%d",&y);
   readAndDiscardRestOfLine(stdin);
   if(y < 0)
   {
      printf("\n invalid y coordinate selected \n");
      goto exit;
   }

   printf("\n*******Enter the width to select***************\t"
                     "Acceptable inputs are:\t"
                     "Min is 0\t"
                     "Max is based on the current resolution\t"
            "**********************************************\n");
   scanf("%d",&width);
   readAndDiscardRestOfLine(stdin);
   if(width < 0)
   {
      printf("\n invalid width selected \n");
      goto exit;
   }

   printf("\n*******Enter the height to select**************\t"
                     "Acceptable inputs are:\t"
                     "Min is 0\t"
                     "Max is based on the current resolution\t"
             "**********************************************\n");
   scanf("%d",&height);
   readAndDiscardRestOfLine(stdin);
   if(width < 0)
   {
      printf("\n invalid height selected \n");
      goto exit;
   }

  ret = dsHdmiInScaleVideo(x, y, width, height);
  if(ret != dsERR_NONE)
  {
     UT_LOG_ERROR("Result: Failed to dsHdmiInScaleVideo:[%s]",ut_control_GetMapString(dsError_mapTable, ret));
  } else {
     UT_LOG_INFO("Result : Passed dsHdmiInScaleVideo paramsx : %d, y : %d, heitht : %d , width : %d",
                  x, y , width, height);
  }

exit:
UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test to select zoom mode.
*
* This test function is select zoom mode of selected HdmiInput port on platform.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 006@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [ds-hdmi-in_halSpec.md](../../docs/pages/ds-hdmi-in_halSpec.md)
*/
void test_l3_HdmiIn_zoom_mode(void)
{
    gTestID = 6;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret   = dsERR_NONE;
    int select;
    dsVideoZoom_t mode;

    printf("\n===================Select Zoom Mode================\n");
    printf("\n**************Availabe Zoom Modes are****************\n");
    for(dsVideoZoom_t i = dsVIDEO_ZOOM_NONE ; i < dsVIDEO_ZOOM_MAX ; i++)
    {
           UT_LOG_INFO("%s : %d", ut_control_GetMapString(dsVideoZoom_mapTable, i) , i);
    }
    printf("\n******************************************************\n");
    scanf("%d",&select);
    readAndDiscardRestOfLine(stdin);
    if(select < 0 || select > dsVIDEO_ZOOM_MAX)
    {
      printf("\n invalid zoom mode selected \n");
      goto exit;
    }  
    
    mode = (dsVideoZoom_t)select;
    ret = dsHdmiInSelectZoomMode(mode);
    if(ret != dsERR_NONE)
    {
       UT_LOG_ERROR("Result: Failed to dsHdmiInSelectZoomMode Error:[%s]",ut_control_GetMapString(dsError_mapTable, ret));
    } else {
           UT_LOG_INFO("Result : dsHdmiInSelectZoomMode: %s, selected: %d",
                 ut_control_GetMapString(dsVideoZoom_mapTable, mode), mode);
    }

exit:
UT_LOG_INFO("Out %s", __FUNCTION__);
    
}

/**
* @brief This test to get current video mode.
*
* This test function is to get current video mode of selected HdmiInput port on platform.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 007@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [ds-hdmi-in_halSpec.md](../../docs/pages/ds-hdmi-in_halSpec.md)
*/
void test_l3_HdmiIn_video_mode(void)
{
    gTestID = 7;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret   = dsERR_NONE;
    dsVideoPortResolution_t resolution;
    
    ret = dsHdmiInGetCurrentVideoMode(&resolution);
    if(ret != dsERR_NONE)
    {
       UT_LOG_ERROR("Result: Failed dsHdmiInGetCurrentVideoMode Error:[%s]",ut_control_GetMapString(dsError_mapTable, ret));
    } else {
       UT_LOG_INFO("Result: Passed dsHdmiInGetCurrentVideoMode resolution name: %s, pixelResolution: %si\t"
                      "aspectRatio:%s, stereoScopicMode:%s, frameRate:%s, interlaced:%s ",
                      resolution.name,
                      ut_control_GetMapString(dsVideoResolution_mapTable, resolution.pixelResolution),
                      ut_control_GetMapString(dsVideoAspectRatio_mapTable, resolution.aspectRatio),
                      ut_control_GetMapString(dsVideoStereoScopicMode_mapTable, resolution.stereoScopicMode),
                      ut_control_GetMapString(dsVideoFrameRate_mapTable, resolution.frameRate),
                      ut_control_GetMapString(bool_mapTable, resolution.interlaced));
    }

    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test to check ARC port.
*
* This test function is to check selected HdmiInput port on platform is ARC or not.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 008@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [ds-hdmi-in_halSpec.md](../../docs/pages/ds-hdmi-in_halSpec.md)
*/
void test_l3_HdmiIn_arc_port(void)
{
    gTestID = 8;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret   = dsERR_NONE;
    int select;
    dsHdmiInPort_t iport = dsHDMI_IN_PORT_NONE;
    bool isarcport = false;
    uint8_t numInputPorts = 0;

    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/numberOfPorts");
    printf("\n**********Please select port***********\n");
    scanf("%d", &select);
    readAndDiscardRestOfLine(stdin);
    
    if(select <= 0 || select >numInputPorts)
    {
      printf("\n invalid port selected\n");
      goto exit;
    }

    iport = select;
    ret = dsIsHdmiARCPort(iport , &isarcport);
    if(ret != dsERR_NONE)
    {
       UT_LOG_ERROR("Result: Failed dsIsHdmiARCPort Error:[%s]",ut_control_GetMapString(dsError_mapTable, ret));
    } else {
           UT_LOG_INFO("Result : Passed dsIsHdmiARCPort port type: %s, port isarc: %s , portnumber: %d",
                 ut_control_GetMapString(dsHdmiInPort_mapTable, iport),
                 ut_control_GetMapString(bool_mapTable, isarcport),iport);
    }

exit:
UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test to get edid.
*
* This test function is to get edid bytes of  selected HdmiInput port on platform.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 009@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [ds-hdmi-in_halSpec.md](../../docs/pages/ds-hdmi-in_halSpec.md)
*/
void test_l3_HdmiIn_get_edid(void)
{
    gTestID = 9;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret   = dsERR_NONE;
    int length = 0;
    unsigned char edidbytes[255] = {0};
    int select;
    dsHdmiInPort_t port = dsHDMI_IN_PORT_NONE;
    uint8_t numInputPorts = 0;

    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/numberOfPorts");
    printf("\n**********Please select port***********\n");
    scanf("%d", &select);
    readAndDiscardRestOfLine(stdin);

    if(select <= 0 || select >numInputPorts)
    {
      printf("\n invalid port selected\n");
      goto exit;
    }

    port = select;
    ret = dsGetEDIDBytesInfo(port, edidbytes, &length);
    if(ret != dsERR_NONE)
    {
       UT_LOG_ERROR("Result: Failed dsGetEDIDBytesInfo Error:[%s]",ut_control_GetMapString(dsError_mapTable, ret));
    } else {
           UT_LOG_INFO("Result : Passed dsGetEDIDBytesInfo port type: %s, \n portnumber: %d,\n\t"
                         "edidinfo: %s", ut_control_GetMapString(dsHdmiInPort_mapTable, port), port, edidbytes);
    }

exit:
UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test to get spdinfo.
*
* This test function is to get spdinfo of  selected HdmiInput port on platform.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 010@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [ds-hdmi-in_halSpec.md](../../docs/pages/ds-hdmi-in_halSpec.md)
*/
void test_l3_HdmiIn_spd_info(void)
{
    gTestID = 10;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret   = dsERR_NONE;
    unsigned char spdinfo[sizeof(struct dsSpd_infoframe_st)] = {0};
    dsHdmiInPort_t port = dsHDMI_IN_PORT_NONE;
    int select;
    uint8_t numInputPorts = 0;
    

    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/numberOfPorts");
    printf("\n**********Please select port***********\n");
    scanf("%d", &select);
    readAndDiscardRestOfLine(stdin);

    if(select <= 0 || select >numInputPorts)
    {
      printf("\n invalid port selected\n");
      goto exit;
    }
   
    port = select;
   
    ret = dsGetHDMISPDInfo(port, spdinfo); 
    if(ret != dsERR_NONE)
    {
       UT_LOG_ERROR("Result: Failed dsGetHDMISPDInfo Error:[%s]",ut_control_GetMapString(dsError_mapTable, ret));
    } else {
          /* UT_LOG_INFO("Result : Passed dsGetHDMISPDInfo porttype: %s, portnumber: %s,\t"
                           "pkttype: %d, version: %d, length: %d, rsd: %d, checksum: %d\t"
                           "vendor_name: %s, product_des: %s, source_info: %d",
                           ut_control_GetMapString(dsHdmiInPort_mapTable, port), port,
                           spdinfo.pkttype, spdinfo.version, spdinfo.length, spdinfo.rsd,
                           spdinfo.checksum, spdinfo.vendor_name, spdinfo.product_des,
                           spdinfo.source_info);*/
    }

exit:
UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test to set edidversion.
*
* This test function is to set edidversion of HdmiInput port on platform.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 011@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [ds-hdmi-in_halSpec.md](../../docs/pages/ds-hdmi-in_halSpec.md)
*/
void test_l3_HdmiIn_set_edidversion(void)
{
    gTestID = 11;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret   = dsERR_NONE;
    int select;
    dsHdmiInPort_t port = dsHDMI_IN_PORT_NONE;
    tv_hdmi_edid_version_t edidver;
    uint8_t numInputPorts = 0;

    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/numberOfPorts");
    printf("\n**********Please select port***********\n");
    scanf("%d", &select);
    readAndDiscardRestOfLine(stdin);

    if(select <= 0 || select >numInputPorts)
    {
      printf("\n invalid port selected\n");
      goto exit;
    }

    port = select;
  
    printf("\n*********Please select from availabe edid versions are***********\n");
    for(tv_hdmi_edid_version_t i = HDMI_EDID_VER_14 ; i < HDMI_EDID_VER_MAX ; i++)
    {
           UT_LOG_INFO("%s : %d", ut_control_GetMapString(tv_hdmi_edid_version_mapTable, i) , i);
    }
    printf("\n**************************************************************\n");

    scanf("%d", &select);
    readAndDiscardRestOfLine(stdin);

    if(select < HDMI_EDID_VER_14 || select > HDMI_EDID_VER_MAX)
    {
      printf("\n invalid edid selected\n");
      goto exit;
    }
    
    edidver = (tv_hdmi_edid_version_t)select;
        
    ret = dsSetEdidVersion(port , edidver);
    if(ret != dsERR_NONE)
    {
       UT_LOG_ERROR("Result: Failed dsSetEdidVersion Error:[%s]",ut_control_GetMapString(dsError_mapTable, ret));
    } else {
           UT_LOG_INFO("Result : Passed dsSetEdidVersion port type: %s, portnumber: %s\t"
                         "selected edid type: %s, edid version:%d\t",
                 ut_control_GetMapString(dsHdmiInPort_mapTable, port), port,
                 ut_control_GetMapString(tv_hdmi_edid_version_mapTable, edidver) , edidver);   
    }

exit:
UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test to get edidversion.
*
* This test function is to get edidversion of HdmiInput port on platform.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 012@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [ds-hdmi-in_halSpec.md](../../docs/pages/ds-hdmi-in_halSpec.md)
*/
void test_l3_HdmiIn_get_edidversion(void)
{
    gTestID = 12;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret   = dsERR_NONE;
    int select;
    dsHdmiInPort_t port = dsHDMI_IN_PORT_NONE;
    tv_hdmi_edid_version_t edidver = HDMI_EDID_VER_MAX;
    uint8_t numInputPorts = 0;

    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/numberOfPorts");
    printf("\n**********Please select port***********\n");
    scanf("%d", &select);
    readAndDiscardRestOfLine(stdin);

    if(select <= 0 || select >numInputPorts)
    {
      printf("\n invalid port selected\n");
      goto exit;
    }
    port = select;
   
    ret = dsGetEdidVersion(port, &edidver);
        if(ret != dsERR_NONE)
    {
       UT_LOG_ERROR("Result: Failed dsGetEdidVersion Error:[%s]",ut_control_GetMapString(dsError_mapTable, ret));
    } else {
           UT_LOG_INFO("Result : Passed dsGetEdidVersion port type: %s, portnumber: %s\t"
                         "retrieved edid type: %s, edid version:%d",
                 ut_control_GetMapString(dsHdmiInPort_mapTable, port), port,
                 ut_control_GetMapString(tv_hdmi_edid_version_mapTable, edidver) , edidver);
    }
exit:
UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test to get allmstatus.
*
* This test function is to get allmstatus of HdmiInput port on platform.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 013@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [ds-hdmi-in_halSpec.md](../../docs/pages/ds-hdmi-in_halSpec.md)
*/
void test_l3_HdmiIn_get_allmstatus(void)
{
    gTestID = 13;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret   = dsERR_NONE;
    int select = 0;
    dsHdmiInPort_t port = dsHDMI_IN_PORT_NONE;
    bool allmstatus = false;
    uint8_t numInputPorts = 0;

    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/numberOfPorts");
    printf("\n**********Please select port***********\n");
    scanf("%d", &select);
    readAndDiscardRestOfLine(stdin);

    if(select <= 0 || select >numInputPorts)
    {
      printf("\n invalid port selected\n");
      goto exit;
    }
    port = (dsHdmiInPort_t)select;

    ret = dsGetAllmStatus(port , &allmstatus);
    if(ret != dsERR_NONE)
    {
       UT_LOG_ERROR("Result: Failed dsGetAllmStatus Error:[%s]",ut_control_GetMapString(dsError_mapTable, ret));
    } else {
           UT_LOG_INFO("Result : Passed dsGetEdidVersion port type: %s, portnumber: %s\t"
                         "retrieved allm status: %s",
                 ut_control_GetMapString(dsHdmiInPort_mapTable, port), port,
                 ut_control_GetMapString(bool_mapTable, allmstatus));
    }
exit:
UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test to get supported game features list.
*
* This test function is to get supported game features list of HdmiInput port on platform.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 014@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [ds-hdmi-in_halSpec.md](../../docs/pages/ds-hdmi-in_halSpec.md)
*/
void test_l3_HdmiIn_get_gamefeatureslist(void)
{
    gTestID = 14;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret   = dsERR_NONE;
    dsSupportedGameFeatureList_t features_list;

    ret = dsGetSupportedGameFeaturesList( &features_list);
    if(ret != dsERR_NONE)
    {
       UT_LOG_ERROR("Result: Failed dsGetSupportedGameFeaturesList Error:[%s]",ut_control_GetMapString(dsError_mapTable, ret));
    } else {
           UT_LOG_INFO("Result : Passed dsGetSupportedGameFeaturesList retrieved features_list count: %d",
                 features_list.gameFeatureCount);
    }
    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test to get AV latency.
*
* This test function is to get AV latency of HdmiInput port on platform.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 015@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [ds-hdmi-in_halSpec.md](../../docs/pages/ds-hdmi-in_halSpec.md)
*/
void test_l3_HdmiIn_get_avlatency(void)
{
    gTestID = 15;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret   = dsERR_NONE;
    int audio_latency = 0, video_latency = 0;
   
    ret = dsGetAVLatency(&audio_latency , &video_latency);
    if(ret != dsERR_NONE)
    {
       UT_LOG_ERROR("Result: dsGetAVLatency Error:[%s]",ut_control_GetMapString(dsError_mapTable, ret));
    } else {
           UT_LOG_INFO("Result : dsGetAVLatency audio_latency: %d ms, video_latency: %d ms",
                         audio_latency , video_latency);
    }
    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test to set allmsupport.
*
* This test function to set allmsupport of HdmiInput port on platform.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 016@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [ds-hdmi-in_halSpec.md](../../docs/pages/ds-hdmi-in_halSpec.md)
*/
void test_l3_HdmiIn_set_edid2allmsupport(void)
{
    gTestID = 16;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret   = dsERR_NONE;
    dsHdmiInPort_t port = dsHDMI_IN_PORT_MAX;
    int32_t select;
    bool allmsupport = false;
    uint8_t numInputPorts = 0;

    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/numberOfPorts");

    printf(" \n================Please Select Inputs==================\n");

    printf("\n*******Enter the port number to select*******\n");
    scanf("%d", &select);
    readAndDiscardRestOfLine(stdin);

    if(select <= 0 || select > numInputPorts)
    {
       printf("\nInvalid port selected\n");
       goto exit;
    }

    port = select;

    printf("\n*******Enter the allmsupport to select*******\t"
                     "Acceptable inputs are:\t"
                     "true (i.e 1)\t"
                     "false(i.e 0)\t"
             "******************************************\n");
    scanf("%d", &select);
    readAndDiscardRestOfLine(stdin);
    if(select < 0 || select > 1)
    {
       printf("\nInvalid allmsupport value selected\n");
       goto exit;
    }
  
    allmsupport = (bool)select;

    ret = dsSetEdid2AllmSupport(port, allmsupport);
    if(ret != dsERR_NONE)
    {
       UT_LOG_ERROR("Result: Failed dsSetEdid2AllmSupport Error:[%s]",ut_control_GetMapString(dsError_mapTable, ret));
    } else {
           UT_LOG_INFO("Result : dsSetEdid2AllmSupport port type: %s, portnumber: %s\t"
                          "allmsupport set: %s",
                 ut_control_GetMapString(dsHdmiInPort_mapTable, port), port,
                 ut_control_GetMapString(bool_mapTable, allmsupport));
    }

exit:
UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test to get allmsupport.
*
* This test function gets allmsupport of HdmiInput port on platform.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 017@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [ds-hdmi-in_halSpec.md](../../docs/pages/ds-hdmi-in_halSpec.md)
*/
void test_l3_HdmiIn_get_edid2allmsupport(void)
{
    gTestID = 17;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret   = dsERR_NONE;
    dsHdmiInPort_t port = dsHDMI_IN_PORT_MAX;
    int32_t select;
    bool allmsupport = false;
    uint8_t numInputPorts = 0;

    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/numberOfPorts");

    printf(" \n================Please Select Inputs==================\n");

    printf("\n*******Enter the port number to select*******\n");
    scanf("%d", &select);
    readAndDiscardRestOfLine(stdin);

    if(select <= 0 || select > numInputPorts)
    {
       printf("\nInvalid port selected\n");
       goto exit;
    }

    port = select;

    ret = dsGetEdid2AllmSupport(port, &allmsupport);
    if(ret != dsERR_NONE)
    {
       UT_LOG_ERROR("Result: Failed dsSetEdid2AllmSupport Error:[%s]",ut_control_GetMapString(dsError_mapTable, ret));
    } else {
           UT_LOG_INFO("Result : dsSetEdid2AllmSupport port type: %s, portnumber: %s\t"
                         "retrieved allmsupport: %s",
                 ut_control_GetMapString(dsHdmiInPort_mapTable, port), port,
                 ut_control_GetMapString(bool_mapTable, allmsupport));
    }

exit:
   UT_LOG_INFO("Out %s", __FUNCTION__);
}


/**
* @brief This test terminates the dsHdmiIn.
*
* This test function terminates the dsHdmiIn.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 018@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [ds-hdmi-in_halSpec.md](../../docs/pages/ds-hdmi-in_halSpec.md)
*/
void test_l3_dsHdmiIn_terminate(void)
{
    gTestID = 18;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;

    UT_LOG_INFO("Calling dsHdmiInTerm()");
    ret = dsHdmiInTerm();
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsHdmiInTerm() dsError_t:[%s]", ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsHdmiInTerm() dsError_t:[%s]", ut_control_GetMapString(dsError_mapTable, ret));
    }

    UT_LOG_INFO("Out %s", __FUNCTION__);
}


static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main test(s) for this module
 *
 * @return int - 0 on success, otherwise failure
 */
int test_l3_dsHdmiIn_register ( void )
{
    ut_kvp_status_t status = UT_KVP_STATUS_SUCCESS;
    pSuite = UT_add_suite( "[L3 dsHdmiIn --  advanced]", NULL, NULL );

    status = ut_kvp_getStringField(ut_kvp_profile_getInstance(), "dsHdmiIn.Type", gDeviceType, TEST_DS_DEVICE_TYPE_SIZE);

    if (status == UT_KVP_STATUS_SUCCESS ) {
        if (!strncmp(gDeviceType, TEST_TYPE_SOURCE_VALUE, TEST_DS_DEVICE_TYPE_SIZE)) {
            // Create the test suite for source type
            pSuite = UT_add_suite("[L3 dsHdmiIn - Source]", NULL, NULL);
            if (pSuite == NULL)
            {
                return -1;
            }

            gSourceType = 1;
    }
    else if(!strncmp(gDeviceType, TEST_TYPE_SINK_VALUE, TEST_DS_DEVICE_TYPE_SIZE)) {
            // Create the test suite for sink type
            pSuite = UT_add_suite("[L3 dsHdmiIn - Sink]", NULL, NULL);
            if (pSuite == NULL)
            {
                return -1;
            }

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

    UT_add_test( pSuite, "HdmiIn_Initialize" ,test_l3_HdmiIn_initialize );
    UT_add_test( pSuite, "HdmiIn_get_inputport" ,test_l3_HdmiIn_get_inputports );
    UT_add_test( pSuite, "HdmiIn_get_status" ,test_l3_HdmiIn_get_status);
    UT_add_test( pSuite, "HdmiIn_select_port" ,test_l3_HdmiIn_select_port );
    UT_add_test( pSuite, "HdmiIn_scale_video" ,test_l3_HdmiIn_scale_video );
    UT_add_test( pSuite, "HdmiIn_zoom_mode" ,test_l3_HdmiIn_zoom_mode );
    UT_add_test( pSuite, "HdmiIn_video_mode" ,test_l3_HdmiIn_video_mode );
    UT_add_test( pSuite, "HdmiIn_arc_port" ,test_l3_HdmiIn_arc_port );
    UT_add_test( pSuite, "HdmiIn_get_edid" ,test_l3_HdmiIn_get_edid );
    UT_add_test( pSuite, "HdmiIn_spd_info" ,test_l3_HdmiIn_spd_info );
    UT_add_test( pSuite, "HdmiIn_set_edidversion" ,test_l3_HdmiIn_set_edidversion );
    UT_add_test( pSuite, "HdmiIn_get_edidversion" ,test_l3_HdmiIn_get_edidversion );
    UT_add_test( pSuite, "HdmiIn_get_allmstatus" ,test_l3_HdmiIn_get_allmstatus );
    UT_add_test( pSuite, "HdmiIn_get_gamefeatureslist" ,test_l3_HdmiIn_get_gamefeatureslist );
    UT_add_test( pSuite, "HdmiIn_get_avlatency" ,test_l3_HdmiIn_get_avlatency );
    UT_add_test( pSuite, "HdmiIn_set_edid2allmsupport" ,test_l3_HdmiIn_set_edid2allmsupport );
    UT_add_test( pSuite, "HdmiIn_get_edid2allmsupport" ,test_l3_HdmiIn_get_edid2allmsupport );
    UT_add_test( pSuite, "dsHdmiIn_terminate" ,test_l3_dsHdmiIn_terminate );

   return 0;
}

/** @} */ // End of DS_HDMIIn_HALTEST_L3
/** @} */ // End of DS_HDMIIn_HALTEST
/** @} */ // End of Device_Settings_HALTEST
/** @} */ // End of Device_Settings
/** @} */ // End of HPK
