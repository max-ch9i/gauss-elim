#include "operationsSym.hpp"
#include <iostream>
#include <random>

CMatrixSym make_matrix(const int rr, const int cc)
{
    CMatrixSym m(rr, cc);
    std::default_random_engine generator;
    std::uniform_int_distribution<float> distribution(1, 999);
    auto dice = std::bind ( distribution, generator );
    for (int i = 0; i < rr * cc; i++) {
        m.add(Symbol<long>(dice(), dice()));
    }
    return m;
}

void prepare_next_row(CMatrixSym& A, int row)
{
    Symbol<long> pivot = A.getElement(row, row);

    if (pivot.getNum() != 0)
    {
        return;
    }

    int i = row + 1;
    int num_row = A.getRowNum();
    while (i < num_row)
    {
        if (A.getElement(i, row).getNum() != 0)
        {
            // Swap
            CMatrixSym current_row = A.extractRow(row);
            A.setRow(row, A.extractRow(i));
            A.setRow(i, current_row);
            return;
        }
        i++;
    }
}

void triangulate(CMatrixSym& A)
{
    int num_rows = A.getRowNum();
    for (int org_row = 0; org_row < num_rows - 1; org_row++)
    {
        prepare_next_row(A, org_row);

        CMatrixSym row_pivot = A.extractRow(org_row);
        Symbol<long> pivot = A.getElement(org_row, org_row);

        if (pivot.getNum() == 0)
        {
            return;
        }

        for (int i = org_row + 1; i < num_rows; i++)
        {
            CMatrixSym r = A.extractRow(i);

            Symbol<long> pivot_multiple = A.getElement(i, org_row) / pivot;
            CMatrixSym row_pivot_multiple = row_pivot * pivot_multiple;
            r -= row_pivot_multiple;

            A.setRow(i, r);
        }
    }
}
