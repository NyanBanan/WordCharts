//
// Created by nyanbanan on 02.12.23.
//

#ifndef WORDCHARTS_WORDDATA_HPP
#define WORDCHARTS_WORDDATA_HPP


#include <QString>

class WordData {
public:
    WordData(QString word, QString doc);

    [[nodiscard]] const QString &getWord() const;

    [[nodiscard]] const QString &getDoc() const;
private:
    QString _word;
    QString _doc;

    qint64 _hash;
};


#endif //WORDCHARTS_WORDDATA_HPP
