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
 * @defgroup DS_VideoPort_HALTEST Device Settings Video Port HAL Tests
 * @{
 */

/**
 * @defgroup DS_VideoPort_HALTEST_L3 Device Settings Video Port HAL Tests L3 File
 * @{
 * @parblock
 *
 * ### L3 Tests for DS Video Port HAL :
 *
 * Level 3 test cases for all APIs of Device Settings Video Port HAL
 *
 * **Pre-Conditions:**  None@n
 * **Dependencies:** None@n
 *
 * Ref to API Definition specification documentation : [ds-video-port_halSpec.md](../../docs/pages/ds-video-port_halSpec.md)
 *
 * @endparblock
 */


/**
 * @file test_l3_dsVideoPort.c
 *
 */

#include <stdlib.h>
#include <stdbool.h>
#include <ut.h>
#include <ut_log.h>
#include <ut_kvp_profile.h>
#include <ut_kvp.h>
#include <ut_control_plane.h>
#include <assert.h>

#include "test_parse_configuration.h"
#include "dsVideoPort.h"


intptr_t gHandle = 0;


// Mapping table for dsError_t
const static ut_control_keyStringMapping_t  dsErrorMappingTable[] = {
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

// Mapping table for dsVideoPortType_t
const static ut_control_keyStringMapping_t  dsVideoPortMappingTable[] = {
    {"dsVIDEOPORT_TYPE_RF", (int32_t)dsVIDEOPORT_TYPE_RF},
    {"dsVIDEOPORT_TYPE_BB", (int32_t)dsVIDEOPORT_TYPE_BB},
    {"dsVIDEOPORT_TYPE_SVIDEO", (int32_t)dsVIDEOPORT_TYPE_SVIDEO},
    {"dsVIDEOPORT_TYPE_1394", (int32_t)dsVIDEOPORT_TYPE_1394},
    {"dsVIDEOPORT_TYPE_DVI", (int32_t)dsVIDEOPORT_TYPE_DVI},
    {"dsVIDEOPORT_TYPE_COMPONENT", (int32_t)dsVIDEOPORT_TYPE_COMPONENT},
    {"dsVIDEOPORT_TYPE_HDMI", (int32_t)dsVIDEOPORT_TYPE_HDMI},
    {"dsVIDEOPORT_TYPE_HDMI_INPUT", (int32_t)dsVIDEOPORT_TYPE_HDMI_INPUT},
    {"dsVIDEOPORT_TYPE_INTERNAL", (int32_t)dsVIDEOPORT_TYPE_INTERNAL},
    {"dsVIDEOPORT_TYPE_MAX", (int32_t)dsVIDEOPORT_TYPE_MAX},
    {NULL, -1}
};

// Mapping table for dsHDRStandard_t
const static ut_control_keyStringMapping_t  dsHDRStandardMappingTable[] = {
    {"dsHDRSTANDARD_NONE", (int32_t)dsHDRSTANDARD_NONE},
    {"dsHDRSTANDARD_HDR10", (int32_t)dsHDRSTANDARD_HDR10},
    {"dsHDRSTANDARD_HLG", (int32_t)dsHDRSTANDARD_HLG},
    {"dsHDRSTANDARD_DolbyVision", (int32_t)dsHDRSTANDARD_DolbyVision},
    {"dsHDRSTANDARD_TechnicolorPrime", (int32_t)dsHDRSTANDARD_TechnicolorPrime},
    {"dsHDRSTANDARD_HDR10PLUS", (int32_t)dsHDRSTANDARD_HDR10PLUS},
    {"dsHDRSTANDARD_SDR", (int32_t)dsHDRSTANDARD_SDR},
    {"dsHDRSTANDARD_Invalid", (int32_t)dsHDRSTANDARD_Invalid},
    {NULL, -1}
};

// Mapping table for dsDisplayMatrixCoefficients_t
const static ut_control_keyStringMapping_t  dsDisplayMatrixCoefficientsMappingTable[] = {
    {"dsDISPLAY_MATRIXCOEFFICIENT_UNKNOWN", (int32_t)dsDISPLAY_MATRIXCOEFFICIENT_UNKNOWN},
    {"dsDISPLAY_MATRIXCOEFFICIENT_BT_709", (int32_t)dsDISPLAY_MATRIXCOEFFICIENT_BT_709},
    {"dsDISPLAY_MATRIXCOEFFICIENT_BT_470_2_BG", (int32_t)dsDISPLAY_MATRIXCOEFFICIENT_BT_470_2_BG},
    {"dsDISPLAY_MATRIXCOEFFICIENT_SMPTE_170M", (int32_t)dsDISPLAY_MATRIXCOEFFICIENT_SMPTE_170M},
    {"dsDISPLAY_MATRIXCOEFFICIENT_XvYCC_709", (int32_t)dsDISPLAY_MATRIXCOEFFICIENT_XvYCC_709},
    {"dsDISPLAY_MATRIXCOEFFICIENT_eXvYCC_601", (int32_t)dsDISPLAY_MATRIXCOEFFICIENT_eXvYCC_601},
    {"dsDISPLAY_MATRIXCOEFFICIENT_BT_2020_NCL", (int32_t)dsDISPLAY_MATRIXCOEFFICIENT_BT_2020_NCL},
    {"dsDISPLAY_MATRIXCOEFFICIENT_BT_2020_CL", (int32_t)dsDISPLAY_MATRIXCOEFFICIENT_BT_2020_CL},
    {"dsDISPLAY_MATRIXCOEFFICIENT_eDVI_FR_RGB", (int32_t)dsDISPLAY_MATRIXCOEFFICIENT_eDVI_FR_RGB},
    {"dsDISPLAY_MATRIXCOEFFICIENT_eHDMI_RGB", (int32_t)dsDISPLAY_MATRIXCOEFFICIENT_eHDMI_RGB},
    {"dsDISPLAY_MATRIXCOEFFICIENT_eFCC", (int32_t)dsDISPLAY_MATRIXCOEFFICIENT_eFCC},
    {"dsDISPLAY_MATRIXCOEFFICIENT_eSMPTE_240M", (int32_t)dsDISPLAY_MATRIXCOEFFICIENT_eSMPTE_240M},
    {"dsDISPLAY_MATRIXCOEFFICIENT_eHDMI_FR_YCbCr", (int32_t)dsDISPLAY_MATRIXCOEFFICIENT_eHDMI_FR_YCbCr},
    {"dsDISPLAY_MATRIXCOEFFICIENT_MAX", (int32_t)dsDISPLAY_MATRIXCOEFFICIENT_MAX},
    {NULL, -1}
};

// Mapping table for dsDisplayColorSpace_t
const static ut_control_keyStringMapping_t  dsDisplayColorSpaceMappingTable[] = {
    {"dsDISPLAY_COLORSPACE_UNKNOWN", (int32_t)dsDISPLAY_COLORSPACE_UNKNOWN},
    {"dsDISPLAY_COLORSPACE_RGB", (int32_t)dsDISPLAY_COLORSPACE_RGB},
    {"dsDISPLAY_COLORSPACE_YCbCr422", (int32_t)dsDISPLAY_COLORSPACE_YCbCr422},
    {"dsDISPLAY_COLORSPACE_YCbCr444", (int32_t)dsDISPLAY_COLORSPACE_YCbCr444},
    {"dsDISPLAY_COLORSPACE_YCbCr420", (int32_t)dsDISPLAY_COLORSPACE_YCbCr420},
    {"dsDISPLAY_COLORSPACE_AUTO", (int32_t)dsDISPLAY_COLORSPACE_AUTO},
    {"dsDISPLAY_COLORSPACE_MAX", (int32_t)dsDISPLAY_COLORSPACE_MAX},
    {NULL, -1}
};

// Mapping table for dsDisplayColorDepth_t
const static ut_control_keyStringMapping_t  dsDisplayColorDepthMappingTable[] = {
    {"dsDISPLAY_COLORDEPTH_UNKNOWN", (int32_t)dsDISPLAY_COLORDEPTH_UNKNOWN},
    {"dsDISPLAY_COLORDEPTH_8BIT", (int32_t)dsDISPLAY_COLORDEPTH_8BIT},
    {"dsDISPLAY_COLORDEPTH_10BIT", (int32_t)dsDISPLAY_COLORDEPTH_10BIT},
    {"dsDISPLAY_COLORDEPTH_12BIT", (int32_t)dsDISPLAY_COLORDEPTH_12BIT},
    {"dsDISPLAY_COLORDEPTH_AUTO", (int32_t)dsDISPLAY_COLORDEPTH_AUTO},
    {NULL, -1}
};

// Mapping table for dsDisplayQuantizationRange_t
const static ut_control_keyStringMapping_t  dsDisplayQuantizationRangeMappingTable[] = {
    {"dsDISPLAY_QUANTIZATIONRANGE_UNKNOWN", (int32_t)dsDISPLAY_QUANTIZATIONRANGE_UNKNOWN},
    {"dsDISPLAY_QUANTIZATIONRANGE_LIMITED", (int32_t)dsDISPLAY_QUANTIZATIONRANGE_LIMITED},
    {"dsDISPLAY_QUANTIZATIONRANGE_FULL", (int32_t)dsDISPLAY_QUANTIZATIONRANGE_FULL},
    {"dsDISPLAY_QUANTIZATIONRANGE_MAX", (int32_t)dsDISPLAY_QUANTIZATIONRANGE_MAX},
    {NULL, -1}
};

// Mapping table for dsSURROUNDMode_t
const static ut_control_keyStringMapping_t  dsSURROUNDModeMappingTable[] = {
    {"dsSURROUNDMODE_NONE", (int32_t)dsSURROUNDMODE_NONE},
    {"dsSURROUNDMODE_DD", (int32_t)dsSURROUNDMODE_DD},
    {"dsSURROUNDMODE_DDPLUS", (int32_t)dsSURROUNDMODE_DDPLUS},
    {"dsSURROUNDMODE_MAX", (int32_t)dsSURROUNDMODE_MAX},
    {NULL, -1}
};

// Mapping table for dsHdcpStatus_t
const static ut_control_keyStringMapping_t  dsHdcpStatusMappingTable[] = {
    {"dsHDCP_STATUS_UNPOWERED", (int32_t)dsHDCP_STATUS_UNPOWERED},
    {"dsHDCP_STATUS_UNAUTHENTICATED", (int32_t)dsHDCP_STATUS_UNAUTHENTICATED},
    {"dsHDCP_STATUS_AUTHENTICATED", (int32_t)dsHDCP_STATUS_AUTHENTICATED},
    {"dsHDCP_STATUS_AUTHENTICATIONFAILURE", (int32_t)dsHDCP_STATUS_AUTHENTICATIONFAILURE},
    {"dsHDCP_STATUS_INPROGRESS", (int32_t)dsHDCP_STATUS_INPROGRESS},
    {"dsHDCP_STATUS_PORTDISABLED", (int32_t)dsHDCP_STATUS_PORTDISABLED},
    {"dsHDCP_STATUS_MAX", (int32_t)dsHDCP_STATUS_MAX},
    {NULL, -1}
};

// Mapping table for dsVideoResolution_t
const static ut_control_keyStringMapping_t  dsVideoResolutionMappingTable[] = {
    {"dsVIDEO_PIXELRES_720x480", (int32_t)dsVIDEO_PIXELRES_720x480},
    {"dsVIDEO_PIXELRES_720x576", (int32_t)dsVIDEO_PIXELRES_720x576},
    {"dsVIDEO_PIXELRES_1280x720", (int32_t)dsVIDEO_PIXELRES_1280x720},
    {"dsVIDEO_PIXELRES_1366x768", (int32_t)dsVIDEO_PIXELRES_1366x768},
    {"dsVIDEO_PIXELRES_1920x1080", (int32_t)dsVIDEO_PIXELRES_1920x1080},
    {"dsVIDEO_PIXELRES_3840x2160", (int32_t)dsVIDEO_PIXELRES_3840x2160},
    {"dsVIDEO_PIXELRES_4096x2160", (int32_t)dsVIDEO_PIXELRES_4096x2160},
    {"dsVIDEO_PIXELRES_MAX", (int32_t)dsVIDEO_PIXELRES_MAX},
    {NULL, -1}
};

// Mapping table for dsVideoAspectRatio_t
const static ut_control_keyStringMapping_t  dsVideoAspectRatioMappingTable[] = {
    {"dsVIDEO_ASPECT_RATIO_4x3", (int32_t)dsVIDEO_ASPECT_RATIO_4x3},
    {"dsVIDEO_ASPECT_RATIO_16x9", (int32_t)dsVIDEO_ASPECT_RATIO_16x9},
    {"dsVIDEO_ASPECT_RATIO_MAX", (int32_t)dsVIDEO_ASPECT_RATIO_MAX},
    {NULL, -1}
};

// Mapping table for dsVideoStereoScopicMode_t
const static ut_control_keyStringMapping_t  dsVideoStereoScopicModeMappingTable[] = {
    {"dsVIDEO_SSMODE_UNKNOWN", (int32_t)dsVIDEO_SSMODE_UNKNOWN},
    {"dsVIDEO_SSMODE_2D", (int32_t)dsVIDEO_SSMODE_2D},
    {"dsVIDEO_SSMODE_3D_SIDE_BY_SIDE", (int32_t)dsVIDEO_SSMODE_3D_SIDE_BY_SIDE},
    {"dsVIDEO_SSMODE_3D_TOP_AND_BOTTOM", (int32_t)dsVIDEO_SSMODE_3D_TOP_AND_BOTTOM},
    {"dsVIDEO_SSMODE_MAX", (int32_t)dsVIDEO_SSMODE_MAX},
    {NULL, -1}
};

// Mapping table for dsVideoFrameRate_t
const static ut_control_keyStringMapping_t  dsVideoFrameRateMappingTable[] = {
    {"dsVIDEO_FRAMERATE_UNKNOWN", (int32_t)dsVIDEO_FRAMERATE_UNKNOWN},
    {"dsVIDEO_FRAMERATE_24", (int32_t)dsVIDEO_FRAMERATE_24},
    {"dsVIDEO_FRAMERATE_25", (int32_t)dsVIDEO_FRAMERATE_25},
    {"dsVIDEO_FRAMERATE_30", (int32_t)dsVIDEO_FRAMERATE_30},
    {"dsVIDEO_FRAMERATE_60", (int32_t)dsVIDEO_FRAMERATE_60},
    {"dsVIDEO_FRAMERATE_23dot98", (int32_t)dsVIDEO_FRAMERATE_23dot98},
    {"dsVIDEO_FRAMERATE_29dot97", (int32_t)dsVIDEO_FRAMERATE_29dot97},
    {"dsVIDEO_FRAMERATE_50", (int32_t)dsVIDEO_FRAMERATE_50},
    {"dsVIDEO_FRAMERATE_59dot94", (int32_t)dsVIDEO_FRAMERATE_59dot94},
    {"dsVIDEO_FRAMERATE_MAX", (int32_t)dsVIDEO_FRAMERATE_MAX},
    {NULL, -1}
};

// Mapping table for dsHdcpProtocolVersion_t
const static ut_control_keyStringMapping_t  dsHdcpProtocolVersionMappingTable[] = {
    {"dsHDCP_VERSION_1X", (int32_t)dsHDCP_VERSION_1X},
    {"dsHDCP_VERSION_2X", (int32_t)dsHDCP_VERSION_2X},
    {"dsHDCP_VERSION_MAX", (int32_t)dsHDCP_VERSION_MAX},
    {NULL, -1}
};

// Define the mapping table for dsVideoBackgroundColor_t
const static ut_control_keyStringMapping_t  dsVideoBackgroundColorMappingTable[] = {
    {"dsVIDEO_BGCOLOR_BLUE",(int32_t)dsVIDEO_BGCOLOR_BLUE },
    {"dsVIDEO_BGCOLOR_BLACK",dsVIDEO_BGCOLOR_BLACK },
    {"dsVIDEO_BGCOLOR_NONE",dsVIDEO_BGCOLOR_NONE },
    {"dsVIDEO_BGCOLOR_MAX",dsVIDEO_BGCOLOR_MAX },
    {NULL, -1 }
};

// Mapping table for dsVideoScanMode_t
const static ut_control_keyStringMapping_t  dsVideoScanModeMappingTable[] = {
    {"dsVIDEO_SCANMODE_INTERLACED", (int32_t)dsVIDEO_SCANMODE_INTERLACED},
    {"dsVIDEO_SCANMODE_PROGRESSIVE", (int32_t)dsVIDEO_SCANMODE_PROGRESSIVE},
    {"dsVIDEO_SCANMODE_MAX", (int32_t)dsVIDEO_SCANMODE_MAX},
    {NULL, -1}
};

// Mapping table for boolean values
const static ut_control_keyStringMapping_t  boolMappingTable[] = {
    {"true", (int32_t)true},
    {"false", (int32_t)false},
    {NULL, -1}
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

/*callback*/
void VideoFormatCallback(dsHDRStandard_t videoFormat)
{
    UT_LOG_INFO("VideoFormatCallback dsHDRStandard_t:[%s] ",UT_Control_GetMapString(dsHDRStandardMappingTable, videoFormat));

}
void HdcpStatusCallback(intptr_t handle, dsHdcpStatus_t status)
{
    UT_LOG_INFO("HdcpStatusCallback dsHdcpStatus_t:[%s] ",UT_Control_GetMapString(dsHdcpStatusMappingTable, status));
}

void dsVideoPort_Init()
{
    dsError_t status   = dsERR_NONE;

    UT_LOG_INFO("Calling dsVideoPortInit()");
    status = dsVideoPortInit();
    UT_LOG_INFO("Result dsVideoPortInit() dsError_t=[%s]", UT_Control_GetMapString(dsErrorMappingTable, status));
    assert(status == dsERR_NONE);

}

void dsVideoPort_Term()
{
    dsError_t status   = dsERR_NONE;

    UT_LOG_INFO("Calling dsVideoPort_Term()");
    status = dsVideoPortTerm();
    UT_LOG_INFO("Result dsVideoPortTerm() dsError_t=[%s]",  UT_Control_GetMapString(dsErrorMappingTable, status));
    assert(status == dsERR_NONE);
}

static void dsVideoPort_getHandle()
{
    dsError_t status   = dsERR_NONE;
    int32_t choice,port;

    UT_LOG_INFO(" \t  Supported Video Port are:");
    UT_LOG_INFO("------------------------------------------");
    for (port = 0; port < gDSvideoPort_NumberOfPorts; port++) {
        UT_LOG_INFO("\t%d.  %-20s\n", port+1, UT_Control_GetMapString(dsVideoPortMappingTable, gDSVideoPortConfiguration[port].typeid));
    }
    UT_LOG_INFO("------------------------------------------");
    UT_LOG_INFO(" Select the Video Port:");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);
    port = choice - 1;
    UT_LOG_INFO("Port %d choice %d ",port,choice);
    if(choice < 1 || choice > gDSvideoPort_NumberOfPorts) {
        UT_LOG_ERROR("Invalid Port choice\n");
        return;
    }

    UT_LOG_INFO("Calling dsGetVideoPort(type:[%s],index:[%d])",UT_Control_GetMapString(dsVideoPortMappingTable, gDSVideoPortConfiguration[port].typeid));

    status = dsGetVideoPort(gDSVideoPortConfiguration[port].typeid, gDSVideoPortConfiguration[port].index, &gHandle);
    UT_LOG_INFO("Result dsGetVideoPort(Handle:[0x%0X]]) dsError_t=[%s]", gHandle, UT_Control_GetMapString(dsErrorMappingTable, status));
    assert(status == dsERR_NONE);

}

void dsVideoPort_EnablePort()
{
    dsError_t status   = dsERR_NONE;
    bool enabled    = false;
    bool connected  = false;
    bool active     = false;

    dsVideoPort_getHandle();

    UT_LOG_INFO("Calling dsVideoFormatUpdateRegisterCB()");
    status = dsVideoFormatUpdateRegisterCB(VideoFormatCallback);
    UT_LOG_INFO("Result dsVideoFormatUpdateRegisterCB() dsError_t=[%s]",  UT_Control_GetMapString(dsErrorMappingTable, status));
    assert(status == dsERR_NONE);

    UT_LOG_INFO("Calling dsRegisterHdcpStatusCallback()");
    status = dsRegisterHdcpStatusCallback(gHandle, HdcpStatusCallback);
    UT_LOG_INFO("Result dsRegisterHdcpStatusCallback() dsError_t=[%s]",  UT_Control_GetMapString(dsErrorMappingTable, status));
    assert(status == dsERR_NONE);

    UT_LOG_INFO("Calling dsIsVideoPortEnabled(Handle:[0x%0X]]) ", gHandle);
    status = dsIsVideoPortEnabled(gHandle, &enabled);
    UT_LOG_INFO("Result dsIsVideoPortEnabled(enabled:[%s]) dsError_t=[%s]",UT_Control_GetMapString(boolMappingTable, enabled),  UT_Control_GetMapString(dsErrorMappingTable, status));
    assert(status == dsERR_NONE);
    if(!enabled){
        UT_LOG_INFO("Calling dsEnableVideoPort(Handle:[0x%0X]],Enable:[true]) ", gHandle);
        status = dsEnableVideoPort(gHandle, true);
        UT_LOG_INFO("Result dsEnableVideoPort() dsError_t=[%s]",  UT_Control_GetMapString(dsErrorMappingTable, status));
        assert(status == dsERR_NONE);
        UT_LOG_INFO("Calling dsIsVideoPortEnabled(Handle:[0x%0X]]) ", gHandle);
        status = dsIsVideoPortEnabled(gHandle, &enabled);
        UT_LOG_INFO("Result dsIsVideoPortEnabled(enabled:[%s]) dsError_t=[%s]",UT_Control_GetMapString(boolMappingTable, enabled),  UT_Control_GetMapString(dsErrorMappingTable, status));
        assert(status == dsERR_NONE);
    }
    UT_LOG_INFO("Calling dsIsDisplayConnected(Handle:[0x%0X]]) ", gHandle);
    status = dsIsDisplayConnected(gHandle, &connected);
    UT_LOG_INFO("Result dsIsDisplayConnected(connected[%s]) dsError_t=[%s]",UT_Control_GetMapString(boolMappingTable, enabled),  UT_Control_GetMapString(dsErrorMappingTable, status));
    assert(status == dsERR_NONE);

    UT_LOG_INFO("Calling dsIsVideoPortActive(Handle:[0x%0X]]) ", gHandle);
    status = dsIsVideoPortActive(gHandle, &active);
    UT_LOG_INFO("Result dsIsVideoPortActive(active:[%s])  dsError_t=[%s]",UT_Control_GetMapString(boolMappingTable, enabled),  UT_Control_GetMapString(dsErrorMappingTable, status));
    assert(status == dsERR_NONE);

}

void dsVideoPort_DisablePort()
{
    dsError_t status   = dsERR_NONE;
    bool enabled    = false;
    bool connected  = false;
    bool active     = false;

    dsVideoPort_getHandle();

    UT_LOG_INFO("Calling dsIsVideoPortEnabled(Handle:[0x%0X]]) ", gHandle);
    status = dsIsVideoPortEnabled(gHandle, &enabled);
    UT_LOG_INFO("Result dsIsVideoPortEnabled(enabled:[%s]) dsError_t=[%s]",UT_Control_GetMapString(boolMappingTable, enabled),  UT_Control_GetMapString(dsErrorMappingTable, status));
    assert(status == dsERR_NONE);
    if(enabled){
        UT_LOG_INFO("Calling dsEnableVideoPort(Handle:[0x%0X]],Enable:[false]) ", gHandle);
        status = dsEnableVideoPort(gHandle, false);
        UT_LOG_INFO("Result dsEnableVideoPort() dsError_t=[%s]",  UT_Control_GetMapString(dsErrorMappingTable, status));
        assert(status == dsERR_NONE);
        UT_LOG_INFO("Calling dsIsVideoPortEnabled(Handle:[0x%0X]]) ", gHandle);
        status = dsIsVideoPortEnabled(gHandle, &enabled);
        UT_LOG_INFO("Result dsIsVideoPortEnabled(enabled:[%s]) dsError_t=[%s]",UT_Control_GetMapString(boolMappingTable, enabled),  UT_Control_GetMapString(dsErrorMappingTable, status));
        assert(status == dsERR_NONE);
    }
    UT_LOG_INFO("Calling dsIsDisplayConnected(Handle:[0x%0X]]) ", gHandle);
    status = dsIsDisplayConnected(gHandle, &connected);
    UT_LOG_INFO("Result dsIsDisplayConnected(connected[%s]) dsError_t=[%s]",UT_Control_GetMapString(boolMappingTable, enabled),  UT_Control_GetMapString(dsErrorMappingTable, status));
    assert(status == dsERR_NONE);

    UT_LOG_INFO("Calling dsIsVideoPortActive(Handle:[0x%0X]]) ", gHandle);
    status = dsIsVideoPortActive(gHandle, &active);
    UT_LOG_INFO("Result dsIsVideoPortActive(active:[%s])  dsError_t=[%s]",UT_Control_GetMapString(boolMappingTable, enabled),  UT_Control_GetMapString(dsErrorMappingTable, status));
    assert(status == dsERR_NONE);

}

void dsVideoPort_EnableHDCP()
{
    dsError_t status   = dsERR_NONE;
    bool enableHDCP = true;
    char hdcpKey[HDCP_KEY_MAX_SIZE] = "ADEF";
    int keySize = HDCP_KEY_MAX_SIZE;

    dsVideoPort_getHandle();
    UT_LOG_INFO("Calling dsEnableHDCP(Handle:[0x%0X]],contentProtect[%s]) ", gHandle,UT_Control_GetMapString(boolMappingTable, enableHDCP));
    status = dsEnableHDCP(gHandle, enableHDCP, hdcpKey, keySize);
    UT_LOG_INFO("Result dsEnableHDCP()  dsError_t=[%s]", UT_Control_GetMapString(dsErrorMappingTable, status));
    assert(status == dsERR_NONE);

}

void dsVideoPort_DisableHDCP()
{
    dsError_t status   = dsERR_NONE;
    bool enableHDCP = false;
    char hdcpKey[HDCP_KEY_MAX_SIZE] = "ADEF";
    int keySize = HDCP_KEY_MAX_SIZE;

    dsVideoPort_getHandle();
    UT_LOG_INFO("Calling dsEnableHDCP(Handle:[0x%0X]],contentProtect[%s]) ", gHandle,UT_Control_GetMapString(boolMappingTable, enableHDCP));
    status = dsEnableHDCP(gHandle, enableHDCP, hdcpKey, keySize);
    UT_LOG_INFO("Result dsEnableHDCP()  dsError_t=[%s]", UT_Control_GetMapString(dsErrorMappingTable, status));
    assert(status == dsERR_NONE);

}

void dsVideoPort_CurrentOutputSettings()
{
    dsError_t status   = dsERR_NONE;
    dsHDRStandard_t hdr_standard;
    dsDisplayMatrixCoefficients_t matrix_coef;
    dsDisplayColorSpace_t color_space;
    unsigned int color_depth;
    dsDisplayQuantizationRange_t quant_range;

    dsVideoPort_getHandle();

    UT_LOG_INFO("Calling dsGetCurrentOutputSettings(Handle:[0x%0X]]) ", gHandle);
    status = dsGetCurrentOutputSettings(gHandle, &hdr_standard ,&matrix_coef, &color_space,\
                &color_depth, &quant_range);
    UT_LOG_INFO("Result dsGetCurrentOutputSettings(dsHDRStandard_t:[%s],dsDisplayMatrixCoefficients_t:[%s],",\
                                                   UT_Control_GetMapString(dsHDRStandardMappingTable, hdr_standard),\
                                                   UT_Control_GetMapString(dsDisplayMatrixCoefficientsMappingTable, matrix_coef));
    UT_LOG_INFO("dsDisplayColorSpace_t:[%s], color_depth:[%s],dsDisplayQuantizationRange_t:[%s],dsError_t=[%s])",
                                                   UT_Control_GetMapString(dsDisplayColorSpaceMappingTable, color_space),\
                                                   UT_Control_GetMapString(dsDisplayColorDepthMappingTable, color_depth),\
                                                   UT_Control_GetMapString(dsDisplayQuantizationRangeMappingTable, quant_range),\
                                                    UT_Control_GetMapString(dsErrorMappingTable, status));
    assert(status == dsERR_NONE);
}

void dsVideoPort_GetSurroundMode()
{
    dsError_t status   = dsERR_NONE;
    bool surround   = false;
    int surround_mode = 0;

    dsVideoPort_getHandle();

    UT_LOG_INFO("Calling dsIsDisplaySurround(Handle:[0x%0X]]) ", gHandle);
    status = dsIsDisplaySurround(gHandle, &surround);
    UT_LOG_INFO("Result dsIsDisplaySurround(surround: [%s]) ,dsError_t=[%s]", UT_Control_GetMapString(boolMappingTable, surround),\
                                                                UT_Control_GetMapString(dsErrorMappingTable, status));
    assert(status == dsERR_NONE);

    if(surround){
        UT_LOG_INFO("Calling dsGetSurroundMode(Handle:[0x%0X]]) ", gHandle);
        status = dsGetSurroundMode(gHandle, &surround_mode);
        UT_LOG_INFO("Result dsGetSurroundMode(dsSURROUNDMode_t:[%s]),dsError_t=[%s]", UT_Control_GetMapString(dsSURROUNDModeMappingTable, surround_mode),\
                                                                           UT_Control_GetMapString(dsErrorMappingTable, status));
        assert(status == dsERR_NONE);
    }
}

void dsVideoPort_GetResolution()
{
    dsError_t status   = dsERR_NONE;
    dsVideoPortResolution_t getResolution;

    dsVideoPort_getHandle();

    UT_LOG_INFO("Calling dsGetResolution(Handle:[0x%0X]]) ", gHandle);
    status = dsGetResolution(gHandle, &getResolution);
    UT_LOG_INFO("Result dsGetResolution(dsVideoPortResolution_t(name:[%s],dsVideoResolution_t:[%s],dsVideoAspectRatio_t:[%s] ", getResolution.name,UT_Control_GetMapString(dsVideoResolutionMappingTable, getResolution.pixelResolution),\
                                                    UT_Control_GetMapString(dsVideoAspectRatioMappingTable, getResolution.aspectRatio));
    UT_LOG_INFO(" dsVideoStereoScopicMode_t:[%s],dsVideoFrameRate_t:[%s],interlaced:[%s],dsError_t=[%s])",UT_Control_GetMapString(dsVideoStereoScopicModeMappingTable, getResolution.stereoScopicMode),\
                                                    UT_Control_GetMapString(dsVideoFrameRateMappingTable, getResolution.frameRate),\
                                                    UT_Control_GetMapString(boolMappingTable, getResolution.interlaced),\
                                                     UT_Control_GetMapString(dsErrorMappingTable, status));
    assert(status == dsERR_NONE);
}


void dsVideoPort_SetResolution()
{
    dsError_t status   = dsERR_NONE;
    int32_t choice,n=1,port,i;

    dsVideoPort_getHandle();

    UT_LOG_INFO("Supported Resolution");
    UT_LOG_INFO("------------------------------------------");

    for (port = 0; port < gDSvideoPort_NumberOfPorts; port++) {
        UT_LOG_INFO("gDSvideoPort_NumberOfPorts: %d no :%d",gDSvideoPort_NumberOfPorts,gDSVideoPortConfiguration[port].numSupportedResolutions);

        for (i = 0; i < gDSVideoPortConfiguration[port].numSupportedResolutions; i++) {
            UT_LOG_INFO("\t%d.  %s frame rate:%s interlaced:%s \n",i,UT_Control_GetMapString(dsVideoResolutionMappingTable, gDSVideoPortConfiguration[port].supportedResolutions[i].pixelResolution),\
                                                UT_Control_GetMapString(dsVideoFrameRateMappingTable, gDSVideoPortConfiguration[port].supportedResolutions[i].frameRate),\
                                                UT_Control_GetMapString(dsVideoScanModeMappingTable, gDSVideoPortConfiguration[port].supportedResolutions[i].interlaced));
        }
    }
    UT_LOG_INFO("Enter your choice: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);

    i = choice;
    port = port -1;

    UT_LOG_INFO("Calling dsSetResolution(In:handle: [%ld],In:dsVideoPortResolution_t[dsVideoResolution_t:[%s]) ", gHandle,UT_Control_GetMapString(dsVideoResolutionMappingTable, gDSVideoPortConfiguration[port].supportedResolutions[i].pixelResolution));
    status = dsSetResolution(gHandle, &gDSVideoPortConfiguration[port].supportedResolutions[i]);
    UT_LOG_INFO("Result dsSetResolution(In:handle: [%ld],In:dsVideoPortResolution_t[dsVideoResolution_t:[%s], dsError_t=[%s]) ", gHandle,UT_Control_GetMapString(dsVideoResolutionMappingTable, gDSVideoPortConfiguration[port].supportedResolutions[i].pixelResolution),\
                                                             UT_Control_GetMapString(dsErrorMappingTable, status));
    assert(status == dsERR_NONE);
}

void dsVideoPort_GetVideoEOTF()
{
    dsError_t status   = dsERR_NONE;
    dsHDRStandard_t eotf;

    dsVideoPort_getHandle();
    UT_LOG_INFO("Calling dsGetVideoEOTF(Handle:[0x%0X]]) ", gHandle);
    status = dsGetVideoEOTF(gHandle, &eotf);
    UT_LOG_INFO("Result dsGetVideoEOTF(dsHDRStandard_t:[%s]) ,dsError_t=[%s]", UT_Control_GetMapString(dsHDRStandardMappingTable, eotf),\
                                                         UT_Control_GetMapString(dsErrorMappingTable, status));
    assert(status == dsERR_NONE);
    UT_LOG_INFO("current HDR format %d",eotf);

}

void dsVideoPort_IsOutputHDR()
{
    dsError_t status   = dsERR_NONE;
    bool hdr = false;

    dsVideoPort_getHandle();
    UT_LOG_INFO("Calling dsIsOutputHDR(Handle:[0x%0X]]) ", gHandle);
    status = dsIsOutputHDR(gHandle, &hdr);
    UT_LOG_INFO("Result dsIsOutputHDR(hdr: [%s]) ,dsError_t=[%s] ", UT_Control_GetMapString(boolMappingTable, hdr),\
                                         UT_Control_GetMapString(dsErrorMappingTable, status));
    assert(status == dsERR_NONE);
    UT_LOG_INFO("Is OUTPUT is HDR %d",hdr);
}

void dsVideoPort_SetForceHDRMode()
{
    dsError_t status   = dsERR_NONE;
    int32_t choice,i;

    dsVideoPort_getHandle();

    UT_LOG_INFO("\t Supported HDR modes ");
    UT_LOG_INFO("------------------------------------------");
    for(i=0;i<=dsHDRSTANDARD_SDR;i = (dsHDRStandard_t)(i ? i << 1 : 1))
    {
        UT_LOG_INFO("\t%d.  %s\n",i,UT_Control_GetMapString(dsHDRStandardMappingTable, i));
    }

    UT_LOG_INFO("Enter your choice: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);

    UT_LOG_INFO("Calling dsSetForceHDRMode(Handle:[0x%0X]] dsHDRStandard_t:[%s]) ", gHandle,UT_Control_GetMapString(dsHDRStandardMappingTable, choice));
    status = dsSetForceHDRMode(gHandle, (dsHDRStandard_t)choice);
    UT_LOG_INFO("Result dsSetForceHDRMode() ,dsError_t=[%s] ", UT_Control_GetMapString(dsErrorMappingTable, status));
    assert(status == dsERR_NONE);

}

void dsVideoPort_ResetOutputToSDR()
{
    dsError_t status   = dsERR_NONE;
    bool hdr = false;

    dsVideoPort_getHandle();

    UT_LOG_INFO("Calling dsResetOutputToSDR(Handle:[0x%0X]]) ", gHandle);
    status = dsResetOutputToSDR();
    UT_LOG_INFO("Result dsResetOutputToSDR() ,dsError_t=[%s] ", UT_Control_GetMapString(dsErrorMappingTable, status));
    assert(status == dsERR_NONE);

    UT_LOG_INFO("Calling dsIsOutputHDR(Handle:[0x%0X]]) ", gHandle);
    status = dsIsOutputHDR(gHandle, &hdr);
    UT_LOG_INFO("Result dsIsOutputHDR(hdr: [%s]) ,dsError_t=[%s] ", UT_Control_GetMapString(boolMappingTable, hdr),\
                                         UT_Control_GetMapString(dsErrorMappingTable, status));
}

void dsVideoPort_GetHDCPStatus()
{
    dsError_t      status = dsERR_NONE;
    dsHdcpStatus_t hdcpStatus;

    dsVideoPort_getHandle();
    UT_LOG_INFO("Calling dsGetHDCPStatus(Handle:[0x%0X]]) ", gHandle);
    status = dsGetHDCPStatus(gHandle, &(hdcpStatus));
    UT_LOG_INFO("Result dsGetHDCPStatus(dsHdcpStatus_t:[%s]) ,dsError_t=[%s] ", UT_Control_GetMapString(dsHdcpStatusMappingTable, hdcpStatus),\
                                         UT_Control_GetMapString(dsErrorMappingTable, status));
    assert(status == dsERR_NONE);
    UT_LOG_INFO("HDCP Status %d",hdcpStatus);

}

void dsVideoPort_GetHDCPCurrentProtocol()
{
    dsError_t status   = dsERR_NONE;
    dsHdcpProtocolVersion_t currentProtocol;

    dsVideoPort_getHandle();
    UT_LOG_INFO("Calling dsGetHDCPCurrentProtocol(Handle:[0x%0X]]) ", gHandle);
    status = dsGetHDCPCurrentProtocol(gHandle, &currentProtocol);
    UT_LOG_INFO("Result dsGetHDCPCurrentProtocol(dsHdcpProtocolVersion_t:[%s]) ,dsError_t=[%s] ", UT_Control_GetMapString(dsHdcpProtocolVersionMappingTable, currentProtocol),\
                                         UT_Control_GetMapString(dsErrorMappingTable, status));
    assert(status == dsERR_NONE);
    UT_LOG_INFO("HDCP Current Protocol Version: %d", currentProtocol);

}

void dsVideoPort_GetHDCPReceiverProtocol()
{
    dsError_t status   = dsERR_NONE;
    dsHdcpProtocolVersion_t protocolVersion;

    dsVideoPort_getHandle();
    UT_LOG_INFO("Calling dsGetHDCPCurrentProtocol(Handle:[0x%0X]]) ", gHandle);
    status = dsGetHDCPReceiverProtocol(gHandle, &(protocolVersion));
    UT_LOG_INFO("Result dsGetHDCPReceiverProtocol(dsHdcpProtocolVersion_t:[%s]) ,dsError_t=[%s] ", UT_Control_GetMapString(dsHdcpProtocolVersionMappingTable, protocolVersion),\
                                         UT_Control_GetMapString(dsErrorMappingTable, status));
    assert(status == dsERR_NONE);
    UT_LOG_INFO("HDCP Receiver Protocol Version: %d", protocolVersion);

}

void dsVideoPort_GetIgnoreEDIDStatus()
{
    dsError_t status   = dsERR_NONE;
    bool ignoreEDIDStatus;

    dsVideoPort_getHandle();
    UT_LOG_INFO("Calling dsGetIgnoreEDIDStatus(Handle:[0x%0X]]) ", gHandle);
    status = dsGetIgnoreEDIDStatus(gHandle, &ignoreEDIDStatus);
    UT_LOG_INFO("Result dsGetIgnoreEDIDStatus(status:[%s]) ,dsError_t=[%s] ", UT_Control_GetMapString(boolMappingTable, ignoreEDIDStatus),\
                                         UT_Control_GetMapString(dsErrorMappingTable, status));
    assert(status == dsERR_NONE);
    UT_LOG_INFO("Ignore EDID Status: %d", ignoreEDIDStatus);

}

void dsVideoPort_SetHdmiPreference()
{
    dsError_t status   = dsERR_NONE;
    int32_t choice,i;
    dsHdcpProtocolVersion_t hdcpCurrentProtocol;

    dsVideoPort_getHandle();
    UT_LOG_INFO("\t Supported HDCP Versions ");
    UT_LOG_INFO("------------------------------------------");
    for(i=0;i<dsHDCP_VERSION_MAX;i++)
    {
        UT_LOG_INFO("\t%d.  %s\n",i,UT_Control_GetMapString(dsHdcpProtocolVersionMappingTable,i));
    }

    UT_LOG_INFO("Select the Hdmi Preference to set: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);

    hdcpCurrentProtocol = (dsHdcpProtocolVersion_t)choice;
    UT_LOG_INFO("Calling dsSetHdmiPreference(Handle:[0x%0X]]dsHdcpProtocolVersion_t:[%s]) ", gHandle,UT_Control_GetMapString(dsHdcpProtocolVersionMappingTable, hdcpCurrentProtocol));
    status = dsSetHdmiPreference(gHandle, &hdcpCurrentProtocol);
    UT_LOG_INFO("Result dsSetHdmiPreference(),dsError_t=[%s] ",  UT_Control_GetMapString(dsErrorMappingTable, status));
    assert(status == dsERR_NONE);

}

void dsVideoPort_GetHdmiPreference()
{
    dsError_t status   = dsERR_NONE;
    dsHdcpProtocolVersion_t  hdcpCurrentProtocol;

    dsVideoPort_getHandle();
    UT_LOG_INFO("Calling dsGetHdmiPreference(Handle:[0x%0X]]) ", gHandle);
    status = dsGetHdmiPreference(gHandle, &hdcpCurrentProtocol);
    UT_LOG_INFO("Result dsGetHdmiPreference(dsHdcpProtocolVersion_t:[%s],dsError_t=[%s]) ", UT_Control_GetMapString(dsHdcpProtocolVersionMappingTable, hdcpCurrentProtocol),\
                                                         UT_Control_GetMapString(dsErrorMappingTable, status));
    assert(status == dsERR_NONE);
    UT_LOG_INFO("Get HDMI Preference: %d", hdcpCurrentProtocol);

}

void dsVideoPort_GetColorSpace()
{
    dsError_t status   = dsERR_NONE;
    dsDisplayColorSpace_t color_space;

    dsVideoPort_getHandle();
    UT_LOG_INFO("Calling dsGetColorSpace(Handle:[0x%0X]]) ", gHandle);
    status = dsGetColorSpace(gHandle, &color_space);
    UT_LOG_INFO("Result dsGetColorSpace(dsDisplayColorSpace_t:[%s], dsError_t=[%s]) ", UT_Control_GetMapString(dsDisplayColorSpaceMappingTable, color_space),\
                                             UT_Control_GetMapString(dsErrorMappingTable, status));
    assert(status == dsERR_NONE);
    UT_LOG_INFO("Get Color Space: %d", color_space);

}

void dsVideoPort_GetColorDepth()
{
    dsError_t status   = dsERR_NONE;
    unsigned int colorDepth;

    dsVideoPort_getHandle();
    UT_LOG_INFO("Calling dsGetColorDepth(Handle:[0x%0X]]) ", gHandle);
    status = dsGetColorDepth(gHandle, &colorDepth);
    UT_LOG_INFO("Result dsGetColorDepth(dsDisplayColorDepth_t:[%s], dsError_t=[%s]) ", UT_Control_GetMapString(dsDisplayColorDepthMappingTable, colorDepth),\
                                             UT_Control_GetMapString(dsErrorMappingTable, status));
    assert(status == dsERR_NONE);
    UT_LOG_INFO("Get Color Depth: %d", colorDepth);

}

void dsVideoPort_SetPreferredColorDepth()
{
    dsError_t status   = dsERR_NONE;
    int32_t choice,i;

    dsVideoPort_getHandle();
    UT_LOG_INFO("\t Supported display Color depth to set ");
    UT_LOG_INFO("------------------------------------------\n");
    for(i=dsDISPLAY_COLORDEPTH_8BIT;i<=dsDISPLAY_COLORDEPTH_AUTO;i<<=1)
    {
        UT_LOG_INFO("\t%d.  %s\n",i,UT_Control_GetMapString(dsDisplayColorDepthMappingTable, i));
    }

    UT_LOG_INFO("Enter your choice: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);

    UT_LOG_INFO("Calling dsSetPreferredColorDepth(Handle:[0x%0X]],dsDisplayColorDepth_t:[%s]) ", gHandle,UT_Control_GetMapString(dsDisplayColorDepthMappingTable, (dsDisplayColorDepth_t)choice));
    status = dsSetPreferredColorDepth(gHandle, (dsDisplayColorDepth_t)choice);
    UT_LOG_INFO("Result dsGetColorDepth(),dsError_t=[%s] ",  UT_Control_GetMapString(dsErrorMappingTable, status));
    assert(status == dsERR_NONE);

}

void dsVideoPort_GetPreferredColorDepth()
{
    dsError_t status   = dsERR_NONE;
    unsigned int colorDepth;

    dsVideoPort_getHandle();
    UT_LOG_INFO("Calling dsGetPreferredColorDepth(Handle:[0x%0X]]) ", gHandle);
    status = dsGetPreferredColorDepth(gHandle, &colorDepth);
    UT_LOG_INFO("Result dsGetPreferredColorDepth(),dsError_t=[%s] ", UT_Control_GetMapString(dsDisplayColorDepthMappingTable, colorDepth),\
                                                     UT_Control_GetMapString(dsErrorMappingTable, status));
    assert(status == dsERR_NONE);
    UT_LOG_INFO("Get Preferred Color Depth: %d", colorDepth);

}

void dsVideoPort_SetBackgroundColor()
{
    dsError_t status   = dsERR_NONE;
    int32_t choice=0,i;

    dsVideoPort_getHandle();
    UT_LOG_INFO("\t Select Background Color to set ");
    UT_LOG_INFO("------------------------------------------");
    for(i=0;i<=dsVIDEO_BGCOLOR_MAX ;i++)
    {
        UT_LOG_INFO("\t%d.  %s\n",i,UT_Control_GetMapString(dsVideoBackgroundColorMappingTable, i));
    }

    UT_LOG_INFO("Enter your choice: ");
    scanf("%d", &choice);
    readAndDiscardRestOfLine(stdin);

    UT_LOG_INFO("Invoking dsSetForceHDRMode() with HDR Mode:%d ",choice);
    UT_LOG_INFO("Calling dsSetBackgroundColor(Handle:[0x%0X]],dsVideoBackgroundColor_t:[%s]) ", gHandle,UT_Control_GetMapString(dsVideoBackgroundColorMappingTable, (dsVideoBackgroundColor_t)choice));
    status = dsSetBackgroundColor(gHandle, (dsVideoBackgroundColor_t)choice);
    UT_LOG_INFO("Result dsSetBackgroundColor(),dsError_t=[%s] ",  UT_Control_GetMapString(dsErrorMappingTable, status));
    assert(status == dsERR_NONE);

}

static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main tests for this module
 *
 * @return int - 0 on success, otherwise failure
 */

int test_l3_dsVideoPort_register(void)
{
    // Create the test suite
    if(gSourceType == 1)
    {
        pSuite = UT_add_suite("[L3 dsVideoPort - Source]", NULL, NULL);
    }
    else
    {
        pSuite = UT_add_suite("[L3 dsVideoPort - Sink]", NULL, NULL);
    }
    if (pSuite == NULL)
    {
        return -1;
    }
    // Create the test suite
    UT_add_test( pSuite, "VideoPort Init", dsVideoPort_Init);
    UT_add_test( pSuite, "VideoPort Term", dsVideoPort_Term);
    UT_add_test( pSuite, "Enable VideoPort", dsVideoPort_EnablePort);
    UT_add_test( pSuite, "Disable VideoPort", dsVideoPort_DisablePort);
    UT_add_test( pSuite, "Get CurrentOutputSettings", dsVideoPort_CurrentOutputSettings);
    UT_add_test( pSuite, "Get Resolution",dsVideoPort_GetResolution);
    UT_add_test( pSuite, "Get VideoEOTF",dsVideoPort_GetVideoEOTF);
    UT_add_test( pSuite, "IsOutputHDR",dsVideoPort_IsOutputHDR);
    UT_add_test( pSuite, "Get HDCPStatus",dsVideoPort_GetHDCPStatus);
    UT_add_test( pSuite, "Get HDCPCurrentProtocol",dsVideoPort_GetHDCPCurrentProtocol);
    UT_add_test( pSuite, "Set HdmiPreference",dsVideoPort_SetHdmiPreference);
    UT_add_test( pSuite, "Get HdmiPreference",dsVideoPort_GetHdmiPreference);
    UT_add_test( pSuite, "Get ColorSpace",dsVideoPort_GetColorSpace);
    UT_add_test( pSuite, "Get ColorDepth",dsVideoPort_GetColorDepth);
    if(gSourceType == 1)
    {
        // add the test suite for source type
        UT_add_test( pSuite, "Get SurroundMode",dsVideoPort_GetSurroundMode);
        UT_add_test( pSuite, "Enable HDCP",dsVideoPort_EnableHDCP);
        UT_add_test( pSuite, "Disable HDCP",dsVideoPort_DisableHDCP);
        UT_add_test( pSuite, "Set Resolution",dsVideoPort_SetResolution);
        UT_add_test( pSuite, "Set ForceHDRMode",dsVideoPort_SetForceHDRMode);
        UT_add_test( pSuite, "ResetOutputToSDR",dsVideoPort_ResetOutputToSDR);
        UT_add_test( pSuite, "Get HDCPReceiverProtocol",dsVideoPort_GetHDCPReceiverProtocol);
        UT_add_test( pSuite, "Get IgnoreEDIDStatus",dsVideoPort_GetIgnoreEDIDStatus);
        UT_add_test( pSuite, "Set PreferredColorDepth",dsVideoPort_SetPreferredColorDepth);
        UT_add_test( pSuite, "Get PreferredColorDepth",dsVideoPort_GetPreferredColorDepth);
        UT_add_test( pSuite, "Set BackgroundColor",dsVideoPort_SetBackgroundColor);
    }

    return 0;
}

/** @} */ // End of DS_VideoPort_HALTEST_L3
/** @} */ // End of DS_VideoPort_HALTEST
/** @} */ // End of Device_Settings_HALTEST
/** @} */ // End of Device_Settings
/** @} */ // End of HPK