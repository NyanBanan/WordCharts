//
// Created by nyanbanan on 02.12.23.
//

#ifndef WORDCHARTS_FILEWORDPARSER_HPP
#define WORDCHARTS_FILEWORDPARSER_HPP

#include <QAbstractItemModel>
#include <QtConcurrentRun>

#include "FileWordStream.hpp"
#include "WordFileCountModel.hpp"
#include "FrequentWords.hpp"
#include "util/NumOfWordsConstant.hpp"

class FileWordParser : public QObject {

Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(WordFileCountModel *model READ getModel WRITE setModel)
    Q_PROPERTY(qreal progress READ getProgress)

public:
    //Данный метод запускает метод parseDocument в отдельном потоке при помощи QtConcurrent::run
    Q_INVOKABLE
    void startParseDocument(const QString &file_path);

    //void setWordStream(FileWordStream *wordStream);

    void setModel(WordFileCountModel *model);

    [[nodiscard]] WordFileCountModel *getModel() const;

    [[nodiscard]] qreal getProgress();
signals:
    void errorOccured(QString error_message);
private slots:
    void onChangeCount(QString word, quint64 count);
private:
    void parseDocument(QString file_path);
    void setCurrentFilename(const QString &file_path);

    FrequentWords _frequent_proxy{util::MAX_WORDS};
    FileWordStream _word_stream;
    QString _current_filename;
};


#endif //WORDCHARTS_FILEWORDPARSER_HPP
