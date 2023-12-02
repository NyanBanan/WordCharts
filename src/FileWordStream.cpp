//
// Created by nyanbanan on 01.12.23.
//

#include "FileWordStream.hpp"

void FileWordStream::setDevice(QIODevice *device) {
    _text_stream.setDevice(device);
    _bytes_size = _text_stream.device()->bytesAvailable();
}

QByteArray FileWordStream::getNextWord() {
    QByteArray ret;
    _text_stream >> ret;
    increaseProgress(ret.size());
    return ret;
}

void FileWordStream::pushNextWord(QByteArray &to) {
    _text_stream >> to;
    increaseProgress(to.size());
}

double FileWordStream::getProgress() {
    QMutexLocker locker(&_progress_mutex);
    return _progress;
}

void FileWordStream::increaseProgress(qint64 bytes_read) {
    QMutexLocker locker(&_progress_mutex);
    _progress +=
            (qreal) (bytes_read + 1) / (qreal) _bytes_size;  // +1 to take into account the standard delimiter ' '
}
