#include "dense-matrix.h"
#include <gtest/gtest.h>
#include <vector>
#include "vector-operations.h"

TEST(denseMatrix, access){
	std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	auto mtr = denseMatrix<int>(data, 3);
	ASSERT_EQ(mtr(1, 2), 6);
	mtr(1, 2) = 7;
	ASSERT_EQ(mtr(1, 2), 7);
}

TEST(denseMatrix, vector_multiply){
	std::vector<int> v = {1, 2, 0, 3, 0, 0, 4, 0, 0, 1, 0, 11};
	size_t width = 4;
	denseMatrix<int> mtr = denseMatrix<int>(v, width);
	std::vector<int> v1 = {1, 2, 3, 4};
	std::vector<int> res1 = {17, 12, 46};
	ASSERT_EQ(mtr * v1, res1);
	std::vector<int> v2 = {4, 3, 2, 1};
	std::vector<int> res2 = {13, 8, 14};
	ASSERT_EQ(mtr * v2, res2);
}

TEST(denseMatrix, vector_constructor){
	std::vector<int> v1 = {1, 2, 3};
	std::vector<int> v2 = {4, 5, 6, 7};
	denseMatrix<int> res = denseMatrix<int>(v1, v2);
	denseMatrix<int> mtr = denseMatrix<int>({4, 5, 6, 7, 8, 10, 12, 14, 12, 15, 18, 21}, 4);
	ASSERT_EQ(res, mtr);
}

TEST(denseMatrix, number_multiply){
	std::vector<int> v = {1, 2, 0, 3, 0, 0, 4, 0, 0, 1, 0, 11};
	size_t width = 4;
	denseMatrix<int> mtr = denseMatrix<int>(v, width);
	denseMatrix<int> mtr2 = denseMatrix<int>(2 * v, width);
	ASSERT_EQ(mtr * 2, mtr2);	
}

TEST(denseMatrix, matrix_multiply){
	denseMatrix<int> mtr1 = denseMatrix<int>({4, 5, 6, 7, 8, 10, 12, 14, 12, 15, 18, 21}, 4);
	denseMatrix<int> mtr2 = denseMatrix<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}, 3);
	denseMatrix<int> prod = mtr1 * mtr2;
	ASSERT_EQ(prod, denseMatrix<int>({136, 158, 180, 272, 316, 360, 408, 474, 540}, 3));
}

TEST(denseMatrix, transpose){
	denseMatrix<int> mtr = denseMatrix<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}, 3);
	denseMatrix<int> res = denseMatrix<int>({1, 4, 7, 10, 2, 5, 8, 11, 3, 6, 9, 12}, 4);
	ASSERT_EQ(transpose(mtr), res);
}

TEST(denseMatrix, QR_decomp){
	denseMatrix<double> mtr = denseMatrix<double>({1, 3, 5, 1, 3, 1, 2, -1, 7}, 3);
	std::pair<denseMatrix<double>, denseMatrix<double>> QR = QRdecomp(mtr);
	denseMatrix<double> res = QR.first * QR.second;
	std::vector<double> v1 = {-0.408248290463863, -0.577350269189626, 0.707106781186548, -0.408248290463863, -0.577350269189626, -0.707106781186548, -0.816496580927726, 0.577350269189626, 0};
	std::vector<double> v2 = {-2.449489742783178, -1.632993161855452, -8.16496580927726, 0, -4.04145188432738, 0.577350269189626, 0, 0, 2.82842712474619};
	for(size_t i = 0; i < v1.size(); i++){
		ASSERT_NEAR(QR.first.data()[i], v1[i], abs(0.001 * QR.first.data()[0]));
		ASSERT_NEAR(QR.second.data()[i], v2[i], abs(0.001 * QR.second.data()[0]));
		ASSERT_NEAR(res.data()[i], mtr.data()[i], abs(0.001 * mtr.data()[0]));
	}
}

TEST(denseMatrix, QR_solve){
	denseMatrix<double> mtr = denseMatrix<double>({9, 2, 10, 2, 10, 7, 8, 8, 5}, 3);
	std::vector<double> f = {0, 10, 1};
	std::vector<double> res = QRsolve(mtr, f);
	std::vector<double> correct = {-1.01993355481727575, 0.65282392026578073, 0.78737541528239203};
	for(size_t i = 0; i < res.size(); i++){
		ASSERT_NEAR(res[i], correct[i], abs(0.001 * res[i]));
	}	
}
