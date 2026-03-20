#include <random>
#include <time.h>
#include <sstream>
#include <iostream>

#include "BigInteger.h"
#include "DEBUG.h"

#define RANDS_NUM 5
using BigInt::BigInteger;
using std::cout;
using std::endl;

int main(int argc, char **argv)
{
    try
    {
        srand(time(0));
        std::string numString;

        if (argc > 1)
        {
            debug("Test");
            numString = argv[1];
            debug("Test");
        }
        else
        {
            debug("Test");
            std::stringstream tmp;
            for (int i = 0; i < RANDS_NUM; ++i)
            {
                tmp << rand();
            }
            numString = tmp.str();
            debug("Test");
        }

        cout << numString;
        BigInteger number = BigInteger(numString);
        debug("Test");
        BigInteger zero = BigInteger();
        debug("Test");
        BigInteger one = BigInteger("1");
        debug("Test");
        BigInteger two = BigInteger("2");
        debug("Test");
        BigInteger three = BigInteger("3");

        debug("Test");

        while (number != one)
        {
            cout << number << endl;

            if ((number % two) == zero)
            {
                number /= two;
            }
            else
            {
                number *= three;
                ++number;
            }
        }
        cout << number << endl;
    }
    catch (std::invalid_argument &e)
    {
        cout << e.what() << endl;
    }
    catch (...)
    {
        cout << "Unknown exception caught" << endl;
    }

    return 0;
}