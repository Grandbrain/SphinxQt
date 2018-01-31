#ifndef RECOGNITION_H
#define RECOGNITION_H

#include <QString>
#include <sphinxbase/ad.h>
#include <pocketsphinx.h>

class Recognition
{
public:
    explicit Recognition();
    virtual ~Recognition();

    bool Initialize(const QString&, const QString&, const QString&, const QString&, int);
    bool IsInitialized() const;
    QString Recognize();
    void Destroy();


protected:
    ps_decoder_t* mDecoder;
    ad_rec_t* mDevice;
};

#endif