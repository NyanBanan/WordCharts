//
// Created by nyanbanan on 02.12.23.
//

#ifndef WORDCHARTS_FILEWORDPARSER_HPP
#define WORDCHARTS_FILEWORDPARSER_HPP

#include <QAbstractItemModel>
#include <QtConcurrentRun>

#include "FileWordStream.hpp"
#include "WordFileCountModel.hpp"

class FileWordParser : public QObject {
public:
Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(WordFileCountModel *model READ getModel WRITE setModel)
    Q_PROPERTY(qreal progress READ getProgress)

    Q_INVOKABLE
    void startParseDocument(const QString &file_path);

    //void setWordStream(FileWordStream *wordStream);

    void setModel(WordFileCountModel *model);

    [[nodiscard]] WordFileCountModel *getModel() const;

    [[nodiscard]] qreal getProgress();
signals:

    void errorOccured(QString error_message);

private:
    void parseDocument(QString file_path);

    WordFileCountModel *_model{nullptr};
    FileWordStream _word_stream;
};


#endif //WORDCHARTS_FILEWORDPARSER_HPP
