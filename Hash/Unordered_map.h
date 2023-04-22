#pragma once
#include <iostream>
#include "HashTable.h"

namespace wyn_map
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

    template <class Key, class Value, class HashFcn = HashFunc<Key>>
    class unordered_map
    {
    public:
        class ExtractKey
        {
        public:
            const Key &operator()(const std::pair<const Key, Value> &kv) const
            {
                return kv.first;
            }
        };

    public:
        typedef typename open::hash<Key, std::pair<const Key, Value>, HashFcn, ExtractKey>::const_iterator const_iterator;
        typedef typename open::hash<Key, std::pair<const Key, Value>, HashFcn, ExtractKey>::iterator iterator;

    public:
        iterator begin()
        {
            return table_.begin();
        }
        iterator end()
        {
            return table_.end();
        }
        const_iterator begin() const
        {
            return table_.begin();
        }
        const_iterator end() const
        {
            return table_.end();
        }
        std::pair<iterator, bool> insert(const std::pair<const Key, Value> &kv)
        {
            return table_.insert(kv);
        }
        Value &operator[](const Key &key)
        {
            std::pair<iterator, bool> res = insert(std::pair<const Key, Value>(key, Value()));
            return res.first->second;
        }
        iterator erase()
        {
            return table_.erase();
        }

    private:
        open::hash<Key, std::pair<const Key, Value>, HashFcn, ExtractKey> table_;
    };
}