#include "../l/lib.h"
#include "../l/geo.h"

class ENewYearAndCastleConstruction {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<pii> A(N); cin >> A;
        ll ans = 0;
        for (int i = 0; i < N; ++i) {
            vector<pii> B;
            for (int j = 0; j < N; ++j) if (i != j) B.push_back({A[j].x - A[i].x,A[j].y-A[i].y});
            sort(B.begin(),B.end(),[&](const pii&a, const pii&b) {
                if (a.x >= 0 && b.x < 0) return true;
                if (b.x >= 0 && a.x < 0) return false;
                return 1LL*a.x * b.y > 1LL*b.x * a.y;
            });
            
            int k = 0;
            for (int j = 0; j < N-1; ++j) {
                if (k == j) k = k==N-2?0:k+1;
                while (1LL*B[j].y*B[k].x < 1LL*B[j].x*B[k].y) k = k==N-2?0:k+1;
                int cnt = k>j?k-j:k-j+N-1;
                ans += (N-cnt)*cnt;
            }
        }
        cout << (ans - N*ll(N-1)*N*(N+1)/6) * (N-4) / 4 << '\n';
    }
};
