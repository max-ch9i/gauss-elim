prog: CMatrix.o operations.o tests.o main.o
	g++ -std=c++11 -g -O0 -Wall -fPIC CMatrix.o operations.o tests.o main.o -o prog

CMatrix.o: CMatrix.cpp CMatrix.hpp Matrix.hpp
	g++ -std=c++11 -c -g -O0 -Wall -fPIC $<

operations.o: operations.cpp operations.hpp
	g++ -std=c++11 -c -g -O0 -Wall -fPIC $<

tests.o: tests.cpp
	g++ -std=c++11 -c -g -O0 -Wall -fPIC $<

main.o: main.cpp
	g++ -std=c++11 -c -g -O0 -Wall -fPIC $<

.PHONY: clean
clean:
	rm *.o *.a *.so
