#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "BigInteger.h"

using namespace BigInt;

class TestLogger
{
private:
    std::ofstream logFile;

public:
    TestLogger(const std::string &filename)
    {
        logFile.open(filename);
    }

    ~TestLogger()
    {
        if (logFile.is_open())
        {
            logFile.close();
        }
    }

    void log(const std::string &message)
    {
        std::cout << message << std::endl;
        if (logFile.is_open())
        {
            logFile << message << std::endl;
        }
    }
};

TestLogger logger("log.txt");

void report(bool passed, const std::string &testName, const std::string &details = "")
{
    std::string result = passed ? "PASS" : "FAIL";
    logger.log("Test [" + testName + "]: " + details + " ... " + result);
}

void testBasic()
{
    logger.log("--- Starting Basic Tests ---");
    BigInteger a("100");
    report(a.toString() == "100", "Constructor", "val=100");

    BigInteger b;
    report(b.isZero(), "Default Constructor", "val=0");

    BigInteger c("-50");
    report(c.getSign(), "Negative Sign", "val=-50");

    c.setSign(false);
    report(!c.getSign() && c.toString() == "50", "setSign", "changed -50 to 50");
}

void testArithmetic()
{
    logger.log("--- Starting Arithmetic Tests ---");
    BigInteger a("10"), b("20");

    report((a + b).toString() == "30", "Addition", "10 + 20 = 30");
    report((b - a).toString() == "10", "Subtraction", "20 - 10 = 10");
    report((a * b).toString() == "200", "Multiplication", "10 * 20 = 200");
    report((b / a).toString() == "2", "Division", "20 / 10 = 2");
    report((b % BigInteger("3")).toString() == "2", "Modulo", "20 % 3 = 2");

    BigInteger d("5");
    d += BigInteger("5");
    report(d.toString() == "10", "operator+=", "5 += 5");

    d -= BigInteger("3");
    report(d.toString() == "7", "operator-=", "10 -= 3");

    d *= BigInteger("2");
    report(d.toString() == "14", "operator*=", "7 *= 2");

    d /= BigInteger("2");
    report(d.toString() == "7", "operator/=", "14 /= 2");

    d %= BigInteger("4");
    report(d.toString() == "3", "operator%=", "7 %= 4");
}

void testComparison()
{
    logger.log("--- Starting Comparison Tests ---");
    BigInteger a("10"), b("20"), c("10");

    report(a == c, "Equality", "10 == 10");
    report(a != b, "Inequality", "10 != 20");
    report(a < b, "Less Than", "10 < 20");
    report(a <= b, "Less Than or Equal", "10 <= 20");
    report(b > a, "Greater Than", "20 > 10");
    report(b >= a, "Greater Than or Equal", "20 >= 10");
}

void testIncrements()
{
    logger.log("--- Starting Increment Tests ---");
    BigInteger a("10");
    ++a;
    report(a.toString() == "11", "Prefix Increment", "++10 = 11");
    --a;
    report(a.toString() == "10", "Prefix Decrement", "--11 = 10");
}

void testLargeNumbers()
{
    logger.log("--- Starting Large Number Tests ---");
    std::string largeStr = "1234567890123456789012345678901234567890";
    BigInteger a(largeStr);
    report(a.toString() == largeStr, "Large String Input", "40 digits");

    BigInteger b("2");
    BigInteger c = a * b;
    report(c.toString() == "2469135780246913578024691357802469135780", "Large Multiplication", "a * 2");
}

void testEdgeCases()
{
    logger.log("--- Starting Edge Case Tests ---");
    BigInteger zero("0");
    BigInteger one("1");
    BigInteger negOne("-1");

    report(zero.isZero(), "isZero for '0'", "yes");
    report(!one.isZero(), "isZero for '1'", "no");

    BigInteger empty;
    report(empty.isEmpty(), "isEmpty for default", "yes");

    try
    {
        BigInteger res = one / zero;
        report(false, "Division by Zero Exception", "No exception caught");
    }
    catch (const ZeroDivisionException &e)
    {
        report(true, "Division by Zero Exception", "Caught correctly");
    }
}

int main()
{
    logger.log("========================================");
    logger.log("   BIGINTEGER UNIT TEST SUITE");
    logger.log("========================================");

    testBasic();
    testArithmetic();
    testComparison();
    testIncrements();
    testLargeNumbers();
    testEdgeCases();

    logger.log("--- Finalizing Reports ---");
    logger.log("Verification of toString formatting...");
    for (int i = 0; i < 5; ++i)
    {
        std::string num = std::to_string(i * 1000);
        BigInteger temp(num);
        report(temp.toString() == num, "toString loop", "num=" + num);
    }

    logger.log("========================================");
    logger.log("Test execution finished.");
    logger.log("Output saved to log.txt");
    logger.log("========================================");

    return 0;
}
