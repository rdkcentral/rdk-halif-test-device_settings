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
#include <dsDisplay.h>

/**
 * @brief This function will do the functional testing of dsGetEDID() and verify its returnign the value properly.
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * dsERR_NONE : will be returned if dsGetSetAudioCompression () is called successfully.
 * dsERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_display_hal_l2_CheckDisplayEDIDResolutions(void)
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
            result = dsERR_GENERAL;
            if (edid.numOfSupportedResolution > 0) {
                result = dsERR_NONE;
            } else {
                printf ("\n Not able to read edid from the video port %d", type);
            }
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

static UT_test_suite_t *pSuite = NULL;

/**
 * @brief Register the main tests for this module
 * 
 * @return int - 0 on success, otherwise failure
 */
int test_Display_l2_register( void )
{
    /* add a suite to the registry */
    pSuite = UT_add_suite("[L2 test_Display_Example]", NULL, NULL);
    if (NULL == pSuite) 
    {
        return -1;
    }

    UT_add_test( pSuite, "display_hal_l2_CheckDisplayEDIDResolutions", test_display_hal_l2_CheckDisplayEDIDResolutions);

    return 0;
}
