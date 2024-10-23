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

class dsDisplay_test02_GetDisplayEDIDBytes(utHelperClass):

    """
    Test class to retrieve and verify EDID bytes from the display.

    This class uses the `dsDisplayClass` to interact with the device's display,
    downloading necessary test assets, retrieving EDID bytes, and performing verification.
    """

    # Class variables
    testName  = "test02_GetDisplayEDIDBytes"
    testSetupPath = dir_path + "/dsDisplay_L3_testSetup.yml"
    moduleName = "dsDisplay"
    rackDevice = "dut"

    def __init__(self):
        """
        Initializes the test02_GetDisplayEDIDBytes test .

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
        Downloads the artifacts in test-setup configuration file to the dut.

        Args:
            None.
        """

        self.deviceDownloadPath = self.cpe.get("target_directory")

        test = self.testSetup.get("assets").get("device").get(self.testName)

        # Download test artifacts to device
        url = test.get("artifacts")
        if url is not None:
            self.downloadToDevice(url, self.deviceDownloadPath, self.rackDevice)

    def testRunPrerequisites(self):
        """
        Runs Prerequisite commands listed in test-setup configuration file on the dut.

        Args:
            None.
        """

        #Run test specific commands
        test = self.testSetup.get("assets").get("device").get(self.testName)
        cmds = test.get("execute")
        if cmds is not None:
            for cmd in cmds:
                self.writeCommands(cmd)

    #TODO: Current version supports only manual verification.
    def testGetEDIDBytes(self, manual=False, port="dsVIDEOPORT_TYPE_HDMI" , index:int = 0):
        """
        Gets the EDIDBytes of the display through the specified video port.
        Args:
            manual (bool, optional): Manual verification (True: manual, False: other verification methods).
                                    Defaults to other verification methods
                                    port (str, optional): The type of video port to retrieve the EDID Bytes.
                                    index (int, optional): The index of the port to retrieve the EDID Bytes.
        Returns:
            bool
        """
        # Get the EDIDBytes from the display
        edidbytes = self.testdsDisplay.getEdidBytes(port, index)

        if manual:
            # Manual verification
            return self.testUserResponse.getUserYN(f"Is the EDID {edidbytes} correct? (Y/N):")
        else:
            # Automation verification
            #TODO: Add automation verification methods
            return False

    def testFunction(self):
        """
        This function will test the Display by getting the EDID Bytes of the display.

        This function:
        - Downloads the required assets.
        - Runs the prerequisite commands.
        - Retrieves EDID bytes for each supported port and verifies them.
        - Cleans up assets after the test.

        Returns:
            bool: Final result of the test.
        """

        # Download the assets listed in the test setup configuration file
        self.testDownloadAssets()

        # Run Prerequisites listed in the test setup configuration file
        self.testRunPrerequisites()

        # Create an instance of the dsDisplayClass
        self.testdsDisplay = dsDisplayClass(self.deviceProfile, self.hal_session)

        # Initialize the dsDisplay module
        self.testdsDisplay.initialise()

        self.log.testStart(self.testName, '1')

        # Get the supported video ports
        supported_ports = self.testdsDisplay.getSupportedPorts()
        result=True

        if not supported_ports:
            self.log.error("No supported ports found.")
            return False

        # Loop through the supported video ports
        for port, index in supported_ports:
            self.log.info(f"Testing port {port} at index {index}.")
            edid_result = self.testGetEDIDBytes(manual=True, port=port, index=index)
            if not edid_result:
                self.log.error(f"EDID verification failed for port {port} at index {index}.")
                result = False
                break  # Exit if verification fails

        #Terminate dsDisplay Module
        self.testdsDisplay.terminate()

        # Delete the dsDisplay class
        del self.testdsDisplay

        return result

if __name__ == '__main__':
    test = dsDisplay_test02_GetDisplayEDIDBytes()
    test.run(False)