#include "operations.hpp"
#include "parallelise.hpp"
#include <iostream>
#include <random>
#include <vector>

CMatrix make_matrix(const int rr, const int cc)
{
    CMatrix m(rr, cc);
    std::default_random_engine generator;
    std::uniform_int_distribution<float> distribution(1,6);
    auto dice = std::bind ( distribution, generator );
    for (int i = 0; i < rr * cc; i++) {
        m.add(dice());
    }
    return m;
}

void prepare_next_row(CMatrix& A, int row)
{
    float pivot = A.getElement(row, row);

    if (pivot != 0)
    {
        return;
    }

    int i = row + 1;
    int num_row = A.getRowNum();
    while (i < num_row)
    {
        if (A.getElement(i, row) != 0)
        {
            // Swap
            CMatrix current_row = A.extractRow(row);
            A.setRow(row, A.extractRow(i));
            A.setRow(i, current_row);
            return;
        }
        i++;
    }
}

void triangulate(CMatrix& A)
{
    int num_rows = A.getRowNum();
    for (int org_row = 0; org_row < num_rows - 1; org_row++)
    {
        prepare_next_row(A, org_row);

        CMatrix row_pivot = A.extractRow(org_row);
        float pivot = A.getElement(org_row, org_row);

        if (pivot == 0)
        {
            return;
        }

        for (int i = org_row + 1; i < num_rows; i++)
        {
            CMatrix r = A.extractRow(i);

            float pivot_multiple = A.getElement(i, org_row) / pivot;
            CMatrix row_pivot_multiple = row_pivot * pivot_multiple;
            r -= row_pivot_multiple;

            A.setRow(i, r);
        }
    }
}

struct eliminate {
  CMatrix* source;
  int row_num;
  CMatrix* row_pivot;
  float pivot_multiple;
  void operator()()
  {
    CMatrix row = (*source).extractRow(row_num);
    CMatrix row_pivot_multiple = *row_pivot * pivot_multiple;
    row -= row_pivot_multiple;
    (*source).setRow(row_num, row);
  }
};

void ptriangulate(CMatrix& A, int t)
{
  parallelise<eliminate> p(t);

  int num_rows = A.getRowNum();
  for (int org_row = 0; org_row < num_rows - 1; org_row++)
  {
    prepare_next_row(A, org_row);

    CMatrix row_pivot = A.extractRow(org_row);
    float pivot = A.getElement(org_row, org_row);

    if (pivot == 0)
    {
      return;
    }

    for (int i = org_row + 1; i < num_rows; i++)
    {
      p.add_work(eliminate{&A, i, &row_pivot, A.getElement(i, org_row) / pivot});
    }
    p.start();
  }
}

/*
    std::vector<eliminate> elim_procs;
        for (int vi = 0, i = org_row + 1; i < num_rows; vi++, i++)
            {
                  elim_procs.push_back(eliminate{A.extractRow(i), A, i, row_pivot, A.getElement(i, org_row) / pivot});
                        p.add_work(&elim_procs[vi]);
                            }
                                std::cout << "AAAAA";
                                    p.start();
*/

CMatrix substitute(CMatrix& A)
{
  int row_num = A.getRowNum();
  int col_num = A.getColNum();
  int last_row_idx = row_num - 1;
  int last_col_idx = col_num - 1;

  if (row_num != col_num - 1)
  {
    throw "Inappropriate matrix format";
  }

  // inverse order. Reordered later
  std::vector<float> x_n;
  for (int i = 0; i < row_num; i++)
  {
    // For every row:
    // Get the sought term coefficient
    float a = A.getElement(last_row_idx - i, last_col_idx - 1 - i);
    // Get rhs
    float b = A.getElement(last_row_idx - i, last_col_idx);
    float sum = 0;

    // Sum known terms in the row
    for (int u = 0; u < i; u++)
    {
      float c = A.getElement(last_row_idx - i, last_col_idx - 1 - u);
      float x_c = x_n[u];
      sum += c * x_c;
    }

    float x = (b - sum) / a;
    x_n.push_back(x);
  }

  CMatrix B(row_num, 1);
  std::vector<float>::reverse_iterator it_x_n = x_n.rbegin();
  std::vector<float>::reverse_iterator it_end_x_n = x_n.rend();
  while(it_x_n != it_end_x_n)
  {
    B.add(*it_x_n);
    it_x_n++;
  }
  return B;
}
