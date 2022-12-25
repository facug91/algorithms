
#include <bits/stdc++.h>

/**
 * \brief Defines a class for a Fenwick Tree (Binary Indexed Tree).
 *        State: tested.
 *        Ref: Competitive Programming 3, section 2.4.4
 *             https://cp-algorithms.com/data_structures/fenwick.html
 *             https://www.geeksforgeeks.org/binary-indexed-tree-range-update-range-queries/
 *
 * \tparam ValueType Type of the elements.
 * \tparam MaxSize Maximum number of elements.
 * // TODO update documentation
 */
class Treap {
private:
	using ValueType = long long;
	using CounterType = long long;

	struct item {
		ValueType key;
		int priority;
		CounterType cnt;
		item* l, * r;

		item() = default;

		item(int key) : key(key), priority(rand()), l(nullptr), r(nullptr), cnt(0) {}

		item(int key, int prior) : key(key), priority(prior), l(nullptr), r(nullptr) {}
	};

	using pItem = item*;

	pItem root;

	int count(pItem t) {
		return t ? t->cnt : 0;
	}

	void updateCounter(pItem t) {
		if (t) t->cnt = 1 + count(t->l) + count(t->r);
	}

	void heapify(pItem t) {
		if (!t) return;
		pItem max = t;
		if (t->l != nullptr && t->l->priority > max->priority)
			max = t->l;
		if (t->r != nullptr && t->r->priority > max->priority)
			max = t->r;
		if (max != t) {
			std::swap(t->priority, max->priority);
			heapify(max);
		}
	}

	void split(pItem t, ValueType key, pItem& l, pItem& r) {
		if (!t) l = r = nullptr;
		else if (t->key <= key) split(t->r, key, t->r, r), l = t;
		else split(t->l, key, l, t->l), r = t;
		updateCounter(t);
	}

	void insert(pItem& t, pItem it) {
		if (!t)
			t = it;
		else if (it->priority > t->priority)
			split(t, it->key, it->l, it->r), t = it;
		else
			insert(t->key <= it->key ? t->r : t->l, it);
		updateCounter(t);
	}

	void merge(pItem& t, pItem l, pItem r) {
		if (!l || !r) t = l ? l : r;
		else if (l->priority > r->priority) merge(l->r, l->r, r), t = l;
		else merge(r->l, l, r->l), t = r;
		updateCounter(t);
	}

	void erase(pItem& t, ValueType key) {
		if (t->key == key) {
			pItem th = t;
			merge(t, t->l, t->r);
			delete th;
		} else
			erase(key < t->key ? t->l : t->r, key);
		updateCounter(t);
	}

	pItem unite(pItem l, pItem r) {
		if (!l || !r) return l ? l : r;
		if (l->priority < r->priority) std::swap(l, r);
		pItem lt, rt;
		split(r, l->key, lt, rt);
		l->l = unite(l->l, lt);
		l->r = unite(l->r, rt);
		updateCounter(l);
		return l;
	}

	CounterType countLessEqual (const pItem& t, ValueType keyId) {
		if (!t) return 0;
		if (t->key > keyId) return countLessEqual(t->l, keyId);
		if (t->key <= keyId) countLessEqual(t->r, keyId) + count(t->l) + 1;
	}
public:

	pItem build(int* a, int n) {
		// Construct a treap on values {a[0], a[1], ..., a[n - 1]}
		if (n == 0) return nullptr;
		int mid = n / 2;
		pItem t = new item(a[mid], rand());
		t->l = build(a, mid);
		t->r = build(a + mid + 1, n - mid - 1);
		heapify(t);
		updateCounter(t);
		return t;
	}

	void insert(ValueType newVal) {
		insert(root, new item(newVal));
	}

	void erase(ValueType val) {
		erase(root, val);
	}

	CounterType countLessEqual(ValueType keyId) {
		return countLessEqual(root, keyId);
	}
};
