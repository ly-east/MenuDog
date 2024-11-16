// #include "Utility/Crash/CrashPad.h"
#include "UI/Loading.h"
#include "ulog/ulog.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  // set file logger
  ulog::setFileLogger(spdlog::level::info, "MenuDog.log");

  // set crash handler

  // if (!utility::crash::setWindowHandler())
  //   ulg.error("main: setWindowHandler failed");

  QApplication a{argc, argv};
  // TODO: launch loading window
  // QBBDown w;
  // w.show();

  Loading l;
  l.show();

  return a.exec();
}
