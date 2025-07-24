#ifndef UI_CONTEXTMENUDIALOG_CONTEXTMENUDIALOG_H
#define UI_CONTEXTMENUDIALOG_CONTEXTMENUDIALOG_H

#include <QDialog>

#include "SimplifiedWindows.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class ContextMenuDialog;
}
QT_END_NAMESPACE

class ContextMenuDialog : public QDialog {
  Q_OBJECT

public:
  ContextMenuDialog(HMENU menu, QWidget *parent = nullptr);

private:
  Ui::ContextMenuDialog *ui;
  HMENU menu;
};

#endif // UI_CONTEXTMENUDIALOG_CONTEXTMENUDIALOG_H
