#include "../../../l/lib.h"

class ChristmasCandySplit {
public:
    vector<long long> buyMoreBags(vector <int> bags) {
        int N = bags.size();
        lxl S = 1;
        set<int> A(bags.begin(),bags.end());
        int tot = accumulate(bags.begin(),bags.end(),0);
        for (int i = 1; i <= 22; ++i) S = S * i / gcd(S, i);

        cerr << S << endl;
        vector<ll> D;
        for (ll i = 1; i * i <= S; ++i) {
            if (S % i == 0) {
                if (A.count(i) == 0) D.push_back(i);
                if (A.count(S/i) == 0 && i * i != S) D.push_back(S / i);
            }
        }
        sort(D.begin(), D.end());
        S -= tot;
        vector<ll> Ans;
        while (S > 1000) {
            if (S-D.back() > 900) {
                S -= D.back();
                Ans.push_back(D.back());
            }
            D.pop_back();
        }

//        cerr << S << endl;

        int M = D.size();
        vector<ll> Pref(M+1, 0);
        for (int i = 0; i < M; ++i) Pref[i+1] = Pref[i] + D[i];
        vector<map<int,int>> Q(M+1);
        Q[0][S] = -1;
        for (int i = 0; i < M; ++i) {
            for (pii q: Q[i]) {
                if (q.x <= Pref[M-i-1]) Q[i+1][q.x] = q.y;
                if (q.x >= D[M-1-i]) Q[i+1][q.x-D[M-1-i]] = D[M-1-i];
            }
        }

        int cur = 0;
        for (int i = 0; i < M; ++i) {
            if (Q[M-i][cur] > 0) {
                Ans.push_back(Q[M-i][cur]);
                cur += Q[M-i][cur];
            }
        }
        cerr << Ans.size() << endl;
        return Ans;
    }

    void solve(istream& cin, ostream& cout) {
        cout << buyMoreBags({2, 6, 4});
        cout << buyMoreBags({2, 4});
        cout << buyMoreBags({10, 12});
    }
};
