#pragma once

#include <iostream>
#include <vector>
#include <utility>

namespace closed
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

namespace open
{
    template <class Value>
    class Node
    {
    public:
        Value value_;
        Node<Value> *next_;
        Node(const Value &value)
            : value_(value), next_(nullptr)
        {
        }
    };

    template <class Key, class Value, class HashFcn, class ExtractKey>
    class hash;

    template <class Key, class Value, class HashFcn, class ExtractKey>
    class iterator
    {
    public:
        typedef iterator<Key, Value, HashFcn, ExtractKey> Self;
        typedef Value &Ref;
        typedef Value *Ptr;

        hash<Key, Value, HashFcn, ExtractKey> *phash_;
        Node<Value> *pvalue_;
        iterator(hash<Key, Value, HashFcn, ExtractKey> *phash, Node<Value> *pvalue)
            : phash_(phash), pvalue_(pvalue)
        {
        }
        Ref operator*() const
        {
            return pvalue_->value_;
        }
        Ptr operator->() const
        {
            return &pvalue_->value_;
        }
        Self &operator++()
        {
            if (pvalue_->next_)
            {
                pvalue_ = pvalue_->next_;
            }
            else
            {
                size_t pos = HashFcn()(ExtractKey()(pvalue_->value_)) % phash_->table_.size();
                ++pos;
                while (pos < phash_->table_.size())
                {
                    if (phash_->table_[pos])
                    {
                        pvalue_ = phash_->table_[pos];
                        break;
                    }
                    ++pos;
                }
                if (pos == phash_->table_.size())
                {
                    pvalue_ = nullptr;
                }
            }
            return *this;
        }
        Self &operator--()
        {
            size_t pos = HashFcn()(ExtractKey()(pvalue_->value_)) % phash_->table_.size();
            Node<Value> *prev = nullptr;
            Node<Value> *cur = phash_->table_[pos];
            while (cur != pvalue_)
            {
                prev = cur;
                cur = cur->next_;
            }
            if (prev)
            {
                pvalue_ = prev;
            }
            else
            {
                while (--pos)
                {
                    if (phash_->table_[pos])
                    {
                        pvalue_ = phash_->table_[pos];
                    }
                }
                if (pos == 0 && !phash_->table_[pos])
                {
                    pvalue_ = nullptr;
                }
            }
            return *this;
        }
        bool operator==(const Self &x) const
        {
            return pvalue_ == x.pvalue_;
        }
        bool operator!=(const Self &x) const
        {
            return pvalue_ != x.pvalue_;
        }
    };

    template <class Key, class Value, class HashFcn, class ExtractKey>
    class hash
    {
    public:
        friend iterator<Key, Value, HashFcn, ExtractKey>;
        typedef iterator<Key, Value, HashFcn, ExtractKey> iterator;

        iterator begin()
        {
            for (size_t i = 0; i < table_.size(); ++i)
            {
                if (table_[i])
                {
                    return iterator(this, table_[i]);
                }
            }
            return end();
        }
        iterator end()
        {
            return iterator(this, nullptr);
        }
        hash()
            : size_(0)
        {
            table_.resize(10);
        }
        bool insert(const Value &value)
        {
            if (find(HashFcn()(ExtractKey()(value))))
            {
                return false;
            }
            if (size_ == table_.size())
            {
                std::vector<Node<Value> *> tmp;
                for (Node<Value> *&cur : table_)
                {
                    while (cur)
                    {
                        Node<Value> *next = cur->next_;
                        size_t pos = HashFcn()(ExtractKey()(cur->value_)) % table_.size();
                        cur->next_ = tmp[pos];
                        tmp[pos] = cur;
                        cur = next;
                    }
                    cur = nullptr;
                }
                table_.swap(tmp);
            }
            size_t pos = HashFcn()(ExtractKey()(value)) % table_.size();
            Node<Value> *node = new Node<Value>(value);
            node->next_ = table_[pos];
            table_[pos] = node;
            ++size_;
            return true;
        }

        Node<Value> *find(const Key &key)
        {
            size_t pos = HashFcn()(ExtractKey()(key)) % table_.size();
            Node<Value> *cur = table_[pos];
            while (cur)
            {
                if (ExtractKey()(cur->value_) == key)
                {
                    return cur;
                }
                cur = cur->next_;
            }
            return nullptr;
        }

        void swap(hash<Key, Value, HashFcn, ExtractKey> &x)
        {
            std::swap(table_, x.table_);
            std::swap(size_, x.size_);
        }

    private:
        std::vector<Node<Value> *> table_;
        size_t size_;
    };
}