//
// Created by nyanbanan on 02.12.23.
//

#ifndef WORDCHARTS_FILEWORDPARSER_HPP
#define WORDCHARTS_FILEWORDPARSER_HPP

#include <QAbstractItemModel>
#include <QtConcurrentRun>

#include "FileWordStream.hpp"
#include "WordFileCountModel.hpp"
#include "WordsFrequentProxy.hpp"
#include "util/NumOfWordsConstant.hpp"

//FileWordParser обрабатывает указанный файл по словам в отдельном потоке, расчитывает прогресс обработки и
//передает необходимые данные в модель посредством _frequent_proxy
class FileWordParser : public QObject {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(WordFileCountModel *model READ getModel WRITE setModel)
    Q_PROPERTY(qreal progress READ getProgress NOTIFY progressChanged)
    Q_PROPERTY(State state READ getCurrentState WRITE setCurrentState NOTIFY stateChanged)

public:
    enum State{
        WORK,
        PAUSE,
        STOP
    };
    Q_ENUM(State)

    //Данный метод запускает метод parseDocument в отдельном потоке при помощи QtConcurrent::run
    Q_INVOKABLE
    void startParseDocument(const QString &file_path);

    //void setWordStream(FileWordStream *wordStream);

    void setModel(WordFileCountModel *model);

    void setCurrentState(State currentState);

    [[nodiscard]] WordFileCountModel *getModel() const;

    [[nodiscard]] qreal getProgress();

    State getCurrentState() const;

signals:
    void progressChanged();
    void stateChanged(FileWordParser::State);
    void errorOccured(QString error_message);
private slots:
    void onChangeCount(QString word, quint64 count);
private:
    void parseDocument(QString file_path);
    void setCurrentFilename(const QString &file_path);
    void increaseProgress(qint64 bytes_read);
    void dropProgress();
    void completeProgress();

    WordsFrequentProxy* _frequent_proxy;
    FileWordStream _word_stream;
    WordFileCountModel* _model;
    QString _short_filename;
    State _current_state{State::STOP};

    qreal _progress{0.0};
    qint64 _bytes_size;
};


#endif //WORDCHARTS_FILEWORDPARSER_HPP
