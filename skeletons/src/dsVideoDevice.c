#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "dsVideoDevice.h"


dsError_t dsVideoDeviceInit(void)
{
  /*TODO: Implement Me!*/
  return (dsError_t)0;
}

dsError_t dsGetVideoDevice(int index, int* handle)
{
  /*TODO: Implement Me!*/
  (void)index;
  (void)handle;
  return (dsError_t)0;
}

dsError_t dsSetDFC(int handle, dsVideoZoom_t dfc)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)dfc;
  return (dsError_t)0;
}

dsError_t dsGetDFC(int handle, dsVideoZoom_t* dfc)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)dfc;
  return (dsError_t)0;
}

dsError_t dsVideoDeviceTerm(void)
{
  /*TODO: Implement Me!*/
  return (dsError_t)0;
}

dsError_t dsGetHDRCapabilities(int handle, int* capabilities)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)capabilities;
  return (dsError_t)0;
}

dsError_t dsGetSupportedVideoCodingFormats(int handle, unsigned int* supported_formats)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)supported_formats;
  return (dsError_t)0;
}

dsError_t dsGetVideoCodecInfo(int handle, dsVideoCodingFormat_t codec, dsVideoCodecInfo_t* info)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)codec;
  (void)info;
  return (dsError_t)0;
}

dsError_t dsForceDisableHDRSupport(int handle, bool disable)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)disable;
  return (dsError_t)0;
}

dsError_t dsSetFRFMode(int handle, int frfmode)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)frfmode;
  return (dsError_t)0;
}

dsError_t dsGetFRFMode(int handle, int* frfmode)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)frfmode;
  return (dsError_t)0;
}

dsError_t dsGetCurrentDisplayframerate(int handle, char* framerate)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)framerate;
  return (dsError_t)0;
}

dsError_t dsSetDisplayframerate(int handle, char* framerate)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)framerate;
  return (dsError_t)0;
}

dsError_t dsRegisterFrameratePreChangeCB(dsRegisterFrameratePreChangeCB_t CBFunc)
{
  /*TODO: Implement Me!*/
  (void)CBFunc;
  return (dsError_t)0;
}

dsError_t dsRegisterFrameratePostChangeCB(dsRegisterFrameratePostChangeCB_t CBFunc)
{
  /*TODO: Implement Me!*/
  (void)CBFunc;
  return (dsError_t)0;
}

