prog: operations.o tests.o main.o
	g++ -std=c++11 -g -O0 -Wall -fPIC operations.o tests.o main.o -o prog

sym: mainSym.o operationsSym.o
	g++ -std=c++11 -g -O0 -Wall -fPIC operationsSym.o mainSym.o -o sym

operations.o: operations.cpp operations.hpp CMatrix.hpp Matrix.hpp parallelise.hpp stack.hpp
	g++ -std=c++11 -c -g -O0 -Wall -fPIC $<

operationsSym.o: operationsSym.cpp operationsSym.hpp
	g++ -std=c++11 -c -g -O0 -Wall -fPIC $<

tests.o: tests.cpp CMatrix.hpp Matrix.hpp
	g++ -std=c++11 -c -g -O0 -Wall -fPIC $<

main.o: main.cpp CMatrix.hpp Matrix.hpp
	g++ -std=c++11 -c -g -O0 -Wall -fPIC $<

mainSym.o: mainSym.cpp
	g++ -std=c++11 -c -g -O0 -Wall -fPIC $<

.PHONY: clean
clean:
	rm *.o *.a *.so
