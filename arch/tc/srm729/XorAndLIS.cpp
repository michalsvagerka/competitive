#include "../../../l/lib.h"
// #include "../l/mod.h"

class XorAndLIS {
public:
    vector<long long> X, Y;
    vector<int> L;


    ll smallestLarger(ll loBound, ll base, int count) {
        // TODO: find smallest guy larger than LO[k] and smaller than LO[k+1]
        // by xoring x[i] with any subset of x[0..i-1]

        for (int b = 0; b <= 60; ++b) {
            ll realLo = loBound;
            if (b > 0) { realLo |= 1LL<<(b-1); }
            if (b > 1) { realLo &= ~((1LL<<(b-1))-1); }

            ll cur = base;
            int k = 0;
            bool ok = true;
            for (int j = 59; j >= 0; --j) {
                ll bit = 1LL<<j;
                if (j < b) {
                    if (L[k] == j && (cur&bit) == 0) {
                        cur ^= Y[k];
                    }
                } else if ((realLo&bit) != (cur&bit)) {
                    if (k < count && L[k] == j) {
                        cur ^= Y[k];
                    } else if ((realLo&bit) > (cur&bit)) {
                        ok = false;
                        break;
                    }
                }

                if (k < count && L[k] == j) ++k;
            }

            if (ok) return cur;
        }

        return 1LL<<60;
    }

    int maximalLength(vector<long long> x) {
        X = x;
        int N = x.size();
        L.resize(N);
        Y.resize(N);
        vector<ll> LO(N+1, 2e18);
        LO[0] = 0;
        LO[1] = x[0];
        int best = 1;
        for (int i = 1; i < N; ++i) {
            for (int j = 0; j < i; ++j) Y[j] = X[j];

            int c = 0;
            for (int b = 60; b >= 0; --b) {
                int p = c;
                while (p < i && (Y[p] & (1LL<<b)) == 0) ++p;
                if (p == i) continue;
                if (c != p) swap(Y[p],Y[c]);
                for (int r = c+1; r < i; ++r) {
                    if (Y[r] & (1LL<<b)) {
                        Y[r] ^= Y[c];
                    }
                }
                L[c] = b;
                ++c;
            }

            for (int k = best; k >= 0; --k) {
                ll value = smallestLarger(LO[k]+1, X[i], c);
//                cerr << "first " << i << " from " << X[i] << " yield " << value << endl;
                if (value > LO[k] && value < LO[k+1]) {
                    LO[k+1] = value;
                    if (k == best) ++best;
                }
            }
        }

        return best;
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<ll> A(N); cin >> A;
        cout << maximalLength(A) << '\n';
    }
};
