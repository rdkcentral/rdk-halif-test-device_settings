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
 * @addtogroup HPK Hardware deviceing Kit
 * @{
 * @par The Hardware deviceing Kit
 * HPK is the next evolution of the well-defined Hardware Abstraction Layer
 * (HAL), but augmented with more comprehensive documentation and test suites
 * that OEM or SOC vendors can use to self-certify their devices before taking
 * them to RDKM for validation or to an operator for final integration and
 * deployment. The Hardware deviceing Kit effectively enables an OEM and/or SOC
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
 * @defgroup DS_CompositeIn_HALTEST Device Settings Composite Input HAL Tests
 * @{
 */

/**
 * @defgroup DS_CompositeIn_HALTEST_L3 Device Settings Composite Input HAL Tests L3 File
 * @{
 * @parblock
 *
 * ### L3 Tests for DS Composite Input HAL :
 *
 * Level 3 test cases for all APIs of Device Settings Composite Input HAL
 *
 * **Pre-Conditions:**  None@n
 * **Dependencies:** None@n
 *
 * Refer to API Definition specification documentation : [ds-composite-in_halSpec.md](../../docs/pages/ds-composite-in_halSpec.md)
 *
 * @endparblock
 */

/**
 * @file test_l3_dsVideoDevice.c
 *
 */

#include <stdlib.h>
#include <stdbool.h>
#include <ut.h>
#include <ut_log.h>
#include <ut_kvp_profile.h>
#include <ut_kvp.h>

#include "test_parse_configuration.h"
#include "dsCompositeIn.h"

/* Global Variables */
static int32_t gTestGroup = 3;
static int32_t gTestID    = 1;

static bool                    gConnectionStatus = false;
static dsCompInSignalStatus_t  gSignalStatus  = dsCOMP_IN_SIGNAL_STATUS_NONE;
static dsCompositeInStatus_t        gStatusChange;

/* Type Definitions */
typedef struct _ut_control_keyMapTable_t
{
    char* string;
    int32_t key;
} ut_control_keyMapTable_t;

/* Mapping table for dsError_t */
const static ut_control_keyMapTable_t dsError_mapTable [] = {
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

/* Mapping table for dsCompInSignalStatus_t */
const static ut_control_keyMapTable_t dsCompInSignalStatusMappingTable[] = {
    {"dsCOMP_IN_SIGNAL_STATUS_NONE", (int32_t)dsCOMP_IN_SIGNAL_STATUS_NONE},
    {"dsCOMP_IN_SIGNAL_STATUS_NOSIGNAL", (int32_t)dsCOMP_IN_SIGNAL_STATUS_NOSIGNAL},
    {"dsCOMP_IN_SIGNAL_STATUS_UNSTABLE", (int32_t)dsCOMP_IN_SIGNAL_STATUS_UNSTABLE},
    {"dsCOMP_IN_SIGNAL_STATUS_NOTSUPPORTED", (int32_t)dsCOMP_IN_SIGNAL_STATUS_NOTSUPPORTED},
    {"dsCOMP_IN_SIGNAL_STATUS_STABLE", (int32_t)dsCOMP_IN_SIGNAL_STATUS_STABLE},
    {"dsCOMP_IN_SIGNAL_STATUS_MAX", (int32_t)dsCOMP_IN_SIGNAL_STATUS_MAX},
    {NULL, -1}
};

/* Mapping table for dsCompositeInPort_t */
const static ut_control_keyMapTable_t dsCompositeInPortMappingTable[] = {
    {"dsCOMPOSITE_IN_PORT_NONE", (int32_t)dsCOMPOSITE_IN_PORT_NONE},
    {"dsCOMPOSITE_IN_PORT_0", (int32_t)dsCOMPOSITE_IN_PORT_0},
    {"dsCOMPOSITE_IN_PORT_1", (int32_t)dsCOMPOSITE_IN_PORT_1},
    {"dsCOMPOSITE_IN_PORT_MAX", (int32_t)dsCOMPOSITE_IN_PORT_MAX},
    {NULL, -1}
};


/* Mapping table for boolean values */
const static ut_control_keyMapTable_t bool_mapTable [] = {
  { "false", (int32_t)false },
  { "true",  (int32_t)true  },
  {  NULL, -1 }
};

/**
 * @brief This functions gets the Enum mapping string.
 *
 * This functions gets the Enum mapping string.
 * &Todo: replace with ut control function
 */
static char* ut_control_GetMapString(const ut_control_keyMapTable_t *conversionMap, int32_t key)
{
    int32_t count = 0;
    while(conversionMap[count].string != NULL){
        if(conversionMap[count].key == key) {
            return conversionMap[count].string;
        }
        count++;
    }
    return "";
}

/**
 * @brief This function clears the stdin buffer.
 *
 * This function clears the stdin buffer.
 */
void readAndDiscardRestOfLine(FILE* in)
{
   int c;
   while ( (c = fgetc(in)) != EOF && c != '\n');
}

/**
*
*This function read the input from the stdin.
*/
void readInput(int *choice)
{
    scanf("%d",choice);
    readAndDiscardRestOfLine(stdin);
}

/**
 * @brief Callback function for Composite Input hot plug status.
 *
 * This function is invoked whenever a change occurs in the Composite Input connection.
 */
static void compositeInConnectCB(dsCompositeInPort_t Port, bool isPortConnected)
{
    UT_LOG_INFO("Received Connection status callback port: %s, Connection: %s",
                 ut_control_GetMapString(dsCompositeInPortMappingTable, Port),
                 ut_control_GetMapString(bool_mapTable, isPortConnected));

    gConnectionStatus = isPortConnected;
}

/**
 * @brief Callback function for CompositeIn signal change.
 *
 * This function is invoked whenever a signal change occurs in the Comosite Input connection.
 */
static void compositeInSignalChangeCB(dsCompositeInPort_t port, dsCompInSignalStatus_t sigStatus)
{
    UT_LOG_INFO("Received SignalChange status callback port: %s, sigstatus: %s",
                 ut_control_GetMapString(dsCompositeInPortMappingTable, port),
                 ut_control_GetMapString(dsCompInSignalStatusMappingTable, sigStatus));

    gSignalStatus = sigStatus;
}

/**
 * @brief Callback function for CompositeIn status change.
 *
 * This function is invoked whenever a status change occurs in the CompositeIn connection.
 */
static void compositeInStatusChangeCB(dsCompositeInStatus_t inputStatus)
{
    UT_LOG_INFO("Received statuschange callback isPresented: %s, activeport: %s",
                 ut_control_GetMapString(bool_mapTable, inputStatus.isPresented),
                 ut_control_GetMapString(dsCompositeInPortMappingTable, inputStatus.activePort));

    for(int i = 0 ; i < dsCOMPOSITE_IN_PORT_MAX ; i++) {

         if(!(inputStatus.isPresented))
                 continue;

         UT_LOG_INFO("Received statuschange callback isPortConnected: %s, activeport: %s",
                 ut_control_GetMapString(bool_mapTable, inputStatus.isPortConnected[i]),
                 ut_control_GetMapString(dsCompositeInPortMappingTable, inputStatus.activePort));
    }

    gStatusChange = inputStatus;
}

/**
* @brief This test initializes the CompositeIn Module.
*
* This test function initializes the CompositeIn Module.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 001@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [dsCompositeIn_L3_Low-Level_TestSpecification.md](../docs/pages/ds-compositeIn_L3_Low-Level_TestSpecification.md)
*/
void test_l3_CompositeIn_initialize(void)
{
    gTestID = 1;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;

    /* Initialize the CompositeIn Module */
    UT_LOG_INFO("Calling dsCompositeInInit()");
    ret = dsCompositeInInit();
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsCompositeInInit() dsError_t:[%s]", ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsCompositeInInit() dsError_t:[%s]", ut_control_GetMapString(dsError_mapTable, ret));
    }

    /* Register connection status callback */
    UT_LOG_INFO("Calling dsCompositeInRegisterConnectCB(CBFunc:[0x%0X])", compositeInConnectCB);
    ret = dsCompositeInRegisterConnectCB(compositeInConnectCB);
    if (ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsCompositeInRegisterConnectCB(CBFunc:[0x%0X]) dsError_t:[%s]",
                        compositeInConnectCB, ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsCompositeInRegisterConnectCB(CBFunc:[0x%0X]) dsError_t:[%s]",
                        compositeInConnectCB, ut_control_GetMapString(dsError_mapTable, ret));
    }

    /* Register Signal change callback */
    UT_LOG_INFO("Calling dsCompositeInRegisterSignalChangeCB(cbFun:[0x%0X])", compositeInSignalChangeCB);
    ret = dsCompositeInRegisterSignalChangeCB(compositeInSignalChangeCB);
    if (ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsCompositeInRegisterSignalChangeCB(cbFun:[0x%0X]) dsError_t:[%s]",
                        compositeInSignalChangeCB, ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsCompositeInRegisterSignalChangeCB(cbFun:[0x%0X]) dsError_t:[%s]",
                        compositeInSignalChangeCB, ut_control_GetMapString(dsError_mapTable, ret));
    }

    /* Register Status change callback */
    UT_LOG_INFO("Calling dsCompositeInRegisterStatusChangeCB(cbFun:[0x%0X])", compositeInStatusChangeCB);
    ret = dsCompositeInRegisterStatusChangeCB(compositeInStatusChangeCB);
    if (ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsCompositeInRegisterStatusChangeCB(cbFun:[0x%0X]) dsError_t:[%s]",
                        compositeInStatusChangeCB, ut_control_GetMapString(dsError_mapTable, ret));
    }
    else {
        UT_LOG_INFO("Result dsCompositeInRegisterStatusChangeCB(cbFun:[0x%0X]) dsError_t:[%s]",
                        compositeInStatusChangeCB, ut_control_GetMapString(dsError_mapTable, ret));
    }

    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test get number of input ports.
*
* This test function gets Composite Input ports on platform.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 002@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [dsCompositeIn_L3_Low-Level_TestSpecification.md](../docs/pages/ds-compositeIn_L3_Low-Level_TestSpecification.md)
*/
void test_l3_CompositeIn_get_inputports(void)
{
    gTestID = 2;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    uint8_t numInputs = 0;
    dsError_t ret   = dsERR_NONE;

    UT_LOG_INFO("Calling dsCompositeInGetNumberOfInputs");
    ret = dsCompositeInGetNumberOfInputs(&numInputs);
    if(ret != dsERR_NONE)
    {
       UT_LOG_ERROR("Result: Failed to Get NumberOfInputsPorts:[%s]",ut_control_GetMapString(dsError_mapTable, ret));
    } 
    UT_LOG_INFO("Result: NumberOfInputsPorts:[%d]",numInputs);
    if(!numInputs)
        UT_LOG_INFO("Result: Platform does not supports CompositeIn Ports");

    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test get status of CompositeIn ports.
*
* This test function gets status of CompositeIn ports on platform.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 003@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [dsCompositeIn_L3_Low-Level_TestSpecification.md](../docs/pages/ds-compositeIn_L3_Low-Level_TestSpecification.md)
*/
void test_l3_CompositeIn_get_status(void)
{
    gTestID = 3;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret   = dsERR_NONE;
    dsCompositeInStatus_t inputstatus;

    UT_LOG_INFO("Calling dsCompositeInGetStatus");
    ret = dsCompositeInGetStatus(&inputstatus);
    if(ret != dsERR_NONE)
    {
        UT_LOG_ERROR("Result: Failed to Get Composite input port status:[%s]",ut_control_GetMapString(dsError_mapTable, ret));
    } 
    UT_LOG_INFO("Result Composite input port status isPresented: %s, activeport: %s",
                ut_control_GetMapString(bool_mapTable, inputstatus.isPresented),
                ut_control_GetMapString(dsCompositeInPortMappingTable, inputstatus.activePort));

    for(int i = 0 ; i < dsCOMPOSITE_IN_PORT_MAX ; i++) {

        if(!(inputstatus.isPresented))
            continue;

        UT_LOG_INFO("Result: CompositeIn port connected info isPortConnected: %s, activeport: %s",
                    ut_control_GetMapString(bool_mapTable, inputstatus.isPortConnected[i]),
                    ut_control_GetMapString(dsCompositeInPortMappingTable, inputstatus.activePort));
    }

    UT_LOG_INFO("Out %s", __FUNCTION__);
}

/**
* @brief This test to select port.
*
* This test function selects CompositeIn port on platform.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 004@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [dsCompositeIn_L3_Low-Level_TestSpecification.md](../docs/pages/ds-compositeIn_L3_Low-Level_TestSpecification.md)
*/
void test_l3_CompositeIn_select_port(void)
{
    gTestID = 4;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret   = dsERR_NONE;
    dsCompositeInPort_t port = dsCOMPOSITE_IN_PORT_MAX;
    int32_t select; 
    uint8_t numInputPorts = 0;

    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsCompositeIn/composite_input_configurations/number_of_ports");

    printf(" \n================Please Select Inputs==================\n");

    printf("\n*******Enter the port number to select*******\n");
    readInput(&select);

    if(select <= 0 || select > numInputPorts) 
    {
       UT_LOG_ERROR("\nInvalid port selected\n");
    }

    port = (dsCompositeInPort_t)select;

    ret = dsCompositeInSelectPort(port);
    if(ret != dsERR_NONE)
    {
       UT_LOG_ERROR("Result: Failed to select the Composite input port:[%s]",ut_control_GetMapString(dsError_mapTable, ret));
    }
    UT_LOG_INFO("Result : dsCompositeInSelectPort: %s, portnumber: %d",
                ut_control_GetMapString(dsCompositeInPortMappingTable, port), port);
}

/**
* @brief This test to scale video.
*
* This test function is to scale video of selected CompositeIn port on platform.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 005@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [dsCompositeIn_L3_Low-Level_TestSpecification.md](../docs/pages/ds-compositeIn_L3_Low-Level_TestSpecification.md)
*/
void test_l3_CompositeIn_scale_video(void)
{
    gTestID = 5;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret   = dsERR_NONE;
    int32_t x = 0 , y = 0, width = 0 , height = 0;

    printf(" \n================Please Select Inputs==================\n");

    printf("\n*******Enter the x coordinate to select*******\t"
                     "Acceptable inputs are:\t"
                     "Min is 0\t"
                     "Max is based on the current resolution\t"
              "**********************************************\n");
   readInput(&x);
   if(x < 0)
   {
      UT_LOG_ERROR("\n invalid x coordinate selected \n");
   }

   printf("\n*******Enter the y coordinate to select*******\t"
                     "Acceptable inputs are:\t"
                     "Min is 0\t"
                     "Max is based on the current resolution\t"
             "**********************************************\n");
   readInput(&y);
   if(y < 0)
   {
      UT_LOG_ERROR("\n invalid y coordinate selected \n");
   }

   printf("\n*******Enter the width to select***************\t"
                     "Acceptable inputs are:\t"
                     "Min is 0\t"
                     "Max is based on the current resolution\t"
            "**********************************************\n");
   readInput(&width);
   if(width < 0)
   {
      UT_LOG_ERROR("\n invalid width selected \n");
   }

   printf("\n*******Enter the height to select**************\t"
                     "Acceptable inputs are:\t"
                     "Min is 0\t"
                     "Max is based on the current resolution\t"
             "**********************************************\n");
   readInput(&height);
   if(height < 0)
   {
      UT_LOG_ERROR("\n invalid height selected \n");
   }

  ret = dsCompositeInScaleVideo(x, y, width, height);
  if(ret != dsERR_NONE)
  {
     UT_LOG_ERROR("Result: Failed to dsCompositeInScaleVideo:[%s]",ut_control_GetMapString(dsError_mapTable, ret));
  }
    UT_LOG_INFO("Result : Passed dsCompositeInScaleVideo paramsx : %d, y : %d, heitht : %d , width : %d",
                x, y , width, height);
}

/**
* @brief This test terminates the dsCompositeIn.
*
* This test function terminates the dsCompositeIn.
*
* **Test Group ID:** 03@n
* **Test Case ID:** 018@n
*
* **Test Procedure:**
* Refer to Test specification documentation
* [dsCompositeIn_L3_Low-Level_TestSpecification.md](../docs/pages/ds-compositeIn_L3_Low-Level_TestSpecification.md)
*/
void test_l3_dsCompositeIn_terminate(void)
{
    gTestID = 18;
    UT_LOG_INFO("In %s [%02d%03d]", __FUNCTION__, gTestGroup, gTestID);

    dsError_t ret = dsERR_NONE;

    UT_LOG_INFO("Calling dsCompositeInTerm()");
    ret = dsCompositeInTerm();
    if(ret != dsERR_NONE) {
        UT_LOG_ERROR("Failed dsCompositeInTerm() dsError_t:[%s]", ut_control_GetMapString(dsError_mapTable, ret));
    }
    UT_LOG_INFO("Result dsCompositeInTerm() dsError_t:[%s]", ut_control_GetMapString(dsError_mapTable, ret));

    UT_LOG_INFO("Out %s", __FUNCTION__);
}

static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main tests for this module
 *
 * @return int - 0 on success, otherwise failure
 */

int test_l3_dsCompositeIn_register(void)
{
    ut_kvp_status_t status = UT_KVP_STATUS_SUCCESS;

    status = ut_kvp_getStringField(ut_kvp_profile_getInstance(), "dsCompositeIn.Type", gDeviceType, TEST_DS_DEVICE_TYPE_SIZE);
    if (status != UT_KVP_STATUS_SUCCESS ) {
        UT_ASSERT_FATAL(status);
    } else {
        if (!strncmp(gDeviceType, TEST_TYPE_SINK_VALUE, TEST_DS_DEVICE_TYPE_SIZE)) {
            // Create the test suite for sink type
            pSuite = UT_add_suite_withGroupID("[L3 dsCompositeIn - Sink]", NULL, NULL, UT_TESTS_L3);
            assert( pSuite != NULL );
        }
        else {
            UT_LOG_ERROR("Invalid platform type: %s", gDeviceType);
            return -1;
        }
    }

    UT_add_test( pSuite, "Initialize CompositeIn" ,test_l3_CompositeIn_initialize );
    UT_add_test( pSuite, "Get input ports" ,test_l3_CompositeIn_get_inputports );
    UT_add_test( pSuite, "Get status of ports" ,test_l3_CompositeIn_get_status );
    UT_add_test( pSuite, "Select the input port" ,test_l3_CompositeIn_select_port );
    UT_add_test( pSuite, "Scale the compositeIn video" ,test_l3_CompositeIn_scale_video );
    UT_add_test( pSuite, "Terminate CompositeIn" ,test_l3_dsCompositeIn_terminate );


    return 0;
}

/** @} */ // End of DS_CompositeIn_HALTEST_L3
/** @} */ // End of DS_CompositeIn_HALTEST
/** @} */ // End of Device_Settings_HALTEST
/** @} */ // End of Device_Settings
/** @} */ // End of HPK
