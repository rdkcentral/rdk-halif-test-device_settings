/*
* If not stated otherwise in this file or this component's LICENSE file the
* following copyright and licenses apply:
*
* Copyright 2022 Sky UK
* Copyright 2022 Amlogic
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
#ifndef _DS_VIDEOOUTPUTPORTSETTINGS_H_
#define _DS_VIDEOOUTPUTPORTSETTINGS_H_

#include "dsTypes.h"
#include "dsUtl.h"
#include "dsVideoResolutionSettings.h"


#ifdef __cplusplus
extern "C" {
namespace {
#endif

/*
 * Setup the supported configurations here.
 */
static const dsVideoPortType_t kSupportedPortTypes[] = { dsVIDEOPORT_TYPE_INTERNAL };

static const dsVideoPortTypeConfig_t kConfigs[]= {
		{
		/*.typeId = */					dsVIDEOPORT_TYPE_INTERNAL,
		/*.name = */ 					"INTERNAL",
		/*.dtcpSupported = */			false,
		/*.hdcpSupported = */			true,
		/*.restrictedResollution = */	-1,
		/*.numSupportedResolutions = */ dsUTL_DIM(kResolutions), // 0 means "Info available at runtime"
		/*.supportedResolutons = */     kResolutions,
		},
};

static const dsVideoPortPortConfig_t kPorts[] = {

#ifdef  HAS_SPDIF_SUPPORT
        {
                /*.typeId = */                                  {dsVIDEOPORT_TYPE_INTERNAL, 0},
                /*.connectedAOP */              {dsAUDIOPORT_TYPE_SPDIF, 0},
                /*.defaultResolution = */               "1080i50"
        },
#endif
#ifdef  HAS_HEADPHONE_SUPPORT
        {

                /*.typeId = */                                  {dsVIDEOPORT_TYPE_INTERNAL, 0},
                /*.connectedAOP */              {dsAUDIOPORT_TYPE_HEADPHONE, 0},
                /*.defaultResolution = */               "1080i50"
        },
#endif

        {
                /*.typeId = */                                  {dsVIDEOPORT_TYPE_INTERNAL, 0},
                /* connectedAOP */             {dsAUDIOPORT_TYPE_SPEAKER, 0},
                /*.defaultResolution = */               "1080i50"
        },
        {
                /*.typeId = */                                  {dsVIDEOPORT_TYPE_INTERNAL, 0},
                /*.connectedAOP */              {dsAUDIOPORT_TYPE_HDMI_ARC, 0},
                /*.defaultResolution = */               "1080i50"
        },

};



#ifdef __cplusplus
  } 
}
#endif


#endif /* VIDEOOUTPUTPORTSETTINGS_H_ */
