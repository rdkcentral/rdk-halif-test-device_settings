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

class dsAudio_test26_MS12AudioProfiles(utHelperClass):
    """
    This class represents the 'test26_MS12AudioProfiles' test case, which is responsible
    for verifying Dolby MS12 audio profiles on different audio ports of the Device Under Test (DUT).

    Attributes:
        testName (str): Name of the test case.
        testSetupPath (str): Path to the test setup configuration file.
        moduleName (str): Name of the module under test.
        rackDevice (str): Identifier for the device under test.
    """
    testName  = "test26_MS12AudioProfiles"
    testSetupPath = os.path.join(dir_path, "dsAudio_L3_testSetup.yml")
    moduleName = "dsAudio"
    rackDevice = "dut"

    def __init__(self):
        """
        Initializes the 'test26_MS12AudioProfiles' test by setting up the test environment.

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
    def testVerifyMS12AudioProfile(self, port, profile, manual=False):
        """
        Verifies if the specified MS12 audio profile is applied correctly on the given audio port.

        This can be done either manually (by asking the user) or through an automated verification method (not yet implemented).

        Args:
            port (str): The audio port to verify (e.g., HDMI, Optical).
            profile (str): The MS12 audio profile to be tested (e.g., Off, Music, Movie, etc.).
            manual (bool, optional): If True, manual verification is used. Defaults to False (automated verification).

        Returns:
            bool: True if the profile is correctly applied, otherwise False.
        """
        if manual == True:
            return self.testUserResponse.getUserYN(f"Has audio profile {profile} applied to the {port}? (Y/N):")
        else :
            #TODO: Add automation verification methods
            return False

    def testFunction(self):
        """
        Executes the 'test26_MS12AudioProfiles' test case. The test performs the following steps:

        - Downloads the required assets.
        - Runs the prerequisite commands on the DUT.
        - Initializes the dsAudio module.
        - Plays test streams and iterates through supported audio ports and profiles.
        - Verifies if the correct MS12 audio profiles are applied to the ports.
        - Cleans up the assets and terminates the dsAudio module.

        Returns:
            bool: Returns True if the test completes successfully.
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
                profileList = self.testdsAudio.getSupportedMS12Profiles(port, index)
                if(profileList):
                    # Enable the audio port
                    self.testdsAudio.enablePort(port, index)

                    for profile in profileList:
                        # Set the Audio Profile
                        self.testdsAudio.setMS12AudioProfile(port, index, profile)
                        # Verify the audio
                        self.testVerifyMS12AudioProfile(port, profile, True)

                    # Enable the audio port
                    self.testdsAudio.disablePort(port, index)

            # Stop the stream playback
            self.testPlayer.stop()

        # Stop the stream playback
        self.testPlayer.stop()

        # Clean the assets downloaded to the device
        self.testCleanAssets()

        # Terminate dsAudio Module
        self.testdsAudio.terminate()

        # Delete the dsAudio class
        del self.testdsAudio

        return True

if __name__ == '__main__':
    test = dsAudio_test26_MS12AudioProfiles()
    test.run(False)
