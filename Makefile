all: test test_opt

test: test.cpp reference.cpp avx2.cpp
	g++ -g -o test test.cpp reference.cpp avx2.cpp

test_opt: test.cpp reference.cpp avx2.cpp
	g++ -O3 -o test_opt test.cpp reference.cpp avx2.cpp

.PHONY: all
