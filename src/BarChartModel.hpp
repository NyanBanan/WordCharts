//
// Created by nyanbanan on 02.12.23.
//

#ifndef WORDCHARTS_BARCHARTMODEL_HPP
#define WORDCHARTS_BARCHARTMODEL_HPP

#include <QAbstractListModel>
#include <QtQml>

#include "WordData.hpp"

class BarChartModel : public QAbstractListModel {
    Q_OBJECT
    QML_ELEMENT
public:
    enum Roles {
        WordRole = Qt::UserRole + 1,
        DocRole,
        CountRole
    };

    BarChartModel();

    [[nodiscard]] int rowCount(const QModelIndex &parent) const override;

    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

private:
    void insert(QString word, QString doc, quint64 count);
//    QMap<WordData, quint64> _data;
    QList<QString> _words_data;
    QList<QString> _doc_data;
    QList<quint64> _count_data;
};


#endif //WORDCHARTS_BARCHARTMODEL_HPP
