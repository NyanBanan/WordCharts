//
// Created by nyanbanan on 02.12.23.
//

#include "WordFrequencyAnalyst.hpp"

void WordFrequencyAnalyst::setModel(WordFileCountModel *model) {
    _model = model;
}

WordFileCountModel *WordFrequencyAnalyst::getModel() const {
    return _model;
}

void WordFrequencyAnalyst::startParseDocument(QString file_path) {
    if(_model == nullptr){
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

    _parse_thread = new WordFrequencyAnalystThread(frequent_proxy);

    connect(_parse_thread, &WordFrequencyAnalystThread::finished, _parse_thread, &QObject::deleteLater);
    connect(_parse_thread, &WordFrequencyAnalystThread::finished, this, &WordFrequencyAnalyst::onThreadEnd);
    connect(_parse_thread, &WordFrequencyAnalystThread::progressChanged, this, &WordFrequencyAnalyst::progressChanged);
    connect(_parse_thread, &WordFrequencyAnalystThread::errorOccured, this, &WordFrequencyAnalyst::errorOccured);

    file_path.replace(QRegularExpression("^(file:[/]{2})"), "");

    _parse_thread->parseFile(file_path);
    setCurrentState(WORK);
}

void WordFrequencyAnalyst::setCurrentState(WordFrequencyAnalyst::State currentState) {
    auto last_state = _current_state;
    _current_state = currentState;
    switch (_current_state) {
        case WORK: {
            if (last_state == PAUSE) {
                _parse_thread->unPause();
            }
            break;
        }
        case PAUSE: {
            if (last_state != STOP) {
                _parse_thread->pause();
            }
            break;
        }
        case STOP: {
            if (last_state == PAUSE) {
                _parse_thread->stop();
            }
            break;
        }
        default:
            break;
    }
    emit stateChanged(_current_state);
}

void WordFrequencyAnalyst::onNewData(const WordData &wd) {
    _model->pushFront(wd);
}

void WordFrequencyAnalyst::onUpdateData(const WordData &old_data, const WordData &new_data) {
    _model->updateData(old_data, new_data);
}

qreal WordFrequencyAnalyst::getProgress() {
    if (_current_state != STOP) {
        return _parse_thread->getProgress();
    } else {
        return 0.0;
    }
}

WordFrequencyAnalyst::State WordFrequencyAnalyst::getCurrentState() const {
    return _current_state;
}

void WordFrequencyAnalyst::onThreadEnd() {
    setCurrentState(STOP);
}

