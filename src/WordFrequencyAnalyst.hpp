//
// Created by nyanbanan on 02.12.23.
//

#ifndef WORDCHARTS_WORDFREQUENCYANALYST_HPP
#define WORDCHARTS_WORDFREQUENCYANALYST_HPP

#include <QAbstractItemModel>

#include "FileWordStream.hpp"
#include "WordFileCountModel.hpp"
#include "WordsFrequentProxy.hpp"
#include "util/NumOfWordsConstant.hpp"
#include "WordFrequencyAnalystThread.hpp"

//WordFrequencyAnalyst обрабатывает указанный файл по словам в отдельном потоке, расчитывает прогресс обработки и
//передает необходимые данные в модель посредством _frequent_proxy
class WordFrequencyAnalyst : public QObject {
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

    Q_INVOKABLE
    void startParseDocument(QString file_path);

    void setModel(WordFileCountModel *model);

    void setCurrentState(WordFrequencyAnalyst::State currentState);

    [[nodiscard]] WordFileCountModel *getModel() const;

    [[nodiscard]] qreal getProgress();

    [[nodiscard]] State getCurrentState() const;

signals:
    void progressChanged();
    void stateChanged(WordFrequencyAnalyst::State);
    void errorOccured(QString error_message);

private slots:
    void onNewData(const WordData &wd);
    void onUpdateData(const WordData &old_data, const WordData &new_data);
    void onThreadEnd();

private:
    State _current_state{State::STOP};
    FileWordStream _word_stream;

    WordFrequencyAnalystThread* _parse_thread;
    WordFileCountModel* _model{nullptr};
};


#endif //WORDCHARTS_WORDFREQUENCYANALYST_HPP
