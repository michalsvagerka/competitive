#include "../../../l/lib.h"
#include "../../../l/fenwick.h"
#include "../../../l/consttree.h"

class pivo {
public:
    void solve(istream& cin, ostream& cout) {
        int N, P; cin >> N >> P;
        vector<pii> W(P);
        cin >> W;
        sort(W.begin(),W.end(),[](const pii&a, const pii&b) {return a.x < b.x || (a.x == b.x && a.y > b.y);});
        vector<pii> C;
        vector<int> Ig(N+2, 0), Used(N+2, 0);

        for (pii w: W) {
            while (!C.empty() && C.back().y >= w.y) {
                Ig[C.back().x]++;
                Ig[w.x]--;
                Ig[w.y+1]++;
                Ig[C.back().y+1]--;
                C.pop_back();
            }

            Used[w.x]++;
            Used[w.y+1]--;
            C.push_back(w);
        }

        for (int i = 0; i <= N; ++i) {
            Ig[i+1] += Ig[i];
            Used[i+1] += Used[i];
        }

        ConstTree<int, MinOp<int>> T(Ig);
        for (pii c:W) {
            if (T.get(c.x, c.y)) {
                cout << "-1\n";
                return;
            }
        }

        int ans = 0, lo = 0, prev = 0;
        for (pii c:C) {
            if (c.x > prev) {
                int next;
                for (next = max(lo,c.x); Ig[next] && next <= c.y; ++next);
                if (next <= c.y) {
                    prev = next;
                    ++ans;
                }
            }
            lo = c.y+1;
        }

        for (int i = 1; i <= N; ++i) {
            ans += (Used[i] == 0);
        }

        cout << ans << endl;
    }
};
