#include "dense-matrix.h"
#include <gtest/gtest.h>
#include <vector>
#include <cstdlib>
#include <chrono>

// TEST(csr, dense){
// 	std::srand(4672313);
// 	std::vector<int> data;
// 	std::vector<int> v;
// 	for(size_t size = 1000; size < 5000; size+= 100){
// 		for(size_t i = (size - 100) * (size - 100); i <= size * size; i++){
// 			data.push_back(std::rand());
// 		}
// 		denseMatrix<int> mtr = denseMatrix<int>(&data, size);

// 		for(size_t i = (size - 100); i <= size; i++){
// 			v.push_back(std::rand());
// 		}

// 		auto startTime = std::chrono::high_resolution_clock::now();
// 		std::vector<int> result = mtr * v;
// 		auto endTime = std::chrono::high_resolution_clock::now();
// 		auto dtime = duration_cast<std::chrono::milliseconds>(endTime - startTime);
// 		// std::cout << size << " elements, elapsed " << dtime << std::endl;
// 		std::cout << size << "," << dtime.count() << std::endl; //output into csv file
// 	}
// }

TEST(csr, sparse){
	std::srand(4672313);
	std::vector<int> data;
	std::vector<int> v;
	for(size_t size = 1000; size < 5000; size+= 100){
		for(size_t i = (size - 100) * (size - 100); i <= size * size; i++){
			int n = std::rand();
			data.push_back(n < RAND_MAX / 20 ? n : 0);
		}
		denseMatrix<int> mtr = denseMatrix<int>(data, size);

		for(size_t i = (size - 100); i <= size; i++){
			v.push_back(std::rand());
		}

		auto startTime = std::chrono::high_resolution_clock::now();
		std::vector<int> result = mtr * v;
		auto endTime = std::chrono::high_resolution_clock::now();
		auto dtime = duration_cast<std::chrono::milliseconds>(endTime - startTime);
		// std::cout << size << " elements, elapsed " << dtime << std::endl;
		std::cout << size << "," << dtime.count() << std::endl; //output into csv file
	}
}
