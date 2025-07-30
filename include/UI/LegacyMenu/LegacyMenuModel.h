#ifndef UI_LEGACYMENU_LEGACYMENUMODEL_H
#define UI_LEGACYMENU_LEGACYMENUMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QString>

struct _ITEMIDLIST;

class LegacyMenuModel : public QAbstractTableModel {
  Q_OBJECT

public:
  LegacyMenuModel(QObject *parent = nullptr);

public:
  int rowCount(const QModelIndex &parent = QModelIndex()) const override {
    return (int)item_list.size();
  }

  int columnCount(const QModelIndex &parent = QModelIndex()) const override {
    return 1 + (int)ColumnIndex::Text;
  }

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  QVariant headerData(int, Qt::Orientation, int) const override;

  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole) override;

  Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
  enum class ColumnIndex : int { Box, Icon, Text };

  struct FileInfo {
    QString name;
    _ITEMIDLIST *pidl;
  };

private:
  bool listPath();

private:
  QList<FileInfo> item_list; // string of each item
};

#endif // UI_LEGACYMENU_LEGACYMENUMODEL_H
