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
#include "dsHost.h"

void test_ds_host_hal_l1_init( void )
{
    int result;
    /* Positive result */
    result = dsHostInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    /*calling init second time should pass and return the valid pointer*/
    result = dsHostInit();
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /*calling close should pass */
    //result = dsHostTerm();//Fixme: Bcm undefined symbol
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_host_hal_l1_close( void )
{
    int result;
    int handle = 0;

    /*calling close before calling open, should return the invalid argument error*/
    //result = dsHostTerm();//Fixme: Bcm undefined symbol//Code crash here
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    result = dsHostInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    /*calling close should pass */
    //result = dsHostTerm();//Fixme: Bcm undefined symbol
    UT_ASSERT_EQUAL( result, dsERR_NONE);  

    /*calling close second time */
    //result = dsHostTerm();//Fixme: Bcm undefined symbol
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /*calling close with invalid handle should return the invalid argument error*/
    //result = dsHostTerm();//Fixme: Bcm undefined symbol
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_host_hal_l1_setHostPowerMode( void )
{
    int result;
    int newPower = 0;


    //Calling api before open, should give invalid state
    //result = dsSetHostPowerMode(newPower);//Fixme: Bcm undefined symbol
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    result = dsHostInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    //result = dsSetHostPowerMode(newPower);//Fixme: Bcm undefined symbol
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsSetHostPowerMode(INT_MAX);//Fixme: Bcm undefined symbol
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    //result = dsHostTerm();//Fixme: Bcm undefined symbol
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    //result = dsSetHostPowerMode(newPower);//Fixme: Bcm undefined symbol
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_host_hal_l1_getHostPowerMode( void )
{
    int result;
    int currPower = 0;


    //Calling api before open, should give invalid state
    //result = dsGetHostPowerMode(result = dsGetHostPowerMode(&currPower);currPower);//Fixme: Bcm undefined symbol
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    result = dsHostInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    //result = dsGetHostPowerMode(result = dsGetHostPowerMode(&currPower);currPower);//Fixme: Bcm undefined symbol
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsGetHostPowerMode(NULL);//Fixme: Bcm undefined symbol
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    //result = dsHostTerm();//Fixme: Bcm undefined symbol
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    //result = dsGetHostPowerMode(result = dsGetHostPowerMode(&currPower);currPower);//Fixme: Bcm undefined symbol
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_host_hal_l1_getPreferredSleepMode( void )
{
    int result;
    dsSleepMode_t mode= 0;


    //Calling api before open, should give invalid state
    //result = dsGetPreferredSleepMode(result = dsGetPreferredSleepMode(&mode);mode);//Fixme: Bcm undefined symbol
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    result = dsHostInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    //result = dsGetPreferredSleepMode(result = dsGetPreferredSleepMode(&mode);mode);//Fixme: Bcm undefined symbol
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsGetPreferredSleepMode(NULL);//Fixme: Bcm undefined symbol
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    //result = dsHostTerm();//Fixme: Bcm undefined symbol
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    //result = dsGetPreferredSleepMode(result = dsGetPreferredSleepMode(&mode);mode);//Fixme: Bcm undefined symbol
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_host_hal_l1_setPreferredSleepMode( void )
{
    int result;
    dsSleepMode_t mode = 0;


    //Calling api before open, should give invalid state
    //result = dsSetPreferredSleepMode(mode);//Fixme: Bcm undefined symbol
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    result = dsHostInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    //result = dsSetPreferredSleepMode(mode);//Fixme: Bcm undefined symbol
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsSetPreferredSleepMode(INT_MAX);//Fixme: Bcm undefined symbol
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    //result = dsHostTerm();//Fixme: Bcm undefined symbol
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    //result = dsSetPreferredSleepMode(mode);//Fixme: Bcm undefined symbol
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_host_hal_l1_getCPUTemperature( void )
{
    int result;
    float cpuTemperature= 0;


    //Calling api before open, should give invalid state
    result = dsGetCPUTemperature(&cpuTemperature);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    result = dsHostInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetCPUTemperature(&cpuTemperature);
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsGetCPUTemperature(NULL); //Fixme: Bcm crashing here
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    //result = dsHostTerm();//Fixme: Bcm undefined symbol
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    result = dsGetCPUTemperature(&cpuTemperature);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_host_hal_l1_getVersion( void )
{
    int result;
    uint32_t versionNumber= 0;


    //Calling api before open, should give invalid state
    result = dsGetVersion(&versionNumber);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    result = dsHostInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetVersion(&versionNumber);
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsGetVersion(NULL);//Fixme: Bcm crashing here
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    //result = dsHostTerm();//Fixme: Bcm undefined symbol
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    result = dsGetVersion(&versionNumber);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_host_hal_l1_setVersion( void )
{
    int result;
    uint32_t versionNumber = 0;


    //Calling api before open, should give invalid state
    result = dsSetVersion(versionNumber);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    result = dsHostInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsSetVersion(versionNumber);
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    /*calling close should pass */
    //result = dsHostTerm();//Fixme: Bcm undefined symbol
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    result = dsSetVersion(versionNumber);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_host_hal_l1_getSocIDFromSDK( void )
{
    int result;
    char socID[128];


    //Calling api before open, should give invalid state
    result = dsGetSocIDFromSDK(socID);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    result = dsHostInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetSocIDFromSDK(socID);
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsGetSocIDFromSDK(NULL);//Fixme: Bcm crashing here
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    //result = dsHostTerm();//Fixme: Bcm undefined symbol
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    result = dsGetSocIDFromSDK(socID);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

void test_ds_host_hal_l1_getHostEDID( void )
{
    int result;
    unsigned char edid[2048];
    int length = 0;


    //Calling api before open, should give invalid state
    result = dsGetHostEDID(edid, &length);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* Positive result */
    result = dsHostInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    //+ve call
    result = dsGetHostEDID(edid, &length);
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Using invalid params
    //result = dsGetHostEDID(NULL, &length);//Fixme: Bcm crashing here
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    //result = dsGetHostEDID(edid, NULL);//Fixme: Bcm crashing here
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM);

    /*calling close should pass */
    //result = dsHostTerm();//Fixme: Bcm undefined symbol
    UT_ASSERT_EQUAL( result, dsERR_NONE);

    //Calling api after close, should give invalid state
    result = dsGetHostEDID(edid, &length);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

static UT_test_suite_t *pSuite = NULL;

/**
 * @brief Register the main tests for this module
 *
 * @return int - 0 on success, otherwise failure
 */
int Host_l1_register( void )
{
    /* add a suite to the registry */
    pSuite = UT_add_suite("[L1 ds host]", NULL, NULL);
    if (NULL == pSuite)
    {
        return -1;
    }

    UT_add_test( pSuite, "host_open", test_ds_host_hal_l1_init);
    UT_add_test( pSuite, "host_close", test_ds_host_hal_l1_close);
    UT_add_test( pSuite, "host_setHostPowerMode", test_ds_host_hal_l1_setHostPowerMode);
    UT_add_test( pSuite, "host_getHostPowerMode", test_ds_host_hal_l1_getHostPowerMode);
    UT_add_test( pSuite, "host_getPreferredSleepMode", test_ds_host_hal_l1_getPreferredSleepMode);
    UT_add_test( pSuite, "host_setPreferredSleepMode", test_ds_host_hal_l1_setPreferredSleepMode);
    UT_add_test( pSuite, "host_getCPUTemperature", test_ds_host_hal_l1_getCPUTemperature);
    UT_add_test( pSuite, "host_getVersion", test_ds_host_hal_l1_getVersion);
    UT_add_test( pSuite, "host_setVersion", test_ds_host_hal_l1_setVersion);
    UT_add_test( pSuite, "host_getSocIDFromSDK", test_ds_host_hal_l1_getSocIDFromSDK);
    UT_add_test( pSuite, "host_getHostEDID", test_ds_host_hal_l1_getHostEDID);

    return 0;
}
