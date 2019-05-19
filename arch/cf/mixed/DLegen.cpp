#include "../l/lib.h"

class DLegen {
public:
    int M;
    vector2<ll> combine(const vector2<ll> &X, const vector2<ll> &Y) {
        vector2<ll> V(M, M, -1);
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < M; ++j) {
                for (int k = 0; k < M; ++k) {
                    if (X[i][j] != -1 && Y[j][k] != -1) V[i][k] = max(V[i][k], X[i][j] + Y[j][k]);
                }
            }
        }
        return V;
    }

    void solve(istream& cin, ostream& cout) {
        int N; ll L;
        cin >> N >> L;
        vector<int> A(N); cin >> A;
        vector<string> P(N); cin >> P;

        vector<int> Pref(N+1, 0);
        for (int i = 0; i < N; ++i) Pref[i+1] = Pref[i] + P[i].size();
        M = Pref[N];

        vector2<ll> Pts(M, M, -1);
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < P[i].size(); ++j) {
                for (char c = 'a'; c <= 'z'; ++c) {
                    string t = P[i].substr(0, j) + c;
                    pii next;
                    bool found = false;
                    for (int k = t.size(); !found && k >= 0; --k) {
                        for (int l = 0; !found && l < N; ++l) {
                            if (P[l].size() > k) {
                                bool ok = true;
                                for (int m = 0; ok && m < k; ++m) {
                                    if (P[l][m] != t[t.size()-k+m]) ok = false;
                                }
                                if (ok) {
                                    next = {k,l};
                                    found = true;
                                }
                            }
                        }
                    }

                    ll pts = 0;
                    for (int l = 0; l < N; ++l) {
                        int k = P[l].size();
                        if (k <= t.size()) {
                            bool ok = true; //t.substr(t.size()-k) == P[left]; //true;
                            for (int m = 0; ok && m < k; ++m) {
                                if (P[l][m] != t[t.size()-k+m]) ok = false;
                            }

                            if (ok) pts += A[l];
                        }
                    }
                    int a = Pref[i]+j, b = Pref[next.y] + next.x;
                    Pts[a][b] = max(Pts[a][b], pts);
                }
            }
        }

        vector2<ll> Res = Pts;
        L -= 1;

        while (L) {
            if (L%2) Res = combine(Res, Pts);
            Pts = combine(Pts, Pts);
            L /= 2;
        }

        cout << *max_element(Res[0].begin(),Res[0].end()) << endl;



    }
};
