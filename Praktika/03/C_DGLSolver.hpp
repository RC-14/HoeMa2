#include "CMyVektor.hpp"

#pragma once

class C_DGLSolver {
private:
	bool n1;
	CMyVektor(*f_DGL_System)(CMyVektor y, double x);
	double (*f_DGL_nterOrdnung)(CMyVektor y, double x);

	CMyVektor ableitungen(CMyVektor y, double x) {
		if (n1) {
			return f_DGL_System(y, x);
		}

		CMyVektor result(y.getSize());

		for (unsigned i = 0; i < y.getSize() - 1; i++) {
			result[i] = y[i + 1];
		}
		result[y.getSize() - 1] = f_DGL_nterOrdnung(y, x);

		return result;
	}

public:
	C_DGLSolver(CMyVektor(*f_DGL_System)(CMyVektor y, double x)) : n1{ true }, f_DGL_System{ f_DGL_System }, f_DGL_nterOrdnung{ nullptr } { };
	C_DGLSolver(double (*f_DGL_nterOrdnung)(CMyVektor y, double x)) : n1{ false }, f_DGL_System{ nullptr }, f_DGL_nterOrdnung{ f_DGL_nterOrdnung } { };

	CMyVektor euler(double xStart, double xEnd, unsigned schritte, CMyVektor y) {
		double schrittWeite = (xEnd - xStart) / schritte;

		double x = xStart;
		for (unsigned i = 0; i < schritte; i++) {
			CMyVektor abl = ableitungen(y, x);

			// Logging
			// std::cout
			// 	<< "x:\t" << x << std::endl
			// 	<< "y:\t" << y << std::endl
			// 	<< "y':\t" << abl << std::endl << std::endl;

			y = y + abl * schrittWeite;

			x += schrittWeite;
		}

		return y;
	}

	CMyVektor heun(double xStart, double xEnd, unsigned schritte, CMyVektor y) {
		double schrittWeite = (xEnd - xStart) / schritte;

		double x = xStart;
		for (unsigned i = 0; i < schritte; i++) {
			double nextX = x + schrittWeite;

			CMyVektor abl1 = ableitungen(y, x);
			CMyVektor yTest = y + abl1 * schrittWeite;
			CMyVektor abl2 = ableitungen(yTest, nextX);

			CMyVektor ablMittel = (abl1 + abl2) * .5;

			// Logging
			// std::cout
			// 	<< "x:\t\t\t" << x << std::endl
			// 	<< "y:\t\t\t" << y << std::endl
			// 	<< "y'_orig:\t" << abl1 << std::endl
			// 	<< "y_Test:\t\t" << yTest << std::endl
			// 	<< "y'_Test:\t" << abl2 << std::endl
			// 	<< "y'_Mittel:\t" << ablMittel << std::endl << std::endl;

			y = y + ablMittel * schrittWeite;

			x = nextX;
		}

		return y;
	}
};
