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
from raft.framework.plugins.ut_raft.utPlayer import utPlayer
from raft.framework.plugins.ut_raft.utUserResponse import utUserResponse

class hdmiInSignalStatustype(Enum):
      dsHDMI_IN_SIGNAL_STATUS_NOSIGNAL = 0
      dsHDMI_IN_SIGNAL_STATUS_UNSTABLE = 1
      dsHDMI_IN_SIGNAL_STATUS_NOTSUPPORTED = 2
      dsHDMI_IN_SIGNAL_STATUS_STABLE = 3
      

class dsHdmiIn_test2_SignalChangeCallback_Verify(utHelperClass):

    testName  = "test2_SignalChangeCallback_Verify"
    testSetupPath = dir_path + "/dsHdmiIn_L3_testSetup.yml"
    moduleName = "dsHdmiIn"
    rackDevice = "dut"

    def __init__(self):
        """
        Initializes the test2_SignalChangeCallback_Verify test .

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
        Downloads the artifacts and streams listed in test-setup configuration file to the dut.

        Args:
            None.
        """

        self.deviceDownloadPath = self.cpe.get("target_directory")

        #download test artifacts to device
        url = self.testSetup.assets.device.test2_SignalChangeCallback_Verify.artifacts
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
        Runs Prerequisite commands listed in test-setup configuration file on the dut.

        Args:
            None.
        """

        #Run test specific commands
        cmds = self.testSetup.assets.device.test2_SignalChangeCallback_Verify.execute
        if cmds is not None:
            for cmd in cmds:
                self.writeCommands(cmd)

     #TODO: Current version supports only manual verification.
    def CheckDeviceStatus(self, manual=False, port_type:str:0):
        """
        Verifies whether the particular input selected or not.

        Args:
            manual (bool, optional): Manual verification (True: manual, False: other verification methods).
                                     Defaults to other verification methods

        Returns:
            bool
        """
        if manual == True:
            return self.testUserResponse.getUserYN(f'Is {port_type} Hdmi In device is ON? (Y/N):')
        else :
            #TODO: Add automation verification methods
            return False

    #TODO: Current version supports only manual verification.
    def VerifyInput(self, manual=False):
        """
        Verifies whether the particular input selected or not.

        Args:
            manual (bool, optional): Manual verification (True: manual, False: other verification methods).
                                     Defaults to other verification methods

        Returns:
            bool
        """
        if manual == True:
            return self.testUserResponse.getUserYN("Is HdmiIn port selected? (Y/N):")
        else :
            #TODO: Add automation verification methods
            return False

    def find_SignalStatus(self, input_str: str, signal_status: str) -> bool:
        if signal_status in input_str:
            return True
        return False

    def testFunction(self):
        """This Callback will check for Signal Change events on HdmiIn ports

        Returns:
            bool
        """

        # Download the assets listed in test setup configuration file
        self.testDownloadAssets()

        # Run Prerequisites listed in the test setup configuration file
        self.testRunPrerequisites()

        # Create the dsHdmiIn class
        self.testdsHdmiIn = dsHdmiInClass(self.deviceProfile, self.hal_session)

        self.log.testStart("test2_SignalChangeCallback_Verify", '1')

        # Initialize the dsAudio module
        self.testdsHdmiIn.initialise(self.testdsHdmiIn.getDeviceType())

        audmix = 0      #default value false
        videoplane = 0  #Always select primary plane.
        topmost = 1     #Always should be true.
   
        # Loop through the supported HdmiIn ports
        for port,index in self.testdsAudio.getSupportedPorts():
            self.log.stepStart(f'Select {port} Port')
            self.log.step(f'Select {port} Port')

            # Check the HdmiIn device is active
            result = self.CheckDeviceStatus(True,port)
          
            if result != False:
                self.testdsHdmiIn.selectPort(port, index, audmix, videoplane, topmost)
                result = self.VerifyInput(True)
                self.log.stepResult(result, f'HdmiIn Select Verification {port} Port')
                
                result = self.hal_session.read_until("Received SignalChange status callback port:  , sigstatus:")
                print(result)
                
                for signalstatus in list(hdmiInSignalStatustype)
                    if find_SignalStatus(result,hdmiInSignalStatustype(signalstatus).name):
                        self.log.stepResult(True,f'Signal change {hdmiInSignalStatustype(signalstatus).name} in Callback found')
                    else:
                        self.log.stepResult(False,f'Signal change {hdmiInSignalStatustype(signalstatus).name} in Callback found')


        # Clean the assets downloaded to the device
        self.testCleanAssets()

        # Terminate dsHdmiIn Module
        self.testdsHdmiIn.terminate()

        # Delete the dsHdmiIn class
        del self.testdsHdmiIn

        return result

if __name__ == '__main__':
    test = dsHdmiIn_test2_SignalChangeCallback_Verify()
    test.run(False)
