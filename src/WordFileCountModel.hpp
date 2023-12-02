//
// Created by nyanbanan on 02.12.23.
//

#ifndef WORDCHARTS_WORDFILECOUNTMODEL_HPP
#define WORDCHARTS_WORDFILECOUNTMODEL_HPP

#include <QAbstractItemModel>
#include <QtQml>

#include "WordData.hpp"

class WordFileCountModel : public QAbstractItemModel {
    Q_OBJECT
    QML_ELEMENT
public:
    enum Roles {
        WordRole = Qt::UserRole + 1,
        FileRole,
        CountRole
    };

    WordFileCountModel();

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QModelIndex parent(const QModelIndex &child) const override;

    [[nodiscard]] int rowCount(const QModelIndex &parent) const override;

    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

    void pushBack(const QString& word, const QString& doc, quint64 count);

private:
    [[nodiscard]] bool hasIndex(int row, int column) const;

//    QMap<WordData, quint64> _data;
    QVector<QString> _words_data;
    QVector<QString> _file_data;
    QVector<quint64> _count_data;
};


#endif //WORDCHARTS_WORDFILECOUNTMODEL_HPP
