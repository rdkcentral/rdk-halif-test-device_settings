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

class dsAudio_test16_ARCSAD(utHelperClass):
    """
    Test class for verifying the ARC SAD (Source Audio Descriptor) functionality.

    Attributes:
        testName (str): Name of the test.
        testSetupPath (str): Path to the test setup configuration file.
        moduleName (str): Name of the module being tested.
        rackDevice (str): Device under test (DUT).
        sadList (list): Predefined list of ARC SAD values.
    """
    testName  = "test16_ARCSAD"
    testSetupPath = os.path.join(dir_path, "dsAudio_L3_testSetup.yml")
    moduleName = "dsAudio"
    rackDevice = "dut"
    """
    Summary of the 3-byte SAD Format:
    Byte    Bit Fields  Description
    Byte 1  Bits 0-2:   Audio Format Code: Type of audio format (PCM, AC-3, DTS, etc.)
            Bits 3-6:   Maximum Number of Channels	Number of audio channels supported
            Bit 7:      Reserved
    Byte 2	Bits 0-6:   Sampling Frequencies: Supported sampling frequencies (32 kHz, 48 kHz, etc.)
            Bit 7:      Reserved
    Byte 3	For LPCM: Bit Depths (16, 20, 24-bit) Supported bit depths for PCM
            For Compressed Formats: Maximum Bitrate	Maximum supported bitrate for compressed formats
    """
    # 0x0040382A - AC3 6 channels sampling rates (48, 96, 192 kHz), Max bitrate (512 kbps)
    # 0x00070709 - PCM 2 channels sampling rates (32, 44.1, 48 kHz), bit depth (16, 20, 24 bit per sample)
    sadList = [[0x00070709],[0x0040382A]]

    def __init__(self):
        """
        Initializes the dsAudio_test16_ARCSAD test.

        Args:
            None.
        """
        super().__init__(self.testName, '1')

        # Test Setup configuration file
        self.testSetup = ConfigRead(self.testSetupPath, self.moduleName)

        # Open Session for hal test
        self.hal_session = self.dut.getConsoleSession("ssh_hal_test")

        # Open Session for player
        self.player_session = self.dut.getConsoleSession("ssh_player")

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

    #TODO: Current version supports only manual.
    def testARCSAD(self, sad, manual=False):
        """
        Verifies the ARC Source Audio Descriptor (SAD).

        Args:
            sad (list): List of ARC SAD values to verify.
            manual (bool, optional): Indicates whether to use manual control.
                                     Defaults to False (automatic methods).

        Returns:
            bool: True if the SAD verification was successful, False otherwise.
        """
        if manual == True:
            return self.testUserResponse.getUserYN(f"Has SAD:{sad} sent to the ARC device [Y/N]:")
        else :
            #TODO: Add automation verification methods
            return False

    def testFunction(self):
        """
        Executes the test for verifying ARC SAD functionality.

        This method performs the following steps:
        - Downloads required assets.
        - Runs prerequisite commands.
        - Initializes the dsAudio module and player.
        - Tests each supported audio port for ARC functionality.
        - Stops the stream playback and cleans up.

        Returns:
            bool: True if the test ran successfully, False otherwise.
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

        # Start the stream playback
        self.testPlayer.play(self.testStreams[0])

        # Loop through the supported audio ports and initialize ARC port
        for port,index in self.testdsAudio.getSupportedPorts():
            if "ARC" in port:
                # Enable the audio port
                self.testdsAudio.enablePort(port, index)

                for sad in self.sadList:
                    self.log.stepStart(f'ARC SAD {sad} Test')

                    self.testdsAudio.setARCSAD(sad)

                    # Verify ARC SAD
                    result = self.testARCSAD(sad, True)

                    self.log.stepResult(result, f'ARC SAD {sad} Test')

                # Disable the audio port
                self.testdsAudio.disablePort(port, index)

        # Stop the stream playback
        self.testPlayer.stop()

        # Terminate dsAudio Module
        self.testdsAudio.terminate()

        # Delete the dsAudio class
        del self.testdsAudio

        return True

if __name__ == '__main__':
    test = dsAudio_test16_ARCSAD()
    test.run(False)
