#ifndef BIGINTEGER_H_65654
#define BIGINTEGER_H_65654

#include <stdexcept>
#define string std::string
#define BINT_BASE 10
#define BINT_POW 9

namespace BigInt
{

    class BigInteger
    {
    private:
        class Inner;
        Inner *impl;

    public:
        BigInteger(const string &number = "");

        BigInteger(const BigInteger &other);
        const BigInteger &operator=(const BigInteger &source);

        ~BigInteger();

        bool getSign() const;

        void setSign(const bool sign);

        void stringToNum(const string &numberString);
        string toString() const;
        void copy(BigInteger &dest) const;
        int count() const;
        void makeEmpty();
        bool isEmpty() const;
        bool isZero() const;

        friend BigInteger &operator+=(BigInteger &dest, const BigInteger &src);
        friend BigInteger &operator-=(BigInteger &dest, const BigInteger &src);
        friend BigInteger &operator*=(BigInteger &dest, const BigInteger &src);
        friend BigInteger &operator/=(BigInteger &dest, const BigInteger &src);
        friend BigInteger &operator%=(BigInteger &dest, const BigInteger &src);

        friend BigInteger operator+(const BigInteger &a, const BigInteger &b);
        friend BigInteger &operator++(BigInteger &a);
        friend BigInteger operator-(const BigInteger &a, const BigInteger &b);
        friend BigInteger operator-(const BigInteger &a);
        friend BigInteger &operator--(BigInteger &a);
        friend BigInteger operator*(const BigInteger &a, const BigInteger &b);
        friend BigInteger operator/(const BigInteger &a, const BigInteger &b);
        friend BigInteger operator%(const BigInteger &a, const BigInteger &b);

        friend bool operator==(const BigInteger &a, const BigInteger &b);
        friend bool operator!=(const BigInteger &a, const BigInteger &b);
        friend bool operator<(const BigInteger &a, const BigInteger &b);
        friend bool operator<=(const BigInteger &a, const BigInteger &b);
        friend bool operator>=(const BigInteger &a, const BigInteger &b);
        friend bool operator>(const BigInteger &a, const BigInteger &b);

        friend std::ostream &operator<<(std::ostream &out, const BigInteger &a);
        friend std::istream &operator>>(std::istream &in, BigInteger &a);
    };

    class ZeroDivisionException : public std::runtime_error
    {
    public:
        ZeroDivisionException(const BigInteger &dividend, const BigInteger &divisor);
    };

}

#undef string
#endif