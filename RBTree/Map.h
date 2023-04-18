#pragma once
#include <iostream>
#include <utility>
#include "RBTree.h"

namespace wyn
{
    template<class Key, class Value>
    class map
    {
    public:
        class KeyOfValue
        {
        public:
            const Key operator()(const std::pair<const Key, Value> &kv) const
            {
                return kv.first;
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
        typedef typename wyn::tree<Key, std::pair<const Key, Value>, KeyOfValue, Compare>::const_iterator const_iterator;
        typedef typename wyn::tree<Key, std::pair<const Key, Value>, KeyOfValue, Compare>::iterator iterator;

        iterator begin()
        {
            return tree_.begin();
        }
        iterator end()
        {
            return tree_.end();
        }
        const_iterator begin() const
        {
            return tree_.begin();
        }
        const_iterator end() const
        {
            return tree_.end();
        }
        std::pair<iterator, bool> insert(const std::pair<const Key, Value> &kv)
        {
            return tree_.insert(kv);
        }
        Value &operator[](const Key &key)
        {
            std::pair<iterator, bool> tmp = insert(std::pair<const Key, Value>(key, Value()));
            return tmp.first->second;
        }
        iterator find(const Key &key)
        {
            return tree_.find(key);
        }
        const_iterator find(const Key &key) const
        {
            return tree_.find(key);
        }
    private:
        wyn::tree<Key, std::pair<const Key, Value>, KeyOfValue, Compare> tree_;
    };
}