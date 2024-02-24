#include <cstddef>
#include <vector>
#include <stdint.h>
#include "vector-operations.h"

template<typename T>
struct denseMatrix{
private:
	size_t __width;
	std::vector<T> __data;
public:
	denseMatrix(const std::vector<T> &data, size_t width);
	denseMatrix(const std::vector<std::vector<T>> &data);
	denseMatrix(const std::vector<T> &v1, const std::vector<T> &v2);
	denseMatrix(size_t height, size_t width);
	T &operator()(size_t h, size_t w);
	const T &operator()(size_t h, size_t w) const;
	size_t height() const;
	size_t width() const;
	const std::vector<T> &data() const;
	const std::vector<T> column(size_t w) const;
	const std::vector<T> row(size_t h) const;
	std::vector<T> operator*(const std::vector<T> &v) const;
	const denseMatrix<T> operator*(T x) const;
	const denseMatrix<T> operator/(T x) const;
};

template<typename T>
denseMatrix<T>::denseMatrix(const std::vector<T> &rawdata, std::size_t w){
	this->__data = rawdata;
	this->__width = w;
}

template<typename T>
denseMatrix<T>::denseMatrix(const std::vector<std::vector<T>> &rawdata){
	this->__width = rawdata[0].size();
	for(std::vector<T> row : rawdata){
		for(T element : row){
			this->__data.push_back(element);
		}
	}
}

template<typename T>
denseMatrix<T>::denseMatrix(size_t height, size_t width){
	this->__width = width;
	this->__data = std::vector<T>(height * width);
}

template<typename T>
size_t denseMatrix<T>::height() const{
	return this->__data.size() / this->__width;
}

template<typename T>
size_t denseMatrix<T>::width() const{
	return this->__width;
}

template<typename T>
const std::vector<T> &denseMatrix<T>::data() const{
	return this->__data;
}

template<typename T>
T &denseMatrix<T>::operator()(std::size_t h, std::size_t w){
	return this->__data[h * this->__width + w];
}

template<typename T>
const T &denseMatrix<T>::operator()(std::size_t h, std::size_t w) const{
	return this->__data[h * this->__width + w];
}

template<typename T>
denseMatrix<T> transpose(const denseMatrix<T> &mtr){
	denseMatrix<T> ret = denseMatrix<T>(mtr.width(), mtr.height());
	for(size_t h = 0; h < mtr.height(); h++){
		for(size_t w = 0; w < mtr.width(); w++){
			ret(w, h) = mtr(h, w);
		}
	}
	return ret;
}

template<typename T>
bool operator==(const denseMatrix<T> &m1, const denseMatrix<T> &m2){
	for(size_t h = 0; h < m1.height(); h++){
		for(size_t w = 0; w < m1.width(); w++){
			if(m1(h, w) != m2(h, w))
				return false;
		}
	}
	return true;
}

template<typename T>
std::vector<T> denseMatrix<T>::operator*(const std::vector<T> &v) const{
	std::vector<T> ret;
	for(size_t row = 0; row < this->__data.size() / this->__width; row++){
		T sum = 0;
		for(size_t i = 0; i < this->__width; i++){
			sum += (*this)(row, i) * v[i];
		}
		ret.push_back(sum);
	}
	return ret;
}

template<typename T>
const denseMatrix<T> denseMatrix<T>::operator*(T x) const{
	denseMatrix<T> ret = denseMatrix<T>(this->__data.size() / this->__width, this->__width);
	for(size_t h = 0; h < this->__data.size() / this->__width; h++)
		for(size_t w = 0; w < this->__width; w++)
			ret(h, w) = (*this)(h, w) * x;
	return ret;
}

template<typename T>
const denseMatrix<T> denseMatrix<T>::operator/(T x) const{
	return (*this) * (1 / x);
}

template<typename T>
denseMatrix<T> operator+(const denseMatrix<T> &m1, const denseMatrix<T> &m2){
	denseMatrix<T> ret = denseMatrix<T>(m1.height(), m1.width());
	for(size_t h = 0; h < m1.height(); h++)
		for(size_t w = 0; w < m1.width(); w++)
			ret(h, w) = m1(h, w) + m2(h, w);
	return ret;
}

template<typename T>
denseMatrix<T> operator-(const denseMatrix<T> &m1, const denseMatrix<T> &m2){
	return m1 + m2 * T(-1);	
}

template<typename T>
denseMatrix<T> operator*(const denseMatrix<T> &m1, const denseMatrix<T> &m2){
	denseMatrix<T> ret = denseMatrix<T>(m1.height(), m2.width());
	for(size_t h = 0; h < m1.height(); h++){
		for(size_t w = 0; w < m2.width(); w++){
			ret(h, w) = dot(m1.row(h), m2.column(w));
		}
	}
	return ret;
}

template<typename T>
const std::vector<T> denseMatrix<T>::column(size_t w) const{
	std::vector<T> ret = std::vector<T>(this->height());
	for(size_t h = 0; h < this->height(); h++){
		ret[h] = (*this)(h, w);
	}
	return ret;
}

template<typename T>
const std::vector<T> denseMatrix<T>::row(size_t h) const{
	std::vector<T> ret = std::vector<T>(this->width());
	for(size_t w = 0; w < this->width(); w++){
		ret[w] = (*this)(h, w);
	}
	return ret;
}

template<typename T>
denseMatrix<T>::denseMatrix(const std::vector<T> &v1, const std::vector<T> &v2){
	this->__data = std::vector<T>(v1.size() * v2.size());
	this->__width = v2.size();
	for(size_t h = 0; h < v1.size(); h ++)
		for(size_t w = 0; w < v2.size(); w++)
			(*this)(h, w) = v1[h] * v2[w];
}

template<typename T>
denseMatrix<T> __theta(const std::vector<T> &nu, const denseMatrix<T> &mtr){
	denseMatrix<T> ret = denseMatrix<T>(mtr.height(), mtr.width());
	for(size_t w = 0; w < mtr.width(); w++){
		std::vector<T> x = mtr.column(w);
		std::vector<T> theta = x - 2 * dot(x, nu) / dot(nu, nu) * nu;
		for(size_t h = 0; h < mtr.height(); h++){
			ret(h, w) = theta[h];
		}
	}
	return ret;
}

template<typename T>
std::pair<denseMatrix<T>, denseMatrix<T>> QRdecomp(const denseMatrix<T> &mtr){
	denseMatrix<T> I = denseMatrix<T>(mtr.height(), mtr.width());
	for(size_t w = 0; w < mtr.width(); w++){
		for(size_t h = 0; h < mtr.width(); h++){
			I(h, w) = 0;
		}
		I(w, w) = 1;
	}	

	denseMatrix<T> Q = I;
	denseMatrix<T> R = mtr;
	for(size_t w = 0; w < R.width(); w++){
		std::vector<T> nu = std::vector<T>(R.width());
		for(size_t h = 0; h < R.width(); h++){
			if(h >= w){
				nu[h] = R(h, w);
			}else{
				nu[h] = 0;
			}
		}
		nu[w] += sign(nu[w]) * abs(nu);
		Q = transpose(__theta(nu, transpose(Q)));
		R = __theta(nu, R);
	}
	return std::pair<denseMatrix<T>, denseMatrix<T>>(Q, R);
}

template<typename T>
std::vector<T> QRsolve(const denseMatrix<T> &mtr, const std::vector<T> &f){
	std::pair<denseMatrix<T>, denseMatrix<T>> QR = QRdecomp(mtr);
	std::vector<T> f2 = transpose(QR.first) * f;
	for(size_t h = f2.size() - 1; h > 0; h--){
		for(size_t w = h + 1; w < QR.second.width(); w++){
			f2[h] = f2[h] - f2[w] / QR.second(w, w) * QR.second(h, w);
		}
	}
	for(size_t w = 1; w < QR.second.width(); w++){
		f2[0] = f2[0] - f2[w] / QR.second(w, w) * QR.second(0, w);
	}
	for(size_t h = 0; h < f2.size(); h++){
		f2[h] = f2[h] / QR.second(h, h);
	}
	return f2;
}