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
import re

dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(dir_path+"/../")

from dsClasses.dsCompositeIn import dsCompositeInClass
from raft.framework.plugins.ut_raft import utHelperClass
from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.plugins.ut_raft.utPlayer import utPlayer
from raft.framework.plugins.ut_raft.utUserResponse import utUserResponse

class dsCompositeIn_test2_VerifyStatus_Callback(utHelperClass):

    testName  = "test2_VerifyStatus_Callback"
    testSetupPath = dir_path + "/dsCompositeIn_L3_testSetup.yml"
    moduleName = "dsCompositeIn"
    rackDevice = "dut"

    def __init__(self):
        """
        Initializes the test2_VerifyStatus_Callback test .

        Args:
            None.
        """
        super().__init__(self.testName, '1')

        # Test Setup configuration file
        self.testSetup = ConfigRead(self.testSetupPath, self.moduleName)

        # Open Session for player
        #self.player_session = self.dut.getConsoleSession("ssh_player")

        # Open Session for hal test
        self.hal_session = self.dut.getConsoleSession("ssh_hal_test")

        #player = self.cpe.get("test").get("player")

        # Create player Class
        #self.testPlayer = utPlayer(self.player_session, player)

         # Create user response Class
        self.testUserResponse = utUserResponse()

        # Get path to device profile file
        self.deviceProfile = dir_path + "/" + self.cpe.get("test").get("profile")

    def testDownloadAssets(self):
        """
        Downloads the artifacts and streams listed in test-setup configuration file to the dut.

        Args:
            None.
        """

        # List of streams with path
        self.testStreams = []

        self.deviceDownloadPath = self.cpe.get("target_directory")

        #download test artifacts to device
        url = self.testSetup.assets.device.test2_VerifyStatus_Callback.artifacts
        if url is not None:
            self.downloadToDevice(url, self.deviceDownloadPath, self.rackDevice)

        #download test streams to device
        url = self.testSetup.assets.device.test2_VerifyStatus_Callback.streams
        if url is not None:
            self.downloadToDevice(url, self.deviceDownloadPath, self.rackDevice)
            for streampath in url:
                self.testStreams.append(self.deviceDownloadPath + "/" + os.path.basename(streampath))

    def testCleanAssets(self):
        """
        Removes the assets copied to the dut.

        Args:
            None.
        """
        self.deleteFromDevice(self.testStreams)

    def testRunPrerequisites(self):
        """
        Runs Prerequisite commands listed in test-setup configuration file on the dut.

        Args:
            None.
        """

        #Run test specific commands
        cmds = self.testSetup.assets.device.test2_VerifyStatus_Callback.execute
        if cmds is not None:
            for cmd in cmds:
                self.writeCommands(cmd)

    #TODO: Current version supports only manual verification.
    def CheckDeviceStatus(self, manual=False):
        """
        Verifies whether Composite Source Device connected or not

        Args:
            manual (bool, optional): Manual verification (True: manual, False: other verification methods).
                                     Defaults to other verification methods

        Returns:
            bool
        """
        if manual == True:
            return self.testUserResponse.getUserYN("Check if CompositeIn source is connected and press Enter:")
        else :
            #TODO: Add automation verification methods
            return False

    def testFunction(self):
        """This function will test and verify the active status callback

        Returns:
            bool
        """

        # Download the assets listed in test setup configuration file
        self.testDownloadAssets()

        # Run Prerequisites listed in the test setup configuration file
        self.testRunPrerequisites()


        # Create the dsCompositeIn class
        self.testdsCompositeIn = dsCompositeInClass(self.deviceProfile, self.hal_session)

        self.log.testStart("test2_VerifyStatus_Callback", '1')

        # Initialize the ddsCompositeIn module
        self.dsCompositeIn.initialise()

        # Loop through the supported ports
        for port in self.dsCompositeIn.getSupportedPorts():
            self.log.stepStart(f'Select {port} Port')
            self.log.step(f'Select {port} Port')

            result = self.CheckDeviceStatus(True)
            self.log.stepResult(result,f'CompositeIn Device is connected {result} on {port}')
          
            self.dsCompositeIn.selectPort(port)
            self.log.step(f'Port Selcted {port}')
                
            status = self.dsCompositeIn.getPortCallbackStatus()
            portstr = f"dsCOMPOSITE_IN_PORT_{port}"
            if status[1] == portstr:
               result = True    
               self.log.stepResult(result,f'Port Status ispresented:{status[0]} activeport:{status[1]} found in Callback')
            else:
               result = False
               self.log.stepResult(result,f'Port Status ispresented:{status[0]} activeport:{status[1]} found in Callback')


        # Clean the assets downloaded to the device
        self.testCleanAssets()

        # Terminate dsCompositeIn Module
        self.dsCompositeIn.terminate()

        # Delete the dsCompositeIn class
        del self.testdsCompositeIn

        return result

if __name__ == '__main__':
    test = dsCompositeIn_test2_VerifyStatus_Callback()
    test.run(False)