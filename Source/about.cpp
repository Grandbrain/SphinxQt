#include "about.h"
#include "ui_about.h"

About::About(QWidget* parent) : QDialog(parent), ui(new Ui::About)
{
    ui->setupUi(this);
    ui->textEdit->viewport()->setCursor(Qt::ArrowCursor);
    setWindowFlags(windowFlags() &~ Qt::WindowContextHelpButtonHint);
}

About::~About()
{
    delete ui;
}