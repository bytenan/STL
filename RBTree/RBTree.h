#pragma once
#include <iostream>
#include <utility>

namespace wyn
{
	enum Color
	{
		RED,
		BLACK
	};

	template<class Value>
	class Node
	{
	public:
		Value value_;
		Color color_;
		Node<Value> *parent_;
		Node<Value> *left_;
		Node<Value> *right_;
		Node(const Value &value)
			: value_(value), color_(RED), parent_(nullptr), left_(nullptr), right_(nullptr)
		{
		}
	};

	template<class Value, class Ref, class Ptr>
	class iterator
	{
	public:
		typedef iterator<Value, Ref, Ptr> Self;
		Node<Value> *pnode_;
		iterator(Node<Value> *node)
			: pnode_(node)
		{
		}
		iterator(const iterator<Value, Value &, Value *> &x)
			: pnode_(x.pnode_)
		{
		}
		Self &operator++()
		{
			if (pnode_->right_)
			{
				Node<Value> *cur = pnode_->right_;
				while (cur->left_)
				{
					cur = cur->left_;
				}
				pnode_ = cur;
			}
			else
			{
				Node<Value> *parent = pnode_->parent_;
				while (parent && parent->right_ == pnode_)
				{
					pnode_ = parent;
					parent = pnode_->parent_;
				}
				pnode_ = parent;
			}
			return *this;
		}
		Self operator++(int)
		{
			Self tmp = *this;
			if (pnode_->right_)
			{
				Node<Value> *cur = pnode_->right_;
				while (cur->left_)
				{
					cur = cur->left_;
				}
				pnode_ = cur;
			}
			else
			{
				Node<Value> *parent = pnode_->parent_;
				while (parent && parent->right_ == pnode_)
				{
					pnode_ = parent;
					parent = pnode_->parent_;
				}
				pnode_ = parent;
			}
			return tmp;
		}
		Self &operator--()
		{
			if (pnode_->left_)
			{
				Node<Value> *cur = pnode_->left_;
				while (cur->right_)
				{
					cur = cur->right_;
				}
				pnode_ = cur;
			}
			else
			{
				Node<Value> *parent = pnode_->parent_;
				while (parent && parent->left_ == pnode_)
				{
					pnode_ = parent;
					parent = pnode_->parent_;
				}
				pnode_ = parent;
			}
			return *this;
		}
		Self operator--(int)
		{
			Self tmp = *this;
			if (pnode_->left_)
			{
				Node<Value> *cur = pnode_->left_;
				while (cur->right_)
				{
					cur = cur->right_;
				}
				pnode_ = cur;
			}
			else
			{
				Node<Value> *parent = pnode_->parent_;
				while (parent && parent->left_ == pnode_)
				{
					pnode_ = parent;
					parent = pnode_->parent_;
				}
				pnode_ = parent;
			}
			return tmp;
		}
		Ref operator*() const
		{
			return pnode_->value_;
		}
		Ptr operator->() const
		{
			return &pnode_->value_;
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

	template<class Key, class Value, class KeyOfValue, class Compare>
	class tree
	{
	public:
		typedef iterator<Value, const Value &, const Value *> const_iterator;
		typedef iterator<Value, Value &, Value *> iterator;
		iterator begin()
		{
			Node<Value> *min = root_;
			while (min && min->left_)
			{
				min = min->left_;
			}
			return iterator(min);
		}
		iterator end()
		{
			return iterator(nullptr);
		}
		const_iterator begin() const
		{
			Node<Value> *min = root_;
			while (min && min->left_)
			{
				min = min->left_;
			}
			return const_iterator(min);
		}
		const_iterator end() const
		{
			return const_iterator(nullptr);
		}
		tree()
			: root_(nullptr)
		{
		}
		std::pair<iterator, bool> insert(const Value &value)
		{
			if (!root_)
			{
				root_ = new Node<Value>(value);
				root_->color_ = BLACK;
				return std::pair<iterator, bool>(iterator(root_), true);
			}
			Node<Value> *parent = nullptr;
			Node<Value> *cur = root_;
			while (cur)
			{
				if (Compare()(KeyOfValue()(cur->value_), KeyOfValue()(value)))
				{
					parent = cur;
					cur = cur->right_;
				}
				else if (Compare()(KeyOfValue()(value), KeyOfValue()(cur->value_)))
				{
					parent = cur;
					cur = cur->left_;
				}
				else
				{
					return std::pair<iterator, bool>(iterator(cur), false);
				}
			}
			cur = new Node<Value>(value);
			Node<Value> *res = cur;
			if (Compare()(KeyOfValue()(parent->value_), KeyOfValue()(value)))
			{
				parent->right_ = cur;
			}
			else
			{
				parent->left_ = cur;
			}
			cur->parent_ = parent;
			while (parent && parent->color_ == RED)
			{
				Node<Value> *grandparent = parent->parent_;
				if (grandparent->left_ == parent)
				{
					Node<Value> *uncle = grandparent->right_;
					if (uncle && uncle->color_ == RED)
					{
						grandparent->color_ = RED;
						parent->color_ = uncle->color_ = BLACK;
						cur = grandparent;
						parent = cur->parent_;
					}
					else
					{
						if (parent->left_ == cur)
						{
							rotateL(grandparent);
							parent->color_ = BLACK;
							grandparent->color_ = RED;
						}
						else
						{
							rotateR(parent);
							rotateL(grandparent);
							cur->color_ = BLACK;
							grandparent->color_ = RED;
						}
						break;
					}
				}
				else
				{
					Node<Value> *uncle = grandparent->left_;
					if (uncle && uncle->color_ == RED)
					{
						grandparent->color_ = RED;
						parent->color_ = uncle->color_ = BLACK;
						cur = grandparent;
						parent = cur->parent_;
					}
					else
					{
						if (parent->right_ == cur)
						{
							rotateR(grandparent);
							parent->color_ = BLACK;
							grandparent->color_ = RED;
						}
						else
						{
							rotateL(parent);
							rotateR(grandparent);
							cur->color_ = BLACK;
							grandparent->color_ = RED;
						}
						break;
					}
				}
			}
			root_->color_ = BLACK;
			return std::pair<iterator, bool>(iterator(res), true);
		}
		iterator find(const Key &key)
		{
			Node<Value> *cur = root_;
			while (cur)
			{
				if (Compare()(key, KeyOfValue()(cur->value_)))
				{
					cur = cur->left_;
				}
				else if (Compare()(KeyOfValue()(cur->value_), key))
				{
					cur = cur->right_;
				}
				else
				{
					return iterator(cur);
				}
			}
			return end();
		}
		const_iterator find(const Key &key) const
		{
			Node<Value> *cur = root_;
			while (cur)
			{
				if (Compare()(key, KeyOfValue()(cur->value_)))
				{
					cur = cur->left_;
				}
				else if (Compare()(KeyOfValue()(cur->value_), key))
				{
					cur = cur->right_;
				}
				else
				{
					return const_iterator(cur);
				}
			}
			return end();
		}

	private:
		void rotateR(Node<Value> *parent)
		{
			Node<Value> *grandparent = parent->parent_;
			Node<Value> *childR = parent->right_;
			Node<Value> *childRL = childR->left_;
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
		}
		void rotateL(Node<Value> *parent)
		{
			Node<Value> *grandparent = parent->parent_;
			Node<Value> *childL = parent->left_;
			Node<Value> *childLR = childL->right_;
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
		}

	private:
		Node<Value> *root_;
	};
}