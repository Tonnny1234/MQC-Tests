# Build the mqc engine. `make` builds bin/mqc; `make test` runs the internal self-test.
CXX      ?= g++
CXXFLAGS ?= -O3 -std=c++11 -Wall -Wextra
OPENMP   ?= -fopenmp

bin/mqc: src/main.cpp src/*.hpp
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $(OPENMP) src/main.cpp -o bin/mqc || \
	$(CXX) $(CXXFLAGS) -Wno-unknown-pragmas src/main.cpp -o bin/mqc

test: bin/mqc
	bin/mqc selftest --trials 60

clean:
	rm -rf bin

.PHONY: test clean
