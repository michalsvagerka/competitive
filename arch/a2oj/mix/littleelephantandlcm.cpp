#include "../../../l/lib.h"
 #include "../../../l/mod.h"

class littleelephantandlcm {
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
        int N; cin >> N;
        vector<int> F(1e5+1, 0);
        for (int i = 0; i < N; ++i) {
            int a; cin >> a;
            F[a]++;
        }
        for (int i = 0; i < 1e5; ++i) F[i+1] += F[i];

        S = vector<int>(1e5+1, 0);
        for (int i = 2; i < 1e5 ; ++i) {
            if (S[i] == 0) {
                for (int j = i; j <= 1e5; j += i) {
                    S[j] = i;
                }
            }
        }

        FieldMod ans = 0;
        for (int i = 1; i <= 1e5 ; ++i) {
            int large = F[1e5] - F[i-1];
            if (large) {
                vector<int> D;
                allDivisors(i, D);
                FieldMod cur = FieldMod{int(D.size())}.pow(large) - FieldMod{int(D.size()-1)}.pow(large);
                for (int j = 0; j < D.size()-1; ++j) {
                    cur *= FieldMod{j+1}.pow(F[D[j+1]-1]-F[D[j]-1]);
                }
                ans += cur;
            }
        }
        cout << ans << endl;



    }
};
