//
// Created by nyanbanan on 02.12.23.
//

#include "WordData.hpp"

#include <utility>

WordData::WordData(QString word, QString doc) : _word(std::move(word)), _doc(std::move(doc)) {}

const QString &WordData::getWord() const {
    return _word;
}

const QString &WordData::getDoc() const {
    return _doc;
}
