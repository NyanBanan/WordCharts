//
// Created by nyanbanan on 03.12.23.
//

#include "WordsFrequentProxy.hpp"

WordsFrequentProxy::WordsFrequentProxy(const QString &filename, qint64 max_amount) : _max_amount(max_amount),
                                                                                     _filename(filename) {}
//Метод updateData увеличивает счетчик вхождения слова в документ и отправляет сигналы на изменение данных в модели
void WordsFrequentProxy::updateData(const QString &word, quint64 count) {
    WordData wd{word, _filename, count};
    //Находим элемент с тем же словом и файлом в списке
    qsizetype ind = _words_count.indexOf(wd);
    if (ind != -1) {
        //Если он найден увеличиваем его счетчик
        _words_count[ind]._count += wd._count;
        //Если он входить в топ _max_amount по частоте, то отправляем сигнал для обновления данных в модели
        if (ind < _max_amount) {
            emit updateModelData(_words_count[ind], _words_count[ind]);
        }
    } else {
        //Если не входит, добавляем его (алгоритмическая сложность QList::push_back O(1) если верить документации)
        _words_count.push_back(wd);
        ind = _words_count.size() - 1;
        //Если прокси коллекция еще не содержит _max_amount элементов, мы отправляем сигнал об изменении данных в
        //основной модели
        if (_words_count.size() <= _max_amount) {
            emit newData(wd);
            //После заполнения коллекции на _max_amount элементов, сортируем коллекцию в порядке убывания
            //Далее при выполнении аглоритма мы поддерживаем только первые _max_amount элементов отсортированными в порядке убывания
            if (_words_count.size() == _max_amount) {
                std::sort(_words_count.begin(), _words_count.end(), std::greater());
            }
        }
    }
    //Если не топовый элемент  встречается чаще, чем последний элемент из топовых, то
    //он занимает место среди топовых и происходит сортировка первых _max_amount элементов
    //_max_amount по популярности элемент занимает _max_amount-1 место в списке
    //Также отправляется сигнал на изменение элемента в модели
     if (ind > _max_amount-1 && _words_count[_max_amount - 1] < _words_count[ind]) {
        emit updateModelData(_words_count[_max_amount - 1], _words_count[ind]);
        _words_count.swapItemsAt(_max_amount - 1, ind);
        std::sort(_words_count.begin(), _words_count.begin() += _max_amount, std::greater());
    }
}
