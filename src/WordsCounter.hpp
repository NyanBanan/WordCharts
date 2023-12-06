//
// Created by nyanbanan on 06.12.23.
//

#ifndef WORDCHARTS_WORDSCOUNTER_HPP
#define WORDCHARTS_WORDSCOUNTER_HPP

#include <QHash>
#include <QString>
#include <QObject>

class WordsCounter : public QObject {
    Q_OBJECT
public:
    void increaseCount(const QString& str, quint64 count);
    signals:
    void countChanged(QString word, quint64 count);
private:
    QHash<QString, quint64> _counter_hash;
};


#endif //WORDCHARTS_WORDSCOUNTER_HPP
