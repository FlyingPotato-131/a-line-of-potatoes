#pragma once
#include <vector>
#include <stdint.h>
#include <cmath>

template<typename T>
std::vector<T> operator+(const std::vector<T> &a, const std::vector<T> &b){
	std::vector<T> ret;
	for(size_t i = 0; i < a.size(); i++){
		ret.push_back(a[i] + b[i]);
	}
	return ret;
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
std::vector<T> operator*(const std::vector<T> &v, T n){
	std::vector<T> ret;
	for(size_t i = 0; i < v.size(); i++){
		ret.push_back(v[i] * n);
	}
	return ret;
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
T dot(const std::vector<T> &a, const std::vector<T> &b){
	T ret = 0;
	for(size_t i = 0; i < a.size(); i++){
		ret += a[i] * b[i];
	}
	return ret;
}

template<typename T>
T abs(const std::vector<T> &v){
	return sqrt(dot(v, v));
}

template<typename T>
T sign(T n){
	return n < 0 ? -1 : n > 0 ? 1 : 0;
}
