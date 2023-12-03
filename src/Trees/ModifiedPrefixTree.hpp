//
// Created by nyanbanan on 03.12.23.
//

#ifndef WORDCHARTS_MODIFIEDPREFIXTREE_HPP
#define WORDCHARTS_MODIFIEDPREFIXTREE_HPP

#include <QString>
#include <QMap>
#include <QObject>

struct Node {
    Node();
    Node(bool isEndOfWord);

    bool _isEndOfWord;
    qint64 _count{0};
    QMap<QChar, Node*> _childrens{};
};

//Данное дерево называется "Модифицированным", т.к оно реализовано для решения конкретной задачи и не подходит для
//использования в общем случае
class ModifiedPrefixTree : public QObject{

Q_OBJECT

public:
    ModifiedPrefixTree() = default;

    Node* insert(const QString &word);

    signals:
    void countChanged(QString word, qint64 count);
private:
    Node root{};
    qint64 _min_count{0};
};


#endif //WORDCHARTS_MODIFIEDPREFIXTREE_HPP
