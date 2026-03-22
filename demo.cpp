#include <random>
#include <time.h>
#include <sstream>
#include <iostream>
#include <fstream>

#include "BigInteger.h"

using BigInt::BigInteger;
using std::cout;
using std::endl;
using std::string;

#define FILENAME "demo_log.txt"


void CollatzConjecture()
{
    std::ofstream demoFile;
    demoFile.exceptions(std::ofstream::failbit);

    try
    {
        srand(time(0));

        std::stringstream tmp;
        int rep = ((rand() % 11) + 5);
        for (int i = 0; i < rep; ++i)
        {
            tmp << rand();
        }
        std::string numString = tmp.str();

        BigInteger number(numString);
        BigInteger zero{};
        BigInteger one{"1"};
        BigInteger two{"2"};
        BigInteger three{"3"};
        demoFile.open(FILENAME);

        demoFile << "Collatz Conjecture problem solving for number " << numString << "\n";

        while (number != one)
        {
            cout << number << endl;
            demoFile << number << "\n";

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
        demoFile << number << std::endl;

        cout << "Collatz Conjecture problem solving for number " << numString << " saved to " << FILENAME << endl;
        demoFile.close();
    }
    catch (std::invalid_argument &e)
    {
        cout << e.what() << endl;
        demoFile.close();
    }
    catch (BigInt::ZeroDivisionException &e)
    {
        cout << e.what() << endl;
        demoFile.close();
    }
    catch (...)
    {
        cout << "Unknown exception caught" << endl;
        demoFile.close();
    }
}

int main(int argc, char **argv)
{
    CollatzConjecture();
    return 0;
}