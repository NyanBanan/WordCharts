//
// Created by nyanbanan on 06.12.23.
//

#include "WordsCounter.hpp"

void WordsCounter::increaseCount(const QString &str, quint64 count) {
    if(!_counter_hash.contains(str)){
        _counter_hash.insert(str, count);
        countChanged(str, count);
    }
    else{
        countChanged(str, ++_counter_hash[str]);
    }
}
