/* 
    Collatz conjecture problem calculator 
*/

#include <random>
#include <time.h>
#include <sstream>
#include <iostream>

#include "BigInteger.h"

#define RANDS_NUM 10
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
            numString = argv[1];
        }
        else
        {
            std::stringstream tmp;
            for (int i = 0; i < RANDS_NUM; ++i)
            {
                tmp << rand();
            }
            numString = tmp.str();
        }

        BigInteger number(numString);
        BigInteger zero("");
        BigInteger one("1");
        BigInteger two("2");
        BigInteger three("3");


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
    catch (BigInt::ZeroDivisionException &e)
    {
        cout << e.what() << endl;
    }
    catch (...)
    {
        cout << "Unknown exception caught" << endl;
    }

    return 0;
}