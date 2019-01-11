#include "../l/lib.h"
// #include "../l/mod.h"

class BNiceTable {
public:

//    vector<string> B;
//    void brute(int R, int C, int r, int c) {
//        if (c == C) {
//            c = 0;
//            r++;
//        }
//
//        if (r == R) {
//            for (auto&b:B) cerr << b << '\n';
//            cerr << endl;
//            return;
//        }
//
//        for (char t : {'A','C','T','G'}) {
//            B[r][c] = t;
//            if ((r!=0 && B[r][c] == B[r-1][c]) || (r!=0 && c!=0 &&B[r][c] == B[r-1][c-1]) || (c!= 0 && B[r][c] == B[r][c-1])
//                || (r!=0 && c!=C-1  && B[r][c] == B[r-1][c+1])) {
//                continue;
//            }
//
//            brute(R, C, r, c+1);
//        }
//    }

    vector<string> trans(const vector<string>&S) {
        int R = S.size();
        int C = S[0].size();
        vector<string> Ans(C, string(R, '_'));
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                Ans[c][r] = S[r][c];
            }
        }
        return Ans;
    }

    pair<int, vector<string>> solve(const vector<string> & S, string T, bool transpose) {
        int R = S.size();
        int C = S[0].size();
        vector<string> Ans(R, string(C, '_'));
        int stay = 0;
        for (int r = 0; r < R; ++r) {


            pii best = {-1,0};
            for (int i = 0; i < 2; ++i) {
                int ok = 0;
                for (int c = 0; c < C; ++c) {
                    ok += T[(r%2)*2 + ((c%2)^i)] == S[r][c];
                }
                best = max(best, {ok, i});
            }

            stay += best.x;
            for (int c = 0; c < C; ++c) {
                Ans[r][c] = T[(r%2)*2 + ((c%2)^best.y)];
            }
        }

        if (transpose) Ans = trans(Ans);
        return {stay, Ans};
    }

    void solve(istream& cin, ostream& cout) {
        int N, M; cin >> N >> M;
        vector<string> S(N);
        cin >> S;

        pair<int, vector<string>> Best = {-1, {}};
        for (int i = 0; i < 2; ++i) {
            Best = max(Best, solve(S, "ACTG", i==1));
            Best = max(Best, solve(S, "AGCT", i==1));
            Best = max(Best, solve(S, "ATCG", i==1));
            Best = max(Best, solve(S, "CTAG", i==1));
            Best = max(Best, solve(S, "CGAT", i==1));
            Best = max(Best, solve(S, "TGAC", i==1));

            S = trans(S);
        }

        for (string &s: Best.y) cout << s << '\n';
    }
};
