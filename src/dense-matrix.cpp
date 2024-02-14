#include "dense-matrix.h"

template<typename T>
denseMatrix<T>::denseMatrix(const std::vector<T> *data, std::size_t width){
	this->data = *data;
	this->width = width;
}

template<typename T>
denseMatrix<T>::denseMatrix(const std::vector<std::vector<T>> *data){
	this->width = (*data)[0].size();
	for(std::vector<T> row : (*data)){
		for(T element : row){
			this->data.push_back(element);
		}
	}
}

template<typename T>
T *denseMatrix<T>::operator()(std::size_t h, std::size_t w){
	return &this->data[h * this->width + w];
}

template<typename T>
std::vector<T> denseMatrix<T>::operator*(const std::vector<T> &v){
	std::vector<T> ret;
	for(size_t row = 0; row < this->data.size() / this->width; row++){
		T sum = 0;
		for(size_t i = 0; i < this->width; i++){
			sum += *(*this)(row, i) * v[i];
		}
		ret.push_back(sum);
	}
	return ret;
}