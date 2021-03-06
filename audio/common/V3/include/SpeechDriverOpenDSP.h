#ifndef ANDROID_SPEECH_DRIVER_OPEN_DSP_H
#define ANDROID_SPEECH_DRIVER_OPEN_DSP_H

#include "SpeechDriverInterface.h"

#include <AudioLock.h>

#include <arsi_type.h>



struct AurisysLibInterface;

namespace android {

class AudioMessengerIPI;

class SpeechDriverOpenDSP : public SpeechDriverInterface {
public:
    virtual         ~SpeechDriverOpenDSP();

    /**
     * lib related
     */
    int              GetRetvalSetParameter();

    status_t         SetParameter(const char *keyValuePair);
    char            *GetParameter(const char *key);


    /**
     * get instance's pointer
     */
    static SpeechDriverInterface *GetInstance(modem_index_t modem_index);


    /**
     * speech control
     */
    virtual status_t SetSpeechMode(const audio_devices_t input_device, const audio_devices_t output_devices);
    virtual status_t SpeechOn();
    virtual status_t SpeechOff();
    virtual status_t VideoTelephonyOn();
    virtual status_t VideoTelephonyOff();
    virtual status_t SpeechRouterOn();
    virtual status_t SpeechRouterOff();

    virtual status_t setMDVolumeIndex(int stream, int device, int index);

    /**
     * record control
     */
    virtual status_t RecordOn();
    virtual status_t RecordOff();
    virtual status_t RecordOn(record_type_t type_record);
    virtual status_t RecordOff(record_type_t type_record);
    virtual status_t SetPcmRecordType(record_type_t type_record);

    virtual status_t VoiceMemoRecordOn();
    virtual status_t VoiceMemoRecordOff();

    virtual uint16_t GetRecordSampleRate() const;
    virtual uint16_t GetRecordChannelNumber() const;


    /**
     * background sound control
     */
    virtual status_t BGSoundOn();
    virtual status_t BGSoundConfig(uint8_t ul_gain, uint8_t dl_gain);
    virtual status_t BGSoundOff();


    /**
     * pcm 2 way
     */
    virtual status_t PCM2WayOn(const bool wideband_on);
    virtual status_t PCM2WayOff();


    /**
     * tty ctm control
     */
    virtual status_t TtyCtmOn(tty_mode_t ttyMode);
    virtual status_t TtyCtmOff();
    virtual status_t TtyCtmDebugOn(bool tty_debug_flag);

    /**
     * rtt control
     */
    virtual int RttConfig(int rttMode);

    /**
     * acoustic loopback
     */
    virtual status_t SetAcousticLoopback(bool loopback_on);
    virtual status_t SetAcousticLoopbackBtCodec(bool enable_codec);

    virtual status_t SetAcousticLoopbackDelayFrames(int32_t delay_frames);
    virtual status_t setLpbkFlag(bool enableLpbk);

    /**
     * Modem Audio DVT and Debug
     */
    virtual status_t SetModemLoopbackPoint(uint16_t loopback_point);

    /**
     * encryption
     */
    virtual status_t SetEncryption(bool encryption_on);

    /**
     * volume control
     */
    virtual status_t SetDownlinkGain(int16_t gain);
    virtual status_t SetEnh1DownlinkGain(int16_t gain);
    virtual status_t SetUplinkGain(int16_t gain);
    virtual status_t SetDownlinkMute(bool mute_on);
    virtual status_t SetUplinkMute(bool mute_on);
    virtual status_t SetUplinkSourceMute(bool mute_on);
    virtual status_t SetSidetoneGain(int16_t gain);
    virtual status_t SetDownlinkMuteCodec(bool mute_on);


    /**
     * device related config
     */
    virtual status_t SetModemSideSamplingRate(uint16_t sample_rate);


    /**
     * speech enhancement control
     */
    virtual status_t SetSpeechEnhancement(bool enhance_on);
    virtual status_t SetSpeechEnhancementMask(const sph_enh_mask_struct_t &mask);

    virtual status_t SetBtHeadsetNrecOn(const bool bt_headset_nrec_on);


    /**
     * speech enhancement parameters setting
     */
    virtual status_t GetVibSpkParam(void *eVibSpkParam);
    virtual status_t SetVibSpkParam(void *eVibSpkParam);

    virtual status_t SetDynamicSpeechParameters(const int type, const void *param_arg);

    /**
     * check whether modem is ready.
     */
    virtual bool     CheckModemIsReady();



protected:
    SpeechDriverOpenDSP() {}
    SpeechDriverOpenDSP(modem_index_t modem_index);

    /**
     * scp phone call on/off
     */
    virtual status_t ScpSpeechOn();
    virtual status_t ScpSpeechOff();

    /**
     * recover status (speech/record/bgs/vt/p2w/tty)
     */
    virtual bool     GetScpSideSpeechStatus(const modem_status_mask_t modem_status_mask);
    virtual void     SetScpSideSpeechStatus(const modem_status_mask_t modem_status_mask);
    virtual void     ResetScpSideSpeechStatus(const modem_status_mask_t modem_status_mask);
    virtual void     RecoverModemSideStatusToInitState();


    virtual void     InitArsiTaskConfig();
    virtual void     init_lib_config();

    virtual void     SetArsiTaskConfigByDevice(
        const audio_devices_t input_device,
        const audio_devices_t output_devices);

    status_t         SetArsiSpeechParam(const int enh_mode);


    SpeechDriverInterface *pSpeechDriverInternal; // adaptor

    AudioMessengerIPI *pIPI;

    arsi_task_config_t *mArsiTaskConfig;
    arsi_lib_config_t *mArsiLibConfig;

    uint32_t         mScpSideSpeechStatus; // value |= modem_status_mask_t
    AudioLock        mScpSideSpeechStatusLock;

    uint32_t         mModemPcmSampleRate; // AFE pcm config
    uint32_t         mModemDspSampleRate; // FD216 working sample rate

    uint32_t         mModemDspChannelMask; // FD216 working channel mask
    uint8_t          mModemDspNumChannels; // FD216 working channel


    /**
     * lib related
     */
    status_t         SetParamFilePath(const char *file_path);
    char            *GetParamFilePath();
    void             createDumpFolder();

    data_buf_t      *mParamBuf;




private:
    /**
     * singleton pattern
     */
    static SpeechDriverOpenDSP *mSpeechDriverMD1;
    static SpeechDriverOpenDSP *mSpeechDriverMD2;
    static SpeechDriverOpenDSP *mSpeechDriverMDExt;
};

} // end namespace android

#endif // end of ANDROID_SPEECH_DRIVER_OPEN_DSP_H
