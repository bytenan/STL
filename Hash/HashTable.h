#pragma once

#include <iostream>
#include <vector>
#include <utility>

namespace wyn
{
    enum State
    {
        EMPTY,
        EXIST,
        DELETE
    };

    template <class Key, class Value>
    class Data
    {
    public:
        State state_;
        std::pair<Key, Value> kv_;
        Data()
            : state_(EMPTY)
        {
        }
    };

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
            size_t n = 0;
            for (const auto &c : str)
            {
                n *= 131;
                n += c;
            }
            return n;
        }
    };

    template <class Key, class Value, class HashFcn = HashFunc<Key>>
    class hash
    {
    public:
        hash()
            : size_(0)
        {
            table_.resize(10);
        }
        bool insert(const std::pair<Key, Value> &kv)
        {
            if (find(kv.first))
            {
                return false;
            }
            if (size_ * 10 / table_.size() >= 7)
            {
                hash<Key, Value, HashFcn> tmp;
                tmp.table_.resize(table_.size() * 2);
                for (const auto &e : table_)
                {
                    if (e.state_ == EXIST)
                    {
                        tmp.insert(e.kv_);
                    }
                }
                swap(tmp);
            }
            size_t pos = HashFcn()(kv.first) % table_.size();
            while (table_[pos].state_ == EXIST)
            {
                ++pos;
                pos %= table_.size();
            }
            table_[pos].kv_ = kv;
            table_[pos].state_ = EXIST;
            ++size_;
            return true;
        }
        Data<Key, Value> *find(const Key &key) 
        {
            size_t pos = HashFcn()(key) % table_.size();
            while (table_[pos].state_ != EMPTY)
            {
                if (table_[pos].state_ != DELETE && table_[pos].kv_.first == key)
                {
                    return &table_[pos];
                }
                ++pos;
                pos %= table_.size();
            }
            return nullptr;
        }
        bool erase(const Key &key)
        {
            Data<Key, Value> *res = find(key);
            if (!res)
            {
                return false;
            }
            else
            {
                res->state_ = DELETE;
                --size_;
                return true;
            }
        }
        size_t size() const
        {
            return size_;
        }
        void swap(hash<Key, Value> &x)
        {
            std::swap(table_, x.table_);
            std::swap(size_, x.size_);
        }

    private:
        std::vector<Data<Key, Value>> table_;
        size_t size_;
    };
}