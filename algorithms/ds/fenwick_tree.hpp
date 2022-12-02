
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

	void init(int size, ValueType val) {
		init(size);
		for (size_t i = 0; i < size; i++) add(i, val);
	}

	void init(int size, ValueType* arr) {
		init(size);
		for (size_t i = 0; i < size; i++) add(i, arr[i]);
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
 *        State: tested.
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

/**
 * \brief Defines a class for a Fenwick Tree 3D (Binary Indexed Tree 3D).
 *        State: tested.
 *
 * \tparam ValueType Type of the elements.
 * \tparam MaxDim1 Maximum size of the first dimension.
 * \tparam MaxDim2 Maximum size of the second dimension.
 * \tparam MaxDim3 Maximum size of the third dimension.
 */
template<typename ValueType, int MaxDim1, int MaxDim2, int MaxDim3>
class FenwickTree3DPointUpdateRangeQuery {
private:
	int d1, d2, d3;
	ValueType bit[MaxDim1 + 1][MaxDim2 + 1][MaxDim3 + 1];

public:

	void init(int dim1, int dim2, int dim3) {
		d1 = dim1 + 1;
		d2 = dim2 + 1;
		d3 = dim3 + 1;
		for (int i = 0; i < d1; i++)
			for (int j = 0; j < d2; j++)
				memset(bit[i][j], 0, sizeof(ValueType) * d3);
	}

	void init(std::vector<std::vector<std::vector<ValueType>>>& mat) {
		init(mat.size(), mat[0].size(), mat[0][0].size());
		for (size_t i = 0; i < mat.size(); i++)
			for (size_t j = 0; j < mat[i].size(); j++)
				for (size_t k = 0; k < mat[i][j].size(); k++)
					add(i, j, k, mat[i][j][k]);
	}

	void add(int x, int y, int z, ValueType delta) {
		for (int i = x + 1; i < d1; i += i & -i)
			for (int j = y + 1; j < d2; j += j & -j)
				for (int k = z + 1; k < d3; k += k & -k)
					bit[i][j][k] += delta;
	}

	ValueType sum(int x, int y, int z) {
		ValueType ret = 0;
		for (int i = x + 1; i > 0; i -= i & -i)
			for (int j = y + 1; j > 0; j -= j & -j)
				for (int k = z + 1; k > 0; k -= k & -k)
					ret += bit[i][j][k];
		return ret;
	}

	ValueType sum(int x1, int y1, int z1, int x2, int y2, int z2) {
		auto val1 = sum(x2, y2, z2) - sum(x1 - 1, y2, z2) - sum(x2, y1 - 1, z2) + sum(x1 - 1, y1 - 1, z2);
		auto val2 = sum(x2, y2, z1 - 1) - sum(x1 - 1, y2, z1 - 1) - sum(x2, y1 - 1, z1 - 1) + sum(x1 - 1, y1 - 1, z1 - 1);
		return val1 - val2;
	}
};

/**
 * \brief Defines a class for a Fenwick Tree (Binary Indexed Tree) for Min/Max value.
 *        State: tested.
 *
 * \tparam ValueType Type of the elements.
 * \tparam MaxSize Maximum number of elements.
 * \tparam ElementCompare Comparator function to use (std::less by default, for a range minimum query).
 * \tparam LimitValue Limit value, used for initialization (std::numeric_limits<ValueType>::max() by default).
 */
template<typename ValueType, int MaxSize, typename ElementCompare = std::less<ValueType>, ValueType LimitValue = std::numeric_limits<ValueType>::max()>
class FenwickTreeMinMax {
private:
	int n;
	ValueType bit[MaxSize + 1];
	ElementCompare elementCompare;

public:

	ValueType Limit = LimitValue;

	void init(int size) {
		n = size + 1;
		std::fill(bit, bit + n, LimitValue);
	}

	void init(int size, ValueType* arr) {
		init(size);
		for (size_t i = 0; i < size; i++)
			update(i, arr[i]);
	}

	void init(std::vector<ValueType>& arr) {
		init(arr.size(), &arr[0]);
	}

	void update(int idx, ValueType val) {
		for (++idx; idx < n; idx += idx & -idx)
			bit[idx] = elementCompare(bit[idx], val) ? bit[idx] : val;
	}

	ValueType getValue(int r) {
		ValueType ret = LimitValue;
		for (++r; r > 0; r -= r & -r)
			ret = elementCompare(bit[r], ret) ? bit[r] : ret;
		return ret;
	}
};
