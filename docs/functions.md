## Documentation of functions in ALOP
#### thomasMethod(triDiagMatrix, std::vector\<double>)
included in <tri-diag-matrix.h>  
function that solves a system of linear equations Ax = f where A is a tridiagonal matrix using the [Thomas method](https://en.wikipedia.org/wiki/Tridiagonal_matrix_algorithm)  
arguments:
```cpp
triDiagMatrix A // coefficient matrix, must be diagonally dominant
std::vector<double> f // free terms
```
return value:
```cpp
std::vector<double> // result vector
```
example usage:
```cpp
triDiagMatrix A{
	{2.0, 5.0, 8.0, 2.0},
	{11.0, 14.0, 17.0, 11.0, 14.0},
	{3.0, 6.0, 9.0, 3.0}
};
std::vector<double> f = {1.0, 2.0, 3.0, 4.0, 5.0};
std::vector<double> x = thomasMethod(A, f);
```
