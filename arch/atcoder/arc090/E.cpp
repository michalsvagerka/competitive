#include "../../../l/lib.h"
#include "../../../l/mod.h"

class E {
public:
    int N, M;
    int S, T;
    vector<vector<pii>> E;
    vector<FieldMod> W, WR;

    void solve(istream& cin, ostream& cout) {
        cin >> N >> M;
        cin >> S >> T;
        --S; --T;
        E.resize(N);
        W.resize(N);
        WR.resize(N);
        for (int i = 0; i < M; ++i) {
            int u,v,d; cin >> u >> v >> d;
            --u; --v;
            E[u].push_back({v,d});
            E[v].push_back({u,d});
        }

        vector<ll> D(N, 1e15);
        minheap<pair<ll,int>> Q;
        Q.push({0,S});
        D[S] = 0;
        W[S] = 1;
        while (!Q.empty()) {
            auto q = Q.top(); Q.pop();
//            cout << "vertex " << q.y << ' ' << D[q.y] << endl;
            if (D[q.y] != q.x) continue;
            for (pii&e:E[q.y]) {
                if (e.y + q.x < D[e.x]) {
                    D[e.x] = e.y + q.x;
                    Q.push({D[e.x], e.x});
                    W[e.x] = W[q.y];
                } else if (e.y + q.x == D[e.x]) {
                    W[e.x] += W[q.y];
                }
            }
        }

//        cout << D;

        vector<ll> DR(N, 1e15);
        Q.push({0,T});
        DR[T] = 0;
        WR[T] = 1;
        while (!Q.empty()) {
            auto q = Q.top(); Q.pop();
            if (DR[q.y] != q.x) continue;
            for (pii&e:E[q.y]) {
                if (e.y + q.x < DR[e.x]) {
                    DR[e.x] = e.y + q.x;
                    Q.push({DR[e.x], e.x});
                    WR[e.x] = WR[q.y];
                } else if (e.y + q.x == DR[e.x]) {
                    WR[e.x] += WR[q.y];
                }
            }
        }


        vector<bool> U(N, false);
        for (int i = 0; i < N; ++i) {
            U[i] = (D[i] + DR[i] == D[T]);
        }

        FieldMod ans = W[T] * W[T];
        for (int i = 0; i < N; ++i) {
            if (U[i]) {
                if (2*D[i] == D[T]) {
//                    cout << "vertex " << i +1<< " removing " << W[i]*WR[i] << endl;
                    ans -= W[i] * W[i] * WR[i] * WR[i];
                } else if (2*D[i] < D[T]) {
                    for (pii &e:E[i]) {
                        if (U[e.x] && 2*D[e.x] > D[T] && D[e.x] == D[i] + e.y) {

//                            cout << "edge " << i+1 << ' ' << e.x+1 << " removing " << W[i]*WR[e.x] << endl;
                            ans -= W[i] * WR[e.x] * W[i] * WR[e.x];
                        }
                    }
                }
            }
        }

//        cout << W[T] << '\n';
//        cout << W;
//        cout << WR;
        cout << ans << endl;
    }
};
