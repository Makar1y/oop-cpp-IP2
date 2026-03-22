#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "BigInteger.h"

using namespace BigInt;

void CollatzConjecture();

int main() {
    std::cout << "--- BigInteger Method Demonstration ---" << std::endl;

    // 1. BigInteger from string
    BigInteger a("1234567890");
    BigInteger zero; // Default constructor (interpreted as zero)
    std::cout << "Constructed a: " << a << " and zero: " << zero << std::endl;

    // 2. Initialize from other BigInteger
    BigInteger b(a);
    std::cout << "Copy constructed b from a: " << b << std::endl;

    // 3. Copy from other BigInteger
    BigInteger c;
    c = b;
    a = c;
    std::cout << "Assigned b to c: " << c << std::endl;
    std::cout << "Assigned c to a: " << a << std::endl;

    // 4. getSign() and setSign()
    std::cout << "c sign: " << (c.getSign() ? "negative" : "positive") << std::endl;
    c.setSign(true);
    std::cout << "c after setSign(true): " << c << " (sign: " << c.getSign() << ")" << std::endl;

    // 6. BigInteger from string
    c.stringToNum("9876543210");
    std::cout << "c after stringToNum(\"9876543210\"): " << c << std::endl;

    // 7. BigInteger to string
    std::string s = c.toString();
    std::cout << "c.toString(): " << s << std::endl;

    // 8. Copy from one to other (same as d = c)
    BigInteger d;
    c.copy(d);
    std::cout << "d after c.copy(d): " << d << std::endl;

    // 10. makeEmpty() and isEmpty()
    BigInteger e("111");
    std::cout << "e is empty before makeEmpty: " << (e.isEmpty() ? "yes" : "no") << std::endl;
    e.makeEmpty();
    std::cout << "e is empty after makeEmpty: " << (e.isEmpty() ? "yes" : "no") << std::endl;

    // 12. isZero()
    std::cout << "zero.isZero(): " << (zero.isZero() ? "yes" : "no") << std::endl;

    // 13. Arithmetic assignment operators (+=, -=, *=, /=, %=)
    BigInteger x("100"), y("30");
    x += y; // 130
    std::cout << "100 += 30 -> " << x << std::endl;
    x -= y; // 100
    std::cout << "130 -= 30 -> " << x << std::endl;
    x *= y; // 3000
    std::cout << "100 *= 30 -> " << x << std::endl;
    x /= y; // 100
    std::cout << "3000 /= 30 -> " << x << std::endl;
    x %= y; // 10
    std::cout << "100 %= 30 -> " << x << std::endl;

    // 14. Arithmetic operators (+, -, *, /, %)
    BigInteger p("50"), q("7");
    std::cout << "50 + 7 = " << (p + q) << std::endl;
    std::cout << "50 - 7 = " << (p - q) << std::endl;
    std::cout << "50 * 7 = " << (p * q) << std::endl;
    std::cout << "50 / 7 = " << (p / q) << std::endl;
    std::cout << "50 % 7 = " << (p % q) << std::endl;

    // 15. Prefix increment (++) and decrement (--)
    std::cout << "p before ++p: " << p << std::endl;
    std::cout << "++p returns: " << (++p) << std::endl;
    std::cout << "p after ++p: " << p << std::endl;
    std::cout << "--p returns: " << (--p) << std::endl;

    // 16. Unary minus (-)
    std::cout << "-p = " << (-p) << std::endl;

    // 17. Comparison operators (==, !=, <, <=, >=, >)
    BigInteger m("10"), n("20");
    std::cout << "10 == 20: " << (m == n) << std::endl;
    std::cout << "10 != 20: " << (m != n) << std::endl;
    std::cout << "10 < 20:  " << (m < n) << std::endl;
    std::cout << "10 <= 20: " << (m <= n) << std::endl;
    std::cout << "10 >= 20: " << (m >= n) << std::endl;
    std::cout << "10 > 20:  " << (m > n) << std::endl;

    // 18. operator<< and operator>>
    std::stringstream ss;
    ss << "12345";
    BigInteger r;
    ss >> r; // operator>>
    std::cout << "Read from stream: " << r << std::endl; // operator<<

    // Collatz Conjecture for big num
    CollatzConjecture();

    std::cout << "--- Demonstration Complete ---" << std::endl;
    return 0;
}


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
        demoFile.open("Collatz_Conjecture.txt");

        demoFile << "Collatz Conjecture problem solving for number " << numString << "\n";

        while (number != one)
        {
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
        demoFile << number << std::endl;

        std::cout << "Collatz Conjecture problem solving for number " << numString << " saved to Collatz_Conjecture.txt" << std::endl;
        demoFile.close();
    }
    catch (std::invalid_argument &e)
    {
        std::cout << e.what() << std::endl;
        demoFile.close();
    }
    catch (BigInt::ZeroDivisionException &e)
    {
        std::cout << e.what() << std::endl;
        demoFile.close();
    }
    catch (...)
    {
        std::cout << "Unknown exception caught" << std::endl;
        demoFile.close();
    }
}