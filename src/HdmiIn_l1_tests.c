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
#include <dsHdmiIn.h>
#include <ut.h>


void test_hdmiIn_hal_l1_dsHdmiInInit(void)
{
    dsError_t result;
    /* Positive result */
    result = dsHdmiInInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    /*calling hdmicec_init second time should pass and return the valid pointer*/
    result = dsHdmiInTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

}

void test_hdmiIn_hal_l1_dsHdmiInGetNumberOfInputs(void)
{
    dsError_t result;
    uint8_t count;
    /* Positive result */
    result = dsHdmiInInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    
    result = dsHdmiInGetNumberOfInputs(&count);
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    
    result = dsHdmiInGetNumberOfInputs(NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    /*Terminating Display*/
    result = dsHdmiInTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

void test_hdmiIn_hal_l1_dsHdmiInGetStatus(void)
{
    dsError_t result;
    dsHdmiInStatus_t status;
    /* Positive result */
    result = dsHdmiInInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    
    result = dsHdmiInGetStatus(&status);
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    
    result = dsHdmiInGetStatus(NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    /*Terminating Display*/
    result = dsHdmiInTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

void test_hdmiIn_hal_l1_dsHdmiInSelectPort(void)
{
    dsError_t result;
    dsHdmiInPort_t port;
    /* Positive result */
    result = dsHdmiInInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    for (port = dsHDMI_IN_PORT_0; port < dsHDMI_IN_PORT_MAX; port++)
    {
        result = dsHdmiInSelectPort(port);
        UT_ASSERT_EQUAL( result, dsERR_NONE );
    }
    
    result = dsHdmiInSelectPort(NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    result = dsHdmiInSelectPort(dsHDMI_IN_PORT_NONE);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    result = dsHdmiInSelectPort(dsHDMI_IN_PORT_MAX);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    /*Terminating Display*/
    result = dsHdmiInTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

void test_hdmiIn_hal_l1_dsHdmiInScaleVideo(void)
{
    dsError_t result;
    int32_t x=0, y=0, width =1920, height =1080;
    /* Positive result */
    result = dsHdmiInInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    result = dsHdmiInScaleVideo(x,y,width,height);    
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    result = dsHdmiInScaleVideo(-1,y,width,height);    
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);
    result = dsHdmiInScaleVideo(x,-1,width,height);    
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);
    result = dsHdmiInScaleVideo(x,y,-1,height);    
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);
    result = dsHdmiInScaleVideo(x,y,width,-1);    
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);
    /*Terminating Display*/
    result = dsHdmiInTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

void test_hdmiIn_hal_l1_dsHdmiInSelectZoomMode(void)
{
    dsError_t result;
    dsVideoZoom_t zoom;
    /* Positive result */
    result = dsHdmiInInit();    
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    for(zoom = dsVIDEO_ZOOM_NONE; zoom < dsVIDEO_ZOOM_MAX; zoom++)
    {
        result = dsHdmiInSelectZoomMode(zoom);
        UT_ASSERT_EQUAL( result, dsERR_NONE );
    }
    result = dsHdmiInSelectZoomMode( dsVIDEO_ZOOM_UNKNOWN);    
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);
    result = dsHdmiInSelectZoomMode(NULL);    
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);
    /*Terminating Display*/
    result = dsHdmiInTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

void test_hdmiIn_hal_l1_dsHdmiInPauseAudio(void)
{
    dsError_t result;
    /* Positive result */
    result = dsHdmiInInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    result = dsHdmiInPauseAudio();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    /*calling hdmicec_init second time should pass and return the valid pointer*/
    result = dsHdmiInTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

}

void test_hdmiIn_hal_l1_dsHdmiInResumeAudio(void)
{
    dsError_t result;
    /* Positive result */
    result = dsHdmiInInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    result = dsHdmiInResumeAudio();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    /*calling hdmicec_init second time should pass and return the valid pointer*/
    result = dsHdmiInTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

}

void test_hdmiIn_hal_l1_dsHdmiInGetCurrentVideoMode(void)
{
    dsError_t result;
    dsVideoPortResolution_t resolution;
    /* Positive result */
    result = dsHdmiInInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    
    result = dsHdmiInGetCurrentVideoMode(&resolution);
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    
    result = dsHdmiInGetCurrentVideoMode(NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );
    /*Terminating Display*/
    result = dsHdmiInTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

static UT_test_suite_t *pSuite = NULL;

/**
 * @brief Register the main tests for this module
 * 
 * @return int - 0 on success, otherwise failure
 */
int HdmiIn_l1_register( void )
{
    /* add a suite to the registry */
    pSuite = UT_add_suite("[L1 HdmiIn]", NULL, NULL);
    if (NULL == pSuite) 
    {
        return -1;
    }

    UT_add_test( pSuite, "HdmiIn_level1_test_func", test_HdmiIn_hal_l1_func);
    UT_add_test( pSuite, "HdmiIn_level1_test_func", test_HdmiIn_hal_l1_func1);
    UT_add_test( pSuite, "HdmiIn_level1_test_func", test_HdmiIn_hal_l1_func2);

    return 0;
}
