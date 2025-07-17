#include "UI/LegacyMenu/LegacyMenuModel.h"
#include "ulog/ulog.h"
#include <ShlObj.h>
#include <shellapi.h>

LegacyMenuModel::LegacyMenuModel(QObject *parent)
    : QAbstractTableModel{parent} {
  listPath();
}

QVariant LegacyMenuModel::data(const QModelIndex &index, int role) const {
  auto column = static_cast<ColumnIndex>(index.column());
  if (ColumnIndex::Text != column)
    return {};

  switch (role) {
  case Qt::DisplayRole:
    return item_list.empty() ? QString{} : item_list[index.row()];
  default:
    return {};
  }
}

QVariant LegacyMenuModel::headerData(int section, Qt::Orientation orientation,
                                     int role) const {
  if (role == Qt::TextAlignmentRole)
    return QVariant{Qt::AlignHCenter | Qt::AlignVCenter};
  else if (role != Qt::DisplayRole || Qt::Orientation::Vertical == orientation)
    return {};

  auto index = static_cast<ColumnIndex>(section);
  switch (index) {
  default:
  case ColumnIndex::Box:
    return {};
  case ColumnIndex::Icon:
    return QString(tr("Icon"));
  case ColumnIndex::Text:
    return QString(tr("Item"));
  }
}

bool LegacyMenuModel::setData(const QModelIndex &index, const QVariant &value,
                              int role) {
  return false;
}

Qt::ItemFlags LegacyMenuModel::flags(const QModelIndex &index) const {
  if (!index.isValid())
    return QAbstractItemModel::flags(index);

  if ((ColumnIndex)index.column() == ColumnIndex::Text) {
    Qt::ItemFlags flag = Qt::ItemIsEditable;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | ~flag;
  }

  return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

bool LegacyMenuModel::listPath() {
  auto check_result = [](const char *const caller, HRESULT result) -> bool {
    if (S_OK != result) {
      ulg.error("listPath:  error {}", result);
      return false;
    }
    return true;
  };

  IShellFolder *isf = nullptr;
  HRESULT result = SHGetDesktopFolder(&isf);
  if (!check_result("SHGetDesktopFolder", result))
    return false;

  // GUID is also acceptible by display name.
  // usage: ::{CLSID for Control Panel}\::{CLSID for printers folder}
  // see MSDN document of `ParseDisplayName` for more information.
  wchar_t display_name[] = L"D:\\work\\";
  ITEMIDLIST *pidl = nullptr;

  SHParseDisplayName(display_name, nullptr, &pidl, 0, nullptr);
  if (!check_result("ParseDisplayName", result))
    return false;
  else if (!pidl) {
    ulg.error("ParseDisplayName: pidl {}", (UINT64)pidl);
    return false;
  }

  IShellFolder *root = nullptr;
  isf->BindToObject(pidl, nullptr, IID_IShellFolder, (void **)&root);
  if (!check_result("BindToObject", result) || !root)
    return false;

  auto path_walker = [this, root](HWND handle, bool is_folder) {
    IEnumIDList *list = nullptr;
    auto mask = is_folder ? SHCONTF_FOLDERS : SHCONTF_NONFOLDERS;
    auto ok = root->EnumObjects(handle, mask | SHCONTF_INCLUDEHIDDEN, &list);

    // TODO: pass over known error codes
    if (S_OK != ok) {
      ulg.warn("EnumObjects failed {}", ok);
      return;
    }

    ITEMIDLIST *pidl = nullptr;
    ULONG celt_fetched = 0;
    while (S_OK == list->Next(1, &pidl, &celt_fetched) &&
           S_FALSE == celt_fetched) {
      SHFILEINFOW info{};
      SHGetFileInfoW((LPCWSTR)pidl, 0, &info, sizeof(SHFILEINFOW),
                     SHGFI_PIDL | SHGFI_DISPLAYNAME | SHGFI_TYPENAME);
      item_list.emplace_back(QString::fromWCharArray(info.szDisplayName));
    }
  };

  path_walker(nullptr, true);
  path_walker(nullptr, false);

  // TODO: use RAII to assure this
  isf->Release();
  root->Release();

  return true;
}
