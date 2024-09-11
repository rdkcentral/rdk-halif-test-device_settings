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
#from raft.framework.plugins.ut_raft.ut_core import UTCoreMenuNavigator

#TODO: Read from yaml file
run_script="./bins/run.sh"

class dsAudioTestHelperClass(utHelperClass):

    UT = None
    test_config = None
    menu_yaml = None
    menu_dict = None

    """
    Device Settings Audio Test Helper Code

    This module provides common extensions for device Settings Audio Module.
    """
    def __init__(self, testName, qcId, test_config_path, device, log=None ):
        super().__init__(testName, qcId, log=log )

        test_config = self.load_yaml(test_config_path)

        target_directory = self.config.deviceConfig.get(device).get("target_directory")

        # Copy test binaries to the target
        for source in test_config["dsAudio"]["test_prerequisite"]["test_bin"]:
            self.downloadFileToDevice(source, target_directory)

        # Copy test asserts to the target
        for source in test_config["dsAudio"]["test_prerequisite"]["test_asserts_target"]:
            self.downloadFileToDevice(source, target_directory)

        # Download Menu config
        menu_url = test_config["dsAudio"]["test_prerequisite"]["test_asserts_host"]["menu_config_url"]
        menu_config = self.downloadFileToHost(menu_url)

        #Set menu to UT Helper
        menu_dict = self.config.decodeConfigIntoDictionary(menu_config)
        self.setMenuConfiguration(menu_config)

        self.groupControl = menu_dict["control"]["menu"]["groups"]

        # Run Prerequisite commands on the target
        for cmd in test_config["dsAudio"]["test_prerequisite"]["test_pre_commands"]:
            self.writeCommandOnDevice(cmd)

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
        self.UT.run_tests(run_script, self.groupControl["name"], self.groupControl["menu_initialize"]["name"])

    def dsAudioEnablePort(self):
        """
        Enables the audio port.

        Args:
            None.

        Returns:
            None
        """
        output = self.UT.select_menu(self.groupControl["menu_enable"])

    def dsAudioVerifyAudio(self, manual=True):
        """
        Verifies whether the audio is fine or not.

        Args:
            None.

        Returns:
            bool
        """
        if manual == True:
            print("Is Audio playing fine[y/n]:")
            pass_res = self.getUserInputFromHostControl()
            if pass_res == 'y' or pass_res == 'Y' :
                return True
            else:
                return False
        else :
            #TOD: Add automation verification methods
            return False

    def dsAudioDisablePort(self):
        """
        Enables the audio port.

        Args:
            None.

        Returns:
            None
        """
        output = self.UT.select_menu(self.groupControl["menu_disable"])

    def dsAudioTerminate(self):
        """
        Enables the audio port.

        Args:
            None.

        Returns:
            None
        """
        output = self.UT.select_menu(self.groupControl["menu_terminate"])
