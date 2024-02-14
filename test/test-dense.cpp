#include "dense-matrix.h"
#include <gtest/gtest.h>
#include <vector>

TEST(denseMatrix, access){
	std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	auto mtr = denseMatrix<int>(&data, 3);
	ASSERT_EQ(*mtr(1, 2), 6);
	*mtr(1, 2) = 7;
	ASSERT_EQ(*mtr(1, 2), 7);
}

TEST(denseMatrix, vector_multiply){
	std::vector<int> v = {1, 2, 0, 3, 0, 0, 4, 0, 0, 1, 0, 11};
	size_t width = 4;
	denseMatrix<int> mtr = denseMatrix<int>(&v, width);
	std::vector<int> v1 = {1, 2, 3, 4};
	std::vector<int> res1 = {17, 12, 46};
	ASSERT_EQ(mtr * v1, res1);
	std::vector<int> v2 = {4, 3, 2, 1};
	std::vector<int> res2 = {13, 8, 14};
	ASSERT_EQ(mtr * v2, res2);
}
