#include "UI/Loading.h"
#include "ui_Loading.h"

Loading::Loading(QWidget *parent) : QMainWindow{parent}, ui{new Ui::Loading} {
  ui->setupUi(this);

  setWindowFlags(Qt::FramelessWindowHint);

  ui->label->setPixmap(QPixmap(":/img/image.jpg").scaled(400, 280));

  ui->statusbar->setSizeGripEnabled(false);
  ui->statusbar->addWidget(new QLabel("Initializing...Please wait", this));
}

Loading::~Loading() { delete ui; }
