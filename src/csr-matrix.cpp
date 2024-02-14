#include "csr-matrix.h"
#include <iostream>

template<typename T>
csrMatrix<T>::csrMatrix(const std::vector<T> *data, size_t width){
	this->rows = {0};
	for(size_t i = 0; i < data->size(); i++){
		if((*data)[i] != 0){
			this->values.push_back((*data)[i]);
			this->columns.push_back(i % width);
		}
		if(i % width == width - 1){
			size_t count = 0;
			for(size_t p = 0; p <= i; p++){
				if((*data)[p] != 0){
					count ++;
				}
			}
			this->rows.push_back(count);
		}
	}
}

template<typename T>
bool csrMatrix<T>::validate(const std::vector<T> *values, const std::vector<size_t> *columns, const std::vector<size_t> *rows){
	return this->values == *values && this->columns == *columns && this->rows == *rows;
}

template<typename T>
T csrMatrix<T>::operator()(size_t h, size_t w){
	for(size_t i = this->rows[h]; i < this->rows[h+1]; i++){
		if(this->columns[i] == w){
			return this->values[i];
		}
	}
	return 0;
}

template<typename T>
std::vector<T> csrMatrix<T>::operator*(const std::vector<T> &v) const{
	std::vector<T> ret;
	for(size_t row = 0; row < this->rows.size() - 1; row++){
		T sum = 0;
		for(size_t i = this->rows[row]; i < this->rows[row + 1]; i++){
			sum += this->values[i] * v[this->columns[i]];
		}
		ret.push_back(sum);
	}
	return ret;
}