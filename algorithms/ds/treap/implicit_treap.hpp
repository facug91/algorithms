
/**
 * \brief Defines a class for an Implicit Treap.
 *        State: tested.
 *        Ref: https://cp-algorithms.com/data_structures/treap.html
 *             https://tanujkhattar.wordpress.com/2016/01/10/treaps-one-tree-to-rule-em-all-part-2/
 */
class ImplicitTreap {
private:
	using ValueType = long long;

	struct item {
		ValueType val, sum, lazy;
		int priority;
		int size;
		item* l, * r;

		item() = default;

		item(ValueType val) : val(val), sum(val), lazy(0), priority(rand()), size(1), l(nullptr), r(nullptr) {}

		item(ValueType val, int prior) : val(val), sum(val), lazy(0), priority(prior), size(1), l(nullptr), r(nullptr) {}
	};

	using pItem = item*;

	pItem root;

	int size(pItem t) {
		return t ? t->size : 0;
	}

	void updateSize(pItem t) {
		if (t) t->size = 1 + size(t->l) + size(t->r);
	}

	void lazy(pItem t) {
		if (!t || !t->lazy) return;
		t->val += t->lazy; //operation of lazy
		t->sum += t->lazy * size(t);
		if (t->l)t->l->lazy += t->lazy; //propagate lazy
		if (t->r)t->r->lazy += t->lazy;
		t->lazy = 0;
	}

	void reset(pItem t) {
		if (t)t->sum = t->val; //lazy already propagated
	}

	void combine(pItem& t, pItem l, pItem r) { //combine segment tree ranges
		if (!l || !r) return void(t = l ? l : r);
		t->sum = l->sum + r->sum;
	}

	void operation(pItem t) { //operation of segment tree
		if (!t) return;
		reset(t); //node represents single element of array
		lazy(t->l);
		lazy(t->r); //imp:propagate lazy before combining l,r
		combine(t, t->l, t);
		combine(t, t, t->r);
	}

	void split(pItem t, pItem& l, pItem& r, int pos, int add = 0) {
		if (!t) return void(l = r = nullptr);
		lazy(t);
		int currPos = add + size(t->l);
		if (currPos <= pos)//element at pos goes to "l"
			split(t->r, t->r, r, pos, currPos + 1), l = t;
		else split(t->l, l, t->l, pos, add), r = t;
		updateSize(t);
		operation(t);
	}

	void merge(pItem& t, pItem l, pItem r) { //result/left/right array
		lazy(l);
		lazy(r);
		if (!l || !r) t = l ? l : r;
		else if (l->priority > r->priority) merge(l->r, l->r, r), t = l;
		else merge(r->l, l, r->l), t = r;
		updateSize(t);
		operation(t);
	}

	pItem init(ValueType val) {
		pItem ret = new item(val, rand());
		return ret;
	}

	ValueType rangeQuery(pItem t, int l, int r) { //[l,r]
		pItem L, mid, R;
		split(t, L, mid, l - 1);
		split(mid, t, R, r - l);//note: r-l!!
		ValueType ans = t->sum;
		merge(mid, L, t);
		merge(t, mid, R);
		return ans;
	}

	void updateRange(pItem t, int l, int r, ValueType val) { // [l,r]
		pItem L, mid, R;
		split(t, L, mid, l - 1);
		split(mid, t, R, r - l);// note: r-l!!
		t->lazy += val; // lazy update
		merge(mid, L, t);
		merge(t, mid, R);
	}

	ValueType at(pItem t, int pos, int add = 0) {
		lazy(t);
		int currPos = add + size(t->l);
		if (currPos == pos) return t->val;
		if (currPos > pos) return at(t->l, pos, add);
		else /* if (currPos < pos) */ return at(t->r, pos, currPos + 1);
	}

	int findPos (pItem t, ValueType val, int add = 0) {
		if (!t) return -1;
		int currPos = add + size(t->l);
		if (t->val == val) return currPos;
		if (t->val > val) return findPos(t->l, val, add);
		else /* if (t->val < val) */ return findPos(t->r, val, currPos + 1);
	}

public:

	void insert(ValueType val, int pos) {
		auto newItem = init(val);
		pItem l, r;
		split(root, l, r, pos);
		merge(root, l, newItem);
		merge(root, root, r);
	}

	ValueType at(int pos) {
		return at(root, pos);
	}

	void erase(int pos) {
		pItem l, m, r, r2;
		if (pos == 0) {
			split(root, l, r, pos);
			root = r;
		} else {
			split(root, l, r, pos - 1);
			split(r, m, r2, pos);
			merge(root, l, r2);
		}
	}

	/*
	 * Only works if the array was sorted.
	 * If not found, return -1;
	 */
	int findPos (ValueType val) {
		return findPos(root, val);
	}

	ValueType rangeQuery(int l, int r) {
		return rangeQuery(root, l, r);
	}

	void updateRange(int l, int r, ValueType val) {
		updateRange(root, l, r, val);
	}

};