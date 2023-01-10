#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "dsCompositeIn.h"


dsError_t dsCompositeInInit(void)
{
  /*TODO: Implement Me!*/
  return (dsError_t)0;
}

dsError_t dsCompositeInTerm(void)
{
  /*TODO: Implement Me!*/
  return (dsError_t)0;
}

dsError_t dsCompositeInGetNumberOfInputs(uint8_t* pNumberOfInputs)
{
  /*TODO: Implement Me!*/
  (void)pNumberOfInputs;
  return (dsError_t)0;
}

dsError_t dsCompositeInGetStatus(dsCompositeInStatus_t* pStatus)
{
  /*TODO: Implement Me!*/
  (void)pStatus;
  return (dsError_t)0;
}

dsError_t dsCompositeInSelectPort(dsCompositeInPort_t Port)
{
  /*TODO: Implement Me!*/
  (void)Port;
  return (dsError_t)0;
}

dsError_t dsCompositeInScaleVideo(int32_t x, int32_t y, int32_t width, int32_t height)
{
  /*TODO: Implement Me!*/
  (void)x;
  (void)y;
  (void)width;
  (void)height;
  return (dsError_t)0;
}

dsError_t dsCompositeInRegisterConnectCB(dsCompositeInConnectCB_t CBFunc)
{
  /*TODO: Implement Me!*/
  (void)CBFunc;
  return (dsError_t)0;
}

dsError_t dsCompositeInRegisterSignalChangeCB(dsCompositeInSignalChangeCB_t CBFunc)
{
  /*TODO: Implement Me!*/
  (void)CBFunc;
  return (dsError_t)0;
}

dsError_t dsCompositeInRegisterStatusChangeCB(dsCompositeInStatusChangeCB_t CBFunc)
{
  /*TODO: Implement Me!*/
  (void)CBFunc;
  return (dsError_t)0;
}

