#include "about.h"
#include "window.h"
#include "ui_window.h"

Window::Window(QWidget* parent) : QMainWindow(parent), mUi(new Ui::Window)
{
    mUi->setupUi(this);

    connect(mUi->actionAbout, SIGNAL(triggered()), SLOT(OnAbout()));
    connect(mUi->buttonAudio, SIGNAL(released()), SLOT(OnExplore()));
    connect(mUi->buttonLang, SIGNAL(released()), SLOT(OnExplore()));
    connect(mUi->buttonDict, SIGNAL(released()), SLOT(OnExplore()));
    connect(mUi->buttonDestroy, SIGNAL(released()), SLOT(OnDestroy()));
    connect(mUi->buttonStart, SIGNAL(released()), SLOT(OnRecognite()));
    connect(mUi->buttonInitialize, SIGNAL(released()), SLOT(OnInitialize()));
    connect(mUi->comboDevices, SIGNAL(currentIndexChanged(int)), SLOT(OnDeviceChanged()));
    connect(&mInitWatcher, SIGNAL(finished()), SLOT(OnInitialized()));
    connect(&mRecognizeWatcher, SIGNAL(finished()), SLOT(OnRecognized()));

    readSettings();
}

Window::~Window()
{
    delete mUi;
}

void Window::OnAbout()
{
	About about(this);
    about.exec();
}

void Window::OnExplore()
{
    QObject* sender = QObject::sender();
    QFileDialog fileDialog(this);

    if(sender == mUi->buttonAudio)
    {
        fileDialog.setFileMode(QFileDialog::Directory);
        fileDialog.setOption(QFileDialog::ShowDirsOnly);

        if(fileDialog.exec() == QFileDialog::Accepted)
        {
            QStringList selected = fileDialog.selectedFiles();
            if(!selected.isEmpty()) mUi->editAudio->setText(selected.first());
        }
    }
    else
    {
        if(fileDialog.exec() == QFileDialog::Accepted)
        {
            QStringList selected = fileDialog.selectedFiles();
            if(!selected.isEmpty())
            {
                if(sender == mUi->buttonLang) mUi->editLang->setText(selected.first());
                else if(sender == mUi->buttonDict) mUi->editDict->setText(selected.first());
            }
        }
    }
}

void Window::OnDestroy()
{
    mRecognition.Destroy();
    mUi->buttonStart->setEnabled(false);
    mUi->buttonDestroy->setEnabled(false);
    mUi->buttonInitialize->setEnabled(true);
}

void Window::OnRecognite()
{
    if(!mRecognition.IsInitialized()) return;

    mUi->buttonDestroy->setEnabled(false);
    mUi->buttonStart->setEnabled(false);
    mUi->labelIcon->setPixmap(QPixmap(":/root/Resources/record.ico"));

    QFuture<QString> future = QtConcurrent::run(&mRecognition, &Recognition::Recognize);
    mRecognizeWatcher.setFuture(future);
}

void Window::OnRecognized()
{
    QString data = mRecognizeWatcher.result();
    if(!data.isEmpty()) mUi->editText->appendPlainText(data);

    mUi->buttonDestroy->setEnabled(true);
    mUi->buttonStart->setEnabled(true);
    mUi->labelIcon->setPixmap(QPixmap(":/root/Resources/norecord.ico"));
}

void Window::OnInitialize()
{
    QString audioModel = mUi->editAudio->text();
    QString langModel = mUi->editLang->text();
    QString dictionary = mUi->editDict->text();
    QString device = mUi->comboDevices->currentText();
    int sampleRate = mUi->comboRates->currentText().toInt();

    if(audioModel.isEmpty() || langModel.isEmpty() ||
       dictionary.isEmpty() || device.isEmpty() || sampleRate <= 0)
        QMessageBox::critical(this, tr("Ошибка"), tr("Необходимо заполнить все поля!"));
    else
    {
        QFuture<bool> future = QtConcurrent::run(&mRecognition,
            &Recognition::Initialize, audioModel, langModel, dictionary, device, sampleRate);
        mInitWatcher.setFuture(future);
    }
}

void Window::OnInitialized()
{
    if(!mInitWatcher.result())
        QMessageBox::critical(this, tr("Ошибка"), tr("Не удалось инициализировать распознавание!"));
    else
    {
        mUi->buttonInitialize->setEnabled(false);
        mUi->buttonDestroy->setEnabled(true);
        mUi->buttonStart->setEnabled(true);
    }
}

void Window::OnDeviceChanged()
{
    int currentIndex = mUi->comboDevices->currentIndex();
    if(currentIndex < 0) return;

    QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    QAudioDeviceInfo device = devices.at(currentIndex);
    QList<int> rates = device.supportedSampleRates();
    QStringList ratesStr;
    foreach (int rate, rates)
        ratesStr.append(QString::number(rate));

    mUi->comboRates->clear();
    mUi->comboRates->addItems(ratesStr);
}

void Window::enumMicrophones(int index)
{
    QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    foreach (QAudioDeviceInfo device, devices)
    {
        if(device.isNull()) continue;
        QString deviceName = device.deviceName();
        mUi->comboDevices->addItem(deviceName);
    }

    if(index < mUi->comboDevices->count())
        mUi->comboDevices->setCurrentIndex(index);
}

void Window::readSettings()
{
    QSettings settings("SphinxQt");
    settings.beginGroup("General");

    int deviceIndex = settings.value("device").toInt();
    int rateIndex = settings.value("rate").toInt();

    enumMicrophones(deviceIndex);
    OnDeviceChanged();

    if(rateIndex < mUi->comboRates->count())
        mUi->comboRates->setCurrentIndex(rateIndex);

    mUi->editAudio->setText(settings.value("audio").toString());
    mUi->editLang->setText(settings.value("lang").toString());
    mUi->editDict->setText(settings.value("dict").toString());
    restoreState(settings.value("state").toByteArray());
    restoreGeometry(settings.value("geometry").toByteArray());

    settings.endGroup();
}

void Window::writeSettings()
{
    QSettings settings("SphinxQt");
    settings.beginGroup("General");

    settings.setValue("device", mUi->comboDevices->currentIndex());
    settings.setValue("rate", mUi->comboRates->currentIndex());
    settings.setValue("audio", mUi->editAudio->text());
    settings.setValue("lang", mUi->editLang->text());
    settings.setValue("dict", mUi->editDict->text());
    settings.setValue("state", saveState());
    settings.setValue("geometry", saveGeometry());

    settings.endGroup();
}

void Window::closeEvent(QCloseEvent* event)
{
    writeSettings();
    event->accept();
}