#include "../l/lib.h"
#include "../l/mod.h"

typedef Field<998244353> FF;

class DSecretPassage {
public:
    set<string> SS;
    void brute(string S) {
        auto it = SS.find(S);
        if (it != SS.end()) return;
        SS.insert(S);
        if (S.size() == 1) return;
        int N = S.size();
        for (int i = 2; i <= N; ++i) {
            brute(S.substr(2, i-2) + S[0] + S.substr(i));
            brute(S.substr(2, i-2) + S[1] + S.substr(i));
        }
    }

    void solve(istream& cin, ostream& cout) {
        string S; cin >> S;
        int N = S.size();

//        brute(S);
//        cout << SS.size() << endl;
//        for (string s: SS) cout << s << endl;

        vector3<FF> D(N+1, N+1, N+1, 0);
        D[0][0][0] = 1;
        for (int i = 0; i < N; ++i) {
            char c = S[N - i - 1];
            for (int j = 0; j < N; ++j) {
                for (int k = 0; k < N; ++k) {
                    if (c == '1') {
                        D[i + 1][j][k] += D[i][j][k];
                        D[i][j + 1][k] += D[i][j][k];
                    } else {
                        D[i][j][k + 1] += D[i][j][k];
                        D[i + 1][j][k] += D[i][j][k];
                    }
                }
            }
        }

        vector3<bool> P(N+1, N+1, N+1, 0);
        P[0][0][0] = true;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                for (int k = 0; k < N; ++k) {
                    if (P[i][j][k]) {
                        P[i+1][j][k] = true;

                        if (j > 0 && S[i] == '1') {
                            P[i+1][j-1][k+1] = true;
                        }

                        if (k > 0 && S[i] == '0') {
                            P[i+1][j+1][k-1] = true;
                        }

                        if (i != N-1) {
                            if (S[i] == '0' || S[i+1] == '0') {
                                P[i+2][j+1][k] = true;
                            }


                            if (S[i] == '1' || S[i+1] == '1') {
                                P[i+2][j][k+1] = true;
                            }

                        }
                    }
                }
            }
        }


//        for (int i = 0; i <= N; ++i) {
//            for (int j = 0; j <= N; ++j) {
//                for (int k = 0; k <= N; ++k) {
//                    if (P[i][j][k]) {
//                        cout << i << ' ' << j << ' ' << k << endl;
//                    }
//                }
//            }
//        }

        FF ans = 0;
        for (int i = 0; i <= N; ++i) {
            for (int j = 0; j < N; ++j) {
                for (int k = 0; k < N; ++k) {
                    if (P[i][j][k] && D[N-i][j][k] != 0) {
//                        cout << N-i << ' ' << j << ' ' << k << ' ' << D[N-i][j][k] << endl;
                        ans += D[N-i][j][k];
                    }
                }
            }
        }
        --ans;

//        int ones = 0;
//        int zeroes = 0;
//        for (int i = 0; i < N; i += 2) {
//            if (S[i] == '0' || (i!=N-1 && S[i+1] == '0')) zeroes++;
//            if (S[i] == '1' || (i!=N-1 && S[i+1] == '1')) ones++;
//        }
//        cout << ones << ' ' << zeroes << endl;
//
//        for (int l = 1; l <= N; ++l) {
//            if (l <= (N+1)/2) {
//                for (int o = 0; o <= min(l, ones); ++o) {
//                    int z = l - o;
//                    if (z <= zeroes) {
//                        cout << l << ' ' << o << ' ' << z << endl;
//                        ans += F[l] * I[o] * I[z];
//                    }
//                }
//                cout << "After " << l << ' ' << ans << endl;
//                continue;
//            }
//
//            for (int i = 0; i < N; i += 2) {
//                if (S[i] == '0' || (i!=N-1 && S[i+1] == '0')) zeroes++;
//                if (S[i] == '1' || (i!=N-1 && S[i+1] == '1')) ones++;
//            }
//
//            int rounds = N - l;
//
//
//            int myOnes = 0;
//            int myZeroes = 0;
//            for (int i = 0; i < 2*rounds; i += 2) {
//                if (S[i] == '0' || S[i+1] == '0') myZeroes++;
//                if (S[i] == '1' || S[i+1] == '1') myOnes++;
//            }
//            cout << l << ' ' << myOnes << ' ' << myZeroes << endl;
//
//            cout << ans << '\n';
//        }
//
        cout << ans << '\n';
    }
};

/**
0 0 0
1 0 0
2 0 0
2 0 1
3 0 0
3 0 1
3 1 0
4 0 0
4 0 1
4 1 0
4 1 1
4 2 0
5 0 0
5 0 1
5 1 0
5 1 1
5 2 0
6 0 0
6 0 1
6 0 2
6 1 0
6 1 1
6 1 2
6 2 0
6 2 1
6 3 0

0 0 0
1 0 0
2 0 0
2 0 1
3 0 0
3 0 1
3 1 0
4 0 0
4 0 1
4 1 0
4 1 1
5 0 0
5 0 1
5 1 0
5 1 1
5 2 0
6 0 0
6 0 1
6 0 2
6 1 0
6 1 1
6 1 2
6 2 0
6 2 1
 */


