#include "recognition.h"

Recognition::Recognition() : mDecoder(nullptr), mDevice(nullptr)
{

}

Recognition::~Recognition()
{
    if(mDecoder || mDevice) Destroy();
}

bool Recognition::Initialize(const QString& audioModelPath,
                             const QString& langModelFile,
                             const QString& dictionary,
                             const QString& deviceName,
                             int sampleRate)
{
    cmd_ln_t* config = cmd_ln_init(nullptr, ps_args(), true,
                "-hmm" , audioModelPath.toUtf8().constData(),
                "-jsgf", langModelFile.toUtf8().constData(),
                "-dict", dictionary.toUtf8().constData(),
                "-vad_threshold", "3.0",
                "-remove_noise" , "yes",
                nullptr);

    if(!config) return false;

    mDecoder = ps_init(config);
    cmd_ln_free_r(config);
    if(!mDecoder) return false;

    mDevice = ad_open_dev(deviceName.toUtf8().constData(), sampleRate);
    if(!mDevice)
    {
        if(mDecoder) ps_free(mDecoder);
        return false;
    }

    return true;
}

bool Recognition::IsInitialized() const
{
    return (mDecoder && mDevice) ? true : false;
}

QString Recognition::Recognize()
{
    bool uttStarted = false;
    const char* data = nullptr;
    int16 buffer[4096];

    if(ad_start_rec(mDevice) >= 0 && ps_start_utt(mDecoder) >= 0)
    {
        while(true)
        {
            int32 numberSamples = ad_read(mDevice, buffer, 4096);
            if(ps_process_raw(mDecoder, buffer, numberSamples, 0, 0) < 0) break;
            bool inSpeech = (ps_get_in_speech(mDecoder) > 0) ? true : false;
            if(inSpeech && !uttStarted) uttStarted = true;
            if(!inSpeech && uttStarted)
            {
                ps_end_utt(mDecoder);
                ad_stop_rec(mDevice);
                data = ps_get_hyp(mDecoder, nullptr);
                break;
            }
        }
        if(data) return QString(data);
    }
    ps_end_utt(mDecoder);
    ad_stop_rec(mDevice);
    return QString();
}

void Recognition::Destroy()
{
    if(mDevice) ad_close(mDevice);
    if(mDecoder) ps_free(mDecoder);

    mDevice = nullptr;
    mDecoder = nullptr;
}