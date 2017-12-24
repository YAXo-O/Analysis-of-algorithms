#include <QThread>

#include "inputstream.h"
#include "speakers.h"
#include "audioproccessor.h"
#include "streammanager.h"

StreamManager::StreamManager(QObject *parent) : QObject(parent),
    mic(nullptr), speakers(nullptr), proccessor(nullptr), micThread(nullptr), speakersThread(nullptr), proccessorThread(nullptr)
{
}

StreamManager::~StreamManager()
{
    if(micThread)
    {
        micThread->terminate();
        delete micThread;
    }

    if(speakersThread)
    {
        speakersThread->terminate();
        delete speakersThread;
    }

    if(proccessorThread)
    {
        proccessorThread->terminate();
        delete proccessorThread;
    }

    if(mic)
        delete mic;
    if(speakers)
        delete speakers;
    if(proccessor)
        delete proccessor;
}

void StreamManager::start()
{
    if(mic || speakers || proccessor)
        return;

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

    mic = new InputStream(format);

    QAudioDeviceInfo infoOut(QAudioDeviceInfo::defaultOutputDevice());
    if (!infoOut.isFormatSupported(format))
        format = infoOut.nearestFormat(format);

    speakers = new Speakers(format);


    micThread = new QThread;
    speakersThread = new QThread;

    mic->moveToThread(micThread);
    speakers->moveToThread(speakersThread);

    proccessor = new AudioProccessor;
    proccessorThread = new QThread;
    proccessor->moveToThread(proccessorThread);
    proccessor->setInput(mic);
    proccessor->setSpeakers(speakers);
    proccessor->setGeneratorAmplitude(1);
    proccessor->setGeneratorStep(.2);
    proccessor->setSourceFactor(1);

    connect(this, SIGNAL(generatorAmplitudeChanged(double)), proccessor, SLOT(setGeneratorAmplitude(double)));
    connect(this, SIGNAL(generatorStepChanged(double)), proccessor, SLOT(setGeneratorStep(double)));
    connect(this, SIGNAL(sourceVolumeChanged(double)), proccessor, SLOT(setSourceFactor(double)));
    connect(proccessor, SIGNAL(volumeBar(int)), this, SIGNAL(volumeBar(int)));

    connect(mic, SIGNAL(dataAvailable()), proccessor, SLOT(proccess()));
    connect(micThread, SIGNAL(started()), mic, SLOT(start()));
    connect(speakersThread, SIGNAL(started()), speakers, SLOT(start()));

    micThread->start();
    speakersThread->start();
    proccessorThread->start();
}
