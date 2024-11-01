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
import struct

dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(dir_path, "../../"))

from raft.framework.plugins.ut_raft.configRead import ConfigRead
from raft.framework.plugins.ut_raft.utUserResponse import utUserResponse
from raft.framework.plugins.ut_raft import utHelperClass
from raft.framework.core.logModule import logModule
from dsClasses.dsDisplay import dsDisplayClass

class dsDisplayHelperClass(utHelperClass):

    def __init__(self, testName:str, qcId:str, log:logModule=None ):
        """
        Initializes the test class with test name, setup configuration, and sessions for the device.

        Args:
            testName (str) : name of the test
            qcId (str): QC ID of the test.
            log (class, optional): Parent log class. Defaults to None.
        """
        self.testName  = ""
        self.testSetupPath = os.path.join(dir_path, "dsDisplay_L3_testSetup.yml")
        self.moduleName = "dsDisplay"
        self.rackDevice = "dut"
        self.testMonitorNameDetails = [
            {"Product":"LG", "manufacturer_id": "GSM"},
            {"Product":"Philips", "manufacturer_id": "PHL"},
            {"Product":"Element", "manufacturer_id": "ELE"}
        ]

        super().__init__(testName, qcId, log)

         # Load test setup configuration
        self.testSetup = ConfigRead(self.testSetupPath, self.moduleName)

        #open Hal Session
        self.hal_session = self.dut.getConsoleSession("ssh_hal_test")

         # Create user response Class
        self.testUserResponse = utUserResponse()

        # Get path to device profile file
        self.deviceProfile = os.path.join(dir_path, self.cpe.get("test").get("profile"))

        self.deviceDownloadPath = self.cpe.get("target_directory")

    def parseEdidData(self, edidData):
        """
        Parses the edid buffer and returns the details as dictionary
        Args:
            edidData (list): list containing edid data
        Returns:
            Dictionary
            {
                "manufacturer_id": "",
                "product_id": "",
                "serial_number": "",
                "manufacture_week": "",
                "manufacture_year": "",
                "version": "",
                "revision": "",
                "video_input_type": "",
                "max_horizontal_size": "",
                "max_vertical_size": "",
                "gamma": "",
                "standby_mode": "",
                "suspend_mode": "",
                "active_off": "",
            }
        """
        edidBytes = bytes(edidData)
        edidInfo = {}

        # EDID is usually 128 bytes long
        if len(edidBytes) < 128:
            raise ValueError("EDID data is too short")

        # Manufacturer ID: bytes 8-9, encoded as 5-bit letters
        edidInfo["manufacturer_id"] = ''.join([
            chr(((edidBytes[8] >> 2) & 0x1F) + ord('A') - 1),
            chr((((edidBytes[8] & 0x03) << 3) | ((edidBytes[9] >> 5) & 0x07)) + ord('A') - 1),
            chr((edidBytes[9] & 0x1F) + ord('A') - 1)
        ])

        # Product ID: bytes 10-11, little-endian
        edidInfo["product_id"] = struct.unpack('<H', edidBytes[10:12])[0]

        # Serial Number: bytes 12-15, little-endian
        edidInfo["serial_number"] = struct.unpack('<I', edidBytes[12:16])[0]

        # Manufacture Week and Year: bytes 16-17
        edidInfo["manufacture_week"] = edidBytes[16]
        edidInfo["manufacture_year"] = edidBytes[17] + 1990

        # EDID version: bytes 18-19
        edidInfo["version"] = edidBytes[18]
        edidInfo["revision"] = edidBytes[19]

        # Basic Display Parameters: byte 20
        edidInfo["video_input_type"] = "Digital" if (edidBytes[20] & 0x80) else "Analog"
        edidInfo["max_horizontal_size"] = edidBytes[21]  # in cm
        edidInfo["max_vertical_size"] = edidBytes[22]    # in cm
        edidInfo["gamma"] = (edidBytes[23] + 100) / 100  # gamma = (value + 100) / 100

        # Supported features: byte 24
        edidInfo["standby_mode"] = bool(edidBytes[24] & 0x80)
        edidInfo["suspend_mode"] = bool(edidBytes[24] & 0x40)
        edidInfo["active_off"] = bool(edidBytes[24] & 0x20)

        return edidInfo

    def testRunPrerequisites(self):
        """
        Executes prerequisite commands listed in the test setup configuration file on the DUT.
        Args:
            None
        """

        test = self.testSetup.get("assets").get("device").get(self.testName)

        # Download test artifacts to device
        url = test.get("artifacts")
        if url is not None:
            self.downloadToDevice(url, self.deviceDownloadPath, self.rackDevice)
        # Run commands as part of test prerequisites
        cmds = test.get("execute")
        if cmds is not None:
            for cmd in cmds:
                self.writeCommands(cmd)

    def testPrepareFunction(self):
        """
        Prepares the environment and assets required for the test.

        This function:
        - Runs the prerequisite commands.
        - Creates dsDisplayClass

        Returns:
            bool
        """
        # Run Prerequisites listed in the test setup configuration file
        self.testRunPrerequisites()

        # Create the dsDisplay class
        self.testdsDisplay = dsDisplayClass(self.deviceProfile, self.hal_session)

        return True

    def testEndFunction(self, powerOff=True):

        # Clean up the dsAudio instance
        del self.testdsDisplay
