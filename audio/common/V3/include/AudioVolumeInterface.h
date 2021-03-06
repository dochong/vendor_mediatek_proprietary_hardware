#ifndef ANDROID_AUDIO_VOLUME_INTERFACE_H
#define ANDROID_AUDIO_VOLUME_INTERFACE_H

#include "AudioType.h"
#include <system/audio.h>
#include <utils/Errors.h>
#include <utils/Vector.h>
#include <utils/String16.h>
#include <utils/String8.h>

//!  A AudioVolumeInterface interface
/*!
  this class is hold for volume controlb base on mode and device.
  need to take care both input and output volume.
*/

class AudioVolumeInterface {
public:
    /**
    * virtual destrutor
    */
    virtual ~AudioVolumeInterface() {};

    /**
    * check volume control init done.
    * @return status_t
    */
    virtual status_t    initCheck() = 0;

    /**
    *  volume controller init funciton
    * @return status_t
    */
    virtual status_t    initVolumeController() = 0;

    /**
    *  volume controller setMasterVolume, usually set master volume is by setting analog gain,
    * @param v
    * @param mode
    * @param routes
    * @return status_t
    */
    virtual status_t setMasterVolume(float v, audio_mode_t mode, uint32_t devices) = 0 ;

    /**
    *  volume controller GetMasterVolume
    * @return mastervolume
    */
    virtual float getMasterVolume() = 0 ;

    /**
    *  volume controller setVoiceVolume, usually set voice volume is use by incall mode
    * @param v
    * @param mode
    * @param routes
    * @return status_t
    */
    virtual status_t setVoiceVolume(float v, audio_mode_t mode, uint32_t devices) = 0 ;
    virtual status_t setVoiceVolume(int MapVolume, uint32_t device) = 0;
    virtual status_t ApplyVoiceGain(int degradeDb, audio_mode_t mode, uint32_t device) = 0;

    /**
    *  volume controller getVoiceVolume
    * @return VoiceVolume
    */
    virtual float getVoiceVolume(void) = 0;

    /**
    *  volume controller setStreamVolume, this function basicaaly use for FM or MATV
    * which need set volume by hardware, diogital is set by audiopolicymanager.
    * @param stream
    * @param v
    * @return status_t
    */
    virtual status_t setStreamVolume(int stream, float v) = 0 ;

    /**
    *  volume controller setStreamMute
    * @param stream
    * @param mute
    * @return status_t
    */
    virtual status_t setStreamMute(int stream, bool mute) = 0 ;

    /**
    *  volume controller getStreamVolume
    * @param stream
    * @return status_t
    */
    virtual float getStreamVolume(int stream) = 0;

    /**
    *  volume controller setFmVolume
    * Set FM playback volume
    * @param volume
    * @return bool
    */
    virtual status_t setFmVolume(const float volume) = 0;

    /**
    *  Audio Tuning tool set playback gain
    */
    virtual int ApplyAudioGainTuning(int Gain, uint32_t mode, uint32_t device) = 0;

    /**
    * volume controller SetSideTone
    * base on mode gain and route to decide sidetone gain
    * @param Mode
    * @param Gain
    * @param routes
    * @return status_t
    */
    virtual status_t SetSideTone(uint32_t Mode, uint32_t gain) = 0 ;

    /**
      * volume controller GetSideToneGain
      * base on output device get sidetone gain
      * @param device
      * @return gain
      */
    virtual uint32_t GetSideToneGain(uint32_t device) = 0 ;

    /**
    * volume controller SetMicGain
    * base on mode gain and route to decide sidetone gain
    * @param Mode
    * @param Gain
    * @param routes
    * @return status_t
    */
    virtual status_t SetMicGain(uint32_t Mode, uint32_t gain) = 0 ;

    /**
    * volume controller SetULTotalGain
    * base on mode and gain
    * @param Mode
    * @param Gain
    * @return status_t
    */
    virtual status_t SetULTotalGain(uint32_t Mode, unsigned char Volume) = 0 ;

    /**
    * volume controller ApplyMicGain
    * base on mode gain and MicType to decide mic gain
    * @param MicType
    * @param Mode
    */
    virtual status_t ApplyMicGain(uint32_t MicType, int mode) = 0 ;

    /**
    * volume controller SetCaptureGain
    * base on mode gain and MicType to decide mic gain
    * @param Mode
    * @param Input Source
    * @param Input device
    * @param Output devices
    */
    virtual status_t SetCaptureGain(audio_mode_t mode, audio_source_t source, audio_devices_t input_device, audio_devices_t output_devices) = 0 ;

    /**
    * volume controller SetDigitalHwGain
    * base on mode gain and route to decide sidetone GAIN_MUTE
    * @param Mode
    * @param Gain
    * @param routes
    * @return status_t
    */
    virtual status_t SetDigitalHwGain(uint32_t Mode, uint32_t Gain, uint32_t devices) = 0 ;

    /**
    *  volume controller GetSWMICGain
    * get MIC software digital gain for HD record library
    */
    virtual uint8_t GetSWMICGain(void) = 0 ;

    /**
    *  volume controller GetULTotalGain
    * get MIC software digital gain for BesRecord library
    */
    virtual uint8_t GetULTotalGain(void) = 0 ;


    /**
    * volume controller Set modem DL gain
    * @param Gain
    * @return status_t
    */
    virtual void ApplyMdDlGain(int  Gain) = 0 ;


    /**
    * volume controller Set modem DL Ehn gain
    * @param Gain
    * @return status_t
    */
    virtual void ApplyMdDlEhn1Gain(int Gain) = 0 ;

    /**
    * volume controller Set modem Ul gain
    * @param Gain
    * @return status_t
    */
    virtual void ApplyMdUlGain(int  Gain) = 0 ;

    /**
    * volume controller map volume to digital gain
    * @param Gain
    * @return digital gain
    */
    virtual uint16_t MappingToDigitalGain(unsigned char Gain) = 0 ;

    /**
    * volume controller map volume to PGA gain
    * @param Gain
    * @return PGA gain
    */
    virtual uint16_t MappingToPGAGain(unsigned char Gain) = 0 ;

    /**
    * volume controller SetMicGainTuning
    * base on mode gain and route to decide sidetone gain
    * @param Mode
    * @param Gain
    * @param routes
    * @return status_t
    */
    virtual status_t SetMicGainTuning(uint32_t Mode, uint32_t gain) = 0 ;

    virtual status_t ApplySideTone(uint32_t Mode) = 0 ;
    // alsa driver set pga gain function
    virtual void SetReceiverGain(int DrgradeDb) = 0 ;
    virtual void SetHeadPhoneRGain(int DrgradeDb) = 0 ;
    virtual void SetHeadPhoneLGain(int DrgradeDb) = 0 ;
    virtual void SetLinoutRGain(int DrgradeDb) = 0 ;
    virtual void SetLinoutLGain(int DrgradeDb) = 0 ;
    virtual void SetSpeakerGain(int DegradedBGain) = 0 ;
    virtual uint32_t GetOffloadGain(float vol_f) = 0;

#ifdef MTK_AUDIO_GAIN_TABLE
    virtual status_t setAnalogVolume(int stream, int device, int index, audio_mode_t mode) = 0;
    virtual status_t speechNetworkChange(unsigned int info) = 0;
    virtual bool isNbSpeechBand(void) = 0;
    virtual status_t setBtVolumeCapability(bool support) = 0;
    virtual void setAudioBufferGain(int gain) = 0;
#else
    virtual void setAudioBufferGain(int gain __unused) {};
#endif
};

#endif
