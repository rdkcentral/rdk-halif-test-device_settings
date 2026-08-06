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

    def testVerifyAVRSignal(self, port, config, prompt):
        return self.testUserResponse.getUserYN(
            f"[{port}][Config:{config}] {prompt} (Y/N):"
        )

    def testFunction(self):
        result = True

        self.testdsAudio.initialise(self.testdsAudio.getDeviceType())

        self.log.stepStart('Query Application Audio Config List')
        configList = self.testdsAudio.getApplicationAudioConfigList()
        self.log.stepResult(
            len(configList) > 0,
            f'Supported application audio configs: {configList}'
        )

        if not configList:
            self.testdsAudio.terminate()
            return True

        for port, index in self.testdsAudio.getSupportedPorts():
            self.testdsAudio.enablePort(port, index)

            for config in configList:
                self.testdsAudio.setApplicationAudioConfig(config, True)

                self.log.stepStart(
                    f'[{config}] Enable CAO, play AC3 to lock AVR clock - {port}/{index}')
                self.testPlayer.play(self.testStreams[0])
                self.testPlayer.stop()

                stepResult = self.testVerifyAVRSignal(
                    port, config,
                    'With CAO enabled and NO stream playing, does the connected '
                    'AVR/Soundbar still display an active DDP/MAT 5.1 (or encoded) signal?'
                )
                self.log.stepResult(
                    stepResult,
                    f'[{config}] AVR shows encoded signal during silence (CAO ON) - {port}/{index}'
                )
                result = result and stepResult

                self.log.stepStart(
                    f'[{config}] AC3->EAC3 transition with CAO enabled - {port}/{index}')
                self.testPlayer.play(self.testStreams[1])

                stepResult = self.testVerifyAVRSignal(
                    port, config,
                    'Did the EAC3 stream start WITHOUT any audible pop, click, or mute gap?'
                )
                self.log.stepResult(
                    stepResult,
                    f'[{config}] No glitch on AC3->EAC3 transition (CAO ON) - {port}/{index}'
                )
                result = result and stepResult

                self.testPlayer.stop()

                self.testdsAudio.setApplicationAudioConfig(config, False)

                self.log.stepStart(
                    f'[{config}] Disable CAO, play AC3 then stop - {port}/{index}')
                self.testPlayer.play(self.testStreams[0])
                self.testPlayer.stop()

                stepResult = self.testVerifyAVRSignal(
                    port, config,
                    'With CAO disabled and NO stream playing, has the AVR/Soundbar '
                    'signal dropped (showing no audio, PCM 2.0, or no channel info)?'
                )
                self.log.stepResult(
                    stepResult,
                    f'[{config}] AVR signal dropped during silence (CAO OFF) - {port}/{index}'
                )
                result = result and stepResult

            self.testdsAudio.disablePort(port, index)

        self.testdsAudio.terminate()
        return result


if __name__ == '__main__':
    summerLogName = os.path.splitext(os.path.basename(__file__))[0] + "_summery"
    summeryLog = logModule(summerLogName, level=logModule.INFO)
    test = dsAudio_test27_ContinuousAudioOutput(summeryLog)
    test.run(False)