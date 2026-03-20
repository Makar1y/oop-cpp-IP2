#include <iostream>
#include <cassert>
#include <string>
#include "BigInteger.h"

using namespace BigInt;

// Helper to check BigInteger against a string
void check(const BigInteger& val, const std::string& expected, const std::string& msg) {
    if (val.toString() != expected) {
        std::cerr << "TEST FAILED: " << msg << "\n"
                  << "  Expected: " << expected << "\n"
                  << "  Got:      " << val.toString() << std::endl;
        assert(false);
    }
}

void testConstructors() {
    std::cout << "Testing Constructors..." << std::endl;
    BigInteger a("1234567890123456789012345678901234567890");
    check(a, "1234567890123456789012345678901234567890", "Large string constructor");

    BigInteger b("-9876543210987654321098765432109876543210");
    check(b, "-9876543210987654321098765432109876543210", "Large negative string constructor");

    BigInteger c;
    check(c, "0", "Default constructor");

    BigInteger d(a);
    check(d, "1234567890123456789012345678901234567890", "Copy constructor");
    
    BigInteger e = b;
    check(e, "-9876543210987654321098765432109876543210", "Assignment operator");
}

void testRelationalOperators() {
    std::cout << "Testing Relational Operators..." << std::endl;
    BigInteger a("1234567890123456789012345678901234567890");
    BigInteger b("1234567890123456789012345678901234567891");
    BigInteger c("-50000000000000000000000000000000000000000");
    BigInteger d("1234567890123456789012345678901234567890");

    assert(a == d);
    assert(a != b);
    assert(a < b);
    assert(a <= d);
    assert(b > a);
    assert(b >= d);
    assert(c < a);
    assert(c <= b);
}

void testIncrements() {
    std::cout << "Testing Increments..." << std::endl;
    BigInteger a("9999999999999999999999999999999999999999");
    check(++a, "10000000000000000000000000000000000000000", "Prefix increment");

    BigInteger b("10000000000000000000000000000000000000000");
    check(--b, "9999999999999999999999999999999999999999", "Prefix decrement");
}

void testBigNumbersAddition() {
    std::cout << "Testing Big Number Addition..." << std::endl;
    BigInteger a("1234567890123456789012345678901234567890");
    BigInteger b("9876543210987654321098765432109876543210");
    // Expected: 11111111101111111110111111111011111111100
    check(a + b, "11111111101111111110111111111011111111100", "Simple big addition");

    BigInteger c("999999999999999999999999999999999999");
    BigInteger d("1");
    check(c + d, "1000000000000000000000000000000000000", "Carry across multiple nodes");
}

void testBigNumbersSubtraction() {
    std::cout << "Testing Big Number Subtraction..." << std::endl;
    BigInteger a("1000000000000000000000000000000000000");
    BigInteger b("1");
    check(a - b, "999999999999999999999999999999999999", "Borrow across multiple nodes");

    BigInteger c("1234567890123456789012345678901234567890");
    BigInteger d("987654321098765432109876543210987654321");
    check(c - d, "246913569024691356902469135690246913569", "Big subtraction with different lengths");
}

void testBigNumbersMultiplication() {
    std::cout << "Testing Big Number Multiplication..." << std::endl;
    // (10^20) * (10^20) = 10^40
    BigInteger a("100000000000000000000"); // 10^20
    check(a * a, "10000000000000000000000000000000000000000", "Multiplication power of 10");

    BigInteger b("1234567890123456789");
    BigInteger c("9876543210987654321");
    // Result: 12193263113702179522374638011112635269
    check(b * c, "12193263113702179522374638011112635269", "Big number multiplication");
}

void testBigNumbersDivision() {
    std::cout << "Testing Big Number Division..." << std::endl;
    BigInteger a("12193263113702179522374638011112635269");
    BigInteger b("1234567890123456789");
    check(a / b, "9876543210987654321", "Big number division");

    BigInteger c("1000000000000000000000000000000000000");
    BigInteger d("3");
    // 333333333333333333333333333333333333
    check(c / d, "333333333333333333333333333333333333", "Big number division by small constant");
}

void testBigNumbersModulo() {
    std::cout << "Testing Big Number Modulo..." << std::endl;
    BigInteger a("1000000000000000000000000000000000001");
    BigInteger b("1000000000000000000");
    check(a % b, "1", "Big number modulo");
}

void testMixedSigns() {
    std::cout << "Testing Big Number Mixed Signs..." << std::endl;
    BigInteger a("-1234567890123456789012345678901234567890");
    BigInteger b("1234567890123456789012345678901234567891");
    check(a + b, "1", "Negative + Positive");
    check(b + a, "1", "Positive + Negative");
    check(a - b, "-2469135780246913578024691357802469135781", "Negative - Positive");
}

int main() {
    std::cout << "Running Big Number Unit Tests..." << std::endl;

    testConstructors();
    testRelationalOperators();
    testBigNumbersAddition();
    testBigNumbersSubtraction();
    testBigNumbersMultiplication();
    testBigNumbersDivision();
    testBigNumbersModulo();
    testIncrements();
    testMixedSigns();

    std::cout << "\nAll Big Number tests passed!" << std::endl;
    return 0;
}
