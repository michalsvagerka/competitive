#include "../../../l/lib.h"
// #include "../l/mod.h"

class waffle {
public:
    struct Calc {
        int R,C,H,V;
        vector<string> A;
        bool possible;

        void calc() {
            int chips = 0;
            for (string a:A) {
                for (char aa:a) {
                    chips += aa == '@';
                }
            }
            if (chips % ((H+1)*(V+1)) != 0) {
                possible = false;
                return;
            }

            if (chips == 0) {
                possible = true;
                return;
            }

            int byRow = chips / (H+1);
            int byPerson = byRow / (V+1);

            int curChips = 0;
            vector<int> HOR{0};
            for (int r = 0; r < R; ++r) {
                for (char aa:A[r]) {
                    curChips += aa == '@';
                }

                if (curChips > byRow) {
                    possible = false;
                    return;
                }

                if (curChips == byRow) {
                    curChips = 0;
                    HOR.push_back(r+1);
                }
            }

            vector<int> COL(H+1, 0);
            for (int c = 0; c < C; ++c) {
                for (int i = 0; i < H+1; ++i) {
                    for (int r = HOR[i]; r < HOR[i+1]; ++r) {
                        COL[i] += A[r][c] == '@';
                        if (COL[i] > byPerson) {
                            possible = false;
                            return;
                        }
                    }
                }

                if (count(COL.begin(),COL.end(),byPerson) == H+1) {
                    fill(COL.begin(),COL.end(),0);
                }
            }

            possible = true;
        }

        void read(istream& cin) {
            cin >> R >> C >> H >> V;
            A.resize(R);
            cin >> A;
        }

        void write(ostream &cout) {
            if (possible) {
                cout << "POSSIBLE";
            } else {
                cout << "IMPOSSIBLE";
            }
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
