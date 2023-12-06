#include <QApplication>
#include <QQmlApplicationEngine>
#include <chrono>

#include "FileWordStream.hpp"
#include "Trees/ModifiedPrefixTree.hpp"


int main(int argc, char *argv[]) {
//    QHash<QString, int> test1;
//    FileWordStream ws;
//    QFile device("/home/nyanbanan/CLionProjects/WordCharts/BigTestText.txt");
//    if (device.open(QIODevice::ReadOnly)) {
//        ws.setDevice(&device);
//        QByteArray dirty_word;
//        auto begin = std::chrono::steady_clock::now();
//        ws.pushNextWord(dirty_word);
//        while (dirty_word != "") {
//            if(test1.contains(dirty_word)){
//                test1.handelWord(dirty_word,1);
//            }
//            else{
//                ++test1[dirty_word];
//            }
//            qDebug() << sizeof (test1);
//            ws.pushNextWord(dirty_word);
//            QThread::msleep(10);
//        }
//        auto end = std::chrono::steady_clock::now();
//        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
//        qDebug() << "The time: " << elapsed_ms.count() << " ms\n";
//    }
//    ModifiedPrefixTree _tree;
//    _tree.handelWord("Aboba");
//    _tree.handelWord("Abo");
//    _tree.handelWord("Abobabus");
//    _tree.handelWord("bo");

//    QDir file_path{"../TestText.txt"};
//    QFile data(file_path.absolutePath());
//    if (data.open(QFile::ReadOnly)) {
//        FileWordStream fws;
//        fws.setDevice(&data);
//        QByteArray test;
//        do {
//            fws.pushNextWord(test);
//            qDebug() << QString(test);
//            qDebug() << fws.getProgress();
//        } while (test != "");
//    } else {
//        qDebug() << "open error";
//    }

    QApplication app(argc, argv);

    QQmlApplicationEngine engine; // Создаём движок qml
    // И загружаем в него исходники
    engine.load(QUrl(QStringLiteral("qrc:/WordChartsQml/src/main.qml")));

    return app.exec();
}
