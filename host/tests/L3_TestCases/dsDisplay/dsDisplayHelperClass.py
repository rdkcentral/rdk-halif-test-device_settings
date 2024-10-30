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
from raft.framework.plugins.ut_raft.utUserResponse import utUserResponse
from raft.framework.plugins.ut_raft import utHelperClass
from raft.framework.core.logModule import logModule
from dsClasses.dsDisplay import dsDisplayClass

class dsDisplayHelperClass(utHelperClass):

    def __init__(self, testName:str, qcId:str, log:logModule=None ):
        """
        Initializes the test class with test name, setup configuration, and sessions for the device.

        Args:
            testName (str) : name of the test
            qcId (str): QC ID of the test.
            log (class, optional): Parent log class. Defaults to None.
        """
        self.testName  = ""
        self.testSetupPath = os.path.join(dir_path, "dsDisplay_L3_testSetup.yml")
        self.moduleName = "dsDisplay"
        self.rackDevice = "dut"

        super().__init__(testName, qcId, log)

         # Load test setup configuration
        self.testSetup = ConfigRead(self.testSetupPath, self.moduleName)

        #open Hal Session
        self.hal_session = self.dut.getConsoleSession("ssh_hal_test")

         # Create user response Class
        self.testUserResponse = utUserResponse()

        # Get path to device profile file
        self.deviceProfile = os.path.join(dir_path, self.cpe.get("test").get("profile"))

        self.deviceDownloadPath = self.cpe.get("target_directory")

    def testRunPrerequisites(self):
        """
        Executes prerequisite commands listed in the test setup configuration file on the DUT.
        Args:
            None
        """

        test = self.testSetup.get("assets").get("device").get(self.testName)

        # Download test artifacts to device
        url = test.get("artifacts")
        if url is not None:
            self.downloadToDevice(url, self.deviceDownloadPath, self.rackDevice)
        # Run commands as part of test prerequisites
        cmds = test.get("execute")
        if cmds is not None:
            for cmd in cmds:
                self.writeCommands(cmd)


    def testPrepareFunction(self):
        """
        Prepares the environment and assets required for the test.

        This function:
        - Runs the prerequisite commands.
        - Creates dsDisplayClass

        Returns:
            bool
        """
        # Run Prerequisites listed in the test setup configuration file
        self.testRunPrerequisites()

        # Create the dsDisplay class
        self.testdsDisplay = dsDisplayClass(self.deviceProfile, self.hal_session)

        return True

    def testEndFunction(self, powerOff=True):

        # Clean up the dsAudio instance
        del self.testdsDisplay
