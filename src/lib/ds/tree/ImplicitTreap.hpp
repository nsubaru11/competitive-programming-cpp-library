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
struct node_t {
	T val; // 値
	node_t* lch;
	node_t* rch;
	double pri; // 優先度
	int cnt; // 部分木のサイズ
	T min_val;
	T lazy_val;
	bool lazy;
	node_t(T v, double p) : val(v), lch(nullptr), rch(nullptr), pri(p), cnt(1), min_val(v), lazy_val(0), lazy(false) {}
	~node_t() {
		delete lch;
		delete rch;
	}
	static void push(node_t* t) {
		if (!t)
			return;
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
	static int count(node_t* t) { return t ? t->cnt : 0; }
	static int min(node_t* t) { return t ? t->min_val : std::numeric_limits<T>::max(); }
	static node_t* update(node_t* t) {
		assert(t != nullptr);
		push(t);
		t->cnt = count(t->lch) + count(t->rch) + 1;
		push(t->lch);
		push(t->rch);
		t->min_val = std::min({min(t->lch), min(t->rch), t->val});
		return t;
	}
	static node_t* merge(node_t* l, node_t* r) {
		if (!l || !r)
			return (!l) ? r : l;
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
	static std::pair<node_t*, node_t*> split(node_t* t, int k) {
		if (!t)
			return std::make_pair(nullptr, nullptr);
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
	static node_t* insert(node_t* t, int k, node_t* new_t) {
		auto s = split(t, k);
		return merge(merge(s.first, new_t), s.second);
	}
	static std::pair<node_t*, node_t*> erase(node_t* t, int k) {
		auto sr = split(t, k + 1);
		auto sl = split(sr.first, k);
		return std::make_pair(merge(sl.first, sr.second), sl.second);
	}
};

static int seed = 28313234; // seed はテキトー。デバッグしやすいように固定。
template <typename T>
class ImplicitTreap {
	typedef node_t<T> node;
	std::function<double(void)> dice_;

public:
	node* root_;
	ImplicitTreap() : root_(nullptr) {
		dice_ = std::bind(std::uniform_real_distribution<double>(0.0, 1.0), std::mt19937(seed));
	}
	~ImplicitTreap() {}
	void insert(int k, T val) { root_ = node::insert(root_, k, new node(val, dice_())); }
	void erase(int k) {
		node* p;
		std::tie(root_, p) = node::erase(root_, k);
		p->lch = p->rch = nullptr;
		delete p;
	}
	// shift for [l,r) 区間ないの要素を一つずらす。
	void shift(int l, int r) {
		if (l == r - 1)
			return;
		assert(l < r);
		auto sr = node::split(root_, r);
		auto sl = node::split(sr.first, l);
		auto lr = node::split(sl.second, r - l - 1);
		root_ = node::merge(node::merge(sl.first, node::merge(lr.second, lr.first)), sr.second);
	}
	int size() const { return node::count(root_); }
	// add to [l,r)
	void add(int l, int r, T val) {
		assert(l < r);
		auto sr = node::split(root_, r);
		auto sl = node::split(sr.first, l);
		auto lr = sl.second;
		lr->lazy = true;
		lr->lazy_val = val;
		root_ = node::merge(node::merge(sl.first, lr), sr.second);
	}
	// min at [l,r)
	T min(int l, int r) {
		assert(l < r);
		auto sr = node::split(root_, r);
		auto sl = node::split(sr.first, l);
		auto lr = sl.second;
		T val = node::min(lr);
		// 戻す
		root_ = node::merge(node::merge(sl.first, lr), sr.second);
		return val;
	}
	T at(int k) {
		assert(0 <= k && k < size());
		auto sr = node::split(root_, k + 1);
		auto sl = node::split(sr.first, k);
		auto lr = sl.second;
		assert(lr != nullptr);
		T val = lr->val;
		root_ = node::merge(node::merge(sl.first, lr), sr.second);
		return val;
	}
	T get(int k) {
		if (0 <= k && k < size())
			return at(k);
		return 0;
	}
	void set(int k, T val) {
		auto sr = node::split(root_, k + 1);
		auto sl = node::split(sr.first, k);
		auto lr = sl.second;
		assert(lr != nullptr);
		lr->val = val;
		root_ = node::merge(node::merge(sl.first, lr), sr.second);
	}
};
