#pragma once
#include "CMyVektor.hpp"
#include <iostream>
#include <vector>
#include <utility>

/*
 * Aufgabe 1
 */

class CMyMatrix {
private:
	std::vector<std::vector<double>> data;

public:
	CMyMatrix(unsigned dimensions) : data{ std::vector<std::vector<double>>(dimensions, std::vector<double>(dimensions, 0)) } { };
	CMyMatrix(unsigned width, unsigned height) : data{ std::vector<std::vector<double>>(height, std::vector<double>(width, 0)) } { };

	CMyMatrix invers() {
		if (data.size() != 2 || data[0].size() != 2) {
			std::cout << "Matrix not 2x2." << std::endl;
			throw;
		}

		CMyMatrix m(data.size());

		double magicNumber = 1 / (data[0][0] * data[1][1] - data[0][1] * data[1][0]);

		m.data[0][0] = magicNumber * data[1][1];
		m.data[0][1] = magicNumber * -data[0][1];
		m.data[1][0] = magicNumber * -data[1][0];
		m.data[1][1] = magicNumber * data[0][0];

		return m;
	}

	CMyVektor operator*(CMyVektor x) const {
		if (data.size() == 0 || data[0].size() != x.getSize()) throw;

		CMyVektor res(data.size());

		for (unsigned i = 0; i < data.size(); i++) {
			for (unsigned j = 0; j < data[0].size(); j++) {
				res[i] += data[i][j] * x[j];
			}
		}

		return res;
	}

	double& operator[](std::pair<unsigned, unsigned> v) {
		return data[v.first][v.second];
	}

	CMyMatrix jacobi(CMyVektor x, CMyVektor(*function)(CMyVektor x));

	friend std::ostream& operator<<(std::ostream& stream, const CMyMatrix& matrix);
};

std::ostream& operator<<(std::ostream& stream, const CMyMatrix& matrix) {
	if (matrix.data.size() == 0) {
		stream << "++" << std::endl << "++" << std::endl;
		return stream;
	}

	unsigned maxLength = 0;

	for (unsigned i = 0; i < matrix.data.size(); i++) {
		const std::vector<double>& column = matrix.data[i];

		for (unsigned j = 0; j < column.size(); j++) {
			if (std::to_string(column[j]).length() <= maxLength) continue;
			maxLength = std::to_string(column[j]).length();
		}
	}

	for (unsigned i = 0; i < matrix.data[0].size(); i++) {
		stream << "+-";
		for (unsigned j = 0; j < maxLength; j++) {
			stream << '-';
		}
		stream << '-';
	}
	stream << '+' << std::endl;

	for (unsigned i = 0; i < matrix.data.size(); i++) {
		const std::vector<double>& column = matrix.data[i];

		for (unsigned j = 0; j < column.size(); j++) {
			stream << "| ";
			for (unsigned k = 0; k < maxLength - std::to_string(column[j]).length(); k++) {
				stream << " ";
			}
			stream << std::to_string(column[j]) << ' ';
		}
		stream << '|' << std::endl;

		for (unsigned j = 0; j < column.size(); j++) {
			stream << "+-";
			for (unsigned k = 0; k < maxLength; k++) {
				stream << '-';
			}
			stream << '-';
		}
		stream << '+' << std::endl;
	}

	return stream;
}

/*
 * Aufgabe 2
 */

const double h_matrix = .0001;

CMyMatrix jacobi(CMyVektor x, CMyVektor(*function)(CMyVektor x)) {
	unsigned m = x.getSize();
	unsigned n = function(x).getSize();
	CMyMatrix jacobiMatrix(m, n);

	for (unsigned i = 0; i < m; i++) {
		CMyVektor x_h = x;
		x_h[i] += h_matrix;
		CMyVektor f_x_h = function(x_h);
		CMyVektor f_x = function(x);

		for (unsigned j = 0; j < n; j++) {
			jacobiMatrix[{j, i}] = (f_x_h[j] - f_x[j]) / h_matrix;
		}
	}

	return jacobiMatrix;
}

/*
 * Aufgabe 3
 */

CMyVektor newtonMethod(CMyVektor x, CMyVektor(*function)(CMyVektor x)) {
	for (unsigned i = 0; i < 50; i++) {
		CMyVektor F = function(x);
		double len = F.getLength();
		if (len < .00001) {
			break;
		}

		CMyMatrix J = jacobi(x, function);
		CMyMatrix J_inv = J.invers();
		CMyVektor delta_x = J_inv * F;

		x = x + -1 * delta_x;
	}

	return x;
}
