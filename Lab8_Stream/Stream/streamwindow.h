#ifndef STREAMWINDOW_H
#define STREAMWINDOW_H

#include <QMainWindow>
#include "streammanager.h"

namespace Ui {
    class StreamWindow;
}

class StreamWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StreamWindow(QWidget *parent = 0);
    ~StreamWindow();

private:
    Ui::StreamWindow *ui;
    StreamManager *manager;

private slots:
    void convertVolume(int value);

signals:
    void volumeChanged(double);
};

#endif // STREAMWINDOW_H
