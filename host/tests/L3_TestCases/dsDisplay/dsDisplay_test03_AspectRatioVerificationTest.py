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
sys.path.append(dir_path+"../../../")

from L3_TestCases.dsDisplay.dsDisplayHelperClass import dsDisplayHelperClass
from dsClasses.dsDisplay import dsVideoAspectRatio


class dsDisplay_test03_AspectRatioVerificationTest(dsDisplayHelperClass):

    """
    Test class to retrieve and verify the display aspect ratio.

    This class uses the `dsDisplayClass` to interact with the device's display,
    downloading necessary test assets, retrieving the aspect ratio, and performing verification.
    """

    # Class variables
    def __init__(self):
        """
        Initializes the test03_GetDisplayAspectRatio test .

        Args:
            None.
        """
        self.testName  = "test03_AspectRatioVerificationTest"
        super().__init__(self.testName,'3')


    #TODO: Current version supports only manual verification.
    def testGetDisplayAspectRatio(self, manual=False, port="dsVIDEOPORT_TYPE_HDMI" , index:int = 0):
        """
        Gets the aspectratio of the display.
        Args:
            manual (bool, optional): Manual verification (True: manual, False: other verification methods).
                                    Defaults to other verification methods
                                    port (str, optional): The type of video port to retrieve the EDID Bytes.
                                    index (int, optional): The index of the port to retrieve the EDID Bytes.
        Returns:
            bool
        """
        # Get the aspectratio from the display
        for ratio in dsVideoAspectRatio:
            if ratio == dsVideoAspectRatio.dsVIDEO_ASPECT_RATIO_MAX:
                continue
            result = self.testUserResponse.getUserYN(f"Set the aspectratio to {ratio}! (Y/N):")
            if not result:
                self.log.error(f"DisplayAspectRatio {ratio.name} could not set from user.")
                continue
            retirevedRatio = self.testdsDisplay.getAspectRatio()
            result = False
            if ratio.name == retirevedRatio:
                result = True
        return result


    def testFunction(self):
        """
        This function will test the Display by getting the aspectratio of the display.

        This function:
        - Downloads the required assets.
        - Runs the prerequisite commands.
        - Retrieves aspectratio for each supported port and verifies them.
        - Cleans up assets after the test.

        Returns:
            bool: Final result of the test.
        """

        self.log.testStart(self.testName, '1')
        # Initialize the dsDisplay module
        self.testdsDisplay.initialise()



        # Get the supported video ports
        supported_ports = self.testdsDisplay.getSupportedPorts()
        result=True

        if not supported_ports:
            self.log.error("No supported ports found.")
            return False

        # Loop through the supported video ports
        for port, index in supported_ports:
            self.log.info(f"Testing port {port} at index {index}.")
            self.testdsDisplay.getDisplayHandle(port, index)
            result = self.testGetDisplayAspectRatio(manual=True)
            if not result:
                self.log.error(f"DisplayAspectRatio verification failed for port {port} at index {index}.")
                result = False
                break  # Exit if verification fails

        #Terminate dsDisplay Module
        self.testdsDisplay.terminate()

        # Delete the dsDisplay class
        del self.testdsDisplay

        return result

if __name__ == '__main__':
    test = dsDisplay_test03_AspectRatioVerificationTest()
    test.run(False)