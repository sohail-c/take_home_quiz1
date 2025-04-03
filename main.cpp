#include <iostream>
using namespace std;


/*
 *
 *      Question #1: Powers of Two
 *
 *
 */
bool is_power_of_two(int num) {
    return ((num & (num - 1)) == 0) && (num > 0);
    // find some way to implement binary in this. know that if pow of 2 binary representation of number will always be in form:
    // 1000 / 10...000 / 10000...00000 (leading left digit will be a 1 and everything to the right of it will be a zero
    // also means that [ (2^n) & ((2^n) -1) ] == 0
    // e.g., 16 is 10000 while 15 is 01111
    // bitwise and compares respective bits and returns 1 at the position only if bits are both 1 so this would return 0
    // this also means that [ (a non power of two) & (a non power of two - 1) ] not equal 0
    // e.g., 15 is 01111 while 14 is 01110 so 15 & 14 would equal 14
    //      01111
    //      01110
    //      -----
    //      01110
    // Resource: https://www.programiz.com/cpp-programming/bitwise-operators
    // also add num > 0 condition because a power of two by definition has to be > 0
}
bool is_power_of_two_loop(int num) {
    // convert to binary - use that to check whether pow of 2
    if (num == 0 | num == 1) {
        return true;
    }
    else if (num % 2 == 0) {
        num = num / 2;
        return is_power_of_two_loop(num);
    }
    else {
        return false;
    }
}
// test for false negatives
void test_powers_of_two_fn() {
    int test;
    printf("Testing is_power_of_two (or is_power_of_two_loop) Function: \n");
    printf("\tTesting even powers of 2 up to 2^29:\n");
    bool flag = true;
    for (int i = 0; i < 30; i++) {
        test = pow(2,i);
        bool result = is_power_of_two_loop(test);
        if (result == false) {
            flag == false;
            printf("\t\tFAILS on %d\n", test);
            break;
        }
    }
    if (flag == true) {
        printf("\t\tPASS\n");
    }
}
// test for false positives
void test_powers_of_two_fp() {
    // since odd numbers can't be powers of 2, generate some # of odds numbers and make sure no false positives
    // / that the function doesn't think they are powers of two
    int test;
    printf("\tTesting for false positives (3^1 up to 3^29): \n");
    bool flag = false;
    for (int i = 1; i < 30; i++) {
        test = pow(3,i);
        bool result = is_power_of_two_loop(test);
        if (result == true) {
            flag == false;
            printf("\t\tFAILS on %d\n", test);
            break;
        }
    }
    if (flag == false) {
        printf("\t\tPASS\n");
    }
}


/*
 *
 *      Question #2: Checking if a number is a prime number
 *
 *      Resources Used:
 *          Used trial division to determine whether a number is a prime. Resources used include Wikipedia to understand why
 *          the trial division of determining whether a number is a prime works and I also looked at some old java code I
 *          had written ~2 years ago that used trial division to determine whether a number is a prime number
 *          * https://en.wikipedia.org/wiki/Trial_division
 *          * My java code from ~2 years ago - not sure how to attach it / link to it from here since it's only on my
 *          computer
 */
bool is_prime(int num) {
    if (num == 2) { // 2 is a prime number and is the exception to the prime numbers can't be even rule
        return true;
    }
    if (num <= 1 || num % 2 == 0) { // prime numbers can't be less than 1 & even numbers aren't primes (except for 2)
        return false;
    }
    bool is_a_prime = true;
    for (int i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) {
            is_a_prime = false;
        }
    }
    return is_a_prime;
}
// test for false positives and false negatives
void test_is_prime() {
    /*
    * Source for:
    *            first fifty primes: https://prime-numbers.info/list/first-50-primes#list
    *            first fifty composite numbers: https://en.wikipedia.org/wiki/Composite_number
    */
    printf("Testing is_prime Function: \n");
    int first_fifty_primes[50] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61,
        67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167,
        173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229};
    int first_fifty_composites[50] = {4, 6, 8, 9, 10, 12, 14, 15, 16, 18, 20, 21, 22, 24, 25, 26, 27,
        28, 30, 32, 33, 34, 35, 36, 38, 39, 40, 42, 44, 45, 46, 48, 49, 50, 51, 52, 54, 55, 56, 57,
        58, 60, 62, 63, 64, 65, 66, 68, 69, 70};
    bool pass = true;
    // maybe double for loop -
    for (int i = 0; i < 50; i++) {
        if (!is_prime(first_fifty_primes[i])) {
            pass = false;
            printf("\t\tFAILS on %d\n", first_fifty_primes[i]);
            break;
        }
    }
    for (int j = 0; j < 50; j++) {
        if (is_prime(first_fifty_composites[j])) {
            pass = false;
            printf("\t\tFAILS on %d\n", first_fifty_composites[j]);
            break;
        }
    }
    if (pass == true) {
        printf("\t\tPASS\n");
    }


}


/*
 *
 *      Question #3: Reducing a fraction number to its lowest term.
 *
 *      Resources Used:
 *          Used the following two sources for some help on c++ syntax:
 *              https://stackoverflow.com/questions/12992925/c-correct-way-to-return-pointer-to-array-from-function:
 *              https://www.w3schools.com/cpp/cpp_arrays.asp
 *          Used wikipedia to get a description of how an algorithm for finding the greatest common divisor works
 *              https://en.wikipedia.org/wiki/Greatest_common_divisor#Calculation
 */
// use the Euclidean algorithm to find the greatest common divisor of two ints (numerator and denominator)
int euclidean_algorithm(int a, int b) { //https://en.wikipedia.org/wiki/Greatest_common_divisor#Calculation
    if (b == 0) {
        return a;
    }
    else {
        return euclidean_algorithm(b, a % b);
    }
}
// reduce the fraction (calls euclidean_algorithm)
int* reduce_fraction(int fraction[]) { // return a pointer that points to the address of the array
    int numerator = fraction[0];
    int denominator = fraction[1];
    printf("Original Fraction:\t %d/%d", numerator, denominator);
    // find the greatest common factor (GCF) / greatest common divisor (GCD) in order to reduce both terms
    int gcd = euclidean_algorithm(numerator, denominator);
    printf("\n\t(Greatest Common Divisor) GCD is: %d\n", gcd);
    fraction[0] = numerator / gcd;
    fraction[1] = denominator / gcd;
    return fraction;
}
// test - NEED TO FIGURE OUT HOW TO TEST IT !!!
void test_reduce_fraction() {
    printf("Testing is_prime Function: \n");
}


/*
 *      MAIN
 */
int main() {
    /*  test is_power_of_two_loop and is_power_of_two code
        currently set to test is_power_of_two_loop. need to change function call in functions in order to test
        is_power_of_two
     */
    test_powers_of_two_fn();
    test_powers_of_two_fp();
    printf("\n\n");
    /*  test is_prime code with the first fifty prime numbers
        and first fifty composite numbers
    */
    test_is_prime();

    printf("\n\n");


    //bool result = is_prime(8);
    //printf("Result: %d\n", result);

    /*
        test reducing fractions code

     */

    printf("\n\n");
    test_reduce_fraction();

    int fraction2[2] = {12,14};
    int* p_fraction = reduce_fraction(fraction2);
    printf("Reduced Fraction:\t %d/%d", fraction2[0], fraction2[1]);

    return 0;
}
