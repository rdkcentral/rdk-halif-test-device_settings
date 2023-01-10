
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
#include <limits.h>

#include <ut.h>
#include "dsVideoPort.h"



void test_ds_video_hal_l1_init( void )
{
    int result;
    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    /*calling init second time should return error*/
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /*calling term should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_term( void )
{
    int result;

    /*calling ir_term before calling init, should return the invalid state error*/
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    /*calling term should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    /*Calling second time should fail*/
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );
    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_getVideoPort( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;

    //Calling api before open, should give invalid state
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );


    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    result = dsGetVideoPort(INT_MAX, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    
    result = dsGetVideoPort(type, INT_MAX, &handle);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    result = dsGetVideoPort(type, index, NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_isVideoPortEnabled( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    bool enabled = false;


    //Calling api before open, should give invalid state
    result = dsIsVideoPortEnabled(handle, &enabled);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsIsVideoPortEnabled(handle, &enabled);
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    result = dsIsVideoPortEnabled(NULL, &enabled);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    result = dsIsVideoPortEnabled(handle, NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    result = dsIsVideoPortEnabled(handle, &enabled);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_isDispalyConnected( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    bool connected = false;


    //Calling api before open, should give invalid state
    result = dsIsDisplayConnected(handle, &connected);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsIsDisplayConnected(handle, &connected);
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsIsDisplayConnected(NULL, &connected); //Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    //result = dsIsDisplayConnected(handle, NULL); //Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    result = dsIsDisplayConnected(handle, &connected);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_getSurrondMode( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    bool connected = false;


    //Calling api before open, should give invalid state
    result = dsIsDisplaySurround(handle, &connected);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsIsDisplayConnected(handle, &connected);
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsIsDisplaySurround(NULL, &connected); //Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    //result = dsIsDisplaySurround(handle, NULL); //Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    result = dsIsDisplaySurround(handle, &connected);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_isVideoPortActive( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    bool active = false;


    //Calling api before open, should give invalid state
    result = dsIsVideoPortActive(handle, &active);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsIsVideoPortActive(handle, &active);
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsIsVideoPortActive(NULL, &active); //Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    //result = dsIsVideoPortActive(handle, NULL);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    result = dsIsVideoPortActive(handle, &active);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_enableDTCP( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    bool contentProtect = true;


    //Calling api before open, should give invalid state
    result = dsEnableDTCP(handle, contentProtect);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsEnableDTCP(handle, false);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsEnableDTCP(handle, true);
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsEnableDTCP(NULL, contentProtect);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    result = dsEnableDTCP(handle, contentProtect);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_enableHDCP( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    bool contentProtect = true;
    size_t keySize = 3;
    char hdcpKey [] = {0, 0, 0};


    //Calling api before open, should give invalid state
    result = dsEnableHDCP(handle, contentProtect, hdcpKey, keySize);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsEnableHDCP(handle, true, hdcpKey, keySize);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsEnableHDCP(handle, false, hdcpKey, keySize);
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsEnableHDCP(NULL, contentProtect, hdcpKey, keySize);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    //result = dsEnableHDCP(NULL, contentProtect, NULL, keySize);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    //result = dsEnableHDCP(NULL, contentProtect, NULL, INT_MAX);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    result = dsEnableHDCP(handle, contentProtect, hdcpKey, keySize);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_isDTCPEnabled( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    bool pContentProtected = false;


    //Calling api before open, should give invalid state
    result = dsIsDTCPEnabled(handle, &pContentProtected);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsIsDTCPEnabled(handle, &pContentProtected);
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsIsDTCPEnabled(NULL, &pContentProtected);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    //result = dsIsDTCPEnabled(handle, NULL);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    result = dsIsDTCPEnabled(handle, &pContentProtected);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_isHDCPEnabled( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    bool pContentProtected = false;


    //Calling api before open, should give invalid state
    result = dsIsHDCPEnabled(handle, &pContentProtected);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsIsHDCPEnabled(handle, &pContentProtected);
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsIsHDCPEnabled(NULL, &pContentProtected);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    //result = dsIsHDCPEnabled(handle, NULL);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    result = dsIsHDCPEnabled(handle, &pContentProtected);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_enableVideoPort( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    bool enabled = true;


    //Calling api before open, should give invalid state
    result = dsEnableVideoPort(handle, enabled);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsEnableVideoPort(handle, true);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsEnableVideoPort(handle, false);
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsEnableVideoPort(NULL, enabled);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    result = dsEnableVideoPort(handle, true);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_setResolution( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    dsVideoPortResolution_t resolution;
    bool persist = true;

    //result = dsInitResolution (&resolution);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api before open, should give invalid state
    result = dsSetResolution(handle, &resolution, persist);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsSetResolution(handle, &resolution, false);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsSetResolution(handle, &resolution, true);
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsSetResolution(0, NULL, persist);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    //result = dsSetResolution(handle, NULL, persist);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    result = dsSetResolution(handle, &resolution, persist);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_getResolution( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    dsVideoPortResolution_t resolution;


    //Calling api before open, should give invalid state
    result = dsGetResolution(handle, &resolution);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsGetResolution(handle, &resolution);
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsGetResolution(handle, NULL);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    //result = dsGetResolution(0, &resolution);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    result = dsGetResolution(handle, &resolution);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_setActiveSoruce( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;


    //Calling api before open, should give invalid state
    //result = dsSetActiveSource(handle); //Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    //result = dsSetActiveSource(handle);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsSetActiveSource(0);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    //result = dsSetActiveSource(handle);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_initResolution( void )
{
    int result;
    dsVideoPortResolution_t resolution;


    //result = dsInitResolution (&resolution);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_dsHDCPStatusCallback (int handle, dsHdcpStatus_t status){
    printf ("Inside the callback %s", __FUNCTION__);
}

void test_ds_video_hal_l1_registerHdcpStatusCallback( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;


    //Calling api before open, should pass
    //result = dsRegisterHdcpStatusCallback(handle, test_ds_video_hal_dsHDCPStatusCallback); //Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    //result = dsRegisterHdcpStatusCallback(handle, test_ds_video_hal_dsHDCPStatusCallback);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //result = dsRegisterHdcpStatusCallback(handle, NULL);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //result = dsRegisterHdcpStatusCallback(0, test_ds_video_hal_dsHDCPStatusCallback);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    //result = dsRegisterHdcpStatusCallback(handle, test_ds_video_hal_dsHDCPStatusCallback);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}


void test_ds_video_hal_l1_getHDCPStatus( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    dsHdcpStatus_t status;


    //Calling api before open, should give invalid state
    //result = dsGetHDCPStatus(handle, &status);//Fixme: BCM symbol lookup error
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    //result = dsGetHDCPStatus(handle, &status);//Fixme: BCM symbol lookup error
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsGetHDCPStatus(handle, NULL);//Fixme: BCM crashing
    //UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    //result = dsGetHDCPStatus(0, &status);//Fixme: BCM crashing
    //UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    //result = dsGetHDCPStatus(handle, &status);//Fixme: BCM symbol lookup error
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_getHDCPProtocol( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    dsHdcpProtocolVersion_t protocolVersion;


    //Calling api before open, should give invalid state
    result = dsGetHDCPProtocol(handle, &protocolVersion);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsGetHDCPProtocol(handle, &protocolVersion);
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsGetHDCPProtocol(handle, NULL);//Fixme: BCM crashing
    //UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    //result = dsGetHDCPProtocol(0, &protocolVersion);//Fixme: BCM crashing
    //UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    result = dsGetHDCPReceiverProtocol(handle, &protocolVersion);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_getHDCPReceiverProtocol( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    dsHdcpProtocolVersion_t protocolVersion;


    //Calling api before open, should give invalid state
    result = dsGetHDCPReceiverProtocol(handle, &protocolVersion);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsGetHDCPReceiverProtocol(handle, &protocolVersion);
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsGetHDCPReceiverProtocol(handle, NULL);//Fixme: BCM crashing
    //UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    //result = dsGetHDCPReceiverProtocol(0, &protocolVersion);//Fixme: BCM crashing
    //UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    result = dsGetHDCPReceiverProtocol(handle, &protocolVersion);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_getHDCPCurrentProtocol( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    dsHdcpProtocolVersion_t protocolVersion;


    //Calling api before open, should give invalid state
    result = dsGetHDCPCurrentProtocol(handle, &protocolVersion);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsGetHDCPCurrentProtocol(handle, &protocolVersion);
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsGetHDCPCurrentProtocol(handle, NULL);//Fixme: BCM crashing
    //UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    //result = dsGetHDCPCurrentProtocol(0, &protocolVersion);//Fixme: BCM crashing
    //UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    result = dsGetHDCPCurrentProtocol(handle, &protocolVersion);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_getTVHDRCapabilities( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    int capabilities;


    //Calling api before open, should give invalid state
    result = dsGetTVHDRCapabilities(handle, &capabilities);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsGetTVHDRCapabilities(handle, &capabilities);
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsGetTVHDRCapabilities(handle, NULL);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    //result = dsGetTVHDRCapabilities(0, &capabilities);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    result = dsGetTVHDRCapabilities(handle, &capabilities);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_getSupportedTvResolutions( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    int resolutions;


    //Calling api before open, should give invalid state
    result = dsSupportedTvResolutions(handle, &resolutions);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsSupportedTvResolutions(handle, &resolutions);
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsSupportedTvResolutions(handle, NULL);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    //result = dsSupportedTvResolutions(0, &resolutions);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    result = dsSupportedTvResolutions(handle, &resolutions);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_setForceDisable4KSupport( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    bool disable = true;


    //Calling api before open, should give invalid state
    //result = dsSetForceDisable4KSupport(handle, disable);//Fixme: BCM symbol lookup error
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    //result = dsSetForceDisable4KSupport(handle, false);//Fixme: BCM symbol lookup error
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    //result = dsSetForceDisable4KSupport(handle, true);//Fixme: BCM symbol lookup error
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsSetForceDisable4KSupport(handle, NULL);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    //result = dsSetForceDisable4KSupport(0, disable);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    //result = dsSetForceDisable4KSupport(handle, disable);//Fixme: BCM symbol lookup error
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_getForceDisable4KSupport( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    bool disable = false;


    //Calling api before open, should give invalid state
    //result = dsGetForceDisable4KSupport(handle, &disable);//Fixme: BCM symbol lookup error
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    //result = dsGetForceDisable4KSupport(handle, &disable);//Fixme: BCM symbol lookup error
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsGetForceDisable4KSupport(handle, NULL);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    //result = dsGetForceDisable4KSupport(0, &disable);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    //result = dsGetForceDisable4KSupport(handle, &disable);//Fixme: BCM symbol lookup error
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_setScartParameter( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;//Fixme: give the scart as the type here
    int index = 0;
    const char* parameter_str = "param"; //Fixme: replace with right value
    const char* value_str = "value";//Fixme: repalce with right value


    //Calling api before open, should give invalid state
    //result = dsSetScartParameter(handle, parameter_str, value_str);//Fixme: BCM symbol lookup error
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    //result = dsSetScartParameter(handle, parameter_str, value_str);//Fixme: BCM symbol lookup error
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsSetScartParameter(handle, NULL, value_str);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    //result = dsSetScartParameter(handle, parameter_str, NULL);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    //result = dsSetScartParameter(0, parameter_str, value_str);//Fixme: BCM symbol lookup error
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    //result = dsSetScartParameter(handle, parameter_str, value_str);//Fixme: BCM symbol lookup error
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_getVideoEOTF( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    dsHDRStandard_t video_eotf;


    //Calling api before open, should give invalid state
    result = dsGetVideoEOTF(handle, &video_eotf);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsGetVideoEOTF(handle, &video_eotf);
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsGetVideoEOTF(handle, NULL);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    //result = dsGetVideoEOTF(0, &video_eotf);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    result = dsGetVideoEOTF(handle, &video_eotf);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_getMatrixCoefficients( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    dsDisplayMatrixCoefficients_t matrix_coefficients;


    //Calling api before open, should give invalid state
    result = dsGetMatrixCoefficients(handle, &matrix_coefficients);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsGetMatrixCoefficients(handle, &matrix_coefficients);
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsGetMatrixCoefficients(handle, NULL);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    //result = dsGetMatrixCoefficients(0, &matrix_coefficients);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    result = dsGetMatrixCoefficients(handle, &matrix_coefficients);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_getColorDepth( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    unsigned int color_depth = 0;


    //Calling api before open, should give invalid state
    result = dsGetColorDepth(handle, &color_depth);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsGetColorDepth(handle, &color_depth);
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsGetColorDepth(handle, NULL);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    //result = dsGetColorDepth(0, &color_depth);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    result = dsGetColorDepth(handle, &color_depth);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_getColorSpace( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    dsDisplayColorSpace_t color_space;


    //Calling api before open, should give invalid state
    result = dsGetColorSpace(handle, &color_space);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsGetColorSpace(handle, &color_space);
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsGetColorSpace(handle, NULL);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    //result = dsGetColorSpace(0, &color_space);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    result = dsGetColorSpace(handle, &color_space);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_getQuantizationRange( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    dsDisplayQuantizationRange_t quantization_range;


    //Calling api before open, should give invalid state
    result = dsGetQuantizationRange(handle, &quantization_range);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsGetQuantizationRange(handle, &quantization_range);
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsGetQuantizationRange(handle, NULL);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    //result = dsGetQuantizationRange(0, &quantization_range);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    result = dsGetQuantizationRange(handle, &quantization_range);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_getCurrentOutputSettings( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    dsHDRStandard_t video_eotf;
    dsDisplayMatrixCoefficients_t matrix_coefficients;
    dsDisplayColorSpace_t color_space;
    unsigned int color_depth;
    dsDisplayQuantizationRange_t quantization_range;


    //Calling api before open, should give invalid state
    result = dsGetCurrentOutputSettings(handle, &video_eotf, &matrix_coefficients, &color_space, &color_depth, &quantization_range);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsGetCurrentOutputSettings(handle, &video_eotf, &matrix_coefficients, &color_space, &color_depth, &quantization_range);
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsGetCurrentOutputSettings(handle, NULL, &matrix_coefficients, &color_space, &color_depth, &quantization_range);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);
    //result = dsGetCurrentOutputSettings(handle, &video_eotf, NULL, &color_space, &color_depth, &quantization_range);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);
    //result = dsGetCurrentOutputSettings(handle, &video_eotf, &matrix_coefficients, NULL, &color_depth, &quantization_range);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);
    //result = dsGetCurrentOutputSettings(handle, &video_eotf, &matrix_coefficients, &color_space, NULL, &quantization_range);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);
    //result = dsGetCurrentOutputSettings(handle, &video_eotf, &matrix_coefficients, &color_space, &color_depth, NULL);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    //result = dsGetCurrentOutputSettings(0, &video_eotf, &matrix_coefficients, &color_space, &color_depth, &quantization_range);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    result = dsGetCurrentOutputSettings(handle, &video_eotf, &matrix_coefficients, &color_space, &color_depth, &quantization_range);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_isOutputHDR( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    bool hdr = false;


    //Calling api before open, should give invalid state
    result = dsIsOutputHDR(handle, &hdr);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsIsOutputHDR(handle, &hdr);
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsIsOutputHDR(handle, NULL);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    //result = dsIsOutputHDR(0, &hdr);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    result = dsIsOutputHDR(handle, &hdr);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_resetOutputToSDR( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;


    //Calling api before open, should give invalid state
    //result = dsResetOutputToSDR();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    //result = dsResetOutputToSDR();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    //result = dsResetOutputToSDR();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_setHdmiPreference( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    dsHdcpProtocolVersion_t hdcpCurrentProtocol = 0;


    //Calling api before open, should give invalid state
    result = dsSetHdmiPreference(handle, &hdcpCurrentProtocol);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsSetHdmiPreference(handle, &hdcpCurrentProtocol);
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsSetHdmiPreference(handle, NULL);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    //result = dsSetHdmiPreference(0, &hdcpCurrentProtocol);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    result = dsSetHdmiPreference(handle, &hdcpCurrentProtocol);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_getHdmiPreference( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    dsHdcpProtocolVersion_t hdcpCurrentProtocol = 0;


    //Calling api before open, should give invalid state
    result = dsGetHdmiPreference(handle, &hdcpCurrentProtocol);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    //result = dsGetHdmiPreference(handle, &hdcpCurrentProtocol);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsGetHdmiPreference(handle, NULL);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    //result = dsGetHdmiPreference(0, &hdcpCurrentProtocol);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    result = dsGetHdmiPreference(handle, &hdcpCurrentProtocol);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_getIgnoreEDIDStatus( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    bool status = false;


    //Calling api before open, should give invalid state
    //result = dsGetIgnoreEDIDStatus(handle, &status);//Fixme: BCM symbol lookup error
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    //result = dsGetIgnoreEDIDStatus(handle, &status);//Fixme: BCM symbol lookup error
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsGetIgnoreEDIDStatus(handle, NULL);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    //result = dsGetIgnoreEDIDStatus(0, &status);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    //result = dsGetIgnoreEDIDStatus(handle, &status);//Fixme: BCM symbol lookup error
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_setBackgroundColor( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    dsVideoBackgroundColor_t color = 0;


    //Calling api before open, should give invalid state
    result = dsSetBackgroundColor(handle, color);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    result = dsSetBackgroundColor(handle, color);
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsSetBackgroundColor(0, color);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    result = dsSetBackgroundColor(handle, color);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_setForceHDRMode( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    dsHDRStandard_t mode = 0;


    //Calling api before open, should give invalid state
    //result = dsSetForceHDRMode(handle, mode);//Fixme: BCM symbol lookup error
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    //result = dsSetForceHDRMode(handle, mode);//Fixme: BCM symbol lookup error
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsSetForceHDRMode(0, mode);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    //result = dsSetForceHDRMode(handle, mode);//Fixme: BCM symbol lookup error
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_getColorDepthCapabilities( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    unsigned int colorDepthCapability = 0;


    //Calling api before open, should give invalid state
    //result = dsColorDepthCapabilities(handle, &colorDepthCapability);//Fixme: BCM symbol lookup error
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    //result = dsColorDepthCapabilities(handle, &colorDepthCapability);//Fixme: BCM symbol lookup error
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsColorDepthCapabilities(handle, NULL);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    //result = dsColorDepthCapabilities(0, &colorDepthCapability);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    //result = dsColorDepthCapabilities(handle, &colorDepthCapability);//Fixme: BCM symbol lookup error
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_getPreferredColorDepth( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    dsDisplayColorDepth_t colorDepth;
    bool persist = true;


    //Calling api before open, should give invalid state
    //result = dsGetPreferredColorDepth(handle, &colorDepth, persist);//Fixme: BCM symbol lookup error
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    //result = dsGetPreferredColorDepth(handle, &colorDepth, true);//Fixme: BCM symbol lookup error
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    //result = dsGetPreferredColorDepth(handle, &colorDepth, false);//Fixme: BCM symbol lookup error
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsGetPreferredColorDepth(handle, NULL, persist);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    //result = dsGetPreferredColorDepth(0, &colorDepth, persist);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    //result = dsGetPreferredColorDepth(handle, &colorDepth, persist);//Fixme: BCM symbol lookup error
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_video_hal_l1_setPreferredColorDepth( void )
{
    int result;
    int handle = 0;
    dsVideoPortType_t type = 0;
    int index = 0;
    dsDisplayColorDepth_t colorDepth=0;
    bool persist = true;


    //Calling api before open, should give invalid state
    //result = dsSetPreferredColorDepth(handle, colorDepth, persist);//Fixme: BCM symbol lookup error
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    //result = dsVideoPortInit ();//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVideoPort(type, index, &handle);
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    //result = dsSetPreferredColorDepth(handle, colorDepth, true);//Fixme: BCM symbol lookup error
    UT_ASSERT_EQUAL( result, dsERR_NONE);
    //result = dsSetPreferredColorDepth(handle, colorDepth, false);//Fixme: BCM symbol lookup error
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsSetPreferredColorDepth(0, colorDepth, persist);//Fixme: BCM crashing
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    result = dsVideoPortTerm ();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    //result = dsSetPreferredColorDepth(handle, colorDepth, persist);//Fixme: BCM symbol lookup error
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

static UT_test_suite_t *pSuite = NULL;

/**
 * @brief Register the main tests for this module
 * 
 * @return int - 0 on success, otherwise failure
 */
int test_l1_ds_videoport_register( void )
{
    /* add a suite to the registry */
    pSuite = UT_add_suite("[IR DS VideoPort L1 cases]", NULL, NULL);
    if (NULL == pSuite) 
    {
        return -1;
    }

    UT_add_test( pSuite, "video_init", test_ds_video_hal_l1_init);
    UT_add_test( pSuite, "video_term", test_ds_video_hal_l1_term);
    UT_add_test( pSuite, "video_getPort", test_ds_video_hal_l1_getVideoPort);
    UT_add_test( pSuite, "video_isPortEnabled", test_ds_video_hal_l1_isVideoPortEnabled);
    UT_add_test( pSuite, "video_isDispalyConnected", test_ds_video_hal_l1_isDispalyConnected);
    UT_add_test( pSuite, "video_getSurrondMode", test_ds_video_hal_l1_getSurrondMode);
    UT_add_test( pSuite, "video_isVideoPortActive", test_ds_video_hal_l1_isVideoPortActive);
    UT_add_test( pSuite, "video_enableDTCP", test_ds_video_hal_l1_enableDTCP);
    UT_add_test( pSuite, "video_enableHDCP", test_ds_video_hal_l1_enableHDCP);
    UT_add_test( pSuite, "video_isDTCPEnabled", test_ds_video_hal_l1_isDTCPEnabled);
    UT_add_test( pSuite, "video_isHDCPEnabled", test_ds_video_hal_l1_isHDCPEnabled);
    UT_add_test( pSuite, "video_enableVideoPort", test_ds_video_hal_l1_enableVideoPort);
    UT_add_test( pSuite, "video_setResolution", test_ds_video_hal_l1_setResolution);
    UT_add_test( pSuite, "video_getResolution", test_ds_video_hal_l1_getResolution);
    UT_add_test( pSuite, "video_setActiveSoruce", test_ds_video_hal_l1_setActiveSoruce);
    UT_add_test( pSuite, "video_initResolution", test_ds_video_hal_l1_initResolution);
    UT_add_test( pSuite, "video_registerHdcpStatusCallback", test_ds_video_hal_l1_registerHdcpStatusCallback);
    UT_add_test( pSuite, "video_getHDCPStatus", test_ds_video_hal_l1_getHDCPStatus);
    UT_add_test( pSuite, "video_getHDCPProtocol", test_ds_video_hal_l1_getHDCPProtocol);
    UT_add_test( pSuite, "video_getHDCPReceiverProtocol", test_ds_video_hal_l1_getHDCPReceiverProtocol);
    UT_add_test( pSuite, "video_getHDCPCurrentProtocol", test_ds_video_hal_l1_getHDCPCurrentProtocol);
    UT_add_test( pSuite, "video_getTVHDRCapabilities", test_ds_video_hal_l1_getTVHDRCapabilities);
    UT_add_test( pSuite, "video_getSupportedTvResolutions", test_ds_video_hal_l1_getSupportedTvResolutions);
    UT_add_test( pSuite, "video_setForceDisable4KSupport", test_ds_video_hal_l1_setForceDisable4KSupport);
    UT_add_test( pSuite, "video_getForceDisable4KSupport", test_ds_video_hal_l1_getForceDisable4KSupport);
    UT_add_test( pSuite, "video_setScartParameter", test_ds_video_hal_l1_setScartParameter);
    UT_add_test( pSuite, "video_getVideoEOTF", test_ds_video_hal_l1_getVideoEOTF);
    UT_add_test( pSuite, "video_getMatrixCoefficients", test_ds_video_hal_l1_getMatrixCoefficients);
    UT_add_test( pSuite, "video_getColorDepth", test_ds_video_hal_l1_getColorDepth);
    UT_add_test( pSuite, "video_getColorSpace", test_ds_video_hal_l1_getColorSpace);
    UT_add_test( pSuite, "video_getColorSpace", test_ds_video_hal_l1_getQuantizationRange);
    UT_add_test( pSuite, "video_getCurrentOutputSettings", test_ds_video_hal_l1_getCurrentOutputSettings);
    UT_add_test( pSuite, "video_isOutputHDR", test_ds_video_hal_l1_isOutputHDR);
    UT_add_test( pSuite, "video_resetOutputToSDR", test_ds_video_hal_l1_resetOutputToSDR);
    UT_add_test( pSuite, "video_setHdmiPreference", test_ds_video_hal_l1_setHdmiPreference);
    UT_add_test( pSuite, "video_getHdmiPreference", test_ds_video_hal_l1_getHdmiPreference);
    UT_add_test( pSuite, "video_getIgnoreEDIDStatus", test_ds_video_hal_l1_getIgnoreEDIDStatus);
    UT_add_test( pSuite, "video_setBackgroundColor", test_ds_video_hal_l1_setBackgroundColor);
    UT_add_test( pSuite, "video_setForceHDRMode", test_ds_video_hal_l1_setForceHDRMode);
    UT_add_test( pSuite, "video_getColorDepthCapabilities", test_ds_video_hal_l1_getColorDepthCapabilities);
    UT_add_test( pSuite, "video_getIgnoreEDIDStatus", test_ds_video_hal_l1_getPreferredColorDepth);
    UT_add_test( pSuite, "video_getIgnoreEDIDStatus", test_ds_video_hal_l1_setPreferredColorDepth);


    return 0;
}
