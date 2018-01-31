#include <QApplication>
#include <QTranslator>
#include "window.h"

void Translate()
{
    QLocale::Language lang = QLocale::system().language();
    QStringList files;
    if(lang == QLocale::Language::Russian) files.append(":/root/Resources/ru.qm");
    else files.append(":/root/Resources/en.qm");
    foreach (QString file, files)
    {
        QTranslator* trans = new QTranslator(qApp);
        if(trans->load(file)) qApp->installTranslator(trans);
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Translate();
    Window w;
    w.show();
    return a.exec();
}