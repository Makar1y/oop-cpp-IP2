BigInteger.o: BigInteger.h BigInteger.cpp
	g++ -std=c++14 -c BigInteger.cpp -o BigInteger.o

clean: BigInteger.o
	rm *.o