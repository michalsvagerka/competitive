#include "../l/lib.h"

constexpr int MAX = 260;

class readbin {
public:
    int calc(int x) {
        if (x == 0) return 4;
        int y = 0;
        while (x) {
            if (x&1) y += 3; else y += 4;
            x >>= 1;
        }
        return y;
    }
    
    void brute(int N, int K, ostream&cout) {
        vector<ll> Ans(MAX, 0);
        for (int i = 0; i <= N; ++i) {
            int j = i;
            for (int k = 0; k < K; ++k) {
                j = calc(j);
            }
            Ans[j]++;
        }
        int c = 0;
        for (int i = 0; i < MAX; ++i) c += Ans[i]!=0;
        cout << c << endl;
        for (int i = 0; i < MAX; ++i) {
            if (Ans[i]!=0) {
                cout << i << ' ' << Ans[i] << endl;
            }
        }
    }

    void solve(istream& cin, ostream& cout) {
        ll N, K; cin >> N >> K;
//        brute(N, K, cout);
        if (K == 0) {
            if (N >= 1000) {
                cout << N+1 << endl;
                for (int i = 0; i < 500; ++i) cout << i << " 1\n";
                for (ll i = N-499; i <= N; ++i) cout << i << " 1\n";
            } else {
                cout << N+1 << endl;
                for (int i = 0; i <= N; ++i) cout << i << " 1\n";
            }
        } else {
            vector4<ll> CNT(63, MAX, 2, 2, 0LL);
            CNT[0][0][0][0] = 1;
            for (int i = 0; i < 62; ++i) {
                int j = (N>>(61-i))&1;
                for (int k = 0; k < MAX; ++k) {
                    for (int l = 0; l < 2; ++l) {
                        for (int n = 0; n < 2; ++n) {
                            if (CNT[i][k][l][n] == 0) continue;
                            for (int m = 0; m < 2; ++m) {
                                int newL = l;
                                int newN = n;
                                if (m == 1) newN = 1;
                                if (j > m) newL = 1;
                                if (l == 0 && m > j) continue;
                                int newK = k + (newN ? 4 - m : 0);
                                CNT[i + 1][newK][newL][newN] += CNT[i][k][l][n];
                            }
                        }
                    }
                }
            }

            vector<ll> C(MAX, 0);
            for (int i = 0; i < MAX; ++i) {
                for (int j = 0; j < 2; ++j) {
                    for (int k = 0; k < 2; ++k) {
                        C[i] += CNT[62][i][j][k];
                    }
                }
            }
            
            C[0]--;
            C[4]++;
            
            --K;
            vector2<int> T(63, MAX, 0);
            for (int i = 0; i < MAX; ++i) {
                T[0][i] = calc(i);
            }

            for (int i = 0; i < 62; ++i) {
                for (int j = 0; j < MAX; ++j) {
                    T[i+1][j] = T[i][T[i][j]];
                }
            }
            
            vector<int> V(MAX);
            for (int i = 0; i < MAX; ++i) V[i] = i;
            for (int i = 62; i >= 0; --i) {
                if (K&(1LL<<i)) {
                    for (int j = 0; j < MAX; ++j) {
                        V[j] = T[i][V[j]];
                    }
                }
            }

            vector<ll> Ans(MAX, 0);
            for (int i = 0; i < MAX; ++i) Ans[V[i]] += C[i];
            int c = 0;
            for (int i = 0; i < MAX; ++i) c += Ans[i]!=0;
            cout << c << endl;
            for (int i = 0; i < MAX; ++i) {
                if (Ans[i]!=0) {
                    cout << i << ' ' << Ans[i] << endl;
                }
            }
        }
    }
};
