#include <iostream>
#include "CMatrix.hpp"
#include "operations.hpp"

char test_failed[] = "Test failed: ";

using namespace std;

void test_2x2()
{
  const int rr = 2;
  const int cc = 2;

  float ar[rr * cc] = { 1, 2
                    , 3, 4};
  float t[rr * cc] = { 1, 2
                    , 0, -2};

  CMatrix A(rr, cc);
  A.add(ar, rr*cc);
  triangulate(A);

  if (A != t)
  {
    cout << test_failed << __FUNCTION__ << endl;
    cout << A << endl;
  }
}

void test_3x3()
{
  const int rr = 3;
  const int cc = 3;

  float ar[rr * cc] = { 1, 2, 3
                      , 1, 4, 6
                      , 1, 6, 10};
  float t[rr * cc] = { 1, 2, 3
                     , 0, 2, 3
                     , 0, 0, 1};

  CMatrix A(rr, cc);
  A.add(ar, rr*cc);
  triangulate(A);

  if (A != t)
  {
    cout << test_failed << __FUNCTION__ << endl;
    cout << A << endl;
  }
}

void test_4x4()
{
  const int rr = 4;
  const int cc = 4;

  float ar[rr * cc] = { 1, 2, 3, 4
                      , 1, 4, 6, 8
                      , 1, 6, 10, 15
                      , 1, 10, 11, 30
                      };
  float t[rr * cc] = { 1, 2, 3, 4
                     , 0, 2, 3, 4
                     , 0, 0, 1, 3
                     , 0, 0, 0, 22};

  CMatrix A(rr, cc);
  A.add(ar, rr*cc);
  triangulate(A);

  if (A != t)
  {
    cout << test_failed << __FUNCTION__ << endl;
    cout << A << endl;
  }
}

void test_4x4aug()
{
  const int rr = 4;
  const int cc = 5;

  float ar[rr * cc] = { 1, 2, 3, 4, 100
                      , 1, 4, 6, 8, 200
                      , 1, 6, 10, 15, 300
                      , 1, 10, 11, 30, 400
                      };
  float t[rr * cc] = { 1, 2, 3, 4, 100
                     , 0, 2, 3, 4, 100
                     , 0, 0, 1, 3, 0
                     , 0, 0, 0, 22, -100};

  CMatrix A(rr, cc);
  A.add(ar, rr*cc);
  triangulate(A);

  if (A != t)
  {
    cout << test_failed << __FUNCTION__ << endl;
    cout << A << endl;
  }
}

void test_3x3_zero_multiple()
{
  const int rr = 3;
  const int cc = 3;

  float ar[rr * cc] = { 1, 2, 3
                      , 2, 4, 8
                      , 1, 6, 10
                      };
  float t[rr * cc] = { 1, 2, 3
                     , 0, 4, 7
                     , 0, 0, 2};

  CMatrix A(rr, cc);
  A.add(ar, rr*cc);
  triangulate(A);

  if (A != t)
  {
    cout << test_failed << __FUNCTION__ << endl;
    cout << A << endl;
  }
}

void test_4x4_zero_multiple()
{
  const int rr = 4;
  const int cc = 4;

  float ar[rr * cc] = { 1, 2, 3, 4
                      , 1, 2, 4, 7
                      , 1, 2, 5, 6
                      , 1, 4, 6, 8
                      };
  float t[rr * cc] = { 1, 2, 3, 4
                     , 0, 2, 3, 4
                     , 0, 0, 2, 2
                     , 0, 0, 0, 2
                     };
  CMatrix A(rr, cc);
  A.add(ar, rr*cc);
  triangulate(A);

  if (A != t)
  {
    cout << test_failed << __FUNCTION__ << endl;
    cout << A << endl;
  }
}

void test_3x3_linear_dependence()
{
  const int rr = 3;
  const int cc = 3;

  float ar[rr * cc] = { 1, 2, 3
                      , 1, 6, 10
                      , 2, 8, 13
                      };
  float t[rr * cc] = { 1, 2, 3
                     , 0, 4, 7
                     , 0, 0, 0};

  CMatrix A(rr, cc);
  A.add(ar, rr*cc);
  triangulate(A);

  if (A != t)
  {
    cout << test_failed << __FUNCTION__ << endl;
    cout << A << endl;
  }
}

void test_3x3_linear_dependence_fail_to_swap()
{
  const int rr = 3;
  const int cc = 3;

  float ar[rr * cc] = { 1, 2, 3
                      , 1, 2, 6
                      , 2, 4, 6
                      };
  float t[rr * cc] = { 1, 2, 3
                     , 0, 0, 3
                     , 0, 0, 0};

  CMatrix A(rr, cc);
  A.add(ar, rr*cc);
  triangulate(A);

  if (A != t)
  {
    cout << test_failed << __FUNCTION__ << endl;
    cout << A << endl;
  }
}

void test_3x4_backwards_substitution()
{
  const int rr = 3;
  const int cc = 4;

  float ar[rr * cc] = { 5, 2, 3, 2
                      , 1, 2, 6, 8
                      , 2, 4, 6, 2
                      };
  float t[rr * 1] = { 0.25
                     , -3.125
                     , 2.33333};
  CMatrix A(rr, cc);
  A.add(ar, rr*cc);
  triangulate(A);
  CMatrix B = substitute(A);

  if (B != t)
  {
    cout << test_failed << __FUNCTION__ << endl;
    cout << B << endl;
  }
}

void run_tests()
{
  test_2x2();
  test_3x3();
  test_4x4();
  test_4x4aug();
  test_3x3_zero_multiple();
  test_4x4_zero_multiple();
  test_3x3_linear_dependence();
  test_3x3_linear_dependence_fail_to_swap();
  test_3x4_backwards_substitution();
}
