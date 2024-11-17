#ifndef MENUDOG_H
#define MENUDOG_H

#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
class MenuDog;
}
QT_END_NAMESPACE

class MenuDog : public QMainWindow {
  Q_OBJECT

public:
  MenuDog(QWidget *parent = nullptr);
  virtual ~MenuDog();

private:
private slots:

private:
  Ui::MenuDog *ui;
};

#endif // MENUDOG_H
