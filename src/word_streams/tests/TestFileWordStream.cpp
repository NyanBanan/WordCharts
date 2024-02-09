//
// Created by nyanbanan on 17.01.24.
//

#include "TestFileWordStream.hpp"

QTEST_MAIN(word_streams::tests::TestFileWordStream)
namespace word_streams::tests {
    void TestFileWordStream::initTestCase_data() {
        QTest::addColumn<QByteArray>("test_string");

        QByteArray test_str{"test"};

        QTest::addRow("test_str_for_all_tests") << test_str;
    }

    void TestFileWordStream::getNextWord() {
        QFETCH_GLOBAL(QByteArray, test_string);

        QBuffer device{&test_string};
        device.open(QIODevice::ReadOnly);

        stream.setDevice(&device);

        auto res = stream.getNextWord();
        QCOMPARE(res, test_string);
    }

    void TestFileWordStream::pushNextWord() {
        QFETCH_GLOBAL(QByteArray, test_string);

        QBuffer device{&test_string};
        device.open(QIODevice::ReadOnly);

        stream.setDevice(&device);

        QByteArray res;
        stream.pushNextWord(res);
        QCOMPARE(res, test_string);
    }
}    //namespace word_streams::tests
