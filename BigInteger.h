#ifndef BigInteger_h
#define BigInteger_h

#define BASE 10
#define BASE_POW 9

/*
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!! Using functions that returns and accepts BigInteger* types with same         !!!
!!! BigInteger* for argument and return value will lead to a memory leak.        !!!
!!! For example:                                                                 !!!
!!!    a = BigIntegerAdd(a, b); lead to memory leak(loosing original a pointer). !!!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/


/// @brief Creates a new empty BigInteger
/// @retval `BigInteger*` to newly allocated BigInteger
/// @retval `NULL` on failure
BigInteger* Create();

/// @brief Returns the number of digit nodes in a BigInteger
/// @param ADT BigInteger to count
/// @retval Number of digit nodes
/// @retval `-1` if ADT is NULL
int count(BigInteger* ADT);

/// @brief Checks if a BigInteger is empty (zero)
/// @param ADT BigInteger to check
/// @retval `1` (true) if empty or ADT is NULL
/// @retval `0` (false) otherwise
int isEmpty(BigInteger* ADT);

/// @brief Checks if a BigInteger is full (always returns false for dynamic structure)
/// @param ADT BigInteger to check
/// @retval `0` (false) always
int isFull(BigInteger* ADT);

/// @brief Converts a BigInteger to its string representation
/// @param ADT BigInteger to convert
/// @retval Dynamically allocated string representation (caller must free)
/// @retval `NULL` if ADT is NULL or allocation error
char* toString(BigInteger* ADT);

/// @brief Creates a copy of a BigInteger
/// @param src_ADT Source BigInteger to clone
/// @retval `BigInteger*` to newly allocated clone
/// @retval `NULL` if src_ADT is NULL or allocation fails
BigInteger* clone(BigInteger* src_ADT);

/// @brief Copies the contents of one BigInteger to another
/// @param src_ADT Source BigInteger
/// @param dst_ADT Destination BigInteger (will be cleared and overwritten)
/// @retval `0` on success
/// @retval `-1` if either parameter is NULL
/// @retval `-2` or `-3` on memory allocation failure
int copy(BigInteger* src_ADT, BigInteger* dst_ADT);

/// @brief Clears all data from a BigInteger, making it empty (zero)
/// @param ADT BigInteger to clear
/// @retval `0` on success
/// @retval `-1` if ADT is NULL
int makeEmpty(BigInteger* ADT);

/// @brief Deallocates all memory associated with a BigInteger and sets pointer to NULL
/// @param ptr_to_ADT Pointer to BigInteger pointer to be freed
/// @retval `0` on success
/// @retval `-1` if ptr_to_ADT is NULL or points to NULL
int Done(BigInteger** ptr_to_ADT);

/// @brief Parses a string and writes the number in a BigInteger
/// @param number_string String representation of number (format: optional '-' followed by digits)
/// @param ADT BigInteger to write the parsed number
/// @retval `0` on success
/// @retval `-1` if either parameter is NULL
/// @retval `-2` or `-3` on memory allocation failure
/// @retval `-4` if string contains non-digit characters (excluding leading '-')
int stringToBigInteger(char* number_string, BigInteger* ADT);

/// @brief Compares two BigIntegers numerically
/// @param a First BigInteger
/// @param b Second BigInteger
/// @retval `1` if a > b
/// @retval `-1` if a < b
/// @retval `0` if a == b
int compareADTs(BigInteger* a, BigInteger* b);

/// @brief Adds two BigIntegers (a + b)
/// @param a First operand
/// @param b Second operand
/// @retval `BigInteger*` to newly allocated result
/// @retval `NULL` if either parameter is NULL
BigInteger* BigIntegerAdd(BigInteger* a, BigInteger* b);

/// @brief Subtracts two BigIntegers (a - b)
/// @param a First operand
/// @param b Second operand
/// @retval `BigInteger*` to newly allocated result
/// @retval `NULL` if either parameter is NULL
BigInteger* BigIntegerSub(BigInteger* a, BigInteger* b);

/// @brief Multiplies two BigIntegers (a * b)
/// @param a First operand (multiplicand)
/// @param b Second operand (multiplier)
/// @retval `BigInteger*` to newly allocated result
/// @retval `NULL` if either parameter is NULL or memory allocation fails
BigInteger* BigIntegerMul(BigInteger* a, BigInteger* b);

/// @brief Divides two BigIntegers with integer division (a / b)
/// @param a First operand (dividend)
/// @param b Second operand (divisor)
/// @retval `BigInteger*` to newly allocated quotient result
/// @retval `NULL` if a or b is NULL, or if b is zero
BigInteger* BigIntegerDiv(BigInteger* a, BigInteger* b);

/// @brief Computes modulo operation (a % b)
/// @param a First operand (dividend)
/// @param b Second operand (divisor)
/// @retval `BigInteger*` to newly allocated remainder result
/// @retval `NULL` if a or b is NULL, or if b is zero
BigInteger* BigIntegerMod(BigInteger* a, BigInteger* b);

/// @brief Multiplies a BigInteger by a long integer
/// @param a BigInteger to multiply
/// @param b Long integer multiplier
/// @retval `BigInteger*` to newly allocated result
/// @retval `NULL` if a is NULL or memory allocation fails
BigInteger* mulByLong(BigInteger* a, long b);
#endif