#include "../l/lib.h"
// #include "../l/mod.h"

class howmanyzeros {
public:
    vector<ui> A, B;

    ui solve(string S) {
        if (S[0]=='0') return 0;
        ui N = S.size(), zeros = 0, ans = 1 - A[N-1] - B[N-1];
        for (int d = 0; d < N; ++d) {
            zeros += S[d] == '0';
            ans += (S[d] != '0') * A[N-d-1];
            ans += (S[d] - '0') * (zeros * A[N-d-1] + B[N-d-1]);
        }

        for (int i = 1; i < N-1; ++i) ans += 9*i*A[i-1];
        return ans;
    }

    void solve(istream& cin, ostream& cout) {
        A.resize(10); B.resize(10);
        A[0] = 1;
        B[0] = 0;
        for (int i = 1; i < 10; ++i) {
            A[i] = A[i-1]*10;
            B[i] = A[i-1] + B[i-1]*10;
        }

        string M,N; cin >> M >> N;
        while (M[0] != '-') {
            cout << solve(N) - solve(M) + count(N.begin(),N.end(),'0') << '\n';
            cin >> M >> N;
        }
    }
};
