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
import yaml
import os
import sys

dir_path = os.path.dirname(os.path.realpath(__file__))
sys.path.append(dir_path+"/../")

from raft.framework.plugins.ut_raft.utHelper import utHelperClass
from raft.framework.plugins.ut_raft.ut_core import UTCoreMenuNavigator
from raft.framework.core.outboundClient import outboundClientClass

#TODO: Read from yaml file
run_script="./bins/run.sh"

class dsAudioTestHelperClass(utHelperClass):

    UT = None
    test_config = None
    menu_yaml = None

    """
    Device Settings Audio Test Helper Code

    This module provides common extensions for device Settings Audio Module.
    """
    def __init__(self, testName, qcId, test_config_path, log=None ):
        super().__init__(testName, qcId, log=log )

        test_config = self.load_yaml(test_config_path)
        working_directory = test_config["dsAudio"]["test_prerequisite"]["Working_directory"]

        outBoundClient = outboundClientClass(log, working_directory)

        # Copy test binaries to the target
        for source,destination in zip(test_config["dsAudio"]["test_prerequisite"]["test_bin"]["source"], test_config["dsAudio"]["test_prerequisite"]["test_bin"]["destination"]):
            file_name = os.path.basename(source)
            outBoundClient.downloadFile(source, file_name)
            self.copyFileFromHost(os.path.join(working_directory, file_name), destination)

        # Copy test asserts to the target
        for source,destination in zip(test_config["dsAudio"]["test_prerequisite"]["test_asserts_target"]["source"], test_config["dsAudio"]["test_prerequisite"]["test_asserts_target"]["destination"]):
            file_name = os.path.basename(source)
            outBoundClient.downloadFile(source, file_name)
            self.copyFileFromHost(os.path.join(working_directory, file_name), destination)

        # Download Menu config
        menu_url = test_config["dsAudio"]["test_prerequisite"]["test_asserts_host"]["menu_config_url"]
        file_name = os.path.basename(menu_url)
        outBoundClient.downloadFile(menu_url, file_name)
        menu_config = os.path.join(working_directory, file_name)

        menu_yaml = self.load_yaml(menu_config)

        # Run Prerequisite commands on the target
        for cmd in test_config["dsAudio"]["test_prerequisite"]["test_pre_commands"]:
            self.writeCommandOnDevice(cmd)

        UT = UTCoreMenuNavigator(menu_config, self.session)

    def load_yaml(self, path):
        """
        Loads and parses a YAML file from the specified path.

        Args:
            path (str): The file path to the YAML file.

        Returns:
            dict: The parsed YAML content.
        """
        with open(path, 'r') as file:
            return yaml.safe_load(file)

    def dsAudioInitialise(self):
        """
        Initializes the device settings Audio module.

        Args:
            None.

        Returns:
            None
        """
        self.UT.run_tests(run_script, self.menu_yaml["dsAudio"]["control"]["menu"]["groups"]["name"],
                          self.menu_yaml["dsAudio"]["control"]["menu"]["groups"]["menu_initialize"]["name"])

    def dsAudioEnablePort(self):
        """
        Enables the audio port.

        Args:
            None.

        Returns:
            None
        """
        output = self.writeCommandOnDevice("s", "Enter number of suite to select")

        index = self.UT.find_index_in_output(output, self.menu_yaml["dsAudio"]["control"]["menu"]["groups"]["menu_enable"]["name"])
        input = self.menu_yaml["dsAudio"]["control"]["menu"]["groups"]["menu_enable"]["input"]
        key, value = input.items()
        output = self.writeCommandOnDevice(str(index), key)

        index = self.UT.find_index_in_output(output, value)
        output = self.writeCommandOnDevice(str(index), "Enter command")

    def dsAudioVerifyAudio(self, manual=True):
        """
        Verifies whether the audio is fine or not.

        Args:
            None.

        Returns:
            bool
        """
        if manual == True:
            print("Is Audio playing fine[y\n]:")
            pass_res = input()
            if pass_res == 'y' or pass_res == 'Y' :
                self.log.testResultMessage("Passed")
                return False
            else:
                self.log.testResultMessage("Failed")
                return True
        else :
            #TOD: Add automation verification methods
            return True

    def dsAudioDisablePort(self):
        """
        Enables the audio port.

        Args:
            None.

        Returns:
            None
        """
        output = self.writeCommandOnDevice("s", "Enter number of suite to select")

        index = self.UT.find_index_in_output(output, self.menu_yaml["dsAudio"]["control"]["menu"]["groups"]["menu_disable"]["name"])
        input = self.menu_yaml["dsAudio"]["control"]["menu"]["groups"]["menu_disable"]["input"]
        key, value = input.items()
        output = self.writeCommandOnDevice(str(index), key)

        index = self.UT.find_index_in_output(output, value)
        output = self.writeCommandOnDevice(str(index), "Enter command")

    def dsAudioTerminate(self):
        """
        Enables the audio port.

        Args:
            None.

        Returns:
            None
        """
        output = self.writeCommandOnDevice("s", "Enter number of suite to select")

        index = self.UT.find_index_in_output(output, self.menu_yaml["dsAudio"]["control"]["menu"]["groups"]["menu_terminate"]["name"])
        output = self.writeCommandOnDevice(str(index), "Enter command")
