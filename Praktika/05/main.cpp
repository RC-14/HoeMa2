#include <iostream>
#include "CRand.hpp"
#include <vector>

using namespace std;

vector<unsigned> ziehKarten(unsigned n) {
	CRand randHelp;
	vector<unsigned> karten(n);

	for (unsigned i = 0; i < n; i++) {
		bool unique = false;

		do {
			karten[i] = randHelp.wert(0, 51);
			unique = true;

			for (unsigned j = 0; j < i; j++) {
				if (karten[j] != karten[i]) continue;

				unique = false;
				break;
			}
		} while (!unique);
	}

	return karten;
}

void monteCarlo_poker(unsigned n) {
	unsigned totalTwoPair = 0;
	unsigned totalThreeOfAKind = 0;

	for (unsigned i = 0; i < n; i++) {
		vector<unsigned> karten = ziehKarten(7);
		vector<unsigned> wertAnz(13);
		vector<unsigned> farbeAnz(4);

		for (unsigned j = 0; j < karten.size(); j++) {
			wertAnz[karten[j] % 13]++;
			farbeAnz[karten[j] / 13]++;
		}

		// Ignore Flush variations
		bool flush = false;
		for (int j = 0; j < farbeAnz.size(); j++) {
			if (farbeAnz[j] < 5) continue;
			flush = true;
			break;
		}
		if (flush) continue;

		unsigned pair = 0;
		unsigned threeOfAKind = 0;
		unsigned straightLen = 0;
		for (unsigned j = 0; j < wertAnz.size(); j++) {
			if (wertAnz[j] == 0) {
				straightLen = 0;
				continue;
			}

			straightLen++;
			if (straightLen == 5) break;

			if (wertAnz[j] == 3) {
				threeOfAKind++;
			} else if (wertAnz[j] == 2) {
				pair++;
			}
		}
		// Ignore Straight
		if (straightLen == 5) continue;
		// Ignore Full House
		if (pair > 0 && threeOfAKind > 0) continue;

		if (pair > 1) {
			totalTwoPair++;
		} else if (threeOfAKind > 0) {
			totalThreeOfAKind++;
		}
	}

	cout
		<< "Monte Carlo (Poker):" << endl
		<< "\tn: " << n << endl
		<< "\tTwo Pair: " << totalTwoPair << " (" << totalTwoPair / double(n) * 100 << "%)" << endl
		<< "\tThree of a Kind: " << totalThreeOfAKind << " (" << totalThreeOfAKind / double(n) * 100 << "%)" << endl;

}

int main() {
	CRand randHelp = CRand();
	randHelp.test(5, 15, 99999999);
	cout << endl;
	randHelp.test_falsch(5, 15, 99999999);
	cout << endl;

	monteCarlo_poker(500);
	
	return 0;
}
