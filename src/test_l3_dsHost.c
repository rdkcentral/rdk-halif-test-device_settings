/**
*  If not stated otherwise in this file or this component's LICENSE
*  file the following copyright and licenses apply:
*
*  Copyright 2024 RDK Management
*
*  Licensed under the Apache License, Version 2.0 (the License);
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*  http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an AS IS BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*/

/**
 * @addtogroup HPK Hardware Porting Kit
 * @{
 * @par The Hardware Porting Kit
 * HPK is the next evolution of the well-defined Hardware Abstraction Layer
 * (HAL), but augmented with more comprehensive documentation and test suites
 * that OEM or SOC vendors can use to self-certify their ports before taking
 * them to RDKM for validation or to an operator for final integration and
 * deployment. The Hardware Porting Kit effectively enables an OEM and/or SOC
 * vendor to self-certify their own Video Accelerator devices, with minimal RDKM
 * assistance.
 *
 */

/**
 * @addtogroup Device_Settings Device Settings Module
 * @{
 */

/**
 * @addtogroup Device_Settings_HALTEST Device Settings HAL Tests
 * @{
 */

/**
 * @defgroup DS_Host_HALTEST Device Settings Host HAL Tests
 * @{
 */

/**
 * @defgroup DS_Host_HALTEST_L2 Device Settings Host HAL Tests L2 File
 * @{
 * @parblock
 *
 * ### L2 Tests for DS Host HAL :
 *
 * Level 2 unit test cases for all APIs of Device Settings Host HAL
 *
 * **Pre-Conditions:**  None@n
 * **Dependencies:** None@n
 *
 * Refer to API Definition specification documentation : [ds-host_halSpec.md](../../docs/pages/ds-host_halSpec.md)
 *
 * @endparblock
 */


/**
 * @file test_l2_dsAudio.c
 *
 */
#include <ut.h>
#include <ut_log.h>
#include <ut_kvp_profile.h>
#include "dsHost.h"
#include "test_parse_configuration.h"

#define DSHOST_SOC_LENGTH    20
#define DS_HOST_KVP_SIZE     128

static int gTestGroup = 2;
static int gTestID = 1;

int prevTemp = 0;


/* dsError_t */
const static ut_control_keyStringMapping_t dsError_mapTable [] = {
  { "dsERR_NONE",                    (int32_t)dsERR_NONE                    },
  { "dsERR_GENERAL",                 (int32_t)dsERR_GENERAL                 },
  { "dsERR_INVALID_PARAM",           (int32_t)dsERR_INVALID_PARAM           },
  { "dsERR_INVALID_STATE",           (int32_t)dsERR_INVALID_STATE           },
  { "dsERR_ALREADY_INITIALIZED",     (int32_t)dsERR_ALREADY_INITIALIZED     },
  { "dsERR_NOT_INITIALIZED",         (int32_t)dsERR_NOT_INITIALIZED         },
  { "dsERR_OPERATION_NOT_SUPPORTED", (int32_t)dsERR_OPERATION_NOT_SUPPORTED },
  { "dsERR_RESOURCE_NOT_AVAILABLE",  (int32_t)dsERR_RESOURCE_NOT_AVAILABLE  },
  { "dsERR_OPERATION_FAILED",        (int32_t)dsERR_OPERATION_FAILED        },
  { "dsErr_MAX",                     (int32_t)dsErr_MAX                     },
  {  NULL, -1 }
};

/**
* @brief Initialization of the HAL dsHost Module
*
* This test provides a scope to open the HAL dsHost module.
*
* **Test Group ID:** 03@n
*
* **Test Case ID:** 001@n
*
* **Pre-Conditions:** None@n
*
* **Dependencies:** None@n
*
* **User Interaction:** @n
* User or Automation tool should select the Test 1 to before running any test.
*
*/
void test_l3_dsHost_hal_Init(void)
{
   gTestID = 1;
   dsError_t status = dsERR_NONE ;

   UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

   // Step 1: Call dsHostInit()
   status = dsHostInit();
   UT_LOG_INFO("Result dsHostInit: dsError_t:[%s]",
                 UT_Control_GetMapString(dsError_mapTable, status));

    UT_ASSERT_EQUAL_FATAL(status, dsERR_NONE);

   UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief getTemperature of the HAL dsHost Module
*
* This test provides a scope to test the get Temperature function.
*
* **Test Group ID:** 03@n
*
* **Test Case ID:** 002@n
*
* **Pre-Conditions:** None@n
*
* **Dependencies:** None@n
*
* **User Interaction:** @n
* User or Automation tool should select the Test 1 to before running any test.
*
*/
void test_l3_dsHost_hal_get_Temperature(void)
{
   gTestID = 2;
   dsError_t status = dsERR_NONE ;

   float cpuTemperature = 0;

   UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

   // Step 1: Call dsGetCPUTemperature()
   status = dsGetCPUTemperature(&cpuTemperature);
   UT_LOG_INFO("Result dsGetCPUTemperature: dsError_t:[%s]",
                 UT_Control_GetMapString(dsError_mapTable, status));
    UT_LOG_INFO("CPU Temperature: %f\n", cpuTemperature);

    UT_ASSERT_EQUAL_FATAL(status, dsERR_NONE);

   if(prevTemp == 0)
   {
       prevTemp = cpuTemperature;
   }
   else
   {
       if(cpuTemperature <= prevTemp +2 || cpuTemperature >= prevTemp -2)
       {
           UT_LOG_ERROR("Temperature is not same as previous value within reasonable variability. 
                        PrevTemp: %d, currentTemp: %d\n", prevTemp, cpuTemperature);
           UT_ASSERT_EQUAL_FATAL(cpuTemperature, prevTemp);
       }
   }

   UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief getSocID of the HAL dsHost Module
*
* This test provides a scope to test the get SoCId function.
*
* **Test Group ID:** 03@n
*
* **Test Case ID:** 003@n
*
* **Pre-Conditions:** None@n
*
* **Dependencies:** None@n
*
* **User Interaction:** @n
* User or Automation tool should select the Test 1 to before running any test.
*
*/
void test_l3_dsHost_hal_get_SocID(void)
{
   gTestID = 3;
   dsError_t status = dsERR_NONE ;

   char socID[DSHOST_SOC_LENGTH] = {0};

   UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

   // Step 1: Call dsGetSoCId()
   status = dsGetSoCId(socID, DSHOST_SOC_LENGTH);
   UT_LOG_INFO("Result dsGetSoCId: dsError_t:[%s]",
                 UT_Control_GetMapString(dsError_mapTable, status));
    UT_LOG_INFO("SoC ID: %s\n", socID);

    UT_ASSERT_EQUAL_FATAL(status, dsERR_NONE);

   UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief hostEdid of the HAL dsHost Module
*
* This test provides a scope to test the get hostEdid function.
*
* **Test Group ID:** 03@n
*
* **Test Case ID:** 004@n
*
* **Pre-Conditions:** None@n
*
* **Dependencies:** None@n
*
* **User Interaction:** @n
* User or Automation tool should select the Test 1 to before running any test.
*
*/
void test_l3_dsHost_hal_get_hostEdid(void)
{
   gTestID = 4;
   dsError_t status = dsERR_NONE ;

   char hostEdid[DS_HOST_KVP_SIZE] = {0};

   UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

   // Step 1: Call dsGetHostEDID()
   status = dsGetHostEDID(hostEdid, DS_HOST_KVP_SIZE);
   UT_LOG_INFO("Result dsGetHostEDID: dsError_t:[%s]",
                 UT_Control_GetMapString(dsError_mapTable, status));
    UT_LOG_INFO("Host EDID: %s\n", hostEdid);

    UT_ASSERT_EQUAL_FATAL(status, dsERR_NONE);

   UT_LOG_INFO("Out %s\n", __FUNCTION__);
}

/**
* @brief Initialization of the HAL dsHost Module
*
* This test provides a scope to terminate the HAL dsHost module.
*
* **Test Group ID:** 03@n
*
* **Test Case ID:** 005@n
*
* **Pre-Conditions:** None@n
*
* **Dependencies:** None@n
*
* **User Interaction:** @n
* User or Automation tool should select the Test 1 to before running any test.
*
*/
void test_l3_dsHost_hal_Term(void)
{
   gTestID = 5;
   dsError_t status = dsERR_NONE ;

   UT_LOG_INFO("In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

   // Step 1: Call dsHostTerm()
   status = dsHostTerm();
   UT_LOG_INFO("Result dsHostTerm: dsError_t:[%s]",
                 UT_Control_GetMapString(dsError_mapTable, status));

    UT_ASSERT_EQUAL_FATAL(status, dsERR_NONE);

   UT_LOG_INFO("Out %s\n", __FUNCTION__);
}


static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main tests for this module
 *
 * @return int - 0 on success, otherwise failure
 */
int test_register_dsHost_hal_l3_tests(void)
{
    // Create the test suite
    pSuite = UT_add_suite("[L3 dsHost Functions] ", NULL, NULL);
    if (pSuite == NULL)
    {
        return -1;
    }
    // List of test function names and strings

    UT_add_test( pSuite, "L3_Init_dsHost", test_l3_dsHost_hal_Init);
    UT_add_test( pSuite, "L3_GetTemperature", test_l3_dsHost_hal_get_Temperature);
    UT_add_test( pSuite, "L3_GetSocID", test_l3_dsHost_hal_get_SocID);
    UT_add_test( pSuite, "L3_GetHostEdid", test_l3_dsHost_hal_get_hostEdid);
    UT_add_test( pSuite, "L3_Term_dsHost", test_l3_dsHost_hal_Term);

    return 0;
}

/** @} */ // End of DS_Host_HALTEST_L2
/** @} */ // End of DS_Host_HALTEST
/** @} */ // End of Device_Settings_HALTEST
/** @} */ // End of Device_Settings
/** @} */ // End of HPK