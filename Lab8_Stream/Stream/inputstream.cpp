#include "inputstream.h"

InputStream::InputStream(QObject *parent) : QObject(parent)
{
    QAudioFormat format;

    format.setSampleRate(8000);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setSampleType(QAudioFormat::UnSignedInt );
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setCodec("audio/pcm");

    QAudioDeviceInfo infoIn(QAudioDeviceInfo::defaultInputDevice());
    if (!infoIn.isFormatSupported(format))
        format = infoIn.nearestFormat(format);

    mic = new QAudioInput(format, this);
}

InputStream::InputStream(const QAudioFormat &format, QObject *parent): QObject(parent)
{
    mic = new QAudioInput(format, this);
}

qint64 InputStream::read(char *data, qint64 maxLen)
{
    return micDevice->read(data, maxLen);
}

void InputStream::start()
{
    micDevice = mic->start();

    connect(micDevice, SIGNAL(readyRead()), SIGNAL(dataAvailable()));
}
