#include <cstddef>
#include <vector>
#include <stdint.h>
#include <vector-operations.h>
#include <functional>
#include <math.h>
#include <iostream>
#include <algorithm>
#include "dense-matrix.h"

template<typename T>
struct csrMatrix{
public:
	std::vector<T> values;
	std::vector<size_t> columns;
	std::vector<size_t> rows;
public:
	csrMatrix();
	csrMatrix(const std::vector<T> &data, std::size_t width);
	csrMatrix(const std::vector<T> &values, const std::vector<size_t> &columns, const std::vector<size_t> &rows);
	bool validate(const std::vector<T> &values, const std::vector<size_t> &columns, const std::vector<size_t> &rows) const;
	T operator()(size_t h, size_t w) const;
	std::vector<T> operator*(const std::vector<T> &v) const;
	std::vector<T> mulCondition(const std::vector<T> &v, const std::function<bool(size_t, size_t)> condition) const; //multiply matrix by vector but values at positions h, w such that condition(h, w) == false are zeroed
	T mulRow(const std::vector<T> &v, size_t row, const std::function<bool(size_t, size_t)> condition = nullptr) const; //multiply row by vector
	// csrMatrix transpose();
};

template<typename T>
csrMatrix<T>::csrMatrix() : values(), columns(), rows(){}

template<typename T>
csrMatrix<T>::csrMatrix(const std::vector<T> &data, size_t width) : rows(data.size() / width + 1){
	size_t len = 0;
	for(T value : data){
		if(value != 0){
			len++;
		}
	}
	this->values.reserve(len);
	this->columns.reserve(len);
	this->rows[0] = 0;
	size_t count = 0;
	for(size_t i = 0; i < data.size(); i++){
		if(data[i] != 0){
			this->values.push_back(data[i]);
			this->columns.push_back(i % width);
			count++;
		}
		if(i % width == width - 1){
			this->rows[i / width + 1] = count;
		}
	}
}

template<typename T>
csrMatrix<T>::csrMatrix(const std::vector<T> &_values, const std::vector<size_t> &_columns, const std::vector<size_t> &_rows) : values(_values), columns(_columns), rows(_rows){}

template<typename T>
bool csrMatrix<T>::validate(const std::vector<T> &vals, const std::vector<size_t> &cols, const std::vector<size_t> &rws) const{
	return this->values == vals && this->columns == cols && this->rows == rws;
}

template<typename T>
T csrMatrix<T>::operator()(size_t h, size_t w) const{
	for(size_t i = this->rows[h]; i < this->rows[h+1]; i++){
		if(this->columns[i] == w){
			return this->values[i];
		}
	}
	return 0;
}

template<typename T>
std::vector<T> csrMatrix<T>::operator*(const std::vector<T> &v) const{
	std::vector<T> ret = std::vector<T>(this->rows.size() - 1);
	for(size_t row = 0; row < this->rows.size() - 1; row++){
		T sum = 0;
		for(size_t i = this->rows[row]; i < this->rows[row + 1]; i++){
			sum += this->values[i] * v[this->columns[i]];
		}
		ret[row] = sum;
	}
	return ret;
}

template<typename T>
std::vector<T> csrMatrix<T>::mulCondition(const std::vector<T> &v, const std::function<bool(size_t, size_t)> condition) const{
	std::vector<T> ret = std::vector<T>(this->rows.size() - 1);
	for(size_t row = 0; row < this->rows.size() - 1; row++){
		T sum = 0;
		for(size_t i = this->rows[row]; i < this->rows[row + 1]; i++){
			if(condition(row, columns[i])){
				sum += this->values[i] * v[this->columns[i]];
			}
		}
		ret[row] = sum;
	}
	return ret;
}

template<typename T>
T csrMatrix<T>::mulRow(const std::vector<T> &v, size_t row, const std::function<bool(size_t, size_t)> condition) const{
	T sum = 0;
	for(size_t i = this->rows[row]; i < this->rows[row + 1]; i++){
		if(condition == nullptr || condition(row, columns[i])){
			sum += this->values[i] * v[this->columns[i]];
		}
	}
	return sum;
}

// template<typename T>
// csrMatrix<T> csrMatrix<T>::transpose(){
// 	std::vector<T> retvals(this->values.size());
// 	std::vector<size_t> retcols(this->rows.size(), 0);
// 	std::vector<size_t> retrows(*std::max_element(this->columns.begin(), this->columns.end()) + 1, 0);

// 	for(size_t i = 0; i < this->values.size(); i++){
// 		retrows[this->columns[i] + 1]++;
// 	}

// 	size_t s = 0;
// 	for(size_t i = 2; i <= retrows.size() - 1; i++){
// 		size_t tmp = retrows[i];
// 		retrows[i] = s;
// 		s += tmp;
// 	}

// 	for(size_t h = 0; h < this->rows.size(); h++){
// 		for(size_t w = this->rows[h]; w < this->rows[h + 1]; w++){
// 			size_t row = this->columns[w];
// 			size_t col = retrows[row + 1];
// 			retvals[col] = this->values[w];
// 			retcols[col] = h;
// 			retrows[row + 1]++;
// 		}
// 	}

// 	// for(size_t h = 0; h < this->rows.size() - 1; h++){
// 	// 	for(size_t w = retrows[h]; w < retrows[h + 1]; w++){
// 	// 		const size_t i = retrows[this->columns[w] + 1];
// 	// 		retrows[this->columns[w]]++;
// 	// 		retvals[i] = this->values[w];
// 	// 		retcols[i] = h;
// 	// 	}	
// 	// }
// 	// retrows.pop_back();
// 	return csrMatrix<T>(retvals, retcols, retrows);
// }

template<typename T>
std::vector<T> simpleIterMethod(const csrMatrix<T> &mtr, const std::vector<T> &v, const std::vector<T> &start, const T tolerance, const size_t nmax, const T tau){
	std::vector<T> current = start;
	for(size_t n = 0; n < nmax; n++){
		current = current - tau * (mtr * current - v);

		bool done = 1;
		for(T error : mtr * current - v){
			if(!(std::abs(error) <= tolerance)){
				done = 0;
				break;
			}
		}
		if(done){
			break;
		}
	}
	return current;
}

template<typename T>
size_t simpleIterMethodCounter(const csrMatrix<T> &mtr, const std::vector<T> &v, const std::vector<T> &start, const T tolerance, const size_t Nmax, const T tau){
	size_t count = 0;
	std::vector<T> current = start;
	for(size_t n = 0; n < Nmax; n++){
		current = current - tau * (mtr * current - v);
		count++;

		bool done = 1;
		for(T error : mtr * current - v){
			if(!(std::abs(error) <= tolerance)){
				done = 0;
				break;
			}
		}
		if(done){
			break;
		}
	}
	return count;
}

template<typename T>
std::vector<T> chebyshevSIM(const csrMatrix<T> &mtr, const std::vector<T> &v, const std::vector<T> &start, const T tolerance, const size_t Nmax, const T eigenMin, const T eigenMax){
	std::vector<size_t> indices(size_t(pow(2, size_t(ceil(log2(Nmax))))));
	indices[0] = 0;
	indices[indices.size() / 2] = 1;
	for(size_t r = 2; r <= size_t(ceil(log2(Nmax))); r++){
		for(size_t i = 1; i < size_t(pow(2, r)); i+= 2){
			indices[size_t(double(i) * (double)indices.size() / pow(2, r))] = size_t(pow(2, r)) - 1 - indices[size_t(double(i - 1) * (double)indices.size() / pow(2, r))];
		}
	}

	std::vector<T> current = start;
	for(size_t n = 0; n < Nmax; n++){
		const T tau = 1 / ((eigenMax + eigenMin) / 2 + (eigenMax - eigenMin) / 2 * cos(M_PI * double(2 * indices[n] + 1) / 2 / double(Nmax)));
		current = current - tau * (mtr * current - v);

		bool done = 1;
		for(T error : mtr * current - v){
			if(!(std::abs(error) <= tolerance)){
				done = 0;
				break;
			}
		}
		if(done){
			break;
		}
	}
	return current;
}

template<typename T>
std::vector<T> jakobiMethod(const csrMatrix<T> &mtr, const std::vector<T> &v, const std::vector<T> &start, const T tolerance, const size_t Nmax){
	std::vector<T> current = start;
	for(size_t n = 0; n < Nmax; n++){
		std::vector<T> D = std::vector<T>(start.size());
		for(size_t i = 0; i < start.size(); i++)
			D[i] = 1 / mtr(i, i);
		current = D * (v - mtr.mulCondition(current, [](size_t h, size_t w) -> bool {return h != w;}));

		bool done = 1;
		for(T error : mtr * current - v){
			if(!(std::abs(error) <= tolerance)){
				done = 0;
				break;
			}
		}
		if(done){
			break;
		}
	}
	return current;
}

template<typename T>
std::vector<T> gaussSeidelMethod(const csrMatrix<T> &mtr, const	std::vector<T> &v, const std::vector<T> &start, const T tolerance, const size_t Nmax){
	std::vector<T> next = std::vector<T>(start.size());
	std::vector<T> current = start;
	for(size_t n = 0; n < Nmax; n++){
		for(size_t h = 0; h < start.size(); h++){
			T Dh = 1 / mtr(h, h);
			T tmp = mtr.mulRow(current, h, [](size_t tmph, size_t tmpw) -> bool {return tmph != tmpw;});
			current[h] = Dh * (v[h] - tmp);
		}

		bool done = 1;
		for(T error : mtr * current - v){
			if(!(std::abs(error) <= tolerance)){
				done = 0;
				break;
			}
		}
		if(done){
			break;
		}
	
	}	
	return current;
}

template<typename T>
std::vector<T> gradientDescent(const csrMatrix<T> &mtr, const std::vector<T> &v, const std::vector<T> &start, const T tolerance, const size_t nmax){
	std::vector<T> current = start;
	for(size_t n = 0; n < nmax; n++){
		const std::vector<T> discrepancy = mtr * current - v;
		const T tau = dot(discrepancy, discrepancy) / dot(discrepancy, mtr * discrepancy);
		current = current - tau * (mtr * current - v);

		bool done = 1;
		for(T error : mtr * current - v){
			if(!(std::abs(error) <= tolerance)){
				done = 0;
				break;
			}
		}
		if(done){
			break;
		}
	}
	return current;
}

template<typename T>
std::vector<T> symGaussSeidelMethod(const csrMatrix<T> &mtr, const	std::vector<T> &v, const std::vector<T> &start, const T tolerance, const size_t Nmax){
	std::vector<T> next = std::vector<T>(start.size());
	std::vector<T> current = start;
	bool reverse = false;
	for(size_t n = 0; n < Nmax; n++){
		for(size_t h = 0; h < start.size(); h++){
			T Dh = 1 / mtr(!reverse ? h : start.size() - 1 - h, !reverse ? h : start.size() - 1 - h);
			T tmp = mtr.mulRow(current, !reverse ? h : start.size() - 1 - h, [](size_t tmph, size_t tmpw) -> bool {return tmph != tmpw;});
			current[!reverse ? h : start.size() - 1 - h] = Dh * (v[!reverse ? h : start.size() - 1 - h] - tmp);
		}
		reverse = !reverse;

		bool done = 1;
		for(T error : mtr * current - v){
			if(!(std::abs(error) <= tolerance)){
				done = 0;
				break;
			}
		}
		if(done){
			break;
		}
	
	}	
	return current;
}

template<typename T>
std::vector<T> conjurateGradientMethod(const csrMatrix<T> &mtr, const std::vector<T> &v, const std::vector<T> &start, const T tolerance, const size_t Nmax){
	std::vector<T> current = start;
	std::vector<T> discrepancy = mtr * current - v;
	std::vector<T> orth = discrepancy;
	for(size_t n = 0; n < Nmax; n++){
		T alpha = dot(orth, discrepancy) / dot(orth, mtr * orth);
		current = current - alpha * orth;
		std::vector <T> discrepancy1 = mtr * current - v;
		if(dot(orth, orth) == 0)
			return current;
		T beta = dot(discrepancy1, discrepancy1) / dot(orth, discrepancy);
		discrepancy = discrepancy1;
		orth = discrepancy + beta * orth;

		bool done = 1;
		for(T error : mtr * current - v){
			if(!(std::abs(error) <= tolerance)){
				done = 0;
				break;
			}
		}
		if(done){
			break;
		}
	}
	return current;
}

template<typename T>
std::pair<denseMatrix<T>, denseMatrix<T>> krylovONB(const csrMatrix<T> &mtr, const std::vector<T> &v, const std::vector<T> &start){
	denseMatrix<T> onb(mtr.rows.size() - 1, mtr.rows.size() - 1);
	denseMatrix<T> h(mtr.rows.size(), mtr.rows.size() - 1);
	std::vector<T> r0 = mtr * start - v;
	std::vector<T> v0 = r0 / abs(r0);

	for(size_t i = 0; i < v0.size(); i++){
		onb(i, 0) = v0[i];
	}

	for(size_t j = 0; j < mtr.rows.size() - 1; j++){
		std::vector<T> t = mtr * onb.column(j);
		for(size_t k = 0; k < j; k++){
			h(k, j) = dot(onb.column(k), t);
			t = t - h(k, j) * onb.column(k);
		}
		h(j + 1, j) = abs(t);
		std::vector<T> vj = t / (h(j + 1, j));
		for(size_t i = 0; i < vj.size() - 1; i++){
			onb(i, j + 1) = vj[i];
		}
	}
	return std::pair(onb, h);
}

template<typename T>
std::vector<T> gmresm(const csrMatrix<T> &mtr, const std::vector<T> &v, const std::vector<T> &start, const size_t dim, const size_t restarts, const T tolerance){
	std::vector<T> ret = start;
	std::vector<std::vector<T>> V(dim + 1, std::vector<T>(v.size()));
	// denseMatrix<T> V(v.size(), dim + 1);
	denseMatrix<T> H(dim + 1, dim);
	std::vector<T> residual = v - mtr * start;

	std::vector<T> givensS(dim + 1);
	std::vector<T> givensC(dim + 1);

	T rho = abs(residual);
	// size_t restarted = 0;

	for(size_t restart = 0; restart < restarts; restart++){
		V[0] = residual / rho;
		std::vector<T> s(dim + 1);
		s[0] = rho;
		for(size_t iter = 0; iter < dim; iter++){
			V[iter + 1] = mtr * V[iter];
			std::vector<T> w = mtr * V[iter];
			for(size_t row = 0; row <= iter; row++){
				H(row, iter) = dot(w, V[iter]);
				w = w - H(row, iter) * V[row];
			}
			H(iter + 1, iter) = abs(w);
			V[iter + 1] = w / H(iter + 1, iter);

			for(size_t row = 0; row < iter; row++){
				T tmp = givensS[row] * H(row, iter) + givensC[row] * H(row + 1, iter);
				H(row + 1, iter) = -givensC[row] * H(row, iter) + givensS[row] * H(row + 1, iter);
				H(row, iter) = tmp;
			}

			if(H(iter + 1, iter) == 0.0){
				givensS[iter] = 1;
				givensC[iter] = 0;
			}else if(std::abs(H(iter + 1, iter)) > std::abs(H(iter, iter))){
				T tmp = H(iter, iter) / H(iter + 1, iter);
				givensC[iter] = 1 / sqrt(1 + tmp * tmp);
				givensS[iter] = tmp * givensC[iter];
			}else{
				T tmp = H(iter + 1, iter) / H(iter, iter);
				givensS[iter] = 1 / sqrt(1 + tmp * tmp);
				givensC[iter] = tmp * givensS[iter];
			}

			T tmp = givensS[iter] * H(iter, iter) + givensC[iter] * H(iter + 1, iter);
			H(iter + 1, iter) = -givensC[iter] * H(iter, iter) + givensS[iter] * H(iter + 1, iter);
			H(iter, iter) = tmp;

			tmp = givensS[iter] * s[iter] + givensC[iter] * s[iter + 1];
			s[iter + 1] = -givensC[iter] * s[iter] + givensS[iter] * s[iter + 1];
			s[iter] = tmp;

			rho = std::abs(s[iter + 1]);
			if(rho < tolerance * abs(v)){
				for(int i = int(iter); i >= 0; i--){
					s[size_t(i)] = s[size_t(i)] / H(size_t(i), size_t(i));
					for(int j = i - 1; j >= 0; j--){
						s[size_t(j)] -= s[size_t(i)] * H(size_t(j), size_t(i));
					}
				}
				for(size_t i = 0; i <= iter; i++)
					ret = ret + V[i] * s[i];
				return ret;
			}
		}
		for(int i = int(dim - 2); i >= 0; i--){
			s[size_t(i)] = s[size_t(i)] / H(size_t(i), size_t(i));
			for(int j = i - 1; j >= 0; j--){
				s[size_t(j)] -= s[size_t(i)] * H(size_t(j), size_t(i));
			}
		}
		for(size_t i = 0; i <= (dim > 2 ? dim - 2 : 0); i++){
			ret = ret + V[i] * s[i];
		}
		residual = v - mtr * ret;
		rho = abs(residual);
	}
	return ret;
}
