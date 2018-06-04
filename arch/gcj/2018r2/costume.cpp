#include "../../../l/lib.h"
#include "../../../l/graph.h"

class costume {
public:
    struct Calc {

        vector<vector<int>> A;
        int N, ans = 0;

        void calc() {
            vector<map<int,int>> rows(2*N+1);
            vector<map<int,int>> cols(2*N+1);
            vector<vector<pii>> coords(2*N+1);
            for (int r = 0; r < N; ++r) {
                for (int c = 0; c < N; ++c) {
                    int a = A[r][c];
                    int rr, cc;
                    auto it = rows[a].find(r);
                    if (it == rows[a].end()) {
                        rr = rows[a].size();
                        rows[a][r] = rr;
                    } else {
                        rr = it->y;
                    }


                    it = cols[a].find(c);
                    if (it == cols[a].end()) {
                        cc = cols[a].size();
                        cols[a][c] = cc;
                    } else {
                        cc = it->y;
                    }

                    coords[a].push_back({rr,cc});
                }
            }

            ans = N*N;
            for (int v = 0; v <= 2*N; ++v) {
                int k = rows[v].size();
                if (rows[v].size() >= 2) {
                    Bipartite G(rows[v].size(), cols[v].size());
                    for (pii&c: coords[v]) {
                        G.addEdge(c.x, c.y + rows[v].size());
                    }
                    k = G.matchingSize();
                }
                ans -= k;
            }
        }

        void read(istream& cin) {
            cin >> N;
            A = vector2<int>(N,N);
            cin >> A;
            for (auto &a: A) for (int &aa: a) aa += N;
        }

        void write(ostream &cout) {
            cout << ans << '\n';
        }
    };


    void solve(istream& cin, ostream& cout) {
        ui T; cin >> T;
        for (int t = 1; t <= T; ++t) {
            Calc c;
            c.read(cin);
            c.calc();
            cout << "Case #" << t << ": ";
            c.write(cout);
        }
    }
};
