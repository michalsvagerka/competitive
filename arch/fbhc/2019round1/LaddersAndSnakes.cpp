#include "../l/lib.h"
#include "../l/util.h"
#include "../l/flow.h"

constexpr int INF = 1e7;

class LaddersAndSnakes {
public:
    int T = 0;
    void solve(istream& cin, ostream& cout) {
        cout << "Case #" << ++T << ": ";
        int N, H; cin >> N >> H;
        vector<pair<int, pii>> S(N); cin >> S;
        sort(S.begin(),S.end());

        PushRelabel<int> G(N+2);
        vector<pii> X{{-1,-1}, {H+1, -1}};
        for (int i = 0; i < N; ++i) {
            if (S[i].y.x == 0) G.AddEdge(N, i, INF);
            if (S[i].y.y == H) G.AddEdge(i, N+1, INF);

            vector<pii> Y;
            for (int j = 0; j < X.size(); ++j) {
                int x = X[j].x;
                if (x < S[i].y.x) Y.push_back(X[j]);
                else if (x <= S[i].y.y) {
                    if (j >= 1 && X[j-1].y != -1) {
                        int len = x - max(S[i].y.x, X[j-1].x);
                        G.AddEdge(X[j-1].y, i, len);
                        G.AddEdge(i, X[j-1].y, len);
                    }
                } else {
                    if (X[j-1].x <= S[i].y.y) {
                        Y.push_back({S[i].y.x, i});
                        Y.push_back({S[i].y.y, X[j - 1].y});

                        if (j >= 1 && X[j-1].y != -1) {
                            int len = S[i].y.y - max(X[j-1].x, S[i].y.x);
                            G.AddEdge(X[j-1].y, i, len);
                            G.AddEdge(i, X[j-1].y, len);
                        }
                    }

                    Y.push_back(X[j]);
                }
            }
            swap(X, Y);
        }

        int f = G.GetMaxFlow(N, N+1);
        if (f >= INF) {
            cout << "-1\n";
        } else {
            cout << f << '\n';
        }
    }
};
