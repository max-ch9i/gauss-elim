#include "CMatrix.hpp"

std::ostream& operator<<(std::ostream& os, const CMatrix& m) { 
    for (int i = 0; i < m.getSize(); i++)
    {
        os << m.getByIndex(i) << " ";
        if (i % m.getColNum() == m.getColNum() - 1)
            os << std::endl;
    }
    return os;
}
