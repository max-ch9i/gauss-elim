#pragma once
#include <iostream>
#include "symbol.hpp"

class CMatrixSym
{
    public:
        CMatrixSym(int nr, int nc):sr(nr),sc(nc),elements(new Symbol<long>[sr*sc]())
        {
            // std::cout << "CONSTRUCT " << std::endl;
        };
        ~CMatrixSym() {
            // std::cout << "DESTRUCT " << std::endl;
            delete[] elements;
        };
        void add(const Symbol<long>& e) {
          if(pointer + 1 <= sr*sc) elements[pointer++] = e;
        };
        void add(Symbol<long>&& e) {
          if(pointer + 1 <= sr*sc) elements[pointer++] = e;
        };
        void add(Symbol<long>* es, int size) {
            if(size <= sr*sc)
            {
                for (int i = 0; i < size; i++)
                {
                    add(es[i]);
                }
            }
        };
        Symbol<long> getByIndex(int i) const { return elements[i]; };
        Symbol<long> getElement(int r, int c) { return elements[sc * r + c]; };
        int getSize() const { return sr*sc; };
        int getColNum() const { return sc; };
        int getRowNum() const { return sr; };
        void setByIndex(int i, Symbol<long> e) { if(i < sr*sc) elements[i] = e; };
        void setRow(int rn, const CMatrixSym& m) {
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
        CMatrixSym extractRow(int rn)
        {
            if (rn > sr)
            {
                throw std::out_of_range("Out of range.");
            }

            CMatrixSym a(1, sc);
            for (int i = 0; i < sc; i++)
            {
                a.add(elements[rn * sc + i]);
            }
            return a;
        }

        void sim()
        {
          for (int i = 0; i < getSize(); i++)
          {
            std::cout << getByIndex(i).sim() << " ";
            if (i % getColNum() == getColNum() - 1)
              std::cout << std::endl;
          }
        }

        // Copy
        CMatrixSym(const CMatrixSym& m):sr(m.sr),sc(m.sc),elements(new Symbol<long>[sr*sc]()) {
            for (int i = 0; i < sr*sc; i++) {
                elements[i] = m.elements[i];
            }
            std::cout << "COPY CONST" << std::endl;
        };
        CMatrixSym& operator=(const CMatrixSym& m) {
            sr = m.sr;
            sc = m.sc;
            delete[] elements;
            elements = new Symbol<long>[sr*sc]();
            for (int i = 0; i < sr*sc; i++) {
                elements[i] = m.elements[i];
            }
            std::cout << "COPY ASSIGN" << std::endl;
            return *this;
        };
        bool operator!=(const Symbol<long>* ar)
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
        CMatrixSym(CMatrixSym&& m):sr(m.sr),sc(m.sc),elements(new Symbol<long>[sr*sc]()) {
            elements = m.elements;
            m.elements = nullptr;
            std::cout << "MOVE CONST" << std::endl;
        };

        CMatrixSym& operator=(CMatrixSym&& m) {
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
        CMatrixSym operator*(const Symbol<long>& f)
        {
            CMatrixSym m(sr, sc);
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

        void operator-=(const CMatrixSym& m)
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

    private:
        int sr;
        int sc;
        int pointer = 0;
        Symbol<long>* elements;
};

std::ostream& operator<<(std::ostream& os, const CMatrixSym& m);
