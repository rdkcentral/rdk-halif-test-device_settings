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
#include <dsCompositeIn.h>
#include <ut.h>
#include <limits.h>

/**
 * @brief This function will do the unit testing of dsAudioPortInit ()
 * This function will ensure underlying API implementation is handling
 * invalid call sequences to the API
 * dsERR_NONE : will be returned if dsAudioPortInit () is called successfully.
 * dsERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_compositeIn_hal_l1_dsCompositeInInit(void)
{
    dsError_t result;
    /* Positive result */
    result = dsCompositeInInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    /*Second time init should pass*/
    result = dsCompositeInInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    result = dsCompositeInTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);

} 

/**
 * @brief This function will do the unit testing of dsCompositeInGetNumberOfInputs ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * dsERR_NONE : will be returned if dsCompositeInGetNumberOfInputs () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsCompositeInInit()
 * dsERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_compositeIn_hal_l1_dsCompositeInGetNumberOfInputs(void)
{
    dsError_t result;
    dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR;
    uint8_t numberOfInputs = 0;
    
    //Calling before init should fail.
    result = dsCompositeInGetNumberOfInputs(&numberOfInputs);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsCompositeInInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    result = dsCompositeInGetNumberOfInputs(&numberOfInputs);
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    
    result = dsCompositeInGetNumberOfInputs(NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    /*Terminating Audio Port*/
    result = dsCompositeInTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}


/**
 * @brief This function will do the unit testing of dsCompositeInGetStatus ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * dsERR_NONE : will be returned if dsCompositeInGetStatus () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsCompositeInInit()
 * dsERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_compositeIn_hal_l1_dsCompositeInGetStatus(void)
{
    dsError_t result;
    dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR;
    dsCompositeInStatus_t status;

    //Calling before init should fail.
    result = dsCompositeInGetStatus(&status);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsCompositeInInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    result = dsCompositeInGetStatus(&status);
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    
    result = dsCompositeInGetStatus(NULL);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    /*Terminating Audio Port*/
    result = dsCompositeInTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

/**
 * @brief This function will do the unit testing of dsCompositeInSelectPort ()
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * dsERR_NONE : will be returned if dsCompositeInSelectPort () is called successfully.
 * dsERR_INVALID_PARAM Indicates error due to invalid parameter value.
 * dsERR_INVALID_STATE : will be returned if this api is called before calling dsCompositeInInit()
 * dsERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_compositeIn_hal_l1_dsCompositeInSelectPort(void)
{
    dsError_t result;
    dsAudioPortType_t type = dsAUDIOPORT_TYPE_ID_LR;
    dsCompositeInStatus_t status;

    result = dsCompositeInSelectPort(0);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsCompositeInInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );

    for(dsCompositeInPort_t port; port>=dsCOMPOSITE_IN_PORT_MAX; port++)
    {
        result = dsCompositeInSelectPort(port);
        UT_ASSERT_EQUAL( result, dsERR_NONE );
    }

    result = dsCompositeInSelectPort(INT_MAX);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_PARAM );

    /*Terminating Audio Port*/
    result = dsCompositeInTerm();
    UT_ASSERT_EQUAL( result, dsERR_NONE);
}

static UT_test_suite_t *pSuite = NULL;

/**
 * @brief Register the main tests for this module
 * 
 * @return int - 0 on success, otherwise failure
 */
int CompositeIn_l1_register( void )
{
    /* add a suite to the registry */
    pSuite = UT_add_suite("[L1 CompositeIn]", NULL, NULL);
    if (NULL == pSuite) 
    {
        return -1;
    }

    UT_add_test( pSuite, "l1_dsCompositeInInit", test_compositeIn_hal_l1_dsCompositeInInit);
    UT_add_test( pSuite, "l1_dsCompositeInGetNumberOfInputs", test_compositeIn_hal_l1_dsCompositeInGetNumberOfInputs);
    UT_add_test( pSuite, "l1_dsCompositeInGetStatus", test_compositeIn_hal_l1_dsCompositeInGetStatus);
    UT_add_test( pSuite, "l1_dsCompositeInSelectPort", test_compositeIn_hal_l1_dsCompositeInSelectPort);

    return 0;
}
