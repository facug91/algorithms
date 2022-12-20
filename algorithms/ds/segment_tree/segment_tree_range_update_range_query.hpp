
/**
 * \brief Defines a class for a Segment Tree.
 *        State: untested.
 *        Ref: Competitive Programming 3, section 2.4.3
 *             https://cp-algorithms.com/data_structures/segment_tree.html
 *
 * \tparam ValueType Type of the elements.
 * \tparam MaxSize Maximum number of elements.
 * \tparam ElementCompare Comparator function to combine intervals and partial answers
 *         (e.g. struct SumCombine { ValueType operator()(ValueType val1, ValueType val2) { return val1 + val2; }};).
 * \tparam DefaultValueFunc Function returning the default value, used when calling with an undefined interval (l > r)
 *         (e.g. struct SumDefaultValue { ValueType operator()() { return 0; }};).
 *         // TODO complete documentation of new parameters
 */
template<typename ValueType, int MaxSize, typename CombineFunc, typename DefaultValueFunc
class SegmentTreeRangeUpdateRangeQuery {
private:
	int n;
	ValueType st[MaxSize * 4], lazyUpdate[MaxSize * 4], lazyAdd[MaxSize * 4];

	ValueType combine(ValueType a, ValueType b) { return a + b; }

	void build(ValueType arr[], int v, int tl, int tr) {
		lazyUpdate[v] = -1;
		lazyAdd[v] = 0;
		if (tl == tr) st[v] = arr[tl];
		else {
			int tm = (tl + tr) / 2;
			build(arr, v * 2, tl, tm);
			build(arr, v * 2 + 1, tm + 1, tr);
			st[v] = combine(st[v * 2], st[v * 2 + 1]);
		}
	}

	void push(int v, int tl, int tr) {
		int tm = (tl + tr) / 2;
		if (lazyUpdate[v] != -1) {
			st[v * 2] = lazyUpdate[v] * (tm - tl + 1);
			lazyUpdate[v * 2] = lazyUpdate[v];
			st[v * 2 + 1] = lazyUpdate[v] * (tr - tm);
			lazyUpdate[v * 2 + 1] = lazyUpdate[v];
			lazyUpdate[v] = -1;
		}
		if (lazyAdd[v] != 0) {
			st[v * 2] = (tm - tl + 1) - st[v * 2];
			lazyAdd[v * 2] = (lazyAdd[v * 2] + lazyAdd[v]) % 2;
			st[v * 2 + 1] = (tr - tm) - st[v * 2 + 1];
			lazyAdd[v * 2 + 1] = (lazyAdd[v * 2 + 1] + lazyAdd[v]) % 2;
			lazyAdd[v] = 0;
		}
	}

	ValueType query(int v, int tl, int tr, int l, int r) {
		if (l > r) return 0;
		if (l == tl && r == tr) return st[v];
		push(v, tl, tr);
		int tm = (tl + tr) / 2;
		return combine(query(v * 2, tl, tm, l, std::min(r, tm)),
		               query(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r));
	}

	void update(int v, int tl, int tr, int l, int r, ValueType val) {
		if (l > r) return;
		if (l == tl && r == tr) {
			st[v] = (tr - tl + 1) * val;
			lazyUpdate[v] = val;
			lazyAdd[v] = 0;
		} else {
			push(v, tl, tr);

			int tm = (tl + tr) / 2;
			update(v * 2, tl, tm, l, std::min(r, tm), val);
			update(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r, val);
			st[v] = combine(st[v * 2], st[v * 2 + 1]);
		}
	}

	void add(int v, int tl, int tr, int l, int r, ValueType val) {
		if (l > r) return;
		if (l == tl && r == tr) {
			st[v] = (tr - tl + 1) - st[v];
			lazyAdd[v] = (lazyAdd[v] + val) % 2;
		} else {
			push(v, tl, tr);

			int tm = (tl + tr) / 2;
			add(v * 2, tl, tm, l, std::min(r, tm), val);
			add(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r, val);
			st[v] = combine(st[v * 2], st[v * 2 + 1]);
		}
	}

public:

	void build(int size) {
		n = size;
		std::fill(st, st + (n * 4), 0);
		std::fill(lazyUpdate, lazyUpdate + (n * 4), -1);
		std::fill(lazyAdd, lazyAdd + (n * 4), 0);
	}

	void build(int size, ValueType val) {
		build(size);
		update(1, val);
	}

	void build(int size, ValueType* arr) {
		n = size;
		build(arr, 1, 0, size - 1);
	}

	ValueType query(int l, int r) {
		return query(1, 0, n - 1, l, r);
	}

	void update(int l, int r, ValueType val) {
		update(1, 0, n - 1, l, r, val);
	}

	void add(int l, int r, ValueType val) {
		add(1, 0, n - 1, l, r, val);
	}
};

/** Segment tree with range update range query to get sum of values in the given interval */
template<typename ValueType> struct SumDefaultValueRURQ { ValueType operator()() { return 0; }};

template<typename ValueType> struct SumCombineRURQ { ValueType operator()(ValueType val1, ValueType val2) { return val1 + val2; }};

template<typename ValueType, int MaxSize>
using SegmentTreeRangeUpdateRangeQuerySum =
		SegmentTreeRangeUpdateRangeQuery<ValueType, MaxSize, SumCombineRURQ<ValueType>, SumDefaultValueRURQ<ValueType>>;

/** Segment tree with range update range query to get min value in the given interval */
template<typename ValueType> struct MinDefaultValueRURQ { ValueType operator()() { return std::numeric_limits<ValueType>::max(); }};

template<typename ValueType> struct MinCombineRURQ { ValueType operator()(ValueType val1, ValueType val2) { return std::min(val1, val2); }};

template<typename ValueType, int MaxSize>
using SegmentTreeRangeUpdateRangeQueryMin =
		SegmentTreeRangeUpdateRangeQuery<ValueType, MaxSize, MinCombineRURQ<ValueType>, MinDefaultValueRURQ<ValueType>>;

/** Segment tree with range update range query to get max value in the given interval */
template<typename ValueType> struct MaxDefaultValueRURQ { ValueType operator()() { return std::numeric_limits<ValueType>::min(); }};

template<typename ValueType> struct MaxCombineRURQ { ValueType operator()(ValueType val1, ValueType val2) { return std::max(val1, val2); }};

template<typename ValueType, int MaxSize>
using SegmentTreeRangeUpdateRangeQueryMax =
		SegmentTreeRangeUpdateRangeQuery<ValueType, MaxSize, MaxCombineRURQ<ValueType>, MaxDefaultValueRURQ<ValueType>>;
