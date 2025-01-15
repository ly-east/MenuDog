#include "Registry/ResourceReader.h"
#include "ulog/ulog.h"
#include <QPixmap>
#include <Windows.h>
#include <cstdlib>
#include <memory>

namespace registry {
QIcon ResourceReader::getIcon(const QString &rsrc_str) {
  QIcon icon;

  auto icon_parser = [&icon](void *hModule, unsigned id) -> bool {
    HICON hicon = LoadIconW((HMODULE)hModule, MAKEINTRESOURCE(id));
    if (!hicon) {
      ulg.error("getIcon: {}", GetLastError());
      return false;
    }

    icon = QPixmap::fromImage(QImage::fromHICON(hicon));
    return true;
  };

  if (getResource(rsrc_str, icon_parser))
    return icon;
  return {};
}

QString ResourceReader::getString(const QString &rsrc_str) {
  QString value;

  auto string_parser = [&value](void *hModule, unsigned id) -> bool {
    unsigned buf_size = 64;
    int ret_val = 0;
    wchar_t *buf = nullptr;
    std::unique_ptr<wchar_t[]> buf_ptr = nullptr;

    do {
      try {
        buf_ptr = std::make_unique<wchar_t[]>(buf_size);
      } catch (const std::exception &e) {
        ulg.error("getString: {} when size is {}", e.what(), buf_size);
        break;
      }

      buf = buf_ptr.get();
      ret_val = LoadStringW((HMODULE)hModule, id, buf, buf_size);

      // try to allocate buffer with double size in next loop
      buf_size = buf_size << 1;
    } while (buf_size <= 256 && !ret_val);

    if (ret_val && buf) {
      value = QString::fromWCharArray(buf, ret_val);
      return true;
    }

    return false;
  };

  if (!getResource(rsrc_str, string_parser))
    value.clear();

  return value;
}

bool ResourceReader::getResource(const QString &rsrc_str,
                                 const RsrcExtFuncTy &func) {
  // prepare arguments

  QString libfile;
  int id = 0;
  if (!splitResourceString(rsrc_str, libfile, id))
    return false;

  HMODULE hModule = nullptr;
  bool is_succeeded = false;

  // load resource

  hModule = LoadLibraryExW(libfile.toStdWString().c_str(), nullptr,
                           LOAD_LIBRARY_AS_DATAFILE);
  if (hModule) {
    is_succeeded = func(hModule, id);
    FreeLibrary(hModule);
  } else
    ulg.error("getResource: failed to load library {}", GetLastError());

  return is_succeeded;
}

bool ResourceReader::splitResourceString(const QString &rsrc_str, QString &path,
                                         int &id) {
  const QChar comma = u',';
  if (rsrc_str.isEmpty() || !rsrc_str.contains(comma)) {
    ulg.error("splitResourceString: invalid string {}", rsrc_str.toStdString());
    return false;
  }

  // split by ','

  auto str_list = rsrc_str.split(comma);
  if (2 != str_list.size()) {
    ulg.error("splitResourceString: too many string({})", str_list.size());
    return false;
  }

  // convert resource id to integer

  QString id_str = str_list.back();
  bool is_succeeded = false;
  id = std::abs(id_str.toInt(&is_succeeded));
  if (!is_succeeded) {
    ulg.error("splitResourceString: failed to convert integer");
    return false;
  }

  // ignore leading '@' if exists

  path = str_list.front();
  if (path.startsWith('@'))
    path = path.sliced(1, path.size() - 1);

  return true;
}
} // namespace registry
