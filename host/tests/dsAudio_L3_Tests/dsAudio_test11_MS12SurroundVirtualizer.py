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

class dsAudio_test11_MS12SurroundVirtualizer(utHelperClass):

    testName  = "test11_MS12SurroundVirtualizer"
    testSetupPath = dir_path + "/dsAudio_L3_testSetup.yml"
    moduleName = "dsAudio"
    rackDevice = "dut"
    ms12DAPFeature = "SurroundVirtualizer"
    volumeModes = [0, 1, 2]
    boostValues = [0, 20, 40, 60, 80, 96]

    def __init__(self):
        """
        Initializes the test11_MS12SurroundVirtualizer test .

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

    #TODO: Current version supports only manual verification.
    def testVerifySurroundVirtualizer(self, stream, port, mode, level, manual=False):
        """
        Verifies whether the audio is fine or not.

        Args:
            stream (str) : Stream used for testing
            port (str) : Audio port to verify
            mode (str): SurroundVirtualizer modes
            level (int): SurroundVirtualizer level
            manual (bool, optional): Manual verification (True: manual, False: other verification methods).
                                     Defaults to other verification methods

        Returns:
            bool : returns the status of audio
        """
        if manual == True:
            return self.testUserResponse.getUserYN(f"Has MS12 {self.ms12DAPFeature} mode {mode} level {level} applied to the {port}? (Y/N):")
        else :
            #TODO: Add automation verification methods
            return False

    def testFunction(self):
        """This function tests the MS12 SurroundVirtualizer

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
        self.testdsAudio.initialise(self.testdsAudio.getDeviceType())

        for stream in self.testStreams:
            # Start the stream playback
            self.testPlayer.play(stream)

            # Loop through the supported audio ports
            for port,index in self.testdsAudio.getSupportedPorts():
                if self.testdsAudio.getMS12DAPFeatureSupport(port, index, self.ms12DAPFeature):
                    # Enable the audio port
                    self.testdsAudio.enablePort(port, index)

                    mode = 0 #SurroundVirtualizer is OFF
                    boost = 0
                    self.log.stepStart(f'MS12 {self.ms12DAPFeature} mode:{mode} boost:{boost} Port:{port} Index:{index} Stream:{stream}')

                    # Set the SurroundVirtualizer
                    self.testdsAudio.setMS12Feature(port, index, {"name":self.ms12DAPFeature, "value":[mode, boost]})

                    result = self.testVerifyVolumeleveller(stream, port, mode, boost, True)

                    mode = 2 #leveller is Auto
                    boost = 0
                    self.log.stepStart(f'MS12 {self.ms12DAPFeature} mode:{mode} boost:{boost} Port:{port} Index:{index} Stream:{stream}')

                    # Set the SurroundVirtualizer
                    self.testdsAudio.setMS12Feature(port, index, {"name":self.ms12DAPFeature, "value":[mode, boost]})

                    result = self.testVerifyVolumeleveller(stream, port, mode, boost, True)

                    mode = 1 #SurroundVirtualizer is On
                    boost = 0
                    for boost in self.boostValues:
                        self.log.stepStart(f'MS12 {self.ms12DAPFeature} mode:{mode} boost:{boost} Port:{port} Index:{index} Stream:{stream}')

                        # Set the SurroundVirtualizer
                        self.testdsAudio.setMS12Feature(port, index, {"name":self.ms12DAPFeature, "value":[mode, boost]})

                        result = self.testVerifyVolumeleveller(stream, port, mode, boost, True)

                        self.log.stepResult(result, f'MS12 {self.ms12DAPFeature} mode:{mode} boost:{boost} Port:{port} Index:{index} Stream:{stream}')

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
    test = dsAudio_test11_MS12SurroundVirtualizer()
    test.run(False)
