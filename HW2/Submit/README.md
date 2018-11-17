# Advanced Theory of Computation 2018 Fall

## HW2, LZ78 Compression & Decoding

* OS: Ubuntu 16.04

* Language: C++

* Compile:

1. g++ -o encoding encoding.cpp
2. g++ -o decoding decoding.cpp

* Execution:

1. ./encoding.cpp infile.txt encoding.txt
2. ./decoding.cpp encoding.txt outfile.txt
3. diff --report infile.txt outfile.txt
