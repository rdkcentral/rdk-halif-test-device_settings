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
#ifndef _DS_VIDEODEVICESETTINGS_H_
#define _DS_VIDEODEVICESETTINGS_H_

#include "dsUtl.h"
#include "dsTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

//namespace  {
static const dsVideoZoom_t kSupportedDFCs[] = { dsVIDEO_ZOOM_NONE, dsVIDEO_ZOOM_FULL, dsVIDEO_ZOOM_PLATFORM};
static const dsVideoZoom_t kDefaultDFC 	   = dsVIDEO_ZOOM_FULL;

static const int kNumVideoDevices = 1;


static const dsVideoConfig_t kConfigs[]= {
		{
		/*.numSupportedDFCs = */ 		dsUTL_DIM(kSupportedDFCs), // 0 means "Info available at runtime"
		/*.supportedDFCs = */			kSupportedDFCs,
		/*.defaultDFC = */			    dsVIDEO_ZOOM_FULL,
		},
};

typedef int _SafetyCheck[(dsUTL_DIM(kConfigs) == kNumVideoDevices) ? 1 : -1];

//}
#ifdef __cplusplus
}
#endif

#endif /* RPVIDEODEVICESETTINGS_H_ */
