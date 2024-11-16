#ifndef LOADING_H
#define LOADING_H

#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
class Loading;
}
QT_END_NAMESPACE

class Loading : public QMainWindow {
  Q_OBJECT

public:
  Loading(QWidget *parent = nullptr);
  virtual ~Loading();

private:
private slots:

private:
  Ui::Loading *ui;
};

#endif // LOADING_H
