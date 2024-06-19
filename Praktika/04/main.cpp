#include <iostream>
#include <fstream>   
#include <vector>
#include "CKomplex.hpp"

using namespace std;

vector<CKomplex> werte_einlesen(const std::string dateiname) {
	int i, N, idx;
	double re, im;
	vector<CKomplex> werte;
	// File oeffnen
	ifstream fp;
	fp.open(dateiname);
	// Dimension einlesen
	fp >> N;
	// Werte-Vektor anlegen
	werte.resize(N);
	CKomplex null(0, 0);
	for (i = 0; i < N; i++)
		werte[i] = null;
	// Eintraege einlesen und im Werte-Vektor ablegen
	while (!fp.eof()) {
		fp >> idx >> re >> im;
		CKomplex a(re, im);
		werte[idx] = a;
	}
	// File schliessen
	fp.close();

	return werte;
}

void werte_ausgeben(const std::string dateiname, const vector<CKomplex> werte, double epsilon = -1) {
	int i;
	int N = werte.size();
	// File oeffnen
	ofstream fp;
	fp.open(dateiname);
	// Dimension in das File schreiben
	fp << N << endl;
	// Eintraege in das File schreiben
	fp.precision(10);
	for (i = 0; i < N; i++)
		if (werte[i].abs() > epsilon)
			fp << i << "\t" << werte[i].re() << "\t" << werte[i].im() << endl;
	// File schliessen
	fp.close();
}

double maxAbw(const vector<CKomplex> a, const vector<CKomplex> b) {
	double maxAbw = 0;
	for (unsigned i = 0; i < b.size(); i++) {
		double abw = (a[i] - b[i]).abs();
		if (abw > maxAbw) maxAbw = abw;
	}

	return maxAbw;
}

int main() {
	for (int fileNum = 1; fileNum <= 2; fileNum++) {
		const vector<CKomplex> origWerte = werte_einlesen("original_" + to_string(fileNum) + ".txt");

		const vector<CKomplex> fourier = fourierTransformation(origWerte);
		werte_ausgeben("output_fourier_" + to_string(fileNum) + ".txt", fourier);
		const vector<CKomplex> invFourier = fourierTransformation(werte_einlesen("output_fourier_" + to_string(fileNum) + ".txt"), true);
		werte_ausgeben("output_inv_fourier_" + to_string(fileNum) + ".txt", invFourier);
		cout << "Max Abweichung \"output_fourier_" + to_string(fileNum) + ".txt\": " << maxAbw(origWerte, invFourier) << endl;

		for (double eps = .001; eps <= 1; eps *= 10) {
			const string filename = "output_fourier_eps_" + to_string(eps) + "_" + to_string(fileNum) + ".txt";
			werte_ausgeben(filename, fourier, eps);

			cout << "Max Abweichung \"" + filename + "\": " << maxAbw(origWerte, fourierTransformation(werte_einlesen(filename), true)) << endl;
		}
	}

	const vector<CKomplex> bildOrig = werte_einlesen("bild.txt");
	const vector<CKomplex> bildFourier = fourierTransformation(bildOrig);

	for (double eps = 10; eps <= 100; eps *= eps / 10 + 1) {
		werte_ausgeben("bild_fourier_eps_" + to_string(eps) + ".txt", bildFourier, eps);
		const vector<CKomplex> bildFourierEps = werte_einlesen("bild_fourier_eps_" + to_string(eps) + ".txt");
		const vector<CKomplex> bildFourierEpsInv = fourierTransformation(bildFourierEps, true);
		werte_ausgeben("bild_fourier_eps_" + to_string(eps) + "_inv.txt", bildFourierEpsInv);
	}

	double eps = 300;
	werte_ausgeben("bild_fourier_eps_" + to_string(eps) + ".txt", bildFourier, eps);
	const vector<CKomplex> bildFourierEps = werte_einlesen("bild_fourier_eps_" + to_string(eps) + ".txt");
	const vector<CKomplex> bildFourierEpsInv = fourierTransformation(bildFourierEps, true);
	werte_ausgeben("bild_fourier_eps_" + to_string(eps) + "_inv.txt", bildFourierEpsInv);

	return 0;
}
