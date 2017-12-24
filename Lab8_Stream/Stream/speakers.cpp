#include "speakers.h"

Speakers::Speakers(QObject *parent) : QObject(parent),
    speakers(nullptr), speakersDevice(nullptr)
{
    QAudioFormat format;

    format.setSampleRate(8000);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setSampleType(QAudioFormat::UnSignedInt);
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setCodec("audio/pcm");

    QAudioDeviceInfo infoOut(QAudioDeviceInfo::defaultOutputDevice());
    if (!infoOut.isFormatSupported(format))
        format = infoOut.nearestFormat(format);

    speakers = new QAudioOutput(format, this);
}

Speakers::Speakers(const QAudioFormat &format, QObject *parent): QObject(parent)
{
    speakers = new QAudioOutput(format, this);
}

qint64 Speakers::write(const char *data, qint64 len)
{
    return speakersDevice->write(data, len);
}

void Speakers::start()
{
    speakersDevice = speakers->start();
}
