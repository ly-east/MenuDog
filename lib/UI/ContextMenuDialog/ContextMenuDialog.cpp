#include "UI/ContextMenuDialog/ContextMenuDialog.h"
#include "ui_ContextMenuDialog.h"

ContextMenuDialog::ContextMenuDialog(HMENU menu, QWidget *parent)
    : QDialog{parent}, ui{new Ui::ContextMenuDialog}, menu{menu} {
  ui->setupUi(this);
}
