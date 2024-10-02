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
 * @defgroup Device_Settings_REGISTER Device Settings HAL Tests Register File
 * @{
 * @parblock
 *
 * ### Registration of tests for Device Settings HAL :
 *
 * This is to ensure that the APIs meets the operational requirements of the module across all vendors.
 *
 * **Pre-Conditions:**  None @n
 * **Dependencies:** None @n
 *
 * Refer to Device Settings HAL Documentation Guide : [README.md](../../docs/pages/README.md)
 *
 * @endparblock
 *
 */

/**
 * @file test_register.c
 *
 */

#include <stdint.h>
#include <ut.h>
#include "test_parse_configuration.h"

/**
 * @brief Register test functionality
 *
 */

/* L1 Testing Functions */
extern int test_l1_dsHost_register(void);
extern int test_l1_dsAudio_register(void);
extern int test_l1_dsVideoDevice_register(void);
extern int test_l1_dsHdmiIn_register(void);
extern int test_l1_dsFPD_register(void);
extern int test_l1_dsVideoPort_register(void);
extern int test_l1_dsCompositeIn_register(void);
extern int test_l1_dsDisplay_register(void);

/* L2 Testing Functions */
extern int test_l2_dsHost_register( void );
extern int test_l2_dsAudio_register( void );
extern int test_l2_dsVideoDevice_register( void );
extern int test_l2_dsHdmiIn_register( void );
extern int test_l2_dsFPD_register( void );
extern int test_l2_dsVideoPort_register( void );

extern int test_l2_dsCompositeIn_register( void );
extern int test_l2_dsDisplay_register( void );

/* L3 Testing Functions */
extern int test_l3_dsAudio_register( void );
extern int test_l3_dsVideoPort_register( void );
extern int test_l3_dsHost_register( void );

int UT_register_tests(void)
{
    int registerFailed = 0;

/*
    FIXME: Upgrade this function to simplify
            each function internally must deal with it's own daemons and configuration
            L1-L3+ is outside of scope for this file, which it's requirement is to register all the tests
    NOTE: Register will NEVER Fail, no requirement to check it, check failure with assert() in each of the regsiter functions.

    dsHost_register();
    dsAudio_register();
    dsVideo_register()
    dsHdmiIn_regsiter()
    dsFPD_register();
    dsVideoPort_register();
    dsCompositeIn_register();
    dsDisplay_register();
*/
    if (gDSModule & dsHost)
    {
        /* TODO: Have a dsHost Register function and call it always */
        registerFailed |= test_l1_dsHost_register();
        registerFailed |= test_l2_dsHost_register();
        registerFailed |= test_l3_dsHost_register();
    }
    if (gDSModule & dsAudioPort)
    {
        registerFailed |= test_l1_dsAudio_register();
        registerFailed |= test_l2_dsAudio_register();
        registerFailed |= test_l3_dsAudio_register();
    }
    if (gDSModule & dsVideoDevice)
    {
        registerFailed |= test_l1_dsVideoDevice_register();
        registerFailed |= test_l2_dsVideoDevice_register();
    }
    if (gDSModule & dsHdmiIn)
    {
        registerFailed |= test_l1_dsHdmiIn_register();
        registerFailed |= test_l2_dsHdmiIn_register();
    }
    if (gDSModule & dsFPD)
    {
        registerFailed |= test_l1_dsFPD_register();
        registerFailed |= test_l2_dsFPD_register();
    }
    if (gDSModule & dsVideoPort)
    {
        registerFailed |= test_l1_dsVideoPort_register();
        registerFailed |= test_l2_dsVideoPort_register();
        registerFailed |= test_l3_dsVideoPort_register();
    }
    if (gDSModule & dsComposite)
    {
        registerFailed |= test_l1_dsCompositeIn_register();
        registerFailed |= test_l2_dsCompositeIn_register();
    }
    if (gDSModule & dsDisplay)
    {
        registerFailed |= test_l1_dsDisplay_register();
        registerFailed |= test_l2_dsDisplay_register();

    return registerFailed;
}

/* Register UT Functions */
int UT_register_APIDEF_l3_tests( void )
{
    int registerFailed=0;

    if(gDSModule & dsAudioPort)
        registerFailed |= test_l3_dsAudio_register();

    if(gDSModule & dsVideoPort)
        registerFailed |= test_l3_dsVideoPort_register();
        
    if(gDSModule & dsHost)
        registerFailed |= test_register_dsHost_hal_l3_tests();
    }

    return registerFailed;
}



/** @} */ // End of Device_Settings_REGISTER
/** @} */ // End of Device_Settings_HALTEST
/** @} */ // End of Device_Settings
/** @} */ // End of HPK
