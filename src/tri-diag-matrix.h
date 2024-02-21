#include <iostream>
#include <vector>

template<typename T>
struct triDiagMatrix{
	std::vector<T> a;
	std::vector<T> b;
	std::vector<T> c;
};

template<typename T>
std::vector<T> thomasMethod(const triDiagMatrix<T> &A, const std::vector<T> &f){
	std::vector<T> x = std::vector<T>(f.size());

	size_t n = f.size() - 1;
	if(x.size() != n + 1){
		x.resize(n + 1);
	}

	std::vector<double> p = std::vector<double>(n + 1);
	std::vector<double> q = std::vector<double>(n + 1);
	p[1] = A.c[0] / A.b[0];
	q[1] = f[0] / A.b[0];

	for(size_t i = 2; i <= n; i++){
		p[i] = (A.c[i - 1]) / (-A.a[i-2] * p[i-1] + A.b[i-1]);
		q[i] = (f[i-1] - A.a[i-2] * q[i-1]) / (-A.a[i-2] * p[i-1] + A.b[i-1]);
	}

	x[n] = (f[n] - A.a[n-1] * q[n]) / (-A.a[n-1] * p[n] + A.b[n]);
	for(size_t i = n-1; i > 0; i--){
		x[i] = -p[i+1] * x[i+1] + q[i+1];
	}
	x[0] = -p[1] * x[1] + q[1];
	return x;
}
