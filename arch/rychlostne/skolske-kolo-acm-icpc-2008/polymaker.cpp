#include <unordered_set>
#include "../l/lib.h"
// #include "../l/mod.h"

class polymaker {
public:
    vector<int> P;
    set<set<vector<int>>> R;
    set<vector<int>> S;

    int ans;
    ll q;

    void solve(int t) {
        if (t >= ans) return;
        if (R.count(S) == 1) return;
        R.insert(S);
        ++q;
        set<vector<int>> O;
        for (auto it = S.begin(); it != S.end(); ++it) {
            for (auto it2 = it; it2 != S.end(); ++it2) {
                int c = it->size(), d = it2->size();
                if (c != 1 || (*it)[0] != 0) {
                    vector<int> Z(c + d - 1, 0);
                    for (int i = 0; i < c; ++i) {
                        for (int j = 0; j < d; ++j) {
                            Z[i + j] += (*it)[i] * (*it2)[j];
                        }
                    }
                    int mx = *max_element(Z.begin(),Z.end());
                    if (mx <= 10) O.insert(Z);
                }

                vector<int> Q(max(c, d), 0);
                for (int i = 0; i < c; ++i) {
                    Q[i] += (*it)[i];
                }
                for (int j = 0; j < d; ++j) {
                    Q[j] += (*it2)[j];
                }
                int mx = *max_element(Q.begin(), Q.end());
                if (mx <= 10) O.insert(Q);
            }
        }

        for (auto o: O) {
            if (o == P) {
                ans = t;
                return;
            }

            if (t < 6 && S.find(o) == S.end()) {
                S.insert(o);
                solve(t+1);
                S.erase(o);
            }
        }
    }

    void solve(istream& cin, ostream& cout) {
        ans = 1000;
        int N; cin >> N; ++N;
        P.resize(N); cin >> P;
        reverse(P.begin(),P.end());
        q = 0;

        S.insert({1});
        S.insert({0,1});

        solve(1);

        if (ans == 1000) cout << "too complicated\n";
        else cout << ans << endl;
    }
};
