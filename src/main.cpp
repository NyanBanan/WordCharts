#include <QApplication>
#include <QQmlApplicationEngine>

#include "FileWordStream.hpp"


int main(int argc, char *argv[]) {
    QDir file_path{"../TestText.txt"};
    QFile data(file_path.absolutePath());
    if (data.open(QFile::ReadOnly)) {
        FileWordStream fws(&data);
        QByteArray test;
        do {
            fws.pushNextWord(test);
            qDebug() << QString(test);
            qDebug() << fws.getProgress();
        } while (test != "");
    } else {
        qDebug() << "open error";
    }

    QApplication app(argc, argv);

    QQmlApplicationEngine engine; // Создаём движок qml
    // И загружаем в него исходники
    engine.load(QUrl(QStringLiteral("qrc:/WordChartsQml/src/main.qml")));

    return app.exec();
}
