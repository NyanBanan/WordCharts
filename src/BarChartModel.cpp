//
// Created by nyanbanan on 02.12.23.
//

#include "BarChartModel.hpp"

int BarChartModel::rowCount(const QModelIndex &parent) const {
    return (int) _words_data.size();
}

QVariant BarChartModel::data(const QModelIndex &index, int role) const {
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
        case DocRole: {
//            auto iter = _data.keyBegin();
//            for (uint i = 0; i < index.row(); ++i) {
//                iter++;
//            }
//            return QVariant::fromValue(iter->getDoc());
            return QVariant::fromValue(_doc_data[index.row()]);
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

QHash<int, QByteArray> BarChartModel::roleNames() const {
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();

    roles[WordRole] = "word";
    roles[DocRole] = "doc";
    roles[CountRole] = "count";

    return roles;
}

BarChartModel::BarChartModel() {
    insert("Aboba", "Abobus.txt", 50);
    insert("Aboba2", "Abobus.txt", 25);
    insert("Aboba3", "Abobus.txt", 100);
    insert("Aboba4", "Abobus2.txt", 50);
    insert("Aboba5", "Abobus2.txt", 25);
    insert("Aboba3", "Abobus2.txt", 90);
}

void BarChartModel::insert(QString word, QString doc, quint64 count) {
    _words_data.push_back(word);
    _doc_data.push_back(doc);
    _count_data.push_back(count);
}
