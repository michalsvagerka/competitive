#include "../l/lib.h"

class DASequenceOfPermutations {
public:
    vector<int> mul(const vector<int>&a, const vector<int>&b) {
        int N = a.size();
        vector<int> R(N);
        for (int i = 0; i < N; ++i) {
            R[i] = a[b[i]];
        }
        return R;
    }

    vector<int> prod(const vector<int>&w, int k) {
        int N = w.size();
        vector<int> R(N), P = w;
        for (int i = 0; i < N; ++i) {
            R[i] = i;
        }

        while (k) {
            if (k%2) R = mul(R, P);
            P = mul(P, P);
            k >>= 1;
        }
        return R;
    }

    void solve(istream& cin, ostream& cout) {
        int N, K; cin >> N >> K;
        vector<int> P(N), Q(N); cin >> P >> Q;

        for (int&p: P) --p;
        for (int&q: Q) --q;

        vector<int> PI(N), QI(N);
        for (int i = 0; i < N; ++i) {
            QI[Q[i]] = i;
            PI[P[i]] = i;
        }
        vector<int> Per(N);
        for (int i = 0; i < N; ++i) Per[i] = Q[PI[QI[P[i]]]];

        int s = (K-1)/6;
        K -= 6*s;

        vector<int> pow = prod(Per, s);
        vector<int> ipow(N);
        for (int i = 0; i < N; ++i) {
            ipow[pow[i]] = i;
        }
        P = mul(pow, mul(P, ipow));
        Q = mul(pow, mul(Q, ipow));
        vector<int> Ans;
        if (K == 1) {
            Ans = P;
        } else {
            for (int k = 3; k <= K; ++k) {
                vector<int> Z(N);
                for (int i = 0; i < N; ++i) {
                    Z[P[i]] = Q[i];
                }
                swap(P, Q);
                swap(Q, Z);
            }
            Ans = Q;
        }

        for (int&ans: Ans) ++ans;
        cout << Ans;
    }
};
