#include "../../../l/lib.h"

class BLightItUp {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<int> A(N); cin >> A;
        A.insert(A.begin(), 0);
        A.push_back(M);
        vector<int> B(N+1);
        for (int i = 0; i <= N; ++i) B[i] = A[i+1] - A[i];

        vector<pii> D(N+2);
        D[0] = {0,0};
        for (int i = 0; i <= N; ++i) {
            D[i+1] = {D[i].x + (i%2==0)*B[i], D[i].y + (i%2==1)*B[i]};
        }
        
        int ans = D[N+1].x;
        for (int i = 0; i <= N; ++i) {
            if (B[i] != 1) {
                ans = max(ans, D[i].x + (D[N+1].y - D[i+1].y) + B[i]-1);
            }
        }
        cout << ans << '\n';
    }
};
