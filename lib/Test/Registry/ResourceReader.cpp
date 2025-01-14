#include "Test/Registry/ResourceReader.h"
#include "Registry/ResourceReader.h"
#include "ulog/ulog.h"
#include <QString>

namespace tester {
void ResourceReaderTest::SetUpTestSuite() { ulog::setFileLogger("tester.log"); }

TEST_F(ResourceReaderTest, splitResourceString) {
  const QStringList list{"@C:\\Program Files (x86)\\Common Files\\Microsoft "
                         "Shared\\MSEnv\\2052\\VSLauncherUI.dll,-1002",
                         "C:\\Program Files (x86)\\Common Files\\Microsoft "
                         "Shared\\MSEnv\\VSLauncher.exe,-105"};

  QString path;
  int id = 0;

  for (auto &str : list) {
    EXPECT_TRUE(registry::ResourceReader::splitResourceString(str, path, id));
    ulg.info("{} {}", path.toStdString(), id);
  }
}
} // namespace tester
