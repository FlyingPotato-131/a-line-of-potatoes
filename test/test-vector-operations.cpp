#include "vector-operations.h"
#include <vector>
#include <gtest/gtest.h>

TEST(vops, add){
	std::vector<int> v1 = {1, 2, 3};
	std::vector<int> v2 = {4, 5, 6};
	std::vector<int> sum = {5, 7, 9};
	ASSERT_EQ(v1 + v2, sum);
}

TEST(vops, subtract){
	std::vector<int> v1 = {1, 2, 3};
	std::vector<int> v2 = {4, 5, 6};
	std::vector<int> sum = {-3, -3, -3};
	ASSERT_EQ(v1 - v2, sum);
}

TEST(vops, multiply){
	std::vector<int> v1 = {1, 2, 3};
	int a = 5;
	std::vector<int> product = {5, 10, 15};
	ASSERT_EQ(v1 * a, product);
	ASSERT_EQ(a * v1, product);
}

TEST(vops, divide){
	std::vector<int> v1 = {2, 4, 6};
	int a = 2;
	std::vector<int> quotient = {1, 2, 3};
	ASSERT_EQ(v1 / a, quotient);
}

TEST(vops, mul){
	std::vector<int> v1 = {1, 2, 3};
	std::vector<int> v2 = {4, 5, 6};
	std::vector<int> product = {4, 10, 18};
	ASSERT_EQ(v1 * v2, product);	
}

TEST(vops, dot){
	std::vector<int> v1 = {1, 2, 3};
	std::vector<int> v2 = {4, 5, 6};
	int product = 32;
	ASSERT_EQ(dot(v1, v2), product);	
}