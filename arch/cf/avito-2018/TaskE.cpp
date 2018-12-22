#include "../l/lib.h"
// #include "../l/mod.h"

class TaskE {
public:
    void solve(istream& cin, ostream& cout) {
        int N; cin >> N;
        vector<int> X(N/2); cin >> X;


        vector<vector<int>> Div(2e5+1);
        for (int i = 1; i <= 2e5; ++i) {
            for (int j = i; j <= 2e5; j+=i) Div[j].push_back(i);
        }

        vector<ll> Ans(N);
        ll cur = 0;
        for (int i = 0; i < N/2; ++i) {
            pair<ll,ll> best = {X[i],X[i]};
            for (int j : Div[X[i]]) {
                if (ll(j)*j >= X[i]) break;
                int twoX = X[i]/j + j;
                int twoY = X[i]/j - j;
                if (twoX % 2 == 0 && twoY % 2 == 0 && twoY/2 > cur) {
                    best = min(best, {twoX/2,twoY/2});
                }
            }

            if (best.x == X[i]) {
                cout << "No\n";
                return;
            }

            Ans[2*i] = best.y*best.y-cur*cur;
            Ans[2*i+1] = X[i];
            cur = best.x;
        }
        cout << "Yes\n" << Ans;
    }
};
