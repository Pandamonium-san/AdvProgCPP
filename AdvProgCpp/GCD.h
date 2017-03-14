#include <cassert>

template<typename T_int>
T_int GCD(T_int A, T_int B) {
    A = abs(A);
    B = abs(B);
    if (A < B)
        return GCD(B, A);
    while (B != 0) {
        T_int temp = A%B;
        A = B;
        B = temp;
    }
    return A;
}

template<typename T_int>
void Reduce(T_int& A, T_int& B) {
    T_int gcd = GCD(A, B);
    if (B < 0) gcd = -gcd;
    A /= gcd;
    B /= gcd;
}

template<typename T_int>
void TestGCD() {
    assert(GCD(30, 42) == 6);
    assert(GCD(30, -42) == 6);
    assert(GCD(-30, 42) == 6);
    assert(GCD(-30, -42) == 6);
    assert(GCD(30, 42) == 6);
}