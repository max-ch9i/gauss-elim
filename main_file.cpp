#include <iostream>
#include "CMatrix.hpp"
#include "operations.hpp"
#include <cmath>
#include <random>
#include <fstream>

using namespace std;

void run_tests();

int main()
{
    // run_tests();
    // const int s = 3;
    // CMatrix D = make_matrix(s, s+1);

    // float ar[4 * 5] = { pow(float{-2}, float{3}), pow(float{-2}, float{2}), -2, 1, 3
    //                   , pow(float{-1}, float{3}), pow(float{-1}, float{2}), -1, 1, 7
    //                   , pow(float{.5}, float{3}), pow(float{.5}, float{2}), .5, 1, -5
    //                   , pow(float{ 2}, float{3}), pow(float{ 2}, float{2}),  2, 1, 3
    //                   };

    const int rn = 6;
    const int cn = rn + 1;
    CMatrix D(rn,cn);
    default_random_engine generator;
    uniform_int_distribution<float> distribution(1.0,20.0);
    auto dice = std::bind(distribution, generator);

    ofstream ofs ("test.txt", ofstream::out);

    for (int r = 0; r < rn; r++)
    {
      float x = float(r)/rn + 1.1;
      float y = dice();
      ofs << x << " " << y << endl;
      for (int c = 0; c < cn; c++)
      {
        if (c == cn - 1)
        {
          // set y
          D.add(y);
          continue;
        }
        if (c == cn - 2)
        {
          // set y
          D.add(1.0);
          continue;
        }
        int inv = cn - c - 2;
        float coeff = pow(float{x}, inv);
        D.add(coeff);
      }
    }

    ofs.close();
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
