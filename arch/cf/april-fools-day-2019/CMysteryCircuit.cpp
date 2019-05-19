#include "../l/lib.h"

class CMysteryCircuit {
public:
    void solve(istream& cin, ostream& cout) {
        int A; cin >> A;
        if (A == 6) { cout << "10\n"; return; }
        if (A == 7) { cout << "11\n"; return; }
        if (A == 10) { cout << "2\n"; return; }
        if (A == 11) { cout << "3\n"; return; }
        if (A == 12) { cout << "4\n"; return; }
        if (A == 13) { cout << "5\n"; return; }
        if (A == 14) { cout << "6\n"; return; }
        if (A == 15) { cout << "7\n"; return; }
        int B = 0;
        for (int i = 0; i < 4; ++i) {
            int b = 1;
            for (int j = i; j < 4; ++j) {
                b ^= (A >> j)&1;
            }
            B |= b<<i;
        }
        cout << B << endl;
    }
};

// 0 -> 15
// 1 -> 14
// 2 -> 12
// 3 -> 13
// 4 -> 8
// 5 -> 9
// 6 -> 10
// 7 -> 11
// 8 -> 0
// 9 -> 1
// 10 -> 2
// 11 -> 3
// 12 -> 4
// 13 -> 5
// 14 -> 6
// 15 -> 7
