#include <cstddef>
#include <vector>
#include <stdint.h>

template<typename T>
struct denseMatrix{
private:
	size_t width;
	std::vector<T> data;
public:
	denseMatrix(const std::vector<T> &data, size_t width);
	denseMatrix(const std::vector<std::vector<T>> &data);
	T &operator()(size_t h, size_t w);
	std::vector<T> operator*(const std::vector<T> &v);
};

template<typename T>
denseMatrix<T>::denseMatrix(const std::vector<T> &rawdata, std::size_t w){
	this->data = rawdata;
	this->width = w;
}

template<typename T>
denseMatrix<T>::denseMatrix(const std::vector<std::vector<T>> &rawdata){
	this->width = rawdata[0].size();
	for(std::vector<T> row : rawdata){
		for(T element : row){
			this->data.push_back(element);
		}
	}
}

template<typename T>
T &denseMatrix<T>::operator()(std::size_t h, std::size_t w){
	return this->data[h * this->width + w];
}

template<typename T>
std::vector<T> denseMatrix<T>::operator*(const std::vector<T> &v){
	std::vector<T> ret;
	for(size_t row = 0; row < this->data.size() / this->width; row++){
		T sum = 0;
		for(size_t i = 0; i < this->width; i++){
			sum += (*this)(row, i) * v[i];
		}
		ret.push_back(sum);
	}
	return ret;
}