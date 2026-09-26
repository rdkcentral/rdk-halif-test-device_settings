#!/usr/bin/env python3
#** *****************************************************************************
# *
# * If not stated otherwise in this file or this component's LICENSE file the
# * following copyright and licenses apply:
# *
# * Copyright 2026 RDK Management
# *
# * Licensed under the Apache License, Version 2.0 (the "License");
# * you may not use this file except in compliance with the License.
# * You may obtain a copy of the License at
# *
# *
# * http://www.apache.org/licenses/LICENSE-2.0
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
sys.path.append(os.path.join(dir_path))
sys.path.append(os.path.join(dir_path, "../../"))

from dsAudioHelperClass import dsAudioHelperClass
from raft.framework.core.logModule import logModule


class dsAudio_test27_ContinuousAudioOutput(dsAudioHelperClass):
    """
    Verifies the Continuous Audio Output (CAO) application audio configuration.

    The primary purpose of CAO is to keep MS12 outputting silent encoded frames
    to the downstream AVR/Soundbar even when no content is playing. This holds
    the external device's clock locked so that when content resumes there is no
    audible pop, click, or mute gap.
    """

    def __init__(self, log: logModule = None):
        self.testName = "test27_ContinuousAudioOutput"
        self.qcID = '27'
        super().__init__(self.testName, self.qcID, log)

    def testVerifyAVRSignal(self, port, index, prompt):
        """
        Manually verify Soundbar behavior.

        The tester should listen for:
          - pop
          - click
          - mute gap
          - audio re-lock delay

        Returns:
            bool: True if expected behavior is observed.
        """
        return self.testUserResponse.getUserYN(
            f"{prompt} Port: {port}/{index} (Y/N):"
        )

    def testFunction(self):
        result = True

        # ---------------------------------------------------------
        # Initialize dsAudio
        # ---------------------------------------------------------
        self.testdsAudio.initialise(
            self.testdsAudio.getDeviceType()
        )

        # ---------------------------------------------------------
        # Get application audio configurations
        # ---------------------------------------------------------
        self.log.stepStart(
            "Query Application Audio Config List"
        )

        configList = (
            self.testdsAudio.getApplicationAudioConfigList()
        )

        self.log.stepResult(
            len(configList) > 0,
            f"Supported application audio configs: {configList}"
        )

        if not configList:
            self.testdsAudio.terminate()
            return True

        # ---------------------------------------------------------
        # Get supported audio ports.
        #
        # CAO is relevant to external encoded outputs.
        # For a Soundbar connected through ARC, HDMI_ARC is the
        # primary port. SPDIF is included when available.
        #
        # getSupportedPorts() provides the actual port/index pair.
        # ---------------------------------------------------------
        supported_ports = self.testdsAudio.getSupportedPorts()

        external_encoded_ports = [
            (port, index)
            for port, index in supported_ports
            if port in ("dsAUDIOPORT_TYPE_HDMI_ARC")
            #, "dsAUDIOPORT_TYPE_SPDIF")
        ]

        self.log.stepResult(
            len(external_encoded_ports) > 0,
            f"External encoded audio ports: "
            f"{external_encoded_ports}"
        )

        if not external_encoded_ports:
            self.testdsAudio.terminate()
            return False

        # ---------------------------------------------------------
        # One stream only:
        #
        # self.testStreams[0] MUST be the 5.1 E-AC3 stream.
        #
        # Example:
        #   tones_string_48k_5.1.eac3
        # ---------------------------------------------------------
        cao_stream = self.testStreams[0]

        self.log.info(
            f"CAO verification stream: {cao_stream}"
        )

        # ---------------------------------------------------------
        # Test each external encoded port
        # ---------------------------------------------------------
        for port, index in external_encoded_ports:

            self.log.stepStart(
                f"Enable audio port {port}/{index}"
            )

            self.testdsAudio.enablePort(port, index, 1)

            # -----------------------------------------------------
            # Test each application configuration
            # -----------------------------------------------------
            for config in configList:

                # =================================================
                # CAO ON
                # =================================================
                self.log.stepStart(
                    f"[{config}] Enable CAO - "
                    f"{port}/{index}"
                )

                enableResult = (
                    self.testdsAudio.setApplicationAudioConfig(
                        config,
                        True
                    )
                )

                self.log.stepResult(
                    enableResult is not False,
                    f"[{config}] CAO enabled - "
                    f"{port}/{index}"
                )

                if enableResult is False:
                    result = False
                    continue

                # -------------------------------------------------
                # Play 5.1 E-AC3
                # -------------------------------------------------
                self.log.stepStart(
                    f"[{config}] CAO ON: Play 5.1 E-AC3 - "
                    f"{port}/{index}"
                )

                self.testPlayer.play(cao_stream)

                # Allow Soundbar/audio pipeline to lock.
                time.sleep(10)

                stepResult = self.testVerifyAVRSignal(
                    port,
                    index,
                    "[CAO ON] Is the 5.1 E-AC3 audio playing "
                    "normally on the Soundbar?"
                )

                self.log.stepResult(
                    stepResult,
                    f"[{config}] 5.1 E-AC3 playback verified "
                    f"(CAO ON) - {port}/{index}"
                )

                result = result and stepResult

                # -------------------------------------------------
                # Simulate short input interruption
                #
                # NOTE:
                # testPlayer.stop() may stop the decoder completely.
                # It is therefore a manual approximation of the
                # input interruption until a player/API capable of
                # creating a real MS12 input stall is available.
                # -------------------------------------------------
                self.log.stepStart(
                    f"[{config}] CAO ON: Interrupt audio input - "
                    f"{port}/{index}"
                )

                self.testPlayer.stop()

                # Short interruption.
                time.sleep(3)

                # -------------------------------------------------
                # Resume SAME 5.1 E-AC3 stream
                # -------------------------------------------------
                self.log.stepStart(
                    f"[{config}] CAO ON: Resume 5.1 E-AC3 - "
                    f"{port}/{index}"
                )

                self.testPlayer.play(cao_stream)

                time.sleep(5)

                stepResult = self.testVerifyAVRSignal(
                    port,
                    index,
                    "[CAO ON] After the short audio interruption "
                    "and restart of the SAME 5.1 E-AC3 stream, "
                    "does audio resume WITHOUT an audible pop, "
                    "click, mute gap, or noticeable Soundbar "
                    "audio re-lock?"
                )

                self.log.stepResult(
                    stepResult,
                    f"[{config}] No audible glitch after "
                    f"E-AC3 interruption (CAO ON) - "
                    f"{port}/{index}"
                )

                result = result and stepResult

                self.testPlayer.stop()

                # =================================================
                # CAO OFF
                # =================================================
                self.log.stepStart(
                    f"[{config}] Disable CAO - "
                    f"{port}/{index}"
                )

                disableResult = (
                    self.testdsAudio.setApplicationAudioConfig(
                        config,
                        False
                    )
                )

                self.log.stepResult(
                    disableResult is not False,
                    f"[{config}] CAO disabled - "
                    f"{port}/{index}"
                )

                if disableResult is False:
                    result = False
                    continue

                # -------------------------------------------------
                # Play SAME 5.1 E-AC3 with CAO OFF
                # -------------------------------------------------
                self.log.stepStart(
                    f"[{config}] CAO OFF: Play 5.1 E-AC3 - "
                    f"{port}/{index}"
                )

                self.testPlayer.play(cao_stream)

                time.sleep(10)

                stepResult = self.testVerifyAVRSignal(
                    port,
                    index,
                    "[CAO OFF] Is the 5.1 E-AC3 audio playing "
                    "normally on the Soundbar?"
                )

                self.log.stepResult(
                    stepResult,
                    f"[{config}] 5.1 E-AC3 playback verified "
                    f"(CAO OFF) - {port}/{index}"
                )

                result = result and stepResult

                # -------------------------------------------------
                # Interrupt and resume SAME stream
                # -------------------------------------------------
                self.log.stepStart(
                    f"[{config}] CAO OFF: Interrupt and resume "
                    f"5.1 E-AC3 - {port}/{index}"
                )

                self.testPlayer.stop()

                time.sleep(3)

                self.testPlayer.play(cao_stream)

                time.sleep(5)

                stepResult = self.testVerifyAVRSignal(
                    port,
                    index,
                    "[CAO OFF] After stopping and restarting "
                    "the SAME 5.1 E-AC3 stream, does audio "
                    "resume WITHOUT an audible pop, click, "
                    "mute gap, or noticeable Soundbar "
                    "audio re-lock?"
                )

                self.log.stepResult(
                    stepResult,
                    f"[{config}] E-AC3 interruption behavior "
                    f"(CAO OFF) - {port}/{index}"
                )

                result = result and stepResult

                self.testPlayer.stop()

            # -----------------------------------------------------
            # Disable port
            # -----------------------------------------------------
            self.log.stepStart(
                f"Disable audio port {port}/{index}"
            )

            self.testdsAudio.disablePort(port, index)

        # ---------------------------------------------------------
        # Terminate
        # ---------------------------------------------------------
        self.testdsAudio.terminate()
        return result


if __name__ == '__main__':
    summerLogName = os.path.splitext(os.path.basename(__file__))[0] + "_summery"
    summeryLog = logModule(summerLogName, level=logModule.INFO)
    test = dsAudio_test27_ContinuousAudioOutput(summeryLog)
    test.run(False)