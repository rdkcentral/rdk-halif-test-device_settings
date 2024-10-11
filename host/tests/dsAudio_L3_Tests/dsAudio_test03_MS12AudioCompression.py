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

class dsAudio_test03_MS12AudioCompression(utHelperClass):
    """
    Test class to verify the MS12 audio compression feature on various audio ports.

    This test interacts with the `dsAudioClass` to:
    - Set audio compression levels.
    - Verify the application of compression on audio streams.
    - Perform manual or automated verification of audio quality and compression.
    """

    testName  = "test03_MS12AudioCompression"
    testSetupPath = os.path.join(dir_path, "dsAudio_L3_testSetup.yml")
    moduleName = "dsAudio"
    rackDevice = "dut"
    compressionValues = [0, 5, 10] # Different levels of audio compression to be tested

    def __init__(self):
        """
        Initializes the MS12 Audio Compression test with setup configuration and sessions.

        Args:
            None.
        """
        super().__init__(self.testName, '1')

        # Load test setup configuration
        self.testSetup = ConfigRead(self.testSetupPath, self.moduleName)

        # Open Session for player
        self.player_session = self.dut.getConsoleSession("ssh_player")

        # Open Session for hal test
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
        cmds = test.get("execute")
        if cmds is not None:
            for cmd in cmds:
                self.writeCommands(cmd)

    #TODO: Current version supports only manual verification.
    def testVerifyCompressionLevel(self, stream, port, compression, manual=False):
        """
        Verifies whether the specified audio compression level is applied on the given port.

        Args:
            stream (str): The audio stream used for testing.
            port (str): The audio port on which compression is verified.
            compression (int): The compression level applied.
            manual (bool, optional): Manual verification (True for manual verification, False for other methods).
                                     Defaults to True for manual verification.

        Returns:
            bool: Returns True if the compression is correctly applied, else False.
        """
        if manual == True:
            return self.testUserResponse.getUserYN(f"Has audio compression level {compression} applied to the {port}? (Y/N):")
        else :
            #TODO: Add automation verification methods
            return False

    def testFunction(self):
        """
        Main test function for verifying MS12 audio compression across various audio ports.

        This function:
        - Downloads the required assets.
        - Runs the prerequisite commands.
        - Tests different levels of audio compression for each supported audio port.
        - Allows manual or future automated verification.

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

        for stream in self.testStreams:
            # Start the stream playback
            self.testPlayer.play(stream)

            # Loop through the supported audio ports
            for port,index in self.testdsAudio.getSupportedPorts():
                if self.testdsAudio.getAudioCompressionSupport(port, index):
                    # Enable the audio port
                    self.testdsAudio.enablePort(port, index)

                    for compression in self.compressionValues:
                        self.log.stepStart(f'Audio Compression:{compression} Port:{port} Index:{index} Stream:{stream}')

                        # Set audio compression value
                        self.testdsAudio.setAudioCompression(port, index, compression)

                        result = self.testVerifyCompressionLevel(stream, port, compression, True)

                        self.log.stepResult(result, f'Audio Compression:{compression} Port:{port} Index:{index} Stream:{stream}')

                    # Resetting audio compression value to default
                    self.testdsAudio.setAudioCompression(port, index, 0)

                    # Disable the audio port
                    self.testdsAudio.disablePort(port, index)

            # Stop the stream playback
            self.testPlayer.stop()

        # Clean the assets downloaded to the device
        self.testCleanAssets()

        # Terminate dsAudio Module
        self.testdsAudio.terminate()

        # Delete the dsAudio class
        del self.testdsAudio

        return result

if __name__ == '__main__':
    test = dsAudio_test03_MS12AudioCompression()
    test.run(False)
