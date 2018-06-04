#include "../../../l/lib.h"
 #include "../../../l/fenwick.h"

class yaroslavanddivisors {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<int> P(N), A(N+1, 0); cin >> P;
        for (int i = 0; i < N; ++i) A[P[i]] = i;

        vector<pii> W;
        for (int i = 1; i <= N; ++i) {
            for (int j = i; j <= N; j+=i) {
                W.push_back({A[i],A[j]});
            }
        }

        Fenwick<int> F(N+1);
        for (pii &w:W) {
            if (w.x > w.y) swap(w.x, w.y);
            F.add(w.y, 1);
        }
        sort(W.begin(),W.end());

        vector<pair<pii,pii>> Q(M);
        for (int i = 0; i < M; ++i) {
            cin >> Q[i].x.x >> Q[i].x.y;
            Q[i].x.x--; Q[i].x.y--;
            Q[i].y.x = i;
        }
        sort(Q.begin(),Q.end());

        int i = 0, j = 0;
        for (int k = 0; k < N; ++k) {
            while (i < M && Q[i].x.x == k) {
                Q[i].y.y = F.range(0, Q[i].x.y);
                i++;
            }

            while (j < W.size() && W[j].x == k) {
                F.add(W[j].y, -1);
                j++;
            }
        }

        sort(Q.begin(),Q.end(),[](const pair<pii,pii>&a, const pair<pii,pii>&b) { return a.y.x < b.y.x; });
        for (int i = 0; i < M; ++i) {
            cout << Q[i].y.y << '\n';
        }
    }
};
