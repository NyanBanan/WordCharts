//
// Created by nyanbanan on 03.12.23.
//

#ifndef WORDCHARTS_FREQUENTWORDS_HPP
#define WORDCHARTS_FREQUENTWORDS_HPP

#include "Trees/ModifiedPrefixTree.hpp"
#include "WordData.hpp"
#include "WordFileCountModel.hpp"

class FrequentWords{
public:
    explicit FrequentWords(qint64 max_amount);

    void updateData(const QString &word, const QString &file, quint64 count);
    void setModel(WordFileCountModel *model);
    [[nodiscard]] WordFileCountModel *getModel() const;

private:
    qint64 _max_amount;
    QList<WordData> _words_for_model{};
    QList<WordData>::iterator _min_elem{};

    WordFileCountModel *_model{nullptr};
};


#endif //WORDCHARTS_FREQUENTWORDS_HPP
