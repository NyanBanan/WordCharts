//
// Created by nyanbanan on 02.12.23.
//

#include "FileWordParser.hpp"

//void FileWordParser::setWordStream(FileWordStream *wordStream) {
//    _word_stream = wordStream;
//}

void FileWordParser::setModel(WordFileCountModel *model) {
    _frequent_proxy.setModel(model);
}

WordFileCountModel *FileWordParser::getModel() const {
    return _frequent_proxy.getModel();
}

void FileWordParser::parseDocument(QString file_path) {
    file_path.replace(QRegularExpression("^(file:[/]{2})"), "");
    QFile device(file_path);
    setCurrentFilename(file_path);
    if (device.open(QIODevice::ReadOnly)) {
        ModifiedPrefixTree tree;
        connect(&tree, &ModifiedPrefixTree::countChanged, this, &FileWordParser::onChangeCount);

        QByteArray word;
        _word_stream.setDevice(&device);

        do {
            _word_stream.pushNextWord(word);
            QString temp{word};
            temp = temp.toLower();
            tree.insert(temp);
            QThread::msleep(10);
        } while (word != "");

        disconnect(&tree, nullptr, this, nullptr);
    } else {
        emit errorOccured("Device open error");
    }
}

void FileWordParser::setCurrentFilename(const QString &file_path) {
    auto index = file_path.lastIndexOf("/");
    if (index != -1) {
        _current_filename = file_path.mid(index + 1, _current_filename.size() - index);
    } else {
        _current_filename = file_path;
    }
}

void FileWordParser::startParseDocument(const QString &file_path) {
    QFuture<void> future = QtConcurrent::run(&FileWordParser::parseDocument, this, file_path);
}

qreal FileWordParser::getProgress() {
    return _word_stream.getProgress();
}

void FileWordParser::onChangeCount(QString word, quint64 count) {
    _frequent_proxy.updateData(word, _current_filename, count);
}
