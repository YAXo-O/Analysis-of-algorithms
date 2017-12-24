#ifndef INPUTSTREAM_H
#define INPUTSTREAM_H

#include <QObject>
#include <QAudioInput>

class InputStream : public QObject
{
    Q_OBJECT
public:
    explicit InputStream(QObject *parent = nullptr);
    explicit InputStream(const QAudioFormat &format, QObject *parent = nullptr);

    qint64 read(char *data, qint64 maxLen);

public slots:
    void start();

private:
    QAudioInput *mic;
    QIODevice *micDevice;

signals:
    void dataAvailable();

};

#endif // INPUTSTREAM_H
