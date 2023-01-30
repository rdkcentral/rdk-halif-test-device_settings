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

/**
 * @brief This function will do the unit testing of dsGetSetAudioEncoding()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * dsERR_NONE : will be returned if dsGetSetAudioEncoding () is called successfully.
 * dsERR_GENERAL: Not able to simulate this condition with the UT implementation
 */

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
/**
 * @brief This function will do the unit testing of dsGetSetAudioCompression()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * dsERR_NONE : will be returned if dsGetSetAudioCompression () is called successfully.
 * dsERR_GENERAL: Not able to simulate this condition with the UT implementation
 */

void test_audio_hal_l2_dsGetSetAudioCompression(void)
{
    dsError_t result = dsERR_GENERAL;
    int handle = 0;
    int compression = 0;

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            for (int value = 0; value <=10; value++)
            {
                result = dsSetAudioCompression(handle, value);
                UT_ASSERT_EQUAL(result, dsERR_NONE);
                result = dsGetAudioCompression(handle, &compression);
                UT_ASSERT_EQUAL(result, dsERR_NONE);
                result = dsERR_GENERAL;
                if (value == compression)
                {
                    result = dsERR_NONE;
                }
                UT_ASSERT_EQUAL( result, dsERR_NONE );
                compression = 0;
            }
        }
    }

    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}
/**
 * @brief This function will do the unit testing of dsGetSetAudioGain()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * dsERR_NONE : will be returned if dsGetSetAudioGain () is called successfully.
 * dsERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l2_dsGetSetAudioGain(void)
{
    dsError_t result = dsERR_GENERAL;
    int handle = 0;
    float gain = -2080.00f;

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type, i, &handle);
            UT_ASSERT_EQUAL(result, dsERR_NONE);
            for (float value = -2080.00f; value <= 480.00f; value += 1.0f)
            {
                result = dsSetAudioGain(handle, value);
                UT_ASSERT_EQUAL(result, dsERR_NONE);
                result = dsGetAudioGain(handle, &gain);
                UT_ASSERT_EQUAL(result, dsERR_NONE);
                result = dsERR_GENERAL;
                if (value == gain)
                {
                    result = dsERR_NONE;
                }
            }
        }
    }

    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetSetAudioDB()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * dsERR_NONE : will be returned if dsGetSetAudioDB () is called successfully.
 * dsERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l2_dsGetSetAudioDB(void)
{
    dsError_t result = dsERR_GENERAL;
    int handle = 0;
    float db = 0.0f;

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type, i, &handle);
            UT_ASSERT_EQUAL(result, dsERR_NONE);
            for (float value = 0.0f; value <= 10.0f; value += 0.1f)
            {
                result = dsSetAudioDB(handle, value);
                UT_ASSERT_EQUAL(result, dsERR_NONE);
                result = dsGetAudioDB(handle, &db);
                UT_ASSERT_EQUAL(result, dsERR_NONE);
                result = dsERR_GENERAL;
                if (value == db)
                {
                    result = dsERR_NONE;
                }
            }
        }
    }

    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}
/**
 * @brief This function will do the unit testing of dsGetSetAudioLevel()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * dsERR_NONE : will be returned if dsGetSetAudioLevel () is called successfully.
 * dsERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l2_dsGetSetAudioLevel(void)
{
    dsError_t result = dsERR_GENERAL;
    int handle = 0;
    float level = 0.0f;

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type, i, &handle);
            UT_ASSERT_EQUAL(result, dsERR_NONE);
            for (float value = 0.0f; value <= 100.0f; value += 1.0f)
            {
                result = dsSetAudioLevel(handle, value);
                UT_ASSERT_EQUAL(result, dsERR_NONE);
                result = dsGetAudioLevel(handle, &level);
                UT_ASSERT_EQUAL(result, dsERR_NONE);
                result = dsERR_GENERAL;
                if (value == level)
                {
                    result = dsERR_NONE;
                }
            }
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
    UT_add_test( pSuite, "l2_dsGetSetAudioCompression", test_audio_hal_l2_dsGetSetAudioCompression);
    UT_add_test( pSuite, "l2_dsGetSetAudioGain", test_audio_hal_l2_dsGetSetAudioGain);
    UT_add_test( pSuite, "l2_dsGetSetAudioDB", test_audio_hal_l2_dsGetSetAudioDB);
    UT_add_test( pSuite, "l2_dsGetSetAudioLevel", test_audio_hal_l2_dsGetSetAudioLevel);

    return 0;
}
