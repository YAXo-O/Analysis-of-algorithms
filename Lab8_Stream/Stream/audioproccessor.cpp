#include <QDebug>

#include "inputstream.h"
#include "speakers.h"
#include "audioproccessor.h"

AudioProccessor::AudioProccessor(QObject *parent) : QObject(parent), micro(nullptr), speakers(nullptr)
{
}

void AudioProccessor::setInput(InputStream *_micro)
{
    micro = _micro;
}

void AudioProccessor::setSpeakers(Speakers *_speakers)
{
    speakers = _speakers;
}

void AudioProccessor::proccess()
{
    static double x = 0;

    const qint64 maxSize = 1024;
    char data[maxSize];
    qint64 len = micro->read(data, maxSize);

    int sum = 0;
    for(int i = 0; i < len; i++)
    {
        sum += abs(data[i]);
        data[i] *= sourceFactor;
        data[i] *= generatorAmplitude*sin(x += generatorStep);
    }

    emit volumeBar(sum/len);

    if(len)
        for(int i = 0; i < len; i++)
            speakers->write(data, len);
}

void AudioProccessor::setSourceFactor(double factor)
{
    sourceFactor = factor;
}

void AudioProccessor::setGeneratorAmplitude(double amp)
{
    generatorAmplitude = amp;
}

void AudioProccessor::setGeneratorStep(double step)
{
    generatorStep = step;
}
