#include <iostream>
#include "C_DGLSolver.hpp"
using namespace std;

CMyVektor f_dglSystem(CMyVektor y, double x) {
	return CMyVektor({
			2 * y[1] - x * y[0],
			y[0] * y[1] - 2 * x * x * x
		});
}

double f_dgl3terOrdnung(CMyVektor y, double x) {
	return 2 * x * y[1] * y[2] + 2 * y[0] * y[0] * y[1];
}

int main() {
	cout << "DGL-System:" << endl;
	C_DGLSolver dgls(f_dglSystem);
	cout << "Euler:\t" << dgls.euler(0, 2, 100, CMyVektor({ 0, 1 })) << endl;
	cout << "Heun:\t" << dgls.heun(0, 2, 100, CMyVektor({ 0, 1 })) << endl;
	cout << endl;

	cout << "DGL-System 3ter Ordnung:" << endl;
	C_DGLSolver dgl3s(f_dgl3terOrdnung);
	for (unsigned i = 10; i <= 10000; i *= 10) {
		cout << i << ':' << endl;
		cout << "\tEuler:\t" << (dgl3s.euler(1, 2, i, CMyVektor({ 1, -1, 2 })))[0] - .5 << endl;
		cout << "\tHeun:\t" << (dgl3s.heun(1, 2, i, CMyVektor({ 1, -1, 2 })))[0] - .5 << endl;
		cout << endl;
	}

	return 0;
}
