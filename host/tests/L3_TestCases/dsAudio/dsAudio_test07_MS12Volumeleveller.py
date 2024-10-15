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

class dsAudio_test07_MS12Volumeleveller(utHelperClass):
    """
    Test class for MS12 Volume Leveller functionality.

    Attributes:
        testName (str): Name of the test case.
        testSetupPath (str): Path to the test setup YAML file.
        moduleName (str): Name of the module being tested.
        rackDevice (str): The rack device type (DUT - Device Under Test).
        ms12DAPFeature (str): Name of the MS12 DAP feature being tested.
        volumeModes (list): List of Volume leveller modes to test.
        volumeLevels (list): List of Volume leveller levels to test.
    """

    testName  = "test07_MS12Volumeleveller"
    testSetupPath = os.path.join(dir_path, "dsAudio_L3_testSetup.yml")
    moduleName = "dsAudio"
    rackDevice = "dut"
    ms12DAPFeature = "Volumeleveller"
    volumeModes = [0, 1, 2]
    volumeLevels = [0, 5, 10]

    def __init__(self):
        """
        Initializes the test case for MS12 Volume leveller.

        Sets up necessary sessions, config files, and utility classes required for the test.

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
    def testVerifyVolumeleveller(self, stream, port, mode, level, manual=False):
        """
        Verifies whether the Volume Leveller feature is functioning correctly.

        Args:
            stream (str): Stream used for testing
            port (str): Audio port to verify
            mode (int): Volume leveller mode
            level (int): Volume leveller level
            manual (bool, optional): Manual verification option (True: manual, False: automated).
                                     Defaults to False.

        Returns:
            bool: Status indicating whether the audio verification was successful.
        """
        if manual == True:
            return self.testUserResponse.getUserYN(f"Has MS12 {self.ms12DAPFeature} mode {mode} level {level} applied to the {port}? (Y/N):")
        else :
            #TODO: Add automation verification methods
            return False

    def testFunction(self):
        """
       Main function to test the MS12 Volume Leveller.

        This function:
        - Plays audio streams
        - Apply  Volume Leveller modes on supported audio ports
        - verify the results.
        - Cleans up the assets after the test completes.

        Returns:
            bool: Result of the final verification.
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

                    mode = 2 #leveller is Auto
                    level = 0
                    self.log.stepStart(f'MS12 {self.ms12DAPFeature} mode:{mode} level:{level} Port:{port} Index:{index} Stream:{stream}')

                    # Set the volume leveller
                    self.testdsAudio.setMS12Feature(port, index, {"name":self.ms12DAPFeature, "value":[mode, level]})

                    result = self.testVerifyVolumeleveller(stream, port, mode, level, True)

                    self.log.stepResult(result, f'MS12 {self.ms12DAPFeature} mode:{mode} level:{level} Port:{port} Index:{index} Stream:{stream}')

                    mode = 1 #leveller is On
                    level = 0
                    for level in self.volumeLevels:
                        self.log.stepStart(f'MS12 {self.ms12DAPFeature} mode:{mode} level:{level} Port:{port} Index:{index} Stream:{stream}')

                        # Set the volume leveller
                        self.testdsAudio.setMS12Feature(port, index, {"name":self.ms12DAPFeature, "value":[mode, level]})

                        result = self.testVerifyVolumeleveller(stream, port, mode, level, True)

                        self.log.stepResult(result, f'MS12 {self.ms12DAPFeature} mode:{mode} level:{level} Port:{port} Index:{index} Stream:{stream}')

                    mode = 0 #leveller is OFF
                    level = 0
                    self.log.stepStart(f'MS12 {self.ms12DAPFeature} mode:{mode} level:{level} Port:{port} Index:{index} Stream:{stream}')

                    # Set the volume leveller
                    self.testdsAudio.setMS12Feature(port, index, {"name":self.ms12DAPFeature, "value":[mode, level]})

                    result = self.testVerifyVolumeleveller(stream, port, mode, level, True)

                    self.log.stepResult(result, f'MS12 {self.ms12DAPFeature} mode:{mode} level:{level} Port:{port} Index:{index} Stream:{stream}')

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
    test = dsAudio_test07_MS12Volumeleveller()
    test.run(False)
