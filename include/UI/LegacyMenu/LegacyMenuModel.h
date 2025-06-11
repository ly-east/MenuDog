#ifndef UI_LEGACYMENU_LEGACYMENUMODEL_H
#define UI_LEGACYMENU_LEGACYMENUMODEL_H

#include <QAbstractTableModel>

class LegacyMenuModel : public QAbstractTableModel {
  Q_OBJECT

public:
  LegacyMenuModel(QObject *parent = nullptr);

public:
  int rowCount(const QModelIndex &parent = QModelIndex()) const override {}

  int columnCount(const QModelIndex &parent = QModelIndex()) const override {
    return 3;
  }

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;

  QVariant headerData(int, Qt::Orientation, int) const override;

  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole) override;

  Qt::ItemFlags flags(const QModelIndex &index) const override;
};

#endif // UI_LEGACYMENU_LEGACYMENUMODEL_H
