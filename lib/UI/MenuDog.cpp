#include "UI/MenuDog.h"
#include "ui_MenuDog.h"
#include <QTableWidget>

MenuDog::MenuDog(QWidget *parent) : QMainWindow{parent}, ui{new Ui::MenuDog} {
  ui->setupUi(this);

  // Window size limitation
  setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
  setFixedSize(width(), height());

  ui->statusbar->setSizeGripEnabled(false);
}

MenuDog::~MenuDog() { delete ui; }
