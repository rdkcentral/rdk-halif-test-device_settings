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
* @file test_l1_dsCompositeIn.c
* @page Device Settings
* @subpage dsCompositeIn
*
* ## Module's Role
* This module includes Level 1 functional tests (success and failure scenarios)
* This is to ensure that the API meets the operational requirements of the dsHost across all vendors
*
* **Pre-Conditions:**  None
* **Dependencies:** None
*
* Ref to API Definition specification documentation : [ds-composite-in_halSpec.md](../../../docs/ds-composite-in_halSpec.md)
*/

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <ut.h>
#include <ut_log.h>
#include "dsCompositeIn.h"

/**
 * @brief Ensure dsCompositeInInit() returns correct error codes during basic positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 001@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsCompositeInInit() to initialize the module | | dsERR_NONE | First-time initialization should succeed |
 * |02|Call dsCompositeInTerm() to terminate the module | | dsERR_NONE | Termination should succeed |
 * |03|Call dsCompositeInInit() again initialize after termination | | dsERR_NONE | Re-initialization should succeed |
 * |04|Call dsCompositeInTerm() again to terminate the module | | dsERR_NONE | Termination should succeed |
 * 
 */
void test_l1_dsCompositeIn_positive_dsCompositeInInit(void)
{
    // Step 01: First-time initialization
    UT_ASSERT_EQUAL(dsCompositeInInit(), dsERR_NONE);

    // Step 02: Termination
    UT_ASSERT_EQUAL(dsCompositeInTerm(), dsERR_NONE);

    // Step 03: Re-initialization
    UT_ASSERT_EQUAL(dsCompositeInInit(), dsERR_NONE);

    // Step 04: Termination again
    UT_ASSERT_EQUAL(dsCompositeInTerm(), dsERR_NONE);
}

/**
 * @brief Ensure dsCompositeInInit() returns correct error codes during negative scenarios with proper initialization and termination
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 002@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsCompositeInInit() to initialize the module | | dsERR_NONE | Initialization should succeed |
 * |02|Call dsCompositeInInit() again while already initialized | | dsERR_ALREADY_INITIALIZED | Should return error indicating the module is already initialized |
 * |03|Call dsCompositeInTerm() again to terminate the module | | dsERR_NONE | Termination should succeed |
 * 
 * @note The ability to simulate specific conditions like dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might require specific setup or environment configuration. These cases are not included in this test plan due to the challenges in realistic simulation.
 */
void test_l1_dsCompositeIn_negative_dsCompositeInInit(void)
{
    // Step 01: Initialize the module
    UT_ASSERT_EQUAL(dsCompositeInInit(), dsERR_NONE);

    // Step 02: Attempt to initialize again
    UT_ASSERT_EQUAL(dsCompositeInInit(), dsERR_ALREADY_INITIALIZED);

    // Step 03: Terminate the module
    UT_ASSERT_EQUAL(dsCompositeInTerm(), dsERR_NONE);
}


/**
 * @brief Ensure dsCompositeInTerm() returns correct error codes during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 003@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsCompositeInInit() and initialize the module | | dsERR_NONE | Initialization should succeed |
 * |02|Call dsCompositeInTerm() to terminate the module| | dsERR_NONE | Termination should succeed |
 * |03|Call dsCompositeInInit() and initialize the module | | dsERR_NONE | Initialization should succeed |
 * |04|Call dsCompositeInTerm() to terminate the module| | dsERR_NONE | Termination should succeed |
 * 
 * 
 */
void test_l1_dsCompositeIn_positive_dsCompositeInTerm(void)
{
    // Step 01: Initialize the module
    UT_ASSERT_EQUAL(dsCompositeInInit(), dsERR_NONE);

    // Step 02: Terminate the module
    UT_ASSERT_EQUAL(dsCompositeInTerm(), dsERR_NONE);

    // Step 03: Re-initialize the module
    UT_ASSERT_EQUAL(dsCompositeInInit(), dsERR_NONE);

    // Step 04: Terminate the module again
    UT_ASSERT_EQUAL(dsCompositeInTerm(), dsERR_NONE);
}


/**
 * @brief Ensure dsCompositeInTerm() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 004@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsCompositeInTerm() without initializing the module | | dsERR_NOT_INITIALIZED | Termination should fail due to the module not being initialized |
 * |02|Call dsCompositeInInit() and initialize the module | | dsERR_NONE | Initialization should succeed |
 * |03|Call dsCompositeInTerm() to terminate the module| | dsERR_NONE | Termination should succeed |
 * |04|Call dsCompositeInTerm() again after proper termination | | dsERR_NOT_INITIALIZED | Termination should fail, indicating the module is already terminated |
 * 
 * @note The ability to simulate specific conditions like dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL might require specific setup or environment configuration. These cases are not included in this test plan due to the challenges in realistic simulation.
 */
void test_l1_dsCompositeIn_negative_dsCompositeInTerm(void)
{
    // Step 01: Call Termination without initialization
    UT_ASSERT_EQUAL(dsCompositeInTerm(), dsERR_NOT_INITIALIZED);

    // Step 02: Initialize the module
    UT_ASSERT_EQUAL(dsCompositeInInit(), dsERR_NONE);

    // Step 03: Terminate the module
    UT_ASSERT_EQUAL(dsCompositeInTerm(), dsERR_NONE);

    // Step 04: Attempt to terminate again after proper termination
    UT_ASSERT_EQUAL(dsCompositeInTerm(), dsERR_NOT_INITIALIZED);
}


/**
 * @brief Ensure dsCompositeInGetNumberOfInputs() returns consistent error codes and output during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 005@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsCompositeInInit() and initialize the module | | dsERR_NONE | Initialization should succeed |
 * |02|Call dsCompositeInGetNumberOfInputs() with a valid pointer | uint8_t *pNumberOfInputs | dsERR_NONE and a valid number of inputs | Number of inputs should be returned correctly |
 * |03|Call dsCompositeInGetNumberOfInputs() with a valid pointer | uint8_t *pNumberOfInputs | dsERR_NONE and a valid number of inputs | Number of inputs should be consistent with the first call |
 * |04|Compare the results of both calls to ensure consistency | Results of first and second calls | Consistent number of inputs | The number of inputs returned should be the same in both calls |
 * |05|Call dsCompositeInTerm() to terminate the module| | dsERR_NONE | Termination should succeed |
 * 
 */
void test_l1_dsCompositeIn_positive_dsCompositeInGetNumberOfInputs(void)
{
    uint8_t numberOfInputs1, numberOfInputs2;

    // Step 01: Initialize the module
    UT_ASSERT_EQUAL(dsCompositeInInit(), dsERR_NONE);

    // Step 02: Get number of inputs for the first time
    UT_ASSERT_EQUAL(dsCompositeInGetNumberOfInputs(&numberOfInputs1), dsERR_NONE);

    // Step 03: Get number of inputs for the second time
    UT_ASSERT_EQUAL(dsCompositeInGetNumberOfInputs(&numberOfInputs2), dsERR_NONE);

    // Step 04: Compare the results of both calls
    UT_ASSERT_EQUAL(numberOfInputs1, numberOfInputs2);

    // Step 05: Terminate the module
    UT_ASSERT_EQUAL(dsCompositeInTerm(), dsERR_NONE);
}


/**
 * @brief Ensure dsCompositeInGetNumberOfInputs() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 006@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsCompositeInGetNumberOfInputs() without initializing the module | uint8_t *pNumberOfInputs | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * |02|Call dsCompositeInInit() and initialize the module | | dsERR_NONE | Initialization should succeed |
 * |03|Call dsCompositeInGetNumberOfInputs() with a NULL pointer | NULL pointer | dsERR_INVALID_PARAM | Should return error indicating invalid parameter |
 * |04|Call dsCompositeInTerm() to terminate the module| | dsERR_NONE | Termination should succeed |
 * |05|Call dsCompositeInGetNumberOfInputs() after terminating the module | uint8_t *pNumberOfInputs | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * 
 * @note Scenarios like dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL are not included in this test plan due to the challenges in realistic simulation.
 */
void test_l1_dsCompositeIn_negative_dsCompositeInGetNumberOfInputs(void)
{
    uint8_t *pNumberOfInputs = NULL;

    // Step 01: Call GetNumberOfInputs without initialization
    UT_ASSERT_EQUAL(dsCompositeInGetNumberOfInputs(&pNumberOfInputs), dsERR_NOT_INITIALIZED);

    // Step 02: Initialize the module
    UT_ASSERT_EQUAL(dsCompositeInInit(), dsERR_NONE);

    // Step 03: Call GetNumberOfInputs with NULL pointer
    UT_ASSERT_EQUAL(dsCompositeInGetNumberOfInputs(NULL), dsERR_INVALID_PARAM);

    // Step 04: Terminate the module
    UT_ASSERT_EQUAL(dsCompositeInTerm(), dsERR_NONE);

    // Step 05: Call GetNumberOfInputs after termination
    UT_ASSERT_EQUAL(dsCompositeInGetNumberOfInputs(&pNumberOfInputs), dsERR_NOT_INITIALIZED);
}


/**
 * @brief Ensure dsCompositeInGetStatus() returns correct status and error codes during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 007@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsCompositeInInit() and initialize the module | | dsERR_NONE | Initialization should succeed |
 * |02|Call dsCompositeInGetStatus() with a valid pointer | dsCompositeInStatus_t *pStatus | dsERR_NONE and valid status | Status should be retrieved correctly |
 * |03|Call dsCompositeInGetStatus() with a valid pointer | dsCompositeInStatus_t *pStatus | dsERR_NONE and valid status | Status should be retrieved correctly |
 * |04|Verify the retrieved statuses are the same |  | Success | Ensures the statuses are equal|
 * |05|Call dsCompositeInTerm() to terminate the module| | dsERR_NONE | Termination should succeed |
 * 
 */
void test_l1_dsCompositeIn_positive_dsCompositeInGetStatus(void)
{
    dsCompositeInStatus_t status1, status2;

    // Step 01: Initialize the module
    UT_ASSERT_EQUAL(dsCompositeInInit(), dsERR_NONE);

    // Step 02: Get status for the first time
    UT_ASSERT_EQUAL(dsCompositeInGetStatus(&status1), dsERR_NONE);

    // Step 03: Get status for the second time
    UT_ASSERT_EQUAL(dsCompositeInGetStatus(&status2), dsERR_NONE);

    // Step 04: Verify the retrieved statuses are the same
    UT_ASSERT_EQUAL(memcmp(&status1, &status2, sizeof(dsCompositeInStatus_t)), 0);

    // Step 05: Terminate the module
    UT_ASSERT_EQUAL(dsCompositeInTerm(), dsERR_NONE);
}


/**
 * @brief Ensure dsCompositeInGetStatus() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 008@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsCompositeInGetStatus() without initializing the module | | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * |02|Call dsCompositeInInit() and initialize the module | | dsERR_NONE | Initialization should succeed |
 * |03|Call dsCompositeInGetStatus() with a NULL pointer | NULL pointer | dsERR_INVALID_PARAM | Should return error indicating invalid parameter |
 * |04|Call dsCompositeInTerm() to terminate the module| | dsERR_NONE | Termination should succeed |
 * |05|Call dsCompositeInGetStatus() after terminating the module | | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * 
 * @note Scenarios like dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL are not included due to challenges in realistic simulation.
 */
void test_l1_dsCompositeIn_negative_dsCompositeInGetStatus(void)
{
    // Step 01: Call GetStatus without initialization
    UT_ASSERT_EQUAL(dsCompositeInGetStatus(NULL), dsERR_NOT_INITIALIZED);

    // Step 02: Initialize the module
    UT_ASSERT_EQUAL(dsCompositeInInit(), dsERR_NONE);

    // Step 03: Call GetStatus with NULL pointer
    UT_ASSERT_EQUAL(dsCompositeInGetStatus(NULL), dsERR_INVALID_PARAM);

    // Step 04: Terminate the module
    UT_ASSERT_EQUAL(dsCompositeInTerm(), dsERR_NONE);

    // Step 05: Call GetStatus after termination
    UT_ASSERT_EQUAL(dsCompositeInGetStatus(NULL), dsERR_NOT_INITIALIZED);
}


/**
 * @brief Ensure dsCompositeInSelectPort() sets the COMPOSITE Input port correctly during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 009@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsCompositeInInit() and initialize the module | | dsERR_NONE | Initialization should succeed |
 * |02|Call dsCompositeInGetNumberOfInputs() with a valid pointer | uint8_t *pNumberOfInputs | dsERR_NONE and a valid number of inputs | Number of inputs should be returned correctly |
 * |03|Call dsCompositeInSelectPort() and loop through all valid ports(based on the number of ports) | dsCOMPOSITE_IN_PORT_0 | dsERR_NONE | Port should be set correctly |
 * |04|Call dsCompositeInTerm() to terminate the module| | dsERR_NONE | Termination should succeed |
 * 
 */
void test_l1_dsCompositeIn_positive_dsCompositeInSelectPort(void)
{
    uint8_t numberOfInputs;

    // Step 01: Initialize the module
    UT_ASSERT_EQUAL(dsCompositeInInit(), dsERR_NONE);

    // Step 02: Get number of inputs
    UT_ASSERT_EQUAL(dsCompositeInGetNumberOfInputs(&numberOfInputs), dsERR_NONE);

    // Step 03: Loop through all valid ports and set them
    for (int i = 0; i < numberOfInputs; ++i) {
        UT_ASSERT_EQUAL(dsCompositeInSelectPort(i), dsERR_NONE);
    }

    // Step 04: Terminate the module
    UT_ASSERT_EQUAL(dsCompositeInTerm(), dsERR_NONE);
}


/**
 * @brief Ensure dsCompositeInSelectPort() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 010@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsCompositeInSelectPort() without initializing the module | Port value | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * |02|Call dsCompositeInInit() and initialize the module | | dsERR_NONE | Initialization should succeed |
 * |03|Call dsCompositeInGetNumberOfInputs() with a valid pointer | uint8_t *pNumberOfInputs | dsERR_NONE and a valid number of inputs | Number of inputs should be returned correctly |
 * |04|Call dsCompositeInSelectPort() with an invalid port number (out of range) | dsCOMPOSITE_IN_PORT_MAX| dsERR_INVALID_PARAM | Should return error indicating invalid port number |
 * |05|Call dsCompositeInSelectPort() with an invalid port number (pNumberOfInputs +1) | [Invalid port number] dsERR_INVALID_PARAM | Should return error indicating invalid port number |
 * |06|Call dsCompositeInTerm() to terminate the module| | dsERR_NONE | Termination should succeed |
 * |07|Call dsCompositeInSelectPort() without initializing the module | Port value | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * 
 * @note Scenarios like dsERR_GENERAL and dsERR_OPERATION_NOT_SUPPORTED are not included due to challenges in realistic simulation.
 */
void test_l1_dsCompositeIn_negative_dsCompositeInSelectPort(void)
{
    uint8_t numberOfInputs;

    // Step 01: Call SelectPort without initialization
    UT_ASSERT_EQUAL(dsCompositeInSelectPort(dsCOMPOSITE_IN_PORT_0), dsERR_NOT_INITIALIZED);

    // Step 02: Initialize the module
    UT_ASSERT_EQUAL(dsCompositeInInit(), dsERR_NONE);

    // Step 03: Get number of inputs
    UT_ASSERT_EQUAL(dsCompositeInGetNumberOfInputs(&numberOfInputs), dsERR_NONE);

    // Step 04: Call SelectPort with an out-of-range port number
    UT_ASSERT_EQUAL(dsCompositeInSelectPort(dsCOMPOSITE_IN_PORT_MAX), dsERR_INVALID_PARAM);

    // Step 05: Call SelectPort with an invalid port number (pNumberOfInputs + 1)
    UT_ASSERT_EQUAL(dsCompositeInSelectPort(numberOfInputs + 1), dsERR_INVALID_PARAM);

    // Step 06: Terminate the module
    UT_ASSERT_EQUAL(dsCompositeInTerm(), dsERR_NONE);

    // Step 07: Call SelectPort after termination
    UT_ASSERT_EQUAL(dsCompositeInSelectPort(dsCOMPOSITE_IN_PORT_0), dsERR_NOT_INITIALIZED);
}


/**
 * @brief Ensure dsCompositeInScaleVideo() scales the COMPOSITE In video correctly during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 011@n
 * 
 * **Pre-Conditions:**None@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Initialize the module and select a COMPOSITE input port | | dsERR_NONE | Initialization and port selection should succeed |
 * |02|Call dsCompositeInGetNumberOfInputs() with a valid pointer | uint8_t *pNumberOfInputs | dsERR_NONE and a valid number of inputs | Number of inputs should be returned correctly |
 * |03|Call dsCompositeInSelectPort() with a valid port number based on pNumberOfInputs | dsCOMPOSITE_IN_PORT_0 | dsERR_NONE | Port should be set correctly |
 * |04|Call dsCompositeInScaleVideo() with valid parameters within current resolution | x=10, y=10, width=800, height=800 | dsERR_NONE | Video scaling should succeed |
 * |05|Call dsCompositeInScaleVideo() with different valid parameters to verify flexibility | Different x=50, y=50, width=600, height=600 | dsERR_NONE | Video should be scaled correctly with different parameters |
 * |06|Call dsCompositeInTerm() to terminate the module| | dsERR_NONE | Termination should succeed |
 * 
 */
void test_l1_dsCompositeIn_positive_dsCompositeInScaleVideo(void)
{
    uint8_t numberOfInputs;

    // Step 01: Initialize the module and select a port
    UT_ASSERT_EQUAL(dsCompositeInInit(), dsERR_NONE);
    UT_ASSERT_EQUAL(dsCompositeInSelectPort(dsCOMPOSITE_IN_PORT_0), dsERR_NONE);

    // Step 02: Get number of inputs
    UT_ASSERT_EQUAL(dsCompositeInGetNumberOfInputs(&numberOfInputs), dsERR_NONE);

    // Step 03: Select a valid port number
    UT_ASSERT_EQUAL(dsCompositeInSelectPort((dsCompositeInPort_t)(numberOfInputs-1)), dsERR_NONE);

    // Step 04: Scale video with first set of parameters
    UT_ASSERT_EQUAL(dsCompositeInScaleVideo(10, 10, 800, 800), dsERR_NONE);

    // Step 05: Scale video with a different set of parameters
    UT_ASSERT_EQUAL(dsCompositeInScaleVideo(50, 50, 600, 600), dsERR_NONE);

    // Step 06: Terminate the module
    UT_ASSERT_EQUAL(dsCompositeInTerm(), dsERR_NONE);
}


/**
 * @brief Ensure dsCompositeInScaleVideo() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 012@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsCompositeInScaleVideo() without initializing the module or selecting a port | | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * |02|Initialize the module and select a COMPOSITE input port | | dsERR_NONE | Initialization and port selection should succeed |
 * |03|Call dsCompositeInScaleVideo() with parameters out of current resolution | x=-1, y=10, width=10, height=10 | dsERR_INVALID_PARAM | Should return error indicating invalid parameters |
 * |04|Call dsCompositeInScaleVideo() with parameters out of current resolution | x=10, y=-1, width=10, height=10 | dsERR_INVALID_PARAM | Should return error indicating invalid parameters |
 * |05|Call dsCompositeInScaleVideo() with parameters out of current resolution | x=10, y=10, width=-1, height=10 | dsERR_INVALID_PARAM | Should return error indicating invalid parameters |
 * |06|Call dsCompositeInScaleVideo() with parameters out of current resolution | x=10, y=10, width=10, height=-1 | dsERR_INVALID_PARAM | Should return error indicating invalid parameters |
 * |07|Call dsCompositeInTerm() to terminate the module| | dsERR_NONE | Termination should succeed |
 * |08|Call dsCompositeInScaleVideo() without initializing the module or selecting a port | | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * 
 * @note Scenarios like dsERR_GENERAL, and dsERR_OPERATION_NOT_SUPPORTED are not included due to challenges in realistic simulation.
 */
void test_l1_dsCompositeIn_negative_dsCompositeInScaleVideo(void)
{
    // Step 01: Call ScaleVideo without initialization or port selection
    UT_ASSERT_EQUAL(dsCompositeInScaleVideo(10, 10, 800, 800), dsERR_NOT_INITIALIZED);

    // Step 02: Initialize the module and select a port
    UT_ASSERT_EQUAL(dsCompositeInInit(), dsERR_NONE);
    UT_ASSERT_EQUAL(dsCompositeInSelectPort(dsCOMPOSITE_IN_PORT_0), dsERR_NONE);

    // Step 03 to 06: Test ScaleVideo with invalid parameters
    UT_ASSERT_EQUAL(dsCompositeInScaleVideo(-1, 10, 10, 10), dsERR_INVALID_PARAM);
    UT_ASSERT_EQUAL(dsCompositeInScaleVideo(10, -1, 10, 10), dsERR_INVALID_PARAM);
    UT_ASSERT_EQUAL(dsCompositeInScaleVideo(10, 10, -1, 10), dsERR_INVALID_PARAM);
    UT_ASSERT_EQUAL(dsCompositeInScaleVideo(10, 10, 10, -1), dsERR_INVALID_PARAM);

    // Step 07: Terminate the module
    UT_ASSERT_EQUAL(dsCompositeInTerm(), dsERR_NONE);

    // Step 08: Call ScaleVideo without initialization or port selection
    UT_ASSERT_EQUAL(dsCompositeInScaleVideo(10, 10, 800, 800), dsERR_NOT_INITIALIZED);
}


/**
 * @brief Ensure dsCompositeInRegisterConnectCB() registers the COMPOSITE Input hot plug event correctly during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 013@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsCompositeInInit() and initialize the module | | dsERR_NONE | Initialization should succeed |
 * |02|Call dsCompositeInRegisterConnectCB() with a valid callback function | dsCompositeInConnectCB_t CBFunc | dsERR_NONE | Callback registration should succeed |
 * |03|Call dsCompositeInTerm() to terminate the module| | dsERR_NONE | Termination should succeed |
 * 
 */
// Example callback function
void exampleConnectCallback(dsCompositeInPort_t Port, bool isPortConnected) {
    // Implementation of the callback (dummy for testing)
}
void test_l1_dsCompositeIn_positive_dsCompositeInRegisterConnectCB(void)
{
    // Step 01: Initialize the module
    UT_ASSERT_EQUAL(dsCompositeInInit(), dsERR_NONE);

    // Step 02: Register the callback function
    UT_ASSERT_EQUAL(dsCompositeInRegisterConnectCB(exampleConnectCallback), dsERR_NONE);

    // Step 03: Terminate the module
    UT_ASSERT_EQUAL(dsCompositeInTerm(), dsERR_NONE);
}


/**
 * @brief Ensure dsCompositeInRegisterConnectCB() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 014@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsCompositeInRegisterConnectCB() without initializing the module | dsCompositeInConnectCB_t CBFunc| dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * |02|Call dsCompositeInInit() and initialize the module | | dsERR_NONE | Initialization should succeed |
 * |03|Call dsCompositeInRegisterConnectCB() with a NULL or invalid callback function | NULL or invalid callback | dsERR_INVALID_PARAM | Should return error indicating invalid parameter |
 * |04|Call dsCompositeInTerm() to terminate the module| | dsERR_NONE | Termination should succeed |
 * |05|Call dsCompositeInRegisterConnectCB() without initializing the module | dsCompositeInConnectCB_t CBFunc | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * 
 * @note Scenarios like dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL are not included due to challenges in realistic simulation.
 */
void test_l1_dsCompositeIn_negative_dsCompositeInRegisterConnectCB(void)
{
    // Step 01: Call RegisterConnectCB without initialization
    UT_ASSERT_EQUAL(dsCompositeInRegisterConnectCB(exampleConnectCallback), dsERR_NOT_INITIALIZED);

    // Step 02: Initialize the module
    UT_ASSERT_EQUAL(dsCompositeInInit(), dsERR_NONE);

    // Step 03: Register the callback with NULL or invalid function
    UT_ASSERT_EQUAL(dsCompositeInRegisterConnectCB(NULL), dsERR_INVALID_PARAM);

    // Step 04: Terminate the module
    UT_ASSERT_EQUAL(dsCompositeInTerm(), dsERR_NONE);

    // Step 05: Call RegisterConnectCB after termination
    UT_ASSERT_EQUAL(dsCompositeInRegisterConnectCB(exampleConnectCallback), dsERR_NOT_INITIALIZED);
}


/**
 * @brief Ensure dsCompositeInRegisterSignalChangeCB() registers the Composite Input Signal Change event correctly during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 015@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsCompositeInInit() and initialize the module | | dsERR_NONE | Initialization should succeed |
 * |02|Call dsCompositeInRegisterSignalChangeCB() with a valid callback function | dsCompositeInSignalChangeCB_t CBFunc | dsERR_NONE | Callback registration should succeed |
 * |03|Call dsCompositeInTerm() to terminate the module| | dsERR_NONE | Termination should succeed |
 * 
 */
// Example callback function for signal change
void exampleSignalChangeCallback(dsCompositeInPort_t port, dsCompInSignalStatus_t sigStatus) {
    // Implementation of the callback (dummy for testing)
}

void test_l1_dsCompositeIn_positive_dsCompositeInRegisterSignalChangeCB(void)
{
    // Step 01: Initialize the module
    UT_ASSERT_EQUAL(dsCompositeInInit(), dsERR_NONE);

    // Step 02: Register the signal change callback function
    UT_ASSERT_EQUAL(dsCompositeInRegisterSignalChangeCB(exampleSignalChangeCallback), dsERR_NONE);

    // Step 03: Terminate the module
    UT_ASSERT_EQUAL(dsCompositeInTerm(), dsERR_NONE);
}


/**
 * @brief Ensure dsCompositeInRegisterSignalChangeCB() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 016@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsCompositeInRegisterSignalChangeCB() without initializing the module | dsCompositeInSignalChangeCB_t CBFunc | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * |02|Call dsCompositeInInit() and initialize the module | | dsERR_NONE | Initialization should succeed |
 * |03|Call dsCompositeInRegisterSignalChangeCB() with a NULL or invalid callback function | NULL or invalid callback | dsERR_INVALID_PARAM | Should return error indicating invalid parameter |
 * |04|Call dsCompositeInTerm() to terminate the module| | dsERR_NONE | Termination should succeed |
 * |05|Call dsCompositeInRegisterSignalChangeCB() without initializing the module | dsCompositeInSignalChangeCB_t CBFunc | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * 
 * @note Scenarios like dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL are not included due to challenges in realistic simulation.
 */
void test_l1_dsCompositeIn_negative_dsCompositeInRegisterSignalChangeCB(void)
{
    // Step 01: Call RegisterSignalChangeCB without initialization
    UT_ASSERT_EQUAL(dsCompositeInRegisterSignalChangeCB(exampleSignalChangeCallback), dsERR_NOT_INITIALIZED);

    // Step 02: Initialize the module
    UT_ASSERT_EQUAL(dsCompositeInInit(), dsERR_NONE);

    // Step 03: Register the callback with NULL or invalid function
    UT_ASSERT_EQUAL(dsCompositeInRegisterSignalChangeCB(NULL), dsERR_INVALID_PARAM);

    // Step 04: Terminate the module
    UT_ASSERT_EQUAL(dsCompositeInTerm(), dsERR_NONE);

    // Step 05: Call RegisterSignalChangeCB after termination
    UT_ASSERT_EQUAL(dsCompositeInRegisterSignalChangeCB(exampleSignalChangeCallback), dsERR_NOT_INITIALIZED);
}


/**
 * @brief Ensure dsCompositeInRegisterStatusChangeCB() registers the Composite Input Status Change event correctly during positive scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 017@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsCompositeInInit() and initialize the module | | dsERR_NONE | Initialization should succeed |
 * |02|Call dsCompositeInRegisterStatusChangeCB() with a valid callback function | dsCompositeInStatusChangeCB_t CBFunc | dsERR_NONE | Callback registration should succeed |
 * |03|Call dsCompositeInTerm() to terminate the module| | dsERR_NONE | Termination should succeed |
 * 
 */
// Example callback function for status change
void exampleStatusChangeCallback(dsCompositeInStatus_t inputStatus) {
    // Implementation of the callback (dummy for testing)
}

void test_l1_dsCompositeIn_positive_dsCompositeInRegisterStatusChangeCB(void)
{
    // Step 01: Initialize the module
    UT_ASSERT_EQUAL(dsCompositeInInit(), dsERR_NONE);

    // Step 02: Register the status change callback function
    UT_ASSERT_EQUAL(dsCompositeInRegisterStatusChangeCB(exampleStatusChangeCallback), dsERR_NONE);

    // Step 03: Terminate the module
    UT_ASSERT_EQUAL(dsCompositeInTerm(), dsERR_NONE);
}


/**
 * @brief Ensure dsCompositeInRegisterStatusChangeCB() returns correct error codes during negative scenarios
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 018@n
 * 
 * **Pre-Conditions:**@n
 * None.
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Test Data|Expected Result|Notes|
 * |:--:|---------|----------|--------------|-----|
 * |01|Call dsCompositeInRegisterStatusChangeCB() without initializing the module | dsCompositeInStatusChangeCB_t CBFunc | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * |02|Call dsCompositeInInit() and initialize the module | | dsERR_NONE | Initialization should succeed |
 * |03|Call dsCompositeInRegisterStatusChangeCB() with a NULL or invalid callback function | NULL or invalid callback | dsERR_INVALID_PARAM | Should return error indicating invalid parameter |
 * |04|Call dsCompositeInTerm() to terminate the module| | dsERR_NONE | Termination should succeed |
 * |05|Call dsCompositeInRegisterStatusChangeCB() without initializing the module | dsCompositeInStatusChangeCB_t CBFunc | dsERR_NOT_INITIALIZED | Should return error indicating the module is not initialized |
 * 
 * @note Scenarios like dsERR_OPERATION_NOT_SUPPORTED and dsERR_GENERAL are not included due to challenges in realistic simulation.
 */
void test_l1_dsCompositeIn_negative_dsCompositeInRegisterStatusChangeCB(void)
{
    // Step 01: Call RegisterStatusChangeCB without initialization
    UT_ASSERT_EQUAL(dsCompositeInRegisterStatusChangeCB(exampleStatusChangeCallback), dsERR_NOT_INITIALIZED);

    // Step 02: Initialize the module
    UT_ASSERT_EQUAL(dsCompositeInInit(), dsERR_NONE);

    // Step 03: Register the callback with NULL or invalid function
    UT_ASSERT_EQUAL(dsCompositeInRegisterStatusChangeCB(NULL), dsERR_INVALID_PARAM);

    // Step 04: Terminate the module
    UT_ASSERT_EQUAL(dsCompositeInTerm(), dsERR_NONE);

    // Step 05: Call RegisterStatusChangeCB after termination
    UT_ASSERT_EQUAL(dsCompositeInRegisterStatusChangeCB(exampleStatusChangeCallback), dsERR_NOT_INITIALIZED);
}


static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main test(s) for this module
 *
 * @return int - 0 on success, otherwise failure
 */
int test_l1_dsCompositeIn_register ( void )
{
	/* add a suite to the registry */
	pSuite = UT_add_suite( "[L1 dsCompositeIn]", NULL, NULL );
	if ( NULL == pSuite )
	{
		return -1;
	}	

	UT_add_test( pSuite, "dsCompositeInInit_L1_positive" ,test_l1_dsCompositeIn_positive_dsCompositeInInit );
	UT_add_test( pSuite, "dsCompositeInInit_L1_negative" ,test_l1_dsCompositeIn_negative_dsCompositeInInit );
	UT_add_test( pSuite, "dsCompositeInTerm_L1_positive" ,test_l1_dsCompositeIn_positive_dsCompositeInTerm );
	UT_add_test( pSuite, "dsCompositeInTerm_L1_negative" ,test_l1_dsCompositeIn_negative_dsCompositeInTerm );
	UT_add_test( pSuite, "dsCompositeInGetNumberOfInputs_L1_positive" ,test_l1_dsCompositeIn_positive_dsCompositeInGetNumberOfInputs );
	UT_add_test( pSuite, "dsCompositeInGetNumberOfInputs_L1_negative" ,test_l1_dsCompositeIn_negative_dsCompositeInGetNumberOfInputs );
	UT_add_test( pSuite, "dsCompositeInGetStatus_L1_positive" ,test_l1_dsCompositeIn_positive_dsCompositeInGetStatus );
	UT_add_test( pSuite, "dsCompositeInGetStatus_L1_negative" ,test_l1_dsCompositeIn_negative_dsCompositeInGetStatus );
	UT_add_test( pSuite, "dsCompositeInSelectPort_L1_positive" ,test_l1_dsCompositeIn_positive_dsCompositeInSelectPort );
	UT_add_test( pSuite, "dsCompositeInSelectPort_L1_negative" ,test_l1_dsCompositeIn_negative_dsCompositeInSelectPort );
	UT_add_test( pSuite, "dsCompositeInScaleVideo_L1_positive" ,test_l1_dsCompositeIn_positive_dsCompositeInScaleVideo );
	UT_add_test( pSuite, "dsCompositeInScaleVideo_L1_negative" ,test_l1_dsCompositeIn_negative_dsCompositeInScaleVideo );
	UT_add_test( pSuite, "dsCompositeInRegisterConnectCB_L1_positive" ,test_l1_dsCompositeIn_positive_dsCompositeInRegisterConnectCB );
	UT_add_test( pSuite, "dsCompositeInRegisterConnectCB_L1_negative" ,test_l1_dsCompositeIn_negative_dsCompositeInRegisterConnectCB );
	UT_add_test( pSuite, "dsCompositeInRegisterSignalChangeCB_L1_positive" ,test_l1_dsCompositeIn_positive_dsCompositeInRegisterSignalChangeCB );
	UT_add_test( pSuite, "dsCompositeInRegisterSignalChangeCB_L1_negative" ,test_l1_dsCompositeIn_negative_dsCompositeInRegisterSignalChangeCB );
	UT_add_test( pSuite, "dsCompositeInRegisterStatusChangeCB_L1_positive" ,test_l1_dsCompositeIn_positive_dsCompositeInRegisterStatusChangeCB );
	UT_add_test( pSuite, "dsCompositeInRegisterStatusChangeCB_L1_negative" ,test_l1_dsCompositeIn_negative_dsCompositeInRegisterStatusChangeCB );
	

	return 0;
} 
