#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#define BASE 10
#define BASE_POW 9

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
        BigIntegerData *getLowerDigits() const;
        BigIntegerData *getHigherDigits() const;

        void setSign(const bool sign);

        int stringToNum(const string &numberString);
        string toString() const;
        int copy(BigInteger &dest) const;
        int count() const;
        void makeEmpty();
        bool isEmpty() const;

        friend void operator+=(BigInteger &dest, const BigInteger &src);
        friend BigInteger &operator-=(BigInteger &dest, const BigInteger &src);
        friend BigInteger &operator*=(BigInteger &dest, const BigInteger &src);
        friend BigInteger &operator/=(BigInteger &dest, const BigInteger &src);
        friend BigInteger &operator%=(BigInteger &dest, const BigInteger &src);

        friend BigInteger operator+(const BigInteger &a, const BigInteger &b);
        friend BigInteger operator-(const BigInteger &a, const BigInteger &b);
        friend BigInteger operator-(const BigInteger &a);
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

#endif