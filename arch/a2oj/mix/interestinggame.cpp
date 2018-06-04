#include "../../../l/lib.h"
// #include "../l/mod.h"

class interestinggame {
public:
    vector<int> S;

    void allDivisors(const vector<pii>&X, int i, int Q, vector<int>&out) {
        if (i == X.size()) {
            out.push_back(Q);
        } else {
            for (int j = 0; j <= X[i].y; ++j) {
                allDivisors(X, i+1, Q, out);
                Q *= X[i].x;
            }
        }
    }

    void allDivisors(int x, vector<int> &v) {
        vector<pii> X;
        while (x != 1) {
            if (X.empty() || X.back().x != S[x]) X.push_back({S[x], 0});
            X.back().y++;
            x /= S[x];
        }

        allDivisors(X, 0, 1, v);
        sort(v.begin(),v.end());
    }


    void solve(istream& cin, ostream& cout) {
        S = vector<int>(2e5+1, 0);
        for (int i = 2; i < 2e5 ; ++i) {
            if (S[i] == 0) {
                for (int j = i; j <= 2e5; j += i) {
                    S[j] = i;
                }
            }
        }

        int N; cin >> N;

        vector<int> GRP(1e5+1, 0);
        for (int i = 1; i <= 1e5; ++i) {
            vector<int> D;
            allDivisors(2*i, D);
            set<int> G;
            for (int k:D) {
                if (k == 1) continue;
                int a1 = 2*i/k+1-k;
                if (a1 > 0 && a1 % 2 == 0) {
                    a1 /= 2;
                    int g = GRP[a1+k-1] ^ GRP[a1-1];
                    if (i == N && g == 0) {
                        cout << k << endl;
                        return;
                    }

                    G.insert(g);
                }
            }
            int g;
            for (g = 0; G.find(g) != G.end(); ++g);
            GRP[i] = GRP[i-1] ^ g;
        }
        cout << "-1\n";
    }
};
