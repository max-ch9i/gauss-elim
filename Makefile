prog: main.cpp CMatrix.cpp CMatrix.h
	g++ -std=c++11 -g -O0 -Wall -fPIC CMatrix.cpp main.cpp -o prog

.PHONY: clean
clean:
	rm *.o *.a *.so
