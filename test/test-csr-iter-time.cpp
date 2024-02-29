#include "csr-matrix.h"
#include <gtest/gtest.h>
#include <fstream>
#include <chrono>

TEST(csr, iter_convergence_compare){
	std::vector<double> mtrData = { 5, -2, 0, -1, 0, 0, 0, 0, 0,
								-2, 3, 0, -0.2, 0, 0, 0, 0, 0,
								 0, 0, 7, 0, 0, 0, 0, 2, 0,
								-1, -0.2, 0, 2, 0, 0, 0, 0, 0,
								 0, 0, 0, 0, 7, 0, 0, 0, 0,
								 0, 0, 0, 0, 6, 2, 0, 0, 0,
								 0, 0, 9, 0, 0, 0, 5, 0, 0,
								 0, 7, 0, 0, 0, 3, 0, 1, 0,
								 0, 0, 0, 2, 0, 0, 0, 0, 2};
	csrMatrix<double> mtr = csrMatrix<double>(mtrData, 9);
	std::vector<double> v = {-7, -9, -5, 8, -8, -6, -8, 1, -8};
	std::vector<double> start = {100, 100, 100, 100, 100, 100, 100, 100, 100};
	// std::vector<double> res = {-2.90666666666666667, -4.8, -10.23265306122448980, 2.06666666666666667, -1.14285714285714286, 0.42857142857142857, 16.81877551020408163, 33.31428571428571429, -6.06666666666666667};

	std::ofstream data;
	data.open("../timestamps-iter-convergence-compare/data.csv");
	data << "Niter, simple time, simple error, jakobi time, jakobi error, gs time, gs error\n";

	for(size_t N = 1; N < 1000; N++){
		data << N << ",";

		auto startTime = std::chrono::high_resolution_clock::now();
		double error = abs(v - mtr * simpleIterMethod(mtr, v, start, 0.0, N, 0.25)) / abs(v);
		auto endTime = std::chrono::high_resolution_clock::now();
		auto dtime = duration_cast<std::chrono::microseconds>(endTime - startTime).count();
		data << dtime << "," << error << ",";

		startTime = std::chrono::high_resolution_clock::now();
		error = abs(v - mtr * jakobiMethod(mtr, v, start, 0.0, N)) / abs(v);
		endTime = std::chrono::high_resolution_clock::now();
		dtime = duration_cast<std::chrono::microseconds>(endTime - startTime).count();
		data << dtime << "," << error << ",";

		startTime = std::chrono::high_resolution_clock::now();
		error = abs(v - mtr * gaussSeidelMethod(mtr, v, start, 0.0, N)) / abs(v);
		endTime = std::chrono::high_resolution_clock::now();
		dtime = duration_cast<std::chrono::microseconds>(endTime - startTime).count();
		data << dtime << "," << error << "\n";
	}

	data.close();
}
