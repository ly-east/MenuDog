#include "UI/LegacyMenu/LegacyMenuModel.h"

LegacyMenuModel::LegacyMenuModel(QObject *parent)
    : QAbstractTableModel{parent} {}

QVariant LegacyMenuModel::data(const QModelIndex &index, int role) const {
  return {};
}

QVariant LegacyMenuModel::headerData(int section, Qt::Orientation orientation,
                                     int role) const {
  if (role == Qt::TextAlignmentRole)
    return QVariant{Qt::AlignHCenter | Qt::AlignVCenter};
  else if (role != Qt::DisplayRole)
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
