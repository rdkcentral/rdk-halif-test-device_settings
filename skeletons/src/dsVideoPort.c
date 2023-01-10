#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "dsVideoPort.h"


dsError_t dsVideoPortInit(void)
{
  /*TODO: Implement Me!*/
  return (dsError_t)0;
}

dsError_t dsGetVideoPort(dsVideoPortType_t type, int index, int* handle)
{
  /*TODO: Implement Me!*/
  (void)type;
  (void)index;
  (void)handle;
  return (dsError_t)0;
}

dsError_t dsIsVideoPortEnabled(int handle, bool* enabled)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)enabled;
  return (dsError_t)0;
}

dsError_t dsIsDisplayConnected(int handle, bool* connected)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)connected;
  return (dsError_t)0;
}

dsError_t dsIsDisplaySurround(int handle, bool* surround)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)surround;
  return (dsError_t)0;
}

dsError_t dsGetSurroundMode(int handle, int* surround)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)surround;
  return (dsError_t)0;
}

dsError_t dsIsVideoPortActive(int handle, bool* active)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)active;
  return (dsError_t)0;
}

dsError_t dsEnableDTCP(int handle, bool contentProtect)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)contentProtect;
  return (dsError_t)0;
}

dsError_t dsEnableHDCP(int handle, bool contentProtect, char* hdcpKey, size_t keySize)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)contentProtect;
  (void)hdcpKey;
  (void)keySize;
  return (dsError_t)0;
}

dsError_t dsIsDTCPEnabled(int handle, bool* pContentProtected)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)pContentProtected;
  return (dsError_t)0;
}

dsError_t dsIsHDCPEnabled(int handle, bool* pContentProtected)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)pContentProtected;
  return (dsError_t)0;
}

dsError_t dsEnableVideoPort(int handle, bool enabled)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)enabled;
  return (dsError_t)0;
}

dsError_t dsSetResolution(int handle, dsVideoPortResolution_t* resolution, bool persist)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)resolution;
  (void)persist;
  return (dsError_t)0;
}

dsError_t dsGetResolution(int handle, dsVideoPortResolution_t* resolution)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)resolution;
  return (dsError_t)0;
}

dsError_t dsSetActiveSource(int handle)
{
  /*TODO: Implement Me!*/
  (void)handle;
  return (dsError_t)0;
}

dsError_t dsVideoPortTerm(void)
{
  /*TODO: Implement Me!*/
  return (dsError_t)0;
}

dsError_t dsInitResolution(dsVideoPortResolution_t* cmock_arg1)
{
  /*TODO: Implement Me!*/
  (void)cmock_arg1;
  return (dsError_t)0;
}

dsError_t dsRegisterHdcpStatusCallback(int handle, dsHDCPStatusCallback_t cb)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)cb;
  return (dsError_t)0;
}

dsError_t dsGetHDCPStatus(int handle, dsHdcpStatus_t* status)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)status;
  return (dsError_t)0;
}

dsError_t dsGetHDCPProtocol(int handle, dsHdcpProtocolVersion_t* protocolVersion)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)protocolVersion;
  return (dsError_t)0;
}

dsError_t dsGetHDCPReceiverProtocol(int handle, dsHdcpProtocolVersion_t* protocolVersion)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)protocolVersion;
  return (dsError_t)0;
}

dsError_t dsGetHDCPCurrentProtocol(int handle, dsHdcpProtocolVersion_t* protocolVersion)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)protocolVersion;
  return (dsError_t)0;
}

dsError_t dsGetTVHDRCapabilities(int handle, int* capabilities)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)capabilities;
  return (dsError_t)0;
}

dsError_t dsSupportedTvResolutions(int handle, int* resolutions)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)resolutions;
  return (dsError_t)0;
}

dsError_t dsSetForceDisable4KSupport(int handle, bool disable)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)disable;
  return (dsError_t)0;
}

dsError_t dsGetForceDisable4KSupport(int handle, bool* disable)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)disable;
  return (dsError_t)0;
}

dsError_t dsSetScartParameter(int handle, const char* parameter_str, const char* value_str)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)parameter_str;
  (void)value_str;
  return (dsError_t)0;
}

dsError_t dsGetVideoEOTF(int handle, dsHDRStandard_t* video_eotf)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)video_eotf;
  return (dsError_t)0;
}

dsError_t dsGetMatrixCoefficients(int handle, dsDisplayMatrixCoefficients_t* matrix_coefficients)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)matrix_coefficients;
  return (dsError_t)0;
}

dsError_t dsGetColorDepth(int handle, unsigned int* color_depth)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)color_depth;
  return (dsError_t)0;
}

dsError_t dsGetColorSpace(int handle, dsDisplayColorSpace_t* color_space)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)color_space;
  return (dsError_t)0;
}

dsError_t dsGetQuantizationRange(int handle, dsDisplayQuantizationRange_t* quantization_range)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)quantization_range;
  return (dsError_t)0;
}

dsError_t dsGetCurrentOutputSettings(int handle, dsHDRStandard_t* video_eotf, dsDisplayMatrixCoefficients_t* matrix_coefficients, dsDisplayColorSpace_t* color_space, unsigned int* color_depth, dsDisplayQuantizationRange_t* quantization_range)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)video_eotf;
  (void)matrix_coefficients;
  (void)color_space;
  (void)color_depth;
  (void)quantization_range;
  return (dsError_t)0;
}

dsError_t dsIsOutputHDR(int handle, bool* hdr)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)hdr;
  return (dsError_t)0;
}

dsError_t dsResetOutputToSDR(void)
{
  /*TODO: Implement Me!*/
  return (dsError_t)0;
}

dsError_t dsSetHdmiPreference(int handle, dsHdcpProtocolVersion_t* hdcpCurrentProtocol)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)hdcpCurrentProtocol;
  return (dsError_t)0;
}

dsError_t dsGetHdmiPreference(int handle, dsHdcpProtocolVersion_t* hdcpCurrentProtocol)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)hdcpCurrentProtocol;
  return (dsError_t)0;
}

dsError_t dsGetIgnoreEDIDStatus(int handle, bool* status)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)status;
  return (dsError_t)0;
}

dsError_t dsSetBackgroundColor(int handle, dsVideoBackgroundColor_t color)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)color;
  return (dsError_t)0;
}

dsError_t dsSetForceHDRMode(int handle, dsHDRStandard_t mode)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)mode;
  return (dsError_t)0;
}

dsError_t dsColorDepthCapabilities(int handle, unsigned int* colorDepthCapability)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)colorDepthCapability;
  return (dsError_t)0;
}

dsError_t dsGetPreferredColorDepth(int handle, dsDisplayColorDepth_t* colorDepth, bool persist)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)colorDepth;
  (void)persist;
  return (dsError_t)0;
}

dsError_t dsSetPreferredColorDepth(int handle, dsDisplayColorDepth_t colorDepth, bool persist)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)colorDepth;
  (void)persist;
  return (dsError_t)0;
}

