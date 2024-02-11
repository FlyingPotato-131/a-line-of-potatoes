#include "tri-diag-matrix.h"

void thomasMethod(const triDiagMatrix *A, const std::vector<double> *f, std::vector<double> *x){
	size_t n = f->size() - 1;
	if(x->size() != n + 1){
		x->resize(n + 1);
	}

	bool hasstrict = 0;
	for(size_t i = 1; i < n; i++){
		if(A->b[i] > A->a[i] + A->c[i]){
			hasstrict = 1;
		}else if(A->b[i] < A->a[i] + A->c[i]){
			throw std::invalid_argument("system cannot be solved by Thomas method");
		}
	}

	std::vector<double> p = std::vector<double>(n + 1);
	std::vector<double> q = std::vector<double>(n + 1);
	p[1] = A->c[0] / A->b[0];
	q[1] = (*f)[0] / A->b[0];

	for(size_t i = 2; i <= n; i++){
		p[i] = (A->c[i - 1]) / (-A->a[i-2] * p[i-1] + A->b[i-1]);
		q[i] = ((*f)[i-1] - A->a[i-2] * q[i-1]) / (-A->a[i-2] * p[i-1] + A->b[i-1]);
	}

	(*x)[n] = ((*f)[n] - A->a[n-1] * q[n]) / (-A->a[n-1] * p[n] + A->b[n]);
	for(size_t i = n-1; i > 0; i--){
		(*x)[i] = -p[i+1] * (*x)[i+1] + q[i+1];
	}
	(*x)[0] = -p[1] * (*x)[1] + q[1];
	// return x;
}
