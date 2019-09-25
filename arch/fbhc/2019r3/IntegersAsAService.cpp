#include "../l/lib.h"

class IntegersAsAService {
public:
    void solve(istream& cin, ostream& cout) {
        int T; cin >> T;
        for (int t = 0; t < T; ++t) {
            int N; cin >> N;
            vector<pair<ll,ll>> G, L;
            for (int i = 0; i < N; ++i) {
                string c; int a, b;
                cin >> c >> a >> b;
                if (c == "G") G.push_back({a,b});
                else L.push_back({a,b});
            }

            bool fail = false;
            for (pii g: G) {
                if (g.x % g.y) fail = true;
            }
            for (pii l: L) {
                if (l.y % l.x) fail = true;
            }

            ll X = 1;
            for (auto g: G) {
                X *= g.y / gcd(g.y, X);
                if (X > 1000000000) { fail = true; break; }
            }

            if (!fail) {
                for (auto g: G) {
                    if (gcd(X, g.x) != g.y) {
                        fail = true;
                        break;
                    }
                }
            }
            
            if (!fail) {
                for (auto l: L) {
                    while (true) {
                        auto Q = l.x * X / gcd(X, l.x);
                        if (l.y == Q) break;
                        if (Q > l.y) {
                            fail = true;
                            break;
                        }
                        if (l.y % Q) {
                            fail = true;
                            break;
                        }
                        
                        
                        X *= l.y / Q;
                        if (X > 1000000000) { fail = true; break; }
                    }
                }
            }
            
            if (!fail) {
                for (auto g: G) {
                    if (gcd(X, g.x) != g.y) {
                        fail = true;
                        break;
                    }
                }
            }


            if (!fail) {
                for (auto l: L) {
                    if (l.x * X / gcd(X, l.x) != l.y) {
                        fail = true;
                        break;
                    }
                }
            }

            cout << "Case #" << t+1 << ": " << (fail ? -1 : X) << '\n';
        }
    }
};
