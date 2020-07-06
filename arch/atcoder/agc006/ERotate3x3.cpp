#include "../l/lib.h"
#include "../l/fenwick.h"

class ERotate3x3 {
public:
    int sign(vector<int> A) {
        int N = A.size();
        Fenwick<int> F(N, 0);
        ll ans = 0;
        for (int i = N-1; i >= 0; --i) {
            if (A[i] != 0) ans += F.range(0, A[i]-1);
            F.add(A[i], 1);
        }
        return int(ans%2);
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector2<int> A(3, N); cin >> A;
        bool fail = false;
        for (int i = 0; i < N; ++i) {
            if (A[1][i]%3 != 2) fail = true;
            if (abs(A[1][i]-A[0][i]) != 1) fail = true;
            if (abs(A[1][i]-A[2][i]) != 1) fail = true;
            if (A[1][i]%6 != 2 + 3*(i%2)) fail = true;

        }

        vector<int> Rev(2, 0);
        for (int p = 0; p < 2; ++p) {
            for (int i = p; i < N; i += 2) {
                if (A[0][i]%3 == 0) Rev[p]++;
            }
            Rev[p] %= 2;
        }

        vector<int> Sign(2, 0);
        for (int p = 0; p < 2; ++p) {
            vector<int> S;
            for (int i = p; i < N; i += 2) S.push_back(A[1][i] / 6);
            Sign[p] = sign(S);
        }

        fail |= Sign[0] != Rev[1];
        fail |= Sign[1] != Rev[0];

        cout << (fail ? "No\n" : "Yes\n");
    }
};
