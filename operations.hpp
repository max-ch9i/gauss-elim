#include "CMatrix.hpp"

CMatrix make_matrix(const int, const int);
void triangulate(CMatrix& A);
CMatrix substitute(CMatrix& A);
void ptriangulate(CMatrix& A, int t);
void sol_print(const CMatrix& A);
