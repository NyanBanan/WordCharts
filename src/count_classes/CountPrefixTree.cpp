//
// Created by nyanbanan on 03.12.23.
//

#include "CountPrefixTree.hpp"

namespace count_classes {

    PrefixTreeNode::~PrefixTreeNode() {
        for(auto child:_childrens){
            delete child;
        }
    }

    void CountPrefixTree::handleWord(const QString& word) {
        auto cur_node = &_root;
        //Данная переменная нужна, в случае если во время прохода по ребрам появится новый минимальный элемент
        qsizetype ch_index{0};
        quint64 min_count_on_way{std::numeric_limits<quint64>::max()};
        for (auto ch : word) {
            ++ch_index;
            auto next_node = cur_node->_childrens[ch];
            if (next_node == nullptr) {
                cur_node->_childrens.insert(ch, new PrefixTreeNode());
                cur_node = cur_node->_childrens[ch];
            } else {
                cur_node = next_node;
            }
            if (++cur_node->_count < min_count_on_way) {
                min_count_on_way = cur_node->_count;
            }
            //Этот условный оператор необходим для уменьшения количества операций при решении задачи поиска слов по вхождению
            //Выполняя вставку нового слова, мы находу проверяем встречаются ли нам на пути ранее рассмотренные слова,
            // являющиеся подстрокой вставляемого слова и увеличиваем их счетчик вхождений
            if (cur_node->_isEndOfWord) {
                countChanged(word.left(ch_index), 1);
            }
        }
        //По окончании вставки последняя нода получает статус "Конец слова" и отправляется сигнал о появлении нового слова
        if (!cur_node->_isEndOfWord) {
            cur_node->_isEndOfWord = true;
            newWord(word, min_count_on_way);
        }

        //Включаем в дерево подстроки вставленного слова, но без метки "Конец слова"
        QString sub_word{word.last(word.size() - 1)};
        while (sub_word.size() >= 1) {
            handleSubWord(sub_word);
            sub_word = sub_word.last(sub_word.size() - 1);
        }
    }

    void CountPrefixTree::handleSubWord(const QString& sub_word) {
        auto cur_node = &_root;
        qsizetype ch_index{0};
        for (auto ch : sub_word) {
            ++ch_index;
            auto next_node = cur_node->_childrens[ch];
            if (next_node == nullptr) {
                cur_node->_childrens.insert(ch, new PrefixTreeNode());
                cur_node = cur_node->_childrens[ch];
            } else {
                cur_node = next_node;
            }
            ++cur_node->_count;
            if (cur_node->_isEndOfWord) {
                countChanged(sub_word.left(ch_index), 1);
            }
        }
    }
}    //namespace count_classes
