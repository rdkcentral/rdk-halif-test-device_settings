/*
* If not stated otherwise in this file or this component's LICENSE file the
* following copyright and licenses apply:*
* Copyright 2024 RDK Management
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

extern int MAX_DEVICES;
extern int get_MaxDevices(void);
extern int register_hal_l2_tests( void );

int main(int argc, char** argv)
{
    int registerReturn = 0;

    /* Register tests as required, then call the UT-main to support switches and triggering */
    UT_init( argc, argv );

    //TODO : This check is to be removed when all the profile files are combined into single profile file.
    if ( (!(strcmp(argv[2],"Source_VideoDevice.yaml")))|| (!(strcmp(argv[2],"Sink_VideoDevice.yaml"))))
    {
        if (get_MaxDevices() == 0)
        {
            UT_LOG("Got the Supported Number of VideoDevices value : %d\n ", MAX_DEVICES);
        }
        else
        {
            printf("Failed to get Supported Number of VideoDevices\n");
        }
    }
    /* Check if tests are registered successfully */
    registerReturn = register_hal_l2_tests();
    if (registerReturn == 0)
    {
        printf("register_hal_l2_tests() returned success");
    }
    else
    {
        printf("register_hal_l2_tests() returned failure");
        return 1;
    }
    /* Begin test executions */
    UT_run_tests();
    return 0;
}
