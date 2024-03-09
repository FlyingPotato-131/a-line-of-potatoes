#include "csr-matrix.h"
#include <gtest/gtest.h>

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
