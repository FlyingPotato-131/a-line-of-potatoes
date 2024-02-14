#include <cstddef>
#include <vector>
#include <stdint.h>

template<typename T>
struct csrMatrix{
private:
	std::vector<T> values;
	std::vector<size_t> columns;
	std::vector<size_t> rows;
public:
	csrMatrix(const std::vector<T> *data, std::size_t width);
	bool validate(const std::vector<T> *values, const std::vector<size_t> *columns, const std::vector<size_t> *rows);
	T operator()(size_t h, size_t w);
	std::vector<T> operator*(const std::vector<T> &v) const;	
};

//instantiate for standard numerical types so that library can be compiled

template struct csrMatrix<int8_t>;
template struct csrMatrix<int16_t>;
template struct csrMatrix<int32_t>;
template struct csrMatrix<int64_t>;

template struct csrMatrix<uint8_t>;
template struct csrMatrix<uint16_t>;
template struct csrMatrix<uint32_t>;
template struct csrMatrix<uint64_t>;

template struct csrMatrix<float>;
template struct csrMatrix<double>;
template struct csrMatrix<long double>;
