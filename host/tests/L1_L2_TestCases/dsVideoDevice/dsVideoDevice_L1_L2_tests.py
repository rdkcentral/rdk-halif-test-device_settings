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
sys.path.append(os.path.join(dir_path, "../../"))

from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.core.logModule import logModule
from dsClasses.dsVideoDevice import dsVideoDeviceClass
from raft.framework.plugins.ut_raft import utHelperClass

class dsVideoDevice_L1_L2_tests(utHelperClass):
    """
    Test class to run the L1 tests on the device.

    This class uses the `dsVideoDeviceClass` to interact with the device

    """
    def __init__(self, log:logModule=None):
        """
        Initializes the test class
        """
        moduleName = "dsVideoDevice"

        testName = "dsVideoDevice_L1_L2_Tests"
        qcId = "1"
        super().__init__(testName, qcId, log)

        deviceTestSetup = self.cpe.get("test")
        targetWorkspace = self.cpe.get("target_directory")

        # Get path to device profile file
        self.moduleConfigProfileFile = os.path.join(dir_path, deviceTestSetup.get("profile"))
        # Get the target workspace
        self.targetWorkspace = os.path.join(targetWorkspace, moduleName)

        # Load test setup configuration
        testSetupPath = os.path.join(dir_path, "dsVideoDevice_L1_L2_testSetup.yml")
        self.testSetup = ConfigRead(testSetupPath, moduleName)

    def testFunction(self):
        """
        The main test function to run the L1 and L2 tests.

        Returns:
            bool: Final result of the test.
        """
        testsuites = self.testSetup.fields.get('test_suites')

        finalresult = True

        for testsuite in testsuites:
            testsuite_name = testsuite.get("name")

            # Create the dsVideoDevice class
            testdVideoDevice = dsVideoDeviceClass(self.moduleConfigProfileFile, self.session, testsuite_name, self.targetWorkspace)
            test_cases = testsuite.get("test_cases")

            if test_cases:
                for test_case in testsuite.get("test_cases"):
                    self.log.stepStart(f'Test Suit: {testsuite_name} Test Case: {test_case}')
                    result = testdVideoDevice.runTest(test_case)
                    finalresult &= result
                    self.log.stepResult(result, f'Test Suit: {testsuite_name} Test Case: {test_case}')
            else:
                self.log.stepStart(f'Test Suit: {testsuite_name} Run all Tests cases')
                # If no test cases are listed, run all tests with 'r' option
                result = testdVideoDevice.runTest()
                finalresult &= result
                self.log.stepResult(result, f'Test Suit: {testsuite_name} Run all Tests cases')

            del testdVideoDevice

        return finalresult

if __name__ == '__main__':
    summerLogName = os.path.splitext(os.path.basename(__file__))[0] + "_summery"
    summeryLog = logModule(summerLogName, level=logModule.INFO)
    test = dsVideoDevice_L1_L2_tests(summeryLog)
    test.run(False)