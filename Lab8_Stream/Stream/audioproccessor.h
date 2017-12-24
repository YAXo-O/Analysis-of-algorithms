#ifndef AUDIOPROCCESSOR_H
#define AUDIOPROCCESSOR_H

#include <QObject>

class InputStream;
class Speakers;

class AudioProccessor : public QObject
{
    Q_OBJECT
public:
    explicit AudioProccessor(QObject *parent = 0);

    void setInput(InputStream *micro);
    void setSpeakers(Speakers *speakers);

public slots:
    void proccess();
    void setSourceFactor(double factor);
    void setGeneratorAmplitude(double amp);
    void setGeneratorStep(double step);

private:
    InputStream *micro;
    Speakers *speakers;

    double sourceFactor;
    double generatorAmplitude;
    double generatorStep;

signals:
    void volumeBar(int);

};

#endif // AUDIOPROCCESSOR_H
