#include "UI/ContextMenuDialog/ContextMenuDialog.h"
#include "UI/ContextMenuDialog/ContextMenuModel.h"
#include "ui_ContextMenuDialog.h"

ContextMenuDialog::ContextMenuDialog(HMENU menu, QWidget *parent)
    : QDialog{parent}, ui{new Ui::ContextMenuDialog}, menu{menu} {
  ui->setupUi(this);

  ContextMenuModel *cmm = new ContextMenuModel{menu, this};
  ui->tableView->setModel(cmm);
  ui->tableView->horizontalHeader()->hide();
  ui->tableView->verticalHeader()->hide();
}
