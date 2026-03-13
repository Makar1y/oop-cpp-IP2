#include <iostream>
#include <sstream>
#include <iomanip>
#include <exception>
#include <stdexcept>

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

    static long long pow(const int num, const int pow)
    {
        long long result = 1;
        for (int i = 0; i < pow; ++i)
        {
            result *= num;
        }
        return result;
    }

    BigInteger &operator=(const BigInteger &source)
    {
        if (this != &source)
        {
            source.copy(*this);
        }
        return *this;
    }

    BigInteger &operator+=(const BigInteger &source)
    {
        addAbsolute(*this, source).copy(*this);
        return *this;
    }

    BigInteger &operator-=(const BigInteger &source)
    {
    }

    BigInteger &operator*=(const BigInteger &source)
    {
    }

    BigInteger &operator/=(const BigInteger &source)
    {
    }

    BigInteger &operator%=(const BigInteger &source)
    {
    }

    BigInteger operator+(const BigInteger &b) const
    {
        BigInteger res;
        if (getSign() == b.getSign())
        {
            res = addAbsolute(*this, b);
            res.setSign(getSign());
        }
        else
        {
            int cmp = compare(b);
            if (cmp == 0)
            {
                res = BigInteger();
            }

            if (cmp > 0)
            {
                res = subAbsolute(*this, b);
                res.setSign(this->getSign());
            }
            else
            {
                res = subAbsolute(b, *this);
                res.setSign(b.getSign());
            }
        }
        return res;
    }

    BigInteger operator-(const BigInteger &source) const
    {
    }

    BigInteger operator*(const BigInteger &source) const
    {
    }

    BigInteger operator/(const BigInteger &source) const
    {
    }

    BigInteger operator%(const BigInteger &source) const
    {
    }

    bool operator==(const BigInteger &b) const
    {
        if (this != &b)
        {
            return !(bool)compare(b);
        }
        return 1;
    }

    bool operator!=(const BigInteger &b) const
    {
        if (this != &b)
        {
            return (bool)compare(b);
        }
        return 0;
    }

    bool operator<(const BigInteger &b) const
    {
        if (this != &b)
        {
            return compare(b) == -1;
        }
        return 0;
    }

    bool operator<=(const BigInteger &b) const
    {
        if (this != &b)
        {
            return compare(b) <= 0;
        }
        return 1;
    }

    bool operator>=(const BigInteger &b) const
    {
        if (this != &b)
        {
            return compare(b) >= 0;
        }
        return 1;
    }

    bool operator>(const BigInteger &b) const
    {
        if (this != &b)
        {
            return compare(b) == 1;
        }
        return 0;
    }

private:
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
};









BigInteger *clone(BigInteger *src)
{
    if (NULL != src)
    {
        BigInteger *dest = Create();
        if (copy(src, dest) < 0)
        {
            Done(&dest);
            return NULL;
        }
        return dest;
    }
    return NULL;
}

BigInteger *BigIntegerSub(BigInteger *a, BigInteger *b)
{
    if (!a || !b)
        return NULL;

    int originalSignB = b->sign;
    b->sign = (originalSignB == 0) ? 1 : 0;

    BigInteger *res = BigIntegerAdd(a, b);

    b->sign = originalSignB;
    return res;
}

BigInteger *BigIntegerMul(BigInteger *a, BigInteger *b)
{
    if (NULL == a || NULL == b)
    {
        return NULL;
    }

    int countA = count(a), countB = count(b);

    if (countA == 0 || countB == 0)
    {
        BigInteger *zero = Create();
        if (zero)
        {
            zero->LowerDigits = calloc(1, sizeof(BigIntegerData));
            if (zero->LowerDigits)
                zero->HigherDigits = zero->LowerDigits;
        }
        return zero;
    }

    unsigned long long *aDigits = calloc(countA, sizeof(unsigned long long));
    unsigned long long *bDigits = calloc(countB, sizeof(unsigned long long));
    if (!aDigits || !bDigits)
    {
        free(aDigits);
        free(bDigits);
        return NULL;
    }

    BigIntegerData *cur = a->LowerDigits;
    for (int i = 0; i < countA; ++i)
    {
        aDigits[i] = (unsigned long long)cur->digits;
        cur = cur->next;
    }
    cur = b->LowerDigits;
    for (int i = 0; i < countB; ++i)
    {
        bDigits[i] = (unsigned long long)cur->digits;
        cur = cur->next;
    }

    int resSize = countA + countB;
    unsigned long long *resDigits = calloc(resSize, sizeof(unsigned long long));
    if (!resDigits)
    {
        free(aDigits);
        free(bDigits);
        return NULL;
    }

    // multiplication
    for (int i = 0; i < countA; ++i)
    {
        for (int j = 0; j < countB; ++j)
        {
            resDigits[i + j] += aDigits[i] * bDigits[j];
        }
    }

    unsigned long long basePow = myPow(BASE, BASE_POW);

    // carries
    for (int i = 0; i < resSize; ++i)
    {
        unsigned long long carry = resDigits[i] / basePow;
        resDigits[i] = resDigits[i] % basePow;
        if (carry)
        {
            if (i + 1 >= resSize)
            {
                int newSize = resSize + 1;
                unsigned long long *tmp = realloc(resDigits, newSize * sizeof(unsigned long long));
                if (!tmp)
                {
                    free(aDigits);
                    free(bDigits);
                    free(resDigits);
                    return NULL;
                }
                resDigits = tmp;
                resDigits[resSize] = 0;
                resSize = newSize;
            }
            resDigits[i + 1] += carry;
        }
    }

    int highestNonZero = resSize - 1;
    while (highestNonZero > 0 && resDigits[highestNonZero] == 0)
        --highestNonZero;

    BigInteger *result = Create();
    if (!result)
    {
        free(aDigits);
        free(bDigits);
        free(resDigits);
        return NULL;
    }

    // remove zeros
    BigIntegerData *tmp = NULL;
    for (int i = 0; i <= highestNonZero; ++i)
    {
        cur = calloc(1, sizeof(BigIntegerData));
        if (!result->LowerDigits)
        {
            result->LowerDigits = cur;
        }
        if (!cur)
        {
            Done(&result);
            free(aDigits);
            free(bDigits);
            free(resDigits);
            return NULL;
        }
        cur->digits = (long)resDigits[i];
        cur->previous = tmp;
        cur->next = NULL;
        if (tmp)
        {
            tmp->next = cur;
        }
        tmp = cur;
    }
    result->HigherDigits = cur;

    result->sign = (a->sign + b->sign) % 2;

    free(aDigits);
    free(bDigits);
    free(resDigits);
    return result;
}

BigInteger *mulByLong(BigInteger *a, long b)
{
    if (b == 0)
        return Create();
    BigInteger *res = Create();
    BigIntegerData *curA = a->LowerDigits, *prev = NULL;
    unsigned long long carry = 0;
    long limit = myPow(BASE, BASE_POW);

    while (curA || carry)
    {
        unsigned long long val = carry + (unsigned long long)(curA ? curA->digits : 0) * b;
        carry = val / limit;

        BigIntegerData *node = calloc(1, sizeof(BigIntegerData));
        node->digits = (long)(val % limit);
        if (!res->LowerDigits)
            res->LowerDigits = node;
        if (prev)
        {
            prev->next = node;
            node->previous = prev;
        }
        prev = node;
        if (curA)
        {
            curA = curA->next;
        }
    }
    res->HigherDigits = prev;
    return res;
}

void trimLeadingZeros(BigInteger *ADT)
{
    while (ADT->HigherDigits && ADT->HigherDigits->digits == 0 && ADT->HigherDigits != ADT->LowerDigits)
    {
        BigIntegerData *tmp = ADT->HigherDigits;
        ADT->HigherDigits = ADT->HigherDigits->previous;
        if (ADT->HigherDigits)
            ADT->HigherDigits->next = NULL;
        free(tmp);
    }
}

int appendNode(BigInteger *rem, long digits)
{
    if (isEmpty(rem) || (count(rem) == 1 && rem->LowerDigits->digits == 0))
    {
        if (!rem->LowerDigits)
        {
            rem->LowerDigits = calloc(1, sizeof(BigIntegerData));
            if (!rem->LowerDigits)
            {
                return -2;
            }
        }
        rem->LowerDigits->digits = digits;
        rem->HigherDigits = rem->LowerDigits;
        return 0;
    }

    BigIntegerData *newNode = calloc(1, sizeof(BigIntegerData));
    if (newNode)
    {
        newNode->digits = digits;
        newNode->next = rem->LowerDigits;
        rem->LowerDigits->previous = newNode;
        rem->LowerDigits = newNode;
        return 0;
    }
    return -1;
}

BigInteger *_div(BigInteger *a, BigInteger *b, int returnReminder)
{
    if (compareADTs(a, b) == -1)
    {
        if (returnReminder)
        {
            return clone(a);
        }
        return Create();
    }
    if (isEmpty(a) || a->HigherDigits->digits == 0)
    {
        return Create();
    }
    if (count(b) == 1 && b->HigherDigits->digits == 1)
    {
        if (returnReminder)
        {
            return Create();
        }
        return clone(a);
    }

    BigInteger *quotient = Create();
    BigInteger *remainder = Create();
    BigIntegerData *curA = a->HigherDigits;

    while (curA)
    {
        appendNode(remainder, curA->digits);
        trimLeadingZeros(remainder);

        long low = 0,
             high = myPow(BASE, BASE_POW) - 1,
             q = 0;

        while (low <= high)
        {
            long mid = low + (high - low) / 2;
            BigInteger *test = mulByLong(b, mid);

            if (compareADTs(test, remainder) <= 0)
            {
                q = mid;
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
            Done(&test);
        }

        // Update reminder
        BigInteger *qb = mulByLong(b, q);
        BigInteger *nextRem = subAbsolute(remainder, qb);
        copy(nextRem, remainder);

        appendNode(quotient, q);

        Done(&qb);
        Done(&nextRem);
        curA = curA->previous;
    }

    if (returnReminder)
    {
        Done(&quotient);
        remainder->sign = !(count(remainder) == 1 && remainder->HigherDigits->digits == 0) ? a->sign : 0;
        trimLeadingZeros(remainder);
        return remainder;
    }

    Done(&remainder);
    quotient->sign = !(count(quotient) == 1 && quotient->HigherDigits->digits == 0) ? a->sign != b->sign : 0;
    trimLeadingZeros(quotient);
    return quotient;
}

BigInteger *BigIntegerDiv(BigInteger *a, BigInteger *b)
{
    if (!a || !b || isEmpty(b) || b->HigherDigits->digits == 0)
    {
        return NULL;
    }
    return _div(a, b, 0);
}

BigInteger *BigIntegerMod(BigInteger *a, BigInteger *b)
{
    if (!a || !b || isEmpty(b) || b->HigherDigits->digits == 0)
    {
        return NULL;
    }
    return _div(a, b, 1);
}
