#include "UI/Loading.h"
#include "Version.h"
#include "ui_Loading.h"

Loading::Loading(QWidget *parent) : QMainWindow{parent}, ui{new Ui::Loading} {
  ui->setupUi(this);

  setWindowFlags(Qt::FramelessWindowHint);

  ui->label->setPixmap(QPixmap(":/img/image.jpg").scaled(400, 280));

  ui->statusbar->setSizeGripEnabled(false);
  ui->statusbar->addWidget(new QLabel("Initializing...Please Wait\t", this));
  ui->statusbar->addWidget(
      new QLabel(QString("Version: V%1R%2C%3")
                     .arg(PROJECT_VERSION_MAJOR * 100, 3, 10, QLatin1Char('0'))
                     .arg(PROJECT_VERSION_MINOR, 3, 10, QLatin1Char('0'))
                     .arg(PROJECT_VERSION_PATCH, 2, 10, QLatin1Char('0')),
                 this));
}

Loading::~Loading() { delete ui; }
