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

from dsDisplayHelperClass import dsDisplayHelperClass
from raft.framework.core.logModule import logModule

class dsDisplay_test01_VerifyDisplayConnectCallBackTest(dsDisplayHelperClass):

    """
    Test class to verifies the display event callbacks.

    This class uses the `dsDisplayClass` to interact with the device's display,
    downloading necessary test assets, and verifies the display callback events.
    """

    def __init__(self, log:logModule=None):
        """
        Initializes the test01_VerifyDisplayConnectCallBackTest test .

        Args:
            None.
        """
        # Class variables
        self.testEvents = ["dsDISPLAY_EVENT_CONNECTED", "dsDISPLAY_EVENT_DISCONNECTED", "dsDISPLAY_RXSENSE_ON", "dsDISPLAY_RXSENSE_OFF", "dsDISPLAY_HDCPPROTOCOL_CHANGE"]
        self.testName  = "test01_VerifyDisplayConnectCallBackTest"
        self.qcID = '1'
        super().__init__(self.testName, self.qcID, log)

    #TODO: Current version supports only manual verification.
    def testRaiseDisplayEvent(self, port, event:str, manual=False):
        """
        Raises the display events to the dut
        Args:
            port (str): display port
            event (bool): display events to raise
            manual (bool, optional): Manual verification (True: manual, False: other verification methods).
                                     Defaults to other verification methods
        Returns:
            bool
        """
        if manual == True:
            return self.testUserResponse.getUserYN(f"Change the {port} status to {event} and press Enter:")
        else :
            #TODO: Add automation verification methods
            return False

    def testFunction(self):
        """
        This function will test the events callbacks raised by the display port.

        Returns:
            bool: Final result of the test.
        """

        # Initialize the dsDisplay module
        self.testdsDisplay.initialise()

        result = True
        # Loop through the supported video ports
        for port, index in self.testdsDisplay.getSupportedPorts():
            self.testdsDisplay.selectDisplayPort(port, index)
            for event in self.testEvents:
                self.log.stepStart(f'Test Display Event {event} for the Port {port}')
                self.testRaiseDisplayEvent(port, event,True)
                eventsGenerated = self.testdsDisplay.getDisplayEventFromCallback()
                result = False
                for eventgen in eventsGenerated:
                    if event == eventgen:
                        result = True
                        break
                self.log.stepResult(result, f'Test Display Event {event} for the Port {port}')

        #Terminate dsDisplay Module
        self.testdsDisplay.terminate()

        return result

if __name__ == '__main__':
    summerLogName = os.path.splitext(os.path.basename(__file__))[0] + "_summery"
    summeryLog = logModule(summerLogName, level=logModule.INFO)
    test = dsDisplay_test01_VerifyDisplayConnectCallBackTest(summeryLog)
    test.run(False)