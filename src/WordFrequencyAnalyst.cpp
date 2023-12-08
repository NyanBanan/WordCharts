//
// Created by nyanbanan on 02.12.23.
//

#include "WordFrequencyAnalyst.hpp"

void WordFrequencyAnalyst::setModel(WordFileCountModel* model) {
    _model = model;
}

WordFileCountModel* WordFrequencyAnalyst::getModel() const {
    return _model;
}

void WordFrequencyAnalyst::startParseDocument(QString file_path) {
    if (_model == nullptr) {
        emit errorOccured("Модель не задана");
    }
    _model->resetData();

    auto index = file_path.lastIndexOf("/");
    auto short_filename = file_path;
    if (index != -1) {
        short_filename = file_path.mid(index + 1, short_filename.size() - index);
    }

    auto frequent_proxy = new proxy_models::WordsFrequentProxy(short_filename, util::MAX_WORDS);
    connect(frequent_proxy, &proxy_models::WordsFrequentProxy::newModelData, this, &WordFrequencyAnalyst::onNewData);
    connect(frequent_proxy, &proxy_models::WordsFrequentProxy::updateModelData, this, &WordFrequencyAnalyst::onUpdateData);

    file_path.replace(QRegularExpression("^(file:[/]{2})"), "");

    _analyze_worker = new WordFrequencyAnalystWorker(file_path, frequent_proxy);
    auto work_thread = new QThread;
    frequent_proxy->moveToThread(work_thread);
    _analyze_worker->moveToThread(work_thread);

    connect(work_thread, &QThread::started, _analyze_worker, &WordFrequencyAnalystWorker::work);

    connect(_analyze_worker, &WordFrequencyAnalystWorker::finished, work_thread, &QThread::quit);
    connect(_analyze_worker, &WordFrequencyAnalystWorker::finished, _analyze_worker, &QObject::deleteLater);
    connect(_analyze_worker, &WordFrequencyAnalystWorker::finished, frequent_proxy, &QObject::deleteLater);
    connect(_analyze_worker, &WordFrequencyAnalystWorker::finished, this, &WordFrequencyAnalyst::onWorkEnd);

    connect(_analyze_worker, &WordFrequencyAnalystWorker::progressChanged, this, &WordFrequencyAnalyst::progressChanged);
    connect(_analyze_worker, &WordFrequencyAnalystWorker::errorOccured, this, &WordFrequencyAnalyst::errorOccured);

    work_thread->start();
    setCurrentState(WORK);
}

void WordFrequencyAnalyst::setCurrentState(WordFrequencyAnalyst::State currentState) {
    auto last_state = _current_state;
    _current_state = currentState;
    switch (_current_state) {
        case WORK: {
            if (last_state == PAUSE) {
                _analyze_worker->unPause();
            }
            break;
        }
        case PAUSE: {
            if (last_state != STOP) {
                _analyze_worker->pause();
            }
            break;
        }
        case STOP: {
            if (last_state == PAUSE) {
                _analyze_worker->stop();
            }
            break;
        }
        default:
            break;
    }
    emit stateChanged(_current_state);
}

void WordFrequencyAnalyst::onNewData(const WordData& wd) {
    _model->pushFront(wd);
}

void WordFrequencyAnalyst::onUpdateData(const WordData& old_data, const WordData& new_data) {
    _model->updateData(old_data, new_data);
}

qreal WordFrequencyAnalyst::getProgress() {
    if (_current_state != STOP) {
        return _analyze_worker->getProgress();
    } else {
        return 0.0;
    }
}

WordFrequencyAnalyst::State WordFrequencyAnalyst::getCurrentState() const {
    return _current_state;
}

void WordFrequencyAnalyst::onWorkEnd() {
    setCurrentState(STOP);
}
