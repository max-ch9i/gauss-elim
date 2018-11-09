#include "CMatrixSym.hpp"
#include "operationsSym.hpp"

int main()
{
  const int s = 3;
  CMatrixSym A = make_matrix(s, s+1);
  // A.sim();
  std::cout << A;
  std::cout << std::endl;

  auto start = std::chrono::steady_clock::now();
  triangulate(A);
  auto end = std::chrono::steady_clock::now();

  // A.sim();
  std::cout << A;
  std::cout << std::endl<< std::endl;
  std::cout <<std::chrono::duration <double, std::milli> (end - start).count()  << std::endl;
}
