#include "../l/lib.h"
// #include "../l/mod.h"

class saving {
public:
    struct Calc {
        int D; string S;
        int ans;

        void calc() {
            if (D < count(S.begin(),S.end(),'S')) {
                ans = -1;
                return;
            }

            ans = 0;
            while (damage() > D) {
                ++ans;
                for (int i = S.size() - 1; i > 0; --i) {
                    if (S[i] == 'S' && S[i - 1] == 'C') {
                        swap(S[i], S[i - 1]);
                        break;
                    }
                }
            }
        }

        int damage() {
            int t = 0, r = 1;
            for (char s:S) {
                if (s=='S') t+=r;
                else r+=r;
            }
            return t;
        }

        void read(istream& cin) {
            cin >> D >> S;
        }

        void write(ostream &cout) {
            if (ans == -1) cout << "IMPOSSIBLE";
            else cout << ans;
            cout << endl;
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
