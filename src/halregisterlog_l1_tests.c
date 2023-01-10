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
#include <dsError.h>
#include <dshalregisterlog.h>
#include <ut.h>

void test_halregisterlog_hal_l1_func(void)
{
    UT_FAIL("Need to implement");
    /* Positive */
    /* Negative */
    /* #TODO: Unclear how the function will fail, maybe this function should be void? */

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
} 

void test_halregisterlog_hal_l1_func1(void)
{
    UT_FAIL("Need to implement");
    /* Positive */
    /* Negative */
    /* #TODO: Unclear how the function will fail, maybe this function should be void? */

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
} 

void test_halregisterlog_hal_l1_func2(void)
{
    UT_FAIL("Need to implement");
    /* Positive */
    /* Negative */
    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
} 
static UT_test_suite_t *pSuite = NULL;

/**
 * @brief Register the main tests for this module
 * 
 * @return int - 0 on success, otherwise failure
 */
int halregisterlog_l1_register( void )
{
    /* add a suite to the registry */
    pSuite = UT_add_suite("[L1 halregisterlog]", NULL, NULL);
    if (NULL == pSuite) 
    {
        return -1;
    }

    UT_add_test( pSuite, "halregisterlog_level1_test_func", test_halregisterlog_hal_l1_func);
    UT_add_test( pSuite, "halregisterlog_level1_test_func", test_halregisterlog_hal_l1_func1);
    UT_add_test( pSuite, "halregisterlog_level1_test_func", test_halregisterlog_hal_l1_func2);

    return 0;
}
