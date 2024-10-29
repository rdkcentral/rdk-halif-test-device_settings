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

from dsClasses.dsVideoDevice import dsVideoDeviceClass
from raft.framework.plugins.ut_raft import utHelperClass
from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.plugins.ut_raft.utPlayer import utPlayer
from raft.framework.plugins.ut_raft.utUserResponse import utUserResponse

class dsVideoDevice_test2_SetAndGetZoomMode(utHelperClass):
    """
    Class to perform set and get the Zoom mode on video device.

    Inherits from utHelperClass to leverage common test functionalities.

    Attributes:
        testName (str): Name of the test case.
        testSetupPath (str): Path to the test setup configuration file.
        moduleName (str): Name of the module being tested.
        rackDevice (str): Identifier for the device under test.
    """
    testName  = "test2_ZoomMode"
    testSetupPath = os.path.join(dir_path, "dsVideoDevice_L3_testSetup.yml")
    moduleName = "dsVideoDevice"
    rackDevice = "dut"

    def __init__(self):
        """
        Initializes the test2_ZoomMode test .

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

        This function retrieves video streams and other necessary files and
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
    def testVerifyZoomMode(self, manual=False, videomode=False):
        """
        Verifies the zoom mode on specified video device.


        Args:
            manual (bool, optional): If True, requires manual confirmation from the user.
                                     Defaults to False.

        Returns:
            bool: True if video is playing and selected zoom mode applied ; otherwise, False.
        """
        if manual == True and videomode == True:
            return self.testUserResponse.getUserYN(f"Is the selected Zoom mode applied in the device's output? (Y/N):")
        else :
            #TODO: Add automation verification methods
            return False

    def testFunction(self):
        """
        Executes the set and get tests on the video device.

        This function performs the following steps:
        - Downloads necessary assets.
        - Runs prerequisite commands.
        - Initializes the dsVideoDevice module.
        - Plays the stream
        - Set and Get the Zoom Mode.
        - Cleans up the downloaded assets after testing.

        Returns:
            bool: Status of the last verification (True if successful, False otherwise).
        """

        # Download the assets listed in test setup configuration file
        self.testDownloadAssets()

        # Run Prerequisites listed in the test setup configuration file
        self.testRunPrerequisites()

        # Create the dsVideoDevice class
        self.testdsVideoDevice = dsVideoDeviceClass(self.deviceProfile, self.hal_session)

        self.log.testStart(self.testName, '1')

        # Initialize the dsVideoDevice module
        self.testdsVideoDevice.initialise(self.testdsVideoDevice.getDeviceType())

        for stream in self.testStreams:
            self.testPlayer.play(stream)

            supported_modes = self.testdsVideoDevice.getZoomModes()
            if supported_modes:
                for zoomMode in supported_modes:
                    self.testdsVideoDevice.setZoomMode(0, zoomMode)
                    self.log.step(f'Verify setZoomMode {zoomMode}')
                    result = self.testVerifyZoomMode(True, True)
                    self.log.stepResult(result, f'Verified setZoomMode with {zoomMode}')
                    mode = self.testdsVideoDevice.getZoomMode()
                    self.log.stepResult(zoomMode in mode, f'Get Zoom Mode {zoomMode} Test')
                result = True
            else:
                self.log.error("No Zoom mode formats available for verification.")
                result = False
                
            self.testPlayer.stop()


        # Clean the assets downloaded to the device
        self.testCleanAssets()

        # Terminate dsVideoDevice Module
        self.testdsVideoDevice.terminate()

        # Delete the dsVideoDevice class
        del self.testdsVideoDevice

        return result

if __name__ == '__main__':
    test = dsVideoDevice_test2_SetAndGetZoomMode()
    test.run(False)
