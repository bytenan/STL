#pragma once

#include <iostream>
#include <cassert>

namespace wyn
{
    template <class T>
    class Node
    {
    public:
        T data_;
        Node<T> *prev_;
        Node<T> *next_;
        Node(const T &data = T())
            : data_(data), prev_(nullptr), next_(nullptr)
        {
        }
    };

    template <class T, class Ref, class Ptr>
    class iterator
    {
    public:
        typedef iterator<T, Ref, Ptr> Self;
        Node<T> *pnode_;
        iterator(Node<T> *node)
            : pnode_(node)
        {
        }
        Self &operator++()
        {
            pnode_ = pnode_->next_;
            return *this;
        }
        Self &operator--()
        {
            pnode_ = pnode_->prev_;
            return *this;
        }
        Self operator++(int)
        {
            Self tmp(pnode_);
            pnode_ = pnode_->next_;
            return tmp;
        }
        Self operator--(int)
        {
            Self tmp(pnode_);
            pnode_ = pnode_->prev_;
            return tmp;
        }
        Ref operator*()
        {
            return pnode_->data_;
        }
        Ptr operator->()
        {
            return &pnode_->data_;
        }
        bool operator==(const Self &x) const
        {
            return pnode_ == x.pnode_;
        }
        bool operator!=(const Self &x) const
        {
            return pnode_ != x.pnode_;
        }
    };

    template <class T>
    class list
    {
    public:
        typedef iterator<T, const T &, const T *> const_iterator;
        typedef iterator<T, T &, T *> iterator;
        iterator begin()
        {
            return iterator(head_->next_);
        }
        iterator end()
        {
            return iterator(head_);
        }
        const_iterator begin() const
        {
            return const_iterator(head_->next_);
        }
        const_iterator end() const
        {
            return const_iterator(head_);
        }
        list()
            : head_(nullptr), size_(0)
        {
            head_ = new Node<T>();
            head_->prev_ = head_;
            head_->next_ = head_;
        }
        list(size_t n, const T &data = T())
            : head_(nullptr), size_(0)
        {
            head_ = new Node<T>();
            head_->prev_ = head_;
            head_->next_ = head_;
            while (n--)
            {
                push_back(data);
            }
        }
        list(const list<T> &x)
        {
            head_ = new Node<T>();
            head_->prev_ = head_;
            head_->next_ = head_;
            for (const auto &data : x)
            {
                push_back(data);
            }
        }
        list<T> &operator=(list<T> x)
        {
            swap(x);
            return *this;
        }
        ~list()
        {
            clear();
            delete head_;
            head_ = nullptr;
        }
        void assign(size_t n, const T &data = T())
        {
            clear();
            while (n--)
            {
                push_back(data);
            }
        }
        void push_front(const T &data)
        {
            Node<T> *node = new Node<T>(data);
            Node<T> *next = head_->next_;
            head_->next_ = node;
            node->prev_ = head_;
            node->next_ = next;
            next->prev_ = node;
            ++size_;
        }
        void push_back(const T &data)
        {
            Node<T> *node = new Node<T>(data);
            Node<T> *prev = head_->prev_;
            head_->prev_ = node;
            node->next_ = head_;
            node->prev_ = prev;
            prev->next_ = node;
            ++size_;
        }
        void pop_front()
        {
            assert(!empty());
            Node<T> *next = head_->next_->next_;
            delete head_->next_;
            head_->next_ = next;
            next->prev_ = head_;
            --size_;
        }
        void pop_back()
        {
            assert(!empty());
            Node<T> *prev = head_->prev_->prev_;
            delete head_->prev_;
            head_->prev_ = prev;
            prev->next_ = head_;
            --size_;
        }
        iterator insert(const_iterator pos, const T &data)
        {
            Node<T> *node = new Node<T>(data);
            Node<T> *prev = pos.pnode_->prev_;
            Node<T> *cur = pos.pnode_;
            prev->next_ = node;
            node->prev_ = prev;
            node->next_ = cur;
            cur->prev_ = node;
            ++size_;
            return iterator(node);
        }
        iterator erase(const_iterator pos)
        {
            Node<T> *prev = pos.pnode_->prev_;
            Node<T> *next = pos.pnode_->next_;
            delete pos.pnode_;
            pos.pnode_ = nullptr;
            prev->next_ = next;
            next->prev_ = prev;
            --size_;
            return iterator(next);
        }
        bool empty() const
        {
            return size_ == 0;
        }
        size_t size() const
        {
            return size_;
        }
        size_t max_size() const
        {
            return (size_t)-1;
        }
        void resize(size_t n, const T &data = T())
        {
            if (n > size())
            {
                size_t nums = n - size();
                while (nums--)
                {
                    push_back(data);
                }
            }
            else
            {
                size_t nums = size() - n;
                while (nums--)
                {
                    pop_back();
                }
            }
        }
        void clear()
        {
            Node<T> *cur = head_->next_;
            while (cur != head_)
            {
                Node<T> *next = cur->next_;
                delete cur;
                head_->next_ = next;
                next->prev_ = head_
                cur = next;
            }
            size_ = 0;
        }
        void swap(list<T> &x)
        {
            std::swap(head_, x.head_);
            std::swap(size_, x.size_);
        }

    private:
        Node<T> *head_;
        size_t size_;
    };
}