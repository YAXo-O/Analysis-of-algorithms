#ifndef SPEAKERS_H
#define SPEAKERS_H

#include <QObject>
#include <QAudioOutput>

class Speakers : public QObject
{
    Q_OBJECT
public:
    explicit Speakers(QObject *parent = nullptr);
    explicit Speakers(const QAudioFormat &format, QObject *parent = nullptr);

    qint64 write(const char *data, qint64 len);

public slots:
    void start();

private:
    QAudioOutput *speakers;
    QIODevice *speakersDevice;

};

#endif // SPEAKERS_H
