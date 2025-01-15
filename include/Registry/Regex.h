#ifndef REGISTRY_REGEX_H
#define REGISTRY_REGEX_H

#include <QString>

namespace registry {
bool isCLSID(const QString &str);

bool isResourcePath(const QString &str);
} // namespace registry

#endif // REGISTRY_REGEX_H
