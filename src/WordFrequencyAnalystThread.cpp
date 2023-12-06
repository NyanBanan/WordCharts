//
// Created by nyanbanan on 05.12.23.
//

#include "WordFrequencyAnalystThread.hpp"

WordFrequencyAnalystThread::WordFrequencyAnalystThread(WordsFrequentProxy *frequent_proxy)
        : _frequent_proxy(frequent_proxy) {
    connect(&_tree, &ModifiedPrefixTree::countChanged, this, &WordFrequencyAnalystThread::onCountChanged);
    _frequent_proxy->moveToThread(this);
}

WordFrequencyAnalystThread::~WordFrequencyAnalystThread() {
    if (_frequent_proxy != nullptr) {
        _frequent_proxy->deleteLater();
    }
}

void WordFrequencyAnalystThread::parseFile(const QString &file_path) {
    _file_path = file_path;
    start();
}

void WordFrequencyAnalystThread::run() {
    if (_frequent_proxy == nullptr) {
        emit errorOccured("Proxy not set");
        exit(1);
    }
    QFile device(_file_path);
    if (device.open(QIODevice::ReadOnly)) {
        _bytes_size = device.bytesAvailable();
        _word_stream.setDevice(&device);

        QByteArray dirty_word;
        _word_stream.pushNextWord(dirty_word);

        while (dirty_word != "") {
            QString word{dirty_word};
            word = word.toLower().replace(QRegularExpression(R"([.,"'()\[\]])"), "");
            _tree.handelWord(word);

            increaseProgress(dirty_word.size());

            _word_stream.pushNextWord(dirty_word);
            while (_pause_required) {
                QThread::msleep(100);
            }
            QThread::msleep(10);
        }
    } else {
        emit errorOccured("Open device error");
        exit(1);
    }
}

qreal WordFrequencyAnalystThread::getProgress() {
    QMutexLocker lock{&_progress_mutex};
    return _progress;
}

void WordFrequencyAnalystThread::increaseProgress(qint64 bytes_read) {
    QMutexLocker lock{&_progress_mutex};
    _progress +=
            (qreal) (bytes_read + 1) / (qreal)
                    _bytes_size;  // +1 to take into account the standard delimiter ' '
    emit progressChanged(_progress);
}

void WordFrequencyAnalystThread::pause() {
    _pause_required = true;
}

void WordFrequencyAnalystThread::unPause() {
    _pause_required = false;
}

void WordFrequencyAnalystThread::stop() {
    dropProgress();
    exit(0);
}

void WordFrequencyAnalystThread::dropProgress()
{
    QMutexLocker lock{&_progress_mutex};
    _progress = 0.0;
    progressChanged(_progress);
}

void WordFrequencyAnalystThread::onCountChanged(const QString &word, quint64 count) {
    _frequent_proxy->updateData(word, count);
}




