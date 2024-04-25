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
 * @defgroup DS_Display_HALTEST Device Settings Display HAL Tests
 * @{
 */

/**
 * @defgroup DS_Display_HALTEST_L1 Device Settings Display HAL Tests L1 File
 * @{
 * @parblock
 *
 * ### L1 Tests for DS Display HAL :
 *
 * Level 1 unit test cases for all APIs of Device Settings Display HAL
 *
 * **Pre-Conditions:**  None@n
 * **Dependencies:** None@n
 *
 * Refer to API Definition specification documentation : [ds-display_halSpec.md](../../docs/pages/ds-display_halSpec.md)
 *
 * @endparblock
 */


/**
 * @file test_l1_dsDisplay.c
 *
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

#define DS_ASSERT_AUTO_TERM_NUMERICAL(value, comparison){\
    if(value != comparison){\
        UT_LOG("\n In %s Comparison: [%d = %d]\n", __FUNCTION__, value, comparison);\
        dsDisplayTerm();\
        UT_FAIL();\
    }\
}\

#define DS_ASSERT_AUTO_TERM_STRING(value, comparison){\
    if(strcmp(value, comparison) != 0){\
        UT_LOG("\n In %s Comparison: [%s = %s]\n", __FUNCTION__, value, comparison);\
        dsDisplayTerm();\
        UT_FAIL();\
    }\
}\

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
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Terminate the display module
    result = dsDisplayTerm();
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Reinitialize the display module to check for reinitialization capability
    result = dsDisplayInit();
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 04: Terminate the display module again
    result = dsDisplayTerm();
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
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
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Attempt to initialize the display module again
    result = dsDisplayInit();
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_ALREADY_INITIALIZED);

    // Step 03: Terminate the display module
    result = dsDisplayTerm();
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
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
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Terminate the display sub-system
    result = dsDisplayTerm();
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Reinitialize the display sub-system to check for reinitialization
    result = dsDisplayInit();
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 04: Terminate the display sub-system again to confirm termination capability
    result = dsDisplayTerm();
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
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
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize the display sub-system
    result = dsDisplayInit();
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Terminate the display sub-system
    result = dsDisplayTerm();
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 04: Call dsDisplayTerm() again after termination
    result = dsDisplayTerm();
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
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
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    for (size_t i = 0; i < numPorts; i++) {
        dsVideoPortType_t vType = kSupportedPortTypes[i];
        UT_LOG("\n In %s Port Type: [%d]\n", __FUNCTION__, vType);
        // Step 02: Call dsGetDisplay() for each valid port
        result = dsGetDisplay(vType, i, &displayHandle1);
        UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
        DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
        UT_LOG("Display handle for port type %d: %ld\n", vType, (long)displayHandle1);

        // Step 03: Call the last value again, and compare the results
        result = dsGetDisplay(vType, i, &displayHandle2);
        UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, displayHandle1, displayHandle2);
        DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
        UT_LOG("\n In %s Comparison: [%d = %d]\n", __FUNCTION__, result);
        DS_ASSERT_AUTO_TERM_NUMERICAL(displayHandle1, displayHandle2);
        UT_LOG("Repeated display handle for port type %d: %ld\n", vType, (long)displayHandle2);
    }

    // Step 04: Terminate the display sub-system
    result = dsDisplayTerm();
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
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
    result = dsGetDisplay(kSupportedPortTypes[0], 0, &displayHandle);
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize the display sub-system
    result = dsDisplayInit();
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Call dsGetDisplay() with invalid video type
    result = dsGetDisplay(dsVIDEOPORT_TYPE_MAX, (int)dsVIDEOPORT_TYPE_MAX, &displayHandle);
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

    // Step 04: Call dsGetDisplay() with invalid index
    result = dsGetDisplay(kSupportedPortTypes[0], -1, &displayHandle);
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

    // Step 05: Call dsGetDisplay() with NULL handle
    result = dsGetDisplay(kSupportedPortTypes[0], 0, NULL);
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

    // Step 06: Terminate the display sub-system
    result = dsDisplayTerm();
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 07: Call dsGetDisplay() again after termination
    result = dsGetDisplay(kSupportedPortTypes[0], 0, &displayHandle);
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
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
    dsDisplayEDID_t *edid1 = {0};
    dsDisplayEDID_t *edid2 = {0};

    // Step 01: Initialize the display sub-system
    result = dsDisplayInit();
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Loop through all valid ports
    for (int i = 0; i < sizeof(kSupportedPortTypes) / sizeof(kSupportedPortTypes[0]); i++) {
        // Step 02: Get the display device handle
        if(kSupportedPortTypes[i] == dsVIDEOPORT_TYPE_INTERNAL || kSupportedPortTypes[i] == dsVIDEOPORT_TYPE_HDMI || kSupportedPortTypes[i] == dsVIDEOPORT_TYPE_HDMI_INPUT){
            result = dsGetDisplay(kSupportedPortTypes[i], i, &displayHandle);
            DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

            // Step 03: Call dsGetEDID() with the obtained handle
            result = dsGetEDID(displayHandle, edid1);
            DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

            // Step 04: Call dsGetEDID() again with the same handle
            result = dsGetEDID(displayHandle, edid2);
            DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

            // Step 05: Compare the returned results
            DS_ASSERT_AUTO_TERM_NUMERICAL(edid1->productCode , edid2->productCode);
            DS_ASSERT_AUTO_TERM_NUMERICAL(edid1->serialNumber , edid2->serialNumber);
            DS_ASSERT_AUTO_TERM_NUMERICAL(edid1->manufactureYear , edid2->manufactureYear);
            DS_ASSERT_AUTO_TERM_NUMERICAL(edid1->manufactureWeek , edid2->manufactureWeek);
            DS_ASSERT_AUTO_TERM_NUMERICAL(edid1->hdmiDeviceType , edid2->hdmiDeviceType);
            DS_ASSERT_AUTO_TERM_NUMERICAL(edid1->isRepeater , edid2->isRepeater);
            DS_ASSERT_AUTO_TERM_NUMERICAL(edid1->physicalAddressA , edid2->physicalAddressA);
            DS_ASSERT_AUTO_TERM_NUMERICAL(edid1->physicalAddressB , edid2->physicalAddressB);
            DS_ASSERT_AUTO_TERM_NUMERICAL(edid1->physicalAddressC , edid2->physicalAddressC);
            DS_ASSERT_AUTO_TERM_NUMERICAL(edid1->physicalAddressD , edid2->physicalAddressD);
            DS_ASSERT_AUTO_TERM_NUMERICAL(edid1->numOfSupportedResolution , edid2->numOfSupportedResolution);
            DS_ASSERT_AUTO_TERM_STRING(edid2->monitorName, edid2->monitorName)

        }
    }

    // Step 06: Terminate the display sub-system
    result = dsDisplayTerm();
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
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
    intptr_t displayHandle=-1;
    dsDisplayEDID_t *edid = {0};

    // Step 01: Call dsGetEDID() without initializing the display sub-system
    result = dsGetEDID(displayHandle, edid);
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize the display sub-system
    result = dsDisplayInit();
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Obtain a display device handle
    for (int i = 0; i < sizeof(kSupportedPortTypes) / sizeof(kSupportedPortTypes[0]); i++) {
        result = dsGetDisplay(kSupportedPortTypes[i], i, &displayHandle);
        DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

        // Step 04: Call dsGetEDID() with an invalid handle
        result = dsGetEDID((intptr_t)NULL, edid);
        DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

        // Step 05: Call dsGetEDID() with a NULL dsDisplayEDID_t
        result = dsGetEDID(displayHandle, NULL);
        DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
    }

    // Step 06: Terminate the display sub-system
    result = dsDisplayTerm();
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 07: Call dsGetEDID() without initializing the display sub-system
    result = dsGetEDID(displayHandle, edid);
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

    // End of the test
    UT_LOG("\n Out %s\n", __FUNCTION__);
}

/**
 * @brief Ensure dsGetEDIDBytesSize() retrieves the EDID buffer maximum length correctly during positive scenarios
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
 * |02|Call dsGetDisplay() Loop through all valid ports in kSupportedPortTypes[]|vType: [ValCall dsGetEDIDid Port Type]_INPUT, int, intptr_t*  | dsERR_NONE and valid handle | Handle of the display device should be retrieved successfully |
 * |03|Call dsGetEDIDBytesSize() to get the maximum EDID buffer size with the obtained handle | intptr_t handle, unsigned int *length | dsERR_NONE, and length | EDID buffer length should be retrieved successfully |
 * |04|Call dsGetEDIDBytesSize() again to get the maximum EDID buffer size with the obtained handle | intptr_t handle, unsigned int *length | dsERR_NONE, and length | EDID buffer length should be retrieved successfully |
 * |05|Verify that the return results are the same |  | Success | The results should be the same  |
 * |06|Terminate the display sub-system with dsDisplayTerm() | | dsERR_NONE | Memory deallocation and termination should succeed |
 * 
 * @note valid ports can be retrieved from kSupportedPortTypes which can be retrieved from dsVideoPortSettings.
 * 
 */
void test_l1_dsDisplay_positive_dsGetEDIDBytesSize(void) {
    // Start of the test
    gTestID = 9;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result;
    intptr_t displayHandle;
    unsigned int length1 = 0;
    unsigned int length2 = 0;

    // Step 01: Initialize the display sub-system
    result = dsDisplayInit();
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL_FATAL(result, dsERR_NONE);

    // Loop through all valid ports
    for (int i = 0; i < sizeof(kSupportedPortTypes) / sizeof(kSupportedPortTypes[0]); i++) {
        // Step 02: Call dsGetDisplay() for each valid port
        result = dsGetDisplay(kSupportedPortTypes[i], i, &displayHandle);
        if(result != dsERR_NONE)
        {
            UT_FAIL("Failed to get display handle");
            break;
        }

        result = dsGetEDIDBytesSize(displayHandle, &length1);
        if(result != dsERR_NONE)
        {
            UT_FAIL("Failed to get EDID Bytes Length");
            continue;
        }

        result = dsGetEDIDBytesSize(displayHandle, &length2);
        if(result != dsERR_NONE)
        {
            UT_FAIL("Failed to get EDID Bytes Length");
            continue;
        }

        // Step 05: Verify that the return results are the same
        UT_ASSERT_EQUAL(length1, length2);
    }

    // Step 06: Terminate the display sub-system
    result = dsDisplayTerm();
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // End of the test
    UT_LOG("\n Out %s\n", __FUNCTION__);
}

/**
 * @brief Ensure dsGetEDIDBytesSize() returns correct error codes during negative scenarios
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
 * |01|Call dsGetEDIDBytesSize() without initializing the display sub-system or obtaining a handle | intptr_t handle, unsigned int *length | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * |02|Initialize the display sub-system and obtain a display device handle | | dsERR_NONE | Initialization and handle retrieval should succeed |
 * |03|Call dsGetDisplay() Loop through all valid ports in kSupportedPortTypes[]|vType: [Valid Port Type]_INPUT, int, intptr_t*  | dsERR_NONE and valid handle | Handle of the display device should be retrieved successfully |
 * |04|Call dsGetEDIDBytesSize() with an invalid handle | intptr_t NULL, unsigned int *length | dsERR_INVALID_PARAM | Should return error indicating invalid parameters |
 * |05|Call dsGetEDIDBytesSize() with null length | intptr_t, NULL| dsERR_INVALID_PARAM | Should return error indicating invalid parameters |
 * |06|Terminate the display sub-system with dsDisplayTerm() | | dsERR_NONE | Termination should succeed |
 * |07|Call dsGetEDIDBytesSize() without initializing the display sub-system or obtaining a handle | intptr_t handle, unsigned int *length | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * 
 * @note The ability to test scenarios like dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might require specific setup or environment configuration. Ensure proper memory management in the test setup.
 * @note valid ports can be retrieved from kSupportedPortTypes which can be retrieved from dsVideoPortSettings.
 * 
 */
void test_l1_dsDisplay_negative_dsGetEDIDBytesSize(void) {
    // Start of the test
    gTestID = 10;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result;
    intptr_t displayHandle =-1;
    unsigned int length = 0;

    // Step 01: Call dsGetEDIDBytesSize() without initializing or obtaining a handle
    result = dsGetEDIDBytesSize(displayHandle, &length);
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    if(result != dsERR_NOT_INITIALIZED)
    {
        UT_FAIL("Incorrect error return");
        return;
    }

    // Step 02: Initialize the display sub-system
    result = dsDisplayInit();
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    if(result != dsERR_NONE)
    {
        UT_FAIL("Init has failed");
        return;
    }

    // Step 03: Loop through all valid ports
    for (int i = 0; i < sizeof(kSupportedPortTypes) / sizeof(kSupportedPortTypes[0]); i++) {
        result = dsGetDisplay(kSupportedPortTypes[i], i, &displayHandle);
        DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
        if(result != dsERR_NONE)
        {
            UT_FAIL("Failed to get displayHandle");
            break;
        }

        // Step 04: Call dsGetEDIDBytesSize() with an invalid handle
        result = dsGetEDIDBytesSize((intptr_t)NULL, &length);
        if(result != dsERR_INVALID_PARAM)
        {
            UT_FAIL("Incorrect error return");
            break;
        }

        // Step 05: Call dsGetEDIDBytesSize() with an invalid length
        result = dsGetEDIDBytesSize(displayHandle, NULL);
        if(result != dsERR_INVALID_PARAM)
        {
            UT_FAIL("Incorrect error return");
            break;
        }
    }

    // Step 06: Terminate the display sub-system
    result = dsDisplayTerm();
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    if(result != dsERR_NONE)
    {
        UT_FAIL("Term has failed");
        return;
    }

    // Step 07: Call dsGetEDIDBytes() without initializing or obtaining a handle
    result = dsGetEDIDBytesSize(displayHandle, length);
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    if(result != dsERR_NOT_INITIALIZED)
    {
        UT_FAIL("Incorrect error return");
        return;
    }
    
    // End of the test
    UT_LOG("\n Out %s\n", __FUNCTION__);
}

/**
 * @brief Ensure dsGetEDIDBytes() retrieves the EDID buffer and length correctly during positive scenarios
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
    gTestID = 11;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result;
    intptr_t displayHandle;
    unsigned char *edid1 = NULL;
    unsigned char *edid2 = NULL;
    int length = 0;

    // Step 01: Initialize the display sub-system
    result = dsDisplayInit();
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL_FATAL(result, dsERR_NONE);

    // Loop through all valid ports
    for (int i = 0; i < sizeof(kSupportedPortTypes) / sizeof(kSupportedPortTypes[0]); i++) {
        // Step 02: Call dsGetDisplay() for each valid port
        result = dsGetDisplay(kSupportedPortTypes[i], i, &displayHandle);
        if(result != dsERR_NONE)
        {
            UT_FAIL("Failed to get display handle");
            break;
        }

        result = dsGetEDIDBytesSize(displayHandle, &length);
        if(result != dsERR_NONE)
        {
            UT_FAIL("Failed to get EDID Bytes Length");
            continue;
        }

        edid1 = malloc(length);
        if(edid1 == NULL) {
            UT_FAIL("Failed to allocate buffer");
            break;
        }

        edid2 = malloc(length);
        if(edid2 == NULL) {
            UT_FAIL("Failed to allocate buffer");
            free(edid1);
            edid1 = NULL;
            break;
        }
        // Step 03 and 04: Allocate memory for the EDID buffer and call dsGetEDIDBytes() twice
        result = dsGetEDIDBytes(displayHandle, edid1, length);
        UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
        if(result != dsERR_NONE)
        {
            UT_FAIL("Failed to get EDID Bytes");
            free(edid1);
            free(edid2);
            continue;
        }
        result = dsGetEDIDBytes(displayHandle, edid2, length);
        UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
        if(result != dsERR_NONE)
        {
            UT_FAIL("Failed to get EDID Bytes");
            free(edid1);
            free(edid2);
            continue;
        }

        // Step 05: Verify that the return results are the same
        UT_ASSERT_EQUAL(memcmp(edid1, edid2, length), 0);

        free(edid1);
        free(edid2);
    }

    // Step 06: Terminate the display sub-system
    result = dsDisplayTerm();
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // End of the test
    UT_LOG("\n Out %s\n", __FUNCTION__);
}

/**
 * @brief Ensure dsGetEDIDBytes() returns correct error codes during negative scenarios
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
 * |01|Call dsGetEDIDBytes() without initializing the display sub-system or obtaining a handle | intptr_t handle, unsigned char *edid, int *length | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * |02|Initialize the display sub-system and obtain a display device handle | | dsERR_NONE | Initialization and handle retrieval should succeed |
 * |03|Call dsGetDisplay() Loop through all valid ports in kSupportedPortTypes[]|vType: [Valid Port Type]_INPUT, int, intptr_t*  | dsERR_NONE and valid handle | Handle of the display device should be retrieved successfully |
 * |04|Call dsGetEDIDBytes() with an invalid handle | intptr_t NULL, unsigned char *edid, int *length | dsERR_INVALID_PARAM | Should return error indicating invalid parameters |
 * |05|Call dsGetEDIDBytes() with null edid | intptr_t, NULL, int *length | dsERR_INVALID_PARAM | Should return error indicating invalid parameters |
 * |06|Call dsGetEDIDBytes() with invalid length | intptr_t, unsigned char *edid, 0 | dsERR_INVALID_PARAM | Should return error indicating invalid parameters |
 * |07|Terminate the display sub-system with dsDisplayTerm() | | dsERR_NONE | Termination should succeed |
 * |08|Call dsGetEDIDBytes() without initializing the display sub-system or obtaining a handle | intptr_t handle, unsigned char *edid, int *length | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * 
 * @note The ability to test scenarios like dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might require specific setup or environment configuration. Ensure proper memory management in the test setup.
 * @note valid ports can be retrieved from kSupportedPortTypes which can be retrieved from dsVideoPortSettings.
 * 
 */
void test_l1_dsDisplay_negative_dsGetEDIDBytes(void) {
    // Start of the test
    gTestID = 12;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result;
    intptr_t displayHandle =-1;
    unsigned char *edid = (unsigned char *)malloc(512);
    unsigned int length = 0;

    // Step 01: Call dsGetEDIDBytes() without initializing or obtaining a handle
    result = dsGetEDIDBytes(displayHandle, edid, length);
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    if(result != dsERR_NOT_INITIALIZED)
    {
        UT_FAIL("Incorrect error return");
        free(edid);
        return;
    }

    // Step 02: Initialize the display sub-system
    result = dsDisplayInit();
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    if(result != dsERR_NONE)
    {
        UT_FAIL("Init has failed");
        free(edid);
        return;
    }

    // Step 03: Loop through all valid ports
    for (int i = 0; i < sizeof(kSupportedPortTypes) / sizeof(kSupportedPortTypes[0]); i++) {
        result = dsGetDisplay(kSupportedPortTypes[i], i, &displayHandle);
        DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
        if(result != dsERR_NONE)
        {
            UT_FAIL("Failed to get displayHandle");
            break;
        }

        // Step 04: Call dsGetEDIDBytes() with an invalid handle
        result = dsGetEDIDBytes((intptr_t)NULL, edid, length);
        if(result != dsERR_INVALID_PARAM)
        {
            UT_FAIL("Incorrect error return");
            break;
        }

        // Step 05: Call dsGetEDIDBytes() with null edid
        result = dsGetEDIDBytes(displayHandle, NULL, length);
        if(result != dsERR_INVALID_PARAM)
        {
            UT_FAIL("Incorrect error return");
            break;
        }

        // Step 06: Call dsGetEDIDBytes() with invalid length
        result = dsGetEDIDBytes(displayHandle, edid, 0);
        if(result != dsERR_INVALID_PARAM)
        {
            UT_FAIL("Incorrect error return");
            break;
        }
    }

    // Step 07: Terminate the display sub-system
    result = dsDisplayTerm();
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    if(result != dsERR_NONE)
    {
        UT_FAIL("Term has failed");
        free(edid);
        return;
    }

    // Step 08: Call dsGetEDIDBytes() without initializing or obtaining a handle
    result = dsGetEDIDBytes(displayHandle, edid, length);
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    if(result != dsERR_NOT_INITIALIZED)
    {
        UT_FAIL("ncorrect error return");
        free(edid);
        return;
    }

    free(edid);
    
    // End of the test
    UT_LOG("\n Out %s\n", __FUNCTION__);
}

/**
 * @brief Ensure dsGetDisplayAspectRatio() retrieves the aspect ratio correctly during positive scenarios
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
    gTestID = 13;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result;
    intptr_t displayHandle;
    dsVideoAspectRatio_t aspectRatio1 = dsVIDEO_ASPECT_RATIO_MAX;
    dsVideoAspectRatio_t aspectRatio2 = dsVIDEO_ASPECT_RATIO_MAX;

    // Step 01: Initialize the display sub-system
    result = dsDisplayInit();
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Loop through all valid ports in kSupportedPortTypes
    for (int i = 0; i < sizeof(kSupportedPortTypes) / sizeof(kSupportedPortTypes[0]); i++) {
        result = dsGetDisplay(kSupportedPortTypes[i], i, &displayHandle);
        DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

        // Step 03: Call dsGetDisplayAspectRatio() with the obtained handle
        result = dsGetDisplayAspectRatio(displayHandle, &aspectRatio1);
        DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

        // Step 04: Call dsGetDisplayAspectRatio() again with the same handle
        result = dsGetDisplayAspectRatio(displayHandle, &aspectRatio2);
        DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

        // Step 05: Compare the results
        DS_ASSERT_AUTO_TERM_NUMERICAL(aspectRatio1, aspectRatio2);
    }

    // Step 06: Terminate the display sub-system
    result = dsDisplayTerm();
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // End of the test
    UT_LOG("\n Out %s\n", __FUNCTION__);
}


/**
 * @brief Ensure dsGetDisplayAspectRatio() returns correct error codes during negative scenarios
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
    gTestID = 14;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result;
    intptr_t displayHandle =-1;
    dsVideoAspectRatio_t aspectRatio;

    // Step 01: Call dsGetDisplayAspectRatio() without initializing the display sub-system
    result = dsGetDisplayAspectRatio(displayHandle, &aspectRatio);
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize the display sub-system
    result = dsDisplayInit();
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Loop through all valid ports in kSupportedPortTypes
    for (int i = 0; i < sizeof(kSupportedPortTypes) / sizeof(kSupportedPortTypes[0]); i++) {
        result = dsGetDisplay(kSupportedPortTypes[i], i, &displayHandle);
        DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

        // Step 04: Call dsGetDisplayAspectRatio() with an invalid handle
        result = dsGetDisplayAspectRatio((intptr_t)NULL, &aspectRatio);
        DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

        // Step 05: Call dsGetDisplayAspectRatio() with a NULL aspectRatio
        result = dsGetDisplayAspectRatio(displayHandle, NULL);
        DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
    }

    // Step 06: Terminate the display sub-system
    result = dsDisplayTerm();
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 07: Call dsGetDisplayAspectRatio() without initializing the display sub-system
    result = dsGetDisplayAspectRatio(displayHandle, &aspectRatio);
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

    // End of the test
    UT_LOG("\n Out %s\n", __FUNCTION__);
}

/**
 * @brief Ensure dsRegisterDisplayEventCallback() registers the callback correctly during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 015@n
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
    gTestID = 15;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result;
    intptr_t displayHandle;

    // Step 01: Initialize the display sub-system
    result = dsDisplayInit();
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Loop through all valid ports in kSupportedPortTypes
    for (int i = 0; i < sizeof(kSupportedPortTypes) / sizeof(kSupportedPortTypes[0]); i++) {
        result = dsGetDisplay(kSupportedPortTypes[i], i, &displayHandle);
        DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

        // Step 03: Call dsRegisterDisplayEventCallback() with the obtained handle and a valid callback function
        result = dsRegisterDisplayEventCallback(displayHandle, testDisplayCallback);
        DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
    }

    // Step 04: Terminate the display sub-system
    result = dsDisplayTerm();
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // End of the test
    UT_LOG("\n Out %s\n", __FUNCTION__);
}

/**
 * @brief Ensure dsRegisterDisplayEventCallback() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 016@n
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
    gTestID = 16;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    int result;
    intptr_t displayHandle =-1;
    const int portCount = sizeof(kSupportedPortTypes) / sizeof(kSupportedPortTypes[0]);

    // Step 01: Call dsRegisterDisplayEventCallback() without initializing the display sub-system
    result = dsRegisterDisplayEventCallback(displayHandle, testDisplayCallback);
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

    // Step 02: Initialize the display sub-system
    result = dsDisplayInit();
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Loop through all valid ports in kSupportedPortTypes[]
    for (int i = 0; i < portCount; ++i) {
        // Obtain a display device handle
        result = dsGetDisplay(kSupportedPortTypes[i], i, &displayHandle);
        DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

        // Call dsRegisterDisplayEventCallback() with a NULL handle
        result = dsRegisterDisplayEventCallback((intptr_t)NULL, testDisplayCallback);
        DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

        // Call dsRegisterDisplayEventCallback() with a NULL callback function
        result = dsRegisterDisplayEventCallback(displayHandle, NULL);
        DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
    }

    // Step 05: Terminate the display sub-system
    result = dsDisplayTerm();
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 06: Call dsRegisterDisplayEventCallback() without reinitializing the display sub-system
    result = dsRegisterDisplayEventCallback(displayHandle, testDisplayCallback);
    UT_LOG("\n In %s Return value: [%d]\n", __FUNCTION__, result);
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);

    // End of the test
    UT_LOG("\n Out %s\n", __FUNCTION__);
}


static UT_test_suite_t * pSuite = NULL;
static UT_test_suite_t * pSuite2 = NULL;

/**
 * @brief Register the main test(s) for this module
 *
 * @return int - 0 on success, otherwise failure
 */
int test_l1_dsDisplay_register ( void )
{
	/* add a suite to the registry */
	pSuite = UT_add_suite( "[L1 dsDisplay]", NULL, NULL );
    pSuite2 = UT_add_suite( "[L1 dsDisplay -- advanced]", NULL, NULL );
	if ( NULL == pSuite || NULL == pSuite2 )
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
	UT_add_test( pSuite2, "dsGetEDIDBytes_L1_positive" ,test_l1_dsDisplay_positive_dsGetEDIDBytes );
	UT_add_test( pSuite, "dsGetEDIDBytes_L1_negative" ,test_l1_dsDisplay_negative_dsGetEDIDBytes );
	UT_add_test( pSuite, "dsGetDisplayAspectRatio_L1_positive" ,test_l1_dsDisplay_positive_dsGetDisplayAspectRatio );
	UT_add_test( pSuite, "dsGetDisplayAspectRatio_L1_negative" ,test_l1_dsDisplay_negative_dsGetDisplayAspectRatio );
	UT_add_test( pSuite, "dsRegisterDisplayEventCallback_L1_positive" ,test_l1_dsDisplay_positive_dsRegisterDisplayEventCallback );
	UT_add_test( pSuite, "dsRegisterDisplayEventCallback_L1_negative" ,test_l1_dsDisplay_negative_dsRegisterDisplayEventCallback );
	

	return 0;
} 


/** @} */ // End of DS_Display_HALTEST_L1
/** @} */ // End of DS_Display_HALTEST
/** @} */ // End of Device_Settings_HALTEST
/** @} */ // End of Device_Settings
/** @} */ // End of HPK