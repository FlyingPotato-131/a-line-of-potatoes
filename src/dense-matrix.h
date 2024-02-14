#include <cstddef>
#include <vector>
#include <stdint.h>

template<typename T>
struct denseMatrix{
private:
	size_t width;
	std::vector<T> data;
public:
	denseMatrix(const std::vector<T> *data, size_t width);
	denseMatrix(const std::vector<std::vector<T>> *data);
	T *operator()(size_t h, size_t w);
	std::vector<T> operator*(const std::vector<T> &v);
};

//instantiate for standard numerical types so that library can be compiled

template struct denseMatrix<int8_t>;
template struct denseMatrix<int16_t>;
template struct denseMatrix<int32_t>;
template struct denseMatrix<int64_t>;

template struct denseMatrix<uint8_t>;
template struct denseMatrix<uint16_t>;
template struct denseMatrix<uint32_t>;
template struct denseMatrix<uint64_t>;

template struct denseMatrix<float>;
template struct denseMatrix<double>;
template struct denseMatrix<long double>;
