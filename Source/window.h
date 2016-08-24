#ifndef WINDOW_H
#define WINDOW_H

#include <QSettings>
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QFutureWatcher>
#include <QAudioDeviceInfo>
#include <QtConcurrent/QtConcurrent>
#include "recognition.h"

namespace Ui
{
    class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget* = 0);
    virtual ~Window();

public slots:
    void OnAbout();
    void OnExplore();
    void OnDestroy();
    void OnRecognite();
    void OnRecognized();
    void OnInitialize();
    void OnInitialized();
    void OnDeviceChanged();

private:
    void enumMicrophones(int = 0);
    void readSettings();
    void writeSettings();
    void closeEvent(QCloseEvent*);

private:
    Ui::Window* mUi;
    Recognition mRecognition;
    QFutureWatcher<bool> mInitWatcher;
    QFutureWatcher<QString> mRecognizeWatcher;
};

#endif