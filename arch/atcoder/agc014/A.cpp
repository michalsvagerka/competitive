#include "../../../l/lib.h"
// #include "../l/mod.h"

class A {
public:
    void solve(istream& cin, ostream& cout) {
        int A, B, C; cin >> A >> B >> C;
        int ans = 0;
        while (true) {
            if (A % 2 == 1 || B % 2 == 1 || C % 2 == 1) {
                break;
            }

            if (A == B && B == C) {
                cout << "-1\n";
                return;
            }


            ++ans;
            int D = (A+B)/2;
            int E = (A+C)/2;
            int F = (C+B)/2;
            A = D;
            B = E;
            C = F;

//            if (ans == 1000000000) {
//                cout << "-1\n";
//                return;
//            }
        }

        cout << ans << endl;
    }
};
