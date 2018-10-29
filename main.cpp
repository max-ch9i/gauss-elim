#include <iostream>
#include "CMatrix.hpp"
#include "operations.hpp"

using namespace std;

void run_tests();

int main()
{
    // run_tests();
    const int s = 8;
    CMatrix A = make_matrix(s, s);
    auto start = chrono::steady_clock::now();
    triangulate(A);
    auto end = chrono::steady_clock::now();

    cout << A << endl;
    cout <<chrono::duration <double, milli> (end - start).count()  << endl;
}
