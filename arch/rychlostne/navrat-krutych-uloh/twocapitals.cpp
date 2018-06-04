#include "../../../l/lib.h"
//#include "../l/random.h"

class twocapitals {
public:
//    void dfs(int r, int c, char d, vector<string>&V, int &tot) {
//        if (r < 0 || r >= V.size() || c < 0 || c >= V[0].size() || V[r][c] != d) return;
//        ++tot;
//        V[r][c] = 'C';
//        dfs(r+1,c,d,V,tot);
//        dfs(r-1,c,d,V,tot);
//        dfs(r,c+1,d,V,tot);
//        dfs(r,c-1,d,V,tot);
//    }
//
//    bool check(vector<string> V, int RA,int CA, int RB,int CB) {
//        if (V[RA][CA] != 'A' || V[RB][CB] != 'B') return false;
//        int ca = 0, cb = 0;
//        dfs(RA,CA,'A',V,ca);
//        dfs(RB,CB,'B',V,cb);
////        cerr << ca << ' ' << cb << ' '  << V.size() * V[0].size() << endl;
////        cerr << V;
//        return ca == cb && ca + cb == V.size() * V[0].size();
//    }
//
//    void brute() {
//
//        random_int D(2,10);
//        for (int i = 0; i < 1000000; ++i) {
//            int R = D(rng), C = D(rng);
//            if (R*C % 2 == 1) continue;
//
//            random_int Rx(0, R-1), Cx(0, C-1);
//            int RA = Rx(rng), RB = Rx(rng), CA = Cx(rng), CB = Cx(rng);
//            auto S = getSolution(R, C, RA, CA, RB, CB);
//            if (S.empty()) continue;
//            if (!check(S, RA, CA, RB, CB)) {
//                cerr << R << ' ' << C << ' ' << RA << ' ' << CA << ' ' << RB << ' ' << CB << endl;
//                for (string &s: S) {
//                    cerr << s << '\n';
//                }
//            }
//        }
//    }

    void solve(istream& cin, ostream& cout) {
//        brute();

        int R, C;
        cin >> R >> C;
        int RA, CA;
        cin >> RA >> CA;
        int RB, CB;
        cin >> RB >> CB;

        auto S = getSolution(R,C,RA,CA,RB,CB);
        if (S.empty()) {
            cout << "IMPOSSIBLE\n";
        } else {
            for (string &s: S) {
                cout << s << '\n';
            }
        }
    }

    vector<string> getSolution(int R,int C,int RA,int CA,int RB,int CB) {
        if (RA == RB && CA == CB) {
            return {};
        }

        bool transposed = false;
        bool revertedR = false;
        bool found = true;

        if (RB == RA) {
            swap(R,C);
            swap(RA,CA);
            swap(RB,CB);
            transposed = true;
        }


        if (RB > RA) {
            revertedR = true;
            RB = R-1-RB;
            RA = R-1-RA;
        }

        vector<string> S(R,string(C,'A'));
        if (C == 1 && RB < R / 2 && RA >= R / 2) {
            for (int c = 0; c < C; ++c) for (int i = 0; i < R / 2; ++i) S[i][c] = 'B';
        } else if (C == 1) {
            return {};
        } else {
            for (int r = 0; r <= RB; ++r) for (int c = 0; c < C; ++c) S[r][c] = 'B';
            int cnt = (RB+1)*C-R*C/2;
            if (cnt > 0) {
                for (int c = 0; c < CB; ++c) for (int r = RB; r >= 0; --r) if (cnt > 0) { --cnt; S[r][c] = 'A'; }
                for (int c = C-1; c > CB; --c) for (int r = RB; r >= 0; --r) if (cnt > 0) { --cnt; S[r][c] = 'A'; }
            } else if (cnt < 0) {
                for (int c = 0; c < CA; ++c) for (int r = RB+1; r < R; ++r) if (cnt < 0) { ++cnt; S[r][c] = 'B'; }
                for (int c = C-1; c > CA; --c) for (int r = RB+1; r < R; ++r) if (cnt < 0) { ++cnt; S[r][c] = 'B'; }
            }
        }

        if (revertedR) {
            reverse(S.begin(),S.end());
            RB = R-1-RB;
            RA = R-1-RA;
        }

        if (transposed) {
            vector<string> Z(C, string(R, 'A'));
            for (int c = 0; c < C; ++c) {
                for (int r = 0; r < R; ++r) {
                    Z[c][r] = S[r][c];
                }
            }
            swap(R,C);
            swap(RA,CA);
            swap(RB,CB);
            return Z;
        } else {
            return S;
        }

    }
};
