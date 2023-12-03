//
// Created by nyanbanan on 02.12.23.
//

#include "WordData.hpp"

#include <utility>

WordData::WordData(QString word, QString doc, quint64 count) : _word(std::move(word)), _file(std::move(doc)),
                                                               _count(count) {}

bool WordData::operator==(const WordData &right) const {
    return _word == right._word && _file == right._file;
}

bool WordData::operator<(const WordData &right) const {
    return _count < right._count;
}
