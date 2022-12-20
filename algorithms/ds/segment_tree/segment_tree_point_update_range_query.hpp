
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
 */
template<typename ValueType, int MaxSize, typename CombineFunc, typename DefaultValueFunc>
class SegmentTreePointUpdateRangeQuery {
private:
	int n;
	ValueType st[MaxSize * 4];
	CombineFunc combine;
	DefaultValueFunc defaultValueFunc;

	void build(int v, int tl, int tr, ValueType val) {
		if (tl == tr) st[v] = val;
		else {
			int tm = (tl + tr) / 2;
			build(v * 2, tl, tm, val);
			build(v * 2 + 1, tm + 1, tr, val);
			st[v] = combine(st[v * 2], st[v * 2 + 1]);
		}
	}

	void build(ValueType arr[], int v, int tl, int tr) {
		if (tl == tr) st[v] = arr[tl];
		else {
			int tm = (tl + tr) / 2;
			build(arr, v * 2, tl, tm);
			build(arr, v * 2 + 1, tm + 1, tr);
			st[v] = combine(st[v * 2], st[v * 2 + 1]);
		}
	}

	ValueType query(int v, int tl, int tr, int l, int r) {
		if (l > r) return defaultValueFunc();
		if (l == tl && r == tr) return st[v];

		int tm = (tl + tr) / 2;
		return combine(query(v * 2, tl, tm, l, std::min(r, tm)),
		               query(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r));
	}

	void update(int v, int tl, int tr, int pos, ValueType val) {
		if (tl == tr) st[v] = val;
		else {
			int tm = (tl + tr) / 2;
			if (pos <= tm) update(v * 2, tl, tm, pos, val);
			else update(v * 2 + 1, tm + 1, tr, pos, val);
			st[v] = combine(st[v * 2], st[v * 2 + 1]);
		}
	}

public:

	void build(int size) {
		n = size;
		build(1, 0, size - 1, defaultValueFunc());
	}

	void build(int size, ValueType val) {
		n = size;
		build(1, 0, size - 1, val);
	}

	void build(int size, ValueType* arr) {
		n = size;
		build(arr, 1, 0, size - 1);
	}

	ValueType query(int l, int r) {
		return query(1, 0, n - 1, l, r);
	}

	void update(int idx, ValueType val) {
		update(1, 0, n - 1, idx, val);
	}
};

/** Segment tree with point update range query to get sum of values in the given interval */
template<typename ValueType> struct SumCombinePURQ { ValueType operator()(ValueType val1, ValueType val2) { return val1 + val2; }};
template<typename ValueType> struct SumDefaultValuePURQ { ValueType operator()() { return 0; }};
template<typename ValueType, int MaxSize>
using SegmentTreePointUpdateRangeQuerySum =
		SegmentTreePointUpdateRangeQuery<ValueType, MaxSize, SumCombinePURQ<ValueType>, SumDefaultValuePURQ<ValueType>>;

/** Segment tree with point update range query to get min value in the given interval */
template<typename ValueType> struct MinCombinePURQ { ValueType operator()(ValueType val1, ValueType val2) { return std::min(val1, val2); }};
template<typename ValueType> struct MinDefaultValuePURQ { ValueType operator()() { return std::numeric_limits<ValueType>::max(); }};
template<typename ValueType, int MaxSize>
using SegmentTreePointUpdateRangeQueryMin =
		SegmentTreePointUpdateRangeQuery<ValueType, MaxSize, MinCombinePURQ<ValueType>, MinDefaultValuePURQ<ValueType>>;

/** Segment tree with point update range query to get max value in the given interval */
template<typename ValueType> struct MaxCombinePURQ { ValueType operator()(ValueType val1, ValueType val2) { return std::max(val1, val2); }};
template<typename ValueType> struct MaxDefaultValuePURQ { ValueType operator()() { return std::numeric_limits<ValueType>::min(); }};
template<typename ValueType, int MaxSize>
using SegmentTreePointUpdateRangeQueryMax =
		SegmentTreePointUpdateRangeQuery<ValueType, MaxSize, MaxCombinePURQ<ValueType>, MaxDefaultValuePURQ<ValueType>>;

/** Segment tree with point update range query to get max value with the number of appearances of that value in the given interval */
template<typename ValueType> struct CombinePairPURQ {
	std::pair<ValueType, ValueType> operator()(const std::pair<ValueType, ValueType>& a, const std::pair<ValueType, ValueType>& b) {
		return a.first > b.first ? a : b.first > a.first ? b : make_pair(a.first, a.second + b.second);
	}
};
template<typename ValueType> struct PairDefaultValuePURQ {
	std::pair<ValueType, ValueType> operator()() { return std::make_pair(std::numeric_limits<ValueType>::min(), 0); }
};
template<typename ValueType, int MaxSize>
using SegmentTreePointUpdateRangeQueryMaxWithCounter =
		SegmentTreePointUpdateRangeQuery<std::pair<ValueType, ValueType>, MaxSize, CombinePairPURQ<ValueType>, PairDefaultValuePURQ<ValueType>>;

/** Segment tree with point update range query to get lcm of values in the given interval */
template<typename ValueType> struct LcmCombinePURQ { ValueType operator()(ValueType val1, ValueType val2) { return std::lcm(val1, val2); }};
template<typename ValueType> struct LcmDefaultValuePURQ { ValueType operator()() { return 1; }};
template<typename ValueType, int MaxSize>
using SegmentTreePointUpdateRangeQueryLcm =
		SegmentTreePointUpdateRangeQuery<ValueType, MaxSize, LcmCombinePURQ<ValueType>, LcmDefaultValuePURQ<ValueType>>;

/** Segment tree with point update range query to get gcd of values in the given interval */
template<typename ValueType> struct GcdCombinePURQ {
	ValueType operator()(ValueType val1, ValueType val2) { return val1 == -1 ? val2 : val2 == -1 ? val1 : std::gcd(val1, val2); }
};
template<typename ValueType> struct GcdDefaultValuePURQ { ValueType operator()() { return -1; }};
template<typename ValueType, int MaxSize>
using SegmentTreePointUpdateRangeQueryGcd =
		SegmentTreePointUpdateRangeQuery<ValueType, MaxSize, GcdCombinePURQ<ValueType>, GcdDefaultValuePURQ<ValueType>>;

/** Segment tree with point update range query to get maximal subsegment sum in the given interval */
template<typename ValueType>
struct Data {
	static const ValueType invalid = std::numeric_limits<ValueType>::min();
	ValueType sum, prefix, suffix, ans;
	Data() = default;
	Data(ValueType sum, ValueType prefix, ValueType suffix, ValueType ans) : sum(sum), prefix(prefix), suffix(suffix), ans(ans) {}
};
template<typename ValueType>
struct MaxSumDefaultValuePURQ {
	Data<ValueType> operator()() {
		return Data<ValueType>(Data<ValueType>::invalid, Data<ValueType>::invalid, Data<ValueType>::invalid, Data<ValueType>::invalid);
	}
};
template<typename ValueType>
struct MaxSumCombinePURQ {
	Data<ValueType> operator()(const Data<ValueType>& l, const Data<ValueType>& r) {
		if (l.ans == Data<ValueType>::invalid) return r;
		if (r.ans == Data<ValueType>::invalid) return l;
		Data<ValueType> res;
		res.sum = l.sum + r.sum;
		res.prefix = std::max(l.prefix, l.sum + r.prefix);
		res.suffix = std::max(r.suffix, r.sum + l.suffix);
		res.ans = std::max(std::max(l.ans, r.ans), l.suffix + r.prefix);
		return res;
	}
};
template<typename ValueType, int MaxSize>
using SegmentTreePointUpdateRangeQueryMaxSum =
		SegmentTreePointUpdateRangeQuery<ValueType, MaxSize, MaxSumCombinePURQ<ValueType>, MaxSumDefaultValuePURQ<ValueType>>;
