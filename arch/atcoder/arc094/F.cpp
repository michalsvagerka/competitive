#include "../../../l/lib.h"
 #include "../../../l/mod.h"

typedef Field<998244353> FL;

class F {
public:
    set<string> Q;

    void solve(string & s) {
        if (Q.find(s) != Q.end()) return;
        Q.insert(s);

        for (int i = 0; i < s.size()-1; ++i) {
            if (s[i] != s[i+1]) {
                char k = s[i], l = s[i+1];
                for (char c = 'a'; c <= 'c'; ++c) {
                    if (k != c && l != c) {
                        s[i] = s[i + 1] = c;
                        solve(s);
                        s[i] = k;
                        s[i+1] = l;
                    }
                }
            }
        }
    }

    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        if (S.size() <= 3) {
            solve(S);
            cout << Q.size() << endl;
        } else {
            bool same = false;
            vector3<FL> P(3, 3, 2, 0);
            P[0][0][0] = P[1][1][0] = P[2][2][0] = 1;
            vector<bool> U(3, false);
            int m = S[S.size()-1] - 'a';
            U[S[S.size()-1]-'a'] = true;
            for (int i = 0; i < S.size()-1; ++i) {
                vector3<FL> R(3, 3, 2, 0);
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        for (int k = 0; k < 3; ++k) {
                            for (int l = 0; l < 2; ++l) {
                                R[i][(i+k)%3][l|(i==j)] += P[j][k][l];
                            }
                        }
                    }
                }
                swap(R,P);

                U[S[i]-'a'] = true;
                m += S[i] - 'a';
                same |= S[i] == S[i+1];
            }

            if (count(U.begin(),U.end(),true) == 1) {
                cout << 1 << endl;
            } else {
                m %= 3;
                FL ans = P[0][m][1] + P[1][m][1] + P[2][m][1];
                if (!same) ans++;
                cout << ans << endl;
            }
        }
    }
};
