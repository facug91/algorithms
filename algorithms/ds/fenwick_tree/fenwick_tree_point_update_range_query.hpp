#include <bits/stdc++.h>

using namespace std;

/**
 * \brief Defines a class for a Fenwick Tree (Binary Indexed Tree).
 *        State: tested.
 *        Ref: Competitive Programming 3, section 2.4.4
 *             https://cp-algorithms.com/data_structures/fenwick.html
 *             https://www.geeksforgeeks.org/binary-indexed-tree-range-update-range-queries/
 *
 * \tparam ValueType Type of the elements.
 */
template<typename ValueType>
class FenwickTreePointUpdateRangeQuery {
private:
	int n{};
	vector<ValueType> bit;

	int log2_floor(ValueType i) {
		return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1;
	}

public:

	void init(int size) {
		n = size + 1;
		bit.assign(n, 0);
	}

	void init(int size, ValueType val) {
		n = size + 1;
		bit.assign(n, val);
		bit[0] = 0;
		for (size_t i = 0; i < n; i++) {
			size_t j = i + (i & -i);
			if (j <= n) bit[j] += bit[i];
		}
	}

	void init(const std::vector<ValueType>& arr) {
		n = arr.size() + 1;
		bit.resize(n);
		bit[0] = 0;
		std::copy(arr.begin(), arr.end(), std::next(bit.begin()));
		for (size_t i = 0; i < n; i++) {
			size_t j = i + (i & -i);
			if (j <= n) bit[j] += bit[i];
		}
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

	ValueType searchPos(ValueType v) {
		ValueType sum = 0;
		int pos = 0;
		for (int i = log2_floor(n); i >= 0; i--) {
			if (pos + (1 << i) < n and sum + bit[pos + (1 << i)] < v) {
				sum += bit[pos + (1 << i)];
				pos += (1 << i);
			}
		}
		return pos;
	}
};

int main() {
	int n = 5;
	FenwickTreePointUpdateRangeQuery<int> bit;

	// print all zeros
	bit.init(n);
	for (int i = 0; i < n; i++)
		cout << bit.sum(i) << " ";
	cout << endl;

	// print 1 to n
	bit.init(5, 1);
	for (int i = 0; i < n; i++)
		cout << bit.sum(i) << " ";
	cout << endl;

	// print 1 to n*(n+1)/2
	vector<int> v = { 1, 2, 3, 4, 5 };
	bit.init(v);
	for (int i = 0; i < n; i++)
		cout << bit.sum(i) << " ";
	cout << endl;

	// print 1 to n*(n+1)/2
	bit.init(5);
	for (int i = 0; i < n; i++) {
		bit.add(i, i + 1);
		cout << bit.sum(i) << " ";
	}
	cout << endl;

	// print 0 to n-1
	for (int i = 1; i <= n; i++)
		cout << bit.searchPos(i) << " ";
	cout << endl;
}
