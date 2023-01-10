/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2016 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

#include <ut.h>

/* L1 Testing Functions */
extern int videodevice_l1_register( void );
extern int audio_l1_register( void );
extern int CompositeIn_l1_register( void );
extern int Display_l1_register( void );
extern int FPD_l1_register( void );
extern int hallogger_l1_register( void );
extern int halregisterlog_l1_register( void );
extern int HdmiIn_l1_register( void );
extern int Host_l1_register( void );
extern int VideoPort_l1_register( void );

/* L2 Testing Functions */
//extern int test_l2_register( void );

int main(int argc, char** argv) 
{
    int registerFailed=0;

    /* Register tests as required, then call the UT-main to support switches and triggering */
    UT_init( argc, argv );

    registerFailed |= videodevice_l1_register();
    registerFailed |= audio_l1_register();
    registerFailed |= CompositeIn_l1_register();
    registerFailed |= Display_l1_register();
    registerFailed |= FPD_l1_register();
    registerFailed |= hallogger_l1_register();
    registerFailed |= halregisterlog_l1_register();
    registerFailed |= HdmiIn_l1_register();
    registerFailed |= Host_l1_register();
    registerFailed |= VideoPort_l1_register();
//    registerFailed |= test_l2_register();

    UT_run_tests();
}
