#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "dsDisplay.h"


dsError_t dsDisplayInit(void)
{
  /*TODO: Implement Me!*/
  return (dsError_t)0;
}

dsError_t dsGetDisplay(dsVideoPortType_t vType, int index, intptr_t* handle)
{
  /*TODO: Implement Me!*/
  (void)vType;
  (void)index;
  (void)handle;
  return (dsError_t)0;
}

dsError_t dsGetEDID(intptr_t handle, dsDisplayEDID_t* edid)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)edid;
  return (dsError_t)0;
}

dsError_t dsGetEDIDBytes(intptr_t handle, unsigned char** edid, int* length)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)edid;
  (void)length;
  return (dsError_t)0;
}

dsError_t dsGetDisplayAspectRatio(intptr_t handle, dsVideoAspectRatio_t* aspectRatio)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)aspectRatio;
  return (dsError_t)0;
}

dsError_t dsDisplayTerm(void)
{
  /*TODO: Implement Me!*/
  return (dsError_t)0;
}

dsError_t dsRegisterDisplayEventCallback(intptr_t handle, dsDisplayEventCallback_t cb)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)cb;
  return (dsError_t)0;
}

