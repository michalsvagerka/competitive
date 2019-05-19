#include "../l/lib.h"
// #include "../l/mod.h"

class ESquareTiling {
public:
    vector<string> S;

    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        S.assign(N, string(M, '_'));
        for (int i = 0; i < N; ++i) {
//            cerr << i << ' ';
            for (int j = 0; j < M; ++j) {
                if (S[i][j] == '_') {
                    char ch = 'A';
                    while (true) {
                        if ((i > 0 && S[i - 1][j] == ch) || (j < M-1 && S[i][j+1] == ch)) ++ch;
                        else if (j > 0 && S[i][j - 1] == ch) {
                            int k = j - 1;
                            while (k > 0 && S[i][k - 1] == ch) --k;
                            int l = j - k;
                            if ((i > 0 && S[i - 1][k] == ch) || i + l == N || (k > 0 && S[i + l][k] == ch)) {
                                ++ch;
                            } else {
                                for (int m = k; m <= j; ++m) S[i + l][m] = ch;
                                for (int m = i; m <= i + l; ++m) S[m][j] = ch;
                                break;
                            }
                        } else {
                            S[i][j] = ch;
                            break;
                        }
                    }
                }
//                cerr << S[i][j];
            }
//            cerr << endl;
        }

        for (string s: S) cout << s << '\n';
    }
};
