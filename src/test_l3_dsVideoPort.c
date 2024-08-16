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
 * @defgroup DS_VideoPort_HALTEST_L2 Device Settings Video Port HAL Tests L3 File
 * @{
 * @parblock
 *
 * ### L2 Tests for DS Video Port HAL :
 *
 * Level 2 unit test cases for all APIs of Device Settings Video Port HAL
 *
 * **Pre-Conditions:**  None@n
 * **Dependencies:** None@n
 *
 * Ref to API Definition specification documentation : [ds-video-port_halSpec.md](../../docs/pages/ds-video-port_halSpec.md)
 *
 * @endparblock
 */


/**
 * @file test_l2_dsVideoPort.c
 *
 */

#include <stdlib.h>
#include <stdbool.h>
#include <ut.h>
#include <ut_log.h>
#include <ut_kvp_profile.h>
#include <ut_kvp.h>

#include "test_parse_configuration.h"
#include "dsVideoPort.h"


intptr_t gHandle = 0;

// Define the Mapping struct
typedef struct {
    int32_t value;
    const char *valueString;
} mapping_key_t;

// Mapping table for dsError_t
mapping_key_t dsErrorMappingTable[] = {
    {dsERR_NONE, "dsERR_NONE"},
    {dsERR_GENERAL, "dsERR_GENERAL"},
    {dsERR_INVALID_PARAM, "dsERR_INVALID_PARAM"},
    {dsERR_INVALID_STATE, "dsERR_INVALID_STATE"},
    {dsERR_ALREADY_INITIALIZED, "dsERR_ALREADY_INITIALIZED"},
    {dsERR_NOT_INITIALIZED, "dsERR_NOT_INITIALIZED"},
    {dsERR_OPERATION_NOT_SUPPORTED, "dsERR_OPERATION_NOT_SUPPORTED"},
    {dsERR_RESOURCE_NOT_AVAILABLE, "dsERR_RESOURCE_NOT_AVAILABLE"},
    {dsERR_OPERATION_FAILED, "dsERR_OPERATION_FAILED"},
    {dsErr_MAX, "dsErr_MAX"}
};

// Mapping table for dsVideoPortType_t
mapping_key_t dsVideoPortMappingTable[] = {
    {dsVIDEOPORT_TYPE_RF, "dsVIDEOPORT_TYPE_RF"},
    {dsVIDEOPORT_TYPE_BB, "dsVIDEOPORT_TYPE_BB"},
    {dsVIDEOPORT_TYPE_SVIDEO, "dsVIDEOPORT_TYPE_SVIDEO"},
    {dsVIDEOPORT_TYPE_1394, "dsVIDEOPORT_TYPE_1394"},
    {dsVIDEOPORT_TYPE_DVI, "dsVIDEOPORT_TYPE_DVI"},
    {dsVIDEOPORT_TYPE_COMPONENT, "dsVIDEOPORT_TYPE_COMPONENT"},
    {dsVIDEOPORT_TYPE_HDMI, "dsVIDEOPORT_TYPE_HDMI"},
    {dsVIDEOPORT_TYPE_HDMI_INPUT, "dsVIDEOPORT_TYPE_HDMI_INPUT"},
    {dsVIDEOPORT_TYPE_INTERNAL, "dsVIDEOPORT_TYPE_INTERNAL"},
    {dsVIDEOPORT_TYPE_MAX, "dsVIDEOPORT_TYPE_MAX"}
};

// Define the mapping table for dsHDRStandard_t
mapping_key_t dsHDRStandardMappingTable[] = {
    {dsHDRSTANDARD_NONE, "dsHDRSTANDARD_NONE"},
    {dsHDRSTANDARD_HDR10, "dsHDRSTANDARD_HDR10"},
    {dsHDRSTANDARD_HLG, "dsHDRSTANDARD_HLG"},
    {dsHDRSTANDARD_DolbyVision, "dsHDRSTANDARD_DolbyVision"},
    {dsHDRSTANDARD_TechnicolorPrime, "dsHDRSTANDARD_TechnicolorPrime"},
    {dsHDRSTANDARD_HDR10PLUS, "dsHDRSTANDARD_HDR10PLUS"},
    {dsHDRSTANDARD_SDR, "dsHDRSTANDARD_SDR"},
    {dsHDRSTANDARD_Invalid, "dsHDRSTANDARD_Invalid"}
};

// Define the mapping table for dsDisplayMatrixCoefficients_t
mapping_key_t dsDisplayMatrixCoefficientsMappingTable[] = {
    {dsDISPLAY_MATRIXCOEFFICIENT_UNKNOWN, "dsDISPLAY_MATRIXCOEFFICIENT_UNKNOWN"},
    {dsDISPLAY_MATRIXCOEFFICIENT_BT_709, "dsDISPLAY_MATRIXCOEFFICIENT_BT_709"},
    {dsDISPLAY_MATRIXCOEFFICIENT_BT_470_2_BG, "dsDISPLAY_MATRIXCOEFFICIENT_BT_470_2_BG"},
    {dsDISPLAY_MATRIXCOEFFICIENT_SMPTE_170M, "dsDISPLAY_MATRIXCOEFFICIENT_SMPTE_170M"},
    {dsDISPLAY_MATRIXCOEFFICIENT_XvYCC_709, "dsDISPLAY_MATRIXCOEFFICIENT_XvYCC_709"},
    {dsDISPLAY_MATRIXCOEFFICIENT_eXvYCC_601, "dsDISPLAY_MATRIXCOEFFICIENT_eXvYCC_601"},
    {dsDISPLAY_MATRIXCOEFFICIENT_BT_2020_NCL, "dsDISPLAY_MATRIXCOEFFICIENT_BT_2020_NCL"},
    {dsDISPLAY_MATRIXCOEFFICIENT_BT_2020_CL, "dsDISPLAY_MATRIXCOEFFICIENT_BT_2020_CL"},
    {dsDISPLAY_MATRIXCOEFFICIENT_eDVI_FR_RGB, "dsDISPLAY_MATRIXCOEFFICIENT_eDVI_FR_RGB"},
    {dsDISPLAY_MATRIXCOEFFICIENT_eHDMI_RGB, "dsDISPLAY_MATRIXCOEFFICIENT_eHDMI_RGB"},
    {dsDISPLAY_MATRIXCOEFFICIENT_eFCC, "dsDISPLAY_MATRIXCOEFFICIENT_eFCC"},
    {dsDISPLAY_MATRIXCOEFFICIENT_eSMPTE_240M, "dsDISPLAY_MATRIXCOEFFICIENT_eSMPTE_240M"},
    {dsDISPLAY_MATRIXCOEFFICIENT_eHDMI_FR_YCbCr, "dsDISPLAY_MATRIXCOEFFICIENT_eHDMI_FR_YCbCr"},
    {dsDISPLAY_MATRIXCOEFFICIENT_MAX, "dsDISPLAY_MATRIXCOEFFICIENT_MAX"}
};

// Define the mapping table for dsDisplayColorSpace_t
mapping_key_t dsDisplayColorSpaceMappingTable[] = {
    {dsDISPLAY_COLORSPACE_UNKNOWN, "dsDISPLAY_COLORSPACE_UNKNOWN"},
    {dsDISPLAY_COLORSPACE_RGB, "dsDISPLAY_COLORSPACE_RGB"},
    {dsDISPLAY_COLORSPACE_YCbCr422, "dsDISPLAY_COLORSPACE_YCbCr422"},
    {dsDISPLAY_COLORSPACE_YCbCr444, "dsDISPLAY_COLORSPACE_YCbCr444"},
    {dsDISPLAY_COLORSPACE_YCbCr420, "dsDISPLAY_COLORSPACE_YCbCr420"},
    {dsDISPLAY_COLORSPACE_AUTO, "dsDISPLAY_COLORSPACE_AUTO"},
    {dsDISPLAY_COLORSPACE_MAX, "dsDISPLAY_COLORSPACE_MAX"}
};

// Define the mapping table for dsDisplayColorDepth_t
mapping_key_t dsDisplayColorDepthMappingTable[] = {
    {dsDISPLAY_COLORDEPTH_UNKNOWN, "dsDISPLAY_COLORDEPTH_UNKNOWN"},
    {dsDISPLAY_COLORDEPTH_8BIT, "dsDISPLAY_COLORDEPTH_8BIT"},
    {dsDISPLAY_COLORDEPTH_10BIT, "dsDISPLAY_COLORDEPTH_10BIT"},
    {dsDISPLAY_COLORDEPTH_12BIT, "dsDISPLAY_COLORDEPTH_12BIT"},
    {dsDISPLAY_COLORDEPTH_AUTO, "dsDISPLAY_COLORDEPTH_AUTO"}
};

// Define the mapping table for dsDisplayQuantizationRange_t
mapping_key_t dsDisplayQuantizationRangeMappingTable[] = {
    {dsDISPLAY_QUANTIZATIONRANGE_UNKNOWN, "dsDISPLAY_QUANTIZATIONRANGE_UNKNOWN"},
    {dsDISPLAY_QUANTIZATIONRANGE_LIMITED, "dsDISPLAY_QUANTIZATIONRANGE_LIMITED"},
    {dsDISPLAY_QUANTIZATIONRANGE_FULL, "dsDISPLAY_QUANTIZATIONRANGE_FULL"},
    {dsDISPLAY_QUANTIZATIONRANGE_MAX, "dsDISPLAY_QUANTIZATIONRANGE_MAX"}
};

// Define the mapping table for dsSURROUNDMode_t
mapping_key_t dsSURROUNDModeMappingTable[] = {
    {dsSURROUNDMODE_NONE, "dsSURROUNDMODE_NONE"},
    {dsSURROUNDMODE_DD, "dsSURROUNDMODE_DD"},
    {dsSURROUNDMODE_DDPLUS, "dsSURROUNDMODE_DDPLUS"},
    {dsSURROUNDMODE_MAX, "dsSURROUNDMODE_MAX"}
};

// Define the mapping table for dsHdcpStatus_t
mapping_key_t dsHdcpStatusMappingTable[] = {
    {dsHDCP_STATUS_UNPOWERED, "dsHDCP_STATUS_UNPOWERED"},
    {dsHDCP_STATUS_UNAUTHENTICATED, "dsHDCP_STATUS_UNAUTHENTICATED"},
    {dsHDCP_STATUS_AUTHENTICATED, "dsHDCP_STATUS_AUTHENTICATED"},
    {dsHDCP_STATUS_AUTHENTICATIONFAILURE, "dsHDCP_STATUS_AUTHENTICATIONFAILURE"},
    {dsHDCP_STATUS_INPROGRESS, "dsHDCP_STATUS_INPROGRESS"},
    {dsHDCP_STATUS_PORTDISABLED, "dsHDCP_STATUS_PORTDISABLED"},
    {dsHDCP_STATUS_MAX, "dsHDCP_STATUS_MAX"}
};

// Define the mapping table for dsVideoResolution_t
mapping_key_t dsVideoResolutionMappingTable[] = {
    {dsVIDEO_PIXELRES_720x480, "dsVIDEO_PIXELRES_720x480"},
    {dsVIDEO_PIXELRES_720x576, "dsVIDEO_PIXELRES_720x576"},
    {dsVIDEO_PIXELRES_1280x720, "dsVIDEO_PIXELRES_1280x720"},
    {dsVIDEO_PIXELRES_1366x768, "dsVIDEO_PIXELRES_1366x768"},
    {dsVIDEO_PIXELRES_1920x1080, "dsVIDEO_PIXELRES_1920x1080"},
    {dsVIDEO_PIXELRES_3840x2160, "dsVIDEO_PIXELRES_3840x2160"},
    {dsVIDEO_PIXELRES_4096x2160, "dsVIDEO_PIXELRES_4096x2160"},
    {dsVIDEO_PIXELRES_MAX, "dsVIDEO_PIXELRES_MAX"}
};

// Define the mapping table for dsVideoAspectRatio_t
mapping_key_t dsVideoAspectRatioMappingTable[] = {
    {dsVIDEO_ASPECT_RATIO_4x3, "dsVIDEO_ASPECT_RATIO_4x3"},
    {dsVIDEO_ASPECT_RATIO_16x9, "dsVIDEO_ASPECT_RATIO_16x9"},
    {dsVIDEO_ASPECT_RATIO_MAX, "dsVIDEO_ASPECT_RATIO_MAX"}
};

// Define the mapping table for dsVideoStereoScopicMode_t
mapping_key_t dsVideoStereoScopicModeMappingTable[] = {
    {dsVIDEO_SSMODE_UNKNOWN, "dsVIDEO_SSMODE_UNKNOWN"},
    {dsVIDEO_SSMODE_2D, "dsVIDEO_SSMODE_2D"},
    {dsVIDEO_SSMODE_3D_SIDE_BY_SIDE, "dsVIDEO_SSMODE_3D_SIDE_BY_SIDE"},
    {dsVIDEO_SSMODE_3D_TOP_AND_BOTTOM, "dsVIDEO_SSMODE_3D_TOP_AND_BOTTOM"},
    {dsVIDEO_SSMODE_MAX, "dsVIDEO_SSMODE_MAX"}
};

// Define the mapping table for dsVideoFrameRate_t
mapping_key_t dsVideoFrameRateMappingTable[] = {
    {dsVIDEO_FRAMERATE_UNKNOWN, "dsVIDEO_FRAMERATE_UNKNOWN"},
    {dsVIDEO_FRAMERATE_24, "dsVIDEO_FRAMERATE_24"},
    {dsVIDEO_FRAMERATE_25, "dsVIDEO_FRAMERATE_25"},
    {dsVIDEO_FRAMERATE_30, "dsVIDEO_FRAMERATE_30"},
    {dsVIDEO_FRAMERATE_60, "dsVIDEO_FRAMERATE_60"},
    {dsVIDEO_FRAMERATE_23dot98, "dsVIDEO_FRAMERATE_23dot98"},
    {dsVIDEO_FRAMERATE_29dot97, "dsVIDEO_FRAMERATE_29dot97"},
    {dsVIDEO_FRAMERATE_50, "dsVIDEO_FRAMERATE_50"},
    {dsVIDEO_FRAMERATE_59dot94, "dsVIDEO_FRAMERATE_59dot94"},
    {dsVIDEO_FRAMERATE_MAX, "dsVIDEO_FRAMERATE_MAX"}
};

// Define the mapping table for dsHdcpProtocolVersion_t
mapping_key_t dsHdcpProtocolVersionMappingTable[] = {
    {dsHDCP_VERSION_1X, "dsHDCP_VERSION_1X"},
    {dsHDCP_VERSION_2X, "dsHDCP_VERSION_2X"},
    {dsHDCP_VERSION_MAX, "dsHDCP_VERSION_MAX"}
};

// Define the mapping table for dsVideoBackgroundColor_t
mapping_key_t dsVideoBackgroundColorMappingTable[] = {
    {dsVIDEO_BGCOLOR_BLUE, "dsVIDEO_BGCOLOR_BLUE"},
    {dsVIDEO_BGCOLOR_BLACK, "dsVIDEO_BGCOLOR_BLACK"},
    {dsVIDEO_BGCOLOR_NONE, "dsVIDEO_BGCOLOR_NONE"},
    {dsVIDEO_BGCOLOR_MAX, "dsVIDEO_BGCOLOR_MAX"}
};

// Mapping table for boolean values
mapping_key_t boolMappingTable[] = {
    {true, "true"},
    {false, "false"}
};

const char* mapToString(int32_t value, mapping_key_t* mappingTable, int tableSize) {
    for (int32_t i = 0; i < tableSize; i++) {
        if (mappingTable[i].value == value) {
            return mappingTable[i].valueString;
        }
    }
    return "Unknown value";
}

/*callback*/
void VideoFormatCallback(dsHDRStandard_t videoFormat)
{
    UT_LOG_INFO("VideoFormatCallback dsHDRStandard_t:[%s] ",mapToString(videoFormat,dsHDRStandardMappingTable,sizeof(dsHDRStandardMappingTable)/sizeof(dsHDRStandardMappingTable[0])));

}
void HdcpStatusCallback(intptr_t handle, dsHdcpStatus_t status)
{
    UT_LOG_INFO("HdcpStatusCallback dsHdcpStatus_t:[%s] ",mapToString(status,dsHDRStandardMappingTable,sizeof(dsHDRStandardMappingTable)/sizeof(dsHDRStandardMappingTable[0])));
}

void dsVideoPort_Init()
{
    dsError_t status   = dsERR_NONE;

    UT_LOG_INFO("Calling dsVideoPortInit()");
    status = dsVideoPortInit();
    UT_LOG_INFO("Result dsVideoPortInit() dsError_t=[%s]", mapToString(status,dsErrorMappingTable,sizeof(dsErrorMappingTable)/sizeof(dsErrorMappingTable[0])));
    UT_ASSERT_EQUAL_FATAL(status, dsERR_NONE);

}

void dsVideoPort_Term()
{
    dsError_t status   = dsERR_NONE;

    UT_LOG_INFO("Calling dsVideoPort_Term()");
    status = dsVideoPortTerm();
    UT_LOG_INFO("Result dsVideoPortTerm() dsError_t=[%s]", mapToString(status,dsErrorMappingTable,sizeof(dsErrorMappingTable)/sizeof(dsErrorMappingTable[0])));
    UT_ASSERT_EQUAL_FATAL(status, dsERR_NONE);
}

static void dsVideoPort_getHandle()
{
    dsError_t status   = dsERR_NONE;
    int32_t choice,port;

    UT_LOG_INFO(" \t  Supported Video Port are:");
    UT_LOG_INFO("------------------------------------------");
    for (port = 0; port < gDSvideoPort_NumberOfPorts; port++) {
        UT_LOG_INFO("\t%d.  %-20s\n", port+1, mapToString(gDSVideoPortConfiguration[port].typeid,dsVideoPortMappingTable,sizeof(dsVideoPortMappingTable)/sizeof(dsVideoPortMappingTable[0])));
    }
    UT_LOG_INFO("------------------------------------------");
    UT_LOG_INFO(" Select the Video Port:");
    scanf("%d", &choice);
    port = choice - 1;
    UT_LOG_INFO("Port %d choice %d ",port,choice);
    if(choice < 1 || choice > gDSvideoPort_NumberOfPorts) {
        UT_LOG_ERROR("Invalid Port choice\n");
        return;
    }

    UT_LOG_INFO("Calling dsGetVideoPort(type:[%s],index:[%d])",mapToString(gDSVideoPortConfiguration[port].typeid,dsVideoPortMappingTable,sizeof(dsVideoPortMappingTable)/sizeof(dsVideoPortMappingTable[0])),gDSVideoPortConfiguration[port].index);
    UT_LOG_INFO("Typeid: %d ",gDSVideoPortConfiguration[port].typeid);
    status = dsGetVideoPort(gDSVideoPortConfiguration[port].typeid, gDSVideoPortConfiguration[port].index, &gHandle);
    UT_LOG_INFO("Result dsGetVideoPort(Handle:[%ld]) dsError_t=[%s]", gHandle,mapToString(status,dsErrorMappingTable,sizeof(dsErrorMappingTable)/sizeof(dsErrorMappingTable[0])));
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    if (status != dsERR_NONE) {
        UT_LOG_ERROR("dsGetVideoPort failed with error: %d", status);
    }

}

void dsVideoPort_Enable()
{
    dsError_t status   = dsERR_NONE;
    bool enabled    = false;
    bool connected  = false;
    bool active     = false;

    dsVideoPort_getHandle();

    UT_LOG_INFO("Calling dsVideoFormatUpdateRegisterCB()");
    status = dsVideoFormatUpdateRegisterCB(VideoFormatCallback);
    UT_LOG_INFO("Result dsVideoFormatUpdateRegisterCB() dsError_t=[%s]", mapToString(status,dsErrorMappingTable,sizeof(dsErrorMappingTable)/sizeof(dsErrorMappingTable[0])));
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    UT_LOG_INFO("Calling dsRegisterHdcpStatusCallback()");
    status = dsRegisterHdcpStatusCallback(gHandle, HdcpStatusCallback);
    UT_LOG_INFO("Result dsRegisterHdcpStatusCallback() dsError_t=[%s]", mapToString(status,dsErrorMappingTable,sizeof(dsErrorMappingTable)/sizeof(dsErrorMappingTable[0])));
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    UT_LOG_INFO("Calling dsIsVideoPortEnabled(Handle:[%ld]) ", gHandle);
    status = dsIsVideoPortEnabled(gHandle, &enabled);
    UT_LOG_INFO("Result dsIsVideoPortEnabled(enabled:[%s]) dsError_t=[%s]",mapToString(enabled,boolMappingTable,sizeof(boolMappingTable)/sizeof(boolMappingTable[0])), mapToString(status,dsErrorMappingTable,sizeof(dsErrorMappingTable)/sizeof(dsErrorMappingTable[0])));
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    if(!enabled){
        UT_LOG_INFO("Calling dsEnableVideoPort(Handle:[%ld],Enable[%s]) ", gHandle,mapToString(enabled,boolMappingTable,sizeof(boolMappingTable)/sizeof(boolMappingTable[0])));
        status = dsEnableVideoPort(gHandle, true);
        UT_LOG_INFO("Result dsEnableVideoPort() dsError_t=[%s]", mapToString(status,dsErrorMappingTable,sizeof(dsErrorMappingTable)/sizeof(dsErrorMappingTable[0])));
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }
    UT_LOG_INFO("Calling dsIsDisplayConnected(Handle:[%ld]) ", gHandle);
    status = dsIsDisplayConnected(gHandle, &connected);
    UT_LOG_INFO("Result dsIsDisplayConnected(connected[%s]) dsError_t=[%s]",mapToString(enabled,boolMappingTable,sizeof(boolMappingTable)/sizeof(boolMappingTable[0])), mapToString(status,dsErrorMappingTable,sizeof(dsErrorMappingTable)/sizeof(dsErrorMappingTable[0])));
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    UT_LOG_INFO("Calling dsIsVideoPortActive(Handle:[%ld]) ", gHandle);
    status = dsIsVideoPortActive(gHandle, &active);
    UT_LOG_INFO("Result dsIsVideoPortActive(active:[%s])  dsError_t=[%s]",mapToString(enabled,boolMappingTable,sizeof(boolMappingTable)/sizeof(boolMappingTable[0])), mapToString(status,dsErrorMappingTable,sizeof(dsErrorMappingTable)/sizeof(dsErrorMappingTable[0])));
    UT_ASSERT_EQUAL(status, dsERR_NONE);

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

    UT_LOG_INFO("Calling dsGetCurrentOutputSettings(Handle:[%ld]) ", gHandle);
    status = dsGetCurrentOutputSettings(gHandle, &hdr_standard ,&matrix_coef, &color_space,\
                &color_depth, &quant_range);
    UT_LOG_INFO("Result dsGetCurrentOutputSettings(dsHDRStandard_t:[%s],dsDisplayMatrixCoefficients_t:[%s],",\
                                                   mapToString(hdr_standard,dsHDRStandardMappingTable,sizeof(dsHDRStandardMappingTable)/sizeof(dsHDRStandardMappingTable[0])),\
                                                   mapToString(matrix_coef,dsDisplayMatrixCoefficientsMappingTable,sizeof(dsDisplayMatrixCoefficientsMappingTable)/sizeof(dsDisplayMatrixCoefficientsMappingTable[0])));
    UT_LOG_INFO("dsDisplayColorSpace_t:[%s], color_depth:[%s],dsDisplayQuantizationRange_t:[%s],dsError_t=[%s])",
                                                   mapToString(color_space,dsDisplayColorSpaceMappingTable,sizeof(dsDisplayColorSpaceMappingTable)/sizeof(dsDisplayColorSpaceMappingTable[0])),\
                                                   mapToString(color_depth,dsDisplayColorDepthMappingTable,sizeof(dsDisplayColorDepthMappingTable)/sizeof(dsDisplayColorDepthMappingTable[0])),\
                                                   mapToString(quant_range,dsDisplayQuantizationRangeMappingTable,sizeof(dsDisplayQuantizationRangeMappingTable)/sizeof(dsDisplayQuantizationRangeMappingTable[0])),\
                                                   mapToString(status,dsErrorMappingTable,sizeof(dsErrorMappingTable)/sizeof(dsErrorMappingTable[0])));
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    UT_LOG_INFO("hdr_standard = %d matrix_coef = %d color_space = %d ",hdr_standard, matrix_coef, color_space);
    UT_LOG_INFO("color_depth = %d quant_range = %d ",color_depth, quant_range);


}

void dsVideoPort_GetSurroundMode()
{
    dsError_t status   = dsERR_NONE;
    bool surround   = false;
    int surround_mode = 0;

    dsVideoPort_getHandle();

    UT_LOG_INFO("Calling dsIsDisplaySurround(handle: [%ld]) ", gHandle);
    status = dsIsDisplaySurround(gHandle, &surround);
    UT_LOG_INFO("Result dsIsDisplaySurround(surround: [%s]) ,dsError_t=[%s]", mapToString(surround,boolMappingTable,sizeof(boolMappingTable)/sizeof(boolMappingTable[0])),\
                                                               mapToString(status,dsErrorMappingTable,sizeof(dsErrorMappingTable)/sizeof(dsErrorMappingTable[0])));
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    if(surround){
        UT_LOG_INFO("Calling dsGetSurroundMode(handle: [%ld]) ", gHandle);
        status = dsGetSurroundMode(gHandle, &surround_mode);
        UT_LOG_INFO("Result dsGetSurroundMode(dsSURROUNDMode_t:[%s]),dsError_t=[%s]", mapToString(surround_mode,dsSURROUNDModeMappingTable,sizeof(dsSURROUNDModeMappingTable)/sizeof(dsSURROUNDModeMappingTable[0])),\
                                                                          mapToString(status,dsErrorMappingTable,sizeof(dsErrorMappingTable)/sizeof(dsErrorMappingTable[0])));
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }
}

void dsVideoPort_GetResolution()
{
    dsError_t status   = dsERR_NONE;
    dsVideoPortResolution_t getResolution;

    dsVideoPort_getHandle();

    UT_LOG_INFO("Calling dsGetResolution(handle: [%ld]) ", gHandle);
    status = dsGetResolution(gHandle, &getResolution);
    UT_LOG_INFO("Result dsGetResolution(dsVideoPortResolution_t(name:[%s],dsVideoResolution_t:[%s],dsVideoAspectRatio_t:[%s] ", getResolution.name,mapToString(getResolution.pixelResolution,dsVideoResolutionMappingTable,sizeof(dsVideoResolutionMappingTable)/sizeof(dsVideoResolutionMappingTable[0])),\
                                                    mapToString(getResolution.aspectRatio,dsVideoAspectRatioMappingTable,sizeof(dsVideoAspectRatioMappingTable)/sizeof(dsVideoAspectRatioMappingTable[0])));
    UT_LOG_INFO(" dsVideoStereoScopicMode_t:[%s],dsVideoFrameRate_t:[%s],interlaced:[%s],dsError_t=[%s])",mapToString(getResolution.stereoScopicMode,dsVideoStereoScopicModeMappingTable,sizeof(dsVideoStereoScopicModeMappingTable)/sizeof(dsVideoAspectRatioMappingTable[0])),\
                                                    mapToString(getResolution.frameRate,dsVideoFrameRateMappingTable,sizeof(dsVideoFrameRateMappingTable)/sizeof(dsVideoFrameRateMappingTable[0])),\
                                                    mapToString(getResolution.interlaced,boolMappingTable,sizeof(boolMappingTable)/sizeof(boolMappingTable[0])),\
                                                    mapToString(status,dsErrorMappingTable,sizeof(dsErrorMappingTable)/sizeof(dsErrorMappingTable[0])));
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    UT_LOG_INFO(" GetResolution");
    UT_LOG_INFO("getResolution.pixelResolution= %d ",getResolution.pixelResolution);
    UT_LOG_INFO("getResolution.aspectRatio= %d ",getResolution.aspectRatio);
    UT_LOG_INFO("getResolution.stereoScopicMode= %d ",getResolution.stereoScopicMode);
    UT_LOG_INFO("getResolution.frameRate= %d ",getResolution.frameRate);
    UT_LOG_INFO("getResolution.interlaced= %d ",getResolution.interlaced);
}

#if 0
void dsVideoPort_SetResolution()
{
    dsError_t status   = dsERR_NONE;

    dsVideoPort_getHandle();

    UT_LOG_INFO("Invoking dsSetResolution() ");
    dsVideoPortResolution_t *pSetResolution = &gDSVideoPortConfiguration[port].supportedResolutions[i];
    status = dsSetResolution(gHandle, pSetResolution);
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    UT_LOG_INFO("Comparing setResolution and getResolution");
    UT_LOG_INFO("SetResolution.pixelResolution= %d ",pSetResolution->pixelResolution);
    UT_LOG_INFO("SetResolution.aspectRatio= %d ",pSetResolution->aspectRatio);
    UT_LOG_INFO("SetResolution.stereoScopicMode= %d ",pSetResolution->stereoScopicMode);
    UT_LOG_INFO("SetResolution.frameRate= %d ",pSetResolution->frameRate);
    UT_LOG_INFO("SSetResolution.interlaced= %d ",pSetResolution->interlaced);
}
#endif

void dsVideoPort_GetVideoEOTF()
{
    dsError_t status   = dsERR_NONE;
    dsHDRStandard_t eotf;

    dsVideoPort_getHandle();
    UT_LOG_INFO("Calling dsGetVideoEOTF(handle: [%ld]) ", gHandle);
    status = dsGetVideoEOTF(gHandle, &eotf);
    UT_LOG_INFO("Result dsGetVideoEOTF(dsHDRStandard_t:[%s]) ,dsError_t=[%s]", mapToString(eotf,dsHDRStandardMappingTable,sizeof(dsHDRStandardMappingTable)/sizeof(dsHDRStandardMappingTable[0])),\
                                                        mapToString(status,dsErrorMappingTable,sizeof(dsErrorMappingTable)/sizeof(dsErrorMappingTable[0])) );
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    UT_LOG_INFO("current HDR format %d",eotf);

}

void dsVideoPort_IsOutputHDR()
{
    dsError_t status   = dsERR_NONE;
    bool hdr = false;

    dsVideoPort_getHandle();
    UT_LOG_INFO("Calling dsIsOutputHDR(handle: [%ld]) ", gHandle);
    status = dsIsOutputHDR(gHandle, &hdr);
    UT_LOG_INFO("Result dsIsOutputHDR(hdr: [%s]) ,dsError_t=[%s] ", mapToString(hdr,boolMappingTable,sizeof(boolMappingTable)/sizeof(boolMappingTable[0])),\
                                        mapToString(status,dsErrorMappingTable,sizeof(dsErrorMappingTable)/sizeof(dsErrorMappingTable[0])));
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    UT_LOG_INFO("Is OUTPUT is HDR %d",hdr);
}

void dsVideoPort_SetForceHDRMode()
{
    dsError_t status   = dsERR_NONE;
    int32_t choice,i=0;

    dsVideoPort_getHandle();

    UT_LOG_INFO("\t Supported HDR modes ");
    UT_LOG_INFO("------------------------------------------\n");
    for(i=0;i<=dsHDRSTANDARD_Invalid;)
    {
        UT_LOG_INFO("\t%d.  %s\n",i,mapToString(i,dsHDRStandardMappingTable,sizeof(dsHDRStandardMappingTable)/sizeof(dsHDRStandardMappingTable[0])));
        i=(1 << i);
    }
    #if 0
    UT_LOG_INFO("\t1.  %-20s\n","HDR NONE");
    UT_LOG_INFO("\t2.  %-20s\n","HDR10");
    UT_LOG_INFO("\t3.  %-20s\n","HLG");
    UT_LOG_INFO("\t4.  %-20s\n","DolbyVision");
    UT_LOG_INFO("\t5.  %-20s\n","TechnicolorPrime");
    UT_LOG_INFO("\t6.  %-20s\n","HDR10PLUS");
    UT_LOG_INFO("\t6.  %-20s\n","SDR");
    #endif
    UT_LOG_INFO("\nEnter your choice: ");
    scanf("%d", &choice);

    UT_LOG_INFO("Calling dsSetForceHDRMode(handle: [%ld] dsHDRStandard_t:[%s]) ", gHandle,mapToString(choice,dsHDRStandardMappingTable,sizeof(dsHDRStandardMappingTable)/sizeof(dsHDRStandardMappingTable[0])));
    status = dsSetForceHDRMode(gHandle, (dsHDRStandard_t)choice);
    UT_LOG_INFO("Result dsSetForceHDRMode() ,dsError_t=[%s] ",mapToString(status,dsErrorMappingTable,sizeof(dsErrorMappingTable)/sizeof(dsErrorMappingTable[0])));
    UT_ASSERT_EQUAL(status, dsERR_NONE);

}

void dsVideoPort_ResetOutputToSDR()
{
    dsError_t status   = dsERR_NONE;
    bool hdr = false;

    dsVideoPort_getHandle();

    UT_LOG_INFO("Calling dsResetOutputToSDR(handle: [%ld]) ", gHandle);
    status = dsResetOutputToSDR();
    UT_LOG_INFO("Result dsResetOutputToSDR() ,dsError_t=[%s] ",mapToString(status,dsErrorMappingTable,sizeof(dsErrorMappingTable)/sizeof(dsErrorMappingTable[0])));
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    UT_LOG_INFO("Calling dsIsOutputHDR(handle: [%ld]) ", gHandle);
    status = dsIsOutputHDR(gHandle, &hdr);
    UT_LOG_INFO("Result dsIsOutputHDR(hdr: [%s]) ,dsError_t=[%s] ", mapToString(hdr,boolMappingTable,sizeof(boolMappingTable)/sizeof(boolMappingTable[0])),\
                                        mapToString(status,dsErrorMappingTable,sizeof(dsErrorMappingTable)/sizeof(dsErrorMappingTable[0])));
    UT_LOG_INFO("Is OUTPUT is HDR %d",hdr);
    if(hdr == true){
        UT_LOG_ERROR("OUT is HDR");
    }

}

void dsVideoPort_GetHDCPStatus()
{
    dsError_t status   = dsERR_NONE;
    dsHdcpStatus_t hdcpStatus;

    dsVideoPort_getHandle();
    UT_LOG_INFO("Calling dsGetHDCPStatus(handle: [%ld]) ", gHandle);
    status = dsGetHDCPStatus(gHandle, &(hdcpStatus));
    UT_LOG_INFO("Result dsGetHDCPStatus(dsHdcpStatus_t:[%s]) ,dsError_t=[%s] ", mapToString(hdcpStatus,dsHdcpStatusMappingTable,sizeof(dsHdcpStatusMappingTable)/sizeof(dsHdcpStatusMappingTable[0])),\
                                        mapToString(status,dsErrorMappingTable,sizeof(dsErrorMappingTable)/sizeof(dsErrorMappingTable[0])));
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    UT_LOG_INFO("HDCP Status %d",hdcpStatus);

}

void dsVideoPort_GetHDCPCurrentProtocol()
{
    dsError_t status   = dsERR_NONE;
    dsHdcpProtocolVersion_t currentProtocol;

    dsVideoPort_getHandle();
    UT_LOG_INFO("Calling dsGetHDCPCurrentProtocol(handle: [%ld]) ", gHandle);
    status = dsGetHDCPCurrentProtocol(gHandle, &currentProtocol);
    UT_LOG_INFO("Result dsGetHDCPCurrentProtocol(dsHdcpProtocolVersion_t:[%s]) ,dsError_t=[%s] ", mapToString(currentProtocol,dsHdcpProtocolVersionMappingTable,sizeof(dsHdcpProtocolVersionMappingTable)/sizeof(dsHdcpProtocolVersionMappingTable[0])),\
                                        mapToString(status,dsErrorMappingTable,sizeof(dsErrorMappingTable)/sizeof(dsErrorMappingTable[0])));
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    UT_LOG_INFO("HDCP Current Protocol Version: %d", currentProtocol);

}

void dsVideoPort_GetHDCPReceiverProtocol()
{
    dsError_t status   = dsERR_NONE;
    dsHdcpProtocolVersion_t protocolVersion;

    dsVideoPort_getHandle();
    UT_LOG_INFO("Calling dsGetHDCPCurrentProtocol(handle: [%ld]) ", gHandle);
    status = dsGetHDCPReceiverProtocol(gHandle, &(protocolVersion));
    UT_LOG_INFO("Result dsGetHDCPReceiverProtocol(dsHdcpProtocolVersion_t:[%s]) ,dsError_t=[%s] ", mapToString(protocolVersion,dsHdcpProtocolVersionMappingTable,sizeof(dsHdcpProtocolVersionMappingTable)/sizeof(dsHdcpProtocolVersionMappingTable[0])),\
                                        mapToString(status,dsErrorMappingTable,sizeof(dsErrorMappingTable)/sizeof(dsErrorMappingTable[0])));
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    UT_LOG_INFO("HDCP Receiver Protocol Version: %d", protocolVersion);

}

void dsVideoPort_GetIgnoreEDIDStatus()
{
    dsError_t status   = dsERR_NONE;
    bool ignoreEDIDStatus;

    dsVideoPort_getHandle();
    UT_LOG_INFO("Calling dsGetIgnoreEDIDStatus(handle: [%ld]) ", gHandle);
    status = dsGetIgnoreEDIDStatus(gHandle, &ignoreEDIDStatus);
    UT_LOG_INFO("Result dsGetIgnoreEDIDStatus(status:[%s]) ,dsError_t=[%s] ", mapToString(ignoreEDIDStatus,boolMappingTable,sizeof(boolMappingTable)/sizeof(boolMappingTable[0])),\
                                        mapToString(status,dsErrorMappingTable,sizeof(dsErrorMappingTable)/sizeof(dsErrorMappingTable[0])));
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    UT_LOG_INFO("Ignore EDID Status: %d", ignoreEDIDStatus);

}

void dsVideoPort_SetHdmiPreference()
{
    dsError_t status   = dsERR_NONE;
    int32_t choice,i;
    dsHdcpProtocolVersion_t hdcpCurrentProtocol;

    dsVideoPort_getHandle();
    UT_LOG_INFO("\t Supported HDCP Versions ");
    UT_LOG_INFO("------------------------------------------\n");
    for(i=0;i<dsHDCP_VERSION_MAX;i++)
    {
        UT_LOG_INFO("\t%d.  %s\n",i,mapToString(i,dsHdcpProtocolVersionMappingTable,sizeof(dsHdcpProtocolVersionMappingTable)/sizeof(dsHdcpProtocolVersionMappingTable[0])));
    }
    //UT_LOG_INFO("\t1.  %-20s\n","dsHDCP_VERSION_1X");
    //UT_LOG_INFO("\t2.  %-20s\n","dsHDCP_VERSION_2X");

    UT_LOG_INFO("Select the Hdmi Preference to set: ");
    scanf("%d", &choice);

    hdcpCurrentProtocol = (dsHdcpProtocolVersion_t)choice;
    UT_LOG_INFO("Calling dsSetHdmiPreference(handle: [%ld]dsHdcpProtocolVersion_t:[%s]) ", gHandle,mapToString(hdcpCurrentProtocol,dsHdcpProtocolVersionMappingTable,sizeof(dsHdcpProtocolVersionMappingTable)/sizeof(dsHdcpProtocolVersionMappingTable[0])));
    status = dsSetHdmiPreference(gHandle, &hdcpCurrentProtocol);
    UT_LOG_INFO("Result dsSetHdmiPreference(),dsError_t=[%s] ", mapToString(status,dsErrorMappingTable,sizeof(dsErrorMappingTable)/sizeof(dsErrorMappingTable[0])));
    UT_ASSERT_EQUAL(status, dsERR_NONE);

}

void dsVideoPort_GetHdmiPreference()
{
    dsError_t status   = dsERR_NONE;
    dsHdcpProtocolVersion_t  hdcpCurrentProtocol;

    dsVideoPort_getHandle();
    UT_LOG_INFO("Calling dsGetHdmiPreference(handle: [%ld]) ", gHandle);
    status = dsGetHdmiPreference(gHandle, &hdcpCurrentProtocol);
    UT_LOG_INFO("Result dsGetHdmiPreference(dsHdcpProtocolVersion_t:[%s],dsError_t=[%s]) ", mapToString(hdcpCurrentProtocol,dsHdcpProtocolVersionMappingTable,sizeof(dsHdcpProtocolVersionMappingTable)/sizeof(dsHdcpProtocolVersionMappingTable[0])),\
                                                        mapToString(status,dsErrorMappingTable,sizeof(dsErrorMappingTable)/sizeof(dsErrorMappingTable[0])));
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    UT_LOG_INFO("Get HDMI Preference: %d", hdcpCurrentProtocol);

}

void dsVideoPort_GetColorSpace()
{
    dsError_t status   = dsERR_NONE;
    dsDisplayColorSpace_t color_space;

    dsVideoPort_getHandle();
    UT_LOG_INFO("Calling dsGetColorSpace(handle: [%ld]) ", gHandle);
    status = dsGetColorSpace(gHandle, &color_space);
    UT_LOG_INFO("Result dsGetColorSpace(dsDisplayColorSpace_t:[%s], dsError_t=[%s]) ", mapToString(color_space,dsDisplayColorSpaceMappingTable,sizeof(dsDisplayColorSpaceMappingTable)/sizeof(dsDisplayColorSpaceMappingTable[0])),\
                                            mapToString(status,dsErrorMappingTable,sizeof(dsErrorMappingTable)/sizeof(dsErrorMappingTable[0])));
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    UT_LOG_INFO("Get Color Space: %d", color_space);

}

void dsVideoPort_GetColorDepth()
{
    dsError_t status   = dsERR_NONE;
    unsigned int colorDepth;

    dsVideoPort_getHandle();
    UT_LOG_INFO("Calling dsGetColorDepth(handle: [%ld]) ", gHandle);
    status = dsGetColorDepth(gHandle, &colorDepth);
    UT_LOG_INFO("Result dsGetColorDepth(dsDisplayColorDepth_t:[%s], dsError_t=[%s]) ", mapToString(colorDepth,dsDisplayColorDepthMappingTable,sizeof(dsDisplayColorDepthMappingTable)/sizeof(dsDisplayColorDepthMappingTable[0])),\
                                            mapToString(status,dsErrorMappingTable,sizeof(dsErrorMappingTable)/sizeof(dsErrorMappingTable[0])));
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    UT_LOG_INFO("Get Color Depth: %d", colorDepth);

}

void dsVideoPort_SetPreferredColorDepth()
{
    dsError_t status   = dsERR_NONE;
    int32_t choice,i;
    //dsDisplayColorDepth_t colorDepth;

    dsVideoPort_getHandle();
    UT_LOG_INFO("\t Supported display Color depth to set ");
    UT_LOG_INFO("------------------------------------------\n");
    for(i=0;i<=dsDISPLAY_COLORDEPTH_AUTO;)
    {
        UT_LOG_INFO("\t%d.  %s\n",i,mapToString(i,dsDisplayColorDepthMappingTable,sizeof(dsDisplayColorDepthMappingTable)/sizeof(dsDisplayColorDepthMappingTable[0])));
        i=(1 << i);
    }
#if 0
    UT_LOG_INFO("\t1.  %-20s\n","8 BIT");
    UT_LOG_INFO("\t2.  %-20s\n","10 BIT");
    UT_LOG_INFO("\t3.  %-20s\n","12 BIT");
    UT_LOG_INFO("\t4.  %-20s\n","AUTO");
#endif
    UT_LOG_INFO("\nEnter your choice: ");
    scanf("%d", &choice);

    UT_LOG_INFO("Calling dsSetPreferredColorDepth(handle:[%ld],dsDisplayColorDepth_t:[%s]) ", gHandle,mapToString((dsDisplayColorDepth_t)choice,dsDisplayColorDepthMappingTable,sizeof(dsDisplayColorDepthMappingTable)/sizeof(dsDisplayColorDepthMappingTable[0])));
    //colorDepth = (dsDisplayColorDepth_t)choice;
    status = dsSetPreferredColorDepth(gHandle, (dsDisplayColorDepth_t)choice);
    UT_LOG_INFO("Result dsGetColorDepth(),dsError_t=[%s] ", mapToString(status,dsErrorMappingTable,sizeof(dsErrorMappingTable)/sizeof(dsErrorMappingTable[0])));
    UT_ASSERT_EQUAL(status, dsERR_NONE);


}

void dsVideoPort_GetPreferredColorDepth()
{
    dsError_t status   = dsERR_NONE;
    unsigned int colorDepth;

    dsVideoPort_getHandle();
    UT_LOG_INFO("Calling dsGetPreferredColorDepth(handle:[%ld]) ", gHandle);
    status = dsGetPreferredColorDepth(gHandle, &colorDepth);
    UT_LOG_INFO("Result dsGetPreferredColorDepth(),dsError_t=[%s] ", mapToString(colorDepth,dsDisplayColorDepthMappingTable,sizeof(dsDisplayColorDepthMappingTable)/sizeof(dsDisplayColorDepthMappingTable[0])),\
                                                    mapToString(status,dsErrorMappingTable,sizeof(dsErrorMappingTable)/sizeof(dsErrorMappingTable[0])));
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    UT_LOG_INFO("Get Preferred Color Depth: %d", colorDepth);

}

void dsVideoPort_SetBackgroundColor()
{
    dsError_t status   = dsERR_NONE;
    //dsVideoBackgroundColor_t color;
    int32_t choice=0,i;

    dsVideoPort_getHandle();
    UT_LOG_INFO("\t Select Background Color to set ");
    UT_LOG_INFO("------------------------------------------\n");
    for(i=0;i<=dsVIDEO_BGCOLOR_MAX ;i++)
    {
        UT_LOG_INFO("\t%d.  %s\n",i,mapToString(i,dsVideoBackgroundColorMappingTable,sizeof(dsVideoBackgroundColorMappingTable)/sizeof(dsVideoBackgroundColorMappingTable[0])));
    }
#if 0
    UT_LOG_INFO("\t1.  %-20s\n","BLUE");
    UT_LOG_INFO("\t2.  %-20s\n","BLACK");
    UT_LOG_INFO("\t3.  %-20s\n","NONE");
#endif
    UT_LOG_INFO("\nEnter your choice: ");
    scanf("%d", &choice);

    UT_LOG_INFO("Invoking dsSetForceHDRMode() with HDR Mode:%d ",choice);
    //color = (dsVideoBackgroundColor_t)choice;

    UT_LOG_INFO("Calling dsSetBackgroundColor(handle:[%ld],dsVideoBackgroundColor_t:[%s]) ", gHandle,mapToString((dsVideoBackgroundColor_t)choice,dsVideoBackgroundColorMappingTable,sizeof(dsVideoBackgroundColorMappingTable)/sizeof(dsVideoBackgroundColorMappingTable[0])));
    status = dsSetBackgroundColor(gHandle, (dsVideoBackgroundColor_t)choice);
    UT_LOG_INFO("Result dsSetBackgroundColor(),dsError_t=[%s] ", mapToString(status,dsErrorMappingTable,sizeof(dsErrorMappingTable)/sizeof(dsErrorMappingTable[0])));
    UT_ASSERT_EQUAL(status, dsERR_NONE);

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
    if(gSourceType == 1) {
        pSuite = UT_add_suite("[L3 dsVideoPort - Source]", NULL, NULL);
    }
    else {
        pSuite = UT_add_suite("[L3 dsVideoPort - Sink]", NULL, NULL);
    }
    if (pSuite == NULL) {
        return -1;
    }
    // Create the test suite
    UT_add_test( pSuite, "VideoPort Init", dsVideoPort_Init);
    UT_add_test( pSuite, "VideoPort Term", dsVideoPort_Term);
    UT_add_test( pSuite, "Enable VideoPort", dsVideoPort_Enable);
    UT_add_test( pSuite, "Get CurrentOutputSettings", dsVideoPort_CurrentOutputSettings);
    UT_add_test( pSuite, "Get SurroundMode",dsVideoPort_GetSurroundMode);
    UT_add_test( pSuite, "Get Resolution",dsVideoPort_GetResolution);
    //UT_add_test( pSuite, "SetResolution",dsVideoPort_SetResolution);
    UT_add_test( pSuite, "Get VideoEOTF",dsVideoPort_GetVideoEOTF);
    UT_add_test( pSuite, "IsOutputHDR",dsVideoPort_IsOutputHDR);
    UT_add_test( pSuite, "ResetOutputToSDR",dsVideoPort_ResetOutputToSDR);
    UT_add_test( pSuite, "Get HDCPStatus",dsVideoPort_GetHDCPStatus);
    UT_add_test( pSuite, "Get HDCPCurrentProtocol",dsVideoPort_GetHDCPCurrentProtocol);
    UT_add_test( pSuite, "Set HdmiPreference",dsVideoPort_SetHdmiPreference);
    UT_add_test( pSuite, "Get HdmiPreference",dsVideoPort_GetHdmiPreference);
    UT_add_test( pSuite, "Get ColorSpace",dsVideoPort_GetColorSpace);
    UT_add_test( pSuite, "Get ColorDepth",dsVideoPort_GetColorDepth);
    if(gSourceType == 1) {
        // add the test suite for source type
        UT_add_test( pSuite, "Set ForceHDRMode",dsVideoPort_SetForceHDRMode);
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