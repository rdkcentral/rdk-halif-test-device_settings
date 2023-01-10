#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "dsAudio.h"


dsError_t dsAudioPortInit(void)
{
  /*TODO: Implement Me!*/
  return (dsError_t)0;
}

dsError_t dsGetAudioPort(dsAudioPortType_t type, int index, int* handle)
{
  /*TODO: Implement Me!*/
  (void)type;
  (void)index;
  (void)handle;
  return (dsError_t)0;
}

dsError_t dsGetAudioEncoding(int handle, dsAudioEncoding_t* encoding)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)encoding;
  return (dsError_t)0;
}

dsError_t dsGetAudioFormat(int handle, dsAudioFormat_t* audioFormat)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)audioFormat;
  return (dsError_t)0;
}

dsError_t dsGetAudioCompression(int handle, int* compression)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)compression;
  return (dsError_t)0;
}

dsError_t dsGetDialogEnhancement(int handle, int* level)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)level;
  return (dsError_t)0;
}

dsError_t dsGetDolbyVolumeMode(int handle, bool* mode)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)mode;
  return (dsError_t)0;
}

dsError_t dsGetIntelligentEqualizerMode(int handle, int* mode)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)mode;
  return (dsError_t)0;
}

dsError_t dsGetVolumeLeveller(int handle, dsVolumeLeveller_t* volLeveller)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)volLeveller;
  return (dsError_t)0;
}

dsError_t dsGetBassEnhancer(int handle, int* boost)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)boost;
  return (dsError_t)0;
}

dsError_t dsIsSurroundDecoderEnabled(int handle, bool* enabled)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)enabled;
  return (dsError_t)0;
}

dsError_t dsGetDRCMode(int handle, int* mode)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)mode;
  return (dsError_t)0;
}

dsError_t dsGetSurroundVirtualizer(int handle, dsSurroundVirtualizer_t* virtualizer)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)virtualizer;
  return (dsError_t)0;
}

dsError_t dsGetMISteering(int handle, bool* enabled)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)enabled;
  return (dsError_t)0;
}

dsError_t dsGetGraphicEqualizerMode(int handle, int* mode)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)mode;
  return (dsError_t)0;
}

dsError_t dsGetMS12AudioProfileList(int handle, dsMS12AudioProfileList_t* profiles)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)profiles;
  return (dsError_t)0;
}

dsError_t dsGetMS12AudioProfile(int handle, char* profile)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)profile;
  return (dsError_t)0;
}

dsError_t dsGetSupportedARCTypes(int handle, int* types)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)types;
  return (dsError_t)0;
}

dsError_t dsAudioSetSAD(int handle, dsAudioSADList_t sad_list)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)sad_list;
  return (dsError_t)0;
}

dsError_t dsAudioEnableARC(int handle, dsAudioARCStatus_t arcStatus)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)arcStatus;
  return (dsError_t)0;
}

dsError_t dsGetStereoMode(int handle, dsAudioStereoMode_t* stereoMode)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)stereoMode;
  return (dsError_t)0;
}

dsError_t dsGetStereoAuto(int handle, int* autoMode)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)autoMode;
  return (dsError_t)0;
}

dsError_t dsGetAudioGain(int handle, float* gain)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)gain;
  return (dsError_t)0;
}

dsError_t dsGetAudioDB(int handle, float* db)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)db;
  return (dsError_t)0;
}

dsError_t dsGetAudioLevel(int handle, float* level)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)level;
  return (dsError_t)0;
}

dsError_t dsGetAudioMaxDB(int handle, float* maxDb)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)maxDb;
  return (dsError_t)0;
}

dsError_t dsGetAudioMinDB(int handle, float* minDb)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)minDb;
  return (dsError_t)0;
}

dsError_t dsGetAudioOptimalLevel(int handle, float* optimalLevel)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)optimalLevel;
  return (dsError_t)0;
}

dsError_t dsGetAudioDelay(int handle, uint32_t* audioDelayMs)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)audioDelayMs;
  return (dsError_t)0;
}

dsError_t dsGetAudioDelayOffset(int handle, uint32_t* audioDelayOffsetMs)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)audioDelayOffsetMs;
  return (dsError_t)0;
}

dsError_t dsSetAudioAtmosOutputMode(int handle, bool enable)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)enable;
  return (dsError_t)0;
}

dsError_t dsGetSinkDeviceAtmosCapability(int handle, dsATMOSCapability_t* capability)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)capability;
  return (dsError_t)0;
}

dsError_t dsIsAudioLoopThru(int handle, bool* loopThru)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)loopThru;
  return (dsError_t)0;
}

dsError_t dsIsAudioMute(int handle, bool* muted)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)muted;
  return (dsError_t)0;
}

dsError_t dsIsAudioPortEnabled(int handle, bool* enabled)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)enabled;
  return (dsError_t)0;
}

dsError_t dsEnableAudioPort(int handle, bool enabled)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)enabled;
  return (dsError_t)0;
}

dsError_t dsEnableMS12Config(int handle, dsMS12FEATURE_t feature, const bool enable)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)feature;
  (void)enable;
  return (dsError_t)0;
}

dsError_t dsEnableLEConfig(int handle, const bool enable)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)enable;
  return (dsError_t)0;
}

dsError_t dsGetLEConfig(int handle, bool* enable)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)enable;
  return (dsError_t)0;
}

dsError_t dsSetAudioEncoding(int handle, dsAudioEncoding_t encoding)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)encoding;
  return (dsError_t)0;
}

dsError_t dsSetAudioCompression(int handle, int compression)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)compression;
  return (dsError_t)0;
}

dsError_t dsSetDialogEnhancement(int handle, int level)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)level;
  return (dsError_t)0;
}

dsError_t dsSetDolbyVolumeMode(int handle, bool mode)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)mode;
  return (dsError_t)0;
}

dsError_t dsSetIntelligentEqualizerMode(int handle, int mode)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)mode;
  return (dsError_t)0;
}

dsError_t dsSetVolumeLeveller(int handle, dsVolumeLeveller_t volLeveller)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)volLeveller;
  return (dsError_t)0;
}

dsError_t dsSetBassEnhancer(int handle, int boost)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)boost;
  return (dsError_t)0;
}

dsError_t dsEnableSurroundDecoder(int handle, bool enabled)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)enabled;
  return (dsError_t)0;
}

dsError_t dsSetDRCMode(int handle, int mode)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)mode;
  return (dsError_t)0;
}

dsError_t dsSetSurroundVirtualizer(int handle, dsSurroundVirtualizer_t virtualizer)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)virtualizer;
  return (dsError_t)0;
}

dsError_t dsSetMISteering(int handle, bool enabled)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)enabled;
  return (dsError_t)0;
}

dsError_t dsSetGraphicEqualizerMode(int handle, int mode)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)mode;
  return (dsError_t)0;
}

dsError_t dsSetMS12AudioProfile(int handle, const char* profile)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)profile;
  return (dsError_t)0;
}

dsError_t dsSetStereoMode(int handle, dsAudioStereoMode_t mode)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)mode;
  return (dsError_t)0;
}

dsError_t dsSetStereoAuto(int handle, int autoMode)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)autoMode;
  return (dsError_t)0;
}

dsError_t dsSetAudioGain(int handle, float gain)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)gain;
  return (dsError_t)0;
}

dsError_t dsSetAudioDB(int handle, float db)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)db;
  return (dsError_t)0;
}

dsError_t dsSetAudioLevel(int handle, float level)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)level;
  return (dsError_t)0;
}

dsError_t dsSetAudioDucking(int handle, dsAudioDuckingAction_t action, dsAudioDuckingType_t cmock_arg1, const unsigned char level)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)action;
  (void)cmock_arg1;
  (void)level;
  return (dsError_t)0;
}

dsError_t dsEnableLoopThru(int handle, bool loopThru)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)loopThru;
  return (dsError_t)0;
}

dsError_t dsSetAudioMute(int handle, bool mute)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)mute;
  return (dsError_t)0;
}

dsError_t dsIsAudioMSDecode(int handle, bool* HasMS11Decode)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)HasMS11Decode;
  return (dsError_t)0;
}

dsError_t dsIsAudioMS12Decode(int handle, bool* HasMS12Decode)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)HasMS12Decode;
  return (dsError_t)0;
}

dsError_t dsSetAudioDelay(int handle, const uint32_t audioDelayMs)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)audioDelayMs;
  return (dsError_t)0;
}

dsError_t dsSetAudioDelayOffset(int handle, const uint32_t audioDelayOffsetMs)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)audioDelayOffsetMs;
  return (dsError_t)0;
}

dsError_t dsAudioPortTerm(void)
{
  /*TODO: Implement Me!*/
  return (dsError_t)0;
}

dsError_t dsAudioOutIsConnected(int handle, bool* pisCon)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)pisCon;
  return (dsError_t)0;
}

dsError_t dsAudioOutRegisterConnectCB(dsAudioOutPortConnectCB_t CBFunc)
{
  /*TODO: Implement Me!*/
  (void)CBFunc;
  return (dsError_t)0;
}

dsError_t dsAudioFormatUpdateRegisterCB(dsAudioFormatUpdateCB_t cbFun)
{
  /*TODO: Implement Me!*/
  (void)cbFun;
  return (dsError_t)0;
}

dsError_t dsGetAudioCapabilities(int handle, int* capabilities)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)capabilities;
  return (dsError_t)0;
}

dsError_t dsGetMS12Capabilities(int handle, int* capabilities)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)capabilities;
  return (dsError_t)0;
}

dsError_t dsResetDialogEnhancement(int handle)
{
  /*TODO: Implement Me!*/
  (void)handle;
  return (dsError_t)0;
}

dsError_t dsResetBassEnhancer(int handle)
{
  /*TODO: Implement Me!*/
  (void)handle;
  return (dsError_t)0;
}

dsError_t dsResetSurroundVirtualizer(int handle)
{
  /*TODO: Implement Me!*/
  (void)handle;
  return (dsError_t)0;
}

dsError_t dsResetVolumeLeveller(int handle)
{
  /*TODO: Implement Me!*/
  (void)handle;
  return (dsError_t)0;
}

dsError_t dsSetMS12AudioProfileSetttingsOverride(int handle, const char* profileState, const char* profileName, const char* profileSettingsName, const char* profileSettingValue)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)profileState;
  (void)profileName;
  (void)profileSettingsName;
  (void)profileSettingValue;
  return (dsError_t)0;
}

dsError_t dsSetAssociatedAudioMixing(int handle, bool mixing)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)mixing;
  return (dsError_t)0;
}

dsError_t dsGetAssociatedAudioMixing(int handle, bool* mixing)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)mixing;
  return (dsError_t)0;
}

dsError_t dsSetFaderControl(int handle, int mixerbalance)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)mixerbalance;
  return (dsError_t)0;
}

dsError_t dsGetFaderControl(int handle, int* mixerbalance)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)mixerbalance;
  return (dsError_t)0;
}

dsError_t dsSetPrimaryLanguage(int handle, const char* pLang)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)pLang;
  return (dsError_t)0;
}

dsError_t dsGetPrimaryLanguage(int handle, char* pLang)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)pLang;
  return (dsError_t)0;
}

dsError_t dsSetSecondaryLanguage(int handle, const char* sLang)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)sLang;
  return (dsError_t)0;
}

dsError_t dsGetSecondaryLanguage(int handle, char* sLang)
{
  /*TODO: Implement Me!*/
  (void)handle;
  (void)sLang;
  return (dsError_t)0;
}

dsError_t dsGetHDMIARCPortId(int* portId)
{
  /*TODO: Implement Me!*/
  (void)portId;
  return (dsError_t)0;
}

