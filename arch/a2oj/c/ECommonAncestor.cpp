#include "../l/lib.h"

class ECommonAncestor {
public:
    void dp(const string&S, vector3<bool>& A, const vector<string>& Sub) {
        int N = S.size();
        for (int j = 0; j < N; ++j) {
            A[1][j][S[j]-'a'] = true;
        }

        for (int l = 2; l <= N; ++l) {
            for (int i = 0; i+l <= N; ++i) {
                for (const string&s: Sub) {
                    for (int m = 1; m < l; ++m) {
                        if (A[m][i][s[3]-'a'] && A[l-m][i+m][s[4]-'a']) {
                            A[l][i][s[0]-'a'] = true;
                        }
                    }
                }
            }
        }
    }

    void solve(istream& cin, ostream& cout) {
        string S, T;
        cin >> S >> T;
        int N; cin >> N;
        vector<string> Sub(N); cin >> Sub;
        vector3<bool> X(S.size()+1,S.size(),26,false);
        vector3<bool> Y(T.size()+1,T.size(),26,false);
        dp(S, X, Sub);
        dp(T, Y, Sub);
        vector2<int> Ans(S.size()+1, T.size()+1,100);
        Ans[0][0] = 0;
        for (int i = 0; i < S.size(); ++i) {
            for (int j = 0; j < T.size(); ++j) {
                for (int k = 1; i+k <= S.size(); ++k) {
                    for (int l = 1; j+l <= T.size(); ++l) {
                        for (int c = 0; c < 26; ++c) {
                            if (X[k][i][c] && Y[l][j][c]) {
                                Ans[i+k][j+l] = min(Ans[i+k][j+l], Ans[i][j] + 1);
                            }
                        }
                    }
                }
            }
        }

        if (Ans.back().back() < 100) cout << Ans.back().back() << endl;
        else cout << -1 << endl;
    }
};
