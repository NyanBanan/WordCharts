//
// Created by nyanbanan on 01.12.23.
//

#ifndef WORDCHARTS_FILEWORDSTREAM_HPP
#define WORDCHARTS_FILEWORDSTREAM_HPP

#include <QTextStream>

#include "WordStream.hpp"

namespace word_streams {
    //Данная реализация позволяет выполнять обработку IODevice по словам при помощи QTextStream
    class FileWordStream : public WordStream {
    public:
        void setDevice(QIODevice* device);
        QByteArray getNextWord() override;
        void pushNextWord(QByteArray& to) override;

    private:
        QTextStream _text_stream;
    };
}    //namespace word_streams

#endif    //WORDCHARTS_FILEWORDSTREAM_HPP
