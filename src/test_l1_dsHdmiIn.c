/**
*  If not stated otherwise in this file or this component's Licenses.txt
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
 * @addtogroup Device_Settings_HAL Device Settings HAL
 * @par Application API Specification
 * Described herein are the DeviceSettings HAL types and functions that are part of
 * the HdmiIn subsystem. The HdmiIn subsystem manages system-specific HAL operations.
 *  @{
 */

/**
*   @defgroup dsHdmiIn_HALTEST DS HdmiIn HALTEST
 *  @{
 * @par Application API Specification
 * dsHdmiIn HAL provides an interface for managing the HdmiIn settings for the device settings module
 */

/**
 * @defgroup DSHAL_HDMI_IN_L1 DS HAL Hdmi Input L1 test cases
 *  @{
 */

/**
* @file test_l1_dsHdmiIn.c
* @page Device Settings
* @subpage HdmiIn
*
* ## Module's Role
* This module includes Level 1 functional tests (success and failure scenarios)
* This is to ensure that the API meets the operational requirements of the Power Manager across all vendors
*
* **Pre-Conditions:**  None@n
* **Dependencies:** None@n
*
* Ref to API Definition specification documentation : [ds-hdmi-in_halSpec.md](../../../docs/pages/ds-hdmi-in_halSpec.md)
*/

#include <string.h>
#include <stdlib.h>

#include <ut.h>
#include <ut_log.h>

static int gTestGroup = 1;
static int gTestID = 1;

/**
 * @brief Ensure dsHdmiInInit() correctly initializes the HDMI input sub-system during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 001@n
 * 
 * **Dependencies:** HDMI input hardware is properly connected and functioning.@n
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
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 3: Call dsHdmiInInit() again
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 4: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

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
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Call dsHdmiInInit() again without terminating the HDMI input sub-system
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_ALREADY_INITIALIZED);

    // Step 3: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

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
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 3: Call dsHdmiInInit() again
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 4: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

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
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NOT_INITIALIZED);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 4: Call dsHdmiInTerm() without initializing the HDMI input sub-system
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NOT_INITIALIZED);

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
 * |02|Call dsHdmiInGetNumberOfInputs() to fetch the number of HDMI input ports |pNumberOfinputs: uint8_t*| dsERR_NONE | Number should be between 0 and max number of inputs defined in dsHdmiInPort_t |
 * |03|Call dsHdmiInGetNumberOfInputs() to fetch the number of HDMI input ports |pNumberOfinputs: uint8_t*| dsERR_NONE | Number should be between 0 and max number of inputs defined in dsHdmiInPort_t |
 * |04|Compare the results to make sure they are equal || Success | The values should be equal |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInGetNumberOfInputs(void) {
    gTestID = 5;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    uint8_t numInputs1, numInputs2;

    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Call dsHdmiInGetNumberOfInputs() to fetch the number of HDMI input ports
    UT_ASSERT_EQUAL(dsHdmiInGetNumberOfInputs(&numInputs1), dsERR_NONE);

    // Step 3: Call dsHdmiInGetNumberOfInputs() again to fetch the number of HDMI input ports
    UT_ASSERT_EQUAL(dsHdmiInGetNumberOfInputs(&numInputs2), dsERR_NONE);

    // Step 4: Compare the results to make sure they are equal
    UT_ASSERT_EQUAL(numInputs1, numInputs2);

    // Step 5: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

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
    UT_ASSERT_EQUAL(dsHdmiInGetNumberOfInputs(&numInputs), dsERR_NOT_INITIALIZED);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsHdmiInGetNumberOfInputs() with NULL as the parameter
    UT_ASSERT_EQUAL(dsHdmiInGetNumberOfInputs(NULL), dsERR_INVALID_PARAM);

    // Step 4: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 5: Call dsHdmiInGetNumberOfInputs() after termination of the HDMI input sub-system
    UT_ASSERT_EQUAL(dsHdmiInGetNumberOfInputs(&numInputs), dsERR_NOT_INITIALIZED);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}


/**
 * @brief Ensure dsHdmiInGetStatus() correctly fetches the HDMI input port status during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 007@n
 * 
 * **Dependencies:** None.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Call dsHdmiInGetStatus() with valid pointer |dsHdmiInStatus_t*| dsERR_NONE | Status information should be populated. Validate the output structure |
 * |03|Call dsHdmiInGetStatus() with valid pointer |dsHdmiInStatus_t*| dsERR_NONE | Status information should be populated. Validate the output structure |
 * |04|Compare the returned values to make sure they are equal || Success | The values should be the same |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInGetStatus(void) {
    gTestID = 7;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    dsHdmiInStatus_t status1, status2;

    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Call dsHdmiInGetStatus()
    UT_ASSERT_EQUAL(dsHdmiInGetStatus(&status1), dsERR_NONE);

    // Step 3: Call dsHdmiInGetStatus() again
    UT_ASSERT_EQUAL(dsHdmiInGetStatus(&status2), dsERR_NONE);

    // Step 4: Compare the returned values to make sure they are equal
    UT_ASSERT_EQUAL(status1.isPresented, status2.isPresented);
    UT_ASSERT_EQUAL(status1.activePort, status2.activePort);
    for (int i = 0; i < dsHDMI_IN_PORT_MAX; i++) {
        UT_ASSERT_EQUAL(status1.isPortConnected[i], status2.isPortConnected[i]);
    }

    // Step 5: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

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
    UT_ASSERT_EQUAL(dsHdmiInGetStatus(&status), dsERR_NOT_INITIALIZED);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsHdmiInGetStatus() with NULL as the parameter
    UT_ASSERT_EQUAL(dsHdmiInGetStatus(NULL), dsERR_INVALID_PARAM);

    // Step 4: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 5: Call dsHdmiInGetStatus() after terminating the HDMI input sub-system
    UT_ASSERT_EQUAL(dsHdmiInGetStatus(&status), dsERR_NOT_INITIALIZED);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsHdmiInSelectPort() correctly selects an HDMI input port during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 009@n
 * 
 * **Dependencies:** None.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Call dsHdmiInSelectPort() |dsHDMI_IN_PORT_0, bool: false, dsVideoPlane_PRIMARY| dsERR_NONE | Port 0 should be selected |
 * |03|Call dsHdmiInSelectPort() |dsHDMI_IN_PORT_1, bool: true, dsVideoPlane_SECONDARY| dsERR_NONE | Port 1 should be selected |
 * |04|Call dsHdmiInSelectPort() |dsHDMI_IN_PORT_2, bool: false, dsVideoPlane_PRIMARY| dsERR_NONE | Port 2 should be selected |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInSelectPort(void) {
    gTestID = 9;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Call dsHdmiInSelectPort() to select Port 0
    UT_ASSERT_EQUAL(dsHdmiInSelectPort(dsHDMI_IN_PORT_0, false, dsVideoPlane_PRIMARY), dsERR_NONE);

    // Step 3: Call dsHdmiInSelectPort() to select Port 1
    UT_ASSERT_EQUAL(dsHdmiInSelectPort(dsHDMI_IN_PORT_1, true, dsVideoPlane_SECONDARY), dsERR_NONE);

    // Step 4: Call dsHdmiInSelectPort() to select Port 2
    UT_ASSERT_EQUAL(dsHdmiInSelectPort(dsHDMI_IN_PORT_2, false, dsVideoPlane_PRIMARY), dsERR_NONE);

    // Step 5: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

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
 * |01|Call dsHdmiInSelectPort() without initializing the HDMI input sub-system |dsHDMI_IN_PORT_0, bool: false, dsVideoPlane_PRIMARY| dsERR_NOT_INITIALIZED | Should Pass |
 * |02|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |03|Call dsHdmiInSelectPort() with invalid value |dsHDMI_IN_PORT_MAX, bool: false, dsVideoPlane_PRIMARY| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInSelectPort() with invalid plane value |dsHDMI_IN_PORT_0, bool: false, dsVideoPlane_MAX| dsERR_INVALID_PARAM | Should Pass |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |06|Call dsHdmiInSelectPort() after terminating the HDMI input sub-system |dsHDMI_IN_PORT_0, bool: false, dsVideoPlane_PRIMARY| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInSelectPort(void) {
    gTestID = 10;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    // Step 1: Call dsHdmiInSelectPort() without initializing the HDMI input sub-system
    UT_ASSERT_EQUAL(dsHdmiInSelectPort(dsHDMI_IN_PORT_0, false, dsVideoPlane_PRIMARY), dsERR_NOT_INITIALIZED);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsHdmiInSelectPort() with an invalid value
    UT_ASSERT_EQUAL(dsHdmiInSelectPort(dsHDMI_IN_PORT_MAX, false, dsVideoPlane_PRIMARY), dsERR_INVALID_PARAM);

    // Step 4: Call dsHdmiInSelectPort() with an invalid plane value
    UT_ASSERT_EQUAL(dsHdmiInSelectPort(dsHDMI_IN_PORT_0, false, dsVideoPlane_MAX), dsERR_INVALID_PARAM);

    // Step 5: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 6: Call dsHdmiInSelectPort() after terminating the HDMI input sub-system
    UT_ASSERT_EQUAL(dsHdmiInSelectPort(dsHDMI_IN_PORT_0, false, dsVideoPlane_PRIMARY), dsERR_NOT_INITIALIZED);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsHdmiInScaleVideo() correctly scales the HDMI input video during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 011@n
 * 
 * **Dependencies:** HDMI input hardware is properly connected and functioning.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Scale HDMI input video using dsHdmiInScaleVideo() |x=0, y=0, width=800, height=600| dsERR_NONE | Video should be scaled |
 * |03|Scale HDMI input video using dsHdmiInScaleVideo() |x=10, y=10, width=1000, height=800| dsERR_NONE | Video should be scaled |
 * |04|Scale HDMI input video using dsHdmiInScaleVideo() |x=-10, y=-10, width=800, height=600| dsERR_NONE | Video should be scaled |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInScaleVideo(void) {
    gTestID = 11;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Scale HDMI input video (x=0, y=0, width=800, height=600)
    UT_ASSERT_EQUAL(dsHdmiInScaleVideo(0, 0, 800, 600), dsERR_NONE);

    // Step 3: Scale HDMI input video (x=10, y=10, width=1000, height=800)
    UT_ASSERT_EQUAL(dsHdmiInScaleVideo(10, 10, 1000, 800), dsERR_NONE);

    // Step 4: Scale HDMI input video (x=-10, y=-10, width=800, height=600)
    UT_ASSERT_EQUAL(dsHdmiInScaleVideo(-10, -10, 800, 600), dsERR_NONE);

    // Step 5: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsHdmiInScaleVideo() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 012@n
 * 
 * **Dependencies:** HDMI input hardware is properly connected and functioning.@n
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
    UT_ASSERT_EQUAL(dsHdmiInScaleVideo(0, 0, 800, 600), dsERR_NOT_INITIALIZED);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

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
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 11: dsHdmiInScaleVideo() after terminating the HDMI input sub-system
    UT_ASSERT_EQUAL(dsHdmiInScaleVideo(0, 0, 800, 600), dsERR_NOT_INITIALIZED);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsHdmiInSelectZoomMode() correctly updates the zoom mode during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 013@n
 * 
 * **Dependencies:** HDMI input hardware is properly connected and functioning.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Call dsHdmiInSelectZoomMode() and loop through all valid dsVideoZoom_t |[Valid Zoom Mode]| dsERR_NONE | Zoom mode should be updated |
 * |03|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInSelectZoomMode(void) {
    gTestID = 13;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Loop through all dsVideoZoom_t values and call dsHdmiInSelectZoomMode()
    for (int i = dsVIDEO_ZOOM_NONE; i < dsVIDEO_ZOOM_MAX; i++) {
        dsVideoZoom_t zoomMode = i;
        UT_ASSERT_EQUAL(dsHdmiInSelectZoomMode(zoomMode), dsERR_NONE);
    }

    // Step 3: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

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
 * |03|Call dsHdmiInSelectZoomMode() with invalid value |dsVIDEO_ZOOM_MAX| dsERR_INVALID_PARAM | Should Pass |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * |05|Call dsHdmiInSelectZoomMode() without terminating the HDMI input sub-system |dsVIDEO_ZOOM_NONE| dsERR_NOT_INITIALIZED | Should Pass |
 * 
 * @note Testing for the `dsERR_OPERATION_NOT_SUPPORTED` and `dsERR_OPERATION_FAILED` might be challenging since it requires a specific scenario where the attempted operation is not supported.
 * 
 */
void test_l1_dsHdmiIn_negative_dsHdmiInSelectZoomMode(void) {
    gTestID = 14;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    // Step 1: Call dsHdmiInSelectZoomMode() without initializing the HDMI input sub-system
    UT_ASSERT_EQUAL(dsHdmiInSelectZoomMode(dsVIDEO_ZOOM_NONE), dsERR_NOT_INITIALIZED);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsHdmiInSelectZoomMode() with invalid value (dsVIDEO_ZOOM_MAX)
    UT_ASSERT_EQUAL(dsHdmiInSelectZoomMode(dsVIDEO_ZOOM_MAX), dsERR_INVALID_PARAM);

    // Step 4: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 5: Call dsHdmiInSelectZoomMode() without terminating the HDMI input sub-system
    UT_ASSERT_EQUAL(dsHdmiInSelectZoomMode(dsVIDEO_ZOOM_NONE), dsERR_NOT_INITIALIZED);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsHdmiInGetCurrentVideoMode() correctly retrieves the current HDMI video mode during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 015@n
 * 
 * **Dependencies:** HDMI input hardware is properly connected and functioning.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Retrieve the current HDMI video mode using dsHdmiInGetCurrentVideoMode() |dsVideoPortResolution_t*| dsERR_NONE | Video mode should be retrieved |
 * |03|Retrieve the current HDMI video mode using dsHdmiInGetCurrentVideoMode() |dsVideoPortResolution_t*| dsERR_NONE | Video mode should be retrieved |
 * |04|Ensure returned values are the same| |Success| The values should be the same |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInGetCurrentVideoMode(void) {
    gTestID = 15;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    dsVideoPortResolution_t resolution1;
    dsVideoPortResolution_t resolution2;
    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Retrieve the current HDMI video mode using dsHdmiInGetCurrentVideoMode()
    UT_ASSERT_EQUAL(dsHdmiInGetCurrentVideoMode(&resolution1), dsERR_NONE);
    UT_ASSERT_EQUAL(dsHdmiInGetCurrentVideoMode(&resolution2), dsERR_NONE);

    // Step 3: Ensure returned values are the same
    UT_ASSERT_EQUAL(resolution1.name, resolution2.name);
    UT_ASSERT_EQUAL(resolution1.pixelResolution, resolution2.pixelResolution);
    UT_ASSERT_EQUAL(resolution1.aspectRatio, resolution2.aspectRatio);
    UT_ASSERT_EQUAL(resolution1.stereoScopicMode, resolution2.stereoScopicMode);
    UT_ASSERT_EQUAL(resolution1.frameRate, resolution2.frameRate);
    UT_ASSERT_EQUAL(resolution1.interlaced, resolution2.interlaced);

    // Step 4: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

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
    UT_ASSERT_EQUAL(dsHdmiInGetCurrentVideoMode(&resolution), dsERR_NOT_INITIALIZED);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: dsHdmiInGetCurrentVideoMode() with NULL `resolution` pointer
    UT_ASSERT_EQUAL(dsHdmiInGetCurrentVideoMode(NULL), dsERR_INVALID_PARAM);

    // Step 4: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 5: Call dsHdmiInGetCurrentVideoMode() after terminating the HDMI input sub-system
    UT_ASSERT_EQUAL(dsHdmiInGetCurrentVideoMode(&resolution), dsERR_NOT_INITIALIZED);

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
 * |02|Call dsHdmiInRegisterConnectCB() |dsHdmiInConnectCB_t| dsERR_NONE | Callback should be registered |
 * |03|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInRegisterConnectCB(void) {
    gTestID = 17;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Call dsHdmiInRegisterConnectCB()
    UT_ASSERT_EQUAL(dsHdmiInRegisterConnectCB(mockConnectCallback), dsERR_NONE);

    // Step 3: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

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
    UT_ASSERT_EQUAL(dsHdmiInRegisterConnectCB(mockConnectCallback), dsERR_NOT_INITIALIZED);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsHdmiInRegisterConnectCB() with invalid input
    UT_ASSERT_EQUAL(dsHdmiInRegisterConnectCB(NULL), dsERR_INVALID_PARAM);

    // Step 4: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 5: Call dsHdmiInRegisterConnectCB() after termination the HDMI input sub-system
    UT_ASSERT_EQUAL(dsHdmiInRegisterConnectCB(mockConnectCallback), dsERR_NOT_INITIALIZED);

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
 * |02|Call dsHdmiInRegisterSignalChangeCB() |dsHdmiInSignalChangeCB_t| dsERR_NONE | Callback should be registered |
 * |03|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInRegisterSignalChangeCB(void) {
    gTestID = 19;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Call dsHdmiInRegisterSignalChangeCB()
    UT_ASSERT_EQUAL(dsHdmiInRegisterSignalChangeCB(mockSignalCallback), dsERR_NONE);

    // Step 3: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

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
    UT_ASSERT_EQUAL(dsHdmiInRegisterSignalChangeCB(mockSignalCallback), dsERR_NOT_INITIALIZED);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsHdmiInRegisterSignalChangeCB() with invalid input
    UT_ASSERT_EQUAL(dsHdmiInRegisterSignalChangeCB(NULL), dsERR_INVALID_PARAM);

    // Step 4: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 5: Call dsHdmiInRegisterSignalChangeCB() after terminating the HDMI input sub-system
    UT_ASSERT_EQUAL(dsHdmiInRegisterSignalChangeCB(mockSignalCallback), dsERR_NOT_INITIALIZED);

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
 * |02|Call dsHdmiInRegisterStatusChangeCB() with valid input |dsHdmiInStatusChangeCB_t| dsERR_NONE | Callback should be registered |
 * |03|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInRegisterStatusChangeCB(void) {
    gTestID = 21;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Call dsHdmiInRegisterStatusChangeCB()
    UT_ASSERT_EQUAL(dsHdmiInRegisterStatusChangeCB(mockStatusChangeCallback), dsERR_NONE);

    // Step 3: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

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
    UT_ASSERT_EQUAL(dsHdmiInRegisterStatusChangeCB(mockStatusChangeCallback), dsERR_NOT_INITIALIZED);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsHdmiInRegisterStatusChangeCB() with invalid input
    UT_ASSERT_EQUAL(dsHdmiInRegisterStatusChangeCB(NULL), dsERR_INVALID_PARAM);

    // Step 4: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 5: Call dsHdmiInRegisterStatusChangeCB() after terminating the HDMI input sub-system
    UT_ASSERT_EQUAL(dsHdmiInRegisterStatusChangeCB(mockStatusChangeCallback), dsERR_NOT_INITIALIZED);

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
 * |02|Call dsHdmiInRegisterVideoModeUpdateCB() with valid inputs |dsHdmiInVideoModeUpdateCB_t| dsERR_NONE | Callback should be registered |
 * |03|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInRegisterVideoModeUpdateCB(void) {
    gTestID = 23;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 
    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Call dsHdmiInRegisterVideoModeUpdateCB()
    UT_ASSERT_EQUAL(dsHdmiInRegisterVideoModeUpdateCB(mockVideoModeUpdateCallback), dsERR_NONE);

    // Step 3: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

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
    UT_ASSERT_EQUAL(dsHdmiInRegisterVideoModeUpdateCB(mockVideoModeUpdateCallback), dsERR_NOT_INITIALIZED);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsHdmiInRegisterVideoModeUpdateCB() with invalid input
    UT_ASSERT_EQUAL(dsHdmiInRegisterVideoModeUpdateCB(NULL), dsERR_INVALID_PARAM);

    // Step 4: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 5: Call dsHdmiInRegisterVideoModeUpdateCB() after terminating the HDMI input sub-system
    UT_ASSERT_EQUAL(dsHdmiInRegisterVideoModeUpdateCB(mockVideoModeUpdateCallback), dsERR_NOT_INITIALIZED);

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
 * |02|Call dsHdmiInRegisterAllmChangeCB() with valid input |dsHdmiInAllmChangeCB_t| dsERR_NONE | Callback should be registered |
 * |03|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInRegisterAllmChangeCB(void) {
    gTestID = 25;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Call dsHdmiInRegisterAllmChangeCB()
    UT_ASSERT_EQUAL(dsHdmiInRegisterAllmChangeCB(mockALLMChangeCallback), dsERR_NONE);

    // Step 3: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

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
    UT_ASSERT_EQUAL(dsHdmiInRegisterAllmChangeCB(mockALLMChangeCallback), dsERR_NOT_INITIALIZED);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsHdmiInRegisterAllmChangeCB() with invalid input
    UT_ASSERT_EQUAL(dsHdmiInRegisterAllmChangeCB(NULL), dsERR_INVALID_PARAM);

    // Step 4: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 5: Call dsHdmiInRegisterAllmChangeCB() after terminating the HDMI input sub-system
    UT_ASSERT_EQUAL(dsHdmiInRegisterAllmChangeCB(mockALLMChangeCallback), dsERR_NOT_INITIALIZED);
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
 * |02|Call dsHdmiInRegisterAVLatencyChangeCB() with valid input |dsAVLatencyChangeCB_t| dsERR_NONE | Callback should be registered |
 * |03|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInRegisterAVLatencyChangeCB(void) {
    gTestID = 27;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Call dsHdmiInRegisterAVLatencyChangeCB()
    UT_ASSERT_EQUAL(dsHdmiInRegisterAVLatencyChangeCB(mockLatencyChangeCallback), dsERR_NONE);

    // Step 3: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

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
    UT_ASSERT_EQUAL(dsHdmiInRegisterAVLatencyChangeCB(mockLatencyChangeCallback), dsERR_NOT_INITIALIZED);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsHdmiInRegisterAVLatencyChangeCB() with invalid input
    UT_ASSERT_EQUAL(dsHdmiInRegisterAVLatencyChangeCB(NULL), dsERR_INVALID_PARAM);

    // Step 4: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 5: Call dsHdmiInRegisterAVLatencyChangeCB() after terminating the HDMI input sub-system
    UT_ASSERT_EQUAL(dsHdmiInRegisterAVLatencyChangeCB(mockLatencyChangeCallback), dsERR_NOT_INITIALIZED);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

void mockAviContentCallback(*dsHdmiInAviContentTypeChangeCB_t)(dsHdmiInPort_t port, dsAviContentType_t avi_content_type){
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
 * |02|Call dsHdmiInRegisterAviContentTypeChangeCB() with valid input |dsHdmiInAviContentTypeChangeCB_t| dsERR_NONE | Callback should be registered |
 * |03|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsHdmiInRegisterAviContentTypeChangeCB(void) {
    gTestID = 29;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Call dsHdmiInRegisterAviContentTypeChangeCB()
    UT_ASSERT_EQUAL(dsHdmiInRegisterAviContentTypeChangeCB(mockAviContentCallback), dsERR_NONE);

    // Step 3: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

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
    UT_ASSERT_EQUAL(dsHdmiInRegisterAviContentTypeChangeCB(mockAviContentCallback), dsERR_NOT_INITIALIZED);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsHdmiInRegisterAviContentTypeChangeCB() with invalid input
    UT_ASSERT_EQUAL(dsHdmiInRegisterAviContentTypeChangeCB(NULL), dsERR_INVALID_PARAM);

    // Step 4: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 5: Call dsHdmiInRegisterAviContentTypeChangeCB() after terminating the HDMI input sub-system
    UT_ASSERT_EQUAL(dsHdmiInRegisterAviContentTypeChangeCB(mockAviContentCallback), dsERR_NOT_INITIALIZED);

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
 * |02|Call dsIsHdmiARCPort() with valid input |dsHDMI_IN_PORT_0, bool*| dsERR_NONE | Should successfully check for ARC capability |
 * |03|Call dsIsHdmiARCPort() with valid input |dsHDMI_IN_PORT_1, bool*| dsERR_NONE | Should successfully check for ARC capability |
 * |04|Call dsIsHdmiARCPort() with valid input |dsHDMI_IN_PORT_2, bool*| dsERR_NONE | Should successfully check for ARC capability |
 * |05|Call dsIsHdmiARCPort() with valid input |dsHDMI_IN_PORT_2, bool*| dsERR_NONE | Should successfully check for ARC capability |
 * |06|Compare the values of steps 4 and 5 to make sure they equal one another || Success | The values should be equal |
 * |07|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsIsHdmiARCPort(void) {
    gTestID = 31;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    bool isArcPort1, isArcPort2;

    // Step 2: Call dsIsHdmiARCPort() with valid input (dsHDMI_IN_PORT_0)
    UT_ASSERT_EQUAL(dsIsHdmiARCPort(dsHDMI_IN_PORT_0, &isArcPort1), dsERR_NONE);

    // Step 3: Call dsIsHdmiARCPort() with valid input (dsHDMI_IN_PORT_1)
    UT_ASSERT_EQUAL(dsIsHdmiARCPort(dsHDMI_IN_PORT_1, &isArcPort2), dsERR_NONE);

    // Step 4: Call dsIsHdmiARCPort() with valid input (dsHDMI_IN_PORT_2)
    UT_ASSERT_EQUAL(dsIsHdmiARCPort(dsHDMI_IN_PORT_2, &isArcPort1), dsERR_NONE);

    // Step 5: Call dsIsHdmiARCPort() with valid input (dsHDMI_IN_PORT_2)
    UT_ASSERT_EQUAL(dsIsHdmiARCPort(dsHDMI_IN_PORT_2, &isArcPort2), dsERR_NONE);

    // Step 6: Compare the values of steps 4 and 5 to make sure they equal one another
    UT_ASSERT_EQUAL(isArcPort1, isArcPort2);

    // Step 7: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

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
void test_l1_dsHdmiIn_negative_dsIsHdmiARCPort(void) {
    gTestID = 32;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Step 1: Call dsIsHdmiARCPort() without initializing the HDMI input sub-system
    UT_ASSERT_EQUAL(dsIsHdmiARCPort(dsHDMI_IN_PORT_0, NULL), dsERR_NOT_INITIALIZED);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    bool isArcPort;

    // Step 3: Call dsIsHdmiARCPort() with invalid value (dsHDMI_IN_PORT_MAX)
    UT_ASSERT_EQUAL(dsIsHdmiARCPort(dsHDMI_IN_PORT_MAX, &isArcPort), dsERR_INVALID_PARAM);

    // Step 4: Call dsIsHdmiARCPort() with invalid value (dsHDMI_IN_PORT_0) and NULL pointer
    UT_ASSERT_EQUAL(dsIsHdmiARCPort(dsHDMI_IN_PORT_0, NULL), dsERR_INVALID_PARAM);

    // Step 5: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 6: Call dsIsHdmiARCPort() after terminating the HDMI input sub-system
    UT_ASSERT_EQUAL(dsIsHdmiARCPort(dsHDMI_IN_PORT_0, &isArcPort), dsERR_NOT_INITIALIZED);

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
 * |02|Call dsGetEDIDBytesInfo() with valid inputs |dsHDMI_IN_PORT_0, unsigned char*, int*| dsERR_NONE | Should return EDID bytes information successfully |
 * |03|Call dsGetEDIDBytesInfo() with valid inputs |dsHDMI_IN_PORT_1, unsigned char*, int*| dsERR_NONE | Should return EDID bytes information successfully |
 * |04|Call dsGetEDIDBytesInfo() with valid inputs |dsHDMI_IN_PORT_2, unsigned char*, int*| dsERR_NONE | Should return EDID bytes information successfully |
 * |05|Call dsGetEDIDBytesInfo() with valid inputs |dsHDMI_IN_PORT_2, unsigned char*, int*| dsERR_NONE | Should return EDID bytes information successfully |
 * |06|Compare the results and make sure they are the same | | Success | The values should be the same |
 * |07|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsGetEDIDBytesInfo(void) {
    gTestID = 33;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    unsigned char* edidBytes1 = (unsigned char*) malloc(255);
    unsigned char* edidBytes2 = (unsigned char*) malloc(255);
    unsigned char* edidBytes3 = (unsigned char*) malloc(255);
    unsigned char* edidBytes4 = (unsigned char*) malloc(255);
    int edidSize1;
    int edidSize2;
    int edidSize3;
    int edidSize4;

    // Step 2: Call dsGetEDIDBytesInfo() with valid input (dsHDMI_IN_PORT_0)
    UT_ASSERT_EQUAL(dsGetEDIDBytesInfo(dsHDMI_IN_PORT_0, edidBytes1, &edidSize1), dsERR_NONE);

    // Step 3: Call dsGetEDIDBytesInfo() with valid input (dsHDMI_IN_PORT_1)
    UT_ASSERT_EQUAL(dsGetEDIDBytesInfo(dsHDMI_IN_PORT_1, edidBytes2, &edidSize2), dsERR_NONE);

    // Step 4: Call dsGetEDIDBytesInfo() with valid input (dsHDMI_IN_PORT_2)
    UT_ASSERT_EQUAL(dsGetEDIDBytesInfo(dsHDMI_IN_PORT_2, edidBytes3, &edidSize3), dsERR_NONE);

    // Step 5: Call dsGetEDIDBytesInfo() with valid input (dsHDMI_IN_PORT_2)
    UT_ASSERT_EQUAL(dsGetEDIDBytesInfo(dsHDMI_IN_PORT_2, edidBytes4, &edidSize4), dsERR_NONE);

    // Step 6: Compare the results and make sure they are the same
    UT_ASSERT_EQUAL(edidSize3, edidSize4);
    UT_ASSERT_TRUE(memcmp(edidSize3, edidSize4, sizeof(edidSize3)),0);

    // You may want to compare the contents of the edidBytes as well, depending on your use case.

    // Step 7: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

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
void test_l1_dsHdmiIn_negative_dsGetEDIDBytesInfo(void) {
    gTestID = 34;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    unsigned char* edidBytes = (unsigned char*) malloc(255);
    int edidSize;

    // Step 1: Call dsGetEDIDBytesInfo() without initializing the HDMI input sub-system
    UT_ASSERT_EQUAL(dsGetEDIDBytesInfo(dsHDMI_IN_PORT_0, edidBytes, &edidSize), dsERR_NOT_INITIALIZED);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsGetEDIDBytesInfo() with invalid value (dsHDMI_IN_PORT_MAX)
    UT_ASSERT_EQUAL(dsGetEDIDBytesInfo(dsHDMI_IN_PORT_MAX, edidBytes, &edidSize), dsERR_INVALID_PARAM);

    // Step 4: Call dsGetEDIDBytesInfo() with invalid value (NULL pointer)
    UT_ASSERT_EQUAL(dsGetEDIDBytesInfo(dsHDMI_IN_PORT_0, NULL, &edidSize), dsERR_INVALID_PARAM);

    // Step 5: Call dsGetEDIDBytesInfo() with invalid value (NULL pointer)
    UT_ASSERT_EQUAL(dsGetEDIDBytesInfo(dsHDMI_IN_PORT_0, edidBytes, NULL), dsERR_INVALID_PARAM);

    // Step 6: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 7: Call dsGetEDIDBytesInfo() after terminating the HDMI input sub-system
    UT_ASSERT_EQUAL(dsGetEDIDBytesInfo(dsHDMI_IN_PORT_0, edidBytes, &edidSize), dsERR_NOT_INITIALIZED);

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
 * |02|Call dsGetHDMISPDInfo() with valid input |dsHDMI_IN_PORT_0, unsigned char*| dsERR_NONE | Should return HDMI SPD information successfully |
 * |03|Call dsGetHDMISPDInfo() with valid input |dsHDMI_IN_PORT_1, unsigned char*| dsERR_NONE | Should return HDMI SPD information successfully |
 * |04|Call dsGetHDMISPDInfo() with valid input |dsHDMI_IN_PORT_2, unsigned char*| dsERR_NONE | Should return HDMI SPD information successfully |
 * |05|Call dsGetHDMISPDInfo() with valid input |dsHDMI_IN_PORT_2, unsigned char*| dsERR_NONE | Should return HDMI SPD information successfully |
 * |06|Compare values from step 4/5 and make sure they're the same || Success | The values should be the same |
 * |07|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsGetHDMISPDInfo(void) {
    gTestID = 35;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    unsigned char* spdInfo1 = (unsigned char*) malloc(sizeof(struct dsSpd_infoframe_st));
    unsigned char* spdInfo2 = (unsigned char*) malloc(sizeof(struct dsSpd_infoframe_st));
    unsigned char* spdInfo3 = (unsigned char*) malloc(sizeof(struct dsSpd_infoframe_st));
    unsigned char* spdInfo4 = (unsigned char*) malloc(sizeof(struct dsSpd_infoframe_st));

    // Step 2: Call dsGetHDMISPDInfo() with valid input (dsHDMI_IN_PORT_0)
    UT_ASSERT_EQUAL(dsGetHDMISPDInfo(dsHDMI_IN_PORT_0, spdInfo1), dsERR_NONE);

    // Step 3: Call dsGetHDMISPDInfo() with valid input (dsHDMI_IN_PORT_1)
    UT_ASSERT_EQUAL(dsGetHDMISPDInfo(dsHDMI_IN_PORT_1, spdInfo2), dsERR_NONE);

    // Step 4: Call dsGetHDMISPDInfo() with valid input (dsHDMI_IN_PORT_2)
    UT_ASSERT_EQUAL(dsGetHDMISPDInfo(dsHDMI_IN_PORT_2, spdInfo3), dsERR_NONE);

    // Step 5: Call dsGetHDMISPDInfo() with valid input (dsHDMI_IN_PORT_2)
    UT_ASSERT_EQUAL(dsGetHDMISPDInfo(dsHDMI_IN_PORT_2, spdInfo4), dsERR_NONE);

    // Step 6: Compare the results and make sure they are the same
    UT_ASSERT_EQUAL(memcmp(spdInfo3, spdInfo4,sizeof(struct dsSpd_infoframe_st)),0);

    // Step 7: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

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
void test_l1_dsHdmiIn_negative_dsGetHDMISPDInfo(void) {
    gTestID = 36;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    unsigned char* spdInfo1 (unsigned char*) malloc(sizeof(struct dsSpd_infoframe_st)); 

    // Step 1: Call dsGetHDMISPDInfo() without initializing the HDMI input sub-system
    UT_ASSERT_EQUAL(dsGetHDMISPDInfo(dsHDMI_IN_PORT_0, spdInfo1), dsERR_NOT_INITIALIZED);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsGetHDMISPDInfo() with invalid values (dsHDMI_IN_PORT_MAX)
    UT_ASSERT_EQUAL(dsGetHDMISPDInfo(dsHDMI_IN_PORT_MAX, spdInfo1), dsERR_INVALID_PARAM);

    // Step 4: Call dsGetHDMISPDInfo() with invalid values (NULL pointer)
    UT_ASSERT_EQUAL(dsGetHDMISPDInfo(dsHDMI_IN_PORT_0, NULL), dsERR_INVALID_PARAM);

    // Step 5: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 6: Call dsGetHDMISPDInfo() after terminating the HDMI input sub-system
    UT_ASSERT_EQUAL(dsGetHDMISPDInfo(dsHDMI_IN_PORT_0, spdInfo1), dsERR_NOT_INITIALIZED);

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
 * |02|Call dsSetEdidVersion() with valid values |dsHDMI_IN_PORT_0, HDMI_EDID_VER_14| dsERR_NONE | Should set EDID version successfully |
 * |03|Call dsSetEdidVersion() with valid values |dsHDMI_IN_PORT_0, HDMI_EDID_VER_20| dsERR_NONE | Should set EDID version successfully |
 * |04|Call dsSetEdidVersion() with valid values |dsHDMI_IN_PORT_1, HDMI_EDID_VER_14| dsERR_NONE | Should set EDID version successfully |
 * |05|Call dsSetEdidVersion() with valid values |dsHDMI_IN_PORT_2, HDMI_EDID_VER_14| dsERR_NONE | Should set EDID version successfully |
 * |06|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsSetEdidVersion(void) {
    gTestID = 37;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Call dsSetEdidVersion() with valid values (dsHDMI_IN_PORT_0, HDMI_EDID_VER_14)
    UT_ASSERT_EQUAL(dsSetEdidVersion(dsHDMI_IN_PORT_0, HDMI_EDID_VER_14), dsERR_NONE);

    // Step 3: Call dsSetEdidVersion() with valid values (dsHDMI_IN_PORT_0, HDMI_EDID_VER_20)
    UT_ASSERT_EQUAL(dsSetEdidVersion(dsHDMI_IN_PORT_0, HDMI_EDID_VER_20), dsERR_NONE);

    // Step 4: Call dsSetEdidVersion() with valid values (dsHDMI_IN_PORT_1, HDMI_EDID_VER_14)
    UT_ASSERT_EQUAL(dsSetEdidVersion(dsHDMI_IN_PORT_1, HDMI_EDID_VER_14), dsERR_NONE);

    // Step 5: Call dsSetEdidVersion() with valid values (dsHDMI_IN_PORT_2, HDMI_EDID_VER_14)
    UT_ASSERT_EQUAL(dsSetEdidVersion(dsHDMI_IN_PORT_2, HDMI_EDID_VER_14), dsERR_NONE);

    // Step 6: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

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
void test_l1_dsHdmiIn_negative_dsSetEdidVersion(void) {
    gTestID = 38;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Step 1: Call dsSetEdidVersion() without initializing the HDMI input sub-system
    UT_ASSERT_EQUAL(dsSetEdidVersion(dsHDMI_IN_PORT_0, HDMI_EDID_VER_14), dsERR_NOT_INITIALIZED);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsSetEdidVersion() with invalid inputs (dsHDMI_IN_PORT_MAX)
    UT_ASSERT_EQUAL(dsSetEdidVersion(dsHDMI_IN_PORT_MAX, HDMI_EDID_VER_14), dsERR_INVALID_PARAM);

    // Step 4: Call dsSetEdidVersion() with invalid inputs (HDMI_EDID_VER_MAX)
    UT_ASSERT_EQUAL(dsSetEdidVersion(dsHDMI_IN_PORT_0, HDMI_EDID_VER_MAX), dsERR_INVALID_PARAM);

    // Step 5: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 6: Call dsSetEdidVersion() without initializing the HDMI input sub-system
    UT_ASSERT_EQUAL(dsSetEdidVersion(dsHDMI_IN_PORT_0, HDMI_EDID_VER_14), dsERR_NOT_INITIALIZED);

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
 * |02|Call dsGetEdidVersion() with all valid ports and call the last one twice|[Valid Port], tv_hdmi_edid_version_t*| dsERR_NONE | Should Pass |
 * |03|Compare the values from final two calls in step 2 and make sure they match || Success | The values should be the same |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsGetEdidVersion(void) {
    gTestID = 39;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Call dsGetEdidVersion() with valid values (dsHDMI_IN_PORT_0, tv_hdmi_edid_version_t*)
    tv_hdmi_edid_version_t edid_version_1, edid_version_2;
    UT_ASSERT_EQUAL(dsGetEdidVersion(dsHDMI_IN_PORT_0, &edid_version_1), dsERR_NONE);
    UT_ASSERT_EQUAL(dsGetEdidVersion(dsHDMI_IN_PORT_1, &edid_version_1), dsERR_NONE);
    UT_ASSERT_EQUAL(dsGetEdidVersion(dsHDMI_IN_PORT_2, &edid_version_1), dsERR_NONE);
    UT_ASSERT_EQUAL(dsGetEdidVersion(dsHDMI_IN_PORT_2, &edid_version_2), dsERR_NONE);

    // Step 3: Compare the values from steps 4/5 and make sure they match
    UT_ASSERT_EQUAL(edid_version_1, edid_version_2);

    // Step 4: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

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
void test_l1_dsHdmiIn_negative_dsGetEdidVersion(void) {
    gTestID = 40;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Step 1: Call dsGetEdidVersion() without initializing the HDMI input sub-system
    tv_hdmi_edid_version_t edid_version;
    UT_ASSERT_EQUAL(dsGetEdidVersion(dsHDMI_IN_PORT_0, &edid_version), dsERR_NOT_INITIALIZED);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsGetEdidVersion() with invalid inputs (dsHDMI_IN_PORT_MAX)
    UT_ASSERT_EQUAL(dsGetEdidVersion(dsHDMI_IN_PORT_MAX, &edid_version), dsERR_INVALID_PARAM);

    // Step 4: Call dsGetEdidVersion() with invalid inputs (NULL)
    UT_ASSERT_EQUAL(dsGetEdidVersion(dsHDMI_IN_PORT_0, NULL), dsERR_INVALID_PARAM);

    // Step 5: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 6: Call dsGetEdidVersion() without initializing the HDMI input sub-system
    UT_ASSERT_EQUAL(dsGetEdidVersion(dsHDMI_IN_PORT_0, &edid_version), dsERR_NOT_INITIALIZED);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsGetAllmStatus() correctly retrieves the ALLM status during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 041@n
 * 
 * **Dependencies:** None.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize the HDMI input sub-system using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Call dsGetAllmStatus() with valid inputs |dsHDMI_IN_PORT_0, bool*| dsERR_NONE | Should retrieve ALLM status successfully |
 * |03|Call dsGetAllmStatus() with valid inputs |dsHDMI_IN_PORT_1, bool*| dsERR_NONE | Should retrieve ALLM status successfully |
 * |04|Call dsGetAllmStatus() with valid inputs |dsHDMI_IN_PORT_2, bool*| dsERR_NONE | Should retrieve ALLM status successfully |
 * |05|Call dsGetAllmStatus() with valid inputs |dsHDMI_IN_PORT_2, bool*| dsERR_NONE | Should retrieve ALLM status successfully |
 * |06|Compare the results of steps 4/5 and make sure they are the same || Success | The returned values should be the same |
 * |07|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsGetAllmStatus(void) {
    gTestID = 41;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Call dsGetAllmStatus() with valid inputs (dsHDMI_IN_PORT_0, bool*)
    bool allm_status_1, allm_status_2;
    UT_ASSERT_EQUAL(dsGetAllmStatus(dsHDMI_IN_PORT_0, &allm_status_1), dsERR_NONE);

    // Step 3: Call dsGetAllmStatus() with valid inputs (dsHDMI_IN_PORT_1, bool*)
    UT_ASSERT_EQUAL(dsGetAllmStatus(dsHDMI_IN_PORT_1, &allm_status_2), dsERR_NONE);

    // Step 4: Call dsGetAllmStatus() with valid inputs (dsHDMI_IN_PORT_2, bool*)
    bool allm_status_3;
    UT_ASSERT_EQUAL(dsGetAllmStatus(dsHDMI_IN_PORT_2, &allm_status_3), dsERR_NONE);

    // Step 5: Call dsGetAllmStatus() with valid inputs (dsHDMI_IN_PORT_2, bool*)
    UT_ASSERT_EQUAL(dsGetAllmStatus(dsHDMI_IN_PORT_2, &allm_status_1), dsERR_NONE);

    // Step 6: Compare the results of steps 4/5 and make sure they are the same
    UT_ASSERT_EQUAL(allm_status_1, allm_status_3);

    // Step 7: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

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
void test_l1_dsHdmiIn_negative_dsGetAllmStatus(void) {
    gTestID = 42;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Step 1: Call dsGetAllmStatus() without initializing the HDMI input sub-system
    bool allm_status;
    UT_ASSERT_EQUAL(dsGetAllmStatus(dsHDMI_IN_PORT_0, &allm_status), dsERR_NOT_INITIALIZED);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsGetAllmStatus() without valid inputs (dsHDMI_IN_PORT_MAX)
    UT_ASSERT_EQUAL(dsGetAllmStatus(dsHDMI_IN_PORT_MAX, &allm_status), dsERR_INVALID_PARAM);

    // Step 4: Call dsGetAllmStatus() without valid inputs (NULL)
    UT_ASSERT_EQUAL(dsGetAllmStatus(dsHDMI_IN_PORT_0, NULL), dsERR_INVALID_PARAM);

    // Step 5: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 6: Call dsGetAllmStatus() after termination the HDMI input sub-system
    UT_ASSERT_EQUAL(dsGetAllmStatus(dsHDMI_IN_PORT_0, &allm_status), dsERR_NOT_INITIALIZED);

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
 * |02|Call dsGetSupportedGameFeaturesList() with valid inputs |dsSupportedGameFeatureList_t*| dsERR_NONE | Should retrieve list successfully |
 * |03|Call dsGetSupportedGameFeaturesList() with valid inputs |dsSupportedGameFeatureList_t*| dsERR_NONE | Should retrieve list successfully |
 * |04|Compare the returns of steps 2/3 and make sure they compare || Success | Make sure the returned are values |
 * |05|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsGetSupportedGameFeaturesList(void) {
    gTestID = 43;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Call dsGetSupportedGameFeaturesList() with valid inputs (dsSupportedGameFeatureList_t*)
    dsSupportedGameFeatureList_t supported_features_1, supported_features_2;
    UT_ASSERT_EQUAL(dsGetSupportedGameFeaturesList(&supported_features_1), dsERR_NONE);

    // Step 3: Call dsGetSupportedGameFeaturesList() with valid inputs (dsSupportedGameFeatureList_t*)
    UT_ASSERT_EQUAL(dsGetSupportedGameFeaturesList(&supported_features_2), dsERR_NONE);

    // Step 4: Compare the returns of steps 2/3 and make sure they compare
    // Note: You should implement a function to compare dsSupportedGameFeatureList_t objects
    UT_ASSERT_EQUAL(supported_features_1.gameFeatureList, supported_features_2.gameFeatureList);
    UT_ASSERT_EQUAL(supported_features_1.gameFeatureCount, supported_features_2.gameFeatureCount);

    // Step 5: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

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
void test_l1_dsHdmiIn_negative_dsGetSupportedGameFeaturesList(void) {
    gTestID = 44;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Step 1: Call dsGetSupportedGameFeaturesList() without initializing the HDMI input sub-system
    dsSupportedGameFeatureList_t supported_features;
    UT_ASSERT_EQUAL(dsGetSupportedGameFeaturesList(&supported_features), dsERR_NOT_INITIALIZED);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsGetSupportedGameFeaturesList() with invalid input (NULL)
    UT_ASSERT_EQUAL(dsGetSupportedGameFeaturesList(NULL), dsERR_INVALID_PARAM);

    // Step 4: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 5: Call dsGetSupportedGameFeaturesList() after terminating the HDMI input sub-system
    UT_ASSERT_EQUAL(dsGetSupportedGameFeaturesList(&supported_features), dsERR_NOT_INITIALIZED);

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
 * |02|Call dsHdmiInSelectPort() |dsHDMI_IN_PORT_0, bool: false, dsVideoPlane_PRIMARY| dsERR_NONE | Port 0 should be selected |
 * |03|Call dsGetAVLatency() with valid input |int*, int*| dsERR_NONE | Should retrieve AV latency values successfully |
 * |04|Call dsHdmiInTerm() to ensure deinitialization | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsGetAVLatency(void) {
    gTestID = 45;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Step 1: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Call dsHdmiInSelectPort() to select Port 0
    UT_ASSERT_EQUAL(dsHdmiInSelectPort(dsHDMI_IN_PORT_0, false, dsVideoPlane_PRIMARY), dsERR_NONE);

    // Step 3: Call dsGetAVLatency() with valid inputs (int*, int*)
    int audioLatency1, videoLatency1;
    UT_ASSERT_EQUAL(dsGetAVLatency(&audioLatency1, &videoLatency1), dsERR_NONE);

    // Step 4: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

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
void test_l1_dsHdmiIn_negative_dsGetAVLatency(void) {
    gTestID = 46;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Step 1: Call dsGetAVLatency() without initializing the HDMI input sub-system
    int audioLatency, videoLatency;
    UT_ASSERT_EQUAL(dsGetAVLatency(&audioLatency, &videoLatency), dsERR_NOT_INITIALIZED);

    // Step 2: Initialize the HDMI input sub-system using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsGetAVLatency() with valid inputs (NULL, int*)
    UT_ASSERT_EQUAL(dsGetAVLatency(NULL, &videoLatency), dsERR_INVALID_PARAM);

    // Step 4: Call dsGetAVLatency() with valid inputs (int*, NULL)
    UT_ASSERT_EQUAL(dsGetAVLatency(&audioLatency, NULL), dsERR_INVALID_PARAM);

    // Step 5: Call dsHdmiInTerm() to ensure deinitialization
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 6: Call dsGetAVLatency() after terminating the HDMI input sub-system
    UT_ASSERT_EQUAL(dsGetAVLatency(&audioLatency, &videoLatency), dsERR_NOT_INITIALIZED);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsSetEdid2AllmSupport() sets the EDID ALLM support correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 047@n
 * 
 * **Dependencies:** HDMI input device supporting EDID ALLM.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize HDMI input using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Call dsSetEdid2AllmSupport() with all valid ports and enable EDID ALLM support | iHdmiPort: dsHDMI_IN_PORT_0, allmSupport: true | dsERR_NONE | Should Pass |
 * |03|Call dsSetEdid2AllmSupport() to disable EDID ALLM support | iHdmiPort: dsHDMI_IN_PORT_0, allmSupport: false | dsERR_NONE | Should Pass |
 * |04|Terminate the HDMI input using dsHdmiInTerm() | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsHdmiIn_positive_dsSetEdid2AllmSupport(void) {
    gTestID = 47;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Step 1: Initialize HDMI input using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Call dsSetEdid2AllmSupport() with all valid ports and enable EDID ALLM support
    UT_ASSERT_EQUAL(dsSetEdid2AllmSupport(dsHDMI_IN_PORT_0, true), dsERR_NONE);
    UT_ASSERT_EQUAL(dsSetEdid2AllmSupport(dsHDMI_IN_PORT_1, true), dsERR_NONE);
    UT_ASSERT_EQUAL(dsSetEdid2AllmSupport(dsHDMI_IN_PORT_2, true), dsERR_NONE);

    // Step 3: Call dsSetEdid2AllmSupport() to disable EDID ALLM support
    UT_ASSERT_EQUAL(dsSetEdid2AllmSupport(dsHDMI_IN_PORT_0, false), dsERR_NONE);

    // Step 4: Terminate the HDMI input using dsHdmiInTerm()
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

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
void test_l1_dsHdmiIn_negative_dsSetEdid2AllmSupport(void) {
    gTestID = 48;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Step 1: Call dsSetEdid2AllmSupport() without prior initialization of HDMI input
    UT_ASSERT_EQUAL(dsSetEdid2AllmSupport(dsHDMI_IN_PORT_0, true), dsERR_NOT_INITIALIZED);

    // Step 2: Initialize HDMI input using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsSetEdid2AllmSupport() with an invalid HDMI port
    UT_ASSERT_EQUAL(dsSetEdid2AllmSupport(dsHDMI_IN_PORT_MAX, true), dsERR_INVALID_PARAM);

    // Step 4: Terminate the HDMI input using dsHdmiInTerm()
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 5: Call dsSetEdid2AllmSupport() after termination
    UT_ASSERT_EQUAL(dsSetEdid2AllmSupport(dsHDMI_IN_PORT_0, true), dsERR_NOT_INITIALIZED);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsGetEdid2AllmSupport() gets the EDID ALLM support correctly during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 049@n
 * 
 * **Dependencies:** HDMI input device supporting EDID ALLM.@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize HDMI input using dsHdmiInInit() | | dsERR_NONE | Should Pass |
 * |02|Call dsGetEdid2AllmSupport() with all valid ports, and call the last port twice to verify EDID ALLM support | iHdmiPort: dsHDMI_IN_PORT_0, allmSupport: bool* | dsERR_NONE | Should Pass |
 * |03|Compare the returned values from steps 2/3 and verify that they are the same |  | success | The values should be the same |
 * |04|Terminate the HDMI input using dsHdmiInTerm() | | dsERR_NONE | Clean up after test |
 * 
 * @note Ensure that the device supports querying of the EDID ALLM feature before running this test.
 * 
 */
void test_l1_dsHdmiIn_positive_dsGetEdid2AllmSupport(void) {
    gTestID = 49;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Step 1: Initialize HDMI input using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 2: Call dsGetEdid2AllmSupport() to verify EDID ALLM support
    bool allmSupport1, allmSupport2;
    UT_ASSERT_EQUAL(dsGetEdid2AllmSupport(dsHDMI_IN_PORT_0, &allmSupport1), dsERR_NONE);
    UT_ASSERT_EQUAL(dsGetEdid2AllmSupport(dsHDMI_IN_PORT_1, &allmSupport1), dsERR_NONE);
    UT_ASSERT_EQUAL(dsGetEdid2AllmSupport(dsHDMI_IN_PORT_2, &allmSupport1), dsERR_NONE);
    UT_ASSERT_EQUAL(dsGetEdid2AllmSupport(dsHDMI_IN_PORT_2, &allmSupport2), dsERR_NONE);

    // Step 3: Compare the returned values from steps 2/3 and verify that they are the same
    UT_ASSERT_EQUAL(allmSupport1, allmSupport2);

    // Step 4: Terminate the HDMI input using dsHdmiInTerm()
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

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
void test_l1_dsHdmiIn_negative_dsGetEdid2AllmSupport(void) {
    gTestID = 50;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    bool allmSupport;
    UT_ASSERT_EQUAL(dsGetEdid2AllmSupport(dsHDMI_IN_PORT_0, &allmSupport), dsERR_NOT_INITIALIZED);

    // Step 2: Initialize HDMI input using dsHdmiInInit()
    UT_ASSERT_EQUAL(dsHdmiInInit(), dsERR_NONE);

    // Step 3: Call dsGetEdid2AllmSupport() with invalid inputs
    UT_ASSERT_EQUAL(dsGetEdid2AllmSupport(dsHDMI_IN_PORT_MAX, &allmSupport), dsERR_INVALID_PARAM);

    // Step 4: Call dsGetEdid2AllmSupport() with invalid inputs
    UT_ASSERT_EQUAL(dsGetEdid2AllmSupport(dsHDMI_IN_PORT_0, NULL), dsERR_INVALID_PARAM);

    // Step 5: Terminate the HDMI input using dsHdmiInTerm()
    UT_ASSERT_EQUAL(dsHdmiInTerm(), dsERR_NONE);

    // Step 6: Call dsGetEdid2AllmSupport() without initializing the HDMI input sub-system again
    UT_ASSERT_EQUAL(dsGetEdid2AllmSupport(dsHDMI_IN_PORT_0, &allmSupport), dsERR_NOT_INITIALIZED);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main test(s) for this module
 *
 * @return int - 0 on success, otherwise failure
 */
int test_l1_dsHdmiIn_register ( void )
{
	/* add a suite to the registry */
	pSuite = UT_add_suite( "[L1 dsHdmiIn]", NULL, NULL );
	if ( NULL == pSuite )
	{
		return -1;
	}	

	UT_add_test( pSuite, "dsHdmiInInit_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInInit );
	UT_add_test( pSuite, "dsHdmiInInit_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInInit );
	UT_add_test( pSuite, "dsHdmiInTerm_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInTerm );
	UT_add_test( pSuite, "dsHdmiInTerm_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInTerm );
	UT_add_test( pSuite, "dsHdmiInGetNumberOfInputs_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInGetNumberOfInputs);
	UT_add_test( pSuite, "dsHdmiInGetNumberOfInputs_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInGetNumberOfInputs);
	UT_add_test( pSuite, "dsHdmiInGetStatus_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInGetStatus );
	UT_add_test( pSuite, "dsHdmiInGetStatus_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInGetStatus );
	UT_add_test( pSuite, "dsHdmiInSelectPort_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInSelectPort );
	UT_add_test( pSuite, "dsHdmiInSelectPort_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInSelectPort );
	UT_add_test( pSuite, "dsHdmiInScaleVideo_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInScaleVideo );
	UT_add_test( pSuite, "dsHdmiInScaleVideo_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInScaleVideo );
	UT_add_test( pSuite, "dsHdmiInSelectZoomMode_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInSelectZoomMode );
	UT_add_test( pSuite, "dsHdmiInSelectZoomMode_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInSelectZoomMode );
	UT_add_test( pSuite, "dsHdmiInGetCurrentVideoMode_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInGetCurrentVideoMode );
	UT_add_test( pSuite, "dsHdmiInGetCurrentVideoMode_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInGetCurrentVideoMode );
	UT_add_test( pSuite, "dsHdmiInRegisterConnectCB_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInRegisterConnectCB );
	UT_add_test( pSuite, "dsHdmiInRegisterConnectCB_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInRegisterConnectCB );
	UT_add_test( pSuite, "dsHdmiInRegisterSignalChangeCB_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInRegisterSignalChangeCB );
	UT_add_test( pSuite, "dsHdmiInRegisterSignalChangeCB_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInRegisterSignalChangeCB );
	UT_add_test( pSuite, "dsHdmiInRegisterStatusChangeCB_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInRegisterStatusChangeCB );
	UT_add_test( pSuite, "dsHdmiInRegisterStatusChangeCB_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInRegisterStatusChangeCB );
	UT_add_test( pSuite, "dsHdmiInRegisterVideoModeUpdateCB_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInRegisterVideoModeUpdateCB );
	UT_add_test( pSuite, "dsHdmiInRegisterVideoModeUpdateCB_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInRegisterVideoModeUpdateCB );
	UT_add_test( pSuite, "dsHdmiInRegisterAllmChangeCB_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInRegisterAllmChangeCB );
	UT_add_test( pSuite, "dsHdmiInRegisterAllmChangeCB_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInRegisterAllmChangeCB );
	UT_add_test( pSuite, "dsHdmiInRegisterAVLatencyChangeCB_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInRegisterAVLatencyChangeCB );
	UT_add_test( pSuite, "dsHdmiInRegisterAVLatencyChangeCB_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInRegisterAVLatencyChangeCB );
	UT_add_test( pSuite, "dsHdmiInRegisterAviContentTypeChangeCB_L1_positive" ,test_l1_dsHdmiIn_positive_dsHdmiInRegisterAviContentTypeChangeCB );
	UT_add_test( pSuite, "dsHdmiInRegisterAviContentTypeChangeCB_L1_negative" ,test_l1_dsHdmiIn_negative_dsHdmiInRegisterAviContentTypeChangeCB );
	UT_add_test( pSuite, "dsIsHdmiARCPort_L1_positive" ,test_l1_dsHdmiIn_positive_dsIsHdmiARCPort );
	UT_add_test( pSuite, "dsIsHdmiARCPort_L1_negative" ,test_l1_dsHdmiIn_negative_dsIsHdmiARCPort );
	UT_add_test( pSuite, "dsGetEDIDBytesInfo_L1_positive" ,test_l1_dsHdmiIn_positive_dsGetEDIDBytesInfo );
	UT_add_test( pSuite, "dsGetEDIDBytesInfo_L1_negative" ,test_l1_dsHdmiIn_negative_dsGetEDIDBytesInfo );
	UT_add_test( pSuite, "dsGetHDMISPDInfo_L1_positive" ,test_l1_dsHdmiIn_positive_dsGetHDMISPDInfo );
	UT_add_test( pSuite, "dsGetHDMISPDInfo_L1_negative" ,test_l1_dsHdmiIn_negative_dsGetHDMISPDInfo );
	UT_add_test( pSuite, "dsSetEdidVersion_L1_positive" ,test_l1_dsHdmiIn_positive_dsSetEdidVersion );
	UT_add_test( pSuite, "dsSetEdidVersion_L1_negative" ,test_l1_dsHdmiIn_negative_dsSetEdidVersion );
	UT_add_test( pSuite, "dsGetEdidVersion_L1_positive" ,test_l1_dsHdmiIn_positive_dsGetEdidVersion );
	UT_add_test( pSuite, "dsGetEdidVersion_L1_negative" ,test_l1_dsHdmiIn_negative_dsGetEdidVersion );
	UT_add_test( pSuite, "dsGetAllmStatus_L1_positive" ,test_l1_dsHdmiIn_positive_dsGetAllmStatus );
	UT_add_test( pSuite, "dsGetAllmStatus_L1_negative" ,test_l1_dsHdmiIn_negative_dsGetAllmStatus );
	UT_add_test( pSuite, "dsGetSupportedGameFeaturesList_L1_positive" ,test_l1_dsHdmiIn_positive_dsGetSupportedGameFeaturesList );
	UT_add_test( pSuite, "dsGetSupportedGameFeaturesList_L1_negative" ,test_l1_dsHdmiIn_negative_dsGetSupportedGameFeaturesList );
	UT_add_test( pSuite, "dsGetAVLatency_L1_positive" ,test_l1_dsHdmiIn_positive_dsGetAVLatency );
	UT_add_test( pSuite, "dsGetAVLatency_L1_negative" ,test_l1_dsHdmiIn_negative_dsGetAVLatency );
    UT_add_test( pSuite, "test_l1_dsHdmiIn_positive_dsSetEdid2AllmSupport" ,test_l1_dsHdmiIn_positive_dsSetEdid2AllmSupport );
	UT_add_test( pSuite, "test_l1_dsHdmiIn_negative_dsSetEdid2AllmSupport" ,test_l1_dsHdmiIn_negative_dsSetEdid2AllmSupport );
	UT_add_test( pSuite, "test_l1_dsHdmiIn_positive_dsGetEdid2AllmSupport" ,test_l1_dsHdmiIn_positive_dsGetEdid2AllmSupport );
	UT_add_test( pSuite, "test_l1_dsHdmiIn_negative_dsGetEdid2AllmSupport" ,test_l1_dsHdmiIn_negative_dsGetEdid2AllmSupport );
	

	return 0;
} 

/** @} */ // End of DS HAL Hdmi Input L1 tests
/** @} */ // End of DS HdmiIn HALTEST
/** @} */ // End of Device Settings HAL
/** @} */ // End of Device Settings Module
/** @} */ // End of HPK