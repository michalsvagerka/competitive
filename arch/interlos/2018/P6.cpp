#include "../l/lib.h"
// #include "../l/mod.h"

class P6 {
public:

    string Ans;
    vector<bool> U;
    vector<string> S;vector<vector<pii>> E;

    void solve(int i, string cur) {
        if (cur.size() >= Ans.size()) {
            Ans = cur;
            cerr << Ans.size() << ' ' << Ans << endl;
        }

        for (pii j : E[i]) {
            if (!U[j.x]) {
                U[j.x] = true;
//                cerr << cur << ' ' << S[j.x].substr(j.y) << endl;
                solve(j.x, cur + S[j.x].substr(j.y));
                U[j.x] = false;
            }
        }
    }

    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        U.assign(N, false);
        S.resize(N); cin >> S;

        E.resize(N);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (i != j) {
                    for (int k = 1; k <= int(min(S[i].size(),S[j].size())); ++k) {
                        if (S[i].substr(int(S[i].size())-k, k) == S[j].substr(0, k)) {

//                            cout << S[i].substr(int(S[i].size())-k, k) << ' ' << S[j].substr(0, k) << ' ' << S[i]+S[j].substr(k) << endl;
                            E[i].push_back({j, k});
                            break;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < N; ++i) {
            U[i] = true;
            solve(i, S[i]);
            cerr << "solved " << i << endl;
            U[i] = false;
        }

//        vector<pii> Longest(N);
//        for (int i = 0; i < N; ++i) {
//            Longest[i] = {S[i].size(), -1};
//        }
//
//        for (int i = 0; i < 2*N; ++i) {
//
//            vector<pii> LL = Longest;
//            for (int j = 0; j < N; ++j) {
//                for (pii e: E[j]) {
//                    LL[e.x] = max(LL[e.x], {Longest[j].x + S[e.x].size() - e.y, j});
//                }
//            }
//            cout << LL;
//            swap(LL, Longest);
//        }
cout << E;
    }
};
