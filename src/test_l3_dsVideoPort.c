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
#include <ut.h>
#include <ut_log.h>
#include <ut_kvp_profile.h>
#include <ut_kvp.h>

#include "test_parse_configuration.h"
#include "dsVideoPort.h"


intptr_t gHandle = 0;

/*callback*/
void VideoFormatCallback(dsHDRStandard_t videoFormat)
{
    UT_LOG("videoFormat From Callback %d ",videoFormat);

}
void HdcpStatusCallback(intptr_t handle, dsHdcpStatus_t status)
{
    UT_LOG("HDCP Status From Callback %d ",status);
}

void dsVideoPort_Init()
{
    dsError_t status   = dsERR_NONE;

    status = dsVideoPortInit();
    UT_LOG_DEBUG("Return status: %d", status);
    UT_ASSERT_EQUAL_FATAL(status, dsERR_NONE);
    UT_LOG_DEBUG("Register dsVideoFormatUpdateRegisterCB");
    status = dsVideoFormatUpdateRegisterCB(VideoFormatCallback);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

}

void dsVideoPort_Term()
{
    dsError_t status   = dsERR_NONE;

    status = dsVideoPortTerm();
    UT_LOG_DEBUG("Return status: %d", status);
    UT_ASSERT_EQUAL_FATAL(status, dsERR_NONE);
}

static void dsVideoPort_getHandle()
{
    dsError_t status   = dsERR_NONE;
    int32_t choice,port;

    UT_LOG(" \t  Select Video Port");
    UT_LOG("------------------------------------------");
    UT_LOG("\t#  %-20s%s\n\n","Video Port", "Index");
    for (port = 0; port < gDSvideoPort_NumberOfPorts; port++) {
        UT_LOG("\t%d.  %-20s%-2d\n", port+1, gDSVideoPortConfiguration[port].port_name, gDSVideoPortConfiguration[port].index);
    }
    UT_LOG("------------------------------------------\n");
    UT_LOG("\n Enter your choice: ");
    scanf("%d", &choice);
    port = choice - 1;
    UT_LOG("Port %d choice %d ",port,choice);
    if(choice < 1 || choice > gDSvideoPort_NumberOfPorts) {
        UT_LOG_ERROR("Invalid Port choice\n");
        return;
    }
    status = dsGetVideoPort(gDSVideoPortConfiguration[port].typeid, gDSVideoPortConfiguration[port].index, &gHandle);
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

    UT_LOG_DEBUG("Register dsRegisterHdcpStatusCallback");
    status = dsRegisterHdcpStatusCallback(gHandle, HdcpStatusCallback);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    UT_LOG_DEBUG("Invoking dsEnableVideoPort() with handle: %ld ", gHandle);
    status = dsIsVideoPortEnabled(gHandle, &enabled);
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    if(!enabled){
        status = dsEnableVideoPort(gHandle, true);
        UT_LOG_DEBUG("Return status: %d", status);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
    }
    status = dsIsDisplayConnected(gHandle, &connected);
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    UT_LOG_DEBUG("Return status: %d, Connected: %d", status, connected);
    status = dsIsVideoPortActive(gHandle, &active);
    UT_LOG_DEBUG("Return status: %d, Active: %d", status, active);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

}

void dsVideoPort_CurrentOutputSettings()
{
    dsError_t status   = dsERR_NONE;
    dsHDRStandard_t hdrstandard;
    dsDisplayMatrixCoefficients_t matrixcoef;
    dsDisplayColorSpace_t colorspace;
    unsigned int colordepth;
    dsDisplayQuantizationRange_t quant_range;

    dsVideoPort_getHandle();

    status = dsGetCurrentOutputSettings(gHandle, &hdrstandard ,&matrixcoef, &colorspace,\
                &colordepth, &quant_range);
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    UT_LOG_DEBUG("hdrstandard = %d matrixcoef = %d colorspace = %d ",hdrstandard, matrixcoef, colorspace);
    UT_LOG_DEBUG("colordepth = %d quant_range = %d ",colordepth, quant_range);


}

void dsVideoPort_GetSurroundMode()
{
    dsError_t status   = dsERR_NONE;
    bool surround   = false;
    int surround_mode = 0;

    dsVideoPort_getHandle();

    UT_LOG_DEBUG("Invoking dsIsDisplaySurround() with handle %ld", gHandle);
    status = dsIsDisplaySurround(gHandle, &surround);
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    UT_LOG_DEBUG("dsIsDisplaySurround() returned %d and surround %d", status, surround);
    if(surround){
        UT_LOG_DEBUG("Invoking dsGetSurroundMode() with valid handle");
        status = dsGetSurroundMode(gHandle, &surround_mode);
        UT_ASSERT_EQUAL(status, dsERR_NONE);
        UT_LOG_DEBUG("Surround mode: %d and return status: %d", surround_mode, status);
    }
}

void dsVideoPort_GetResolution()
{
    dsError_t status   = dsERR_NONE;
    dsVideoPortResolution_t getResolution;

    dsVideoPort_getHandle();

    UT_LOG_DEBUG("Invoking dsGetResolution() with handle and getResolution");
    status = dsGetResolution(gHandle, &getResolution);
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    UT_LOG_DEBUG(" GetResolution");
    UT_LOG_DEBUG("getResolution.pixelResolution= %d ",getResolution.pixelResolution);
    UT_LOG_DEBUG("getResolution.aspectRatio= %d ",getResolution.aspectRatio);
    UT_LOG_DEBUG("getResolution.stereoScopicMode= %d ",getResolution.stereoScopicMode);
    UT_LOG_DEBUG("getResolution.frameRate= %d ",getResolution.frameRate);
    UT_LOG_DEBUG("getResolution.interlaced= %d ",getResolution.interlaced);
}

#if 0
void dsVideoPort_SetResolution()
{
    dsError_t status   = dsERR_NONE;

    dsVideoPort_getHandle();

    UT_LOG_DEBUG("Invoking dsSetResolution() ");
    dsVideoPortResolution_t *pSetResolution = &gDSVideoPortConfiguration[port].supportedResolutions[i];
    status = dsSetResolution(gHandle, pSetResolution);
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    UT_LOG_DEBUG("Comparing setResolution and getResolution");
    UT_LOG_DEBUG("SetResolution.pixelResolution= %d ",pSetResolution->pixelResolution);
    UT_LOG_DEBUG("SetResolution.aspectRatio= %d ",pSetResolution->aspectRatio);
    UT_LOG_DEBUG("SetResolution.stereoScopicMode= %d ",pSetResolution->stereoScopicMode);
    UT_LOG_DEBUG("SetResolution.frameRate= %d ",pSetResolution->frameRate);
    UT_LOG_DEBUG("SSetResolution.interlaced= %d ",pSetResolution->interlaced);
}
#endif

void dsVideoPort_GetVideoEOTF()
{
    dsError_t status   = dsERR_NONE;
    dsHDRStandard_t eotf;

    dsVideoPort_getHandle();
    status = dsGetVideoEOTF(gHandle, &eotf);
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    UT_LOG("current HDR format %d",eotf);

}

void dsVideoPort_IsOutputHDR()
{
    dsError_t status   = dsERR_NONE;
    bool hdr = false;

    dsVideoPort_getHandle();
    status = dsIsOutputHDR(gHandle, &hdr);
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    UT_LOG("Is OUTPUT is HDR %d",hdr);
}

void dsVideoPort_SetForceHDRMode()
{
    dsError_t status   = dsERR_NONE;
    int32_t choice;

    dsVideoPort_getHandle();

    UT_LOG("\t Select the HDR mode to set ");
    UT_LOG("------------------------------------------\n");
    UT_LOG("\t1.  %-20s\n","HDR NONE");
    UT_LOG("\t2.  %-20s\n","HDR10");
    UT_LOG("\t3.  %-20s\n","HLG");
    UT_LOG("\t4.  %-20s\n","DolbyVision");
    UT_LOG("\t5.  %-20s\n","TechnicolorPrime");
    UT_LOG("\t6.  %-20s\n","HDR10PLUS");
    UT_LOG("\t6.  %-20s\n","SDR");
    UT_LOG("\nEnter your choice: ");
    scanf("%d", &choice);

    UT_LOG_DEBUG("Invoking dsSetForceHDRMode() with HDR Mode:%d ",choice);
    status = dsSetForceHDRMode(gHandle, (dsHDRStandard_t)choice);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

}

void dsVideoPort_ResetOutputToSDR()
{
    dsError_t status   = dsERR_NONE;
    bool hdr = false;

    dsVideoPort_getHandle();

    UT_LOG_DEBUG("Invoking dsResetOutputToSDR() ");
    status = dsResetOutputToSDR();
    UT_ASSERT_EQUAL(status, dsERR_NONE);

    UT_LOG("Verify the OUTPUT is SDR %d",hdr);
    status = dsIsOutputHDR(gHandle, &hdr);
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    UT_LOG("Is OUTPUT is HDR %d",hdr);
    if(hdr == true){
        UT_LOG_ERROR("OUT is HDR");
    }

}

void dsVideoPort_GetHDCPStatus()
{
    dsError_t status   = dsERR_NONE;
    dsHdcpStatus_t hdcpStatus;

    dsVideoPort_getHandle();
    status = dsGetHDCPStatus(gHandle, &(hdcpStatus));
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    UT_LOG("HDCP Status %d",hdcpStatus);

}

void dsVideoPort_GetHDCPCurrentProtocol()
{
    dsError_t status   = dsERR_NONE;
    dsHdcpProtocolVersion_t currentProtocol;

    dsVideoPort_getHandle();
    status = dsGetHDCPCurrentProtocol(gHandle, &currentProtocol);
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    UT_LOG("HDCP Current Protocol Version: %d", currentProtocol);

}

void dsVideoPort_GetHDCPReceiverProtocol()
{
    dsError_t status   = dsERR_NONE;
    dsHdcpProtocolVersion_t protocolVersion;

    dsVideoPort_getHandle();
    status = dsGetHDCPReceiverProtocol(gHandle, &(protocolVersion));
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    UT_LOG("HDCP Receiver Protocol Version: %d", protocolVersion);

}

void dsVideoPort_GetIgnoreEDIDStatus()
{
    dsError_t status   = dsERR_NONE;
    bool ignoreEDIDStatus;

    dsVideoPort_getHandle();
    status = dsGetIgnoreEDIDStatus(gHandle, &ignoreEDIDStatus);
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    UT_LOG("Ignore EDID Status: %d", ignoreEDIDStatus);

}

void dsVideoPort_SetHdmiPreference()
{
    dsError_t status   = dsERR_NONE;
    int32_t choice;
    dsHdcpProtocolVersion_t hdcpCurrentProtocol;

    dsVideoPort_getHandle();
    UT_LOG("\t Select the Hdmi Preference to set ");
    UT_LOG("------------------------------------------\n");
    UT_LOG("\t1.  %-20s\n","dsHDCP_VERSION_1X");
    UT_LOG("\t2.  %-20s\n","dsHDCP_VERSION_2X");

    UT_LOG("\nEnter your choice: ");
    scanf("%d", &choice);

    UT_LOG_DEBUG("Invoking dsSetForceHDRMode() with HDR Mode:%d ",choice);
    hdcpCurrentProtocol = (dsHdcpProtocolVersion_t)choice;
    status = dsSetHdmiPreference(gHandle, &hdcpCurrentProtocol);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

}

void dsVideoPort_GetHdmiPreference()
{
    dsError_t status   = dsERR_NONE;
    dsHdcpProtocolVersion_t  hdcpCurrentProtocol;

    dsVideoPort_getHandle();
    status = dsGetHdmiPreference(gHandle, &hdcpCurrentProtocol);
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    UT_LOG("Get HDMI Preference: %d", hdcpCurrentProtocol);

}

void dsVideoPort_GetColorSpace()
{
    dsError_t status   = dsERR_NONE;
    dsDisplayColorSpace_t color_space;

    dsVideoPort_getHandle();
    status = dsGetColorSpace(gHandle, &color_space);
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    UT_LOG("Get Color Space: %d", color_space);

}

void dsVideoPort_GetColorDepth()
{
    dsError_t status   = dsERR_NONE;
    unsigned int colorDepth;

    dsVideoPort_getHandle();
    status = dsGetColorDepth(gHandle, &colorDepth);
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    UT_LOG("Get Color Depth: %d", colorDepth);

}

void dsVideoPort_SetPreferredColorDepth()
{
    dsError_t status   = dsERR_NONE;
    int32_t choice;
    //dsDisplayColorDepth_t colorDepth;

    dsVideoPort_getHandle();
    UT_LOG("\t Select display Color depth to set ");
    UT_LOG("------------------------------------------\n");
    UT_LOG("\t1.  %-20s\n","8 BIT");
    UT_LOG("\t2.  %-20s\n","10 BIT");
    UT_LOG("\t3.  %-20s\n","12 BIT");
    UT_LOG("\t4.  %-20s\n","AUTO");

    UT_LOG("\nEnter your choice: ");
    scanf("%d", &choice);

    UT_LOG_DEBUG("Invoking dsSetPreferredColorDepth() with Color depth :%d ",choice);
    //colorDepth = (dsDisplayColorDepth_t)choice;
    status = dsSetPreferredColorDepth(gHandle, (dsDisplayColorDepth_t)choice);
    UT_ASSERT_EQUAL(status, dsERR_NONE);

}

void dsVideoPort_GetPreferredColorDepth()
{
    dsError_t status   = dsERR_NONE;
    unsigned int colorDepth;

    dsVideoPort_getHandle();
    status = dsGetPreferredColorDepth(gHandle, &colorDepth);
    UT_ASSERT_EQUAL(status, dsERR_NONE);
    UT_LOG("Get Preferred Color Depth: %d", colorDepth);

}

void dsVideoPort_SetBackgroundColor()
{
    dsError_t status   = dsERR_NONE;
    dsVideoBackgroundColor_t color;
    int32_t choice;

    dsVideoPort_getHandle();
    UT_LOG("\t Select Background Color to set ");
    UT_LOG("------------------------------------------\n");
    UT_LOG("\t1.  %-20s\n","BLUE");
    UT_LOG("\t2.  %-20s\n","BLACK");
    UT_LOG("\t3.  %-20s\n","NONE");

    UT_LOG("\nEnter your choice: ");
    scanf("%d", &choice);

    UT_LOG_DEBUG("Invoking dsSetForceHDRMode() with HDR Mode:%d ",choice);
    color = (dsVideoBackgroundColor_t)choice;
    status = dsSetBackgroundColor(gHandle, color);
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