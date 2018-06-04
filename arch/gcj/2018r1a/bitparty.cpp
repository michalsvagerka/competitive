#include "../../../l/lib.h"
// #include "../l/mod.h"

class bitparty {
public:
    struct Calc {
        int R,B,C;
        vector<int> M,S,P;
        ll Ans;


        void calc() {
            Ans = bsl(0LL, 2000000000000000000LL, [&](ll T) {
                vector<ll> cnt;
                for (int i = 0; i < C; ++i) {
                    ll count = (T - P[i])/S[i];
                    if (count < 0) count = 0;
                    if (count > M[i]) count = M[i];
                    cnt.push_back(count);
                }

                sort(cnt.begin(),cnt.end());
                reverse(cnt.begin(),cnt.end());
                ll tot = 0;
                for (int r = 0; r < R; ++r) {
                    tot += cnt[r];
                }
                return tot >= B;
            });
        }

        void read(istream& cin) {
            cin >> R >> B >> C;
            M.resize(C);
            S.resize(C);
            P.resize(C);
            for (int i = 0; i < C; ++i) {
                cin >> M[i] >> S[i] >> P[i];
            }
        }

        void write(ostream &cout) {
            cout << Ans << endl;
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
