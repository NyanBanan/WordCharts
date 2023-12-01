//
// Created by nyanbanan on 01.12.23.
//

#include "FileWordStream.hpp"

FileWordStream::FileWordStream(QFile *stream) {
    _text_stream.setDevice(stream);
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

double FileWordStream::getProgress() const {
    return _progress;
}

void FileWordStream::increaseProgress(qint64 bytes_read) {
    _progress += (double) (bytes_read + 1) / (double) _bytes_size;  // +1 to take into account the standard delimiter ' '
}
