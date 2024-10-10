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

class dsAudio_test17_OutputMode(utHelperClass):
    """
    Test case class for verifying the audio output modes of the Device Under Test (DUT).
    
    This class inherits from utHelperClass and implements various test methods to ensure 
    proper functionality of audio output modes.

    Attributes:
        testName (str): The name of the test case.
        testSetupPath (str): Path to the test setup configuration file.
        moduleName (str): Name of the audio module under test.
        rackDevice (str): Device under test identifier.
        testOutputModes (list): List of audio output modes to be tested.
    """
    testName  = "test17_OutputMode"
    testSetupPath = os.path.join(dir_path, "dsAudio_L3_testSetup.yml")
    moduleName = "dsAudio"
    rackDevice = "dut"
    testOutputModes = [["STEREO", "PASSTHRU"], ["STEREO", "DD", "PASSTHRU"], ["STEREO", "DD", "DDPLUS", "PASSTHRU"]]

    def __init__(self):
        """
        Initializes the dsAudio_test17_OutputMode test instance.

        This constructor sets up the necessary configurations, including loading the test 
        setup file, establishing console sessions for player and HAL, and initializing 
        the player and user response classes.

        Args:
            None.
        """
        super().__init__(self.testName, '1')

        # Test Setup configuration file
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

        # remove the callback log files
        self.deleteFromDevice([self.connectionCB, self.formatCB, self.atmosCB])

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
    def testVerifyOutputMode(self, stream, port, outMode, manual=False):
        """
        Verifies the audio output mode on the specified audio port during playback.

        Args:
            stream (str): The audio stream being tested.
            port (str): The audio port to verify the output mode.
            outMode (str): The expected output mode.
            manual (bool, optional): Flag to indicate if manual verification is required.
                                     Defaults to False (automated verification).

        Returns:
            bool: True if the output mode is correct; otherwise, False.
        """
        if manual == True:
            return self.testUserResponse.getUserYN(f"Stream:{stream} Is output mode on the {port} {outMode}? (Y/N):")
        else :
            #TODO: Add automation verification methods
            return False

    def testFunction(self):
        """
        Executes the output mode tests for the audio ports by enabling/disabling each port.

        This method performs the following actions:
        - Downloads necessary test assets.
        - Runs prerequisite commands.
        - Initializes the audio module.
        - Plays the audio stream
        - Tests each supported audio port by setting and verifying output modes.

        Returns:
            bool: The final status of the output mode tests.
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
            supportedModes = self.testdsAudio.getSupportedOutputModes(port,index)

            if(supportedModes == None or len(supportedModes) == 0):
                continue

            # Enable the audio port
            self.testdsAudio.enablePort(port, index)

            for i, stream in enumerate(self.testStreams):
                # Start the stream playback
                self.testPlayer.play(stream)

                for mode in self.testOutputModes[i]:
                    for smode in supportedModes:
                        if mode in smode:
                            self.log.stepStart(f'Test Outputmode Stream:{stream} Port:{port} index:{index} output mode:{smode}')
                            # Set OutputMode
                            self.testdsAudio.setOutputMode(port, index, smode)
                            result = self.testVerifyOutputMode(stream, port, smode, True)
                            self.log.stepResult(result, f'Test Outputmode Stream:{stream} Port:{port} index:{index} output mode:{smode}')
                            break
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

        return result

if __name__ == '__main__':
    test = dsAudio_test17_OutputMode()
    test.run(False)
