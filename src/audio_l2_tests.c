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
#include <dsAudio.h>
#include <limits.h>


void test_audio_hal_l2_dsGetSetAudioEncoding(void)
{
    dsError_t result = dsERR_GENERAL;
    int handle = 0;
    dsAudioEncoding_t encoding = dsAUDIO_ENC_NONE;

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsSetAudioEncoding(handle, dsAUDIO_ENC_NONE);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetAudioEncoding(handle,&encoding);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsERR_GENERAL;
            if (dsAUDIO_ENC_NONE == encoding) {
                result = dsERR_NONE;
            }
            UT_ASSERT_EQUAL( result, dsERR_NONE );

            result = dsSetAudioEncoding(handle, dsAUDIO_ENC_DISPLAY);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetAudioEncoding(handle,&encoding);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsERR_GENERAL;
            if (dsAUDIO_ENC_DISPLAY == encoding) {
                result = dsERR_NONE;
            }
            UT_ASSERT_EQUAL( result, dsERR_NONE );

            result = dsSetAudioEncoding(handle, dsAUDIO_ENC_PCM);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetAudioEncoding(handle,&encoding);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsERR_GENERAL;
            if (dsAUDIO_ENC_PCM == encoding) {
                result = dsERR_NONE;
            }
            UT_ASSERT_EQUAL( result, dsERR_NONE );

            result = dsSetAudioEncoding(handle, dsAUDIO_ENC_AC3);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetAudioEncoding(handle,&encoding);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsERR_GENERAL;
            if (dsAUDIO_ENC_AC3 == encoding) {
                result = dsERR_NONE;
            }
            UT_ASSERT_EQUAL( result, dsERR_NONE );

            result = dsSetAudioEncoding(handle, dsAUDIO_ENC_EAC3);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetAudioEncoding(handle,&encoding);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsERR_GENERAL;
            if (dsAUDIO_ENC_EAC3 == encoding) {
                result = dsERR_NONE;
            }
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }

    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}


static UT_test_suite_t *pSuite = NULL;

/**
 * @brief Register the main tests for this module
 * 
 * @return int - 0 on success, otherwise failure
 */
int test_audio_l2_register( void )
{
    /* add a suite to the registry */
    pSuite = UT_add_suite("[L2 test_audio_Example]", NULL, NULL);
    if (NULL == pSuite) 
    {
        return -1;
    }

    UT_add_test( pSuite, "l2_dsGetSetAudioEncoding", test_audio_hal_l2_dsGetSetAudioEncoding);

    return 0;
}
