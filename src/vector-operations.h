#include <vector>
#include <stdint.h>

template<typename T>
std::vector<T> operator+(const std::vector<T> &a, const std::vector<T> &b){
	std::vector<T> ret;
	for(size_t i = 0; i < a.size(); i++){
		ret.push_back(a[i] + b[i]);
	}
	return ret;
}

template<typename T>
void operator+=(std::vector<T> &a, const std::vector<T> &b){
	for(size_t i = 0; i < a.size(); i++){
		a[i] += b[i];
	}
}

template<typename T>
std::vector<T> operator-(const std::vector<T> &a, const std::vector<T> &b){
	std::vector<T> ret;
	for(size_t i = 0; i < a.size(); i++){
		ret.push_back(a[i] - b[i]);
	}
	return ret;
}

template<typename T>
void operator-=(std::vector<T> &a, const std::vector<T> &b){
	for(size_t i = 0; i < a.size(); i++){
		a[i] -= b[i];
	}
}

template<typename T>
std::vector<T> operator*(const std::vector<T> &v, T n){
	std::vector<T> ret;
	for(size_t i = 0; i < v.size(); i++){
		ret.push_back(v[i] * n);
	}
	return ret;
}

template<typename T>
void operator*=(std::vector<T> &v, T n){
	for(size_t i = 0; i < v.size(); i++){
		v[i] *= n;
	}
}

template<typename T>
std::vector<T> operator*(T n, const std::vector<T> &v){
	return v * n;
}

template<typename T>
std::vector<T> operator/(const std::vector<T> &v, T n){
	std::vector<T> ret;
	for(size_t i = 0; i < v.size(); i++){
		ret.push_back(v[i] / n);
	}
	return ret;
}

template<typename T>
void operator/=(std::vector<T> &v, T n){
	for(size_t i = 0; i < v.size(); i++){
		v[i] /= n;
	}
}

template<typename T>
T dot(const std::vector<T> &a, const std::vector<T> &b){
	T ret = 0;
	for(size_t i = 0; i < a.size(); i++){
		ret += a[i] * b[i];
	}
	return ret;
}
