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

/**
 * @brief This function will do the functional testing of dsSetVesion () and verify its value using dsGetVersion().
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * dsERR_NONE : will be returned if dsGetVersion () os dsGEtVersion is called successfully.
 * dsERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_ds_host_hal_l2_setGetVersion( void )
{
    int result=dsERR_GENERAL;
    uint32_t versionNumber = 0;


    //Calling api before open, should give invalid state
    result = dsSetVersion(versionNumber);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    result = dsHostInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    uint32_t versionNumberToSet = 1;
    result = dsSetVersion(versionNumberToSet);
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    result = dsGetVersion(&versionNumber);
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    result = dsERR_GENERAL;
    if (versionNumberToSet==versionNumber) {
        result = dsERR_NONE;
    }
    UT_ASSERT_EQUAL( result, dsERR_NONE );

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

    UT_add_test( pSuite, "l2_setGetVersion", test_ds_host_hal_l2_setGetVersion);

    return 0;
}
