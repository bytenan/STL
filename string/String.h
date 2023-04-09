#pragma once

#include <iostream>
#include <cstring>
#include <cassert>

namespace wyn
{
    class string
    {
    public:
        typedef char *iterator;
        typedef const char *const_iterator;
        iterator begin()
        {
            return s_;
        }
        iterator end()
        {
            return s_ + size_;
        }
        const_iterator begin() const
        {
            return s_;
        }
        const_iterator end() const
        {
            return s_ + size_;
        }
        string(const char *s = "")
            : s_(nullptr), size_(0), capacity_(0)
        {
            size_ = strlen(s);
            capacity_ = strlen(s);
            s_ = new char[capacity_ + 1];
            strcpy(s_, s);
        }
        string(const string &str)
            : s_(nullptr), size_(0), capacity_(0)
        {
            size_ = str.size();
            capacity_ = str.capacity();
            s_ = new char[capacity_ + 1];
            strcpy(s_, str.c_str());
        }
        string &operator=(string str)
        {
            if (this != &str)
            {
                swap(str);
            }
            return *this;
        }
        ~string()
        {
            delete s_;
            size_ = 0;
            capacity_ = 0;
        }
        void resize(size_t n, char c = 'x')
        {
            reserve(n);
            if (n <= size_)
            {
                *(s_ + n) = '\0';
            }
            else
            {
                for (size_t i = size_; i < capacity_; ++i)
                {
                    *(s_ + i) = c;
                }
                *(s_ + capacity_) = '\0';
            }
            size_ = n;
        }
        void reserve(size_t n = 0)
        {
            if (n > capacity_)
            {
                char *tmp = new char[n + 1];
                strcpy(tmp, s_);
                delete[] s_;
                s_ = tmp;
                capacity_ = n;
            }
        }
        string &push_back(char c)
        {
            reserve(size_+1);
            s_[size_++] = c;
            s_[size_] = '\0';
            return *this;
        }
        string &operator+=(const string &str)
        {
            append(str);
            return *this;
        }
        string &append(const string &str)
        {
            reserve(size_ + str.size_);
            for (size_t i = 0; i < str.size(); ++i)
            {
                s_[size_++] = str[i];
            }
            s_[size_] = '\0';
            return *this;
        }
        string &assign(const string &str)
        {
            clear();
            append(str);
            return *this;
        }
        string &insert(size_t pos, const string &str)
        {
            assert(pos >= 0);
            assert(pos <= size_);
            size_t len = str.size();
            reserve(size_ + len);
            size_t end = size_;
            while (end > pos)
            {
                s_[end+len] = s_[end];
                --end;
            }
            s_[end+len] = s_[end];
            --end;
            for (size_t i = 0; i < len; ++i)
            {
                s_[pos++] = str[i];
                ++size_;
            }
            return *this;
        }
        string &erase(size_t pos, size_t len = npos)
        {
            assert(pos >= 0);
            assert(pos <= size_);
            if (len >= size_ - pos)
            {
                s_[pos] = '\0';
                size_ = pos;
            }
            else
            {
                while (pos + len <= capacity_)
                {
                    s_[pos] = s_[pos+len];
                    ++pos;
                }
                size_ -= len;
            }
            return *this;
        }
        char &operator[](size_t pos)
        {
            return *(s_ + pos);
        }
        const char &operator[](size_t pos) const
        {
            return *(s_ + pos);
        }
        const char *c_str() const
        {
            return s_;
        }
        size_t size() const
        {
            return size_;
        }
        size_t capacity() const
        {
            return capacity_;
        }
        size_t max_size() const
        {
            return (int)npos;
        }
        void clear()
        {
            if (s_)
            {
                *s_ = '\0';
                size_ = 0;
            }
        }
        bool empty() const
        {
            return size_ == 0;
        }
        void swap(string &str)
        {
            std::swap(s_, str.s_);
            std::swap(size_, str.size_);
            std::swap(capacity_, str.capacity_);
        }

    private:
        char *s_;
        size_t size_;
        size_t capacity_;
        const static size_t npos = -1;
    };
}
