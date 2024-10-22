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
from raft.framework.plugins.ut_raft.utUserResponse import utUserResponse

class dsAudio_test02_PortConnectionStatus(utHelperClass):
    """
    Test class to verify the connection and disconnection status of headphone.

    This class interacts with the `dsAudioClass` to:
    - Check the connection status of headphones.
    - Test callback mechanisms for headphone connection/disconnection.
    - Perform manual or automated connection status verification.
    """
    testName  = "test02_PortConnectionStatus"
    testSetupPath = os.path.join(dir_path, "dsAudio_L3_testSetup.yml")
    moduleName = "dsAudio"
    rackDevice = "dut"

    def __init__(self):
        """
        Initializes the test class with test name, setup configuration, and session for HAL testing.

        Args:
            None
        """
        super().__init__(self.testName, '1')

        # Load test setup configuration
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
    def testWaitForConnectionChange(self, connection, manual=False):
        """
        Waits for the headphone connection or disconnection.

        Args:
            connection (bool): Set to True for connection, False for disconnection.
            manual (bool, optional): Manual control flag (True for manual user input, False for automation). 
                                     Defaults to False.

        Returns:
            None
        """
        if manual == True:
            if connection == True:
                self.testUserResponse.getUserYN(f"Connect the HEADPONE and press Enter:")
            else:
                self.testUserResponse.getUserYN(f"Disconnect the HEADPONE and press Enter:")
        else :
            # TODO: Implement automated connection change detection
            return False

    def testFunction(self):
        """
        The main test function that verifies headphone connection and disconnection.

        This function:
        - Downloads necessary assets.
        - Runs prerequisite commands.
        - Verifies headphone connection and disconnection through callbacks and direct status checks.

        Returns:
            bool: Final result of the test.
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

        # Wait for headphone connection
        self.testWaitForConnectionChange(True, True)

        self.log.stepStart('Headphone Connect Callback Test')

        callbackStatus = self.testdsAudio.getHeadphoneConnectionCallbackStatus()

        # Validate headphone connection callback
        if(callbackStatus == None or "HEADPHONE" not in callbackStatus[0] or callbackStatus[2] == False):
            result = False
        else:
            result = True

        self.log.stepResult(result, 'Headphone Connect Callback Test')

        self.log.stepStart('Headphone Connect Test')

        connectionStatus = self.testdsAudio.getHeadphoneConnectionStatus()

        self.log.stepResult(connectionStatus, 'Headphone Connect Test')

        # Wait for headphone disconnection
        self.testWaitForConnectionChange(False, True)

        self.log.stepStart('Headphone Disconnect Callback Test')

        callbackStatus = self.testdsAudio.getHeadphoneConnectionCallbackStatus()

        if(callbackStatus == None or "HEADPHONE" not in callbackStatus[0] or callbackStatus[2] == True):
            result = False
        else:
            result = True

        self.log.stepResult(result, 'Headphone Disconnect Callback Test')

        self.log.stepStart('Headphone Disconnect Test')

        connectionStatus = self.testdsAudio.getHeadphoneConnectionStatus()

        self.log.stepResult(not connectionStatus, 'Headphone Disconnect Test')

        # Terminate dsAudio Module
        self.testdsAudio.terminate()

        # Delete the dsAudio class
        del self.testdsAudio

        return True

if __name__ == '__main__':
    test = dsAudio_test02_PortConnectionStatus()
    test.run(False)
