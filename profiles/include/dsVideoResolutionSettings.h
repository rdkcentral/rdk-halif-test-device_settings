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
#ifndef _DS_VIDEORESOLUTIONSETTINGS_H_
#define _DS_VIDEORESOLUTIONSETTINGS_H_

#include "dsTypes.h"

#ifdef __cplusplus
extern "C" {
namespace {
#endif


#define  _INTERLACED true
#define _PROGRESSIVE false

#define dsVideoPortRESOLUTION_NUMMAX 32

static dsVideoPortResolution_t invalid_kRes[] = {
		{   /*480i*/
			/*.name = */					"480i",
			/*.pixelResolution = */			dsVIDEO_PIXELRES_720x480,
			/*.aspectRatio = */				dsVIDEO_ASPECT_RATIO_4x3,
			/*.stereoscopicMode = */		dsVIDEO_SSMODE_2D,
			/*.frameRate = */				dsVIDEO_FRAMERATE_29dot97,
			/*.interlaced = */				_INTERLACED,
		}
};
/* List all supported resolutions here */

static dsVideoPortResolution_t kResolutions[] = {
		{   /*480i*/
			/*.name = */					"480i",
			/*.pixelResolution = */			dsVIDEO_PIXELRES_720x480,
			/*.aspectRatio = */				dsVIDEO_ASPECT_RATIO_4x3,
			/*.stereoscopicMode = */		dsVIDEO_SSMODE_2D,
			/*.frameRate = */				dsVIDEO_FRAMERATE_29dot97,
			/*.interlaced = */				_INTERLACED,
		},
		{   /*480p*/
			/*.name = */					"480p",
			/*.pixelResolution = */			dsVIDEO_PIXELRES_720x480,
			/*.aspectRatio = */				dsVIDEO_ASPECT_RATIO_4x3,
			/*.stereoscopicMode = */		dsVIDEO_SSMODE_2D,
			/*.frameRate = */				dsVIDEO_FRAMERATE_59dot94,
			/*.interlaced = */				_PROGRESSIVE,
		},
		{   /*576p*/
			/*.name = */					"576p50",
			/*.pixelResolution = */			dsVIDEO_PIXELRES_720x576,
			/*.aspectRatio = */				dsVIDEO_ASPECT_RATIO_4x3,
			/*.stereoscopicMode = */		dsVIDEO_SSMODE_2D,
			/*.frameRate = */				dsVIDEO_FRAMERATE_50,
			/*.interlaced = */				_PROGRESSIVE,
		},
		{   /*720p - Default - AutoSelect */
			/*.name = */					"720p",
			/*.pixelResolution = */			dsVIDEO_PIXELRES_1280x720,
			/*.aspectRatio = */				dsVIDEO_ASPECT_RATIO_16x9,
			/*.stereoscopicMode = */		dsVIDEO_SSMODE_2D,
			/*.frameRate = */				dsVIDEO_FRAMERATE_59dot94,
			/*.interlaced = */				_PROGRESSIVE,
		},
		{   /*720p - Default - AutoSelect */
			/*.name = */					"720p50",
			/*.pixelResolution = */			dsVIDEO_PIXELRES_1280x720,
			/*.aspectRatio = */				dsVIDEO_ASPECT_RATIO_16x9,
			/*.stereoscopicMode = */		dsVIDEO_SSMODE_2D,
			/*.frameRate = */				dsVIDEO_FRAMERATE_50,
			/*.interlaced = */				_PROGRESSIVE,
		},
		{   /*768p60 - Default - AutoSelect */
			/*.name = */                    		"768p60",
			/*.pixelResolution = */         	dsVIDEO_PIXELRES_1366x768,
			/*.aspectRatio = */             	dsVIDEO_ASPECT_RATIO_16x9,
			/*.stereoscopicMode = */        	dsVIDEO_SSMODE_2D,
			/*.frameRate = */               	dsVIDEO_FRAMERATE_59dot94,
			/*.interlaced = */              	_PROGRESSIVE,
		},
		{   /*1080p24*/
			/*.name = */					"1080p24",
			/*.pixelResolution = */			dsVIDEO_PIXELRES_1920x1080,
			/*.aspectRatio = */				dsVIDEO_ASPECT_RATIO_16x9,
			/*.stereoscopicMode = */		dsVIDEO_SSMODE_2D,
			/*.frameRate = */				dsVIDEO_FRAMERATE_24,
			/*.interlaced = */				_PROGRESSIVE,
		},
		{   /*1080p60*/
			/*.name = */					"1080p",
			/*.pixelResolution = */			dsVIDEO_PIXELRES_1920x1080,
			/*.aspectRatio = */				dsVIDEO_ASPECT_RATIO_16x9,
			/*.stereoscopicMode = */		dsVIDEO_SSMODE_2D,
			/*.frameRate = */				dsVIDEO_FRAMERATE_59dot94,
			/*.interlaced = */				_PROGRESSIVE,
		},
		{   /*1080i*/
			/*.name = */					"1080i50",
			/*.pixelResolution = */			dsVIDEO_PIXELRES_1920x1080,
			/*.aspectRatio = */				dsVIDEO_ASPECT_RATIO_16x9,
			/*.stereoscopicMode = */		dsVIDEO_SSMODE_2D,
			/*.frameRate = */				dsVIDEO_FRAMERATE_50,
			/*.interlaced = */				_INTERLACED,
		},
		{   /*1080p30*/
			/*.name = */					"1080i",
			/*.pixelResolution = */			dsVIDEO_PIXELRES_1920x1080,
			/*.aspectRatio = */				dsVIDEO_ASPECT_RATIO_16x9,
			/*.stereoscopicMode = */		dsVIDEO_SSMODE_2D,
			/*.frameRate = */				dsVIDEO_FRAMERATE_59dot94,
			/*.interlaced = */				_INTERLACED,
		},
#ifdef HAS_4K_SUPPORT
                {   /*2160p30*/
                        /*.name = */                                    "2160p30",
                        /*.pixelResolution = */                 dsVIDEO_PIXELRES_3840x2160,
                        /*.aspectRatio = */                     dsVIDEO_ASPECT_RATIO_16x9,
                        /*.stereoscopicMode = */                dsVIDEO_SSMODE_2D,
                        /*.frameRate = */                       dsVIDEO_FRAMERATE_30,
                        /*.interlaced = */                      _PROGRESSIVE,
                },
                {   /*2160p60*/
                        /*.name = */                                    "2160p60",
                        /*.pixelResolution = */                 dsVIDEO_PIXELRES_3840x2160,
                        /*.aspectRatio = */                     dsVIDEO_ASPECT_RATIO_16x9,
                        /*.stereoscopicMode = */                dsVIDEO_SSMODE_2D,
                        /*.frameRate = */                       dsVIDEO_FRAMERATE_59dot94,
                        /*.interlaced = */                      _PROGRESSIVE,
                },
#endif
};

static const int kDefaultResIndex = 7; //Pick one resolution from kResolutions[] as default

#ifdef __cplusplus
}
}
#endif

#endif /* VIDEORESOLUTIONSETTINGS_H_ */
