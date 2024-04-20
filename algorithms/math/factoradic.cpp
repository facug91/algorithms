#include <bits/stdc++.h>

using namespace std;

/**
 * \brief Defines a class for a factoradic representation of permutations.
 *        State: tested.
 *        Ref: https://en.wikipedia.org/wiki/Factorial_number_system
 *             https://blatherstrike.blogspot.com/2020/03/treesbinary-lifting-501-d-misha-and.html
 */
class Factoradic {
private:

	class FenwickTreePointUpdateRangeQuery {
	private:
		int n{};
		std::vector<int> bit;

		int log2_floor(int i) {
			return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1;
		}

	public:

		// A Binary Indexed Tree with binary lifting is needed in order to work in O(n*log(n))
		FenwickTreePointUpdateRangeQuery(int size, int val) {
			n = size + 1;
			bit.assign(n, val);
			bit[0] = 0;
			for (size_t i = 0; i < size; i++) {
				size_t j = i + (i & -i);
				if (j <= n) bit[j] += bit[i];
			}
		}

		void add(int idx, int delta) {
			for (++idx; idx < n; idx += idx & -idx)
				bit[idx] += delta;
		}

		int sum(int r) {
			int ret = 0;
			for (++r; r > 0; r -= r & -r)
				ret += bit[r];
			return ret;
		}

		int searchPos(int v) {
			int sum = 0;
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

	template<typename T>
	T fastMod(const T input, const T ceil) {
		return input >= ceil ? input % ceil : input;
	}

	std::vector<int> factoradic;

public:

	size_t size() {
		return factoradic.size();
	}

	// Creates a factoradic from an integer number
	void createFromInt(uint64_t n) {
		for (uint64_t i = 1; n > 0; i++, n /= i)
			factoradic.push_back(int(n % i));
		reverse(factoradic.begin(), factoradic.end());
	}

	// Creates a factoradic representing the order of the permutation
	void ordOfPermutation(const std::vector<int>& permutation) {
		FenwickTreePointUpdateRangeQuery bit(permutation.size(), 0);
		factoradic.assign(permutation.size(), 0);
		for (int i = 0; i < permutation.size(); i++) {
			factoradic[i] = permutation[i] - bit.sum(permutation[i]);
			bit.add(permutation[i], 1);
		}
	}

	uint64_t getDecimal() {
		int n = factoradic.size();
		uint64_t ans = 0;
		for (int i = 0, mul = n; i < n; i++, mul--) {
			ans = ans * mul + factoradic[i];
		}
		return ans;
	}

	uint64_t getDecimal(uint64_t mod) {
		uint64_t n = factoradic.size();
		uint64_t ans = 0;
		for (uint64_t i = 0, mul = n; i < n; i++, mul--)
			ans = fastMod(fastMod(ans * mul, mod) + factoradic[i], mod);
		return ans;
	}

	vector<int> getPermutationOfSizeN(int n) {
		FenwickTreePointUpdateRangeQuery bit(n, 1);
		vector<int> perm;
		for (int i = 0; i < n; i++) {
			int pos = bit.searchPos(factoradic[i]+1);
			perm.push_back(pos);
			bit.add(pos, -1);
		}
		return perm;
	}

	void add(const Factoradic& fac) {
		auto aux = fac.factoradic;
		std::reverse(aux.begin(), aux.end());
		std::reverse(factoradic.begin(), factoradic.end());
		int minSize = (int)min(aux.size(), factoradic.size());
		bool carry = false;
		int i = 0;
		for (; i < minSize; i++) {
			factoradic[i] += aux[i] + carry;
			carry = factoradic[i] / (i + 1);
			factoradic[i] = fastMod(factoradic[i], (i + 1));
		}
		for (; i < factoradic.size(); i++) {
			factoradic[i] += carry;
			carry = factoradic[i] / (i + 1);
			factoradic[i] = fastMod(factoradic[i], (i + 1));
		}
		while (i < aux.size()) {
			factoradic.push_back(aux[i] + carry);
			carry = factoradic[i] / (i + 1);
			factoradic[i] = fastMod(factoradic[i], (i + 1));
		}
		if (carry)
			factoradic.push_back(carry);
		std::reverse(factoradic.begin(), factoradic.end());
	}

	// Since factoradics represents the number as x*(n-1)!+y*(n-2)!+...w*0!
	// factoradic % (N-1)! is the same as removing the first element
	void modLastNFactorial() {
		if (!factoradic.empty())
			factoradic.erase(factoradic.begin());
	}

	void print() {
		for (int f: factoradic)
			cout << f << " ";
		cout << endl;
	}
};

int main() {
	int n = 4;
	vector<int> perm1 = {0, 1, 3, 2}; // ord = 1
	Factoradic f1;
	f1.ordOfPermutation(perm1);
	cout << "factoradic1 ";
	f1.print();

	vector<int> perm2 = {3, 2, 1, 0}; // ord = 3×3!+2×2!+1*1!+0*0! = 23
	Factoradic f2;
	f2.ordOfPermutation(perm2);
	cout << "factoradic2 ";
	f2.print();

	f1.add(f2);
	cout << "factoradic1 after add ";
	f1.print();
	if (f1.size() > n)
		f1.modLastNFactorial();
	cout << "factoradic1 after mod ";
	f1.print();

	vector<int> perm = f1.getPermutationOfSizeN(n);
	cout << "Final permutation ";
	for (int p : perm)
		cout << p << " ";
}
