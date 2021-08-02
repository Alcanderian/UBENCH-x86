CXX=g++
CXXFLAGS=-O2 -g -std=c++11
SSEFLAGS=-msse4.2
AVXFLAGS=-mavx

sse_bench:
	$(CXX) $(CXXFLAGS) $(SSEFLAGS) -o $@.exe $@.cpp

clean:
	rm *.exe
