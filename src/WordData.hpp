//
// Created by nyanbanan on 02.12.23.
//

#ifndef WORDCHARTS_WORDDATA_HPP
#define WORDCHARTS_WORDDATA_HPP

#include <QString>

struct WordData {
    WordData(const QString& word, const QString& doc, quint32 count = 1);

    bool operator== (const WordData& right) const;
    bool operator< (const WordData& right) const;
    bool operator> (const WordData& right) const;

    QString _word;
    QString _file;
    quint32 _count;
};

#endif    //WORDCHARTS_WORDDATA_HPP
