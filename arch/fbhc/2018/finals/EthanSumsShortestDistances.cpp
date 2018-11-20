#include "../l/lib.h"
// #include "../l/mod.h"

class EthanSumsShortestDistances {
public:
    struct Calc {

        int N;
        vector<int> A, B, PA, PB, P;
        ll ans, tot;
        unordered_map<pair<pii,pii>, ll> Mem;

        void calc() {
            Mem.clear();

            P.assign(N+1, 0);
            PA.assign(N+1, 0);
            PB.assign(N+1, 0);

            for (int i = 0; i < N; ++i) {
                PA[i+1] = PA[i] + A[i];
                PB[i+1] = PB[i] + B[i];
                P[i+1] = P[i] + A[i] + B[i];
            }
            tot = P[N];

            ans = best(0, N-1, -1, -1);
            for (int i = 1; i < N; ++i) {
                ans += P[i] * (tot - P[i]);
            }
        }

        ll best(int l, int r, int cl, int cr) {
            if (l > r) return 0;

            auto it = Mem.find({{l,r},{cl,cr}});
            if (it != Mem.end()) return it->y;

            ll cur = 1e18;
            for (int vert = l; vert <= r; ++vert) {
                for (int left = l; left <= vert; ++left) {
                    for (int a = 0; a <= 1; ++a) {
                        ll allLeft = P[left];
                        if (cl != -1 && a != cl) continue;

                        ll d = 0;
                        {
                            ll top = (a == 0) * allLeft, bottom = (a == 1) * allLeft;
                            for (int i = left; i < vert; ++i) {
                                top += A[i];
                                bottom += B[i];
                                d += 2 * top * bottom;
                            }
                        }

                    
                        for (int right = vert; right <= r; ++right) {
                            ll allRight = P[N] - P[right+1];
                            for (int b = 0; b <= 1; ++b) {
                                if (cr != -1 && b != cr) continue;
                                ll cost = 0;
                                ll whole = (PA[right+1] - PA[left]) + (a == 0) * allLeft + (b == 0) * allRight;
                                cost += whole * (tot - whole);

                                ll e = 0;

//                                auto it = R.find({right, b});
//                                if (it != R.end()) e = it->y;
//                                else 
                                {
                                    ll top = (b == 0) * allRight, bottom = (b == 1) * allRight;

                                    for (int i = r; i > vert; --i) {
                                        top += A[i];
                                        bottom += B[i];
                                        e += 2 * top * bottom;
                                    }
                                }
                                
                                cost += d + e + best(l, left-1, cl, a) + best(right+1, r, b, cr);
                                cur = min(cur, cost);
                            }
                        }

                    }
                }
            }

            Mem[{{l,r},{cl,cr}}] = cur;
            return cur;
        }

        void read(istream& cin) {
            cin >> N;
            A.resize(N);
            B.resize(N);
            cin >> A >> B;
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
