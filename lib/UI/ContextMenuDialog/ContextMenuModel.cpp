#include "UI/ContextMenuDialog/ContextMenuModel.h"
#include "ulog/ulog.h"
#include <QReadLocker>
#include <QWriteLocker>

ContextMenuModel::ContextMenuModel(HMENU menu, QObject *parent)
    : QAbstractTableModel{parent}, menu{menu} {
  fetchContextMenu();
}

int ContextMenuModel::rowCount(const QModelIndex &parent) const {
  QReadLocker locker{&list_mutex};
  return menu_list.size();
}

QVariant ContextMenuModel::data(const QModelIndex &index, int role) const {
  if (Qt::DisplayRole != role || index.column() != (int)Column::Label)
    return {};

  const auto row = index.row();

  QReadLocker locker{&list_mutex};
  const auto size = menu_list.size();
  if (row >= size) {
    ulg.error("data: access is out of range");
    return {};
  }

  return menu_list[row].label;
}

bool ContextMenuModel::setData(const QModelIndex &index, const QVariant &value,
                               int role) {
  // TODO: save changes of context menu
  return false;
}

void ContextMenuModel::fetchContextMenu() {
  const int itemCount = GetMenuItemCount(menu);
  if (!itemCount) {
    ulg.warn("fetchContextMenu: no item at context menu");
    return;
  }

  QWriteLocker locker{&list_mutex};

  if (!menu_list.empty())
    menu_list.clear();
  menu_list.reserve(itemCount);

  for (int i = 0; i < itemCount; i++) {
    MENUITEMINFOW mii = {sizeof(MENUITEMINFOW)};
    mii.fMask = MIIM_STRING | MIIM_BITMAP | MIIM_ID;

    wchar_t itemText[256];
    mii.dwTypeData = itemText;
    mii.cch = sizeof(itemText) / sizeof(wchar_t);

    if (GetMenuItemInfo(menu, i, TRUE, &mii)) {
      // https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-menuiteminfow
      // itemText contains the label
      // mii.hbmpItem contains the bitmap (icon)
      // mii.wID contains the command ID
      // mii.fType indicates the item type
      // mii.fState indicates the item state
      RichMenuInfo rmi{QString::fromWCharArray(itemText)};
      menu_list.emplace_back(std::move(rmi));
    } else
      ulg.error("fetchContextMenu failed %u", GetLastError());
  }
}
