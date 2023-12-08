//
// Created by nyanbanan on 05.12.23.
//

#include "WordFrequencyAnalystWorker.hpp"

WordFrequencyAnalystWorker::WordFrequencyAnalystWorker(const QString& file_path,
                                                       proxy_models::WordsFrequentProxy* frequent_proxy)
    : _frequent_proxy(frequent_proxy), _file_path(file_path) {
    connect(&_tree, &count_classes::CountClass::countChanged, this, &WordFrequencyAnalystWorker::onCountChanged);
    connect(&_tree, &count_classes::CountClass::newWord, this, &WordFrequencyAnalystWorker::onNewWord);
}

void WordFrequencyAnalystWorker::work() {
    if (_frequent_proxy == nullptr) {
        emit errorOccured("Proxy not set");
        exit(1);
    }
    QFile device(_file_path);
    if (device.open(QIODevice::ReadOnly)) {
        _bytes_size = device.bytesAvailable();
        _word_stream.setDevice(&device);

        QByteArray dirty_word;
        auto begin = std::chrono::steady_clock::now();
        _word_stream.pushNextWord(dirty_word);

        while (dirty_word != "" && !_stop_required) {
            QString word{dirty_word};
            word = word.toLower().replace(QRegularExpression(R"([.,"'()\[\]!?])"), "");
            if (!word.isEmpty()) {
                _tree.handleWord(word);
            }
            increaseProgress(dirty_word.size());

            _word_stream.pushNextWord(dirty_word);
            while (_pause_required && !_stop_required) {
                QThread::msleep(100);
            }
            QThread::msleep(5);
        }
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        qDebug() << "The time: " << elapsed_ms.count() << " ms\n";
        completeProgress();
    } else {
        emit errorOccured("Open device error");
    }
    emit finished();
}

qreal WordFrequencyAnalystWorker::getProgress() {
    QMutexLocker lock{&_progress_mutex};
    return _progress;
}

void WordFrequencyAnalystWorker::increaseProgress(qint64 bytes_read) {
    QMutexLocker lock{&_progress_mutex};
    _progress += (qreal)(bytes_read + 1) / (qreal)_bytes_size;    // +1 to take into account the standard delimiter ' '
    emit progressChanged(_progress);
}

void WordFrequencyAnalystWorker::completeProgress() {
    QMutexLocker lock{&_progress_mutex};
    _progress = 1.0;
    progressChanged(_progress);
}

void WordFrequencyAnalystWorker::dropProgress() {
    QMutexLocker lock{&_progress_mutex};
    _progress = 0.0;
    progressChanged(_progress);
}

void WordFrequencyAnalystWorker::pause() {
    _pause_required = true;
}

void WordFrequencyAnalystWorker::unPause() {
    _pause_required = false;
}

void WordFrequencyAnalystWorker::stop() {
    dropProgress();
    _stop_required = true;
}

void WordFrequencyAnalystWorker::onCountChanged(const QString& word, quint32 count) {
    _frequent_proxy->updateData(word, count);
}

void WordFrequencyAnalystWorker::onNewWord(const QString& word, quint32 count) {
    _frequent_proxy->newData(word, count);
}
