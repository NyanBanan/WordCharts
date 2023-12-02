//
// Created by nyanbanan on 02.12.23.
//

#include "FileWordParser.hpp"

//void FileWordParser::setWordStream(FileWordStream *wordStream) {
//    _word_stream = wordStream;
//}

void FileWordParser::setModel(WordFileCountModel *model) {
    _model = model;
}

WordFileCountModel *FileWordParser::getModel() const {
    return _model;
}

void FileWordParser::parseDocument(QString file_path) {
    auto path = file_path.replace(QRegularExpression("^(file:[/]{2})"),"");
    QDir full_path(file_path);
    QFile device(full_path.absolutePath());
    QMap<QString, qint64> map;
    if (device.open(QIODevice::ReadOnly)) {
        QByteArray word;
        _word_stream.setDevice(&device);
        do {
            _word_stream.pushNextWord(word);
            if (map.contains(word)) {
                ++map[word];
            } else {
                map[word] = 1;
            }
            _model->pushBack(word, file_path, map[word]);
            QThread::msleep(10);
        } while (word != "");
    } else {
        emit errorOccured("Device open error");
    }
}

void FileWordParser::startParseDocument(const QString &file_path) {
    QFuture<void> future = QtConcurrent::run(&FileWordParser::parseDocument, this, file_path);
}

qreal FileWordParser::getProgress() {
    return _word_stream.getProgress();
}
