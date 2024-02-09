//
// Created by nyanbanan on 17.01.24.
//

#ifndef WORDCHARTS_TESTWORDSFREQUENTPROXY_HPP
#define WORDCHARTS_TESTWORDSFREQUENTPROXY_HPP

#include <QObject>
#include <QtTest/QtTest>
#include <QSignalSpy>

#include "src/WordData.hpp"
#include "../WordsFrequentProxy.hpp"

namespace proxy_models::tests {
    struct testWord{
        QString word;
        quint32 count;
    };

    class TestWordsFrequentProxy : public QObject {
        Q_OBJECT
    private slots:
        void newData_data();
        void newData();
        void updateData_data();
        void updateData();
    };
}
#endif    //WORDCHARTS_TESTWORDSFREQUENTPROXY_HPP
