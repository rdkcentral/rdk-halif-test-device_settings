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
#include <dsVideoDevice.h>

/**
 * @brief This function will do the functional testing of dsGetSuportedVideoCodingFormats() verify its result.
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * dsERR_NONE : will be returned if dsGetSupportedVedioCodingFormats () is called successfully.
 * dsERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_videodevice_hal_l2_dsGetSupportedVideoCodingFormatsAndVerifyCount(void)
{
    dsError_t result = dsERR_GENERAL;
    unsigned int supported_formats = 0;
    int index = 0;
    int handle = 0;

    /* Positive result */
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    result = dsGetVideoDevice(index,&handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    result = dsGetSupportedVideoCodingFormats(handle,&supported_formats);
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    result = dsERR_GENERAL;
    //supported formats should be greater than zero.
    if (supported_formats) {
        result = dsERR_NONE;
    }
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

} 

static UT_test_suite_t *pSuite = NULL;

/**
 * @brief Register the main tests for this module
 * 
 * @return int - 0 on success, otherwise failure
 */
int test_l2_register( void )
{
    /* add a suite to the registry */
    pSuite = UT_add_suite("[L2 test_Example]", NULL, NULL);
    if (NULL == pSuite) 
    {
        return -1;
    }

    UT_add_test( pSuite, "l2_dsGetSupportedVideoCodingFormatsAndVerifyCount", test_videodevice_hal_l2_dsGetSupportedVideoCodingFormatsAndVerifyCount);

    return 0;
}
