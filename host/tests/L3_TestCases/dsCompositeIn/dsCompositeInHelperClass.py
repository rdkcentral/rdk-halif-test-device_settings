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
from dsClasses.dsCompositeIn import dsCompositeInClass

class dsCompositeInHelperClass(utHelperClass):

    def __init__(self, testName:str, qcId:str, log:logModule=None ):
        """
        Initializes the test class with test name, setup configuration, and sessions for the device.

        Args:
            testName (str) : name of the test
            qcId (str): QC ID of the test.
            log (class, optional): Parent log class. Defaults to None.
        """
        self.testName  = ""
        self.testSetupPath = os.path.join(dir_path, "dsCompositeIn_L3_testSetup.yml")
        self.moduleName = "dsCompositeIn"
        self.rackDevice = "dut"

        super().__init__(testName, qcId, log)

        # Load test setup configuration
        self.testSetup = ConfigRead(self.testSetupPath, self.moduleName)

        # Open Sessions for hal test
        self.hal_session = self.dut.getConsoleSession("ssh_hal_test")

         # Create user response Class
        self.testUserResponse = utUserResponse()

        # Get path to device profile file
        self.deviceProfile = os.path.join(dir_path, self.cpe.get("test").get("profile"))

        self.targetWorkspace = self.cpe.get("target_directory")
        self.targetWorkspace = os.path.join(self.targetWorkspace, self.moduleName)
        self.streamDownloadURL = self.cpe.get("test").get("streams_download_url")

    def testDownloadAssets(self):
        """
        Downloads the test artifacts and streams listed in the test setup configuration.

        This function retrieves streams and other necessary files and
        saves them on the DUT (Device Under Test).

        Args:
            None
        """

        # List of streams with path
        self.testStreams = []
        url = []

        streamPaths = self.testSetup.get("assets").get("device").get(self.testName).get("streams")

        # Download test streams to device
        if streamPaths and self.streamDownloadURL:
            for streamPath in streamPaths:
                url.append(os.path.join(self.streamDownloadURL, streamPath))
                self.testStreams.append(os.path.join(self.targetWorkspace, os.path.basename(streamPath)))
            self.downloadToDevice(url, self.targetWorkspace, self.rackDevice)

    def testCleanAssets(self):
        """
        Removes the downloaded assets and test streams from the DUT after test execution.

        Args:
            None
        """
        self.deleteFromDevice(self.testStreams)

    def testRunPrerequisites(self):
        """
        Executes prerequisite commands listed in the test setup configuration file on the DUT.

        Args:
            None
        """

        # Run commands as part of test prerequisites
        test = self.testSetup.get("assets").get("device").get(self.testName)
        cmds = test.get("execute")
        if cmds is not None:
            for cmd in cmds:
                self.writeCommands(cmd)

        # Run commands as part of test prerequisites
        prerequisite_cmds = self.cpe.get("test").get("prerequisites")
        if prerequisite_cmds is not None:
            for expcmd in prerequisite_cmds:
                print(expcmd)
                self.writeCommands(expcmd)

    def testPrepareFunction(self):
        """
        Prepares the environment and assets required for the test.

        This function:
        - Downloads the required assets.
        - Runs the prerequisite commands.
        - Creates dsCompositeInClass

        Returns:
            bool
        """

        # Download the assets listed in test setup configuration file
        self.testDownloadAssets()

        # Run Prerequisites listed in the test setup configuration file
        self.testRunPrerequisites()

        # Create the dsCompositeIn class
        self.testdsCompositeIn = dsCompositeInClass(self.deviceProfile, self.hal_session, self.targetWorkspace)

        return True

    def testEndFunction(self, powerOff=True):
        # Clean up the dsCompositeIn instance
        del self.testdsCompositeIn

    def testExceptionCleanUp (self):
        # Clean the assets downloaded to the device
        self.testCleanAssets()