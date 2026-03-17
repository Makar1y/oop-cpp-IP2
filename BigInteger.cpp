#include <iostream>
#include <sstream>
#include <iomanip>
#include <exception>
#include <stdexcept>
#include <vector>

#include "BigInteger.h"
#include "DEBUG.h"

using std::string;

class BigIntegerData
{
private:
    long digits;
    struct BigIntegerData *next;
    struct BigIntegerData *previous;

public:
    BigIntegerData(long digits)
    {
        setAll(nullptr, nullptr, digits);
    }
    BigIntegerData(BigIntegerData *previous = nullptr, BigIntegerData *next = nullptr, long digits = 0)
    {
        setAll(previous, next, digits);
    }

    BigIntegerData *getNext() const
    {
        return next;
    }
    BigIntegerData *getPrevious() const
    {
        return previous;
    }
    long getDigits() const
    {
        return digits;
    }

    void createNext(BigIntegerData *previous, BigIntegerData *next, long digits)
    {
        this->next = new BigIntegerData(previous, next, digits);
    }
    void createPrevious()
    {
        this->previous = new BigIntegerData(previous, next, digits);
    }
    void setPrevious(BigIntegerData *previous)
    {
        this->previous = previous;
    }
    void setNext(BigIntegerData *next)
    {
        this->next = next;
    }
    void setDigits(long digits)
    {
        this->digits = digits;
    }

    void setAll(BigIntegerData *previous = nullptr, BigIntegerData *next = nullptr, long digits = 0)
    {
        setPrevious(previous);
        setNext(next);
        setDigits(digits);
    }
};

class BigInteger
{
private:
    bool sign;
    BigIntegerData *LowerDigits;
    BigIntegerData *HigherDigits;

public:
    BigInteger(const string &number = "")
    {
        stringToNum(number);
    }
    BigInteger(const BigInteger &other)
    {
        other.copy(*this);
    }
    BigInteger &operator=(const BigInteger &source)
    {
        if (this != &source)
        {
            source.copy(*this);
        }
        return *this;
    }
    ~BigInteger()
    {
        this->makeEmpty();
    }

    bool getSign() const
    {
        return this->sign;
    }

private:
    BigIntegerData *getLowerDigits() const
    {
        return this->LowerDigits;
    }

    BigIntegerData *getHigherDigits() const
    {
        return this->HigherDigits;
    }

public:
    void setSign(const bool sign)
    {
        this->sign = sign;
    }

private:
    void setLowerDigits(BigIntegerData *const LowerDigits)
    {
        this->LowerDigits = LowerDigits;
    }

    void setHigherDigits(BigIntegerData *const HigherDigits)
    {
        this->HigherDigits = HigherDigits;
    }

public:
    int stringToNum(const string &numberString)
    {
        size_t numLength = numberString.length();
        makeEmpty();
        setLowerDigits(new BigIntegerData());

        if (numberString[0] == '-')
        {
            setSign(true);
        }

        BigIntegerData *current = getLowerDigits();

        for (int i = numLength - 1, j = 0; i >= 0; --i, ++j)
        {
            if (j % BASE_POW == 0 && j != 0)
            {
                current->createNext(current, nullptr, 0);
                current = current->getNext();
            }

            char intChar = numberString[i] - 48;
            bool is_integer = (0 <= intChar) && (intChar <= 9);

            if (!is_integer)
            {
                throw std::invalid_argument("Non integer char found in input string.");
            }
            current->setDigits(current->getDigits() + intChar * this->pow(BASE, j % BASE_POW));
        }
        setHigherDigits(current);
        return 0;
    }

    string toString() const
    {
        std::stringstream result;

        if (!getHigherDigits())
        {
            result << 0;
            return result.str();
        }
        if (getSign())
        {
            result << "-";
        }

        BigIntegerData *current = getHigherDigits();
        while (current)
        {
            if (current == getHigherDigits())
            {
                result << current->getDigits();
            }
            else
            {
                result << std::setw(BASE) << std::setfill('0') << current->getDigits();
            }
            current = current->getPrevious();
        }
        return result.str();
    }

    int copy(BigInteger &dest) const
    {
        dest.makeEmpty();
        dest.setSign(getSign());

        BigIntegerData *currSRC = getLowerDigits();
        if (!currSRC)
        {
            dest.setLowerDigits(nullptr);
            dest.setHigherDigits(nullptr);
            return 0;
        }

        BigIntegerData *currDEST = new BigIntegerData(nullptr, nullptr, 0);
        dest.setLowerDigits(currDEST);

        while (currSRC)
        {
            currDEST->setDigits(currSRC->getDigits());

            if (currSRC->getNext())
            {
                currDEST->createNext(currDEST, nullptr, 0);
                currDEST = currDEST->getNext();
            }
            else
            {
                currSRC = currSRC->getNext();
            }
        }
        dest.setHigherDigits(currDEST);
        return 0;
    }

    int count() const
    {
        BigIntegerData *element = getLowerDigits();
        int counter = 0;

        while (element)
        {
            ++counter;
            element = element->getNext();
        }
        return counter;
    }

    void makeEmpty()
    {
        BigIntegerData *current = getLowerDigits();
        BigIntegerData *temp;

        this->sign = 0;

        while (current)
        {
            temp = current->getNext();
            delete current;
            current = temp;
        }
        setLowerDigits(nullptr);
        setHigherDigits(nullptr);
    }

    bool isEmpty() const
    {
        int result = count();
        if (result == 0)
        {
            return true;
        }
        return false;
    }

private:
    static long long pow(const int num, const int pow)
    {
        long long result = 1;
        for (int i = 0; i < pow; ++i)
        {
            result *= num;
        }
        return result;
    }

    int compare(const BigInteger &b) const
    {
        int countA = count(), countB = b.count();
        if (countA > countB)
            return 1;
        if (countA < countB)
            return -1;

        BigIntegerData *curA = getHigherDigits();
        BigIntegerData *curB = b.getHigherDigits();

        while (curA && curB)
        {
            if (curA->getDigits() > curB->getDigits())
                return 1;
            if (curB->getDigits() > curA->getDigits())
                return -1;
            curA = curA->getPrevious();
            curB = curB->getPrevious();
        }
        return 0;
    }

    void appendNode(BigInteger &rem, const long digits) const
    {
        if (rem.isEmpty() || (rem.count() == 1 && rem.getLowerDigits()->getDigits() == 0))
        {
            if (!rem.getLowerDigits())
            {
                rem.setLowerDigits(new BigIntegerData());
            }
            rem.getLowerDigits()->setDigits(digits);
            rem.setHigherDigits(rem.getLowerDigits());
            return;
        }

        BigIntegerData *newNode = new BigIntegerData(nullptr, rem.getLowerDigits(), digits);
        rem.getLowerDigits()->setPrevious(newNode);
        rem.setLowerDigits(newNode);
    }

    void trimLeadingZeros(BigInteger &num) const
    {
        while (num.getHigherDigits() && num.getHigherDigits()->getDigits() == 0 && num.getHigherDigits() != num.getLowerDigits())
        {
            BigIntegerData *tmp = num.getHigherDigits();
            num.setHigherDigits(num.getHigherDigits()->getPrevious());

            if (num.getHigherDigits())
                num.getHigherDigits()->setNext(nullptr);
            delete tmp;
        }
    }

    BigInteger addAbsolute(const BigInteger &a, const BigInteger &b) const
    {
        BigInteger res = BigInteger();
        BigIntegerData *curA = a.getLowerDigits(),
                       *curB = b.getLowerDigits(),
                       *lastNode = nullptr;
        long long carry = 0;
        long long limit = pow(BASE, BASE_POW);

        while (curA || curB || carry)
        {
            long long sum = carry + (curA ? curA->getDigits() : 0) + (curB ? curB->getDigits() : 0);
            carry = sum / limit;

            BigIntegerData *dataNode = new BigIntegerData(sum % limit);

            if (!res.getLowerDigits())
            {
                res.setLowerDigits(dataNode);
            }
            if (lastNode)
            {
                lastNode->setNext(dataNode);
                dataNode->setPrevious(lastNode);
            }
            lastNode = dataNode;

            if (curA)
            {
                curA = curA->getNext();
            }
            if (curB)
            {
                curB = curB->getNext();
            }
        }
        res.setHigherDigits(lastNode);
        return res;
    }

    BigInteger subAbsolute(const BigInteger &a, const BigInteger &b) const
    {
        BigInteger res = BigInteger();
        BigIntegerData *curA = a.getLowerDigits(),
                       *curB = b.getLowerDigits(),
                       *lastNode = nullptr;
        long long cary = 0;
        long long limit = pow(BASE, BASE_POW);

        while (curA)
        {
            long long valA = curA->getDigits();
            long long valB = curB ? curB->getDigits() : 0;
            long long difference = valA - valB - cary;

            if (difference < 0)
            {
                difference += limit;
                cary = 1;
            }
            else
            {
                cary = 0;
            }

            BigIntegerData *dataNode = new BigIntegerData(difference);

            if (!res.getLowerDigits())
            {
                res.setLowerDigits(dataNode);
            }
            if (lastNode)
            {
                lastNode->setNext(dataNode);
                dataNode->setPrevious(lastNode);
            }
            lastNode = dataNode;

            curA = curA->getNext();
            if (curB)
            {
                curB = curB->getNext();
            }
        }
        res.setHigherDigits(lastNode);

        while (res.getHigherDigits() && res.getHigherDigits()->getDigits() == 0 && res.getHigherDigits() != res.getLowerDigits())
        {
            res.setHigherDigits(res.getHigherDigits()->getPrevious());
            delete res.getHigherDigits()->getNext();
            res.getHigherDigits()->setNext(nullptr);
        }
        return res;
    }

    BigInteger multiply(const BigInteger &a, const BigInteger &b) const
    {

        int countA = a.count(),
            countB = b.count();

        if (countA == 0 || countB == 0)
        {
            return BigInteger();
        }

        std::vector<unsigned long long> aDigits;
        aDigits.reserve(countA);
        std::vector<unsigned long long> bDigits;
        bDigits.reserve(countB);

        BigIntegerData *cur = a.getLowerDigits();
        for (int i = 0; i < countA; ++i)
        {
            aDigits[i] = (unsigned long long)cur->getDigits();
            cur = cur->getNext();
        }
        cur = b.getLowerDigits();
        for (int i = 0; i < countB; ++i)
        {
            bDigits[i] = (unsigned long long)cur->getDigits();
            cur = cur->getNext();
        }

        int resSize = countA + countB;
        std::vector<unsigned long long> resDigits;
        resDigits.reserve(resSize);

        // multiplication
        for (int i = 0; i < countA; ++i)
        {
            for (int j = 0; j < countB; ++j)
            {
                resDigits[i + j] += aDigits[i] * bDigits[j];
            }
        }

        unsigned long long basePow = pow(BASE, BASE_POW);

        // carries
        for (int i = 0; i < resSize; ++i)
        {
            unsigned long long carry = resDigits[i] / basePow;
            resDigits[i] = resDigits[i] % basePow;
            if (carry)
            {
                if (i + 1 >= resSize)
                {
                    resDigits.push_back(carry);
                    ++resSize;
                }
                else
                {
                    resDigits[i + 1] += carry;
                }
            }
        }

        int highestNonZero = resSize - 1;
        while (highestNonZero > 0 && resDigits[highestNonZero] == 0)
            --highestNonZero;

        BigInteger result = BigInteger();

        // remove zeros
        BigIntegerData *tmp = nullptr;
        for (int i = 0; i <= highestNonZero; ++i)
        {
            cur = new BigIntegerData(tmp, nullptr, (long)resDigits[i]);
            if (!result.getLowerDigits())
            {
                result.setLowerDigits(cur);
            }
            if (tmp)
            {
                tmp->setNext(cur);
            }
            tmp = cur;
        }

        result.setHigherDigits(cur);
        result.setSign(a.getSign() == b.getSign() ? false : true);
        return result;
    }

    BigInteger multiply(const BigInteger &a, const long b) const
    {
        BigInteger res = BigInteger();
        if (b == 0)
        {
            return res;
        }
        bool isNegative = b < 0;
        res.setSign(res.getSign() == isNegative ? false : true);
        long bCopy = isNegative ? -b : b;

        BigIntegerData *curA = a.getLowerDigits(),
                       *prev = nullptr;

        unsigned long long carry = 0;
        long limit = pow(BASE, BASE_POW);

        while (curA || carry)
        {
            unsigned long long val = carry + (unsigned long long)(curA ? curA->getDigits() : 0) * bCopy;
            carry = val / limit;

            BigIntegerData *node = new BigIntegerData((long)(val % limit));
            if (!res.getLowerDigits())
                res.setLowerDigits(node);
            if (prev)
            {
                prev->setNext(node);
                node->setPrevious(prev);
            }
            prev = node;
            if (curA)
            {
                curA = curA->getNext();
            }
        }
        res.setHigherDigits(prev);
        return res;
    }

    BigInteger divide(const BigInteger &a, const BigInteger &b, const bool returnReminder) const
    {
        if (a < b)
        {
            if (returnReminder)
            {
                return BigInteger(a);
            }
            return BigInteger();
        }
        if (a.isEmpty() || a.getHigherDigits()->getDigits() == 0)
        {
            return BigInteger();
        }
        if (b.count() == 1 && b.getHigherDigits()->getDigits() == 1)
        {
            if (returnReminder)
            {
                return BigInteger();
            }
            return BigInteger(a);
        }

        BigInteger quotient = BigInteger();
        BigInteger remainder = BigInteger();
        BigIntegerData *curA = a.getHigherDigits();

        while (curA)
        {
            appendNode(remainder, curA->getDigits());
            trimLeadingZeros(remainder);

            long low = 0,
                 high = pow(BASE, BASE_POW) - 1,
                 q = 0;

            while (low <= high)
            {
                long mid = low + (high - low) / 2;
                BigInteger test = a.multiply(b, mid);

                if (test <= remainder)
                {
                    q = mid;
                    low = mid + 1;
                }
                else
                {
                    high = mid - 1;
                }
            }

            // Update reminder
            BigInteger qb = a.multiply(b, q);
            BigInteger nextRem = subAbsolute(remainder, qb);
            remainder = nextRem;

            appendNode(quotient, q);
            curA = curA->getPrevious();
        }

        if (returnReminder)
        {
            trimLeadingZeros(remainder);
            remainder.setSign((remainder.count() == 1 && remainder.getHigherDigits()->getDigits() == 0) || remainder.isEmpty() ? false : a.getSign());
            return remainder;
        }

        trimLeadingZeros(quotient);
        quotient.setSign((quotient.count() == 1 && quotient.getHigherDigits()->getDigits() == 0) || quotient.isEmpty() ? false : a.getSign() != b.getSign());
        return quotient;
    }

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

void operator+=(BigInteger &dest, const BigInteger &src)
{
    dest = dest + src;
}

BigInteger &operator-=(BigInteger &dest, const BigInteger &src)
{
    dest = dest - src;
}

BigInteger &operator*=(BigInteger &dest, const BigInteger &src)
{
    dest = dest * src;
}

BigInteger &operator/=(BigInteger &dest, const BigInteger &src)
{
    dest = dest / src;
}

BigInteger &operator%=(BigInteger &dest, const BigInteger &src)
{
    dest = dest % src;
}

BigInteger operator+(const BigInteger &a, const BigInteger &b)
{
    BigInteger res;
    if (a.getSign() == b.getSign())
    {
        res = a.addAbsolute(a, b);
        res.setSign(a.getSign());
    }
    else
    {
        int cmp = a.compare(b);
        if (cmp == 0)
        {
            res = BigInteger();
        }

        if (cmp > 0)
        {
            res = a.subAbsolute(a, b);
            res.setSign(a.getSign());
        }
        else
        {
            res = a.subAbsolute(b, a);
            res.setSign(b.getSign());
        }
    }
    return res;
}

BigInteger operator-(const BigInteger &a, const BigInteger &b)
{
    return a + (-b);
}

BigInteger operator-(const BigInteger &a)
{
    BigInteger res = BigInteger(a);
    res.setSign(!a.getSign());
    return res;
}

BigInteger operator*(const BigInteger &a, const BigInteger &b)
{
    return a.multiply(a, b);
}

BigInteger operator/(const BigInteger &a, const BigInteger &b)
{
    if (b.isEmpty() || b.getHigherDigits()->getDigits() == 0)
    {
        throw std::runtime_error("Zero division error.\n");
    }
    return a.divide(a, b, false);
}

BigInteger operator%(const BigInteger &a, const BigInteger &b)
{
    if (b.isEmpty() || b.getHigherDigits()->getDigits() == 0)
    {
        throw std::runtime_error("Zero division error.\n");
    }
    return a.divide(a, b, true);
}

bool operator==(const BigInteger &a, const BigInteger &b)
{
    if (&a != &b)
    {
        return !(bool)a.compare(b);
    }
    return 1;
}

bool operator!=(const BigInteger &a, const BigInteger &b)
{
    if (&a != &b)
    {
        return (bool)a.compare(b);
    }
    return 0;
}

bool operator<(const BigInteger &a, const BigInteger &b)
{
    if (&a != &b)
    {
        return a.compare(b) == -1;
    }
    return 0;
}

bool operator<=(const BigInteger &a, const BigInteger &b)
{
    if (&a != &b)
    {
        return a.compare(b) <= 0;
    }
    return 1;
}

bool operator>=(const BigInteger &a, const BigInteger &b)
{
    if (&a != &b)
    {
        return a.compare(b) >= 0;
    }
    return 1;
}

bool operator>(const BigInteger &a, const BigInteger &b)
{
    if (&a != &b)
    {
        return a.compare(b) == 1;
    }
    return 0;
}

std::ostream &operator<<(std::ostream &out, const BigInteger &a)
{
    out << a.toString();
    return out;
}

std::istream &operator>>(std::istream &in, BigInteger &a)
{
    string num;
    in >> num;
    a.stringToNum(num);
    if (in.fail())
    {
        throw std::ios_base::failure("Number input failure.");
    }
    return in;
}
