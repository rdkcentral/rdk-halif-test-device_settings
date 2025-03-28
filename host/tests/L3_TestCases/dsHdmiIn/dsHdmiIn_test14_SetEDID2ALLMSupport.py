import os
import sys
import time
from enum import Enum, auto

dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(dir_path))
sys.path.append(os.path.join(dir_path, "../../"))

from L3_TestCases.dsHdmiIn.dsHdmiInHelperClass import dsHdmiInHelperClass
from raft.framework.core.logModule import logModule

class dsHdmiIn_test14_SetEDID2ALLMSupport(dsHdmiInHelperClass):
    """
    A test class for setting EDID 2 ALLM support on HDMI input ports.

    This class extends `dsHdmiInHelperClass` and provides functionality
    to test setting ALLM (Auto Low Latency Mode) support in EDID 2.
    """
    def __init__(self, log: logModule = None):
        """
        Initializes the test14_SetEDID2ALLMSupport test.
        """
        self.testName = "test14_SetEDID2ALLMSupport"
        self.qcID = '14'
        super().__init__(self.testName, self.qcID, log)

    def verifyManualALLM(self, port):
        """
        Prompts the user to manually verify if the ALLM bit is set on an analyzer.

        Args:
            port (str): The HDMI input port being tested.

        Returns:
            bool: True if the user confirms the ALLM bit is set, otherwise False.
        """
        self.log.step(f'Please verify manually: Check if ALLM bit is set on the analyzer for port {port}.')
        return self.testUserResponse.getUserYN(f'Is ALLM bit set for {port}? Y/N:')

    def testFunction(self):
        """
        The main test function to set EDID 2 ALLM support on HDMI input ports
        and prompt the user for manual verification.

        Returns:
            bool: True if the user confirms the ALLM bit is set, otherwise False.
        """
        self.testdsHdmiIn.initialise()
        result = True

        for port in self.testdsHdmiIn.getSupportedPorts():
            self.log.stepStart(f'{port} Port')

            for versionIndex in range(0, 1):
                self.testdsHdmiIn.setEdid2Allm(port, versionIndex)

                user_confirmation = self.verifyManualALLM(port)

                if user_confirmation:
                    self.log.stepResult(True, f'ALLM bit is set properly as expected for the port {port}')
                    result &= True
                else:
                    self.log.stepResult(False, f'ALLM bit is not set for port as expected {port}')
                    result &= False

        self.testdsHdmiIn.terminate()
        return result

if __name__ == '__main__':
    summerLogName = os.path.splitext(os.path.basename(__file__))[0] + "_summery"
    summeryLog = logModule(summerLogName, level=logModule.INFO)
    test = dsHdmiIn_test14_SetEDID2ALLMSupport(summeryLog)
    test.run(False)
