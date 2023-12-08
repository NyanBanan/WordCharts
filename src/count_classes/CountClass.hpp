//
// Created by nyanbanan on 07.12.23.
//

#ifndef WORDCHARTS_COUNTCLASS_HPP
#define WORDCHARTS_COUNTCLASS_HPP

#include <QObject>

namespace count_classes {
    class CountClass : public QObject{
        Q_OBJECT
    public:
        virtual void handleWord(const QString& word) = 0;

    signals:
        void newWord(const QString& word, quint32 count);
        void countChanged(const QString& word, quint32 count);
    };

}
#endif    //WORDCHARTS_COUNTCLASS_HPP
