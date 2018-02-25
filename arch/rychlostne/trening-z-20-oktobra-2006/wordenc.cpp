#include "../../../l/lib.h"
// #include "../l/mod.h"

class wordenc {
public:

    vector3<bool> A;
    vector2<bool> B;
    vector<bool> C;
    vector4<ll> F;

    ll count(int a, int b, int c, int l) {
        if (a != 26 && !A[a][b][c]) return 0;
        if (b != 26 && !B[b][c]) return 0;
        if (c != 26 && !C[c]) return 0;
        if (l == 0) return 1;

        if (F[a][b][c][l] != -1) return F[a][b][c][l];

        ll ans = 0;
        for (int i = 0; i < 26; ++i) {
            ans += count(b,c,i,l-1);
        }

        return F[a][b][c][l] = ans;
    }

    ll index(string S) {
        int ans = 1;
        for (int i = 1; i < S.size(); ++i) {
            ans += count(26,26,26,i);
        }

        int a = 26, b = 26, c;
        for (int i = 0; i < S.size(); ++i) {
            c = S[i] - 'a';
            for (int q = 0; q < c; ++q) {
                ans += count(a,b,q,S.size()-i-1);
            }
            a = b;
            b = c;
        }

        return ans;
    }

    string word(ll idx) {
        int l = 1;
        while (idx > count(26,26,26,l)) {
            idx -= count(26,26,26,l);
            ++l;
        }

        string Ans(l, '?');
        int a = 26, b = 26, c;
        for (int i = 0; i < l; ++i) {
            for (c = 0 ;; ++c) {
                if (idx > count(a,b,c,l-i-1)) {
                    idx -= count(a,b,c,l-i-1);
                } else break;
            }
            Ans[i] = char('a'+c);
            a = b;
            b = c;
        }

        return Ans;
    }

    void solve(istream& cin, ostream& cout) {
        int T;
        cin >> T;
        for (int t = 1; t <= T; ++t) {
            int N,M; cin >> N >> M;
            F = vector4<ll>(27,27,27,21,-1);
            A = vector3<bool>(26,26,26,true);
            B = vector2<bool>(26,26,true);
            C = vector<bool>(26,true);
            for (int i = 0; i < N; ++i) {
                string S; cin >> S;
                if (S.size() == 3) {
                    A[S[0]-'a'][S[1]-'a'][S[2]-'a'] = false;
                } else if (S.size() == 2) {
                    B[S[0]-'a'][S[1]-'a'] = false;
                } else {
                    C[S[0]-'a'] = false;
                }
            }

            for (int i = 0; i < M; ++i) {
                string S; cin >> S;
                if (S[0] >= '0' && S[0] <= '9') {
                    stringstream ss(S);
                    ll k;
                    ss >> k;
                    cout << word(k) << '\n';
                } else {
                    cout << index(S) << '\n';
                }
            }
        }
    }
};
