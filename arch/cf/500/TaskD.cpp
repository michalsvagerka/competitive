#include "../l/lib.h"
// #include "../l/mod.h"

class TaskD {
public:
void solve(istream& cin, ostream& cout) {
    string S, T; cin >> S >> T;

    auto runs = [](const string &S) {
        int i = 0, r = 0;
        while (i < S.size()) {
            char z = S[i];
            while (i < S.size() && S[i] == z) ++i;
            ++r;
        }
        return r;
    };

    vector<pii> Ans;
    int best = 1e9;

    auto adv = [](int &i, int &s, const string&S) {
        if (i == S.size()) return;
        char z = S[i];
        while (i < S.size() && S[i] == z) { ++i; ++s; }
    };

    auto advRuns = [&](string &S, int runs) {
        int i = 0;
        while (i < S.size() && runs > 0) {
            char z = S[i];
            while (i < S.size() && S[i] == z) ++i;
            --runs;
        }
        return i;
    };

    auto solve = [&](int r1, int r2, int w) {
        vector<pii> Cur;
        int s = 0, t = 0;
        int i = advRuns(S, r1);
        int j = advRuns(T, r2);
        if (i != 0 || j != 0) Cur.push_back({i,j});
        string A = T.substr(0, j) + S.substr(i);
        string B = S.substr(0, i) + T.substr(j);

        i = 0, j = 0;
        if (A[0] == B[0]) {
            adv(w?i:j,w?s:t,w?A:B);
            Cur.push_back({i, j});
            swap(s,t);
        }

        while (i < A.size() || j < B.size()) {
            adv(i,s,A);
            adv(j,t,B);
            if (i == A.size() && j == B.size()) break;

            Cur.push_back({s, t});
            swap(t, s);
        }

        if (Cur.size() < best) { Ans = Cur; best = Cur.size(); }
    };

    int r1 = runs(S), r2 = runs(T), l = 1, h = 2;
    for (int w = 0; w < 2; ++w) {
        for (int z = max(0,(r1-r2)/2-l); z <= min(r1, (r1-r2)/2+h); ++z) {
            solve(z, 0, w);
            solve(z, 1, w);
        }
        for (int z = max(0,(r2-r1)/2-l); z <= min(r2, (r2-r1)/2+h); ++z) {
            solve(0, z, w);
            solve(1, z, w);
        }
    }

    cout << Ans.size() << '\n';
    for (auto ans:Ans) cout << ans << '\n';
}
};
