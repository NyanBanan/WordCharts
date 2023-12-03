//

#include "WordFileCountModel.hpp"

// Created by nyanbanan on 02.12.23.

WordFileCountModel::WordFileCountModel() {
    _words_data.reserve(util::MAX_WORDS);
    _words_data.reserve(util::MAX_WORDS);
    _words_data.reserve(util::MAX_WORDS);
//
//    pushBack("Aboba", "Abobus.txt", 50);
//    pushBack("Aboba2", "Abobus.txt", 25);
//    pushBack("Aboba3", "Abobus.txt", 100);
//    pushBack("Aboba4", "Abobus2.txt", 50);
//    pushBack("Aboba5", "Abobus2.txt", 25);
//    pushBack("Aboba3", "Abobus2.txt", 90);
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

void WordFileCountModel::pushBack(const QString &word, const QString &doc, quint64 count) {
    beginInsertRows(QModelIndex{}, (int) _words_data.count(), (int) _words_data.count());

    _words_data.push_back({word, doc, count});

    endInsertRows();
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

void WordFileCountModel::changeData(WordFileCountModel::Roles role, qsizetype index, const QVariant &value) {
    switch (role) {
        case WordRole: {
            _words_data[index]._word = value.toString();
            break;
        }
        case FileRole: {
            _words_data[index]._file = value.toString();
            break;
        }
        case CountRole: {
            _words_data[index]._count = value.toInt();
            break;
        }
        default:
            return;
    }
}

qsizetype WordFileCountModel::getIndexOf(const QString &word, const QString &file) {
    return _words_data.indexOf({word, file});
}

void WordFileCountModel::changeData(const WordData &data, const WordData &new_data) {
    auto ind = _words_data.indexOf(data);
    if(ind != -1){
        _words_data[ind] = new_data;
    }
    dataChanged(createIndex(ind, 0), createIndex(ind,0));
}
//
//Qt::ItemFlags WordFileCountModel::flags(const QModelIndex &index) const {
//    if (!index.isValid()) {
//        return Qt::NoItemFlags;
//    }
//    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
//}
//
//bool WordFileCountModel::setData(const QModelIndex &index, const QVariant &value, int role) {
//    switch (role) {
//        case WordRole: {
//            _words_data[index.row()] = value.toString();
//            break;
//        }
//        case FileRole: {
//            _file_data[index.row()] = value.toString();
//            break;
//        }
//        case CountRole: {
//            _count_data[index.row()] = value.toInt();
//            break;
//        }
//        default:
//            return false;
//    }
//    return true;
//}

