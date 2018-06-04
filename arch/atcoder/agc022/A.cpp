#include "../../../l/lib.h"
// #include "../l/mod.h"

class A {
public:
    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        if (S.size() < 26) {
            vector<bool> K(26,false);
            for (char s:S) K[s-'a'] = true;
            cout << S;
            for (int i = 0; i < 26; ++i) {
                if (!K[i]) {
                    cout << char(i+'a') << endl;
                    return;
                }
            }
        } else {
            vector<bool> U(26, false);
            U[S[25]-'a'] = true;
            int i = 24;
            while (i >= 0 && S[i] > S[i+1]) {
                U[S[i]-'a'] = true;
                --i;
            }

            if (i == -1) {
                cout << -1 << endl;
            } else {
                for (int j = 0; j < i; ++j) cout << S[j];
                for (int j = S[i]-'a'; j < 26; ++j) {
                    if (U[j]) {
                        cout << char(j+'a') << endl;
                        return;
                    }
                }
            }
        }
    }
};
