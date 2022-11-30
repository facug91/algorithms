

/**
 * Fenwick Tree (Binary Indexed Tree).
 * Ref: Competitive Programming 3, section 2.4.4
 *      https://cp-algorithms.com/data_structures/fenwick.html
 *      https://www.geeksforgeeks.org/binary-indexed-tree-range-update-range-queries/
 */

/**
 * \brief Defines a class for a Fenwick Tree (Binary Indexed Tree).
 *
 * \tparam ValueType Type of the elements.
 * \tparam MaxSize Maximum number of elements.
 */
template<typename ValueType, int MaxSize>
class FenwickTreePointUpdateRangeQuery {
private:
	int n;
	ValueType bit[MaxSize];

public:

	void init(int size) {
		n = size;
		std::fill(bit, bit + n, 0);
	}

	void init(int size, ValueType* arr) {
		init(size);
		for (size_t i = 0; i < n; i++)
			add(i, arr[i]);
	}

	void init(std::vector<ValueType>& arr) {
		init(arr.size(), &arr[0]);
	}

	void add(int idx, ValueType delta) {
		for (++idx; idx < n; idx += idx & -idx)
			bit[idx] += delta;
	}

	ValueType sum(int r) {
		ValueType ret = 0;
		for (++r; r > 0; r -= r & -r)
			ret += bit[r];
		return ret;
	}

	ValueType sum(int l, int r) {
		return sum(r) - sum(l - 1);
	}
};

/**
 * \brief Defines a class for a Fenwick Tree (Binary Indexed Tree).
 *
 * \tparam ValueType Type of the elements.
 * \tparam MaxSize Maximum number of elements.
 */
template<typename ValueType, int MaxSize>
class FenwickTreeRangeUpdatePointQuery {
private:
	int n;
	ValueType bit[MaxSize];

	void add(int idx, ValueType delta) {
		for (++idx; idx < n; idx += idx & -idx)
			bit[idx] += delta;
	}

public:

	void init(int size) {
		n = size;
		std::fill(bit, bit + n, 0);
	}

	void range_add(int l, int r, ValueType val) {
		add(l, val);
		add(r + 1, -val);
	}

	ValueType point_query(int idx) {
		ValueType ret = 0;
		for (++idx; idx > 0; idx -= idx & -idx)
			ret += bit[idx];
		return ret;
	}
};

/**
 * \brief Defines a class for a Fenwick Tree (Binary Indexed Tree).
 *
 * \tparam ValueType Type of the elements.
 * \tparam MaxSize Maximum number of elements.
 */
template<typename ValueType, int MaxSize>
class FenwickTreeRangeUpdateRangeQuery {
private:
	int n;
	FenwickTreePointUpdateRangeQuery<ValueType, MaxSize> B1, B2;

public:

	void init(int size) {
		n = size;
		B1.init(n);
		B2.init(n);
	}

	void range_add(int l, int r, ValueType x) {
		B1.add(l, r);
		B1.add(r + 1, -x);
		B2.add(l, x * (l - 1));
		B2.add(r + 1, -x * r);
	}

	ValueType sum(int r) {
		return B1.sum(r) * r - B2.sum(r);
	}

	ValueType range_sum(int l, int r) {
		return sum(r) - sum(l-1);
	}
};

/**
 * \brief Defines a class for a Fenwick Tree 2D (Binary Indexed Tree 2D).
 *
 * \tparam ValueType Type of the elements.
 * \tparam MaxRows Maximum number of rows.
 * \tparam MaxCols Maximum number of columns.
 */
template<typename ValueType, int MaxRows, int MaxCols>
class FenwickTree2DPointUpdateRangeQuery {
private:
	int n, m;
	ValueType bit[MaxRows][MaxCols];

public:

	void init(int rows, int cols) {
		n = rows;
		m = cols;
		std::fill(bit, bit + n * m, 0);
	}

	void init(int rows, int cols, ValueType** mat) {
		init(rows, cols);
		for (size_t i = 0; i < n; i++)
			for (size_t j = 0; j < m; j++)
				add(i, mat[i][j]);
	}

	void init(std::vector<std::vector<ValueType>>& mat) {
		init(mat.size(), mat[0].size());
		for (size_t i = 0; i < n; i++)
			for (size_t j = 0; j < m; j++)
				add(i, mat[i][j]);
	}

	void add(int x, int y, ValueType delta) {
		for (int i = x; i > 0; i -= i & -i)
			for (int j = y; j > 0; j -= j & -j)
				bit[i][j] += delta;
	}

	ValueType sum(int x, int y) {
		ValueType ret = 0;
		for (int i = x + 1; i > 0; i -= i & -i)
			for (int j = y + 1; j > 0; j -= j & -j)
				ret += bit[i][j];
		return ret;
	}

	ValueType sum(int top, int left, int bottom, int right) {
		return sum(bottom, right) - sum(bottom, left - 1) - sum(top - 1, right) + sum(top - 1, left - 1);
	}
};
