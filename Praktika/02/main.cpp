#include <iostream>
#include "CMyMatrix.hpp"

using namespace std;

CMyVektor a2_f(CMyVektor x) {
	CMyVektor result(3);
	result[0] = x[0] * x[1] * exp(x[2]);
	result[1] = x[1] * x[2] * x[3];
	result[2] = x[3];
	return result;
}

CMyVektor a3_f(CMyVektor x) {
	CMyVektor result(2);
	result[0] = x[0] * x[0] * x[0] * x[1] * x[1] * x[1] - 2 * x[1];
	result[1] = x[0] - 2;
	return result;
}

int main() {
	CMyMatrix m(2, 2);

	m[{0, 0}] = 1;
	m[{0, 1}] = 2;
	m[{1, 0}] = 3;
	m[{1, 1}] = 4;

	cout << m << endl;
	cout << m * CMyVektor({ 1, 2 }) << endl << endl;
	cout << m.invers() << endl;

	cout << jacobi(CMyVektor({ 1, 2, 0, 3 }), a2_f);

	cout << newtonMethod(CMyVektor({ 1,1 }), a3_f) << endl;

	return 0;
}
