#include "../l/lib.h"

class CBadSequence {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        string S; cin >> S;
        string T; bool hasC = false;
        for (int i = 0; i < N; ++i) {
            if (S[i] == ')' && !hasC) {
                hasC = true;
            } else {
                T += S[i];
            }
        }
        if (hasC) T += ')';
        reverse(S.begin(),S.end());
        string U; bool hasO = false;
        for (int i = 0; i < N; ++i) {
            if (S[i] == '(' && !hasO) {
                hasO = true;
            } else {
                U += S[i];
            }
        }
        if (hasO) U += '(';
        reverse(S.begin(),S.end());
        reverse(U.begin(),U.end());
        for (string C: {S,T,U}) {
            int b = 0;
            for (char s: C) {
                if (s == '(') b++;
                else {
                    b--;
                    if (b < 0) { b = -1; break; }
                }
            }
            if (b == 0) {
                cout << "Yes\n";
                return;
            }
        }

        cout << "No\n";
    }
};
