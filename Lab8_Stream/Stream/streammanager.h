#ifndef STREAMMANAGER_H
#define STREAMMANAGER_H

#include <QObject>

class InputStream;
class Speakers;
class AudioProccessor;

class StreamManager : public QObject
{
    Q_OBJECT
public:
    explicit StreamManager(QObject *parent = 0);
    ~StreamManager();

    void start();

private:
    InputStream *mic;
    Speakers *speakers;
    AudioProccessor *proccessor;
    QThread *micThread;
    QThread *speakersThread;
    QThread *proccessorThread;

signals:
    void sourceVolumeChanged(double value);
    void generatorAmplitudeChanged(double value);
    void generatorStepChanged(double value);
    void volumeBar(int);
};

#endif // STREAMMANAGER_H
