#include "UI/ContextMenuDialog/ContextMenuModel.h"

ContextMenuModel::ContextMenuModel(HMENU menu, QObject *parent)
    : QAbstractTableModel{parent}, menu{menu} {}

void ContextMenuModel::fetchContextMenu() {
  int itemCount = GetMenuItemCount(menu);
  for (int i = 0; i < itemCount; i++) {
    MENUITEMINFO mii = {};
    mii.cbSize = sizeof(MENUITEMINFO);
    mii.fMask = MIIM_STRING | MIIM_BITMAP | MIIM_ID;

    wchar_t itemText[256];
    mii.dwTypeData = itemText;
    mii.cch = sizeof(itemText) / sizeof(wchar_t);

    if (GetMenuItemInfo(menu, i, TRUE, &mii)) {
      // itemText contains the label
      // mii.hbmpItem contains the bitmap (icon)
      // mii.wID contains the command ID
    }
  }
}
