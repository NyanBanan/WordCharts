//
// Created by nyanbanan on 03.12.23.
//

#ifndef WORDCHARTS_WORDSFREQUENTPROXY_HPP
#define WORDCHARTS_WORDSFREQUENTPROXY_HPP

#include <QObject>

#include "WordData.hpp"

namespace proxy_models {
    //Данный класс обрабатывает данные для модели и передает их посредством сигналов
    //Такой подход позволяет избежать проблем при работе с данными модели напрямую из другого потока
    //Основная задача класса - поддерживать в модели util::MAX_WORDS элементов для каждого из обработанных документов и
    //обновлять в них данные
    class WordsFrequentProxy : public QObject {
        Q_OBJECT
    public:
        explicit WordsFrequentProxy(const QString& filename, qint64 max_amount);
        void newData(const QString& word, quint32 count);
        void updateData(const QString& word, quint32 count);

    signals:
        void newModelData(const WordData&);
        void updateModelData(const WordData& old_data, const WordData& new_data);

    private:
        qint64 _max_amount;
        QString _filename;
        QList<WordData> _words_count{};
        quint32 _min_count{};
        qsizetype _min_count_pos{};
    };

}    //namespace proxy_models

#endif    //WORDCHARTS_WORDSFREQUENTPROXY_HPP
