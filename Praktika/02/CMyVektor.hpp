#include <vector>
#include <math.h>
#include <iostream>

/*
 * Aufgabe 1
*/

class CMyVektor {
private:
	std::vector<double> values;

public:
	CMyVektor(unsigned size) {
		values.resize(size);
	}

	CMyVektor(std::vector<double> values) {
		this->values = values;
	}

	unsigned getSize() const {
		return values.size();
	}

	double getIndex(unsigned index) const {
		return values[index];
	}

	void setIndex(unsigned index, double value) {
		values[index] = value;
	}

	double getLength() const {
		double result = 0;

		for (double val : values) {
			result += pow(val, 2);
		}

		return sqrt(result);
	}

	CMyVektor operator+(const CMyVektor& other) const {
		if (values.size() != other.values.size()) throw;

		CMyVektor result(values.size());

		for (unsigned i = 0; i < values.size(); i++) {
			result.values[i] = values[i] + other.values[i];
		}

		return result;
	}

	CMyVektor operator*(const double& lambda) const {
		CMyVektor result(values.size());

		for (unsigned i = 0; i < values.size(); i++) {
			result.values[i] = lambda * values[i];
		}

		return result;
	}

	double& operator[](unsigned i) {
		return values[i];
	}

	friend std::ostream& operator<<(std::ostream& stream, const CMyVektor& vector);
};

CMyVektor operator*(const double& lambda, const CMyVektor& vector) {
	return vector * lambda;
}

std::ostream& operator<<(std::ostream& stream, const CMyVektor& vector) {
	stream << "[";

	for (unsigned i = 0; i < vector.values.size(); i++) {
		stream << vector.values[i];
		if (i < vector.values.size() - 1) stream << ", ";
	}
	stream << "]";

	return stream;
}

/*
 * Aufgabe 2
*/

const double h_vektor = pow(10, -8);

CMyVektor gradient(CMyVektor x, double (*f)(CMyVektor x)) {
	CMyVektor g = CMyVektor(x.getSize());

	for (unsigned i = 0; i < g.getSize(); i++) {
		CMyVektor tmp = x;
		tmp[i] = tmp[i] + h_vektor;

		g[i] = (f(tmp) - f(x)) / h_vektor;
	}

	return g;
}

/*
 * Aufgabe 3
 */

const double tolerance = pow(10, -5);

CMyVektor gradMax(CMyVektor x, double (*f)(CMyVektor x), double lambda = 1) {
	for (int i = 0; i < 25; i++) {
		CMyVektor tmp = gradient(x, f);

		if (tmp.getLength() < tolerance) break;

		CMyVektor nextX = lambda * tmp + x;

		if (f(nextX) <= f(x)) {
			while (f(nextX) <= f(x)) {
				lambda /= 2;
				nextX = lambda * tmp + x;
			}
		} else {
			lambda *= 2;
			x = lambda * tmp + x;

			if (f(x) > f(nextX)) continue;
			lambda /= 2;
		}

		x = nextX;
	}

	return x;
}
