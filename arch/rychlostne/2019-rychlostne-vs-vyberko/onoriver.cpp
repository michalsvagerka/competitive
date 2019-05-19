#include "../l/lib.h"
#include "../l/segtree.h"

class onoriver {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        ll D, W; cin >> W >> D;
        vector<ll> S(N), E(N), M(N);
        for (int i = 0; i < N; ++i) {
            cin >> M[i] >> S[i] >> E[i];
        }

        vector<pair<ll, pii>> Ev;
        for (int i = 0; i < N; ++i) {
            Ev.push_back({S[i], {1, i}});
            Ev.push_back({E[i], {-1, i}});
        }
        sort(Ev.begin(),Ev.end());

        vector<pair<ll,int>> ByM;
        for (int i = 0; i < N; ++i) ByM.emplace_back(M[i], i);

        ByM.emplace_back(W, N);
        sort(ByM.begin(),ByM.end());
        vector<int> I(N);
        for (int i = 0; i < N; ++i) I[ByM[i].y] = i;

        AddMinTree<int> T;
        T.setup(N+1, 0);

        for (int i = 0; i < N; ++i) {
            if (ByM[i].x <= D) {
                T.put(i, 1);
            }
        }

        ll ans = 0, lastT = 0, lo = -1;
        for (auto &ev: Ev) {
            if (lastT != ev.x && T.get(0, N) > 0) {
                if (lo == -1) lo = lastT;
                ans += ev.x - lastT;
            }
            lastT = ev.x;

            int j = ev.y.y;
            int h = bsh(I[j], N, [&](int x) { return ByM[x].x <= M[j] + D; });
            if (h != I[j]) {
                T.put(I[j]+1, h, ev.y.x);
            }
        }

        cout << lo << ' ' << ans << endl;
    }
};
