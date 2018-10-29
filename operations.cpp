#include "operations.hpp"

CMatrix make_matrix()
{
    const int rr = 3;
    const int cc = 3;
    CMatrix m(rr, cc);
    for (int i = 0; i < rr * cc; i++) {
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
