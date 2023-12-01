//
// Created by nyanbanan on 01.12.23.
//

#ifndef WORDCHARTS_WORDSTREAM_HPP
#define WORDCHARTS_WORDSTREAM_HPP

#include <QtQml>
#include <QString>

class WordStream {
//    QML_UNCREATABLE("This is interface type")
//    Q_INVOKABLE
    virtual QByteArray getNextWord() = 0;
    virtual void pushNextWord(QByteArray &to) = 0;
};


#endif //WORDCHARTS_WORDSTREAM_HPP
