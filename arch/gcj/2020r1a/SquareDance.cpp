#include "../l/lib.h"

class SquareDance {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int R, C; cin >> R >> C;
            vector2<int> A(R,C); cin >> A;
            ll cur = 0, tot = 0;
            vector<set<int>> Rows(R), Columns(C);
            for (int i = 0; i < R; ++i) {
                for (int j = 0; j < C; ++j) {
                    Rows[i].insert(j);
                    Columns[j].insert(i);
                    cur += A[i][j];
                }
            }
            auto neigh = [&](int r, int c) {
                vector<pii> Neigh;
                auto it = Rows[r].lower_bound(c);
                if (it != Rows[r].begin()) Neigh.push_back({r,*prev(it)});
                it = Rows[r].upper_bound(c);
                if (it != Rows[r].end()) Neigh.push_back({r,*it});
                it = Columns[c].lower_bound(r);
                if (it != Columns[c].begin()) Neigh.push_back({*prev(it),c});
                it = Columns[c].upper_bound(r);
                if (it != Columns[c].end()) Neigh.push_back({*it,c});
                return Neigh;
            };
            auto elim = [&](int r, int c) {
                int cnt = 0, all = 0;
                for (pii p: neigh(r,c)) {
                    cnt++;
                    all += A[p.x][p.y];
                }
                return cnt && A[r][c]*cnt < all;
            };


            set<pii> Elim;
            for (int r = 0; r < R; ++r) {
                for (int c = 0; c < C; ++c) {
                    if (elim(r,c)) Elim.insert({r,c});
                }
            }

            while (!Elim.empty()) {
                tot += cur;
                for (pii e: Elim) {
                    cur -= A[e.x][e.y];
                    A[e.x][e.y] = 0;
                    Rows[e.x].erase(e.y);
                    Columns[e.y].erase(e.x);
                }

                set<pii> NewElim;
                for (pii e: Elim) {
                    auto nn = neigh(e.x,e.y);
                    for (pii n: nn) {
                        if (elim(n.x, n.y)) {
                            NewElim.insert(n);
                        }
                    }
                }

                swap(NewElim, Elim);
            };

            cout << "Case #" << t+1 << ": " << tot+cur << '\n';
        }
    }
};
