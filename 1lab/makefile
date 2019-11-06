all: main

main: main.o Trit.o TritSet.o
	g++ main.o Trit.o TritSet.o -L/root/mybuild/lib/ -l gtest -l pthread -o main

main.o: main.cpp
	g++ -c -std=c++11 -I/root/googletest-release-1.10.0/googletest/include/ main.cpp

Trit.o: Trit.cpp
	g++ -c Trit.cpp

TritSet.o: TritSet.cpp
	g++ -c TritSet.cpp

clean:
	rm -rf *o
