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
import time

dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(dir_path, "../"))

from dsClasses.dsAudio import dsAudioClass
from raft.framework.plugins.ut_raft import utHelperClass
from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.plugins.ut_raft.utPlayer import utPlayer
from raft.framework.plugins.ut_raft.utUserResponse import utUserResponse

class dsAudio_test25_AudioMix(utHelperClass):
    """
    Class to perform audio mixing tests for the dsAudio module.

    This test checks the behavior of primary and system audio levels while playing audio streams.
    It verifies if the audio output behaves as expected for different volume settings.

    Attributes:
        testName (str): Name of the test case.
        testSetupPath (str): Path to the test setup configuration file.
        moduleName (str): Name of the module under test.
        rackDevice (str): Identifier for the device under test.
        primaryVolume (list): List of primary volume levels to test (0-100).
        systemVolume (list): List of system volume levels to test (0-100).
    """
    testName  = "test25_AudioMix"
    testSetupPath = os.path.join(dir_path, "dsAudio_L3_testSetup.yml")
    moduleName = "dsAudio"
    rackDevice = "dut"
    primaryVolume = [0, 25, 50, 75, 100]
    systemVolume = [0, 25, 50, 75, 100]

    def __init__(self):
        """
        Initializes the dsAudio_test25_AudioMix test instance.

        Sets up the necessary sessions and reads the configuration for the test.

        Args:
            None.
        """
        super().__init__(self.testName, '1')

        # Test Setup configuration file
        self.testSetup = ConfigRead(self.testSetupPath, self.moduleName)

        # Open Session for player
        self.player_session = self.dut.getConsoleSession("ssh_player")

        # Open Session for secondary player
        self.secondary_player_session = self.dut.getConsoleSession("ssh_player_secondary")

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
        cmds = test.get("execute");
        if cmds is not None:
            for cmd in cmds:
                self.writeCommands(cmd)

    #TODO: Current version supports only manual verification.
    def testVerifyAudio(self, port, primary_volume, system_volume, manual=False):
        """
        Verifies if the audio is functioning as expected at given volume levels.

        Args:
            port (str) : The audio port to verify.
            primary_volume (int): Primary audio volume level (0-100).
            system_volume (int): System audio volume level (0-100).
            manual (bool, optional): Indicates if manual verification is required. 
                                     Defaults to False (automated verification).

        Returns:
            bool: True if audio plays as expected, otherwise False.
        """
        if manual == True:
            return self.testUserResponse.getUserYN(f"Is Audio playing on {port} as expected with Mixing: Primary Volume: {primary_volume} System Volume: {system_volume}? (Y/N):")
        else :
            #TODO: Add automation verification methods
            return False

    def testFunction(self):
        """
        Executes the audio mixing test by verifying audio output with various volume settings.

        This function handles the overall test flow, including:
        - downloading assets
        - running prerequisites
        - Plays the primary and secondary streams
        - setting audio levels
        - verifying audio output for different combinations of primary and system volumes.

        Returns:
            bool: True if the test executes successfully, otherwise False.
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

        for port,index in self.testdsAudio.getSupportedPorts():
            # Enable the audio port
            self.testdsAudio.enablePort(port, index)

            for i in range(0, len(self.testStreams) - 1, 2):
                primaryStream = self.testStreams[i]
                systemStream = self.testStreams[i+1]

                # Start the stream playback
                self.testPlayer.play(primaryStream)

                # TODO: Update the utPlayer class to take additional arguments for the playback
                self.secondary_player_session.write(f'gst-play-1.0 {systemStream} --audiosink "amlhalasink direct-mode=0"')

                for prime in self.primaryVolume:
                    for system in self.systemVolume:
                        self.log.stepStart(f'Audio Mixing Stream: Port:{port} Primary Voulem: {prime}, System Volume: {system}')

                        self.testdsAudio.setAudioMixerLevels("dsAUDIO_INPUT_PRIMARY", prime)

                        self.testdsAudio.setAudioMixerLevels("dsAUDIO_INPUT_SYSTEM", system)

                        result = self.testVerifyAudio(port, prime, system, True)

                        self.log.stepResult(result, f'Audio Mixing Stream: Port:{port} Primary Voulem: {prime}, System Volume: {system}')

                # TODO: Update the utPlayer class to take additional arguments for the playback
                self.secondary_player_session.write("q")

                # Stop the stream playback
                self.testPlayer.stop()

            # Disable the audio port
            self.testdsAudio.disablePort(port, index)

        # Clean the assets downloaded to the device
        self.testCleanAssets()

        # Terminate dsAudio Module
        self.testdsAudio.terminate()

        # Delete the dsAudio class
        del self.testdsAudio

        return True

if __name__ == '__main__':
    test = dsAudio_test25_AudioMix()
    test.run(False)
