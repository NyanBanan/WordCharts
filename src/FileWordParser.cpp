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

void FileWordParser::startParseDocument(const QString &file_path) {
    QFuture<void> future = QtConcurrent::run(&FileWordParser::parseDocument, this, file_path);
}

void FileWordParser::parseDocument(QString file_path) {
    file_path.replace(QRegularExpression("^(file:[/]{2})"), "");
    QFile device(file_path);
    setCurrentFilename(file_path);
    if (device.open(QIODevice::ReadOnly)) {
        _frequent_proxy = new WordsFrequentProxy{util::MAX_WORDS};
        _frequent_proxy->setModel(_model);
        _bytes_size = device.bytesAvailable();
        ModifiedPrefixTree tree;
        connect(&tree, &ModifiedPrefixTree::countChanged, this, &FileWordParser::onChangeCount);
        QByteArray dirty_word;
        _word_stream.setDevice(&device);
        _word_stream.pushNextWord(dirty_word);

        setCurrentState(State::WORK);
        while (dirty_word != "" && _current_state != STOP) {
            QString word{dirty_word};
            word = word.toLower().replace(QRegularExpression(R"([.,"'()\[\]])"), "");
            tree.insert(word);

            increaseProgress(dirty_word.size());

            _word_stream.pushNextWord(dirty_word);
            qDebug() << getProgress();
            while (_current_state == PAUSE) {
                QThread::msleep(100);
            }
            QThread::msleep(10);
        }
        disconnect(&tree, nullptr, this, nullptr);
        if (_current_state == STOP) {
            dropProgress();
        } else {
            completeProgress();
            setCurrentState(STOP);
        }
    } else {
        emit errorOccured("Device open error");
    }
}

void FileWordParser::setCurrentFilename(const QString &file_path) {
    auto index = file_path.lastIndexOf("/");
    if (index != -1) {
        _short_filename = file_path.mid(index + 1, _short_filename.size() - index);
    } else {
        _short_filename = file_path;
    }
}

void FileWordParser::increaseProgress(qint64 bytes_read) {
//    QMutexLocker locker(&_progress_mutex);
    _progress +=
            (qreal) (bytes_read + 1) / (qreal)
                    _bytes_size;  // +1 to take into account the standard delimiter ' '
    emit progressChanged();
}

qreal FileWordParser::getProgress() {
    return _progress;
}

FileWordParser::State FileWordParser::getCurrentState() const {
    return _current_state;
}

void FileWordParser::setCurrentState(FileWordParser::State currentState) {
    _current_state = currentState;
    emit stateChanged(_current_state);
}

void FileWordParser::onChangeCount(QString word, quint64 count) {
    _frequent_proxy->updateData(word, _short_filename, count);
}

void FileWordParser::dropProgress() {
    _progress = 0.0;
    progressChanged();
}

void FileWordParser::completeProgress() {
    _progress = 1.0;
    progressChanged();
}
