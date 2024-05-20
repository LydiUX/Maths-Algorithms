#include <iostream>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

long extended_gcd(long a, long b, long& s, long& t) { // compute gcd and (s,t) s.t. as+bt = gcd(a,b)
    if (b == 0) {
        s = 1;
        t = 0;
        return a;
    }
    long s_n, t_n;
    long gcd = extended_gcd(b, a % b, s_n, t_n);
    s = t_n;
    t = s_n - (a / b) * t_n;
    return gcd;
}

int main() {
    long a, b, s, t;
    cout << "cin a b" << endl;
    cin >> a >> b;
    cout << "gcd(" << a << ", " << b << ") = " << extended_gcd(a, b, s, t) << endl;
    cout << "(s, t) = (" << s << ", " << t << ")" << endl;
    return 0;
}