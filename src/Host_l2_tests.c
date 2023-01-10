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
#include "dsHost.h"

void test_ds_host_hal_l2_getSetPowerMode( void )
{
    int result;
    int newPower = 0;
    int currPower = 0;

    /* Positive result */
    result = dsHostInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    newPower = 0;
    //result = dsSetHostPowerMode(newPower);//Fixme: Bcm undefined symbol
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    //result = dsGetHostPowerMode(result = dsGetHostPowerMode(&currPower);currPower);//Fixme: Bcm undefined symbol
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsERR_GENERAL;
    //Power mode properly applied
    if (newPower==currPower){
        result = dsERR_NONE;
    }
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    newPower = 1;
    //result = dsSetHostPowerMode(newPower);//Fixme: Bcm undefined symbol
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    //result = dsGetHostPowerMode(result = dsGetHostPowerMode(&currPower);currPower);//Fixme: Bcm undefined symbol
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsERR_GENERAL;
    //Power mode properly applied
    if (newPower==currPower){
        result = dsERR_NONE;
    }
    UT_ASSERT_EQUAL( result, dsERR_NONE);


    /*calling close should pass */
    //result = dsHostTerm();//Fixme: Bcm undefined symbol

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}


static UT_test_suite_t *pSuite = NULL;

/**
 * @brief Register the main tests for this module
 * 
 * @return int - 0 on success, otherwise failure
 */
int test_l2_ds_host_register( void )
{

    /* add a suite to the registry */
    pSuite = UT_add_suite("[DS VideoPort HAL L2 cases]", NULL, NULL);
    if (NULL == pSuite) 
    {
        return -1;
    }

    UT_add_test( pSuite, "host_getSetPowerMode", test_ds_host_hal_l2_getSetPowerMode);

    return 0;
}
