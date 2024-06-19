#include <vector>
#include <cmath>
#include <iostream>

class CKomplex {
private:
	double real;
	double imag;

public:
	CKomplex() : real{ 0 }, imag{ 0 } { }
	CKomplex(double real, double imag) : real{ real }, imag{ imag } { }
	CKomplex(double phi) : real{ cos(phi) }, imag{ sin(phi) } { }

	double re() const {
		return real;
	}

	double im() const {
		return imag;
	}

	CKomplex operator+(const CKomplex other) const {
		return CKomplex(other.real + real, other.imag + imag);
	}

	CKomplex operator-(const CKomplex other) const {
		return CKomplex(other.real - real, other.imag - imag);
	}

	CKomplex operator*(const CKomplex other) const {
		return CKomplex(
			other.real * real - other.imag * imag,
			other.imag * real + other.real * imag
		);
	}

	CKomplex operator*(const double other) const {
		return CKomplex(other * real, other * imag);
	}

	double abs() const {
		return sqrt(real * real + imag * imag);
	}
};

CKomplex operator*(double a, CKomplex b) {
	return b * a;
}

std::ostream& operator<<(std::ostream& stream, CKomplex a) {
	stream.precision(4);
	stream << std::fixed << a.re() << "+j*" << (a.im());
	return stream;
}

std::vector<CKomplex> fourierTransformation(const std::vector<CKomplex> input, bool inv = false) {
	const double INV_SQRT_N = 1.0 / sqrt(input.size());
	const double INV_N_2PI = (inv ? 1.0 : -1.0) / input.size() * M_PI * 2.0;

	std::vector<CKomplex> output(input.size());

	for (double n = 0; n < output.size(); n++) {
		CKomplex sum;

		for (double k = 0; k < input.size(); k++) {
			sum = sum + input[k] * CKomplex(n * INV_N_2PI * k);
		}

		output[n] = sum * INV_SQRT_N;
	}

	return output;
}
