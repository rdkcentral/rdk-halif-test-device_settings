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
sys.path.append(os.path.join(dir_path, "../"))

from dsClasses.dsCompositeIn import dsCompositeInClass
from raft.framework.plugins.ut_raft import utHelperClass
from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.plugins.ut_raft.utUserResponse import utUserResponse

class dsCompositeIn_test3_ScaleAndVerify_Video(utHelperClass):

    testName  = "dsCompositeIn_test3_ScaleAndVerify_Video"
    testSetupPath = dir_path + "/dsCompositeIn_L3_testSetup.yml"
    moduleName = "dsCompositeIn"
    rackDevice = "dut"

    def __init__(self):
        """
        Initializes the test9_ScalevideoAndVerify test .

        Args:
            None.
        """
        super().__init__(self.testName, '1')

        # Test Setup configuration file
        self.testSetup = ConfigRead(self.testSetupPath, self.moduleName)

        # Open Session for hal test
        self.hal_session = self.dut.getConsoleSession("ssh_hal_test")

         # Create user response Class
        self.testUserResponse = utUserResponse()

        # Get path to device profile file
        self.deviceProfile = dir_path + "/" + self.cpe.get("test").get("profile")

    def testDownloadAssets(self):
        """
        Downloads the test artifacts and streams listed in the test setup configuration.

        This function retrieves audio streams and other necessary files and
        saves them on the DUT (Device Under Test).

        Args:
            None
        """

        # List of streams with path
        self.testStreams = []

        self.deviceDownloadPath = self.cpe.get("target_directory")

        test = self.testSetup.get("assets").get("device").get(self.testName)

        # Download test artifacts to device
        url = test.get("artifacts")
        if url is not None:
            self.downloadToDevice(url, self.deviceDownloadPath, self.rackDevice)

        # Download test streams to device
        url =  test.get("streams")
        if url is not None:
            self.downloadToDevice(url, self.deviceDownloadPath, self.rackDevice)
            for streampath in url:
                self.testStreams.append(os.path.join(self.deviceDownloadPath, os.path.basename(streampath)))


    def testCleanAssets(self):
        """
        Removes the assets copied to the dut.

        Args:
            None.
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

    def testRunPostreiquisites(self):
        """
        Executes postrequisite commands listed in test-setup configuration file on the DUT.

        Args:
            None.
        """

       # Run commands as part of test prerequisites
        test = self.testSetup.get("assets").get("device").get(self.testName)
        cmds = test.get("postcmd")
        if cmds is not None:
            for cmd in cmds:
                self.writeCommands(cmd)

    #TODO: Current version supports only manual verification.
    def CheckDeviceStatusAndVerifyVideoScale(self, manual=False, port_type:str=0, videoscale:str=0):
        """
        Verifies whether the particular port video scaled or not.

        Args:
            manual (bool, optional): Manual verification (True: manual, False: other verification methods).
                                     Defaults to other verification methods

        Returns:
            bool
        """
        if manual == True and videoscale == False:
            return self.testUserResponse.getUserYN("Check CompositeIn source device connected on port {port_type} and press Enter")
        elif manual == True and videoscale == True:
            return self.testUserResponse.getUserYN("Check video scaled on {port_type} and press Enter")
        else:
            #TODO: Add automation verification methods
            return False

    def testFunction(self):
        """
        The main test function test scale video of dsCompositeIn device.

        This function:
        - Downloads necessary assets.
        - Runs prerequisite commands.
        - Verifies video scaling .

        Returns:
            bool: Final result of the test.
        """

        # Download the assets listed in test setup configuration file
        self.testDownloadAssets()

        # Run Prerequisites listed in the test setup configuration file
        self.testRunPrerequisites()

        # Create the dsCompositeIn class
        self.testdsCompositeIn = dsCompositeInClass(self.deviceProfile, self.hal_session)

        self.log.testStart("test3_ScaleAndVerify_Video", '1')

        # Initialize the dsCompositeIn module
        self.testdsCompositeIn.initialise(self.testdsCompositeIn.getDeviceType())

        # x-coordiante, y-coordinate, width, height list
        videoScale_argList = [[0,0,720,576], [500,500,500,500], [500,500,1000,1000],[1000,1000,2000,2000]]
        # Loop through the supported CompositeIn ports
        for port,index in self.testdsCompositeIn.getSupportedPorts():
            self.log.stepStart(f'Select {port} Port')
            self.log.step(f'Select {port} Port')

            # Check the ComposteIn device connected to is active
            portstr = f"dsCOMPOSITE_IN_PORT_{port}"
            result = self.CheckDeviceStatusAndVerifyVideoScale(True,portstr,False)
            self.log.stepResult(result,f'CompositeIn Device is connected {result} on {portstr}')

            # Select the ComposteIn port
            self.testdsCompositeIn.selectPort(port)
            self.log.step(f'Selected port {port}')
            # video scaling of ComposteIn port
            for xcord, ycord, width, height in videoScale_argList:
                scalevideo = self.testdsCompositeIn.scaleVdieo(xcord, ycord, width, height)
                result = self.CheckDeviceStatusAndVerifyVideoScale(True,port,True)
                self.log.stepResult(result, f'CompositeIn Video Scale Verification {port} Port')

        # Clean the assets downloaded to the device
        self.testCleanAssets()

        #Run postrequisites listed in the test setup configuration file 
        self.testRunPostreiquisites()

        # Terminate dsCompositeIn Module
        self.testdsCompositeIn.terminate()

        # Delete the dsCompositeIn class
        del self.testdsCompositeIn

        return result

if __name__ == '__main__':
    test = dsCompositeIn_test3_ScaleAndVerify_Video()
    test.run(False)