#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "dsHdmiIn.h"


dsError_t dsHdmiInInit(void)
{
  /*TODO: Implement Me!*/
  return (dsError_t)0;
}

dsError_t dsHdmiInTerm(void)
{
  /*TODO: Implement Me!*/
  return (dsError_t)0;
}

dsError_t dsHdmiInGetNumberOfInputs(uint8_t* pNumberOfInputs)
{
  /*TODO: Implement Me!*/
  (void)pNumberOfInputs;
  return (dsError_t)0;
}

dsError_t dsHdmiInGetStatus(dsHdmiInStatus_t* pStatus)
{
  /*TODO: Implement Me!*/
  (void)pStatus;
  return (dsError_t)0;
}

dsError_t dsHdmiInSelectPort(dsHdmiInPort_t Port)
{
  /*TODO: Implement Me!*/
  (void)Port;
  return (dsError_t)0;
}

dsError_t dsHdmiInScaleVideo(int32_t x, int32_t y, int32_t width, int32_t height)
{
  /*TODO: Implement Me!*/
  (void)x;
  (void)y;
  (void)width;
  (void)height;
  return (dsError_t)0;
}

dsError_t dsHdmiInSelectZoomMode(dsVideoZoom_t requestedZoomMode)
{
  /*TODO: Implement Me!*/
  (void)requestedZoomMode;
  return (dsError_t)0;
}

dsError_t dsHdmiInPauseAudio(void)
{
  /*TODO: Implement Me!*/
  return (dsError_t)0;
}

dsError_t dsHdmiInResumeAudio(void)
{
  /*TODO: Implement Me!*/
  return (dsError_t)0;
}

dsError_t dsHdmiInGetCurrentVideoMode(dsVideoPortResolution_t* resolution)
{
  /*TODO: Implement Me!*/
  (void)resolution;
  return (dsError_t)0;
}

dsError_t dsHdmiInRegisterConnectCB(dsHdmiInConnectCB_t CBFunc)
{
  /*TODO: Implement Me!*/
  (void)CBFunc;
  return (dsError_t)0;
}

dsError_t dsHdmiInRegisterSignalChangeCB(dsHdmiInSignalChangeCB_t CBFunc)
{
  /*TODO: Implement Me!*/
  (void)CBFunc;
  return (dsError_t)0;
}

dsError_t dsHdmiInRegisterStatusChangeCB(dsHdmiInStatusChangeCB_t CBFunc)
{
  /*TODO: Implement Me!*/
  (void)CBFunc;
  return (dsError_t)0;
}

dsError_t dsHdmiInRegisterVideoModeUpdateCB(dsHdmiInVideoModeUpdateCB_t CBFunc)
{
  /*TODO: Implement Me!*/
  (void)CBFunc;
  return (dsError_t)0;
}

dsError_t dsHdmiInRegisterAllmChangeCB(dsHdmiInAllmChangeCB_t CBFunc)
{
  /*TODO: Implement Me!*/
  (void)CBFunc;
  return (dsError_t)0;
}

bool dsIsHdmiARCPort(int iPort)
{
  /*TODO: Implement Me!*/
  (void)iPort;
  return (bool)0;
}

dsError_t dsGetEDIDBytesInfo(int iHdmiPort, unsigned char** edid, int* length)
{
  /*TODO: Implement Me!*/
  (void)iHdmiPort;
  (void)edid;
  (void)length;
  return (dsError_t)0;
}

dsError_t dsGetHDMISPDInfo(int iHdmiPort, unsigned char** data)
{
  /*TODO: Implement Me!*/
  (void)iHdmiPort;
  (void)data;
  return (dsError_t)0;
}

dsError_t dsSetEdidVersion(int iHdmiPort, int iEdidVersion)
{
  /*TODO: Implement Me!*/
  (void)iHdmiPort;
  (void)iEdidVersion;
  return (dsError_t)0;
}

dsError_t dsGetEdidVersion(int iHdmiPort, int* iEdidVersion)
{
  /*TODO: Implement Me!*/
  (void)iHdmiPort;
  (void)iEdidVersion;
  return (dsError_t)0;
}

dsError_t dsGetAllmStatus(int iHdmiPort, bool* allmStatus)
{
  /*TODO: Implement Me!*/
  (void)iHdmiPort;
  (void)allmStatus;
  return (dsError_t)0;
}

dsError_t dsGetSupportedGameFeaturesList(dsSupportedGameFeatureList_t* features)
{
  /*TODO: Implement Me!*/
  (void)features;
  return (dsError_t)0;
}

