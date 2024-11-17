#include "UI/Loading.h"
#include "ucrash/ucrash.h"
#include "ulog/ulog.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  // set file logger
  ulog::setFileLogger(spdlog::level::info, "MenuDog.log");

  // set crash handler
  if (!ucrash::setWindowHandler())
    ulg.error("main: setWindowHandler failed");

  QApplication a{argc, argv};

  Loading l;
  l.show();

  return a.exec();
}
