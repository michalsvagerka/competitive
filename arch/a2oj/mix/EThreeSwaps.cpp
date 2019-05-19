#include "../l/lib.h"
// #include "../l/mod.h"
#include <numeric>

class EThreeSwaps {
public:
    vector<int> A, T;
    vector<pii> S;
    vector<bool> B;

    bool solve(int k) {
        if (T == A) return true;
        if (k == 3) return false;

        vector<int> F;
        for (int i = 0; i < A.size(); ++i) if (B[A[i]-1]) F.push_back(i);
        int M = F.size();

        for (int a = 0; a < M; ++a) {
            for (int b = a+1; b < M; ++b) {
                int c = F[a];
                int d = F[b];
                if (c > d) swap(c,d);

                reverse(A.begin()+c,A.begin()+d+1);
                if (solve(k+1)) {
                    S.emplace_back(c+1,d+1);
                    return true;
                }
                reverse(A.begin()+c,A.begin()+d+1);
            }
        }
        return false;
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        A.resize(N); cin >> A;
        T.resize(N);
        iota(T.begin(),T.end(),1);
        set<int> FF;
        B.assign(N, false);
        for (int i = 0; i < N; ++i) {
            if (i == 0 || i == N-1 || abs(A[i]-A[i+1]) != 1 || abs(A[i]-A[i-1]) != 1) {
                B[A[i]-1] = true;
            }
        }
        solve(0);
        cout << S.size() << '\n';
        for (pii s:S) cout << s << '\n';
    }
};
