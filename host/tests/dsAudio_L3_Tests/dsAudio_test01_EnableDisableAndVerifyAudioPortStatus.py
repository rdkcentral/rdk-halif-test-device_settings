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

class dsAudio_test01_EnableDisableAndVerifyAudioPortStatus(utHelperClass):
    """
    Test class to enable, disable, and verify the status of audio ports on a device.

    This class uses the `dsAudioClass` to interact with the device's audio ports,
    downloading necessary test assets, playing audio streams, enabling and disabling
    audio ports, and performing verification of audio output.
    """

    # Class variables
    testName  = "test01_EnableDisableAndVerifyAudioPortStatus"
    testSetupPath = os.path.join(dir_path, "dsAudio_L3_testSetup.yml")
    moduleName = "dsAudio"
    rackDevice = "dut"

    def __init__(self):
        """
        Initializes the test class with test name, setup configuration, and sessions for the device.

        Args:
            None
        """
        super().__init__(self.testName, '1')

        # Load test setup configuration
        self.testSetup = ConfigRead(self.testSetupPath, self.moduleName)

        # Open Sessions for player and hal test
        self.player_session = self.dut.getConsoleSession("ssh_player")
        self.hal_session = self.dut.getConsoleSession("ssh_hal_test")

        player = self.cpe.get("test").get("player")

        # Create player Class
        self.testPlayer = utPlayer(self.player_session, player)

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

    #TODO: Current version supports only manual verification.
    def testVerifyAudio(self, port, manual=False):
        """
        Verifies if the audio is working on the specified port.

        For manual verification, it prompts the user to confirm if audio is heard on the port.

        Args:
            port (str): The name of the audio port to verify.
            manual (bool, optional): Flag to indicate if manual verification should be used.
                                     Defaults to False for automation, True for manual.

        Returns:
            bool: True if audio verification succeeds, False otherwise.
        """
        if manual == True:
            return self.testUserResponse.getUserYN(f"Is audio playing on the {port}? (Y/N):")
        else :
            #TODO: Add automation verification methods
            return False

    def testFunction(self):
        """
        The main test function that verifies audio ports by enabling and disabling them.

        This function:
        - Downloads the required assets.
        - Runs the prerequisite commands.
        - Plays an audio stream and verifies audio output for each supported port.
        - Enables and disables audio ports while performing verification.
        - Cleans up assets after the test.

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

        # Loop through the supported audio ports
        for port,index in self.testdsAudio.getSupportedPorts():
            # Start the stream playback
            self.testPlayer.play(self.testStreams[0])

            # Port Enable test
            self.log.stepStart(f'Enable {port} Port')
            # Enable the audio port
            self.testdsAudio.enablePort(port, index)
            result = self.testVerifyAudio(port, True)
            self.log.stepResult(result, f'Audio Verification {port} Port')

            # Port Disable test
            self.log.stepStart(f'Disable {port} Port')
            # Disable the audio port
            self.testdsAudio.disablePort(port, index)
            result = self.testVerifyAudio(port, True)
            self.log.stepResult(not result, f'Audio Verification {port} Port')

            # Stop the stream playback
            self.testPlayer.stop()

        # Clean the assets downloaded to the device
        self.testCleanAssets()

        # Terminate dsAudio Module
        self.testdsAudio.terminate()

        # Clean up the dsAudio instance
        del self.testdsAudio

        return result

if __name__ == '__main__':
    test = dsAudio_test01_EnableDisableAndVerifyAudioPortStatus()
    test.run(False)
