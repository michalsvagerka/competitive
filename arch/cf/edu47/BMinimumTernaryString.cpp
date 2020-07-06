#include "../l/lib.h"

class BMinimumTernaryString {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        int N = S.size();
        int o = 0;
        string T;
        for (int i = 0; i < N; ++i) {
            if (S[i] == '0') {
                T += '0';
            } else if (S[i] == '1') {
                o++;
            } else if (S[i] == '2') {
                T += '2';
            }
        }

        string U;
        for (char t: T) {
            if (t == '2') {
                U += string(o, '1');
                o = 0;
            }
            U += t;
        }
        U += string(o, '1');
        cout << U << endl;
    }
};
