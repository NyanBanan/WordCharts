//
// Created by nyanbanan on 02.12.23.
//

#ifndef WORDCHARTS_WORDFILECOUNTMODEL_HPP
#define WORDCHARTS_WORDFILECOUNTMODEL_HPP

#include <QAbstractItemModel>
#include <QtQml>

#include "WordData.hpp"
#include "util/NumOfWordsConstant.hpp"

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

    [[nodiscard]] QModelIndex index(int row, int column, const QModelIndex &parent) const override;

    [[nodiscard]] int columnCount(const QModelIndex &parent) const override;

    [[nodiscard]] QModelIndex parent(const QModelIndex &child) const override;

    [[nodiscard]] int rowCount(const QModelIndex &parent) const override;

    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

    void pushBack(const QString& word, const QString& doc, quint64 count);

    void changeData(const WordData &data, const WordData &new_data);

    qsizetype getIndexOf(const QString &word, const QString &file);

    Q_INVOKABLE
    void resetData();
private:
    [[nodiscard]] bool hasIndex(int row, int column) const;

    QList<WordData> _words_data;
};


#endif //WORDCHARTS_WORDFILECOUNTMODEL_HPP
