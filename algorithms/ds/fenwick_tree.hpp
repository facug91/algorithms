
/**
 * Fenwick Tree (Binary Indexed Tree).
 * Ref: Competitive Programming 3, section 2.4.4
 *      https://cp-algorithms.com/data_structures/fenwick.html
 *      https://www.geeksforgeeks.org/binary-indexed-tree-range-update-range-queries/
 */

/**
 * \brief Defines a class for a Fenwick Tree (Binary Indexed Tree).
 *        State: tested.
 *
 * \tparam ValueType Type of the elements.
 * \tparam MaxSize Maximum number of elements.
 */
template<typename ValueType, int MaxSize>
class FenwickTreePointUpdateRangeQuery {
private:
	int n;
	ValueType bit[MaxSize + 1];

public:

	void init(int size) {
		n = size + 1;
		memset(bit, 0, sizeof(ValueType) * n);
	}

	void init(int size, ValueType* arr) {
		init(size);
		for (size_t i = 0; i < size; i++)
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
 *        State: untested.
 *
 * \tparam ValueType Type of the elements.
 * \tparam MaxSize Maximum number of elements.
 */
template<typename ValueType, int MaxSize>
class FenwickTreeRangeUpdatePointQuery {
private:
	int n;
	ValueType bit[MaxSize + 2];

	void add(int idx, ValueType delta) {
		for (++idx; idx < n; idx += idx & -idx)
			bit[idx] += delta;
	}

public:

	void init(int size) {
		n = size + 2;
		memset(bit, 0, sizeof(ValueType) * n);
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
 *        State: untested.
 *
 * \tparam ValueType Type of the elements.
 * \tparam MaxSize Maximum number of elements.
 */
template<typename ValueType, int MaxSize>
class FenwickTreeRangeUpdateRangeQuery {
private:
	FenwickTreePointUpdateRangeQuery<ValueType, MaxSize> B1, B2;

public:

	void init(int size) {
		B1.init(size);
		B2.init(size);
	}

	void range_add(int l, int r, ValueType x) {
		B1.add(l, x);
		B1.add(r + 1, -x);
		B2.add(l, x * (l - 1));
		B2.add(r + 1, -x * r);
	}

	ValueType sum(int r) {
		return B1.sum(r) * r - B2.sum(r); // TODO : check if r is ok
	}

	ValueType range_sum(int l, int r) {
		return sum(r) - sum(l - 1);
	}
};

/**
 * \brief Defines a class for a Fenwick Tree 2D (Binary Indexed Tree 2D).
 *        State: tested.
 *
 * \tparam ValueType Type of the elements.
 * \tparam MaxRows Maximum number of rows.
 * \tparam MaxCols Maximum number of columns.
 */
template<typename ValueType, int MaxRows, int MaxCols>
class FenwickTree2DPointUpdateRangeQuery {
private:
	int n, m;
	ValueType bit[MaxRows + 1][MaxCols + 1];

public:

	void init(int rows, int cols) {
		n = rows + 1;
		m = cols + 1;
		for (int i = 0; i < n; i++)
			memset(bit[i], 0, sizeof(ValueType) * m);
	}

	void init(int rows, int cols, ValueType** mat) {
		init(rows, cols);
		for (size_t i = 0; i < rows; i++)
			for (size_t j = 0; j < cols; j++)
				add(i, j, mat[i][j]);
	}

	void init(std::vector<std::vector<ValueType>>& mat) {
		init(mat.size(), mat[0].size());
		for (size_t i = 0; i < mat.size(); i++)
			for (size_t j = 0; j < mat[i].size(); j++)
				add(i, j, mat[i][j]);
	}

	void add(int row, int col, ValueType delta) {
		for (int i = row + 1; i < n; i += i & -i)
			for (int j = col + 1; j < m; j += j & -j)
				bit[i][j] += delta;
	}

	ValueType sum(int row, int col) {
		ValueType ret = 0;
		for (int i = row + 1; i > 0; i -= i & -i)
			for (int j = col + 1; j > 0; j -= j & -j)
				ret += bit[i][j];
		return ret;
	}

	ValueType sum(int bottomRow, int leftCol, int topRow, int rightCol) {
		return sum(topRow, rightCol) - sum(topRow, leftCol - 1) - sum(bottomRow - 1, rightCol) + sum(bottomRow - 1, leftCol - 1);
	}
};
