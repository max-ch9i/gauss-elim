#include <iostream>
#include "CMatrix.hpp"
#include "operations.hpp"
#include <cmath>

using namespace std;

void run_tests();

int main()
{
    // run_tests();
    // const int s = 3;
    // CMatrix D = make_matrix(s, s+1);

    float ar[4 * 5] = { pow(float{-2}, float{3}), pow(float{-2}, float{2}), -2, 1, 3
                      , pow(float{-1}, float{3}), pow(float{-1}, float{2}), -1, 1, 7
                      , pow(float{.5}, float{3}), pow(float{.5}, float{2}), .5, 1, -5
                      , pow(float{ 2}, float{3}), pow(float{ 2}, float{2}),  2, 1, 3
                      };
    CMatrix D(4,5);
    D.add(ar, 4*5);

    cout << D << endl;
    cout << endl;

    // CMatrix P = D;

    // auto start = chrono::steady_clock::now();
    // triangulate(P);
    // auto end = chrono::steady_clock::now();

    // cout <<chrono::duration <double, milli> (end - start).count()  << endl;

    // auto start = chrono::steady_clock::now();
    ptriangulate(D, 8);
    // auto end = chrono::steady_clock::now();

    // cout <<chrono::duration <double, milli> (end - start).count()  << endl;

    cout << D << endl;
    cout << endl;

    CMatrix sol = substitute(D);
    sol_print(sol);
}
