#include "../l/lib.h"
#include "../l/fenwick.h"

class DEels {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<pair<char, int>> T(N);
        cin >> T;

        set<int> Z;
        for (auto&t:T) Z.insert(t.y);

        int s = 0;
        unordered_map<int, int> I;
        vector<ll> W;
        for (int z : Z) {
            W.push_back(z);
            I[z] = s++;
        }

        Fenwick<ll> F(s, 0LL);
        multiset<ll> G;
        for (auto &t:T) {
            if (t.x == '+') {
                G.insert(t.y);
                F.add(I[t.y], t.y);
            } else {
                G.erase(G.find(t.y));
                F.add(I[t.y], -t.y);
            }

            if (G.empty()) {
                cout << "0\n";
                continue;
            }

            int bad = 0;
            int last = *G.begin();
            while (true) {
                ll tot = F.sum(I[last]+1);
                auto it = G.upper_bound(2*tot);
                if (it == G.end()) break;
                if (F.sum(I[*it]) == tot) {
                    bad++;
                    last = *it;
                } else {
                    last = W[I[*it]-1];
                }
            }

            cout << int(G.size()) - 1 - bad << '\n';
        }
    }
};
