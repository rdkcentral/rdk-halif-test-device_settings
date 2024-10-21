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

from dsClasses.dsAudio import dsAudioClass
from raft.framework.plugins.ut_raft import utHelperClass
from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.plugins.ut_raft.utPlayer import utPlayer
from raft.framework.plugins.ut_raft.utUserResponse import utUserResponse

class dsAudio_test15_ARCPort(utHelperClass):
    """
    Test class for verifying ARC (Audio Return Channel) port functionality.

    This class handles the setup, execution, and cleanup of tests that check
    the connection and disconnection of ARC and eARC devices to the DUT (Device Under Test).

    Attributes:
        testName (str): Name of the test.
        testSetupPath (str): Path to the test setup configuration file.
        moduleName (str): Name of the audio module.
        rackDevice (str): Device under test (DUT).
    """

    testName  = "test15_ARCPort"
    testSetupPath = os.path.join(dir_path, "dsAudio_L3_testSetup.yml")
    moduleName = "dsAudio"
    rackDevice = "dut"

    def __init__(self):
        """
        Initializes the dsAudio_test15_ARCPort test.

        Sets up the test by reading the configuration, establishing necessary
        sessions, and preparing the environment for the test execution.

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
        self.deviceProfile = os.path.join(dir_path, self.cpe.get("test").get("profile"))

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

        #download test artifacts to device
        url = test.get("artifacts")
        if url is not None:
            self.downloadToDevice(url, self.deviceDownloadPath, self.rackDevice)

        #download test streams to device
        url =  test.get("streams")
        if url is not None:
            self.downloadToDevice(url, self.deviceDownloadPath, self.rackDevice)
            for streampath in url:
                self.testStreams.append(os.path.join(self.deviceDownloadPath, os.path.basename(streampath)))

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

        #Run test specific commands
        test = self.testSetup.get("assets").get("device").get(self.testName)
        cmds = test.get("execute");
        if cmds is not None:
            for cmd in cmds:
                self.writeCommands(cmd)

    #TODO: Current version supports only manual.
    def testWaitForConnectionChange(self, connection, type = "NONE", manual=False):
        """
        Waits for a change in port connection state (connection or disconnection).

        Depending on the specified parameters, it can prompt the user to
        connect or disconnect a device, or it can implement automated methods
        for managing the connection.

        Args:
            connection (bool): If True, waits for a connection; if False, waits for disconnection.
            type (str): Type of device being connected (e.g., "ARC", "eARC").
            manual (bool, optional): Indicates if manual intervention is required
                                     (True for manual, False for automated methods). Defaults to False.

        Returns:
            None
        """
        if manual == True:
            if connection == True:
                self.testUserResponse.getUserYN(f"Connect the {type} device and press Enter:")
            else:
                self.testUserResponse.getUserYN(f"Disconnect the ARC and press Enter:")
        else :
            #TODO: Add automation verification methods
            return False

    def testFunction(self):
        """
        Executes the main testing routine for verifying ARC and eARC port functionality.

        This method orchestrate
        - Downloading assets
        - Running prerequisites
        - Checking the connection status of ARC/eARC devices.

        Returns:
            bool: Indicates the success of the test execution (True if successful).
        """

        # Download the assets listed in test setup configuration file
        self.testDownloadAssets()

        # Run Prerequisites listed in the test setup configuration file
        self.testRunPrerequisites()

        # Create the dsAudio class
        self.testdsAudio = dsAudioClass(self.deviceProfile, self.hal_session)

        self.log.testStart(self.testName, '1')

        # Initialize the dsAudio module
        self.testdsAudio.initialise(self.testdsAudio.getDeviceType())

        # Loop through the supported audio ports and initialize ARC port
        for port,index in self.testdsAudio.getSupportedPorts():
            if "ARC" in port:
                # Enable the audio port
                self.testdsAudio.enablePort(port, index)

                self.log.stepStart('ARC Type Test No Device Connected')

                # Wait for ARC Port Disconnection
                self.testWaitForConnectionChange(False, "NONE", True)

                portType = self.testdsAudio.getConnectedARCType()

                self.log.stepResult(portType == "NONE", 'ARC Type Test No Device Connected')

                self.log.stepStart('ARC Test')

                # Wait for ARC device connection
                self.testWaitForConnectionChange(True, "ARC", True)

                portType = self.testdsAudio.getConnectedARCType()

                self.log.stepResult(portType == "ARC", 'ARC Test')

                self.log.stepStart('eARC Test')

                # Wait for ARC device connection
                self.testWaitForConnectionChange(True, "eARC", True)

                portType = self.testdsAudio.getConnectedARCType()

                self.log.stepResult(portType == "eARC", 'eARC Test')

                # Disable the audio port
                self.testdsAudio.disablePort(port, index)

        # Terminate dsAudio Module
        self.testdsAudio.terminate()

        # Delete the dsAudio class
        del self.testdsAudio

        return True

if __name__ == '__main__':
    test = dsAudio_test15_ARCPort()
    test.run(False)
