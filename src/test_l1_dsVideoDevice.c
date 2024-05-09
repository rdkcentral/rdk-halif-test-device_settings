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
 * @defgroup DS_VideoDevice_HALTEST Device Settings Video Device HAL Tests
 * @{
 */

/**
 * @defgroup DS_VideoDevice_HALTEST_L1 Device Settings Video Device HAL Tests L1 File
 * @{
 * @parblock
 *
 * ### L1 Tests for DS Video Device HAL :
 *
 * Level 1 unit test cases for all APIs of Device Settings Video Device HAL
 *
 * **Pre-Conditions:**  None@n
 * **Dependencies:** None@n
 *
 * Refer to API Definition specification documentation : [ds-video-device_halSpec.md](../../docs/pages/ds-video-device_halSpec.md)
 *
 * @endparblock
 */

/**
 * @file test_l1_dsVideoDevice.c
 *
 */


#include <string.h>
#include <stdlib.h>

#include <ut.h>
#include <ut_log.h>
#include "dsVideoDevice.h"

static int gTestGroup = 1;
static int gTestID = 1;
#define DS_ASSERT_AUTO_TERM_NUMERICAL(value, comparison){\
    if(value != comparison){\
        UT_LOG("\n In %s Comparison: [%d = %d]\n", __FUNCTION__, value, comparison);\
        dsVideoDeviceTerm();\
        UT_FAIL();\
    }\
}\

#define DS_ASSERT_AUTO_TERM_STRING(value, comparison){\
    if(strcmp(value, comparison) != 0){\
        UT_LOG("\n In %s Comparison: [%s = %s]\n", __FUNCTION__, value, comparison);\
        dsVideoDeviceTerm();\
        UT_FAIL();\
    }\
}\

/**
 * @brief Ensure dsVideoDeviceInit() correctly initializes all video devices during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 001@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsVideoDeviceInit() to initialize all video devices | | dsERR_NONE | Video devices should be initialized successfully |
 * |02|De-initialize the video devices using dsVideoDeviceTerm() for cleanup | | dsERR_NONE | Clean up after test |
 * |03|Call dsVideoDeviceInit() to initialize all video devices | | dsERR_NONE | Video devices should be initialized successfully |
 * |04|De-initialize the video devices using dsVideoDeviceTerm() for cleanup | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsVideoDevice_positive_dsVideoDeviceInit(void)
{
    gTestID = 1;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 

    // Step 01: Initialize video devices
    int result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: De-initialize the video devices for cleanup
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Initialize video devices again
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 04: De-initialize the video devices for cleanup
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsVideoDeviceInit() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 002@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsVideoDeviceInit() to initialize all video devices | | dsERR_NONE | Video devices should be initialized successfully |
 * |02|Call dsVideoDeviceInit() again without terminating the previous initialization | | dsERR_ALREADY_INITIALIZED | Should not allow double initialization |
 * |03|De-initialize the video devices using dsVideoDeviceTerm() for cleanup | | dsERR_NONE | Clean up after test |
 * 
 * @note The return value dsERR_GENERAL may be difficult to test in a simulated environment
 * 
 */
void test_l1_dsVideoDevice_negative_dsVideoDeviceInit(void)
{
    gTestID = 2;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 

    // Step 01: Initialize video devices
    int result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Try initializing again without terminating
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsVideoDeviceInit();
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_ALREADY_INITIALIZED);
    #endif

    // Step 03: De-initialize the video devices for cleanup
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsVideoDeviceTerm() correctly de-initializes all video devices during positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 003@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsVideoDeviceInit() to initialize all video devices | | dsERR_NONE | Video devices should be initialized successfully |
 * |02|De-initialize the video devices using dsVideoDeviceTerm() for cleanup | | dsERR_NONE | Clean up after test |
 * |03|Call dsVideoDeviceInit() to initialize all video devices | | dsERR_NONE | Video devices should be initialized successfully |
 * |04|De-initialize the video devices using dsVideoDeviceTerm() for cleanup | | dsERR_NONE | Clean up after test |
 * 
 */
void test_l1_dsVideoDevice_positive_dsVideoDeviceTerm(void)
{
    gTestID = 3;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 

    // Step 01: Initialize video devices
    int result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: De-initialize the video devices for cleanup
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Initialize video devices again
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 04: De-initialize the video devices for cleanup
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Ensure dsVideoDeviceTerm() returns correct error codes during negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 004@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsVideoDeviceTerm() without prior initialization of video devices | | dsERR_NOT_INITIALIZED | Should report module not initialized |
 * |02|Initialize video devices using dsVideoDeviceInit() | | dsERR_NONE | Video devices should be initialized successfully |
 * |03|Call dsVideoDeviceTerm() to de-initialize all video devices | | dsERR_NONE | Video devices should be de-initialized successfully |
 * |04|Call dsVideoDeviceTerm() again without re-initialization | | dsERR_NOT_INITIALIZED | Should report module not initialized |
 * 
 * @note The return value dsERR_GENERAL may be difficult to test in a simulated environment
 * 
 */
void test_l1_dsVideoDevice_negative_dsVideoDeviceTerm(void)
{
    gTestID = 4;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID); 

    // Step 01: Call de-initialization without prior initialization
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    int result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);
    #endif

    // Step 02: Initialize video devices
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: De-initialize the video devices
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 04: Call de-initialization again without re-initialization
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);
    #endif

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Test guidance to ensure dsGetVideoDevice() correctly fetches the handle for the video device in positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 005@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize video devices using dsVideoDeviceInit() | | dsERR_NONE | Video devices should be initialized successfully |
 * |02|Call dsGetVideoDevice() using index as 0 and a pointer to retrieve the handle | int=index, int=*handle | dsERR_NONE and (handle >= 0) | Should obtain a valid handle successfully |
 * |03|De-initialize the video devices using dsVideoDeviceTerm() | | dsERR_NONE | Video devices should be de-initialized successfully|
 * 
 * @note Index is always set to 0, due to devices only having a single video device.
 */
void test_l1_dsVideoDevice_positive_dsGetVideoDevice(void)
{
    gTestID = 5;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    // Step 01: Initialize video devices
    int result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Get the video device handle
    intptr_t handle = -1;
    result = dsGetVideoDevice(0, &handle);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
    UT_ASSERT_TRUE(handle >= 0);

    // Step 03: De-initialize the video devices
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__);
}

/**
 * @brief Test guidance to ensure dsGetVideoDevice() returns correct error codes for negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 006@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetVideoDevice() without prior initialization of video devices| int=index, int=*handle | dsERR_NOT_INITIALIZED | Should report module not initialized |
 * |02|Initialize video devices using dsVideoDeviceInit() | | dsERR_NONE | Video devices should be initialized successfully |
 * |03|Call dsGetVideoDevice() with index > 0 and a valid pointer to retrieve handle | int=-1, int=*handle | dsERR_INVALID_PARAM | Should report invalid parameter since index should always be 0 |
 * |04|Call dsGetVideoDevice() with index set to 0 but a null pointer for handle | int=index, NULL | dsERR_INVALID_PARAM | Should report invalid parameter |
 * |05|De-initialize the video devices using dsVideoDeviceTerm() | | dsERR_NONE | Video devices should be de-initialized successfully|
 * |06|Call dsGetVideoDevice() after prior termination of video devices| int=index, int=*handle | dsERR_NOT_INITIALIZED | Should report module not initialized |
 *
 * @note The return value dsERR_GENERAL and dsERR_OPERATION_NOT_SUPPORTED may be difficult to test in a simulated environment
 * 
 */
void test_l1_dsVideoDevice_negative_dsGetVideoDevice(void)
{
    gTestID = 6;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);

    // Step 01: Get the video device handle without prior initialization
    intptr_t handle = -1;
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    int result = dsGetVideoDevice(0, &handle);
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);
    #endif

    // Step 02: Initialize video devices
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Get the video device handle with invalid index
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsGetVideoDevice(-1, &handle);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
    #endif

    // Step 04: Get the video device handle with valid index but null pointer for handle
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsGetVideoDevice(0, NULL);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
    #endif

    // Step 05: De-initialize the video devices
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 06: Get the video device handle after prior termination
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsGetVideoDevice(0, &handle);
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);
    #endif

    UT_LOG("\n Out %s\n", __FUNCTION__);
}

/**
 * @brief Test guidance to ensure dsSetDFC() correctly sets the screen zoom mode in positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 007@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize video devices using dsVideoDeviceInit() | | dsERR_NONE | Video devices should be initialized successfully |
 * |02|Obtain video device handle using dsGetVideoDevice() | int=index, int=*handle | dsERR_NONE and (handle >= 0) | Should obtain a valid handle successfully |
 * |03|Set the DFC mode using dsSetDFC() with the obtained handle and a valid zoom mode | int=handle, dsVideoZoom_t=dsVIDEO_ZOOM_UNKNOWN | dsERR_NONE | Should successfully set the DFC mode |
 * |04|Set the DFC mode using dsSetDFC() with the obtained handle and a valid zoom mode | int=handle, dsVideoZoom_t=dsVIDEO_ZOOM_NONE | dsERR_NONE | Should successfully set the DFC mode |
 * |05|Set the DFC mode using dsSetDFC() with the obtained handle and a valid zoom mode | int=handle, dsVideoZoom_t=dsVIDEO_ZOOM_FULL | dsERR_NONE | Should successfully set the DFC mode |
 * |06|Set the DFC mode using dsSetDFC() with the obtained handle and a valid zoom mode | int=handle, dsVideoZoom_t=dsVIDEO_ZOOM_LB_16_9 | dsERR_NONE | Should successfully set the DFC mode |
 * |07|Set the DFC mode using dsSetDFC() with the obtained handle and a valid zoom mode | int=handle, dsVideoZoom_t=dsVIDEO_ZOOM_LB_14_9 | dsERR_NONE | Should successfully set the DFC mode |
 * |08|Set the DFC mode using dsSetDFC() with the obtained handle and a valid zoom mode | int=handle, dsVideoZoom_t=dsVIDEO_ZOOM_CCO | dsERR_NONE | Should successfully set the DFC mode |
 * |09|Set the DFC mode using dsSetDFC() with the obtained handle and a valid zoom mode | int=handle, dsVideoZoom_t=dsVIDEO_ZOOM_PAN_SCAN | dsERR_NONE | Should successfully set the DFC mode |
 * |10|Set the DFC mode using dsSetDFC() with the obtained handle and a valid zoom mode | int=handle, dsVideoZoom_t=dsVIDEO_ZOOM_LB_2_21_1_ON_4_3 | dsERR_NONE | Should successfully set the DFC mode |
 * |11|Set the DFC mode using dsSetDFC() with the obtained handle and a valid zoom mode | int=handle, dsVideoZoom_t=dsVIDEO_ZOOM_LB_2_21_1_ON_16_9 | dsERR_NONE | Should successfully set the DFC mode |
 * |12|Set the DFC mode using dsSetDFC() with the obtained handle and a valid zoom mode | int=handle, dsVideoZoom_t=dsVIDEO_ZOOM_PLATFORM | dsERR_NONE | Should successfully set the DFC mode |
 * |13|Set the DFC mode using dsSetDFC() with the obtained handle and a valid zoom mode | int=handle, dsVideoZoom_t=dsVIDEO_ZOOM_16_9_ZOOM | dsERR_NONE | Should successfully set the DFC mode |
 * |14|Set the DFC mode using dsSetDFC() with the obtained handle and a valid zoom mode | int=handle, dsVideoZoom_t=dsVIDEO_ZOOM_PILLARBOX_4_3 | dsERR_NONE | Should successfully set the DFC mode |
 * |15|Set the DFC mode using dsSetDFC() with the obtained handle and a valid zoom mode | int=handle, dsVideoZoom_t=dsVIDEO_ZOOM_WIDE_4_3 | dsERR_NONE | Should successfully set the DFC mode |
 * |16|De-initialize the video devices using dsVideoDeviceTerm() | | dsERR_NONE | Video devices should be de-initialized successfully|
 * 
 */
void test_l1_dsVideoDevice_positive_dsSetDFC (void) 
{

    gTestID = 7;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;
    intptr_t handle = -1;
    
    // 01: Initialize video devices
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // 02: Obtain video device handle
    result = dsGetVideoDevice(0, &handle);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
    UT_ASSERT_TRUE(handle >= 0);

    // 03-15: Set DFC mode with various zoom modes
    for (int i = 0; i < dsVIDEO_ZOOM_MAX; ++i) 
    {
        dsVideoZoom_t zoomMode = i;
        result = dsSetDFC(handle, zoomMode);
        DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
    }

    // 16: De-initialize video devices
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Test guidance to ensure dsSetDFC() returns correct error codes for negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 008@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsSetDFC() without prior initialization of video devices | int=handle, dsVideoZoom_t=dsVIDEO_ZOOM_NONE | dsERR_NOT_INITIALIZED | Should report module not initialized |
 * |02|Initialize video devices using dsVideoDeviceInit() | | dsERR_NONE | Video devices should be initialized successfully |
 * |03|Obtain video device handle using dsGetVideoDevice() | int=index, int=*handle | dsERR_NONE and (handle >= 0) | Should obtain a valid handle successfully |
 * |04|Call dsSetDFC() with an invalid handle | int=-1, dsVideoZoom_t=dsVIDEO_ZOOM_NONE | dsERR_INVALID_PARAM | Should report invalid parameter |
 * |05|Call dsSetDFC() with an invalid zoom mode | int=handle, dsVideoZoom_t=dsVIDEO_ZOOM_MAX | dsERR_INVALID_PARAM | Should report invalid parameter |
 * |06|De-initialize the video devices using dsVideoDeviceTerm() | | dsERR_NONE | Video devices should be de-initialized successfully|
 * |07|Call dsSetDFC() after termination of video devices | int=handle, dsVideoZoom_t=dsVIDEO_ZOOM_NONE | dsERR_NOT_INITIALIZED | Should report module not initialized |
 *
 * @note The return value dsERR_GENERAL and dsERR_OPERATION_NOT_SUPPORTED may be difficult to test in a simulated environment
 * 
 */
void test_l1_dsVideoDevice_negative_dsSetDFC (void) 
{
    gTestID = 8;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    dsError_t result;
    intptr_t handle = -1;
    
    // 01: Call dsSetDFC() without initialization
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsSetDFC(-1, dsVIDEO_ZOOM_NONE);
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);
    #endif

    // 02: Initialize video devices
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // 03: Obtain video device handle
    result = dsGetVideoDevice(0, &handle);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
    UT_ASSERT_TRUE(handle >= 0);

    // 04: Call dsSetDFC() with an invalid handle
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsSetDFC(-1, dsVIDEO_ZOOM_NONE);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
    #endif

    // 05: Call dsSetDFC() with an invalid zoom mode
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsSetDFC(handle, dsVIDEO_ZOOM_MAX);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
    #endif

    // 06: De-initialize video devices
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // 07: Call dsSetDFC() after termination
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsSetDFC(handle, dsVIDEO_ZOOM_NONE);
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);
    #endif
    UT_LOG("\n Out %s\n", __FUNCTION__); 
}


/**
 * @brief Test guidance to ensure dsGetDFC() correctly fetches the screen zoom mode in positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 009@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize video devices using dsVideoDeviceInit() | | dsERR_NONE | Video devices should be initialized successfully |
 * |02|Obtain video device handle using dsGetVideoDevice() | int=index, int=*handle | dsERR_NONE and (handle >= 0) | Should obtain a valid handle successfully |
 * |03|Get the DFC mode using dsGetDFC() with the obtained handle |int=handle, dsVideoZoom_t*| dsERR_NONE | Should successfully fetch the DFC mode |
 * |04|Get the DFC mode using dsGetDFC() again |int=handle, dsVideoZoom_t*| dsERR_NONE | Should successfully fetch the DFC mode |
 * |05|Compare the results to make sure they match || Success | Should be equal |
 * |06|De-initialize the video devices using dsVideoDeviceTerm() | | dsERR_NONE | Video devices should be de-initialized successfully|
 * 
 */
void test_l1_dsVideoDevice_positive_dsGetDFC(void)
{
    gTestID = 9;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Define variables
    int result;
    int index = 0;
    intptr_t handle = -1;
    dsVideoZoom_t dfc_mode_1;
    dsVideoZoom_t dfc_mode_2;

    // Step 01: Initialize video devices
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Obtain video device handle
    result = dsGetVideoDevice(index, &handle);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
    DS_ASSERT_AUTO_TERM_NUMERICAL((handle >= 0), true);

    // Step 03: Get the DFC mode using dsGetDFC() with the obtained handle
    result = dsGetDFC(handle, &dfc_mode_1);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

    // Step 04: Get the DFC mode using dsGetDFC() again
    result = dsGetDFC(handle, &dfc_mode_2);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

    // Step 05: Compare the results to make sure they match
    DS_ASSERT_AUTO_TERM_NUMERICAL(memcmp(&dfc_mode_1, &dfc_mode_2, sizeof(dsVideoZoom_t)),0);

    // Step 06: De-initialize the video devices
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("\n Out %s\n", __FUNCTION__); 
}


/**
 * @brief Test guidance to ensure dsGetDFC() returns correct error codes for negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 010@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetDFC() without prior initialization of video devices |int=handle, dsVideoZoom_t*| dsERR_NOT_INITIALIZED | Should report module not initialized |
 * |02|Initialize video devices using dsVideoDeviceInit() | | dsERR_NONE | Video devices should be initialized successfully |
 * |03|Obtain video device handle using dsGetVideoDevice() | int=index, int=*handle | dsERR_NONE and (handle >= 0) | Should obtain a valid handle successfully |
 * |04|Call dsGetDFC() with an invalid handle |int=-1, dsVideoZoom_t*| dsERR_INVALID_PARAM | Should report invalid parameter |
 * |05|Call dsGetDFC() with an invalid pointer |int=handle, NULL| dsERR_INVALID_PARAM | Should report invalid parameter |
 * |06|De-initialize the video devices using dsVideoDeviceTerm() | | dsERR_NONE | Video devices should be de-initialized successfully|
 * |07|Call dsGetDFC() after termination of video devices |int=handle, dsVideoZoom_t*| dsERR_NOT_INITIALIZED | Should report module not initialized |
 * 
 * @note The return value dsERR_GENERAL and dsERR_OPERATION_NOT_SUPPORTED may be difficult to test in a simulated environment
 * 
 */
void test_l1_dsVideoDevice_negative_dsGetDFC(void)
{
    gTestID = 10;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Define variables
    int result;
    int index = 0;
    intptr_t handle = -1;
    dsVideoZoom_t dfc_mode;

    // Step 01: Call dsGetDFC() without prior initialization
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsGetDFC(handle, &dfc_mode);
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);
    #endif

    // Step 02: Initialize video devices
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Obtain video device handle
    result = dsGetVideoDevice(index, &handle);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
    DS_ASSERT_AUTO_TERM_NUMERICAL((handle >= 0), true);

    // Step 04: Call dsGetDFC() with an invalid handle
    result = dsGetDFC(-1, &dfc_mode);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

    // Step 05: Call dsGetDFC() with an invalid pointer
    result = dsGetDFC(handle, NULL);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

    // Step 06: De-initialize the video devices
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 07: Call dsGetDFC() after termination
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsGetDFC(handle, &dfc_mode);
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);
    #endif
    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

/**
 * @brief Test guidance to ensure dsGetHDRCapabilities() correctly fetches the HDR capabilities in positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 011@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize video devices using dsVideoDeviceInit() | | dsERR_NONE | Video devices should be initialized successfully |
 * |02|Obtain video device handle using dsGetVideoDevice() | int=index, int=*handle | dsERR_NONE and (handle >= 0) | Should obtain a valid handle successfully |
 * |03|Get HDR capabilities using dsGetHDRCapabilities() with the obtained handle |int=handle, int*| dsERR_NONE | Should successfully fetch the HDR capabilities |
 * |04|Get HDR capabilities using dsGetHDRCapabilities() again |int=handle, int*| dsERR_NONE | Should successfully fetch the HDR capabilities |
 * |05|Compare the results to make sure they are the same || Success | The returned values should be the same |
 * |06|De-initialize the video devices using dsVideoDeviceTerm() | | dsERR_NONE | Video devices should be de-initialized successfully|
 * 
 */
void test_l1_dsVideoDevice_positive_dsGetHDRCapabilities(void)
{
    gTestID = 11;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Define variables
    int result;
    int index = 0;
    intptr_t handle = -1;
    int hdr_capabilities_1 = dsHDRSTANDARD_NONE;
    int hdr_capabilities_2 = dsHDRSTANDARD_NONE;

    // Step 01: Initialize video devices
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Obtain video device handle
    result = dsGetVideoDevice(index, &handle);
    UT_LOG("\nHandle: %d\n", handle);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
    DS_ASSERT_AUTO_TERM_NUMERICAL((handle >= 0), true);

    // Step 03: Get HDR capabilities using dsGetHDRCapabilities() with the obtained handle
    result = dsGetHDRCapabilities(handle, &hdr_capabilities_1);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

    // Step 04: Get HDR capabilities using dsGetHDRCapabilities() again
    result = dsGetHDRCapabilities(handle, &hdr_capabilities_2);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

    // Step 05: Compare the results to make sure they match
    UT_LOG("\nhdr1: %d, hrd2: %d\n", hdr_capabilities_1, hdr_capabilities_2);
    DS_ASSERT_AUTO_TERM_NUMERICAL(hdr_capabilities_1, hdr_capabilities_2);

    // Step 06: De-initialize the video devices
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("\n Out %s\n", __FUNCTION__); 
}


/**
 * @brief Test guidance to ensure dsGetHDRCapabilities() returns correct error codes for negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 012@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetHDRCapabilities() without prior initialization of video devices |int=handle, int*| dsERR_NOT_INITIALIZED | Should report module not initialized |
 * |02|Initialize video devices using dsVideoDeviceInit() | | dsERR_NONE | Video devices should be initialized successfully |
 * |03|Obtain video device handle using dsGetVideoDevice() | int=index, int=*handle | dsERR_NONE and (handle >= 0) | Should obtain a valid handle successfully |
 * |04|Call dsGetHDRCapabilities() with an invalid handle |int=-1, int*| dsERR_INVALID_PARAM | Should report invalid parameter |
 * |05|Call dsGetHDRCapabilities() with an null parameter |int=handle, NULL| dsERR_INVALID_PARAM | Should report invalid parameter |
 * |06|De-initialize the video devices using dsVideoDeviceTerm() | | dsERR_NONE | Video devices should be de-initialized successfully|
 * |07|Call dsGetHDRCapabilities() after termination of video devices |int=handle, int*| dsERR_NOT_INITIALIZED | Should report module not initialized |
 * 
 * @note The return value dsERR_GENERAL and dsERR_OPERATION_NOT_SUPPORTED may be difficult to test in a simulated environment
 * 
 */
void test_l1_dsVideoDevice_negative_dsGetHDRCapabilities(void)
{
    gTestID = 12;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Define variables
    int result;
    int index = 0;
    intptr_t handle = -1;
    int hdr_capabilities;

    // Step 01: Call dsGetHDRCapabilities() without prior initialization
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsGetHDRCapabilities(handle, &hdr_capabilities); // Note: using handle for HDR capabilities for this error case
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);
    #endif

    // Step 02: Initialize video devices
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Obtain video device handle
    result = dsGetVideoDevice(index, &handle);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
    DS_ASSERT_AUTO_TERM_NUMERICAL((handle >= 0), true);

    // Step 04: Call dsGetHDRCapabilities() with an invalid handle
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsGetHDRCapabilities(-1, &hdr_capabilities);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
    #endif

    // Step 05: Call dsGetHDRCapabilities() with a null parameter
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsGetHDRCapabilities(handle, NULL);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
    #endif

    // Step 06: De-initialize the video devices
    result = dsVideoDeviceTerm();
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

    // Step 07: Call dsGetHDRCapabilities() after termination
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsGetHDRCapabilities(handle, &hdr_capabilities);
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);
    #endif
    UT_LOG("\n Out %s\n", __FUNCTION__); 
}


/**
 * @brief Test guidance to ensure dsGetSupportedVideoCodingFormats() correctly fetches supported video formats in positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 013@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize video devices using dsVideoDeviceInit() | | dsERR_NONE | Video devices should be initialized successfully |
 * |02|Obtain video device handle using dsGetVideoDevice() | int=index, int=*handle | dsERR_NONE and (handle >= 0) | Should obtain a valid handle successfully |
 * |03|Get supported video formats using dsGetSupportedVideoCodingFormats() with the obtained handle |int=handle, unsigned int*| dsERR_NONE | Should successfully fetch the supported video formats |
 * |04|Get supported video formats using dsGetSupportedVideoCodingFormats() with the obtained handle |int=handle, unsigned int*| dsERR_NONE | Should successfully fetch the supported video formats |
 * |05|Compare the returned values to make sure they return the same value || Success | The values should be equal |
 * |06|De-initialize the video devices using dsVideoDeviceTerm() | | dsERR_NONE | Video devices should be de-initialized successfully|
 * 
 */
void test_l1_dsVideoDevice_positive_dsGetSupportedVideoCodingFormats(void)
{
    gTestID = 13;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Define variables
    int result;
    int index = 0;
    intptr_t handle = -1;
    unsigned int supported_formats_1;
    unsigned int supported_formats_2;

    // Step 01: Initialize video devices
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Obtain video device handle
    result = dsGetVideoDevice(index, &handle);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
    DS_ASSERT_AUTO_TERM_NUMERICAL((handle >= 0), true);

    // Step 03: Get supported video formats using dsGetSupportedVideoCodingFormats() with the obtained handle
    result = dsGetSupportedVideoCodingFormats(handle, &supported_formats_1);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

    // Step 04: Get supported video formats using dsGetSupportedVideoCodingFormats() with the obtained handle
    result = dsGetSupportedVideoCodingFormats(handle, &supported_formats_2);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

    // Step 05: Compare the results to make sure they match
    DS_ASSERT_AUTO_TERM_NUMERICAL(supported_formats_1, supported_formats_2);

    // Step 06: De-initialize the video devices
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);
    UT_LOG("\n Out %s\n", __FUNCTION__); 
}


/**
 * @brief Test guidance to ensure dsGetSupportedVideoCodingFormats() returns correct error codes for negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 014@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetSupportedVideoCodingFormats() without prior initialization of video devices |int=handle, unsigned int*| dsERR_NOT_INITIALIZED | Should report module not initialized |
 * |02|Initialize video devices using dsVideoDeviceInit() | | dsERR_NONE | Video devices should be initialized successfully |
 * |03|Obtain video device handle using dsGetVideoDevice() | int=index, int=*handle | dsERR_NONE and (handle >= 0) | Should obtain a valid handle successfully |
 * |04|Call dsGetSupportedVideoCodingFormats() with an invalid handle |int=-1, unsigned int*| dsERR_INVALID_PARAM | Should report invalid parameter |
 * |05|Call dsGetSupportedVideoCodingFormats() with null value |int=handle, NULL| dsERR_INVALID_PARAM | Should report invalid parameter |
 * |06|De-initialize the video devices using dsVideoDeviceTerm() | | dsERR_NONE | Video devices should be de-initialized successfully|
 * |07|Call dsGetSupportedVideoCodingFormats() after termination of video devices |int=handle, unsigned int*| dsERR_NOT_INITIALIZED | Should report module not initialized |
 * 
 * @note The return value dsERR_GENERAL and dsERR_OPERATION_NOT_SUPPORTED may be difficult to test in a simulated environment
 * 
 */
void test_l1_dsVideoDevice_negative_dsGetSupportedVideoCodingFormats(void)
{
    gTestID = 14;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Define variables
    int result;
    int index = 0;
    intptr_t handle = -1;
    unsigned int supported_formats;

    // Step 01: Call dsGetSupportedVideoCodingFormats() without prior initialization
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsGetSupportedVideoCodingFormats(handle, &supported_formats); // Note: using handle for supported formats for this error case
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);
    #endif

    // Step 02: Initialize video devices
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Obtain video device handle
    result = dsGetVideoDevice(index, &handle);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
    DS_ASSERT_AUTO_TERM_NUMERICAL((handle >= 0), true);

    // Step 04: Call dsGetSupportedVideoCodingFormats() with an invalid handle
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsGetSupportedVideoCodingFormats(-1, &supported_formats);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
    #endif

    // Step 05: Call dsGetSupportedVideoCodingFormats() with a null value
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsGetSupportedVideoCodingFormats(handle, NULL);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
    #endif

    // Step 06: De-initialize the video devices
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 07: Call dsGetSupportedVideoCodingFormats() after termination
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsGetSupportedVideoCodingFormats(handle, &supported_formats);
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);
    #endif
    UT_LOG("\n Out %s\n", __FUNCTION__); 
}


/**
 * @brief Test guidance to ensure dsGetVideoCodecInfo() correctly fetches the video codec information in positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 015@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize video devices using dsVideoDeviceInit() | | dsERR_NONE | Video devices should be initialized successfully |
 * |02|Obtain video device handle using dsGetVideoDevice() | int=index, int=*handle | dsERR_NONE and (handle >= 0) | Should obtain a valid handle successfully |
 * |03|Get video codec information using dsGetVideoCodecInfo() with the obtained handle | int=handle, dsVIDEO_CODEC_MPEGHPART2, dsVideoCodecInfo_t*| dsERR_NONE | Should successfully fetch the supported video formats |
 * |04|Get video codec information using dsGetVideoCodecInfo() with the obtained handle | int=handle, dsVIDEO_CODEC_MPEG4PART10, dsVideoCodecInfo_t*| dsERR_NONE | Should successfully fetch the supported video formats |
 * |05|Get video codec information using dsGetVideoCodecInfo() with the obtained handle | int=handle, dsVIDEO_CODEC_MPEG2, dsVideoCodecInfo_t*| dsERR_NONE | Should successfully fetch the supported video formats |
 * |06|Get video codec information using dsGetVideoCodecInfo() with the obtained handle | int=handle, dsVIDEO_CODEC_MPEG2, dsVideoCodecInfo_t*| dsERR_NONE | Should successfully fetch the supported video formats |
 * |07|De-initialize the video devices using dsVideoDeviceTerm() | | dsERR_NONE | Video devices should be de-initialized successfully|
 * 
 */
void test_l1_dsVideoDevice_positive_dsGetVideoCodecInfo(void)
{
    gTestID = 15;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Define variables
    int result;
    int index = 0;
    intptr_t handle = -1;
    dsVideoCodecInfo_t codecInfo;

    // Step 01: Initialize video devices
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Obtain video device handle
    result = dsGetVideoDevice(index, &handle);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
    DS_ASSERT_AUTO_TERM_NUMERICAL((handle >= 0), true);

    // Step 03: Get video codec information with dsVIDEO_CODEC_MPEGHPART2
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsGetVideoCodecInfo(handle, dsVIDEO_CODEC_MPEGHPART2, &codecInfo);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
    #endif

    // Step 04: Get video codec information with dsVIDEO_CODEC_MPEG4PART10
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsGetVideoCodecInfo(handle, dsVIDEO_CODEC_MPEG4PART10, &codecInfo);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
    #endif

    // Step 05: Get video codec information with dsVIDEO_CODEC_MPEG2
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsGetVideoCodecInfo(handle, dsVIDEO_CODEC_MPEG2, &codecInfo);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
    #endif

    // Step 06: Get video codec information with dsVIDEO_CODEC_MPEG2 (again to replicate the provided test case)
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsGetVideoCodecInfo(handle, dsVIDEO_CODEC_MPEG2, &codecInfo);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
    #endif

    // Step 07: De-initialize the video devices
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}


/**
 * @brief Test guidance to ensure dsGetVideoCodecInfo() returns correct error codes for negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 016@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetVideoCodecInfo() without prior initialization of video devices | int=handle, dsVIDEO_CODEC_MPEGHPART2, dsVideoCodecInfo_t*| dsERR_NOT_INITIALIZED | Should report module not initialized |
 * |02|Initialize video devices using dsVideoDeviceInit() | | dsERR_NONE | Video devices should be initialized successfully |
 * |03|Obtain video device handle using dsGetVideoDevice() | int=index, int=*handle | dsERR_NONE and (handle >= 0) | Should obtain a valid handle successfully |
 * |04|Call dsGetVideoCodecInfo() with an invalid handle | int=-1, dsVIDEO_CODEC_MPEGHPART2, dsVideoCodecInfo_t*| dsERR_INVALID_PARAM | Should report invalid parameter |
 * |05|Call dsGetVideoCodecInfo() with an invalid coding format | int=handle, dsVIDEO_CODEC_MAX, dsVideoCodecInfo_t*| dsERR_INVALID_PARAM | Should report invalid parameter |
 * |06|Call dsGetVideoCodecInfo() with null parameter | int=handle, dsVIDEO_CODEC_MPEGHPART2, NULL| dsERR_INVALID_PARAM | Should report invalid parameter |
 * |07|De-initialize the video devices using dsVideoDeviceTerm() | | dsERR_NONE | Video devices should be de-initialized successfully|
 * |08|Call dsGetVideoCodecInfo() without prior initialization of video devices | int=handle, dsVIDEO_CODEC_MPEGHPART2, dsVideoCodecInfo_t*| dsERR_NOT_INITIALIZED | Should report module not initialized |
 * 
 * @note The return value dsERR_GENERAL and dsERR_OPERATION_NOT_SUPPORTED may be difficult to test in a simulated environment
 * 
 */
void test_l1_dsVideoDevice_negative_dsGetVideoCodecInfo(void)
{
    gTestID = 16;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Define variables
    int result;
    int index = 0;
    intptr_t handle = -1;
    dsVideoCodecInfo_t codecInfo;

    // Step 01: Call dsGetVideoCodecInfo() without prior initialization
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsGetVideoCodecInfo(handle, dsVIDEO_CODEC_MPEGHPART2, &codecInfo);
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);
    #endif

    // Step 02: Initialize video devices
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Obtain video device handle
    result = dsGetVideoDevice(index, &handle);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
    DS_ASSERT_AUTO_TERM_NUMERICAL((handle >= 0), true);

    // Step 04: Call dsGetVideoCodecInfo() with an invalid handle
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsGetVideoCodecInfo(-1, dsVIDEO_CODEC_MPEGHPART2, &codecInfo);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
    #endif

    // Step 05: Call dsGetVideoCodecInfo() with an invalid coding format
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsGetVideoCodecInfo(handle, dsVIDEO_CODEC_MAX, &codecInfo);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
    #endif

    // Step 06: Call dsGetVideoCodecInfo() with a null parameter
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsGetVideoCodecInfo(handle, dsVIDEO_CODEC_MPEGHPART2, NULL);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);
    #endif

    // Step 07: De-initialize the video devices
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 08: Call dsGetVideoCodecInfo() after termination
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsGetVideoCodecInfo(handle, dsVIDEO_CODEC_MPEGHPART2, &codecInfo);
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);
    #endif

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}


/**
 * @brief Test guidance to ensure dsForceDisableHDRSupport() correctly force disables the HDR support in positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 017@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize video devices using dsVideoDeviceInit() | | dsERR_NONE | Video devices should be initialized successfully |
 * |02|Obtain video device handle using dsGetVideoDevice() | int=index, int=*handle | dsERR_NONE and (handle >= 0) | Should obtain a valid handle successfully |
 * |03|Force disable HDR support using dsForceDisableHDRSupport() with the obtained handle |int=handle, bool=true| dsERR_NONE | HDR support should be force disabled successfully |
 * |04|Force disable HDR support using dsForceDisableHDRSupport() with the obtained handle |int=handle, bool=false| dsERR_NONE | HDR support should be force disabled successfully |
 * |05|De-initialize the video devices using dsVideoDeviceTerm() | | dsERR_NONE | Video devices should be de-initialized successfully|
 * 
 */
void test_l1_dsVideoDevice_positive_dsForceDisableHDRSupport(void)
{
    gTestID = 17;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Define variables
    int result;
    int index = 0;
    intptr_t handle = -1;

    // Step 01: Initialize video devices
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Obtain video device handle
    result = dsGetVideoDevice(index, &handle);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
    DS_ASSERT_AUTO_TERM_NUMERICAL((handle >= 0), true);

    // Step 03: Force disable HDR support (set to true)
    result = dsForceDisableHDRSupport(handle, true);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

    // Step 04: Force disable HDR support (set to false)
    result = dsForceDisableHDRSupport(handle, false);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

    // Step 05: De-initialize the video devices
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}


/**
 * @brief Test guidance to ensure dsForceDisableHDRSupport() returns correct error codes for negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 018@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsForceDisableHDRSupport() without prior initialization of video devices |int=handle, bool=true| dsERR_NOT_INITIALIZED | Should report module not initialized |
 * |02|Initialize video devices using dsVideoDeviceInit() | | dsERR_NONE | Video devices should be initialized successfully |
 * |03|Obtain video device handle using dsGetVideoDevice() | int=index, int=*handle | dsERR_NONE and (handle >= 0) | Should obtain a valid handle successfully |
 * |04|Call dsForceDisableHDRSupport() with an invalid handle |int=-1, bool=true| dsERR_INVALID_PARAM | Should report invalid parameter |
 * |05|De-initialize the video devices using dsVideoDeviceTerm() | | dsERR_NONE | Video devices should be de-initialized successfully|
 * |06|Call dsForceDisableHDRSupport() after termination of video devices |int=handle, bool=true| dsERR_NOT_INITIALIZED | Should report module not initialized |
 * 
 * @note The return value dsERR_GENERAL and dsERR_OPERATION_NOT_SUPPORTED may be difficult to test in a simulated environment
 * 
 */
void test_l1_dsVideoDevice_negative_dsForceDisableHDRSupport(void)
{
    gTestID = 18;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Define variables
    int result;
    int index = 0;
    intptr_t handle = -1;

    // Step 01: Call dsForceDisableHDRSupport() without prior initialization
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsForceDisableHDRSupport(handle, true); // Note: uninitialized 'handle' used here
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);
    #endif

    // Step 02: Initialize video devices
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Obtain video device handle
    result = dsGetVideoDevice(index, &handle);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
    DS_ASSERT_AUTO_TERM_NUMERICAL((handle >= 0), true);

    // Step 04: Call dsForceDisableHDRSupport() with an invalid handle
    result = dsForceDisableHDRSupport(-1, true);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

    // Step 05: De-initialize the video devices
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 06: Call dsForceDisableHDRSupport() after termination
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsForceDisableHDRSupport(handle, true);
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);
    #endif

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}


/**
 * @brief Test guidance to ensure dsSetFRFMode() correctly sets the FRF mode of the device in positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 019@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize video devices using dsVideoDeviceInit() | | dsERR_NONE | Video devices should be initialized successfully |
 * |02|Obtain video device handle using dsGetVideoDevice() | int=index, int=*handle | dsERR_NONE and (handle >= 0) | Should obtain a valid handle successfully |
 * |03|Set the FRF mode using dsSetFRFMode() with the obtained handle and a valid framerate value | int=handle, int| dsERR_NONE | FRF mode should be set successfully |
 * |04|De-initialize the video devices using dsVideoDeviceTerm() | | dsERR_NONE | Video devices should be de-initialized successfully|
 * 
 */
void test_l1_dsVideoDevice_positive_dsSetFRFMode(void)
{
    gTestID = 19;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Define variables
    int result;
    int index = 0;
    intptr_t handle = -1;
    int validFramerate = 60; // This is just a placeholder value; replace with an appropriate value as per your environment.

    // Step 01: Initialize video devices
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Obtain video device handle
    result = dsGetVideoDevice(index, &handle);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
    DS_ASSERT_AUTO_TERM_NUMERICAL((handle >= 0), true);

    // Step 03: Set the FRF mode using a valid framerate
    result = dsSetFRFMode(handle, validFramerate);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

    // Step 04: De-initialize the video devices
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}


/**
 * @brief Test guidance to ensure dsSetFRFMode() returns correct error codes for negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 020@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsSetFRFMode() without prior initialization of video devices | int=handle, int| dsERR_NOT_INITIALIZED | Should report module not initialized |
 * |02|Initialize video devices using dsVideoDeviceInit() | | dsERR_NONE | Video devices should be initialized successfully |
 * |03|Obtain video device handle using dsGetVideoDevice() | int=index, int=*handle | dsERR_NONE and (handle >= 0) | Should obtain a valid handle successfully |
 * |04|Call dsSetFRFMode() with an invalid handle | int=-1, int| dsERR_INVALID_PARAM | Should report invalid parameter |
 * |05|Call dsSetFRFMode() with an invalid framerate | int=handle, int=-1| dsERR_INVALID_PARAM | Should report invalid parameter |
 * |06|De-initialize the video devices using dsVideoDeviceTerm() | | dsERR_NONE | Video devices should be de-initialized successfully|
 * |07|Call dsSetFRFMode() after termination of video devices | int=handle, int| dsERR_NOT_INITIALIZED | Should report module not initialized |
 * 
 * @note The return value dsERR_GENERAL and dsERR_OPERATION_NOT_SUPPORTED may be difficult to test in a simulated environment
 * 
 */
void test_l1_dsVideoDevice_negative_dsSetFRFMode(void)
{
    gTestID = 20;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Define variables
    int result;
    int index = 0;
    intptr_t handle = -1;

    // Step 01: Call dsSetFRFMode() without prior initialization
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsSetFRFMode(handle, 60); // Note: uninitialized 'handle' used here
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);
    #endif

    // Step 02: Initialize video devices
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Obtain video device handle
    result = dsGetVideoDevice(index, &handle);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
    DS_ASSERT_AUTO_TERM_NUMERICAL((handle >= 0), true);

    // Step 04: Call dsSetFRFMode() with an invalid handle
    result = dsSetFRFMode(-1, 60);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

    // Step 05: Call dsSetFRFMode() with an invalid framerate
    result = dsSetFRFMode(handle, -1);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

    // Step 06: De-initialize the video devices
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 07: Call dsSetFRFMode() after termination
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsSetFRFMode(handle, 60);
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);
    #endif

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}


/**
 * @brief Test guidance to ensure dsGetFRFMode() correctly fetches the FRF mode of the device in positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 021@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize video devices using dsVideoDeviceInit() | | dsERR_NONE | Video devices should be initialized successfully |
 * |02|Obtain video device handle using dsGetVideoDevice() | int=index, int=*handle | dsERR_NONE and (handle >= 0) | Should obtain a valid handle successfully |
 * |03|Get the FRF mode using dsGetFRFMode() with the obtained handle |int=handle,int*| dsERR_NONE | Should fetch the FRF mode successfully |
 * |04|Get the FRF mode using dsGetFRFMode() again |int=handle,int*| dsERR_NONE | Should fetch the FRF mode successfully |
 * |05|Compare the returned values to make sure they are the same || Success | The values should be the same value |
 * |06|De-initialize the video devices using dsVideoDeviceTerm() | | dsERR_NONE | Video devices should be de-initialized successfully|
 * 
 */
void test_l1_dsVideoDevice_positive_dsGetFRFMode(void)
{
    gTestID = 21;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Define variables
    int result;
    int index = 0;
    intptr_t handle = -1;
    int fetchedFRFMode1;
    int fetchedFRFMode2;

    // Step 01: Initialize video devices
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Obtain video device handle
    result = dsGetVideoDevice(index, &handle);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
    UT_ASSERT_TRUE(handle >= 0);

    // Step 03: Get the FRF mode using the obtained handle
    result = dsGetFRFMode(handle, &fetchedFRFMode1);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

    // Step 04: Get the FRF mode using the obtained handle again
    result = dsGetFRFMode(handle, &fetchedFRFMode2);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

    // Step 05: Compare the returned values
    DS_ASSERT_AUTO_TERM_NUMERICAL(fetchedFRFMode1, fetchedFRFMode2);

    // Step 06: De-initialize the video devices
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}


/**
 * @brief Test guidance to ensure dsGetFRFMode() returns correct error codes for negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 022@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetFRFMode() without prior initialization of video devices |int=handle,int*| dsERR_NOT_INITIALIZED | Should report module not initialized |
 * |02|Initialize video devices using dsVideoDeviceInit() | | dsERR_NONE | Video devices should be initialized successfully |
 * |03|Obtain video device handle using dsGetVideoDevice() | int=index, int=*handle | dsERR_NONE and (handle >= 0) | Should obtain a valid handle successfully |
 * |04|Call dsGetFRFMode() with an invalid handle |int=-1,int*| dsERR_INVALID_PARAM | Should report invalid parameter |
 * |05|Call dsGetFRFMode() with null value |int=handle,NULL| dsERR_INVALID_PARAM | Should report invalid parameter |
 * |06|De-initialize the video devices using dsVideoDeviceTerm() | | dsERR_NONE | Video devices should be de-initialized successfully|
 * |07|Call dsGetFRFMode() after termination of video devices |int=handle,int*| dsERR_NOT_INITIALIZED | Should report module not initialized |
 * 
 * @note The return value dsERR_GENERAL and dsERR_OPERATION_NOT_SUPPORTED may be difficult to test in a simulated environment
 * 
 */
void test_l1_dsVideoDevice_negative_dsGetFRFMode(void)
{
    gTestID = 22;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Define variables
    int result;
    int index = 0;
    intptr_t handle = -1;
    int fetchedFRFMode;

    // Step 01: Call dsGetFRFMode() without prior initialization
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsGetFRFMode(handle, &fetchedFRFMode); // Note: uninitialized 'handle' used here
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);
    #endif

    // Step 02: Initialize video devices
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Obtain video device handle
    result = dsGetVideoDevice(index, &handle);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
    UT_ASSERT_TRUE(handle >= 0);

    // Step 04: Call dsGetFRFMode() with an invalid handle
    result = dsGetFRFMode(-1, &fetchedFRFMode);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

    // Step 05: Call dsGetFRFMode() with null value
    result = dsGetFRFMode(handle, NULL);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

    // Step 06: De-initialize the video devices
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 07: Call dsGetFRFMode() after termination
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsGetFRFMode(handle, &fetchedFRFMode);
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);
    #endif

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}


/**
 * @brief Test guidance to ensure dsGetCurrentDisplayframerate() correctly fetches the current framerate of the device in positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 023@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize video devices using dsVideoDeviceInit() | | dsERR_NONE | Video devices should be initialized successfully |
 * |02|Obtain video device handle using dsGetVideoDevice() | int=index, int=*handle | dsERR_NONE and (handle >= 0) | Should obtain a valid handle successfully |
 * |03|Get the current display framerate using dsGetCurrentDisplayframerate() with the obtained handle |int=handle,char*| dsERR_NONE | Should fetch the current framerate successfully |
 * |04|Get the current display framerate using dsGetCurrentDisplayframerate() again |int=handle,char*| dsERR_NONE | Should fetch the current framerate successfully |
 * |05|Compare the results to make sure they are the same || Success | The results should equal one another |
 * |06|De-initialize the video devices using dsVideoDeviceTerm() | | dsERR_NONE | Video devices should be de-initialized successfully|
 * 
 */
void test_l1_dsVideoDevice_positive_dsGetCurrentDisplayframerate(void)
{
    gTestID = 23;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Define variables
    int result;
    int index = 0;
    intptr_t handle = -1;
    char fetchedFramerate1[50]; // Assuming a buffer size, modify as necessary.
    char fetchedFramerate2[50]; // Assuming a buffer size, modify as necessary.

    // Step 01: Initialize video devices
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Obtain video device handle
    result = dsGetVideoDevice(index, &handle);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
    UT_ASSERT_TRUE(handle >= 0);

    // Step 03: Get the current display framerate using the obtained handle
    result = dsGetCurrentDisplayframerate(handle, fetchedFramerate1);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

    // Step 04: Get the current display framerate again
    result = dsGetCurrentDisplayframerate(handle, fetchedFramerate2);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

    // Step 05: Compare the returned values
    DS_ASSERT_AUTO_TERM_NUMERICAL(strcmp(fetchedFramerate1, fetchedFramerate2), 0); // They should be the same

    // Step 06: De-initialize the video devices
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}


/**
 * @brief Test guidance to ensure dsGetCurrentDisplayframerate() returns correct error codes for negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 024@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsGetCurrentDisplayframerate() without prior initialization of video devices|int=handle,char*| dsERR_NOT_INITIALIZED | Should report module not initialized |
 * |02|Initialize video devices using dsVideoDeviceInit() | | dsERR_NONE | Video devices should be initialized successfully |
 * |03|Obtain video device handle using dsGetVideoDevice() | int=index, int=*handle | dsERR_NONE and (handle >= 0) | Should obtain a valid handle successfully |
 * |04|Call dsGetCurrentDisplayframerate() with an invalid handle |int=-1,char* |dsERR_INVALID_PARAM | Should report invalid parameter |
 * |05|Call dsGetCurrentDisplayframerate() with NULL value |int=handle, NULL |dsERR_INVALID_PARAM | Should report invalid parameter |
 * |06|De-initialize the video devices using dsVideoDeviceTerm() | | dsERR_NONE | Video devices should be de-initialized successfully|
 * |07|Call dsGetCurrentDisplayframerate() after termination of video devices|int=handle,char*| dsERR_NOT_INITIALIZED | Should report module not initialized |
 * 
 * @note The return value dsERR_GENERAL and dsERR_OPERATION_NOT_SUPPORTED may be difficult to test in a simulated environment
 * 
 */
void test_l1_dsVideoDevice_negative_dsGetCurrentDisplayframerate(void)
{
    gTestID = 24;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Define variables
    int result;
    int index = 0;
    intptr_t handle = -1;
    char fetchedFramerate[50]; // Assuming a buffer size, modify as necessary.

    // Step 01: Call dsGetCurrentDisplayframerate() without prior initialization
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsGetCurrentDisplayframerate(handle, fetchedFramerate); // Note: uninitialized 'handle' used here
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);
    #endif

    // Step 02: Initialize video devices
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Obtain video device handle
    result = dsGetVideoDevice(index, &handle);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
    UT_ASSERT_TRUE(handle >= 0);

    // Step 04: Call dsGetCurrentDisplayframerate() with an invalid handle
    result = dsGetCurrentDisplayframerate(-1, fetchedFramerate);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

    // Step 05: Call dsGetCurrentDisplayframerate() with NULL value
    result = dsGetCurrentDisplayframerate(handle, NULL);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

    // Step 06: De-initialize the video devices
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 07: Call dsGetCurrentDisplayframerate() after termination
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsGetCurrentDisplayframerate(handle, fetchedFramerate);
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);
    #endif

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}


/**
 * @brief Test guidance to ensure dsSetDisplayframerate() correctly sets the display framerate for the device in positive scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 025@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Initialize video devices using dsVideoDeviceInit() | | dsERR_NONE | Video devices should be initialized successfully |
 * |02|Obtain video device handle using dsGetVideoDevice() | int=index, int=*handle | dsERR_NONE and (handle >= 0) | Should obtain a valid handle successfully |
 * |03|Set the display framerate using dsSetDisplayframerate() with the obtained handle and a valid framerate |int=handle,char*| dsERR_NONE | Display framerate should be set successfully |
 * |04|De-initialize the video devices using dsVideoDeviceTerm() | | dsERR_NONE | Video devices should be de-initialized successfully|
 * 
 */
void test_l1_dsVideoDevice_positive_dsSetDisplayframerate(void)
{
    gTestID = 25;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Define variables
    int result;
    int index = 0;
    intptr_t handle = -1;
    char desiredFramerate[] = "30fps"; // You can modify this value as necessary

    // Step 01: Initialize video devices
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 02: Obtain video device handle
    result = dsGetVideoDevice(index, &handle);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
    UT_ASSERT_TRUE(handle >= 0);

    // Step 03: Set the display framerate using the obtained handle
    result = dsSetDisplayframerate(handle, desiredFramerate);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);

    // Step 04: De-initialize the video devices
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}


/**
 * @brief Test guidance to ensure dsSetDisplayframerate() returns correct error codes for negative scenarios.
 * 
 * **Test Group ID:** Basic: 01@n
 * **Test Case ID:** 026@n
 * 
 * **Dependencies:** None@n
 * **User Interaction:** None
 * 
 * **Test Procedure:**@n
 * |Variation / Step|Description|Expected Result|Notes|
 * |:--:|-----------|----------|--------------|-----|
 * |01|Call dsSetDisplayframerate() without prior initialization of video devices |int=handle,char*| dsERR_NOT_INITIALIZED | Should report module not initialized |
 * |02|Initialize video devices using dsVideoDeviceInit() | | dsERR_NONE | Video devices should be initialized successfully |
 * |03|Obtain video device handle using dsGetVideoDevice() | int=index, int=*handle | dsERR_NONE and (handle >= 0) | Should obtain a valid handle successfully |
 * |04|Call dsSetDisplayframerate() with an invalid handle |int=-1,char*| dsERR_INVALID_PARAM | Should report invalid parameter |
 * |05|Call dsSetDisplayframerate() with NULL char*|int=handle,NULL| dsERR_INVALID_PARAM | Should report invalid parameter |
 * |06|Call dsSetDisplayframerate() with invalid char* |int=-1,char*="junk"| dsERR_INVALID_PARAM | Should report invalid parameter |
 * |07|De-initialize the video devices using dsVideoDeviceTerm() | | dsERR_NONE | Video devices should be de-initialized successfully|
 * |08|Call dsSetDisplayframerate() after termination of video devices |int=handle,char*| dsERR_NOT_INITIALIZED | Should report module not initialized |
 * 
 * @note The return value dsERR_GENERAL and dsERR_OPERATION_NOT_SUPPORTED may be difficult to test in a simulated environment
 * 
 */
void test_l1_dsVideoDevice_negative_dsSetDisplayframerate(void)
{
    gTestID = 26;
    UT_LOG("\n In %s [%02d%03d]\n", __FUNCTION__, gTestGroup, gTestID);
    // Define variables
    int result;
    int index = 0;
    intptr_t handle = -1;

    // Step 01: Call dsSetDisplayframerate() without prior initialization
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsSetDisplayframerate(handle, "30fps"); // Note: uninitialized 'handle' used here
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);
    #endif

    // Step 02: Initialize video devices
    result = dsVideoDeviceInit();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 03: Obtain video device handle
    result = dsGetVideoDevice(index, &handle);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_NONE);
    UT_ASSERT_TRUE(handle >= 0);

    // Step 04: Call dsSetDisplayframerate() with an invalid handle
    result = dsSetDisplayframerate(-1, "30fps");
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

    // Step 05: Call dsSetDisplayframerate() with NULL char*
    result = dsSetDisplayframerate(handle, NULL);
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

    // Step 06: Call dsSetDisplayframerate() with invalid char*
    result = dsSetDisplayframerate(handle, "junk");
    DS_ASSERT_AUTO_TERM_NUMERICAL(result, dsERR_INVALID_PARAM);

    // Step 07: De-initialize the video devices
    result = dsVideoDeviceTerm();
    UT_ASSERT_EQUAL(result, dsERR_NONE);

    // Step 08: Call dsSetDisplayframerate() after termination
    #ifdef ENABLE_ENHANCED_ERROR_CODE
    result = dsSetDisplayframerate(handle, "30fps");
    UT_ASSERT_EQUAL(result, dsERR_NOT_INITIALIZED);
    #endif

    UT_LOG("\n Out %s\n", __FUNCTION__); 
}

static UT_test_suite_t * pSuite1 = NULL;
static UT_test_suite_t * pSuite2 = NULL;

/**
 * @brief Register the main test(s) for this module
 *
 * @return int - 0 on success, otherwise failure
 */
int test_l1_dsVideoDevice_register ( void )
{
	/* add a suite to the registry */
	pSuite1 = UT_add_suite( "[L1 dsVideoDevice]", NULL, NULL );
    pSuite2 = UT_add_suite( "[L1 dsVideoDevice - advanced]", NULL, NULL );
	if ( NULL == pSuite1 )
	{
		return -1;
	}
    if ( NULL == pSuite2 )
	{
		return -1;
	}	

    UT_add_test( pSuite1, "dsVideoDeviceInit_L1_positive" ,test_l1_dsVideoDevice_positive_dsVideoDeviceInit );
    UT_add_test( pSuite1, "dsVideoDeviceTerm_L1_positive" ,test_l1_dsVideoDevice_positive_dsVideoDeviceTerm );
    UT_add_test( pSuite1, "dsGetVideoDevice_L1_positive" ,test_l1_dsVideoDevice_positive_dsGetVideoDevice );
    UT_add_test( pSuite1, "dsSetDFC_L1_positive" ,test_l1_dsVideoDevice_positive_dsSetDFC );
    UT_add_test( pSuite1, "dsGetHDRCapabilities_L1_positive" ,test_l1_dsVideoDevice_positive_dsGetHDRCapabilities );
    UT_add_test( pSuite1, "dsGetSupportedVideoCodingFormats_L1_positive" ,test_l1_dsVideoDevice_positive_dsGetSupportedVideoCodingFormats );
    UT_add_test( pSuite1, "dsGetVideoCodecInfo_L1_positive" ,test_l1_dsVideoDevice_positive_dsGetVideoCodecInfo );
    UT_add_test( pSuite1, "dsSetFRFMode_L1_positive" ,test_l1_dsVideoDevice_positive_dsSetFRFMode );
    UT_add_test( pSuite1, "dsGetFRFMode_L1_positive" ,test_l1_dsVideoDevice_positive_dsGetFRFMode );
    UT_add_test( pSuite1, "dsGetCurrentDisplayframerate_L1_positive" ,test_l1_dsVideoDevice_positive_dsGetCurrentDisplayframerate );
    UT_add_test( pSuite1, "dsSetDisplayframerate_L1_positive" ,test_l1_dsVideoDevice_positive_dsSetDisplayframerate );


	UT_add_test( pSuite1, "dsVideoDeviceInit_L1_negative" ,test_l1_dsVideoDevice_negative_dsVideoDeviceInit );
	UT_add_test( pSuite1, "dsVideoDeviceTerm_L1_negative" ,test_l1_dsVideoDevice_negative_dsVideoDeviceTerm );
	UT_add_test( pSuite1, "dsGetVideoDevice_L1_negative" ,test_l1_dsVideoDevice_negative_dsGetVideoDevice );
	UT_add_test( pSuite1, "dsSetDFC_L1_negative" ,test_l1_dsVideoDevice_negative_dsSetDFC );
	UT_add_test( pSuite1, "dsGetHDRCapabilities_L1_negative" ,test_l1_dsVideoDevice_negative_dsGetHDRCapabilities );
	UT_add_test( pSuite1, "dsGetSupportedVideoCodingFormats_L1_negative" ,test_l1_dsVideoDevice_negative_dsGetSupportedVideoCodingFormats );
	UT_add_test( pSuite1, "dsGetVideoCodecInfo_L1_negative" ,test_l1_dsVideoDevice_negative_dsGetVideoCodecInfo );
	UT_add_test( pSuite1, "dsSetFRFMode_L1_negative" ,test_l1_dsVideoDevice_negative_dsSetFRFMode );
	UT_add_test( pSuite1, "dsGetFRFMode_L1_negative" ,test_l1_dsVideoDevice_negative_dsGetFRFMode );
	UT_add_test( pSuite1, "dsGetCurrentDisplayframerate_L1_negative" ,test_l1_dsVideoDevice_negative_dsGetCurrentDisplayframerate );
	UT_add_test( pSuite1, "dsSetDisplayframerate_L1_negative" ,test_l1_dsVideoDevice_negative_dsSetDisplayframerate );


    UT_add_test( pSuite2, "dsGetDFC_L1_positive" ,test_l1_dsVideoDevice_positive_dsGetDFC );
    UT_add_test( pSuite2, "dsForceDisableHDRSupport_L1_positive" ,test_l1_dsVideoDevice_positive_dsForceDisableHDRSupport );
    UT_add_test( pSuite2, "dsGetDFC_L1_negative" ,test_l1_dsVideoDevice_negative_dsGetDFC );
    UT_add_test( pSuite2, "dsForceDisableHDRSupport_L1_negative" ,test_l1_dsVideoDevice_negative_dsForceDisableHDRSupport );
	

	return 0;
} 


/** @} */ // End of DS_VideoDevice_HALTEST_L1
/** @} */ // End of DS_VideoDevice_HALTEST
/** @} */ // End of Device_Settings_HALTEST
/** @} */ // End of Device_Settings
/** @} */ // End of HPK
