//
// Created by nyanbanan on 17.01.24.
//

#include "TestWordsFrequentProxy.hpp"

QTEST_MAIN(proxy_models::tests::TestWordsFrequentProxy)

namespace proxy_models::tests {
    void TestWordsFrequentProxy::newData_data() {
        //Тестовые данные, word - слово для вставки, count - кол-во вхождений слова в коллекцию
        //Сигнал newModelData должен вернуть то же значение в поле _count, что и передано в метод onNewData
        QTest::addColumn<QStack<testWord>>("test_case");
        QTest::addColumn<qint64>("max_amount");

        QStack<testWord> test_case{{{"Пингвинусы", 1}, {"Пингвинята", 1}, {"Пингвин", 3}, {"Пинг", 4}}};
        QTest::addRow("first_case") << test_case << qint64(3);
    }

    void TestWordsFrequentProxy::newData() {
        QFETCH(QStack<testWord>, test_case);

        QString file_name{""};
        WordsFrequentProxy proxy{file_name, test_case.size()};

        QSignalSpy signal_spy(&proxy, &WordsFrequentProxy::newModelData);
        for (auto [str, count] : test_case) {
            proxy.onNewData(str, count);
            auto signal = signal_spy.takeFirst();
            auto arg = signal.at(0).value<WordData>();
            QCOMPARE(arg._file, file_name);
            QCOMPARE(arg._word, str);
            QCOMPARE(arg._count, count);
        }
    }

    void TestWordsFrequentProxy::updateData_data() {
        //Данные для инициализации прокси модели word - слово для вставки, count - кол-во вхождений слова в коллекцию
        QTest::addColumn<QStack<testWord>>("start_data");
        //Тестовые данные: word - слово для обновления, count - кол-во вхождений слова в коллекцию
        //new_data._count cигнала updateModelData должен быть равен count
        //Если равен 0 - сигнал не должен быть вызван, следовательно signal_spy.count должен быть равен 0
        QTest::addColumn<QStack<testWord>>("test_case");

        QStack<testWord> start_data_1{{{"Пингвинусы", 1}, {"Пингвинята", 1}, {"Пингвин", 3}, {"Пинг", 4}}};
        QStack<testWord> test_case_1{{{"Пинг", 5}, {"Слово", 0}, {"Слово", 2}}};

        QTest::addRow("first_case") << start_data_1 << test_case_1;
    }

    void TestWordsFrequentProxy::updateData() {
        QFETCH(QStack<testWord>, start_data);
        QFETCH(QStack<testWord>, test_case);

        QString file_name{""};
        WordsFrequentProxy proxy{file_name, start_data.size()};

        for (auto [str, count] : start_data) {
            proxy.onNewData(str, count);
        }

        QSignalSpy signal_spy(&proxy, &WordsFrequentProxy::updateModelData);
        for (auto [str, count] : test_case) {
            //Обновляем данные о вхождениях слова в коллекцию (добавляем 1 вхождение уже существующему слову)
            if(proxy.onUpdateData(str, 1)){
                //Если слово есть в коллекции, то проверяем приходящий сигнал
                auto signal = signal_spy.takeFirst();
                auto arg = signal.at(1).value<WordData>();
                QCOMPARE(arg._file, file_name);
                QCOMPARE(arg._word, str);
                QCOMPARE(arg._count, count);
            }
            else{
                //Если слова не было в коллекции, то добавляем его, при этом не должно быть инициировано сигналов updateModelData
                proxy.onNewData(str, 1);
                QVERIFY(signal_spy.count() == 0);
            }
        }
    }
}    //namespace proxy_models::tests
