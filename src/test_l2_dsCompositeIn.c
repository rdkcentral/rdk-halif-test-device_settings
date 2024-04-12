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
 * @addtogroup DS_CompositeIn_HALTEST Device Settings Composite Input HAL Tests
 * @{
 */

/**
 * @defgroup DS_CompositeIn_HALTEST_L2 Device Settings Composite Input HAL Tests L2 File
 * @{
 * @parblock
 *
 * ### L2 Tests for DS Composite Input HAL :
 *
 * Level 2 unit test cases for all APIs of Device Settings Composite Input HAL
 *
 * **Pre-Conditions:**  None@n
 * **Dependencies:** None@n
 *
 * TODO: Refer to L2 Specification documentation : [l2_module_test_specification_template.md](../docs/pages/l2_module_test_specification_template.md)
 *
 * @endparblock
 */

/**
 * @file test_l2_dsCompositeIn.c
 *
 */

#include <string.h>
#include <stdlib.h>

#include <ut.h>
#include <ut_log.h>

/**
* @brief TODO: Describe the object of the test
*
* TODO: Add the description of what is tested and why in this test
*
* **Test Group ID:** TODO: Add the group this test belongs to - Basic (for L1): 01 / Module (L2): 02 / Stress (L2): 03)@n
* **Test Case ID:** TODO: Add the ID of the test case so that it can be logically tracked in the logs@n
*
* **Test Procedure:**
* TODO: Refer to L2 Specification documentation : [l2_module_test_specification_template.md](../docs/pages/l2_module_test_specification_template.md)
*/
void test_l2_dsCompositeIn (void)
{
	UT_FAIL("This function needs to be implemented!");
}

static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main test(s) for this module
 *
 * @return int - 0 on success, otherwise failure
 */
int test_l2_dsCompositeIn_register ( void )
{
	/* add a suite to the registry */
	pSuite = UT_add_suite( "[L2 dsCompositeIn]", NULL, NULL );
	if ( NULL == pSuite )
	{
		return -1;
	}	

	
	UT_add_test( pSuite, "test_l2_dsCompositeIn" ,test_l2_dsCompositeIn );

	return 0;
} 

/** @} */ // End of DS_CompositeIn_HALTEST_L2
/** @} */ // End of DS_CompositeIn_HALTEST
/** @} */ // End of Device_Settings_HALTEST
/** @} */ // End of Device_Settings
/** @} */ // End of HPK
