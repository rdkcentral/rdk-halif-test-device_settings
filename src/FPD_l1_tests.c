#include <string.h>
#include <stdlib.h>
#include <dsError.h>
#include <dsHdmiIn.h>
#include <ut.h>
#include <limits.h>


void test_FPD_hal_l1_init(void)
{
    dsError_t result;
    /* Positive result */
    result = dsFPInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    /*calling hdmicec_init second time should pass and return the valid pointer*/
    result = dsFPTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_FPD_hal_l1_dsSetFPBlink(void)
{
    dsError_t result;
	dsFPDIndicator_t eIndicator = dsFPD_INDICATOR_MESSAGE;
	unsigned int uBlinkDuration = 1;
	unsigned int uBlinkIterations = 1;
	
	if(eIndicator > dsFPD_INDICATOR_MAX || eIndicator < 0)
    {
        return;
    }

    /* Positive result */
    result =  dsFPInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );
	
    for(eIndicator=dsFPD_INDICATOR_MESSAGE;eIndicator<=dsFPD_INDICATOR_MAX;eIndicator++){
    result = dsSetFPBlink(eIndicator,uBlinkDuration,uBlinkIterations);
    UT_ASSERT_EQUAL( result, dsERR_NONE );
	}
	
    /* Passing Invalid Parameter to the function*/
    uBlinkDuration = -1;
    result = dsSetFPBlink(eIndicator,uBlinkDuration,uBlinkIterations);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    uBlinkIterations = -1;
    result = dsSetFPBlink(eIndicator,uBlinkDuration,uBlinkIterations);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
	
	uBlinkDuration = 65536;
    result = dsSetFPBlink(eIndicator,uBlinkDuration,uBlinkIterations);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
	
	uBlinkIterations = 65536;
    result = dsSetFPBlink(eIndicator,uBlinkDuration,uBlinkIterations);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    /*calling hdmicec_init second time should pass and return the valid pointer*/
    result = dsFPTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

}

void test_FPD_hal_l1_dsSetFPBrightness(void)
{
    dsError_t result;
	// Make the changes
    dsFPDIndicator_t eIndicator = dsFPD_INDICATOR_MESSAGE; 
	dsFPDBrightness_t eBrightness = dsFPD_MODE_ANY;

    /* Positive result */
    result = dsFPInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for(eIndicator=dsFPD_INDICATOR_MESSAGE,eBrightness = dsFPD_MODE_ANY;eIndicator<=dsFPD_INDICATOR_MAX,eBrightness<=dsFPD_MODE_CLOCK;eIndicator++,eBrightness++){
    result = dsSetFPBrightness(eIndicator,eBrightness);
    UT_ASSERT_EQUAL( result, dsERR_NONE );
	}
  
    /* Passing Invalid Parameter to the function*/
    result = dsSetFPBrightness(NULL,eBrightness);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);
    
    result = dsSetFPBrightness(eIndicator,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling hdmicec_init second time should pass and return the valid pointer*/
    result = dsFPTerm();
     UT_ASSERT_EQUAL( result, dsERR_NONE);

}

void test_FPD_hal_l1_dsGetFPState(void)
{
    dsError_t result;
    // initialization
	dsFPDIndicator_t eIndicator = dsFPD_INDICATOR_MESSAGE; 
	dsFPDState_t* state = dsFPD_STATE_OFF;
	
    /* Positive result */
     result = dsFPInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for(eIndicator=dsFPD_INDICATOR_MESSAGE,state = dsFPD_STATE_OFF;eIndicator<=dsFPD_INDICATOR_MAX,state<=dsFPD_STATE_ON;eIndicator++,state++){
    result = dsGetFPState(eIndicator,&state);
    UT_ASSERT_EQUAL( result, dsERR_NONE );
	}

    /* Passing Invalid Parameter to the function*/
    result = dsGetFPState(NULL,&state);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

     result = dsGetFPState(eIndicator,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    /*calling hdmicec_init second time should pass and return the valid pointer*/
    result = dsFPTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

}

void test_videodevice_hal_l1_dsSetFPState(void)
{
    dsError_t result;
    dsFPDIndicator_t eIndicator = dsFPD_INDICATOR_MESSAGE;
	dsFPDState_t state = dsFPD_STATE_OFF;

    /* Positive result */
    result = dsFPInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

   for(eIndicator=dsFPD_INDICATOR_MESSAGE,state = dsFPD_STATE_OFF;eIndicator<=dsFPD_INDICATOR_MAX,state<=dsFPD_STATE_ON;eIndicator++,state++){
    result = dsSetFPState(eIndicator,state);
    UT_ASSERT_EQUAL( result, dsERR_NONE );
	}
    /* Passing Invalid Parameter to the function*/
    result = dsSetFPState(NULL,state);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsSetFPState(eIndicator,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
	
    /*calling hdmicec_init second time should pass and return the valid pointer*/
    result = dsFPTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

}

void test_videodevice_hal_l1_dsGetFPBrightness(void)
{
    dsError_t result;
    dsFPDIndicator_t eIndicator = dsFPD_INDICATOR_MESSAGE; 
	dsFPDBrightness_t *pBrightness = dsFPD_MODE_ANY;

    /* Positive result */
    result = dsFPInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for(eIndicator=dsFPD_INDICATOR_MESSAGE,pBrightness = dsFPD_MODE_ANY;eIndicator<=dsFPD_INDICATOR_MAX,pBrightness<=dsFPD_MODE_CLOCK;eIndicator++,pBrightness++){
    result = dsGetFPBrightness(eIndicator,&pBrightness);
    UT_ASSERT_EQUAL( result, dsERR_NONE );
	}

    /* Passing Invalid Parameter to the function*/
    result = dsGetFPBrightness(NULL,&pBrightness);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsGetFPBrightness(eIndicator,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    /*calling hdmicec_init second time should pass and return the valid pointer*/
    result = dsFPTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

}

void test_FPD_hal_l1_dsGetFPColor(void)
{
    uint32_t R8 = 0;
    uint32_t G8 = 0;
    uint32_t B8 = 0;

    dsError_t result;
    dsFPDIndicator_t eIndicator = dsFPD_INDICATOR_MESSAGE;
	dsFPDColor_t *pColor = dsFPDColor_Make(R8,G8,B8);

    /* Positive result */
    result = dsFPInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for(eIndicator=dsFPD_INDICATOR_MESSAGE,pColor = dsFPDColor_Make(R8,G8,B8);eIndicator<=dsFPD_INDICATOR_MAX,pColor<=dsFPD_COLOR_MAX;eIndicator++,pColor++){
    result = dsGetFPColor(eIndicator,&pColor);
    UT_ASSERT_EQUAL( result, dsERR_NONE );
	}

    /* Passing Invalid Parameter to the function*/
    result = dsGetFPColor(eIndicator,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsGetFPColor(NULL,&pColor);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    /*calling hdmicec_init second time should pass and return the valid pointer*/
    result = dsFPTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

}

void test_FDP_hal_l1_dsSetFPColor(void)
{
    uint32_t R8 = 0;
    uint32_t G8 = 0;
    uint32_t B8 = 0;
    dsError_t result;
    dsFPDIndicator_t eIndicator = dsFPD_INDICATOR_MESSAGE;
	dsFPDColor_t eColor = dsFPDColor_Make(R8,G8,B8);
	
    /* Positive result */
    result = dsFPInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for(eIndicator=dsFPD_INDICATOR_MESSAGE,eColor = dsFPDColor_Make(R8,G8,B8);eIndicator<=dsFPD_INDICATOR_MAX,eColor<=dsFPD_COLOR_MAX;eIndicator++,eColor++){
    result = dsSetFPColor(eIndicator,eColor);
    UT_ASSERT_EQUAL( result, dsERR_NONE );
	}

    /* Passing Invalid Parameter to the function*/
    result = dsSetFPColor(eIndicator,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsSetFPColor(NULL,eColor);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsFPTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

}

void test_FPD_hal_l1_dsSetFPTime(void)
{
    dsError_t result;
    dsFPDTimeFormat_t eTimeFormat = dsFPD_TIME_12_HOUR; 
    unsigned int uHour = 1;
    unsigned int uMinutes = 1;
	
    /* Positive result */
    result = dsFPInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

	for(eTimeFormat = dsFPD_TIME_12_HOUR;eTimeFormat<=dsFPD_TIME_STRING;eTimeFormat++){
    result = dsSetFPTime(eTimeFormat,uHour,uMinutes);
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    }

    /* Passing Invalid Parameter to the function*/
    uHour = -1;
    result = dsSetFPTime(eTimeFormat,uHour,uMinutes);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    uMinutes = -1;
    result = dsSetFPTime(eTimeFormat,uHour,uMinutes);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    uHour = 65536;
    result = dsSetFPTime(eTimeFormat,uHour,uMinutes);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    uMinutes = 65536;
    result = dsSetFPTime(eTimeFormat,uHour,uMinutes);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsFPTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

}

void test_FPD_hal_l1_dsSetFPText(void)
{
    dsError_t result;
    const char* pText = "";
	
    /* Positive result */
    result = dsFPInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    result = dsSetFPText(&pText);
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    /* Passing Invalid Parameter to the function*/
    /*calling hdmicec_init second time should pass and return the valid pointer*/
    result = dsSetFPText(&pText);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsSetFPText(NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsFPTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

}

void test_FDP_hal_l1_dsSetFPTextBrightness(void)
{
    dsError_t result;
    dsFPDTextDisplay_t eIndicator = dsFPD_TEXTDISP_TEXT; 
	dsFPDBrightness_t eBrightness = dsFPD_MODE_ANY;
	
    /* Positive result */
    result = dsFPInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    
    for(eIndicator = dsFPD_TEXTDISP_TEXT,eBrightness = dsFPD_MODE_ANY;eIndicator<=dsFPD_TEXTDISP_MAX,eBrightness<=dsFPD_MODE_CLOCK;eIndicator++,eBrightness++){
    result = dsSetFPTextBrightness(eIndicator,eBrightness);
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    }

    /* Passing Invalid Parameter to the function*/
    /*calling hdmicec_init second time should pass and return the valid pointer*/
    result = dsSetFPTextBrightness(eIndicator,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsSetFPTextBrightness(NULL,eBrightness);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsFPTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

}

void test_FDP_hal_l1_dsGetFPTextBrightness(void)
{
    dsError_t result;
    dsFPDTextDisplay_t eIndicator = dsFPD_TEXTDISP_TEXT; 
	dsFPDBrightness_t *eBrightness = dsFPD_MODE_ANY;
	
    /* Positive result */
    result = dsFPInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    for(eIndicator = dsFPD_TEXTDISP_TEXT,eBrightness = dsFPD_MODE_ANY;eIndicator<=dsFPD_TEXTDISP_MAX,eBrightness<=dsFPD_MODE_CLOCK;eIndicator++,eBrightness++){
    result = dsGetFPTextBrightness(eIndicator,&eBrightness);
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    }

    /* Passing Invalid Parameter to the function*/
    /*calling hdmicec_init second time should pass and return the valid pointer*/
    result = dsGetFPTextBrightness(eIndicator,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsGetFPTextBrightness(NULL,&eBrightness);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsFPTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

}

void test_FDP_hal_l1_dsFPEnableCLockDisplay(void)
{
    dsError_t result;
    int enable = 0;
	
    /* Positive result */
    result = dsFPInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for(enable=0;enable<=1;enable++){
    result = dsFPEnableCLockDisplay(enable);
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    }

    /* Passing Invalid Parameter to the function*/
    /*calling hdmicec_init second time should pass and return the valid pointer*/
    enable = -1;
    result = dsFPEnableCLockDisplay(enable);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsFPTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

}

void test_FDP_hal_l1_dsSetFPScroll(void)
{
    dsError_t result;
    unsigned int uScrollHoldOnDur = 1;
	unsigned int uHorzScrollIterations = 1;
	unsigned int uVertScrollIterations = 1;
	
    /* Positive result */
    result = dsFPInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    result = dsSetFPScroll(uScrollHoldOnDur,uHorzScrollIterations,uVertScrollIterations);
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    /* Passing Invalid Parameter to the function*/
    /*calling hdmicec_init second time should pass and return the valid pointer*/
    uScrollHoldOnDur = -1;
    result = dsSetFPScroll(uScrollHoldOnDur,uHorzScrollIterations,uVertScrollIterations);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    uHorzScrollIterations = -1;
    result = dsSetFPScroll(uScrollHoldOnDur,uHorzScrollIterations,uVertScrollIterations);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    uVertScrollIterations = -1;
    result = dsSetFPScroll(uScrollHoldOnDur,uHorzScrollIterations,uVertScrollIterations);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    uScrollHoldOnDur = 65536;
    result = dsSetFPScroll(uScrollHoldOnDur,uHorzScrollIterations,uVertScrollIterations);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    uHorzScrollIterations = 65536;
    result = dsSetFPScroll(uScrollHoldOnDur,uHorzScrollIterations,uVertScrollIterations);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    uVertScrollIterations = 65536; 
    result = dsSetFPScroll(uScrollHoldOnDur,uHorzScrollIterations,uVertScrollIterations);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsFPTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

}

void test_FDP_hal_l1_dsSetFPDBrightness(void)
{
    dsError_t result;
    dsFPDIndicator_t eIndicator = dsFPD_INDICATOR_MESSAGE;
	dsFPDBrightness_t eBrightness = dsFPD_MODE_ANY;
	bool toPersist = true;
	
    /* Positive result */
    result = dsFPInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    for(eIndicator=dsFPD_INDICATOR_MESSAGE,eBrightness = dsFPD_MODE_ANY;eIndicator<=dsFPD_INDICATOR_MAX,eBrightness<=dsFPD_MODE_CLOCK;eIndicator++,eBrightness++){
    result = dsSetFPDBrightness(eIndicator,eBrightness,toPersist);
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    }

    /* Passing Invalid Parameter to the function*/
    /*calling hdmicec_init second time should pass and return the valid pointer*/
    result = dsSetFPDBrightness(NULL,eBrightness,toPersist);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsSetFPDBrightness(eIndicator,NULL,toPersist);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsSetFPDBrightness(eIndicator,eBrightness,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsFPTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

}

void test_FDP_hal_l1_dsSetFPDColor(void)
{
    uint32_t R8 = 0;
    uint32_t G8 = 0;
    uint32_t B8 = 0;
    dsError_t result;
    dsFPDIndicator_t eIndicator = dsFPD_INDICATOR_MESSAGE;
	dsFPDColor_t eColor = dsFPDColor_Make(R8,G8,B8);
	bool toPersist = true;
	
    /* Positive result */
    result = dsFPInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for(eIndicator = dsFPD_INDICATOR_MESSAGE,eColor = dsFPDColor_Make(R8,G8,B8); eIndicator<=dsFPD_INDICATOR_MAX, eColor<=dsFPD_COLOR_MAX;eIndicator++ ){
        result = dsSetFPDColor(eIndicator,eColor,toPersist);
        UT_ASSERT_EQUAL( result, dsERR_NONE );
    }

    /* Passing Invalid Parameter to the function*/
    /*calling hdmicec_init second time should pass and return the valid pointer*/
    result = dsSetFPDColor(NULL,eColor,toPersist);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsSetFPDColor(eIndicator,NULL,toPersist);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsSetFPDColor(eIndicator,eColor,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsFPTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

}

void test_FDP_hal_l1_dsSetFPTimeFormat(void)
{
    dsError_t result;
    dsFPDTimeFormat_t eTimeFormat = dsFPD_TIME_12_HOUR;
	
    /* Positive result */
    result = dsFPInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );
   
    for(eTimeFormat=dsFPD_TIME_12_HOUR;eTimeFormat<=dsFPD_TIME_STRING;eTimeFormat++){
        result = dsSetFPTimeFormat(eTimeFormat);
        UT_ASSERT_EQUAL( result, dsERR_NONE );
    }

    /* Passing Invalid Parameter to the function*/
    /*calling hdmicec_init second time should pass and return the valid pointer*/
    result = dsSetFPTimeFormat(NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsFPTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

}

void test_FDP_hal_l1_dsGetFPTimeFormat(void)
{
    dsError_t result;
    dsFPDTimeFormat_t *pTimeFormat = dsFPD_TIME_12_HOUR;
	
    /* Positive result */
    result = dsFPInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for(pTimeFormat=dsFPD_TIME_12_HOUR;pTimeFormat<=dsFPD_TIME_STRING;pTimeFormat++){
    result = dsGetFPTimeFormat(&pTimeFormat);
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    }

    /* Passing Invalid Parameter to the function*/
    /*calling hdmicec_init second time should pass and return the valid pointer*/
    result = dsGetFPTimeFormat(NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsFPTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

}

void test_FDP_hal_l1_dsSetFPDMode(void)
{
    dsError_t result;
    dsFPDMode_t eMode = dsFPD_MODE_ANY;
	
    /* Positive result */
    result = dsFPInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    
    for(eMode = dsFPD_MODE_ANY;eMode<=dsFPD_MODE_CLOCK;eMode++){
    result = dsSetFPDMode(eMode);
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    }

    /* Passing Invalid Parameter to the function*/
    /*calling hdmicec_init second time should pass and return the valid pointer*/
    result = dsSetFPDMode(NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsFPTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

}



static UT_test_suite_t *pSuite = NULL;

/**
 * @brief Register the main tests for this module
 *
 * @return int - 0 on success, otherwise failure
 */
int FPD_l1_register ( void )
{
    /* add a suite to the registry */
    pSuite = UT_add_suite("[L1 ds host]", NULL, NULL);
    if (NULL == pSuite)
    {
        return -1;
    }

    UT_add_test( pSuite, "l1_init", test_FPD_hal_l1_init);
    UT_add_test( pSuite, "l1_dsSetFPBlink", test_FPD_hal_l1_dsSetFPBlink);
    UT_add_test( pSuite, "l1_dsSetFPBrightness", test_FPD_hal_l1_dsSetFPBrightness);
    UT_add_test( pSuite, "l1_dsSetFPBrightness", test_FPD_hal_l1_dsSetFPBrightness);
    UT_add_test( pSuite, "l1_dsSetFPState", test_videodevice_hal_l1_dsSetFPState);
    UT_add_test( pSuite, "l1_dsGetFPBrightness", test_videodevice_hal_l1_dsGetFPBrightness);
    UT_add_test( pSuite, "l1_dsGetFPColor", test_FPD_hal_l1_dsGetFPColor);
    UT_add_test( pSuite, "l1_dsSetFPColor", test_FDP_hal_l1_dsSetFPColor);
    UT_add_test( pSuite, "l1_dsSetFPTime", test_FPD_hal_l1_dsSetFPTime);
    UT_add_test( pSuite, "l1_dsSetFPText", test_FPD_hal_l1_dsSetFPText);
    UT_add_test( pSuite, "l1_dsSetFPTextBrightness", test_FDP_hal_l1_dsSetFPTextBrightness);
    UT_add_test( pSuite, "l1_dsGetFPTextBrightness", test_FDP_hal_l1_dsGetFPTextBrightness);
    UT_add_test( pSuite, "l1_dsFPEnableCLockDisplay", test_FDP_hal_l1_dsFPEnableCLockDisplay);
    UT_add_test( pSuite, "l1_dsSetFPScroll", test_FDP_hal_l1_dsSetFPScroll);
    UT_add_test( pSuite, "l1_dsSetFPDBrightness", test_FDP_hal_l1_dsSetFPDBrightness);
    UT_add_test( pSuite, "l1_dsSetFPDColor", test_FDP_hal_l1_dsSetFPDColor);
    UT_add_test( pSuite, "l1_dsSetFPTimeFormat", test_FDP_hal_l1_dsSetFPTimeFormat);
    UT_add_test( pSuite, "l1_dsGetFPTimeFormat", test_FDP_hal_l1_dsGetFPTimeFormat);
    UT_add_test( pSuite, "l1_dsSetFPDMode", test_FDP_hal_l1_dsSetFPDMode);

    return 0;
}

