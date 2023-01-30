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
#include <dsHdmiIn.h>

/**
 * @brief This function will do the functional testing of dsHdmiInSelectPort() and verify its connection using dsHdmiInGetStatus.
 * This function will ensure underlying API implementation is handling
 * the invalid arguments passed and invalid call sequences to the API
 * dsERR_NONE : will be returned if dsHdmiInSelectPort () or dsHdmiInGetStatus () is called successfully.
 * dsERR_GENERAL: Not able to simulate this condition with the UT implementation
 */
void test_hdmiIn_hal_l1_dsHdmiInSelectPortVerifyConnection (void)
{
    dsError_t result=dsERR_GENERAL;
    dsHdmiInPort_t port = dsHDMI_IN_PORT_0;
    dsHdmiInStatus_t status;

    result = dsHdmiInSelectPort(port);
    UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

    /* Positive result */
    result = dsHdmiInInit();
    UT_ASSERT_EQUAL( result, dsERR_NONE );
    for (port = dsHDMI_IN_PORT_0; port < dsHDMI_IN_PORT_MAX; port++)
    {
        result = dsHdmiInSelectPort(port);
        UT_ASSERT_EQUAL( result, dsERR_NONE );

        result = dsHdmiInGetStatus(&status);
        UT_ASSERT_EQUAL( result, dsERR_INVALID_STATE );

        result = dsERR_GENERAL;
        if (status.isPortConnected[port]) {
            result = dsERR_NONE;
        }
        UT_ASSERT_EQUAL( result, dsERR_NONE );
    }
    
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
int test_HdmiIn_l2_register( void )
{
    /* add a suite to the registry */
    pSuite = UT_add_suite("[L2 test_HdmiIn_Example]", NULL, NULL);
    if (NULL == pSuite) 
    {
        return -1;
    }

    UT_add_test( pSuite, "l1_dsHdmiInSelectPortVerifyConnection", test_hdmiIn_hal_l1_dsHdmiInSelectPortVerifyConnection);

    return 0;
}
