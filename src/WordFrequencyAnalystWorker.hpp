//
// Created by nyanbanan on 05.12.23.
//

#ifndef WORDCHARTS_WORDFREQUENCYANALYSTWORKER_HPP
#define WORDCHARTS_WORDFREQUENCYANALYSTWORKER_HPP

#include <QObject>

#include "count_classes/CountPrefixTree.hpp"
#include "proxy_models/WordsFrequentProxy.hpp"
#include "src/word_streams/FileWordStream.hpp"
#include "util/NumOfWordsConstant.hpp"

class WordFrequencyAnalystWorker : public QObject {
    Q_OBJECT
public:
    explicit WordFrequencyAnalystWorker(const QString& file_path, proxy_models::WordsFrequentProxy* frequent_proxy);

    void pause();
    void unPause();

    [[nodiscard]] qreal getProgress();

signals:
    void progressChanged(qreal progress);
    void errorOccured(QString error);
    void finished();
public slots:
    void work();
    void stop();

private:
    void completeProgress();
    void increaseProgress(qint64 bytes_read);
    void dropProgress();

    proxy_models::WordsFrequentProxy* _frequent_proxy{nullptr};
    count_classes::CountPrefixTree _tree{};
    word_streams::FileWordStream _word_stream{};

    std::atomic<bool> _pause_required{false};
    std::atomic<bool> _stop_required{false};
    qreal _progress{0.0};
    QString _file_path;
    QString _short_filename;

    QMutex _state_mutex{};
    QMutex _progress_mutex{};

    qint64 _bytes_size{};
};

#endif    //WORDCHARTS_WORDFREQUENCYANALYSTWORKER_HPP
