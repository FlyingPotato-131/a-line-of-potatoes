#include <iostream>
#include <vector>

struct triDiagMatrix{
	std::vector<double> a;
	std::vector<double> b;
	std::vector<double> c;
};

// std::vector<double> thomasMethod(const triDiagMatrix &A, const std::vector<double> &f);
void thomasMethod(const triDiagMatrix *A, const std::vector<double> *f, std::vector<double> *x);