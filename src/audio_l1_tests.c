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
#include <dsAudio.h>
#include <ut.h>
#include <limits.h>

/**
 * @brief This function will do the unit testing of dsAudioPortInit ()
 * This function will ensure underlying API implementation is handling
 * invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsAudioPortInit () is called successfully.
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsAudioPortInit(void)
{
    dsError_t result;
    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    /*calling hdmicec_init second time should pass and return the valid pointer*/
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

} 

/**
 * @brief This function will do the unit testing of dsGetAudioPort ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetAudioPort () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetAudioPort(void)
{
    dsError_t result;
    dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR;
    int index = 0;
    int handle = 0;

    result = dsGetAudioPort(type,0,&handle);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsGetAudioPort(dsAUDIOPORT_TYPE_ID_LR,3,&handle);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetAudioPort(dsAUDIOPORT_TYPE_ID_LR,-1,&handle);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsGetAudioPort(dsAUDIOPORT_TYPE_MAX,index,&handle);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsGetAudioPort(-1,index,&handle);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsGetAudioPort(dsAUDIOPORT_TYPE_ID_LR,index,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    /*Terminating Audio Port*/
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetAudioEncoding ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetAudioEncoding () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * dsERR_OPERATION_NOT_SUPPORTED : Not able to simulate this condition with the UT implementation
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetAudioEncoding(void)
{
    dsError_t result;
    dsAudioEncoding_t encoding;
    int index = 0;
    int handle = 0;

    result = dsGetAudioEncoding(handle,&encoding);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetAudioEncoding(handle,&encoding);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsGetAudioEncoding(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetAudioEncoding(NULL,&encoding);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetAudioEncoding ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetAudioEncoding () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * dsERR_OPERATION_NOT_SUPPORTED : Not able to simulate this condition with the UT implementation
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetAudioFormat(void)
{
    dsError_t result;
    dsAudioFormat_t format;
    int index = 0;
    int handle = 0;

    result = dsGetAudioFormat(handle,&format);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE  );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetAudioFormat(handle,&format);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsGetAudioFormat(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetAudioFormat(NULL,&format);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetAudioCompression ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetAudioCompression () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * dsERR_OPERATION_NOT_SUPPORTED : Not able to simulate this condition with the UT implementation
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetAudioCompression(void)
{
    dsError_t result;
    int compression;
    int index = 0;
    int handle = 0;

    result = dsGetAudioCompression(handle,&compression);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE  );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetAudioCompression(handle,&compression);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsGetAudioCompression(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetAudioCompression(NULL,&compression);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetDialogEnhancement ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetDialogEnhancement () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * dsERR_OPERATION_NOT_SUPPORTED : Not able to simulate this condition with the UT implementation
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetDialogEnhancement(void)
{
    dsError_t result;
    int level=0;
    int index = 0;
    int handle = 0;

    result = dsGetDialogEnhancement(handle,&level);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE  );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetDialogEnhancement(handle,&level);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsGetDialogEnhancement(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetDialogEnhancement(NULL,&level);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetDolbyVolumeMode ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetDolbyVolumeMode () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * dsERR_OPERATION_NOT_SUPPORTED : Not able to simulate this condition with the UT implementation
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetDolbyVolumeMode(void)
{
    dsError_t result;
    bool mode=false;
    int index = 0;
    int handle = 0;

    result = dsGetDolbyVolumeMode(handle,&mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE  );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetDolbyVolumeMode(handle,&mode);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsGetDolbyVolumeMode(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetDolbyVolumeMode(NULL,&mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetIntelligentEqualizerMode ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetIntelligentEqualizerMode () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * dsERR_OPERATION_NOT_SUPPORTED : Not able to simulate this condition with the UT implementation
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetIntelligentEqualizerMode(void)
{
    dsError_t result;
    bool mode=false;
    int index = 0;
    int handle = 0;

    result = dsGetIntelligentEqualizerMode(handle,&mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE  );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetIntelligentEqualizerMode(handle,&mode);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsGetIntelligentEqualizerMode(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetIntelligentEqualizerMode(NULL,&mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetVolumeLeveller ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetVolumeLeveller () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * dsERR_OPERATION_NOT_SUPPORTED : Not able to simulate this condition with the UT implementation
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetVolumeLeveller(void)
{
    dsError_t result;
    dsVolumeLeveller_t volLeveler;
    int index = 0;
    int handle = 0;

    result = dsGetVolumeLeveller(handle,&volLeveler);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE  );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetVolumeLeveller(handle,&volLeveler);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsGetVolumeLeveller(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetVolumeLeveller(NULL,&volLeveler);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetBassEnhancer ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetBassEnhancer () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * dsERR_OPERATION_NOT_SUPPORTED : Not able to simulate this condition with the UT implementation
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetBassEnhancer(void)
{
    dsError_t result;
    int boost=0;
    int index = 0;
    int handle = 0;

    result = dsGetBassEnhancer(handle,&boost);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE  );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetBassEnhancer(handle,&boost);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsGetBassEnhancer(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetBassEnhancer(NULL,&boost);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsIsSurroundDecoderEnabled ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsIsSurroundDecoderEnabled () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * dsERR_OPERATION_NOT_SUPPORTED : Not able to simulate this condition with the UT implementation
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsIsSurroundDecoderEnabled(void)
{
    dsError_t result;
    bool enabled=false;
    int index = 0;
    int handle = 0;

    result = dsIsSurroundDecoderEnabled(handle,&enabled);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE  );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsIsSurroundDecoderEnabled(handle,&enabled);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsIsSurroundDecoderEnabled(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsIsSurroundDecoderEnabled(NULL,&enabled);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetDRCMode ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetDRCMode () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * dsERR_OPERATION_NOT_SUPPORTED : Not able to simulate this condition with the UT implementation
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetDRCMode(void)
{
    dsError_t result;
    int mode=0;
    int index = 0;
    int handle = 0;

    result = dsGetDRCMode(handle,&mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE  );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetDRCMode(handle,&mode);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsGetDRCMode(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetDRCMode(NULL,&mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetSurroundVirtualizer ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetSurroundVirtualizer () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * dsERR_OPERATION_NOT_SUPPORTED : Not able to simulate this condition with the UT implementation
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetSurroundVirtualizer(void)
{
    dsError_t result;
    dsSurroundVirtualizer_t virtualizer;
    int index = 0;
    int handle = 0;

    result = dsGetSurroundVirtualizer(handle,&virtualizer);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE  );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetSurroundVirtualizer(handle,&virtualizer);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsGetSurroundVirtualizer(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetSurroundVirtualizer(NULL,&virtualizer);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetMISteering ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetMISteering () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * dsERR_OPERATION_NOT_SUPPORTED : Not able to simulate this condition with the UT implementation
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetMISteering(void)
{
    dsError_t result;
    bool enabled=false;
    int index = 0;
    int handle = 0;

    result = dsGetMISteering(handle,&enabled);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE  );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetMISteering(handle,&enabled);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsGetMISteering(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetMISteering(NULL,&enabled);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetGraphicEqualizerMode ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetGraphicEqualizerMode () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * dsERR_OPERATION_NOT_SUPPORTED : Not able to simulate this condition with the UT implementation
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetGraphicEqualizerMode(void)
{
    dsError_t result;
    int mode=0;
    int index = 0;
    int handle = 0;

    result = dsGetGraphicEqualizerMode(handle,&mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE  );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetGraphicEqualizerMode(handle,&mode);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsGetGraphicEqualizerMode(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetGraphicEqualizerMode(NULL,&mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetMS12AudioProfileList ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetMS12AudioProfileList () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * dsERR_OPERATION_NOT_SUPPORTED : Not able to simulate this condition with the UT implementation
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetMS12AudioProfileList(void)
{
    dsError_t result;
    dsMS12AudioProfileList_t profiles;
    int index = 0;
    int handle = 0;

    result = dsGetMS12AudioProfileList(handle,&profiles);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE  );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetMS12AudioProfileList(handle,&profiles);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsGetMS12AudioProfileList(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetMS12AudioProfileList(NULL,&profiles);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetMS12AudioProfileList ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetMS12AudioProfileList () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * dsERR_OPERATION_NOT_SUPPORTED : Not able to simulate this condition with the UT implementation
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetMS12AudioProfile(void)
{
    dsError_t result;
    char profiles [50] = {0};
    int index = 0;
    int handle = 0;

    result = dsGetMS12AudioProfileList(handle,&profiles);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE  );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetMS12AudioProfileList(handle,profiles);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsGetMS12AudioProfileList(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetMS12AudioProfileList(NULL,profiles);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetSupportedARCTypes ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetSupportedARCTypes () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * dsERR_OPERATION_NOT_SUPPORTED : Not able to simulate this condition with the UT implementation
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetSupportedARCTypes(void)
{
    dsError_t result;
    int types;
    int index = 0;
    int handle = 0;

    result = dsGetSupportedARCTypes(handle,&types);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetSupportedARCTypes(handle,&types);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsGetSupportedARCTypes(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetSupportedARCTypes(NULL,&types);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsAudioSetSAD ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsAudioSetSAD () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsAudioSetSAD(void)
{
    dsError_t result;
    dsAudioSADList_t sad_list;
    int index = 0;
    int handle = 0;

    result = dsAudioSetSAD(handle,sad_list);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        result = dsGetAudioPort(dsAUDIOPORT_TYPE_HDMI_ARC,i,&handle);
        UT_ASSERT_EQUAL( result, dsERR_NONE );
        result = dsAudioSetSAD(handle,sad_list);
        UT_ASSERT_EQUAL( result, dsERR_NONE );
    }

    result = dsAudioSetSAD(NULL,sad_list);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    //#TODO: Check and add fucntions unit testing
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsAudioEnableARC ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsAudioEnableARC () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsAudioEnableARC(void)
{
    dsError_t result;
    dsAudioARCStatus_t arcStatus;
    int index = 0;
    int handle = 0;

    result = dsAudioEnableARC(handle,arcStatus);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        result = dsGetAudioPort(dsAUDIOPORT_TYPE_HDMI_ARC,i,&handle);
        UT_ASSERT_EQUAL( result, dsERR_NONE );
        result = dsAudioEnableARC(handle,arcStatus);
        UT_ASSERT_EQUAL( result, dsERR_NONE );
    }

    //#TODO: Check and add fucntions unit testing
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetStereoMode ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetStereoMode () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetStereoMode(void)
{
    dsError_t result;
    dsAudioStereoMode_t stereoMode;
    int index = 0;
    int handle = 0;

    result = dsGetStereoMode(handle,&stereoMode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetStereoMode(handle,&stereoMode);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsGetStereoMode(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetStereoMode(NULL,&stereoMode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetStereoAuto ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetStereoAuto () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetStereoAuto(void)
{
    dsError_t result;
    int autoMode=0;
    int index = 0;
    int handle = 0;

    result = dsGetStereoAuto(handle,&autoMode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetStereoAuto(handle,&autoMode);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsGetStereoAuto(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetStereoAuto(NULL,&autoMode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetAudioGain ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetAudioGain () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetAudioGain(void)
{
    dsError_t result;
    float gain=0.0f;
    int index = 0;
    int handle = 0;

    result = dsGetAudioGain(handle,&gain);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );


    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetAudioGain(handle,&gain);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsGetAudioGain(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetAudioGain(NULL,&gain);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetAudioDB ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetAudioDB () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetAudioDB(void)
{
    dsError_t result;
    float db=0.0f;
    int index = 0;
    int handle = 0;

    result = dsGetAudioDB(handle,&db);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetAudioDB(handle,&db);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsGetAudioDB(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetAudioDB(NULL,&db);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetAudioLevel ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetAudioLevel () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetAudioLevel(void)
{
    dsError_t result;
    float level=0.0f;
    int index = 0;
    int handle = 0;

    result = dsGetAudioLevel(handle,&level);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetAudioLevel(handle,&level);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsGetAudioLevel(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetAudioLevel(NULL,&level);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetAudioMaxDB ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetAudioMaxDB () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetAudioMaxDB(void)
{
    dsError_t result;
    float db=0.0f;
    int index = 0;
    int handle = 0;

    result = dsGetAudioMaxDB(handle,&db);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetAudioMaxDB(handle,&db);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsGetAudioMaxDB(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetAudioMaxDB(NULL,&db);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetAudioMinDB ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetAudioMinDB () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetAudioMinDB(void)
{
    dsError_t result;
    float db=0.0f;
    int index = 0;
    int handle = 0;

    result = dsGetAudioMinDB(handle,&db);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetAudioMinDB(handle,&db);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsGetAudioMinDB(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetAudioMinDB(NULL,&db);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetAudioMinDB ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetAudioMinDB () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetAudioOptimalLevel(void)
{
    dsError_t result;
    float optimalLevel=0.0f;
    int index = 0;
    int handle = 0;

    result = dsGetAudioOptimalLevel(handle,&optimalLevel);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetAudioOptimalLevel(handle,&optimalLevel);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsGetAudioOptimalLevel(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetAudioOptimalLevel(NULL,&optimalLevel);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetAudioDelay ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetAudioDelay () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetAudioDelay(void)
{
    dsError_t result;
    uint32_t audioDelayMs=0;
    int index = 0;
    int handle = 0;

    result = dsGetAudioDelay(handle,&audioDelayMs);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetAudioDelay(handle,&audioDelayMs);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsGetAudioDelay(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetAudioDelay(NULL,&audioDelayMs);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetAudioDelayOffset ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetAudioDelayOffset () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetAudioDelayOffset(void)
{
    dsError_t result;
    uint32_t audioDelayOffsetMs=0;
    int index = 0;
    int handle = 0;

    result = dsGetAudioDelayOffset(handle,&audioDelayOffsetMs);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetAudioDelayOffset(handle,&audioDelayOffsetMs);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsGetAudioDelayOffset(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetAudioDelayOffset(NULL,&audioDelayOffsetMs);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsSetAudioAtmosOutputMode ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsSetAudioAtmosOutputMode () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsSetAudioAtmosOutputMode(void)
{
    dsError_t result;
    bool enable = true;
    int handle = 0;

    result = dsSetAudioAtmosOutputMode(handle,enable);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsSetAudioAtmosOutputMode(handle,enable);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }

        result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetSinkDeviceAtmosCapability ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetSinkDeviceAtmosCapability () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetSinkDeviceAtmosCapability(void)
{
    dsError_t result;
    dsATMOSCapability_t capabilities;
    int index = 0;
    int handle = 0;

    result = dsGetSinkDeviceAtmosCapability(handle,&capabilities);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetSinkDeviceAtmosCapability(handle,&capabilities);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsGetSinkDeviceAtmosCapability(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetSinkDeviceAtmosCapability(NULL,&capabilities);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsIsAudioLoopThru ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsIsAudioLoopThru () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsIsAudioLoopThru(void)
{
    dsError_t result;
    bool loopThrough;
    int index = 0;
    int handle = 0;

    result = dsIsAudioLoopThru(handle,&loopThrough);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsIsAudioLoopThru(handle,&loopThrough);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsIsAudioLoopThru(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsIsAudioLoopThru(NULL,&loopThrough);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsIsAudioMute ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsIsAudioMute () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsIsAudioMute(void)
{
    dsError_t result;
    bool muted;
    int index = 0;
    int handle = 0;

    result = dsIsAudioMute(handle,&muted);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsIsAudioMute(handle,&muted);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsIsAudioMute(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsIsAudioMute(NULL,&muted);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsIsAudioPortEnabled ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsIsAudioPortEnabled () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsIsAudioPortEnabled(void)
{
    dsError_t result;
    bool enabled;
    int index = 0;
    int handle = 0;

    result = dsIsAudioPortEnabled(handle,&enabled);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsIsAudioPortEnabled(handle,&enabled);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsIsAudioPortEnabled(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsIsAudioPortEnabled(NULL,&enabled);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsEnableAudioPort ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsEnableAudioPort () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsEnableAudioPort(void)
{
    dsError_t result;
    bool enabled;
    int index = 0;
    int handle = 0;

    result = dsEnableAudioPort(handle,enabled);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsEnableAudioPort(handle,enabled);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/  
    result = dsEnableAudioPort(NULL,enabled);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsEnableMS12Config ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsEnableMS12Config () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsEnableMS12Config(void)
{
    dsError_t result;
    bool enabled;
    int index = 0;
    int handle = 0;
    dsMS12FEATURE_t feature;

    result = dsEnableMS12Config(handle,feature, enabled);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsEnableMS12Config(handle,feature, enabled);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/  
    result = dsEnableMS12Config(NULL,feature, enabled);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsEnableLEConfig ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsEnableLEConfig () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsEnableLEConfig(void)
{
    dsError_t result;
    bool enabled;
    int index = 0;
    int handle = 0;

    result = dsEnableLEConfig(handle,enabled);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsEnableLEConfig(handle,enabled);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/  
    result = dsEnableLEConfig(NULL,enabled);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetLEConfig ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetLEConfig () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetLEConfig(void)
{
    dsError_t result;
    bool enabled;
    int index = 0;
    int handle = 0;

    result = dsGetLEConfig(handle,&enabled);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetLEConfig(handle,&enabled);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsGetLEConfig(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetLEConfig(NULL,&enabled);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsSetAudioEncoding ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsSetAudioEncoding () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsSetAudioEncoding(void)
{
    dsError_t result;
    bool enabled = false;
    int index = 0;
    int handle = 0;

    result = dsSetAudioEncoding(handle,true);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsSetAudioEncoding(handle,true);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsSetAudioEncoding(handle,false);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    result = dsSetAudioEncoding(handle, INT_MAX);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsSetAudioEncoding(NULL,enabled);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsSetAudioCompression ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsSetAudioCompression () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsSetAudioCompression(void)
{
    dsError_t result;
    int compression = 1;
    int index = 0;
    int handle = 0;

    result = dsSetAudioCompression(handle,compression);
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsSetAudioCompression(handle,compression);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    result = dsSetAudioCompression(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsSetAudioCompression(handle,-1);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsSetAudioCompression(NULL,compression);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsSetDialogEnhancement ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsSetDialogEnhancement () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsSetDialogEnhancement(void)
{
    dsError_t result;
    int level = 1;
    int index = 0;
    int handle = 0;

    result = dsSetDialogEnhancement(handle,level);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsSetDialogEnhancement(handle,level);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    result = dsSetDialogEnhancement(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsSetDialogEnhancement(handle,-1);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsSetDialogEnhancement(NULL,level);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsSetDolbyVolumeMode ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsSetDolbyVolumeMode () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsSetDolbyVolumeMode(void)
{
    dsError_t result;
    bool mode = true;
    int index = 0;
    int handle = 0;

    result = dsSetDolbyVolumeMode(handle,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsSetDolbyVolumeMode(handle,mode);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    result = dsSetDolbyVolumeMode(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsSetDolbyVolumeMode(NULL,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsSetIntelligentEqualizerMode ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsSetIntelligentEqualizerMode () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsSetIntelligentEqualizerMode(void)
{
    dsError_t result;
    int mode = 1;
    int index = 0;
    int handle = 0;

    result = dsSetIntelligentEqualizerMode(handle,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsSetIntelligentEqualizerMode(handle,mode);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    result = dsSetIntelligentEqualizerMode(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsSetIntelligentEqualizerMode(NULL,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsSetIntelligentEqualizerMode(handle,-1);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsSetIntelligentEqualizerMode(handle,65535);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsSetVolumeLeveller ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsSetVolumeLeveller () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsSetVolumeLeveller(void)
{
    dsError_t result;
    dsVolumeLeveller_t mode;
    int index = 0;
    int handle = 0;
    mode.mode = 0;
    mode.level = 10;

    result = dsSetVolumeLeveller(handle,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsSetVolumeLeveller(handle,mode);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }

    result = dsSetVolumeLeveller(NULL,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsSetBassEnhancer ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsSetBassEnhancer () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsSetBassEnhancer(void)
{
    dsError_t result;
    int mode = 1;
    int index = 0;
    int handle = 0;

    result = dsSetBassEnhancer(handle,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsSetBassEnhancer(handle,mode);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    result = dsSetBassEnhancer(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsSetBassEnhancer(NULL,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsEnableSurroundDecoder ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsEnableSurroundDecoder () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsEnableSurroundDecoder(void)
{
    dsError_t result;
    bool mode = true;
    int index = 0;
    int handle = 0;

    result = dsEnableSurroundDecoder(handle,mode);
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsEnableSurroundDecoder(handle,mode);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    result = dsEnableSurroundDecoder(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsEnableSurroundDecoder(NULL,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsSetDRCMode ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsSetDRCMode () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsSetDRCMode(void)
{
    dsError_t result;
    int mode = 1;
    int index = 0;
    int handle = 0;

    result = dsSetDRCMode(handle,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsSetDRCMode(handle,mode);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    result = dsSetDRCMode(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsSetDRCMode(NULL,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsSetDRCMode(handle,-1);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsSetDRCMode(handle,65535);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsSetSurroundVirtualizer ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsSetSurroundVirtualizer () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsSetSurroundVirtualizer(void)
{
    dsError_t result;
    dsSurroundVirtualizer_t mode;
    int index = 0;
    int handle = 0;
    mode.mode = 1;
    mode.boost =1;

    result = dsSetSurroundVirtualizer(handle,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsSetSurroundVirtualizer(handle,mode);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }

    result = dsSetSurroundVirtualizer(NULL,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsSetMISteering ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsSetMISteering () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsSetMISteering(void)
{
    dsError_t result;
    bool mode = false;
    int index = 0;
    int handle = 0;

    result = dsSetMISteering(handle,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsSetMISteering(handle,mode);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    result = dsSetMISteering(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsSetMISteering(NULL,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsSetGraphicEqualizerMode ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsSetGraphicEqualizerMode () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsSetGraphicEqualizerMode(void)
{
    dsError_t result;
    int mode = 1;
    int index = 0;
    int handle = 0;

    result = dsSetGraphicEqualizerMode(handle,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsSetGraphicEqualizerMode(handle,mode);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    result = dsSetGraphicEqualizerMode(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsSetGraphicEqualizerMode(NULL,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsSetGraphicEqualizerMode(handle,-1);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsSetGraphicEqualizerMode(handle,65535);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsSetMS12AudioProfile ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsSetMS12AudioProfile () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsSetMS12AudioProfile(void)
{
    dsError_t result;
    char mode = 0x01;
    int index = 0;
    int handle = 0;

    result = dsSetMS12AudioProfile(handle,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsSetMS12AudioProfile(handle,mode);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    result = dsSetMS12AudioProfile(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsSetMS12AudioProfile(NULL,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsSetStereoMode ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsSetStereoMode () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsSetStereoMode(void)
{
    dsError_t result;
    dsAudioStereoMode_t mode = dsAUDIO_STEREO_MONO;
    int index = 0;
    int handle = 0;

    result = dsSetStereoMode(handle,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsSetStereoMode(handle,mode);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    result = dsSetStereoMode(handle, INT_MAX);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsSetStereoMode(NULL,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsSetStereoMode(handle,dsAUDIO_STEREO_UNKNOWN);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsSetIntelligentEqualizerMode(handle,dsAUDIO_STEREO_MAX);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsSetStereoAuto ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsSetStereoAuto () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsSetStereoAuto(void)
{
    dsError_t result;
    int mode = 1;
    int index = 0;
    int handle = 0;

    result = dsSetStereoAuto(handle,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsSetStereoAuto(handle,mode);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    result = dsSetStereoAuto(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsSetStereoAuto(NULL,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsSetStereoAuto(handle,-1);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsSetStereoAuto(handle,65535);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsSetAudioGain ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsSetAudioGain () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsSetAudioGain(void)
{
    dsError_t result;
    float mode = 1.0f;
    int index = 0;
    int handle = 0;

    result = dsSetAudioGain(handle,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsSetAudioGain(handle,mode);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    result = dsSetAudioGain(handle, INT_MAX);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsSetAudioGain(NULL,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsSetAudioDB ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsSetAudioDB () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsSetAudioDB(void)
{
    dsError_t result;
    float mode = 1.0f;
    int index = 0;
    int handle = 0;

    result = dsSetAudioDB(handle,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsSetAudioDB(handle,mode);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    result = dsSetAudioDB(handle, INT_MAX);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsSetAudioDB(NULL,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsSetAudioLevel ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsSetAudioLevel () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsSetAudioLevel(void)
{
    dsError_t result;
    float mode = 1.0f;
    int index = 0;
    int handle = 0;

    result = dsSetAudioLevel(handle,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsSetAudioLevel(handle,mode);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    result = dsSetAudioLevel(handle, INT_MAX);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsSetAudioLevel(NULL,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsSetStereoAuto ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsSetStereoAuto () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsSetAudioDucking(void)
{
    dsError_t result;
    int index = 0;
    int handle = 0;
    dsAudioDuckingAction_t action = 0;
    dsAudioDuckingType_t type = dsAUDIO_DUCKINGTYPE_ABSOLUTE;
    const unsigned char level = 1;
    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsSetAudioDucking(handle, action, dsAUDIO_DUCKINGTYPE_ABSOLUTE, level);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsSetAudioDucking(handle, action, dsAUDIO_DUCKINGTYPE_RELATIVE, level);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    result = dsSetAudioDucking(NULL, action, dsAUDIO_DUCKINGTYPE_RELATIVE, level);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsSetAudioDucking(handle, action, INT_MAX, level);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsSetAudioDucking(handle, action, dsAUDIO_DUCKINGTYPE_RELATIVE,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsEnableLoopThru ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsEnableLoopThru () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsEnableLoopThru(void)
{
    dsError_t result;
    bool mode = true;
    int index = 0;
    int handle = 0;

    result = dsEnableLoopThru(handle,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsEnableLoopThru(handle,mode);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    result = dsEnableLoopThru(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsEnableLoopThru(NULL,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsSetAudioMute ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsSetAudioMute () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsSetAudioMute(void)
{
    dsError_t result;
    bool mode = true;
    int index = 0;
    int handle = 0;

    result = dsSetAudioMute(handle,mode);
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsSetAudioMute(handle,mode);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    result = dsSetAudioMute(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsSetAudioMute(NULL,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsIsAudioMSDecode ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsIsAudioMSDecode () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsIsAudioMSDecode(void)
{
    dsError_t result;
    bool HasMs11Decode;
    int index = 0;
    int handle = 0;

    result = dsIsAudioMSDecode(handle,&HasMs11Decode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsIsAudioMSDecode(handle,&HasMs11Decode);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsIsAudioMSDecode(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsIsAudioMSDecode(NULL,&HasMs11Decode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsIsAudioMS12Decode ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsIsAudioMS12Decode () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsIsAudioMS12Decode(void)
{
    dsError_t result;
    bool HasMs12Decode;
    int index = 0;
    int handle = 0;

    result = dsIsAudioMS12Decode(handle,&HasMs12Decode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsIsAudioMS12Decode(handle,&HasMs12Decode);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsIsAudioMS12Decode(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsIsAudioMS12Decode(NULL,&HasMs12Decode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsSetAudioDelay ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsSetAudioDelay () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsSetAudioDelay(void)
{
    dsError_t result;
    uint32_t mode = 10;
    int index = 0;
    int handle = 0;

    result = dsSetAudioDelay(handle,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsSetAudioDelay(handle,mode);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    result = dsSetAudioDelay(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsSetAudioDelay(NULL,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsSetAudioDelayOffset ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsSetAudioDelayOffset () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsSetAudioDelayOffset(void)
{
    dsError_t result;
    uint32_t mode = 10;
    int index = 0;
    int handle = 0;

    result = dsSetAudioDelayOffset(handle,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsSetAudioDelayOffset(handle,mode);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    result = dsSetAudioDelayOffset(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsSetAudioDelayOffset(NULL,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsAudioOutIsConnected ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsAudioOutIsConnected () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsAudioOutIsConnected(void)
{
    dsError_t result;
    bool isCon;
    int index = 0;
    int handle = 0;

    result = dsAudioOutIsConnected(handle,&isCon);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsAudioOutIsConnected(handle,&isCon);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsAudioOutIsConnected(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioOutIsConnected(NULL,&isCon);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsAudioOutIsConnected ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsAudioOutIsConnected () is called successfully.
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsAudioOutRegisterConnectCB(void)
{
    dsError_t result;
    //TODO:
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsAudioOutIsConnected ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsAudioOutIsConnected () is called successfully.
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsAudioFormatUpdateRegisterCB(void)
{
    dsError_t result;
    //TODO:
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetAudioCapabilities ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetAudioCapabilities () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetAudioCapabilities(void)
{
    dsError_t result;
    int capabilites;
    int index = 0;
    int handle = 0;

    result = dsGetAudioCapabilities(handle,&capabilites);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetAudioCapabilities(handle,&capabilites);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsGetAudioCapabilities(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetAudioCapabilities(NULL,&capabilites);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetAudioCapabilities ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetAudioCapabilities () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetMS12Capabilities(void)
{
    dsError_t result;
    int capabilites;
    int index = 0;
    int handle = 0;

    result = dsGetMS12Capabilities(handle,&capabilites);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetMS12Capabilities(handle,&capabilites);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsGetMS12Capabilities(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetMS12Capabilities(NULL,&capabilites);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsResetDialogEnhancement ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsResetDialogEnhancement () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsResetDialogEnhancement(void)
{
    dsError_t result;
    int index = 0;
    int handle = 0;

    result = dsResetDialogEnhancement(handle);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsResetDialogEnhancement(handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsResetDialogEnhancement(NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsResetBassEnhancer ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsResetBassEnhancer () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsResetBassEnhancer(void)
{
    dsError_t result;
    int index = 0;
    int handle = 0;

    result = dsResetBassEnhancer(handle);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsResetBassEnhancer(handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsResetBassEnhancer(NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsResetSurroundVirtualizer ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsResetSurroundVirtualizer () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsResetSurroundVirtualizer(void)
{
    dsError_t result;
    int index = 0;
    int handle = 0;

    result = dsResetSurroundVirtualizer(handle);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsResetSurroundVirtualizer(handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsResetSurroundVirtualizer(NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsResetVolumeLeveller ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsResetVolumeLeveller () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsResetVolumeLeveller(void)
{
    dsError_t result;
    int index = 0;
    int handle = 0;

    result = dsResetVolumeLeveller(handle);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsResetVolumeLeveller(handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsResetVolumeLeveller(NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsResetVolumeLeveller ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsResetVolumeLeveller () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsSetMS12AudioProfileSetttingsOverride(void)
{
    dsError_t result = dsERR_OPERATION_NOT_SUPPORTED;
    //TODO:
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsResetVolumeLeveller ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsResetVolumeLeveller () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsSetAssociatedAudioMixing(void)
{
    dsError_t result;
    bool mode = true;
    int index = 0;
    int handle = 0;

    result = dsSetAssociatedAudioMixing(handle,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsSetAssociatedAudioMixing(handle,mode);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    result = dsSetAssociatedAudioMixing(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsSetAssociatedAudioMixing(NULL,mode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetAssociatedAudioMixing ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetAssociatedAudioMixing () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetAssociatedAudioMixing(void)
{
    dsError_t result;
    bool mixing;
    int index = 0;
    int handle = 0;

    result = dsGetAssociatedAudioMixing(handle,&mixing);
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetAssociatedAudioMixing(handle,&mixing);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsGetAssociatedAudioMixing(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetAssociatedAudioMixing(NULL,&mixing);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsSetFaderControl ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsSetFaderControl () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsSetFaderControl(void)
{
    dsError_t result;
    int mixerControl = 1;
    int index = 0;
    int handle = 0;

    result = dsSetFaderControl(handle,mixerControl);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsSetFaderControl(handle,mixerControl);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    result = dsSetFaderControl(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsSetFaderControl(NULL,mixerControl);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsSetFaderControl(handle,-1);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsSetFaderControl(handle,65535);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetFaderControl ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetFaderControl () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetFaderControl(void)
{
    dsError_t result;
    int mixerbalance;
    int index = 0;
    int handle = 0;

    result = dsGetFaderControl(handle,&mixerbalance);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetFaderControl(handle,&mixerbalance);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsGetFaderControl(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetFaderControl(NULL,&mixerbalance);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsSetPrimaryLanguage ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsSetPrimaryLanguage () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsSetPrimaryLanguage(void)
{
    dsError_t result;
    char pLang[25] = "ENGLISH";
    int index = 0;
    int handle = 0;

    result = dsSetPrimaryLanguage(handle,pLang);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsSetPrimaryLanguage(handle,pLang);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    result = dsSetPrimaryLanguage(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsSetPrimaryLanguage(NULL,pLang);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetPrimaryLanguage ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetPrimaryLanguage () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetPrimaryLanguage(void)
{
    dsError_t result;
    char lang[100]={0};
    int index = 0;
    int handle = 0;

    result = dsGetPrimaryLanguage(handle,lang);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetPrimaryLanguage(handle,lang);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsGetPrimaryLanguage(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetPrimaryLanguage(NULL,lang);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsSetSecondaryLanguage ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsSetSecondaryLanguage () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsSetSecondaryLanguage(void)
{
    dsError_t result;
    char sLang[25] = "ENGLISH";
    int index = 0;
    int handle = 0;

    result = dsSetSecondaryLanguage(handle,sLang);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsSetSecondaryLanguage(handle,sLang);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    result = dsSetSecondaryLanguage(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsSetSecondaryLanguage(NULL, sLang);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetSecondaryLanguage ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetSecondaryLanguage () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetSecondaryLanguage(void)
{
    dsError_t result;
    char lang[100] = {0};
    int index = 0;
    int handle = 0;

    result = dsGetSecondaryLanguage(handle,lang);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for (int i = 0; i > 1; i++)
    {
        for(dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR; type < dsAUDIOPORT_TYPE_MAX; type++)
        {
            result = dsGetAudioPort(type,i,&handle);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
            result = dsGetSecondaryLanguage(handle,lang);
            UT_ASSERT_EQUAL( result, dsERR_NONE );
        }
    }
    /* Passing Invalid Parameter to the function*/
    result = dsGetSecondaryLanguage(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetSecondaryLanguage(NULL,lang);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsGetHDMIARCPortId ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * mfrERR_NONE : will be returned if dsGetHDMIARCPortId () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsAudioPortInit()
 * mfrERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_audio_hal_l1_dsGetHDMIARCPortId(void)
{
    dsError_t result;
    int portId;

    result = dsGetHDMIARCPortId(&portId);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsAudioPortInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    result = dsGetHDMIARCPortId(&portId);
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    /* Passing Invalid Parameter to the function*/
    result = dsGetHDMIARCPortId(NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsAudioPortTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}
static UT_test_suite_t *pSuite = NULL;

/**
 * @brief Register the main tests for this module
 * 
 * @return int - 0 on success, otherwise failure
 */
int audio_l1_register( void )
{
    /* add a suite to the registry */
    pSuite = UT_add_suite("[L1 Audio]", NULL, NULL);
    if (NULL == pSuite) 
    {
        return -1;
    }

    UT_add_test( pSuite, "l1_dsAudioPortInit", test_audio_hal_l1_dsAudioPortInit);
    UT_add_test( pSuite, "l1_dsGetAudioPort", test_audio_hal_l1_dsGetAudioPort);
    UT_add_test( pSuite, "l1_dsGetAudioEncoding", test_audio_hal_l1_dsGetAudioEncoding);
    UT_add_test( pSuite, "l1_dsGetAudioFormat", test_audio_hal_l1_dsGetAudioFormat);
    UT_add_test( pSuite, "l1_dsGetAudioCompression", test_audio_hal_l1_dsGetAudioCompression);
    UT_add_test( pSuite, "l1_dsGetDialogEnhancement", test_audio_hal_l1_dsGetDialogEnhancement);
    UT_add_test( pSuite, "l1_dsGetDolbyVolumeMode", test_audio_hal_l1_dsGetDolbyVolumeMode);
    UT_add_test( pSuite, "l1_dsGetIntelligentEqualizerMode", test_audio_hal_l1_dsGetIntelligentEqualizerMode);
    UT_add_test( pSuite, "l1_dsGetVolumeLeveller", test_audio_hal_l1_dsGetVolumeLeveller);
    UT_add_test( pSuite, "l1_dsGetBassEnhancer", test_audio_hal_l1_dsGetBassEnhancer);
    UT_add_test( pSuite, "l1_dsIsSurroundDecoderEnabled", test_audio_hal_l1_dsIsSurroundDecoderEnabled);
    UT_add_test( pSuite, "l1_dsGetDRCMode", test_audio_hal_l1_dsGetDRCMode);
    UT_add_test( pSuite, "l1_dsGetSurroundVirtualizer", test_audio_hal_l1_dsGetSurroundVirtualizer);
    UT_add_test( pSuite, "l1_dsGetMISteering", test_audio_hal_l1_dsGetMISteering);
    UT_add_test( pSuite, "l1_dsGetGraphicEqualizerMode", test_audio_hal_l1_dsGetGraphicEqualizerMode);
    UT_add_test( pSuite, "l1_dsGetMS12AudioProfileList", test_audio_hal_l1_dsGetMS12AudioProfileList);
    UT_add_test( pSuite, "l1_dsGetMS12AudioProfile", test_audio_hal_l1_dsGetMS12AudioProfile);
    UT_add_test( pSuite, "l1_dsGetSupportedARCTypes", test_audio_hal_l1_dsGetSupportedARCTypes);
    UT_add_test( pSuite, "l1_dsAudioSetSAD", test_audio_hal_l1_dsAudioSetSAD);
    UT_add_test( pSuite, "l1_dsAudioEnableARC", test_audio_hal_l1_dsAudioEnableARC);
    UT_add_test( pSuite, "l1_dsGetStereoMode", test_audio_hal_l1_dsGetStereoMode);
    UT_add_test( pSuite, "l1_dsGetStereoAuto", test_audio_hal_l1_dsGetStereoAuto);
    UT_add_test( pSuite, "l1_dsGetAudioGain", test_audio_hal_l1_dsGetAudioGain);
    UT_add_test( pSuite, "l1_dsGetAudioDB", test_audio_hal_l1_dsGetAudioDB);
    UT_add_test( pSuite, "l1_dsGetAudioLevel", test_audio_hal_l1_dsGetAudioLevel);
    UT_add_test( pSuite, "l1_dsGetAudioMaxDB", test_audio_hal_l1_dsGetAudioMaxDB);
    UT_add_test( pSuite, "l1_dsGetAudioMinDB", test_audio_hal_l1_dsGetAudioMinDB);
    UT_add_test( pSuite, "l1_dsGetAudioOptimalLevel", test_audio_hal_l1_dsGetAudioOptimalLevel);
    UT_add_test( pSuite, "l1_dsGetAudioDelay", test_audio_hal_l1_dsGetAudioDelay);
    UT_add_test( pSuite, "l1_dsGetAudioDelayOffset", test_audio_hal_l1_dsGetAudioDelayOffset);
    UT_add_test( pSuite, "l1_dsSetAudioAtmosOutputMode", test_audio_hal_l1_dsSetAudioAtmosOutputMode);
    UT_add_test( pSuite, "l1_dsGetSinkDeviceAtmosCapability", test_audio_hal_l1_dsGetSinkDeviceAtmosCapability);
    UT_add_test( pSuite, "l1_dsIsAudioLoopThru", test_audio_hal_l1_dsIsAudioLoopThru);
    UT_add_test( pSuite, "l1_dsIsAudioMute", test_audio_hal_l1_dsIsAudioMute);
    UT_add_test( pSuite, "l1_dsIsAudioPortEnabled", test_audio_hal_l1_dsIsAudioPortEnabled);
    UT_add_test( pSuite, "l1_dsEnableAudioPort", test_audio_hal_l1_dsEnableAudioPort);
    UT_add_test( pSuite, "l1_dsEnableMS12Config", test_audio_hal_l1_dsEnableMS12Config);
    UT_add_test( pSuite, "l1_dsEnableLEConfig", test_audio_hal_l1_dsEnableLEConfig);
    UT_add_test( pSuite, "l1_dsGetLEConfig", test_audio_hal_l1_dsGetLEConfig);
    UT_add_test( pSuite, "l1_dsSetAudioEncoding", test_audio_hal_l1_dsSetAudioEncoding);
    UT_add_test( pSuite, "l1_dsSetAudioCompression", test_audio_hal_l1_dsSetAudioCompression);
    UT_add_test( pSuite, "l1_dsSetDialogEnhancement", test_audio_hal_l1_dsSetDialogEnhancement);
    UT_add_test( pSuite, "l1_dsSetDolbyVolumeMode", test_audio_hal_l1_dsSetDolbyVolumeMode);
    UT_add_test( pSuite, "l1_dsSetIntelligentEqualizerMode", test_audio_hal_l1_dsSetIntelligentEqualizerMode);
    UT_add_test( pSuite, "l1_dsSetVolumeLeveller", test_audio_hal_l1_dsSetVolumeLeveller);
    UT_add_test( pSuite, "l1_dsSetBassEnhancer", test_audio_hal_l1_dsSetBassEnhancer);
    UT_add_test( pSuite, "l1_dsEnableSurroundDecoder", test_audio_hal_l1_dsEnableSurroundDecoder);
    UT_add_test( pSuite, "l1_dsSetDRCMode", test_audio_hal_l1_dsSetDRCMode);
    UT_add_test( pSuite, "l1_dsSetSurroundVirtualizer", test_audio_hal_l1_dsSetSurroundVirtualizer);
    UT_add_test( pSuite, "l1_dsSetMISteering", test_audio_hal_l1_dsSetMISteering);
    UT_add_test( pSuite, "l1_dsSetGraphicEqualizerMode", test_audio_hal_l1_dsSetGraphicEqualizerMode);
    UT_add_test( pSuite, "l1_dsSetMS12AudioProfile", test_audio_hal_l1_dsSetMS12AudioProfile);
    UT_add_test( pSuite, "l1_dsSetStereoMode", test_audio_hal_l1_dsSetStereoMode);
    UT_add_test( pSuite, "l1_dsSetStereoAuto", test_audio_hal_l1_dsSetStereoAuto);
    UT_add_test( pSuite, "l1_dsSetAudioGain", test_audio_hal_l1_dsSetAudioGain);
    UT_add_test( pSuite, "l1_dsSetAudioDB", test_audio_hal_l1_dsSetAudioDB);
    UT_add_test( pSuite, "l1_dsSetAudioLevel", test_audio_hal_l1_dsSetAudioLevel);
    UT_add_test( pSuite, "l1_dsSetAudioDucking", test_audio_hal_l1_dsSetAudioDucking);
    UT_add_test( pSuite, "l1_dsEnableLoopThru", test_audio_hal_l1_dsEnableLoopThru);
    UT_add_test( pSuite, "l1_dsSetAudioMute", test_audio_hal_l1_dsSetAudioMute);
    UT_add_test( pSuite, "l1_dsIsAudioMSDecode", test_audio_hal_l1_dsIsAudioMSDecode);
    UT_add_test( pSuite, "l1_dsIsAudioMS12Decode", test_audio_hal_l1_dsIsAudioMS12Decode);
    UT_add_test( pSuite, "l1_dsSetAudioDelay", test_audio_hal_l1_dsSetAudioDelay);
    UT_add_test( pSuite, "l1_dsSetAudioDelayOffset", test_audio_hal_l1_dsSetAudioDelayOffset);
    UT_add_test( pSuite, "l1_dsAudioOutIsConnected", test_audio_hal_l1_dsAudioOutIsConnected);
    UT_add_test( pSuite, "l1_dsAudioOutRegisterConnectCB", test_audio_hal_l1_dsAudioOutRegisterConnectCB);
    UT_add_test( pSuite, "l1_dsAudioFormatUpdateRegisterCB", test_audio_hal_l1_dsAudioFormatUpdateRegisterCB);
    UT_add_test( pSuite, "l1_dsGetAudioCapabilities", test_audio_hal_l1_dsGetAudioCapabilities);
    UT_add_test( pSuite, "l1_dsGetMS12Capabilities", test_audio_hal_l1_dsGetMS12Capabilities);
    UT_add_test( pSuite, "l1_dsResetDialogEnhancement", test_audio_hal_l1_dsResetDialogEnhancement);
    UT_add_test( pSuite, "l1_dsResetBassEnhancer", test_audio_hal_l1_dsResetBassEnhancer);
    UT_add_test( pSuite, "l1_dsResetSurroundVirtualizer", test_audio_hal_l1_dsResetSurroundVirtualizer);
    UT_add_test( pSuite, "l1_dsResetVolumeLeveller", test_audio_hal_l1_dsResetVolumeLeveller);
    UT_add_test( pSuite, "l1_dsSetMS12AudioProfileSetttingsOverride", test_audio_hal_l1_dsSetMS12AudioProfileSetttingsOverride);
    UT_add_test( pSuite, "l1_dsSetAssociatedAudioMixing", test_audio_hal_l1_dsSetAssociatedAudioMixing);
    UT_add_test( pSuite, "l1_dsGetAssociatedAudioMixing", test_audio_hal_l1_dsGetAssociatedAudioMixing);
    UT_add_test( pSuite, "l1_dsSetFaderControl", test_audio_hal_l1_dsSetFaderControl);
    UT_add_test( pSuite, "l1_dsGetFaderControl", test_audio_hal_l1_dsGetFaderControl);
    UT_add_test( pSuite, "l1_dsSetPrimaryLanguage", test_audio_hal_l1_dsSetPrimaryLanguage);
    UT_add_test( pSuite, "l1_dsGetPrimaryLanguage", test_audio_hal_l1_dsGetPrimaryLanguage);
    UT_add_test( pSuite, "l1_dsSetSecondaryLanguage", test_audio_hal_l1_dsSetSecondaryLanguage);
    UT_add_test( pSuite, "l1_dsGetSecondaryLanguage", test_audio_hal_l1_dsGetSecondaryLanguage);
    UT_add_test( pSuite, "l1_dsGetHDMIARCPortId", test_audio_hal_l1_dsGetHDMIARCPortId);

    return 0;
}
