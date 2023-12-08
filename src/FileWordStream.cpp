//
// Created by nyanbanan on 01.12.23.
//

#include "FileWordStream.hpp"

void FileWordStream::setDevice(QIODevice *device) {
    _text_stream.setDevice(device);
}

QByteArray FileWordStream::getNextWord() {
    QByteArray ret;
    _text_stream >> ret;
    return ret;
}

void FileWordStream::pushNextWord(QByteArray &to) {
    _text_stream >> to;
}
