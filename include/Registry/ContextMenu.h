#ifndef REGISTRY_CONTEXTMENU_H
#define REGISTRY_CONTEXTMENU_H

#include <QIcon>
#include <QString>
#include <vector>

namespace registry {
struct ContextMenu {
  QString name;    // display name
  QString command; // command may not exist if it has any submenu
  QIcon icon;      // icon
  bool is_shown;   // indicates whether this item is shown or hid
  bool extended;   // appears in extended menu

  std::vector<ContextMenu> submenu;
};
} // namespace registry

#endif // REGISTRY_CONTEXTMENU_H
