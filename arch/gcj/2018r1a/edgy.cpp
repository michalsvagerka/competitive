#include "../../../l/lib.h"
// #include "../l/mod.h"

class edgy {
public:
    struct Calc {
        int N, P;
        vector<pii> D;
        double ans;

        void calc() {
            int tot = 0;
            vector<pair<double,double>> R;
            for (int i = 0; i < N; ++i) {
                tot += D[i].x + D[i].y;

                vector<pair<double,double>> S;

                double lo = min(D[i].x, D[i].y);
                double hi = sqrt(D[i].x * D[i].x + D[i].y * D[i].y);
                for (auto&r:R) {
                    S.push_back(r);
                    S.emplace_back(r.x + lo, r.y + hi);
                }
                S.emplace_back(lo, hi);

                sort(S.begin(),S.end());
                R.clear();

                for (auto &s:S) {
                    if (!R.empty() && R.back().y >= s.x - (1e-8)) {
                        R.back().y = max(R.back().y, s.y);
                    } else {
                        R.push_back(s);
                    }
                }
            }

            double search = P/2.0 - tot;
            ans = 0.0;
            for (auto &r:R) {
                if (r.x <= search) {
                    ans = min(r.y, search);
                }
            }

            ans += tot;
            ans *= 2;
        }

        void read(istream& cin) {
            cin >> N >> P;
            D.resize(N);
            for (int i = 0; i < N; ++i) {
                cin >> D[i];
            }
            sort(D.begin(),D.end());
            reverse(D.begin(),D.end());
        }

        void write(ostream &cout) {
            cout << fixed << setprecision(10) << ans << endl;
        }
    };


    void solve(istream& cin, ostream& cout) {
        ui T; cin >> T;
        vector<Calc> C(T);
        for (auto &c: C) c.read(cin);
        for (auto &c: C) c.calc();
        for (int t = 0; t < T; ++t) {
            cout << "Case #" << t+1 << ": ";
            C[t].write(cout);
        }
    }
};
