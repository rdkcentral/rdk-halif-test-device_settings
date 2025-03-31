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
from enum import Enum, auto

dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(dir_path)
sys.path.append(os.path.join(dir_path, "../../"))

from L3_TestCases.dsHdmiIn.dsHdmiInHelperClass import dsHdmiInHelperClass
from raft.framework.core.logModule import logModule

class dsHdmiIn_test14_SetEDID2ALLMSupport(dsHdmiInHelperClass):
    """
    A test class for setting EDID 2 ALLM support on HDMI input ports.
    """

    def __init__(self, log: logModule = None):
        """ Initializes the test. """
        self.testName  = "test14_SetEDID2ALLMSupport"
        self.qcID = '14'
        super().__init__(self.testName, self.qcID, log)

    def verifyALLMStatus(self, port, allmsupport, manual=True):
        """
        Verifies if the ALLM bit is set, either manually or through automation (future implementation).

        Args:
            port (str): The HDMI port to verify.
            allmsupport (int): Expected ALLM status (0 or 1).
            manual (bool, optional): If True, prompts for manual verification; otherwise, uses automation. Defaults to True.

        Returns:
            bool: True if the ALLM status matches expectations, False otherwise.
        """
        if manual:
            self.log.step(f"Please verify manually: Check if the ALLM bit is set to {allmsupport} on the analyzer for port {port}.")
            self.testdsHdmiIn.selectHDMIInPort(port)
            return self.testUserResponse.getUserYN(f"Is the ALLM bit set to {allmsupport} for port {port}? (Y/N):")
        else:
            # TODO: Implement automated ALLM status verification
            self.log.info(f"Automation block for verifying ALLM status on port {port} is not yet implemented.")
            return False

    def checkDeviceStatusAndEnableALLM(self, port, manual=True):
        """
        Checks if the HDMI device is connected and enables ALLM mode.

        Args:
            port (str): The HDMI port to check.
            manual (bool, optional): If True, prompts for manual verification; otherwise, uses automation. Defaults to True.

        Returns:
            bool: True if the device is connected and verified, False otherwise.
        """
        if manual:
            return self.testUserResponse.getUserYN(f"Have you connected the HDMI device to port {port}? (Y/N):")
        else:
            # TODO: Implement automated device status check
            self.log.info(f"Automation block for checking device connection on port {port} is not yet implemented.")
            return False

    def testFunction(self):
        """
        Main test function to set EDID 2 ALLM support on HDMI input ports
        and prompt the user for verification.
        """
        self.testdsHdmiIn.initialise()

        # Get ports supporting EDID 2.0
        supportedPorts = self.testdsHdmiIn.getSupportedPortsByEdidVersion("HDMI_EDID_VER_20")

        if not supportedPorts:
            self.log.info("No ports support EDID 2.0. Test skipped.")
            return False

        for port in supportedPorts:
            self.log.stepStart(f"{port} Port")

            if not self.checkDeviceStatusAndEnableALLM(port):
                self.log.stepResult(False, f"Failed to connect to port {port}.")
                continue  # Skip to next port

            for allmSupport in (0, 1):
                self.testdsHdmiIn.setEdid2Allm(port, allmSupport)
                if self.verifyALLMStatus(port, allmSupport):
                    self.log.stepResult(True, f"ALLM bit is correctly set for port {port}.")
                else:
                    self.log.stepResult(False, f"ALLM bit is NOT set as expected for port {port}.")

        self.testdsHdmiIn.terminate()
        return True

if __name__ == '__main__':
    summerLogName = os.path.splitext(os.path.basename(__file__))[0] + "_summary"
    summaryLog = logModule(summerLogName, level=logModule.INFO)
    test = dsHdmiIn_test14_SetEDID2ALLMSupport(summaryLog)
    test.run(False)


