#include <iostream>
#include "CMatrix.h"

using namespace std;

#define R 4
#define C 5

CMatrix make_matrix()
{
    CMatrix m(R, C);
    for (int i = 0; i < R * C; i++) {
        m.add(i);
    }
    return m;
}

void triangulate(CMatrix& A)
{
    int num_rows = A.getRowNum();
    for (int org_row = 0; org_row < num_rows - 1; org_row++)
    {
        CMatrix row_pivot = A.extractRow(org_row);
        for (int i = org_row + 1; i < num_rows; i++)
        {
            CMatrix r = A.extractRow(i);
            float pivot = A.getElement(i, org_row) / A.getElement(org_row, org_row);
            CMatrix row_pivot_multiple = row_pivot * pivot;
            r -= row_pivot_multiple;

            A.setRow(i, r);
        }
    }
}

int main()
{
    CMatrix A(R,C);
    // float ar[R*C] = { 1, 2
    //                 , 3, 4};
    // float ar1[R*C] = { 1, 2, 3
    //                  , 1, 4, 6
    //                  , 1, 6, 10};
    // float ar2[R*C] = { 1, 2, 3, 4
    //                  , 1, 4, 6, 8
    //                  , 1, 6, 10, 15
    //                  , 1, 10, 11, 30
    //                  };
    float ar3aug[R*C] = { 1, 2, 3, 4, 100
                     , 1, 4, 6, 8, 200
                     , 1, 6, 10, 15, 300
                     , 1, 10, 11, 30, 400
                     };
    A.add(ar3aug, R*C);

    triangulate(A);

    cout << A << endl;
}
