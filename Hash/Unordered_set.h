#pragma once
#include <iostream>
#include "HashTable.h"

namespace wyn_set
{
    template <class Key>
    class HashFunc
    {
    public:
        size_t operator()(const Key &key) const
        {
            return (size_t)key;
        }
    };
    template <>
    class HashFunc<std::string>
    {
    public:
        size_t operator()(const std::string &str) const
        {
            size_t res = 0;
            for (const auto &c : str)
            {
                res *= 131;
                res += c;
            }
            return res;
        }
    };

    template <class Key, class HashFcn = HashFunc<Key>>
    class unordered_set
    {
    public:
        class ExtractKey
        {
        public:
            const Key &operator()(const Key &key) const
            {
                return key;
            }
        };

    public:
        typedef typename open::hash<Key, Key, HashFcn, ExtractKey>::const_iterator iterator;

    public:
        iterator begin() const
        {
            return table_.begin();
        }
        iterator end() const
        {
            return table_.end();
        }
        std::pair<iterator, bool> insert(const Key &key)
        {
            std::pair<typename open::hash<Key, Key, HashFcn, ExtractKey>::iterator, bool> tmp = table_.insert(key);
            return std::pair<iterator, bool>(tmp.first, tmp.second);
        }
        iterator erase()
        {
            return table_.erase();
        }

    private:
        open::hash<Key, Key, HashFcn, ExtractKey> table_;
    };
}