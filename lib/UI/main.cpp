#include "UI/MenuDog.h"
#include "ucrash/ucrash.h"
#include "ulog/ulog.h"
#include <QApplication>
#include <QSplashScreen>

int main(int argc, char *argv[]) {
  // set file logger
  ulog::setFileLogger(spdlog::level::info, "MenuDog.log");

  // set crash handler
  if (!ucrash::setWindowHandler())
    ulg.error("main: setWindowHandler failed");

  QApplication a{argc, argv};

  QPixmap pixmap{":/img/image.jpg"};
  QSplashScreen splash{pixmap.scaled(400, 280)};
  splash.show();

  a.processEvents();

  // TODO: load CLSID
  splash.showMessage(QStringLiteral("Loading CLSID..."),
                     Qt::AlignHCenter | Qt::AlignBottom, Qt::white);
  std::this_thread::sleep_for(std::chrono::seconds(3));

  // TODO: load rules
  splash.showMessage(QStringLiteral("Loading Rules..."),
                     Qt::AlignHCenter | Qt::AlignBottom, Qt::white);
  std::this_thread::sleep_for(std::chrono::seconds(3));

  MenuDog md;
  md.show();
  splash.finish(&md);

  return a.exec();
}
