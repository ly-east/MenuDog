#ifndef UI_CONTEXTMENUDIALOG_CONTEXTMENUMODEL_H
#define UI_CONTEXTMENUDIALOG_CONTEXTMENUMODEL_H

#include <QAbstractTableModel>

#include "SimplifiedWindows.h"

class ContextMenuModel : public QAbstractTableModel {
  Q_OBJECT

public:
  ContextMenuModel(HMENU menu, QObject *parent = nullptr);

public:
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  QVariant headerData(int, Qt::Orientation, int) const override;

  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole) override;

  Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
  void fetchContextMenu();

private:
  HMENU menu;
};

#endif // UI_CONTEXTMENUDIALOG_CONTEXTMENUMODEL_H
