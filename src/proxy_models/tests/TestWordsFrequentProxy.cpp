//
// Created by nyanbanan on 17.01.24.
//

#include "TestWordsFrequentProxy.hpp"

QTEST_MAIN(proxy_models::tests::TestWordsFrequentProxy)

namespace proxy_models::tests{
    void TestWordsFrequentProxy::newData_data() {
        QTest::addColumn<QStack<testWord>>("test_case");

        QStack<testWord> test_case{{{"Пингвинусы", 1}, {"Пингвинята", 1}, {"Пингвин", 3}, {"Пинг", 4}}};
        QTest::addRow("first_case") << test_case;
    }

    void TestWordsFrequentProxy::newData() {
        QFETCH(QStack<testWord>, test_case);

        QString file_name{""};
        WordsFrequentProxy proxy{file_name, test_case.size()};

        qRegisterMetaType<WordData>();
        QSignalSpy signal_spy(&proxy, &WordsFrequentProxy::newModelData);
        for(auto [str, count]: test_case){
            proxy.onNewData(str, count);
            auto signal = signal_spy.takeFirst();
            auto arg = signal.at(0).value<WordData>();
            QCOMPARE(arg._file, file_name);
            QCOMPARE(arg._word, str);
            QCOMPARE(arg._count, count);
        }
    }

    void TestWordsFrequentProxy::updateData_data() {}

    void TestWordsFrequentProxy::updateData() {}
}