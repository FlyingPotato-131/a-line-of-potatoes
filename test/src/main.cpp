#include <ALOP/tri-diag-matrix.h>
#include <vector>
#include <iostream>
#include <gtest/gtest.h>

TEST(Thomas_Method, value_eq_0){
	triDiagMatrix A{
		{2.0, 5.0, 8.0, 2.0},
		{11.0, 14.0, 17.0, 11.0, 14.0},
		{3.0, 6.0, 9.0, 3.0}
	};
	std::vector<double> f = {1.0, 2.0, 3.0, 4.0, 5.0};
	std::vector<double> result = thomasMethod(A, f);
	std::vector<double> correct = {0.05147295002982609, 0.14459918322397100, -0.02122241086587436, 0.29308722984444546, 0.31527325287936493};
	for(size_t i = 0; i < result.size(); i++){
		ASSERT_NEAR(result[i], correct[i], 0.001 * abs(result[i]));
	}
}

TEST(Thomas_Method, value_eq_1){
	triDiagMatrix A{
		{9, 0, 8, 5, 7, 9, 7, 4, 2, 4, 7, 5, 4},
		{15, 18, 19, 16, 17, 20, 14, 12, 12, 14, 14, 20, 11, 14},
		{7, 0, 2, 5, 6, 9, 3, 4, 1, 6, 7, 9, 1}
	};
	std::vector<double> f = {3, 2, 3, 0, 3, 7, 8, 3, 4, 3, 9, 10, 5, 8};
	std::vector<double> result = thomasMethod(A, f);
	std::vector<double> correct = {0.19323671497584541, 0.01449275362318841, 0.17465193371758323, -0.15919337031704065, 0.22997569106639693, -0.01893664942392408, 0.64098923900152257, -0.26780650040199976, 0.43168833295333478, -0.10903399383201836, 0.61051654129026458, 0.12698634246633848, 0.35407304018237538, 0.47026484566217846};
	for(size_t i = 0; i < result.size(); i++){
		ASSERT_NEAR(result[i], correct[i], 0.001 * abs(result[i]));
	}
}

TEST(Thomas_Method, throw_0){
	triDiagMatrix A{
		{9, 0, 8, 5, 7, 9, 7, 4, 2, 4, 7, 5, 4},
		{15, 18, 9, 16, 17, 20, 14, 12, 12, 14, 14, 20, 11, 14},
		{7, 0, 2, 5, 6, 9, 3, 4, 1, 6, 7, 9, 1}
	};
	std::vector<double> f = {3, 2, 3, 0, 3, 7, 8, 3, 4, 3, 9, 10, 5, 8};
	EXPECT_THROW({thomasMethod(A, f);}, std::invalid_argument);
}

int main(){
	testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}