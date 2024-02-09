//
// Created by nyanbanan on 17.01.24.
//

#ifndef WORDCHARTS_TESTFILEWORDSTREAM_HPP
#define WORDCHARTS_TESTFILEWORDSTREAM_HPP

#include <QObject>
#include <QtTest/QtTest>

#include "../FileWordStream.hpp"

namespace word_streams::tests {
    class TestFileWordStream: public QObject {
    Q_OBJECT
    private slots:
        void initTestCase_data();
        void getNextWord();
        void pushNextWord();
    private:
        FileWordStream stream;
    };
}    //namespace word_streams::tests

#endif    //WORDCHARTS_TESTFILEWORDSTREAM_HPP
