#ifndef UI_CONTEXTMENUDIALOG_CONTEXTMENUMODEL_H
#define UI_CONTEXTMENUDIALOG_CONTEXTMENUMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QReadWriteLock>
#include <QString>

#include "SimplifiedWindows.h"

class ContextMenuModel : public QAbstractTableModel {
  Q_OBJECT

public:
  ContextMenuModel(HMENU menu, QObject *parent = nullptr);

  enum class Column { Checkbox, Icon, Label, Submenu };

public:
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  int columnCount(const QModelIndex &parent = QModelIndex()) const override {
    return (int)Column::Submenu;
  }

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  // TODO: disable header
  QVariant headerData(int, Qt::Orientation, int) const override { return {}; }

  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole) override;

  // shall we override this?
  // Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
  struct RichMenuInfo {
    QString label;
  };

private:
  void fetchContextMenu();

private:
  HMENU menu;

  QList<RichMenuInfo> menu_list;
  mutable QReadWriteLock list_mutex;
};

#endif // UI_CONTEXTMENUDIALOG_CONTEXTMENUMODEL_H
