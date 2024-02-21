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
