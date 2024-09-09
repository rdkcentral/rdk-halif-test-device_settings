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
#include <ut_control_plane.h>
#include "test_parse_configuration.h"

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
const static ut_control_keyStringMapping_t dsHdmiInPort_mapTable [] = {
  { "dsHDMI_IN_PORT_NONE",     (int32_t)dsHDMI_IN_PORT_NONE },
  { "dsHDMI_IN_PORT_0",        (int32_t)dsHDMI_IN_PORT_0    },
  { "dsHDMI_IN_PORT_1",        (int32_t)dsHDMI_IN_PORT_1    },
  { "dsHDMI_IN_PORT_2",        (int32_t)dsHDMI_IN_PORT_2    },
  { "dsHDMI_IN_PORT_MAX",      (int32_t)dsHDMI_IN_PORT_MAX  },
  {  NULL, -1 }
};

/* dsHdmiInSignalStatus_t */
const static ut_control_keyStringMapping_t dsHdmiInSignalStatus_mapTable [] = {
  { "dsHDMI_IN_SIGNAL_STATUS_NONE",            (int32_t)dsHDMI_IN_SIGNAL_STATUS_NONE         },
  { "dsHDMI_IN_SIGNAL_STATUS_NOSIGNAL",        (int32_t)dsHDMI_IN_SIGNAL_STATUS_NOSIGNAL     },
  { "dsHDMI_IN_SIGNAL_STATUS_UNSTABLE",        (int32_t)dsHDMI_IN_SIGNAL_STATUS_UNSTABLE     },
  { "dsHDMI_IN_SIGNAL_STATUS_NOTSUPPORTED",    (int32_t)dsHDMI_IN_SIGNAL_STATUS_NOTSUPPORTED },
  { "dsHDMI_IN_SIGNAL_STATUS_STABLE",          (int32_t)dsHDMI_IN_SIGNAL_STATUS_STABLE       },
  { "dsHDMI_IN_SIGNAL_STATUS_MAX",             (int32_t)dsHDMI_IN_SIGNAL_STATUS_MAX          },
  {  NULL, -1 }
};

/* dsError_t */
const static ut_control_keyStringMapping_t dsError_mapTable [] = {
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
const static ut_control_keyStringMapping_t dsVideoResolution_mapTable [] = {
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
const static ut_control_keyStringMapping_t dsVideoAspectRatio_mapTable [] = {
  { "dsVIDEO_ASPECT_RATIO_4x3",     (int32_t)dsVIDEO_ASPECT_RATIO_4x3  },
  { "dsVIDEO_ASPECT_RATIO_16x9",    (int32_t)dsVIDEO_ASPECT_RATIO_16x9 },
  { "dsVIDEO_ASPECT_RATIO_MAX",     (int32_t)dsVIDEO_ASPECT_RATIO_MAX  },
  {  NULL, -1 }
};

/* dsVideoStereoScopicMode_t */
const static ut_control_keyStringMapping_t dsVideoStereoScopicMode_mapTable [] = {
  { "dsVIDEO_SSMODE_UNKNOWN",            (int32_t)dsVIDEO_SSMODE_UNKNOWN            },
  { "dsVIDEO_SSMODE_2D",                 (int32_t)dsVIDEO_SSMODE_2D                 },
  { "dsVIDEO_SSMODE_3D_SIDE_BY_SIDE",    (int32_t)dsVIDEO_SSMODE_3D_SIDE_BY_SIDE    },
  { "dsVIDEO_SSMODE_3D_TOP_AND_BOTTOM",  (int32_t)dsVIDEO_SSMODE_3D_TOP_AND_BOTTOM  },
  { "dsVIDEO_SSMODE_MAX",                (int32_t)dsVIDEO_SSMODE_MAX                },
  {  NULL, -1 }
};

/* dsVideoFrameRate_t */
const static ut_control_keyStringMapping_t dsVideoFrameRate_mapTable [] = {
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
const static ut_control_keyStringMapping_t dsAviContentType_mapTable [] = {
  { "dsAVICONTENT_TYPE_GRAPHICS",    (int32_t)dsAVICONTENT_TYPE_GRAPHICS },
  { "dsAVICONTENT_TYPE_PHOTO",       (int32_t)dsAVICONTENT_TYPE_PHOTO    },
  { "dsAVICONTENT_TYPE_CINEMA",      (int32_t)dsAVICONTENT_TYPE_CINEMA   },
  { "dsAVICONTENT_TYPE_GAME",        (int32_t)dsAVICONTENT_TYPE_GAME     },
  { "dsAVICONTENT_TYPE_INVALID",     (int32_t)dsAVICONTENT_TYPE_INVALID  },
  { "dsAVICONTENT_TYPE_MAX",         (int32_t)dsAVICONTENT_TYPE_MAX      },
  {  NULL, -1 }
};

/* dsVideoPlaneType_t */
const static ut_control_keyStringMapping_t dsVideoPlaneType_mapTable [] = {
  { "dsVideoPlane_PRIMARY",     (int32_t)dsVideoPlane_PRIMARY   },
  { "dsVideoPlane_SECONDARY",   (int32_t)dsVideoPlane_SECONDARY },
  { "dsVideoPlane_MAX",         (int32_t)dsVideoPlane_MAX       },
  {  NULL, -1 }
};

/* dsVideoZoom_t */
const static ut_control_keyStringMapping_t dsVideoZoom_mapTable [] = {
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
const static ut_control_keyStringMapping_t tv_hdmi_edid_version_mapTable [] = {
  { "HDMI_EDID_VER_14",     (int32_t)HDMI_EDID_VER_14  },
  { "HDMI_EDID_VER_20",     (int32_t)HDMI_EDID_VER_20  },
  { "HDMI_EDID_VER_MAX",    (int32_t)HDMI_EDID_VER_MAX },
  {  NULL, -1 }
};

/* bool */
const static ut_control_keyStringMapping_t bool_mapTable [] = {
  { "false", (int32_t)false },
  { "true",  (int32_t)true  },
  {  NULL, -1 }
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

/**
*
*This function read the input from the stdin.
*/

void readInput(int *choice)
{
    scanf("%d",choice);
    readAndDiscardRestOfLine(stdin);
}

/**
 * @brief Callback function for HdmiIn connection status.
 *
 * This function is invoked whenever a change occurs in the Hdmi connection.
 */
static void hdmiInConnectCB(dsHdmiInPort_t Port, bool isPortConnected)
{
    UT_LOG_INFO("Received Connection status callback port: %s, Connection: %s",
                 UT_Control_GetMapString(dsHdmiInPort_mapTable, Port),
                 UT_Control_GetMapString(bool_mapTable, isPortConnected));

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
                 UT_Control_GetMapString(dsHdmiInPort_mapTable, port),
                 UT_Control_GetMapString(dsHdmiInSignalStatus_mapTable, sigStatus));

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
                 UT_Control_GetMapString(bool_mapTable, inputStatus.isPresented),
                 UT_Control_GetMapString(dsHdmiInPort_mapTable, inputStatus.activePort));

    for(int i = 0 ; i < dsHDMI_IN_PORT_MAX ; i++) 
    {
         
         UT_LOG_INFO("Received statuschange callback port:%d , isPortConnected: %s",
                 UT_Control_GetMapString(dsHdmiInPort_mapTable, i),
                 UT_Control_GetMapString(bool_mapTable, inputStatus.isPortConnected[i]));
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
                 UT_Control_GetMapString(dsHdmiInPort_mapTable, port),
                 videoResolution.name, 
                 UT_Control_GetMapString(dsVideoResolution_mapTable, videoResolution.pixelResolution),
                 UT_Control_GetMapString(dsVideoAspectRatio_mapTable, videoResolution.aspectRatio),
                 UT_Control_GetMapString(dsVideoStereoScopicMode_mapTable, videoResolution.stereoScopicMode),
                 UT_Control_GetMapString(dsVideoFrameRate_mapTable, videoResolution.frameRate),
                 UT_Control_GetMapString(bool_mapTable, videoResolution.interlaced));

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
                 UT_Control_GetMapString(dsHdmiInPort_mapTable, port),
                 UT_Control_GetMapString(bool_mapTable, allm_mode));

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
                 UT_Control_GetMapString(dsHdmiInPort_mapTable, port),
                 UT_Control_GetMapString(dsAviContentType_mapTable, avi_content_type)),

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
    UT_LOG_INFO("Result dsHdmiInInit() dsError_t:[%s]", UT_Control_GetMapString(dsError_mapTable, ret));
    assert(ret == dsERR_NONE);

    /* Register connection status callback */
    UT_LOG_INFO("Calling dsHdmiInRegisterConnectCB(CBFunc:[0x%0X])", hdmiInConnectCB);
    ret = dsHdmiInRegisterConnectCB(hdmiInConnectCB);
    UT_LOG_INFO("Result dsHdmiInRegisterConnectCB(CBFunc:[0x%0X]) dsError_t:[%s]",
                        hdmiInConnectCB, UT_Control_GetMapString(dsError_mapTable, ret));
    assert(ret == dsERR_NONE);

    /* Register Signal change callback */
    if(gSourceType == 0)
    {
        UT_LOG_INFO("Calling dsHdmiInRegisterSignalChangeC(CBFun:[0x%0X])", hdmiInSignalChangeCB);
        ret = dsHdmiInRegisterSignalChangeCB(hdmiInSignalChangeCB);
        UT_LOG_INFO("Result dsHdmiInRegisterSignalChangeC(CBFun:[0x%0X]) dsError_t:[%s]",
                            hdmiInSignalChangeCB, UT_Control_GetMapString(dsError_mapTable, ret));
        assert(ret == dsERR_NONE);

        /* Register Status change callback */
        UT_LOG_INFO("Calling dsHdmiInRegisterStatusChangeCB(CBFun:[0x%0X])", hdmiInStatusChangeCB);
        ret = dsHdmiInRegisterStatusChangeCB(hdmiInStatusChangeCB);
        UT_LOG_INFO("Result dsHdmiInRegisterStatusChangeCB(CBFun:[0x%0X]) dsError_t:[%s]",
                            hdmiInStatusChangeCB, UT_Control_GetMapString(dsError_mapTable, ret));
        assert(ret == dsERR_NONE);

        /* Register Video Mode Update callback */
        UT_LOG_INFO("Calling dsHdmiInRegisterVideoModeUpdateCB(CBFun:[0x%0X])", hdmiInVideoModeUpdateCB);
        ret = dsHdmiInRegisterVideoModeUpdateCB(hdmiInVideoModeUpdateCB);
        UT_LOG_INFO("Result dsHdmiInRegisterVideoModeUpdateCB(CBFun:[0x%0X]) dsError_t:[%s]",
                            hdmiInVideoModeUpdateCB, UT_Control_GetMapString(dsError_mapTable, ret));
        assert(ret == dsERR_NONE);

        /* Register Allm changes callback */
        UT_LOG_INFO("Calling dsHdmiInRegisterAllmChangeCB(CBFun:[0x%0X])", hdmiInAllmChangeCB);
        ret = dsHdmiInRegisterAllmChangeCB(hdmiInAllmChangeCB);
        UT_LOG_INFO("Result dsHdmiInRegisterAllmChangeCB(CBFun:[0x%0X]) dsError_t:[%s]",
                            hdmiInAllmChangeCB, UT_Control_GetMapString(dsError_mapTable, ret));
        assert(ret == dsERR_NONE);

        /* Register AV latency changes callback */
        UT_LOG_INFO("Calling dsHdmiInRegisterAVLatencyChangeCB(CBFun:[0x%0X])", hdmiInAVLatencyChangeCB);
        ret = dsHdmiInRegisterAVLatencyChangeCB(hdmiInAVLatencyChangeCB);
        UT_LOG_INFO("Result dsHdmiInRegisterAVLatencyChangeCB(CBFun:[0x%0X]) dsError_t:[%s]",
                            hdmiInAVLatencyChangeCB, UT_Control_GetMapString(dsError_mapTable, ret));
        assert(ret == dsERR_NONE);

        /* Register AVI Content changes callback */
        UT_LOG_INFO("Calling dsHdmiInRegisterAviContentTypeChangeCB(CBFun:[0x%0X])", hdmiInAviContentTypeChangeCB);
        ret = dsHdmiInRegisterAviContentTypeChangeCB(hdmiInAviContentTypeChangeCB);
        UT_LOG_INFO("Result dsHdmiInRegisterAviContentTypeChangeCB(CBFun:[0x%0X]) dsError_t:[%s]",
                            hdmiInAviContentTypeChangeCB, UT_Control_GetMapString(dsError_mapTable, ret));
        assert(ret == dsERR_NONE);
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
    UT_LOG_INFO("Result: NumberOfInputsPorts:[%d]",numInputs);
    assert(ret == dsERR_NONE);

    if(!numInputs)
       UT_LOG_INFO("Result: Platform does not supports HdmiIn Ports");

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
    dsHdmiInStatus_t inputstatus = {0};
    
    UT_LOG_INFO("Calling dsHdmiInGetStatus");
    ret = dsHdmiInGetStatus(&inputstatus);
    UT_LOG_INFO("Result HDMI input port status isPresented: %s, activeport: %s",
                 UT_Control_GetMapString(bool_mapTable, inputstatus.isPresented),
                 UT_Control_GetMapString(dsHdmiInPort_mapTable, inputstatus.activePort));
    assert(ret == dsERR_NONE);

    for(int i = 0 ; i < dsHDMI_IN_PORT_MAX ; i++) {

           UT_LOG_INFO("Result: HDMI port connected info port:%s , isPortConnected: %s",
                         UT_Control_GetMapString(dsHdmiInPort_mapTable, i),
                         UT_Control_GetMapString(bool_mapTable, inputstatus.isPortConnected[i]));
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
    int32_t select = 0; 
    bool audmix = false;
    dsVideoPlaneType_t videoplanetype = dsVideoPlane_MAX;
    bool topmost = false;
    uint8_t numInputPorts = 0;
 
    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/numberOfPorts");

    UT_LOG_INFO(" \n================Please Select Inputs==================\n");
    UT_LOG_INFO("\n*******Enter the port number to select*******\n");
    
    readInput(&select);
    if(select <= 0 || select > (numInputPorts-1)) 
    {
       UT_LOG_ERROR("\nInvalid port selected\n");
    }

    port = (select - 1);

    UT_LOG_INFO("\n*******Enter the audiomix to select*******\n\t"
                     "\tAcceptable inputs are:\n\t"
                     "\ttrue (i.e 1)\n\t"
                     "\tfalse(i.e 0)\n\t"                    
                "\n******************************************\n");

    readInput(&select);
    if(select < 0 || select > 1)
    {
       UT_LOG_ERROR("\nInvalid audmix selected\n");
    }
   
    audmix = (bool)select;

    UT_LOG_INFO("\n*******Enter the videoplanetype to select*******\n");
    for(dsVideoPlaneType_t i = dsVideoPlane_PRIMARY ; i < dsVideoPlane_MAX ; i++)
    {
          UT_LOG_INFO("\n Available videoplane type: %s, videoplane number: %d \n",
                 UT_Control_GetMapString(dsVideoPlaneType_mapTable,i),i);
    }
    UT_LOG_INFO("\n**************************************************\n");

    readInput(&select);
    if(select < 0 || select >= dsVideoPlane_MAX)
    {
       UT_LOG_ERROR("\nInvalid video plane type selected\n");
    }

    videoplanetype = (dsVideoPlaneType_t)select;

    UT_LOG_INFO("\n*******Enter the topmost to select*******\n\t"
                     "\tAcceptable inputs are:\n\t"
                     "\ttrue (i.e 1)\n\t"
                     "\tfalse(i.e 0)\n\t"
                "\n******************************************\n");
    
    readInput(&select);
    if(select < 0 || select > 1)
    {
       UT_LOG_ERROR("\nInvalid audmix selected\n");
    }
    
    topmost = (bool)select;

    ret = dsHdmiInSelectPort(port , audmix , videoplanetype , topmost);
    UT_LOG_INFO("Result : dsHdmiInSelectPort: %s, portnumber: %d",
                  UT_Control_GetMapString(dsHdmiInPort_mapTable, port), port);
    assert(ret == dsERR_NONE);
    
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
    int32_t select = 0;

    UT_LOG_INFO("\n================Please Select Inputs==================\n");
    UT_LOG_INFO("\n*******Enter the x coordinate to select*******\n\t"
                     "\tAcceptable inputs are:\n\t"
                     "\tMin is 0\n\t"
                     "\tMax is based on the current resolution\n\t"
                "\n**********************************************\n");

   readInput(&select);
   x = select;
   if(x < 0)
   {
      UT_LOG_ERROR("\n invalid x coordinate selected \n");
   }

   UT_LOG_INFO("\n*******Enter the y coordinate to select*******\n\t"
                     "\tAcceptable inputs are:\n\t"
                     "\tMin is 0\n\t"
                     "\tMax is based on the current resolution\n\t"
               "\n**********************************************\n");

   readInput(&select);
   y = select;
   if(y < 0)
   {
      UT_LOG_ERROR("\n invalid y coordinate selected \n");
   }

   UT_LOG_INFO("\n*******Enter the width to select***************\n\t"
                     "\tAcceptable inputs are:\n\t"
                     "\tMin is 0\n\t"
                     "\tMax is based on the current resolution\n\t"
               "\n**********************************************\n");

   readInput(&select);
   width = select;
   if(width < 0)
   {
      UT_LOG_ERROR("\n invalid width selected \n");
   }

   UT_LOG_INFO("\n*******Enter the height to select**************\t"
                     "\tAcceptable inputs are:\n\t"
                     "\tMin is 0\n\t"
                     "\tMax is based on the current resolution\n\t"
               "\n**********************************************\n");

   readInput(&select);
   height = select;
   if(height < 0)
   {
      UT_LOG_INFO("\n invalid height selected \n");
   }

   ret = dsHdmiInScaleVideo(x, y, width, height);
   UT_LOG_INFO("Result : Passed dsHdmiInScaleVideo params x : %d, y : %d, width : %d , height : %d",
                  x, y , width, height);
   assert(ret == dsERR_NONE);

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
    int32_t select = 0;
    dsVideoZoom_t mode = dsVIDEO_ZOOM_NONE;

    UT_LOG_INFO("\n===================Select Zoom Mode================\n");
    UT_LOG_INFO("\n**************Availabe Zoom Modes are****************\n");
    for(dsVideoZoom_t i = dsVIDEO_ZOOM_NONE ; i < dsVIDEO_ZOOM_MAX ; i++)
    {
           UT_LOG_INFO("%s : %d", UT_Control_GetMapString(dsVideoZoom_mapTable, i) , i);
    }
    UT_LOG_INFO("\n******************************************************\n");

    readInput(&select);
    if(select < 0 || select > dsVIDEO_ZOOM_MAX)
    {
      UT_LOG_ERROR("\n invalid zoom mode selected \n");
    }  
    
    mode = (dsVideoZoom_t)select;
    ret = dsHdmiInSelectZoomMode(mode);
    UT_LOG_INFO("Result : dsHdmiInSelectZoomMode: %s, selected: %d",
                 UT_Control_GetMapString(dsVideoZoom_mapTable, mode), mode);
    assert(ret == dsERR_NONE);

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
    dsVideoPortResolution_t resolution = {0};
    
    ret = dsHdmiInGetCurrentVideoMode(&resolution);
    UT_LOG_INFO("Result: Passed dsHdmiInGetCurrentVideoMode resolution name: %s, pixelResolution: %s\t"
                      "aspectRatio:%s, stereoScopicMode:%s, frameRate:%s, interlaced:%s ",
                      resolution.name,
                      UT_Control_GetMapString(dsVideoResolution_mapTable, resolution.pixelResolution),
                      UT_Control_GetMapString(dsVideoAspectRatio_mapTable, resolution.aspectRatio),
                      UT_Control_GetMapString(dsVideoStereoScopicMode_mapTable, resolution.stereoScopicMode),
                      UT_Control_GetMapString(dsVideoFrameRate_mapTable, resolution.frameRate),
                      UT_Control_GetMapString(bool_mapTable, resolution.interlaced));
    assert(ret == dsERR_NONE);

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
    int32_t select = 0;
    dsHdmiInPort_t iport = dsHDMI_IN_PORT_NONE;
    bool isarcport = false;
    uint8_t numInputPorts = 0;

    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/numberOfPorts");
    UT_LOG_INFO("\n**********Please select port***********\n");

    readInput(&select);
    if(select <= 0 || select > (numInputPorts -1))
    {
      UT_LOG_ERROR("\n invalid port selected\n");
    }

    iport = (select -1);
    ret = dsIsHdmiARCPort(iport , &isarcport);
    UT_LOG_INFO("Result : Passed dsIsHdmiARCPort port type: %s, port isarc: %s , portnumber: %d",
                  UT_Control_GetMapString(dsHdmiInPort_mapTable, iport),
                  UT_Control_GetMapString(bool_mapTable, isarcport),iport);
    assert(ret == dsERR_NONE);

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
    int32_t select = 0;
    dsHdmiInPort_t port = dsHDMI_IN_PORT_NONE;
    uint8_t numInputPorts = 0;

    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/numberOfPorts");
    UT_LOG_INFO("\n**********Please select port***********\n");

    readInput(&select);
    if(select <= 0 || select > (numInputPorts -1))
    {
      UT_LOG_ERROR("\n invalid port selected\n");
    }

    port = (select - 1);
    ret = dsGetEDIDBytesInfo(port, edidbytes, &length);
    UT_LOG_INFO("Result : dsGetEDIDBytesInfo port type: %s, portnumber: %d\t"
                         "edidinfo: %s", UT_Control_GetMapString(dsHdmiInPort_mapTable, port), port, edidbytes);
    assert(ret == dsERR_NONE);

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
    int32_t select = 0;
    uint8_t numInputPorts = 0;
    
    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/numberOfPorts");
    UT_LOG_INFO("\n**********Please select port***********\n");

    readInput(&select);
    if(select <= 0 || select >(numInputPorts - 1))
    {
      UT_LOG_ERROR("\n invalid port selected\n");
    }
   
    port = (select - 1);
   
    ret = dsGetHDMISPDInfo(port, spdinfo); 
    UT_LOG_INFO("\n dsGetHDMISPDInfo : %s \n",spdinfo);
    assert(ret == dsERR_NONE);

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
    int32_t select = 0;
    dsHdmiInPort_t port = dsHDMI_IN_PORT_NONE;
    tv_hdmi_edid_version_t edidver = HDMI_EDID_VER_MAX;
    uint8_t numInputPorts = 0;

    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/numberOfPorts");
    UT_LOG_INFO("\n**********Please select port***********\n");

    readInput(&select);
    if(select <= 0 || select > (numInputPorts -1))
    {
       UT_LOG_ERROR("\n invalid port selected\n");
    }

    port = (select - 1);
  
    UT_LOG_INFO("\n*********Please select from availabe edid versions are***********\n");
    for(tv_hdmi_edid_version_t i = HDMI_EDID_VER_14 ; i < HDMI_EDID_VER_MAX ; i++)
    {
           UT_LOG_INFO("%s : %d", UT_Control_GetMapString(tv_hdmi_edid_version_mapTable, i) , i);
    }
    UT_LOG_INFO("\n*****************************************************************\n");

    readInput(&select);
    if(select < HDMI_EDID_VER_14 || select > HDMI_EDID_VER_MAX)
    {
       UT_LOG_ERROR("\n invalid edid selected\n");
    }
    
    edidver = (tv_hdmi_edid_version_t)select;
        
    ret = dsSetEdidVersion(port , edidver);
    UT_LOG_INFO("Result : Passed dsSetEdidVersion port type: %s, portnumber: %s\t"
                         "selected edid type: %s, edid version:%d\t",
                 UT_Control_GetMapString(dsHdmiInPort_mapTable, port), (port+1),
                 UT_Control_GetMapString(tv_hdmi_edid_version_mapTable, edidver) , edidver);
    assert(ret == dsERR_NONE);

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
    int32_t select = 0;
    dsHdmiInPort_t port = dsHDMI_IN_PORT_NONE;
    tv_hdmi_edid_version_t edidver = HDMI_EDID_VER_MAX;
    uint8_t numInputPorts = 0;

    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/numberOfPorts");
    UT_LOG_INFO("\n**********Please select port***********\n");

    readInput(&select);
    if(select <= 0 || select >(numInputPorts-1))
    {
      UT_LOG_ERROR("\n invalid port selected\n");
    }
    port = (select - 1);
   
    ret = dsGetEdidVersion(port, &edidver);
    UT_LOG_INFO("Result : dsGetEdidVersion port type: %s, portnumber: %s\t"
                         "retrieved edid type: %s, edid version:%d",
                 UT_Control_GetMapString(dsHdmiInPort_mapTable, port), (port+1),
                 UT_Control_GetMapString(tv_hdmi_edid_version_mapTable, edidver) , edidver);
    assert(ret == dsERR_NONE);

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
    int32_t select = 0;
    dsHdmiInPort_t port = dsHDMI_IN_PORT_NONE;
    bool allmstatus = false;
    uint8_t numInputPorts = 0;

    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/numberOfPorts");
    UT_LOG_INFO("\n**********Please select port***********\n");

    readInput(&select);
    if(select <= 0 || select > (numInputPorts -1))
    {
      UT_LOG_ERROR("\n invalid port selected\n");
    }
    port = (select - 1);

    ret = dsGetAllmStatus(port , &allmstatus);
    UT_LOG_INFO("Result : Passed dsGetEdidVersion port type: %s, portnumber: %s\t"
                         "retrieved allm status: %s",
                 UT_Control_GetMapString(dsHdmiInPort_mapTable, port), (port+1),
                 UT_Control_GetMapString(bool_mapTable, allmstatus));
    assert(ret == dsERR_NONE);

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
    char *token = NULL;

    ret = dsGetSupportedGameFeaturesList( &features_list);
    UT_LOG_INFO("Result : dsGetSupportedGameFeaturesList retrieved features_list count: %d",
                 features_list.gameFeatureCount);
    assert(ret == dsERR_NONE);
          
    token = strtok(features_list.gameFeatureList , ",");
    while(token != NULL)
    {
       UT_LOG_INFO("Result: Supported featureslist: %s", token);
       token = strtok(NULL , ",");
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
           UT_LOG_INFO("Result : dsGetAVLatency audio_latency: %d ms, video_latency: %d ms",
                         audio_latency , video_latency);
    assert(ret == dsERR_NONE);

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
    int32_t select = 0;
    bool allmsupport = false;
    uint8_t numInputPorts = 0;

    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/numberOfPorts");

    UT_LOG_INFO(" \n================Please Select Inputs==================\n");
    UT_LOG_INFO("\n*******Enter the port number to select*******\n");
    
    readInput(&select);
    if(select <= 0 || select > (numInputPorts-1))
    {
       UT_LOG_ERROR("\nInvalid port selected\n");
    }

    port = (select-1);

    UT_LOG_INFO("\n*******Enter the allmsupport to select*******\n\t"
                     "\tAcceptable inputs are:\n\t"
                     "\ttrue (i.e 1)\n\t"
                     "\tfalse(i.e 0)\n\t"
                "******************************************\n");

    readInput(&select);
    if(select < 0 || select > 1)
    {
       UT_LOG_ERROR("\nInvalid allmsupport value selected\n");
    }
  
    allmsupport = (bool)select;

    ret = dsSetEdid2AllmSupport(port, allmsupport);
    UT_LOG_INFO("Result : dsSetEdid2AllmSupport port type: %s, portnumber: %d\t"
                  "allmsupport set: %s",
                 UT_Control_GetMapString(dsHdmiInPort_mapTable, port), (port+1),
                 UT_Control_GetMapString(bool_mapTable, allmsupport));
    assert(ret == dsERR_NONE);

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
    int32_t select = 0;
    bool allmsupport = false;
    uint8_t numInputPorts = 0;

    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/numberOfPorts");

    UT_LOG_INFO(" \n================Please Select Inputs==================\n");
    UT_LOG_INFO(" \n*******Enter the port number to select*******\n");
    
    readInput(&select);
    if(select <= 0 || select > (numInputPorts -1))
    {
        UT_LOG_ERROR("\nInvalid port selected\n");
    }

    port = (select - 1);

    ret = dsGetEdid2AllmSupport(port, &allmsupport);
    UT_LOG_INFO("Result : dsSetEdid2AllmSupport port type: %s, portnumber: %d\t"
                         "retrieved allmsupport: %s",
                 UT_Control_GetMapString(dsHdmiInPort_mapTable, port), (port+1),
                 UT_Control_GetMapString(bool_mapTable, allmsupport));
    assert(ret == dsERR_NONE);

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
    UT_LOG_INFO("Result dsHdmiInTerm() dsError_t:[%s]", UT_Control_GetMapString(dsError_mapTable, ret));
    assert(ret == dsERR_NONE);

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

    status = ut_kvp_getStringField(ut_kvp_profile_getInstance(), "dsHdmiIn.Type", gDeviceType, TEST_DS_DEVICE_TYPE_SIZE);
    if(status != UT_KVP_STATUS_SUCCESS)
    {
       UT_ASSERT_FATAL(status);
    } else {
            if (!strncmp(gDeviceType, TEST_TYPE_SOURCE_VALUE, TEST_DS_DEVICE_TYPE_SIZE)) 
            {
                // Create the test suite for source type
                pSuite = UT_add_suite_withGroupID("[L3 dsHdmiIn - Source]", NULL, NULL,UT_TESTS_L3);
                assert(pSuite != NULL);

                gSourceType = 1;

            } else if(gSourceType == 0) {
                // Create the test suite for sink type
                pSuite = UT_add_suite_withGroupID("[L3 dsHdmiIn - Sink]", NULL, NULL,UT_TESTS_L3);
                assert(pSuite != NULL);
            }
            else {
                UT_LOG_ERROR("Invalid platform type: %s", gDeviceType);
                return -1;
            }
    }

    UT_add_test( pSuite, "HdmiIn_Initialize" ,test_l3_HdmiIn_initialize );
    UT_add_test( pSuite, "HdmiIn_get_inputport" ,test_l3_HdmiIn_get_inputports );
    UT_add_test( pSuite, "HdmiIn_get_status" ,test_l3_HdmiIn_get_status);
    UT_add_test( pSuite, "HdmiIn_select_port" ,test_l3_HdmiIn_select_port );
    UT_add_test( pSuite, "HdmiIn_scale_video" ,test_l3_HdmiIn_scale_video );
    if(gSourceType)
    {
         UT_add_test( pSuite, "HdmiIn_zoom_mode" ,test_l3_HdmiIn_zoom_mode );
    }
    UT_add_test( pSuite, "HdmiIn_video_mode" ,test_l3_HdmiIn_video_mode );
    if(gSourceType == 0)
    {
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
    }
    UT_add_test( pSuite, "dsHdmiIn_terminate" ,test_l3_dsHdmiIn_terminate );

   return 0;
}

/** @} */ // End of DS_HDMIIn_HALTEST_L3
/** @} */ // End of DS_HDMIIn_HALTEST
/** @} */ // End of Device_Settings_HALTEST
/** @} */ // End of Device_Settings
/** @} */ // End of HPK
