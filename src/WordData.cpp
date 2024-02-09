//
// Created by nyanbanan on 02.12.23.
//

#include "WordData.hpp"

WordData::WordData(const QString& word, const QString& doc, quint32 count)
    : _word(word),
      _file(doc),
      _count(count) {}

bool WordData::operator== (const WordData& right) const {
    return _word == right._word && _file == right._file;
}

bool WordData::operator< (const WordData& right) const {
    return _count < right._count;
}

bool WordData::operator> (const WordData& right) const {
    return _count > right._count;
}
