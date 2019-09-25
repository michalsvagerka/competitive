#include "../l/lib.h"
#include "../l/mod.h"

class E1MarekAndMatchingEasyVersion {
public:
    vector<int> Cur, Msk;
    vector<int> P;
    int N;
    vector<FieldMod> Q;

    vector<int> RealMsk;

    FieldMod pst(int mask, int len, int off) {
        FieldMod ans = 1;
        for (int i = 0; i < len; ++i) {
            if (mask&1<<i) ans *= P[i+off];
            else ans *= 100 - P[i+off];
        }
        return ans;
    }

    void build(int M, int off) {
        for (int i = 0; i < (1<<N); ++i) if (__builtin_popcount(i) == M) RealMsk.push_back(i);
        Q.resize(1<<RealMsk.size());

        for (int i = 0; i < (1<<(N*M)); ++i) {
            vector<bool> Msk(1<<N, false);
            for (int a = 0; a < N; ++a) {
                if ((i&1<<a) == 0) continue;
                if (M == 1) {
                    Msk[1<<a] = true;
                } else {
                    for (int b = 0; b < N; ++b) {
                        if (a == b || (i&1<<(b+N)) == 0) continue;
                        if (M == 2) {
                            Msk[1<<a|1<<b] = true;
                        } else {
                            for (int c = 0; c < N; ++c) {
                                if (a == c || b == c || (i&1<<(c+2*N)) == 0) continue;
                                Msk[1<<a|1<<b|1<<c] = true;
                            }
                        }
                    }
                }
            }

            int mask = 0;
            for (int i = 0; i < RealMsk.size(); ++i) if (Msk[RealMsk[i]]) mask |= 1<<i;
            Q[mask] += pst(i, N*M, off);
        }
    }


    void solve(istream& cin, ostream& cout) {
        cin >> N;
        P.resize(N * N);

        cin >> P;
        if (N == 1) {
            cout << FieldMod{P[0]} / 100 << endl;
            return;
        }

        int SA = N / 2;
        build(SA, 0);
        vector<FieldMod> A = Q;
        vector<int> MA = RealMsk;
        Q.clear();
        RealMsk.clear();

        int SB = N - SA;
        build(SB, SA * N);
        vector<FieldMod> B = Q;
        vector<int> MB = RealMsk;

        vector<FieldMod> C(B.size(), 0);
        for (int i = 0; i < B.size(); ++i) {
            int k = 0;
            for (int j = 0; j < MB.size(); ++j) {
                if (i & 1 << j) k |= 1 << (MB.size() - j - 1);
            }
            C[k] = B[i];
        }

        for (int j = 0; j < MB.size(); ++j) {
            for (int i = 0; i < B.size(); ++i) {
                if (i&1<<j) continue;
                C[i|1<<j] += C[i];
            }
        }

        FieldMod ans = 0;
        int W = 1<<MB.size();
        for (int i = 0; i < A.size(); ++i) {
            ans += A[i] * C[W-1-i];
        }

        for (int i = 0; i < N*N; ++i) ans /= 100;

        cout << FieldMod{1}-ans << endl;
    }
};
