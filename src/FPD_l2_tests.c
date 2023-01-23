/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2016 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

#include <string.h>
#include <stdlib.h>

#include <ut.h>

#include <dsError.h>
#include <dsFPD.h>

void test_FPD_l2_function(void)
{
	UT_FAIL("Need to implement");
    /* Positive */
    /* Negative */
} 

void test_videodevice_hal_l2_dsSetGetFPState(void)
{
    dsError_t result;
    dsFPDIndicator_t eIndicator = dsFPD_INDICATOR_MESSAGE;
    dsFPDState_t state = dsFPD_STATE_OFF;

    /* Positive result */
    result = dsFPInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for(eIndicator=dsFPD_INDICATOR_MESSAGE ; eIndicator<=dsFPD_INDICATOR_MAX; eIndicator++ ){
        for(state = dsFPD_STATE_OFF; state<=dsFPD_STATE_ON; state++){
            state = dsFPD_STATE_OFF;
            result = dsSetFPState(eIndicator,state);
            UT_ASSERT_EQUAL( result, dsERR_NONE );

            result = dsGetFPState(eIndicator,&state);
            UT_ASSERT_EQUAL( result, dsERR_NONE );

            result = dsERR_GENERAL;
            if (dsFPD_STATE_OFF == state) {
                result = dsERR_NONE;
            }
            UT_ASSERT_EQUAL( result, dsERR_NONE );

            dsFPDState_t state = dsFPD_STATE_ON;
            result = dsSetFPState(eIndicator,state);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetFPState(eIndicator,&state);
            UT_ASSERT_EQUAL( result, dsERR_NONE );

            result = dsERR_GENERAL;
            if (dsFPD_STATE_ON == state) {
                result = dsERR_NONE;
            }
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
	
    /*calling hdmicec_init second time should pass and return the valid pointer*/
    result = dsFPTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

}

static UT_test_suite_t *pSuite = NULL;

/**
 * @brief Register the main tests for this module
 * 
 * @return int - 0 on success, otherwise failure
 */
int test_FPD_l2_register( void )
{
    /* add a suite to the registry */
    pSuite = UT_add_suite("[L2 test_FPD_Example]", NULL, NULL);
    if (NULL == pSuite) 
    {
        return -1;
    }

    UT_add_test( pSuite, "l2_dsSetGetFPState", test_videodevice_hal_l2_dsSetGetFPState);

    return 0;
}
