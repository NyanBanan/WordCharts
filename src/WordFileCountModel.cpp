// Created by nyanbanan on 02.12.23.

#include "WordFileCountModel.hpp"

WordFileCountModel::WordFileCountModel() {
    _words_data.reserve(util::MAX_WORDS);
}

int WordFileCountModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;
    return (int) _words_data.size();
}

int WordFileCountModel::columnCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : 3;
}

QVariant WordFileCountModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return {};
    switch (role) {
        case WordRole: {
            return QVariant::fromValue(_words_data[index.row()]._word);
        }
        case FileRole: {
            return QVariant::fromValue(_words_data[index.row()]._file);
        }
        case CountRole: {
            return QVariant::fromValue(_words_data[index.row()]._count);
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

void WordFileCountModel::pushFront(const WordData &wd) {
    beginInsertRows(QModelIndex{},  0, 0);

    _words_data.push_front(wd);

    endInsertRows();
}
void WordFileCountModel::updateData(const WordData &old_data, const WordData &new_data) {
    auto ind = _words_data.indexOf(old_data);
    if (ind != -1) {
        _words_data[ind] = new_data;
    }
    dataChanged(createIndex(ind, 0), createIndex(ind, 0));
}

QModelIndex WordFileCountModel::index(int row, int column, const QModelIndex &parent) const {
    if (hasIndex(row, column)) {
        switch (column) {
            case 0: {
                return createIndex(row, column, &_words_data[row]._word);
            }
            case 1: {
                return createIndex(row, column, &_words_data[row]._file);
            }
            case 2: {
                return createIndex(row, column, &_words_data[row]._count);
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
    if (column < 0 || column > columnCount(QModelIndex{}) || row < 0 || row > _words_data.count() - 1) {
        return false;
    }
    return true;
}

void WordFileCountModel::resetData() {
    beginResetModel();
    _words_data.clear();
    _words_data.reserve(util::MAX_WORDS);
    endResetModel();
}
