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

dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(dir_path+"/../")

from dsClasses.dsDisplay import dsDisplayClass
from raft.framework.plugins.ut_raft import utHelperClass
from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.plugins.ut_raft.utUserResponse import utUserResponse

class dsDisplay_test02_GetDisplayEdidBytes(utHelperClass):

    testName  = "test02_GetDisplayEdidBytes"
    testSetupPath = dir_path + "/dsDisplay_L3_testSetup.yml"
    moduleName = "dsDisplay"
    rackDevice = "dut"

    def __init__(self):
        """
        Initializes the test02_GetDisplayEdidBytes test .

        Args:
            None.
        """
        super().__init__(self.testName, '1')

        # Test Setup configuration file
        self.testSetup = ConfigRead(self.testSetupPath, self.moduleName)

        # Open Session for hal test
        self.hal_session = self.dut.getConsoleSession("ssh_hal_test")

        # Create user response Class
        self.testUser Response = utUser Response()

        # Get path to device profile file
        self.deviceProfile = dir_path + "/" + self.cpe.get("test").get("profile")

    def testRunPrerequisites(self):
        """
        Runs Prerequisite commands listed in test-setup configuration file on the dut.

        Args:
            None.
        """

        #Run test specific commands
        cmds = self.testSetup.assets.device.test02_GetDisplayEdidBytes.execute
        if cmds is not None:
            for cmd in cmds:
                self.writeCommands(cmd)

    def testGetEdidBytes(self, manual=False):
        """
        Gets the EDID bytes of the display.
        Args:
            manual (bool, optional): Manual verification (True: manual, False: other verification methods).
                                 Defaults to other verification methods
        Returns:
            bool
        """
        if manual == True:
            # Manual verification
            edid_bytes = self.testdsDisplay.getEdidBytes()
            return self.testUserResponse.getUserYN(f"Are the EDID bytes {edid_bytes} correct? (Y/N):")
        else:
            # Automation verification
            #TODO: Add automation verification methods
            return False

    def testFunction(self):
        """
        This function will test the Display by getting the EDID bytes of the display

        Returns:
            bool
        """

        # Run Prerequisites listed in the test setup configuration file
        self.testRunPrerequisites()

        # Create an instance of the dsDisplayClass
        self.testdsDisplay = dsDisplayClass(self.deviceProfile, self.hal_session)

        # Get the EDID bytes of the display
        result = self.testGetEdidBytes()

        # Delete the dsDisplay class
        del self.testdsDisplay

        return result

if __name__ == '__main__':
    test = dsDisplay_test02_GetDisplayEdidBytes()
    test.run(False)