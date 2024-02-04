#include <ALOP/tri-diag-matrix.h>
#include <vector>
#include <iostream>
#include <gtest/gtest.h>

TEST(Thomas_Method, value_test){
	triDiagMatrix A{
		{2.0, 5.0, 8.0, 2.0},
		{11.0, 14.0, 17.0, 11.0, 14.0},
		{3.0, 6.0, 9.0, 3.0}
	};
	std::vector<double> f = {1.0, 2.0, 3.0, 4.0, 5.0};
	std::vector<double> result = thomasMethod(A, f);
	std::vector<double> correct = {0.05147295002982611, 0.14459918322397095, -0.021222410865874258, 0.29308722984444535, 0.31527325287936492};
	ASSERT_EQ(result, correct);
}

int main(){
	testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}