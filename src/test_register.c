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
 * Describe the details about Device Settings HAL function specifications.
 *  @{
 */

/**
 * @defgroup dsDEVICESETTINGS_REGISTER DS Register
 *  @{
 * @par Application API Specification
 *
 */

#include <ut.h>

/**
 * @brief Register test functionality
 * 
 */

/* L1 Testing Functions */
extern int test_l1_dsAudio_register( void );
extern int test_l1_dsCompositeIn_register( void );
extern int test_l1_dsDisplay_register( void );
extern int test_l1_dsFPD_register( void );
extern int test_l1_dsHdmiIn_register( void );
extern int test_l1_dsHost_register( void );
extern int test_l1_dsVideoDevice_register( void );
extern int test_l1_dsVideoPort_register( void );


/* L2 Testing Functions */
extern int test_l2_dsAudio_register( void );
extern int test_l2_dsCompositeIn_register( void );
extern int test_l2_dsDisplay_register( void );
extern int test_l2_dsFPD_register( void );
extern int test_l2_dsHdmiIn_register( void );
extern int test_l2_dsHost_register( void );
extern int test_l2_dsVideoDevice_register( void );
extern int test_l2_dsVideoPort_register( void );

int UT_register_APIDEF_l1_tests( void )
{
	int registerFailed=0;

	registerFailed |= test_l1_dsAudio_register();
	registerFailed |= test_l1_dsCompositeIn_register();
	registerFailed |= test_l1_dsDisplay_register();
	registerFailed |= test_l1_dsFPD_register();
	registerFailed |= test_l1_dsHdmiIn_register();
	registerFailed |= test_l1_dsHost_register();
	registerFailed |= test_l1_dsVideoDevice_register();
	registerFailed |= test_l1_dsVideoPort_register();

	return registerFailed;
}

/* Register UT Functions */
int UT_register_APIDEF_l2_tests( void )
{
	int registerFailed=0;

	registerFailed |= test_l2_dsAudio_register();
registerFailed |= test_l2_dsCompositeIn_register();
registerFailed |= test_l2_dsDisplay_register();
registerFailed |= test_l2_dsFPD_register();
registerFailed |= test_l2_dsHdmiIn_register();
registerFailed |= test_l2_dsHost_register();
registerFailed |= test_l2_dsVideoDevice_register();
registerFailed |= test_l2_dsVideoPort_register();

	return registerFailed;
}

/** @} */ // End of DS REGISTER
/** @} */ // End of Device Settings HAL
/** @} */ // End of Device Settings Module
/** @} */ // End of HPK