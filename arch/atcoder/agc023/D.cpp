#include "../../../l/lib.h"
// #include "../l/mod.h"

class D {
public:
    void solve(istream& cin, ostream& cout) {
        int N, S; cin >> N >> S;
        vector<int> X(N+1), P(N+1);
        int j = 0, m = -1;
        for (int i = 0; i < N; ++i) {
            int x,p; cin >> x >> p;
            if (m == -1 && x > S) {
                m = j;
                X[j] = S;
                P[j] = 0;
                j++;
            }
            X[j] = x;
            P[j] = p;
            j++;
        }

        if (m == -1) {
            m = N;
            X[N] = S;
            P[N] = 0;
        }

        vector4<ll> D(N+1,N+1,2,N+1,0);
        vector3<ll> E(N+1,N+1,2);
        vector3<int> V(N+1,N+1,N+1,0);
        for (int l = 0; l <= m; ++l) {
            for (int r = N; r >= m; --r) {
                if (l == 0 && r == N) continue;
                for (int q = 0; q < 2; ++q) {
                    bool canLeft = l != 0;
                    bool canRight = r != N;
                    ll vote = 0;
                    int pos = X[q ? r : l];
                    for (int i = 0; i <= N; ++i) {
                        if (i == l-1) { V[i][l][r] = -1; vote += P[i]; }
                        else if (i == r+1) { V[i][l][r] = 1; vote -= P[i]; }
                        else if (i < l || i > r) {
                            ll left = canLeft ? D[l-1][r][0][i] + pos - X[l-1] : 1e18;
                            ll right = canRight ? D[l][r+1][1][i] + X[r+1] - pos : 1e18;
                            if (left <= right) { vote += P[i]; V[i][l][r] = -1; }
                            else { V[i][l][r] = 1; vote -= P[i]; }
                        }
                    }
                    E[l][r][q] = vote;
                    for (int i = 0; i <= N; ++i) {
                        if (i < l || i > r) {
                            if (vote >= 0) {
                                D[l][r][q][i] = D[l-1][r][0][i] + pos - X[l-1];
                            } else {
                                D[l][r][q][i] = D[l][r+1][1][i] + X[r+1] - pos;
                            }
                        }
                    }
                }
            }
        }

        for (int i = 0; i <= N; ++i) {
            cerr << V[i];
        }

        int L = m, R = m, Q = 0;
        ll ans = 0;
        while (L > 0 || R < N) {
            int pos = X[Q ? R : L];

            if (E[L][R][Q] >= 0) {
                cerr << "go left\n";

                ans += pos - X[L-1];
                --L;
                Q = 0;
            } else {
                cerr << "go right\n";

                ans += X[R+1] - pos;
                ++R;
                Q = 1;
            }
        }

        cout << ans << endl;
    }
};
