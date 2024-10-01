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

from dsClasses.dsAudio import dsAudioClass
from raft.framework.plugins.ut_raft import utHelperClass
from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.plugins.ut_raft.utPlayer import utPlayer
from raft.framework.plugins.ut_raft.utUserResponse import utUserResponse

class dsAudio_test10_TestAudioFormat(utHelperClass):

    testName  = "test10_TestAudioFormat"
    testSetupPath = dir_path + "/dsAudio_L3_testSetup.yml"
    moduleName = "dsAudio"
    rackDevice = "dut"
    audioFormats = ["NONE", "PCM", "AC3", "EAC3", "AC4", "MAT", "TRUEHD", "EAC3_ATMOS",
                    "TRUEHD_ATMOS","MAT_ATMOS", "AC4_ATMOS", "AAC", "VORBIS", "WMA"]

    def __init__(self):
        """
        Initializes the test10_TestAudioFormat test .

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
                self.testStreams.append(self.deviceDownloadPath + "/" + os.path.basename(streampath))

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
    def testWaitForConnectionChange(self, connection, manual=False):
        """
        Wait for the port connection, disconnection.

        Args:
            connection (bool) : If True connect the port, otherwise disconnect the port
            manual (bool, optional): Manual Control (True: manual, False: other disconnect/connect methods).
                                     Defaults to other

        Returns:
            None
        """
        if manual == True:
            if connection == True:
                self.testUserResponse.getUserYN(f"Connect the port and press Enter:")
            else:
                self.testUserResponse.getUserYN(f"Disconnect the port and press Enter:")
        else :
            #TODO: Add automation verification methods
            return False

    def testFunction(self):
        """This function will test the Audio Ports by enabling and disabling the ports

        Returns:
            bool
        """

        # Download the assets listed in test setup configuration file
        self.testDownloadAssets()

        # Run Prerequisites listed in the test setup configuration file
        self.testRunPrerequisites()

        i = 0
        for format in self.audioFormats:
            # Start the stream playback
            self.testPlayer.play(self.testStreams[i])
            i += 1

            # Create the dsAudio class
            self.testdsAudio = dsAudioClass(self.deviceProfile, self.hal_session)

            self.log.testStart(self.testName, '1')

            # Initialize the dsAudio module
            self.testdsAudio.initialise(self.testdsAudio.getDeviceType())

            self.log.stepStart('Audio Format {format} Test')

            audioFormat = self.testdsAudio.getAudioFormat()

            self.log.stepResult(format in audioFormat, 'Audio Format {format} Test')

            # Stop the stream playback
            self.testPlayer.stop()

        # Clean the assets downloaded to the device
        self.testCleanAssets()

        # Delete the dsAudio class
        del self.testdsAudio

        return True

if __name__ == '__main__':
    test = dsAudio_test10_TestAudioFormat()
    test.run(False)
