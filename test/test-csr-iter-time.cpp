#include "csr-matrix.h"
#include <gtest/gtest.h>
#include <fstream>
#include <chrono>

TEST(csr, iter_convergence_compare){
	// std::vector<double> mtrData = { 5, -2, 0, -1, 0, 0, 0, 0, 0,
	// 							-2, 3, 0, -0.2, 0, 0, 0, 0, 0,
	// 							 0, 0, 7, 0, 0, 0, 0, 2, 0,
	// 							-1, -0.2, 0, 2, 0, 0, 0, 0, 0,
	// 							 0, 0, 0, 0, 7, 0, 0, 0, 0,
	// 							 0, 0, 0, 0, 6, 2, 0, 0, 0,
	// 							 0, 0, 9, 0, 0, 0, 5, 0, 0,
	// 							 0, 7, 0, 0, 0, 3, 0, 1, 0,
	// 							 0, 0, 0, 2, 0, 0, 0, 0, 2};
	// std::vector<double> mtrData = {
	// 	5,	0,	0,	0,	0,	0,	0,	0,	0,
	// 	0,	100,0,	2,	0,	0,	0,	1,	0,
	// 	0,	0,	5,	0,	0,	0,	0,	0,	0,
	// 	0,	2,	0,	8,	0,	0,	0,	5,	0,
	// 	0,	0,	0,	0,	1,	0,	0,	0,	3,
	// 	0,	0,	0,	0,	0,	9,	0,	0,	0,
	// 	0,	0,	0,	0,	0,	0,	30,	0,	0,
	// 	0,	1,	0,	5,	0,	0,	0,	2,	0,
	// 	0,	0,	0,	0,	3,	0,	0,	0,	4
	// };
	std::vector<double> mtrData = {
		 5,	   2,	-1,	   0,	0,	0,	0,	0,	0,
		 2,	   3,	 0,	-0.2,	0,	0,	0,	0,	0,
		-1,	   0,	 7,	   0,	0,	0,	0,	0,	0,
		 0,	-0.2,	 0,	   2,	0,	0,	0,	0,	0,
		 0,	   0,	 0,	   0,	7,	0,	0,	0,	0,
		 0,	   0,	 0,	   0,	0,	2,	0,	0,	0,
		 0,	   0,	 0,	   0,	0,	0,	5,	0,	0,
		 0,	   0,	 0,	   0,	0,	0,	0,	1,	0,
		 0,	   0,	 0,	   0,	0,	0,	0,	0,	2
	};
	csrMatrix<double> mtr = csrMatrix<double>(mtrData, 9);
	std::vector<double> v = {-7, -9, -5, 8, -8, -6, -8, 1, -8};
	std::vector<double> start = {100, 100, 100, 100, 100, 100, 100, 100, 100};

	std::ofstream data;
	data.open("../timestamps-iter-convergence-compare/data.csv");
	data << "Niter, simple time, simple error, chebyshev time, chebyshev error, jakobi time, jakobi error, gs time, gs error, conjgrad time, conjgrad error\n";

	for(size_t N = 1; N < 1000; N++){
		data << N << ",";

		auto startTime = std::chrono::high_resolution_clock::now();
		std::vector res = simpleIterMethod(mtr, v, start, 0.0, N, 0.25);
		auto endTime = std::chrono::high_resolution_clock::now();
		double error = abs(v - mtr * res) / abs(v);
		auto dtime = duration_cast<std::chrono::microseconds>(endTime - startTime).count();
		data << dtime << "," << error << ",";

		startTime = std::chrono::high_resolution_clock::now();
		res = chebyshevSIM(mtr, v, start, 0.0, N, 1.0, 7.0);
		endTime = std::chrono::high_resolution_clock::now();
		error = abs(v - mtr * res) / abs(v);
		dtime = duration_cast<std::chrono::microseconds>(endTime - startTime).count();
		data << dtime << "," << error << ",";

		startTime = std::chrono::high_resolution_clock::now();
		res = jakobiMethod(mtr, v, start, 0.0, N);
		endTime = std::chrono::high_resolution_clock::now();
		error = abs(v - mtr * res) / abs(v);
		dtime = duration_cast<std::chrono::microseconds>(endTime - startTime).count();
		data << dtime << "," << error << ",";

		startTime = std::chrono::high_resolution_clock::now();
		res = gaussSeidelMethod(mtr, v, start, 0.0, N);
		endTime = std::chrono::high_resolution_clock::now();
		error = abs(v - mtr * res) / abs(v);
		dtime = duration_cast<std::chrono::microseconds>(endTime - startTime).count();
		data << dtime << "," << error << ",";

		startTime = std::chrono::high_resolution_clock::now();
		res = conjurateGradientMethod(mtr, v, start, 0.0, N);
		endTime = std::chrono::high_resolution_clock::now();
		error = abs(v - mtr * res) / abs(v);
		dtime = duration_cast<std::chrono::microseconds>(endTime - startTime).count();
		data << dtime << "," << error << "\n";
	}

	data.close();
}
