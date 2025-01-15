#ifndef REGISTRY_RESOURCEREADER_H
#define REGISTRY_RESOURCEREADER_H

#include <QIcon>
#include <QString>
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
  friend class tester::ResourceReaderTest_splitResourceString_Test; // for gtest

  // Extraction method of specific type of resource
  using RsrcExtFuncTy = std::function<bool(void *, unsigned)>;

  static bool getResource(const QString &rsrc_str, const RsrcExtFuncTy &func);

  static bool splitResourceString(const QString &rsrc_str, QString &path,
                                  int &id);
};
} // namespace registry

#endif // REGISTRY_RESOURCEREADER_H
