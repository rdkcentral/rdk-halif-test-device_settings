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
#include <dsVideoDevice.h>
#include <ut.h>

/**
 * @brief This function will do the unit testing of dsVideoDeviceInit ()
 * This function will ensure underlying API implementation is handling
 * invalid call sequences to the API
 * dsERR_NONE : will be returned if dsVideoDeviceInit () is called successfully.
 * dsERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_videodevice_hal_l1_init(void)
{
    dsError_t result;
    /* Positive result */
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    /*calling hdmicec_init second time should pass and return the valid pointer*/
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
} 

/**
 * @brief This function will do the unit testing of dsGetVideoDevice ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * dsERR_NONE : will be returned if dsGetVideoDevice () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsVideoDeviceInit()
 * dsERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_videodevice_hal_l1_dsGetVideoDevice(void)
{
    dsError_t result;
    int index = 0;
    int* handle = NULL;
    handle = malloc(sizeof(int));
    if(handle == NULL)
    {
        return;
    }

    result = dsGetVideoDevice(index,handle);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    result = dsGetVideoDevice(index,handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    /* Passing Invalid Parameter to the function*/
    index = -1;
    result = dsGetVideoDevice(index,handle);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );


    free(handle);
    handle = NULL;
    result = dsGetVideoDevice(index,handle);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );


    /*calling hdmicec_init second time should pass and return the valid pointer*/
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

} 

/**
 * @brief This function will do the unit testing of dsSetDFC ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * dsERR_NONE : will be returned if dsSetDFC () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsVideoDeviceInit()
 * dsERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_videodevice_hal_l1_dsSetDFC(void)
{
    dsError_t result;
    int index = 0;
    int handle = 0;

    result = dsSetDFC(handle,0);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    result = dsGetVideoDevice(index,&handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    for(dsVideoZoom_t i = dsVIDEO_ZOOM_FULL; i < dsVIDEO_ZOOM_MAX;i++)
    {    
        result = dsSetDFC(handle,i);
        UT_ASSERT_EQUAL( result, dsERR_NONE );
    }

    /* Passing Invalid Parameter to the function*/
    // Passing invalid index
    result = dsSetDFC(handle,dsVIDEO_ZOOM_NONE);
    UT_ASSERT_EQUAL( result, dsERR_OPERATION_NOT_SUPPORTED );

    result = dsSetDFC(handle,dsVIDEO_ZOOM_UNKNOWN);
    UT_ASSERT_EQUAL( result, dsERR_OPERATION_NOT_SUPPORTED );

    result = dsSetDFC(handle,dsVIDEO_ZOOM_MAX);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    handle = 0;
    result = dsSetDFC(handle,dsVIDEO_ZOOM_FULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    /*calling hdmicec_init second time should pass and return the valid pointer*/
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

}

/**
 * @brief This function will do the unit testing of dsGetDFC ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * dsERR_NONE : will be returned if dsGetDFC () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsVideoDeviceInit()
 * dsERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_videodevice_hal_l1_dsGetDFC(void)
{
    dsError_t result;
    int index = 0;
    int handle = 0;
    dsVideoZoom_t* dfc = NULL;

    dfc = malloc(sizeof(dsVideoZoom_t));
    if(dfc == NULL)
    {
        return;
    }

    result = dsGetDFC(handle,dfc);
    UT_ASSERT_EQUAL( result , dsERR_INVALID_STATE );

    /* Positive result */
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    result = dsGetVideoDevice(index,&handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    for(dsVideoZoom_t i = dsVIDEO_ZOOM_FULL; i < dsVIDEO_ZOOM_MAX;i++)
    {    
        result = dsSetDFC(handle,i);
        result = dsGetDFC(handle,dfc);
        UT_ASSERT_EQUAL( result , dsERR_NONE );
        UT_ASSERT_EQUAL( dfc, i );
    }

    /* Passing Invalid Parameter to the function*/
    // Passing invalid index
    
    result = dsGetDFC(0,dfc);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    free(dfc);
    dfc = NULL;
    result = dsGetDFC(handle,dfc);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    /*calling hdmicec_init second time should pass and return the valid pointer*/
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

}

/**
 * @brief This function will do the unit testing of dsGetHDRCapabilities ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * dsERR_NONE : will be returned if dsGetHDRCapabilities () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsVideoDeviceInit()
 * dsERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_videodevice_hal_l1_dsGetHDRCapabilities(void)
{
    dsError_t result;
    int capabilities = 0;
    int index = 0;
    int handle = 0;

    result = dsGetHDRCapabilities(handle,&capabilities);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    result = dsGetVideoDevice(index,&handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    result = dsGetHDRCapabilities(handle,&capabilities);
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    /* Passing Invalid Parameter to the function*/
    result = dsGetHDRCapabilities(NULL,&capabilities);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsGetHDRCapabilities(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    /*calling hdmicec_init second time should pass and return the valid pointer*/
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

} 

/**
 * @brief This function will do the unit testing of dsGetSupportedVideoCodingFormats ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * dsERR_NONE : will be returned if dsGetSupportedVideoCodingFormats () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsVideoDeviceInit()
 * dsERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_videodevice_hal_l1_dsGetSupportedVideoCodingFormats(void)
{
    dsError_t result;
    unsigned int supported_formats = 0;
    int index = 0;
    int handle = 0;

    result = dsGetSupportedVideoCodingFormats(handle,&supported_formats);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    result = dsGetVideoDevice(index,&handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    result = dsGetSupportedVideoCodingFormats(handle,&supported_formats);
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    /* Passing Invalid Parameter to the function*/
    result = dsGetSupportedVideoCodingFormats(NULL,&supported_formats);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsGetSupportedVideoCodingFormats(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    /*calling hdmicec_init second time should pass and return the valid pointer*/
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

} 

/**
 * @brief This function will do the unit testing of dsGetVideoCodecInfo ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * dsERR_NONE : will be returned if dsGetVideoCodecInfo () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsVideoDeviceInit()
 * dsERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_videodevice_hal_l1_dsGetVideoCodecInfo(void)
{
    dsError_t result;
    dsVideoCodingFormat_t code = dsVIDEO_CODEC_MPEG2;
    dsVideoCodecInfo_t info;
    int index = 0;
    int handle = 0;

    result = dsGetVideoCodecInfo(handle,code,&info);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    result = dsGetVideoDevice(index,&handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    code= dsVIDEO_CODEC_MPEG2;
    result = dsGetVideoCodecInfo(handle,code,&info);
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    code= dsVIDEO_CODEC_MPEGHPART2;
    result = dsGetVideoCodecInfo(handle,code,&info);
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    code= dsVIDEO_CODEC_MPEGHPART2;
    result = dsGetVideoCodecInfo(handle,code,&info);
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    /* Passing Invalid Parameter to the function*/
    result = dsGetVideoCodecInfo(NULL,code,&info);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    
    result = dsGetVideoCodecInfo(handle,0,&info);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsGetVideoCodecInfo(handle,0,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    /*calling hdmicec_init second time should pass and return the valid pointer*/
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

} 

/**
 * @brief This function will do the unit testing of dsForceDisableHDRSupport ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * dsERR_NONE : will be returned if dsForceDisableHDRSupport () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsVideoDeviceInit()
 * dsERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_videodevice_hal_l1_dsForceDisableHDRSupport(void)
{
    dsError_t result;
    int index = 0;
    int handle = 0;
    bool disableStatus = false;

    result = dsForceDisableHDRSupport(handle,disableStatus);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    result = dsGetVideoDevice(index,&handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    result = dsForceDisableHDRSupport(handle,disableStatus);
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    disableStatus = true;
    result = dsForceDisableHDRSupport(handle,disableStatus);
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    /* Passing Invalid Parameter to the function*/
    /*calling hdmicec_init second time should pass and return the valid pointer*/
    result = dsForceDisableHDRSupport(NULL,disableStatus);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

} 

/**
 * @brief This function will do the unit testing of dsSetFRFMode ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * dsERR_NONE : will be returned if dsSetFRFMode () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsVideoDeviceInit()
 * dsERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_videodevice_hal_l1_dsSetFRFMode(void)
{
    dsError_t result;
    int index = 0;
    int handle = 0;
    int frfMode = 0;

    result = dsSetFRFMode(handle,frfMode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    result = dsGetVideoDevice(index,&handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    result = dsSetFRFMode(handle,frfMode);
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    /* Passing Invalid Parameter to the function*/
    /*calling hdmicec_init second time should pass and return the valid pointer*/
    result = dsSetFRFMode(NULL,frfMode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsForceDisableHDRSupport(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

} 

/**
 * @brief This function will do the unit testing of dsGetFRFMode ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * dsERR_NONE : will be returned if dsGetFRFMode () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsVideoDeviceInit()
 * dsERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_videodevice_hal_l1_dsGetFRFMode(void)
{
    dsError_t result;
    int index = 0;
    int handle = 0;
    int frfMode = 0;

    result = dsGetFRFMode(handle,&frfMode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    result = dsGetVideoDevice(index,&handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    result = dsGetFRFMode(handle,&frfMode);
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    /* Passing Invalid Parameter to the function*/
    /*calling hdmicec_init second time should pass and return the valid pointer*/
    result = dsGetFRFMode(NULL,&frfMode);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsGetFRFMode(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

} 

/**
 * @brief This function will do the unit testing of dsGetCurrentDisplayframerate ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * dsERR_NONE : will be returned if dsGetCurrentDisplayframerate () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsVideoDeviceInit()
 * dsERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_videodevice_hal_l1_dsGetCurrentDisplayframerate(void)
{
    dsError_t result;
    int index = 0;
    int handle = 0;
    char frameRate[50] = {0};

    result = dsGetCurrentDisplayframerate(handle,frameRate);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    result = dsGetVideoDevice(index,&handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    result = dsGetCurrentDisplayframerate(handle,frameRate);
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    /* Passing Invalid Parameter to the function*/
    /*calling hdmicec_init second time should pass and return the valid pointer*/
    result = dsGetCurrentDisplayframerate(NULL,frameRate);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsGetCurrentDisplayframerate(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

} 

/**
 * @brief This function will do the unit testing of dsSetDisplayframerate ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * dsERR_NONE : will be returned if dsSetDisplayframerate () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsVideoDeviceInit()
 * dsERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_videodevice_hal_l1_dsSetDisplayframerate(void)
{
    dsError_t result;
    int index = 0;
    int handle = 0;
    char frameRate[50] = "FRAMERATE_DATA";

    result = dsSetDisplayframerate(handle,frameRate);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    result = dsGetVideoDevice(index,&handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    result = dsSetDisplayframerate(handle,frameRate);
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    /* Passing Invalid Parameter to the function*/
    /*calling hdmicec_init second time should pass and return the valid pointer*/
    result = dsSetDisplayframerate(NULL,frameRate);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsSetDisplayframerate(handle,NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

} 

static UT_test_suite_t *pSuite = NULL;



/**
 * @brief Register the main tests for this module
 * 
 * @return int - 0 on success, otherwise failure
 */
int videodevice_l1_register( void )
{
    /* add a suite to the registry */
    pSuite = UT_add_suite("[L1 Video Device]", NULL, NULL);
    if (NULL == pSuite) 
    {
        return -1;
    }

    UT_add_test( pSuite, "videodevice_level1_test_init"            , test_videodevice_hal_l1_init);
    UT_add_test( pSuite, "videodevice_level1_test_dsGetVideoDevice", test_videodevice_hal_l1_dsGetVideoDevice);
    UT_add_test( pSuite, "videodevice_level1_test_dsGetDFC"        , test_videodevice_hal_l1_dsGetDFC);
    UT_add_test( pSuite, "videodevice_level1_test_dsSetDFC"        , test_videodevice_hal_l1_dsSetDFC);
    UT_add_test( pSuite, "videodevice_level1_test_dsGetFRFMode"    , test_videodevice_hal_l1_dsGetFRFMode);
    UT_add_test( pSuite, "videodevice_level1_test_dsGetHDRCapabilities", test_videodevice_hal_l1_dsGetHDRCapabilities);
    UT_add_test( pSuite, "videodevice_level1_test_dsGetVideoDevice", test_videodevice_hal_l1_dsGetCurrentDisplayframerate);
    UT_add_test( pSuite, "videodevice_level1_test_dsGetVideoDevice", test_videodevice_hal_l1_dsGetVideoCodecInfo);
    UT_add_test( pSuite, "videodevice_level1_test_dsGetVideoDevice", test_videodevice_hal_l1_dsSetDisplayframerate);
    UT_add_test( pSuite, "videodevice_level1_test_dsGetVideoDevice", test_videodevice_hal_l1_dsSetFRFMode);
    UT_add_test( pSuite, "videodevice_level1_test_dsGetVideoDevice", test_videodevice_hal_l1_dsForceDisableHDRSupport);

    return 0;
}
