#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "dsFPD.h"


dsError_t dsFPInit(void)
{
  /*TODO: Implement Me!*/
  return (dsError_t)0;
}

dsError_t dsSetFPBlink(dsFPDIndicator_t eIndicator, unsigned int uBlinkDuration, unsigned int uBlinkIterations)
{
  /*TODO: Implement Me!*/
  (void)eIndicator;
  (void)uBlinkDuration;
  (void)uBlinkIterations;
  return (dsError_t)0;
}

dsError_t dsSetFPBrightness(dsFPDIndicator_t eIndicator, dsFPDBrightness_t eBrightness)
{
  /*TODO: Implement Me!*/
  (void)eIndicator;
  (void)eBrightness;
  return (dsError_t)0;
}

dsError_t dsGetFPBrightness(dsFPDIndicator_t eIndicator, dsFPDBrightness_t* pBrightness)
{
  /*TODO: Implement Me!*/
  (void)eIndicator;
  (void)pBrightness;
  return (dsError_t)0;
}

dsError_t dsSetFPState(dsFPDIndicator_t eIndicator, dsFPDState_t state)
{
  /*TODO: Implement Me!*/
  (void)eIndicator;
  (void)state;
  return (dsError_t)0;
}

dsError_t dsGetFPState(dsFPDIndicator_t eIndicator, dsFPDState_t* state)
{
  /*TODO: Implement Me!*/
  (void)eIndicator;
  (void)state;
  return (dsError_t)0;
}

dsError_t dsSetFPColor(dsFPDIndicator_t eIndicator, dsFPDColor_t eColor)
{
  /*TODO: Implement Me!*/
  (void)eIndicator;
  (void)eColor;
  return (dsError_t)0;
}

dsError_t dsGetFPColor(dsFPDIndicator_t eIndicator, dsFPDColor_t* pColor)
{
  /*TODO: Implement Me!*/
  (void)eIndicator;
  (void)pColor;
  return (dsError_t)0;
}

dsError_t dsSetFPTime(dsFPDTimeFormat_t eTimeFormat, const unsigned int uHour, const unsigned int uMinutes)
{
  /*TODO: Implement Me!*/
  (void)eTimeFormat;
  (void)uHour;
  (void)uMinutes;
  return (dsError_t)0;
}

dsError_t dsSetFPText(const char* pText)
{
  /*TODO: Implement Me!*/
  (void)pText;
  return (dsError_t)0;
}

dsError_t dsSetFPTextBrightness(dsFPDTextDisplay_t eIndicator, dsFPDBrightness_t eBrightness)
{
  /*TODO: Implement Me!*/
  (void)eIndicator;
  (void)eBrightness;
  return (dsError_t)0;
}

dsError_t dsGetFPTextBrightness(dsFPDTextDisplay_t eIndicator, dsFPDBrightness_t* eBrightness)
{
  /*TODO: Implement Me!*/
  (void)eIndicator;
  (void)eBrightness;
  return (dsError_t)0;
}

dsError_t dsFPEnableCLockDisplay(int enable)
{
  /*TODO: Implement Me!*/
  (void)enable;
  return (dsError_t)0;
}

dsError_t dsSetFPScroll(unsigned int uScrollHoldOnDur, unsigned int uHorzScrollIterations, unsigned int uVertScrollIterations)
{
  /*TODO: Implement Me!*/
  (void)uScrollHoldOnDur;
  (void)uHorzScrollIterations;
  (void)uVertScrollIterations;
  return (dsError_t)0;
}

dsError_t dsFPTerm(void)
{
  /*TODO: Implement Me!*/
  return (dsError_t)0;
}

dsError_t dsSetFPTimeFormat(dsFPDTimeFormat_t eTimeFormat)
{
  /*TODO: Implement Me!*/
  (void)eTimeFormat;
  return (dsError_t)0;
}

dsError_t dsGetFPTimeFormat(dsFPDTimeFormat_t* pTimeFormat)
{
  /*TODO: Implement Me!*/
  (void)pTimeFormat;
  return (dsError_t)0;
}

dsError_t dsSetFPDMode(dsFPDMode_t eMode)
{
  /*TODO: Implement Me!*/
  (void)eMode;
  return (dsError_t)0;
}

dsError_t dsFPGetLEDState(dsFPDLedState_t* state)
{
  /*TODO: Implement Me!*/
  (void)state;
  return (dsError_t)0;
}

dsError_t dsFPSetLEDState(dsFPDLedState_t state)
{
  /*TODO: Implement Me!*/
  (void)state;
  return (dsError_t)0;
}

