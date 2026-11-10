#pragma once

#include <algorithm>
#include <cassert>
#include <functional>
#include <limits>
#include <random>
#include <tuple>
#include <utility>

//
// a[0],a[1],a[2],...,a[k],...
//
template <typename T>
struct ImplicitTreapNode {
	T val; // 値
	ImplicitTreapNode* lch;
	ImplicitTreapNode* rch;
	double pri; // 優先度
	int cnt; // 部分木のサイズ
	T min_val;
	T lazy_val;
	bool lazy;
	ImplicitTreapNode(T v, double p) :
			val(v), lch(nullptr), rch(nullptr), pri(p), cnt(1), min_val(v), lazy_val(0), lazy(false) {}
	~ImplicitTreapNode() {
		delete lch;
		delete rch;
	}
	static void push(ImplicitTreapNode* t) {
		if (!t) return;
		if (t->lazy) {
			t->val += t->lazy_val;
			t->min_val += t->lazy_val;
			if (t->lch) {
				t->lch->lazy = true;
				t->lch->lazy_val += t->lazy_val;
			}
			if (t->rch) {
				t->rch->lazy = true;
				t->rch->lazy_val += t->lazy_val;
			}
			t->lazy_val = 0;
			t->lazy = false;
		}
	}
	static int count(ImplicitTreapNode* t) { return t ? t->cnt : 0; }
	static int min(ImplicitTreapNode* t) { return t ? t->min_val : std::numeric_limits<T>::max(); }
	static ImplicitTreapNode* update(ImplicitTreapNode* t) {
		assert(t != nullptr);
		push(t);
		t->cnt = count(t->lch) + count(t->rch) + 1;
		push(t->lch);
		push(t->rch);
		t->min_val = std::min({min(t->lch), min(t->rch), t->val});
		return t;
	}
	static ImplicitTreapNode* merge(ImplicitTreapNode* l, ImplicitTreapNode* r) {
		if (!l || !r) return (!l) ? r : l;
		update(l);
		update(r);
		if (l->pri > r->pri) {
			l->rch = merge(l->rch, r);
			return update(l);
		} else {
			r->lch = merge(l, r->lch);
			return update(r);
		}
		assert(false);
		return nullptr;
	}
	//
	// node をたどることになる。k番目のノードで再帰が止まる
	//    [0,1,2,...,k-1,k,...]
	// -> [0,1,2,...,k-1] [k,...]
	//
	static std::pair<ImplicitTreapNode*, ImplicitTreapNode*> split(ImplicitTreapNode* t, int k) {
		if (!t) return std::make_pair(nullptr, nullptr);
		update(t);
		if (k <= count(t->lch)) {
			auto s = split(t->lch, k);
			t->lch = s.second;
			return std::make_pair(s.first, update(t));
		} else {
			auto s = split(t->rch, k - count(t->lch) - 1);
			t->rch = s.first;
			return std::make_pair(update(t), s.second);
		}
		assert(false);
		return std::make_pair(nullptr, nullptr);
	}
	static ImplicitTreapNode* insert(ImplicitTreapNode* t, int k, ImplicitTreapNode* new_t) {
		auto s = split(t, k);
		return merge(merge(s.first, new_t), s.second);
	}
	static std::pair<ImplicitTreapNode*, ImplicitTreapNode*> erase(ImplicitTreapNode* t, int k) {
		auto sr = split(t, k + 1);
		auto sl = split(sr.first, k);
		return std::make_pair(merge(sl.first, sr.second), sl.second);
	}
};

static int seed = 28313234; // seed はテキトー。デバッグしやすいように固定。
template <typename T>
class ImplicitTreap {
	using Node = ImplicitTreapNode<T>;
	std::function<double(void)> dice_;

public:
	Node* root_;
	ImplicitTreap() : root_(nullptr) {
		dice_ = std::bind(std::uniform_real_distribution<double>(0.0, 1.0), std::mt19937(seed));
	}
	~ImplicitTreap() {}
	void insert(int k, T val) { root_ = Node::insert(root_, k, new Node(val, dice_())); }
	void remove_at(int k) {
		Node* p;
		std::tie(root_, p) = Node::erase(root_, k);
		p->lch = p->rch = nullptr;
		delete p;
	}
	// shift for [l,r) 区間ないの要素を一つずらす。
	void shift(int l, int r) {
		if (l == r - 1) return;
		assert(l < r);
		auto sr = Node::split(root_, r);
		auto sl = Node::split(sr.first, l);
		auto lr = Node::split(sl.second, r - l - 1);
		root_ = Node::merge(Node::merge(sl.first, Node::merge(lr.second, lr.first)), sr.second);
	}
	int size() const { return Node::count(root_); }
	// add to [l,r)
	void add(int l, int r, T val) {
		assert(l < r);
		auto sr = Node::split(root_, r);
		auto sl = Node::split(sr.first, l);
		auto lr = sl.second;
		lr->lazy = true;
		lr->lazy_val = val;
		root_ = Node::merge(Node::merge(sl.first, lr), sr.second);
	}
	// min at [l,r)
	T min(int l, int r) {
		assert(l < r);
		auto sr = Node::split(root_, r);
		auto sl = Node::split(sr.first, l);
		auto lr = sl.second;
		T val = Node::min(lr);
		// 戻す
		root_ = Node::merge(Node::merge(sl.first, lr), sr.second);
		return val;
	}
	T get_by_index(int k) {
		assert(0 <= k && k < size());
		auto sr = Node::split(root_, k + 1);
		auto sl = Node::split(sr.first, k);
		auto lr = sl.second;
		assert(lr != nullptr);
		T val = lr->val;
		root_ = Node::merge(Node::merge(sl.first, lr), sr.second);
		return val;
	}
	T get(int k) {
		if (0 <= k && k < size()) return get_by_index(k);
		return 0;
	}
	void set(int k, T val) {
		auto sr = Node::split(root_, k + 1);
		auto sl = Node::split(sr.first, k);
		auto lr = sl.second;
		assert(lr != nullptr);
		lr->val = val;
		root_ = Node::merge(Node::merge(sl.first, lr), sr.second);
	}
};
