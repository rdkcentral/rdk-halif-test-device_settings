#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "dsHost.h"


dsError_t dsHostInit(void)
{
  /*TODO: Implement Me!*/
  return (dsError_t)0;
}

dsError_t dsSetHostPowerMode(int newPower)
{
  /*TODO: Implement Me!*/
  (void)newPower;
  return (dsError_t)0;
}

dsError_t dsGetHostPowerMode(int* currPower)
{
  /*TODO: Implement Me!*/
  (void)currPower;
  return (dsError_t)0;
}

dsError_t dsHostTerm(void)
{
  /*TODO: Implement Me!*/
  return (dsError_t)0;
}

dsError_t dsGetPreferredSleepMode(dsSleepMode_t* pMode)
{
  /*TODO: Implement Me!*/
  (void)pMode;
  return (dsError_t)0;
}

dsError_t dsSetPreferredSleepMode(dsSleepMode_t mode)
{
  /*TODO: Implement Me!*/
  (void)mode;
  return (dsError_t)0;
}

dsError_t dsGetCPUTemperature(float* cpuTemperature)
{
  /*TODO: Implement Me!*/
  (void)cpuTemperature;
  return (dsError_t)0;
}

dsError_t dsGetVersion(uint32_t* versionNumber)
{
  /*TODO: Implement Me!*/
  (void)versionNumber;
  return (dsError_t)0;
}

dsError_t dsSetVersion(uint32_t versionNumber)
{
  /*TODO: Implement Me!*/
  (void)versionNumber;
  return (dsError_t)0;
}

dsError_t dsGetSocIDFromSDK(char* socID)
{
  /*TODO: Implement Me!*/
  (void)socID;
  return (dsError_t)0;
}

dsError_t dsGetHostEDID(unsigned char* edid, int* length)
{
  /*TODO: Implement Me!*/
  (void)edid;
  (void)length;
  return (dsError_t)0;
}

