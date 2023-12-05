//
// Created by nyanbanan on 05.12.23.
//

#ifndef WORDCHARTS_WORDFREQUENCYANALYSTTHREAD_HPP
#define WORDCHARTS_WORDFREQUENCYANALYSTTHREAD_HPP


#include <QThread>

#include "FileWordStream.hpp"
#include "Trees/ModifiedPrefixTree.hpp"
#include "WordsFrequentProxy.hpp"
#include "util/NumOfWordsConstant.hpp"

class WordFrequencyAnalystThread: public QThread {
Q_OBJECT
public:
    WordFrequencyAnalystThread(WordsFrequentProxy *frequent_proxy);
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
    void onCountChanged(const QString &word, quint64 count);

protected:
    void run() override;

private:
    void increaseProgress(qint64 bytes_read);
    void dropProgress();

    WordsFrequentProxy* _frequent_proxy{nullptr};
    FileWordStream _word_stream{};
    ModifiedPrefixTree _tree{};

    std::atomic<bool> _pause_required{false};
    qreal _progress{0.0};
    QString _file_path;
    QString _short_filename;

    QMutex _state_mutex{};
    QMutex _progress_mutex{};

    qint64 _bytes_size{};
};


#endif //WORDCHARTS_WORDFREQUENCYANALYSTTHREAD_HPP
