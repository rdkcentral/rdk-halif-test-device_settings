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
sys.path.append(os.path.join(dir_path, "../../"))

from L3_TestCases.dsAudio.dsAudioHelperClass import dsAudioHelperClass

class dsAudio_test22_AudioFormat(dsAudioHelperClass):
    """
    Test class for validating audio format functionalities.

    This class is designed to test the audio formats supported by the device.
    It extends the utHelperClass to leverage its utility methods for device interaction
    and test execution.

    Attributes:
        testName (str): Name of the test.
        audioFormats (list): List of audio formats to be tested.
    """
    audioFormats = ["PCM", "AC3", "EAC3", "AAC", "VORBIS", "WMA", "AC4", "MAT", "TRUEHD", "EAC3_ATMOS", "TRUEHD_ATMOS", "MAT_ATMOS", "AC4_ATMOS"]

    def __init__(self):
        """
        Initializes the dsAudio_test22_AudioFormat test.

        This constructor sets up the necessary configurations and prepares the 
        test environment by initializing player and user response classes.

        Args:
            None
        """
        self.testName  = "test22_AudioFormat"
        super().__init__(self.testName, '1')

    def testFunction(self):
        """
        Executes the audio format test.

        This method:
        - Runs through the various audio formats
        - Playing associated streams
        - Verifying that the audio formats are correctly reported by the device.

        Returns:
            bool: Always returns True upon successful execution of the test.
        """
        self.log.testStart(self.testName, '1')

        # Initialize the dsAudio module
        self.testdsAudio.initialise(self.testdsAudio.getDeviceType())

        self.log.stepStart(f'Audio Format NONE Test')

        # Get the Audio Format
        audioFormat = self.testdsAudio.getAudioFormat()

        self.log.stepResult("NONE" in audioFormat, f'Audio Format NONE Test')

        for format, stream in zip(self.audioFormats, self.testStreams):
            # Start the stream playback
            self.testPlayer.play(stream)
            time.sleep(3)

            self.log.stepStart(f'Audio Format {format} Callback Test')

            cbAudioFormat = self.testdsAudio.getAudioFormatCallbackStatus()

            self.log.stepResult(cbAudioFormat and format in cbAudioFormat, f'Audio Format {format} Callback Test')

            self.log.stepStart(f'Audio Format {format} Test')

            # Get the Audio Format
            audioFormat = self.testdsAudio.getAudioFormat()

            self.log.stepResult(format in audioFormat, f'Audio Format {format} Test')

            # Stop the stream playback
            self.testPlayer.stop()

        # Terminate dsAudio Module
        self.testdsAudio.terminate()

        return True

if __name__ == '__main__':
    test = dsAudio_test22_AudioFormat()
    test.run(False)
