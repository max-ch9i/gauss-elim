#pragma once
#include <iostream>
#include "Matrix.hpp"
#include <cmath>

class CMatrix : public Matrix
{
    public:
        CMatrix(int nr, int nc):sr(nr),sc(nc),elements(new float[sr*sc]())
        {
            // std::cout << "CONSTRUCT " << std::endl;
        };
        ~CMatrix() {
            // std::cout << "DESTRUCT " << std::endl;
            delete[] elements;
        };
        void add(float e) { if(pointer + 1 <= sr*sc) elements[pointer++] = e; };
        void add(float* es, int size) {
            if(size <= sr*sc)
            {
                for (int i = 0; i < size; i++)
                {
                    add(es[i]);
                }
            }
        };
        float getByIndex(int i) const { return elements[i]; };
        float getElement(int r, int c) { return elements[sc * r + c]; };
        int getSize() const { return sr*sc; };
        int getColNum() const { return sc; };
        int getRowNum() const { return sr; };
        void setByIndex(int i, float e) { if(i < sr*sc) elements[i] = e; };
        void setRow(int rn, const CMatrix& m) {
            if (m.sr > 1)
            {
                throw std::out_of_range("Can copy only one row.");
            }
            if (m.sc != sc)
            {
                throw std::out_of_range("Column count must be identical.");
            }

            for (int i = 0; i < sc; i++)
            {
                elements[rn * sc + i] = m.elements[i];
            }
        };
        CMatrix extractRow(int rn)
        {
            if (rn > sr)
            {
                throw std::out_of_range("Out of range.");
            }

            CMatrix a(1, sc);
            for (int i = 0; i < sc; i++)
            {
                a.add(elements[rn * sc + i]);
            }
            return a;
        }

        // Copy
        CMatrix(const CMatrix& m):sr(m.sr),sc(m.sc),elements(new float[sr*sc]()) {
            for (int i = 0; i < sr*sc; i++) {
                elements[i] = m.elements[i];
            }
            std::cout << "COPY CONST" << std::endl;
        };
        CMatrix& operator=(const CMatrix& m) {
            sr = m.sr;
            sc = m.sc;
            delete[] elements;
            elements = new float[sr*sc]();
            for (int i = 0; i < sr*sc; i++) {
                elements[i] = m.elements[i];
            }
            std::cout << "COPY ASSIGN" << std::endl;
            return *this;
        };
        bool operator!=(const float* ar)
        {
            for (int i = 0; i < sr*sc;i++)
            {
                if (ar[i] != elements[i])
                {
                    return true;
                }
            }
            return false;
        }

        // Move
        CMatrix(CMatrix&& m):sr(m.sr),sc(m.sc),elements(new float[sr*sc]()) {
            elements = m.elements;
            m.elements = nullptr;
            std::cout << "MOVE CONST" << std::endl;
        };

        CMatrix& operator=(CMatrix&& m) {
            if (this != &m)
            {
                sr = m.sr;
                sc = m.sc;
                delete[] elements;
                elements = m.elements;
                m.elements = nullptr;
                std::cout << "MOVE ASSIGN" << std::endl;
            }
            return *this;
        };

        // COPY
        CMatrix operator*(const float& f)
        {
            CMatrix m(sr, sc);
            for (int i = 0; i < sr * sc; i++)
            {
                m.elements[i] = elements[i] * f;
            }
            return m;
        }

        void operator*=(float&& f)
        {
            for (int i = 0; i < sr * sc; i++)
            {
                elements[i] *= f;
            }
        }

        void operator-=(const CMatrix& m)
        {
            if (m.getSize() != getSize())
            {
                throw std::out_of_range("Lengths do not match.");
            }
            for (int i = 0; i < sr * sc; i++)
            {
                elements[i] -= m.elements[i];
            }
        }
        float mroundf(float a) const
        {
          return std::round(a * 1000) / 1000;
        }

    private:
        int sr;
        int sc;
        int pointer = 0;
        float* elements;
};

inline std::ostream& operator<<(std::ostream& os, const CMatrix& m) { 
    for (int i = 0; i < m.getSize(); i++)
    {
        os << m.mroundf(m.getByIndex(i)) << " ";
        if (i % m.getColNum() == m.getColNum() - 1)
            os << std::endl;
    }
    return os;
}
