#include "../l/lib.h"
// #include "../l/mod.h"

class BSportsFestival {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector2<int> A(N, M); cin >> A;
        for (auto&a:A) for (int&aa:a) --aa;
        vector<int> S(N, 0), C(M, 0);
        vector<bool> U(M, true);
        for (int i = 0; i < N; ++i) C[A[i][0]]++;
        int ans = N;
        for (int i = 0; i < M-1; ++i) {
            ans = min(ans, *max_element(C.begin(),C.end()));
            pii b = {0, -1};
            for (int j = 0; j < M; ++j) b = max(b, {C[j],j});
            U[b.y] = false;
            for (int j = 0; j < N; ++j) {
                C[A[j][S[j]]]--;
                while (!U[A[j][S[j]]]) ++S[j];
                C[A[j][S[j]]]++;
            }
        }
        cout << ans << '\n';
    }
};
