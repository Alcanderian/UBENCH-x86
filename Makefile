CXX?=g++
CXXFLAGS+=-O2 -g -std=c++11
SSEFLAGS?=-msse4.2
AVXFLAGS?=-mavx
FMAFLAGS?=-mfma -mavx2
FFTWFLAGS?=-lfftw3 -lfftw3_omp

all:sse_bench avx_bench fma_bench omp_bench

sse_bench:
	$(CXX) $(CXXFLAGS) $(SSEFLAGS) -o $@.exe $@.cpp

avx_bench:
	$(CXX) $(CXXFLAGS) $(AVXFLAGS) -o $@.exe $@.cpp

fma_bench:
	$(CXX) $(CXXFLAGS) $(FMAFLAGS) -o $@.exe $@.cpp

omp_bench:
	$(CXX) $(CXXFLAGS) $(SSEFLAGS) -o $@.exe $@.cpp -fopenmp

find_bench:
	$(CXX) $(CXXFLAGS) -c $@.cpp arg_find.cpp
	$(CXX) $(CXXFLAGS) -o $@.exe $@.o arg_find.o

fftw_bench:
	$(CXX) $(CXXFLAGS) $(SSEFLAGS) -o $@.exe $@.cpp $(FFTWFLAGS) -fopenmp

xbyak_test:
	$(CXX) $(CXXFLAGS) -o $@.exe $@.cpp

clean:
	rm *.exe
