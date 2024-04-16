#include "csr-matrix.h"
#include <gtest/gtest.h>
#include <fstream>

TEST(csr, construction){
	std::vector<int> v = {1, 2, 0, 3, 0, 0, 4, 0, 0, 1, 0, 11};
	size_t width = 4;
	std::vector<int> values = {1, 2, 3, 4, 1, 11};
	std::vector<size_t> columns = {0, 1, 3, 2, 1, 3};
	std::vector<size_t> rows = {0, 3, 4, 6};
	csrMatrix<int> mtr = csrMatrix<int>(v, width);
	ASSERT_TRUE(mtr.validate(values, columns, rows));
}

TEST(csr, get_element){
	std::vector<int> v = {1, 2, 0, 3, 0, 0, 4, 0, 0, 1, 0, 11};
	size_t width = 4;
	csrMatrix<int> mtr = csrMatrix<int>(v, width);
	ASSERT_EQ(mtr(1, 2), 4);
	ASSERT_EQ(mtr(1, 1), 0);
	ASSERT_EQ(mtr(2, 3), 11);
}

TEST(csr, vector_multiply){
	std::vector<int> v = {1, 2, 0, 3, 0, 0, 4, 0, 0, 1, 0, 11};
	size_t width = 4;
	csrMatrix<int> mtr = csrMatrix<int>(v, width);
	std::vector<int> v1 = {1, 2, 3, 4};
	std::vector<int> res1 = {17, 12, 46};
	ASSERT_EQ(mtr * v1, res1);
	std::vector<int> v2 = {4, 3, 2, 1};
	std::vector<int> res2 = {13, 8, 14};
	ASSERT_EQ(mtr * v2, res2);
}

TEST(csr, simple_iter_method){
	std::vector<double> data = {5, -2, 0, -1, -2, 3, 0, -0.2, 0, 0, 7, 0, -1, -0.2, 0, 2};
	csrMatrix<double> mtr = csrMatrix<double>(data, 4);
	std::vector<double> v = {-4, 0, -2, 9};
	std::vector<double> start = {1, 1, 1, 1};
	std::vector<double> res = simpleIterMethod(mtr, v, start, 0.0001, 1000, 0.25);
	std::vector<double> correct = {0.37555555555555556, 0.56666666666666667, -0.28571428571428571, 4.74444444444444444};
	for(size_t i = 0; i < res.size(); i++){
		ASSERT_NEAR(res[i], correct[i], 0.0001);
	}
}

TEST(csr, chebyshev_SIM){
	std::vector<double> data = {5, -2, 0, -1, -2, 3, 0, -0.2, 0, 0, 7, 0, -1, -0.2, 0, 2};
	csrMatrix<double> mtr = csrMatrix<double>(data, 4);
	std::vector<double> v = {-4, 0, -2, 9};
	std::vector<double> start = {1, 1, 1, 1};
	std::vector<double> res = chebyshevSIM(mtr, v, start, 0.0001, 1000, 1.129, 7.0);
	std::vector<double> correct = {0.37555555555555556, 0.56666666666666667, -0.28571428571428571, 4.74444444444444444};
	for(size_t i = 0; i < res.size(); i++){
		ASSERT_NEAR(res[i], correct[i], 0.0001);
	}
}

TEST(csr, jakobi_method){
	std::vector<double> data = {5, -2, 0, -1, -2, 3, 0, -0.2, 0, 0, 7, 0, -1, -0.2, 0, 2};
	csrMatrix<double> mtr = csrMatrix<double>(data, 4);
	std::vector<double> v = {-4, 0, -2, 9};
	std::vector<double> start = {1, 1, 1, 1};
	std::vector<double> res = jakobiMethod(mtr, v, start, 0.0001, 1000);
	std::vector<double> correct = {0.37555555555555556, 0.56666666666666667, -0.28571428571428571, 4.74444444444444444};
	for(size_t i = 0; i < res.size(); i++){
		ASSERT_NEAR(res[i], correct[i], 0.0001);
	}
}

TEST(csr, gauss_seidel_method){
	std::vector<double> data = {5, -2, 0, -1, -2, 3, 0, -0.2, 0, 0, 7, 0, -1, -0.2, 0, 2};
	csrMatrix<double> mtr = csrMatrix<double>(data, 4);
	std::vector<double> v = {-4, 0, -2, 9};
	std::vector<double> start = {1, 1, 1, 1};
	std::vector<double> res = gaussSeidelMethod(mtr, v, start, 0.0001, 1000);
	std::vector<double> correct = {0.37555555555555556, 0.56666666666666667, -0.28571428571428571, 4.74444444444444444};
	for(size_t i = 0; i < res.size(); i++){
		ASSERT_NEAR(res[i], correct[i], 0.0001);
	}
}

TEST(csr, gradient_descent){
	std::vector<double> data = {5, -2, 0, -1, -2, 3, 0, -0.2, 0, 0, 7, 0, -1, -0.2, 0, 2};
	csrMatrix<double> mtr = csrMatrix<double>(data, 4);
	std::vector<double> v = {-4, 0, -2, 9};
	std::vector<double> start = {1, 1, 1, 1};
	std::vector<double> res = gradientDescent(mtr, v, start, 0.0001, 1000);
	std::vector<double> correct = {0.37555555555555556, 0.56666666666666667, -0.28571428571428571, 4.74444444444444444};
	for(size_t i = 0; i < res.size(); i++){
		ASSERT_NEAR(res[i], correct[i], 0.0001);
	}
}

TEST(csr, sym_gauss_seidel_method){
	std::vector<double> data = {5, -2, 0, -1, -2, 3, 0, -0.2, 0, 0, 7, 0, -1, -0.2, 0, 2};
	csrMatrix<double> mtr = csrMatrix<double>(data, 4);
	std::vector<double> v = {-4, 0, -2, 9};
	std::vector<double> start = {1, 1, 1, 1};
	std::vector<double> res = symGaussSeidelMethod(mtr, v, start, 0.0001, 1000);
	std::vector<double> correct = {0.37555555555555556, 0.56666666666666667, -0.28571428571428571, 4.74444444444444444};
	for(size_t i = 0; i < res.size(); i++){
		ASSERT_NEAR(res[i], correct[i], 0.0001);
	}
}

TEST(csr, conjurate_gradient_method){
	std::vector<double> data = {5, -2, 0, -1, -2, 3, 0, -0.2, 0, 0, 7, 0, -1, -0.2, 0, 2};
	csrMatrix<double> mtr = csrMatrix<double>(data, 4);
	std::vector<double> v = {-4, 0, -2, 9};
	std::vector<double> start = {1, 1, 1, 1};
	std::vector<double> res = conjurateGradientMethod(mtr, v, start, 0.0001, 1000);
	std::vector<double> correct = {0.37555555555555556, 0.56666666666666667, -0.28571428571428571, 4.74444444444444444};
	for(size_t i = 0; i < res.size(); i++){
		ASSERT_NEAR(res[i], correct[i], 0.0001);
	}
}

// TEST(csr, problem1){
// 	std::vector<int> data = {8, 9, 0, 7, 1, 6, 0, 1, 2, 8, 3, 0, 9, 0, 0, 1};
// 	csrMatrix<int> mtr(data, 4);
// 	for(size_t value : mtr.columns)
// 		std::cout << value << " ";
// 	std::cout << "\n";
// 	for(size_t value : mtr.rows)
// 		std::cout << value << " ";
// 	std::cout << "\n";
// }

// TEST(csr, problem3){
// 	std::vector<double> data = {73, 8, 5, 0, 0, 66, 8, 0, 0, 0, 80, 7, 0, 2, 0, 89};
// 	csrMatrix<double> mtr(data, 4);
// 	std::vector<double> v = {3, 5, 3, 5};
// 	std::vector<double> correct = {0.03098693134737314, 0.07179085679272901, 0.03272543145998570, 0.05456649760016339};
// 	for(double a = -1; a <= 1; a++){
// 	for(double b = -1; b <= 1; b++){
// 	for(double c = -1; c <= 1; c++){
// 	for(double d = -1; d <= 1; d++){
// 		std::vector<double> start = {a, b, c, d};
// 		for(size_t N = 1; N < 1000; N++){
// 			std::vector<double> res = simpleIterMethod(mtr, v, start , 0.0, N, 1e-3);
// 			if(1e3 * abs(res - correct) <= abs(start - correct)){
// 				for(double value : start)
// 					std::cout << value << " ";
// 				std::cout << ", " << N << "\n";
// 				break;
// 			}
// 		}
// 	}}}}	
// }

// TEST(csr, problem4){
// 	std::vector<double> data = {95, 0, 6, 0, 6, 50, 0, 0, 3, 8, 72, 0, 6, 0, 0, 70};
// 	// std::vector<double> data = {333, 0, 0, 0, 0, 333, 0, 0, 0, 0, 333, 0, 0, 0, 0, 333};
// 	csrMatrix<double> mtr(data, 4);
// 	std::vector<double> v = {1, 1, 1, 1};
// 	std::vector<double> start = {0, 0, 0, 0};

// 	std::ofstream results;
// 	results.open("../counts-problem-4.csv");
// 	results << "tau, Niter\n";

// 	for(double tau = 0.03; tau > 0.01; tau -= 0.0001){
// 	// for(double tau = 1; tau > 0.001; tau -= 0.0001){
// 		size_t iterations = simpleIterMethodCounter(mtr, v, start, 1e-12, 10000, tau);
// 		results << tau << "," << iterations << "\n";
// 	}
// }
