#ifndef REGISTRY_RESOURCEREADER_H
#define REGISTRY_RESOURCEREADER_H

#include <QString>
#include <QVariant>
#include <functional>

namespace tester {
class ResourceReaderTest_splitResourceString_Test;
}

namespace registry {
class ResourceReader {
public:
  static QIcon getIcon(const QString &rsrc_str);

  static QString getString(const QString &rsrc_str);

private:
  friend class tester::ResourceReaderTest_splitResourceString_Test;

  static QVariant getResource(const QString &path, int id);

  static bool splitResourceString(const QString &rsrc_str, QString &path,
                                  int &id);
};
} // namespace registry

#endif // REGISTRY_RESOURCEREADER_H
