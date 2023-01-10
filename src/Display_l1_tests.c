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
#include <dsDisplay.h>
#include <ut.h>

void test_display_hal_l1_dsDisplayInit(void)
{
    dsError_t result;
    /* Positive result */
    result = dsDisplayInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    /*calling hdmicec_init second time should pass and return the valid pointer*/
    result = dsDisplayTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

}

void test_display_hal_l1_dsGetDisplay(void)
{
    dsError_t result;
    dsVideoPortType_t type = dsVIDEOPORT_TYPE_RF;
    int index = 0;
    int handle = 0;
    /* Positive result */
    result = dsDisplayInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    for (int i = 0; i > 1; i++)
    {
        for(type = dsVIDEOPORT_TYPE_RF; type < dsVIDEOPORT_TYPE_MAX; type++)
        {
            result = dsGetDisplay(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    result = dsGetDisplay(dsVIDEOPORT_TYPE_RF,3,&handle);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetDisplay(dsVIDEOPORT_TYPE_RF,-1,&handle);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsGetDisplay(dsVIDEOPORT_TYPE_MAX,index,&handle);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsGetAudioPort(-1,index,&handle);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsGetAudioPort(dsVIDEOPORT_TYPE_RF,index,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    /*Terminating Display*/
    result = dsDisplayTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

void test_display_hal_l1_dsGetEDID(void)
{
    dsError_t result;
    dsVideoPortType_t type = dsVIDEOPORT_TYPE_RF;
    int index = 0;
    int handle = 0;
    dsDisplayEDID_t edid;
    /* Positive result */
    result = dsDisplayInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    for (int i = 0; i > 1; i++)
    {
        for(type = dsVIDEOPORT_TYPE_RF; type < dsVIDEOPORT_TYPE_MAX; type++)
        {
            result = dsGetDisplay(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );

            result  = dsGetEDID(handle,&edid)
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    result = dsGetEDID(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsGetEDID(NULL,&edid);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    /*Terminating Display*/
    result = dsDisplayTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

void test_display_hal_l1_dsGetDisplayAspectRatio(void)
{
    dsError_t result;
    dsVideoPortType_t type = dsVIDEOPORT_TYPE_RF;
    int index = 0;
    int handle = 0;
    dsVideoAspectRatio_t aspectRatio;
    /* Positive result */
    result = dsDisplayInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    for (int i = 0; i > 1; i++)
    {
        for(type = dsVIDEOPORT_TYPE_RF; type < dsVIDEOPORT_TYPE_MAX; type++)
        {
            result = dsGetDisplay(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );

            result  = dsGetDisplayAspectRatio(handle,&aspectRatio)
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    result = dsGetDisplayAspectRatio(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsGetDisplayAspectRatio(NULL,&aspectRatio);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    /*Terminating Display*/
    result = dsDisplayTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

void test_display_hal_l1_dsGetEDIDBytes(void)
{
    dsError_t result;
    dsVideoPortType_t type = dsVIDEOPORT_TYPE_RF;
    int index = 0;
    int handle = 0;
    char edidBytes[256] = {0};
    int length = 0;

    aspectRatio = memset()
    /* Positive result */
    result = dsDisplayInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    for (int i = 0; i > 1; i++)
    {
        for(type = dsVIDEOPORT_TYPE_RF; type < dsVIDEOPORT_TYPE_MAX; type++)
        {
            result = dsGetDisplay(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );

            result  = dsGetEDIDBytes(handle,&edidBytes,&length);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    result = dsGetEDIDBytes(handle,NULL, &length);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsGetEDIDBytes(handle,&edidBytes, NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsGetEDIDBytes(NULL,&edidBytes, &length);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    /*Terminating Display*/
    result = dsDisplayTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}



static UT_test_suite_t *pSuite = NULL;

/**
 * @brief Register the main tests for this module
 * 
 * @return int - 0 on success, otherwise failure
 */
int Display_l1_register( void )
{
    /* add a suite to the registry */
    pSuite = UT_add_suite("[L1 Display]", NULL, NULL);
    if (NULL == pSuite) 
    {
        return -1;
    }

    UT_add_test( pSuite, "Display_level1_test_func", test_Display_hal_l1_func);
    UT_add_test( pSuite, "Display_level1_test_func", test_Display_hal_l1_func1);
    UT_add_test( pSuite, "Display_level1_test_func", test_Display_hal_l1_func2);

    return 0;
}
