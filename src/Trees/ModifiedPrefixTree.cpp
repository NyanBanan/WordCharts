//
// Created by nyanbanan on 03.12.23.
//

#include "ModifiedPrefixTree.hpp"

Node::Node(bool isEndOfWord) : _isEndOfWord(isEndOfWord) {
}

Node::Node() : Node(false) {}

Node *ModifiedPrefixTree::insert(const QString &word) {
    auto cur_node = &root;
    //Данная переменная нужна, в случае если во время прохода по ребрам появится новый минимальный элемент
    QString substr{};
    for (auto ch: word) {
        substr += ch;
        //Этот условный оператор необходим для уменьшения количества операций при решении задачи поиска слов по вхождению
        //Выполняя вставку нового слова, мы находу проверяем встречаются ли нам на пути ранее рассмотренные слова,
        // являющиеся подстрокой вставляемого слова и увеличиваем их счетчик вхождений
        if (cur_node->_isEndOfWord) {
            countChanged(substr, ++cur_node->_count);
        }
        auto next_node = cur_node->_childrens[ch];
        if (next_node == nullptr) {
            cur_node->_childrens.insert(ch, new Node(false));
            cur_node = cur_node->_childrens[ch];
        } else {
            cur_node = next_node;
        }
    }
    //По окончании вставки последняя нода получает статус "Конец слова" и счетчику прибавляется 1
    cur_node->_isEndOfWord = true;
    countChanged(substr, ++cur_node->_count);
    return cur_node;
}
