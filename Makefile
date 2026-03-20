demo: demo.cpp BigInteger.o BigInteger.h
	g++ -std=c++14 -o demo.exe demo.cpp BigInteger.o -Wall -DDEBUG

tests: tests.cpp BigInteger.o BigInteger.h
	g++ -std=c++14 -o tests.exe tests.cpp BigInteger.o -Wall

BigInteger.o: BigInteger.h BigInteger.cpp
	g++ -std=c++14 -c -o  BigInteger.o BigInteger.cpp -Wall

clean: BigInteger.o
	rm *.o