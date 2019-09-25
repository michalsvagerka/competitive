#include "../l/lib.h"

constexpr int T = 1000000;
constexpr int N = 2000;

class BWrongAnswer {
public:
    void solve(istream& cin, ostream& cout) {
        int K; cin >> K;
        for (int b = 1; b <= T; ++b) {
            int lo = bsl(1, N-1, [&](int s) { return (K+b)/s + b <= T; });
            if (lo == -1) continue;
            for (int t = lo; t <= min(b, N-1); ++t) {
                if ((K+b)%t == 0) {
                    int c = (K+b)/t;
                    int a = c + b;
                    if (a <= T) {
                        vector<int> X(t+1, -1);
                        X[t] = a;
                        b -= t;
                        for (int i = 0; i < t; ++i) {
                            int add = min(T-1, b);
                            b -= add;
                            X[i] -= add;
                        }
                        cout << t+1 << '\n' << X;
                        return;
                    }
                }
            }
        }
        cout << -1 << endl;
    }
};
