#include <iostream>
#include "CMatrix.h"

using namespace std;

#define R 3
#define C 3

CMatrix make_matrix()
{
    CMatrix m(R, C);
    for (int i = 0; i < R * C; i++) {
        m.add(i);
    }
    return m;
}

int main()
{
    // CMatrix m1 = make_matrix();
    // CMatrix m2(R, C);
    // m2 = make_matrix();
    CMatrix A(R,C);
    // float ar[R*C] = { 1, 2
    //                 , 3, 4};
    float ar1[R*C] = { 1, 2, 3
                     , 4, 5, 6
                     , 7, 8, 9};
    A.add(ar1, R*C);
    CMatrix U(R,C);

    // Step 1
    for (int org_row = 0; org_row < R - 1; org_row++)
    {
        CMatrix row_pivot = A.extractRow(org_row);
        U.setRow(org_row, row_pivot);
        for (int i = org_row + 1; i < R; i++)
        {
            CMatrix r = A.extractRow(i);
            CMatrix row_pivot_multiple = row_pivot * (A.getElement(i, 0) / A.getElement(org_row, 0));
            r -= row_pivot_multiple;

            U.setRow(i, r);
            cout << U << endl;
        }
    }

    
    // CMatrix row1 = a.extractRow(1);
    // cout << "Res: " << row0.getByIndex(1) << endl;
    // row0 *= 3;
    // cout << "Res: " << row0.getByIndex(1) << endl;

    // cout << m3.getByIndex(5) << endl;
    // cout << m1.getByIndex(5) << endl;
    // m1.setByIndex(5, 10);
    // cout << m1.getByIndex(5) << endl;
    // cout << m2.getByIndex(5) << endl;
}
