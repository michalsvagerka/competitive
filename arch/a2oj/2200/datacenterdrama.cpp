#include "../l/lib.h"
// #include "../l/mod.h"

class datacenterdrama {
public:
    int N, M;
    vector<vector<pii>> E;
    vector<bool> U;
    vector<pii> S;

    void run(int u, vector<int>&P) {
        while (!E[u].empty() && U[E[u].back().y]) E[u].pop_back();

        if (E[u].empty()) return;

        pii v = E[u].back();
        E[u].pop_back();
        U[v.y] = true;
        P.push_back(v.x);
        run(v.x, P);
    }


    void solve(istream& cin, ostream& cout) {
        cin >> N >> M;
        E.resize(N);
        U = vector<bool>(M, false);
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            E[u].push_back({v,i});
            E[v].push_back({u,i});
        }

        vector<int> Q;
        for (int i = 0; i < N; ++i) {
            while (true) {
                vector<int> P{i};
                run(i, P);
                reverse(P.begin(), P.end());
                run(i, P);

                if (P.size() == 1) {
                    // no more edges
                    break;
                }

                if (P.size() % 2 == 0) {
                    // loop of _odd_ length, just close it
                    P.push_back(P[0]);
                }

                if (P.front() == P.back()) {
                    // this is a closed loop of even length, orient it in any way
                    for (int i = 0; i + 2 < P.size(); i += 2) {
                        S.push_back({P[i], P[i + 1]});
                        S.push_back({P[i + 2], P[i + 1]});
                    }
                } else {
                    // just connect it to the mega loop
                    Q.insert(Q.end(), P.begin(), P.end());
                }
            }
        }

        if (!Q.empty()) {
            if (Q.front() != Q.back()) Q.push_back(Q[0]); // close itself
            if (Q.size()%2 == 0) Q.push_back(Q[0]); // odd length, just add one more
            for (int i = 0; i+2 < Q.size(); i+=2) {
                S.push_back({Q[i], Q[i+1]});
                S.push_back({Q[i+2], Q[i+1]});
            }
        }

        cout << S.size() << '\n';
        for (pii&s:S) {
            cout << s.x+1 << ' ' << s.y+1 << '\n';
        }
    }
};
