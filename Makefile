CXX=g++
CXXFLAGS=-O2 -g -std=c++11
SSEFLAGS=-msse4.2
AVXFLAGS=-mavx

all:sse_bench avx_bench

sse_bench:
	$(CXX) $(CXXFLAGS) $(SSEFLAGS) -o $@.exe $@.cpp

avx_bench:
	$(CXX) $(CXXFLAGS) $(AVXFLAGS) -o $@.exe $@.cpp

clean:
	rm *.exe
