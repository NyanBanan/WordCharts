//

#include "WordFileCountModel.hpp"

// Created by nyanbanan on 02.12.23.

WordFileCountModel::WordFileCountModel() {
    _words_data.reserve(15);
    _file_data.reserve(15);
    _count_data.reserve(15);

    pushBack("Aboba", "Abobus.txt", 50);
    pushBack("Aboba2", "Abobus.txt", 25);
    pushBack("Aboba3", "Abobus.txt", 100);
    pushBack("Aboba4", "Abobus2.txt", 50);
    pushBack("Aboba5", "Abobus2.txt", 25);
    pushBack("Aboba3", "Abobus2.txt", 90);
}

int WordFileCountModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;

    return (int) _words_data.size();
}

//
int WordFileCountModel::columnCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : 3;
}

QVariant WordFileCountModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return {};
    switch (role) {
        case WordRole: {
//            auto iter = _data.keyBegin();
//            for (uint i = 0; i < index.row(); ++i) {
//                iter++;
//            }
//            return QVariant::fromValue(iter->getWord());
            return QVariant::fromValue(_words_data[index.row()]);
        }
        case FileRole: {
//            auto iter = _data.keyBegin();
//            for (uint i = 0; i < index.row(); ++i) {
//                iter++;
//            }
//            return QVariant::fromValue(iter->getDoc());
            return QVariant::fromValue(_file_data[index.row()]);
        }
        case CountRole: {
//            auto iter = _data.keyValueBegin();
//            for (uint i = 0; i < index.row(); ++i) {
//                iter++;
//            }
//            return QVariant::fromValue(*iter);
            return QVariant::fromValue(_count_data[index.row()]);
        }
        default:
            return {};
    }
}

QHash<int, QByteArray> WordFileCountModel::roleNames() const {
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();

    roles[WordRole] = "word";
    roles[FileRole] = "file";
    roles[CountRole] = "count";

    return roles;
}

void WordFileCountModel::pushBack(const QString &word, const QString &doc, quint64 count) {
    beginInsertRows(QModelIndex{}, (int) _words_data.count(), (int) _words_data.count());

    _words_data.push_back(word);
    _file_data.push_back(doc);
    _count_data.push_back(count);

    endInsertRows();
}

QModelIndex WordFileCountModel::index(int row, int column, const QModelIndex &parent) const {
    if (hasIndex(row, column)) {
        switch (column) {
            case 0: {
                return createIndex(row, column, &_words_data[row]);
            }
            case 1: {
                return createIndex(row, column, &_file_data[row]);
            }
            case 2: {
                return createIndex(row, column, &_count_data[row]);
            }
            default:
                return {};
        }
    }
    return {};
}

QModelIndex WordFileCountModel::parent(const QModelIndex &child) const {
    return {};
}

bool WordFileCountModel::hasIndex(int row, int column) const {
    if (column < 0 || column > columnCount() || row < 0 || row > _words_data.count() - 1) {
        return false;
    }
    return true;
}

