#include "../l/lib.h"
// #include "../l/mod.h"

class ContestEnvironment {
public:
    struct Calc {
        int N; string A, B;
        bool ans;

        void calc() {
            if (count(B.begin(),B.end(),'#') > 0) ans = false;
            else {
                int mxDiff = 1, prev = 0;
                for (int i = 1; i < N; ++i) {
                    if (A[i] != '#') {
                        mxDiff = max(mxDiff, i-prev);
                        prev = i;
                    }
                }

                int empty = count(A.begin(),A.end(),'.') + count(B.begin(),B.end(),'.');
                ans = empty >= mxDiff + 2;
            }
        }

        void read(istream& cin) {
            cin >> A >> B;
            N = A.size();
        }

        void write(ostream &cout) {
            cout << (ans ? "Possible" : "Impossible");
            cout << '\n';
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
