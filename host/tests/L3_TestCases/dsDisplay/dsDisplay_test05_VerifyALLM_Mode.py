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

# Get directory path and append to system path
dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(dir_path, "../../"))

# Import required classes from modules
from dsDisplayHelperClass import dsDisplayHelperClass
from raft.framework.core.logModule import logModule


class dsDisplay_test05_VerifyALLM_Mode(dsDisplayHelperClass):
    """
    A class to test and verify Enables/Disables ALLM mode for HDMI output video port.

    Attributes:
        testName (str): Name of the test.
        testSetupPath (str): Path to the test setup configuration file.
        moduleName (str): Name of the module being tested.
        rackDevice (str): Device under test (DUT).
    """

    def __init__(self, log:logModule=None):
        """
        Initializes the test10_VerifyALLM_Mode test setup and configuration.

        Initializes sessions, reads the test setup, and prepares the user response.
        """
        self.testName  = "test05_VerifyALLM_Mode"
        self.qcID      = '5'

        super().__init__(self.testName, self.qcID, log)


    #TODO: Current version supports only manual verification.
    def testVerifyAllmMode(self, manual=False, mode:str=''):
        """
        Verifies Enables/Disables ALLM mode for HDMI output video port..

        Args:
            manual (bool, optional): If True, manual verification is done using user response; otherwise,
                                     automated verification is used (yet to be implemented).

        Returns:
            bool: Result of the ALLM mode verification.
        """
        if manual == True and mode == 'Enable':
            return self.testUserResponse.getUserYN(f'Is ALLM Mode Enabled and it is displayed on Analyzer (Y/N): ')
        elif manual == True and mode == 'Disable':
            return self.testUserResponse.getUserYN(f'Is ALLM Mode Disabled and it is displayed on Analyzer (Y/N): ')
        return False

    def testFunction(self):
        """
        Main test function that enables video ports and verifies the ALLM Mode.

        Downloads assets, runs prerequisites, enables/disables ports, and verifies ALLM Mode.

        Returns:
            bool: Final result of the ALLM Mode verification.
        """
        # Initialize the dsDisplay module
        self.testdsDisplay.initialise()

        # Loop through supported video ports and verify ALLM Mode
        for port, index in self.testdsDisplay.getSupportedPorts():
            self.testdsDisplay.selectDisplayPort(port, index)

            hdmi_version = self.testUserResponse.getUserYN(f'Please connect HDMI port on TV with 2.x (Y/N):')
            if hdmi_version:
                # Set the ALLM Mode as Enable
                self.testdsDisplay.setAllmMode('Enable')

                # Verify ALLM Mode when enabled
                self.log.stepStart(f'Verify ALLM mode Enabled')
                result = self.testVerifyAllmMode(True,'Enable')
                self.log.stepResult(result, f'Verified ALLM mode Enabled')

                # Set the ALLM Mode as Disable
                self.testdsDisplay.setAllmMode('Disable')

                # Verify ALLM Mode when disabled
                self.log.stepStart(f'Verify ALLM mode Disabled')
                result = self.testVerifyAllmMode(True,'Disable')
                self.log.stepResult(result, f'Verified ALLM mode Disabled')
            else:
                self.log.stepResult(False, f'ALLM feature is supported only on HDMI version 2.x')

        return result

if __name__ == '__main__':
    summerLogName = os.path.splitext(os.path.basename(__file__))[0] + "_summery"
    summeryLog = logModule(summerLogName, level=logModule.INFO)
    test = dsDisplay_test05_VerifyALLM_Mode(summeryLog)
    test.run(False)