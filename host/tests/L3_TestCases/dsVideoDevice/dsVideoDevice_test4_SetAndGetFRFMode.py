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


class dsVideoDevice_test4_SetAndGetFRFMode(dsVideoDeviceHelperClass):
    """
    Class to perform set and get the FRF mode on video device.

    Inherits from utHelperClass to leverage common test functionalities.

    Attributes:
        testName (str): Name of the test case.
        testSetupPath (str): Path to the test setup configuration file.
        moduleName (str): Name of the module being tested.
        rackDevice (str): Identifier for the device under test.
    """

    def __init__(self):
        """
        Initializes the test4_FRFMode test .

        Args:
            None.
        """
        self.testName  = "test4_FRFMode"
        super().__init__(self.testName, '1')


    def testVerifyFRFMode(self, manual=False, frfmode=False):
        """
        Verifies the FRF mode on specified video device.


        Args:
            manual (bool, optional): If True, requires manual confirmation from the user.
                                     Defaults to False.

        Returns:
            bool: True if selected FRF mode is visible in output device; otherwise, False.
        """
        if manual == True and frfmode == True:
            return self.testUserResponse.getUserYN(f"Wait till playback ends. And, Check whether the video playback is smooth without any streaming issues (Y/N):")
        elif manual == True and frfmode == False:
            return self.testUserResponse.getUserYN(f"Wait till playback ends. And, Check whether the video playback has streamming issues is seen? (Y/N):")
        else :
            #TODO: Add automation verification methods
            return False

    
    def testFunction(self):
        """
        Executes the set and get FRF mode tests on the video device.

        This function performs the following steps:
        - Downloads necessary assets.
        - Runs prerequisite commands.
        - Initializes the dsVideoDevice module.
        - Get the number of video devices
        - Set the FRF mode to Enable
        - Play the video stream
        - Wait till playback ends and verify with observation
        - Set the FRF mode to Disable
        - Play the video stream
        - Wait till playback ends and verify with observation
        - Cleans up the downloaded assets after testing.

        Returns:
            bool: Status of the last verification (True if successful, False otherwise).
        """
        
        self.log.testStart(self.testName, '1')

        # Initialize the dsVideoDevice module
        self.testdsVideoDevice.initialise(self.testdsVideoDevice.getDeviceType())

        NumofVideoDevices = self.testdsVideoDevice.getVideoDevice()
        for i in range(0, NumofVideoDevices):
            self.testdsVideoDevice.setFRFMode(i, 'Enable')
            self.log.step(f'Wait till Playback ends.')
            
            #Playback with framerate 24fps
            for stream in self.testStreams:
                self.testPlayer.play(stream)

            result = self.testVerifyFRFMode(True,True)
            if result:
                self.log.stepResult(result, f'Playback was fine without any streaming issues')
            else:
                self.log.error("Able to observe streaming issues")

            self.testdsVideoDevice.setFRFMode(i, 'Disable')
            self.log.step(f'Wait till Playback ends.')
            
            #Playback with framerate 24fps
            for stream in self.testStreams:
                self.testPlayer.play(stream)
            

            result = self.testVerifyFRFMode(True,False)
            if result:
                self.log.stepResult(True, f'Playback with streaming issues')
            else:
                self.log.error("When FRF mode Disable playback was smooth")

            self.testPlayer.stop()
        # Terminate dsVideoDevice Module
        self.testdsVideoDevice.terminate()

        
        return result

if __name__ == '__main__':
    test = dsVideoDevice_test4_SetAndGetFRFMode()
    test.run(False)
