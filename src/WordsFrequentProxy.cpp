//
// Created by nyanbanan on 03.12.23.
//

#include "WordsFrequentProxy.hpp"

WordsFrequentProxy::WordsFrequentProxy(qint64 max_amount) : _max_amount(max_amount) {
    _words_for_model.reserve(_max_amount);
}

void WordsFrequentProxy::updateData(const WordData &wd) {
    if (_words_for_model.size() != _max_amount) {
        _words_for_model.emplaceBack(wd);
        emit newData(wd);
        if (_words_for_model.size() == _max_amount - 1) {
            _min_elem = std::min_element(_words_for_model.begin(), _words_for_model.end());
        }
    } else {
        auto iter = std::find(_words_for_model.begin(), _words_for_model.end(), wd);
        if (iter != _words_for_model.end()) {
            iter->_count = wd._count;
            emit updateModelData(wd, wd);
        } else if (_min_elem->_count < wd._count) {
            emit updateModelData(*_min_elem, wd);
            _min_elem->_word = wd._word;
            _min_elem->_count = wd._count;
            _min_elem = std::min_element(_words_for_model.begin(), _words_for_model.end());
        }
    }
}

