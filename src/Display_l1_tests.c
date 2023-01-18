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
#include <dsAudio.h>

/**
 * @brief This function will do the unit testing of dsDisplayInit ()
 * This function will ensure underlying API implementation is handling
 * invalid call sequences to the API
 * dsERR_NONE : will be returned if dsDisplayInit () is called successfully.
 * dsERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_display_hal_l1_dsDisplayInit(void)
{
    int result = dsERR_GENERAL;
    /* Positive result */
    result = dsDisplayInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    result = dsDisplayInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    /*calling hdmicec_init second time should pass and return the valid pointer*/
    result = dsDisplayTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

}

/**
 * @brief This function will do the unit testing of dsGetDisplay ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * dsERR_NONE : will be returned if dsGetDisplay () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsDisplayInit()
 * dsERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_display_hal_l1_dsGetDisplay(void)
{
    int result = dsERR_GENERAL;
    dsVideoPortType_t type = dsVIDEOPORT_TYPE_RF;
    int index = 0;
    int handle = 0;

    result = dsGetDisplay(dsVIDEOPORT_TYPE_RF,3,&handle);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

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

/**
 * @brief This function will do the unit testing of dsGetEDID ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * dsERR_NONE : will be returned if dsGetEDID () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsDisplayInit()
 * dsERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_display_hal_l1_dsGetEDID(void)
{
    int result = dsERR_GENERAL;
    dsVideoPortType_t type = dsVIDEOPORT_TYPE_RF;
    int handle = 0;
    dsDisplayEDID_t edid;

    result  = dsGetEDID(handle,&edid);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsDisplayInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    for (int i = 0; i > 1; i++)
    {
        for(type = dsVIDEOPORT_TYPE_RF; type < dsVIDEOPORT_TYPE_MAX; type++)
        {
            result = dsGetDisplay(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );

            result  = dsGetEDID(handle,&edid);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    result = dsGetEDID(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsGetEDID(0,&edid);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    /*Terminating Display*/
    result = dsDisplayTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetDisplayAspectRatio ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * dsERR_NONE : will be returned if dsGetDisplayAspectRatio () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsDisplayInit()
 * dsERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_display_hal_l1_dsGetDisplayAspectRatio(void)
{
    int result = dsERR_GENERAL;
    dsVideoPortType_t type = dsVIDEOPORT_TYPE_RF;
    int handle = 0;
    dsVideoAspectRatio_t aspectRatio;

    result  = dsGetDisplayAspectRatio(handle,&aspectRatio);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsDisplayInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    for (int i = 0; i > 1; i++)
    {
        for(type = dsVIDEOPORT_TYPE_RF; type < dsVIDEOPORT_TYPE_MAX; type++)
        {
            result = dsGetDisplay(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );

            result  = dsGetDisplayAspectRatio(handle,&aspectRatio);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    result = dsGetDisplayAspectRatio(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsGetDisplayAspectRatio(0,&aspectRatio);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    /*Terminating Display*/
    result = dsDisplayTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetEDIDBytes ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * dsERR_NONE : will be returned if dsGetEDIDBytes () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsDisplayInit()
 * dsERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_display_hal_l1_dsGetEDIDBytes(void)
{
    int result = dsERR_GENERAL;
    dsVideoPortType_t type = dsVIDEOPORT_TYPE_RF;
    int handle = 0;
    unsigned char edidBytes[256] = {0};
    int length = 0;

    result  = dsGetEDIDBytes(handle,(unsigned char **)&edidBytes,&length);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsDisplayInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    for (int i = 0; i > 1; i++)
    {
        for(type = dsVIDEOPORT_TYPE_RF; type < dsVIDEOPORT_TYPE_MAX; type++)
        {
            result = dsGetDisplay(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );

            result  = dsGetEDIDBytes(handle, (unsigned char **)&edidBytes,&length);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    result = dsGetEDIDBytes(handle,NULL, &length);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsGetEDIDBytes(handle, (unsigned char **)&edidBytes, NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsGetEDIDBytes(0, (unsigned char **)&edidBytes, &length);
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

    UT_add_test( pSuite, "l1_dsDisplayInit", test_display_hal_l1_dsDisplayInit);
    UT_add_test( pSuite, "l1_dsGetDisplay", test_display_hal_l1_dsGetDisplay);
    UT_add_test( pSuite, "l1_dsGetEDID", test_display_hal_l1_dsGetEDID);
    UT_add_test( pSuite, "l1_dsGetDisplayAspectRatio", test_display_hal_l1_dsGetDisplayAspectRatio);
    UT_add_test( pSuite, "l1_dsGetEDIDBytes", test_display_hal_l1_dsGetEDIDBytes);

    return 0;
}
