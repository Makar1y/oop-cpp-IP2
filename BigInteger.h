#ifndef BIGINTEGER_H_65654
#define BIGINTEGER_H_65654

#include <stdexcept>
#define string std::string


#define BINT_BASE 10
#define BINT_POW 9

namespace BigInt
{

    /// @brief 
    class BigInteger
    {
    private:
        class Inner;
        Inner *impl;

    public:
        /// @brief 
        /// @param number 
        BigInteger(const string &number = "");

        /// @brief 
        /// @param other 
        BigInteger(const BigInteger &other);

        /// @brief 
        /// @param source 
        /// @return 
        const BigInteger &operator=(const BigInteger &source);

        /// @brief 
        ~BigInteger();


        /// @brief 
        /// @return 
        bool getSign() const;

        /**
         * @brief Set the sign of the `BigInteger`.
         * @param sign true for negative, false for positive/zero.
         */
        void setSign(const bool sign);

        /**
         * @brief Converts a string to a `BigInteger` representation.
         * @param numberString `string` to convert.
         */
        void stringToNum(const string &numberString);

        /**
         * @brief Converts the `BigInteger` to its string representation.
         * @return `string` The string representation.
         */
        string toString() const;

        /**
         * @brief Deep copies this `BigInteger` into dest.
         * @param dest The destination `BigInteger` object.
         */
        void copy(BigInteger &dest) const;

        /**
         * @brief Clears the BigInteger's value to an empty state(also interpreted as 0).
         */
        void makeEmpty();

        /**
         * @brief Checks if the BigInteger is empty (no sets of digits).
         * @return `bool` true if empty.
         */
        bool isEmpty() const;

        /**
         * @brief Checks if the `BigInteger` is zero.
         * @return `bool` true if zero.
         */
        bool isZero() const;

        // Arithmetic operators
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

        // Comparison operators
        friend bool operator==(const BigInteger &a, const BigInteger &b);
        friend bool operator!=(const BigInteger &a, const BigInteger &b);
        friend bool operator<(const BigInteger &a, const BigInteger &b);
        friend bool operator<=(const BigInteger &a, const BigInteger &b);
        friend bool operator>=(const BigInteger &a, const BigInteger &b);
        friend bool operator>(const BigInteger &a, const BigInteger &b);

        // Stream operators
        friend std::ostream &operator<<(std::ostream &out, const BigInteger &a);
        friend std::istream &operator>>(std::istream &in, BigInteger &a);
    };

    /**
     * @class ZeroDivisionException
     * @brief custom exception for division by zero.
     */
    class ZeroDivisionException : public std::runtime_error
    {
    public:
        ZeroDivisionException(const BigInteger &dividend, const BigInteger &divisor);
    };

}

#undef string
#endif