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

#include "dsVideoPort.h"

void test_ds_video_hal_l2_getSetEnableVideoPort( void )
{
    int result=dsERR_GENERAL;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    bool enabled = false;

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsEnableVideoPort(handle, true);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsIsVideoPortEnabled(handle, &enabled);

    result = dsERR_GENERAL;
    //Video port enabled as expected
    if (enabled){
        result = dsERR_NONE;
    }
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsEnableVideoPort(handle, false);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsIsVideoPortEnabled(handle, &enabled);
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    result = dsERR_GENERAL;
    //Video port disabled as expected
    if (!enabled){
        result = dsERR_NONE;
    }
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}


static UT_test_suite_t *pSuite = NULL;

/**
 * @brief Register the main tests for this module
 * 
 * @return int - 0 on success, otherwise failure
 */
int test_l2_ds_videoport_register( void )
{

    /* add a suite to the registry */
    pSuite = UT_add_suite("[DS VideoPort HAL L2 cases]", NULL, NULL);
    if (NULL == pSuite) 
    {
        return -1;
    }

    UT_add_test( pSuite, "video_getSetEnableVideoPort", test_ds_video_hal_l2_getSetEnableVideoPort);

    return 0;
}

