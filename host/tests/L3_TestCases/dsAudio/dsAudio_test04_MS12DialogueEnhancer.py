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

from L3_TestCases.dsAudio.dsAudioHelperClass import dsAudioHelperClass

class dsAudio_test04_MS12DialogueEnhancer(dsAudioHelperClass):
    """
    Test class to validate the MS12 Dialogue Enhancer functionality.

    This test configures and verifies different levels of the MS12 Dialogue Enhancer
    using the dsAudio class on the DUT (Device Under Test).
    Attributes:
        testName (str): Name of the test case.
        dialogueEnhance(list): list of dialogueenhancer values to be tested
        ms12DAPFeature(str): Name of the MS12 DAP feature being tested.
    """
    dialogueEnhance = [0, 8, 16]
    ms12DAPFeature = "DialogueEnhancer"

    def __init__(self):
        """
        Initializes the test04_MS12DialogueEnhancer test, setting up player sessions,
        configuration reading, and other required components

        Args:
            None.
        """
        self.testName  = "test04_MS12DialogueEnhancer"
        super().__init__(self.testName, '1')

    #TODO: Current version supports only manual verification.
    def testVerifyDialogueEnhance(self, stream, port, level, manual=False):
        """
        Verifies if the MS12 Dialogue Enhancer level is correctly applied.

        Args:
            stream (str): The stream used for testing.
            port (str): The audio port to verify.
            level (int): The Dialogue Enhancer level (0-16).
            manual (bool): If True, prompts the user for verification. Defaults to False.

        Returns:
            bool: True if the user confirms, otherwise False.
        """
        if manual == True:
            return self.testUserResponse.getUserYN(f"Has MS12 {self.ms12DAPFeature} level {level} applied to the {port}? (Y/N):")
        else :
            #TODO: Add automation verification methods
            return False

    def testFunction(self):
        """
        Main test function to validate MS12 Dialogue Enhancer functionality.

        This function
        - Configures the Dialogue Enhancer
        - Verifies the enhancement, and cleans up after the test.

        Returns:
            bool: True if the test passes, otherwise False.
        """
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

                    for level in self.dialogueEnhance:
                        self.log.stepStart(f'MS12 {self.ms12DAPFeature} level:{level} Port:{port} Index:{index} Stream:{stream}')

                        # Set the DialogueEnhancer
                        self.testdsAudio.setMS12Feature(port, index, {"name":self.ms12DAPFeature, "value":level})

                        result = self.testVerifyDialogueEnhance(stream, port, level, True)

                        self.log.stepResult(result, f'MS12 {self.ms12DAPFeature} level:{level} Port:{port} Index:{index} Stream:{stream}')

                    # Set the DialogueEnhancer to default
                    self.testdsAudio.setMS12Feature(port, index, {"name":self.ms12DAPFeature, "value":0})

                    # Disable the audio port
                    self.testdsAudio.disablePort(port, index)

            # Stop the stream playback
            self.testPlayer.stop()

        # Terminate dsAudio Module
        self.testdsAudio.terminate()

        return result

if __name__ == '__main__':
    test = dsAudio_test04_MS12DialogueEnhancer()
    test.run(False)
