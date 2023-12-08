//
// Created by nyanbanan on 03.12.23.
//

#include "WordsFrequentProxy.hpp"

namespace proxy_models {

    WordsFrequentProxy::WordsFrequentProxy(const QString& filename, qint64 max_amount)
        : _max_amount(max_amount),
          _filename(filename) {}

    void WordsFrequentProxy::newData(const QString& word, quint32 count) {
        WordData wd{word, _filename, count};
        _words_count.push_back(wd);
        //Если прокси коллекция еще не содержит _max_amount элементов, мы отправляем сигнал об изменении данных в
        //основной модели
        if (_words_count.size() <= _max_amount) {
            emit newModelData(wd);
            //После заполнения коллекции на _max_amount элементов, находим редчайший топовый и сохраняем его индекс и значение _count
            if (_words_count.size() == _max_amount) {
                auto min_elem = std::min_element(_words_count.begin(), _words_count.end());
                _min_count_pos = min_elem - _words_count.begin();
                _min_count = min_elem->_count;
            }
        }
    }

    //Метод updateData увеличивает счетчик вхождения слова в документ и отправляет сигналы на изменение данных в модели
    //Элементы встречающиеся чаще всего в тексте - первые _max_amount элементов (топовые элементы)
    //Элемент среди первых _max_amount с самым малым значением _count - Самый редкий среди первых _max_amount элементов (редчайший топовый)
    void WordsFrequentProxy::updateData(const QString& word, quint32 count) {
        WordData wd{word, _filename, count};
        //Находим элемент с тем же словом и файлом в списке (на случай непредвиденных ошибок, индекс проверяется на валидность)
        qsizetype ind = _words_count.indexOf(wd);
        if (ind != -1) {
            //Если он найден увеличиваем его счетчик
            _words_count[ind]._count += wd._count;
            //Если он является топовым, то отправляем сигнал для обновления данных в модели
            if (ind < _max_amount) {
                emit updateModelData(_words_count[ind], _words_count[ind]);
            }
            //Мы храним индекс и частоту появления самого редкого среди первых _max_amount элементов (редчайший топовый)
            //Если встречается элемент не входящий в топовые и при этом встречающийся чаще чем редчайший топовый,
            //то мы отправляем сигнал основной модели, который заменяет редчайший топовый элемент на новый
            //после этого мы меняем местами эти элементы и находим новое самое редкое из первых _max_amount
            else if (_min_count < _words_count[ind]._count) {
                emit updateModelData(_words_count[_min_count_pos], _words_count[ind]);
                _words_count.swapItemsAt(_min_count_pos, ind);
                auto min_elem = std::min_element(_words_count.begin(), _words_count.begin() += _max_amount);
                _min_count_pos = min_elem - _words_count.begin();
                _min_count = min_elem->_count;
            }
        }
    }
}    //namespace proxy_models
