#include "UI/MenuDog.h"
#include "UI/LegacyMenu/LegacyMenuModel.h"
#include "Version.h"
#include "ui_MenuDog.h"
#include <QString>
#include <QTableWidget>

MenuDog::MenuDog(QWidget *parent) : QMainWindow{parent}, ui{new Ui::MenuDog} {
  ui->setupUi(this);

  // Window size limitation
  setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
  setFixedSize(width(), height());

  ui->statusbar->setSizeGripEnabled(false);

  auto legacy_model = new LegacyMenuModel{this};
  ui->legacy_menu->setModel(legacy_model);

  // hide win11 context table. functions related may be implemented in the
  // future
  ui->morden_menu->hide();

  // default tab
  ui->tabWidget->setCurrentIndex(0);

  // About tab

  QString version =
      QString("Version: V%1R%2C%3")
          .arg(PROJECT_VERSION_MAJOR * 100, 3, 10, QLatin1Char('0'))
          .arg(PROJECT_VERSION_MINOR, 3, 10, QLatin1Char('0'))
          .arg(PROJECT_VERSION_PATCH, 2, 10, QLatin1Char('0'));
  ui->version->setText(version);
}

MenuDog::~MenuDog() { delete ui; }
