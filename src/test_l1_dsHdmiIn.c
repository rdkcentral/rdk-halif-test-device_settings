/**
*  If not stated otherwise in this file or this component's LICENSE
*  file the following copyright and licenses apply:
*
*  Copyright 2022 RDK Management
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
 * @defgroup DS_HDMIIn_HALTEST Device Settings HDMI Input HAL Tests
 * @{
 */

/**
 * @defgroup DS_HDMIIn_HALTEST_L1 Device Settings HDMI Input HAL Tests L1 File
 * @{
 * @parblock
 *
 * ### L1 Tests for DS HDMI Input HAL :
 *
 * Level 1 unit test cases for all APIs of Device Settings HDMI Input HAL
 *
 * **Pre-Conditions:**  None@n
 * **Dependencies:** None@n
 *
 * Refer to API Definition specification documentation : [ds-hdmi-in_halSpec.md](../../docs/pages/ds-hdmi-in_halSpec.md)
 * @endparblock
 */


/**
 * @file test_l1_dsHdmiIn.c
 *
 */

#include <string.h>
#include <stdlib.h>
#include "dsHdmiIn.h"

#include <ut.h>
#include <ut_log.h>
#include <ut_kvp_profile.h>
#include "test_parse_configuration.h"

static int gTestGroup = 1;
static int gTestID = 1;

#define CHECK_FOR_EXTENDED_ERROR_CODE( result, enhanced, old )\
{\
   if ( extendedEnumsSupported == true )\
   {\
      UT_ASSERT_EQUAL( enhanced, result );\
   }\
   else\
   {\
       UT_ASSERT_EQUAL( old, result );\
   }\
}

/* Global flags to support features */
static bool extendedEnumsSupported=false; //Default to not supported

/**
 * @brief Ensure dsHdmiInInit() correctly initializes the HDMI input sub-system during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 001@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | dsERR_NONE | Should Pass |
 * |02|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after initialization |
 * |03|Call dsHdmiInInit() again | | dsERR_NONE | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after initialization |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInInit(void) {
    gTestID = 1;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 3: Call dsHdmiInInit() again
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 4: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsHdmiInInit() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 002@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Call dsHdmiInInit() again without terminating the HDMI input sub-system | | dsERR_ALREADY_INITIALIZED | Should Pass |
 * |03|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 * @note Testing for the `dsERR_GENERAL` and `dsERR_RESOURCE_NOT_AVAILABLE` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 */
void test_l1_dsHdmiIn_negative_dsHdmiInInit(void) {
    gTestID = 2;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Call dsHdmiInInit() again without terminating the HDMI input sub-system
    dsError_t result = dsHdmiInInit();
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_ALREADY_INITIALIZED, dsERR_NONE);

    // Step 3: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsHdmiInTerm() correctly terminates the HDMI input sub-system during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 003@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after initialization |
 * |03|Call dsHdmiInInit() again | | dsERR_NONE | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after initialization |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInTerm(void) {
    gTestID = 3;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 3: Call dsHdmiInInit() again
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 4: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsHdmiInTerm() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 004@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsHdmiInTerm() without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after initialization |
 * |04|Call dsHdmiInTerm() without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing for the `dsERR_GENERAL` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInTerm(void) {
    gTestID = 4;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    // Step 1: Call dsHdmiInTerm() without initializing the HDMI input sub-system
    dsError_t result = dsHdmiInTerm();
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 4: Call dsHdmiInTerm() without initializing the HDMI input sub-system
    result = dsHdmiInTerm();
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsHdmiInGetNumberOfInputs() correctly fetches the number of HDMI input ports during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 005@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Get the number of input ports from the profile file
 * |02|Call dsHdmiInGetNumberOfInputs() to fetch the number of HDMI input ports |pNumberOfinputs: uint8_t*| dsERR_NONE | Number should be between 0 and max number of inputs defined in dsHdmiInPort_t |
 * |03|Retrieve the expected number of HDMI input ports from the profile file and compare it with the number obtained from dsHdmiInGetNumberOfInputs() |
 * |04|Call dsHdmiInGetNumberOfInputs() to fetch the number of HDMI input ports |dsERR_OPERATION_NOT_SUPPORTED |For source devices without HDMI input support | 
 * |05|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInGetNumberOfInputs(void) {
    gTestID = 5;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    uint8_t numInputs;
    uint8_t numInputPorts = 0;
    
    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Get the number of input ports from the profile file
    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/HdmiInputPort/numberOfPorts");
    if (numInputPorts > 0) {

       // Step 3: Call dsHdmiInGetNumberOfInputs() to fetch the number of HDMI input ports
       UT_ASSERT_EQUAL(dsHdmiInGetNumberOfInputs(&numInputs), dsERR_NONE);

       // Step 4: Verify that the number of HDMI input ports obtained matches the expected value from the profile
       UT_ASSERT_KVP_EQUAL_PROFILE_UINT8(numInputs, "dsHdmiIn/HdmiInputPort/numberOfPorts");
    } else {
       // Step 5: For source devices without HDMI input support
       UT_ASSERT_EQUAL(dsHdmiInGetNumberOfInputs(&numInputs), 0);
    }

    // Step 6: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsHdmiInGetNumberOfInputs() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 006@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsHdmiInGetNumberOfInputs() without initializing the HDMI input sub-system |pNumberOfinputs: uint8_t*| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsHdmiInGetNumberOfInputs() with NULL as the parameter |pNumberOfinputs: NULL| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |05|Call dsHdmiInGetNumberOfInputs() after termination of the HDMI input sub-system |pNumberOfinputs: uint8_t*| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInGetNumberOfInputs(void) {
    gTestID = 6;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    uint8_t numInputs;

    // Step 1: Call dsHdmiInGetNumberOfInputs() without initializing the HDMI input sub-system
    dsError_t result = dsHdmiInGetNumberOfInputs(&numInputs);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsHdmiInGetNumberOfInputs() with NULL as the parameter
    UT_ASSERT_EQUAL(dsHdmiInGetNumberOfInputs(NULL),dsERR_INVALID_PARAM);

    // Step 4: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 5: Call dsHdmiInGetNumberOfInputs() after termination of the HDMI input sub-system
    result = dsHdmiInGetNumberOfInputs(&numInputs);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsHdmiInGetStatus() correctly fetches the HDMI input port status during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 007@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Get the number of input ports from the profile file
 * |03|Call dsHdmiInGetStatus() with valid pointer |dsHdmiInStatus_t*| dsERR_NONE | Status information should be populated. Validate the output structure |
 * |04|Call dsHdmiInGetStatus() with valid pointer |dsHdmiInStatus_t*| dsERR_NONE | Status information should be populated. Validate the output structure |
 * |05|Compare the returned values to make sure they are equal || Success | The values should be the same |
 * |06|Call dsHdmiInGetStatus() with valid pointer |dsHdmiInStatus_t*| dsERR_OPERATION_NOT_SUPPORTED | For source devices without HDMI input support |
 * |07|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInGetStatus(void) {
    gTestID = 7;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    dsHdmiInStatus_t status1, status2;
    uint8_t numInputPorts = 0;

    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Get the number of input ports from the profile file
    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/HdmiInputPort/numberOfPorts");
    if (numInputPorts > 0) {
        // Step 3: Call dsHdmiInGetStatus()
        UT_ASSERT_EQUAL(dsHdmiInGetStatus(&status1), dsERR_NONE);

        // Step 4: Call dsHdmiInGetStatus() again
        UT_ASSERT_EQUAL(dsHdmiInGetStatus(&status2), dsERR_NONE);

        // Step 5: Compare the returned values to make sure they are equal
        UT_ASSERT_EQUAL(status1.isPresented, status2.isPresented);
        UT_ASSERT_EQUAL(status1.activePort, status2.activePort);
        for (int i = 0; i < dsHDMI_IN_PORT_MAX; i++) {
             UT_LOG("\n In %s Comparing isPresented:[%d,%d]\n", __FUNCTION__, status1.isPresented, status2.isPresented); 
             UT_LOG("\n In %s Comparing activePort:[%d,%d]\n", __FUNCTION__, status1.activePort, status2.activePort); 
             UT_LOG("\n In %s Comparing isPortConnected:[%d,%d]\n", __FUNCTION__, status1.isPortConnected[i], status2.isPortConnected[i]); 
             UT_ASSERT_EQUAL(status1.isPortConnected[i], status2.isPortConnected[i]);
        }
    } else {
      // Step 6: For source devices without hdmi input support
      UT_ASSERT_EQUAL(dsHdmiInGetStatus(&status1), dsERR_OPERATION_NOT_SUPPORTED);
    }

    // Step 7: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsHdmiInGetStatus() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 008@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsHdmiInGetStatus() without initializing the HDMI input sub-system |dsHdmiInStatus_t*| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsHdmiInGetStatus() with NULL as the parameter |NULL| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |05|Call dsHdmiInGetStatus() after terminating the HDMI input sub-system |dsHdmiInStatus_t*| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInGetStatus(void) {
    gTestID = 8;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    dsHdmiInStatus_t status;

    // Step 1: Call dsHdmiInGetStatus() without initializing the HDMI input sub-system
    dsError_t result = dsHdmiInGetStatus(&status);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsHdmiInGetStatus() with NULL as the parameter
    UT_ASSERT_EQUAL(dsHdmiInGetStatus(NULL),dsERR_INVALID_PARAM);

    // Step 4: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 5: Call dsHdmiInGetStatus() after terminating the HDMI input sub-system
    result = dsHdmiInGetStatus(&status);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsHdmiInSelectPort() correctly selects an HDMI input port during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 009@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Get the number of input ports from the profile file
 * |03|Call dsHdmiInSelectPort() |dsHDMI_IN_PORT_0, bool: false, dsVideoPlane_PRIMARY, bool false| dsERR_NONE | Port 0 should be selected |
 * |04|Call dsHdmiInSelectPort() |dsHDMI_IN_PORT_1, bool: true, dsVideoPlane_SECONDARY, bool true| dsERR_NONE | Port 1 should be selected |
 * |05|Call dsHdmiInSelectPort() |dsHDMI_IN_PORT_2, bool: false, dsVideoPlane_PRIMARY, bool false| dsERR_NONE | Port 2 should be selected |
 * |06||Call dsHdmiInSelectPort() | dsERR_OPERATION_NOT_SUPPORTED | Loop through the ports where HDMI input is not supported
 * |07|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInSelectPort(void) {
    gTestID = 9;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    uint8_t numInputPorts = 0;

    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Get the number of input ports from the profile file
    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/HdmiInputPort/numberOfPorts");
    if (numInputPorts > 0) {
       
        for (uint8_t i = dsHDMI_IN_PORT_0; i < numInputPorts; i++)
        {
             // Step 3: Call dsHdmiInSelectPort() to select Port 0
             UT_ASSERT_EQUAL(dsHdmiInSelectPort(i, false, dsVideoPlane_PRIMARY, false), dsERR_NONE);

             // Step 4: Call dsHdmiInSelectPort() to select Port 1
             UT_ASSERT_EQUAL(dsHdmiInSelectPort(i, true, dsVideoPlane_SECONDARY, true), dsERR_NONE);
      
             // Step 5: Call dsHdmiInSelectPort() to select Port 2
             UT_ASSERT_EQUAL(dsHdmiInSelectPort(i, false, dsVideoPlane_PRIMARY, false), dsERR_NONE);
       }
    } else {
       
	for (uint8_t i =  numInputPorts; i < dsHDMI_IN_PORT_MAX; i++)
        {
             // Step 6: Call dsHdmiInSelectPort() 
	     UT_ASSERT_EQUAL(dsHdmiInSelectPort(i, false, dsVideoPlane_PRIMARY, false), dsERR_OPERATION_NOT_SUPPORTED);
        }
    }
     
    // Step 7: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsHdmiInSelectPort() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 010@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsHdmiInSelectPort() without initializing the HDMI input sub-system |dsHDMI_IN_PORT_0, bool: false, dsVideoPlane_PRIMARY, bool: false| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Get the number of input ports from the profile file
 * |04|Call dsHdmiInSelectPort() with invalid value |dsHDMI_IN_PORT_MAX, bool: false, dsVideoPlane_PRIMARY, bool: false| dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsHdmiInSelectPort() with invalid plane value |dsHDMI_IN_PORT_0, bool: false, dsVideoPlane_MAX, bool: true| dsERR_INVALID_PARAM | Should Pass |
 * |06|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |07|Call dsHdmiInSelectPort() after terminating the HDMI input sub-system |dsHDMI_IN_PORT_0, bool: false, dsVideoPlane_PRIMARY, bool: false| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInSelectPort(void) {
    gTestID = 10;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    uint8_t numInputPorts = 0;

    // Step 1: Call dsHdmiInSelectPort() without initializing the HDMI input sub-system
    dsError_t result = dsHdmiInSelectPort(dsHDMI_IN_PORT_0, false, dsVideoPlane_PRIMARY, false);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_INVALID_PARAM);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Get the number of input ports from the profile file
    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/HdmiInputPort/numberOfPorts");
    for (uint8_t i = dsHDMI_IN_PORT_0; i < numInputPorts; i++)
    {
	  // Step 4: Call dsHdmiInSelectPort() with an invalid value
          UT_ASSERT_EQUAL(dsHdmiInSelectPort(i, false, dsVideoPlane_PRIMARY, false), dsERR_INVALID_PARAM);

          // Step 5: Call dsHdmiInSelectPort() with an invalid plane value
          UT_ASSERT_EQUAL(dsHdmiInSelectPort(i, false, dsVideoPlane_MAX, false), dsERR_INVALID_PARAM);
    }
	
    // Step 6: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 7: Call dsHdmiInSelectPort() after terminating the HDMI input sub-system
    result = dsHdmiInSelectPort(dsHDMI_IN_PORT_0, false, dsVideoPlane_PRIMARY, false);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_INVALID_PARAM);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsHdmiInScaleVideo() correctly scales the HDMI input video during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 011@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Get the number of input ports from the profile file
 * |03|Scale HDMI input video using dsHdmiInScaleVideo() |x=0, y=0, width=800, height=600| dsERR_NONE | Video should be scaled |
 * |04|Scale HDMI input video using dsHdmiInScaleVideo() |x=10, y=10, width=1000, height=800| dsERR_NONE | Video should be scaled |
 * |05|Scale HDMI input video using dsHdmiInScaleVideo() |x=100, y=100, width=800, height=600| dsERR_NONE | Video should be scaled |
 * |06|Scale HDMI input video using dsHdmiInScaleVideo() |x=0, y=0, width=800, height=600| dsERR_OPERATION_NOT_SUPPORTED | For source devices without HDMI input support |
 * |07|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInScaleVideo(void) {
    gTestID = 11;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    uint8_t numInputPorts = 0;

    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Get the number of input ports from the profile file
    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/HdmiInputPort/numberOfPorts");
    if (numInputPorts > 0) {
        // Step 3: Scale HDMI input video (x=0, y=0, width=800, height=600)
        UT_ASSERT_EQUAL(dsHdmiInScaleVideo(0, 0, 800, 600), dsERR_NONE);

       // Step 4: Scale HDMI input video (x=10, y=10, width=1000, height=800)
       UT_ASSERT_EQUAL(dsHdmiInScaleVideo(10, 10, 1000, 800), dsERR_NONE);

       // Step 5: Scale HDMI input video (x=-10, y=-10, width=800, height=600)
       UT_ASSERT_EQUAL(dsHdmiInScaleVideo(100, 100, 800, 600), dsERR_NONE);
    } else {
      // Step 6: For source devices without hdmi input support
      UT_ASSERT_EQUAL(dsHdmiInScaleVideo(0, 0, 800, 600), dsERR_OPERATION_NOT_SUPPORTED);
    }

    // Step 7: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsHdmiInScaleVideo() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 012@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|dsHdmiInScaleVideo() without initializing the HDMI input sub-system |x=0, y=0, width=800, height=600| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|dsHdmiInScaleVideo()  |x=0, y=0, width=2000, height=600 | dsERR_INVALID_PARAM | Should Pass |
 * |04|dsHdmiInScaleVideo() with out of bounds|x=-1000, y=0, width=800, height=600| dsERR_INVALID_PARAM | Should Pass |
 * |05|dsHdmiInScaleVideo() with out of bounds|x=0, y=0, width=-800, height=600| dsERR_INVALID_PARAM | Should Pass |
 * |06|dsHdmiInScaleVideo() with out of bounds|x=0, y=0, width=800, height=-600| dsERR_INVALID_PARAM | Should Pass |
 * |07|dsHdmiInScaleVideo() with out of bounds|x=0, y=-1000, width=800, height=600| dsERR_INVALID_PARAM | Should Pass |
 * |08|dsHdmiInScaleVideo() with out of bounds|x=0, y=20000, width=800, height=600| dsERR_INVALID_PARAM | Should Pass |
 * |09|dsHdmiInScaleVideo() with out of bounds|x=20000, y=0, width=800, height=600| dsERR_INVALID_PARAM | Should Pass |
 * |10|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |11|dsHdmiInScaleVideo() after terminating the HDMI input sub-system |x=0, y=0, width=800, height=600| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInScaleVideo(void) {
    gTestID = 12;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    // Step 1: Call dsHdmiInScaleVideo() without initializing the HDMI input sub-system
    dsError_t result = dsHdmiInScaleVideo(0, 0, 800, 600);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: dsHdmiInScaleVideo() with invalid parameters (x=0, y=0, width=2000, height=600)
    UT_ASSERT_EQUAL(dsHdmiInScaleVideo(0, 0, 2000, 600), dsERR_INVALID_PARAM);

    // Step 4: dsHdmiInScaleVideo() with out of bounds parameters (x=-1000, y=0, width=800, height=600)
    UT_ASSERT_EQUAL(dsHdmiInScaleVideo(-1000, 0, 800, 600), dsERR_INVALID_PARAM);

    // Step 5: dsHdmiInScaleVideo() with out of bounds parameters (x=0, y=0, width=-800, height=600)
    UT_ASSERT_EQUAL(dsHdmiInScaleVideo(0, 0, -800, 600), dsERR_INVALID_PARAM);

    // Step 6: dsHdmiInScaleVideo() with out of bounds parameters (x=0, y=0, width=800, height=-600)
    UT_ASSERT_EQUAL(dsHdmiInScaleVideo(0, 0, 800, -600), dsERR_INVALID_PARAM);

    // Step 7: dsHdmiInScaleVideo() with out of bounds parameters (x=0, y=-1000, width=800, height=600)
    UT_ASSERT_EQUAL(dsHdmiInScaleVideo(0, -1000, 800, 600), dsERR_INVALID_PARAM);

    // Step 8: dsHdmiInScaleVideo() with out of bounds parameters (x=0, y=20000, width=800, height=600)
    UT_ASSERT_EQUAL(dsHdmiInScaleVideo(0, 20000, 800, 600), dsERR_INVALID_PARAM);

    // Step 9: dsHdmiInScaleVideo() with out of bounds parameters (x=20000, y=0, width=800, height=600)
    UT_ASSERT_EQUAL(dsHdmiInScaleVideo(20000, 0, 800, 600), dsERR_INVALID_PARAM);

    // Step 10: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 11: dsHdmiInScaleVideo() after terminating the HDMI input sub-system
    result = dsHdmiInScaleVideo(0, 0, 800, 600);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsHdmiInSelectZoomMode() correctly updates the zoom mode during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 013@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Get the number of input ports from the profile file
 * |03|Call dsHdmiInSelectPort() |dsHDMI_IN_PORT_0, bool: false, dsVideoPlane_PRIMARY, bool false| dsERR_NONE | Port 0 should be selected |
 * |04|Call dsHdmiInSelectZoomMode() and loop through all valid dsVideoZoom_t |[Valid Zoom Mode]| dsERR_NONE | Zoom mode should be updated |
 * |05|Call dsHdmiInSelectZoomMode() updates the video zoom on the active HDMI input using the provided zoom |dsERR_OPERATION_NOT_SUPPORTED |For both sink and source devices without HDMI input support
 * |06|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInSelectZoomMode_source(void) {
    gTestID = 13;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    uint8_t numInputPorts = 0;
    
    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Get the number of input ports from the profile file
    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/HdmiInputPort/numberOfPorts");
    if (numInputPorts > 0) {
        // Step 3: Call dsHdmiInSelectPort() to select Port 0
        UT_ASSERT_EQUAL(dsHdmiInSelectPort(dsHDMI_IN_PORT_0, false, dsVideoPlane_PRIMARY, false), dsERR_NONE);

        // Step 4: Loop through all dsVideoZoom_t values and call dsHdmiInSelectZoomMode()
        for (int i = dsVIDEO_ZOOM_NONE; i < dsVIDEO_ZOOM_MAX; i++) {
              dsVideoZoom_t zoomMode = i;
              UT_ASSERT_EQUAL(dsHdmiInSelectZoomMode(zoomMode), dsERR_NONE);
        }
    } else {
       // Step 5:Calling dsHdmiInSelectZoomMode(dsVIDEO_ZOOM_MAX)
       UT_ASSERT_EQUAL(dsHdmiInSelectZoomMode(dsVIDEO_ZOOM_MAX), dsERR_OPERATION_NOT_SUPPORTED);
    }
    
    // Step 6: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsHdmiInSelectZoomMode() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 014@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsHdmiInSelectZoomMode() without initializing the HDMI input sub-system |dsVIDEO_ZOOM_NONE| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsHdmiInSelectPort() |dsHDMI_IN_PORT_0, bool: false, dsVideoPlane_PRIMARY, bool false| dsERR_NONE | Port 0 should be selected |
 * |04|Call dsHdmiInSelectZoomMode() with invalid value |dsVIDEO_ZOOM_MAX| dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |06|Call dsHdmiInSelectZoomMode() without terminating the HDMI input sub-system |dsVIDEO_ZOOM_NONE| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInSelectZoomMode_source(void) {
    gTestID = 14;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    // Step 1: Call dsHdmiInSelectZoomMode() without initializing the HDMI input sub-system
    dsError_t result = dsHdmiInSelectZoomMode(dsVIDEO_ZOOM_NONE);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);
    
    // Step 3: Call dsHdmiInSelectPort() to select Port 0
    UT_ASSERT_EQUAL(dsHdmiInSelectPort(dsHDMI_IN_PORT_0, false, dsVideoPlane_PRIMARY, false), dsERR_NONE);

    // Step 4: Call dsHdmiInSelectZoomMode() with invalid value (dsVIDEO_ZOOM_MAX)
    UT_ASSERT_EQUAL(dsHdmiInSelectZoomMode(dsVIDEO_ZOOM_MAX),dsERR_INVALID_PARAM);
    
    // Step 5: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 6: Call dsHdmiInSelectZoomMode() without terminating the HDMI input sub-system
    result = dsHdmiInSelectZoomMode(dsVIDEO_ZOOM_NONE);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsHdmiInGetCurrentVideoMode() correctly retrieves the current HDMI video mode during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 015@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Get the number of input ports from the profile file
 * |03|Retrieve the current HDMI video mode using dsHdmiInGetCurrentVideoMode() |dsVideoPortResolution_t*| dsERR_NONE | Video mode should be retrieved |
 * |04|Retrieve the current HDMI video mode using dsHdmiInGetCurrentVideoMode() |dsVideoPortResolution_t*| dsERR_NONE | Video mode should be retrieved |
 * |05|Ensure returned values are the same| |Success| The values should be the same |
 * |06|dsHdmiInGetCurrentVideoMode() to get the current HDMI input video mode of the active port | dsERR_OPERATION_NOT_SUPPORTED| For source devices without HDMI input support
 * |07|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInGetCurrentVideoMode(void) {
    gTestID = 15;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    dsVideoPortResolution_t resolution1;
    dsVideoPortResolution_t resolution2;
    uint8_t numInputPorts = 0;

    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Get the number of input ports from the profile file
    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/HdmiInputPort/numberOfPorts");
    if (numInputPorts > 0) {
	// Step 3: Retrieve the current HDMI video mode using dsHdmiInGetCurrentVideoMode()
        UT_ASSERT_EQUAL(dsHdmiInGetCurrentVideoMode(&resolution1), dsERR_NONE);
        UT_ASSERT_EQUAL(dsHdmiInGetCurrentVideoMode(&resolution2), dsERR_NONE);

        // Step 4: Ensure returned values are the same
        UT_LOG("\n In %s Name: [%d,%d]\n", __FUNCTION__, resolution1.name, resolution2.name); 
        UT_ASSERT_EQUAL(resolution1.name, resolution2.name);
        UT_LOG("\n In %s pixelResolution: [%d,%d]\n", __FUNCTION__, resolution1.pixelResolution, resolution2.pixelResolution); 
        UT_ASSERT_EQUAL(resolution1.pixelResolution, resolution2.pixelResolution);
        UT_LOG("\n In %s aspectRatio: [%d,%d]\n", __FUNCTION__, resolution1.aspectRatio, resolution2.aspectRatio); 
        UT_ASSERT_EQUAL(resolution1.aspectRatio, resolution2.aspectRatio); 
        UT_LOG("\n In %s frameRate: [%d,%d]\n", __FUNCTION__, resolution1.frameRate, resolution2.frameRate); 
        UT_ASSERT_EQUAL(resolution1.frameRate, resolution2.frameRate);
        UT_LOG("\n In %s interlaced: [%d,%d]\n", __FUNCTION__, resolution1.interlaced, resolution2.interlaced); 
        UT_ASSERT_EQUAL(resolution1.interlaced, resolution2.interlaced);
    } else {
      // Step 6: Retrieve the current HDMI video mode using dsHdmiInGetCurrentVideoMode()
      UT_ASSERT_EQUAL(dsHdmiInGetCurrentVideoMode(&resolution1), dsERR_OPERATION_NOT_SUPPORTED);
    }
    
    // Step 7: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsHdmiInGetCurrentVideoMode() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 016@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsHdmiInGetCurrentVideoMode() without initializing the HDMI input sub-system |dsVideoPortResolution_t*| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|dsHdmiInGetCurrentVideoMode() with NULL `resolution` pointer |NULL} dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |05|Call dsHdmiInGetCurrentVideoMode() after terminating the HDMI input sub-system |dsVideoPortResolution_t*| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInGetCurrentVideoMode(void) {
    gTestID = 16;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    // Step 1: Call dsHdmiInGetCurrentVideoMode() without initializing the HDMI input sub-system
    dsVideoPortResolution_t resolution;
    dsError_t result = dsHdmiInGetCurrentVideoMode(&resolution);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: dsHdmiInGetCurrentVideoMode() with NULL `resolution` pointer
    UT_ASSERT_EQUAL(dsHdmiInGetCurrentVideoMode(NULL),dsERR_INVALID_PARAM);
	
    // Step 4: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 5: Call dsHdmiInGetCurrentVideoMode() after terminating the HDMI input sub-system
    result = dsHdmiInGetCurrentVideoMode(&resolution);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

void mockConnectCallback(dsHdmiInPort_t Port, bool isPortConnected){
// Mock implementation, can be customized for testing
}

/**
 * @brief Ensure dsHdmiInRegisterConnectCB() correctly registers a callback during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 017@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Call dsHdmiInRegisterConnectCB() registers a callback based on the number of input ports from the profile file |dsHdmiInConnectCB_t| dsERR_NONE | Callback should be registered |
 * |03|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInRegisterConnectCB(void) {
    gTestID = 17;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    uint8_t numInputPorts = 0;
    
    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);
    
    // Step 2: Call dsHdmiInRegisterConnectCB() based on the number of input ports
    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/HdmiInputPort/numberOfPorts");
    if (numInputPorts > 0) {
	 // For sink devices
         UT_ASSERT_EQUAL(dsHdmiInRegisterConnectCB(mockConnectCallback), dsERR_NONE);
     } else {
	 // For source devices
	 UT_ASSERT_EQUAL(dsHdmiInRegisterConnectCB(mockConnectCallback), dsERR_OPERATION_NOT_SUPPORTED);
     }

    // Step 3: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsHdmiInRegisterConnectCB() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 018@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01| Call dsHdmiInRegisterConnectCB() without initializing the HDMI input sub-system |dsHdmiInConnectCB_t| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsHdmiInRegisterConnectCB() with invalid input |NULL| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |05| Call dsHdmiInRegisterConnectCB() after termination the HDMI input sub-system |dsHdmiInConnectCB_t| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInRegisterConnectCB(void) {
    gTestID = 18;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    // Step 1: Call dsHdmiInRegisterConnectCB() without initializing the HDMI input sub-system
    dsError_t result = dsHdmiInRegisterConnectCB(mockConnectCallback);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsHdmiInRegisterConnectCB() with invalid input
    UT_ASSERT_EQUAL(dsHdmiInRegisterConnectCB(NULL), dsERR_INVALID_PARAM);

    // Step 4: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 5: Call dsHdmiInRegisterConnectCB() after termination the HDMI input sub-system
    result = dsHdmiInRegisterConnectCB(mockConnectCallback);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

void mockSignalCallback(dsHdmiInPort_t port, dsHdmiInSignalStatus_t sigStatus){
// Mock implementation, can be customized for testing
}

/**
 * @brief Ensure dsHdmiInRegisterSignalChangeCB() correctly registers a callback during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 019@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Call dsHdmiInRegisterSignalChangeCB() based on the number of input ports from the profile file |dsHdmiInSignalChangeCB_t| dsERR_NONE | Callback should be registered |
 * |03|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInRegisterSignalChangeCB(void) {
    gTestID = 19;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    uint8_t numInputPorts = 0;

    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/HdmiInputPort/numberOfPorts");

    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Call dsHdmiInRegisterSignalChangeCB() based on the number of input ports
    if (numInputPorts > 0) {
	// For sink devices
	UT_ASSERT_EQUAL(dsHdmiInRegisterSignalChangeCB(mockSignalCallback), dsERR_NONE);

    } else {
	// For source devices  
        UT_ASSERT_EQUAL(dsHdmiInRegisterSignalChangeCB(mockSignalCallback), dsERR_OPERATION_NOT_SUPPORTED);
    }

    // Step 3: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsHdmiInRegisterSignalChangeCB() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 020@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsHdmiInRegisterSignalChangeCB() without initializing the HDMI input sub-system |dsHdmiInSignalChangeCB_t| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsHdmiInRegisterSignalChangeCB() with invalid input |NULL| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |05|Call dsHdmiInRegisterSignalChangeCB() after terminating the HDMI input sub-system |dsHdmiInSignalChangeCB_t| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInRegisterSignalChangeCB(void) {
    gTestID = 20;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    // Step 1: Call dsHdmiInRegisterSignalChangeCB() without initializing the HDMI input sub-system
    dsError_t result = dsHdmiInRegisterSignalChangeCB(mockSignalCallback);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsHdmiInRegisterSignalChangeCB() with invalid input
    UT_ASSERT_EQUAL(dsHdmiInRegisterSignalChangeCB(NULL), dsERR_INVALID_PARAM);

    // Step 4: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 5: Call dsHdmiInRegisterSignalChangeCB() after terminating the HDMI input sub-system
    result = dsHdmiInRegisterSignalChangeCB(mockSignalCallback);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

void mockStatusChangeCallback(dsHdmiInStatus_t inputStatus){
// Mock implementation, can be customized for testing
}

/**
 * @brief Ensure dsHdmiInRegisterStatusChangeCB() correctly registers a callback during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 021@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Call dsHdmiInRegisterStatusChangeCB() based on the number of input ports from the profile file |dsHdmiInStatusChangeCB_t| dsERR_NONE | Callback should be registered |
 * |03|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInRegisterStatusChangeCB(void) {
    gTestID = 21;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    uint8_t numInputPorts = 0;

    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/HdmiInputPort/numberOfPorts");

    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Call dsHdmiInRegisterStatusChangeCB()
    if (numInputPorts > 0) {
	// For sink devices
        UT_ASSERT_EQUAL(dsHdmiInRegisterStatusChangeCB(mockStatusChangeCallback), dsERR_NONE);
    } else {
        // For source devices
        UT_ASSERT_EQUAL(dsHdmiInRegisterStatusChangeCB(mockStatusChangeCallback), dsERR_OPERATION_NOT_SUPPORTED);
    }
    
    // Step 3: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsHdmiInRegisterStatusChangeCB() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 022@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsHdmiInRegisterStatusChangeCB() without initializing the HDMI input sub-system |dsHdmiInStatusChangeCB_t| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsHdmiInRegisterStatusChangeCB() with invalid input |NULL| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |05|Call dsHdmiInRegisterStatusChangeCB() after termination the HDMI input sub-system |dsHdmiInStatusChangeCB_t| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInRegisterStatusChangeCB(void) {
    gTestID = 22;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    // Step 1: Call dsHdmiInRegisterStatusChangeCB() without initializing the HDMI input sub-system
    dsError_t result = dsHdmiInRegisterStatusChangeCB(mockStatusChangeCallback);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsHdmiInRegisterStatusChangeCB() with invalid input
    UT_ASSERT_EQUAL(dsHdmiInRegisterStatusChangeCB(NULL), dsERR_INVALID_PARAM);

    // Step 4: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 5: Call dsHdmiInRegisterStatusChangeCB() after terminating the HDMI input sub-system
    result = dsHdmiInRegisterStatusChangeCB(mockStatusChangeCallback);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

void mockVideoModeUpdateCallback(dsHdmiInPort_t port, dsVideoPortResolution_t videoResolution){
// Mock implementation, can be customized for testing
}

/**
 * @brief Ensure dsHdmiInRegisterVideoModeUpdateCB() correctly registers a callback during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 023@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Call dsHdmiInRegisterVideoModeUpdateCB() based on the number of input ports from the profile file |dsHdmiInVideoModeUpdateCB_t| dsERR_NONE | Callback should be registered |
 * |03|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInRegisterVideoModeUpdateCB(void) {
    gTestID = 23;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    uint8_t numInputPorts = 0;
   
    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/HdmiInputPort/numberOfPorts");

    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Call dsHdmiInRegisterVideoModeUpdateCB()
    if (numInputPorts > 0) {
        // For sink devices
         UT_ASSERT_EQUAL(dsHdmiInRegisterVideoModeUpdateCB(mockVideoModeUpdateCallback), dsERR_NONE);

    } else {
        // For source devices
        UT_ASSERT_EQUAL(dsHdmiInRegisterVideoModeUpdateCB(mockVideoModeUpdateCallback), dsERR_OPERATION_NOT_SUPPORTED);
    }
    
    // Step 3: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsHdmiInRegisterVideoModeUpdateCB() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 024@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsHdmiInRegisterVideoModeUpdateCB() without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsHdmiInRegisterVideoModeUpdateCB() with invalid input |NULL| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |05|Call dsHdmiInRegisterVideoModeUpdateCB() after terminating the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInRegisterVideoModeUpdateCB(void) {
    gTestID = 24;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    // Step 1: Call dsHdmiInRegisterVideoModeUpdateCB() without initializing the HDMI input sub-system
    dsError_t result = dsHdmiInRegisterVideoModeUpdateCB(mockVideoModeUpdateCallback);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsHdmiInRegisterVideoModeUpdateCB() with invalid input
    UT_ASSERT_EQUAL(dsHdmiInRegisterVideoModeUpdateCB(NULL), dsERR_INVALID_PARAM);

    // Step 4: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 5: Call dsHdmiInRegisterVideoModeUpdateCB() after terminating the HDMI input sub-system
    result = dsHdmiInRegisterVideoModeUpdateCB(mockVideoModeUpdateCallback);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

void mockALLMChangeCallback(dsHdmiInPort_t port, bool allm_mode){
// Mock implementation, can be customized for testing
}

/**
 * @brief Ensure dsHdmiInRegisterAllmChangeCB() correctly registers a callback during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 025@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Call dsHdmiInRegisterAllmChangeCB() based on the number of input ports from the profile file |dsHdmiInAllmChangeCB_t| dsERR_NONE | Callback should be registered |
 * |03|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInRegisterAllmChangeCB(void) {
    gTestID = 25;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    uint8_t numInputPorts = 0;

    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/HdmiInputPort/numberOfPorts");

    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Call dsHdmiInRegisterAllmChangeCB()
    if (numInputPorts > 0) {
        // For sink devices
         UT_ASSERT_EQUAL(dsHdmiInRegisterAllmChangeCB(mockALLMChangeCallback), dsERR_NONE);

    } else {
        // For source devices
        UT_ASSERT_EQUAL(dsHdmiInRegisterAllmChangeCB(mockALLMChangeCallback), dsERR_OPERATION_NOT_SUPPORTED);
    }
    
    // Step 3: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsHdmiInRegisterAllmChangeCB() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 026@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsHdmiInRegisterAllmChangeCB() without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsHdmiInRegisterAllmChangeCB() with invalid input |NULL| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |05|Call dsHdmiInRegisterAllmChangeCB() after terminating the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInRegisterAllmChangeCB(void) {
    gTestID = 26;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Step 1: Call dsHdmiInRegisterAllmChangeCB() without initializing the HDMI input sub-system
    dsError_t result = dsHdmiInRegisterAllmChangeCB(mockALLMChangeCallback);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsHdmiInRegisterAllmChangeCB() with invalid input
    UT_ASSERT_EQUAL(dsHdmiInRegisterAllmChangeCB(NULL), dsERR_INVALID_PARAM);

    // Step 4: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 5: Call dsHdmiInRegisterAllmChangeCB() after terminating the HDMI input sub-system
    result = dsHdmiInRegisterAllmChangeCB(mockALLMChangeCallback);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

void mockLatencyChangeCallback(int audio_latency, int video_latency){
// Mock implementation, can be customized for testing
}

/**
 * @brief Ensure dsHdmiInRegisterAVLatencyChangeCB() correctly registers a callback during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 027@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Call dsHdmiInRegisterAVLatencyChangeCB() based on the number of input ports from the profile file |dsAVLatencyChangeCB_t| dsERR_NONE | Callback should be registered |
 * |03|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInRegisterAVLatencyChangeCB(void) {
    gTestID = 27;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    uint8_t numInputPorts = 0;

    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/HdmiInputPort/numberOfPorts");

    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Call dsHdmiInRegisterAVLatencyChangeCB()
    if (numInputPorts > 0) {
        // For sink devices
        UT_ASSERT_EQUAL(dsHdmiInRegisterAVLatencyChangeCB(mockLatencyChangeCallback), dsERR_NONE);

    } else {
        // For source devices
        UT_ASSERT_EQUAL(dsHdmiInRegisterAVLatencyChangeCB(mockLatencyChangeCallback), dsERR_OPERATION_NOT_SUPPORTED);
    }
    
    // Step 3: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsHdmiInRegisterAVLatencyChangeCB() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 028@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsHdmiInRegisterAVLatencyChangeCB() without initializing the HDMI input sub-system |dsAVLatencyChangeCB_t| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsHdmiInRegisterAVLatencyChangeCB() with invalid input |NULL| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |05|Call dsHdmiInRegisterAVLatencyChangeCB() after terminating the HDMI input sub-system |dsAVLatencyChangeCB_t| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note The return values dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL may be difficult to test in a simulated environment
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInRegisterAVLatencyChangeCB(void) {
    gTestID = 28;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Step 1: Call dsHdmiInRegisterAVLatencyChangeCB() without initializing the HDMI input sub-system
    dsError_t result = dsHdmiInRegisterAVLatencyChangeCB(mockLatencyChangeCallback);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsHdmiInRegisterAVLatencyChangeCB() with invalid input
    UT_ASSERT_EQUAL(dsHdmiInRegisterAVLatencyChangeCB(NULL), dsERR_INVALID_PARAM);

    // Step 4: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 5: Call dsHdmiInRegisterAVLatencyChangeCB() after terminating the HDMI input sub-system
    result = dsHdmiInRegisterAVLatencyChangeCB(mockLatencyChangeCallback);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

void mockAviContentCallback(dsHdmiInPort_t port, dsAviContentType_t avi_content_type){
// Mock implementation, can be customized for testing
}

/**
 * @brief Ensure dsHdmiInRegisterAviContentTypeChangeCB() correctly registers a callback during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 029@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Call dsHdmiInRegisterAviContentTypeChangeCB() based on the number of input ports from the profile file |dsHdmiInAviContentTypeChangeCB_t| dsERR_NONE | Callback should be registered |
 * |03|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInRegisterAviContentTypeChangeCB(void) {
    gTestID = 29;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    uint8_t numInputPorts = 0;

    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/HdmiInputPort/numberOfPorts");

    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Call dsHdmiInRegisterAviContentTypeChangeCB()
    if (numInputPorts > 0) {
        // For sink devices
         UT_ASSERT_EQUAL(dsHdmiInRegisterAviContentTypeChangeCB(mockAviContentCallback), dsERR_NONE);

    } else {
        // For source devices
        UT_ASSERT_EQUAL(dsHdmiInRegisterAviContentTypeChangeCB(mockAviContentCallback), dsERR_OPERATION_NOT_SUPPORTED);
    }

    // Step 3: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsHdmiInRegisterAviContentTypeChangeCB() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 030@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsHdmiInRegisterAviContentTypeChangeCB() without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsHdmiInRegisterAviContentTypeChangeCB() with invalid input |NULL| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |05|Call dsHdmiInRegisterAviContentTypeChangeCB() after terminating the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_GENERAL` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInRegisterAviContentTypeChangeCB(void) {
    gTestID = 30;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Step 1: Call dsHdmiInRegisterAviContentTypeChangeCB() without initializing the HDMI input sub-system
    dsError_t result = dsHdmiInRegisterAviContentTypeChangeCB(mockAviContentCallback);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsHdmiInRegisterAviContentTypeChangeCB() with invalid input
    UT_ASSERT_EQUAL(dsHdmiInRegisterAviContentTypeChangeCB(NULL), dsERR_INVALID_PARAM);

    // Step 4: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 5: Call dsHdmiInRegisterAviContentTypeChangeCB() after terminating the HDMI input sub-system
    result = dsHdmiInRegisterAviContentTypeChangeCB(mockAviContentCallback);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsIsHdmiARCPort() correctly checks for an HDMI ARC port during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 031@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Get the number of input ports from the profile file
 * |03|Call dsIsHdmiARCPort() with valid input |dsHDMI_IN_PORT_0, bool*| dsERR_NONE | Should successfully check for ARC capability |
 * |04|Call dsIsHdmiARCPort() with valid input |dsHDMI_IN_PORT_1, bool*| dsERR_NONE | Should successfully check for ARC capability |
 * |05|Call dsIsHdmiARCPort() with valid input |dsHDMI_IN_PORT_2, bool*| dsERR_NONE | Should successfully check for ARC capability |
 * |06|Call dsIsHdmiARCPort() with valid input |dsHDMI_IN_PORT_2, bool*| dsERR_NONE | Should successfully check for ARC capability |
 * |07|Compare the values of steps 4 and 5 to make sure they equal one another || Success | The values should be equal |
 * |08|Call dsIsHdmiARCPort() with valid input |dsHDMI_IN_PORT_0, bool*| dsERR_OPERATION_NOT_SUPPORTED | for source devices
 * |09|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsIsHdmiARCPort_sink(void) {
    gTestID = 31;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    uint8_t numInputPorts = 0;
    bool isArcPort1, isArcPort2;

    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/HdmiInputPort/numberOfPorts");

    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Check if HDMI ARC is supported based on the number of input ports
    if (numInputPorts > 0) {
       
        // Step 3: Call dsIsHdmiARCPort() with valid input (dsHDMI_IN_PORT_0)
        UT_ASSERT_EQUAL(dsIsHdmiARCPort(dsHDMI_IN_PORT_0, &isArcPort1), dsERR_NONE);

        // Step 4: Call dsIsHdmiARCPort() with valid input (dsHDMI_IN_PORT_1)
        UT_ASSERT_EQUAL(dsIsHdmiARCPort(dsHDMI_IN_PORT_1, &isArcPort2), dsERR_NONE);

        // Step 5: Call dsIsHdmiARCPort() with valid input (dsHDMI_IN_PORT_2)
        UT_ASSERT_EQUAL(dsIsHdmiARCPort(dsHDMI_IN_PORT_2, &isArcPort1), dsERR_NONE);

        // Step 6: Call dsIsHdmiARCPort() with valid input (dsHDMI_IN_PORT_2)
        UT_ASSERT_EQUAL(dsIsHdmiARCPort(dsHDMI_IN_PORT_2, &isArcPort2), dsERR_NONE);

        // Step 7: Compare the values of steps 4 and 5 to make sure they equal one another
        UT_ASSERT_EQUAL(isArcPort1, isArcPort2);
    
    } else {
        // Step 8:Call dsIsHdmiARCPort() with valid input for source devices
        UT_ASSERT_EQUAL(dsIsHdmiARCPort(dsHDMI_IN_PORT_0, &isArcPort1), dsERR_OPERATION_NOT_SUPPORTED);
    }

    // Step 9: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsIsHdmiARCPort() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 032@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsIsHdmiARCPort() without initializing the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsIsHdmiARCPort() with invalid value |dsHDMI_IN_PORT_MAX, bool*| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsIsHdmiARCPort() with invalid value |dsHDMI_IN_PORT_0, NULL| dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |06|Call dsIsHdmiARCPort() after terminating the HDMI input sub-system | dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 * 
 */
void test_l1_dsHdmiIn_negative_dsIsHdmiARCPort_sink(void) {
    gTestID = 32;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Step 1: Call dsIsHdmiARCPort() without initializing the HDMI input sub-system
    dsError_t result = dsIsHdmiARCPort(dsHDMI_IN_PORT_0, NULL);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    bool isArcPort;

    // Step 3: Call dsIsHdmiARCPort() with invalid value (dsHDMI_IN_PORT_MAX)
    UT_ASSERT_EQUAL(dsIsHdmiARCPort(dsHDMI_IN_PORT_MAX, &isArcPort),dsERR_INVALID_PARAM);

    // Step 4: Call dsIsHdmiARCPort() with invalid value (dsHDMI_IN_PORT_0) and NULL pointer
    UT_ASSERT_EQUAL(dsIsHdmiARCPort(dsHDMI_IN_PORT_0, NULL),dsERR_INVALID_PARAM);

    // Step 5: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 6: Call dsIsHdmiARCPort() after terminating the HDMI input sub-system
    result = dsIsHdmiARCPort(dsHDMI_IN_PORT_0, &isArcPort);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsGetEDIDBytesInfo() correctly retrieves the EDID bytes information during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 033@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Get the number of input ports from the profile file
 * |03|Call dsGetEDIDBytesInfo() with valid inputs |dsHDMI_IN_PORT_0, unsigned char*, int*| dsERR_NONE | Should return EDID bytes information successfully |
 * |04|Call dsGetEDIDBytesInfo() with valid inputs |dsHDMI_IN_PORT_1, unsigned char*, int*| dsERR_NONE | Should return EDID bytes information successfully |
 * |05|Call dsGetEDIDBytesInfo() with valid inputs |dsHDMI_IN_PORT_2, unsigned char*, int*| dsERR_NONE | Should return EDID bytes information successfully |
 * |06|Call dsGetEDIDBytesInfo() with valid inputs |dsHDMI_IN_PORT_2, unsigned char*, int*| dsERR_NONE | Should return EDID bytes information successfully |
 * |07|Compare the results and make sure they are the same | | Success | The values should be the same |
 * |08|Call dsGetEDIDBytesInfo() with valid input |dsHDMI_IN_PORT_0, unsigned char*, int*| dsERR_OPERATION_NOT_SUPPORTED| For source devices
 * |09|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsGetEDIDBytesInfo_sink(void) {
    gTestID = 33;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    uint8_t numInputPorts = 0;
    unsigned char* edidBytes1 = (unsigned char*) malloc(255);
    unsigned char* edidBytes2 = (unsigned char*) malloc(255);
    unsigned char* edidBytes3 = (unsigned char*) malloc(255);
    unsigned char* edidBytes4 = (unsigned char*) malloc(255);
    int edidSize1;
    int edidSize2;
    int edidSize3;
    int edidSize4;

    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);
   
    // Step 2: Get the number of input ports from the profile file
    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/HdmiInputPort/numberOfPorts");
    if (numInputPorts > 0) {
        // Step 3: Call dsGetEDIDBytesInfo() with valid input (dsHDMI_IN_PORT_0)
        UT_ASSERT_EQUAL(dsGetEDIDBytesInfo(dsHDMI_IN_PORT_0, edidBytes1, &edidSize1), dsERR_NONE);

        // Step 4: Call dsGetEDIDBytesInfo() with valid input (dsHDMI_IN_PORT_1)
        UT_ASSERT_EQUAL(dsGetEDIDBytesInfo(dsHDMI_IN_PORT_1, edidBytes2, &edidSize2), dsERR_NONE);

        // Step 5: Call dsGetEDIDBytesInfo() with valid input (dsHDMI_IN_PORT_2)
        UT_ASSERT_EQUAL(dsGetEDIDBytesInfo(dsHDMI_IN_PORT_2, edidBytes3, &edidSize3), dsERR_NONE);

        // Step 6: Call dsGetEDIDBytesInfo() with valid input (dsHDMI_IN_PORT_2)
        UT_ASSERT_EQUAL(dsGetEDIDBytesInfo(dsHDMI_IN_PORT_2, edidBytes4, &edidSize4), dsERR_NONE);

        // Step 7: Compare the results and make sure they are the same
        UT_ASSERT_EQUAL(edidSize3, edidSize4);
        UT_ASSERT_EQUAL(memcmp(edidBytes3, edidBytes4, edidSize3),0);
     } else {
        // Step 8: Call dsGetEDIDBytesInfo() with valid input for source devices
	UT_ASSERT_EQUAL(dsGetEDIDBytesInfo(dsHDMI_IN_PORT_0, edidBytes1, &edidSize1), dsERR_OPERATION_NOT_SUPPORTED);
     }

    // Step 9: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    free(edidBytes1);
    free(edidBytes2);
    free(edidBytes3);
    free(edidBytes4);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsGetEDIDBytesInfo() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 034@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetEDIDBytesInfo() without initializing the HDMI input sub-system |dsHDMI_IN_PORT_0, unsigned char*, int*| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsGetEDIDBytesInfo() with invalid value |dsHDMI_IN_PORT_MAX, unsigned char*, int*| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsGetEDIDBytesInfo() with invalid value |dsHDMI_IN_PORT_0, NULL, int*| dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsGetEDIDBytesInfo() with invalid value |dsHDMI_IN_PORT_0, unsigned char*, NULL| dsERR_INVALID_PARAM | Should Pass |
 * |06|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |07|Call dsGetEDIDBytesInfo() after termination the HDMI input sub-system |dsHDMI_IN_PORT_0, unsigned char*, int*| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 * 
 */
void test_l1_dsHdmiIn_negative_dsGetEDIDBytesInfo_sink(void) {
    gTestID = 34;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    unsigned char* edidBytes = (unsigned char*) malloc(255);
    int edidSize;

    // Step 1: Call dsGetEDIDBytesInfo() without initializing the HDMI input sub-system
    dsError_t result = dsGetEDIDBytesInfo(dsHDMI_IN_PORT_0, edidBytes, &edidSize);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsGetEDIDBytesInfo() with invalid value (dsHDMI_IN_PORT_MAX)
    UT_ASSERT_EQUAL(dsGetEDIDBytesInfo(dsHDMI_IN_PORT_MAX, edidBytes, &edidSize),dsERR_INVALID_PARAM);

    // Step 4: Call dsGetEDIDBytesInfo() with invalid value (NULL pointer)
    UT_ASSERT_EQUAL(dsGetEDIDBytesInfo(dsHDMI_IN_PORT_0, NULL, &edidSize),dsERR_INVALID_PARAM);

    // Step 5: Call dsGetEDIDBytesInfo() with invalid value (NULL pointer)
    UT_ASSERT_EQUAL(dsGetEDIDBytesInfo(dsHDMI_IN_PORT_0, edidBytes, NULL),dsERR_INVALID_PARAM);

    // Step 6: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 7: Call dsGetEDIDBytesInfo() after terminating the HDMI input sub-system
    result = dsGetEDIDBytesInfo(dsHDMI_IN_PORT_0, edidBytes, &edidSize);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    free(edidBytes);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsGetHDMISPDInfo() correctly retrieves the HDMI SPD information during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 035@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Get the number of input ports from the profile file
 * |03|Call dsGetHDMISPDInfo() with valid input |dsHDMI_IN_PORT_0, unsigned char*| dsERR_NONE | Should return HDMI SPD information successfully |
 * |04|Call dsGetHDMISPDInfo() with valid input |dsHDMI_IN_PORT_1, unsigned char*| dsERR_NONE | Should return HDMI SPD information successfully |
 * |05|Call dsGetHDMISPDInfo() with valid input |dsHDMI_IN_PORT_2, unsigned char*| dsERR_NONE | Should return HDMI SPD information successfully |
 * |06|Call dsGetHDMISPDInfo() with valid input |dsHDMI_IN_PORT_2, unsigned char*| dsERR_NONE | Should return HDMI SPD information successfully |
 * |07|Compare values from step 4/5 and make sure they're the same || Success | The values should be the same |
 * |08|Call dsGetHDMISPDInfo() with valid input | dsHDMI_IN_PORT_0, unsigned char* | dsERR_OPERATION_NOT_SUPPORTED | For source devices
 * |09|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsGetHDMISPDInfo_sink(void) {
    gTestID = 35;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    uint8_t numInputPorts = 0;
    unsigned char* spdInfo1 = (unsigned char*) malloc(sizeof(struct dsSpd_infoframe_st));
    unsigned char* spdInfo2 = (unsigned char*) malloc(sizeof(struct dsSpd_infoframe_st));
    unsigned char* spdInfo3 = (unsigned char*) malloc(sizeof(struct dsSpd_infoframe_st));
    unsigned char* spdInfo4 = (unsigned char*) malloc(sizeof(struct dsSpd_infoframe_st));

    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/HdmiInputPort/numberOfPorts");

    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Get the number of input ports from the profile file
    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/HdmiInputPort/numberOfPorts");
    if (numInputPorts > 0) {
         // Step 3: Call dsGetHDMISPDInfo() with valid input (dsHDMI_IN_PORT_0)
         UT_ASSERT_EQUAL(dsGetHDMISPDInfo(dsHDMI_IN_PORT_0, spdInfo1), dsERR_NONE);

        // Step 4: Call dsGetHDMISPDInfo() with valid input (dsHDMI_IN_PORT_1)
        UT_ASSERT_EQUAL(dsGetHDMISPDInfo(dsHDMI_IN_PORT_1, spdInfo2), dsERR_NONE);

        // Step 5: Call dsGetHDMISPDInfo() with valid input (dsHDMI_IN_PORT_2)
        UT_ASSERT_EQUAL(dsGetHDMISPDInfo(dsHDMI_IN_PORT_2, spdInfo3), dsERR_NONE);

        // Step 6: Call dsGetHDMISPDInfo() with valid input (dsHDMI_IN_PORT_2)
        UT_ASSERT_EQUAL(dsGetHDMISPDInfo(dsHDMI_IN_PORT_2, spdInfo4), dsERR_NONE);

        // Step 7: Compare the results and make sure they are the same
        UT_ASSERT_EQUAL(memcmp(spdInfo3, spdInfo4,sizeof(struct dsSpd_infoframe_st)),0);

     } else {
        // Step 8: Call dsGetHDMISPDInfo() with valid input for source devices 
        UT_ASSERT_EQUAL(dsGetHDMISPDInfo(dsHDMI_IN_PORT_0, spdInfo1), dsERR_OPERATION_NOT_SUPPORTED);
    }
        
    // Step 9: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    free(spdInfo1);
    free(spdInfo2);
    free(spdInfo3);
    free(spdInfo4);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsGetHDMISPDInfo() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 036@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetHDMISPDInfo() without initializing the HDMI input sub-system |dsHDMI_IN_PORT_0, unsigned char*| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsGetHDMISPDInfo() with invalid values |dsHDMI_IN_PORT_MAX, unsigned char*| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsGetHDMISPDInfo() with invalid values |dsHDMI_IN_PORT_0, NULL| dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |06|Call dsGetHDMISPDInfo() after terminating the HDMI input sub-system |dsHDMI_IN_PORT_0, unsigned char*| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 * 
 */
void test_l1_dsHdmiIn_negative_dsGetHDMISPDInfo_sink(void) {
    gTestID = 36;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    unsigned char* spdInfo1 = (unsigned char*) malloc(sizeof(struct dsSpd_infoframe_st)); 

    // Step 1: Call dsGetHDMISPDInfo() without initializing the HDMI input sub-system
    dsError_t result = dsGetHDMISPDInfo(dsHDMI_IN_PORT_0, spdInfo1);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_GENERAL); 

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsGetHDMISPDInfo() with invalid values (dsHDMI_IN_PORT_MAX)
    UT_ASSERT_EQUAL(dsGetHDMISPDInfo(dsHDMI_IN_PORT_MAX, spdInfo1), dsERR_INVALID_PARAM);

    // Step 4: Call dsGetHDMISPDInfo() with invalid values (NULL pointer)
    UT_ASSERT_EQUAL(dsGetHDMISPDInfo(dsHDMI_IN_PORT_0, NULL), dsERR_INVALID_PARAM);

    // Step 5: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 6: Call dsGetHDMISPDInfo() after terminating the HDMI input sub-system
    result = dsGetHDMISPDInfo(dsHDMI_IN_PORT_0, spdInfo1);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_GENERAL);

    free(spdInfo1);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsSetEdidVersion() correctly sets the EDID version during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 037@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Get the number of input ports from the profile file
 * |03|Call dsSetEdidVersion() with valid values |dsHDMI_IN_PORT_0, HDMI_EDID_VER_14| dsERR_NONE | Should set EDID version successfully |
 * |04|Call dsSetEdidVersion() with valid values |dsHDMI_IN_PORT_0, HDMI_EDID_VER_20| dsERR_NONE | Should set EDID version successfully |
 * |05|Call dsSetEdidVersion() with valid values |dsHDMI_IN_PORT_1, HDMI_EDID_VER_14| dsERR_NONE | Should set EDID version successfully |
 * |06|Call dsSetEdidVersion() with valid values |dsHDMI_IN_PORT_2, HDMI_EDID_VER_14| dsERR_NONE | Should set EDID version successfully |
 * |07|Call dsSetEdidVersion() with valid values | dsHDMI_IN_PORT_0, HDMI_EDID_VER_14 | dsERR_OPERATION_NOT_SUPPORTED | For source devices
 * |08|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsSetEdidVersion_sink(void) {
    gTestID = 37;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    uint32_t ver14, ver20;
    uint8_t numInputPorts = 0;

    ver14 = UT_KVP_PROFILE_GET_UINT32("dsHdmiIn/EdidVersions/0");

    ver20 = UT_KVP_PROFILE_GET_UINT32("dsHdmiIn/EdidVersions/1");

    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);
    
    // Step 2: Get the number of input ports from the profile file
    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/HdmiInputPort/numberOfPorts");
    if (numInputPorts > 0) {
        // Step 3: Call dsSetEdidVersion() with valid values (dsHDMI_IN_PORT_0, HDMI_EDID_VER_14)
        UT_ASSERT_EQUAL(dsSetEdidVersion(dsHDMI_IN_PORT_0, ver14), dsERR_NONE);
    
        // Step 4: Call dsSetEdidVersion() with valid values (dsHDMI_IN_PORT_0, HDMI_EDID_VER_20)
        UT_ASSERT_EQUAL(dsSetEdidVersion(dsHDMI_IN_PORT_0, ver20), dsERR_NONE);

        // Step 5: Call dsSetEdidVersion() with valid values (dsHDMI_IN_PORT_1, HDMI_EDID_VER_14)
        UT_ASSERT_EQUAL(dsSetEdidVersion(dsHDMI_IN_PORT_1, ver14), dsERR_NONE);

        // Step 6: Call dsSetEdidVersion() with valid values (dsHDMI_IN_PORT_2, HDMI_EDID_VER_14)
        UT_ASSERT_EQUAL(dsSetEdidVersion(dsHDMI_IN_PORT_2, ver14), dsERR_NONE);
    } else {
       // Step 7: Call dsSetEdidVersion() with valid values for source devices
	UT_ASSERT_EQUAL(dsSetEdidVersion(dsHDMI_IN_PORT_0, ver14), dsERR_OPERATION_NOT_SUPPORTED);
    }
    
    // Step 8: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsSetEdidVersion() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 038@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsSetEdidVersion() without initializing the HDMI input sub-system |dsHDMI_IN_PORT_0, HDMI_EDID_VER_14| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsSetEdidVersion() with invalid inputs |dsHDMI_IN_PORT_MAX, HDMI_EDID_VER_14| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsSetEdidVersion() with invalid inputs |dsHDMI_IN_PORT_0, HDMI_EDID_VER_MAX| dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |06|Call dsSetEdidVersion() without initializing the HDMI input sub-system |dsHDMI_IN_PORT_0, HDMI_EDID_VER_14| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 * 
 */
void test_l1_dsHdmiIn_negative_dsSetEdidVersion_sink(void) {
    gTestID = 38;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    uint8_t ver14 = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/EdidVersions/0");
   
    // Step 1: Call dsSetEdidVersion() without initializing the HDMI input sub-system
    dsError_t result = dsSetEdidVersion(dsHDMI_IN_PORT_0, ver14);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsSetEdidVersion() with invalid inputs (dsHDMI_IN_PORT_MAX)
    UT_ASSERT_EQUAL(dsSetEdidVersion(dsHDMI_IN_PORT_MAX, ver14), dsERR_INVALID_PARAM);

    // Step 4: Call dsSetEdidVersion() with invalid inputs (HDMI_EDID_VER_MAX)
    UT_ASSERT_EQUAL(dsSetEdidVersion(dsHDMI_IN_PORT_0, HDMI_EDID_VER_MAX), dsERR_INVALID_PARAM);

    // Step 5: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 6: Call dsSetEdidVersion() without initializing the HDMI input sub-system
    result = dsSetEdidVersion(dsHDMI_IN_PORT_0, ver14);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);
    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsGetEdidVersion() correctly retrieves the EDID version during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 039@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Get the number of input ports from the profile file
 * |03|Call dsGetEdidVersion() with all valid ports and call the last one twice|[Valid Port], tv_hdmi_edid_version_t*| dsERR_NONE | Should Pass |
 * |04|Compare the values from final two calls in step 2 and make sure they match || Success | The values should be the same |
 * |05|Call dsGetEdidVersion() with valid ports | dsERR_OPERATION_NOT_SUPPORTED | For source devices
 * |06|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsGetEdidVersion_sink(void) {
    gTestID = 39;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    uint8_t numInputPorts = 0;
    tv_hdmi_edid_version_t edid_version_1, edid_version_2;

    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Get the number of input ports from the profile file
    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/HdmiInputPort/numberOfPorts");
    if (numInputPorts > 0) {
       // Step 3: Call dsGetEdidVersion() with valid values (dsHDMI_IN_PORT_0, tv_hdmi_edid_version_t*)
       UT_ASSERT_EQUAL(dsGetEdidVersion(dsHDMI_IN_PORT_0, &edid_version_1), dsERR_NONE);
       UT_ASSERT_EQUAL(dsGetEdidVersion(dsHDMI_IN_PORT_1, &edid_version_1), dsERR_NONE);
       UT_ASSERT_EQUAL(dsGetEdidVersion(dsHDMI_IN_PORT_2, &edid_version_1), dsERR_NONE);
       UT_ASSERT_EQUAL(dsGetEdidVersion(dsHDMI_IN_PORT_2, &edid_version_2), dsERR_NONE);

       // Step 4: Compare the values from steps 4/5 and make sure they match
       UT_ASSERT_EQUAL(edid_version_1, edid_version_2);
    } else {
       // Step 5: Call dsGetEdidVersion() with valid ports 
       UT_ASSERT_EQUAL(dsGetEdidVersion(dsHDMI_IN_PORT_0, &edid_version_1), dsERR_OPERATION_NOT_SUPPORTED);
    }

    // Step 6: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsGetEdidVersion() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 040@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetEdidVersion() without initializing the HDMI input sub-system |dsHDMI_IN_PORT_0, tv_hdmi_edid_version_t*| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsGetEdidVersion() with invalid inputs |dsHDMI_IN_PORT_MAX, tv_hdmi_edid_version_t*| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsGetEdidVersion() with invalid inputs |dsHDMI_IN_PORT_0, NULL| dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |06|Call dsGetEdidVersion() without initializing the HDMI input sub-system |dsHDMI_IN_PORT_0, tv_hdmi_edid_version_t*| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 * 
 */
void test_l1_dsHdmiIn_negative_dsGetEdidVersion_sink(void) {
    gTestID = 40;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    tv_hdmi_edid_version_t edid_version;

    // Step 1: Call dsGetEdidVersion() without initializing the HDMI input sub-system
    dsError_t result = dsGetEdidVersion(dsHDMI_IN_PORT_0, &edid_version);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsGetEdidVersion() with invalid inputs (dsHDMI_IN_PORT_MAX)
    UT_ASSERT_EQUAL(dsGetEdidVersion(dsHDMI_IN_PORT_MAX, &edid_version), dsERR_INVALID_PARAM);

    // Step 4: Call dsGetEdidVersion() with invalid inputs (NULL)
    UT_ASSERT_EQUAL(dsGetEdidVersion(dsHDMI_IN_PORT_0, NULL), dsERR_INVALID_PARAM);

    // Step 5: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 6: Call dsGetEdidVersion() without initializing the HDMI input sub-system
    result = dsGetEdidVersion(dsHDMI_IN_PORT_0, &edid_version);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsGetAllmStatus() correctly retrieves the ALLM status during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 041@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Get the number of input ports from the profile file
 * |03|Call dsGetAllmStatus() with valid inputs |dsHDMI_IN_PORT_0, bool*| dsERR_NONE | Should retrieve ALLM status successfully |
 * |04|Call dsGetAllmStatus() with valid inputs |dsHDMI_IN_PORT_1, bool*| dsERR_NONE | Should retrieve ALLM status successfully |
 * |05|Call dsGetAllmStatus() with valid inputs |dsHDMI_IN_PORT_2, bool*| dsERR_NONE | Should retrieve ALLM status successfully |
 * |06|Call dsGetAllmStatus() with valid inputs |dsHDMI_IN_PORT_2, bool*| dsERR_NONE | Should retrieve ALLM status successfully |
 * |07|Compare the results of steps 4/5 and make sure they are the same || Success | The returned values should be the same |
 * |08|Call dsGetAllmStatus() with valid inputs | dsHDMI_IN_PORT_0, bool*| dsERR_OPERATION_NOT_SUPPORTED | For source devices
 * |09|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsGetAllmStatus_sink(void) {
    gTestID = 41;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    uint8_t numInputPorts = 0;
    bool allm_status_1, allm_status_2;
    bool allm_status_3;

    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);
    
    // Step 2: Get the number of input ports from the profile file
    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/HdmiInputPort/numberOfPorts");
    if (numInputPorts > 0) {
       // Step 2: Call dsGetAllmStatus() with valid inputs (dsHDMI_IN_PORT_0, bool*)
       UT_ASSERT_EQUAL(dsGetAllmStatus(dsHDMI_IN_PORT_0, &allm_status_1), dsERR_NONE);

       // Step 3: Call dsGetAllmStatus() with valid inputs (dsHDMI_IN_PORT_1, bool*)
       UT_ASSERT_EQUAL(dsGetAllmStatus(dsHDMI_IN_PORT_1, &allm_status_2), dsERR_NONE);

       // Step 4: Call dsGetAllmStatus() with valid inputs (dsHDMI_IN_PORT_2, bool*)
       UT_ASSERT_EQUAL(dsGetAllmStatus(dsHDMI_IN_PORT_2, &allm_status_3), dsERR_NONE);

       // Step 5: Call dsGetAllmStatus() with valid inputs (dsHDMI_IN_PORT_2, bool*)
       UT_ASSERT_EQUAL(dsGetAllmStatus(dsHDMI_IN_PORT_2, &allm_status_1), dsERR_NONE);

       // Step 6: Compare the results of steps 4/5 and make sure they are the same
       UT_ASSERT_EQUAL(allm_status_1, allm_status_3);
    } else {
       // Step 7: Call dsGetAllmStatus() with valid inputs
       UT_ASSERT_EQUAL(dsGetAllmStatus(dsHDMI_IN_PORT_0, &allm_status_1), dsERR_OPERATION_NOT_SUPPORTED);
    }

    // Step 8: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsGetAllmStatus() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 042@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetAllmStatus() without initializing the HDMI input sub-system |dsHDMI_IN_PORT_0, bool*| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsGetAllmStatus() without valid inputs |dsHDMI_IN_PORT_MAX, bool*| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsGetAllmStatus() without valid inputs |dsHDMI_IN_PORT_0, NULL| dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |06|Call dsGetAllmStatus() after termination the HDMI input sub-system |dsHDMI_IN_PORT_0, bool*| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 * 
 */
void test_l1_dsHdmiIn_negative_dsGetAllmStatus_sink(void) {
    gTestID = 42;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Step 1: Call dsGetAllmStatus() without initializing the HDMI input sub-system
    bool allm_status;
    dsError_t result = dsGetAllmStatus(dsHDMI_IN_PORT_0, &allm_status);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsGetAllmStatus() without valid inputs (dsHDMI_IN_PORT_MAX)
    UT_ASSERT_EQUAL(dsGetAllmStatus(dsHDMI_IN_PORT_MAX, &allm_status), dsERR_INVALID_PARAM);

    // Step 4: Call dsGetAllmStatus() without valid inputs (NULL)
    UT_ASSERT_EQUAL(dsGetAllmStatus(dsHDMI_IN_PORT_0, NULL), dsERR_INVALID_PARAM);

    // Step 5: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 6: Call dsGetAllmStatus() after termination the HDMI input sub-system
    result = dsGetAllmStatus(dsHDMI_IN_PORT_0, &allm_status);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsGetSupportedGameFeaturesList() correctly retrieves the list of supported game features during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 043@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Get the number of input ports from the profile file
 * |03|Call dsGetSupportedGameFeaturesList() with valid inputs |dsSupportedGameFeatureList_t*| dsERR_NONE | Should retrieve list successfully |
 * |04|Call dsGetSupportedGameFeaturesList() with valid inputs and Comparing the results to the expected values defined in the test profile |
 * |05||Call dsGetSupportedGameFeaturesList() with valid inputs | dsERR_OPERATION_NOT_SUPPORTED |For source devices
 * |06|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsGetSupportedGameFeaturesList_sink(void) {
    gTestID = 43;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    uint8_t numInputPorts = 0;
    dsSupportedGameFeatureList_t supported_features_1;

    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Get the number of input ports from the profile file
    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/HdmiInputPort/numberOfPorts");
    if (numInputPorts > 0) {
       // Step 3: Call dsGetSupportedGameFeaturesList() with valid inputs (dsSupportedGameFeatureList_t*)
       UT_ASSERT_EQUAL(dsGetSupportedGameFeaturesList(&supported_features_1), dsERR_NONE);

       //step 4:Validating the results retrieved from dsGetSupportedGameFeaturesList() 
       //and Comparing the results to the expected values defined in the profile file
       UT_ASSERT_KVP_EQUAL_PROFILE_STRING(supported_features_1.gameFeatureList, "dsHdmiIn/gameFeatures/feature");
       UT_ASSERT_KVP_EQUAL_PROFILE_UINT32(supported_features_1.gameFeatureCount, "dsHdmiIn/gameFeatures/count");
    } else {
       // Step 5:Call dsGetSupportedGameFeaturesList() with valid inputs	    
       UT_ASSERT_EQUAL(dsGetSupportedGameFeaturesList(&supported_features_1), dsERR_OPERATION_NOT_SUPPORTED);
    }

    // Step 6: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsGetSupportedGameFeaturesList() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 044@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetSupportedGameFeaturesList() without initializing the HDMI input sub-system |dsSupportedGameFeatureList_t*| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsGetSupportedGameFeaturesList() with invalid input |NULL| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |05|Call dsGetSupportedGameFeaturesList() after termination the HDMI input sub-system |dsSupportedGameFeatureList_t*| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 * 
 */
void test_l1_dsHdmiIn_negative_dsGetSupportedGameFeaturesList_sink(void) {
    gTestID = 44;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Step 1: Call dsGetSupportedGameFeaturesList() without initializing the HDMI input sub-system
    dsSupportedGameFeatureList_t supported_features;
    dsError_t result = dsGetSupportedGameFeaturesList(&supported_features);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_GENERAL);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsGetSupportedGameFeaturesList() with invalid input (NULL)
    UT_ASSERT_EQUAL(dsGetSupportedGameFeaturesList(NULL), dsERR_INVALID_PARAM);

    // Step 4: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 5: Call dsGetSupportedGameFeaturesList() after terminating the HDMI input sub-system
    result = dsGetSupportedGameFeaturesList(&supported_features);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_GENERAL);
    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsGetAVLatency() correctly retrieves the current AV latency during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 045@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Get the number of input ports from the profile file
 * |03|Call dsHdmiInSelectPort() |dsHDMI_IN_PORT_0, bool: false, dsVideoPlane_PRIMARY, bool: false| dsERR_NONE | Port 0 should be selected |
 * |04|Call dsGetAVLatency() with valid input |int*, int*| dsERR_NONE | Should retrieve AV latency values successfully |
 * |05|Call dsGetAVLatency() with valid input | dsERR_OPERATION_NOT_SUPPORTED | For source devices
 * |06|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsGetAVLatency_sink(void) {
    gTestID = 45;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    int audioLatency1, videoLatency1;
    uint8_t numInputPorts = 0;

    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Get the number of input ports from the profile file
    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/HdmiInputPort/numberOfPorts");
    if (numInputPorts > 0){
        // Step 3: Call dsHdmiInSelectPort() to select Port 0
        UT_ASSERT_EQUAL(dsHdmiInSelectPort(dsHDMI_IN_PORT_0, false, dsVideoPlane_PRIMARY, false), dsERR_NONE);

        // Step 4: Call dsGetAVLatency() with valid inputs (int*, int*)
        UT_ASSERT_EQUAL(dsGetAVLatency(&audioLatency1, &videoLatency1), dsERR_NONE);
    } else {
        //Step 5: Call dsGetAVLatency() with valid inputs
	UT_ASSERT_EQUAL(dsGetAVLatency(&audioLatency1, &videoLatency1), dsERR_OPERATION_NOT_SUPPORTED);
    }

    // Step 6: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsGetAVLatency() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 046@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetAVLatency() without initializing the HDMI input sub-system |int*, int*| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsGetAVLatency() with valid inputs |NULL, int*| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsGetAVLatency() with valid inputs |int*, NULL| dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |06|Call dsGetAVLatency() after terminating the HDMI input sub-system |int*, int*| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 * 
 */
void test_l1_dsHdmiIn_negative_dsGetAVLatency_sink(void) {
    gTestID = 46;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Step 1: Call dsGetAVLatency() without initializing the HDMI input sub-system
    int audioLatency, videoLatency;
    dsError_t result = dsGetAVLatency(&audioLatency, &videoLatency);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsGetAVLatency() with valid inputs (NULL, int*)
    UT_ASSERT_EQUAL(dsGetAVLatency(NULL, &videoLatency), dsERR_INVALID_PARAM);

    // Step 4: Call dsGetAVLatency() with valid inputs (int*, NULL)
    UT_ASSERT_EQUAL(dsGetAVLatency(&audioLatency, NULL), dsERR_INVALID_PARAM);

    // Step 5: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 6: Call dsGetAVLatency() after terminating the HDMI input sub-system
    result = dsGetAVLatency(&audioLatency, &videoLatency);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsSetEdid2AllmSupport() sets the EDID ALLM support correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 047@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize HDMI input using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Get the number of input ports from the profile file
 * |03|Call dsSetEdid2AllmSupport() with all valid ports and enable EDID ALLM support | iHdmiPort: dsHDMI_IN_PORT_0, allmSupport: true | dsERR_NONE | Should Pass |
 * |04|Call dsSetEdid2AllmSupport() to disable EDID ALLM support | iHdmiPort: dsHDMI_IN_PORT_0, allmSupport: false | dsERR_NONE | Should Pass |
 * |05|Call dsSetEdid2AllmSupport() with valid ports | dsERR_OPERATION_NOT_SUPPORTED | For source devices
 * |06|Terminate the HDMI input using dsHdmiInTerm() | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsSetEdid2AllmSupport_sink(void) {
    gTestID = 47;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    uint8_t numInputPorts = 0;

    // Step 1: Initialize HDMI input using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Get the number of input ports from the profile file
    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/HdmiInputPort/numberOfPorts");
    if (numInputPorts > 0) {
        // Step 3: Call dsSetEdid2AllmSupport() with all valid ports and enable EDID ALLM support
        UT_ASSERT_EQUAL(dsSetEdid2AllmSupport(dsHDMI_IN_PORT_0, true), dsERR_NONE);
        UT_ASSERT_EQUAL(dsSetEdid2AllmSupport(dsHDMI_IN_PORT_1, true), dsERR_NONE);
        UT_ASSERT_EQUAL(dsSetEdid2AllmSupport(dsHDMI_IN_PORT_2, true), dsERR_NONE);
    
        // Step 4: Call dsSetEdid2AllmSupport() to disable EDID ALLM support
        UT_ASSERT_EQUAL(dsSetEdid2AllmSupport(dsHDMI_IN_PORT_0, false), dsERR_NONE);
    } else {
        // Step 5:Call dsSetEdid2AllmSupport() with valid ports
	UT_ASSERT_EQUAL(dsSetEdid2AllmSupport(dsHDMI_IN_PORT_0, true), dsERR_OPERATION_NOT_SUPPORTED);
    }
    
    // Step 6: Terminate the HDMI input using dsHdmiInTerm()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsSetEdid2AllmSupport() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 048@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsSetEdid2AllmSupport() without prior initialization of HDMI input | iHdmiPort: dsHDMI_IN_PORT_0, allmSupport: true | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize HDMI input using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsSetEdid2AllmSupport() with an invalid HDMI port | iHdmiPort: dsHDMI_IN_PORT_MAX, allmSupport: true | dsERR_INVALID_PARAM | Should Pass |
 * |04|Terminate the HDMI input using dsHdmiInTerm() | | dsERR_NONE | Clean up after test |
 * |05|Call dsSetEdid2AllmSupport() after termination | iHdmiPort: dsHDMI_IN_PORT_0, allmSupport: true | dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported or has failed respectively.
 * 
 */
void test_l1_dsHdmiIn_negative_dsSetEdid2AllmSupport_sink(void) {
    gTestID = 48;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Step 1: Call dsSetEdid2AllmSupport() without prior initialization of HDMI input
    dsError_t result = dsSetEdid2AllmSupport(dsHDMI_IN_PORT_0, true);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    // Step 2: Initialize HDMI input using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsSetEdid2AllmSupport() with an invalid HDMI port
    UT_ASSERT_EQUAL(dsSetEdid2AllmSupport(dsHDMI_IN_PORT_MAX, true), dsERR_INVALID_PARAM);

    // Step 4: Terminate the HDMI input using dsHdmiInTerm()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 5: Call dsSetEdid2AllmSupport() after termination
    result = dsSetEdid2AllmSupport(dsHDMI_IN_PORT_0, true);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsGetEdid2AllmSupport() gets the EDID ALLM support correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 049@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize HDMI input using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Get the number of input ports from the profile file
 * |03|Call dsGetEdid2AllmSupport() with all valid ports, and call the last port twice to verify EDID ALLM support | iHdmiPort: dsHDMI_IN_PORT_0, allmSupport: bool* | dsERR_NONE | Should Pass |
 * |04|Compare the returned values from steps 2/3 and verify that they are the same |  | success | The values should be the same |
 * |05|Call dsGetEdid2AllmSupport() with  valid ports | dsERR_OPERATION_NOT_SUPPORTED | For source devices
 * |06|Terminate the HDMI input using dsHdmiInTerm() | | dsERR_NONE | Clean up after test |
 * 
 * @note Ensure that the device supports querying of the EDID ALLM feature before running this test.
 * 
 */
void test_l1_dsHdmiIn_positive_dsGetEdid2AllmSupport_sink(void) {
    gTestID = 49;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    bool allmSupport1, allmSupport2;
    uint8_t numInputPorts = 0;

    // Step 1: Initialize HDMI input using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Get the number of input ports from the profile file
    numInputPorts = UT_KVP_PROFILE_GET_UINT8("dsHdmiIn/HdmiInputPort/numberOfPorts");
    if (numInputPorts > 0) {
        // Step 3: Call dsGetEdid2AllmSupport() to verify EDID ALLM support
        UT_ASSERT_EQUAL(dsGetEdid2AllmSupport(dsHDMI_IN_PORT_0, &allmSupport1), dsERR_NONE);
        UT_ASSERT_EQUAL(dsGetEdid2AllmSupport(dsHDMI_IN_PORT_1, &allmSupport1), dsERR_NONE);
        UT_ASSERT_EQUAL(dsGetEdid2AllmSupport(dsHDMI_IN_PORT_2, &allmSupport1), dsERR_NONE);
        UT_ASSERT_EQUAL(dsGetEdid2AllmSupport(dsHDMI_IN_PORT_2, &allmSupport2), dsERR_NONE);

        // Step 4: Compare the returned values from steps 2/3 and verify that they are the same
        UT_ASSERT_EQUAL(allmSupport1, allmSupport2);
    } else {
      // Step 5:Call dsGetEdid2AllmSupport() with valid ports
      UT_ASSERT_EQUAL(dsGetEdid2AllmSupport(dsHDMI_IN_PORT_0, &allmSupport1), dsERR_OPERATION_NOT_SUPPORTED);
    }
   
    // Step 6: Terminate the HDMI input using dsHdmiInTerm()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsGetEdid2AllmSupport() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 050@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetEdid2AllmSupport() without initializing the HDMI input sub-system | iHdmiPort: dsHDMI_IN_PORT_0, allmSupport: bool* | dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsGetEdid2AllmSupport() with invalid inputs | iHdmiPort: dsHDMI_IN_PORT_MAX, allmSupport: bool* | dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsGetEdid2AllmSupport() with invalid inputs | iHdmiPort: dsHDMI_IN_PORT_0, allmSupport: NULL | dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |06|Call dsGetEdid2AllmSupport() without initializing the HDMI input sub-system again | iHdmiPort: dsHDMI_IN_PORT_0, allmSupport: bool* | dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported or fails due to other reasons.
 * 
 */
void test_l1_dsHdmiIn_negative_dsGetEdid2AllmSupport_sink(void) {
    gTestID = 50;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    bool allmSupport;
    dsError_t result = dsGetEdid2AllmSupport(dsHDMI_IN_PORT_0, &allmSupport);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_OPERATION_NOT_SUPPORTED);

    // Step 2: Initialize HDMI input using dsHdmiInInit()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsGetEdid2AllmSupport() with invalid inputs
    UT_ASSERT_EQUAL(dsGetEdid2AllmSupport(dsHDMI_IN_PORT_MAX, &allmSupport), dsERR_INVALID_PARAM);

    // Step 4: Call dsGetEdid2AllmSupport() with invalid inputs
    UT_ASSERT_EQUAL(dsGetEdid2AllmSupport(dsHDMI_IN_PORT_0, NULL), dsERR_INVALID_PARAM);

    // Step 5: Terminate the HDMI input using dsHdmiInTerm()
    UT_ASSERT_EQUAL_FATAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 6: Call dsGetEdid2AllmSupport() without initializing the HDMI input sub-system again
    result = dsGetEdid2AllmSupport(dsHDMI_IN_PORT_0, &allmSupport);
    CHECK_FOR_EXTENDED_ERROR_CODE(result, dsERR_NOT_INITIALIZED, dsERR_OPERATION_NOT_SUPPORTED);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

static UT_test_suite_t * pSuite = NULL;
static UT_test_suite_t * pSuite2 = NULL;

/**
 * @brief Register the main test(s) for this module
 *
 * @return int - 0 on success, otherwise failure
 */
int test_l1_dsHdmiIn_register ( void )
{
    ut_kvp_status_t status;
    int32_t source_type = 0;
    pSuite2 = UT_add_suite( "[L1 dsHdmiIn --  advanced]", NULL, NULL );
 
    status = ut_kvp_getStringField(ut_kvp_profile_getInstance(), "dsHdmiIn.Type", gDeviceType, TEST_DS_DEVICE_TYPE_SIZE);

    if (status == UT_KVP_STATUS_SUCCESS ) {
        if (!strncmp(gDeviceType, TEST_TYPE_SOURCE_VALUE, TEST_DS_DEVICE_TYPE_SIZE)) {
            // Create the test suite for source type
            pSuite = UT_add_suite("[L1 dsHdmiIn - Source]", NULL, NULL);
            if (pSuite == NULL)
            {
                return -1;
            }
            source_type = 1;
        }
    else if(!strncmp(gDeviceType, TEST_TYPE_SINK_VALUE, TEST_DS_DEVICE_TYPE_SIZE)) {
            // Create the test suite for sink type
            pSuite = UT_add_suite("[L1 dsHdmiIn - Sink]", NULL, NULL);
            if (pSuite == NULL)
            {
                return -1;
            }
            source_type = 0;
        }
        else {
              UT_LOG_ERROR("Invalid platform type: %s", gDeviceType);
              return -1;
        }
    }
    else {
        UT_LOG_ERROR("Failed to get the platform type");
        return -1;
    }

    UT_add_test( pSuite, "dsHdmiInInit_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInInit );
    UT_add_test( pSuite, "dsHdmiInTerm_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInTerm );
    UT_add_test( pSuite, "dsHdmiInGetNumberOfInputs_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInGetNumberOfInputs);
    UT_add_test( pSuite, "dsHdmiInGetStatus_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInGetStatus );
    UT_add_test( pSuite, "dsHdmiInSelectPort_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInSelectPort );
    UT_add_test( pSuite, "dsHdmiInScaleVideo_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInScaleVideo );
    UT_add_test( pSuite, "dsHdmiInGetCurrentVideoMode_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInGetCurrentVideoMode );
    UT_add_test( pSuite, "dsHdmiInRegisterConnectCB_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInRegisterConnectCB );
    UT_add_test( pSuite, "dsHdmiInRegisterSignalChangeCB_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInRegisterSignalChangeCB );
    UT_add_test( pSuite, "dsHdmiInRegisterStatusChangeCB_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInRegisterStatusChangeCB );
    UT_add_test( pSuite, "dsHdmiInRegisterVideoModeUpdateCB_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInRegisterVideoModeUpdateCB );
    UT_add_test( pSuite, "dsHdmiInRegisterAllmChangeCB_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInRegisterAllmChangeCB );
    UT_add_test( pSuite, "dsHdmiInRegisterAVLatencyChangeCB_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInRegisterAVLatencyChangeCB );
    UT_add_test( pSuite, "dsHdmiInRegisterAviContentTypeChangeCB_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInRegisterAviContentTypeChangeCB );
    UT_add_test( pSuite, "dsHdmiInInit_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInInit );
    UT_add_test( pSuite, "dsHdmiInTerm_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInTerm );
    UT_add_test( pSuite, "dsHdmiInGetNumberOfInputs_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInGetNumberOfInputs);
    UT_add_test( pSuite, "dsHdmiInSelectPort_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInSelectPort );
    UT_add_test( pSuite, "dsHdmiInScaleVideo_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInScaleVideo );
    UT_add_test( pSuite, "dsHdmiInGetCurrentVideoMode_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInGetCurrentVideoMode );
    UT_add_test( pSuite, "dsHdmiInRegisterConnectCB_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInRegisterConnectCB );
    UT_add_test( pSuite, "dsHdmiInRegisterSignalChangeCB_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInRegisterSignalChangeCB );
    UT_add_test( pSuite, "dsHdmiInRegisterStatusChangeCB_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInRegisterStatusChangeCB );
    UT_add_test( pSuite, "dsHdmiInRegisterVideoModeUpdateCB_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInRegisterVideoModeUpdateCB );
    UT_add_test( pSuite, "dsHdmiInRegisterAllmChangeCB_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInRegisterAllmChangeCB );
    UT_add_test( pSuite, "dsHdmiInRegisterAVLatencyChangeCB_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInRegisterAVLatencyChangeCB );
    UT_add_test( pSuite, "dsHdmiInRegisterAviContentTypeChangeCB_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInRegisterAviContentTypeChangeCB );
    UT_add_test( pSuite2, "dsHdmiInGetStatus_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInGetStatus );

   if ( source_type == 1 ){
        UT_add_test( pSuite, "dsHdmiInSelectZoomMode_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInSelectZoomMode_source );
        UT_add_test( pSuite, "dsHdmiInSelectZoomMode_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInSelectZoomMode_source );
   }

   if ( source_type == 0 ){
	UT_add_test( pSuite, "dsIsHdmiARCPort_L1_positive" ,test_l1_dsHdmiIn_positive_dsIsHdmiARCPort_sink );
	UT_add_test( pSuite, "dsGetEDIDBytesInfo_L1_positive" ,test_l1_dsHdmiIn_positive_dsGetEDIDBytesInfo_sink );
        UT_add_test( pSuite, "dsGetHDMISPDInfo_L1_positive" ,test_l1_dsHdmiIn_positive_dsGetHDMISPDInfo_sink );
        UT_add_test( pSuite, "dsSetEdidVersion_L1_positive" ,test_l1_dsHdmiIn_positive_dsSetEdidVersion_sink );
        UT_add_test( pSuite, "dsGetEdidVersion_L1_positive" ,test_l1_dsHdmiIn_positive_dsGetEdidVersion_sink );
        UT_add_test( pSuite, "dsGetAllmStatus_L1_positive" ,test_l1_dsHdmiIn_positive_dsGetAllmStatus_sink );
        UT_add_test( pSuite, "dsGetSupportedGameFeaturesList_L1_positive" ,test_l1_dsHdmiIn_positive_dsGetSupportedGameFeaturesList_sink );
        UT_add_test( pSuite, "dsGetAVLatency_L1_positive" ,test_l1_dsHdmiIn_positive_dsGetAVLatency_sink );
        UT_add_test( pSuite, "dsSetEdid2AllmSupport_l1_positive" ,test_l1_dsHdmiIn_positive_dsSetEdid2AllmSupport_sink );

        UT_add_test( pSuite, "dsGetEDIDBytesInfo_L1_negative" ,test_l1_dsHdmiIn_negative_dsGetEDIDBytesInfo_sink );
        UT_add_test( pSuite, "dsGetHDMISPDInfo_L1_negative" ,test_l1_dsHdmiIn_negative_dsGetHDMISPDInfo_sink );
        UT_add_test( pSuite, "dsSetEdidVersion_L1_negative" ,test_l1_dsHdmiIn_negative_dsSetEdidVersion_sink );
	UT_add_test( pSuite, "dsGetEdidVersion_L1_negative" ,test_l1_dsHdmiIn_negative_dsGetEdidVersion_sink );
	UT_add_test( pSuite, "dsGetAllmStatus_L1_negative" ,test_l1_dsHdmiIn_negative_dsGetAllmStatus_sink );
	UT_add_test( pSuite, "dsGetSupportedGameFeaturesList_L1_negative" ,test_l1_dsHdmiIn_negative_dsGetSupportedGameFeaturesList_sink );
	UT_add_test( pSuite, "dsGetAVLatency_L1_negative" ,test_l1_dsHdmiIn_negative_dsGetAVLatency_sink );
	UT_add_test( pSuite, "dsSetEdid2AllmSupport_l1_negative" ,test_l1_dsHdmiIn_negative_dsSetEdid2AllmSupport_sink );
	UT_add_test( pSuite2, "dsGetEdid2AllmSupport_l1_positive" ,test_l1_dsHdmiIn_positive_dsGetEdid2AllmSupport_sink );
        UT_add_test( pSuite2, "dsGetEdid2AllmSupport_l1_negative" ,test_l1_dsHdmiIn_negative_dsGetEdid2AllmSupport_sink );
        UT_add_test( pSuite2, "dsIsHdmiARCPort_L1_negative" ,test_l1_dsHdmiIn_negative_dsIsHdmiARCPort_sink );
   }

   extendedEnumsSupported = ut_kvp_getBoolField( ut_kvp_profile_getInstance(), "dsHdmiIn/features/extendedEnumsSupported" );

   return 0;
} 

/** @} */ // End of DS_HDMIIn_HALTEST_L1
/** @} */ // End of DS_HDMIIn_HALTEST
/** @} */ // End of Device_Settings_HALTEST
/** @} */ // End of Device_Settings
/** @} */ // End of HPK
