#include "../l/lib.h"
// #include "../l/mod.h"

class CVasyaAndTemplates {
public:
    int K;
    string S, A, B, M;
    vector<bool> U;

    bool solve(int i, bool ga, bool lb) {
        if ((ga && lb) || i == S.size()) return true;

        int z = S[i]-'a';
        if (M[z] != '_') {
            if (!ga && M[z] < A[i]) {
                // fail
            } else if (!lb && M[z] > B[i]) {
                // fail
            } else {
                // ok
                if (solve(i+1, ga || M[z] > A[i], lb || M[z] < B[i])) return true;
            }
        } else {
            for (char c = 'a'; c < char('a' + K); ++c) {
                int g = c - 'a';
                if (U[g]) continue;
                U[g] = true;
                M[z] = c;


                if (!ga && c < A[i]) {
                } else if (!lb && c > B[i]) {
                } else {
                    if (solve(i + 1, ga || c > A[i], lb || c < B[i])) return true;
                }

                M[z] = '_';
                U[g] = false;
            }
        }


        return false;
    }

    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            cin >> K;

            cin >> S >> A >> B;
            M = string(K, '_');
            U.assign(K, false);
            bool ans = solve(0, false, false);
            if (ans) {
                cout << "YES\n";
                for (int i = 0; i < K; ++i) {
                    if (M[i] == '_') {
                        for (int j = 0; j < K; ++j) {
                            if (!U[j]) {
                                U[j] = true;
                                M[i] = char('a' + j);
                                break;
                            }
                        }
                    }
                }
                cout << M << '\n';
            } else {
                cout << "NO\n";
            }
        }
    }
};
