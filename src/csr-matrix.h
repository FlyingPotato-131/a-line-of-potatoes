#include <cstddef>
#include <vector>
#include <stdint.h>
#include <vector-operations.h>
#include <functional>

template<typename T>
struct csrMatrix{
private:
	std::vector<T> values;
	std::vector<size_t> columns;
	std::vector<size_t> rows;
public:
	csrMatrix(const std::vector<T> &data, std::size_t width);
	bool validate(const std::vector<T> &values, const std::vector<size_t> &columns, const std::vector<size_t> &rows) const;
	T operator()(size_t h, size_t w) const;
	std::vector<T> operator*(const std::vector<T> &v) const;
	std::vector<T> mulCondition(const std::vector<T> &v, const std::function<bool(size_t, size_t)> condition) const; //multiply matrix by vector but values at positions h, w such that condition(h, w) == false are zeroed
	T mulRow(const std::vector<T> &v, size_t row, const std::function<bool(size_t, size_t)> condition = nullptr) const; //multiply row by vector
};

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

template<typename T>
std::vector<T> simpleIterMethod(const csrMatrix<T> &mtr, const std::vector<T> &v, const std::vector<T> &start, const T tolerance, const size_t Nmax, const T tau){
	std::vector<T> current = start;
	for(size_t n = 0; n < Nmax; n++){
		current = current - tau * (mtr * current - v);

		bool done = 1;
		for(T error : mtr * current - v){
			if(std::abs(error) > tolerance){
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
			if(std::abs(error) > tolerance){
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
			if(std::abs(error) > tolerance){
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