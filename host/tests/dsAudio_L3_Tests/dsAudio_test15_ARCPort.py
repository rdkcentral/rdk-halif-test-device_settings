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

from dsClasses.dsAudio import dsAudioClass
from raft.framework.plugins.ut_raft import utHelperClass
from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.plugins.ut_raft.utPlayer import utPlayer
from raft.framework.plugins.ut_raft.utUserResponse import utUserResponse

class dsAudio_test15_ARCPort(utHelperClass):

    testName  = "test15_ARCPort"
    testSetupPath = os.path.join(dir_path, "dsAudio_L3_testSetup.yml")
    moduleName = "dsAudio"
    rackDevice = "dut"

    def __init__(self):
        """
        Initializes the test15_ARCPort test .

        Args:
            None.
        """
        super().__init__(self.testName, '1')

        # Test Setup configuration file
        self.testSetup = ConfigRead(self.testSetupPath, self.moduleName)

        self.connectionCB = self.testSetup.get("callback").get("connection_status")
        self.formatCB = self.testSetup.get("callback").get("format_status")
        self.atmosCB = self.testSetup.get("callback").get("atmos_status")

        # Open Session for hal test
        self.hal_session = self.dut.getConsoleSession("ssh_hal_test")

         # Create user response Class
        self.testUserResponse = utUserResponse()

        # Get path to device profile file
        self.deviceProfile = os.path.join(dir_path, self.cpe.get("test").get("profile"))

    def testDownloadAssets(self):
        """
        Downloads the artifacts and streams listed in test-setup configuration file to the dut.

        Args:
            None.
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
        test = self.testSetup.get("assets").get("device").get(self.testName)
        cmds = test.get("execute");
        if cmds is not None:
            for cmd in cmds:
                self.writeCommands(cmd)

    #TODO: Current version supports only manual.
    def testWaitForConnectionChange(self, connection, type = "NONE", manual=False):
        """
        Wait for the port connection, disconnection.

        Args:
            connection (bool) : If True connect the port, otherwise disconnect the port
            type (str): Type of device to be connected (ARC, eARC)
            manual (bool, optional): Manual Control (True: manual, False: other disconnect/connect methods).
                                     Defaults to other

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
        """This function tests the ARC Types connected to device

        Returns:
            bool
        """

        # Download the assets listed in test setup configuration file
        self.testDownloadAssets()

        # Run Prerequisites listed in the test setup configuration file
        self.testRunPrerequisites()

        # Create the dsAudio class
        self.testdsAudio = dsAudioClass(self.deviceProfile, self.hal_session)

        self.log.testStart(self.testName, '1')

        # Initialize the dsAudio module
        self.testdsAudio.initialise(self.testdsAudio.getDeviceType(), self.connectionCB, self.formatCB, self.atmosCB)

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
