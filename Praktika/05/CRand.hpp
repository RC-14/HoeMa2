#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
#pragma once

class CRand {
private:
public:
	CRand() { }
	int wert(int a, int b) const {
		return rand() % (b - a + 1) + a;
	}
	void initialisiere(int s) const {
		srand(s);
	}
	void test(int a, int b, int N) const {
		unsigned len = b - a + 1;
		unsigned* counters = new unsigned[len];
		unsigned bStrLen = std::to_string(b).length();
		std::string header = "-------- test(" + std::to_string(a) + ", " + std::to_string(b) + ", " + std::to_string(N) + ") ---------";

		std::cout << header << std::endl;

		for (unsigned i = 0; i < N; i++) {
			counters[wert(a, b) - a]++;
		}

		for (unsigned i = 0; i < len; i++) {
			std::cout << '\t';
			for (unsigned j = std::to_string(a + i).length(); j < bStrLen; j++) {
				std::cout << ' ';
			}
			std::cout << i + a << ": " << counters[i] << std::endl;
		}

		for (int i = 0; i < header.length(); i++) {
			std::cout << '-';
		}
		std::cout << std::endl;
	}
	void test_falsch(int a, int b, int N) const {
		unsigned len = b - a + 1;
		unsigned* counters = new unsigned[len];
		unsigned bStrLen = std::to_string(b).length();
		std::string header = "----- test_falsch(" + std::to_string(a) + ", " + std::to_string(b) + ", " + std::to_string(N) + ") -----";

		std::cout << header << std::endl;

		for (unsigned i = 0; i < N; i++) {
			initialisiere(time(NULL));
			counters[wert(a, b) - a]++;
		}

		for (unsigned i = 0; i < len; i++) {
			std::cout << '\t';
			for (unsigned j = std::to_string(a + i).length(); j < bStrLen; j++) {
				std::cout << ' ';
			}
			std::cout << i + a << ": " << counters[i] << std::endl;
		}

		for (int i = 0; i < header.length(); i++) {
			std::cout << '-';
		}
		std::cout << std::endl;
	}
};
