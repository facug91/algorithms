#include <bits/stdc++.h>

template <typename T>
T exgcd (T a, T b, T& x, T& y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	T d = exgcd(b, a%b, x, y);
	T x1 = y;
	T y1 = x - (a / b) * y;
	x = x1;
	y = y1;
	return d;
}

int main () {
	int x, y, a = 21, b = 35;
	std::cout << exgcd(a, b, x, y) << std::endl;
	std::cout << x << " " << y << std::endl;
}
