//
// Created by nyanbanan on 03.12.23.
//

#ifndef WORDCHARTS_COUNTPREFIXTREE_HPP
#define WORDCHARTS_COUNTPREFIXTREE_HPP

#include <QMap>
#include <QObject>
#include <QString>
#include <climits>

#include "CountClass.hpp"

namespace count_classes {

    struct PrefixTreeNode {
        ~PrefixTreeNode();

        bool _isEndOfWord{false};
        qint64 _count{0};
        QMap<QChar, PrefixTreeNode*> _childrens{};
    };

    class CountPrefixTree : public CountClass {
        Q_OBJECT

    public:
        void handleWord(const QString& word) override;
        void handleSubWord(const QString& sub_word);

    private:
        PrefixTreeNode _root{};
    };
}    //namespace count_classes

#endif    //WORDCHARTS_COUNTPREFIXTREE_HPP
