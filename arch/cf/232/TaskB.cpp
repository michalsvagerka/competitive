#include "../l/lib.h"
 #include "../l/primes.h"
#include "../l/frac.h"

class TaskB {
public:
void solve(istream& cin, ostream& cout) {
    int T; cin >> T;
    for (int t = 0; t < T; ++t) {
        int a; cin >> a;
        if (a == 2) cout << "1/6\n";
        else if (a == 3) cout << "7/30\n";
        else {
            ll b = a+1;
            while (!isPrime(b)) ++b;
            ll c = a;
            while (!isPrime(c)) --c;
            ll num = c*(b-2) - 2*(b-a-1);
            ll den = 2*b*c;
            cout << Fraction{num, den} << '\n';
        }
    }
}
};
