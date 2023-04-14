#pragma once

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <algorithm>

namespace wyn
{
    template <class T>
    class Node
    {
    public:
        T data_;
        int bf_;
        Node<T> *parent_;
        Node<T> *left_;
        Node<T> *right_;
        Node(const T &data)
            : data_(data), bf_(0), parent_(nullptr), left_(nullptr), right_(nullptr)
        {
        }
    };

    template <class T>
    class tree
    {
    public:
        tree()
            : root_(nullptr)
        {
        }
        bool insert(const T &data)
        {
            if (!root_)
            {
                root_ = new Node<T>(data);
                return true;
            }
            Node<T> *parent = nullptr;
            Node<T> *cur = root_;
            while (cur)
            {
                if (cur->data_ < data)
                {
                    parent = cur;
                    cur = cur->right_;
                }
                else if (cur->data_ > data)
                {
                    parent = cur;
                    cur = cur->left_;
                }
                else
                {
                    return false;
                }
            }
            cur = new Node<T>(data);
            if (parent->data_ < data)
            {
                parent->right_ = cur;
                cur->parent_ = parent;
            }
            else
            {
                parent->left_ = cur;
                cur->parent_ = parent;
            }
            while (parent)
            {
                if (parent->right_ == cur)
                {
                    ++parent->bf_;
                }
                else
                {
                    --parent->bf_;
                }
                if (parent->bf_ == 0)
                {
                    break;
                }
                else if (parent->bf_ == 1 || parent->bf_ == -1)
                {
                    cur = parent;
                    parent = cur->parent_;
                }
                else if (parent->bf_ == 2 || parent->bf_ == -2)
                {
                    if (parent->bf_ == 2 && cur->bf_ == 1)
                    {
                        rotateR(parent);
                    }
                    else if (parent->bf_ == 2 && cur->bf_ == -1)
                    {
                        rotateLR(parent);
                    }
                    else if (parent->bf_ == -2 && cur->bf_ == -1)
                    {
                        rotateL(parent);
                    }
                    else if (parent->bf_ == -2 && cur->bf_ == 1)
                    {
                        rotateRL(parent);
                    }
                    else
                    {
                        assert(false);
                    }
                    break;
                }
                else
                {
                    assert(false);
                }
            }
            return true;
        }
        bool isBlance() const
        {
            return isBlance_(root_);
        }

    private:
        bool isBlance_(Node<T> *root) const
        {
            if (!root)
            {
                return true;
            }
            if (root->left_ && !(root->left_->data_ < root->data_))
            {
                return false;
            }
            if (root->right_ && !(root->right_->data_ > root->data_))
            {
                return false;
            }
            if (!(root->bf_ == -1 || root->bf_ == 0 || root->bf_ == 1))
            {
                return false;
            }
            if (abs(height(root->left_) - height(root->right_)) != abs(root->bf_))
            {
                return false;
            }
            return true && isBlance_(root->left_) && isBlance_(root->right_);
        }
        int height(Node<T> *root) const
        {
            if (!root)
            {
                return 0;
            }
            return 1 + std::max(height(root->left_), height(root->right_));
        }
        void rotateR(Node<T> *parent)
        {
            Node<T> *grandparent = parent->parent_;
            Node<T> *childR = parent->right_;
            Node<T> *childRL = childR->left_;
            childR->left_ = parent;
            parent->parent_ = childR;
            parent->right_ = childRL;
            if (childRL)
            {
                childRL->parent_ = parent;
            }
            if (grandparent)
            {
                if (grandparent->right_ == parent)
                {
                    grandparent->right_ = childR;
                }
                else
                {
                    grandparent->left_ = childR;
                }
                childR->parent_ = grandparent;
            }
            else
            {
                childR->parent_ = nullptr;
                root_ = childR;
            }
            parent->bf_ = childR->bf_ = 0;
        }
        void rotateL(Node<T> *parent)
        {
            Node<T> *grandparent = parent->parent_;
            Node<T> *childL = parent->left_;
            Node<T> *childLR = childL->right_;
            childL->right_ = parent;
            parent->parent_ = childL;
            parent->left_ = childLR;
            if (childLR)
            {
                childLR->parent_ = parent;
            }
            if (grandparent)
            {
                if (grandparent->left_ == parent)
                {
                    grandparent->left_ = childL;
                }
                else
                {
                    grandparent->right_ = childL;
                }
                childL->parent_ = grandparent;
            }
            else
            {
                childL->parent_ = nullptr;
                root_ = childL;
            }
            parent->bf_ = childL->bf_ = 0;
        }
        void rotateLR(Node<T> *parent)
        {
            Node<T> *childR = parent->right_;
            Node<T> *childRL = childR->left_;
            int bf = childRL->bf_;
            rotateL(childR);
            rotateR(parent);
            if (bf == 0)
            {
                childRL->bf_ = 0;
                parent->bf_ = 0;
                childR->bf_ = 0;
            }
            else if (bf == 1)
            {
                childRL->bf_ = 0;
                parent->bf_ = 1;
                childR->bf_ = 0;
            }
            else if (bf == -1)
            {
                childRL->bf_ = 0;
                parent->bf_ = 0;
                childR->bf_ = -1;
            }
            else
            {
                assert(false);
            }
        }
        void rotateRL(Node<T> *parent)
        {
            Node<T> *childL = parent->left_;
            Node<T> *childLR = childL->right_;
            int bf = childLR->bf_;
            rotateR(childL);
            rotateL(parent);
            if (bf == 0)
            {
                childLR->bf_ = 0;
                childL->bf_ = 0;
                parent->bf_ = 0;
            }
            else if (bf == 1)
            {
                childLR->bf_ = 0;
                childL->bf_ = -1;
                parent->bf_ = 0;
            }
            else if (bf == -1)
            {
                childLR->bf_ = 0;
                childL->bf_ = 0;
                parent->bf_ = 1;
            }
            else
            {
                assert(false);
            }
        }

    private:
        Node<T> *root_;
    };
}