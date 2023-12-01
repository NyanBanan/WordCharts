//
// Created by nyanbanan on 01.12.23.
//

#ifndef WORDCHARTS_FILEWORDSTREAM_HPP
#define WORDCHARTS_FILEWORDSTREAM_HPP

#include <QTextStream>

#include "WordStream.hpp"

//This realization might calculate progress value untruly if target file contains a lot whitespaces
//I think this is not critical because visualization of processing progress in this task may contain some error
class FileWordStream : public WordStream {
public:
    explicit FileWordStream(QFile *stream);

    QByteArray getNextWord() override;

    void pushNextWord(QByteArray &to) override;

    [[nodiscard]] double getProgress() const;

private:
    void increaseProgress(qint64 bytes_read);

    QTextStream _text_stream;
    double _progress{0.0};
    qint64 _bytes_size;
};


#endif //WORDCHARTS_FILEWORDSTREAM_HPP
