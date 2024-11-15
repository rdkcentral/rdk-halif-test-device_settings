#!/usr/bin/env python3
#** *****************************************************************************
# *
# * If not stated otherwise in this file or this component's LICENSE file the
# * following copyright and licenses apply:
# *
# * Copyright 2024 RDK Management
# *
# * Licensed under the Apache License, Version 2.0 (the "License");
# * you may not use this file except in compliance with the License.
# * You may obtain a copy of the License at
# *
# *
# http://www.apache.org/licenses/LICENSE-2.0
# *
# * Unless required by applicable law or agreed to in writing, software
# * distributed under the License is distributed on an "AS IS" BASIS,
# * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# * See the License for the specific language governing permissions and
# * limitations under the License.
# *
#* ******************************************************************************

import os
import sys
import time

dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(dir_path+"/../../")

from dsClasses.dsHost import dsHostClass
from raft.framework.plugins.ut_raft import utHelperClass
from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.plugins.ut_raft.utUserResponse import utUserResponse

class dsHost_test1_VerifyTemperature(utHelperClass):


    def __init__(self):
        """
        Initializes the test1_VerifyTemperature test .

        Args:
            None.
        """

        self.testName  = "test1_VerifyTemperature"
        self.testSetupPath = dir_path + "/dsHost_L3_testSetup.yml"
        self.moduleName = "dsHost"
        self.rackDevice = "dut"

        
        super().__init__(self.testName, '1')

        # Test Setup configuration file
        self.testSetup = ConfigRead(self.testSetupPath, self.moduleName)

        # Open Session for hal test
        self.hal_session = self.dut.getConsoleSession("ssh_hal_test")

        # Create user response Class
        self.testUserResponse = utUserResponse()

        # Get path to device profile file
        self.deviceProfile = dir_path + "/" + self.cpe.get("test").get("profile")

    def testFunction(self):
        """This function will test the get cpu tempature functionality

        Returns:
            bool
        """
        # Create the dsHost class
        self.testdsHost = dsHostClass(self.deviceProfile, self.hal_session)

        self.log.stepStart(f'dsHost_test1_VerifyTemperature')

        # Initialize the dsHost module
        self.testdsHost.initialise()

        # Ask the user to put the DUT in a heating chamber
        self.testUserResponse.getUserYN(f"Put the DUT in a heating chamber and press Enter:")

        # Get the CPU temperature
        temp1 = self.testdsHost.getCPUTemperature()
        self.log.step(f'Temperature 1: {temp1}')

        # Ask the user to increase the temperature
        self.testUserResponse.getUserYN(f"Please begin to increase the temperature, and wait around one to two minutes before pressing enter to continue:")


        # Get the CPU temperature again
        temp2 = self.testdsHost.getCPUTemperature()
        self.log.step(f'Temperature 2: {temp2}')

        # Check to make sure the temperature has increased
        self.log.step(f'Check that the temperature has increased')

        # Log the result
        self.log.step(f'Temperature {temp2} & {temp1} difference:: {abs(temp2 - temp1)}')
        tolerance = 1e-9 
        abs(temp2 - temp1) > tolerance
        if temp2 <= temp1:
            self.log.stepResult(False,f'Temperature is not within expected range')
            result = False
        else:
            self.log.stepResult(True,f'Temperature is within expected range')
            result = True

        # Delete the dsHost class
        self.testdsHost.terminate()

        del self.testdsHost

        return result

if __name__ == '__main__':
    test = dsHost_test1_VerifyTemperature()
    test.run(False)
