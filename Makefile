LINK.o = $(CXX) $(CXXFLAGS) $(LDFLAGS) $(TARGET_ARCH)
CXXFLAGS = -std=c++11 -g -O0 -Wall -fPIC

SOURCES = operations.cpp \
					tests.cpp \
					main.cpp \
					operationsSym.cpp \
					mainSym.cpp

main: operations.o tests.o main.o
mainSym: operationsSym.o mainSym.o

.PHONY: clean
clean:
	rm *.o *.d

include $(subst .cpp,.d,$(SOURCES))

%.d: %.cpp
	$(CXX) -M $(CXXFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$
