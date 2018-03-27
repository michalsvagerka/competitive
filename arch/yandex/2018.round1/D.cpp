#include "../../../l/lib.h"
// #include "../l/mod.h"

class D {
public:
    string S;
    int N;

    bool canMake(const string &T) {
        int M = T.size();
        vector2<bool> D(N+1, M+1, false);
        D[0][0] = true;
        for (int i = 0; i < N; ++i) {
            char s = S[i];
            for (int j = 0; j < M; ++j) {
                if (T[j] == s && (D[i][j] || D[i][M])) {
                    D[i + 1][j + 1] = true;
                }
            }
            for (int j = 0; j <= M; ++j) {
                if (D[i][j] && T[0] == s) D[i+1][1] = true;
            }
        }

        return D[N][M];
    }

    void solve(istream& cin, ostream& cout) {
        cin >> S;
        N = S.size();
        set<string> Q;

        set<string> C;
        for (int i = 0; i < N; ++i) {
            for (int j = i+1; j <= N; ++j) {
                string T = S.substr(i, j-i);
                C.insert(T);
            }
        }

        for (const string&c:C) {
            if (canMake(c)) {
                Q.insert(c);
            }
        }
        
        for (const string&q:Q) {
            cout << q << '\n';
        }
    }
};
