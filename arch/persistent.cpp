#include "../l/lib.h"
#include "../l/bigint.h"

class persistent {
public:
    void solve(istream& cin, ostream& cout) {
        while (true) {
            string S; cin >> S;
            if (S == "-1") return;
            Num N(S);
            if (N < 10) {
                cout << '1' << S << '\n';
                continue;
            }
            int a=0,b=0,c=0,d=0;
            while (N % 2 == 0) { ++a; N /= 2; }
            while (N % 3 == 0) { ++b; N /= 3; }
            while (N % 5 == 0) { ++c; N /= 5; }
            while (N % 7 == 0) { ++d; N /= 7; }
            if (N != 1) {
                cout << "There is no such number.\n";
                continue;
            }
            int e = a/3, f = b/2;
            a %= 3; b %= 2;
            if (a==b+1) cout << "2";
            if (b>a) cout << "3";
            if (a==b+2) cout << "4";
            while (c--) cout << "5";
            if (a&&b) cout << "6";
            while (d--) cout << "7";
            while (e--) cout << "8";
            while (f--) cout << "9";
            cout << "\n";
        }
    }
};
