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
 * @addtogroup Device_Settings_HAL Device Settings HAL
 * @par Application API Specification
 * Described herein are the DeviceSettings HAL types and functions that are part of
 * the Display subsystem. The Display subsystem manages system-specific HAL operations.
 *  @{
 */

/**
*   @defgroup dsDisplay_HALTEST DS Display HALTEST
 *  @{
 * @par Application API Specification
 * dsDisplay HAL provides an interface for managing the Display settings for the device settings module
 */

/**
 * @defgroup dsDisplay_HALTESTS_L1 DS Display HAL Tests L1 File
 *  @{
 */

/**
* @file test_l1_dsDisplay.c
* @page Device Settings
* @subpage Display
*
* ## Module's Role
* This module includes Level 1 functional tests (success and failure scenarios)
* This is to ensure that the API meets the operational requirements of the Power Manager across all vendors
*
* **Pre-Conditions:**  None@n
* **Dependencies:** None@n
*
* Ref to API Definition specification documentation : [ds-display_halSpec.md](../../../docs/pages/ds-display_halSpec.md)
*/


#include <string.h>
#include <stdlib.h>

#include <ut.h>
#include <ut_log.h>
#include "stdint.h"
#include "dsDisplay.h"
#include "dsVideoPortSettings.h"

static int gTestGroup = 1;
static int gTestID = 1;

/**
 * @brief Ensure dsDisplayInit() initializes the DS Display sub-system correctly during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 001@n
 * 
 * **Pre-Conditions:**@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsDisplayInit() to initialize the module| | dsERR_NONE | Initialization should succeed |
 * |02|Terminate the DS Display sub-system with dsDisplayTerm() | | dsERR_NONE | Termination should succeed |
 * |03|Reinitialize the display sub-system with dsDisplayInit() to check for reinitialization capability| | dsERR_NONE | Initialization should succeed |
 * |04|Terminate the DS Display sub-system with dsDisplayTerm() | | dsERR_NONE | Termination should succeed |
 * 
 */
void test_l1_dsDisplay_positive_dsDisplayInit(void) {
    // Start of the test
    gTestID = 1;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result;

    // Step 01: Initialize the display module
    result = dsDisplayInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Terminate the display module
    result = dsDisplayTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Reinitialize the display module to check for reinitialization capability
    result = dsDisplayInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 04: Terminate the display module again
    result = dsDisplayTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // End of the test
    UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsDisplayInit() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 002@n
 * 
 * **Pre-Conditions:**@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize the module with dsDisplayInit() | | dsERR_NONE | Initialization should succeed |
 * |02|Call dsDisplayInit() again to check if it returns an error when the module is already initialized | | dsERR_ALREADY_INITIALIZED | Should return error indicating the module is already initialized |
 * |03|Terminate the module with dsDisplayTerm() | | dsERR_NONE | Termination should succeed |
 * 
 * @note Scenarios like dsERR_GENERAL are not included in this test plan due to the challenges in realistic simulation. Each test case is functionally independent with proper initialization and termination steps.
 */
void test_l1_dsDisplay_negative_dsDisplayInit(void) {
    // Start of the test
    gTestID = 2; 
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result;

    // Step 01: Initialize the display module
    result = dsDisplayInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Attempt to initialize the display module again
    result = dsDisplayInit();
    UT_ASSERT_EQUAL(result, dsERR_ALREADY_INITIALIZED);

    // Step 03: Terminate the display module
    result = dsDisplayTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // End of the test
    UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsDisplayTerm() terminates the display sub-system correctly during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 003@n
 * 
 * **Pre-Conditions:**@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize the display sub-system with dsDisplayInit() | | dsERR_NONE | Initialization should succeed |
 * |02|Terminate the display sub-system with dsDisplayTerm() | | dsERR_NONE | Termination should succeed |
 * |03|Reinitialize the display sub-system with dsDisplayInit() to check for reinitialization capability | | dsERR_NONE | Reinitialization should succeed |
 * |04|Terminate the display sub-system again with dsDisplayTerm() to confirm termination capability | | dsERR_NONE | Termination should succeed again |
 * 
 */
void test_l1_dsDisplay_positive_dsDisplayTerm(void) {
    // Start of the test
    gTestID = 3; 
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result;

    // Step 01: Initialize the display sub-system
    result = dsDisplayInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Terminate the display sub-system
    result = dsDisplayTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Reinitialize the display sub-system to check for reinitialization
    result = dsDisplayInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 04: Terminate the display sub-system again to confirm termination capability
    result = dsDisplayTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // End of the test
    UT_LOG("\n Out %s\n", __FUNCTION__);
}

/**
 * @brief Ensure dsDisplayTerm() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 004@n
 * 
 * **Pre-Conditions:**@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsDisplayTerm() without initializing the display sub-system | | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * |02|Initialize the display sub-system with dsDisplayInit() | | dsERR_NONE | Initialization should succeed |
 * |03|Terminate the display sub-system with dsDisplayTerm() | | dsERR_NONE | Termination should succeed |
 * |04|Call dsDisplayTerm() again after termination | | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * 
 * @note The ability to test scenarios like dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might require specific setup or environment configuration.
 */
void test_l1_dsDisplay_negative_dsDisplayTerm(void) {
    // Start of the test
    gTestID = 4; 
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result;

    // Step 01: Call dsDisplayTerm() without initializing the display sub-system
    result = dsDisplayTerm();
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize the display sub-system
    result = dsDisplayInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Terminate the display sub-system
    result = dsDisplayTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 04: Call dsDisplayTerm() again after termination
    result = dsDisplayTerm();
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

    // End of the test
    UT_LOG("\n Out %s\n", __FUNCTION__);
}



/**
 * @brief Ensure dsGetDisplay() retrieves the handle of the connected display device correctly during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 005@n
 * 
 * **Pre-Conditions:**@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize the display sub-system with dsDisplayInit() | | dsERR_NONE | Initialization should succeed |
 * |02|Call dsGetDisplay() Loop through all based on kSupportedPortTypes |vType: [Valid Port Type], int, intptr_t*  | dsERR_NONE and valid handle | Handle of the display device should be retrieved successfully |
 * |03|Call a the last value again, and compare the results |  |Success | The values should be the same |
 * |04|Terminate the display sub-system with dsDisplayTerm() | | dsERR_NONE | Termination should succeed |
 * 
 * @note valid ports can be retrieved from kSupportedPortTypes which can be retrieved from dsVideoPortSettings.
 */
void test_l1_dsDisplay_positive_dsGetDisplay(void) {
    // Start of the test
    gTestID = 5;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result;
    intptr_t displayHandle1, displayHandle2;
    size_t numPorts = sizeof(kSupportedPortTypes) / sizeof(kSupportedPortTypes[0]);

    // Step 01: Initialize the display sub-system
    result = dsDisplayInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    for (size_t i = 0; i < numPorts; i++) {
        dsVideoPortType_t vType = kSupportedPortTypes[i];

        // Step 02: Call dsGetDisplay() for each valid port
        result = dsGetDisplay(vType, 1, &displayHandle1);
        UT_ASSERT_EQUAL(result, dsERR_NONE);
        UT_LOG("Display handle for port type %d: %ld\n", vType, (long)displayHandle1);

        // Step 03: Call the last value again, and compare the results
        result = dsGetDisplay(vType, 1, &displayHandle2);
        UT_ASSERT_EQUAL(result, dsERR_NONE);
        UT_ASSERT_EQUAL(displayHandle1, displayHandle2);
        UT_LOG("Repeated display handle for port type %d: %ld\n", vType, (long)displayHandle2);
    }

    // Step 04: Terminate the display sub-system
    result = dsDisplayTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // End of the test
    UT_LOG("\n Out %s\n", __FUNCTION__);
}




/**
 * @brief Ensure dsGetDisplay() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 006@n
 * 
 * **Pre-Conditions:**@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetDisplay() without initializing the display sub-system | vType: [Valid Port Type], int=1, intptr_t* | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * |02|Initialize the display sub-system with dsDisplayInit() | | dsERR_NONE | Initialization should succeed |
 * |03|Call dsGetDisplay() with invalid parameter video type | vType: dsVIDEOPORT_TYPE_MAX, int=1, intptr_t* | dsERR_INVALID_PARAM | Should return error indicating invalid parameters |
 * |04|Call dsGetDisplay() with invalid index | vType: [Valid Port Type], int=-1, intptr_t* | dsERR_INVALID_PARAM | Should return error indicating invalid parameters |
 * |05|Call dsGetDisplay() with NULL | vType:dsVIDEOPORT_TYPE_HDMI, int=1, NULL | dsERR_INVALID_PARAM | Should return error indicating invalid parameters |
 * |06|Terminate the display sub-system with dsDisplayTerm() | | dsERR_NONE | Termination should succeed |
 * |07|Call dsGetDisplay() without initializing the display sub-system |vType: [Valid Port Type], int=1, intptr_t* | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * 
 * @note The ability to test scenarios like dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might require specific setup or environment configuration.
 */
void test_l1_dsDisplay_negative_dsGetDisplay(void) {
    // Start of the test
    gTestID = 6; 
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result;
    intptr_t displayHandle;

    // Step 01: Call dsGetDisplay() without initializing the display sub-system
    result = dsGetDisplay(kSupportedPortTypes[0], 1, &displayHandle);
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize the display sub-system
    result = dsDisplayInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Call dsGetDisplay() with invalid video type
    result = dsGetDisplay(dsVIDEOPORT_TYPE_MAX, 1, &displayHandle);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    // Step 04: Call dsGetDisplay() with invalid index
    result = dsGetDisplay(kSupportedPortTypes[0], -1, &displayHandle);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    // Step 05: Call dsGetDisplay() with NULL handle
    result = dsGetDisplay(kSupportedPortTypes[0], 1, NULL);
    UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

    // Step 06: Terminate the display sub-system
    result = dsDisplayTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 07: Call dsGetDisplay() again after termination
    result = dsGetDisplay(kSupportedPortTypes[i], 1, &displayHandle);
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

    // End of the test
    UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetEDID() retrieves the EDID information correctly during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 007@n
 * 
 * **Pre-Conditions:**@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize the display sub-system and get a display device handle | | dsERR_NONE | Initialization and handle retrieval should succeed |
 * |02|Call dsGetDisplay() Loop through all valid ports in kSupportedPortTypes[]|vType: [Valid Port Type]_INPUT, int, intptr_t*  | dsERR_NONE and valid handle | Handle of the display device should be retrieved successfully |
 * |03|Call dsGetEDID() with the obtained display device handle | intptr_t handle, dsDisplayEDID_t *edid | dsERR_NONE and valid EDID info | EDID information should be retrieved successfully |
 * |04|Call dsGetEDID() with the obtained display device handle | intptr_t handle, dsDisplayEDID_t *edid | dsERR_NONE and valid EDID info | EDID information should be retrieved successfully |
 * |05|Compare the returned results |  | Success | The values should be the same |
 * |06|Terminate the display sub-system with dsDisplayTerm() | | dsERR_NONE | Termination should succeed |
 * 
 * @note valid ports can be retrieved from kSupportedPortTypes which can be retrieved from dsVideoPortSettings.
 * 
 */
void test_l1_dsDisplay_positive_dsGetEDID(void) {
    // Start of the test
    gTestID = 7;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result;
    intptr_t displayHandle;
    dsDisplayEDID_t edid1, edid2;

    // Step 01: Initialize the display sub-system
    result = dsDisplayInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Loop through all valid ports
    for (int i = 0; i < sizeof(kSupportedPortTypes) / sizeof(kSupportedPortTypes[0]); i++) {
        // Step 02: Get the display device handle
        result = dsGetDisplay(kSupportedPortTypes[i], i, &displayHandle);
        UT_ASSERT_EQUAL(result, dsERR_NONE);

        // Step 03: Call dsGetEDID() with the obtained handle
        result = dsGetEDID(displayHandle, &edid1);
        UT_ASSERT_EQUAL(result, dsERR_NONE);

        // Step 04: Call dsGetEDID() again with the same handle
        result = dsGetEDID(displayHandle, &edid2);
        UT_ASSERT_EQUAL(result, dsERR_NONE);

        // Step 05: Compare the returned results
        UT_ASSERT_EQUAL(memcmp(&edid1, &edid2, sizeof(dsDisplayEDID_t)), 0);
    }

    // Step 06: Terminate the display sub-system
    result = dsDisplayTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // End of the test
    UT_LOG("\n Out %s\n", __FUNCTION__);
}



/**
 * @brief Ensure dsGetEDID() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 008@n
 * 
 * **Pre-Conditions:**@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetEDID() without initializing the display sub-system or obtaining a handle | intptr_t handle, dsDisplayEDID_t *edid | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * |02|Initialize the display sub-system and obtain a display device handle | | dsERR_NONE | Initialization and handle retrieval should succeed |
 * |03|Call dsGetDisplay() Loop through all valid ports in kSupportedPortTypes[]|vType: [Valid Port Type]_INPUT, int, intptr_t*  | dsERR_NONE and valid handle | Handle of the display device should be retrieved successfully |
 * |04|Call dsGetEDID() with an invalid handle | intptr_t NULL, dsDisplayEDID_t *edid | dsERR_INVALID_PARAM | Should return error indicating invalid handle |
 * |05|Call dsGetEDID() with a NULL dsDisplayEDID_t | intptr_t handle, NULL | dsERR_INVALID_PARAM | Should return error indicating invalid handle |
 * |06|Terminate the display sub-system with dsDisplayTerm() | | dsERR_NONE | Termination should succeed |
 * |07|Call dsGetEDID() without initializing the display sub-system or obtaining a handle | | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * 
 * @note The ability to test scenarios like dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might require specific setup or environment configuration.
 * @note valid ports can be retrieved from kSupportedPortTypes which can be retrieved from dsVideoPortSettings.
 * 
 */
void test_l1_dsDisplay_negative_dsGetEDID(void) {
    // Start of the test
    gTestID = 8;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result;
    intptr_t displayHandle=0;
    dsDisplayEDID_t *edid = NULL;

    // Step 01: Call dsGetEDID() without initializing the display sub-system
    result = dsGetEDID(displayHandle, &edid);
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize the display sub-system
    result = dsDisplayInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Obtain a display device handle
    for (int i = 0; i < sizeof(kSupportedPortTypes) / sizeof(kSupportedPortTypes[0]); i++) {
        result = dsGetDisplay(kSupportedPortTypes[i], i, &displayHandle);
        UT_ASSERT_EQUAL(result, dsERR_NONE);

        // Step 04: Call dsGetEDID() with an invalid handle
        result = dsGetEDID(NULL, &edid);
        UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

        // Step 05: Call dsGetEDID() with a NULL dsDisplayEDID_t
        result = dsGetEDID(displayHandle, NULL);
        UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);
    }

    // Step 06: Terminate the display sub-system
    result = dsDisplayTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 07: Call dsGetEDID() without initializing the display sub-system
    result = dsGetEDID(displayHandle, &edid);
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

    // End of the test
    UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetEDIDBytes() retrieves the EDID buffer and length correctly during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 009@n
 * 
 * **Pre-Conditions:**@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize the display sub-system and get a display device handle | | dsERR_NONE | Initialization and handle retrieval should succeed |
 * |02|Call dsGetDisplay() Loop through all valid ports in kSupportedPortTypes[]|vType: [Valid Port Type]_INPUT, int, intptr_t*  | dsERR_NONE and valid handle | Handle of the display device should be retrieved successfully |
 * |03|Allocate memory for the EDID buffer and call dsGetEDIDBytes() with the obtained handle | intptr_t handle, unsigned char *edid, int *length | dsERR_NONE, valid EDID data, and length | EDID buffer and length should be retrieved successfully |
 * |04|Allocate memory for the EDID buffer and call dsGetEDIDBytes() with the obtained handle | intptr_t handle, unsigned char *edid, int *length | dsERR_NONE, valid EDID data, and length | EDID buffer and length should be retrieved successfully |
 * |05|Verify that the return results are the same |  | Success | The results should be the same  |
 * |06|Free the allocated EDID buffer and terminate the display sub-system with dsDisplayTerm() | | dsERR_NONE | Memory deallocation and termination should succeed |
 * 
 * @note valid ports can be retrieved from kSupportedPortTypes which can be retrieved from dsVideoPortSettings.
 * 
 */
void test_l1_dsDisplay_positive_dsGetEDIDBytes(void) {
    // Start of the test
    gTestID = 9;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result;
    intptr_t displayHandle;
    unsigned char *edid1 = (unsigned char *)malloc(256);
    unsigned char *edid2 = (unsigned char *)malloc(256);
    int length1 = 0;
    int length2 = 0;

    // Step 01: Initialize the display sub-system
    result = dsDisplayInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Loop through all valid ports
    for (int i = 0; i < sizeof(kSupportedPortTypes) / sizeof(kSupportedPortTypes[0]); i++) {
        // Step 02: Call dsGetDisplay() for each valid port
        result = dsGetDisplay(kSupportedPortTypes[i], 1, &displayHandle);
        UT_ASSERT_EQUAL(result, dsERR_NONE);
        UT_ASSERT_NOT_NULL(displayHandle);

        // Step 03 and 04: Allocate memory for the EDID buffer and call dsGetEDIDBytes() twice
        result = dsGetEDIDBytes(displayHandle, edid1, &length1);
        UT_ASSERT_EQUAL(result, dsERR_NONE);
        result = dsGetEDIDBytes(displayHandle, edid2, &length2);
        UT_ASSERT_EQUAL(result, dsERR_NONE);

        // Step 05: Verify that the return results are the same
        UT_ASSERT_EQUAL(length1, length2);
        UT_ASSERT_EQUAL(memcmp(edid1, edid2, length1), 0);

        // Free the allocated memory
        
    }
    free(edid1);
    free(edid2);

    // Step 06: Terminate the display sub-system
    result = dsDisplayTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // End of the test
    UT_LOG("\n Out %s\n", __FUNCTION__);
}

/**
 * @brief Ensure dsGetEDIDBytes() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 010@n
 * 
 * **Pre-Conditions:**@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetEDIDBytes() without initializing the display sub-system or obtaining a handle | intptr_t handle, unsigned char *edid, int *length | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * |02|Initialize the display sub-system and obtain a display device handle | | dsERR_NONE | Initialization and handle retrieval should succeed |
 * |03|Call dsGetDisplay() Loop through all valid ports in kSupportedPortTypes[]|vType: [Valid Port Type]_INPUT, int, intptr_t*  | dsERR_NONE and valid handle | Handle of the display device should be retrieved successfully |
 * |04|Call dsGetEDIDBytes() with an invalid handle | intptr_t NULL, unsigned char *edid, int *length | dsERR_INVALID_PARAM | Should return error indicating invalid parameters |
 * |05|Call dsGetEDIDBytes() with null edid | intptr_t, NULL, int *length | dsERR_INVALID_PARAM | Should return error indicating invalid parameters |
 * |06|Call dsGetEDIDBytes() with null length | intptr_t, unsigned char *edid, NULL | dsERR_INVALID_PARAM | Should return error indicating invalid parameters |
 * |07|Terminate the display sub-system with dsDisplayTerm() | | dsERR_NONE | Termination should succeed |
 * |08|Call dsGetEDIDBytes() without initializing the display sub-system or obtaining a handle | intptr_t handle, unsigned char *edid, int *length | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * 
 * @note The ability to test scenarios like dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might require specific setup or environment configuration. Ensure proper memory management in the test setup.
 * @note valid ports can be retrieved from kSupportedPortTypes which can be retrieved from dsVideoPortSettings.
 * 
 */
void test_l1_dsDisplay_negative_dsGetEDIDBytes(void) {
    // Start of the test
    gTestID = 10;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result;
    intptr_t displayHandle;
    unsigned char *edid = NULL;
    int length = 0;

    // Step 01: Call dsGetEDIDBytes() without initializing or obtaining a handle
    result = dsGetEDIDBytes((intptr_t)0, edid, &length);
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize the display sub-system
    result = dsDisplayInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Loop through all valid ports
    for (int i = 0; i < sizeof(kSupportedPortTypes) / sizeof(kSupportedPortTypes[0]); i++) {
        result = dsGetDisplay(kSupportedPortTypes[i], i, &displayHandle);
        UT_ASSERT_EQUAL(result, dsERR_NONE);

        // Step 04: Call dsGetEDIDBytes() with an invalid handle
        result = dsGetEDIDBytes(NULL, edid, &length);
        UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

        // Step 05: Call dsGetEDIDBytes() with null edid
        result = dsGetEDIDBytes(displayHandle, NULL, &length);
        UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

        // Step 06: Call dsGetEDIDBytes() with null length
        result = dsGetEDIDBytes(displayHandle, edid, NULL);
        UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);
    }

    // Step 07: Terminate the display sub-system
    result = dsDisplayTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 08: Call dsGetEDIDBytes() without initializing or obtaining a handle
    result = dsGetEDIDBytes(displayHandle, edid, &length);
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

    // End of the test
    UT_LOG("\n Out %s\n", __FUNCTION__);
}

/**
 * @brief Ensure dsGetDisplayAspectRatio() retrieves the aspect ratio correctly during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 011@n
 * 
 * **Pre-Conditions:**@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize the display sub-system and get a display device handle | | dsERR_NONE | Initialization and handle retrieval should succeed |
 * |02|Call dsGetDisplay() Loop through all valid ports in kSupportedPortTypes[]|vType: [Valid Port Type]_INPUT, int, intptr_t*  | dsERR_NONE and valid handle | Handle of the display device should be retrieved successfully |
 * |03|Call dsGetDisplayAspectRatio() with the obtained display device handle | intptr_t handle, dsVideoAspectRatio_t *aspectRatio | dsERR_NONE and valid aspect ratio | Aspect ratio of the display device should be retrieved successfully |
 * |04|Call dsGetDisplayAspectRatio() with the obtained display device handle | intptr_t handle, dsVideoAspectRatio_t *aspectRatio | dsERR_NONE and valid aspect ratio | Aspect ratio of the display device should be retrieved successfully |
 * |05|Compare the results, and make sure the returned values are the same |  | Success | The values should be the same |
 * |06|Terminate the display sub-system with dsDisplayTerm() | | dsERR_NONE | Termination should succeed |
 * 
 * @note valid ports can be retrieved from kSupportedPortTypes which can be retrieved from dsVideoPortSettings.
 * 
 */
void test_l1_dsDisplay_positive_dsGetDisplayAspectRatio(void) {
    // Start of the test
    gTestID = 11;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result;
    intptr_t displayHandle;
    dsVideoAspectRatio_t aspectRatio1, aspectRatio2;

    // Step 01: Initialize the display sub-system
    result = dsDisplayInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Loop through all valid ports in kSupportedPortTypes
    for (int i = 0; i < sizeof(kSupportedPortTypes) / sizeof(kSupportedPortTypes[0]); i++) {
        result = dsGetDisplay(kSupportedPortTypes[i], i, &displayHandle);
        UT_ASSERT_EQUAL(result, dsERR_NONE);

        // Step 03: Call dsGetDisplayAspectRatio() with the obtained handle
        result = dsGetDisplayAspectRatio(displayHandle, &aspectRatio1);
        UT_ASSERT_EQUAL(result, dsERR_NONE);

        // Step 04: Call dsGetDisplayAspectRatio() again with the same handle
        result = dsGetDisplayAspectRatio(displayHandle, &aspectRatio2);
        UT_ASSERT_EQUAL(result, dsERR_NONE);

        // Step 05: Compare the results
        UT_ASSERT_EQUAL(aspectRatio1, aspectRatio2);
    }

    // Step 06: Terminate the display sub-system
    result = dsDisplayTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // End of the test
    UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetDisplayAspectRatio() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 012@n
 * 
 * **Pre-Conditions:**@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsGetDisplayAspectRatio() without initializing the display sub-system or obtaining a handle | intptr_t handle, dsVideoAspectRatio_t *aspectRatio | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * |02|Initialize the display sub-system and obtain a display device handle | | dsERR_NONE | Initialization and handle retrieval should succeed |
 * |03|Call dsGetDisplay() Loop through all valid ports in kSupportedPortTypes[]|vType: [Valid Port Type]_INPUT, int, intptr_t*  | dsERR_NONE and valid handle | Handle of the display device should be retrieved successfully |
 * |04|Call dsGetDisplayAspectRatio() with an invalid handle| NULL, dsVideoAspectRatio_t *aspectRatio | dsERR_INVALID_PARAM | Should return error indicating invalid handle |
 * |05|Call dsGetDisplayAspectRatio() with an NULL aspectRatio | intptr_t handle, NULL | dsERR_INVALID_PARAM | Should return error indicating invalid handle |
 * |06|Terminate the display sub-system with dsDisplayTerm() | | dsERR_NONE | Termination should succeed |
 * |07|Call dsGetDisplayAspectRatio() without initializing the display sub-system or obtaining a handle | intptr_t handle, dsVideoAspectRatio_t *aspectRatio  | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * 
 * @note The ability to test scenarios like dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might require specific setup or environment configuration.
 * @note valid ports can be retrieved from kSupportedPortTypes which can be retrieved from dsVideoPortSettings.
 * 
 */
void test_l1_dsDisplay_negative_dsGetDisplayAspectRatio(void) {
    // Start of the test
    gTestID = 12;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result;
    intptr_t displayHandle;
    dsVideoAspectRatio_t aspectRatio;

    // Step 01: Call dsGetDisplayAspectRatio() without initializing the display sub-system
    result = dsGetDisplayAspectRatio(NULL, &aspectRatio);
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize the display sub-system
    result = dsDisplayInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Loop through all valid ports in kSupportedPortTypes
    for (int i = 0; i < sizeof(kSupportedPortTypes) / sizeof(kSupportedPortTypes[0]); i++) {
        result = dsGetDisplay(kSupportedPortTypes[i], i, &displayHandle);
        UT_ASSERT_EQUAL(result, dsERR_NONE);

        // Step 04: Call dsGetDisplayAspectRatio() with an invalid handle
        result = dsGetDisplayAspectRatio(NULL, &aspectRatio);
        UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

        // Step 05: Call dsGetDisplayAspectRatio() with a NULL aspectRatio
        result = dsGetDisplayAspectRatio(displayHandle, NULL);
        UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);
    }

    // Step 06: Terminate the display sub-system
    result = dsDisplayTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 07: Call dsGetDisplayAspectRatio() without initializing the display sub-system
    result = dsGetDisplayAspectRatio(displayHandle, &aspectRatio);
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

    // End of the test
    UT_LOG("\n Out %s\n", __FUNCTION__);
}

/**
 * @brief Ensure dsRegisterDisplayEventCallback() registers the callback correctly during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 013@n
 * 
 * **Pre-Conditions:**@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize the display sub-system and get a display device handle | | dsERR_NONE | Initialization and handle retrieval should succeed |
 * |02|Call dsGetDisplay() Loop through all valid ports in kSupportedPortTypes[]|vType: [Valid Port Type]_INPUT, int, intptr_t*  | dsERR_NONE and valid handle | Handle of the display device should be retrieved successfully |
 * |03|Call dsRegisterDisplayEventCallback() with the obtained display device handle and a valid callback function | Valid handle and callback function | dsERR_NONE | Callback registration should succeed |
 * |04|Terminate the display sub-system with dsDisplayTerm() | | dsERR_NONE | Termination should succeed |
 * 
 * @note valid ports can be retrieved from kSupportedPortTypes which can be retrieved from dsVideoPortSettings.
 * 
 */

void testDisplayCallback(int handle, dsDisplayEvent_t event,void* eventData) {
    // Callback function logic
}

void test_l1_dsDisplay_positive_dsRegisterDisplayEventCallback(void) {
 // Start of the test
    gTestID = 13;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result;
    intptr_t displayHandle;

    // Step 01: Initialize the display sub-system
    result = dsDisplayInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Loop through all valid ports in kSupportedPortTypes
    for (int i = 0; i < sizeof(kSupportedPortTypes) / sizeof(kSupportedPortTypes[0]); i++) {
        result = dsGetDisplay(kSupportedPortTypes[i], i, &displayHandle);
        UT_ASSERT_EQUAL(result, dsERR_NONE);

        // Step 03: Call dsRegisterDisplayEventCallback() with the obtained handle and a valid callback function
        result = dsRegisterDisplayEventCallback(displayHandle, testDisplayCallback);
        UT_ASSERT_EQUAL(result, dsERR_NONE);
    }

    // Step 04: Terminate the display sub-system
    result = dsDisplayTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // End of the test
    UT_LOG("\n Out %s\n", __FUNCTION__);
}

/**
 * @brief Ensure dsRegisterDisplayEventCallback() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 014@n
 * 
 * **Pre-Conditions:**@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsRegisterDisplayEventCallback() without initializing the display sub-system or obtaining a handle |Valid handle and callback function | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * |02|Initialize the display sub-system and obtain a display device handle | | dsERR_NONE | Initialization and handle retrieval should succeed |
 * |03|Call dsGetDisplay() Loop through all valid ports in kSupportedPortTypes[]|vType: [Valid Port Type]_INPUT, int, intptr_t*  | dsERR_NONE and valid handle | Handle of the display device should be retrieved successfully |
 * |04|Call dsRegisterDisplayEventCallback() with an NULL handle | NULL, callback function | dsERR_INVALID_PARAM | Should return error indicating invalid parameters |
 * |04|Call dsRegisterDisplayEventCallback() with an NULL callback function | Valid handle,  NULL | dsERR_INVALID_PARAM | Should return error indicating invalid parameters |
 * |05|Terminate the display sub-system with dsDisplayTerm() | | dsERR_NONE | Termination should succeed |
 * |06|Call dsRegisterDisplayEventCallback() without initializing the display sub-system or obtaining a handle | Valid handle and callback function| dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * 
 * @note The ability to test scenarios like dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might require specific setup or environment configuration.
 */


void test_l1_dsDisplay_negative_dsRegisterDisplayEventCallback(void) {
    // Start of the test
    gTestID = 14;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result;
    intptr_t displayHandle;
    const int portCount = sizeof(kSupportedPortTypes) / sizeof(kSupportedPortTypes[0]);

    // Step 01: Call dsRegisterDisplayEventCallback() without initializing the display sub-system
    result = dsRegisterDisplayEventCallback(VALID_HANDLE, testDisplayCallback);
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize the display sub-system
    result = dsDisplayInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Loop through all valid ports in kSupportedPortTypes[]
    for (int i = 0; i < portCount; ++i) {
        // Obtain a display device handle
        result = dsGetDisplay(kSupportedPortTypes[i], i, &displayHandle);
        UT_ASSERT_EQUAL(result, dsERR_NONE);

        // Call dsRegisterDisplayEventCallback() with a NULL handle
        result = dsRegisterDisplayEventCallback(NULL, testDisplayCallback);
        UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);

        // Call dsRegisterDisplayEventCallback() with a NULL callback function
        result = dsRegisterDisplayEventCallback(displayHandle, NULL);
        UT_ASSERT_EQUAL(result, dsERR_INVALID_PARAM);
    }

    // Step 05: Terminate the display sub-system
    result = dsDisplayTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 06: Call dsRegisterDisplayEventCallback() without reinitializing the display sub-system
    result = dsRegisterDisplayEventCallback(VALID_HANDLE, testDisplayCallback);
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

    // End of the test
    UT_LOG("\n Out %s\n", __FUNCTION__);
}

// Note: Replace UT_LOG and UT_ASSERT_EQUAL with your actual logging and assertion methods.
// Note: VALID_HANDLE should be a valid handle for a display device, which is typically obtained from a successful call to dsGetDisplay().
// Note: Ensure proper setup of test environment and handle values.
// Note: Ensure that testDisplayCallback is defined in your test suite.

// Note: Replace UT_LOG and UT_ASSERT_EQUAL with your actual logging and assertion methods.
// Note: VALID_HANDLE should be a valid handle for a display device, which is typically obtained from a successful call to dsGetDisplay().
// Note: Ensure proper setup of test environment and handle values.

static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main test(s) for this module
 *
 * @return int - 0 on success, otherwise failure
 */
int test_l1_dsDisplay_register ( void )
{
	/* add a suite to the registry */
	pSuite = UT_add_suite( "[L1 dsDisplay]", NULL, NULL );
	if ( NULL == pSuite )
	{
		return -1;
	}	

	UT_add_test( pSuite, "dsDisplayInit_L1_positive" ,test_l1_dsDisplay_positive_dsDisplayInit );
	UT_add_test( pSuite, "dsDisplayInit_L1_negative" ,test_l1_dsDisplay_negative_dsDisplayInit );
	UT_add_test( pSuite, "dsDisplayTerm_L1_positive" ,test_l1_dsDisplay_positive_dsDisplayTerm );
	UT_add_test( pSuite, "dsDisplayTerm_L1_negative" ,test_l1_dsDisplay_negative_dsDisplayTerm );
	UT_add_test( pSuite, "dsGetDisplay_L1_positive" ,test_l1_dsDisplay_positive_dsGetDisplay );
	UT_add_test( pSuite, "dsGetDisplay_L1_negative" ,test_l1_dsDisplay_negative_dsGetDisplay );
	UT_add_test( pSuite, "dsGetEDID_L1_positive" ,test_l1_dsDisplay_positive_dsGetEDID );
	UT_add_test( pSuite, "dsGetEDID_L1_negative" ,test_l1_dsDisplay_negative_dsGetEDID );
	UT_add_test( pSuite, "dsGetEDIDBytes_L1_positive" ,test_l1_dsDisplay_positive_dsGetEDIDBytes );
	UT_add_test( pSuite, "dsGetEDIDBytes_L1_negative" ,test_l1_dsDisplay_negative_dsGetEDIDBytes );
	UT_add_test( pSuite, "dsGetDisplayAspectRatio_L1_positive" ,test_l1_dsDisplay_positive_dsGetDisplayAspectRatio );
	UT_add_test( pSuite, "dsGetDisplayAspectRatio_L1_negative" ,test_l1_dsDisplay_negative_dsGetDisplayAspectRatio );
	UT_add_test( pSuite, "dsRegisterDisplayEventCallback_L1_positive" ,test_l1_dsDisplay_positive_dsRegisterDisplayEventCallback );
	UT_add_test( pSuite, "dsRegisterDisplayEventCallback_L1_negative" ,test_l1_dsDisplay_negative_dsRegisterDisplayEventCallback );
	

	return 0;
} 


/** @} */ // End of DS Display HAL Tests L1 File
/** @} */ // End of DS Display HALTEST
/** @} */ // End of Device Settings HAL
/** @} */ // End of Device Settings Module
/** @} */ // End of HPK