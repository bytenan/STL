#pragma once
#include <iostream>
#include "RBTree.h"

namespace wyn
{
    template<class Key>
    class set
    {
    public:
        class KeyOfValue
        {
        public:
            Key operator()(const Key &key) const
            {
                return key;
            }
        };
        class Compare
        {
        public:
            bool operator()(const Key &lhs, const Key &rhs) const
            {
                return lhs < rhs;
            }
        };
    public:
        typedef typename wyn::tree<Key, Key, KeyOfValue, Compare>::const_iterator iterator;
        iterator begin() const
        {
            return tree_.begin();
        }
        iterator end() const
        {
            return tree_.end();
        }
        std::pair<iterator, bool> insert(const Key &key)
        {
            std::pair<typename wyn::tree<Key, Key, KeyOfValue, Compare>::iterator, bool> tmp = tree_.insert(key);
            return std::pair<iterator, bool>(tmp.first, tmp.second);
        }
        iterator find(const Key &key) const
        {
            return tree_.find(key);
        }
    private:
        wyn::tree<Key, Key, KeyOfValue, Compare> tree_;
    };
}