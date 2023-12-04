//
// Created by nyanbanan on 03.12.23.
//

#ifndef WORDCHARTS_WORDSFREQUENTPROXY_HPP
#define WORDCHARTS_WORDSFREQUENTPROXY_HPP

#include "Trees/ModifiedPrefixTree.hpp"
#include "WordData.hpp"
#include "WordFileCountModel.hpp"

//Данный класс обрабатывает данные и передает их в модель, а также редактирует уже находящиеся в модели данные
//Основная задача класса - поддерживать в модели util::MAX_WORDS элементов и обновлять в них данные
class WordsFrequentProxy{
public:
    explicit WordsFrequentProxy(qint64 max_amount);

    void updateData(const QString &word, const QString &file, quint64 count);
    void setModel(WordFileCountModel *model);
    [[nodiscard]] WordFileCountModel *getModel() const;

private:
    qint64 _max_amount;
    QList<WordData> _words_for_model{};
    QList<WordData>::iterator _min_elem{};

    WordFileCountModel *_model{nullptr};
};


#endif //WORDCHARTS_WORDSFREQUENTPROXY_HPP
