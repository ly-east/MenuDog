#include "Registry/ResourceReader.h"
#include "ulog/ulog.h"
#include <cstdlib>

namespace registry {
// string:
// @C:\Program Files (x86)\Common Files\Microsoft
// Shared\MSEnv\2052\VSLauncherUI.dll,-1002

// icon: C:\Program Files (x86)\Common Files\Microsoft
// Shared\MSEnv\VSLauncher.exe,-105

bool ResourceReader::splitResourceString(const QString &rsrc_str, QString &path,
                                         int &id) {
  const QChar comma = u',';
  if (rsrc_str.isEmpty() || !rsrc_str.contains(comma)) {
    ulg.error("splitResourceString: invalid string {}", rsrc_str.toStdString());
    return false;
  }

  auto str_list = rsrc_str.split(comma);
  if (2 != str_list.size()) {
    ulg.error("splitResourceString: too many string({})", str_list.size());
    return false;
  }

  QString id_str = str_list.back();
  bool is_succeeded = false;
  id = std::abs(id_str.toInt(&is_succeeded));
  if (!is_succeeded) {
    ulg.error("splitResourceString: failed to convert integer");
    return false;
  }

  path = str_list.front();
  if (path.startsWith('@'))
    path = path.sliced(1, path.size() - 1);

  return true;
}

} // namespace registry
