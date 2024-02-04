#include <iostream>
#include <vector>

struct triDiagMatrix{
	std::vector<double> a;
	std::vector<double> b;
	std::vector<double> c;
};

std::vector<double> thomasMethod(triDiagMatrix A, std::vector<double> f);