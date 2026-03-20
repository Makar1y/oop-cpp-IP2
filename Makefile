demo: demo.cpp BigInteger.o BigInteger.h
	g++ -std=c++14 -o demo.exe demo.cpp BigInteger.o -Wall -DDEBUG

tests: test.cpp BigInteger.o BigInteger.h
	g++ -std=c++14 -o test.exe test.cpp BigInteger.o -Wall

BigInteger.o: BigInteger.h BigInteger.cpp
	g++ -std=c++14 -c -o  BigInteger.o BigInteger.cpp -Wall

clean: BigInteger.o
	rm *.o