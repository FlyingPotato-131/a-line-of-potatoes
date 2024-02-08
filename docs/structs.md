## Documentation of structs in ALOP

#### triDiagMatrix
included in <tri-diag-matrix.h>
structure containing a [tridiagonal matrix](https://en.wikipedia.org/wiki/Tridiagonal_matrix)
example usage:
```cpp
//11  2  0  0  0
// 3 14  5  0  0
// 0  6 17  8  0
// 0  0  9 11  2
// 0  0  0  3 14
triDiagMatrix A{
		{2.0, 5.0, 8.0, 2.0},
		{11.0, 14.0, 17.0, 11.0, 14.0},
		{3.0, 6.0, 9.0, 3.0}
};
triDiagMatrix B{a, b, c}; // where a, b, c of type std::vector<double> are the diagonals
```