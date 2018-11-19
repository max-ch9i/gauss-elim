#include <iostream>
#include "CMatrix.hpp"
#include "operations.hpp"

using namespace std;

void run_tests();

int main()
{
    // run_tests();
    const int s = 2000;
    CMatrix D = make_matrix(s, s+1);

    CMatrix P = D;

    auto start = chrono::steady_clock::now();
    triangulate(P);
    auto end = chrono::steady_clock::now();

    cout <<chrono::duration <double, milli> (end - start).count()  << endl;

    P = D;

    start = chrono::steady_clock::now();
    ptriangulate(P, 8);
    end = chrono::steady_clock::now();

    // cout << A << endl;
    cout <<chrono::duration <double, milli> (end - start).count()  << endl;
}
