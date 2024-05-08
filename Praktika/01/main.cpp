#include <iostream>
#include "CMyVektor.hpp"

using namespace std;

double u(CMyVektor x) {
	return x.getLength();
}

double f(CMyVektor x) {
	return sin(x[0] * x[1]) + sin(x[0]) + cos(x[1]);
}

double g(CMyVektor x) {
	return -(2 * pow(x[0], 2) - 2 * x[0] * x[1] + pow(x[1], 2) + pow(x[2], 2) - 2 * x[0] - 4 * x[2]);
}

int main() {
	CMyVektor a = CMyVektor({ 0, 3, 0 });
	CMyVektor b = CMyVektor({ 4, 0, 0 });

	CMyVektor x1 = CMyVektor({ 0.2, -2.1 });
	CMyVektor x2 = CMyVektor(3);

	cout
		<< "a: " << a << endl
		<< "b: " << b << endl
		<< "a.getLength(): " << a.getLength() << endl
		<< "a + b: " << a + b << endl
		<< "2 * a: " << 2 * a << endl
		<< "gradient(a + b, u(x)): " << gradient(a + b, u) << endl
		<< "gradMax(x1, f): " << gradMax(x1, f) << endl
		<< "gradMax(x2, g, 0.1): " << gradMax(x2, g, .1) << endl;

	return 0;
}
