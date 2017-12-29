#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class QDoubleValidator;
template<typename T>
class QVector;
class QLineEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QDoubleValidator *validator;
    QVector<QLineEdit *> lines;

    void setConnections();

private slots:
    void createMatrix();
    void count();
};

#endif // MAINWINDOW_H
