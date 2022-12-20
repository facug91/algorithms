
/**
 * \brief Defines a class for a Segment Tree.
 *        State: untested.
 *        Ref: https://cp-algorithms.com/data_structures/segment_tree.html
 *
 * \tparam ValueType Type of the elements.
 * \tparam MaxSize Maximum number of elements.
 * \tparam ElementCompare Comparator function to combine intervals and partial answers
 *         (e.g. struct SumCombine { ValueType operator()(ValueType val1, ValueType val2) { return val1 + val2; }};).
 * \tparam DefaultValueFunc Function returning the default value, used when calling with an undefined interval (l > r)
 *         (e.g. struct SumDefaultValue { ValueType operator()() { return 0; }};).
 */
template<typename ValueType, int MaxSize, typename CalcResultFunc, typename CombineFunc, typename DefaultValueFunc>
class MergeSortSegmentTreeRangeQuery {
private:
	int n;
	std::vector<ValueType> st[MaxSize * 4];
	CalcResultFunc calcResultFunc;
	CombineFunc combine;
	DefaultValueFunc defaultValueFunc;

	void build(ValueType arr[], int v, int tl, int tr) {
		if (tl == tr) st[v] = std::vector<int>(1, arr[tl]);
		else {
			int tm = (tl + tr) / 2;
			build(arr, v * 2, tl, tm);
			build(arr, v * 2 + 1, tm + 1, tr);
			std::merge(st[v * 2].begin(), st[v * 2].end(), st[v * 2 + 1].begin(), st[v * 2 + 1].end(), back_inserter(st[v]));
		}
	}

	ValueType query(int v, int tl, int tr, int l, int r, ValueType val) {
		if (l > r) return defaultValueFunc();
		if (l == tl && r == tr) return calcResultFunc(st[v], val);

		int tm = (tl + tr) / 2;
		return combine(query(v * 2, tl, tm, l, std::min(r, tm), val),
		               query(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r, val));
	}

public:

	void build(int size, ValueType* arr) {
		n = size;
		build(arr, 1, 0, size - 1);
	}

	ValueType query(int l, int r, ValueType val) {
		return query(1, 0, n - 1, l, r, val);
	}
};

/** Merge sort segment tree with range query to get the smallest number greater or equal to a specified number. */
template<typename ValueType> struct MinGreaterEqualCombineMSRQ {
	ValueType operator()(ValueType val1, ValueType val2) { return std::min(val1, val2); }
};
template<typename ValueType> struct MinGreaterEqualDefaultValueMSRQ { ValueType operator()() { return std::numeric_limits<ValueType>::max(); }};
template<typename ValueType> struct MinGreaterEqualCalcResultMSRQ {
	ValueType operator()(const std::vector<ValueType>& sortedSegment, ValueType val) {
		auto pos = std::lower_bound(sortedSegment.begin(), sortedSegment.end(), val);
		if (pos != sortedSegment.end()) return *pos;
		return MinGreaterEqualDefaultValueMSRQ<ValueType>()();
	}
};
template<typename ValueType, int MaxSize>
using MergeSortSegmentTreeRangeQueryMinGreaterEqual =
		MergeSortSegmentTreeRangeQuery<ValueType, MaxSize,
				MinGreaterEqualCalcResultMSRQ<ValueType>, MinGreaterEqualCombineMSRQ<ValueType>, MinGreaterEqualDefaultValueMSRQ<ValueType>>;

/** Merge sort segment tree with range query to get the number of elements greater than a specified number. */
template<typename ValueType> struct SumGreaterCombineMSRQ { ValueType operator()(ValueType val1, ValueType val2) { return val1 + val2; }};
template<typename ValueType> struct SumGreaterDefaultValueMSRQ { ValueType operator()() { return 0; }};
template<typename ValueType> struct SumGreaterCalcResultMSRQ {
	ValueType operator()(const std::vector<ValueType>& sortedSegment, ValueType val) {
		return std::distance(std::upper_bound(sortedSegment.begin(), sortedSegment.end(), val), sortedSegment.end());
	}
};
template<typename ValueType, int MaxSize>
using MergeSortSegmentTreeRangeQuerySumGreater =
		MergeSortSegmentTreeRangeQuery<ValueType, MaxSize,
				SumGreaterCalcResultMSRQ<ValueType>, SumGreaterCombineMSRQ<ValueType>, SumGreaterDefaultValueMSRQ<ValueType>>;
