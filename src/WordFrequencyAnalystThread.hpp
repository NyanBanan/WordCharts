//
// Created by nyanbanan on 05.12.23.
//

#ifndef WORDCHARTS_WORDFREQUENCYANALYSTTHREAD_HPP
#define WORDCHARTS_WORDFREQUENCYANALYSTTHREAD_HPP

#include <QThread>

#include "count_classes/CountPrefixTree.hpp"
#include "proxy_models/WordsFrequentProxy.hpp"
#include "src/word_streams/FileWordStream.hpp"
#include "util/NumOfWordsConstant.hpp"

class WordFrequencyAnalystThread : public QThread {
    Q_OBJECT
public:
    explicit WordFrequencyAnalystThread(proxy_models::WordsFrequentProxy* frequent_proxy);
    ~WordFrequencyAnalystThread() override;

    void parseFile(const QString& file_path);

    void pause();
    void unPause();
    void stop();

    [[nodiscard]] qreal getProgress();

signals:
    void progressChanged(qreal progress);
    void errorOccured(QString error);
public slots:
    void onCountChanged(const QString& word, quint32 count);
    void onNewWord(const QString& word, quint32 count);

protected:
    void run() override;

private:
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

#endif    //WORDCHARTS_WORDFREQUENCYANALYSTTHREAD_HPP
