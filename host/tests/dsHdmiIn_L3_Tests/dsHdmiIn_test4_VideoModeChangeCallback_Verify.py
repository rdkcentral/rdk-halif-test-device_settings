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
from enum import Enum, auto

dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(dir_path, "../"))

from dsClasses.dsHdmiIn import dsHdmiInClass
from raft.framework.plugins.ut_raft import utHelperClass
from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.plugins.ut_raft.utUserResponse import utUserResponse

class dsHdmiIn_test4_VideoModeChangeCallback_Verify(utHelperClass):

    testName  = "test4_VideoModeChangeCallback_Verify"
    testSetupPath = dir_path + "/dsHdmiIn_L3_testSetup.yml"
    moduleName = "dsHdmiIn"
    rackDevice = "dut"

    def __init__(self):
        """
        Initializes the test4_VideoModeChangeCallback_Verify test .

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
        Downloads the test artifacts listed in the test setup configuration.

        This function retrieves necessary files and saves them on the DUT (Device Under Test).

        Args:
            None
        """

        self.deviceDownloadPath = self.cpe.get("target_directory")

        test = self.testSetup.get("assets").get("device").get(self.testName)

        # Download test artifacts to device
        url = test.get("artifacts")
        if url is not None:
            self.downloadToDevice(url, self.deviceDownloadPath, self.rackDevice)

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

       # Run commands as part of test postrequisites
        test = self.testSetup.get("assets").get("device").get(self.testName)
        cmds = test.get("postcmd")
        if cmds is not None:
            for cmd in cmds:
                self.writeCommands(cmd)

    #TODO: Current version supports only manual verification.
    def CheckDeviceStatusAndResolutionChange(self, manual=False, port_type:str=0, resolution_info:str=0):
       """
        Verifies whether the particular input selected or not.
        Ask for resolution change on source device.
        Args:
            manual (bool, optional): Manual verification (True: manual, False: other verification methods).
                                     Defaults to other verification methods
            port_type (str) : Hdmi In port type as string.
            resolution (bool, optional) : Manual verification(True: manual, False: other verification methods)

        Returns:
            bool
       """
       if manual == True and resolution_info == False:
            return self.testUserResponse.getUserYN(f'Check the Hdmi In device is on connect to {port_type} and then press Enter:')
       elif  manual == True and resolution_info == True:
            return self.testUserResponse.getUserYN(f'Change the Resolution on device connected to {port_type} and then press Enter:')
       else:
            #TODO: Add automation verification methods
            return False
       

    def testFunction(self):
        """
        The main test function video mode of Hdmi In device.

        This function:
        - Downloads necessary assets.
        - Runs prerequisite commands.
        - Verifies HDMI In video mode update through callbacks.

        Returns:
            bool: Final result of the test.
        """

        # Download the assets listed in test setup configuration file
        self.testDownloadAssets()

        # Run Prerequisites listed in the test setup configuration file
        self.testRunPrerequisites()

        # Create the dsHdmiIn class
        self.testdsHdmiIn = dsHdmiInClass(self.deviceProfile, self.hal_session)

        self.log.testStart("test4_VideoModeChangeCallback_Verify", '1')

        # Initialize the dsHdmiIn module
        self.testdsHdmiIn.initialise()

        audmix = 0      #default value false
        videoplane = 0  #Always select primary plane.
        topmost = 1     #Always should be true.
   
        # Loop through the supported HdmiIn ports
        for port in self.testdsHdmiIn.getSupportedPorts():
            self.log.stepStart(f'Select {port} Port')
            self.log.step(f'Select {port} Port')

            # Check the HdmiIn device is active
            self.CheckDeviceStatusAndResolutionChange(True, port , False)
            self.testdsHdmiIn.selectHDMIInPort(port, audmix, videoplane, topmost)
            self.log.step(f'Port Selcted {port}')

            self.CheckDeviceStatusAndResolutionChange(True, port, True)
            videomode = self.testdsHdmiIn.getVideoModeCallbackStatus()
            if port == videomode[0]:
                result = True
                self.log.stepResult(result,f'hdmi video mode port:{port} pixelresolution:{videomode[1]} aspectratio:{videomode[2]} in Callback found')
            else:
                result = False
                self.log.stepResult(result,f'hdmi video mode port:{port} pixelresolution:{videomode[1]} aspectratio:{videomode[2]} in Callback found')

        #Run postrequisites listed in the test setup configuration file 
        self.testRunPostreiquisites()

        # Terminate dsHdmiIn Module
        self.testdsHdmiIn.terminate()

        # Delete the dsHdmiIn class
        del self.testdsHdmiIn

        return result

if __name__ == '__main__':
    test = dsHdmiIn_test4_VideoModeChangeCallback_Verify()
    test.run(False)
