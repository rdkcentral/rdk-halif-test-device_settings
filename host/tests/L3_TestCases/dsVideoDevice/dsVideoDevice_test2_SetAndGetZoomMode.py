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

from L3_TestCases.dsVideoDevice.dsVideoDeviceHelperClass import dsVideoDeviceHelperClass

class dsVideoDevice_test2_SetAndGetZoomMode(dsVideoDeviceHelperClass):
    """
    Class to perform set and get the Zoom mode on video device.

    Inherits from utHelperClass to leverage common test functionalities.

    Attributes:
        testName (str): Name of the test case.
        testSetupPath (str): Path to the test setup configuration file.
        moduleName (str): Name of the module being tested.
        rackDevice (str): Identifier for the device under test.
    """

    def __init__(self):
        """
        Initializes the test2_ZoomMode test .

        Args:
            None.
        """
        self.testName = "test2_ZoomMode"
        super().__init__(self.testName, '1')

       

    #TODO: Current version supports only manual verification.
    def testVerifyZoomMode(self, manual=False):
        """
        Verifies the zoom mode on specified video device.


        Args:
            manual (bool, optional): If True, requires manual confirmation from the user.
                                     Defaults to False.

        Returns:
            bool: True if audio is playing; otherwise, False.
        """
        if manual == True:
            return self.testUserResponse.getUserYN(f"Is the selected Zoom mode applied in the device's output? (Y/N):")
        else :
            return False

    def testFunction(self):
        """
        Executes the set and get tests on the video device.

        This function performs the following steps:
        - Downloads necessary assets.
        - Runs prerequisite commands.
        - Initializes the dsVideoDevice module.
        - Set and Get the Zoom Mode.
        - Cleans up the downloaded assets after testing.

        Returns:
            bool: Status of the last verification (True if successful, False otherwise).
        """

        self.log.testStart(self.testName, '1')

        # Initialize the dsVideoDevice module
        self.testdsVideoDevice.initialise(self.testdsVideoDevice.getDeviceType())

        NumofVideoDevices = self.testdsVideoDevice.getVideoDevice()
        for i in range(0, NumofVideoDevices):
            for stream in self.testStreams:
                self.testPlayer.play(stream)
                supported_modes = self.testdsVideoDevice.getZoomModes()
                if supported_modes:
                    for zoomMode in supported_modes:
                        self.testdsVideoDevice.setZoomMode(i, zoomMode)
                        self.log.step(f'Verify setZoomMode {zoomMode}')
                        result = self.testVerifyZoomMode(True)
                        self.log.stepResult(result, f'Verified setZoomMode with {zoomMode}')
                        mode = self.testdsVideoDevice.getZoomMode()
                        self.log.stepResult(zoomMode in mode, f'Get Zoom Mode {zoomMode} Test')
                else:
                    self.log.error("No Zoom mode formats available for verification.")
                    result = False

        self.testPlayer.stop()
        # Terminate dsVideoDevice Module
        self.testdsVideoDevice.terminate()

        return result

if __name__ == '__main__':
    test = dsVideoDevice_test2_SetAndGetZoomMode()
    test.run(False)
