#include "../l/lib.h"
// #include "../l/mod.h"

class CColoringTorus {
public:

    void solve(istream& cin, ostream& cout) {
        int K; cin >> K;
        if (K == 1) {
            cout << "1\n1\n";
            return;
        }

        int N = K;
        while (N%4 != 0) ++N;
        vector2<int> R(N/2, N/2, 0);
        int S = N-K;
        int l = 1;
        for (int i = 0; i < N/2; ++i) {
            int a = l;
            int b = l + (i>=S);

            for (int j = 0; j < N/2; ++j) {
                int k = (j+i)%(N/2);
                R[j][k] = j%2?a:b;
            }

            l++;
            l += (i>=S);
        }

        cout << N/2 << endl;
        for (auto&r:R) cout << r;
    }
};
