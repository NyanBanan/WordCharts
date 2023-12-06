//
// Created by nyanbanan on 03.12.23.
//

#ifndef WORDCHARTS_WORDSFREQUENTPROXY_HPP
#define WORDCHARTS_WORDSFREQUENTPROXY_HPP

#include <QObject>
#include <QHash>

#include "WordData.hpp"

//Данный класс обрабатывает данные для модели и передает их посредством сигналов
//Такой подход позволяет избежать проблем при работе с данными модели напрямую из другого потока
//Основная задача класса - поддерживать в модели util::MAX_WORDS элементов для каждого из обработанных документов и
//обновлять в них данные
class WordsFrequentProxy : public QObject{
    Q_OBJECT
public:
    explicit WordsFrequentProxy(const QString &filename, qint64 max_amount);

    void updateData(const QString &word, quint64 count);

signals:
    void newData(WordData);
    void updateModelData(WordData old_data, WordData new_data);

private:
    qint64 _max_amount;
    QString _filename;
    QList<WordData> _words_count{};
};


#endif //WORDCHARTS_WORDSFREQUENTPROXY_HPP
