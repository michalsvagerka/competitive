#include "../l/lib.h"
// #include "../l/mod.h"

class ECandiesAndStones {
public:
    void solve(istream& cin, ostream& cout) {
        int N, M, P; cin >> N >> M >> P;
        vector<int> X(N), Y(M); cin >> X >> Y;
        for (int&x:X) x %= P;
        for (int&y:Y) y %= P;
        vector<pii> D(M, {0,0});
        vector<vector<pii>> R;
        vector<int> CH, W;
        int C = 100;
        D[0] = {(X[0] + Y[0])%P, 0};
        for (int j = 0; j < M-1; ++j) D[j+1] = max(D[j+1], {D[j].x + (X[0] + Y[j+1])%P, D[j].y});

        for (int i = 0; i < N; ++i) {
            if (i % C == 0 || i == N-1) {
                CH.push_back(i);
                R.push_back(D);
                for (int j = 0; j < M; ++j) D[j].y = j;
            }

            if (i != N-1) {
                vector<pii> E(M, {0, 0});
                for (int j = 0; j < M; ++j) {
                    E[j] = max(E[j], {D[j].x + (X[i + 1] + Y[j]) % P, D[j].y});
                }
                
                for (int j = 0; j < M-1; ++j) E[j+1] = max(E[j+1], {E[j].x + (X[i+1] + Y[j+1])%P, E[j].y});

                swap(E, D);
            }
        }

//        cout << R;

        int Q = R.size();
        W.resize(Q);
        int w = M-1;
        W[Q-1] = w;
        for (int i = Q-1; i >= 1; --i) {
            W[i-1] = w = R[i][w].y;
        }
//        cout << W;

        string Ans;
        for (int i = 0; i < Q-1; ++i) {
            int L = CH[i+1] - CH[i];
            vector2<pii> D(L+1, M, {0,0});
            int l = W[i];
            D[0][l] = {R[i][l].x, l};

            for (int j = 0; j < L; ++j) {
                for (int k = l; k < M; ++k) {
                    D[j + 1][k] = max(D[j + 1][k], {D[j][k].x + (X[CH[i] + j + 1] + Y[k]) % P, k});
                }

                for (int k = l; k < M - 1; ++k) {
                    D[j + 1][k + 1] = max(D[j + 1][k + 1],
                                          {D[j + 1][k].x + (X[CH[i] + j + 1] + Y[k + 1]) % P, D[j+1][k].y});
                }
            }

//            cout << D;

            w = W[i+1];
//            cout << "W " << w << ' ';
            string S = "";
            for (int j = L; j > 0; --j) {
                int t = D[j][w].y;
                for (int a = t; a < w; ++a) S += 'S';
                S += 'C';
                w = t;
            }
//            cout << w << endl;
            reverse(S.begin(),S.end());
            Ans += S;
        }

        string S;
        for (int a = 0; a < W[0]; ++a) S += 'S';
        Ans = S + Ans;

        int a = 0, b = 0, t = (X[0]+Y[0])%P;
        for (char c: Ans) {
            if (c == 'C') ++a;
            else ++b;
            t += (X[a] + Y[b])%P;
        }

//        cout << Ans.size() << '\n';
//        cout << t << endl;
        cout << R.back().back().x << '\n';
        cout << Ans << '\n';


    }
};
